<?
include_once("dyspControl.inc");
class dyspTextBox extends dyspControl
{
	private $click;
	
	public function __construct($id)
	{
		parent::__construct($id);
	}
	public function OnInit()
	{
		parent::OnInit();
		$this->SetText($this->GetPostValue());
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
		$class = $this->GetCssClass();
		if(!empty($class))
		{
			$class = " class=\"$class\" ";
		}
		echo "<input id=\"$id\" name=\"$id\"$class type=\"text\" value=\"$text\"/>";
	} //OnRender methods
	
}//JohanButton class
?>