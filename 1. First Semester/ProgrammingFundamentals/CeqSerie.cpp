/*
Programa 1. Hacer un programa que 
calcule la capacitancia equivalente
Ceq de un conjunto n de capacitores
en serie.
*/
#include<iostream>
using namespace std;

/*
La formula para la capacitancia equivalente
de n capacitores en serie es:

 1     1     1           1
——— = ——— + ——— + ... + ———
Ceq    C1    C2          Cn

Si multiplicamos el lado derecho de la ecuacion
por el producto de todas las capacitancias
C1C2...Cn arriba y abajo (lo que equivale a
multiplicar el lado derecho por 1) y cancelando
un C1 con un C1 en la primera fraccion, un C2 con
un C2 en la segunda fraccion, ... un Cn con un Cn
en la n-esima ecuacion, tenemos que:

 1    C2C3...Cn   C1C3...Cn         C1C2...Cn-1
——— = ————————— + ————————— + ... + ———————————
Ceq   C1C2...Cn   C1C2...Cn          C1C2...Cn

 1    C2C3...Cn + C1C3...Cn + ... + C1C2...Cn-1
——— = —————————————————————————————————————————
Ceq                      C1C2...Cn

Ahora

 1
—————   [ b ]
[ a ] = —————
—————   [ a ]
[ b ]

Es decir, la inversa de una fraccion es el numerador
convertido en denominador y el denominador convertido
en numerador (se voltea la fraccion), por lo que
aplicando la inversa a ambos lados de la ecuación tenemos:

                         C1C2...Cn
Ceq = —————————————————————————————————————————
      C2C3...Cn + C1C3...Cn + ... + C1C2...Cn-1

Ocuparemos este ultimo resultado para el programa
*/

void  Ceq_Serie( void )
{
    double p=1, q=0;
    int n;
    /*
    p sera igual al producto de las capacitancias
    q sera igual a la suma de productos de las capacitancias
    n sera igual al numero de capacitancias
    */

    cout << "Ingrese el numero de capacitores: ";
    cin >> n;
    
    double v[n];
    cout << "Ingrese las capacitancias individuales en microfaradays:\n";
    for( int c=0; c<n; c++ )
        cin >> v[c];
    
    //producto de capacitancias
    for( int c=0; c<n; c++ )
        p *= v[c];
    
    //suma de productos de capacitancias
    for( int i=0; i<n; i++ )
        q += p / v[i]; //Como p guarda el producto de todas las capacitancias, para quitarle la n-esima solo hay que dividir el producto p entre dicha capacitancia
    
    cout << "La Capacitancia equivalente Ceq es:\n"
         << p/q
         << " microfaradays " << endl;
}

int main()
{
    Ceq_Serie();
}
