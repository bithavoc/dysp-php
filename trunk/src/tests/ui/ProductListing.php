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
	private $btnSearch;
	private $txtSearch;
	
	public function __construct()
	{
		parent::__construct("ProductListing",DYSP_KEY);
		$this->EnableCustomRender();
	}
	
	public function OnInit()
	{
		parent::OnInit();
		$this->btnSearch = new dyspButton("btnSearch");
		$this->btnSearch->SetClick(new dyspEventHandler($this,"btnSearch_Click"));
		$this->Add($this->btnSearch);
		$this->btnSearch->SetText("Go!");
		
		$this->txtSearch = new dyspTextBox("txtSearch");
		$this->Add($this->txtSearch);
		
		$this->AddHeadItem(new dyspStyleReference("main","ProductsManagement.css"));
		
		$this->list = new dyspDataGrid("list");
		
		$this->list->AddColumn("Id","Id");
		$this->list->AddColumn("Name","Nombre");
		$priceColumn = $this->list->AddColumn("Price","Precio",null,new dyspControlStyle());
		$priceColumn->GetItemStyle()->SetTextAlign("right");
		$this->list->AddColumn("IsDisabled","Desactivado");
		
		$this->list->SetStyle(new dyspControlStyle("Grid"));
		$this->list->SetHeaderStyle(new dyspControlStyle("GridHeader"));
		$this->list->SetItemStyle(new dyspControlStyle("GridValueBack"));
		
		$this->Add($this->list);
	}
	public function OnLoad()
	{
		parent::OnLoad();
		if(!$this->IsPostBack())
		{
			$manager = new dyboProductDataManager();
			
			$this->list->SetDataSource($manager->GetList());
		}
	}
	function btnSearch_Click()
	{
		$manager = new dyboProductDataManager();
		
		$this->list->SetDataSource($manager->GetList($this->txtSearch->GetText()));
	}
	protected function OnCustomRender()
	{
		?>
		<div style="width=250px">
		Search: 
		<? $this->txtSearch->Render(); ?>
		<? $this->btnSearch->Render(); ?>
		</div>
		<div>
		<? $this->list->Render(); ?>
		</div>
		<a href="ProductCreate.php">Create</a>
		
		<?
	}
}
$form = new ProductListing();
$form->Render();
?>