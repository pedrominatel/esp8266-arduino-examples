#include "FS.h"
#include <EEPROM.h>

//Define o quanto sera alocado entre 4 e 4096bytes
#define MEM_ALOC_SIZE 8
uint8_t boot_num = 0;

void  setup() {

  Serial.begin(115200);

  Serial.printf("Flash chip ID: %d\n", ESP.getFlashChipId());
  Serial.printf("Flash chip size (in bytes): %d\n", ESP.getFlashChipSize());
  Serial.printf("Flash chip speed (in Hz): %d\n", ESP.getFlashChipSpeed());

  EEPROM.begin(MEM_ALOC_SIZE);
  boot_num = EEPROM.read(0);
  boot_num++;
  EEPROM.write(0,boot_num);
  EEPROM.end();

  Serial.printf("Boot num: %d\n", boot_num);

}

void loop() {

}
