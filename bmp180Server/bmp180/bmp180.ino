#include <Adafruit_Sensor.h>
#include <ESP8266WiFi.h>
#include <Adafruit_BMP085.h> // This is the version 1 library
#include <STRING.h>
#include <Wire.h>

#define ledPin 2 
Adafruit_BMP085 bmp;
 
const char* ssid = "YOUR SSID";
const char* password = "YOURPASS";
 
// int ledPin = 2; // GPIO2
WiFiServer server(80);
 
char test[20];
 
 void setup() {
    Serial.begin(115200);
    delay(10);
     
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);
     
    // Connect to WiFi network
    Serial.println();
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
   
      // Start the server
      server.begin();
      Serial.println("Server started");
       
      // Print the IP address
      Serial.print("Use this URL to connect: ");
      Serial.print("http://");
      Serial.print(WiFi.localIP());
      Serial.println("/");
      if (!bmp.begin()) {
      Serial.println("Could not find a valid BMP085 sensor, check wiring!");
          while (1) {}
        }
  }
 
void loop() {
 
        // Check if a client has connected
        WiFiClient client = server.available();
        if (!client) {
        return;
        }
         
        // Wait until the client sends some data
        Serial.println("new client");
        while(!client.available()){
        delay(1);
        }
         
        // Read the first line of the request
        String request = client.readStringUntil('\r');
        Serial.println(request);
        client.flush();
         
        // Match the request
         
        int value = LOW;
        if (request.indexOf("/LED=ON") != -1) {
        digitalWrite(ledPin, HIGH);
        value = HIGH;
        }
        if (request.indexOf("/LED=OFF") != -1) {
        digitalWrite(ledPin, LOW);
        value = LOW;
        }
         
        // Set ledPin according to the request
        //digitalWrite(ledPin, value);
         
        // Return the response
         
        long Pressure = bmp.readPressure();
        long Temperature = bmp.readTemperature();
         
        Serial.print("Temperature = ");
        Serial.print(Temperature);
        Serial.println(" *C");
        Serial.print("Pressure = ");
        Serial.print(Pressure / 133.3);
        Serial.println(" *C");
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/html");
        client.println(""); // do not forget this one
        client.println("<!DOCTYPE HTML>");
        client.println("<html><head><title>Led pin ON/OFF</title><style>body { background-color: #d0e4fe;}</style></head>");
         
        client.print("<h1>Led pin is now: ");
         
        if(value == HIGH) {
        client.print("<p style= color:red><b>On</b></p>");
        } else {
        client.print("<p style= color:green><b>Off</b></p>");
        }
        client.println("</h1><h2 style= color:blue> Temperature: ");
         
        client.println(Temperature);
         
        client.println("</h2>");
        client.println("<h2 style= color:blue>Pressure: ");
         
        client.println(Pressure / 133.3);
         
        client.println("</h2><br>");
        client.println("<p>Click <a href=\"/LED=ON\">here</a> turn the LED on pin 2 ON<br></p>");
        client.println("<p1>Click <a href=\"/LED=OFF\">here</a> turn the LED on pin 2 OFF<br></p1><br>");
         
        client.println("<form>");
        client.println("<input type= button value = ON  onClick='location.href= \"/LED=ON\"'>");
        client.println("<input type= button value= OFF onClick='location.href= \"/LED=OFF\"'>");
        client.println("</form>");
         
         
        client.println("</body> </html>");
        /**/
        delay(1);
        Serial.println("Client disonnected");
        Serial.println("");
}
