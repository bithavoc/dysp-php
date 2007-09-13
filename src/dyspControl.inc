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
	
	const PostNameKey = "postName";//Event id;
	
	public function __construct($id)
	{
		parent::__construct($id);
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
	
	public function Render()
	{
		$this->OnInit();
		$this->OnLoad();
		if($this->GetVisible())
		{
			$this->OnRender();
		}
		//return "";
	}
	
	protected function GenerateClientFunctionEventCall($eventName,$eventArg = "''")
	{
		$formId = $this->GetForm()->GetClientId();
		$clientId = $this->GetClientId();
		return "dysp_submitFormArgs('$formId','$clientId','$eventName',$eventArg)";
	}
	
	protected function IsEventFired($eventName)
	{
		return $this->IsPostBack() && $_POST["formName"] == $this->GetForm()->GetClientId() && $_POST[dyspControl::PostNameKey] == $eventName && $_POST["controlId"] == $this->GetClientId();
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