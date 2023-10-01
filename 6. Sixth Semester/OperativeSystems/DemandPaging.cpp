#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

#define CAPMEMO 64
#define MARCOPAG 2
#define TAMSO 4
#define TAMPAG 100
#define MAXLIN 1000
#define NUMTAR 6
#define NUMSEC 5
#define MARCPORTAREA 3

void CrearMMT(void);
void VerMMT(void);
void CrearJT(void);
void VerJT(void);
void CrearPMT(void);
void VerPMT(void);
void PaginacionPorDemanda(void);

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
   int secuencia[5];
	//liga
 	JT *liga;
};

struct PMT
{
	//datos
   int NoPag;
   int LocMarco;
   int Estado;
   int Referencia;
   int Modificacion;
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
	PaginacionPorDemanda();

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
	printf("-----------TABLA DE MAPA DE MEMORIA-----------\n");
	printf("NO. MARCO\t|\tLOC. INICIO\t|\tESTADO\n");
	Aux = Plista;
   while( Aux != NULL)
   {
   	printf("%d\t\t\t%dB\t\t\t%d\n", Aux->NoMarco, Aux->LocalidadInicial, Aux->Estado);
      Aux = Aux->liga;
   }
   printf("\n");
   getch();
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
        for( int k=0; k<NUMSEC; k++)
   		{
      		Ptabla->secuencia[k] = rand() % ((Ptabla->tam / TAMPAG)
            + (Ptabla->tam % TAMPAG > 0? 1 : 0));
   		}
        Ptabla->liga = NULL;
        Qtabla = Ptabla;
      }
      else
      {
      	NuevaTarea = (JT *)malloc(sizeof(JT));
        NuevaTarea->noTarea = NumTar;
        NuevaTarea->tam = 1 + (rand() % MAXLIN);
        NuevaTarea->LocPMT = LocalidadPMT;
        for( int k=0; k<NUMSEC; k++)
   		{
         	NuevaTarea->secuencia[k] = rand() % ((NuevaTarea->tam / TAMPAG)
            + (NuevaTarea->tam % TAMPAG > 0? 1 : 0));
   		}
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
	printf("-----------TABLA DE TAREAS-----------\n");
	printf("NO. TAREA\t|\tTAMANIO\t|\tLOCALIDAD PMT\tSECUENCIA\n");
	AuxT = Ptabla;
   while( AuxT != NULL)
	{
   	printf("J%d\t\t\t%d lineas\t%d\t\tP%d P%d P%d P%d P%d\n",
       AuxT->noTarea, AuxT->tam, AuxT->LocPMT, AuxT->secuencia[0],
	   AuxT->secuencia[1], AuxT->secuencia[2], AuxT->secuencia[3], AuxT->secuencia[4]);
      AuxT = AuxT->liga;
   }
   printf("\n");
   getch();
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
            PTablasMapaPaginas[c]->LocMarco = 0;
            PTablasMapaPaginas[c]->Estado = 0;
            PTablasMapaPaginas[c]->Referencia = 0;
            PTablasMapaPaginas[c]->Modificacion = 0;
            PTablasMapaPaginas[c]->liga = NULL;
            QTablasMapaPaginas[c] = PTablasMapaPaginas[c];
         }
         else
         {
         	AuxPMT = (PMT *)malloc(sizeof(PMT));
            AuxPMT->NoPag = NumPag;
            AuxPMT->LocMarco = 0;
            AuxPMT->Estado = 0;
            AuxPMT->Referencia = 0;
            AuxPMT->Modificacion = 0;
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
   	printf("-----------TABLA DE MAPA DE PAGINAS DE LA TAREA J%d-----------\n", c+1);
   	printf("NO. PAGINA\t|\tLOCALIDAD MARCO\t|\tESTADO\t|\tREFERENCIA\t|\tMODIFICACION\n");
		AuxPMT = PTablasMapaPaginas[c];
   	while( AuxPMT != NULL)
		{
   		printf("P%d\t\t\t%d\t\t\t%d\t\t%d\t\t\t%d\n", AuxPMT->NoPag, AuxPMT->LocMarco, AuxPMT->Estado,
		   		AuxPMT->Referencia, AuxPMT->Modificacion);
      	AuxPMT = AuxPMT->liga;
   	}
   	printf("\n");
   	getch();
   }
}

