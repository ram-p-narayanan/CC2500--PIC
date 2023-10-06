
static int16 Timer1_Flag;
float restemp, truehumid;
static int32 Value_To_Be_Sent;
static int32 in, n, len, rem, num;
static int i, j;

void Send_to_Tx();
void Send_to_Tx()
{
    Value_To_Be_Sent = (int32) restemp;
    in = Value_To_Be_Sent;
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
    else
        printf("\nNot Valid\n");
}