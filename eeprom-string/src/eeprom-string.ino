
#include <EEPROM.h>
#include <ESP8266WiFi.h>

void erase_eeprom(void);

void  setup() {

  Serial.begin(115200);

  String message = "Minha String na EEPROM";
  byte msg_write[message.length()+1];
  byte msg_read[message.length()+1];
  message.getBytes(msg_write, message.length()+1);

  Serial.print("\n");
  Serial.print("String: " +message+ " Tamanho: " +message.length()+ "\n");

  EEPROM.begin(message.length()+1);

  uint8_t boot_num = EEPROM.read(0);

  for (int i = 0; i < message.length(); i++){
    EEPROM.write(i,msg_write[i]);
  }

  EEPROM.commit();

  for (int i = 0; i < message.length(); i++){
    msg_read[i] = EEPROM.read(i);
    Serial.print(msg_read[i],DEC);
    Serial.print(" ");
  }

  Serial.print("\n");

  EEPROM.end();

  for (int i = 0; i < message.length(); i++){
    char str = char(msg_read[i]);
    Serial.print(str);
  }

}

void loop() {

}
