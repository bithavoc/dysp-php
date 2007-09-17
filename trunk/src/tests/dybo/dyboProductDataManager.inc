<?
require_once("../../dybo/dyboDataManager.inc");
require_once("../testutil.inc");

class ProductDataItem
{
	public $Id;
	public $Name;
	public $Price;
	public $IsDisabled;
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
	
	public function GetList($text = "")
	{
		$list = new ArrayObject();
		$query = empty($text) ? "SELECT id,name,price,is_disabled from products;": "SELECT id,name,price,is_disabled from products where name like '%$text%';";
		$reader = $this->ExecuteReader($query);
		while($reader->Read())
		{
			$newItem = new ProductDataItem();
			$newItem->Id = $reader->GetValue("id");
			$newItem->Name = $reader->GetValue("name");
			$newItem->Price = $reader->GetValue("price");
			$newItem->IsDisabled = $reader->GetValue("is_disabled");
			
			$list->append($newItem);
		}
		$reader->Close();
		return $list;
	}
}

?>