void SetDB(float att) {  
  
  int i;
  int iAttn0;
  int iAttn1;
  float Attn0;
  float Attn1;
  if (att>=31.5) {
      Attn0=31.5;
      Attn1=att-31.5;}
  else
  {
      Attn1=0;
      Attn0=att;
    }
 if (Attn0>int(Attn0)) {
    // this is a half
    iAttn0 = int(Attn0)*2+1;
  }
 else
  {
    iAttn0=int(Attn0)*2;
  }
 
 if (Attn1>int(Attn1)) {
    // this is a half
    iAttn1 = int(Attn1)*2+1;
  }
 else
  {
    iAttn1=int(Attn1)*2;
  }
 
 
 
 
 //rotate each register left - clocking bit 0 as 0
  
  ;
  Serial.print(att);
  Serial.println(" dB");
  lcd.setCursor(0,0);
  lcd.print("Attn ");
  lcd.print(att);
  lcd.print(" dB      ");
  
  for (i=5; i>=0; i--){
    //Serial.println(i);
    digitalWrite(dataPinA,bitRead(iAttn0,i));
    digitalWrite(dataPinB,bitRead(iAttn1,i));
    digitalWrite(clockPinA,HIGH);
    digitalWrite(clockPinB,HIGH);
    digitalWrite(clockPinA,LOW);
    digitalWrite(clockPinB,LOW); 
    }
    //
    //  Toggle latch pin high to load shift register
    //
    digitalWrite(latchPinA,HIGH);
    digitalWrite(latchPinB,HIGH);
    digitalWrite(latchPinA,LOW);
    digitalWrite(latchPinB,LOW);
    
}
  
