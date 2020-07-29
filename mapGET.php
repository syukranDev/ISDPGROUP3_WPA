<?php
//setting header to json
header('Access-Control-Allow-Origin: *'); 
header('Content-Type: application/json');

//--- Replace # with your db credentials :)
define('DB_HOST', '#');
define('DB_USERNAME', '#');
define('DB_PASSWORD', '#');
define('DB_NAME', '#');

//get connection
$mysqli = new mysqli(DB_HOST, DB_USERNAME, DB_PASSWORD, DB_NAME);

if(!$mysqli){
die("Connection failed: " . $mysqli->error);
}

//query to get data from the table
$query = sprintf("SELECT id , value11,value12, reading_time FROM # ORDER BY id DESC LIMIT 14;");



//execute query
$result = $mysqli->query($query);

//loop through the returned data
$data = array();
foreach ($result as $row) {
$data[] = $row;
}

//free memory associated with result
$result->close();

//close connection
$mysqli->close();

//now print the data
print json_encode($data);

?>
