
/*
----------------------------------------------------- 
DESCRIPTION
   MeerkatDesign.co Keypad Test Software
Date Version: 
   11/27/2022
Documentation:
   * Hardware:
        red   = 3.3v 
        black = gnd
        green = SCL (serial clock)
        white = SDA (serial data)
   * Find wiring diagram for an Arduino Uno at 
        https://github.com/TopherCoder/ArduinoKeypad/blob/main/WireDiagram.Small.jpg
   * View this program's results in serial monitor
        Arduino IDE -> Tools -> Serial Monitor 
        Make sure Serial Monitor settigs (lower right of the app) is set so new line on "Both NL & CR", 
        and Baud "9600")
Warrantee: 
   Software is distributed as-is without warrantee.
Licensing: 
   This softare is open source "thank-you-ware". 
   If you meet the creator in person, say 'Hey!  Thank you!' or some other variation.
----------------------------------------------------- 
*/


//----------------------------------------------------- 
//INCLUDES
#include <Wire.h>                                                       //include I2C library (required !!)
#include <SparkFunSX1509.h>                                             //include SparkFunSX1509 library (required !!)
                                                                        //  https://github.com/sparkfun/SparkFun_SX1509_Arduino_Library
SX1509 io;                                                              //create an SX1509 object called 'io'
                                                                        //   The SX1509 chipset is the heart of the keypad technology. 

//----------------------------------------------------- 
//GLOBAL VARIALBES

//none

 
//----------------------------------------------------- 
// void setup = run once
void setup()
{
  Serial.begin(9600);                                                   //I recommend a default baud rate of 115200 (instead of 9600) between my computer and any Arduino board.
                                                                        //  This makes for very peppy serial monitor experience. 
                                                                        //If serial monitor is displaying garbage 
                                                                        //  1. make sure the baud rate (lower right) is set to the baud rate in Serial.begin() command.
                                                                        //  2. make sure new line & carriage return (lower right) is set to "Both NL & CR" 
  
  if (!io.begin(0x3E))                                                  //Look for SX1509 at this I2C address (default).
  {
    Serial.print("ERROR: Keypad NOT detected. Program stopped.\n\n");   //On failure to connect print error
    while (1);                                                          //  loop forever.   
                                                                        //WARNING: With this code example, after you connect your keypad, you will need to 
                                                                        //  REBOOT your Arduino to get out of this wait state.  This can be done by simply 
                                                                        //  pressing the reboot button on your Arduino.
  } //if

  for (int sxInit=0;sxInit<=15;sxInit++) {                              //Initialize individual keypad keys (required)  /!\ Always loop 0 to <=15 even if your product has less buttons.
    io.pinMode(sxInit, INPUT_PULLUP);
  } //for
} //setup


//----------------------------------------------------- 
// void loop = main code to loop forever 
void loop()                                                              //Run repeatedly
{
  bool keypadPressed = HIGH;                                             //Measure state change
  int buttonPressed = -1;                                                //Numerical value of the button pressed.  
                                                                         //Note: In most products, the first button (top left) has a value of 1, not 0
                                                                         //  For example, a 3 x 4 (12 key) keypad has buttonPressed values of 1 to 12 not 0 to 11.

  Serial.print("\n");
  Serial.print("\n");
  Serial.print("--MeerkatDesign.co--------------------------------------\n");
  Serial.print("Keypad Basic Test Software v3 \n");
  Serial.print("--------------------------------------------------------\n");
  Serial.print("\n");
  Serial.print("\n");
  Serial.print("\n");
  Serial.print("\n");
  Serial.print("Press keys on keypad.\n");
  Serial.print("Their values should be printed below when you RELEASE the key.\n");
  Serial.print("\n");


  do {
   
    for (int sxButton=0;sxButton<=15;sxButton++) {                         //Read from each possible button location SX1509 port 0 - 15
                                                                           //Note: A 12 button keypad (for example a 3x4 configuration) 
                                                                           //        will have buttons press numbers ranging from 1 to 12.
                                                                           //      A 16 button keypad (for example a 4x4 configuration)
                                                                           //        will have button press numbers ranging from 1 to 15 with
                                                                           //        0 representing the press of the 16th (last) key.
      keypadPressed = io.digitalRead(sxButton);                            //Read the status of the current button in this loop 
    
      if ( keypadPressed==LOW ) {                                          //If that button has a condition of LOW that means the key is currently PRESSED!
        buttonPressed = sxButton;                                          //Set variable buttonPressed to the number of the key that was pressed (again, generally starting with 1)
        Serial.print("[" + String(buttonPressed) + "]");
        int counter = 1; 
        do {                                                               //Wait for key to be lifted.
          keypadPressed = io.digitalRead(sxButton);
          if (counter > 20) {
            Serial.print(".");
            counter = 0; 
          }
          counter = counter +1;
        } while (keypadPressed == LOW);                                    //If button still LOW (pressed) loop again. 
                                                                           //WARNING: If you're trying to improve this piece of code, 
                                                                           //  for some reason you can't use the io.digitalRead function directly in a while condition loop :(
      } //if
    } //for

  if ( buttonPressed != -1 ) {
     Serial.print("[" + String(buttonPressed) + "]\n");
     buttonPressed = -1;
  }  //if 
  
  } while (true);                                                         //loop again 


} //loop
