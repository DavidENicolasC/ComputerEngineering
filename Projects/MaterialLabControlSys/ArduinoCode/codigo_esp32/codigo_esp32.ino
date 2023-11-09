#include <WiFi.h>              // Librería para establecer la conexión WIFI
#include <WiFiClient.h>        // Librería para crear un cliente WIFI
#include <HTTPClient.h>        //Librería para crear un cliente HTTP
#include <Wire.h>              // Librería para el bus I2C
#include <Adafruit_GFX.h>      // Librería para los gráficos
#include <Adafruit_SH110X.h>  // Librería para el controlador SH1106

#define QR Serial1                        //Objeto que representa al lector de barras
#define i2c_Address 0x3c                  //Direccion de la pantalla OLED
//DATOS QUE SE DEFINEN POR CODIGO
String correcta = String("OSP-01\r");      //Credencial de acceso
const char* ssid = "Wi-Fi IPN";       // Nombre de la red Wi-Fi a la que te conectas
const char* password = "Es1m3Cu231"; // Contraseña de la red Wi-Fi
String strHost = "10.110.150.191";           // Dirección IP del servidor al que te conectas (la de la computadora)

//Pines de los botones de seleccion
int boton1 = 2, boton2 = 4, boton3 = 5;
int boton_actual = 0;

//Leds indicadores
int ledVerde = 32; //Verde
int ledRojo = 33; //Rojo

//Cadenas que almacenan los datos por registrar a la base de datos
String profesor = "";
String credencial_alumno = "";
String material = "";

//Variable que indica a que cadena se debe asignar la entrada leida
int scanning = 0;
//-------------------VARIABLES GLOBALES--------------------------

int contConexion = 0;
String codigo = "";          // Variable para almacenar datos del puerto serial QR
String codigoAnterior = "";  // Variable para almacenar el dato anterior

//Esta variable booleana indica si se debe iniciar o no el sistema
bool accesoconcedido = false;
String credencial = "";

//-------Para poder trabajar con la pantalla OLED----------------
#define ANCHO 128
#define ALTO 64
#define OLED_RESET -1
Adafruit_SH1106G oled = Adafruit_SH1106G(ANCHO, ALTO, &Wire, OLED_RESET);  //Objeto que representa a la pantalla

//-------Para poder trabajar con los botones
int O1 = 0, O2 = 0, O3 = 0;
int ultimoO1 = 0, ultimoO2 = 0, ultimoO3 = 0;

