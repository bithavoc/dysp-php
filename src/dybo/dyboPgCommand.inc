<?
require_once("dyboDataCommand.inc");
require_once("dyboDataReader.inc");

class dyboPgDataReader extends dyboDataReader
{
	private $pgQueryId;
	private $row;//as a object from pg_fetch_object
	private $rowsQty;
	private $rowsCount;
	
	public function __construct($command,$pgQueryId)
	{
		parent::__construct($command);
		$this->pgQueryId = $pgQueryId;
		$this->rowsQty = pg_num_rows($pgQueryId);
		$this->rowsCount = 0;
	}
	protected function OnRead()
	{
		if($this->rowsCount == $this->rowsQty)
		{
			return false;
		}
		$this->row = pg_fetch_object($this->pgQueryId);
		if(!$this->row)
		{
			throw new Exception("Aqui no hay ROW FUCKING!");
		}
		$this->rowsCount++;
		return true;
	}
	public function OnGetValue($name,$defaultValue)
	{
		if(!isset($this->row->{$name}))
		{
			return $defaultValue;
			//throw new dyboPgException("Field '$name' does not exist in query");
		}
		return $this->row->{$name};
	}
	protected function OnClose()
	{
		pg_free_result($this->pgQueryId);
	}
}
class dyboPgCommand extends dyboDataCommand
{
	public function __construct($connection)
	{
		parent::__construct($connection);
	}//ctor
	private function internalExecute()
	{
		//Get the POstgreSQL connection id and send the command.
		$ret = pg_query($this->GetConnection()->_GETID(), $this->GetCommandText());
		if(!$ret)
		{
			throw new dyboPgException("Command execution error: " . pg_last_error());
		}
		return $ret;
	}
	protected function OnExecute()
	{
		self::internalExecute();
	}//OnExecute function
	
	protected function OnExecuteReader()
	{
		$ret = self::internalExecute();

		return new dyboPgDataReader($this,$ret);
	}//OnExecute function
}

?>