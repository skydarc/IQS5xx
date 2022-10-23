/**
  **********************************************************************************
  * @file     IQS5xx.cpp
  * @author   skydarc
  * @version  V0.0.0
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

#include "IQS5xx.h"

/**************************************************************************************************************/
/*                                                CONSTRUCTORS                                                */
/**************************************************************************************************************/

IQS5xx::IQS5xx() {
}

/**
  * @name   begin
  * @brief  A method to initialize the IQS5xx device with the device address and ready pin specified by the user.
  * @param  deviceAddress -> The address of the IQS5xx device.
  *         readyPin      -> The Arduino pin which is connected to the ready pin of the IQS266 device.
  * @retval Returns true if communication has been successfully established, returns false if not.
  * @notes  Receiving a true return value does not mean that initialization was successful.
  *         Receiving a true return value only means that the IQS device responded to the request for communication.
  *         Receiving a false return value means that initialization did not take place at all.
  *         If communication is successfully established then it is unlikely than initialization will fail.
  */
bool IQS5xx::begin(uint8_t deviceAddressIn, uint8_t readyPinIn)
{
  
  // Initialize I2C communication here, since this library can't function without it.
  Wire.begin();
  
  Wire.setClock(400000);

  bool response = false;  // The return value. Is set to the return value of the requestComms function.
  _deviceAddress = deviceAddressIn;
  _readyPin = readyPinIn;
  
  pinMode(_readyPin, INPUT);

}

//*****************************************************************************
//
//! Acknowledge the reset flag
//!
//! This function simply sets the ACK_RESET bit found in the SYSTEM_CONTROL_0 
//! register.  By setting this bit the SHOW_RESET flag is cleared in the 
//! SYSTEM_INFO_0 register.  During normal operation, the SHOW_RESET bit can be 
//! monitored and if it becomes set, then an unexpected reset has occurred.  
//! If any device configuration is needed, it must then be repeated.
//!
//! \param None
//!
//! \return None
//
//*****************************************************************************
void IQS5xx::AcknowledgeReset(void) {
    static  uint8_t System_ctrl_0 = ACK_RESET;  

    I2C_Write(SystemControl0_adr, &System_ctrl_0, 1);
}

uint8_t IQS5xx::CheckVersion(uint8_t *pData) {
  
    //uint8_t ui8DataBuffer[15];  // defaut size : 6
	
    //
    // Dont wait for RDY here, since the device could be in EventMode, and then
    // there will be no communication window to complete this.  Rather do a 
    // forced communication, where clock stretching will be done on the IQS5xx
    // until an appropriate time to complete the i2c.
    //
    I2C_Read(ProductNumber_adr, pData ,6);
  
    /*printf("Product %d ", (ui8DataBuffer[0]<<8) + ui8DataBuffer[1]); 
    printf("Project %d ", (ui8DataBuffer[2]<<8) + ui8DataBuffer[3]);
    printf("Verrsion %d.%d\n", ui8DataBuffer[4], ui8DataBuffer[5]);*/
	
	return;
	
	//return &ui8DataBuffer[0];
    
    ////////////////////////
    // check other address :
    ////////////////////////
    
	/*
    // System Config 1
    ui8DataBuffer[0] = 3; 
    I2C_Write(SystemConfig1_adr, &ui8DataBuffer[0] ,1);
    I2C_Read(SystemConfig1_adr, &ui8DataBuffer[0] ,1);
    printf("System Config : %d\n", ui8DataBuffer[0]); 
      
    // swipe initial distance
    ui8DataBuffer[1] = 150; ui8DataBuffer[0] = 0; 
    I2C_Write(SwipeInitDistance_adr, &ui8DataBuffer[0] ,2);
    I2C_Read(SwipeInitDistance_adr, &ui8DataBuffer[0] ,2);
    printf("Swp init dist. : %d\n", (ui8DataBuffer[0]<<8) + ui8DataBuffer[1]); 
    
    // X resolution
    ui8DataBuffer[1] = 0; ui8DataBuffer[0] = 8; 
    I2C_Write(XResolution_adr, &ui8DataBuffer[0] ,2);
    I2C_Read(XResolution_adr, &ui8DataBuffer[0] ,2);
    printf("X resolution : %d\n", (ui8DataBuffer[0]<<8) + ui8DataBuffer[1]); 
    
    // Yresolution
    ui8DataBuffer[1] = 0; ui8DataBuffer[0] = 8; 
    I2C_Write(YResolution_adr, &ui8DataBuffer[0] ,2);
    I2C_Read(YResolution_adr, &ui8DataBuffer[0] ,2);
    printf("Y resolution : %d\n", (ui8DataBuffer[0]<<8) + ui8DataBuffer[1]);
    
    // Rx mapping
    I2C_Read(RxMapping_adr, &ui8DataBuffer[0] ,10);
    printf("mapping Rx :"); 
    printf(" %d,", ui8DataBuffer[0]);
    printf(" %d,", ui8DataBuffer[1]);
    printf(" %d,", ui8DataBuffer[2]);
    printf(" %d,", ui8DataBuffer[3]);
    printf(" %d,", ui8DataBuffer[4]);
    printf(" %d,", ui8DataBuffer[5]);
    printf(" %d,", ui8DataBuffer[6]);
    printf(" %d\n", ui8DataBuffer[7]);
    
    // Tx mapping
    I2C_Read(TxMapping_adr, &ui8DataBuffer[0] ,10);
    printf("mapping Tx :"); 
    printf(" %d,", ui8DataBuffer[0]);
    printf(" %d,", ui8DataBuffer[1]);
    printf(" %d,", ui8DataBuffer[2]);
    printf(" %d,", ui8DataBuffer[3]);
    printf(" %d,", ui8DataBuffer[4]);
    printf(" %d,", ui8DataBuffer[5]);
    printf(" %d,", ui8DataBuffer[6]);
    printf(" %d\n", ui8DataBuffer[7]);
    
    // total chanel Rx
    ui8DataBuffer[0] = 3; 
    I2C_Write(TotalRx_adr, &ui8DataBuffer[0] ,1);
    I2C_Read(TotalRx_adr, &ui8DataBuffer[0] ,1);
    printf("nombre cannaux Rx : %d\n", ui8DataBuffer[0]); 

    // total chanel Tx
    ui8DataBuffer[0] = 4; 
    I2C_Write(TotalTx_adr, &ui8DataBuffer[0] ,1);
    I2C_Read(TotalTx_adr, &ui8DataBuffer[0] ,1);
    printf("nombre cannaux Tx : %d\n", ui8DataBuffer[0]);  
	*/
}

