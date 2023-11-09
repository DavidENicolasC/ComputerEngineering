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
    $e = "Defectuoso";       //Estado del material. Como se da de baja, es defectuoso

    //Busca el material en la tabla "defectuosos" para evitar duplicados
    $buscarendefectuosos = "SELECT * FROM defectuosos WHERE material = '$m'";
    $resultado = $conn->query($buscarendefectuosos);
    //Si no esta, entonces realiza la baja
    if( $resultado->num_rows == 0 )
    {
        $buscarenmateriales = "SELECT * FROM materiales WHERE material = '$m'";
        $resultado = $conn->query($buscarenmateriales);
        //Si el material estaba en la tabla "materiales", significa que se ha descompuesto
        if ($resultado->num_rows > 0) {
            //Entonces se retira de la tabla "materiales"
            echo " Material registrado ahora defectuoso.";
            $eliminardemateriales = "DELETE FROM materiales WHERE material = '$m'";
            if (mysqli_query($conn, $eliminardemateriales)) {
                echo " Eliminado de materiales.";
            } else {
                echo " Error: " . $sql . "<br>" . mysqli_error($conn);
            }
        } else {    //Si no esta, entonces se acaba de registrar
            echo " Registrado por primera vez.";
        }

        //Se inserta el material en la tabla "defectuosos"
        $sqlinsert = "INSERT INTO defectuosos (material,estado) VALUES ('".$m."', '".$e."')";

        //Si el material se logra registrar
        if (mysqli_query($conn, $sqlinsert)) {
        echo " Material dado de baja.";
        } else {
            echo " Error: " . $sql . "<br>" . mysqli_error($conn);
        }
    }
    else    //Si esta, informa del intento de duplicado
    {
        echo " Error: El material ya esta dado de baja.";
        http_response_code(100);
    }
}

?>