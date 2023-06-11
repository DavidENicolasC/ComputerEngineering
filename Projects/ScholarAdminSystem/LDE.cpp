LDE :: LDE ( void )

{

  Inicio = NULL;

  Final = NULL;

}



LDE :: LDE ( NodoAL * _Inicio ,NodoAL * _Final )

{

  Inicio = _Inicio;

  Final = _Final;

}



LDE :: LDE ( LDE * L )

{

  Inicio = NULL ;

  Final  = NULL ;

  

  *this = *L;

  

    if( L->getInicio() != NULL && this->getInicio() == NULL )

    {

      cout << "\t*** NO HAY MEMORIA DISPONIBLE *** " << endl << endl;

    }

}

NodoAL* LDE :: getInicio( void )

{

  return Inicio;

}

NodoAL* LDE :: getFinal( void )

{

  return Final;

}

    

LDE& LDE :: operator = ( LDE* L )

{

  if ( this != L )

  {

    NodoAL* Aux;

    


    while ( Inicio != NULL )

      EliminarInicio();

    

    if ( L->getInicio() != NULL )

    {

      NodoAL* Nuevo;


      Nuevo = new NodoAL();

        

      *Nuevo = *L->getInicio();

      Nuevo->setAptAnt( NULL );

      Inicio = Nuevo;

      Aux = Inicio;

      Nuevo = NULL;

      

      for( NodoAL *i = L->getInicio() ; i != NULL ; i = i->getAptSig() )

      {

        Nuevo = new NodoAL();

        *Nuevo = *i;


        Aux->setAptSig(Nuevo);

        Nuevo->setAptAnt( Aux );

        Aux = Aux->getAptSig();

        Nuevo = NULL;

      }

      Aux->setAptSig(NULL);

      Final = Aux;

    }

  }

  return *this;

}

    

void LDE :: InsertarInicio ( NodoAL *A )

{

  
if( Inicio == NULL )

  {

    Inicio = Final = A;

    A->setAptAnt( NULL );

    A->setAptSig( NULL );

  }

  else

  {

    Inicio->setAptAnt( A );

    A->setAptSig( Inicio );

    Inicio = A;

    A->setAptAnt( NULL );

  }

}



void LDE :: InsertarFinal ( NodoAL* A )

{

  if( Final == NULL )

  {

    Inicio = Final = A;

    A->setAptAnt( NULL );

    A->setAptSig( NULL );

  }

  else

  {

    Final->setAptSig( A );

    A->setAptAnt( Final );

    Final = A;

    A->setAptSig( NULL );

  }

}

void LDE :: InsertarAntes( NodoAL* N )

{

  NodoAL *x;

  do

  {

    x = Buscar();

    if( x != NULL )

    {

      N->setAptSig( x );

      N->setAptAnt( x->getAptAnt() );

      N->getAptAnt()->setAptSig( N );

      x->setAptAnt( N );

      if( Inicio == x )

          Inicio = N;

    }

    else

      cout << "\t*** El Alumno buscado no se encuentra en la lista. ***" << endl;

  }while( x == NULL ); //Si ingresa una materia erronea, se repite hasta que ingrese una correcta

}



void LDE :: InsertarDespues( NodoAL* N )

{

  NodoAL *x;

  do

  {

    x = Buscar();

    if( x != NULL )

    {

      N->setAptSig( x->getAptSig() );

      N->setAptAnt( x );

      N->getAptSig()->setAptAnt( N );

      x->setAptSig( N );

      if( Final == x)

          Final = N;

    }

    else

      cout << "\t*** El Alumno buscado no se encuentra en la lista. ***" << endl;

  }while( x == NULL ); //Si ingresa una materia erronea, se repite hasta que ingrese una correcta

}



void LDE :: Insertar ( void )

{

  NodoAL *Nuevo;

  Nuevo = new NodoAL();

  if( Nuevo != NULL )

  {

    Nuevo->Leer();

    

    int opcion;

    

    cout << "\t*** ELIJA COMO QUIERE INSERTAR EL NUEVO ALUMNO: ***" << endl << endl

         << "\t1. Inicio " << endl

         << "\t2. Final " << endl

         << "\t3. Antes de " << endl

         << "\t4. Despues de" << endl<< endl

         << "\tINTRODUZCA LA OPCION DESEADA: ";

     cin >> opcion;

  

    system("cls");

    switch(opcion)

    {

      case 1:


        cout << "\t*** INSERTANDO al Alumno AL INICIO DE LA LISTA ***" << endl<< endl;

        this->InsertarInicio(Nuevo);

        break;

        

      case 2:


        cout << "\t*** INSERTANDO al Alumno AL FINAL DE LA LISTA ***" << endl<< endl;

        this->InsertarFinal(Nuevo);

        break;

        

      case 3:

        cout << "\t*** INSERTANDO al Alumno ANTES DE UN ALUMNO ESPECIFICO DE LA LISTA ***" << endl << endl;

        this->InsertarAntes(Nuevo);

        break;

      

      case 4:


        cout << "\t*** INSERTANDO al Alumno DESPUES DE UN ALUMNO ESPECIFICO DE LA LISTA ***" << endl<< endl;

        this->InsertarDespues(Nuevo);

        break;

        

      default:

        cout << "\t*** OPCION INCORRECTA, INTENTE DE NUEVO ***" << endl<< endl;

        break;

    }

  }

  else

    cout << "\t*** NO HAY MEMORIA SUFICIENTE PARA INSERTAR AL NUEVO ALUMNO ***" << endl;

}



