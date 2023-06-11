NodoPA :: NodoPA ( void )

{

  AptSig = NULL;

}



NodoPA :: NodoPA ( Periodo_Academico _Dato ,NodoPA* _AptSig )

{

  Dato   = _Dato;

  AptSig = _AptSig;

}



NodoPA :: NodoPA ( NodoPA *NA)

{

  *this = *NA;

}



NodoPA& NodoPA :: operator= ( NodoPA * NA )

{

  if ( this != NA )

  {

    Dato   = NA->Dato;

    AptSig = NA->AptSig;

  }

  

  return *this;

}

  

Periodo_Academico* NodoPA :: getDato ( void )

{

  return &Dato;

}



LSE_AS* NodoPA :: getUADato ( void )

{

  return Dato.getUA();

}



string NodoPA :: getPeriodoDato ( void )

{

  return Dato.getPeriodo();

}



Situacion_Academica* NodoPA :: getSADato ( void )

{

  return Dato.getSA();

}



NodoPA* NodoPA :: getAptSig ( void )

{

  return AptSig;

}



void NodoPA :: setDato ( Periodo_Academico* _Dato )

{

  Dato = *_Dato;

}



void NodoPA :: setPeriodo_Dato ( string _Periodo)

{

  Dato.setPeriodo(_Periodo);

}



void NodoPA :: setTurno_Dato ( string _Turno)

{

  Dato.setTurno(_Turno);

}



void NodoPA :: setProm_Dato ( float _Prom)

{

  Dato.setPromedio(_Prom);

}



void NodoPA :: setCreditCursados_Dato ( float _CreditCursados)

{

  Dato.setCreditosCursados(_CreditCursados);

}

    

void NodoPA :: setAptSig ( NodoPA* _AptSig )

{

  AptSig = _AptSig;

}



void NodoPA :: Leer ( void )

{

  cout << "\tIngrese los datos de la Periodo Academico :" << endl << endl;

  Dato.Leer();

}



void NodoPA :: Imprimir ( void )

{

  cout << "\t**** Los datos del Periodo Academico son **** " << endl << endl ;

  Dato.Imprimir();

}

    

NodoPA :: ~NodoPA ( void )

{

  cout << endl << "\t\t****Destructor NodoPA****" << endl << endl ;

}
