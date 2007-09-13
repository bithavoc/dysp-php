<?
include_once("dyboDataCommand.inc");

class dyboPgCommand extends dyboDataCommand
{
	public function __construct($connection)
	{
		parent::__construct($connection);
	}//ctor
	
	protected function OnExecute()
	{
		//Get the POstgreSQL connection id and send the command.
		$ret = pg_query($this->GetConnection()->_GETID(), $this->GetCommandText());
		if(!$ret)
		{
			throw new dyboPgException("Command execution error: " . pg_last_error());
		}
	}//OnExecute function
}

?>