
/*
The MIT License (MIT)
Copyright (c) 2017 Pedro Minatel
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <Wire.h>

//Endereço do sensor BH1750
byte u8_BH1750_address = 0x23; //Pino ADDR em nível lógico 0
//byte u8_BH1750_address = 0x5c; //Pino ADDR em nível lógico 1

//Instruções de modo de leitura
byte mode_HighResolution_1 = 0x10; //Modo de alta precisão com 1 lux de resolução
byte mode_HighResolution_2 = 0x11; //Modo de alta precisão com 0.5 lux de resolução
byte mode_LowResolution = 0x13; //Modo de baixa precisão com 4 lux de resolução

int16_t sensor_result = 0;

void read_sensor(void){

  //Inicia a comunicação I2C no endereço selecionado
  Wire.beginTransmission(u8_BH1750_address);
  //Configura o sensor para o modo de operação
	Wire.write(mode_HighResolution_1);
  //Finaliza a comunicação
	Wire.endTransmission();

  //Faz a requisição de leitura do sensor, esperando 2 bytes de resosta
  Wire.requestFrom(u8_BH1750_address, 2); //

  //Espera a chegada dos 2 bytes
  if (2 <= Wire.available()) {
    sensor_result = Wire.read();
    sensor_result = sensor_result << 8;
    sensor_result |= Wire.read();
    Serial.println(sensor_result);
  }
}

void setup(void){
  Wire.begin();
  Serial.begin(115200);
}

void loop(void){
  read_sensor();
  delay(2000);
}
