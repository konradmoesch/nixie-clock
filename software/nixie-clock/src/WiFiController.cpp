#include "Arduino.h"
#include "WiFiController.hpp"
#include <ArduinoLog.h>

#define CONNECT_TIME 10000
#define TIMEOUTTIME 5000

/*void startWiFiAP(){
  WiFi.softAP("nixieclock", "sicher123!");
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  Serial.println("config not yet impl!");
  //server.begin();
  while (true) {
    WiFiClient client = server.available();   // listen for incoming clients
    if (client) {                             // if you get a client,
      Serial.println("New Client.");           // print a message out the serial port
      String currentLine = "";                // make a String to hold incoming data from the client
      while (client.connected()) {            // loop while the client's connected
        if (client.available()) {             // if there's bytes to read from the client,
          char c = client.read();             // read a byte, then
          Serial.write(c);                    // print it out the serial monitor
          if (c == '\n') {                    // if the byte is a newline character
  
            // if the current line is blank, you got two newline characters in a row.
            // that's the end of the client HTTP request, so send a response:
            if (currentLine.length() == 0) {
              // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
              // and a content-type so the client knows what's coming, then a blank line:
              client.println("HTTP/1.1 200 OK");
              client.println("Content-type:text/html");
              client.println();
  
              // the content of the HTTP response follows the header:
              client.println("blA"); 
  
              // The HTTP response ends with another blank line:
              client.println();
              // break out of the while loop:
              break;
            } else {    // if you got a newline, then clear currentLine:
              currentLine = "";
            }
          } else if (c != '\r') {  // if you got anything else but a carriage return character,
            currentLine += c;      // add it to the end of the currentLine
          }
        }
      }
      // close the connection:
      client.stop();
      Serial.println("Client Disconnected.");
    }
  }
  const char* ssid = "foo";
  const char *password = "bar";
  delay(10000);
  WiFi.disconnect();
  WiFi.begin();
}*/

void startWifi(const char* ssid, const char* password){
  Serial.print("Attempting to connect to ");
  Serial.println(ssid);
  WiFi.persistent(true);
  WiFi.begin(ssid, password);
  //WiFi.begin();
  size_t start_time = millis();
  size_t dot_time = millis();
  while ((WiFi.status() != WL_CONNECTED) && (start_time + CONNECT_TIME) > millis()) {
    if (dot_time + 250 < millis()) {
      Serial.print(".");
      dot_time = millis();
    }
  }

  /*if (WiFi.status() != WL_CONNECTED) {
    startWiFiAP();
  }*/
  
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("ESP32 IP address: ");
  Serial.println(WiFi.localIP());
}

void WiFiController::initialize(const char* ssid, const char* password) {
  Log.noticeln("Initializing WiFi");
  startWifi(ssid, password);
}
