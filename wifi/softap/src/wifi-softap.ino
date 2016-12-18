//Include da lib de Wifi do ESP8266
#include <ESP8266WiFi.h>

//Definir o SSID da rede WiFi
const char* ssid = "pedro";
//Definir a senha da rede WiFi
const char* password = "minhasenha123";

void setup(void){

  //Configuração da UART
  Serial.begin(115200);

  //Modo debug do WiFi
  //Habilita o printf do debug na serial
  Serial.setDebugOutput(true);
  //Habilita o debug do WiFi/modo diagnostico
  WiFi.printDiag(Serial);

  //Logs na porta serial
  Serial.print("Iniciando a rede ");
  Serial.println(ssid);

  //Inicia o WiFi para modo AP (Access Point)
  WiFi.mode(WIFI_AP);

  /* Configura o AP
  SSID
  senha
  canal (1-14)
  esconder rede (0-nao 1-sim)
  */
  //Configura o AP
  WiFi.softAP(ssid,password,2,0);

  //Logs na porta serial
  Serial.print("AP IP: ");
  Serial.println(WiFi.softAPIP());

}

void loop(void){

}
