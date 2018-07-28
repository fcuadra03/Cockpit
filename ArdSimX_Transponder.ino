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

    int frec_transponder = 0;
    int modo = 0; // 0 off 1 stb 2 on 4 test 5 gnd 3 alt
    

    LedControl display1 = LedControl(33, 34, 35, 1);   // (DIN_pin, CLK_pin, LOAD_pin, number_of_chips a utilizar )
//------------------------------------------
void setup()  {
    display1.shutdown(0, false);  // turns on display
    display1.setIntensity(0, 5); // 15 = brightest
    
    display1.setDigit(0,0,0, true); // module one
    display1.setDigit(0,1,1, true); // module one
    display1.setDigit(0,2,2, true); // module one
    display1.setDigit(0,3,3, true); // module one
    display1.setDigit(0,4,4, true); // module one
    display1.setDigit(0,5,5, true); // module one
    display1.setDigit(0,6,6, true); // module one
    display1.setDigit(0,7,7, true); // module one

   
}
//------------------------------- // main loop -----------
void loop()   {
 
     ArdSimX (1);         // -- Assign Board Number here  (1...9)
  
     // ====== DON't include here your code that executes in each loop!!!
   
}     

void display_limpia(int modulo){
  for (int x = 0;x<8;x++){
    display1.setChar(modulo, x, ' ', false);
  }
}

void display_transponder(int modulo, int frecuencia, int modo)
{
     String txt_modo = "";
     switch (modo)
     {
      case 0: txt_modo = "   ";
      break;
      case 1: txt_modo = "Stb";
      break;
      case 2: txt_modo = "On ";
      break;
      case 3: txt_modo = "ALt";
      break;
      case 4: txt_modo = "tES";
      break;
      case 5: txt_modo = "Gnd";
      break;
     }
     char buf_frecuencia[4];
 
//     ltoa(frecuencia, buf_frecuencia, 10);
     sprintf (buf_frecuencia,"%04d",frecuencia);

     if (modo == 0)
     {
          display_limpia(modulo);
     } else {

          display1.setChar(modulo,7,txt_modo[0], false);
          display1.setChar(modulo,6,txt_modo[1], false);
          display1.setChar(modulo,5,txt_modo[2], false);
          display1.setChar(modulo,4,' ', false);
          display1.setChar(modulo,3,buf_frecuencia[0], false);
          display1.setChar(modulo,2,buf_frecuencia[1], false);
          display1.setChar(modulo,1,buf_frecuencia[2], false);
          display1.setChar(modulo,0,buf_frecuencia[3], false);
      
     }

}
//===========================================
//---- Custom Outputs
void ProgOut(byte id, float val) {
    switch (id)  {
      case 1: frec_transponder = val;   break;
      case 2: modo = val; break;
  }

  display_transponder(0, frec_transponder, modo);

}

           
           
           // end program

/*
@ ================= INFO =================

Board #1 - Arduino (LAN) -------------------------------------------------------

---- Digital pins: ----

6 - Transponder digits 3 and 4 +/-.
8 - Transponder digits 1 and 2 +/-
43 - Transponder active â€“ ID light is On
44 - Transponder ALT
45 - Transponder GND
46 - Transponder TEST
47 - Transponder ON
48 - Transponder STBY
49 - Transponder OFF

---- Programmable outputs: ----

1 - Current Transponder code (0000-7777)



@ ================= CONFIG =================

*1-0L
[A]
[I]
D49+ sim/transponder/transponder_off
D48+ sim/transponder/transponder_standby
D47+ sim/transponder/transponder_on
D46+ sim/transponder/transponder_test
D45+ sim/transponder/transponder_ground
D44+ sim/transponder/transponder_alt
E8- sim/transponder/transponder_12_down
E8+ sim/transponder/transponder_12_up
E6- sim/transponder/transponder_34_down
E6+ sim/transponder/transponder_34_up
[O]
43L 0 sim/cockpit/radios/transponder_light 1
1D 0 sim/cockpit2/radios/actuators/transponder_code 1
2D 0 sim/cockpit/radios/transponder_mode 1 
*/
