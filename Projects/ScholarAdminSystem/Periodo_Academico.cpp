Periodo_Academico :: Periodo_Academico (void)

{

  Turno = "-Sin Asignar-";

  Promedio = 0;

  CreditosCursados = 0;

  CreditosTotales = 450;

  CreditosRestantes = 0;

}



Periodo_Academico :: Periodo_Academico ( string _Turno, float _Promedio, float _CreditosCursados, float _CreditosTotales, float _CreditosRestantes, LSE_AS _UA, Situacion_Academica _SA)

{

  Turno = _Turno;

  Promedio = _Promedio;

  CreditosCursados = _CreditosCursados;

  CreditosTotales = _CreditosTotales;

  CreditosRestantes = _CreditosRestantes;

  UA = _UA;

  SA = _SA;

}

    

string Periodo_Academico :: getTurno (void)

{

  return Turno;

}



float Periodo_Academico :: getPromedio (void)

{

  return Promedio;

}



float Periodo_Academico :: getCreditosCursados (void)

{

  return CreditosCursados;

}



float Periodo_Academico :: getCreditosTotales (void)

{

  return CreditosTotales;

}



float Periodo_Academico :: getCreditosRestantes (void)

{

  return CreditosRestantes;

}



LSE_AS* Periodo_Academico :: getUA (void)

{

  return &UA;

}



Situacion_Academica* Periodo_Academico :: getSA (void)

{

  return &SA;

}



string Periodo_Academico :: getPeriodo (void)

{

  return Periodo;

}

    

void Periodo_Academico :: setTurno (string _Turno)

{

  Turno = _Turno;

  

}



void Periodo_Academico :: setPeriodo (string _Periodo)

{

  Periodo = _Periodo;

  

}



void Periodo_Academico :: setPromedio (float _Promedio)

{

  Promedio = _Promedio;

  

}



void Periodo_Academico :: setCreditosCursados (float _CreditosCursados)

{

  CreditosCursados = _CreditosCursados;

  

}



void Periodo_Academico :: setCreditosTotales (float _CreditosTotales)

{

  CreditosTotales = _CreditosTotales;

  

}



void Periodo_Academico :: setCreditosRestantes (float _CreditosRestantes)

{

  CreditosRestantes = _CreditosRestantes;

  

}



void Periodo_Academico :: setUA (LSE_AS* _UA)

{

  UA = *_UA;

}



void Periodo_Academico :: setSA (Situacion_Academica* _SA)

{

  SA = *_SA;

}



void Periodo_Academico :: CalcCreditos (void)

{

  CreditosCursados = UA.getCreditosTotales();

  CreditosRestantes= CreditosTotales - CreditosCursados ;

}

Periodo_Academico& Periodo_Academico :: operator = ( Periodo_Academico *P )

{

  Turno = P->Turno;

  Periodo = P->Periodo;

  Promedio = P->Promedio;

  CreditosCursados = P->CreditosCursados;

  CreditosTotales = P->CreditosTotales;

  CreditosRestantes = P->CreditosRestantes;

  UA = P->UA;

  SA = P->SA;

}

  

void Periodo_Academico :: Leer (void)

{

  getline( cin, Turno );

  cout << "\t\tTurno   :";


  getline( cin, Turno );

  

  cout << "\t\tPeriodo :";


  getline( cin, Periodo );

  

  cout << "\tSituacion Academica :" << endl << endl ;

  SA.Leer();

  

  UA.Menu_LSE_Asignatura();



  Promedio = UA.getPromFinal();

  

  CalcCreditos();

}



void Periodo_Academico :: Imprimir (void)

{

  cout << "\t\tPeriodo               :" << Periodo << endl ;

  cout << "\t\tTurno                 :" << Turno << endl ;

  cout << "\t\tPromedio              :" << Promedio << endl ;

  cout << "\t\tCreditos Cursados     :" << CreditosCursados << endl ;

  cout << "\t\tCreditos Totales      :" << CreditosTotales << endl ;

  cout << "\t\tCreditos Restantes    :" << CreditosRestantes << endl << endl ;

  UA.Imprimir();

  cout  << "\tSituacion Academica :" << endl << endl ;

  SA.Imprimir();

}

    

Periodo_Academico :: ~Periodo_Academico (void)

{

  cout << "\t*** Destructor Periodo_Academico *** " << endl;

}
