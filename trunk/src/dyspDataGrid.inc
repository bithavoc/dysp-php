<?
require_once("dyspControl.inc");

class dyspDataGrid extends dyspControl
{
	private $columns;
	private $dataSource;
	private $itemStyle; //dyspControlStyle
	private $style; //dyspControlStyle
	
	public function __construct($id)
	{
		parent::__construct($id);
		$this->columns = new ArrayObject();
	}
	
	//Add a new column to the grid.
	public function AddColumn($name,$title)
	{
		$this->columns->append(new dyspDataColumn($name,$title));
	}
	
	public function SetDataSource($list)
	{
		$this->dataSource = $list;
	}
	
	public function SetStyle(dyspControlStyle $style)
	{
		$this->style = $style;
	}
	
	public function GetStyle()
	{
		return $this->style;
	}
	
	public function SetItemStyle(dyspControlStyle $style)
	{
		$this->itemStyle = $style;
	}
	
	public function GetItemStyle(dyspControlStyle $style)
	{
		return $this->itemStyle;
	}
	
	protected function OnRender()
	{
		if($this->dataSource == null && $this->columns->count() == 0)
		{
			return;
		}
		$id = $this->GetClientId();
		$class = $this->GetCssClass();
		if(!empty($class))
		{
			$class = " class=\"$class\" ";
		}
		
		$tableClassesDec = $this->style == null? "" : $this->style->GetHtmlAttributesDeclaration();
		
		echo "<table $tableClassesDec id=\"$id\" name=\"$id\"$class >";
		echo "<tr>";
		foreach($this->columns as $column)
		{
			echo "<td>";
			echo $column->GetTitle();
			echo "</td>";
		}
		echo "</tr>";
		
		$itemClassesDec = $this->itemStyle == null? "" : $this->itemStyle->GetHtmlAttributesDeclaration();
		
		foreach($this->dataSource as $item)
		{
			echo "<tr>";
			foreach($this->columns as $column)
			{
				echo "<td$itemClassesDec>";
				
				echo $item->{$column->GetName()};
				echo "</td>";
			}
			echo "</tr>";
		}
		echo "</table>";
	} //OnRender methods
}

class dyspDataColumn
{
	private $name;
	private $title;
	
	public function __construct($name,$title)
	{
		$this->name = $name;
		$this->title = $title;
	}
	public function GetName()
	{
		return $this->name;
	}
	public function GetTitle()
	{
		return $this->title;
	}
}
?>