class Situacion_Academica
{
  private:
    string Estado;
    bool DictamenCOSIE;
    bool DictamenGeneral;
    int CargaMinima;
    int CargaMedia;
    int CargaMaxima;
  public:
    Situacion_Academica (void);
    Situacion_Academica (string , bool , bool , int , int , int );
    
    Situacion_Academica& operator= ( Situacion_Academica * );
    
    string getEstado (void);
    bool getDictamenCOSIE (void);
    bool getDictamenGeneral (void);
    int getCargaMinima (void);
    int getCargaMedia (void);
    int getCargaMaxima (void);
    
    void setEstado (string);
    void setDictamenCOSIE (bool);
    void setDictamenGeneral (bool);
    void setCargaMinima (int);
    void setCargaMedia (int);
    void setCargaMaxima (int);
    
    void AsigCarga (void);
    string ValidarDicCOSIE (void);
    string ValidarDicGen (void);
    
    void Leer (void);
    void Imprimir (void);
    
    ~Situacion_Academica (void);
};
