class Alumno

{

  private:

    string Nombre;

    string Boleta;

    string Direccion;

    string Telefono;

    string CorreoElectronico;

    string Carrera;

    string Plantel;

    LSE_PA PA;

  public:

    Alumno ( void );

    Alumno ( string ,string ,string ,string ,string ,string ,string , LSE_PA);

    Alumno ( Alumno * );

    

    Alumno& operator= ( Alumno * );

    

    string getNombre ( void );

    string getBoleta ( void );

    string getDireccion ( void );

    string getTelefono ( void );

    string getCorreoElectronico ( void );

    string getCarrera ( void );

    string getPlantel ( void );

    LSE_PA* getPA ( void );

  

    void setNombre (string);

    void setBoleta (string);

    void setDireccion (string);

    void setTelefono (string);

    void setCorreoElectronico (string);

    void setCarrera (string);

    void setPlantel (string);

    void setPA (LSE_PA * );

    

    void Leer ( void );

    void Imprimir ( void );

    

    ~Alumno ( void );

};
