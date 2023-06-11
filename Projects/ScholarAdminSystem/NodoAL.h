class NodoAL

{

  private:

    Alumno Dato;

    NodoAL *AptSig;

    NodoAL *AptAnt;

  public:

    NodoAL ( void );

    NodoAL ( Alumno ,NodoAL* ,NodoAL* );

    NodoAL ( NodoAL * );

    

    NodoAL& operator= ( NodoAL * );

    

    Alumno* getDato ( void );

    NodoAL* getAptSig ( void );

    NodoAL* getAptAnt ( void );

    

    void setDato ( Alumno* );

    void setAptSig ( NodoAL* );

    void setAptAnt ( NodoAL* );

    

    void Leer ( void );

    void Imprimir ( void );

    

    ~NodoAL ( void );

};
