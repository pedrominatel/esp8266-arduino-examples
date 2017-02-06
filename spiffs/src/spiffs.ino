#include "FS.h"

void formatFS(void){
  SPIFFS.format();
}

void createFile(void){
  File wFile;

  if(SPIFFS.exists("/log.txt")){
    Serial.println("Arquivo ja existe!");
  } else {
    Serial.println("Criando o arquivo...");
    wFile = SPIFFS.open("/log.txt","w+");

    if(!wFile){
      Serial.println("Erro ao criar arquivo!");
    } else {
      Serial.println("Arquivo criado com sucesso!");
    }
  }
  wFile.close();
}

void deleteFile(void) {
  if(SPIFFS.remove("/log.txt")){
    Serial.println("Erro ao remover arquivo!");
  } else {
    Serial.println("Arquivo removido com sucesso!");
  }
}

void writeFile(String msg) {
  File rFile = SPIFFS.open("/log.txt","a+");

  if(!rFile){
    Serial.println("Erro ao abrir arquivo!");
  } else {
    rFile.println(msg);
  }
  rFile.close();
}

void readFile(void) {
  File rFile = SPIFFS.open("/log.txt","r");
  Serial.println("Reading file...");
  while(rFile.available()) {
    String line = rFile.readStringUntil('\n');
    Serial.println(line);
  }
  rFile.close();
}

void closeFS(void){
  SPIFFS.end();
}

void openFS(void){
  if(!SPIFFS.begin()){
    Serial.println("Erro ao abrir o sistema de arquivos");
  } else {
    Serial.println("Sistema de arquivos aberto com sucesso!");
  }
}

//_____setup routine____________________________________________
void setup(void){
  //Configura a porta serial para 115200bps
  Serial.begin(115200);

  //Abre o sistema de arquivos (mount)
  openFS();
  //Cria o arquivo caso o mesmo não exista
  createFile();
  //Escreve uma string no arquivo
  writeFile("Escreve no arquivo!");
  writeFile("Adiciona uma linha no arquivo");
  //Faz a leitura do arquivo
  readFile();
  //Fecha o sistema de arquivos (unmount)
  closeFS();

}

void loop(void){

}
