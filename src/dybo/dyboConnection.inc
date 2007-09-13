<?
class dyboConnectionState
{
	private function __construct(){}
	
	//The connection is Open
	const OPEN = 10;
	
	//The connection is Closed
	const CLOSED = 11;
}
class dyboConnectionBase
{
	private $connString;
	private $state;
	protected function __construct($connectionString)
	{
		$this->connString = $connectionString;
		$this->state = dyboConnectionState::CLOSED;
	}
	
	public function Open()
	{
		try
		{
			$this->OnOpen();
			$this->state = dyboConnectionState::OPEN;
		}catch(Exception $ex)
		{
			throw new dyboDataException ("An error occurs when trying to open Connection",$ex);
		}
	}
	
	public function GetConnectionString()
	{
		return $this->connString;
	}
	
	public function CreateCommand()
	{
		return $this->OnCreateCommand($this);
	}
	
	protected function OnCreateCommand($who)
	{
		//Derived classes must override this function.
	}
	
	public function Close()
	{
		$this->OnClose();
	}
	
	public function IsOpen()
	{
		return $this->state != dyboConnectionState::CLOSED;
	}
	
	protected function OnOpen()
	{
		//Derived class overrides from here.
	}
	
	protected function OnClose()
	{
		//Derived class overrides from here.
	}
	public function BeginTransaction()
	{
		$this->OnBeginTransaction();
	}
	public function OnBeginTransaction()
	{
		//Derived classes must override this function.
	}
	
	public function CommitTransaction()
	{
		$this->OnCommitTransaction();
	}
	public function OnCommitTransaction()
	{
		//Derived classes must override this function.
	}
	
	public function RollbackTransaction()
	{
		$this->OnRollbackTransaction();
	}
	public function OnRollbackTransaction()
	{
		//Derived classes must override this function.
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