
/*
----------------------------------------------------- 
DESCRIPTION
   Mearkat.co Keypad Test Software
Date Version: 
   2/4/2021 v2
Documentation:
   * Hardware:
        red   = 3.3v 
        black = gnd
        green = SCL (serial clock)
        white = SDA (serial data)
   * Find wiring diagram for an Arduino Uno at 
        https://github.com/TopherCoder/ArduinoKeypad/blob/main/WireDiagram.Small.jpg
   * View this program's results in serial monitor
        Arduino IDE -> Tools -> Serial Monitor (New line on "Both NL & CR", Baud "115200")
Warrantee: 
   Software is distributed as-is without warrantee.
Licensing: 
   This softare is open source thank-you-ware. 
   If you meet the creator, say 'Hey!  Thank you!' or some other friendly variation.
----------------------------------------------------- 
*/


//----------------------------------------------------- 
//INCLUDES
#include <Wire.h>                                                       //include I2C library (required)
#include <SparkFunSX1509.h>                                             //include SparkFunSX1509 library (required)
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
  Serial.begin(115200);                                                 //Changing baud rate of your serial interface does not change the rate at which the keypad is read per-se. 
                                                                        //If serial monitor is displaying garbage 
                                                                        //  make sure lower right of serial-monitor software dropdown displays "Both NL & CR" 
                                                                        //  and you can experiment with a slower BAUD rate by replaceing 115200 in this line of code with 9600.
                                                                        //  Then re upload to your Arduino.  And make sure serial-monitor is also set to 9600 in lower right. 
  
  if (!io.begin(0x3E))                                                  //Look for SX1509 at this I2C address (default).
  {
    Serial.print("ERROR: Keypad NOT detected. Program stopped.\n\n");   //on failure to connect print error.
    while (1);                                                          //loop forever.   
                                                                        //NOTE: With this code example, after you connect your keypad, you will need to 
                                                                        //  REBOOT your Arduino to get out of this wait state.  This can be done by simply 
                                                                        //  pressing the reboot button on your Arduino.
  } //if

  for (int sxInit=0;sxInit<=15;sxInit++) {                              //initialize individual keypad keys (required)  /!\ Always loop 0 to <=15 even if your product has less buttons.
    io.pinMode(sxInit, INPUT_PULLUP);
  } //for
} //setup


//----------------------------------------------------- 
// void loop = main code to loop forever 
void loop()                                                              //run repeatedly
{
  bool keypadPressed = HIGH;                                             //used to measure state change
  int buttonPressed = -1;                                                //numerical value of the button pressed.  
                                                                         //Note: In most products, the first button (top left) has a value of 1, not 0
                                                                         //  For example, a 3 x 4 (12 key) keypad has buttonPressed values of 1 to 12 not 0 to 11.

  Serial.print("\n\n");
  Serial.print("--mearkat.co--------------------------------------\n");
  Serial.print("  Keypad Test - Example Menu Program  \n");
  Serial.print("\n");
  Serial.print("  [1] secret message\n");
  Serial.print("  [2] my favorite emoticon\n");
  Serial.print("  [3] a message from Mearkat.co\n");
  Serial.print("  Select button of your choice [ ]  \n\n");

  do {
   
    for (int sxButton=0;sxButton<=15;sxButton++) {                         //read from each possible button location SX1509 port 0 - 15
                                                                           //Note: A 12 button keypad (for example a 3x4 configuration) 
                                                                           //        will have buttons press numbers ranging from 1 to 12.
                                                                           //      A 16 button keypad (for example a 4x4 configuration)
                                                                           //        will have button press numbers ranging from 1 to 15 with
                                                                           //        0 representing the press of the 16th (last) key.
      keypadPressed = io.digitalRead(sxButton);                            //read the status of the current button in this loop 
    
      if ( keypadPressed==LOW ) {                                          //if that button has a condition of LOW that means the key is currently PRESSED!
        Serial.print("Button "+String(sxButton)+" Pressed\n");             //print result to serial monitor
        buttonPressed = sxButton;                                          //set variable buttonPressed to the number of the key that was pressed (again, generally starting with 1)
        do {                                                               //wait for key to be lifted
          keypadPressed = io.digitalRead(sxButton);
        } while (keypadPressed == LOW);                                    //if button still LOW (pressed) loop again. 
                                                                           //Note: If you're trying to improve this piece of code, 
                                                                           //  for some reason you can't use the io.digitalRead function directly in a while condition loop :(
      }  //if
    } //for
  } while (buttonPressed == -1);                                           //if no button was pressed, loop again

  Serial.print("--------------------------------------------------\n\n\n");
  if (buttonPressed == 1) {                                                //if button 1 was pressed...
    Serial.print("SECRET MESSAGE: There is always money in the bananna stand.\n\n\n\n");
  }
  if (buttonPressed == 2) { 
    Serial.print("EMOTICON: My favorite emoticon has a hair flip and a tie!  \":^)~ \n\n\n\n");
  }
  if (buttonPressed == 3) { 
    Serial.print("MEARKAT.CO:  Thank you!\n");
    Serial.print("             It was crazy fun creating this product for you.\n");
    Serial.print("             Now let's create something amazing!\n");
  } 
  if ((buttonPressed > 3) || (buttonPressed = 0)) { 
    Serial.print("XXXXXXX:  Instructions!? ...We don't need no stinking instructions.\n\n\n\n");
  } 

} //loop
