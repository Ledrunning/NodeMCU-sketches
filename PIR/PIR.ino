
#define STATUS 12
#define SENSOR 13

void setup() {
  pinMode(SENSOR, INPUT); // declare sensor as input
  pinMode(STATUS, OUTPUT);  // declare LED as output
}

void loop(){
  long state = digitalRead(SENSOR);
  delay(1000);
    if(state == HIGH){
      digitalWrite (STATUS, HIGH);
      Serial.println("Motion detected!");
    }
    else {
          digitalWrite (STATUS, LOW);
          Serial.println("Motion absent!");
      }
}
