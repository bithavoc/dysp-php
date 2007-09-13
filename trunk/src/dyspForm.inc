<?
include_once("dyspContainerControl.inc");
include_once("dyspCrypto.inc");

class dyspForm extends dyspContainerControl
{
	private $crypto;
	private $title;
	private $headers;//CSS Style List.(Generic Array)
	public function __construct($id,$cryptoString)
	{
		parent::__construct($id);
		$this->crypto = new dyspCrypto($cryptoString);
	}
	public function AddHeadItem(dyspRenderable $item)
	{
		if($this->headers == null)
		{
			$this->headers = array();
		}
		$this->headers[$item->GetId()] = $item;
	}
	public function SetTitle($title)
	{
		$title = $title;
	}
	public function GetForm()
	{
		return $this;
	}
	protected function OnInit()
	{
		$isPostback = $this->IsPostBack();
		$container = null;
		
		if($isPostback)
		{
			$encryptedViewState = 	$_POST["__viewState"];
			$container = unserialize($this->crypto->Decrypt($encryptedViewState));
		}
		else
		{
			$container = new dyspStateContainer();
		}
		$this->SetViewState(new dyspControlState($this,$container));
		$this->UpdateClientId();
		$this->SetAsInitiated();
		parent::OnInit();
	}
	public function Render()
	{
		parent::Render();
	}

	protected function OnRender()
	{
		$parts =Explode('/', $_SERVER["PHP_SELF"]);
		$partIndex = count($parts) -1;
		if(!isset($parts[$partIndex]))
		{
			throw new Exception("Can not get formAction");
		}
		$file = $parts[$partIndex];
		$lang = "en";
		$title = $this->title;
		$postName = dyspControl::PostNameKey;
		echo "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\"\n\t\"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">"
					,   "\n<html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"$lang\" lang=\"$lang\"><head><title>$title</title><script src=\"dyspForm.js\" type=\"text/javascript\"></script>";
		if($this->headers != null && count($this->headers) > 0)
		{
			foreach($this->headers as $head)
			{
				$head->Render();
			}
		}
		echo "</head><body><form method=\"post\" action=\"$file\" id=\"" . $this->GetClientId() . "\" name=\"" . $this->GetClientId() . "\"><input type=\"hidden\" name=\"formName\"/><input type=\"hidden\" name=\"$postName\"/><input type=\"hidden\" name=\"postArg\"/><input type=\"hidden\" name=\"controlId\"/>";
		parent::OnRender();
		$vstate = $this->crypto->Encrypt(serialize($this->GetViewState()->GetContainer()));
		echo "<input type=\"hidden\" name=\"__viewState\" value=\"$vstate\"/></form></body></html>";
		//return $val;
	}
}
?>