void setup() {
  //Botones
  pinMode(2, INPUT_PULLDOWN);
  pinMode(4, INPUT_PULLDOWN);
  pinMode(5, INPUT_PULLDOWN);

  //Leds
  pinMode(ledVerde, OUTPUT);
  pinMode(ledRojo, OUTPUT);

  Wire.begin();                            // Inicializa el bus I2C
  Serial.begin(921600);
  QR.begin(9600, SERIAL_8N1, 26, 27);  // Configura el puerto serial del lector de códigos QR
  delay(250); //Retardo para que la pantalla OLED se encienda
  oled.begin(i2c_Address, true); //Inicializa la pantalla

  // Conexión a una red WiFi
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);

  oled.clearDisplay();       // Limpia la pantalla
  oled.setTextColor(SH110X_WHITE);  // Establece el color (blanco en una pantalla monocromática)
  oled.setCursor(0, 0);    // Ubica el cursor arriba a la izquierda de la pantalla
  oled.setTextSize(2);       // Establece el tamaño del texto
  oled.println("CONECTANDO");  // Escribe el texto
  oled.println("A");    // Escribe el texto
  oled.println("INTERNET");   //Escribe el texto
  oled.println("...");
  oled.display();            // Muestra en pantalla todo lo establecido anteriormente
  delay(2000);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED and contConexion < 50) {  // Intenta conectarse hasta 50 veces; si no puede, cancela
    ++contConexion;
    delay(500);
    Serial.print(".");
  }
  if (contConexion < 50) {
    Serial.println("");
    Serial.println("Conexión WiFi establecida");
    Serial.print("Dirección IP de la ESP32: ");
    Serial.println(WiFi.localIP());
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledRojo, LOW);
    oled.clearDisplay();       // Limpia la pantalla
    oled.setTextColor(SH110X_WHITE);  // Establece el color (blanco en una pantalla monocromática)
    oled.setCursor(0, 0);    // Ubica el cursor arriba a la izquierda de la pantalla
    oled.setTextSize(2);       // Establece el tamaño del texto
    oled.println("CONEXION");  // Escribe el texto
    oled.println("WIFI");    // Escribe el texto
    oled.println("CORRECTA");   //Escribe el texto
    oled.display();            // Muestra en pantalla todo lo establecido anteriormente
    delay(2000);
  } else {
    Serial.println("");
    Serial.println("Ocurrio un fallo al intentar conectarse a WiFi");
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledRojo, HIGH);
    oled.clearDisplay();       // Limpia la pantalla
    oled.setTextColor(SH110X_WHITE);  // Establece el color (blanco en una pantalla monocromática)
    oled.setCursor(0, 0);    // Ubica el cursor arriba a la izquierda de la pantalla
    oled.setTextSize(2);       // Establece el tamaño del texto
    oled.println("FALLO AL");  // Escribe el texto
    oled.println("CONECTAR");    // Escribe el texto
    oled.println("A WIFI");   //Escribe el texto
    oled.display();            // Muestra en pantalla todo lo establecido anteriormente
    delay(2000);
  }

  // Muestra un mensaje de bienvenida en la pantalla OLED
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledRojo, LOW);
  oled.clearDisplay();       // Limpia la pantalla
  oled.setTextColor(SH110X_WHITE);  // Establece el color (blanco en una pantalla monocromática)
  oled.setCursor(0, 0);    // Ubica el cursor arriba a la izquierda de la pantalla
  oled.setTextSize(2);       // Establece el tamaño del texto
  oled.println("MONITOREO");  // Escribe el texto
  oled.println("MATERIAL");    // Escribe el texto
  oled.println("LAB.");   //Escribe el texto
  oled.println("CONTROL");
  oled.display();            // Muestra en pantalla todo lo establecido anteriormente
  delay(4000);
}

