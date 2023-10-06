////////////////////////////////////////////////////////////////////////////////
//==============================================================================
//    				Tiino Research Labs, Coimbatore 
//==============================================================================
// Project   :  PIC Mote Coding for Sensirion sensor interface
// File      :  main.c
// Author    :  Ram Prasadh Narayanan
// Controller:  PIC16F8x
// Brief     :  Main routine for initialization and reading of data from 
//				temperature and Humidity Sensor
//==============================================================================
////////////////////////////////////////////////////////////////////////////////


/* ---------- Includes ---------------------------------------------------------- */
 
// Include files to be added here

#include "SHT2x.h"          								//header file for SHT2x functions
#include <stdio.h>          								//header file standard input / output functions
#include "typedefs.h"              							// type definitions
#include "I2C_HAL.h"
#include "main.h"

/* Main Routine starts here */

int main (void)
{
	u8t  error = 0;              							//variable for error code.
	static u8t  SerialNumber_SHT2x[8];  					//64bit serial number
	nt16 sRH;                    							// variable to store raw humidity data , can vary between 8-bit to 12-bit          
	nt16 sT;					 							// Variable to store raw temperature data,can vary between 11-bit to 14-bit
	ft   humidityRH;             							//variable for relative humidity[%RH] as float
	ft   temperatureC;          							//variable for temperature[°C] as float
	Init_GPIO();      										//initializes Hardware (osc, watchdog,...)  , initializes uC-ports for I2C
	I2c_Init(); 
	DelayMicroSeconds(15000);    							//wait for sensor initialization t_powerUp (15ms)
	
	while(1)
	{
		error = 0;                                       // reset error status
	// Reset the Sensor By Command
		error |= SHT2x_SoftReset();
		if (error) {									// Make an LED indication as of now. 
														// Code may be written here for further improvements
				   }
	// --- Read the sensors serial number (64bit) ---
		error |= SHT2x_GetSerialNumber(SerialNumber_SHT2x);	
		if (error) {									// Make an LED indication as of now. 
														// Code may be written here for further improvements
				   }
	// --- Set Resolution e.g. RH 12bit, Temp 14bit ---
		error |= SHT2x_ReadUserRegister(&userRegister);  //get actual user reg
		userRegister = (userRegister & ~SHT2x_RES_MASK) | SHT2x_RES_12_14BIT;
		error |= SHT2x_WriteUserRegister(&userRegister); //write changed user reg

	// --- measure humidity with "Hold Master Mode (HM)"  ---
		error |= SHT2x_MeasureHM(HUMIDITY, &sRH);
    // --- measure temperature with "Polling Mode" (no hold master) ---
		error |= SHT2x_MeasurePoll(TEMP, &sT);
	//-- calculate humidity and temperature --
		temperatureC = SHT2x_CalcTemperatureC(sT.u16);
		humidityRH   = SHT2x_CalcRH(sRH.u16);
		
    // --- check end of battery status (eob)---
    // note: a RH / Temp. measurement must be executed to update the status of eob
		error |= SHT2x_ReadUserRegister(&userRegister);  //get actual user reg
		if( (userRegister & SHT2x_EOB_MASK) == SHT2x_EOB_ON ) endOfBattery = true;
		else endOfBattery = false;
		if(endOfBattery) { // Indicate the controller module on the battery status.  
		
							}
		sprintf(humitityOutStr,    "Humidity RH:%6.2f %% ",humidityRH);
		sprintf(temperatureOutStr, "Temperature:%6.2f€C",temperatureC);
		
		DelayMicroSeconds(300000);     					// wait 0.3s for next measurement
	}

	return(0);
}

//********************************************************************************
//**                      Revision History                                      **
//********************************************************************************
//** Revision    Date            By                    Description              **
//********************************************************************************
//**  1.0.0    26-08-14     Ram Prasadh N             Initial version           **
//********************************************************************************
