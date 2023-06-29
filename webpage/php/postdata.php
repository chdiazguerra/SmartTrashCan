<?php

$id = $_GET['id'] ?? null;
$estado = $_GET['estado'] ?? null;

if ($id && $estado && ($estado=="1" || $estado=="2" || $estado=="3")){
    $dbServerName = "localhost";
    $dbUserName = "root";
    $dbPassword = "";
    $dbName = "basura";

    $conn = mysqli_connect($dbServerName, $dbUserName, $dbPassword, $dbName);
    
    date_default_timezone_set("America/Santiago");
    $date = date('Y-m-d H:i:s');

    $sql = "UPDATE state SET estado='$estado', fecha='$date' WHERE id='$id';";
    
    if ($conn->query($sql) === TRUE) {
        echo "Correct";
      } else {
        echo "error " . $conn->error;
      }
} else {
    echo 'error';
}


?>