//*****************************************************************************
//
//! Display a snap state change
//!                            
//! If the state of any snap output has changed, then this function can be used
//! to display which Rx/Tx channel has changed status.  
//!                                  
//! \param None
//!                                           
//! \return None
//                                                      
//*****************************************************************************
void IQS5xx::DisplaySnap(void)
{
    uint8_t     ui8Tx, ui8Rx;
    uint16_t    ui16ToggledBits;
    
    for(ui8Tx = 0; ui8Tx < 15; ui8Tx++)
    {
        ui16ToggledBits = ui16PrevSnap[ui8Tx] ^ ui16SnapStatus[ui8Tx];

        for(ui8Rx = 0; ui8Rx < 10; ui8Rx++)
        {
            if(BitIsSet(ui16ToggledBits, ui8Rx))
            {
                if(BitIsSet(ui16SnapStatus[ui8Tx], ui8Rx))
                {
                    printf("Snap set on Rx:");
                }
                else
                {
                    printf("Snap released on Rx:");
                }
                printf(" %d / Tx: %d  channel    \n", ui8Rx, ui8Tx);
            }
        }
    }
}

//*****************************************************************************
//
//! Process the data received
//!                            
//! This function sorts the read bytes from the IQS5xx and prints relevant data 
//! on serial port. 
//! REL_X[n]: Relative X Position of the finger n; n is from (1 to 5)
//! REL_Y[n]: Relative X Position of the finger n; n is from (1 to 5)
//! ABS_X[n]: Absolute X Position of the finger n; n is from (1 to 5)
//! ABS_Y[n]: Absolute Y Position of the finger n; n is from (1 to 5)
//! ui16TouchStrength[n]   : Touch strength of finger n; n is from (1 to 5)
//! ui8Area[n]   : Touch area of finger n; this is number of channels under touch 
//! for a particular finger; 
//! Where 'n' is from (1 to 5)
//!                                  
//! \param None
//!                                           
//! \return None
//                                                      
//*****************************************************************************
uint8_t IQS5xx::Process_XY(void) 
{ 
    uint8_t     i; 
    static uint8_t ui8FirstTouch = 0;
    uint8_t     ui8NoOfFingers;
    uint8_t     ui8SystemFlags[2];
    int16_t     i16RelX[6];
    int16_t     i16RelY[6];
    uint16_t    ui16AbsX[6];
    uint16_t    ui16AbsY[6];
    uint16_t    ui16TouchStrength[6];
    uint8_t     ui8Area[6];
 
    I2C_Read(GestureEvents0_adr, &Data_Buff[0], 44);
	
	Close_Comms();
	
	ui8SystemFlags[0] = Data_Buff[2];
    ui8SystemFlags[1] = Data_Buff[3];
    ui8NoOfFingers = Data_Buff[4];
	
    if((ui8SystemFlags[0] & SHOW_RESET) != 0) {
        AcknowledgeReset(); 
        return 0;
    }

    if((ui8SystemFlags[1] & SNAP_TOGGLE) != 0) {
        DisplaySnap();
        return 0;
    }

    if((Data_Buff[0]) == SINGLE_TAP) {       
        return SINGLE_TAP;
    }
    else if((Data_Buff[1]) == TWO_FINGER_TAP) {
        return TWO_FINGER_TAP+0x20;
    }       

    if(ui8NoOfFingers != 0) 
    {
        if (!(ui8FirstTouch)) {
            ui8FirstTouch = 1;
        }

        switch (Data_Buff[0]) {
            case TAP_AND_HOLD   :   return TAP_AND_HOLD;
            case SWIPE_X_NEG    :   return SWIPE_X_NEG;
            case SWIPE_X_POS    :   return SWIPE_X_POS;
            case SWIPE_Y_POS    :   return SWIPE_Y_POS;
            case SWIPE_Y_NEG    :   return SWIPE_Y_NEG;
        }

        switch (Data_Buff[1]) {
            case SCROLL         :   return SCROLL+0x20;
            case ZOOM           :   return ZOOM+0x20;
        }
    } 
    else 
    {
        ui8FirstTouch = 0;
    }
	
	return 0;
}

