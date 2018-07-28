/*
Base code for ArdSimX Library  v1.20+
/
The latest version and manuals at http://www.simvim.com
Copyright © SimVim 20012-2018
/
Previous projects: XPData (UDP), ARDref, ArdSim Interfaces.
/
The newest interface is  ASX2 (ArdSimX.2) project,
see details, plans and development status at https://ardsimx.blogspot.com
/
*/
#include <ArdSimX.h>
//#include <Ethernet.h>     // !!! comment or delete this line if USB connection is used
#include <LiquidCrystal_I2C.h>



//================================

    LiquidCrystal_I2C lcd(0x27, 20, 4);

    const int int_pin = 22;

    float in_hg = 0.0;
    int modo = 0; // 0 inhg 1 hpa

    
//------------------------------------------
void setup()  {


   lcd.begin();                      
   lcd.backlight();
   lcd.setCursor(0, 0);
   lcd.print("Prueba QNH");
   lcd.setCursor(0, 1);
   lcd.print("Por Paco Cuadra");
   delay(1000);
   lcd.clear();
   
   pinMode(int_pin, INPUT_PULLUP);
  
  
}
void display_qnh(int modulo, float inhg, int modo_sw)
{

    int hpa = round(inhg * 33.863886666667);
    char hpa_formato[4];
    sprintf(hpa_formato,"%04d",hpa);


          lcd.setCursor(0,0);
          if (modo_sw == 0) {
            lcd.print("InHg: ");
            lcd.print(inhg);
          } else {
            lcd.print("HPA:   ");
            lcd.print(hpa_formato);
          }


}
void cambia_modo() {
  modo = !modo;
  display_qnh(0, in_hg, modo);
}

//------------------------------- // main loop -----------
void loop()   {
 
     ArdSimX (1);         // -- Assign Board Number here  (1...9)
     bool pulsado = false;

     // ====== DON't include here your code that executes in each loop!!!
     
     while (digitalRead(int_pin) == LOW) {
      pulsado = true;
     }
     if (pulsado) {
      modo = !modo;
      display_qnh(0, in_hg, modo);
      delay(300);
     }
  

}     


//===========================================
//---- Custom Outputs
void ProgOut(byte id, float val) {
    switch (id)  {
       case 1: in_hg = val; break;
  }

  display_qnh(0, in_hg, modo);

}

           
           
           // end program

/*
@ ================= INFO =================

Board #1 - Arduino (USB) -------------------------------------------------------

---- Digital pins: ----



---- Programmable inputs: ----


---- Programmable outputs: ----

1 - Barometric pressure, Pilot
2 - dataref_1



@ ================= CONFIG =================

*1-0U
[A]
[I]
[O]
1D 2 sim/cockpit2/gauges/actuators/barometer_setting_in_hg_pilot 1

*/
