/*
The MIT License (MIT)
Copyright (c) 2015 Pedro Minatel
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "FS.h"
#include <ESP8266WiFi.h>

const char* ssid = "ssid";
const char* password = "pass";
String buf;

WiFiServer server(80);

void formatFS(void){
  SPIFFS.format();
}

void createFile(void){
  File wFile;

  if(SPIFFS.exists("/log.txt")){
    Serial.println("Arquivo ja existe!");
  } else {
    Serial.println("Criando o arquivo...");
    wFile = SPIFFS.open("/log.txt","w+");

    if(!wFile){
      Serial.println("Erro ao criar arquivo!");
    } else {
      Serial.println("Arquivo criado com sucesso!");
    }
  }
  wFile.close();
}

void deleteFile(void) {
  if(SPIFFS.remove("/log.txt")){
    Serial.println("Erro ao remover arquivo!");
  } else {
    Serial.println("Arquivo removido com sucesso!");
  }
}

void writeFile(String msg) {
  File rFile = SPIFFS.open("/log.txt","a+");

  if(!rFile){
    Serial.println("Erro ao abrir arquivo!");
  } else {
    rFile.println(msg);
    Serial.println(msg);
  }
  rFile.close();
}

void readFile(void) {
  File rFile = SPIFFS.open("/log.txt","r");
  Serial.println("Reading file...");
  while(rFile.available()) {
    String line = rFile.readStringUntil('\n');
    buf += "<li>";
    buf += line;
    buf += "</li>";
  }
  rFile.close();
}

void closeFS(void){
  SPIFFS.end();
}

void openFS(void){
  if(!SPIFFS.begin()){
    Serial.println("Erro ao abrir o sistema de arquivos");
  } else {
    Serial.println("Sistema de arquivos aberto com sucesso!");
  }
}

//_____setup routine____________________________________________
void setup(void){
  //Configura a porta serial para 115200bps
  Serial.begin(115200);

  //Abre o sistema de arquivos (mount)
  openFS();
  //Cria o arquivo caso o mesmo não exista
  createFile();

  writeFile("Connecting to ");
  writeFile(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  writeFile("WiFi connected");
  Serial.println(WiFi.localIP());

  server.begin();
  writeFile("Server started");
}

void loop(void){
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

  buf = "";

  buf += "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n";
  buf += "<h3>ESP8266 Log</h3>";
  buf += "<ul>";
  readFile();
  buf += "</ul>";
  buf += "<h4>Criado por Pedro Minatel</h4>";
  buf += "</html>\n";

  client.print(buf);
  client.flush();

  Serial.println("Client disonnected");
}
