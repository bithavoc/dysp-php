<?
require_once("dyspControl.inc");

class dyspDataGrid extends dyspContainerControl
{
	//private $columns;
	private $dataSource;
	private $itemStyle; //dyspControlStyle
	private $style; //dyspControlStyle
	private $headerStyle; //dyspControlStyle
	private $keyName;
	
	public function __construct($id)
	{
		parent::__construct($id);
		$this->columns = new ArrayObject();
	}
	
	public function AddColumnInstance(dyspDataColumn $col)
	{
		$col->__SETDG($this);
		$this->Add($col);
		//$this->columns->append($col);
		return $col;
	}
	
	//Add a new column to the grid.
	public function AddColumn($name,$title,dyspControlStyle $headerStyle = null,dyspControlStyle $itemStyle = null)
	{
		$col = new dyspTextColumn($name,$title);
		if($headerStyle != null)
		{
			$col->SetHeaderStyle($headerStyle);
		}
		if($itemStyle != null)
		{
			$col->SetItemStyle($itemStyle);
		}
		$this->AddColumnInstance($col);
		return $col;
	}
	
	public function SetDataSource($list)
	{
		$this->dataSource = $list;
	}
	
	public function SetKeyName($name)
	{
		$this->keyName = $name;
	}
	
	public function GetKeyName()
	{
		return $this->keyName;
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
	
	public function OnLoad()
	{
		foreach($this->GetChildren() as $column)
		{
			$column->ForceLoad();
		}
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
		foreach($this->GetChildren() as $column)
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
			foreach($this->GetChildren() as $column)
			{
				$fieldName =$column->GetName();
				$itCssClass = "";
				if($column->HasItemStyle())
				{
					$itCssClass = $column->GetItemStyle()->GetHtmlAttributesDeclaration();
				}
				echo "<td$itCssClass>";
				/*if(isset($item->{$fieldName})) //Note: only if the field exists, try to render the value.
				{*/
					$column->RenderValue($item); //let the column render byselft
				/*}*/
				echo "</td>";
			}
			echo "</tr>";
		}
		echo "</table>";
	} //OnRender methods
	
}//dyspDataGrid class

class dyspDataColumn extends dyspControl
{
	private $name;
	private $title;
	private $headerStyle;
	private $itemStyle;
	private $dataGrid;
	
	public function __construct($name,$title)
	{
		parent::__construct($name);
		$this->name = $name;
		$this->title = $title;
	}
	public function __SETDG($val)
	{
		//Set the datagrid.
		$this->dataGrid = $val;
	}
	public function GetDataGrid()
	{
		return $this->dataGrid;
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
	
	public function RenderValue($item)
	{
		throw new Exception("RenderValue is not implemented");
	}
	
	protected function GetKeyValue($item)
	{
		return self::GetValue($item,$this->dataGrid->GetKeyName());
	}
	
	protected function GetValue($item,$fieldName = null)
	{
		//Is null is passed, the value for the field is returned.
		$_fieldName = $fieldName;
		if($_fieldName == null)
		{
			$_fieldName = $this->name;
		}
		return $value =$item->{$_fieldName};
	}
	
}//dyspDataColumn

class dyspTextColumn extends dyspDataColumn
{
	public function __construct($name,$title)
	{
		parent::__construct($name,$title);
	}
	
	public function RenderValue($item)
	{
		echo parent::GetValue($item); //Render the default value for the column.
	}
	
}//dyspTextColumn

class dyspLinkColumn extends dyspDataColumn
{
	//private $commandName;
	private $click;
	public function __construct($name,$title)
	{
		parent::__construct($name,$title);
	}
	public function SetClick(dyspEventHandler &$handler)
	{
		$this->click = &$handler;
	}
	protected function OnLoad()
	{
		if($this->GetForm()->IsPostBack())
		{
			if($this->IsEventFired("Click"))
			{
					if($this->click  != null)
					{
						$this->click->Invoke($this->GetEventArg());
					}
			}
		}
		parent::OnLoad();
	}//OnExecute method
	/*public function SetCommandName($name)
	{
		$this->commandName = $name;
	}*/
	
	public function RenderValue($item)
	{
		parent::Render();
		//$this->GetDataGrid()->
		$jsCall =  parent::GenerateClientFunctionEventCall("Click",parent::GetKeyValue($item));
		$text =parent::GetTitle();
		echo "<a href=\"javascript:$jsCall\">$text</a>";
	}
	
}//dyspLinkColumn

?>