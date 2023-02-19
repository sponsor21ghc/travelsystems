// Transmitter Code


/*
 * Arduino Wireless Communication Tutorial
 *  Example 1 - Transmitter Code
 *  
 *  by Dejan Nedelkovski, www.howtomechatronics.com
 *  
 * Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
 *
*/

#include <SPI.h>
#include <nRF24L01.h>
/*#include <printf.h>   */
#include <RF24.h>
#include <RF24_config.h>

#define CE_PIN 7
#define CSN_PIN 8

#define INTERVAL_MS_TRANSMISSION 250

RF24 radio(CE_PIN,CSN_PIN); // CE, CSN

const byte address[6] = "00001";

int plinsky = A3;  // potentiometer wiper (middle terminal) connected to analog pin 3
                   // outside leads to gnd and +5
int val = 0;
String conval = "";

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(115200);
  Serial.begin(9600);
  radio.begin();
  radio.setAutoAck(1);
  radio.setPALevel(RF24_PA_MAX);
  //radio.setDataRate(RF24_2MBPS);
  radio.openWritingPipe(address);
  radio.stopListening();
  //delay(INTERVAL_MS_TRANSMISSION);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(plinsky);
  int conval = val;
  //conval = String(val, DEC);
  //int conval = 320;
  //Serial.println(conval);
  const char text[] = "billskibillskibillski";
  radio.write(&conval, sizeof(conval));
  //radio.write(&text, sizeof(text), 1);

  Serial.println(conval);
  //Serial.println(conval);
  delay(INTERVAL_MS_TRANSMISSION);
  //delay(5000);
}
