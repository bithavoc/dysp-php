<?
include_once("dyspState.inc");
include_once("dyspEventing.inc");
class dyspControl extends dyspRenderable
{
	//Visible
	//OnInit()
	//OnLoad
	//OnRender()
	//Init(parent);
	private $parent;
	private $clientId;
	private $viewState;
	private $isInitiated;
	private $isLoaded;
	
	const PostNameKey = "postName";//Event id;
	
	public function __construct($id)
	{
		parent::__construct($id);
		$thid->isLoaded = false;
	}
	
	public function SetVisible($val)
	{
		$this->GetViewState()->SetBool("Visible",$val);
	}
	
	public function GetVisible() //Default=true
	{
		return $this->GetViewState()->GetBool("Visible",true);
	}
	public function SetCssClass($val)
	{
		$this->GetViewState()->Set("CssClass",$val);
	}
	
	public function GetCssClass() //Default=""
	{
		return $this->GetViewState()->Get("CssClass","");
	}
	public function IsInitiated()
	{
		return $this->isInitiated;
	}
	protected function SetAsInitiated()
	{
		$this->isInitiated = true;
	}
	public function GetForm()
	{
		return $this->parent->GetForm();
	}
	protected function SetViewState($val)
	{
			$this->viewState =$val;
	}
	protected function GetViewState()
	{
		if($this->viewState == null)
		{
			$id = $this->GetId();
			throw new Exception("$id has no viewstate");
		}
		return $this->viewState;
	}
	public function GetClientId()
	{
		return $this->clientId;
	}
	public function IsPostBack()
	{
		if(!isset($_POST["formName"] ))
		{
			return false;
		}
		$name = $_POST["formName"] ;
		return !empty($name) && $name == $this->GetForm()->GetId();
	}
	protected function SetClientId($id)
	{
		$this->clientId = $id;
	}
	
	//when the control is added or dinamically rendered, this method is called.
	public function Init(dyspControl $parent)
	{
		$this->SetViewState($parent->viewState->CreateSubState($this));
		$this->parent = $parent;
		$this->UpdateClientId();
		$this->OnInit();
	}
	
	protected function UpdateClientId()
	{
		if($this->parent == null)
		{
			$this->clientId = $this->id;
		}
		else
		{
			$this->clientId = $this->parent->GetClientId() . "$" . $this->id;
		}
	}

	protected function OnInit()
	{
		$this->SetAsInitiated();
	}//OnInit
	
	protected  function OnLoad()
	{
		
	}//OnLoad
	
	protected  function OnRender()
	{
		//Derived classes does not need return anything, just do echo.
	}//OnRender
	
	public function ForceLoad()
	{
		$this->OnInit();
		$this->OnLoad();
		$this->isLoaded = true;
	}
	
	public function Render()
	{
		if(!$this->isLoaded)
		{
			self::ForceLoad();
		}
		if($this->GetVisible())
		{
			$this->OnRender();
		}
	}
	
	public function GenerateClientFunctionEventCall($eventName,$eventArg = "''")
	{
		$formId = $this->GetForm()->GetClientId();
		$clientId = $this->GetClientId();
		return "dysp_submitFormArgs('$formId','$clientId','$eventName',$eventArg)";
	}
	
	protected function GetEventArg()
	{
		return $_POST["postArg"];
	}
	
	protected function IsEventFired($eventName)
	{
		//echo $_POST["controlId"];
		//echo "<br/>";
		//echo $this->GetForm()->GetClientId();
		/*echo "postback4Form=",$_POST["formName"] == $this->GetForm()->GetClientId();
		echo " IsPostBack=",$this->IsPostBack();
		echo " Is EventName =",$_POST[dyspControl::PostNameKey] == $eventName ;
		echo " Is ControlId=",$_POST["controlId"] == $this->GetClientId();
		echo " ControlId='",$_POST["controlId"],"'  ";
		echo " ClientId='",$this->GetClientId(),"'
*/
		$val = $this->IsPostBack() && $_POST["formName"] == $this->GetForm()->GetClientId() && $_POST[dyspControl::PostNameKey] == $eventName && $_POST["controlId"] == $this->GetClientId();
		//echo " IsEvent for CLick on Delete Column:$val<br/>";
		return $val;
	}
	protected function GetPostValue($key = "")
	{
		$id =$this->GetClientId() . $key;
		if(!isset($_POST[$id]))
		{
			return null;
		}
		return  $_POST[$id];
	}
}//dyspControl class

class dyspRenderable
{
	protected $id;
	public function __construct($id)
	{
		$this->id = $id;
	}
	public function GetId()
	{
		return $this->id;
	}
	public function Render()
	{
		//Derived class does not neet return anything, just do echo.
	}
}
class dyspControlStyle
{
	private $cssClass;
	private $styleKeyValues;
	
	public function __construct($cssClass = null)
	{
		$this->cssClass = $cssClass;
	}
	
	public function SetTextAlign($value)
	{
		self::SetProperty("text-align",$value);
	}
	
	/*
	* CssClass
	*/
	public function SetCssClass($class)
	{
		$this->cssClass = $class;
		$this->styleKeyValues = array();
	}
	public function GetCssClass($class)
	{
		return $this->cssClass;
	}
	
	/*
	* SetProperty
	*/
	public function SetProperty($key,$value)
	{
		$this->styleKeyValues[$key] = $value;
	}
	
	/*
	* GetHTML Atts.
	*/
	public function GetHtmlAttributesDeclaration()
	{
		/*
Note: Rendering MUST start with space and ends with space.
*/
		$ret = "";
		if(!empty($this->cssClass))
		{
			$ret = " class=\"" . $this->cssClass . "\"";
		}
		if(count($this->styleKeyValues) > 0)
		{
			$ret .=" style=\"";
			foreach($this->styleKeyValues as $key=>$value)
			{
				$ret .= $key . ":" . $value . ";";
			}
			$ret .= "\" ";
		}
		return $ret;
	}
}
class dyspStyleReference extends dyspRenderable
{
	private $url;
	public function __construct($id,$url)
	{
		parent::__construct($id);
		$this->url = $url;
	}
	public function Render()
	{
		$url = $this->url;
		print "<link rel=\"stylesheet\" type=\"text/css\" href=\"$url\" />";
	}
}
?>