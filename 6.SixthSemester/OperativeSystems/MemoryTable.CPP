  /*
  Instituto Politecnico Nacional
  Escuela Superior de Ingenieria Mecanica y Electrica Unidad Culhuacan
  6CM23 Sistemas Operativos
  M. en C. Marisol Hernandez Lopez
  Programador: David Emmanuel Nicolas Castañeda
  */
  #include <stdio.h>
  #include <conio.h>
  #include <stdlib.h>
  #include <time.h>
  #include <windows.h>
  #include <string.h>

  #define MAXMEMO 100
  #define TAMSO 20
  #define MAXPART 50

  void CrearLista(void);
  void CrearTabla(void);
  void VerLista(void);
  void VerTabla(void);
  void CrearTablaTareas(void);
  void MostrarTablaTareas(void);
  void AlgoritmoPrimerAjuste(void);
  void OrdenarJTAscendente(void);
  void AlgoritmoMejorAjuste(void);
  void AlgoritmoPeorAjuste(void);

  struct Nodo
  {
   	  //datos
      int NoParticion;
      int Capacidad;
      int LocalidadInicial;
      int LocalidadFinal;
      int Estado;
      int Asignacion;
      int FragmentacionInterna;
      //liga
      Nodo *liga;
  };

  struct JT
  {
  		//datos
		int noTarea;
		int tam;
      	//liga
      	JT *liga;
  };

  Nodo *Plista, *Qlista, *Aux, *NuevoNodo;

  JT *Ptabla, *Qtabla, *AuxT, *NuevaTarea;

  int main()
  {
  		Plista = NULL;
   	Qlista = NULL;
   	CrearLista();
   	VerLista();
    	CrearTablaTareas();
    	MostrarTablaTareas();
    	//Algoritmo del Primer Ajuste
    	//AlgoritmoPrimerAjuste();
	 	//
    	//Algoritmo del Mejor Ajuste
    	OrdenarJTAscendente();
  	 	MostrarTablaTareas();
    	AlgoritmoMejorAjuste();
    	//
    	/*Algoritmo del Peor Ajuste
    	OrdenarJTAscendente();
    	MostrarTablaTareas();
    	AlgoritmoPeorAjuste();
    	*/
    	VerLista();
    	system("PAUSE");
    	return 0;
  }

  void CrearLista(void)
  {
  	int NumPart, Cap, LocIni, LocFin, Est, Asig, FragInt;
  	int r, CapRes = MAXMEMO;

   //SE CREA LA PARTICION DEL SISTEMA OPERATIVO
   Plista = (Nodo *)malloc(sizeof(Nodo));
   Plista->NoParticion = NumPart;
   Plista->Capacidad = TAMSO;
   Plista->LocalidadInicial = 0;
   Plista->LocalidadFinal = TAMSO - 1;
   Plista->Estado = 0;
   Plista->Asignacion = 0;
   Plista->FragmentacionInterna = 0;
   Plista->liga = NULL;
   Qlista = Plista;
   CapRes -= TAMSO;
   //------------------------------------------

   //SE CREAN LAS PARTICIONES SOLICITADAS POR EL USUARIO
   NumPart = 0;
   printf( "Â¿Desea crear una particion\? 1->SI 2->NO: " );
   scanf("%d", &r);
  	while( CapRes > 0 && r == 1 )
   {
   	NuevoNodo = (Nodo*)malloc(sizeof(Nodo));
      printf("Ingrese la capacidad: ");
      scanf("%d", &Cap);
      if( CapRes - Cap >= 0 )
      {
      	NumPart++;
         NuevoNodo = (Nodo *)malloc(sizeof(Nodo));
      	NuevoNodo->NoParticion = NumPart;
      	NuevoNodo->Capacidad = Cap;
      	NuevoNodo->LocalidadInicial = Qlista->LocalidadFinal + 1;
      	NuevoNodo->LocalidadFinal = Qlista->LocalidadFinal + Cap;
      	NuevoNodo->Estado = 1;
      	NuevoNodo->Asignacion = 0;
      	NuevoNodo->FragmentacionInterna = 0;
         CapRes -= Cap;
      	NuevoNodo->liga = NULL;
      	Qlista->liga = NuevoNodo;
      	Qlista = NuevoNodo;
      }
      else
      {
      	printf("La capacidad restante es de %dKB\n", CapRes);
      }
      if( CapRes > 0 )
      {
      	printf( "ï¿½Desea crear una particion? 1->SI 2->NO: " );
      	scanf("%d", &r);
	  }
	  else
	  	r = 0;
   }
   if( CapRes > 0 )
   {
		NumPart++;
   		NuevoNodo = (Nodo *)malloc(sizeof(Nodo));
   		NuevoNodo->NoParticion = NumPart;
   		NuevoNodo->Capacidad = CapRes;
   		NuevoNodo->LocalidadInicial = Qlista->LocalidadFinal + 1;
   		NuevoNodo->LocalidadFinal = Qlista->LocalidadFinal + CapRes;
   		NuevoNodo->Estado = 1;
   		NuevoNodo->Asignacion = 0;
   		NuevoNodo->FragmentacionInterna = 0;
   		CapRes = 0;
   		NuevoNodo->liga = NULL;
   		Qlista->liga = NuevoNodo;
   		Qlista = NuevoNodo;
   }
  }

  void VerLista(void)
  {
  		printf("\n");
  		Aux = Plista;
      printf("NO. PARTICION\tCAPACIDAD\tLOCALIDAD INICIAL\tLOCALIDAD FINAL\tESTADO\tASIGNACION\tFRAGMENTACION INTERNA\n");
      printf("B%d\t\t%d\t\t%d\t\t\t%d\t\t%d\tS%d\t\t%d\n", Aux->NoParticion, Aux->Capacidad, Aux->LocalidadInicial, Aux->LocalidadFinal, Aux->Estado, Aux->Asignacion, Aux->FragmentacionInterna);
      Aux = Aux->liga;
      while( Aux != NULL )
      {
         printf("B%d\t\t%d\t\t%d\t\t\t%d\t\t%d\tJ%d\t\t%d\n", Aux->NoParticion, Aux->Capacidad, Aux->LocalidadInicial, Aux->LocalidadFinal, Aux->Estado, Aux->Asignacion, Aux->FragmentacionInterna);
         Aux = Aux->liga;
      }
  }

  void CrearTablaTareas(void)
  {
  		int c;
      int nT = 1;

      //Se genera un numero aleatorio
      srand(time(NULL));

      //SE CREA LA PRIMERA TAREA
      Ptabla = (JT *)malloc(sizeof(JT));
   	Ptabla->noTarea = nT;
   	Ptabla->tam = rand() % MAXPART + 5;
   	Ptabla->liga = NULL;
   	Qtabla = Ptabla;
      nT++;
      //------------------------
  		for(c = 2; c <= 10; c++)
      {
         NuevaTarea = (JT *)malloc(sizeof(JT));
   		NuevaTarea->noTarea = nT;
   		NuevaTarea->tam = rand() % 46 + 5;
   		NuevaTarea->liga = NULL;
         Qtabla->liga = NuevaTarea;
   		Qtabla = NuevaTarea;
      	nT++;
      }
  }

  void MostrarTablaTareas(void)
  {
      printf("\n");
      AuxT = Ptabla;
      printf("NO. TAREA\tCAPACIDAD\n");
      printf("J%d\t\t%d\n", AuxT->noTarea, AuxT->tam);
      AuxT = AuxT->liga;
      while( AuxT != NULL )
      {
         printf("J%d\t\t%d\n", AuxT->noTarea, AuxT->tam);
         AuxT = AuxT->liga;
      }
  }

  void AlgoritmoPrimerAjuste(void)
  {
  	//Ciclo para obtener la cantidad de particiones
  	Aux = Plista->liga;
  	int i = 0;
  	while(Aux != NULL)
  	{
  		i++;
  		Aux = Aux->liga;
	}
	int T = i;
	
	//Ciclo para asignar las tareas a las particiones
	//El ciclo se ejecuta mientras haya tareas disponibles y haya particiones libres
	Aux = Plista->liga;
	AuxT = Ptabla;
	while( i > 0 && Ptabla != NULL )
	{
		int c = T;
		while( c > 0 )
		{
			if( Aux->Estado == 1 && AuxT->tam <= Aux->Capacidad )
			{
				Aux->Estado = 0;
				Aux->Asignacion = AuxT->noTarea;
				Aux->FragmentacionInterna = Aux->Capacidad - AuxT->tam;
				i--;
				break;	
			}
			Aux = Aux->liga;
			if( Aux == NULL )
				Aux = Plista->liga;	
			c--;
		}
		Ptabla = Ptabla->liga;
		free(AuxT);
		AuxT = Ptabla;
	}
}

