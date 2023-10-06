#ifndef SYSTEM_H
#define SYSTEM_H
////////////////////////////////////////////////////////////////////////////////
//==============================================================================
//    				Tiino Research Labs, Coimbatore 
//==============================================================================
// Project   :  PIC Mote Coding for Sensirion sensor interface
// File      :  System.h
// Author    :  Ram Prasadh Narayanan
// Controller:  PIC16F8x
// Brief     :  System functions, global definitions
//==============================================================================
////////////////////////////////////////////////////////////////////////////////


//---------- Includes ----------------------------------------------------------

#include <assert.h>                // assert functions
#include <intrinsics.h>            // low level microcontroller commands
#include "typedefs.h"              // type definitions

//---------- Enumerations ------------------------------------------------------
// Error codes
typedef enum{
  ACK_ERROR                = 0x01,
  TIME_OUT_ERROR           = 0x02,
  CHECKSUM_ERROR           = 0x04,
  UNIT_ERROR               = 0x08
}etError;

//==============================================================================
void Init_HW (void);
//==============================================================================
// Initializes the used hardware

//==============================================================================
void DelayMicroSeconds (u32t nbrOfUs);
//==============================================================================
// wait function for small delays
// input:  nbrOfUs   wait x times approx. one micro second (fcpu = 4MHz)
// return: -
// note: smallest delay is approx. 30us due to function call

#endif

//********************************************************************************
//**                      Revision History                                      **
//********************************************************************************
//** Revision    Date            By                    Description              **
//********************************************************************************
//**  1.0.0    26-08-14     Ram Prasadh N             Initial version           **
//********************************************************************************