#include "spi_header.h"

/********************************************************************
*   Function Name:  OpenSPI1                                        *
*   Return Value:   void                                            *
*   Parameters:     SSP1 peripheral set-up bytes                    *
*   Description:    This function sets up the SSP1 module on a      * 
*                   PIC18Cxxx device for use with a SPI bus device. *
********************************************************************/

void OpenSPI1( unsigned char sync_mode, unsigned char bus_mode, unsigned char smp_phase)
{
  SSP1STAT &= 0x3F;               // power on state 
  SSP1CON1 = 0x00;                // power on state
  SSP1CON1 |= sync_mode;          // select serial mode 
  SSP1STAT |= smp_phase;          // select data input sample phase

  switch( bus_mode )
  {
    case 0:                       // SPI1 bus mode 0,0
      SSP1STATbits.CKE = 0;       // data transmitted on Rising edge
	  SSP1CON1bits.CKP = 0; 		// clock idle state low
      break;    
	case 1:                       // SPI1 bus mode 0,1
      SSP1STATbits.CKE = 0;       // data transmitted on falling edge
	  SSP1CON1bits.CKP = 1;			// clock idle state high
      break;    
    case 2:                       // SPI1 bus mode 1,0
      SSP1STATbits.CKE = 1;       // data transmitted on falling edge
      SSP1CON1bits.CKP = 0;       // clock idle state low
      break;
    default:                      // default SPI1 bus mode 0,1
	  SSP1STATbits.CKE = 1;       // data transmitted on rising edge
      SSP1CON1bits.CKP = 1;       // clock idle state high
      break;
  }
 
		TRISCbits.TRISC3 = 0;       // define clock pin as output
		TRISCbits.TRISC4 = 1;       // define SDI pin as input
	 	TRISCbits.TRISC5 = 0;       // define SDO pin as output
  
	    SS = Disable;
            SSP1CON1 |= SSPENB;             	// enable synchronous serial port
 }