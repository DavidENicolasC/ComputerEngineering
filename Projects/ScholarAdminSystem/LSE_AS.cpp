LSE_AS :: LSE_AS ( void )

{

  Inicio = NULL;

}



LSE_AS :: LSE_AS ( NodoAS *_Inicio )

{

  Inicio = _Inicio;

}



LSE_AS :: LSE_AS ( LSE_AS * LA )

{

  Inicio = NULL;

  *this = LA;

  


  if( LA->Inicio != NULL && Inicio == NULL )


    cout << "\t*** NO HAY MEMORIA DISPONIBLE *** " << endl;


}

NodoAS* LSE_AS :: getInicio(void)

{

  return Inicio;

}



LSE_AS& LSE_AS :: operator = ( LSE_AS *LA )

{

  if ( this != LA ) //Aparte de evitar copiar la lista sobre sí misma, recordemos que primero se limpia para poder copiar los nodos de la del parámetro. por lo que tenemos que verificarlo para no borrar los nodos por error.

  {

    NodoAS* Aux;

    Aux = Inicio;

    while( Inicio != NULL ) //Limpieza de la lista

      EliminarInicio();

    

    NodoAS* Nuevo = new NodoAS();

    if ( LA->getInicio() != NULL && Nuevo != NULL ) //Se logro reservar memoria apuntada por Nodo

    {

        *Nuevo = *(LA->getInicio());

        Inicio = Nuevo;

        Aux = Inicio;

        Nuevo = NULL;

        

        for( NodoAS *i = LA->getInicio()->getAptSig() ; i != NULL ; i = i->getAptSig() )

        {

          Nuevo = new NodoAS();

          *Nuevo = *i;


          Aux->setAptSig( Nuevo ); //El ultimo nodo agregado a la nueva lista apunta al nodo recien creado

          Aux = Aux->getAptSig(); //Aux se mueve al siguiente nodo para ligarlo

          Nuevo = NULL;

        }

        Aux->setAptSig( NULL );

     }

  }

  return *this;

}



void LSE_AS :: Insertar ( void )

