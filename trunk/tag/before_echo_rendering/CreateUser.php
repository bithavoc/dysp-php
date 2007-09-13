<?
include_once("dyspCommon.inc");

define("DYSP_KEY","fdsfjj32h4hhnzhsz7z767s8s");

class Form1 extends dyspForm
{
	private $lblFName;
	private $txtFName;
	
	private $lblLName;
	private $txtLName;
	
	private $lblBirthDay;
	private $txtBirthDay;
	
	public function __construct()
	{
		parent::__construct("f1",DYSP_KEY);
	}
	protected function OnInit()
	{
		parent::OnInit();
		$this->AddHeadItem(new dyspStyleReference("s1","CreateUser.css"));
		
		$this->lblFName = new dyspLabel("lblFName","Nombre");
		$this->Add($this->lblFName);
		$this->lblFName->SetCssClass("LABEL");
		$this->txtFName = new dyspTextBox("txtFName");
		$this->Add($this->txtFName);
		$this->txtFName->SetCssClass("INPUT_FIELD");
		$this->Add(new dyspBreak);
		
		$this->lblLName = new dyspLabel("lblLName","Apellido");
		$this->Add($this->lblLName);
		$this->lblLName->SetCssClass("LABEL");
		
		$this->txtLName = new dyspTextBox("txtLName");
		$this->Add($this->txtLName);
		$this->txtLName->SetCssClass("INPUT_FIELD");
		$this->Add(new dyspBreak);
		
		$this->lblBirthDay = new dyspLabel("lblBirthDay","Fecha Nacimiento");
		$this->Add($this->lblBirthDay);
		$this->lblBirthDay->SetCssClass("LABEL");
		$this->txtBirthDay = new dyspTextBox("txtBirthDay");
		$this->Add($this->txtBirthDay);
		$this->txtBirthDay->SetCssClass("INPUT_FIELD");
		$this->Add(new dyspBreak);

		
		$this->lblComments = new dyspLabel("lblComments","Comentarios");
		$this->Add($this->lblComments);
		$this->lblComments->SetCssClass("LABEL");
		$this->txtComments = new dyspTextBox("txtComments");
		$this->Add($this->txtComments);
		$this->txtComments->SetCssClass("INPUT_FIELD");
		$this->Add(new dyspBreak);
		
		$this->btnCreate = new dyspButton("btnCreate");
		$this->Add($this->btnCreate);
		$this->btnCreate->SetText("Crear");
		$this->Add(new dyspBreak);
	}
}

$form1 = new Form1();
$form1->SetTitle("Crear Usuario");
$form1->Render();
?>