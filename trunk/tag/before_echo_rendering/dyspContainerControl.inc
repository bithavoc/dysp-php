<?
include_once("dyspControl.inc");

class dyspContainerControl extends dyspControl
{
	private $children;
	
	public function __construct($id)
	{
		parent::__construct($id);
		$this->children = new ArrayObject();
	}
	
	public function Add(dyspControl $control)
	{
		if(!$this->IsInitiated()) //Can't add child control if $this is not initiated.
		{
			$id = $this->GetId();
			throw new Exception("$id is not initiated");
		}
		$control->Init($this);
		$this->children->append($control);
	}
	
	protected function OnRender()
	{
		return $this->RenderChildren();
	}
	
	protected function RenderChildren()
	{
		$val = "";
		foreach($this->children as $child)
		{
			$val .= $child->Render();
		}
		return $val;
	}
	
}//class
?>