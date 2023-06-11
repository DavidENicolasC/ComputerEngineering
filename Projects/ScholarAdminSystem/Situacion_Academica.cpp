#include <iostream>

#include <string>

#include "Situacion_Academica.h"

Situacion_Academica :: Situacion_Academica (void)

{

  Estado          = "-Sin Asignar-";

  DictamenCOSIE   = false;

  DictamenGeneral = false;

  CargaMinima     = 0;

  CargaMedia      = 0;

  CargaMaxima     = 0;

}



Situacion_Academica :: Situacion_Academica (string _Estado, bool _DictamenCOSIE, bool _DictamenGeneral, int _CargaMinima, int _CargaMedia, int _CargaMaxima)

{

  Estado          = _Estado;

  DictamenCOSIE   = _DictamenCOSIE;

  DictamenGeneral = _DictamenGeneral;

  CargaMinima     = _CargaMinima;

  CargaMedia      = _CargaMedia;

  CargaMaxima     = _CargaMaxima;

}



string Situacion_Academica :: getEstado (void)

{

  return Estado;

}

    

bool Situacion_Academica :: getDictamenCOSIE (void)

{

  return DictamenCOSIE;

}



bool Situacion_Academica :: getDictamenGeneral (void)

{

  return DictamenGeneral;

}



int Situacion_Academica :: getCargaMinima (void)

{

  return CargaMinima;

}



int Situacion_Academica :: getCargaMedia (void)

{

  return CargaMedia;

}



int Situacion_Academica :: getCargaMaxima (void)

{

  return CargaMaxima;

}



void Situacion_Academica :: setEstado (string _Estado)

{

  Estado          = _Estado;

}



void Situacion_Academica :: setDictamenCOSIE (bool _DictamenCOSIE)

{

  DictamenCOSIE   = _DictamenCOSIE;

}



void Situacion_Academica :: setDictamenGeneral (bool _DictamenGeneral)

{

  DictamenGeneral = _DictamenGeneral;

}



void Situacion_Academica :: setCargaMinima (int _CargaMinima)

{

  CargaMinima     = _CargaMinima;

}



void Situacion_Academica :: setCargaMedia (int _CargaMedia)

{

  CargaMedia      = _CargaMedia;

}



void Situacion_Academica :: setCargaMaxima (int _CargaMaxima)

{

  CargaMaxima     = _CargaMaxima;

}

Situacion_Academica& Situacion_Academica :: operator = ( Situacion_Academica *S )

{

  this->Estado = S->Estado;

  this->DictamenCOSIE = S->DictamenCOSIE;

  this->DictamenGeneral = S->DictamenGeneral;

  this->CargaMinima = S->CargaMinima;

  this->CargaMedia = S->CargaMedia;

  this->CargaMaxima = S->CargaMaxima;

  

  return *this;

}



void Situacion_Academica :: Leer (void)

{

  int DicCOSIE;

  int DicGen;

  

  cout << "\t\tEstado del Alumno: ";


  getline( cin, Estado );

  

  do

  {

    cout << "\t\tDictamen COSIE: " << endl ;

    cout << "\t\t\t1.- Si " << endl;

    cout << "\t\t\t0.- No " << endl << endl;

    cout << "\t\t\tElija una opcion : ";

    cin >> DicCOSIE;

    

    if ( DicCOSIE == 1 )


      DictamenCOSIE = true;

    else
 if( DicCOSIE == 0 )


      DictamenCOSIE = false;


        

  }while ( (DicCOSIE != 1) && (DicCOSIE != 0) );

  

  do

  {

    cout << "\t\tDictamen General: " << endl ;

    cout << "\t\t\t1.- Si " << endl;

    cout << "\t\t\t0.- No " << endl << endl;

    cout << "\t\t\tElija una opcion : ";

    cin >> DicGen;

    

    if ( DicGen == 1 )


      DictamenGeneral = true;


    else if( DicGen == 0 )


      DictamenGeneral = false;



  }while ( (DicGen != 1) && (DicGen != 0) );

  

  this->AsigCarga();

}



void Situacion_Academica :: AsigCarga (void)

{

  if( (DictamenCOSIE == false ) && (DictamenGeneral == false) )

  {

    CargaMinima = 3 ;

    CargaMedia  = 6 ;

    CargaMaxima = 12;

  }

  if( ((DictamenCOSIE == true ) && (DictamenGeneral == false)) || ((DictamenCOSIE == false ) && (DictamenGeneral == true)))

  {

    CargaMinima = 4 ;

    CargaMedia  = 6 ;

    CargaMaxima = 8;

  }

  if( (DictamenCOSIE == true ) && (DictamenGeneral == true) )

  {

    CargaMinima = 5 ;

    CargaMedia  = 6 ;

    CargaMaxima = 7 ;

  }

}



void Situacion_Academica :: Imprimir (void)

{

  cout << "\t\tEstado del Alummno    : " << Estado << endl;

  cout << "\t\tDictamen COSIE        : " << this->ValidarDicCOSIE() << endl;

  cout << "\t\tDictamen General      : " << this->ValidarDicGen() << endl;

  cout << "\t\tDictamen Carga Minima : " << CargaMinima << endl;

  cout << "\t\tDictamen Carga Media  : " << CargaMedia << endl;

  cout << "\t\tDictamen Carga Maxima : " << CargaMaxima << endl;

}



string Situacion_Academica :: ValidarDicCOSIE (void)

{

  return (DictamenCOSIE == false) ? "No" : "Si" ;

}



string Situacion_Academica :: ValidarDicGen (void)

{

  return (DictamenGeneral == false) ? "No" : "Si" ;

}



Situacion_Academica :: ~Situacion_Academica (void)

{

  cout << "\t*** Destructor Situacion_Academica *** " << endl;

}
