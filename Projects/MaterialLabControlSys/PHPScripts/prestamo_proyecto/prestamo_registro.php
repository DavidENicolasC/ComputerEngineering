<?php

$hostname = "localhost";
$username = "root";
$password = "";
$database = "prestamo_db";

$conn = mysqli_connect($hostname, $username, $password, $database);

if (!$conn){
    die("connection is failed: " . mysqli_connect_error());
}

echo "Conectado a la base de datos.";

if(isset($_POST["profesor"]) && isset($_POST["credencial_alumno"]) && isset($_POST["material"])) {
    $p = $_POST["profesor"];
    $c = $_POST["credencial_alumno"];
    $m = $_POST["material"];
    $o = "Si";

    $actualizamaterial = ("UPDATE materiales SET prestado = '$o' WHERE material = '$m'");
    if (mysqli_query($conn, $actualizamaterial)) {
        echo " Material marcado como prestado.";
    } else {
        echo " Error: " . $sql . "<br>" . mysqli_error($conn);
    }

    $sql = "INSERT INTO prestamo (profesor, credencial_alumno, material) VALUES ('".$p."', '".$c."', '".$m."')";

    if (mysqli_query($conn, $sql)) {
        echo " Se registro el prestamo con exito.";
    } else {
        echo " Error: " . $sql . "<br>" . mysqli_error($conn);
    }
}

?>