void OrdenarJTAscendente(void)
{
	AuxT = Ptabla;
	int i = 0;
	//Obtengo el tamaño de la tabla
	while( AuxT != NULL )
	{
		i++;
		AuxT = AuxT->liga;
	}
	
	int c, d;
	JT *Aux2T;
	if( i > 1 )
	{
		AuxT = Ptabla;
		for( c = 0; c < i; c++)
		{
			for( d = 0; d < i - 2; d++ )
			{
				if( AuxT == Ptabla )
				{
					//Ordena los primeros dos elementos de la tabla de tareas
					if( Ptabla->liga->tam < Ptabla->tam )
					{
						AuxT = Ptabla->liga;
						Ptabla->liga = AuxT->liga;
						AuxT->liga = Ptabla;
						Ptabla = AuxT;
					}
					//Ordena los dos elementos que estan adelante del primer elemento (el de Ptabla)
					if( i > 2 && Ptabla->liga->liga->tam < Ptabla->liga->tam )
					{
						AuxT = Ptabla->liga->liga;
						Ptabla->liga->liga = AuxT->liga;
						AuxT->liga = Ptabla->liga;
						Ptabla->liga = AuxT;
					}
				}
				else if( AuxT->liga->liga != NULL )
				{
					//Ordena los dos elementos que estan adelante del elemento apuntado por AuxT
					if( AuxT->liga->liga->tam < AuxT->liga->tam )
					{
						Aux2T = AuxT->liga;
						AuxT->liga = Aux2T->liga;
						Aux2T->liga = AuxT->liga->liga;
						AuxT->liga->liga = Aux2T;
					}		
				}
				AuxT = AuxT->liga;
			}
			AuxT = Ptabla;
		}
	}
}

