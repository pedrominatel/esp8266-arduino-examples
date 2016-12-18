//Include da lib de Wifi do ESP8266
#include <ESP8266WiFi.h>

//Definir o SSID da rede WiFi
const char* ssid = "LCH";
//Definir a senha da rede WiFi
const char* password = "tijolo22";

//Define o IP
IPAddress ip(192, 168, 0, 110);
//Define o GateWay
IPAddress gateway(192, 168, 0, 1);
//Define a mascara de subrede
IPAddress subnet(255, 255, 255, 0);


void setup(void){

  //Configura o pino digital para saida/output
  pinMode(5, OUTPUT);
  digitalWrite(5, LOW);
  //Configuração da UART
  Serial.begin(115200);

  //Modo debug do WiFi
  //Habilita o printf do debug na serial
  //Serial.setDebugOutput(true);
  //Habilita o debug do WiFi/modo diagnostico
  WiFi.printDiag(Serial);

  //Logs na porta serial
  Serial.print("Conectando na rede ");
  Serial.println(ssid);

  //Inicia o WiFi
  WiFi.begin(ssid, password);

  //Configura para obter IP fixo
  //WiFi.config(ip, gateway, subnet);

  //Loop até conectar no WiFi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

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
  Serial.println("WiFi conectado!");
  delay(2000);
}
