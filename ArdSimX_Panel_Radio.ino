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
#include <LedControl.h>



//================================

    long com1_active = 0;
    long com1_standby = 0;

    LedControl display1 = LedControl(47, 48, 49, 2);   // (DIN_pin, CLK_pin, LOAD_pin, number_of_chips a utilizar )
//------------------------------------------
void setup()  {
    display1.shutdown(0, false);  // turns on display
    display1.shutdown(1, false);  // turns on display
    display1.setIntensity(0, 5); // 15 = brightest
    display1.setIntensity(1, 5); // 15 = brightest
    
    display1.setDigit(0,0,0, true); // module one
    display1.setDigit(0,1,1, true); // module one
    display1.setDigit(0,2,2, true); // module one
    display1.setDigit(0,3,3, true); // module one
    display1.setDigit(0,4,4, true); // module one
    display1.setDigit(0,5,5, true); // module one
    display1.setDigit(0,6,6, true); // module one
    display1.setDigit(0,7,7, true); // module one

    display1.setDigit(1,0,0, true); // module one
    display1.setDigit(1,1,1, true); // module one
    display1.setDigit(1,2,2, true); // module one
    display1.setDigit(1,3,3, true); // module one
    display1.setDigit(1,4,4, true); // module one
    display1.setDigit(1,5,5, true); // module one
    display1.setDigit(1,6,6, true); // module one
    display1.setDigit(1,7,7, true); // module one
   
}
//------------------------------- // main loop -----------
void loop()   {
 
     ArdSimX (1);         // -- Assign Board Number here  (1...9)
  
     // ====== DON't include here your code that executes in each loop!!!
   
}     

void display_com1(int modulo, long active, long standby)
{

     char buf_active[6];
     char buf_standby[6];
 
     ltoa(com1_active, buf_active, 10);

     display1.setChar(modulo,7,' ', false);
     display1.setChar(modulo,6,' ', false);
     display1.setChar(modulo,5,buf_active[0], false);
     display1.setChar(modulo,4,buf_active[1], false);
     display1.setChar(modulo,3,buf_active[2], true);
     display1.setChar(modulo,2,buf_active[3], false);
     display1.setChar(modulo,1,buf_active[4], false);
     display1.setChar(modulo,0,buf_active[5], false);

     ltoa(com1_standby, buf_standby, 10);

     display1.setChar(modulo+1,7,' ', false);
     display1.setChar(modulo+1,6,' ', false);
     display1.setChar(modulo+1,5,buf_standby[0], false);
     display1.setChar(modulo+1,4,buf_standby[1], false);
     display1.setChar(modulo+1,3,buf_standby[2], true);
     display1.setChar(modulo+1,2,buf_standby[3], false);
     display1.setChar(modulo+1,1,buf_standby[4], false);
     display1.setChar(modulo+1,0,buf_standby[5], false);
}
//===========================================
//---- Custom Outputs
void ProgOut(byte id, float val) {
    switch (id)  {
      case 1: com1_active = val;   break;
      case 2: com1_standby = val;  break;
  }

  display_com1(0, com1_active, com1_standby);

}

           
           
           // end program

/*
@ ================= INFO =================

Board #1 - Arduino (USB) -------------------------------------------------------

---- Digital pins: ----

4 - COM 1 flip standby.
6 - COM 1 kHz, 3 digits
8 - COM 1 Mhz

---- Programmable inputs: ----


---- Programmable outputs: ----


@ ================= CONFIG =================

*1-0U
[A]
[I]
E8- sim/radios/stby_com1_coarse_down
E8+ sim/radios/stby_com1_coarse_up
E6- sim/radios/stby_com1_fine_down_833
E6+ sim/radios/stby_com1_fine_up_833
D4+ sim/radios/com1_standy_flip
[O]
1D 0 sim/cockpit2/radios/actuators/com1_frequency_hz_833 1
2D 1 sim/cockpit2/radios/actuators/com1_standby_frequency_hz_833 1

*/
