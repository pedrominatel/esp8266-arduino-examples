
#include <EEPROM.h>

//Define o quanto sera alocado entre 4 e 4096bytes
#define MEM_ALOC_SIZE 8
uint8_t boot_num = 0;
uint8_t * e_payload;
uint8_t * saved;

void erase_eeprom(void);

void  setup() {

  Serial.begin(115200);

  EEPROM.begin(MEM_ALOC_SIZE);

  Serial.printf("Flash chip ID: %d\n", ESP.getFlashChipId());
  Serial.printf("Flash chip size (in bytes): %d\n", ESP.getFlashChipSize());
  Serial.printf("Flash chip speed (in Hz): %d\n", ESP.getFlashChipSpeed());

  e_payload = (uint8_t *)calloc(MEM_ALOC_SIZE, sizeof(uint8_t));
  saved = (uint8_t *)calloc(MEM_ALOC_SIZE, sizeof(uint8_t));

  uint16_t cnt = 0;

  for (cnt = 0; cnt < MEM_ALOC_SIZE; cnt++) {
    e_payload[cnt] = cnt;
  }

  write_eeprom(e_payload,MEM_ALOC_SIZE);

  read_eeprom(saved,MEM_ALOC_SIZE);

  for (cnt = 0; cnt < MEM_ALOC_SIZE; cnt++) {
    Serial.printf("Saved position %d value %d\n", cnt, saved[cnt]);
  }

  //EEPROM.begin(MEM_ALOC_SIZE);
  //boot_num = EEPROM.read(0);
  //boot_num++;
  //EEPROM.write(0,boot_num);
  //EEPROM.end();
  //Serial.printf("Boot num: %d\n", boot_num);
}

void loop() {

}

void erase_eeprom(void) {
  uint16_t e_pos = 0;
  for (e_pos = 0; e_pos < MEM_ALOC_SIZE; e_pos++) {
    EEPROM.write(e_pos,0);
  }
  EEPROM.end();
}

void write_eeprom(uint8_t *payload, uint16_t size) {
  uint16_t e_pos = 0;
  for (e_pos = 0; e_pos < size; e_pos++) {
    EEPROM.write(e_pos,payload[e_pos]);
  }
  EEPROM.end();
}

void read_eeprom(uint8_t *payload, uint16_t size) {
  uint16_t e_pos = 0;
  for (e_pos = 0; e_pos < size; e_pos++) {
    payload[e_pos] = EEPROM.read(e_pos);
  }
  EEPROM.end();
}
