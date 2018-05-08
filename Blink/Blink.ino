/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://www.arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pins as an output.
  pinMode(16, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(0, OUTPUT);
}

// the loop function runs over and over again forever
// turn the LED on (HIGH is the voltage level)
// wait for a 300 ms
void loop() {
  digitalWrite(16, LOW);   
  delay(300);              
  digitalWrite(16, HIGH);   
  delay(300);              
  digitalWrite(2, LOW);   
  delay(300);              
  digitalWrite(2, HIGH);  
  digitalWrite(14, LOW);   
  delay(300);              
  digitalWrite(14, HIGH);   
  delay(300);  
  digitalWrite(0, LOW);   
  delay(300);              
  digitalWrite(0, HIGH);    
  delay(300);        
  digitalWrite(4, LOW);   
  delay(300);              
  digitalWrite(4, HIGH);    
  delay(300);  
  delay(300);
           
}
