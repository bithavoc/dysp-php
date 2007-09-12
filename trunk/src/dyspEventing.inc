<?
class dyspEventHandler
{

	private $obj;
	private $functionName;
	public function __construct(&$object,$functionName)
	{
		$this->obj = &$object;
		$this->functionName = $functionName;
	}//__construct function
	
	public function Invoke($args = null)
	{
			call_user_func(array(&$this->obj,$this->functionName));
	}//Invoke function
	
}//JohanEventHandler class

?>