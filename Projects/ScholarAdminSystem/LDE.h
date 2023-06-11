class LDE 

{

  private:

    NodoAL *Inicio;

    NodoAL *Final;

  public:

    LDE ( void );

    LDE ( NodoAL * , NodoAL *);

    LDE ( LDE * );

    

    NodoAL *getInicio( void );

    NodoAL *getFinal( void );

    

    LDE& operator = ( LDE * );

    

    void InsertarInicio ( NodoAL* );

    void InsertarFinal ( NodoAL* );

    void InsertarAntes( NodoAL* );

    void InsertarDespues ( NodoAL* );

    void Insertar ( void );

    

    void EliminarInicio ( void );

    void EliminarFinal ( void );

    void EliminarEspecifico ( void );

    void Eliminar ( void );

    

    void Imprimir ( void );

    NodoAL * Buscar ( void );

    void Editar ( void );

    

    void Menu_LDE_Alumno ( void );

    

    ~LDE ( void );

};
