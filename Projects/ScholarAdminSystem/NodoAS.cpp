NodoAS :: NodoAS ( void )

{

  AptSig = NULL;

}



NodoAS :: NodoAS ( Asignatura _Dato ,NodoAS* _AptSig )

{

  Dato   = _Dato;

  AptSig = _AptSig;

}



NodoAS :: NodoAS ( NodoAS * NA )

{

  *this = *NA;

}



NodoAS& NodoAS :: operator= ( NodoAS* NA )

{

  Dato = NA->Dato;

  AptSig = NA->getAptSig();

  

  return *this;

}

  

Asignatura* NodoAS :: getDato ( void )

{

  return &Dato;

}



NodoAS* NodoAS :: getAptSig ( void )

{

  return AptSig;

}



void NodoAS :: setDato ( Asignatura * _Dato )

{

  Dato = *_Dato;

}



void NodoAS :: setClave_Dato ( string _DClave)

{

  Dato.setClave(_DClave);

}



void NodoAS :: setNombre_Dato ( string _DNombre)

{

  Dato.setNombre(_DNombre);

}



void NodoAS :: setGrupo_Dato ( string _DGrupo)

{

  Dato.setGrupo( _DGrupo);

}



void NodoAS :: setProfesor_Dato ( string _DProfesor)

{

  Dato.setProfesor(_DProfesor);

}



void NodoAS :: setCD1_Dato ( float _DCD1)

{

  Dato.setCalifDep1(_DCD1);

}



void NodoAS :: setCD2_Dato ( float _DCD2)

{

  Dato.setCalifDep2(_DCD2);

}



void NodoAS :: setCD3_Dato ( float _DCD3)

{

  Dato.setCalifDep3(_DCD3);

}

    

void NodoAS :: setAptSig ( NodoAS* _AptSig )

{

  AptSig = _AptSig;

}



void NodoAS :: RestablecerCalif (void)

{

  Dato.AsigExtra();

  Dato.CalcCalifFinal();

}



void NodoAS :: Leer ( void )

{

  cout << "\tIngrese los datos de la ASIGNATURA :" << endl << endl;

  Dato.Leer();

}



void NodoAS :: Imprimir ( void )

{

  cout << "\tLos datos de la ASIGNATURA son: " << endl << endl ;

  Dato.Imprimir();

}

    

NodoAS :: ~NodoAS ( void )

{

  cout << endl << "\t\t****Destructor NodoAS****" << endl ;

}

