#include "AD7173.h"
#include <SPI.h>

byte data_aux[3];

union mv{
  long int valor;
  byte data[3];
};

mv med;
double soma; 
byte LSB, MSB;
void setup(){
  Serial.begin(9600);
SPI.begin();
//SPI.setDataMode(SPI_MODE3);
//SPI.setClockDivider(SPI_CLOCK_DIV128);


AD7173.resync();
AD7173.read_register_public(0x07,data_aux,2);
if (data_aux[0]==0x30 && data_aux[1]==0xD5){
  Serial.println("ID verified!");
      Serial.print("ID value read (expected 0x30 0xD5): ");
    Serial.print(data_aux[0],HEX);
    Serial.print(" ");
    Serial.println(data_aux[1],HEX);
  delay(1000);
}
else{
  while(1){
    Serial.println("ID verification failed!");
    Serial.print("ID value read (expected 0x30 0xD5): ");
    Serial.print(data_aux[0],HEX);
    Serial.print(" ");
    Serial.println(data_aux[1],HEX);
    delay(2000);
  }
}

AD7173.reset();

AD7173.read_register_public(0x20,data_aux,2);

  Serial.print("Value read (expected 0x10 0x00): ");
  Serial.print(data_aux[0],HEX);
  Serial.print(" ");
  Serial.println(data_aux[1],HEX);

AD7173.resync();

  MSB=0x20;
LSB=0x16;

data_aux[0]=MSB; 
data_aux[1]=LSB;
  
  AD7173.write_register_public(0x10,data_aux,2);

AD7173.read_register_public(0x10,data_aux,2);

  Serial.print("Value written (expected 0x20 0x16): ");
  Serial.print(data_aux[0],HEX);
  Serial.print(" ");
  Serial.println(data_aux[1],HEX);
  delay(2500);

AD7173.write_register_public(0x20,data_aux,2);

MSB=0x00;
LSB=0x00;

data_aux[0]=MSB; 
data_aux[1]=LSB;

AD7173.read_register_public(0x20,data_aux,2);

  Serial.print("Value written (expected 0x10 0x00): ");
  Serial.print(data_aux[0],HEX);
  Serial.print(" ");
  Serial.println(data_aux[1],HEX);
 
digitalWrite(SS,LOW);

delay(2);
}
void loop() {  
  delay(100);
  //AD7173.resync();
  //AD7173.reset();
  //AD7173.set_setup_coding_mode(SETUP0, UNIPOLAR);
  //AD7173.set_data_mode(CONTINUOUS_CONVERSION_MODE);
  //delay(10);
  AD7173.read_register_public(0x04,data_aux,3);
  med.data[0]=data_aux[2];
  med.data[1]=data_aux[1];
  med.data[2]=data_aux[0];
  //Serial.print(data_aux[0],HEX);
  //Serial.print(" ");
  //Serial.print(data_aux[1],HEX),
  //Serial.print(" ");
  //Serial.println(data_aux[2],HEX);
  //Serial.println(med.valor);
  soma=(double)med.valor/(double)16777216*(double)5;
  Serial.println(soma,9);
}
