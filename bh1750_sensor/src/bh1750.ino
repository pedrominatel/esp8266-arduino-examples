#include <Wire.h>


//Endereço do sensor BH1750
byte u8_BH1750_address = 0x23; //Pino ADDR em nível lógico 0
//byte u8_BH1750_address = 0x5c; //Pino ADDR em nível lógico 1

//Instruções de modo de leitura
byte mode_HighResolution_1 = 0x10; //0001_0000
byte mode_HighResolution_2 = 0x11; //0001_0001
byte mode_LowResolution = 0x13; //0001_0011

int sensor_result = 0;

void read_sensor(void){

  Wire.beginTransmission(u8_BH1750_address);
	Wire.write(mode_HighResolution_1); //
	Wire.endTransmission();
	
  Wire.requestFrom(u8_BH1750_address, 2); //

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
