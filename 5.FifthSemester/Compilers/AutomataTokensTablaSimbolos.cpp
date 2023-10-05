/*Programador: David Emmanuel Nicolas Castañeda
  Compiladores 5CV14
  Profr: Jesus Mora Jain
  Practica 3: Reconocedor de tokens con tabla de simbolos
*/
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

struct TSimbolos
{
	//datos
	char lexema[1000];
	char tipotoken[1000];
	//liga
	TSimbolos *liga;
} *PTabla, *QTabla, *Aux, *NuevoTabla;

int IdentificaTipo( const char* );
int AnalizadorLexico(const char* );
void LeeArchivo(const char*);
void AgregaTablaSimbolos(const char*, int);
void RecorreTablaSimbolos(void);

char *palres[] = {"for", "int", "while", "if", "float", 
				"printf", "do", "double", "char", "bool", "string"};


int main(void)
{
	const char* archivo = "archivofuente.txt"; 
	
	//En lugar de ingresar una cadena, se leen del archivo
	LeeArchivo(archivo);
	
	system("PAUSE");
	return 0;
}

//1: ID
//3: Operador Relacional
//4: Operador Logico
//5: Operador Aritmetico
//6: Entero
//7: Decimal
//8: Exponencial
int AnalizadorLexico( const char* lex )
{
	int i = 0, t = strlen(lex), tiptok;

	switch( lex[i] )
	{
		case 'a'...'z':
		case 'A'...'Z':
			tiptok = 1;
			i++;
			while( i < t && isalnum( lex[i] ) )
			{
				i++;
			}
			break;
		case '<':
		case '>':
		case '=':
		case '!':
			if( lex[i] == '!' )
				tiptok = 4;
			else
				tiptok = 3;
			i++;
			if( i < t )
			{
				if( lex[i] == '=' )
					tiptok = 3;
				else
					i--;
				i++;
			}
			break;
		case '*':
		case '/':
			i++;
			if(i == t )
				tiptok = 5;
			else
				i--;
			break;
		case '&':
			i++;
			if( i < t && lex[i] == '&' )
			{
				tiptok = 2;
			}
			else
				i--;
			break;
		case '|':
			i++;
			if( i < t && lex[i] == '|' )
			{
				tiptok = 2;
				i++;
			}
			else
				i--;
			break;
		case '0'...'9':
		case '+':
		case '-':
			if( lex[i] == '+' || lex[i] == '-' )
			{
				tiptok = 5;
				i++;
			}
			if( i < t && lex[i] >= '0' && lex[i] <= '9' )
			{
				i++;
				tiptok = 6;
				while( i < t && lex[i] >= '0' && lex[i] <= '9' )
					i++;
				if( i < t && lex[i] == '.' )
				{
					i++;
					if( i < t && lex[i] >= '0' && lex[i] <= '9' )
					{
						tiptok = 7;
						while( i < t && lex[i]>='0' && lex[i] <= '9' )
							i++;
					}
					else
						i--;
				}
				if( lex[i] == 'e' || lex[i] == 'E' )
				{
					i++;
					if( lex[i] == '+' || lex[i] == '-' )
						i++;
					if( i < t && lex[i] >= '0' && lex[i] <= '9' )
					{
						tiptok = 8;
						while( i < t && lex[i] >= '0' && lex[i] <= '9' )
							i++;
					}
					else
						i--;
				}
			}
			break;
		default:
			break;
	}
	if( i == t )
		return tiptok;
	return 0;
}

int IdentificaTipo( const char* cad )
{
	int tipo = AnalizadorLexico( cad );
	
	//2: Palabra Reservada
	int c = 0;
	if( tipo == 1 )
		while( c < (11) )
		{
			if( !(strcmp( cad, palres[c] ) ) )
			{
				tipo = 2;
				break;
			}
			c++;
		}
	
	switch( tipo )
	{
		case 1:
			return 1;
		case 2:
			return 2;
		case 3:
			return 3;
		case 4:
			return 4;
		case 5:
			return 5;
		case 6:
			return 6;
		case 7:
			return 7;
		case 8:
			return 8;
		default:
			return -1;
	}
}

void LeeArchivo(const char* arc)
{
	FILE *Archivo = fopen(arc, "r");
	char cadena[1000];
	if( Archivo != NULL ) //Si el archivo se abre correctamente
	{
		
		while( fscanf(Archivo,"%s",cadena) != EOF )
		{			
			int tipo = IdentificaTipo(cadena);
		
			if(tipo != -1)
				AgregaTablaSimbolos(cadena, tipo);
		///////////////////////////////////////////////////////////////////	
		
		}
		
		//////////////Imprime la tabla de simbolos
		RecorreTablaSimbolos();
		///////////////////////////////////////
	}
	else
		printf("Ocurrio un error al intentar abrir el archivo\n\n");
}

void AgregaTablaSimbolos(const char* lex, int tiptok)
{
	NuevoTabla = (TSimbolos *)malloc(sizeof(TSimbolos));
	strcpy(NuevoTabla->lexema, lex);
	NuevoTabla->liga = NULL;
	
	switch( tiptok )
	{
		case 1:
			strcpy(NuevoTabla->tipotoken, "Identificador");
			break;
		case 2:
			strcpy(NuevoTabla->tipotoken, "Palabra Reservada");
			break;
		case 3:
			strcpy(NuevoTabla->tipotoken, "Operador Relacional");
			break;
		case 4:
			strcpy(NuevoTabla->tipotoken, "Operador Logico");
			break;
		case 5:
			strcpy(NuevoTabla->tipotoken, "Operador Aritmetico");
			break;
		case 6:
			strcpy(NuevoTabla->tipotoken, "Entero");
			break;
		case 7:
			strcpy(NuevoTabla->tipotoken, "Decimal");
			break;
		case 8:
			strcpy(NuevoTabla->tipotoken, "Exponencial");
			break;
	}
	
	if( PTabla == NULL)
	{
		PTabla = NuevoTabla;
		QTabla = PTabla;
	}
	else
	{
		QTabla->liga = NuevoTabla;
		QTabla = NuevoTabla;
	}	
}

void RecorreTablaSimbolos(void)
{
	printf("\tTABLA DE SIMBOLOS\n\n");
	printf("LEXEMA\t\tTIPO DE TOKEN\n");
	Aux = PTabla;
	while(Aux != NULL)
	{
		printf( "%s\t\t%s\n", Aux->lexema, Aux->tipotoken );
		Aux = Aux->liga;
	}
}
