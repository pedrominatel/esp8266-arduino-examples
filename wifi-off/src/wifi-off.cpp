//Include da lib de Wifi do ESP8266
#include <ESP8266WiFi.h>

//Definir o SSID da rede WiFi
const char* ssid = "<<<SSID>>>";
//Definir a senha da rede WiFi
const char* password = "<<PASSWORD>>";

void connect_wifi(void){
  //Inicia o WiFi
  WiFi.begin(ssid, password);
  Serial.print("Conectando");
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

  digitalWrite(D6, HIGH);
  delay(2000);
}

void setup(void){

  //Configura o pino digital para saida/output
  pinMode(D6, OUTPUT);
  digitalWrite(D6, LOW);
  //Configuração da UART
  Serial.begin(115200);

  //Logs na porta serial
  Serial.print("Conectando na rede ");
  Serial.println(ssid);
  connect_wifi();

  Serial.println("Desabilitando o WiFi - Modo WIFI_OFF");
  WiFi.mode(WIFI_OFF);
  Serial.println("Forcando o desligamento do WiFi");
  WiFi.forceSleepBegin();
  delay(10);

  digitalWrite(D6, LOW);

  Serial.println("Forcando o religamento do WiFi");
  WiFi.forceSleepWake();
  Serial.println("Conectando na rede");
  connect_wifi();

}

void loop(void){
}
