#define sht_data_pin   PIN_A2
#define sht_clk_pin    PIN_A3

void comstart (void)
{
    output_float(sht_data_pin);  //data high
    output_bit(sht_clk_pin, 0);     delay_us(1);  //clk low
    output_bit(sht_clk_pin, 1);     delay_us(1);  //clk high
    output_bit(sht_data_pin, 0);    delay_us(1);  //data low
    output_bit(sht_clk_pin, 0);     delay_us(2);  //clk low
    output_bit(sht_clk_pin, 1);     delay_us(1);  //clk high
    output_float(sht_data_pin);     delay_us(1);  //data high
    output_bit(sht_clk_pin, 0);                   //clk low
}

//***** Function to write data to SHT11 *****

int1 comwrite (int8 iobyte)
{
    int8 i, mask = 0x80;
    int1 ack;
    //Shift out command
    delay_us(4);
    for(i=0; i<8; i++)
    {
        output_bit(sht_clk_pin, 0);                 //clk low
        if((iobyte & mask) > 0)
            output_float(sht_data_pin);             //data high if MSB high
        else
            output_bit(sht_data_pin, 0);            //data low if MSB low
        delay_us(1);
        output_bit(sht_clk_pin, 1);                 //clk high
        delay_us(1);
        mask = mask >> 1;                           //shift to next bit
    }
    //Shift in ack
    output_bit(sht_clk_pin, 0);                     //clk low
    delay_us(1);
    ack = input(sht_data_pin);                      //get ack bit
    output_bit(sht_clk_pin, 1);                     //clk high
    delay_us(1);
    output_bit(sht_clk_pin, 0);                     //clk low
    return(ack);
}

//***** Function to read data from SHT11 *****

int16 comread (void)
{
    int8 i;
    int16 iobyte = 0;
    const int16 mask0 = 0x0000;
    const int16 mask1 = 0x0001;
    //shift in MSB data
    for(i=0; i<8; i++)
    {
        iobyte = iobyte << 1;
        output_bit(sht_clk_pin, 1);                 //clk high
        delay_us(1);
        if (input(sht_data_pin))
            iobyte |= mask1;                        //shift in data bit
        else
            iobyte |= mask0;
        output_bit(sht_clk_pin, 0);                 //clk low
        delay_us(1);
    }
     //send ack 0 bit
    output_bit(sht_data_pin, 0);                    //data low
    delay_us(1);
    output_bit(sht_clk_pin, 1);                     //clk high
    delay_us(2);
    output_bit(sht_clk_pin, 0);                     //clk low
    delay_us(1);
    output_float(sht_data_pin);                     //data high
     //shift in LSB data
    for(i=0; i<8; i++)
    {
        iobyte = iobyte << 1;
        output_bit(sht_clk_pin, 1);                 //clk high
        delay_us(1);
        if (input(sht_data_pin))
            iobyte |= mask1;                        //shift in data bit
        else
            iobyte |= mask0;
        output_bit(sht_clk_pin, 0);                 //clk low
        delay_us(1);
    }
    //send ack 1 bit
    output_float(sht_data_pin);                     //data high
    delay_us(1);
    output_bit(sht_clk_pin, 1);                     //clk high
    delay_us(2);
    output_bit(sht_clk_pin, 0);                     //clk low
    return(iobyte);
}

//***** Function to wait for SHT11 reading *****

void comwait (void)
{
    int16 sht_delay;
    output_float(sht_data_pin);                     //data high
    output_bit(sht_clk_pin, 0);                     //clk low
    delay_us(1);
    for(sht_delay=0; sht_delay<30000; sht_delay++)  // wait for max 300ms
    {
        if (!input(sht_data_pin)) break;            //if sht_data_pin low, SHT75 ready
        delay_us(10);
    }
}

//***** Function to reset SHT11 communication *****

void comreset (void)
{
    int8 i;
    output_float(sht_data_pin);                     //data high
    output_bit(sht_clk_pin, 0);                     //clk low
    delay_us(2);
    for(i=0; i<9; i++)
    {
        output_bit(sht_clk_pin, 1);                 //toggle clk 9 times
        delay_us(2);
        output_bit(sht_clk_pin, 0);
        delay_us(2);
    }
    comstart();
}

//***** Function to soft reset SHT11 *****

void sht_soft_reset (void)
{
    comreset();                                     //SHT11 communication reset
    comwrite(0x1e);                                 //send SHT11 reset command
    delay_ms(15);                                   //pause 15 ms
}

//***** Function to measure SHT11 temperature *****

int16 measuretemp (void)
{
    int1 ack;
    int16 iobyte;
    comstart();                                     //alert SHT11
    ack = comwrite(0x03);                           //send measure temp command and read ack status
    if(ack == 1)
        return;
    comwait();                                      //wait for SHT11 measurement to complete
    iobyte = comread();                             //read SHT11 temp data
    return(iobyte);
}

//***** Function to measure SHT11 RH *****

int16 measurehumid (void)
{
    int1 ack;
    int16 iobyte;
    comstart();                                     //alert SHT11
    ack = comwrite(0x05);                           //send measure RH command and read ack status
    if(ack == 1)
        return;
    comwait();                                      //wait for SHT11 measurement to complete
    iobyte = comread();                             //read SHT11 temp data
    return(iobyte);
}

//***** Function to calculate SHT11 temp & RH *****

void calculate_data (int16 temp, int16 humid, float & tc, float & rhlin, float & rhtrue)
{
    float rh;
    //calculate temperature reading
    tc = ((float) temp * 0.01) - 40.0;
    //calculate Real RH reading
    rh = (float) humid;
    rhlin = (rh * 0.0405) - (rh * rh * 0.0000028) - 4.0;
    //calculate True RH reading
    rhtrue = ((tc - 25.0) * (0.01 + (0.00008 * rh))) + rhlin;
}

//***** Function to measure & calculate SHT11 temp & RH *****

void sht_rd (float & temp, float & truehumid)
{
    int16 restemp, reshumid;
    float realhumid;
    restemp = 0; truehumid = 0;
    restemp = measuretemp();                                //measure temp
    reshumid = measurehumid();                              //measure RH
    calculate_data (restemp, reshumid, temp, realhumid, truehumid);  //calculate temp & RH
}
