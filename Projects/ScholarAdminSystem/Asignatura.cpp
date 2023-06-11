#include <iostream>

#include <string>

#include "Asignatura.h"

Asignatura :: Asignatura (void)

{

  Nombre   = "-Sin Asignar-";

  Grupo    = "-Sin Asignar-";

  Clave    = "-Sin Asignar-";

  Profesor = "-Sin Asignar-";

  

  CalifDep1  = 0;

  CalifDep2  = 0;

  CalifDep3  = 0;

  CalifExtra = 0;

  CalifFinal = 0;

  Creditos   = 0;

}



Asignatura :: Asignatura (string _Nombre, string _Grupo, string _Clave, string _Profesor, float _CalifDep1, float _CalifDep2, float _CalifDep3, float _CalifExtra, float _CalifFinal, float _Creditos)

{

  Nombre   = _Nombre;

  Grupo    = _Grupo;

  Clave    = _Clave;

  Profesor = _Profesor;

  

  CalifDep1  = _CalifDep1;

  CalifDep2  = _CalifDep2;

  CalifDep3  = _CalifDep3;

  CalifExtra = _CalifExtra;

  CalifFinal = _CalifFinal;

  Creditos   = _Creditos;  

}

    

void Asignatura :: setNombre (string _Nombre)

{

  Nombre   = _Nombre;

}



void Asignatura :: setGrupo (string _Grupo)

{

  Grupo    = _Grupo;

}



void Asignatura :: setClave (string _Clave)

{

  Clave    = _Clave; 

}



void Asignatura :: setProfesor (string _Profesor)

{

  Profesor = _Profesor;

}



void Asignatura :: setCalifDep1 (float _CalifDep1)

{

  CalifDep1  = _CalifDep1;

}



void Asignatura :: setCalifDep2 (float _CalifDep2)

{

  CalifDep2  = _CalifDep2;

}



void Asignatura :: setCalifDep3 (float _CalifDep3)

{

  CalifDep3  = _CalifDep3;  

}



void Asignatura :: setCalifExtra (float _CalifExtra)

{

  CalifExtra = _CalifExtra;

}



void Asignatura :: setCalifFinal (float _CalifFinal)

{

  CalifFinal = _CalifFinal;

}



void Asignatura :: setCreditos (float _Creditos)

{

  Creditos   = _Creditos;  

}

    

string Asignatura :: getNombre (void)

{

  return Nombre;

}



string Asignatura :: getGrupo (void)

{

  return Grupo;

}



string Asignatura :: getClave (void)

{

  return Clave;

}



string Asignatura :: getProfesor (void)

{

  return Profesor;

}



float Asignatura :: getCalifDep1 (void)

{

  return CalifDep1;

}



float Asignatura :: getCalifDep2 (void)

{

  return CalifDep2;

}



float Asignatura :: getCalifDep3 (void)

{

  return CalifDep3;

}



float Asignatura :: getCalifExtra (void)

{

  return CalifExtra;

}



float Asignatura :: getCalifFinal (void)

{

  return CalifFinal;

}



float Asignatura :: getCreditos (void)

{

  return Creditos;

}



void Asignatura :: CalcCalifFinal ( void )

{

  if ( ((CalifDep1 + CalifDep2 + CalifDep3) < 18) && (  (CalifDep1 + CalifDep2 + CalifDep3) < (3 * CalifExtra) ) ) 

  CalifFinal = CalifExtra ;

  else

  CalifFinal = (CalifDep1 + CalifDep2 + CalifDep3) / 3 ;

}

Asignatura& Asignatura :: operator = ( Asignatura* A )

{

  this->Nombre = A->Nombre;

  this->Grupo = A->Grupo;

  this->Clave = A->Clave;

  this->Profesor = A->Profesor;

  this->CalifDep1 = A->CalifDep1;

  this->CalifDep2 = A->CalifDep2;

  this->CalifDep3 = A->CalifDep3;

  this->CalifExtra = A->CalifExtra;

  this->CalifFinal = A->CalifFinal;

  this->Creditos = A->Creditos;

  

  return *this;

}

    

void Asignatura :: Leer (void)

{

  cout << "\t\t    -Informacion de la Asignatura- " << endl ;

  getline( cin, Nombre );

  cout << "\t\tNombre             : " ;

  getline( cin, Nombre );

  

  if ( Nombre.length() == 0 )

  {

    Nombre = "-Sin Informacion-";

  }

  


  cout << "\t\tGrupo              : " ;

  getline(cin, Grupo);

  

  if ( Grupo.length() == 0 )

  {

    Grupo = "-Sin Informacion-";

  }

  


  cout << "\t\tClave              : " ;

  getline(cin, Clave);

  

  if ( Clave.length() == 0 )

  {

    Clave = "-Sin Informacion-";

  }

  


  cout << "\t\tProfesor           : " ;

  getline(cin, Profesor);

  

  if ( Profesor.length() == 0 )

  {

    Profesor = "-Sin Informacion-";

  }

  

  cout << "\t\t           -Calificaciones- " << endl ;

  

  this->Calificaciones();

  this->CalcCalifFinal();

  

  cout << "\t\tCreditos           : " ;

  cin >> Creditos ;

  

  cout << endl;

}



void Asignatura :: Calificaciones (void)

{

  cout << "\t\tCalificacion Dep 1 : " ;

  cin >> CalifDep1 ;

  

  cout << "\t\tCalificacion Dep 2 : " ;

  cin >> CalifDep2 ;

  

  cout << "\t\tCalificacion Dep 3 : " ;

  cin >> CalifDep3 ;

  

  if( (CalifDep1 + CalifDep2 + CalifDep3) < 18 )

  {

    cout << "\t\tEl alumno reprobó el periodo ordinario." << endl;

    this->AsigExtra();

  }

  else

  {

    int x;

    cout << "\t\t¿El alumno presenta extraordinario\?" << endl;

    cout << "\t\t1.- Si" << endl;

    cout << "\t\t0.- No" << endl;

    cout << "\t\t\tElija una opcion: ";

    cin >> x;

    if( x == 1 )

      this->AsigExtra();

  }

}



void Asignatura :: AsigExtra (void)

{

  cout << "\t\tCalificacion Extraordinario : " ;

  cin >> CalifExtra ;


}



void Asignatura :: Imprimir (void)

{

  cout << "\t\tNombre                : " << Nombre   << endl;

  cout << "\t\tGrupo                 : " << Grupo    << endl;

  cout << "\t\tClave                 : " << Clave    << endl;

  cout << "\t\tProfesor              : " << Profesor << endl;

  

  cout << endl ;

  

  cout << "\t\tCalificacion Dep 1    : " << CalifDep1  << endl;

  cout << "\t\tCalificacion Dep 2    : " << CalifDep2  << endl;

  cout << "\t\tCalificacion Dep 3    : " << CalifDep3  << endl;

  cout << "\t\tCalificacion Extra    : " << CalifExtra << endl;

  cout << "\t\tCalificacion final    : " << CalifFinal << endl;

  cout << "\t\tCreditos              : " << Creditos      << endl;

  

  cout << endl ;

}

    

Asignatura :: ~Asignatura (void)

{

  cout << "\t*** DESTRUCTOR ASIGNATURA *** " << endl;

}
