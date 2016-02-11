/*
*
*/

#include <ESP8266WiFi.h>

const char* ssid = "ssid";
const char* password = "password";

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);

  // prepare GPIO2
  pinMode(4, OUTPUT);
  digitalWrite(4, 0);

  pinMode(5, OUTPUT);
  digitalWrite(5, 0);
  
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
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  String buf = "";

  buf += "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n";
  buf += "<h3> ESP8266 Web Server</h3>";
  buf += "<p>GPIO4 <a href=\"?function=led4_on\"><button>ON</button></a>&nbsp;<a href=\"?function=led4_off\"><button>OFF</button></a></p>";
  buf += "<p>GPIO5 <a href=\"?function=led5_on\"><button>ON</button></a>&nbsp;<a href=\"?function=led5_off\"><button>OFF</button></a></p>";
  buf += "<h4>Criado por Pedro Minatel</h4>";
  buf += "</html>\n";

  client.print(buf);
  client.flush();
  
  if (req.indexOf("led5_on") != -1)
    digitalWrite(5, 1);
  else if (req.indexOf("led5_off") != -1)
    digitalWrite(5, 0);
  else if (req.indexOf("led4_on") != -1)
    digitalWrite(4, 1);
  else if (req.indexOf("led4_off") != -1)
    digitalWrite(4, 0);
  else {
    Serial.println("invalid request");
    client.stop();
  }
  Serial.println("Client disonnected");
}

