#include "sensor-shield.h"

void setup(void) {
  //Configura o pino digital para saida/output
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
}


void loop(void) {
  //envia o comando de escrita no pino digital
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_B, LOW);

  digitalWrite(LED_R, HIGH);
  //funcao de pausa/delay em mili-segundos
  delay(1000);
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_G, HIGH);
  delay(1000);
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_B, HIGH);
  delay(1000);
  digitalWrite(LED_B, LOW);
}