void PaginacionPorDemanda(void)
{
	int fallos = 0;
	
	PMT *PCola, *QCola, *AuxCola, *NuevoCola;
	int tamCola = 0;
	
	int totMarcos = CAPMEMO / MARCOPAG;
	Aux = Plista;
	while( Aux->Estado == 1 )
	{
		totMarcos--;
		Aux = Aux->liga;
	}
	//Por cada tarea
		//AuxT se posiciona en la primera tarea
	AuxT = Ptabla;
	//Esta variable indica el marco inicial asignado para cada tarea
	MMT *Inicio = Plista;
	for(int c=0; c<NUMTAR; c++)
	{
		//Por cada valor de la secuencia de la tarea
		for(int k=0; k<NUMSEC; k++)
		{
			//Se obtiene el numero de pagina a buscar
			int pag = AuxT->secuencia[k];
			//Las referencias de las tareas que ya estan cargadas se ponen a 0
			AuxPMT = PTablasMapaPaginas[c];
			while( AuxPMT != NULL )
			{
				if( AuxPMT->Estado == 1 )
					AuxPMT->Referencia = 0;
				AuxPMT = AuxPMT->liga;
			}
			//Se encuentra el numero de pagina de esta iteracion dentro de la PMT de la tarea en ejecucion
				//AuxPMT se posiciona en la primera pagina de la PMT correspondiente
			AuxPMT = PTablasMapaPaginas[c];
			while( AuxPMT != NULL && AuxPMT->NoPag != pag )
				AuxPMT = AuxPMT->liga;
			
			//Una vez encontrada, se comprueba su estado y referencia
			if( AuxPMT != NULL )
			{
				//Si aun no esta cargada en memoria
				if( AuxPMT->Estado == 0 )
				{
					//Se obtiene un fallo
					fallos++;
					//Se crea un nuevo elemento para la cola
					NuevoCola = (PMT *)malloc(sizeof(PMT));
					//El elemento creado se corresponde con la pagina en proceso
					NuevoCola->NoPag = AuxPMT->NoPag;
					//Si la cola está llena, se elimina la pagina del frente de la cola
					if( tamCola == MARCPORTAREA )
					{
						//Aux empieza en el marco inicial asignado a la tarea en proceso
						Aux = Inicio;
						//Se busca el marco de la pagina en el frente de la cola
						for(int x = 0; x < MARCPORTAREA; x++)
						{
							if(Aux == NULL || Aux->NoMarco == PCola->LocMarco)
								break;
							else
								Aux = Aux->liga;
						}
						
						//Si se encontro el marco de la pagina en el frente de la cola, se retira esa pagina
						if( Aux != NULL )
						{
							//Se libera el marco
							Aux->Estado = 0;
							//Se busca la pagina dentro de la tabla de mapa de paginas para retirarla
							AuxPMT = PTablasMapaPaginas[c];
							while( AuxPMT != NULL && AuxPMT->NoPag != PCola->NoPag )
								AuxPMT = AuxPMT->liga;
							if( AuxPMT != NULL )
								AuxPMT->LocMarco = 0;
						}
						
						//Se elimina la pagina de la cola	
						AuxCola = PCola;
						PCola = PCola->liga;
						free(AuxCola);
						//Se reduce el tamaño de la cola
						tamCola--;
					}
					//Se asigna la nueva pagina detras de la cola
					if(tamCola == 0)
					{
						PCola = NuevoCola;
						QCola = PCola;
					}
					else
					{
						QCola->liga = NuevoCola;
						QCola = NuevoCola;
					}
					//Se localiza la pagina a asignar
					AuxPMT = PTablasMapaPaginas[c];
					while( AuxPMT != NULL && AuxPMT->NoPag != QCola->NoPag )
						AuxPMT = AuxPMT->liga;
					//Se asigna el primer marco libre dentro de lo asignado para esa tarea
					Aux = Inicio;
					while(Aux->Estado == 1)
						Aux = Aux->liga;
					Aux->Estado = 1;
					AuxPMT->LocMarco = Aux->NoMarco;
					//Su Estado y Referencia se colocan a 1
					AuxPMT->Estado = 1;
					AuxPMT->Referencia = 1;
					//Se aumenta el tamaño de la cola
					tamCola++;
				}
				VerMMT();
				VerPMT();
			}
		}
		//La cola se vacía para procesar la siguiente tarea
		AuxCola = PCola;
		while(AuxCola != NULL)
		{
			NuevoCola = AuxCola;
			AuxCola = AuxCola->liga;
			free(NuevoCola);
		}
		tamCola = 0;
		//La variable Inicio se desplaza la cantidad de marcos necesarios para la siguiente tarea
		for(int x = 0; x < MARCPORTAREA; x++)
			Inicio = Inicio->liga;
		//AuxT se desplaza a la siguiente tarea
		AuxT = AuxT->liga;
	}
}
