/*
Programa 4. Hacer una función que
llene una hipermatriz de m×n×o,
que utilice como argumentos las
dimensiones m, n y o. Los valores
de cada elemento los pedirá del
teclado.
*/
#include<iostream>
#include<vector>
using namespace std;

void Lee_HipMat( vector<vector<vector<double> > >& p, int a, int b, int c )
{
    p.resize( a );
    for( int i=0; i<a; i++ )
    {
        p[i].resize( b );
        for( int j=0; j<b; j++ )
        {
            p[i][j].resize( c );
            for( int k=0; k<c; k++ )
                cin >> p[i][j][k];
        }
    }
}

int main()
{
    int m, n, o;
    vector<vector<vector<double> > > v;

    cout << "Ingrese las dimensiones m, n, o de la hipermatriz:\n";
    cin >> m >> n >> o;
    
    cout << "Ingrese los valores de la hipermatriz:\n";
    Lee_HipMat( v, m, n, o );
}
