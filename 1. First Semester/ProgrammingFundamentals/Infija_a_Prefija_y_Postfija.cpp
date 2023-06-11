/*
Programa. Convertir Notación Infija a: 
          1. Prefija
          2. Postfija
          utilizando una clase Pila
          definida por el usuario
*/
#include<iostream>

using namespace std;

class Pila
{
    private:
        char p[50]; //El arreglo que almacena la pila
        int tope; //guarda la posición del último elemento en la pila, osea en el tope
    public:
        //constructor. Establece los valores iniciales de la pila
        Pila(void)
        {
            tope = -1;
            /*
            Inicialmente, tope
            guarda -1, lo que significa
            que no hay elementos en
            la pila
            */
        }
        
        //Se encarga de meter caracteres a la pila
        void mete( char c ) //c guarda el carácter a meter
        {
            p[++tope] = c;
            /*
            la variable tope es la que
            guarda la posición donde se
            encuentra el último carácter
            metido a la pila. Al ejecutar
            la instrucción anterior, primero,
            como el operador ++ está adelante
            de la variable tope (++tope), primero
            se le suma uno al valor de tope para
            que "se mueva" a la siguiente posición
            en el arreglo, que está vacía, y luego
            coloca en esa posición (que está vacía)
            el nuevo carácter a meter en la pila, que 
            se le pasó como parámetro en la variable
            c (char c)
            */
        }
        
        //Se encarga de sacar caracteres de la pila
        char saca(void)
        {
            return p[tope--];
            /*
            la variable tope es la que guarda
            la posición en el arreglo del último
            carácter metido a la pila. como la pila
            es una estructura de dato LIFO (último
            en entrar, primero en salir), y tope
            señala al último carácter en entrar,
            se devuelve el carácter que está siendo 
            apuntado por tope. Ahora, como el operador
            -- está después de tope (tope--), primero se
            hace todo lo anterior y después se le quita
            1 al valor de tope para que "se mueva" a la
            posición anterior y así ignore al último 
            carácter que se acaba de sacar, dando a entender
            que ya se eliminó de la pila
            */
        }
        
        //Nos indica si la pila esta vacia. Muy útil
        bool estaVacia(void) //bool sólo devuelve dos valores: true (1 o verdadero), false (0 o falso)
        {
            return tope == -1;
            /*
            Como habiamos dicho, al
            inicio tope guarda -1, lo
            que significa que no hay 
            elementos en la pila. La expresión
            anterior se ejecuta de la siguiente manera:
            Se compara el valor de tope con -1. Si 
            tope es igual a -1 (guarda -1), entonces
            la expresión anterior es cierta y se 
            evalúa como un valor true, y eso se devuelve.
            Esto indica que no hay elementos en la pila.
            Si tope no guarda -1, entonces la expresión
            anterior es falsa y se evalúa como un valor
            false, y eso es lo que se devuelve.
            Esto quiere decir que tope guarda un valor de
            0 para arriba, lo que significa que sí está
            apuntando a algún elemento dentro de la pila,
            y por lo tanto, no está vacía.
            */
        }
};

void Infija_a_Prefija(char *origen) //recibe la cadena original
{
    Pila pila; //La pila de los operadores
    Pila resultado; //Segun el procedimiento, al final debemos invertir la cadena formada. Una pila es perfecta para eso.
    
    int i=0; //nos ayuda a recorrer la cadena original
    
    while( origen[i] != '\0' ) //Se posiciona al final de la cadena para comenzar a leer de derecha a izquierda
        i++;
    
    while( i>=0 ) //0 es la última posición hacia la izquierda
    {
        if( origen[i] >= '0' && origen[i] <= '9' ) //Es un operando, osea un numero
            resultado.mete( origen[i] ); //se agrega directamente al resultado
        else if( origen[i] == ')' || origen[i] == '+' || origen[i] == '-' || origen[i] == '/' || origen[i] == '*' ) //es operador o parentesis de apertura
        {
                pila.mete( origen[i] ); //ingresa el carácter en la pila
        }
        /*
        Cuando nos encontremos un paréntesis
        de cerrado, tenemos que agregar los operandos
        de la pila hasta que nos encontremos con el
        paréntesis de abierto que le corresponde a este
        paréntesis de cerrado que nos acabamos de
        encontrar. Por supuesto, los paréntesis no van
        dentro de la expresión final.
        */
        else if( origen[i] == '(' ) //el if es innecesario; basta con un else. Sin embargo, se coloca para que entienda un poquito mejor
        {
            char a = pila.saca(); // se saca el primer operando de la pila
            
            do
            {
                if( a != ')' ) //si no es paréntesis de abierto
                    resultado.mete( a ); //lo imprime
                if( !pila.estaVacia() ) //si la pila aún tiene operadores
                    a = pila.saca(); //vuelve a sacar otro carácter de la pila
            }
            while( a != ')' ); //mientras no se saque de la pila un paréntesis de abierto
        }
        i--; //avanza al siguiente carácter en la cadena original (recordemos que es hacia la izquierda)
    }
    /*
    Como ya no hay mas caracteres por leer,
    ahora se agregan todos los operadores de la
    pila hasta dejarla vacía. Por supuesto, los
    paréntesis no cuentan
    */
    char a = pila.saca(); // se saca el primer operando de la pila       
    do
    {
        if( a != ')' ) //si no es paréntesis de abierto
            resultado.mete( a ); //lo imprime
        if( !pila.estaVacia() ) //si la pila aún tiene operadores
            a = pila.saca(); //vuelve a sacar otro carácter de la pila
    }while( !pila.estaVacia() ); //mientras la pila no se vacíe
    
    //Finalmente, se imprime el resultado invertido aprovechando la pila
    while( !resultado.estaVacia() )
        cout << resultado.saca();
    cout << endl;
}

