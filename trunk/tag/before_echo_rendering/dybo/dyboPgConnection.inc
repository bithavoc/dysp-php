<?
include_once("dyboConnection.inc");
include_once("dyboPgCommand.inc");

class dyboPgException extends Exception
{
	public function __construct($message,$code = 0)
	{
		parent::__construct($message,$code);
	}
}

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
			throw new dyboPgException(pg_last_error());
		}
	}//OnOpen method.
	
	protected function OnClose()
	{
		pg_close($this->connId);
	}//OnClose method.
	
	public function _GETID()
	{
		return $this->connId;
	}
	
	protected function OnCreateCommand($who)
	{
		return new dyboPgCommand($who);
	}
	
	public function OnBeginTransaction()
	{
		pg_query($this->connId, "BEGIN TRANSACTION;");
	}
	
	public function OnCommitTransaction()
	{
		pg_query($this->connId, "COMMIT TRANSACTION;");
	}
	
	public function OnRollbackTransaction()
	{
		pg_query($this->connId, "ROLLBACK TRANSACTION;");
	}
}//class
?>