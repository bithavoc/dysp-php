<?
include_once("dyspControl.inc");
class dyspStateContainer
{
	private $values;
	public function __construct()
	{
		$this->values = array();
	}
	public function Set($key,$value)
	{
		$this->values[$key] = $value;
	}
	public function Get($key)
	{
		if(!isset($this->values[$key]))
		{
			return null;
		}
		return $this->values[$key];
	}
}
class dyspControlState
{
	private $control;
	private $container;
	public function __construct(dyspControl $control,dyspStateContainer $container)
	{
		$this->control = $control;
		$this->container = $container;
	}
	public function GetContainer()
	{
		return $this->container;
	}
	private function getPropName($propKey)
	{
		return  $this->control->GetClientId() . "_" . $propKey;
	}
	public function Set($key,$value)
	{
		$composedKey = $this->getPropName($key);
		$this->container->Set($composedKey,$value);
	}
	public function SetBool($key,$value)
	{
		$composedKey = $this->getPropName($key);
		if(!$value)
		{
			$this->container->Set($composedKey,"F");
		}
		else
			$this->container->Set($composedKey,$value);
	}
	public function GetBool($key,$unsetValue)
	{
		$composedKey = $this->getPropName($key);
		$val =$this->container->Get($composedKey);
		if($val == "F") return false;
		else
		return $unsetValue;
	}
	public function Get($key,$defaultVal)
	{
		$composedKey = $this->getPropName($key);
		$val =$this->container->Get($composedKey);
		if($val == null)
		{
			return $defaultVal;
		}
		return $val;
	}
	public function CreateSubState(dyspControl $control)
	{
		return new dyspControlState($control,$this->container);
	}
}
?>