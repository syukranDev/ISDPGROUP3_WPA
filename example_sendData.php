<?php


$servername = " ";
$dbname = " ";
$username = " ";
$password = " ";

$value1 = $value2 = $value3 = $value4 = $value5 = $value6 = $value7 = $value8 = $value9 = $value10 = $value11 = $value12 = $value13 = $value14 = $value15 = $value16 = "";

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // $sensor = test_input($_POST["sensor"]);
    // $location = test_input($_POST["location"]);
    $value1 = test_input($_POST["value1"]);
    $value2 = test_input($_POST["value2"]);
    $value3 = test_input($_POST["value3"]);
    $value4 = test_input($_POST["value4"]);
    $value5 = test_input($_POST["value5"]);
    $value6 = test_input($_POST["value6"]);
    $value7 = test_input($_POST["value7"]);
    $value8 = test_input($_POST["value8"]);
    $value9 = test_input($_POST["value9"]);
    $value10 = test_input($_POST["value10"]);
    $value11 = test_input($_POST["value11"]);
    $value12 = test_input($_POST["value12"]);
    $value13 = test_input($_POST["value13"]);
    $value14 = test_input($_POST["value14"]);
    $value15 = test_input($_POST["value15"]);
    $value16 = test_input($_POST["value16"]);
    
    // Create connection
    $conn = new mysqli($servername, $username, $password, $dbname);
    // Check connection
    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    } 
    
    $sql = "INSERT INTO # (value1, value2, value3, value4, value5, value6, value7, value8, value9, value10, value11, value12, value13, value14, value15, value16 ) 
    VALUES (    
            '" . $value1 . "', 
            '" . $value2 . "', 
            '" . $value3 . "',
            '" . $value4 . "', 
            '" . $value5 . "', 
            '" . $value6 . "',
            '" . $value7 . "', 
            '" . $value8 . "', 
            '" . $value9 . "',
            '" . $value10 . "', 
            '" . $value11 . "', 
            '" . $value12 . "',
            '" . $value13 . "', 
            '" . $value14 . "', 
            '" . $value15 . "',
            '" . $value16 . "'
            )";
    
    if ($conn->query($sql) === TRUE) {
        echo "New record created successfully";
    } 
    else {
        echo "Error: " . $sql . "<br>" . $conn->error;
    }

    $conn->close();
}
else {
    echo "No data posted with HTTP POST.";
}

function test_input($data) {
    $data = trim($data);
    $data = stripslashes($data);
    $data = htmlspecialchars($data);
    return $data;
}

