class LSE_PA

{

  private:

    NodoPA *Inicio;

  public:

    LSE_PA ( void );

    LSE_PA ( NodoPA * );

    LSE_PA ( LSE_PA * );

    

    NodoPA *getInicio(void);

    

    void Insertar ( void );

    void InsertarInicio( NodoPA* );

    void InsertarDespues( NodoPA* );

    void InsertarFinal( NodoPA* );

    

    void Eliminar ( void );

    void EliminarInicio( void );

    void EliminarEspecifico( void );

    void EliminarFinal( void );

    

    void Imprimir ( void );

    NodoPA * Buscar ( void );

    void Editar ( void );

    

    void Menu_LSE_PeriodoA (void);

    

    LSE_PA& operator = ( LSE_PA* );

    

    ~LSE_PA ( void );

};
