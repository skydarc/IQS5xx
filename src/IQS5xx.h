/**
  **********************************************************************************
  * @file     IQS5xx.h
  * @author   skydarc
  * @version  V0.1
  * @date     2022-10-20
  * @brief    This file contains the constructors and methods which allow ease of
  *           use of an IQS5xx capactive touch controller. The IQS5xx is a capacitive
  *           touch Integrated Circuit (IC) which provides easy trackpad
  *           functionality. This class provides an easy means of initializing
  *           and interacting with the IQS5xx device from an Arduino.
  **********************************************************************************
  * @attention  Makes use of the following standard Arduino libraries:
  * - Arduino.h -> Included in IQS5xx.h, comes standard with Arduino
  * - Wire.h    -> Included in IQS5xx.h, comes standard with Arduino
  *
  **********************************************************************************
  */


#include "Arduino.h"
#include <Wire.h>
#include "IQS5xx_addresses.h"



/**
* This class allows for easy control over a IQS5xx IC.
*/
class IQS5xx {
    public:
		uint8_t _readyPin;
        uint8_t  Data_Buff[44];
        uint16_t ui16SnapStatus[15], ui16PrevSnap[15];
    
        /**
         * @param sda the pin identifier for SDA I2C signal
         * @param scl the pin identifier for SCL I2C signal
         * @param i2c_addr the 8-bit I2C address for this device. Note that LSB is a don't care.
         */
        IQS5xx();
        
        uint8_t I2C_Write(uint16_t ui16RegisterAddress, uint8_t *pData, uint8_t ui8NoOfBytes);
        uint8_t I2C_Read(uint16_t ui16RegisterAddress, uint8_t *pData, uint8_t ui8NoOfBytes);
        
        // Public Methods
		bool begin(uint8_t deviceAddressIn, uint8_t readyPinIn);
		void startInterrupt(void *pFunc, uint8_t trigger);
        void AcknowledgeReset(void);
        uint8_t CheckVersion(uint8_t pData[]);
        void DisplaySnap(void);
        uint8_t Process_XY(uint16_t pData[]);
		uint8_t getGesture(void);
        void Close_Comms();
  
    private:
		uint8_t _deviceAddress;
        uint8_t ui8Success;
        
        // Private Methods
        uint8_t I2C_Write2(uint16_t ui16RegisterAddress, uint8_t *pData, uint8_t ui8NoOfBytes);
        uint8_t I2C_Read2(uint16_t ui16RegisterAddress, uint8_t *pData, uint8_t ui8NoOfBytes);
      
};

 