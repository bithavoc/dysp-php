<?
require_once("dyspControl.inc");

class dyspDataGrid extends dyspControl
{
	private $columns;
	private $dataSource;
	private $itemStyle; //dyspControlStyle
	private $style; //dyspControlStyle
	private $headerStyle; //dyspControlStyle
	
	public function __construct($id)
	{
		parent::__construct($id);
		$this->columns = new ArrayObject();
	}
	
	//Add a new column to the grid.
	public function AddColumn($name,$title,dyspControlStyle $headerStyle = null,dyspControlStyle $itemStyle = null)
	{
		$col = new dyspDataColumn($name,$title);
		if($headerStyle != null)
		{
			$col->SetHeaderStyle($headerStyle);
		}
		if($itemStyle != null)
		{
			$col->SetItemStyle($itemStyle);
		}
		$this->columns->append($col);
		return $col;
	}
	
	public function SetDataSource($list)
	{
		$this->dataSource = $list;
	}
	
	/*
	* Style
	*/
	public function SetStyle(dyspControlStyle $style)
	{
		$this->style = $style;
	}
	
	public function GetStyle()
	{
		return $this->style;
	}
	
	/*
	* ItemStyle
	*/
	public function SetItemStyle(dyspControlStyle $style)
	{
		$this->itemStyle = $style;
	}
	
	public function GetItemStyle(dyspControlStyle $style)
	{
		return $this->itemStyle;
	}
	
	/*
	* HeaderStyle
	*/
	public function SetHeaderStyle(dyspControlStyle $style)
	{
		$this->headerStyle = $style;
	}
	
	public function GetHeaderStyle()
	{
		return $this->headerStyle;
	}
	
	/*
	* OnRender
	*/
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
		
		$headerClassesDec = $this->headerStyle == null? "" : $this->headerStyle->GetHtmlAttributesDeclaration();
		
		echo "<tr$headerClassesDec>";
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
			echo "<tr$itemClassesDec>";
			foreach($this->columns as $column)
			{
				$fieldName =$column->GetName();
				$itCssClass = "";
				if($column->HasItemStyle())
				{
					$itCssClass = $column->GetItemStyle()->GetHtmlAttributesDeclaration();
				}
				echo "<td$itCssClass>";
				if(isset($item->{$fieldName})) //Note: only if the field exists, try to render the value.
				{
					echo $item->{$fieldName};
				}
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
	private $headerStyle;
	private $itemStyle;
	
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
	
	/*
	* Header Style.
	*/
	public function SetHeaderStyle(dyspControlStyle $style)
	{
		$this->headerStyle = $style;
	}
	public function GetHeaderStyle()
	{
		return $this->headerStyle;
	}
	public function HasHeaderStyle()
	{
		return $this->headerStyle != null;
	}
	
	/*
	* Item Style.
	*/
	public function SetItemStyle(dyspControlStyle $style)
	{
		$this->itemStyle = $style;
	}
	public function GetItemStyle()
	{
		return $this->itemStyle;
	}
	public function HasItemStyle()
	{
		return $this->itemStyle != null;
	}
}
?>