void loop() {
    O1 = digitalRead(2);
    O2 = digitalRead(4);
    O3 = digitalRead(5);

    if( ultimoO1 != O1 || ultimoO2 != O2 || ultimoO3 != O3 )
    {
      ultimoO1 = O1;
      ultimoO2 = O2;
      ultimoO3 = O3;
      //Los if preguntan si solo se seleccionó uno de los 3 botones
      if( ultimoO1 == 1 && ultimoO2 == 0 && ultimoO3 == 0 )
      {
        boton_actual = 1;
        digitalWrite(ledVerde, LOW);
        digitalWrite(ledRojo, LOW);
        oled.clearDisplay();       // Limpia la pantalla
        oled.setTextColor(SH110X_WHITE);  // Establece el color (blanco en una pantalla monocromática)
        oled.setCursor(0, 0);    // Ubica el cursor arriba a la izquierda de la pantalla
        oled.setTextSize(2);       // Establece el tamaño del texto
        oled.println("REGISTRAR");  // Escribe el texto
        oled.println("NUEVO");    // Escribe el texto
        oled.println("MATERIAL");   //Escribe el texto
        oled.display();            // Muestra en pantalla todo lo establecido anteriormente
      }
      if( ultimoO1 == 0 && ultimoO2 == 1 && ultimoO3 == 0 )
      {
        boton_actual = 2;
        digitalWrite(ledVerde, LOW);
        digitalWrite(ledRojo, LOW);
        oled.clearDisplay();       // Limpia la pantalla
        oled.setTextColor(SH110X_WHITE);  // Establece el color (blanco en una pantalla monocromática)
        oled.setCursor(0, 0);    // Ubica el cursor arriba a la izquierda de la pantalla
        oled.setTextSize(2);       // Establece el tamaño del texto
        oled.println("PRESTAR/");  // Escribe el texto
        oled.println("DEVOLVER");    // Escribe el texto
        oled.println("MATERIAL");   //Escribe el texto
        oled.display();            // Muestra en pantalla todo lo establecido anteriormente
      }
      if( ultimoO1 == 0 && ultimoO2 == 0 && ultimoO3 == 1 )
      {
        boton_actual = 3;
        digitalWrite(ledVerde, LOW);
        digitalWrite(ledRojo, LOW);
        oled.clearDisplay();       // Limpia la pantalla
        oled.setTextColor(SH110X_WHITE);  // Establece el color (blanco en una pantalla monocromática)
        oled.setCursor(0, 0);    // Ubica el cursor arriba a la izquierda de la pantalla
        oled.setTextSize(2);       // Establece el tamaño del texto
        oled.println("BAJA");  // Escribe el texto
        oled.println("DE");    // Escribe el texto
        oled.println("MATERIAL");   //Escribe el texto
        oled.display();            // Muestra en pantalla todo lo establecido anteriormente
      }
    }

    if(accesoconcedido == false)
    {
      digitalWrite(ledVerde, LOW);
      digitalWrite(ledRojo, LOW);
      oled.clearDisplay();       // Limpia la pantalla
      oled.setTextColor(SH110X_WHITE);  // Establece el color (blanco en una pantalla monocromática)
      oled.setCursor(0, 0);    // Ubica el cursor arriba a la izquierda de la pantalla
      oled.setTextSize(2);       // Establece el tamaño del texto
      oled.println("ESCANEE");  // Escribe el texto
      oled.println("SU");    // Escribe el texto
      oled.println("CREDENCIAL");   //Escribe el texto
      oled.display();            // Muestra en pantalla todo lo establecido anteriormente
      delay(4000);

      Serial.println("Escanee su credencial");

      while( !QR.available() );

      if (QR.available())  // Comprueba si hay datos entrantes en el búfer del puerto serie del lector de códigos QR
      {
        while (QR.available())  // Continúa leyendo byte a byte hasta que el búfer esté vacío
        {
          credencial += (char)QR.read();    // Lee 1 byte de datos y lo concatena con la cadena del codigo
          delay(5);              // Un pequeño retraso
        }
      }

      int res = credencial.compareTo(correcta);
      delay(500);
      //Una vez capturada la credencial, verifica si es la correcta.
      if(res == 0)
      {
        accesoconcedido = true;
        oled.clearDisplay();       // Limpia la pantalla
        oled.setTextColor(SH110X_WHITE);  // Establece el color (blanco en una pantalla monocromática)
        oled.setCursor(0, 0);    // Ubica el cursor arriba a la izquierda de la pantalla
        oled.setTextSize(2);       // Establece el tamaño del texto
        oled.println("BIENVENIDO");  // Escribe el texto
        oled.println(correcta);    // Escribe el texto
        oled.display();            // Muestra en pantalla todo lo establecido anteriormente
        Serial.println("Bienvenido!");
        digitalWrite(ledVerde, HIGH);
        digitalWrite(ledRojo, LOW);
        delay(2000);
        oled.clearDisplay();       // Limpia la pantalla
        oled.setTextColor(SH110X_WHITE);  // Establece el color (blanco en una pantalla monocromática)
        oled.setCursor(0, 0);    // Ubica el cursor arriba a la izquierda de la pantalla
        oled.setTextSize(2);       // Establece el tamaño del texto
        oled.println("SELECCIONE");  // Escribe el texto
        oled.println("UNA");    // Escribe el texto
        oled.println("OPERACION");   //Escribe el texto
        oled.display();            // Muestra en pantalla todo lo establecido anteriormente
      }
      else if (credencial.length() > 0)
      {
        oled.clearDisplay();       // Limpia la pantalla
        oled.setTextColor(SH110X_WHITE);  // Establece el color (blanco en una pantalla monocromática)
        oled.setCursor(0, 0);    // Ubica el cursor arriba a la izquierda de la pantalla
        oled.setTextSize(2);       // Establece el tamaño del texto
        oled.println("USUARIO");  // Escribe el texto
        oled.println("NO");    // Escribe el texto
        oled.println("RECONOCIDO.");   //Escribe el texto
        oled.display();            // Muestra en pantalla todo lo establecido anteriormente
        Serial.println("Usuario no reconocido.");
        digitalWrite(ledVerde, LOW);
        digitalWrite(ledRojo, HIGH);
        delay(3000);
        accesoconcedido = false;
      }
      credencial = "";
    }
    if(accesoconcedido == true) //Si ya le dieron acceso al sistema
    {
      SistemaDePrestamo();
    }
}

