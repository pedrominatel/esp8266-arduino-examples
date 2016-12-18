#include "sensor-shield.h"

int brilho = 0;  //variavel para o brilho do LED
int fade = 1;    //incremento do brilho do LED

void setup(void) {
  //Configura o pino digital para saida/output
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  //Coloca todos os pinos do LED com sinal baixo
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_B, LOW);
}

void loop(void) {
  //envia o comando de escrita no pino A0 analogico o valor de 0 a 1023
  analogWrite(LED_B, brilho);

  //incrementa o brilho do LED
  brilho = brilho + fade;

  //inverte o sentido do incremento para diminuir o brilho
  if (brilho <= 0 || brilho >= 1023) {
    fade = -fade;
  }

  //pausa para o efeito de fade do LED
  delay(1);
}
