LSE_PA :: LSE_PA ( void )

{

  Inicio = NULL;

}



LSE_PA :: LSE_PA ( NodoPA *_Inicio )

{

  Inicio = _Inicio;

}



LSE_PA :: LSE_PA ( LSE_PA * LA )

{

  Inicio = NULL;


  *this = *LA;

  if( LA->Inicio != NULL && this == NULL )

  {

    cout << "\t*** NO HAY MEMORIA DISPONIBLE :( *** " << endl ;

  }


}

NodoPA* LSE_PA::getInicio( void )

{

  return Inicio;

}



LSE_PA& LSE_PA :: operator = ( LSE_PA* LA )

{

  if ( this != LA )

  {

    NodoPA* Aux;

    


    while ( Inicio != NULL )

      EliminarInicio();

    

    if ( LA->getInicio() != NULL )

    {

      NodoPA* Nuevo;


      Nuevo = new NodoPA();

        

      *Nuevo = *LA->getInicio();

      Inicio = Nuevo;

      Aux = Inicio;

      Nuevo = NULL;

      

      for( NodoPA *i = LA->getInicio() ; i != NULL ; i = i->getAptSig() )

      {

        Nuevo = new NodoPA();

        *Nuevo = *i;


        Aux->setAptSig(Nuevo);

        Aux = Aux->getAptSig();

        Nuevo = NULL;

      }

      Aux->setAptSig(NULL);

    }

  }

  return *this;

} 



void LSE_PA :: Insertar ( void )

{

  NodoPA* Nuevo;

  NodoPA* Aux;

  Nuevo = new NodoPA();

  

  if ( Nuevo != NULL)

  {

    Nuevo->Leer();

    

    int o;

    

    do

    {

      system( "cls" );

      cout << "\t\tElija como quiere insertar el periodo academico:" << endl

           << "\t\t\t1.- Al Inicio" << endl

           << "\t\t\t2.- Despues de" << endl

           << "\t\t\t3.- Al Final" << endl

           << "\t\tIngrese su opcion: " << endl;

      cin >> o;

    

      switch( o )

      {

        case 1:

          InsertarInicio( Nuevo );

        break;

        case 2:

          InsertarDespues( Nuevo );

        break;

        case 3:

          InsertarFinal( Nuevo );

        break;

        default:

          cout << "OPCION NO VALIDA. INTENTE DE NUEVO" << endl;

      }

    }while( o != 1 && o != 2 && o != 3 );

  }

  else

  {

    cout << "\t*** NO HAY MEMORIA DISPONIBLE :( *** " << endl ;

  }

}

void LSE_PA :: InsertarInicio( NodoPA* N )

{

  N->setAptSig( Inicio ); //El nuevo nodo apunta al primero de la lista

  Inicio = N; //Ahora Inicio apunta a N y se convierte en el nuevo primer nodo

}

void LSE_PA :: InsertarDespues( NodoPA* N )

{

  NodoPA *x;

  do

  {

    x = Buscar();

    if( x != NULL )

    {

      N->setAptSig( x->getAptSig() );

      x->setAptSig( N );

    }

    else

      cout << "\t*** PERIODO ACADEMICO NO ENCONTRADO. INTENTE DE NUEVO***" << endl;

  }while( x == NULL ); //Si ingresa una materia erronea, se repite hasta que ingrese una correcta

}

void LSE_PA :: InsertarFinal( NodoPA* N )

{

  if( Inicio == NULL )

  {

    Inicio = N;

  }

  else

  {

    NodoPA *i = Inicio;

    while( i->getAptSig() != NULL )

      i = i->getAptSig();

    i->setAptSig( N );

  }

  N->setAptSig( NULL );

}



void LSE_PA :: Eliminar ( void )

