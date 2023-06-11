void VaciaInformacion(LDE *L)

{

  ofstream file;

  

  file.open("archivo.txt", ios::out);

  

  if( !file.fail() )

  {

    NodoAL *X = L->getInicio(); //Recorre los Alumnos

    while( X != NULL ) //Ciclo dentro de los Alumnos

    {

      file << "ALUMNO" << endl;

      file << X->getDato()->getNombre() << endl;

      file << X->getDato()->getBoleta() << endl;

      file << X->getDato()->getDireccion() << endl;

      file << X->getDato()->getTelefono() << endl;

      file << X->getDato()->getCorreoElectronico() << endl;

      file << X->getDato()->getCarrera() << endl;

      file << X->getDato()->getPlantel() << endl;

      NodoPA *Y = X->getDato()->getPA()->getInicio(); //Recorre los Periodos Academicos del Alumno seleccionado

      while( Y != NULL ) //Ciclo dentro de los Periodos Academicos del Alumno seleccionado

      {

        file << "PERIODO ACADEMICO" << endl;

        file << Y->getDato()->getTurno() << endl;

        file << Y->getDato()->getPeriodo() << endl;

        file << Y->getDato()->getPromedio() << endl;

        file << Y->getDato()->getCreditosCursados() << endl;

        file << Y->getDato()->getCreditosTotales() << endl;

        file << Y->getDato()->getCreditosRestantes() << endl;

        //Situación Académica. Recordemos que es un único objeto

        file << "SITUACION ACADEMICA" << endl;

        file << Y->getSADato()->getEstado() << endl;

        file << Y->getSADato()->getDictamenCOSIE() << endl;

        file << Y->getSADato()->getDictamenGeneral() << endl;

        file << Y->getSADato()->getCargaMinima() << endl;

        file << Y->getSADato()->getCargaMedia() << endl;

        file << Y->getSADato()->getCargaMaxima() << endl;

        NodoAS *Z = Y->getUADato()->getInicio(); //Recorre las Asignaturas dentro del Periodo Académico seleccionado del Alumno seleccionado

        while( Z != NULL ) //Ciclo dentro de las Asignaturas del Periodo Académico seleccionado del Alumno seleccionado

        {

          file << "ASIGNATURA" << endl;

          file << Z->getDato()->getNombre() << endl;

          file << Z->getDato()->getClave() << endl;

          file << Z->getDato()->getGrupo() << endl;

          file << Z->getDato()->getProfesor() << endl;

          file << Z->getDato()->getCalifDep1() << endl;

          file << Z->getDato()->getCalifDep2() << endl;

          file << Z->getDato()->getCalifDep3() << endl;

          file << Z->getDato()->getCalifExtra() << endl;

          file << Z->getDato()->getCalifFinal() << endl;

          file << Z->getDato()->getCreditos() << endl;

          Z = Z->getAptSig(); //Se cambia a la siguiente Asignatura

        }

        file << "FIN ASIGNATURA" << endl;

        Y = Y->getAptSig(); //Se cambia al siguiente Periodo Academico

      }

      file << "FIN PERIODO ACADEMICO" << endl;

      X = X->getAptSig(); //Se cambia al siguiente Alumno

    }

    file << "FIN ALUMNO" << endl;

    file.close();

    cout << "LA BASE DE DATOS DE ALUMNOS HA SIDO ACTUALIZADA." << endl;

  }

  else

    cout << "Error al abrir el archivo" << endl;

}

  

void CargaInformacion(LDE *A)

