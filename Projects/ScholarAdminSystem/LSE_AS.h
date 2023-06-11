class LSE_AS

{

  private:

    NodoAS *Inicio;

  public:

    LSE_AS ( void );

    LSE_AS ( NodoAS * );

    LSE_AS ( LSE_AS * );

    

    NodoAS* getInicio( void );

    

    void Menu_LSE_Asignatura( void );

    

    void Insertar ( void );

    void InsertarInicio( NodoAS* );

    void InsertarDespues( NodoAS* );

    void InsertarFinal( NodoAS* );

    

    void Eliminar ( void );

    void EliminarInicio( void );

    void EliminarEspecifico( void );

    void EliminarFinal( void );

    

    void Imprimir ( void );

    

    NodoAS* Buscar ( void );

    

    void Editar ( void );

    void EditarInfo ( NodoAS* );

    void EditarCalif ( NodoAS* );

    

    float getPromFinal ( void );

    float getCreditosTotales ( void );

    

    LSE_AS& operator = ( LSE_AS * );

    

    ~LSE_AS ( void );

};
