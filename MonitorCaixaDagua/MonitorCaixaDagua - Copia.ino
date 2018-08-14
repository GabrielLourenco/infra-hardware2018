#define BLYNK_PRINT Serial

#include <SPI.h>
#include <Ethernet.h>
#include <BlynkSimpleEthernet.h>

// Auth Token de conexão com o Blynk
char auth[] = "483f60feb270488d9df7754c35178b1e";

#define W5100_CS  10

const int pinoSensor1 = 2; //constante que define o pino digital 8 como do Sensor1.
const int pinoSensor2 = 3; //constante que define o pino digital 9 como do Sensor2.
//const int pinoSensor3 = 4; //constante que define o pino digital 10 como do Sensor1.
const int pinoSensor4 = 5; //constante que define o pino digital 11 como do Sensor2.
const int pinoSensor5 = 6; //constante que define o pino digital 12 como do Sensor1.

int estadoSensor1 = 0; //Variável que conterá os estados do Sensor1 (0 LOW, 1 HIGH).
int estadoSensor2 = 0; //Variável que conterá os estados do Sensor2 (0 LOW, 1 HIGH).
int estadoSensor3 = 0; //Variável que conterá os estados do Sensor3 (0 LOW, 1 HIGH).
int estadoSensor4 = 0; //Variável que conterá os estados do Sensor4 (0 LOW, 1 HIGH).
int estadoSensor5 = 0; //Variável que conterá os estados do Sensor5 (0 LOW, 1 HIGH).

WidgetLED led1(V1); //registra o led1 no virtual pino 1, simbolizando o led de conexão 
WidgetLED led2(V2); //registra o led2 no virtual pino 2, simbolizando o led da bomba

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth);

  pinMode(pinoSensor1,INPUT); //Definindo pino do Sensor1 como de entrada. 
  pinMode(pinoSensor2,INPUT); //Definindo pino do Sensor2 como de entrada.
  //pinMode(pinoSensor3,INPUT); //Definindo pino do Sensor1 como de entrada. 
  pinMode(pinoSensor4,INPUT); //Definindo pino do Sensor2 como de entrada.
  pinMode(pinoSensor5,INPUT); //Definindo pino do Sensor1 como de entrada.
  Blynk.virtualWrite(V0, 0);
}

void loop()
{
  Blynk.run();
  led1.off();
    
  estadoSensor1 = digitalRead(pinoSensor1); //Lendo o estado do pino do Sensor1
  estadoSensor2 = digitalRead(pinoSensor2); //Lendo o estado do pino do Sensor2
  //estadoSensor3 = digitalRead(pinoSensor3); //Lendo o estado do pino do Sensor3
  estadoSensor4 = digitalRead(pinoSensor4); //Lendo o estado do pino do Sensor4
  estadoSensor5 = digitalRead(pinoSensor5); //Lendo o estado do pino do Sensor5

  /*if (estadoSensor4 == LOW) {
    led2.on(); //caixa está em 60%, led da bomba acende
  } else {
    led2.off();      
  }
  Blynk.virtualWrite(V0, 20*estadoSensor1+20*estadoSensor2+20*estadoSensor3+20*estadoSensor4+20*estadoSensor5);
  */
  Serial.print(estadoSensor1);
  Serial.print(estadoSensor2);
  Serial.print(estadoSensor3);
  Serial.print(estadoSensor4);
  Serial.print(estadoSensor5);
  Serial.println();
  //Blynk.virtualWrite(V0, 20*estadoSensor1+20*estadoSensor2+20);
  led2.on();
  delay(100);
  led2.off();
  delay(100);
  led2.on();
  delay(100);
  led2.off();
}
