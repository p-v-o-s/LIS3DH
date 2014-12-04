/*
  LISH3D_core_spi.cpp - Library for interacting with the STMicro LIS3DH
                        MEMS digital output motion sensor, ultra low-power
                        high performance 3-axes “nano” accelerometer.
  Created by Craig Wm. Versek, 2014-12-04
 */
#include <Arduino.h>
#include <SPI.h>
#include "LIS3DH_core_spi.h"
 
LIS3DH_CoreSPIClass::LIS3DH_CoreSPIClass(const int slaveSelectLowPin,
                                         const int dataReadyLowPin
                                        ){
  _slaveSelectLowPin = slaveSelectLowPin;
  _dataReadyLowPin   = dataReadyLowPin;
}

void LIS3DH_CoreSPIClass::begin(int startup_delay_ms) {
  //wait for the LIS3DH to be ready - it can take a while to charge caps
  delay(startup_delay_ms); 
  // Configure the Arduino pins
  pinMode(_slaveSelectLowPin, OUTPUT);
  pinMode(_dataReadyLowPin, INPUT);
  digitalWrite(_slaveSelectLowPin, HIGH);  //comm. off
}


int LIS3DH_CoreSPIClass::startConversions(){
  digitalWrite(_slaveSelectLowPin, LOW);
  SPI.transfer(LIS3DH::START);
  delayMicroseconds(1);
  digitalWrite(_slaveSelectLowPin, HIGH);
  delayMicroseconds(2);
  return 0;
}

int LIS3DH_CoreSPIClass::stopConversions(){
  digitalWrite(_slaveSelectLowPin, LOW);
  SPI.transfer(LIS3DH::STOP);
  delayMicroseconds(1);
  digitalWrite(_slaveSelectLowPin, HIGH);
  delayMicroseconds(2);
  return 0;
}

int LIS3DH_CoreSPIClass::readDataRaw(byte *data_array){
  //while (digitalRead(_dataReadyLowPin)){}
  //data_array must be at least 27 bytes
  digitalWrite(_slaveSelectLowPin, LOW);
  SPI.transfer(LIS3DH::RDATA);
  for(int i = 0; i < RDATA_NUM_BYTES; i++){
    data_array[i] = SPI.transfer(0);
  }
  delayMicroseconds(1);
  digitalWrite(_slaveSelectLowPin, HIGH);
  //delay(10);
  return 0;
}


void LIS3DH_CoreSPIClass::attach_dataReadyLow_interrupt(void (*function)(void)){
  attachInterrupt(_dataReadyLowPin, function, FALLING);
}

void LIS3DH_CoreSPIClass::detach_dataReadyLow_interrupt(){
  detachInterrupt(_dataReadyLowPin);
}

byte LIS3DH_CoreSPIClass::_readRegister(int addr) {
  byte opcode1, opcode2, data;
  opcode1 = LIS3DH::RREG | (addr & 0b00011111);
  opcode2 = 0b00000000;// | (n    & 0b00011111); //FIXME we only ever need to read 1 byte at a time, right?
  digitalWrite(_slaveSelectLowPin, LOW);  //set chip as listener
  SPI.transfer(opcode1);                  //send command
  delayMicroseconds(5);
  SPI.transfer(opcode2);
  delayMicroseconds(5);
  data = SPI.transfer(0);                 //read back response (sending null byte)
  delayMicroseconds(1);
  digitalWrite(_slaveSelectLowPin, HIGH); //release chip select
  return data;
}


int LIS3DH_CoreSPIClass::_writeRegister(int addr, byte value) {
  if(addr > 0 && addr <= ADDR_MAX){
    byte opcode1, opcode2;
    opcode1 = LIS3DH::WREG | (addr &  0b00011111);
    opcode2 = 0b00000000;// | (n    & 0b00011111); //FIXME we only ever need to read 1 byte at a time, right?
    digitalWrite(_slaveSelectLowPin, LOW);
    SPI.transfer(opcode1);
    delayMicroseconds(5);
    SPI.transfer(opcode2);  // number of registers to be read/written – 1
    SPI.transfer(value);    // send the data
    delayMicroseconds(1);
    digitalWrite(_slaveSelectLowPin, HIGH);
    return 0;
  }
  else{ return -1; }          //error, out of range
}
