#include <ESP8266WiFi.h>
#include "DHT.h"
 
// Choose your sensor
//#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

#define PORTD2 2
 
// Your data fo Wi Fi network
const char* ssid = "YOUR SSID";
const char* password = "YOUR PASS";
 
// Web - server with 80 port
WiFiServer server(80);
 
// DHT input to NodeMCU
const int DHTPin = 5;
// DHT init
DHT dht(DHTPin, DHTTYPE);
 
static char celsiusTemp[7];
static char fahrenheitTemp[7];
static char humidityTemp[7];
 
// Initialization
void setup() {

  pinMode(PORTD2, OUTPUT);
  
  // Serial Port for debug:
  Serial.begin(115200);
  delay(10);
  
  dht.begin();
 
  // connecting to WiFi
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
 
  // print IP-address ESP on serial terminal
  Serial.println(WiFi.localIP());
}
 
// main 
void loop() {
  // Clients listening
  WiFiClient client = server.available();

  // Just blink
  digitalWrite(PORTD2, HIGH);   
  delay(300);                       
  digitalWrite(PORTD2, LOW);    
  delay(300); 
                        
  if (client) {
    Serial.println("New client"); 
     
    // End of HTTP request flag
    boolean blank_line = true;
    
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
       
        if (c == '\n' && blank_line) {
            
            float h = dht.readHumidity();
            // Read temp in celsius (default)
            float t = dht.readTemperature();
            // Read temp in fahrenheit
            // (isFahrenheit = true):
            float f = dht.readTemperature(true);
            // Check read data,
            if (isnan(h) || isnan(t) || isnan(f)) {
              Serial.println("Failed to read from DHT sensor!");
              strcpy(celsiusTemp,"Failed");
              strcpy(fahrenheitTemp, "Failed");
              strcpy(humidityTemp, "Failed");        
            }
            else{
           
              float hic = dht.computeHeatIndex(t, h, false);      
              dtostrf(hic, 6, 2, celsiusTemp);            
              float hif = dht.computeHeatIndex(f, h);
              dtostrf(hif, 6, 2, fahrenheitTemp);        
              dtostrf(h, 6, 2, humidityTemp);
 
              // Debug region (printing data on USART)
              Serial.print("Humidity: ");  
              Serial.print(h);
              Serial.print(" %\t Temperature: ");  
              Serial.print(t);
              Serial.print(" *C ");
              Serial.print(f);
              Serial.print(" *F\t Heat index: ");
              Serial.print(hic);
              Serial.print(" *C ");
              Serial.print(hif);
              Serial.print(" *F");
              Serial.print("Humidity: ");  
              Serial.print(h);
              Serial.print(" %\t Temperature: ");  
              Serial.print(t);
              Serial.print(" *C ");
              Serial.print(f);
              Serial.print(" *F\t Heat index: ");
              Serial.print(hic);
              Serial.print(" *C ");
              Serial.print(hif);
              Serial.println(" *F");
            }
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Connection: close");
            client.println();
            // Our hardcoded web page
            client.println("<!DOCTYPE HTML>");
            client.println("<html>");
            client.println("<head></head><body><h1>ESP8266 - Temperature and Humidity</h1><h3>Temperature in Celsius: ");
            client.println(celsiusTemp);
            client.println("*C</h3><h3>Temperature in Fahrenheit: ");
            client.println(fahrenheitTemp);
            client.println("*F</h3><h3>Humidity: ");
            client.println(humidityTemp);
            client.println("%</h3><h3>");
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
    // Close conection
    delay(1);
    client.stop();
    Serial.println("Client disconnected.");
               
  }
}