void LDE :: EliminarInicio ( void )

{

  NodoAL* Aux1;

  

  Aux1 = Inicio;

  

  if( Inicio == Final )

  {

      Final = NULL;

      cout << "\t***AHORA LA LISTA ESTA VACIA***" << endl << endl;

  }

  Inicio = Inicio->getAptSig();

  if( Inicio != NULL )

      Inicio->setAptAnt(NULL);

  

  delete Aux1;

    

}



void LDE :: EliminarFinal ( void )

{

  NodoAL* Aux1;

  

  Aux1 = Final;

  

  if( Inicio == Final )

  {

      Inicio = NULL;

      cout << "\t***AHORA LA LISTA ESTA VACIA***" << endl << endl;

  }

  Final = Final->getAptAnt();

  if( Final != NULL )

      Final->setAptSig(NULL);

  

  delete Aux1;

}



void LDE :: EliminarEspecifico(void)

{

  NodoAL *x;

  do

  {

    x = Buscar();

    

    if( x != NULL )

    {

      NodoAL* i = Inicio;

      while( i->getAptSig() != x )

        i = i->getAptSig();

      if( Inicio != Final )

      {

          i->setAptSig( x->getAptSig() );

          x->getAptSig()->setAptAnt( i );

          delete x;

      }

      else

      {

          Final = NULL;

          delete Inicio;

          Inicio = NULL;

          cout << "\t***AHORA LA LISTA ESTA VACIA***" << endl << endl;

      }

    }

    else

      cout << "\t***ALUMNO NO ENCONTRADO. INGRESE EL NOMBRE DE UN ALUMNO EXISTENTE***" << endl;

  }while( x == NULL );

}

        

void LDE :: Eliminar ( void )

{

    int opcion;

    cout << "\t***ELIMINAR ALUMNO***" << endl<< endl;

    cout << "\t1. Al inicio. " << endl;

    cout << "\t2. Al final. " << endl;

    cout << "\t3. Alumno especifico" << endl << endl;

    cout << "\tINTRODUZCA LA OPCION DESEADA: ";

    cin >> opcion;

    

    switch(opcion)

    {

      case 1:

        system("cls");

        cout << "\t***ELIMINAR Alumno AL INICIO DE LA LISTA***" << endl << endl;

        this->EliminarInicio();

        break;

        

      case 2:

        system("cls");

        cout << "\t***ELIMINAR Alumno AL FINAL DE LA LISTA***" << endl << endl;

        this->EliminarFinal();

        break;

        

      case 3:

        system("cls");

        cout << "\t***ELIMINAR Alumno ESPECIFICO***" << endl << endl;

        this->EliminarEspecifico();

        break;

        

      default:

        cout << "\t***OPCION INCORRECTA, INTENTE DE NUEVO***" << endl << endl;

        break;

    }


}

    

void LDE :: Imprimir ( void )

{

  if ( (Inicio != NULL) && ( Final != NULL ) )

  {

    for ( NodoAL *i = Inicio; i != NULL; i = i->getAptSig() )

      i->Imprimir();

  }  

  else

  {

    cout << "\t*** LA LISTA ESTA VACIA *** " << endl;

  }

}

void LDE :: Editar ( void )

