#include <Arduino.h>
#include "scoreBoardEvents.h"
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino

//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager

WiFiServer server(80);
String header;
String title = "Foosball Counter";

//// Start of Code
void setup() {
  utils_init();
  scoreBoardEventsInit();
  Serial.begin(115200);
  WiFiManager wifiManager;
  wifiManager.autoConnect();
  server.begin();
}

void loop() {
  scoreBoardEventsCheckClicks();
  WiFiClient client = server.available();   
  if (client) {                             
    String currentLine = "";                
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            client.println("<!DOCTYPE html><html>");
            client.println("<head>");
            client.println("<meta charset=\"utf-8\">");
            client.println("<meta name=\"viewport\" content=\"width=device-width, user-scalable=no, minimum-scale=1.0, maximum-scale=1.0\">");
            client.println("<title>"+title+"</title>");
            client.println("<style type=\"text/css\">html {background-image: linear-gradient(to left, #1fc8db , #188db9 )} #info { position : absolute; top : 0px; width : 99\%; text-align : center; } #info a { color : #66F; text-decoration : none; } #info a:hover { text-decoration : underline; } #container { width: 100%; height: 100%; overflow: hidden; padding: 0;margin: 0; -webkit-user-select: none; -moz-user-select: none;} button { height: 150px;width: 150px;margin: 10px;font-size: 50px;}</style>");
            client.println("</head>");
            client.println("<body>");
            client.println("<div id=\"container\"></div>");
            client.println("<div id=\"info\">");
            client.println("<h1 style=\"text-align:center;margin:auto;color:#f3f3f3;font-size:30px;font-weight:550;padding-top:105px;font-family: Verdana,sans-serif;\">"+title+"</h1>");

            String scoreA = " (Team A) " + String(teamAScore);
            String scoreB = String(teamBScore) +" (Team B)";
            String scoreText = scoreA +" : " + scoreB;
            
            Serial.println(scoreText);

            client.println("<span style=\"text-align:center;margin:auto;color:#f3f3f3;font-size:20px;font-weight:250;padding-top:105px;font-family: Verdana,sans-serif;\" id=\"result\"> "+scoreText+"</span>");
            client.println("</div>");

            
            client.println("<script>");
            client.println("setTimeout(function() { location.reload();}, 5000);");
            client.println("</script>");
            client.println("</body>");
            client.println("</html>");
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}