//*****************************************************************************
//
//! Process the data received
//!                            
//! This function sorts the read bytes from the IQS5xx and prints relevant data 
//! on serial port. 
//! REL_X[n]: Relative X Position of the finger n; n is from (1 to 5)
//! REL_Y[n]: Relative X Position of the finger n; n is from (1 to 5)
//! ABS_X[n]: Absolute X Position of the finger n; n is from (1 to 5)
//! ABS_Y[n]: Absolute Y Position of the finger n; n is from (1 to 5)
//! ui16TouchStrength[n]   : Touch strength of finger n; n is from (1 to 5)
//! ui8Area[n]   : Touch area of finger n; this is number of channels under touch 
//! for a particular finger; 
//! Where 'n' is from (1 to 5)
//!                                  
//! \param None
//!                                           
//! \return None
//                                                      
//*****************************************************************************
uint8_t IQS5xx::getGesture(void) {
	
    uint8_t     ui8NoOfFingers;
    uint8_t     ui8SystemFlags[2];
    int16_t     i16RelX;
    int16_t     i16RelY;

    I2C_Read(GestureEvents0_adr, &Data_Buff[0], 44);
	
	Close_Comms();
	
	ui8SystemFlags[0] = Data_Buff[2];
    ui8SystemFlags[1] = Data_Buff[3];
    ui8NoOfFingers = Data_Buff[4];
	
	i16RelX = ((Data_Buff[5] << 8) | (Data_Buff[6]));
	i16RelY = ((Data_Buff[7] << 8) | (Data_Buff[8]));
	
    if((ui8SystemFlags[0] & SHOW_RESET) != 0) {
        AcknowledgeReset(); 
        return 0;
    }

    if((ui8SystemFlags[1] & SNAP_TOGGLE) != 0) {
        DisplaySnap();
        return 0;
    }

    if((Data_Buff[0]) == SINGLE_TAP) {       
        return SINGLE_TAP;
    }
    else if((Data_Buff[1]) == TWO_FINGER_TAP) {
        return TWO_FINGER_TAP+0x20;
    }       

    if(ui8NoOfFingers != 0) 
    {
 

        switch (Data_Buff[0]) {
            case TAP_AND_HOLD   :   return TAP_AND_HOLD;
            case SWIPE_X_NEG    :   return SWIPE_X_NEG;
            case SWIPE_X_POS    :   return SWIPE_X_POS;
            case SWIPE_Y_POS    :   return SWIPE_Y_POS;
            case SWIPE_Y_NEG    :   return SWIPE_Y_NEG;
        }

        switch (Data_Buff[1]) {
            case SCROLL         :   if(i16RelX < 0) {
										return SCROLL+0x10; // Horizontal Scroll -
									}
									else if(i16RelX > 0) {
										return SCROLL+0x20; // Horizontal Scroll +
									}
									else if(i16RelY < 0) {
										return SCROLL+0x30; // Vertical Scroll -
									}
									else if(i16RelY > 0) {
										return SCROLL+0x40; // Vertical Scroll +
									}
			
            case ZOOM           :   if(i16RelX > 0) {
										return ZOOM+0x10; // Zoom In
									}
									else {
										return ZOOM+0x20; // Zoom Out
									}
        }
    } 

	return 0;
	
}

