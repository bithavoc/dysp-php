<?
require_once("../../dyspCommon.inc");
require_once("../../dybo/dyboPgConnection.inc");
require_once("../dybo/dyboProductDataManager.inc");
require_once("../testutil.inc");

class MyItem
{
	public $id;
	public $name;
	public function __get($key)
	{
		if($key == "id") return $this->id;
		if($key == "name") return $this->name;
	}
}
function getData()
{
	$list = new ArrayObject();
	$it = new MyItem;
	$it->id = 0;
	$it->name = "Cero";
	$list->append($it);
	
	$it = new MyItem;
	$it->id = 1;
	$it->name = "One";
	$list->append($it);
	
	$it = new MyItem;
	$it->id = 2;
	$it->name = "Two";
	$list->append($it);
	return $list;
}
class ProductListing extends dyspForm
{
	private $list;
	public function __construct()
	{
		parent::__construct("ProductListing",DYSP_KEY);
		//$this->EnableCustomRender();
	}
	public function OnInit()
	{
		parent::OnInit();
		$this->AddHeadItem(new dyspStyleReference("main","ProductsManagement.css"));
		
		$this->list = new dyspDataGrid("list");
		$this->list->SetDataSource(getData());
		$this->list->AddColumn("id","Id");
		$this->list->AddColumn("name","Nombre");
		
		$newItemStyle = new dyspControlStyle();
		$newItemStyle->SetCssClass("GridValueBack");
		$this->list->SetItemStyle($newItemStyle);
		
		$newItemStyle = new dyspControlStyle();
		$newItemStyle->SetCssClass("Grid");
		$this->list->SetStyle($newItemStyle);
		
		$this->Add($this->list);
	}
}
$form = new ProductListing();
$form->Render();
?>