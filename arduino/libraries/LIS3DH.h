/*
  LISH3D_core_spi.h - Library for interacting with the STMicro LIS3DH
                      MEMS digital output motion sensor, ultra low-power
                      high performance 3-axes “nano” accelerometer.
  Created by Craig Wm. Versek, 2014-12-04
 */
#ifndef _LISH3D_core_spi_H_INCLUDED
#define _LISH3D_core_spi_H_INCLUDED

#include <Arduino.h>

#define DEFAULT_STARTUP_DELAY_MS 500
#define VREF_MAX 5.46 /*Vdd_MAX - 0.04 V */
#define RES24BIT 16777216
#define ADDR_MAX 32   /* 001r rrrr 2**5 possible*/
#define RDATA_NUM_BYTES 27

/*******************************************************************************
  LIS3DH_CoreSPIClass
  
*******************************************************************************/
class LIS3DH_CoreSPIClass {
public:
  LIS3DH_CoreSPIClass(const int slaveSelectLowPin,
                      const int dataReadyLowPin,
                     );
  //Configuration methods
  void begin(int startup_delay_ms = DEFAULT_STARTUP_DELAY_MS);
  //Functionality method
  int startConversions();
  int stopConversions();
  int readDataRaw(byte *data_array);
  void attach_dataReadyLow_interrupt(void (*function)(void));
  void detach_dataReadyLow_interrupt();
  byte _readRegister (int addr);
  int  _writeRegister(int addr, byte value);
private:
  //Attributes
  int _slaveSelectLowPin;
  int _dataReadyLowPin;
};

/*******************************************************************************
  LIS3DH NAMESPACE DEFINITIONS
*******************************************************************************/
#ifdef __cplusplus
namespace LIS3DH {
#endif
const int ADDR_MAX = 0x3D;
//    enum spi_command {
//        // system commands
////        WAKEUP = 0x02,
////        STANDBY = 0x04,
////        RESET = 0x06,
////        START = 0x08,
////        STOP = 0x0a,

////        // read commands
////        RDATAC = 0x10,
////        SDATAC = 0x11,
////        RDATA = 0x12,

////        // register commands
////        RREG = 0x20,
////        WREG = 0x40
//    };

//    enum reg {
//        // device settings
//        ID = 0x00,

//        // global settings
//        CONFIG1 = 0x01,
//        CONFIG2 = 0x02,
//        CONFIG3 = 0x03,
//        LOFF = 0x04,

//        // channel specific settings
//        CHnSET = 0x04,
//        CH1SET = CHnSET + 1,
//        CH2SET = CHnSET + 2,
//        CH3SET = CHnSET + 3,
//        CH4SET = CHnSET + 4,
//        CH5SET = CHnSET + 5,
//        CH6SET = CHnSET + 6,
//        CH7SET = CHnSET + 7,
//        CH8SET = CHnSET + 8,
//        RLD_SENSP = 0x0d,
//        RLD_SENSN = 0x0e,
//        LOFF_SENSP = 0x0f,
//        LOFF_SENSN = 0x10,
//        LOFF_FLIP = 0x11,

//        // lead off status
//        LOFF_STATP = 0x12,
//        LOFF_STATN = 0x13,

//        // other
//        GPIO = 0x14,
//        PACE = 0x15,
//        RESP = 0x16,
//        CONFIG4 = 0x17,
//        WCT1 = 0x18,
//        WCT2 = 0x19
//    };

//    enum ID_bits {
//        DEV_ID7 = 0x80,
//        DEV_ID6 = 0x40,
//        DEV_ID5 = 0x20,
//        DEV_ID2 = 0x04,
//        DEV_ID1 = 0x02,
//        DEV_ID0 = 0x01,

//        ID_const = 0x10,
//        ID_ADS129x = DEV_ID7,
//        ID_ADS129xR = (DEV_ID7 | DEV_ID6),

//        ID_4CHAN = 0,
//        ID_6CHAN = DEV_ID0,
//        ID_8CHAN = DEV_ID1,

//        ID_ADS1294 = (ID_ADS129x | ID_4CHAN),
//        ID_ADS1296 = (ID_ADS129x | ID_6CHAN),
//        ID_ADS1298 = (ID_ADS129x | ID_8CHAN),
//        ID_ADS1294R = (ID_ADS129xR | ID_4CHAN),
//        ID_ADS1296R = (ID_ADS129xR | ID_6CHAN),
//        ID_ADS1298R = (ID_ADS129xR | ID_8CHAN)
//    };


#ifdef __cplusplus
}
#endif /* namespace ADS129x */


#endif /* _LISH3D_core_spi_H_INCLUDED */
