<?
include_once("dyspControl.inc");
class dyspLiteral extends dyspControl
{
	private $tempText;
	public function __construct($id,$text)
	{
		parent::__construct($id);
		$this->tempText = $text;
	}
	protected function OnInit()
	{
		parent::OnInit();
		
		if(!$this->IsPostBack())
		{
			$this->SetText($this->tempText);
		}
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
		return $this->GetText();
	}
}

?>