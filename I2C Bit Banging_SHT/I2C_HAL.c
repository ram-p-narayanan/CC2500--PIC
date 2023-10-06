////////////////////////////////////////////////////////////////////////////////
//==============================================================================
//    				Tiino Research Labs, Coimbatore 
//==============================================================================
// Project   :  PIC Mote Coding for Sensirion sensor interface
// File      :  I2C_HAL
// Author    :  Ram Prasadh Narayanan
// Controller:  PIC16F8x
// Brief     :  I2C routine for initialization and reading of data from 
//				temperature and Humidity Sensor
//==============================================================================
////////////////////////////////////////////////////////////////////////////////

//---------- Includes ----------------------------------------------------------
#include "I2C_HAL.h"

//==============================================================================
void I2c_Init ()
//==============================================================================
{
  SDA=LOW;                									// Set port as output for configuration
  SCL=LOW;                									// Set port as output for configuration

  SDA_TRIS=LOW;           									// Set SDA level as low for output mode
  SCL_TRIS=LOW;           									// Set SCL level as low for output mode

  SDA=HIGH;               									// I2C-bus idle mode SDA released (input)
  SCL=HIGH;               									// I2C-bus idle mode SCL released (input)
}

//==============================================================================
void I2c_StartCondition ()
//==============================================================================
{
  SDA=HIGH;
  SCL=HIGH;
  SDA=LOW;
  DelayMicroSeconds(10);  									// hold time start condition (t_HD;STA)
  SCL=LOW;
  DelayMicroSeconds(10);
}

//==============================================================================
void I2c_StopCondition ()
//==============================================================================
{
  SDA=LOW;
  SCL=LOW;
  SCL=HIGH;
  DelayMicroSeconds(10);  									// set-up time stop condition (t_SU;STO)
  SDA=HIGH;
  DelayMicroSeconds(10);
}

//==============================================================================
u8t I2c_WriteByte (u8t txByte)
//==============================================================================
{
  u8t mask,error=0;
  for (mask=0x80; mask>0; mask>>=1)   						//shift bit for masking (8 times)
  { if ((mask & txByte) == 0) SDA=LOW;						//masking txByte, write bit to SDA-Line
    else SDA=HIGH;
    DelayMicroSeconds(1);             						//data set-up time (t_SU;DAT)
    SCL=HIGH;                         						//generate clock pulse on SCL
    DelayMicroSeconds(5);             						//SCL high time (t_HIGH)
    SCL=LOW;
    DelayMicroSeconds(1);             						//data hold time(t_HD;DAT)
  }
  SDA=HIGH;                           						//release SDA-line
  SCL=HIGH;                           						//clk #9 for ack
  DelayMicroSeconds(1);               						//data set-up time (t_SU;DAT)
  if(SDA_TRIS==HIGH) error=ACK_ERROR; 						//check ack from i2c slave
  SCL=LOW;
  DelayMicroSeconds(20);              						//wait time to see byte package on scope
  return error;                       						//return error code
}

//==============================================================================
u8t I2c_ReadByte (etI2cAck ack)
//==============================================================================
{
  u8t mask,rxByte=0;
  SDA=HIGH;                           						//release SDA-line
  for (mask=0x80; mask>0; mask>>=1)   						//shift bit for masking (8 times)
  { SCL=HIGH;                         						//start clock on SCL-line
    DelayMicroSeconds(1);             						//data set-up time (t_SU;DAT)
    DelayMicroSeconds(3);            						//SCL high time (t_HIGH)
    if (SDA_TRIS==1) rxByte=(rxByte | mask); 				//read bit
    SCL=LOW;
    DelayMicroSeconds(1);             						//data hold time(t_HD;DAT)
  }
  SDA=ack;                            						//send acknowledge if necessary
  DelayMicroSeconds(1);               						//data set-up time (t_SU;DAT)
  SCL=HIGH;                           						//clk #9 for ack
  DelayMicroSeconds(5);               						//SCL high time (t_HIGH)
  SCL=LOW;
  SDA=HIGH;                           						//release SDA-line
  DelayMicroSeconds(20);              						//wait time to see byte package on scope
  return rxByte;                      						//return error code
}

//********************************************************************************
//**                      Revision History                                      **
//********************************************************************************
//** Revision    Date            By                    Description              **
//********************************************************************************
//**  1.0.0    26-08-14     Ram Prasadh N             Initial version           **
//********************************************************************************


