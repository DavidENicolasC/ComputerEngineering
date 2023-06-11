NodoAL :: NodoAL ( void )

{

  AptSig = NULL;

  AptAnt = NULL;

}



NodoAL :: NodoAL ( Alumno _Dato ,NodoAL* _AptSig ,NodoAL* _AptAnt )

{

  Dato   = _Dato;

  AptSig = _AptSig;

  AptAnt = _AptAnt;

}



NodoAL :: NodoAL ( NodoAL * NA )

{

  *this = *NA;

}



NodoAL& NodoAL :: operator= ( NodoAL * NA )

{

  if ( this != NA )

  {

    Dato   = NA->Dato;

    AptSig = NA->AptSig;

    AptAnt = NA->AptAnt;

  }

  

  return *this;

}

  

Alumno* NodoAL :: getDato ( void )

{

  return &Dato;

}



NodoAL* NodoAL :: getAptSig ( void )

{

  return AptSig;

}



NodoAL* NodoAL :: getAptAnt ( void )

{

  return AptAnt;

}



void NodoAL :: setDato ( Alumno* _Dato )

{

  Dato = *_Dato;

}



void NodoAL :: setAptSig ( NodoAL* _AptSig )

{

  AptSig = _AptSig;

}



void NodoAL :: setAptAnt ( NodoAL* _AptAnt )

{

  AptAnt = _AptAnt;

}



void NodoAL :: Leer ( void )

{

  cout << "\t*** Ingrese los datos del Alumno ***" << endl << endl;

  Dato.Leer();

}



void NodoAL :: Imprimir ( void )

{

  cout << "\t***Los datos del Alumno son *** " << endl << endl ;

  Dato.Imprimir();

}

    

NodoAL :: ~NodoAL ( void )

{

  cout << endl << "\t\t****Destructor Nodo_Alumno****" << endl << endl ;

}
