Alumno :: Alumno ( void )

{

  Nombre    = "-Sin Asignar-";

  Boleta    = "-Sin Asignar-";

  Direccion = "-Sin Asignar-";

  Telefono  = "-Sin Asignar-";

  CorreoElectronico = "-Sin Asignar-";

  Carrera   = "-Sin Asignar-";

  Plantel   = "-Sin Asignar-";

}

Alumno :: Alumno ( string _Nombre,string _Boleta,string _Direccion,string _Telefono,string _CorreoElectronico,string _Carrera,string _Plantel, LSE_PA _PA)

{

  Nombre    = _Nombre;

  Boleta    = _Boleta;

  Direccion = _Direccion;

  Telefono  = _Telefono;

  CorreoElectronico = _CorreoElectronico;

  Carrera   = _Carrera;

  Plantel   = _Plantel;

  PA = _PA;

}



Alumno :: Alumno ( Alumno * A )

{

  *this = *A;

}



Alumno& Alumno :: operator= ( Alumno * A )

{

  if (this != A)

  {

    Nombre    = A->Nombre;

    Boleta    = A->Boleta;

    Direccion = A->Direccion;

    Telefono  = A->Telefono;

    CorreoElectronico = A->CorreoElectronico;

    Carrera   = A->Carrera;

    Plantel   = A->Plantel;

    PA = A->PA;

  }

  

  return *this;

}



string Alumno :: getNombre ( void )

{

  return Nombre;

}



string Alumno :: getBoleta ( void )

{

  return Boleta;

}



string Alumno :: getDireccion ( void )

{

  return Direccion;

}



string Alumno :: getTelefono ( void )

{

  return Telefono;

}



string Alumno :: getCorreoElectronico ( void )

{

  return CorreoElectronico;

}



string Alumno :: getCarrera ( void )

{

  return Carrera;

}



string Alumno :: getPlantel ( void )

{

  return Plantel;

}



LSE_PA* Alumno :: getPA ( void )

{

  return &PA;

}

  

void Alumno :: setNombre (string _Nombre)

{

  Nombre    = _Nombre;

  

}



void Alumno :: setBoleta (string _Boleta)

{

  Boleta    = _Boleta;

  

}



void Alumno :: setDireccion (string _Direccion)

{

  Direccion = _Direccion;

  

}



void Alumno :: setTelefono (string _Telefono)

{

  Telefono  = _Telefono;

  

}



void Alumno :: setCorreoElectronico (string _CorreoElectronico)

{

  CorreoElectronico = _CorreoElectronico;

  

}



void Alumno :: setCarrera (string _Carrera)

{

  Carrera   = _Carrera;

  

}



void Alumno :: setPlantel (string _Plantel)

{

  Plantel   = _Plantel;

}



void Alumno :: setPA (LSE_PA * _PA)

{

  PA = *_PA;

}

    

void Alumno :: Leer ( void )

{

  getline( cin, Nombre );

  cout << "\t\tNombre del Alumno  : " ;

  getline(cin, Nombre);

  


  cout << "\t\tBoleta             : " ;

  getline(cin, Boleta);

  


  cout << "\t\tDireccion          : " ;

  getline(cin, Direccion);

  


  cout << "\t\tTelefono           : " ;

  getline(cin, Telefono);

  


  cout << "\t\tCorreo Electronico : " ;

  getline(cin, CorreoElectronico);

  


  cout << "\t\tCarrera            : " ;

  getline(cin, Carrera);

  


  cout << "\t\tPlantel            : " ;

  getline(cin, Plantel);

  

  PA.Menu_LSE_PeriodoA();

}



void Alumno :: Imprimir ( void )

{

  cout << "\t\tNombre             : " << Nombre   << endl;

  cout << "\t\tDireccion          : " << Direccion     << endl;

  cout << "\t\tTelefono           : " << Telefono     << endl;

  cout << "\t\tCorreo Electronico : " << CorreoElectronico << endl;

  cout << "\t\tCarrera            : " << Carrera    << endl;

  cout << "\t\tPlantel            : " << Plantel << endl;

  

  cout << endl ;

  

  PA.Imprimir();

}

    

Alumno :: ~Alumno ( void )

{

  cout << "\t*** DESTRUYE ALUMNO ***" << endl;

}
