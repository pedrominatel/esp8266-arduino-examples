//https://github.com/tzapu/WiFiManager

#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager


void setup() {

    Serial.begin(115200);

    //Inicializacao do WiFiManager
    WiFiManager wifiManager;

    //Define o auto connect e o SSID do modo AP
    wifiManager.autoConnect("AutoConnectAP");

    //Log na serial se conectar
    Serial.println("Conectado");

}

void loop() {

}
