
/*
----------------------------------------------------- 
DESCRIPTION
   Mearkat.co Keypad Test Software
Date: 
   12/23/2020
Version: 
   1.0
Documentation:
   * Hardware:
   *    red   = 3.3v 
   *    black = gnd
   *    green = SCL (serial clock)
   *    white = SDA (serial data)
   * Find wiring diagram at _____________
   * View test results in serial Monitor
   *    Arduino IDE -> Tools -> Serial Monitor (Baud 9600)
   *    or press Ctrl+Shift+M
Warrantee: 
   Software is distributed as-is without warrantee.
Licensing: 
   This softare is thank-you-ware. If you meet the creator, 
   say 'Hey!  Thank you!' or some other friendly variation. :)
----------------------------------------------------- 
*/


//----------------------------------------------------- 
//INCLUDES
#include <Wire.h>                                                       //include I2C library (required)
#include <SparkFunSX1509.h>                                             //include SparkFunSX1509 library (required)
                                                                        //  https://github.com/sparkfun/SparkFun_SX1509_Arduino_Library
SX1509 io;                                                              //create an SX1509 (keypad chip) io object


//----------------------------------------------------- 
//GLOBAL VARIALBES

 
//----------------------------------------------------- 
//SETUP  //run once
void setup()
{
  Serial.begin(9600);
  
  if (!io.begin(0x3E))                                                  //look for SX1509 at this address
  {
    Serial.print("ERROR: Keypad NOT detected. Program stopped.\n\n");   //on failure to connect print error.
    while (1);                                                          //loop forever.
  } //if

  for (int sxInit=0;sxInit<16;sxInit++) {                               //initialize keypad (required)
    io.pinMode(sxInit, INPUT_PULLUP);
  } //for
} //setup


//----------------------------------------------------- 
//MAIN LOOP

void loop()                                                              //run repeatedly
{
  bool keypadPressed = HIGH;                                               //used for debounce
  int buttonPressed = -1;

  Serial.print("\n\n");
  Serial.print("----------------------------------------\n");
  Serial.print("  Test Menu Program  \n");
  Serial.print("\n");
  Serial.print("  [1] secret message\n");
  Serial.print("  [2] my favorite emoji\n");
  Serial.print("  [3] a message from Mearkat.co\n");
  Serial.print("  Select choice [ ]  \n\n");


  do {
   
    for (int sxButton=0;sxButton<16;sxButton++) {                          //read from each possible button location
                                                                           //Note: A 12 button keypad (for example a 3x4 configuration) 
                                                                           //        will have buttons press numbers ranging from 1 to 12.
                                                                           //      A 16 button keypad (for example a 4x4 configuration)
                                                                           //        will have button press numbers ranging from 1 to 15 with
                                                                           //        0 representing the press of the 16th (last) key.
      keypadPressed = io.digitalRead(sxButton);                            //read the status of each button manually
    
      if ( keypadPressed==LOW ) {                                          //read current button and test for LOW which equals PRESSED
        Serial.print("Button "+String(sxButton)+" Pressed\n");             
        buttonPressed = sxButton;
        do {                                                               //debounce (wait for key to be lifted)
          keypadPressed = io.digitalRead(sxButton);
        } while (keypadPressed == LOW);                                    //wait for button to be lifted to continue loop
                                                                         //Note: Can't use io.digitalRead directly in while condition loop :(
      }  //if
    } //for
  } while (buttonPressed == -1);

  if (buttonPressed == 1) { 
    Serial.print("SECRET MESSAGE: There is always money in the bananna stand.\n\n");
  }
  if (buttonPressed == 2) { 
    Serial.print("My favorite emoji has a lil' hair flip \":^) \n\n");
  }
  if (buttonPressed == 3) { 
    Serial.print("Thank you!\n");
    Serial.print("It was crazy fun creating this product for you.\n");
    Serial.print("I appreciate your business.\n\n");
  } 
  if ((buttonPressed > 3) || (buttonPressed = 0)) { 
    Serial.print("Instructions!  We don't need no stinking instructions.\n");
  } 

} //loop
