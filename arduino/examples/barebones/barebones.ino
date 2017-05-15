#include "AD7173.h"
#include <SPI.h>

byte data_aux[3];

union mv{
  long int valor;
  byte data[3];
};

mv med;
double soma; 
void setup(){
  Serial.begin(9600);
SPI.begin();
//SPI.setDataMode(SPI_MODE3);
//SPI.setClockDivider(SPI_CLOCK_DIV128);
AD7173.reset();
  AD7173.resync();
digitalWrite(SS,LOW);

delay(2);
}
void loop() {  
  delay(100);
  AD7173.resync();
  //AD7173.reset();
  //AD7173.read_register_public(0x07,data_aux,1);
  AD7173.read_register_public(0x07,data_aux,3);
  med.data[0]=data_aux[2];
  med.data[1]=data_aux[1];
  med.data[2]=data_aux[0];
  Serial.print(data_aux[0],HEX);
  Serial.print(" ");
  Serial.print(data_aux[1],HEX),
  Serial.print(" ");
  Serial.println(data_aux[2],HEX);
  //Serial.println(med.valor);
  //soma=(double)med.valor/(double)16777216*(double)5;
  //Serial.println(soma,9);
}
