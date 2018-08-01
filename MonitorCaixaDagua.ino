/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************

  You’ll need:
   - Blynk App (download from AppStore or Google Play)
   - Arduino Mega 2560 board
   - Decide how to connect to Blynk
     (USB, Ethernet, Wi-Fi, Bluetooth, ...)

  There is a bunch of great example sketches included to show you how to get
  started. Think of them as LEGO bricks  and combine them as you wish.
  For example, take the Ethernet Shield sketch and combine it with the
  Servo example, or choose a USB sketch and add a code from SendData
  example.
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <SPI.h>
#include <Ethernet.h>
#include <BlynkSimpleEthernet.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "e2cb9357049c4d4d809194849b240f78";

#define W5100_CS  10
//#define SDCARD_CS 4
const int pinoSensor1 = 8; //constante que define o pino digital 8 como do Sensor1.
const int pinoSensor2 = 9; //constante que define o pino digital 9 como do Sensor2.
const int pinoSensor3 = 10; //constante que define o pino digital 10 como do Sensor3.
const int pinoSensor4 = 11; //constante que define o pino digital 11 como do Sensor4.
const int pinoSensor5 = 12; //constante que define o pino digital 12 como do Sensor5.
int estadoSensor1 = 0; //Variável que conterá os estados do Sensor1 (0 LOW, 1 HIGH).
int estadoSensor2 = 0; //Variável que conterá os estados do Sensor2 (0 LOW, 1 HIGH).
int estadoSensor3 = 0; //Variável que conterá os estados do Sensor3 (0 LOW, 1 HIGH).
int estadoSensor4 = 0; //Variável que conterá os estados do Sensor4 (0 LOW, 1 HIGH).
int estadoSensor5 = 0; //Variável que conterá os estados do Sensor5 (0 LOW, 1 HIGH).
WidgetLED led1(V1); //registra o led1 no virtual pino 1
WidgetLED led2(V2); //registra o led2 no virtual pino 2
WidgetLED led3(V3); //registra o led3 no virtual pino 3
WidgetLED led4(V4); //registra o led4 no virtual pino 4
WidgetLED led5(V5); //registra o led5 no virtual pino 5

void setup()
{
  // Debug console
  Serial.begin(9600);

  //pinMode(SDCARD_CS, OUTPUT);
  //digitalWrite(SDCARD_CS, HIGH); // Deselect the SD card

  Blynk.begin(auth);
  // You can also specify server:
  //Blynk.begin(auth, "blynk-cloud.com", 80);
  //Blynk.begin(auth, IPAddress(192,168,1,100), 8080);
  pinMode(pinoSensor1,INPUT); //Definindo pino do Sensor1 como de entrada. 
  pinMode(pinoSensor2,INPUT); //Definindo pino do Sensor2 como de entrada. 
  pinMode(pinoSensor3,INPUT); //Definindo pino do Sensor3 como de entrada. 
  pinMode(pinoSensor4,INPUT); //Definindo pino do Sensor4 como de entrada. 
  pinMode(pinoSensor5,INPUT); //Definindo pino do Sensor5 como de entrada. 

  Blynk.run();
  led1.off(); //desligando o led1
  led2.off(); //desligando o led2
  led3.off(); //desligando o led3
  led4.off(); //desligando o led4
  led5.off(); //desligando o led5
  Blynk.virtualWrite(V0, 0);
}

void loop()
{
//  led1.off(); //desligando o led1
//  led2.off(); //desligando o led2
//  led3.off(); //desligando o led3
//  led4.off(); //desligando o led4
//  led5.off(); //desligando o led5
  
  estadoSensor1 = digitalRead(pinoSensor1); //Lendo o estado do pino do Sensor1
  estadoSensor2 = digitalRead(pinoSensor2); //Lendo o estado do pino do Sensor2
  estadoSensor3 = digitalRead(pinoSensor3); //Lendo o estado do pino do Sensor3
  estadoSensor4 = digitalRead(pinoSensor4); //Lendo o estado do pino do Sensor4
  estadoSensor5 = digitalRead(pinoSensor5); //Lendo o estado do pino do Sensor5

  if (estadoSensor1 == HIGH) {
    led1.on(); //Sensor1 fechado, acende o led1.
  } else {
    led1.off(); //Sensor1 aberto, apaga o led1.    
  }       

  if (estadoSensor2 == HIGH) {
    led2.on(); //Sensor1 fechado, acende o led2.
  } else {
    led2.off(); //Sensor1 aberto, apaga o led2.    
  }       

  if (estadoSensor3 == HIGH) {
    led3.on(); //Sensor1 fechado, acende o led3.
  } else {
    led3.off(); //Sensor1 aberto, apaga o led3.    
  }       

  if (estadoSensor4 == HIGH) {
    led4.on(); //Sensor1 fechado, acende o led4.
  } else {
    led4.off(); //Sensor1 aberto, apaga o led4.    
  }       

  if (estadoSensor5 == HIGH) {
    led5.on(); //Sensor1 fechado, acende o led5.
  } else {
    led5.off(); //Sensor1 aberto, apaga o led5.    
  }       
  
  Blynk.virtualWrite(V0, 20*estadoSensor1+20*estadoSensor2+20*estadoSensor3+20*estadoSensor4+20*estadoSensor5);
  delay(500);

//  led1.on(); //ligando o led1
//  led2.on(); //ligando o led2
//  led3.on(); //ligando o led3
//  led4.on(); //ligando o led4
//  led5.on(); //ligando o led5
//  Blynk.virtualWrite(V0, 20);
//  delay(500);
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}

