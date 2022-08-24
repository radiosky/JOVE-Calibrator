  //
  // 
  // Auto Step Calibrator
  // Original firmware by
  // RF Associates, LLC/JLB Consulting
  //
  // Modified for MK2 PC control
  // 3/2/2021
  // Radio-Sky Publishing
  // Added ability to set to a specific dB setting from serial port N+dB
  // Added ability to set the duration from serial port  
  // Added ability to cancel calibrations from serial port "C"
  //
  // Steps in dB
  // 2/12/2022
  // Fixed LCD feedback
  // returns FW version with v command.
  // 8/23/2022
  // Renamed JOVECal
  
  
#include <Wire.h>//   Comes with Arduino IDE
#include <LiquidCrystal_I2C.h>
String FWversion = "v 1.0.1";

// if you don't know the I2C addr of your LCD - load and run scanner.ino 

LiquidCrystal_I2C lcd(0x3F,20,4);  // set the LCD address to 0x3F for a 16 chars and 2 line display



  //  
  //        Initialize
  //
int relayA=5;     //  Antenna Relay
int relayB=6;     //  Antenna Relay
  //
int latchPinA=7;  //  Attenuator A
int clockPinA=8;  //  Attenuator A
int dataPinA=9;   //  Attenuator A
  //
  //
int latchPinB=10;  // Attenuator B
int clockPinB=11;  // Attenuator B  
int dataPinB=12;   // Attenuator B
  //
int ledRelays=13;   // LED to indicate relays energized
  //
int incomingByte;   // Keyboard input
  //
float pauseTime=5000;// Set the pause time between each attenuation step here   <------ Pause time setting
  //
  //
  //        VOID SETUP  
  //
  //
void setup(){
  //
  //
Serial.begin(19200);
  //
  lcd.init();  
  lcd.backlight();//To Power ON the back light
  //
  //        Set pinMode at startup
  //
  //
pinMode (relayA, OUTPUT);   //  Antenna relay
pinMode (relayB, OUTPUT);   //  Antenna relay
pinMode (ledRelays, OUTPUT);//  LED on to indicate relays energized
  //
  //
pinMode(clockPinA,OUTPUT);   // Attenuator A
pinMode(latchPinA,OUTPUT);   // Attenuator A
pinMode(dataPinA,OUTPUT);    // Attenuator A
  //
  //
pinMode(clockPinB,OUTPUT);   // Attenuator B
pinMode(latchPinB,OUTPUT);   // Attenuator B
pinMode(dataPinB,OUTPUT);    // Attenuator B
  //
  //  ------ Set pin states at startup --------
  //
digitalWrite(dataPinA,LOW);  // Attenuator A
digitalWrite(clockPinA,LOW); // Attenuator A
digitalWrite(latchPinA,LOW); // Attenuator A
  //
  //
digitalWrite(dataPinB,LOW);  // Attenuator B
digitalWrite(clockPinB,LOW); // Attenuator B
digitalWrite(latchPinB,LOW); // Attenuator B
  //
  lcd.clear();//Clean the screen
  lcd.setCursor(0,0);
  lcd.print("Noise Calibrator");
  lcd.setCursor(0,1);
  lcd.print("JOVECal: "+FWversion+"  ");
  
}
  //
  //        Void Loop  
  //
void loop(){
  //
      keyboardInput();
 
}


void solarStart(){
  //  

while (Serial.available()>0)
 { 
  incomingByte == Serial.read();
  Serial.println(char(incomingByte)); 
 }
 
relaysON();
float TimeSpent = 0;
int stepNum = 0;
int maxSteps = 14;
for (float u=42; u>=0; u=u-3)
  {
   // Serial.print("Attn ");
   // Serial.println(u);
    SetDB(u);
    ++stepNum;
    lcd.setCursor(0,1);
    lcd.print("Step ");
    lcd.print(stepNum);
    lcd.print(" of ");
    lcd.print(maxSteps);
    TimeSpent = 0;
    while (TimeSpent < pauseTime)
        { 

          //Serial.println(TimeSpent);
          delay(500);
          if (CheckForCancel() >0)
          {
            BypassCal();
            return;
          }
          TimeSpent = TimeSpent + 500;
        }
  }
    //  
    maxAtt(); //  Gives max attenuation 
   
   relaysOFF();
//
}

void maxAtt(){
//   Gives max attenuation at start of calibration run so there is a seperation
 SetDB(63);  //            between last cal output and beginning of real time data
  
}

void Noise()
{
  
 //  Energize relays and LED on Keystroke
  digitalWrite (ledRelays, HIGH);
  digitalWrite (relayA, HIGH);
  digitalWrite (relayB, HIGH);
  // Turn on the calibrator fixed to 0 dB attn
  // keep in a loop until a char is rcvd
  Serial.flush();
  SetDB(0);

while(Serial.available()==0){
  }

 BypassCal();


}


void BypassCal()
{
    //  Turn off relays & LED
  //
  //
digitalWrite (ledRelays, LOW);
digitalWrite (relayA, LOW);
digitalWrite (relayB, LOW);
}


int CheckForCancel(){
if (Serial.available() > 0)
{
 incomingByte = Serial.read();
 if (incomingByte == 'C'||incomingByte == 'c')
    {
        Serial.println ("Cancel");
        return 1;
    }  
  else
    {  
        return 0;
    }
    }
else
    {
    return 0;
    }
  }
 
void relaysON(){
    //
  //  Energize relays and LED on Keystroke
  //
  digitalWrite (ledRelays, HIGH);
  digitalWrite (relayA, HIGH);
  digitalWrite (relayB, HIGH);
  Serial.println("Relays ON ");
  lcd.setCursor(0,1);
  lcd.print("Relays ON       ");
}
void relaysOFF(){
    //
  //  Energize relays and LED on Keystroke
  //
  digitalWrite (ledRelays, LOW);
  digitalWrite (relayA, LOW);
  digitalWrite (relayB, LOW);
  Serial.println("Relays OFF");
  lcd.setCursor(0,1);
  lcd.print("Relays OFF      ");
}
