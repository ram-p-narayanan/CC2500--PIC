#include <18F24J11.h>
#include <Display.h>
#include <ccrx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int32 in,letter[10];
static int32 num[10],size;
static int i;

void display(int32 number)
{
    int i = 0;
    while (number!=0)
    {
    letter[i] = number % 10;
    i++;
    number = number/10;
    }
    for(;i<=5;i++) letter[i] = 15;
    
    for (i = 0; i < 6; i++)
    {
        Enable(i+1);
        Write(letter[i]);
        Disable_All();
        delay_ms(2);
    }
    Disable_All();
    Data_Lines_Init();
    
    for(int d=0;d<6;d++)
    {
        letter[d] = 0;
    }
}

void main()
{
    delay_us(100);
    printf("\nStart\n");
    output_high(SPI_SS);  // Initial Slave Select to a high level
    setup_spi(SPI_MASTER | SPI_MODE_0 | SPI_CLK_DIV_64);
    output_low(SPI_SS);
    output_low(PIN_B0);
    set_tris_b(PIN_B0);
    CC_SetIdleMode();
    CC_Initial_Check();
    CC_WriteRFSettings();
    CC_SetIdleMode();
    TI_CC_SPIWriteReg(TI_CCxxx0_FSCTRL1,  0x0B);  // Freq synthesizer control.
    TI_CC_SPIWriteReg(TI_CCxxx0_MDMCFG2,  0x83);  // Modem configuration.
    TI_CC_SPIWriteReg(TI_CCxxx0_DEVIATN,  0x44);  // Modem dev (when FSK mod en)
    //GetUserInput();
    CC_CheckNoOfBytesinRXFIFO();
    CC_SetReceiveModeMode();
    delay_ms(1);
    
    uC_Init();
    GPIO_Init();
    delay_ms(500);
    Data_Lines_Init();
    EnablenBlank();
    delay_ms(500);
    while(1)
    {
        output_low(SPI_SS); //delay_us(100);
        spi_write(NUMBER_RXBYTES_IN_FIFO);
        ReceiveValue = spi_read(DUMMY);
        //delay_ms(10);
        if(ReceiveValue)
        {
            printf("\nCheck1\n");
            spi_write(RSSI);
            RxSignalStrength = spi_read(DUMMY);
            spi_write(LQI);
            LinkQIndicator = spi_read(DUMMY);
            delay_us(5);
            for(Temp =  0; Temp < ReceiveValue; Temp++)
            {
                delay_us(100);
                spi_write(RX_FIFO);
                ReceiveData[Temp] = spi_read(DUMMY);
                if(ReceiveData[Temp]=='*')
                {
                    ReceiveData[Temp] = '\0';
                    break;
                }
            }
            printf("Received Value is %s \r", ReceiveData);
            
            for (i = 0; i < 6 && Temp!=0; i++)
            {
                ReceiveData1[i] = ReceiveData[Temp-1];
                Temp--;
            }
            ReceiveData1[i] = '\0';
            
            for(int d=0;d<6;d++)
            {
                num[d] = 0;
                ReceiveData[d] = 0;
            }
            
            for(int c=0;c<6;c++)
            {
                num[c] = ReceiveData1[c] - 48;
                if((num[c]<0) || (num[c]>9)) num[c] = 0;
            }
            
            for(int e=0;e<6;e++)
            {
                ReceiveData1[e] = 0;
            } 
        
            in = num[0]+(num[1]*10)+(num[2]*100)+(num[3]*1000)+(num[4]*10000)+(num[5]*100000);
            
            printf("Number is %ld \r", in);
            display(in);
        }
        spi_write(SIDLE);
        delay_us(1);
        spi_write(SFRX);
        delay_us(1);
        spi_write(SRX);
        delay_us(1);
        output_high(SPI_SS);
        delay_ms(195);
        
    }
}