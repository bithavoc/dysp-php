<?
include_once("dyspCommon.inc");
include_once("dybo/dyboPgConnection.inc");

define("DYSP_KEY","fdsfjj32h4hhnzhsz7z767s8s");

class Form1 extends dyspForm
{
	private $btnSelf;
	private $btnAuto;
	private $btnInsert;
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
		
		//btnInsert
		$this->btnInsert = new dyspButton("btnInsert");
		$this->Add($this->btnInsert);
		$this->btnInsert->SetText("Insert");
		$this->btnInsert->SetClick(new dyspEventHandler(&$this,"btninsert_Click"));
		
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
	
	public function btninsert_Click()
	{
		$name = $this->txtName->GetText();
		$conn = new  dyboPgConnection("host=localhost dbname=db1 user=postgres password=programador");
		$conn->Open();
		$conn->BeginTransaction();
		$cmd = $conn->CreateCommand();
		$cmd->SetCommandText("insert into names(name) values('$name');");
		$cmd->Execute();
		$conn->CommitTransaction();
		$conn->Close();
	}
}

$form1 = new Form1();
$form1->SetTitle("TForm1");
$form1->Render();



?>