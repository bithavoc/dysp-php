<?
class dyboConnectionBase
{
	private $connString;
	
	public function __construct($connectionString)
	{
		$this->connString = $connectionString;
	}
	
	public function Open()
	{
		try
		{
			$this->OnOpen();
		}catch(Exception $ex)
		{
			throw new dyboDataException ("An error occurs when trying to open Connection",$ex);
		}
	}
	
	public function GetConnectionString()
	{
		return $this->connString;
	}
	
	public function Close()
	{
		$this->OnClose();
	}
	protected function OnOpen()
	{
		//Derived class overrides from here.
	}
	
	protected function OnClose()
	{
		//Derived class overrides from here.
	}
}
class dyboDataException extends Exception
{
	private $innerException;
    public function __construct($message, Exception $innerException = null, $code = 0) 
	{
        parent::__construct($message, $code);
		 $this->innerException = $innerException;
    }
}
?>