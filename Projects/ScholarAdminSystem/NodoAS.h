class NodoAS

{

  private:

    Asignatura Dato;

    NodoAS *AptSig;

  public:

    NodoAS ( void );

    NodoAS ( Asignatura ,NodoAS* );

    NodoAS ( NodoAS* );

    

    NodoAS& operator= ( NodoAS *);

    

    Asignatura* getDato ( void );

    NodoAS* getAptSig ( void );

    

    void setDato ( Asignatura* );

    void setClave_Dato ( string );

    void setNombre_Dato ( string );

    void setGrupo_Dato ( string );

    void setProfesor_Dato ( string );

    void setCD1_Dato ( float );

    void setCD2_Dato ( float );

    void setCD3_Dato ( float );

    void setAptSig ( NodoAS* );

    void RestablecerCalif (void);

    

    void Leer ( void );

    void Imprimir ( void );

    

    ~NodoAS ( void );

};
