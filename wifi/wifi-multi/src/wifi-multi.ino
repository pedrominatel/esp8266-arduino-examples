//Include das libs de Wifi do ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

//Inicializacao da lib de WiFiMulti
ESP8266WiFiMulti wifiMulti;

void setup(void){

  //Configuração da UART
  Serial.begin(115200);

  //Modo debug do WiFi
  //Habilita o printf do debug na serial
  Serial.setDebugOutput(true);
  //Habilita o debug do WiFi/modo diagnostico
  WiFi.printDiag(Serial);

  //Inicia o WiFiMulti
  //Define o primeiro AP
  wifiMulti.addAP("SMART", "redeiot123");
  //Define o segundo AP
  wifiMulti.addAP("ssid2", "senha");
  //Pode definir multiplos APs

  //Logs na porta serial
  Serial.println("");
  Serial.println("WiFi conectado!");
  Serial.print("Conectado na rede ");
  Serial.println(WiFi.SSID());
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("Subnet Mask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("MAC Address: ");
  Serial.println(WiFi.macAddress());
  Serial.print("RSSI: ");
  Serial.println(WiFi.RSSI());

}

void loop(void){
  //Loop até conectar no WiFi
  while (wifiMulti.run() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
}
