//  receiver code

/*
 * Arduino Wireless Communication Tutorial
 *  Example 1 - Receiver Code
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

#define INTERVAL_MS_SIGNAL_LOST 1000
#define INTERVAL_MS_SIGNAL_RETRY 250

unsigned long lastSignalMillis = 0;

//int text[] = 0;

RF24 radio(7,8); // CE, CSN

const byte address[6] = "00001";

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(115200);
  Serial.begin(9600);
  radio.begin();

  radio.setAutoAck(1);

  //radio.setDataRate(RF24_2MBPS);
  
  radio.setPALevel(RF24_PA_MAX);

  radio.openReadingPipe(0, address);
  
  radio.startListening();
}

void loop() {  
  // put your main code here, to run repeatedly:
  unsigned long currentMillis = millis();
  //Serial.println("hiski!");
  if (radio.available() > 0){
    //Serial.println("radio available");
    //char text[32] = "";
    int sling = 0;
    //int text = 0;
    radio.read(&sling, sizeof(sling));
    //radio.read(&text, sizeof(text));
    
    Serial.println(sling);

    //delay(40);

    lastSignalMillis = currentMillis;

    if (currentMillis - lastSignalMillis > INTERVAL_MS_SIGNAL_LOST){
      lostConnection();
    }
    //Serial.println("Hi, Mom!");
    //delay(5000);
  }
}

void lostConnection()
{
  Serial.println("We have lost connection, preventing unwanted behavior");

  delay(INTERVAL_MS_SIGNAL_RETRY);
}
    