void SistemaDePrestamo()
{
  if (QR.available())  // Comprueba si hay datos entrantes en el búfer del puerto serie del lector de códigos QR
  {
    while (QR.available())  // Continúa leyendo byte a byte hasta que el búfer esté vacío
    {
      codigo += (char)QR.read();    // Lee 1 byte de datos y lo concatena con la cadena del codigo
      delay(5);              // Un pequeño retraso
    }
    Serial.println("codigo: " + codigo);
  }

  if(codigo != "")
  {
    if (boton_actual == 1) { //Boton 1 seleccionado
      Serial.println("Registrando el material escaneado...");
      oled.clearDisplay();       // Limpia la pantalla
      oled.setTextColor(SH110X_WHITE);  // Establece el color (blanco en una pantalla monocromática)
      oled.setCursor(0, 0);    // Ubica el cursor arriba a la izquierda de la pantalla
      oled.setTextSize(2);       // Establece el tamaño del texto
      oled.println("REGISTRANDO");  // Escribe el texto
      oled.println("MATERIAL...");    // Escribe el texto
      oled.display();            // Muestra en pantalla todo lo establecido anteriormente          
      material = codigo;
      String postData = "material=" + material;

      //URL que almacena la dirección para acceder a la petición PHP
      String URL = "http://" + strHost + "/prestamo_proyecto/nuevo_material.php";

      HTTPClient http;
      http.begin(URL);
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
      int httpCode = http.POST(postData);
      String payload = http.getString();
    
      Serial.println("--------------------------------------------------");
      Serial.print("PHP: "); Serial.println(URL);
      Serial.print("Datos: "); Serial.println(postData);
      Serial.print("httpCode: "); Serial.println(httpCode);
      Serial.print("Resultado: "); Serial.println(payload);
      Serial.println("--------------------------------------------------");
          
      if( httpCode == 200 )
      {
        digitalWrite(ledVerde, HIGH);
        digitalWrite(ledRojo, LOW);
        oled.clearDisplay();       // Limpia la pantalla
        oled.setTextColor(SH110X_WHITE);  // Establece el color (blanco en una pantalla monocromática)
        oled.setCursor(0, 0);    // Ubica el cursor arriba a la izquierda de la pantalla
        oled.setTextSize(2);       // Establece el tamaño del texto
        oled.println("NUEVO");  // Escribe el texto
        oled.println("MATERIAL");   // Escribe el texto
        oled.println("REGISTRADO");      //Escribe el texto
        oled.display();            // Muestra en pantalla todo lo establecido anteriormente            
      }
      else if( httpCode == 100 )  //Material duplicado
      {
        digitalWrite(ledVerde, LOW);
        digitalWrite(ledRojo, HIGH);
        oled.clearDisplay();       // Limpia la pantalla
        oled.setTextColor(SH110X_WHITE);  // Establece el color (blanco en una pantalla monocromática)
        oled.setCursor(0, 0);    // Ubica el cursor arriba a la izquierda de la pantalla
        oled.setTextSize(2);       // Establece el tamaño del texto
        oled.println("MATERIAL");  // Escribe el texto
        oled.println("YA");
        oled.println("REGISTRADO");   // Escribe el texto
        oled.display();            // Muestra en pantalla todo lo establecido anteriormente            
      }
      else //Un error que no es especifico
      {
        digitalWrite(ledVerde, LOW);
        digitalWrite(ledRojo, HIGH);
        oled.clearDisplay();       // Limpia la pantalla
        oled.setTextColor(SH110X_WHITE);  // Establece el color (blanco en una pantalla monocromática)
        oled.setCursor(0, 0);    // Ubica el cursor arriba a la izquierda de la pantalla
        oled.setTextSize(2);       // Establece el tamaño del texto
        oled.println("OCURRIO");  // Escribe el texto
        oled.println("UN ERROR");   // Escribe el texto
        oled.println("INESPERADO"); //
        oled.display();            // Muestra en pantalla todo lo establecido anteriormente            
      }

      material = "";
    } else if (boton_actual == 2) { //Boton 2 seleccionado
      Serial.println("Revisando material escaneado...");
      Serial.println(" ");

      oled.clearDisplay();       // Limpia la pantalla
      oled.setTextColor(SH110X_WHITE);  // Establece el color (blanco en una pantalla monocromática)
      oled.setCursor(0, 0);    // Ubica el cursor arriba a la izquierda de la pantalla
      oled.setTextSize(2);       // Establece el tamaño del texto
      oled.println("REVISANDO");  // Escribe el texto
      oled.println("MATERIAL...");    // Escribe el texto
      oled.display();            // Muestra en pantalla todo lo establecido anteriormente          
      material = codigo;
      String postDataConsulta = "material=" + material;

      //URL que almacena la dirección para acceder a la petición PHP
      String URLconsulta = "http://" + strHost + "/prestamo_proyecto/consulta_material.php";

      HTTPClient httpConsulta;
      httpConsulta.begin(URLconsulta);
      httpConsulta.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
      int httpCodeConsulta = httpConsulta.POST(postDataConsulta);
      String payloadConsulta = httpConsulta.getString();

      Serial.println("--------------------------------------------------");
      Serial.print("httpCode: "); Serial.println(httpCodeConsulta);
      Serial.print("Resultado: "); Serial.println(payloadConsulta);
      Serial.println("--------------------------------------------------");
      Serial.println(" ");

      if( httpCodeConsulta == 200 ) //Material disponible
      {
        digitalWrite(ledVerde, HIGH);
        digitalWrite(ledRojo, LOW);
        oled.clearDisplay();       // Limpia la pantalla
        oled.setTextColor(SH110X_WHITE);  // Establece el color (blanco en una pantalla monocromática)
        oled.setCursor(0, 0);    // Ubica el cursor arriba a la izquierda de la pantalla
        oled.setTextSize(2);       // Establece el tamaño del texto
        oled.println("MATERIAL");  // Escribe el texto
        oled.println("DISPONIBLE");   // Escribe el texto
        oled.display();            // Muestra en pantalla todo lo establecido anteriormente
        delay(1000);
        Serial.println("Escanee la credencial del profesor y del alumno, en ese orden");
        Serial.println(" ");
        oled.clearDisplay();       // Limpia la pantalla
        oled.setTextColor(SH110X_WHITE);  // Establece el color (blanco en una pantalla monocromática)
        oled.setCursor(0, 0);    // Ubica el cursor arriba a la izquierda de la pantalla
        oled.setTextSize(2);       // Establece el tamaño del texto
        oled.println("ESCANEE:");  // Escribe el texto
        oled.println("PROFESOR");   // Escribe el texto
        oled.println("ALUMNO");      // Escribe el texto
        oled.display();            // Muestra en pantalla todo lo establecido anteriormente                    

        //Mientras no se hayan escaneado los IDs de profesor y alumno
        while( profesor == "" && credencial_alumno == "" )
        {
          while( !QR.available() );

          if( profesor == "" )
          {
            codigo = "";
            while (QR.available())  // Continúa leyendo byte a byte hasta que el búfer esté vacío
            {
              codigo += (char)QR.read();    // Lee 1 byte de datos y lo concatena con la cadena del codigo
              delay(5);              // Un pequeño retraso
            }
            Serial.println("profesor: " + codigo);
            handleQRCode(codigo);
            codigoAnterior = codigo;
          }

          while( !QR.available() );

          if( credencial_alumno == "" )
          {
            codigo = "";
            while (QR.available())  // Continúa leyendo byte a byte hasta que el búfer esté vacío
            {
              codigo += (char)QR.read();    // Lee 1 byte de datos y lo concatena con la cadena del codigo
              delay(5);              // Un pequeño retraso
            }
            Serial.println("alumno: " + codigo);
            if( codigo != codigoAnterior ) {
              handleQRCode(codigo);
            }
          }
          codigo = "";
        }

        digitalWrite(ledVerde, LOW);
        digitalWrite(ledRojo, LOW);

        oled.clearDisplay();       // Limpia la pantalla
        oled.setTextColor(SH110X_WHITE);  // Establece el color (blanco en una pantalla monocromática)
        oled.setCursor(0, 0);    // Ubica el cursor arriba a la izquierda de la pantalla
        oled.setTextSize(2);       // Establece el tamaño del texto
        oled.println("REGISTRANDO");  // Escribe el texto
        oled.println("PRESTAMO...");    // Escribe el texto
        oled.display();            // Muestra en pantalla todo lo establecido anteriormente          
        String postData = "profesor=" + profesor + "&credencial_alumno=" + credencial_alumno + "&material=" + material;

        //URL que almacena la dirección para acceder a la petición PHP
        String URL = "http://" + strHost + "/prestamo_proyecto/prestamo_registro.php";

        HTTPClient http;
        http.begin(URL);
        http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
        int httpCode = http.POST(postData);
        String payload = http.getString();
    
        Serial.println("--------------------------------------------------");
        Serial.print("PHP: "); Serial.println(URL);
        Serial.print("Datos: "); Serial.println(postData);
        Serial.print("httpCode: "); Serial.println(httpCode);
        Serial.print("Resultado: "); Serial.println(payload);
        Serial.println("--------------------------------------------------");
          
        if( httpCode == 200 )
        {
          digitalWrite(ledVerde, HIGH);
          digitalWrite(ledRojo, LOW);
          oled.clearDisplay();       // Limpia la pantalla
          oled.setTextColor(SH110X_WHITE);  // Establece el color (blanco en una pantalla monocromática)
          oled.setCursor(0, 0);    // Ubica el cursor arriba a la izquierda de la pantalla
          oled.setTextSize(2);       // Establece el tamaño del texto
          oled.println("PRESTAMO");   // Escribe el texto
          oled.println("EXITOSO");      //Escribe el texto
          oled.display();            // Muestra en pantalla todo lo establecido anteriormente            
        }
        else
        {
          digitalWrite(ledVerde, LOW);
          digitalWrite(ledRojo, HIGH);
          oled.clearDisplay();       // Limpia la pantalla
          oled.setTextColor(SH110X_WHITE);  // Establece el color (blanco en una pantalla monocromática)
          oled.setCursor(0, 0);    // Ubica el cursor arriba a la izquierda de la pantalla
          oled.setTextSize(2);       // Establece el tamaño del texto
          oled.println("OCURRIO");  // Escribe el texto
          oled.println("UN ERROR");   // Escribe el texto
          oled.println("INESPERADO");
          oled.display();            // Muestra en pantalla todo lo establecido anteriormente            
        }

        // Reiniciamos las variables y los indicadores para el próximo escaneo
        profesor = "";
        credencial_alumno = "";
      }
      else if( httpCodeConsulta == 100 )  //Material devuelto
      {
        digitalWrite(ledVerde, HIGH);
        digitalWrite(ledRojo, LOW);
        oled.clearDisplay();       // Limpia la pantalla
        oled.setTextColor(SH110X_WHITE);  // Establece el color (blanco en una pantalla monocromática)
        oled.setCursor(0, 0);    // Ubica el cursor arriba a la izquierda de la pantalla
        oled.setTextSize(2);       // Establece el tamaño del texto
        oled.println("MATERIAL");  // Escribe el texto
        oled.println(material);
        oled.println("DEVUELTO");   // Escribe el texto
        oled.display();            // Muestra en pantalla todo lo establecido anteriormente            
      }
      else if( httpCodeConsulta == 207 ) //Material marcado como defectuoso
      {
        digitalWrite(ledVerde, LOW);
        digitalWrite(ledRojo, HIGH);
        oled.clearDisplay();       // Limpia la pantalla
        oled.setTextColor(SH110X_WHITE);  // Establece el color (blanco en una pantalla monocromática)
        oled.setCursor(0, 0);    // Ubica el cursor arriba a la izquierda de la pantalla
        oled.setTextSize(2);       // Establece el tamaño del texto
        oled.println("MATERIAL");  // Escribe el texto
        oled.println("DEFECTUOSO");   // Escribe el texto
        oled.println("NO PRESTAR"); //
        oled.display();            // Muestra en pantalla todo lo establecido anteriormente            
      }
      else if( httpCodeConsulta == 300 ) //Material no registrado
      {
        digitalWrite(ledVerde, LOW);
        digitalWrite(ledRojo, HIGH);
        oled.clearDisplay();       // Limpia la pantalla
        oled.setTextColor(SH110X_WHITE);  // Establece el color (blanco en una pantalla monocromática)
        oled.setCursor(0, 0);    // Ubica el cursor arriba a la izquierda de la pantalla
        oled.setTextSize(2);       // Establece el tamaño del texto
        oled.println("MATERIAL");  // Escribe el texto
        oled.println("NO");   // Escribe el texto
        oled.println("REGISTRADO"); //
        oled.display();            // Muestra en pantalla todo lo establecido anteriormente            
      }
      else //Un error que no es especifico
      {
        digitalWrite(ledVerde, LOW);
        digitalWrite(ledRojo, HIGH);
        oled.clearDisplay();       // Limpia la pantalla
        oled.setTextColor(SH110X_WHITE);  // Establece el color (blanco en una pantalla monocromática)
        oled.setCursor(0, 0);    // Ubica el cursor arriba a la izquierda de la pantalla
        oled.setTextSize(2);       // Establece el tamaño del texto
        oled.println("OCURRIO");  // Escribe el texto
        oled.println("UN ERROR");   // Escribe el texto
        oled.println("INESPERADO"); //
        oled.display();            // Muestra en pantalla todo lo establecido anteriormente            
      }

      material = "";      
    }
    else if(boton_actual == 3)
    {
      Serial.println("Dando de baja el material escaneado...");
      oled.clearDisplay();       // Limpia la pantalla
      oled.setTextColor(SH110X_WHITE);  // Establece el color (blanco en una pantalla monocromática)
      oled.setCursor(0, 0);    // Ubica el cursor arriba a la izquierda de la pantalla
      oled.setTextSize(2);       // Establece el tamaño del texto
      oled.println("DANDO DE");  // Escribe el texto
      oled.println("BAJA");
      oled.println("MATERIAL...");    // Escribe el texto
      oled.display();            // Muestra en pantalla todo lo establecido anteriormente          
      material = codigo;
      String postData = "material=" + material;

      //URL que almacena la dirección para acceder a la petición PHP
      String URL = "http://" + strHost + "/prestamo_proyecto/baja_material.php";

      HTTPClient http;
      http.begin(URL);
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
      int httpCode = http.POST(postData);
      String payload = http.getString();
    
      Serial.println("--------------------------------------------------");
      Serial.print("PHP: "); Serial.println(URL);
      Serial.print("Datos: "); Serial.println(postData);
      Serial.print("httpCode: "); Serial.println(httpCode);
      Serial.print("Resultado: "); Serial.println(payload);
      Serial.println("--------------------------------------------------");
          
      if( httpCode == 200 )
      {
        digitalWrite(ledVerde, HIGH);
        digitalWrite(ledRojo, LOW);
        oled.clearDisplay();       // Limpia la pantalla
        oled.setTextColor(SH110X_WHITE);  // Establece el color (blanco en una pantalla monocromática)
        oled.setCursor(0, 0);    // Ubica el cursor arriba a la izquierda de la pantalla
        oled.setTextSize(2);       // Establece el tamaño del texto
        oled.println("MATERIAL");  // Escribe el texto
        oled.println("DADO DE");   // Escribe el texto
        oled.println("BAJA");      //Escribe el texto
        oled.display();            // Muestra en pantalla todo lo establecido anteriormente            
      }
      else if( httpCode == 100 )  //Material duplicado
      {
        digitalWrite(ledVerde, LOW);
        digitalWrite(ledRojo, HIGH);
        oled.clearDisplay();       // Limpia la pantalla
        oled.setTextColor(SH110X_WHITE);  // Establece el color (blanco en una pantalla monocromática)
        oled.setCursor(0, 0);    // Ubica el cursor arriba a la izquierda de la pantalla
        oled.setTextSize(2);       // Establece el tamaño del texto
        oled.println("MATERIAL");  // Escribe el texto
        oled.println("YA DADO");
        oled.println("DE BAJA");   // Escribe el texto
        oled.display();            // Muestra en pantalla todo lo establecido anteriormente            
      }
      else //Un error que no es especifico
      {
        digitalWrite(ledVerde, LOW);
        digitalWrite(ledRojo, HIGH);
        oled.clearDisplay();       // Limpia la pantalla
        oled.setTextColor(SH110X_WHITE);  // Establece el color (blanco en una pantalla monocromática)
        oled.setCursor(0, 0);    // Ubica el cursor arriba a la izquierda de la pantalla
        oled.setTextSize(2);       // Establece el tamaño del texto
        oled.println("OCURRIO");  // Escribe el texto
        oled.println("UN ERROR");   // Escribe el texto
        oled.println("INESPERADO"); //
        oled.display();            // Muestra en pantalla todo lo establecido anteriormente            
      }

      material = "";
    }
    else
    {
      Serial.println("Error. No hay ninguna operacion seleccionada");
      digitalWrite(ledVerde, LOW);
      digitalWrite(ledRojo, HIGH);
      oled.clearDisplay();       // Limpia la pantalla
      oled.setTextColor(SH110X_WHITE);  // Establece el color (blanco en una pantalla monocromática)
      oled.setCursor(0, 0);    // Ubica el cursor arriba a la izquierda de la pantalla
      oled.setTextSize(2);       // Establece el tamaño del texto
      oled.println("NO HA");  // Escribe el texto
      oled.println("SELECCIONADO");    // Escribe el texto
      oled.println("UNA OPER.");   //Escribe el texto
      oled.display();            // Muestra en pantalla todo lo establecido anteriormente
    }
    codigo = "";
  }
}