{

  ifstream file;

  string texto;

  string Al("FIN ALUMNO");

  string Pe("FIN PERIODO ACADEMICO");

  string As("FIN ASIGNATURA");

  NodoAL *X;

  NodoPA *Y;

  NodoAS *Z;

  

  file.open("archivo.txt", ios::in);

  

  if( !file.fail() )

  {

    getline( file, texto );

    while( texto.compare(Al) ) //Ciclo dentro de los Alumnos

    {

      X = new NodoAL();

      getline( file, texto );

      X->getDato()->setNombre(texto);

      getline( file, texto );

      X->getDato()->setBoleta(texto);

      getline( file, texto );

      X->getDato()->setDireccion(texto);

      getline( file, texto );

      X->getDato()->setTelefono(texto);

      getline( file, texto );

      X->getDato()->setCorreoElectronico(texto);

      getline( file, texto );

      X->getDato()->setCarrera(texto);

      getline( file, texto );

      X->getDato()->setPlantel(texto);

      A->InsertarFinal( X );

      getline( file, texto ); //Toma sus periodos

      while( texto.compare( Pe ) ) //Ciclo dentro de los Periodos Academicos del Alumno seleccionado

      {

        cout << "COMPARA" << texto.compare( Pe ) << endl;

        Y = new NodoPA();

        getline( file, texto );

        Y->getDato()->setTurno(texto);

        getline( file, texto );

        Y->getDato()->setPeriodo( texto );

        getline( file, texto );

        Y->getDato()->setPromedio( atof( texto.c_str() ) );

        getline( file, texto );

        Y->getDato()->setCreditosCursados( atof( texto.c_str() ) );

        getline( file, texto );

        Y->getDato()->setCreditosTotales( atof( texto.c_str() ) );

        getline( file, texto );

        Y->getDato()->setCreditosRestantes( atof( texto.c_str() ) );

        //Situación Académica. Recordemos que es un único objeto

        getline( file, texto );

        getline( file, texto );

        Y->getSADato()->setEstado(texto);

        getline( file, texto );

        Y->getSADato()->setDictamenCOSIE( atoi( texto.c_str() ) );

        getline( file, texto );

        Y->getSADato()->setDictamenGeneral( atoi( texto.c_str() ) );

        getline( file, texto );

        Y->getSADato()->setCargaMinima( atoi( texto.c_str() ) );

        getline( file, texto );

        Y->getSADato()->setCargaMedia( atoi( texto.c_str() ) );

        getline( file, texto );

        Y->getSADato()->setCargaMaxima( atoi( texto.c_str() ) );

        A->getFinal()->getDato()->getPA()->InsertarFinal( Y );

        getline( file, texto ); //Toma sus asignaturas

        while( texto.compare( As ) ) //Ciclo dentro de las Asignaturas del Periodo Académico seleccionado del Alumno seleccionado

        {

          Z = new NodoAS();

          getline( file, texto );

          Z->getDato()->setNombre(texto);

          getline( file, texto );

          Z->getDato()->setClave(texto);

          getline( file, texto );

          Z->getDato()->setGrupo( texto );

          getline( file, texto );

          Z->getDato()->setProfesor( texto );

          getline( file, texto );

          Z->getDato()->setCalifDep1( atof( texto.c_str() ) );

          getline( file, texto );

          Z->getDato()->setCalifDep2( atof( texto.c_str() ) );

          getline( file, texto );

          Z->getDato()->setCalifDep3( atof( texto.c_str() ) );

          getline( file, texto );

          Z->getDato()->setCalifExtra( atof( texto.c_str() ) );

          getline( file, texto );

          Z->getDato()->setCalifFinal( atof( texto.c_str() ) );

          getline( file, texto );

          Z->getDato()->setCreditos( atof( texto.c_str() ) );

          getline( file, texto ); //Busca el Fin Asignatura

          cout << "BANDERA " << texto << endl;

          cout << "COMPARA " << texto.compare( As ) << endl;

          system("pause");

          Y->getUADato()->InsertarFinal( Z );

          Z = NULL;

        }

        getline( file, texto ); //Busca el Fin Periodo Academico. sino, es por que hay otro

        A->Imprimir();

        Y = NULL;

      }

      getline( file, texto ); //busca el Fin Alumno. Sino, es por que hay otro

      X = NULL;

    }

    file.close();

    cout << "LA INFORMACIÓN DE LA BASE DE DATOS HA SIDO CARGADA EN MEMORIA." << endl;

  }

  else

    cout << "Error al abrir el archivo o solicitar memoria" << endl;

}

  

int main() 

{ 

   LDE A;

  

  CargaInformacion( &A );

  

  cout << "Plataforma Integral De Administracion Escolar" << endl

       << "Instituto Politecnico Nacional" << endl

       << "Escuela Superior de Ingenieria Mecanica y Electrica" << endl

       << "Unidad Culhuacan" << endl;

  

  A.Menu_LDE_Alumno();

  

  VaciaInformacion( &A );

  

  return 0;

} 