{

  if ( Inicio != NULL)

  {

    int o;

    

    do

    {

      //system("cls");

      cout << "\t\tElija como quiere eliminar el periodo academico:" << endl

           << "\t\t\t1.- Periodo Academico Al Inicio" << endl

           << "\t\t\t2.- Periodo Academico Especifico" << endl

           << "\t\t\t3.- Periodo Academico Al Final" << endl

           << "\t\tIngrese su opcion: " << endl;

      cin >> o;

      switch( o )

      {

        case 1:

          EliminarInicio();

        break;

        case 2:

          EliminarEspecifico();

        break;

        case 3:

          EliminarFinal();

        break;

        default:

          cout << "\t***OPCION NO VALIDA. INTENTE DE NUEVO***" << endl;

      }

    }while( o != 1 && o != 2 && o != 3 );

  }

  else


    cout << "\t*** LA LISTA ESTA VACIA *** " << endl << endl;


}

void LSE_PA :: EliminarInicio(void)

{

  NodoPA* Aux = Inicio;

  Inicio = Inicio->getAptSig();

  delete Aux;

  if( Inicio == NULL )

      cout << "\t***LA LISTA ESTA VACIA***" << endl << endl;

}

void LSE_PA :: EliminarEspecifico(void)

{

  NodoPA *x;

  do

  {

    x = Buscar();

    

    if( x != NULL )

    {

      NodoPA* i = Inicio;

      while( i->getAptSig() != x )

        i = i->getAptSig();

      i->setAptSig( x->getAptSig() );

      delete x;

    }

    else

      cout << "\tPERIODO ACADEMICO NO ENCONTRADO. INGRESE UNO EXISTENTE" << endl;

  }while( x == NULL );

}

void LSE_PA :: EliminarFinal( void )

{

  NodoPA* i = Inicio;

  if( i->getAptSig() == NULL )

  {

    delete i;

    Inicio = NULL;

    cout << "\t***AHORA LA LISTA ESTA VACIA***" << endl << endl;

  }

  else

  {

    while( i->getAptSig()->getAptSig() != NULL )

      i = i->getAptSig();

    NodoPA* Aux = i->getAptSig();

    i->setAptSig( NULL );

    delete Aux;

  }

}



void LSE_PA :: Editar ( void )

{

  int Opcion;

  string NuevoDatoTxt;

  int NuevoDatoNum;

  

  NodoPA* x = Buscar();

  

  if( x != NULL )

  {

      do

      {

      system ("cls");

      

      cout << "\t*** EDITAR PERIODO ACADEMICO ***" << endl << endl ;

      cout << "\t\t1.- Periodo " << endl;

      cout << "\t\t2.- Turno " << endl;

      cout << "\t\t3.- Promedio " << endl;

      cout << "\t\t4.- Creditos Cursados " << endl;

      cout << "\t\t5.- Unidades de Aprendisajes " << endl;

      cout << "\t\t6.- Situacion Academica " << endl;

      cout << "\t\t7.- Regresar " << endl << endl;

      

      cout << "\tINTRODUZCA UNA OPCION: ";

      cin >> Opcion;

      

      getline( cin, NuevoDatoTxt );

      system("cls");

      switch( Opcion )

      {

        case 1:


            cout << "\t*** Editar Periodo ***" << endl << endl;

            cout << "\tIngrese el Nuevo Periodo :" ;


            getline( cin, NuevoDatoTxt );

            

            x->setPeriodo_Dato(NuevoDatoTxt);

            break;

        case 2:


            cout << "\t*** Editar Turno ***" << endl << endl;

            cout << "\tIngrese el Nuevo Turno :" ;


            getline( cin, NuevoDatoTxt );

            

            x->setTurno_Dato(NuevoDatoTxt);

            break;

            

        case 3:


            cout << "\t*** Editar Promedio ***" << endl << endl;

            cout << "\tIngrese el Nuevo Promedio :" ;

            cin >> NuevoDatoNum;

            

            x->setProm_Dato(NuevoDatoNum);

            break;

            

        case 4:


            cout << "\t*** Editar Creditos Cursados ***" << endl << endl;

            cout << "\tIngrese el Nuevo Creditos Cursados :" ;

            cin >> NuevoDatoNum;

            

            x->setCreditCursados_Dato(NuevoDatoNum);

            break;

            

        case 5:


            cout << "\t*** Editar Unidades de Aprendisajes ***" << endl << endl;

            

            x->getUADato()->Editar();

            

            break;

            

        case 6:


            cout << "\t*** Editar Situacion Academica ***" << endl << endl;

            

            getline( cin, NuevoDatoTxt );

            x->getSADato()->Leer();

            

            break;

        case 7:

            cout << "\t*** VOLVIENDO AL MENU DE PERIODOS ACADEMICOS ***" << endl << endl;

            break;

        default:


            cout << "\t***OPCION INCORRECTA, INTENTE DE NUEVO***" << endl << endl;

      }

      cout <<endl;

      system ("pause");

      }while (Opcion != 7);

  }

  else


    cout << "\t*** NO SE ENCONTRO EL PERIODO *** " << endl;


}

