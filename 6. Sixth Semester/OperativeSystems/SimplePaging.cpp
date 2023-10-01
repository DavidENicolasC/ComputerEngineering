#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

#define CAPMEMO 64
#define MARCOPAG 2
#define TAMSO 4
#define TAMPAG 100
#define MAXLIN 1000
#define NUMTAR 20

void CrearMMT(void);
void VerMMT(void);
void CrearJT(void);
void VerJT(void);
void CrearPMT(void);
void VerPMT(void);
void AlgoritmoAsignacion(void);

//Tabla de Mapa de Memoria
struct MMT
{
	//datos
   int NoMarco;
   int Capacidad;
   int LocalidadInicial;
   int Estado;
   //liga
   MMT *liga;
};

//Tabla de Tareas
struct JT
{
  	//datos
	int noTarea;
	int tam;
   int LocPMT;
	//liga
 	JT *liga;
};

struct PMT
{
	//datos
   int NoPag;
   int LocMarco;
   //liga
   PMT *liga;
};

MMT *Plista, *Qlista, *Aux, *NuevoMarco;

PMT *PTablasMapaPaginas[NUMTAR];
PMT *QTablasMapaPaginas[NUMTAR];
PMT *AuxPMT;

JT *Ptabla, *Qtabla, *AuxT, *NuevaTarea;

int main(void)
{
	CrearMMT();
	VerMMT();
	CrearJT();
	VerJT();
	CrearPMT();
	VerPMT();
	AlgoritmoAsignacion();
	VerMMT();
	VerPMT();

   system("PAUSE");
   return 0;
}

void CrearMMT(void)
{
	Plista = NULL;
   Qlista = NULL;

	int NoM = 0;
   //Tamaño de Memoria en KB
	int CapMemo = CAPMEMO * 1024;
   //Capacidad de Marco en KB
   int MarcoPag = MARCOPAG * 1024;

   int NumMarcos = CapMemo / MarcoPag;
   int LocIniMarco = 0;

   //Se crean los Marcos del SO
   //Marco 1
   Plista = (MMT *)malloc(sizeof(MMT));
   Plista->NoMarco = NoM;
   Plista->LocalidadInicial = LocIniMarco;
   Plista->Estado = 1;
   Plista->liga = NULL;
   Qlista = Plista;
   NumMarcos--;
   NoM++;
   LocIniMarco += MarcoPag;
   //Marco 2
   NuevoMarco = (MMT *)malloc(sizeof(MMT));
   NuevoMarco->NoMarco = NoM;
   NuevoMarco->LocalidadInicial = LocIniMarco;
   NuevoMarco->Estado = 1;
   NuevoMarco->liga = NULL;
   Qlista->liga = NuevoMarco;
   Qlista = NuevoMarco;
   NumMarcos--;
   NoM++;
   LocIniMarco += MarcoPag;

   while( NumMarcos > 0 )
   {
   	NuevoMarco = (MMT *)malloc(sizeof(MMT));
   	NuevoMarco->NoMarco = NoM;
   	NuevoMarco->LocalidadInicial = LocIniMarco;
   	NuevoMarco->Estado = 0;
   	NuevoMarco->liga = NULL;
   	Qlista->liga = NuevoMarco;
   	Qlista = NuevoMarco;
   	NumMarcos--;
   	NoM++;
   	LocIniMarco += MarcoPag;
   }
}

void VerMMT(void)
{
	printf("NO. MARCO\t|\tLOC. INICIO\t|\tESTADO\n");
	Aux = Plista;
   while( Aux != NULL)
   {
   	printf("%d\t\t\t%dB\t\t\t%d\n", Aux->NoMarco, Aux->LocalidadInicial, Aux->Estado);
      Aux = Aux->liga;
   }
   printf("\n");
}

