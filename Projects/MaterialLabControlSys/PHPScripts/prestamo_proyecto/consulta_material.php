<?php
//Credenciales de acceso
$hostname = "localhost"; //IP del servidor. Como es la propia computadora, es localhost
$username = "root"; //Usuario
$password = ""; //Contraseña
$database = "prestamo_db"; //Base de Datos

$conn = mysqli_connect($hostname, $username, $password, $database);

if (!$conn){
    die("connection is failed: " . mysqli_connect_error());
}

echo "Conectado a la base de datos.";

if(isset($_POST["material"])) {
    $m = $_POST["material"];
    $o = "No";

    //Busca el material en la tabla "prestamo" para averiguar si es devolucion
    $buscarenprestamos = "SELECT * FROM prestamo WHERE material = '$m'";
    $resultado = $conn->query($buscarenprestamos);
    //Si esta, devuelve el material
    if( $resultado->num_rows > 0 )
    {
        echo "El material estaba prestado.";
        $eliminardeprestamos = "DELETE FROM prestamo WHERE material = '$m'";
        if (mysqli_query($conn, $eliminardeprestamos)) {
            echo " Eliminado de los prestamos.";
        } else {
            echo " Error: " . $eliminardeprestamos . "<br>" . mysqli_error($conn);
        }
        $actualizamaterial = ("UPDATE materiales SET prestado='$o' WHERE material = '$m'");
        if (mysqli_query($conn, $actualizamaterial)) {
            echo " Material marcado como no prestado.";
        } else {
            echo " Error: " . $actualizamaterial . "<br>" . mysqli_error($conn);
        }
        http_response_code(100);
    }
    else
    {
        //Busca el material en la tabla "defectuosos" para evitar prestarlo
        $buscarenprestamos = "SELECT * FROM defectuosos WHERE material = '$m'";
        $resultado = $conn->query($buscarenprestamos);
        //Si esta, notifica que no se debe prestar
        if( $resultado->num_rows > 0 )
        {
            echo "El material esta defectuoso. No se debe prestar";
            http_response_code(207);
        }
        else
        {
            //Busca el material en la tabla "materiales" para prestarlo
            $buscarenprestamos = "SELECT * FROM materiales WHERE material = '$m'";
            $resultado = $conn->query($buscarenprestamos);
            //Si esta, presta el material
            if( $resultado->num_rows > 0 )
            {
                echo "El material esta disponible. Registrando el prestamo...\n";
                http_response_code(200);
            }
            else //Como no esta en ninguna de las tablas, el material no ha sido registrado
            {
                echo "Error: El material no esta registrado en el sistema";
                http_response_code(300);
            }
        }
    }
}

?>