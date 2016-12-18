#include "sensor-shield.h"

int botao_status = 0;
int btn_last = 0;
int debounce = 0;
int ciclos_cpu = 1000;
int button_debounced = 0;


void setup (void){

  //configura o botao como entrada/input
  pinMode(BOTAO, INPUT);
  //configura o rele como saida/output
  pinMode(RELE, OUTPUT);

  //Configura a serial/uart0 para 115200bps
  Serial.begin(115200);

}

void loop(void){

  //le o status do botao e inverte o status (pullup)


  botao_status = !digitalRead(BOTAO);

  if(botao_status == 1){
    debounce++;
  } else {
    debounce = 0;
  }

  if(debounce >= ciclos_cpu){
    button_debounced = 1;
  } else {
    button_debounced = 0;
  }

  if(button_debounced != btn_last){
    if(button_debounced == HIGH){
      digitalWrite(RELE, HIGH);
      btn_last = HIGH;
      //escreve na serial o resultado do push
      Serial.printf("Ligado\n");
    } else {
      digitalWrite(RELE, LOW);
      btn_last = LOW;
      //escreve na serial o resultado do push
      Serial.printf("Desligado\n");
    }
  }

}