{

  int Opcion;

  string NuevoDatoTxt;

  

  NodoAL* x = Buscar();

  

  if( x != NULL )

  {

      do

      {

        system ("cls");

      

        cout << "\t*** EDITAR ALUMNO ***" << endl << endl

             << "\t\t1.- Nombre " << endl

             << "\t\t2.- Boleta " << endl

             << "\t\t3.- Direccion " << endl

             << "\t\t4.- Telefono " << endl

             << "\t\t5.- Correo Electronico " << endl

             << "\t\t6.- Carrera " << endl

             << "\t\t7.- Plantel " << endl

             << "\t\t8.- Editar los Periodos Academicos del Alumno" << endl

             << "\t\t9.- Regresar " << endl << endl;

      

        cout << "\tINTRODUZCA UNA OPCION: ";

        cin >> Opcion;

        

        getline( cin, NuevoDatoTxt );

        system("cls");

        switch( Opcion )

        {

          case 1:


            cout << "\t*** Editar Nombre ***" << endl << endl;

            cout << "\tIngrese el Nuevo Nombre : ";


            getline( cin, NuevoDatoTxt );

            

            x->getDato()->setNombre(NuevoDatoTxt);

            break;

          case 2:


            cout << "\t*** Editar Boleta ***" << endl << endl;

            cout << "\tIngrese la Nueva Boleta : ";


            getline( cin, NuevoDatoTxt );

            

            x->getDato()->setBoleta(NuevoDatoTxt);

            break;

            

          case 3:


            cout << "\t*** Editar Direccion ***" << endl << endl;

            cout << "\tIngrese la Nueva Direccion : ";

            getline( cin, NuevoDatoTxt );

            

            x->getDato()->setDireccion(NuevoDatoTxt);

            break;

            

          case 4:


            cout << "\t*** Editar Telefono ***" << endl << endl;

            cout << "\tIngrese el Nuevo Telefono : ";

            getline( cin, NuevoDatoTxt );

            

            x->getDato()->setTelefono(NuevoDatoTxt);

            break;

            

          case 5:


            cout << "\t*** Editar Correo Electronico ***" << endl << endl;

            cout << "\tIngrese el Nuevo Correo Electronico : ";

            getline( cin, NuevoDatoTxt );

            

            x->getDato()->setCorreoElectronico( NuevoDatoTxt );

            

            break;

            

          case 6:


            cout << "\t*** Editar Carrera ***" << endl << endl;

            cout << "\tIngrese la Nueva Carrera : ";

            getline( cin, NuevoDatoTxt );

            

            x->getDato()->setCarrera( NuevoDatoTxt );

            

            break;

            

          case 7:


            cout << "\t*** Editar Plantel ***" << endl << endl;

            cout << "\tIngrese el Nuevo Plantel : ";

            getline( cin, NuevoDatoTxt );

            

            x->getDato()->setPlantel( NuevoDatoTxt );

            

            break;

        

          case 8:


            cout << "\t*** Editar Periodos Academicos del Alumno ***" << endl << endl;

            

            x->getDato()->getPA()->Editar();

            

            break;

            

          case 9:

            cout << "\t*** VOLVIENDO AL MENU PRINCIPAL ***" << endl << endl;

            break;

          default:


            cout << "\t*** OPCION INCORRECTA, INTENTE DE NUEVO ***" << endl << endl;

        }

        cout <<endl;

        system ("pause");

    }while (Opcion != 9);

  }

  else

  {

    cout << "\t*** NO SE ENCONTRO AL ALUMNO ***" << endl;

  }

}



NodoAL * LDE :: Buscar( void )

{

  string cad;

  cout << "\t\tINGRESE EL NOMBRE DEL ALUMNO : ";

  getline( cin, cad ); //Limpia el \n del entero anterior

  getline( cin, cad );

  

  NodoAL *i = Inicio;

  while(i != NULL && i->getDato()->getNombre() != cad )

    i = i->getAptSig();

  

  return i;

}



void LDE :: Menu_LDE_Alumno( void )

{

  int opcion;

  

  do

  {

    system("cls");

    

    cout << "\t*** ALUMNOS REGISTRADOS ***" << endl << endl

         << "\t1. Insertar Nuevo Alumno " << endl

         << "\t2. Imprimir Lista de Alumnos " << endl

         << "\t3. Eliminar Alumno Existente " << endl

         << "\t4. Buscar Alumno Existente " << endl

         << "\t5. Editar Alumno Existente " << endl

         << "\t6. Salir del PIDAE. " << endl<< endl

         << "\tINTRODUZCA LA OPCION DESEADA: ";

    cin >> opcion;

    

    system("cls");

    switch( opcion )

    {

      case 1:

        cout << "\t***INSERTAR NUEVO ALUMNO***" << endl << endl;

        Insertar();

        break;

        

      case 2:


        cout << "\t***IMPRIMIR LISTA DE ALUMNOS***" << endl << endl;

        Imprimir();

        break;

      

      case 3:


        cout << "\t***ELIMINAR ALUMNO EXISTENTE***" << endl << endl;

        Eliminar();

        break;

        

      case 4:

        cout << "\t***BUSCAR ALUMNO EXISTENTE***" << endl << endl;

        NodoAL *x;

        x = Buscar();

        if( x != NULL )

            x->Imprimir();

        else

            cout << "***NO SE ENCONTRO NINGUN RESULTADO***" << endl << endl;

        break;

    

      case 5:


        cout << "\t***EDITAR ALUMNO EXISTENTE***" << endl << endl;

        Editar();

        break;

        

      case 6:


        cout << "\t***CERRANDO EL PIDAE...***" << endl<< endl;

        break;

      

      default:


        cout << "\t***LA OPCION ELEGIDA NO ES VALIDA, INTENTE DE NUEVO***" << endl<< endl;

    }

    cout <<'\t';  

    system ("pause");

    

  }while(opcion != 6); 

  

  cout << endl <<'\t';

}

    

LDE :: ~LDE ( void )

{

  NodoAL *Auxiliar;

  if ( (Inicio != NULL) && (Final != NULL ) ) //La lista tiene elementos

  {

    Final = NULL;

    

    while ( Inicio != NULL ) //Recorre toda la lista

    {

      Auxiliar = Inicio;

      Inicio = Inicio->getAptSig();

      delete Auxiliar;

    }

  }

  cout << "\t*** DESTRUCTOR LDE ***" << endl;

}
