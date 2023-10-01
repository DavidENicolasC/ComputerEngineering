/*
Programa 9. Hacer un programa
que genere una secuencia de n
números pseudoaleatorios en el
rango -0.3<x<0.3 y que lo guarde
en un archivo en formato de texto.
*/
#include<iostream>
#include<stdlib.h>
#include<cmath>
#include<fstream>
#include<vector>
using namespace std;

void GenerayGuarda( int n, ofstream& f )
{
    for( int c=0; c<n; c++ )
    {
        double r = fmod( rand(), 0.3 );
        int s = rand() % 2;
        if( !s ) //Aqui se decide el signo del numero obtenido
            r *= -1;
        
        cout << "El numero a meter en el archivo es: "
             << r << endl; //Imprimirlo para que sepa el usuario
        f << r << endl; //Esta instruccion mete el valor en el archivo
    }
    f.close();
}

int main()
{
    int n;
    ofstream file;
    
    file.open( "archivo.txt", ios::out );
    
    if( !file.fail() )
    {
        cout << "Ingrese el numero de valores a escribir en el archivo: ";
        cin >> n;
        GenerayGuarda( n, file );
    }
    else
        cout << "Ocurrio un error al abrir el archivo" << endl;
}
