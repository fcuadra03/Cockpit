/* V.1.0.
 * Libreria para conexion para recepcion de datos de Xplane. 
 * 
 * Para su uso es necesario incluir en el programa principal:
 * Include de libreria
 *    #include "Xplane.h"
 * La definicion del objeto:
 *    XPLANE xplane; 
 * Dentro de setup:
 *    Tras conexion de la placa a red:
 *      xplane.infoXplane(WiFi.localIP());
 *    Suscripcion a los dataref que se requieran:  
 *      xplane.suscribeDataRef(frecuencia,orden,dataref);
 *          frecuencia es el numero de veces por segundo que xplane devolvera el valor del dataref.
 *          orden es un numero que identifica el dataref y que xplan devolvera junto al valor del dataref.
 *          dateref cadena de texto con el dataref que se requiere
 * Dentro de loop:         
 *    xplane.readDataRef();
 * Creacion de nueva funcionque sera llamada automaticamente por cada dato recibido, el orden equivale al orden que se ha indicado anteriormente en la suscripcion.  
 *  void DataRefOut(int orden, float valor){
 *       switch (orden) {
 *         case 1: 
 *            .... 
 *            ....
 *            break;
 *         case 2: 
 *            .....
 *            .....
 *            break;
 *         case ....
 *         .....
 *         .....
 *       }
 *   }
 *   Autor Francisco Jose Cuadra Lopez.
 */



#include "Xplane.h"
  
IPAddress ipMulticast ( 239,255,1,1 );
const int portMulticast = 49707;
WiFiUDP _Udp;

//constructor
XPLANE::XPLANE() {
  
}

void XPLANE::infoXplane(IPAddress localIp) {
  bool infoOk = false;
  _Udp.beginMulticast(localIp, ipMulticast , portMulticast);
  while (!infoOk) {
    readData();
    memcpy (&_datosRecibidos, &_packetBuffer, _packetSize);

  //se comprueba si se ha recibido la informacion de Xplane
    if (strcmp(_datosRecibidos.comando,"BECN")==0) {
      infoOk = true;
      memcpy (&_dataBecn, &_packetBuffer, _packetSize);
      memcpy (&_infoXplane.beacon_major_version, &_dataBecn.beacon_major_version, 1);
      memcpy (&_infoXplane.beacon_minor_version, &_dataBecn.beacon_minor_version, 1);
      memcpy (&_infoXplane.application_host_id, &_dataBecn.application_host_id, 4);
      memcpy (&_infoXplane.version_number, &_dataBecn.version_number, 4);
      memcpy (&_infoXplane.role, &_dataBecn.role, 4);
      memcpy (&_infoXplane.port, &_dataBecn.port, 2);
      memcpy (&_infoXplane.computer_name, &_dataBecn.computer_name, 500);
      _infoXplane.Ip = _Udp.remoteIP();

      Serial.println(_infoXplane.beacon_major_version);
      Serial.println(_infoXplane.beacon_minor_version);
      Serial.println(_infoXplane.application_host_id);
      Serial.println(_infoXplane.version_number);
      Serial.println(_infoXplane.role);
      Serial.println(_infoXplane.port);
      Serial.println(_infoXplane.computer_name);
      Serial.println(_infoXplane.Ip);
    }
  }
  _Udp.stop();

}

void XPLANE::readDataRef() {
    bool infoOk = false;
    char tipo[4];
    unsigned int orden;
    float valor;
    int numDatos;

    _Udp.begin(_infoXplane.port);
    
    while (!infoOk) {
      readData();
      memcpy (&tipo, &_packetBuffer, 4);
      
//      if (strcmp(tipo,"RREF")==0) {
        numDatos = (_packetSize-5)/8;
        for (int x=0;x <numDatos;x++) {
          memcpy (&orden, &_packetBuffer[(x*8)+5], sizeof(unsigned int));
          memcpy (&valor, &_packetBuffer[(x*8)+9], sizeof(float));
          DataRefOut(orden, valor);
        }
        infoOk = true;
//      }      
    }
  _Udp.stop();
// _Udp.begin(58670);
}

//queda a la espera de recibir informacion por UDP.
void XPLANE::readData() {
    bool recibido = false;
    
    while (!recibido) {
      _packetSize = _Udp.parsePacket();
      if (_packetSize) {
        _Udp.read(_packetBuffer, _packetSize);
        recibido = true;
      }
      delay(10);
  }
}

void XPLANE::writeData() {
  int estado;
  estado = _Udp.beginPacket(_infoXplane.Ip, _infoXplane.port);
  estado = _Udp.write(_bufferEnvio, _longBuffer);
  estado = _Udp.endPacket();
}

void XPLANE::suscribeDataRef( int frecuencia,  int orden, String dataref) {

  _Udp.begin(_infoXplane.port);
  
  memset (_bufferEnvio, 0, sizeof(_bufferEnvio));
  memcpy (&_bufferEnvio, "RREF", 4);
  memcpy (&_bufferEnvio[5], &frecuencia, sizeof(int));
  memcpy (&_bufferEnvio[9], &orden, sizeof(int));
  for (int x = 0;x < dataref.length(); x++) {
    _bufferEnvio[13+x] = dataref[x];
  }
  _longBuffer = 413;

  writeData();
  _Udp.stop();
}


//String XPLANE::respuesta() {
//  return _datosRecibidos.comando;
//}

void XPLANE::logmensaje(char mensaje[]) {
  for (int x=0;x<100;x++) {
    Serial.print(mensaje[x], HEX);
    Serial.print(" ");
  }
  Serial.println();

  for (int x=0;x<100;x++) {
    Serial.print(mensaje[x]);
    Serial.print(" ");
  }
  Serial.println();  
}

void XPLANE::logmensaje(char mensaje[], int longBuffer) {
  for (int x=0;x<longBuffer;x++) {
    Serial.print(mensaje[x], HEX);
    Serial.print(" ");
  }
  Serial.println();

  for (int x=0;x<longBuffer;x++) {
    Serial.print(mensaje[x]);
    Serial.print(" ");
  }
  Serial.println();  
}



