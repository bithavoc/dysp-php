<?
include_once("dyboConnection.inc");

class dyboDataCommand
{
	private $commandString;
	private $connection;//dyboConnection
	protected function __construct($connection)
	{
		$this->connection = $connection;
	}
	public function IsEmpty()
	{
		return empty($this->commandString);
	}
	public function SetCommandText($cmd)
	{
		$this->commandString = $cmd;
	}
	public function GetCommandText()
	{
		return $this->commandString;
	}
	public function GetConnection()
	{
		return $this->connection;
	}
	public function Execute()
	{
		if($this->IsEmpty())
		{
			throw new dyboPgException("Can not execute and empty command");
		}
		$this->OnExecute();
	}
	protected function OnExecute()
	{
		//Derived classes override this function.
	}
}

?>