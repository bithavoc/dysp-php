<?
require_once "dyboConnection.inc";
require_once "dyboDataCommand.inc";

class dyboDataManagerBase
{
	private $connection;
	
	public function __construct($connection)
	{
		$this->connection = $connection;
	}
	
	protected function Execute($commandText)
	{
		$cmd = $this->connection->CreateCommand();
		$cmd->SetCommandText($commandText);
		$cmd->Execute();
	}
	
	protected function ExecuteReader($commandText)
	{
		$cmd = $this->connection->CreateCommand();
		$cmd->SetCommandText($commandText);
		return $cmd->ExecuteReader();
	}
}

?>