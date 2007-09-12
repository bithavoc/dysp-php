<?
include_once("dyspLiteral.inc");

class dyspLabel extends dyspLiteral
{
	public function __construct($id,$text)
	{
		parent::__construct($id,$text);
	}
	
	protected function OnRender()
	{
		$class = $this->GetCssClass();
		if(!empty($class))
		{
			$class = " class=\"$class\" ";
		}
		$text = $this->GetText();
		return "<div$class>$text</div>";
	}
}
?>