<?
require_once("dyboDataCommand.inc");

class dyboDataReader
{
	private $command;
	protected function __construct($command)
	{
		$this->command = $command;
	}
	
	//Returns true if the reader do next row, otherwise,false.
	public function Read()
	{
		return $this->OnRead();
	}
	
	//Derived classes MUST override this function.
	protected function OnRead()
	{
		throw new dyboDataException("DataReader class does not implements Read Operation");
	}
	
	public function GetValue($name,$defaultValue = null)
	{
		return $this->OnGetValue($name,$defaultValue);
	}
	
	public function OnGetValue($name,$defaultValue)
	{
		throw new dyboDataException("DataReader class does not implements GetValue Operation");
	}
	
	public function Close()
	{
		$this->OnClose();
	}
	protected function OnClose()
	{
		throw new dyboDataException("DataReader class does not implements Close Operation");
	}
}

?>