#include "sensor-shield.h"

int valor_ldr = 0;
unsigned long currentMillis = 0;
long previousMillis = 0;        // Variável de controle do tempo
long redLedInterval = 250;     // Tempo em ms do intervalo a ser executado

void setup(void){

  //Configura a serial/uart0 para 115200bps
  Serial.begin(115200);

}

void read_ldr(void){

  //Le o valor do pino analogico A0
  valor_ldr = analogRead(LDR);
  //Imprime o resultado na serial
  Serial.print("Valor LDR: ");
  Serial.println(valor_ldr);

}

void loop(void){

  currentMillis = millis();    //Tempo atual em ms
  	//Lógica de verificação do tempo
  if (currentMillis - previousMillis > redLedInterval) {
    previousMillis = currentMillis;    // Salva o tempo atual
    //Chama a funcao de leitura do ADC
    read_ldr();
  }

}
