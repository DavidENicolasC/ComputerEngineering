#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <windows.h>

bool DetectaCadenaAlfabetica(const char* );

int main(void)
{
	char cadena[1000];
	printf("Ingrese una cadena en minusculas: ");
	gets( cadena );
	if( DetectaCadenaAlfabetica( cadena ) )
		printf( "Aceptado\n" );
	else
		printf( "No Aceptado\n" );
}

bool DetectaCadenaAlfabetica( const char* cad )
{
	int i = 0, t = strlen( cad );
	if( isalpha( cad[i] ) )
	{
		LOOP:
		i++;
		switch( cad[i] )
		{
			case 'a' ... 'z':
					goto LOOP;
			default:
				break;
		}
	}
	
	if( i < t )
		return 0;
	return 1;
}
