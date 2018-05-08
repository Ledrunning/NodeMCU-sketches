#include <ESP8266WiFi.h>
// defines pins numbers for HC SR04
#define TRIG_PIN 5  //D1
#define ECHO_PIN 4  //D2

const char* ssid = "YOUR SSID";
const char* password = "YOUR PASS";
 
// Web server with 80 port
WiFiServer server(80);

void setup()
{
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Try to connect using WiFi
  Serial.println();
  Serial.print("Connecting to ");  
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");  
             
  // Launch web-server
  server.begin();
  Serial.println("Web server running. Waiting for the ESP IP...");
              
  delay(10000);
 
  // печатаем IP-адрес ESP:
  Serial.println(WiFi.localIP());
}

void loop()
{ 

  // Clients listening
  WiFiClient client = server.available();

                          
  if (client) {
    Serial.println("New client");  
    // Flag for end of http request
    boolean blank_line = true;
    
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
       
        if (c == '\n' && blank_line) {

      
  // Clears the trigPin for 2 microseconds
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 microseconds
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  long duration = pulseIn(ECHO_PIN, HIGH);
  
  // Prints the duration on the Serial Monitor
  Serial.print("Duration (us): ");
  Serial.println(duration);
  
  // Calculating the distance ( distance = (duration/1.000.000)*(1/2) x (0.034 x 1000.000 cm/s) )
  float distance = duration*0.017;
  
  // Prints the distance on the Serial Monitor
  Serial.print("Distance (cm): ");
  Serial.println(distance,3);
  
  Serial.println();

  delay(1000);
           
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Connection: close");
            client.println();
            // Our web page
            client.println("<!DOCTYPE HTML>");
            client.println("<html>");
            client.println("<head></head><body><h1>Node MCU - Distance Meter</h1><h3>");
            client.println("</h3><h3>Distance: ");
            client.println(distance);
            client.println("</h3><h3>Duaration: ");
            client.println(duration);
            client.println("</body></html>");    
            break;
        }
        if (c == '\n') {
            blank_line = true;
        }
        else if (c != '\r') {
          blank_line = false;
        }
      }
    }  
    // Close connection
    delay(1);
    client.stop();
    Serial.println("Client disconnected.");
  }
}

