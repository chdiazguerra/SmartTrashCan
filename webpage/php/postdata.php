<?php

$id = $_GET['id'] ?? null;
$estado = $_GET['estado'] ?? null;

if ($id && $estado){
    $dbServerName = "localhost";
    $dbUserName = "root";
    $dbPassword = "";
    $dbName = "basura";

    $conn = mysqli_connect($dbServerName, $dbUserName, $dbPassword, $dbName);

    $sql = "UPDATE state SET estado='$estado', fecha=CURRENT_TIMESTAMP() WHERE id='$id';";//"INSERT INTO state (id, estado) VALUES ('$id', '$estado') ON DUPLICATE KEY UPDATE estado = '$estado';";
    
    if ($conn->query($sql) === TRUE) {
        echo "Correct";
      } else {
        echo "error";//"Error: " . $sql . "<br>" . $conn->error;
      }
} else {
    echo 'error';
}


?>