void Infija_a_Postfija(char *origen) //recibe la cadena original
{
    Pila pila; //La pila de los operadores
    
    int i=0; //nos ayuda a recorrer la cadena original
    
    while( origen[i] != '\0' )
    {
        if( origen[i] >= '0' && origen[i] <= '9' ) //Es un operando, osea un numero
            cout << origen[i]; //se imprime el carácter
        else if( origen[i] == '(' || origen[i] == '+' || origen[i] == '-' || origen[i] == '/' || origen[i] == '*' ) //es operador o parentesis de apertura
        {
                pila.mete( origen[i] ); //ingresa el carácter en la pila
        }
        /*
        Cuando nos encontremos un paréntesis
        de cerrado, tenemos que imprimir los operandos
        de la pila hasta que nos encontremos con el
        paréntesis de abierto que le corresponde a este
        paréntesis de cerrado que nos acabamos de
        encontrar. Por supuesto, los paréntesis no van
        dentro de la expresión final.
        */
        else if( origen[i] == ')' ) //el if es innecesario; basta con un else. Sin embargo, se coloca para que se entienda un poquito mejor
        {
            char a = pila.saca(); // se saca el primer operando de la pila
            
            do
            {
                if( a != '(' ) //si no es paréntesis de abierto
                    cout << a; //lo imprime
                if( !pila.estaVacia() ) //si la pila aún tiene operadores
                    a = pila.saca(); //vuelve a sacar otro operador de la pila
            }
            while( a != '(' ); //mientras no se saque de la pila un paréntesis de abierto
        }
        i++; //avanza al siguiente carácter en la cadena original.
    }
    /*
    Como ya no hay mas caracteres por leer,
    ahora se agregan todos los operadores de la
    pila hasta dejarla vacía; nuevamente,
    los paréntesis no se toman en cuenta
    */
    char a = pila.saca(); // se saca el primer operando de la pila       
    do
    {
        if( a != '(' ) //si no es paréntesis de abierto
            cout << a; //lo imprime
        if( !pila.estaVacia() ) //si la pila aún tiene operadores
            a = pila.saca(); //vuelve a sacar otro carácter de la pila
    }while( !pila.estaVacia() ); //mientras la pila no se vacíe
    cout << endl;
}

int main()
{
    char expresion[30]; //guarda la expresión de la entrada
    char resultado[30]; //guarda la expresión resultante
    int o; //guarda si el usuario quiere convertir a prefija o a postfija
    
    cout << "Ingrese la expresión en notación infija: " << endl;
    cin >> expresion;
    /*
    Importante: si ingresamos la expresión
    de la forma anterior (cin >> expresión), al final 
    el sistema le agrega de manera automática un
    '\0' (carácter nulo), indicando que ahí termina
    la cadena. Nos va a ser muy útil a la hora
    de convertir la cadena, por que así sabremos
    hasta dónde termina la cadena que vamos a convertir
    porque, como te habrás dado cuenta, no hay ninguna
    variable que guarde el tamaño de la cadena.
    */
    
    /*
    El ciclo se ejecuta hasta que el usuario ingrese
    una opción válida. Esto es para controlar que el
    usuario no meta opciones 5, 8, -14, que por supuesto
    no existen.
    */
    do
    {
        cout << endl << "1. Infija a Prefija\n2. Infija a Posfija\n" << endl;
        cout << "Ingrese su opcion: ";
        cin >> o;
    }while( o < 1 || o > 2 ); //El usuario ingresó opciones no válidas
    
    if( o == 1 ) //Eligió Prefija
        Infija_a_Prefija(expresion); //Se le envia la cadena original
    else //Eligió Postfija
        Infija_a_Postfija(expresion); //Se le envia la cadena original
}
