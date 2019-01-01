/* V.1.0.
 * Libreria para conexion para recepcion de datos de Xplane. 
 * Fichero cabecera.
 * 
 *   Autor Francisco Jose Cuadra Lopez.
 */


#ifndef xplane_h
#define xplane_h

#include "Arduino.h"
#include <WiFiUdp.h>
extern void DataRefOut(int orden, float valor); 

class XPLANE {
  public:
    XPLANE(); //constructor
    void infoXplane(IPAddress localIp); //obtiene informacion de Xplane
    void suscribeDataRef( int frecuencia,  int ordern, String dataRef); //funcion para susbir la peticion de un data_ref
    void readDataRef(); //lee dataref devueltos por xplane
//    String respuesta(void);

  
  private:
    void readData(void); //lee datos de xplane
    void writeData(void); //manda datos a xplane
    void logmensaje(char[]);
    void logmensaje(char[], int);
    
    char _packetBuffer[500]; //buffer donde se obtiene la informacion recibida de Xplane
    int _packetSize; // tamanio del mensaje recibido
//    float _dataRefOrden;
//    float _dataRefValor;
    char _bufferEnvio[413]; //buffer de envio a Xplane
    int _longBuffer;
    
    

    struct DATA {
      char comando[4];
      char nulo;
      char data[495];
    };

    struct DATABECN {
      char comando[4];
      char nulo;
      char beacon_major_version[1];
      char beacon_minor_version[1];
      char application_host_id[4];
      char version_number[4];
      char role[4];
      char port[2];
      char computer_name[500];
    };

    struct INFOXPLANE {
      unsigned int beacon_major_version;
      unsigned int beacon_minor_version;
      unsigned int application_host_id;
      unsigned int version_number;
      unsigned int role;
      unsigned int port;
      char computer_name[500];
      IPAddress Ip;
    };

    struct SUSCRIBE {
      char comando[4];
      char nulo;
      char frecuencia[4];
      char orden[4];
      String dref;
    };

    struct DATAREF {
      char comando[4];
      char orden[4];
      char valor[4]; 
      char fill;
    };

    DATA _datosRecibidos;
//    char _datosEnviados[500];
    DATABECN _dataBecn;
    INFOXPLANE _infoXplane;
//    SUSCRIBE _suscribe;
//    DATAREF _datosDataRef;
    
union {
    float fval;
    byte bval[4];
} floatAsBytes;



    
};

#endif