void handleQRCode(String input) {
  // Procesar el código QR y asignar los datos a las variables correspondientes
    switch (scanning) {
      case 0:
        profesor = input;
        scanning = 1;
        oled.clearDisplay();       // Limpia la pantalla
        oled.setTextColor(SH110X_WHITE);  // Establece el color (blanco en una pantalla monocromática)
        oled.setCursor(0, 0);    // Ubica el cursor arriba a la izquierda de la pantalla
        oled.setTextSize(2);       // Establece el tamaño del texto
        oled.println("PROFESOR:");  // Escribe el texto
        oled.println(profesor);    // Escribe el texto
        oled.display();            // Muestra en pantalla todo lo establecido anteriormente
        delay(1000);
        break;
      case 1:
        credencial_alumno = input;
        scanning = 0;
        oled.clearDisplay();       // Limpia la pantalla
        oled.setTextColor(SH110X_WHITE);  // Establece el color (blanco en una pantalla monocromática)
        oled.setCursor(0, 0);    // Ubica el cursor arriba a la izquierda de la pantalla
        oled.setTextSize(2);       // Establece el tamaño del texto
        oled.println("ALUMNO:");  // Escribe el texto
        oled.println(credencial_alumno);    // Escribe el texto
        oled.display();            // Muestra en pantalla todo lo establecido anteriormente
        delay(1000);
        break;
    }
}