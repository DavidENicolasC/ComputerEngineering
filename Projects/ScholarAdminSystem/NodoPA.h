class NodoPA

{

  private:

    Periodo_Academico Dato;

    NodoPA *AptSig;

  public:

    NodoPA ( void );

    NodoPA ( Periodo_Academico ,NodoPA* );

    NodoPA ( NodoPA * );

    

    NodoPA& operator= ( NodoPA *);

    

    Periodo_Academico *getDato ( void );

    LSE_AS* getUADato ( void );

    string getPeriodoDato ( void );

    Situacion_Academica* getSADato ( void );

    NodoPA* getAptSig ( void );

    

    void setDato ( Periodo_Academico* );

    void setPeriodo_Dato ( string );

    void setTurno_Dato ( string );

    void setProm_Dato ( float );

    void setCreditCursados_Dato ( float );

    void setAptSig ( NodoPA* );

    

    void Leer ( void );

    void Imprimir ( void );

    

    ~NodoPA ( void );

};
