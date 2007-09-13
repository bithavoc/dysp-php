<?
include_once("dybo/dyboConnection.inc");
include_once("dybo/dyboDataCommand.inc");

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
}

?>