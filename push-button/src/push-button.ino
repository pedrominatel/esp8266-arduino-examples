#include "sensor-shield.h"

int botao_status = 0;

void setup (void){

  //configura o botao como entrada/input
  //pinMode(BOTAO, INPUT);
  //configura o rele como saida/output
  pinMode(RELE, OUTPUT);

}

void loop(void){

  //le o status do botao e inverte o status (pullup)
  botao_status = !digitalRead(BOTAO);
  //encreve na saida digital o resultado da leitura do botao
  digitalWrite(RELE,botao_status);

}
