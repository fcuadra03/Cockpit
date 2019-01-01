/*
Codigo de ejemplo para el uso de libreria xplane a traves de wifi con la placa ESP8266.
Para configurar wifi hay que indicar el identificador y pass en STASSID y STAPSK respectivamente.
*/
// powershell get-content log.txt -wait

#include <ESP8266WiFi.h>

//Necesario para conectar con xplane
#include "Xplane.h"

#ifndef STASSID
#define STASSID "identificador wifi" //poner aqui el ssid del wifi
#define STAPSK  "pass wifi" //poner aqui la pass del wifi
#endif

const char* ssid     = STASSID;
const char* password = STAPSK;

//Necesario para conectar con xplane
XPLANE xplane;

void setup() {
  Serial.begin(9600);

  Serial.println();
  Serial.println();
  Serial.print("Connectando wifi");


  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

//Necesario para conectar con xplane  
  xplane.infoXplane(WiFi.localIP());


//Necesario para conectar con xplane
//Crear una linea por cada dataref que se quiere recibir, (frecuencia -veces por segundo-, orden, dataref)
//si se indica frecuencia 0, entondes xplane deja de enviar ese data ref.
//si alguna suscripcion devuelve siempre valor 0, es posible que no se haya especificado bien el dataref, es sensible a las mayusculas.
  xplane.suscribeDataRef(1,1,"sim/cockpit2/clock_timer/zulu_time_seconds");
  xplane.suscribeDataRef(1,2,"sim/cockpit2/clock_timer/zulu_time_minutes");
  xplane.suscribeDataRef(1,3,"sim/cockpit2/radios/actuators/com1_standby_frequency_hz_833");
  xplane.suscribeDataRef(4,4,"sim/cockpit2/gauges/indicators/airspeed_kts_pilot");
  xplane.suscribeDataRef(4,5,"sim/cockpit2/gauges/indicators/compass_heading_deg_mag");

  
}

void loop() {
  //Necesario para conectar con xplane
  xplane.readDataRef();

}

//Funcion que sera llamada automaticamente por cada dato recibido, el orden equivale al orden que se ha indicado anteriormente en la suscripcion.  
void DataRefOut(int orden, float valor){
     String titulo;
        switch (orden) {
          case 1: titulo = "Segundos zulu: ";
             break;
          case 2: titulo = "Minutos zulu: ";
             break;
          case 3: titulo = "Com1 stby: ";
             break;
          case 4: titulo = "Velociad: ";
             break;
          case 5: titulo = "Heading: ";
             break;
        }
        Serial.print(titulo);
        Serial.println(valor);
}