NodoPA * LSE_PA :: Buscar( void )

{

  string cad;

  cout << "\t\tINGRESE EL NOMBRE DEL PERIODO ACADEMICO : ";

  getline( cin, cad );

  getline( cin, cad );

  

  NodoPA *i;

  i = Inicio;

  while(i != NULL && i->getDato()->getPeriodo() != cad )

    i = i->getAptSig();

  

  return i;

}



void LSE_PA :: Imprimir ( void )

{

  if ( Inicio != NULL)

  {

    for ( NodoPA *i = Inicio; i != NULL; i = i->getAptSig() )

      i->Imprimir();

  }

  else

  {

    cout << "\t*** LA LISTA ESTA VACIA *** " << endl ;

  }

}



void LSE_PA ::Menu_LSE_PeriodoA (void)

{

  int opcion;

  

  do

  {

    system("cls");

    

    cout << "\t*** MENU DE PERIODO ACADEMICO ***" << endl << endl;

    cout << "\t1. Insertar. " << endl;

    cout << "\t2. Imprimir. " << endl;

    cout << "\t3. Eliminar. " << endl;

    cout << "\t4. Editar. " << endl;

    cout << "\t5. Buscar. " << endl;

    cout << "\t6. Regresar. " << endl << endl;

    cout << "\tINTRODUZCA LA OPCION DESEADA: ";

    cin >> opcion;

    

    system("cls");

    switch( opcion )

    {

      case 1:

        cout << "\t***INGRESO A LA OPCION INSERTAR NUEVO PERIODO ACADEMICO***" << endl << endl;

        Insertar();

        break;

        

      case 2:


        cout << "\t***INGRESO A LA OPCION IMPRIMIR LISTA DE PERIODOS ACADEMICOS***" << endl << endl;

        Imprimir();

        break;

      

      case 3:


        cout << "\t***INGRESO A LA OPCION ELIMINAR PERIODO ACADEMICO***" << endl << endl;

        Eliminar();

        break;

      

      case 4:


        cout << "\t***INGRESO A LA OPCION EDITAR PERIODO ACADEMICO***" << endl << endl;

        Editar();

        break;

      

      case 5:

        cout << "\t***INGRESO A LA OPCION BUSCAR PERIODO ACADEMICO***" << endl << endl; 

        NodoPA *x;

        x = Buscar();

        if( x!= NULL )

            x->Imprimir();

        else

            cout << "\t***NO SE ENCONTRO NINGUN RESULTADO***" << endl << endl;

        break;

        

      case 6:


        cout << "\t***REGRESANDO AL MENU DE ALUMNOS***" << endl<< endl;

        break;

      

      default:


        cout << "\t***OPCION INCORRECTA, INTENTE DE NUEVO***" << endl<< endl;

    }

      cout <<'\t';  

      system ("pause");

    

  }while(opcion != 6); 


}



LSE_PA :: ~LSE_PA ( void )

{

  NodoPA *Aux;

  if ( Inicio != NULL ) //La lista tiene elementos

  {

    while ( Inicio != NULL ) //Recorre toda la lista

    {

      Aux = Inicio;

      Inicio = Inicio->getAptSig();

      delete Aux;

    }

  }

  cout << "\t\t\t*** DESTRUCTOR LSE_Periodo_Academico ***" << endl;

}
