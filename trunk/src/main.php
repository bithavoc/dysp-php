<?
include_once("dyspCommon.inc");
include_once("dybo/dyboPgConnection.inc");

define("DYSP_KEY","fdsfjj32h4hhnzhsz7z767s8s");

class Form1 extends dyspForm
{
	private $btnSelf;
	private $btnAuto;
	private $txtName;
	
	public function __construct()
	{
		parent::__construct("form1",DYSP_KEY);
	}
	protected function OnInit()
	{
		parent::OnInit();
		$this->AddHeadItem(new dyspStyleReference("mainStyleInclude","style.css"));
		
		//btnSelf
		$this->btnSelf = new dyspButton("btnSelf");
		$this->btnSelf->SetClick(new dyspEventHandler(&$this,"btnSelf_Click"));
		$this->Add($this->btnSelf);
		$this->btnSelf->SetText("Flush");
		
		$this->Add(new dyspBreak);
		
		//btnAuto
		$this->btnAuto = new dyspButton("btnAuto");
		$this->Add($this->btnAuto);
		$this->btnAuto->SetText("Init");
		
		//txtName
		$this->txtName = new dyspTextBox("txtName");
		$this->Add($this->txtName);
		$this->txtName->SetCssClass("TXT");
		
		
	}
	public function btnSelf_Click()
	{
		$this->btnSelf->SetText("Cambio!");
		$this->btnAuto->SetVisible(false);
	}
}

$form1 = new Form1();
$form1->SetTitle("TForm1");
$form1->Render();

$conn = new  dyboPgConnection("host=localhost dbname=db1 user=postgres password=programador");
$conn->Open();
$conn->Close();

?>