<?
include_once("dyspControl.inc");

class dyspButton extends dyspControl
{
	private $click;
	
	public function __set($key, $val)
	{
		if ($key == "Click")
			$this->click = $val;
	}

	public function __get($key)
	{
		if ($key == "Click")
			return $this->click;
	}
	
	public function __construct($id)
	{
		parent::__construct($id);
		$this->click = null;
	}
	public function SetClick(dyspEventHandler &$handler)
	{
		$this->click = &$handler;
	}
	
	public function SetText($val)
	{
		$this->GetViewState()->Set("text",$val);
	}//SetText method
	
	public function GetText()
	{
		return $this->GetViewState()->Get("text","");
	}//GetText method
	
	protected function OnRender()
	{
		$text = $this->GetText();
		$id = $this->GetClientId();
		$script = $this->GenerateClientFunctionEventCall("Click");
		$class = $this->GetCssClass();
		if(!empty($class))
		{
			$class = " class=\"$class\" ";
		}
		echo "<input id=\"$id\" name=\"$id\" type=\"button\"$class onclick=\"javascript:$script\" value=\"$text\"/>";
	} //OnRender method
	
	protected function OnLoad()
	{
		if($this->GetForm()->IsPostBack())
		{
			if($this->IsEventFired("Click"))
			{
					if($this->click  != null)
					{
						$this->click->Invoke(null);
					}
			}
		}
		parent::OnLoad();
	}//OnExecute method
	
}//JohanButton class
?>