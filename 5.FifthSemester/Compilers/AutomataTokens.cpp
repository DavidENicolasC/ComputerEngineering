/*Programador: David Emmanuel Nicolas Castañeda
  Compiladores 5CV14
  Profr: Jesus Mora Jain
*/
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

void IdentificaTipo( const char* );
int AnalizadorLexico(const char* );

char *palres[] = {"for", "int", "while", "if", "float", 
				"switch", "do", "double", "char", "bool", "string"};


int main(void)
{
	char cadena[1000];
	
	printf("Ingrese una cadena en minusculas: ");
	gets(cadena);
	
	IdentificaTipo( cadena );
	
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

void IdentificaTipo( const char* cad )
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
			printf("Identificador\n");
			break;
		case 2:
			printf("Palabra Reservada\n");
			break;
		case 3:
			printf("Operador Relacional\n");
			break;
		case 4:
			printf("Operador Logico\n");
			break;
		case 5:
			printf("Operador Aritmetico\n");
			break;
		case 6:
			printf("Entero\n");
			break;
		case 7:
			printf("Decimal\n");
			break;
		case 8:
			printf("Exponencial\n");
			break;
		default:
			printf("Error\n");
			break;
	}
}
