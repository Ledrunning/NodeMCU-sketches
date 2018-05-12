#ifndef UNIT_TEST
#include <Arduino.h>
#endif
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

/* An IR detector/demodulator is connected to GPIO pin 14(D5 on a NodeMCU
/ board).
/ Code for NEC protocol, IR RC Eurosky
/ 202807F - 1
/ 20240BF - 2
/ 202C03F - 3
/ 20250AF - OFF
*/

#define FIRST_LED 12
#define SECOND_LED 13
#define RECV_PIN 14

IRrecv irrecv(RECV_PIN);
void translateIR();

decode_results results;

void setup() {
  Serial.begin(115200);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  irrecv.enableIRIn();  // Start the receiver
  while (!Serial)  // Wait for the serial connection to be establised.
    delay(50);
  Serial.println();
  Serial.print("IRrecvDemo is now running and waiting for IR message on Pin ");
  Serial.println(RECV_PIN);
}

void loop() {
  if (irrecv.decode(&results)) {
    // print() & println() can't handle printing long longs. (uint64_t)
    serialPrintUint64(results.value, HEX);
    Serial.println("");
    translateIR();
    irrecv.resume();  // Receive the next value
  }
  delay(100);
}

void translateIR() 
{

  switch(results.value)

  {

      case 0x202807F:  
        Serial.println(" 1            "); 
        digitalWrite(FIRST_LED, HIGH);
        digitalWrite(SECOND_LED, LOW);
        break;
    
      case 0x20240BF:  
        Serial.println(" 2             "); 
        digitalWrite(FIRST_LED, LOW);
        digitalWrite(SECOND_LED, HIGH);
        break;
    
      case 0x202C03F:  
        Serial.println(" 3            "); 
        // Do something...
        break;
        
      case 0x20250AF: 
        digitalWrite(FIRST_LED, LOW);
        digitalWrite(SECOND_LED, LOW);
        break;
  }
 }