{

  NodoAS* Nuevo;


  Nuevo = new NodoAS();

  

  if ( Nuevo != NULL)

  {

    Nuevo->Leer(); //Primero se lee la informacion del nodo

    //Luego se decide donde se va a insertar

    int o;

    

    do

    {

      //system("cls");

      cout << "\t\tElija como quiere insertar la asignatura:" << endl

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

void LSE_AS :: InsertarInicio( NodoAS* N )

{

  N->setAptSig( Inicio ); //El nuevo nodo apunta al primero de la lista

  Inicio = N; //Ahora Inicio apunta a N y se convierte en el nuevo primer nodo

}

void LSE_AS :: InsertarDespues( NodoAS* N )

{

  NodoAS *x;

  do

  {

    x = Buscar();

    if( x != NULL )

    {

      N->setAptSig( x->getAptSig() );

      x->setAptSig( N );

    }

    else

      cout << "\t*** ASIGNATURA NO ENCONTRADA. INGRESE UNA EXISTENTE ***" << endl;

  }while( x == NULL ); //Si ingresa una materia erronea, se repite hasta que ingrese una correcta

}

void LSE_AS :: InsertarFinal( NodoAS* N )

{

  if( Inicio == NULL )

  {

    Inicio = N;

  }

  else

  {

    NodoAS *i = Inicio;

    while( i->getAptSig() != NULL )

      i = i->getAptSig();

    i->setAptSig( N );

  }

  N->setAptSig( NULL );

}



void LSE_AS :: Eliminar ( void )

{

  if ( Inicio != NULL)

  {

    int o;

    

    do

    {

      //system("cls");

      cout << "\t\tElija como quiere eliminar la asignatura:" << endl

           << "\t\t\t1.- Asignatura Al Inicio" << endl

           << "\t\t\t2.- Asignatura Especifica" << endl

           << "\t\t\t3.- Asignatura Al Final" << endl

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

          cout << "OPCION NO VALIDA. INTENTE DE NUEVO" << endl;

      }

    }while( o != 1 && o != 2 && o != 3 );

  }

  else

  {

    cout << "\t*** LA LISTA ESTA VACIA *** " << endl ;

  }

}

void LSE_AS :: EliminarInicio(void)

{

  NodoAS* Aux = Inicio;

  Inicio = Inicio->getAptSig();

  delete Aux;

  if( Inicio == NULL )

    cout << "\t***AHORA LA LISTA ESTA VACIA***" << endl << endl;

}

void LSE_AS :: EliminarEspecifico(void)

{

  NodoAS *x;

  do

  {

    x = Buscar();

    

    if( x != NULL )

    {

      NodoAS* i = Inicio;

      while( i->getAptSig() != x )

        i = i->getAptSig();

      i->setAptSig( x->getAptSig() );

      delete x;

    }

    else

      cout << "\tASIGNATURA NO ENCONTRADA. INTENTE DE NUEVO" << endl;

  }while( x == NULL );

}

void LSE_AS :: EliminarFinal( void )

{

  NodoAS* i = Inicio;

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

    NodoAS* Aux = i->getAptSig();

    i->setAptSig( NULL );

    delete Aux;

  }

}

NodoAS * LSE_AS :: Buscar( void )

{

  string cad;

  cout << "\t\tIngrese el nombre de la materia : ";

  getline( cin, cad );

  getline( cin, cad );

  

  NodoAS *i = Inicio;

  while(i != NULL && i->getDato()->getNombre() != cad )

    i = i->getAptSig();

  

  return i;

}



void LSE_AS :: EditarInfo (NodoAS * N )

{

  int Opcion;

  string NuevoDato;

  

  do

  {

    system ("cls");

      

    cout << "\t*** EDITAR INFORMACION DE LA ASIGNATURA ***" << endl << endl

         << "\t\t1.- Nombre " << endl

         << "\t\t2.- Grupo " << endl

         << "\t\t3.- Clave " << endl

         << "\t\t4.- Profesor " << endl

         << "\t\t5.- Regresar " << endl << endl;

      

    cout << "\tINTRODUZCA LA OPCION DESEADA: ";

    cin >> Opcion;

    

    getline( cin, NuevoDato );

    system("cls"); 

    switch( Opcion )

    {

      case 1:

        cout << "\t*** Editar Nombre ***" << endl << endl;

        cout << "Nombre Actual: " << N->getDato()->getNombre() << endl << endl;

            

        cout << "\tIngrese El nuevo NOMBRE :" ;


        getline( cin, NuevoDato );

            

        N->setNombre_Dato(NuevoDato);

      break;

      case 2:


        cout << "\t*** Editar Grupo ***" << endl << endl;

        cout << "Grupo Actual: " << N->getDato()->getGrupo() << endl << endl;

            

        cout << "\tIngrese El nuevo Grupo :" ;


        getline( cin, NuevoDato );

        N->setGrupo_Dato(NuevoDato);

      break;

      case 3:


        cout << "\t*** Editar Clave ***" << endl << endl;

        cout << "Clave Actual: " << N->getDato()->getClave() << endl << endl;

        

        cout << "\tIngrese la nueva Clave :" ;


        getline( cin, NuevoDato ); 

        N->setClave_Dato(NuevoDato);

      break;

      case 4:


        cout << "\t*** Editar Profesor ***" << endl << endl;

        cout << "Profesor Actual: " << N->getDato()->getProfesor() << endl << endl;

        

        cout << "\tIngrese El nuevo Profesor :" ;


        getline( cin, NuevoDato );

        N->setProfesor_Dato(NuevoDato);

      break;

      case 5:


        cout << "\t*** REGRESANDO AL MENU DE EDITAR ASIGNATURA ***" << endl << endl;

      break;

      default:


        cout << "\t***OPCION INCORRECTA, INTENTE DE NUEVO***" << endl<< endl;

    }

    cout <<'\t';  

//  system ("pause");

  }while (Opcion != 5);



}



void LSE_AS :: EditarCalif ( NodoAS *N )

{

  int Opcion;


  float NuevoDato;


  


  do

  {

    system ("cls");

      

    cout << "\t*** EDITAR CALIFICACIONES DE LA ASIGNATURA ***" << endl << endl

         << "\t\t1.- Calificacion Dep. 1 " << endl

         << "\t\t2.- Calificacion Dep. 2 " << endl

         << "\t\t3.- Calificacion Dep. 3 " << endl

         << "\t\t4.- Regresar " << endl << endl;

      

    cout << "\tINTRODUZCA LA OPCION DESEADA: ";

    cin >> Opcion;

    

    system("cls"); 

    switch( Opcion )

    {

      case 1:


        cout << "\t*** Editar Calificacion Dep. 1 ***" << endl << endl;

        cout << "\t** Calificacion Dep. 1 Actual: " << N->getDato()->getCalifDep1() << endl << endl;

            

        cout << "\tIngrese la nueva Calificacion Dep. 1 :" ;

        cin >> NuevoDato;
   

        N->setCD1_Dato(NuevoDato);

        break;

      case 2:


        cout << "\t*** Editar Calificacion Dep. 2 ***" << endl << endl;

        cout << "\t** Calificacion Dep. 2 Actual: " << N->getDato()->getCalifDep2() << endl << endl;

            

        cout << "\tIngrese la nueva Calificacion Dep. 2 :" ;

        cin >> NuevoDato;

        N->setCD2_Dato(NuevoDato);

        break;

      case 3:


        cout << "\t*** Editar Calificacion Dep. 3 ***" << endl << endl;

        cout << "\t** Calificacion Dep. 3 Actual: " << N->getDato()->getCalifDep3() << endl << endl;

            

        cout << "\tIngrese la nueva Calificacion Dep. 3 :" ;

        cin >> NuevoDato;

        N->setCD3_Dato(NuevoDato);

        break;

      case 4:



        cout << "\t*** REGRESANDO AL MENU DE EDITAR ASIGNATURA ***" << endl << endl;

        break;

      default:


        cout << "\t***OPCION INCORRECTA, INTENTE DE NUEVO***" << endl<< endl;

    }

    cout <<endl;

    N->RestablecerCalif();

    system ("pause");

  }while (Opcion != 4);

}



void LSE_AS :: Editar ( void )

{

  NodoAS *x;

  if ( Inicio != NULL )

  {

    x = Buscar();

    int opcion;

    if( x != NULL )

    {

      do

      {

        system("cls");

        

        x->Imprimir();

      

        cout << "\t*** MENU DE LA OPCION EDITAR ***" << endl << endl

             << "\t1. Editar Informacion de la Asignatura. " << endl

             << "\t2. Editar Calificaciones de la Asignatura. " << endl

             << "\t3. Regresar. " << endl << endl

             << "\tINTRODUZCA LA OPCION DESEADA: ";

        

        cin >> opcion;

      

        system("cls");

        switch( opcion )

        {

          case 1:


            cout << "\t***INGRESO A LA OPCION EDITAR INFORMACION ***" << endl << endl;

            this->EditarInfo( x );

            break;

          

          case 2:


            cout << "\t***INGRESO A LA OPCION EDITAR CALIFICACIONES***" << endl << endl;

            this->EditarCalif( x );

            break;

        

          case 3:


            cout << "\t*** REGRESANDO AL MENU DE ASIGNATURAS ***" << endl<< endl;

            break;

        

          default:


            cout << "\t***OPCION INCORRECTA, INTENTE DE NUEVO***" << endl<< endl;

        }

        cout <<'\t';  

        system ("pause");


      }while(opcion != 3);

    }

    else

      cout << "\t*** NO SE ENCONTRO LA ASIGNATURA *** " << endl;

  }

  else


    cout << "\t*** LA LISTA ESTA VACIA *** " << endl ;


}



void LSE_AS :: Imprimir ( void )

{

  if ( Inicio != NULL)

  {

    for ( NodoAS *i = Inicio; i != NULL; i = i->getAptSig() )

      i->Imprimir();

  }

  else

  {

    cout << "\t*** LA LISTA ESTA VACIA *** " << endl ;

  }

}



float LSE_AS :: getPromFinal ( void )

{

  float PromFinal = 0;

  int NAsig = 0;

  

  for (NodoAS* i = Inicio ; i != NULL ; i = i->getAptSig() )

  {

    PromFinal += i->getDato()->getCalifFinal();

    NAsig ++ ;

  }

  

  PromFinal = (PromFinal/NAsig);

  

  return PromFinal;

}



float LSE_AS :: getCreditosTotales ( void )

{

  float CredTot = 0;

  

  for (NodoAS* i = Inicio ; i != NULL ; i = i->getAptSig() )

  {

    CredTot += i->getDato()->getCreditos();

  }

  

  return CredTot;

}



void LSE_AS ::Menu_LSE_Asignatura (void)

{

  int opcion;

  

  do

  {

    system("cls");

    

    cout << "\tUnidades de Aprendizaje :" << endl << endl;

    cout << "\t*** MENU DE ASIGNATURA ***" << endl << endl;

    cout << "\t1. Insertar. " << endl;

    cout << "\t2. Imprimir. " << endl;

    cout << "\t3. Eliminar. " << endl;

    cout << "\t4. Editar. " << endl;

    cout << "\t5. Buscar. " << endl;

    cout << "\t6. Volver a Periodos Academicos " << endl << endl;

    cout << "\tINTRODUZCA LA OPCION DESEADA: ";

    cin >> opcion;

    

    system("cls");

    switch( opcion )

    {

      case 1:

        cout << "\t***INGRESO A LA OPCION INSERTAR***" << endl << endl;

        Insertar();

        break;

        

      case 2:


        cout << "\t***INGRESO A LA OPCION IMPRIMIR***" << endl << endl;

        Imprimir();

        break;

      

      case 3:


        cout << "\t***INGRESO A LA OPCION ELIMINAR ASIGNATURA***" << endl << endl;

        Eliminar();

        break;

      

      case 4:


        cout << "\t***INGRESO A LA OPCION EDITAR ASIGNATURA***" << endl << endl;

        Editar();

        break;

      

      case 5:

        cout << "\t***INGRESO A LA OPCION BUSCAR ASIGNATURA***" << endl << endl;

        NodoAS *x;

        x = Buscar();

        if( x != NULL )

            x->Imprimir();

        else

            cout << "\t***ASIGNATURA NO ENCONTRADA***" << endl << endl;

        

      case 6:


        cout << "\t***REGRESANDO AL MENU DE PERIODOS ACADEMICOS***" << endl<< endl;

        break;

      

      default:


        cout << "\t***OPCION INCORRECTA, INTENTE DE NUEVO***" << endl<< endl;

    }

    cout <<'\t';  

    system ("pause");

    

  }while(opcion != 6); 

  

  cout << endl;

}



LSE_AS :: ~LSE_AS ( void )

{

  NodoAS *Aux;

  if ( Inicio != NULL ) //La lista tiene elementos

  {

    while ( Inicio != NULL ) //Recorre toda la lista

    {

      Aux = Inicio;

      Inicio = Inicio->getAptSig();

      delete Aux;

    }

  }

  cout << "\t\t\t*** DESTRUCTOR LSE_Asignatura ***" << endl;

}

