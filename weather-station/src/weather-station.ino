#include <ArduinoJson.h>
#include <Task.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

void updateWeatherInfo(uint32_t deltaTime);
void parseWeatherInfo(String payload);

//Definir o SSID da rede WiFi
const char* ssid = "ssid";
//Definir a senha da rede WiFi
const char* password = "password";

ESP8266WiFiMulti WiFiMulti;

TaskManager taskManager;
FunctionTask taskGetInfo(updateWeatherInfo, MsToTaskTime(10000)); // turn on the led in 400ms

#define JSON_BUFFER 2048
//Definir a chave do site openweathermap.org
char id[] = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
char city[] = "SaoPaulo";

void setup() {
  Serial.begin(115200);
  WiFiMulti.addAP(ssid, password);
  while (WiFiMulti.run() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  taskManager.StartTask(&taskGetInfo);
}

void loop() {
  taskManager.Loop();
}

void parseWeatherInfo(String payload) {
  StaticJsonBuffer<JSON_BUFFER> jsonBuffer;

  JsonObject& root = jsonBuffer.parseObject(payload);

  if (!root.success()) {
    Serial.println("parseObject() failed");
    return;
  }

  double temp = root["main"]["temp"];
  int humd = root["main"]["humidity"];
  double temp_m = root["main"]["temp_min"];
  double temp_p = root["main"]["temp_max"];
  int press = root["main"]["pressure"];

  Serial.print("Temp: ");
  Serial.println(temp - 273.15, 2);
  Serial.printf("Umidade: %d%\n", humd);
  Serial.printf("Temperatura Maxima: ");
  Serial.println(temp_m - 273.15, 2);
  Serial.printf("Temperatura Minima: ");
  Serial.println(temp_p - 273.15, 2);
  Serial.printf("Pressao Atm: %d\n", press);
}

void updateWeatherInfo(uint32_t deltaTime) {
  HTTPClient http;

  String httpAsk = "http://api.openweathermap.org/data/2.5/weather?q=";
  httpAsk += city;
  httpAsk += ",uk&id=524901&APPID=";
  httpAsk += id;

  http.begin(httpAsk);

  int httpCode = http.GET();

  if(httpCode > 0) {
    if(httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      //Serial.println(payload);
      parseWeatherInfo(payload);
    }
  } else {
    Serial.printf("Error: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();
}
