#include <18F24J11.h>
#include <stdlib.h>
#include <stdio.h>
#include <Wireless.h>
#include <string.h>

/*This Program is used for the Basic Transmitting function implementation in the Tiino Mote
We can vary the RF Settings appropriately for usage in different KBaud, Rx Sensitivity,
Data Whitening etc. The Back-Up original code is present in C:\Users\ram\Desktop\TiinoMote_Programs_Backup
*/
static int32 in, letter[10], n, len, rem, num;
static int i, j;

void main()
{

    printf("Start Of Operation \r");
    setup_adc_ports(ADC_OFF);
    setup_adc(NO_ANALOGS);
    setup_adc(ADC_OFF);
    set_tris_b(0x00);
    output_low(PIN_B1);
    output_low(PIN_B2);
    output_low(PIN_B3);
    output_high(SPI_SS);  // Initial Slave Select to a high level
    setup_spi(SPI_MASTER | SPI_MODE_0 | SPI_CLK_DIV_64);
    CC_SetIdleMode();
    CC_WriteRFSettings();
    output_high(PIN_B1);

    while(TRUE)
    {
        
        in = rand() % 1000000;
        n = in;
        num = in;
        while (n != 0)
        {
            len++;
            n /= 10;
        }
        for(j = 0; j < len; j++)
        {
            rem = num % 10;
            num = num / 10;
            TransmitData[len-(j+1)] = rem+'0';
        }
        TransmitData[len] = '*';
        TransmitData[len+1] = '\0';
        len = 0;
        printf("\nString is : %s\n",TransmitData);
        while(1);
        if(in >= 0 && in < 1000000)
        {
            for(i = 0;i < 1; i++)
            {
                output_high(SPI_SS);  // Initial Slave Select to a high level
                setup_spi(SPI_MASTER | SPI_MODE_0 | SPI_CLK_DIV_64);
                output_low(SPI_SS);
                CC_SetIdleMode();
                CC_Initial_Check();
                CC_ClearTransmitFIFO();
                CC_TransmitData();
                CC_CheckNoOfBytesinTXFIFO();
                CC_SetTransmitModeMode();
                delay_ms(200);
            }
        }
        else printf("\nNot Valid\n");
    }
}


