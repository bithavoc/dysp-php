<?
require_once("../../dyspCommon.inc");
require_once("../../dybo/dyboPgConnection.inc");
require_once("../dybo/dyboProductDataManager.inc");
require_once("../testutil.inc");

class ProductCreateForm extends dyspForm
{
	private $txtName;
	private $txtPrice;
	private $btnCreate;
	private $lblFinalMessage;
	
	public function __construct()
	{
		parent::__construct("ProductCreateForm",DYSP_KEY);
		$this->EnableCustomRender();
	}
	
	protected function OnInit()
	{
		parent::OnInit();
		$this->AddHeadItem(new dyspStyleReference("main","ProductsManagement.css"));
		$this->Add($this->txtName = new dyspTextBox("txtName"));
		$this->Add($this->txtPrice = new dyspTextBox("txtPrice"));
		$this->Add($this->btnCreate = new dyspButton("btnCreate"));
		$this->btnCreate->SetClick(new dyspEventHandler(&$this,"btnCreate_Click"));
		$this->btnCreate->SetText("Create");
		
		$this->txtName->SetCssClass("InputBox");
		$this->txtPrice->SetCssClass("InputBox");
		$this->btnCreate->SetCssClass("Action");
		
		
		//$this->Add($this->btnCreate = new dyspButton("btnCreate"));
		
		$this->lblFinalMessage = new dyspLabel("lblFinalMessage","Listo!");
		$this->Add($this->lblFinalMessage);
		
	}
	
	protected function OnLoad()
	{
		parent::OnLoad();
		if(!$this->IsPostBack())
		{
			//echo "IsPost";
			$this->lblFinalMessage->SetVisible(false);
		}
	}
	
	function btnCreate_Click()
	{
		//echo "A guardar!";
		$manager = new dyboProductDataManager();
		
		$newProduct = new ProductDataItem();
		$newProduct->Name=$this->txtName->GetText();
		$newProduct->Price=doubleval($this->txtPrice->GetText());
		$manager->SaveOne($newProduct);
		$this->lblFinalMessage->SetVisible(true);
		$this->lblFinalMessage->SetText("Listo!");
		//echo "label deberia estar en true</br>";
		
	}
	
	protected function OnCustomRender()
	{
		?>
		<p><h1>Create Product</h1></p>
		<p style="font-style:italic">Product Creation</p>
		<div>
			<div  style="width: 250px;float: left; background-color:#8b6914">
			<p><div>Name</div><? $this->txtName->Render(); ?></p>
			<p><div>Price</div><? $this->txtPrice->Render(); ?></p>
			</div>
		</div>
		<div class="HelpPanel">
			Este es el panel de la izquierda. Aqui tenemos una pequeña introduccion de como funciona el panel de la izquierda. Algunos linkx
			para ayuda y asistencia se presentaran en esta posicion. Puede ser que con el cambio de campo se presente la ayuda para el campo.
		</div>
		<div style="width: 250px;background-color:#D0D03D">
		<? $this->btnCreate->Render(); ?>
		<a href="ProductListing.php">View List</a>
		<? $this->lblFinalMessage->Render(); ?>
		</div>
		
		<?
	}
	
}
$frm = new ProductCreateForm();
$frm->Render();
?>