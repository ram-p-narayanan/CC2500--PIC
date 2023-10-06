#ifndef I2C_HAL_H
#define I2C_HAL_H
////////////////////////////////////////////////////////////////////////////////
//==============================================================================
//    				Tiino Research Labs, Coimbatore 
//==============================================================================
// Project   :  PIC Mote Coding for Sensirion sensor interface
// File      :  I2C_HAL
// Author    :  Ram Prasadh Narayanan
// Controller:  PIC16F8x
// Brief     :  I2C routine Header for initialization and reading of data from 
//				temperature and Humidity Sensor
//==============================================================================
////////////////////////////////////////////////////////////////////////////////

//---------- Includes ----------------------------------------------------------
#include "system.h"

//---------- Defines -----------------------------------------------------------
//I2C ports
//The communication on SDA and SCL is done by switching pad direction
//For a low level on SCL or SDA, direction is set to output. For a high level on
//SCL or SDA, direction is set to input. (pull up resistor active)

#define SDA_TRIS  TRISCbits.TRISC4
#define SCL_TRIS  TRISCbits.TRISC3
#define SDA       PORTCbits.RC4
#define SCL       PORTCbits.RC3

//---------- Enumerations ------------------------------------------------------
//  I2C level
typedef enum{
  LOW                      = 0,
  HIGH                     = 1,
}etI2cLevel;

// I2C acknowledge
typedef enum{
  ACK                      = 0,
  NO_ACK                   = 1,
}etI2cAck;

//==============================================================================
void I2c_Init ();
//==============================================================================
//Initializes the ports for I2C interface

//==============================================================================
void I2c_StartCondition ();
//==============================================================================
// writes a start condition on I2C-bus
// input : -
// output: -
// return: -
// note  : timing (delay) may have to be changed for different microcontroller
//       _____
// SDA:       |_____
//       _______
// SCL :        |___

//==============================================================================
void I2c_StopCondition ();
//==============================================================================
// writes a stop condition on I2C-bus
// input : -
// output: -
// return: -
// note  : timing (delay) may have to be changed for different microcontroller
//              _____
// SDA:   _____|
//            _______
// SCL :  ___|

//===========================================================================
u8t I2c_WriteByte (u8t txByte);
//===========================================================================
// writes a byte to I2C-bus and checks acknowledge
// input:  txByte  transmit byte
// output: -
// return: error
// note: timing (delay) may have to be changed for different microcontroller

//===========================================================================
u8t I2c_ReadByte (etI2cAck ack);
//===========================================================================
// reads a byte on I2C-bus
// input:  rxByte  receive byte
// output: rxByte
// note: timing (delay) may have to be changed for different microcontroller

#endif

//********************************************************************************
//**                      Revision History                                      **
//********************************************************************************
//** Revision    Date            By                    Description              **
//********************************************************************************
//**  1.0.0    26-08-14     Ram Prasadh N             Initial version           **
//********************************************************************************