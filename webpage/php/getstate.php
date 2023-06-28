<?php
$dbServerName = "localhost";
$dbUserName = "root";
$dbPassword = "";
$dbName = "basura";

$conn = mysqli_connect($dbServerName, $dbUserName, $dbPassword, $dbName);

$sql = "SELECT * FROM state;";

$result = mysqli_query($conn, $sql);

$basureros = array();
while ($row = mysqli_fetch_assoc($result)){
    $basurero = new stdClass();
    $basurero->id = $row['id'];
    $basurero->estado = $row['estado'];
    $basurero->fecha = $row['fecha'];
    array_push($basureros, $basurero);
}

date_default_timezone_set('America/Santiago');
$current_date = date('Y-m-d H:i:s');

array_push($basureros, $current_date);

$myJSON = json_encode($basureros);
echo $myJSON;
?>