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
$query = sprintf("SELECT id , value13, value14, value15, value16, reading_time FROM id10681925_syukran.SensorData2  ORDER BY id DESC LIMIT 50;");



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