//*****************************************************************************
//
//! Terminate communication window
//!                            
//! The IQS5xx B000 does not close the communication window on the reception of 
//! the STOP bit; therefore this function sends the END COMMUNICATION WINDOW 
//! COMMAND (Please see datasheet for more information). RDY will go low after 
//! receiving any write to 0xEEEE followed by a STOP. 
//!                                  
//! \param None
//!                                           
//! \return None
//                                                      
//*****************************************************************************
void IQS5xx::Close_Comms() {
	
  uint8_t ui8DataBuffer[1];
  
  I2C_Write(END_WINDOW, &ui8DataBuffer[0], 1);
}

//*****************************************************************************
//
//! I2C write function
//!
//! This function writes the provided data to the address specified.  If  
//! anything in the write process is not successful, then it will be repeated
//! up till four more times.  If still not successful, it will write an error
//! message on the serial terminal.
//!
//! \param ui16RegisterAddress is the 16-bit memory map address on the IQS5xx
//! \param pData is a pointer to the first byte of a block of data to write
//! \param ui8NoOfBytes indicates how many bytes of data to write
//!
//! \return Boolean indicating success/fail of write attempt
//
//*****************************************************************************
uint8_t IQS5xx::I2C_Write(uint16_t ui16RegisterAddress, uint8_t *pData, uint8_t ui8NoOfBytes) {
    
    uint8_t ui8Retry = 4;
    
    ui8Success = I2C_Write2(ui16RegisterAddress, pData, ui8NoOfBytes);
    
    //
    // If comms was not successful, retry 4 more times
    //
    while((!ui8Success) && (ui8Retry != 0)) {
        delay(5);
        ui8Success = I2C_Write2(ui16RegisterAddress, pData, ui8NoOfBytes);
        ui8Retry--;
    }
    
    if(ui8Success) return(true);
    else {
        //printf("Comms write error\n");
        return(false);
    }
}

//*****************************************************************************
//
//! I2C read function
//!
//! This function reads data from the address specified and stores this data
//! in the area provided by the pointer.  If anything in the read process is 
//! not successful, then it will be repeated up till four more times.  
//! If still not successful, it will write an error message on the serial 
//! terminal.
//!
//! \param ui16RegisterAddress is the 16-bit memory map address on the IQS5xx
//! \param pData is a pointer to where the read data must be stored
//! \param ui8NoOfBytes indicates how many bytes of data to read
//!
//! \return Boolean indicating success/fail of read attempt
//
//*****************************************************************************
uint8_t IQS5xx::I2C_Read(uint16_t ui16RegisterAddress, uint8_t *pData, uint8_t ui8NoOfBytes) {
    
    uint8_t ui8Retry = 4;
    
    ui8Success = I2C_Read2(ui16RegisterAddress, pData, ui8NoOfBytes);
    
    //
    // If comms was not successful, retry 4 more times
    //
    while((!ui8Success) && (ui8Retry != 0)) {
        delay(5);
        ui8Success = I2C_Read2(ui16RegisterAddress, pData, ui8NoOfBytes);
        ui8Retry--;
    }
    
    if(ui8Success) return(true);
    else {
        //printf("Comms read error\n");
        return(false);
    }
}

uint8_t IQS5xx::I2C_Write2(uint16_t ui16RegisterAddress, uint8_t *pData, uint8_t ui8NoOfBytes) {
 
	Wire.beginTransmission(_deviceAddress);
	Wire.write(ui16RegisterAddress>>8);
	Wire.write(ui16RegisterAddress);
	
	for(uint8_t i = 0; i < ui8NoOfBytes; i++) {
		Wire.write(*pData);
		pData++;
	}
	uint8_t result = Wire.endTransmission();
    
    return result == 0 ? 1 : 0;
}

uint8_t IQS5xx::I2C_Read2(uint16_t ui16RegisterAddress, uint8_t *pData, uint8_t ui8NoOfBytes) {
    
	uint8_t i;
    int adr = _deviceAddress;
	int nbr = ui8NoOfBytes;
    
    if(ui8NoOfBytes == 0) {
		ui8NoOfBytes++;
	}
	
	Wire.beginTransmission(_deviceAddress);
	Wire.write(ui16RegisterAddress>>8);
	Wire.write(ui16RegisterAddress);
	uint8_t result = Wire.endTransmission(RESTART);
	
	do {
		Wire.requestFrom(adr, nbr, 1);
	}while(Wire.available() == 0);  // Wait for response, this sometimes takes a few attempts

	while(Wire.available())
	{
		// Load the received bytes into the user supplied array
		*pData = Wire.read();
		pData++;
	
	}

    return result == 0 ? 1 : 0;
}
