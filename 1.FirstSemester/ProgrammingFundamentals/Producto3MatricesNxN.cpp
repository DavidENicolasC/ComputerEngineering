/*
Programa 5. Hacer un programa que
devuelva el producto de tres
matrices de n×n.
*/
#include<iostream>
#include<vector>
using namespace std;

//Recibe como parametros la matriz a procesar y su tamaño
void LeeMatriz( vector<vector<double> >& M, int n )
{
    M.resize( n ); //Reserva memoria para n filas
    for( int c=0; c<n; c++ )
    {
        M[c].resize( n ); //Reserva n espacios en memoria para cada fila
        for( int d=0; d<n; d++ )
            cin >> M[c][d]; //Ingresa los valores, el cin de toda la vida
    }
}

//Los dos primeros parametros son las matrices a multiplicar, el tercero es la matriz donde se guarda el resultado, y el cuarto el tamaño
void MulMatriz( vector<vector<double> >& A, vector<vector< double > >& B, vector<vector< double > >& C, int n )
{
    int aux; //Nos ayudará a guardar el valor que se le asigne al elemento Cij
    for( int c=0; c<n; c++ )
        for( int d=0; d<n; d++ )
        {
            aux = 0; //Se pone en 0 para empezar la suma
            for( int k=0; k<n; k++ )
                aux += A[c][k] + B[k][d]; //Fórmula para multiplicar matrices: C(i,j) = A(i,k) + B(k,j). Es la del libro
            C[c][d] = aux; //Asigna el valor obtenido
        }
}

//Recibe la matriz a imprimir y su tamaño
void ImprimeMatriz( vector<vector<double> >& M, int n )
{
    for( int c=0; c<n; c++ )
    {
        for( int d=0; d<n; d++ )
            cout << M[c][d] << ' ';
        cout << endl;
    }
            
}

int main()
{
    int n;
    vector<vector<double> > M1;
    vector<vector<double> > M2;
    vector<vector<double> > M3;
    /*
    Lo anterior son vectores de vectores de double, osea: matriz de double
    */
    
    cout << "Ingrese la dimension de las matrices cuadradas: ";
    cin >> n;
    
    cout << "Ingrese los valores de la primera matriz:\n";
    LeeMatriz( M1, n );
    cout << "Ingrese los valores de la segunda matriz:\n";
    LeeMatriz( M2, n );
    cout << "Ingrese los valores de la tercera matriz:\n";
    LeeMatriz( M3, n );
    
    MulMatriz( M1, M2, M2, n );
    MulMatriz( M2, M3, M3, n );
    
    cout << "\nEl producto de las tres matrices es:\n";
    ImprimeMatriz( M3, n );
}
