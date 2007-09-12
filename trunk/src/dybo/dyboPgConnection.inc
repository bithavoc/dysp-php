<?
include_once("dyboConnection.inc");

class dyboPgConnection extends dyboConnectionBase
{
	private $connId;
	public function __construct($connectionString)
	{
		parent::__construct($connectionString);
	}
	
	protected function OnOpen()
	{
		$this->connId = pg_connect($this->GetConnectionString());
		if(!$this->connId)
		{
			throw new Exception(pg_last_error());
		}
	}//OnOpen method.
	
	protected function OnClose()
	{
		pg_close($this->connId);
	}//OnClose method.
	
}//class
?>