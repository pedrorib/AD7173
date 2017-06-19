/*
=================================================
example to configure and get data from AD7173 ADC
=================================================
*/
#include <SPI.h>
#include "AD7173.h"

union mv{
  unsigned long int valor;
  byte data[3];
};

double soma=0;
mv med;
byte data_aux[3];

void setup() {
       /* initiate serial communication */
	Serial.begin(9600);
        //SPI.setClockDivider(SPI_CLOCK_DIV128);
	/* initiate ADC, returns true if the device ID is valid */
	AD7173.init();
//SPI.setClockDivider(SPI_CLOCK_DIV128);


	/* reset ADC registers to the default state */
	AD7173.reset();

	/* set ADC configuration */
	/* enable channel 0 and channel 1 and connect each to 2 analog inputs for bipolar input */
	/* CH0 - CH15 */
	/* AIN0 - AIN16, REF_POS, REF_NEG, TEMP_SENSOR_POS, TEMP_SENSOR_NEG */
	AD7173.enable_channel(CH0, true, AIN1,REF_NEG);
        data_aux[0]=0x80; //MSB
        data_aux[1]=0x36; //LSB
        AD7173.write_register_public(0x10,data_aux,2);
//	AD7173.enable_channel(CH1, true, AIN2, AIN3);

	/* set the ADC filter samplingrate to 1007 Hz*/
	/* FILTER0 - FILTER7 */
	/* SPS_1, SPS_2, SPS_5, SPS_10, SPS_16, SPS_20, SPS_50, SPS_60, SPS_100, SPS_200 */
	/* SPS_381, SPS_504, SPS_1007, SPS_2597, SPS_5208, SPS_10417, SPS_15625, SPS_31250 */
	AD7173.set_filter_speed(FILTER0, SPS_1007);
	/* set the ADC setup coding to BIPLOAR output*/
	/* SETUP0 - SETUP7 */
	/* BIPOLAR, UNIPOLAR */
	//AD7173.set_setup_coding_mode(SETUP0, UNIPOLAR);
        data_aux[0]=0x00; //MSB
        data_aux[1]=0x00; //LSB
        AD7173.write_register_public(0x20,data_aux,2);
	/* set the ADC data mode */
	/* CONTINUOUS_READ_MODE, SINGLE_CONVERSION_MODE, CONTINUOUS_CONVERSION_MODE */
	AD7173.set_data_mode(CONTINUOUS_CONVERSION_MODE);

	/* set the ADC clock mode */
	/* INTERNAL_CLOCK, INTERNAL_CLOCK_OUTPUT, EXTERNAL_CLOCK_INTPUT, EXTERNAL_CLOCK */
	AD7173.set_clock_mode(INTERNAL_CLOCK);

	/* wait for ADC */
	//delay(10);
                AD7173.resync();
		//AD7173.read_register_public(0x07,data_aux,1);
}

/* ADC conversion data */
void loop() {
	if (DATA_READY) {
		/* get ADC conversion result */
		AD7173.get_data(data_aux);

		/* send result via serial */
		//Serial.print(data_aux[0], HEX);
		//Serial.print(data_aux[1], HEX);
		//Serial.println(data_aux[2], HEX);
		delay(10);
}

med.data[0]=data_aux[2];
med.data[1]=data_aux[1];
med.data[2]=data_aux[0];

soma=(double)5*(double)med.valor/(double)16777216;

Serial.println(soma,9);

}
