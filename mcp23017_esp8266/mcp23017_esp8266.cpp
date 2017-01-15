/*
 * MCP23017 for ESP8266
 *
 *  Created on: 07/10/2015
 *      Author: pedrominatel
 */

#include "Wire.h"

//GPIOs definition
#define GPIO1			0
#define GPIO2			1
#define GPIO3			2
#define GPIO4			3
#define GPIO5			4
#define GPIO6			5
#define GPIO7			6
#define GPIO8			7
#define GPIO9			8
#define GPIO10			9
#define GPIO11			10
#define GPIO12			11
#define GPIO13			12
#define GPIO14			13
#define GPIO15			14
#define GPIO16			15
//GPIO mode
#define GPIO_OUTPUT		0
#define GPIO_INPUT		1
//GPIO state
#define GPIO_HIGH		0
#define GPIO_LOW		1
//GPIO BANK
#define IODIRA			0x00 //Config register PORTA
#define IODIRB			0x01 //Config register PORTB
#define PORTA			0x12 //PORT A register
#define PORTB			0x13 //PORT B register
//Chip Model
//#define CHIP8BITS
#define CHIP16BITS

unsigned short u16_GPIO_register = 0x00;
unsigned short u16_GPIO_controlState = 0x00;
byte u8_MCP23017_address = 0x20; //Default address is 0x20

/*
 * 
 * */
void MCP23017_I2C_send(byte portRegister, byte portValue){
	Wire.beginTransmission(u8_MCP23017_address);
	Wire.write(portRegister); // PORT A register
	Wire.write(portValue);
	Wire.endTransmission();
}

/*
 * 
 * */
void MCP23017_init(byte chipAddress, byte sda, byte scl) {
	u8_MCP23017_address = chipAddress;
	u16_GPIO_register = 0x00;
	u16_GPIO_controlState = 0x00;
	Wire.begin(sda, scl);
}

/*
 * 
 * */
void MCP23017_config(void) {
	MCP23017_I2C_send(IODIRA,0x00);
#ifdef CHIP16BITS
	MCP23017_I2C_send(IODIRB,0x00);
#endif
}

/*
 * 
 * */
void MCP23017_GPIO_config(byte gpio, byte gpioMode) {
	if (gpioMode == GPIO_OUTPUT)
		u16_GPIO_register |= 1 << gpio;
	if (gpioMode == GPIO_INPUT)
		u16_GPIO_register &= ~(1 << gpio);

	byte iodira = u16_GPIO_register;

	MCP23017_I2C_send(IODIRA,iodira);
#ifdef CHIP16BITS
	byte iodirb = u16_GPIO_register >> 8;
	MCP23017_I2C_send(IODIRB,iodirb);
#endif
}

/*
 * 
 * */
void MCP23017_GPIO_write(byte gpio, byte gpioState) {
	if (gpioState == GPIO_OUTPUT)
		u16_GPIO_controlState |= 1 << gpio;
	if (gpioState == GPIO_INPUT)
		u16_GPIO_controlState &= ~(1 << gpio);

	byte porta = u16_GPIO_controlState;

	MCP23017_I2C_send(PORTA,porta);
#ifdef CHIP16BITS
	byte portb = u16_GPIO_controlState >> 8;
	MCP23017_I2C_send(PORTB,portb);
#endif
}

/*
 * 
 * */
void MCP23017_GPIO_writeBits(unsigned short gpioState) {

	u16_GPIO_controlState = gpioState;

	byte porta = u16_GPIO_controlState;

	MCP23017_I2C_send(PORTA,porta);
#ifdef CHIP16BITS
	byte portb = u16_GPIO_controlState >> 8;
	MCP23017_I2C_send(PORTB,portb);
#endif
}

/*
 * 
 * */
byte MCP23017_GPIO_read(byte gpio) {

	byte port = PORTA;
	byte inputs = 0;

	if(gpio > GPIO8)
		port = PORTB;

	Wire.beginTransmission(u8_MCP23017_address);
	Wire.write(port); // set MCP23017 memory pointer to GPIOB address
	Wire.endTransmission();
	Wire.requestFrom(u8_MCP23017_address, gpio); // request one byte of data from MCP20317
	inputs = Wire.read(); // store the incoming byte into "inputs"

	if(inputs > 0)
		return inputs;

	return 0;
}

void setup() {
  MCP23017_init(u8_MCP23017_address, 4,14);
  MCP23017_config();
}

void loop() {
  
  MCP23017_GPIO_write(GPIO9, GPIO_HIGH);
  MCP23017_GPIO_write(GPIO1, GPIO_LOW);
  delay(1000);
  MCP23017_GPIO_write(GPIO9, GPIO_LOW);
  MCP23017_GPIO_write(GPIO1, GPIO_HIGH);
  delay(1000);
  
//   for (int a=0; a<65536; a++)
// {
//   MCP23017_GPIO_writeBits(a);
//   delay(50);
// }
}
