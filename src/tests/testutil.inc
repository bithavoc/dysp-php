<?
include_once("../../dybo/dyboPgConnection.inc");

define("DYSP_KEY","fdsfjj32h4hhnzhsz7z767s8s");
define("SITE_URL_ROOT","/jhernandez-php/PHPFramework2/");

function testConnect()
{
		$conn = new  dyboPgConnection("host=localhost dbname=db1 user=postgres password=programador");
		$conn->Open();
		return $conn;
}

?>