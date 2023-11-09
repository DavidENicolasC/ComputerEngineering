<?php
//Credenciales de conexion a la base de datos
$hostname = "localhost"; //Servidor. Como es la computadora, por defecto es localhost
$username = "root";      //Usuario por defecto de phpMyAdmin
$password = "";          //Password por defecto de phpMyAdmin
$database = "prestamo_db"; //Base de datos a la que se va a conectar

//Se conecta a la base de datos
$conn = mysqli_connect($hostname, $username, $password, $database);

//Si no se logra conectar a la base de datos
if (!$conn){
    die("connection is failed: " . mysqli_connect_error());
}

echo "Conectado a la base de datos."; //Este mensaje se enviara a la ESP32

if(isset($_POST["material"])) {
    $m = $_POST["material"]; //Codigo del material
    $e = "Bueno";            //Estado del material. Como se registra por primera vez, esta en Buen estado
    $p = "No";            //Si esta prestado. Como se registra por primera vez, No esta prestado

    //Busca el material para evitar duplicados
    $buscarenmateriales = "SELECT * FROM materiales WHERE material = '$m'";
    $resultado = $conn->query($buscarenmateriales);
    //Si no esta, entonces realiza la alta
    if( $resultado->num_rows == 0 )
    {
        $buscarendefectuosos = "SELECT * FROM defectuosos WHERE material = '$m'";
        $resultado = $conn->query($buscarendefectuosos);
        //Si el material estaba en la tabla "defectuosos", y se escanea de nuevo significa que ya ha sido reparado
        if ($resultado->num_rows > 0) {
            //Entonces se retira de la tabla "defectuosos"
            echo " El material era defectuoso y ha sido reparado.";
            $eliminardedefectuosos = "DELETE FROM defectuosos WHERE material = '$m'";
            if (mysqli_query($conn, $eliminardedefectuosos)) {
                echo " Eliminado de materiales defectuosos.";
            } else {
                echo " Error: " . $sql . "<br>" . mysqli_error($conn);
            }
        } else {    //Si no esta, entonces es completamente nuevo
            echo " Material nuevo.";
        }

        //Se inserta el material en la tabla "materiales"
        $sqlinsert = "INSERT INTO materiales (material,estado,prestado) VALUES ('".$m."', '".$e."', '".$p."')";

        //Si el material se logra registrar
        if (mysqli_query($conn, $sqlinsert)) {
        echo " Material dado de alta.";
        } else {
            echo " Error: " . $sql . "<br>" . mysqli_error($conn);
        }
    }
    else    //Si esta, informa del intento de duplicado
    {
        echo " Error: El material ya esta dado de alta.";
        http_response_code(100);
    }
}

?>