void CrearJT(void)
{
   Ptabla = NULL;
   Qtabla = NULL;

   //La localidad de PMT se genera de forma aleatoria
   int LocalidadPMT = rand() % (MARCOPAG * 1024);

   int NumTar = 1;
   int TotTar = NUMTAR;

   while(TotTar > 0)
   {
   	if( Ptabla == NULL )
      {
      	Ptabla = (JT *)malloc(sizeof(JT));
         Ptabla->noTarea = NumTar;
         Ptabla->tam = 100 + (rand() % MAXLIN);
         Ptabla->LocPMT = LocalidadPMT;
         Ptabla->liga = NULL;
         Qtabla = Ptabla;
      }
      else
      {
      	NuevaTarea = (JT *)malloc(sizeof(JT));
         NuevaTarea->noTarea = NumTar;
         NuevaTarea->tam = 1 + (rand() % MAXLIN);
         NuevaTarea->LocPMT = LocalidadPMT;
         NuevaTarea->liga = NULL;
         Qtabla->liga = NuevaTarea;
         Qtabla = NuevaTarea;
      }
      TotTar--;
      LocalidadPMT++;
      NumTar++;
   }
}

void VerJT(void)
{
	printf("NO. TAREA\t|\tTAMANIO\t|\tLOCALIDAD PMT\n");
	AuxT = Ptabla;
   while( AuxT != NULL)
	{
   	printf("J%d\t\t\t%d lineas\t\t\t%d\n", AuxT->noTarea, AuxT->tam, AuxT->LocPMT);
      AuxT = AuxT->liga;
   }
   printf("\n");
}

void CrearPMT(void)
{
	AuxT = Ptabla;
	for(int c=0; c<NUMTAR; c++)
   {
   	int NumPag = 0;
   	int TotPag = AuxT->tam / TAMPAG;
      if( AuxT->tam % TAMPAG > 0 )
      	TotPag++;
      for(int d=0; d<TotPag; d++)
      {
      	if( PTablasMapaPaginas[c] == NULL )
         {
         	PTablasMapaPaginas[c] = (PMT *)malloc(sizeof(PMT));
            PTablasMapaPaginas[c]->NoPag = NumPag;
            PTablasMapaPaginas[c]->LocMarco = -1;
            PTablasMapaPaginas[c]->liga = NULL;
            QTablasMapaPaginas[c] = PTablasMapaPaginas[c];
         }
         else
         {
         	AuxPMT = (PMT *)malloc(sizeof(PMT));
            AuxPMT->NoPag = NumPag;
            AuxPMT->LocMarco = -1;
            AuxPMT->liga = NULL;
            QTablasMapaPaginas[c]->liga = AuxPMT;
            QTablasMapaPaginas[c] = AuxPMT;
         }
         NumPag++;
      }
      AuxT = AuxT->liga;
   }
}

void VerPMT(void)
{
	for(int c=0; c<NUMTAR; c++)
   {
   	printf("NO. PAGINA\t|\tLOCALIDAD MARCO\n");
		AuxPMT = PTablasMapaPaginas[c];
   	while( AuxPMT != NULL)
		{
   		printf("P%d\t\t\t%d\n", AuxPMT->NoPag, AuxPMT->LocMarco);
      	AuxPMT = AuxPMT->liga;
   	}
   	printf("\n");
   }
}

void AlgoritmoAsignacion(void)
{
	int TotMarcos = CAPMEMO / MARCOPAG;
	Aux = Plista;
	printf("Entro\n");
	while( Aux->Estado == 1 )
	{
		printf("PASO\n");
		TotMarcos--;
		Aux = Aux->liga;
	}
	printf("Tot Marcos es: %d", TotMarcos);
	for(int c=0; c<NUMTAR; c++)
	{
		int i = 0;
		AuxPMT = PTablasMapaPaginas[c];
		while( AuxPMT != NULL )
		{
			AuxPMT = AuxPMT->liga;
			i++;
		}
		if( i <= TotMarcos )
		{
			TotMarcos -= i;
			AuxPMT = PTablasMapaPaginas[c];
			for( int d=0; d<i; d++ )
			{
				Aux->Estado = 1;
				AuxPMT->LocMarco = Aux->NoMarco;
				Aux = Aux->liga;
				AuxPMT = AuxPMT->liga;
			}	
		}
		printf("Todo bien\n");
	}
}
