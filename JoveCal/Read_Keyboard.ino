  
  //
  //-------------------------- Read Keyboard/Serial Port  ----------------------------------
void keyboardInput(){

float Xin = 0;

if (Serial.available() > 0){
  //

while (!Serial.available());
incomingByte = Serial.read();

if (incomingByte == 'C'||incomingByte == 'c')
// Cancel the calibration
{
  Serial.println(char(incomingByte));
  //cancel any activity
  relaysOFF();
  maxAtt();
}

if (incomingByte == 'V'||incomingByte == 'v')
// return firmware version
{
  Serial.println(char(incomingByte));
  delay(100);
  Serial.println(FWversion);
 
}

if (incomingByte == 'N'||incomingByte == 'n')
// turn on the calibrator set to Xin dB
{
  Serial.println(char(incomingByte));
  delay(100);
  Xin = Serial.parseFloat();
  Serial.print("N = ");
  Serial.println(Xin);
  SetDB(Xin);
  relaysON();
  
}

if (incomingByte == 'P'||incomingByte == 'p')
// Set the step delay / receive in seconds, output ms
{
  //Serial.println(char(incomingByte));
  Xin = Serial.parseFloat();
  //Serial.println(Xin);
  if (Xin > 0) 
  {
    pauseTime=Xin*1000;
    Serial.print("Pause ms = ");
    Serial.println(pauseTime);
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("Step dur: ");
    lcd.print(pauseTime);
    lcd.print("ms");
  }
}

if (incomingByte == 'S'||incomingByte == 's')
{
  relaysON();
  //
  solarStart(); // Solar Calibration Sequence
}

while(Serial.available()>0){
  incomingByte=Serial.read();
  Serial.println(incomingByte);
}

}
}
