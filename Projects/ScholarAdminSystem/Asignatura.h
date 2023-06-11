class Asignatura

{

  private:

    string Nombre;

    string Grupo;

    string Clave;

    string Profesor;

    float CalifDep1;

    float CalifDep2;

    float CalifDep3;

    float CalifExtra;

    float CalifFinal;

    float Creditos;

  public:

    Asignatura (void);

    Asignatura (string, string, string, string, float, float, float, float, float, float);

    

    void setNombre (string);

    void setGrupo (string);

    void setClave (string);

    void setProfesor (string);

    void setCalifDep1 (float);

    void setCalifDep2 (float);

    void setCalifDep3 (float);

    void setCalifExtra (float);

    void setCalifFinal (float);

    void setCreditos (float);

    

    string getNombre (void);

    string getGrupo (void);

    string getClave (void);

    string getProfesor (void);

    float getCalifDep1 (void);

    float getCalifDep2 (void);

    float getCalifDep3 (void);

    float getCalifExtra (void);

    float getCalifFinal (void);

    float getCreditos (void);

    

    void AsigExtra (void);

    void Calificaciones (void);

    void CalcCalifFinal (void);

    

    Asignatura& operator= (Asignatura * );

    

    void Leer (void);

    void Imprimir (void);

    

    ~Asignatura (void);

};
