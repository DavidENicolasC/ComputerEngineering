class Periodo_Academico

{

  private:

    string Turno;

    string Periodo;

    float Promedio;

    float CreditosCursados;

    float CreditosTotales;

    float CreditosRestantes;

    LSE_AS UA;

    Situacion_Academica SA;

  public:

    Periodo_Academico (void);

    Periodo_Academico ( string, float , float , float , float , LSE_AS , Situacion_Academica );

    

    string getTurno (void);

    string getPeriodo (void);

    float getPromedio (void);

    float getCreditosCursados (void);

    float getCreditosTotales (void);

    float getCreditosRestantes (void);

    LSE_AS* getUA (void);

    Situacion_Academica* getSA (void);

    

    void setTurno (string);

    void setPeriodo (string);

    void setPromedio (float);

    void setCreditosCursados (float);

    void setCreditosTotales (float);

    void setCreditosRestantes (float);

    void setUA (LSE_AS*);

    void setSA (Situacion_Academica*);

    

    void CalcCreditos (void);

    void Leer (void);

    void Imprimir (void);

    

    Periodo_Academico& operator= ( Periodo_Academico * );

    

    ~Periodo_Academico (void);

};
