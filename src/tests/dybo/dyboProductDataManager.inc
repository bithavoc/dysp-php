<?
require_once("../../dybo/dyboDataManager.inc");
require_once("../testutil.inc");

class ProductDataItem
{
	public $Id;
	public $Name;
	public $Price;
}

class dyboProductDataManager extends dyboDataManagerBase
{
	private $connection;
	
	public function __construct($connection = null)
	{
		if($connection == null)
		{
			$connection = testConnect();
		}
		parent::__construct($connection);
	}
	
	public function SaveOne(ProductDataItem $product)
	{
		$name = $product->Name;
		$price = $product->Price;
		$this->Execute("Insert into products(name,price) Values('$name',$price);");
	}
}

?>