void AlgoritmoMejorAjuste(void)
{
  	//Ciclo para obtener la cantidad de particiones
  	Aux = Plista->liga;
  	int i = 0;
  	while(Aux != NULL)
  	{
  		i++;
  		Aux = Aux->liga;
	}
	
	//Ciclo para asignar las tareas a las particiones
	//El ciclo se ejecuta mientras haya tareas disponibles y haya particiones libres
	Aux = Plista->liga;
	AuxT = Ptabla;
	while( i > 0 && Ptabla != NULL )
	{
		//Variable que almacena la diferencia mas pequeña entre las particiones y la tarea 
		int min = -1;
		int part;
		while( Aux != NULL )
		{
			if( Aux->Estado == 1 && AuxT->tam <= Aux->Capacidad && ( min < 0 || Aux->Capacidad - AuxT->tam < min ) )
			{
				min = Aux->Capacidad - AuxT->tam;
				part = Aux->NoParticion;	
			}
			Aux = Aux->liga;
		}
		if( min >= 0 )
		{
			Aux = Plista->liga;
			while( Aux->NoParticion != part )
				Aux = Aux->liga;
			Aux->Estado = 0;
			Aux->Asignacion = AuxT->noTarea;
			Aux->FragmentacionInterna = Aux->Capacidad - AuxT->tam;
			i--;
		}
		Ptabla = Ptabla->liga;
		free(AuxT);
		AuxT = Ptabla;
		Aux = Plista->liga;
	}
}

void AlgoritmoPeorAjuste(void)
{
  	//Ciclo para obtener la cantidad de particiones
  	Aux = Plista->liga;
  	int i = 0;
  	while(Aux != NULL)
  	{
  		i++;
  		Aux = Aux->liga;
	}
	
	//Ciclo para asignar las tareas a las particiones
	//El ciclo se ejecuta mientras haya tareas disponibles y haya particiones libres
	Aux = Plista->liga;
	AuxT = Ptabla;
	while( i > 0 && Ptabla != NULL )
	{
		//Variable que almacena la diferencia mas pequeña entre las particiones y la tarea 
		int max = -1;
		int part;
		while( Aux != NULL )
		{
			if( Aux->Estado == 1 && AuxT->tam <= Aux->Capacidad && Aux->Capacidad - AuxT->tam > max )
			{
				max = Aux->Capacidad - AuxT->tam;
				part = Aux->NoParticion;	
			}
			Aux = Aux->liga;
		}
		if( max >= 0 )
		{
			Aux = Plista->liga;
			while( Aux->NoParticion != part )
				Aux = Aux->liga;
			Aux->Estado = 0;
			Aux->Asignacion = AuxT->noTarea;
			Aux->FragmentacionInterna = Aux->Capacidad - AuxT->tam;
			i--;
		}
		Ptabla = Ptabla->liga;
		free(AuxT);
		AuxT = Ptabla;
		Aux = Plista->liga;
	}
}
