<?php
$dbServerName = "localhost";
$dbUserName = "root";
$dbPassword = "";
$dbName = "basura";

$conn = mysqli_connect($dbServerName, $dbUserName, $dbPassword, $dbName);

$sql = "SELECT * FROM basureros;";

$result = mysqli_query($conn, $sql);

$basureros = array();
while ($row = mysqli_fetch_assoc($result)){
    $basurero = new stdClass();
    $basurero->num = $row['num'];
    $basurero->id = $row['id'];
    $basurero->lat = $row['lat'];
    $basurero->lon = $row['lon'];
    array_push($basureros, $basurero);
}

$myJSON = json_encode($basureros);
echo $myJSON;
?>