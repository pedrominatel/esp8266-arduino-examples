void setup(void) {
  //Configura o pino digital para saida/output
  pinMode(5, OUTPUT);
  digitalWrite(5, LOW);
}

void loop(void) {
  //envia o comando de escrita no pino digital
  digitalWrite(5, HIGH);
  //funcao de pausa/delay em mili-segundos
  delay(1000);
  digitalWrite(5, LOW);
  delay(1000);
}
