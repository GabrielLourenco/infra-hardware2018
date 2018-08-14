#define BLYNK_PRINT Serial


#include <SPI.h>
#include <Ethernet.h>
#include <BlynkSimpleEthernet.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "78177ea4b1c044be83be484f66d977e6";

#define W5100_CS  10

const int pinoSensor1 = 2; //constante que define o pino digital 8 como do Sensor1.
const int pinoSensor2 = 3; //constante que define o pino digital 8 como do Sensor1.
const int pinoSensor3 = 4; //constante que define o pino digital 8 como do Sensor1.
const int pinoSensor4 = 5; //constante que define o pino digital 8 como do Sensor1.
const int pinoSensor5 = 6; //constante que define o pino digital 8 como do Sensor1.

int estadoSensor1 = 0; //Variável que conterá os estados do Sensor1 (0 LOW, 1 HIGH).
int estadoSensor2 = 0; //Variável que conterá os estados do Sensor1 (0 LOW, 1 HIGH).
int estadoSensor3 = 0; //Variável que conterá os estados do Sensor1 (0 LOW, 1 HIGH).
int estadoSensor4 = 0; //Variável que conterá os estados do Sensor1 (0 LOW, 1 HIGH).
int estadoSensor5 = 0; //Variável que conterá os estados do Sensor1 (0 LOW, 1 HIGH).

int estadoLed1 = 1; //Variável que conterá os estados do Sensor1 (0 LOW, 1 HIGH).

long lastTime1 = 0;
long lastTime2 = 0;

WidgetLED led1(V1); //register to virtual pin
WidgetLED led2(V2); //register to virtual pin

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth);

  pinMode(pinoSensor1,INPUT); //Definindo pino do Sensor1 como de entrada. 
  pinMode(pinoSensor2,INPUT); //Definindo pino do Sensor2 como de entrada.
  pinMode(pinoSensor3,INPUT); //Definindo pino do Sensor2 como de entrada.
  pinMode(pinoSensor4,INPUT); //Definindo pino do Sensor2 como de entrada.
  pinMode(pinoSensor5,INPUT); //Definindo pino do Sensor2 como de entrada.

  led1.off(); //desligando o led1
  //led2.off(); //desligando o led2
  Blynk.run();
}

void loop()
{
  //delay(1000);

  if (millis() - lastTime2 > 500) {
    if (estadoLed1 == HIGH) {
      estadoLed1 = 0;
      led1.off();
    } else {
      estadoLed1 = 1;
      led1.on();
    }

    lastTime2 = millis();
  }
  
  if (millis() - lastTime1 > 1000) {
    //Blynk.run();
    estadoSensor1 = digitalRead(pinoSensor1); //Lendo o estado do pino do Sensor1
    estadoSensor2 = digitalRead(pinoSensor2); //Lendo o estado do pino do Sensor2
    estadoSensor3 = digitalRead(pinoSensor3); //Lendo o estado do pino do Sensor2
    estadoSensor4 = digitalRead(pinoSensor4); //Lendo o estado do pino do Sensor2
    estadoSensor5 = digitalRead(pinoSensor5); //Lendo o estado do pino do Sensor2

    Blynk.virtualWrite(V0, 20*estadoSensor1+20*estadoSensor2+20*estadoSensor3+20*estadoSensor4+20*estadoSensor5);

    Blynk.run();
    
    lastTime1 = millis();
  }
}

