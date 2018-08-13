#define BLYNK_PRINT Serial

#include <SPI.h>
#include <Ethernet.h>
#include <BlynkSimpleEthernet.h>

// Auth Token de conexão com o Blynk
char auth[] = "23988228d5244a64910de5ce99fa9894";

#define W5100_CS  10

const int pinoSensor1 = 8; //constante que define o pino digital 8 como do Sensor1.
const int pinoSensor2 = 9; //constante que define o pino digital 9 como do Sensor2.
const int pinoSensor3 = 10; //constante que define o pino digital 10 como do Sensor1.
const int pinoSensor4 = 11; //constante que define o pino digital 11 como do Sensor2.
const int pinoSensor5 = 12; //constante que define o pino digital 12 como do Sensor1.
int lastTime = 0;
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
  pinMode(pinoSensor3,INPUT); //Definindo pino do Sensor1 como de entrada. 
  pinMode(pinoSensor4,INPUT); //Definindo pino do Sensor2 como de entrada.
  pinMode(pinoSensor5,INPUT); //Definindo pino do Sensor1 como de entrada. 

  led1.off(); //desligando o led1
  led2.off(); //desligando o led2
  

  Blynk.virtualWrite(V0, 0);
}

void conectarBlynk(){
  led1.off();
  bool result = Blynk.connect(1000);
  if(result){
    Blynk.run();
    led1.on();
  }

}

void loop()
{
  
  //if (millis() - lastTime > 500) {
    conectarBlynk();
    
    estadoSensor1 = digitalRead(pinoSensor1); //Lendo o estado do pino do Sensor1
    estadoSensor2 = digitalRead(pinoSensor2); //Lendo o estado do pino do Sensor2
    estadoSensor3 = digitalRead(pinoSensor3); //Lendo o estado do pino do Sensor3
    estadoSensor4 = digitalRead(pinoSensor4); //Lendo o estado do pino do Sensor4
    estadoSensor5 = digitalRead(pinoSensor5); //Lendo o estado do pino do Sensor5
  
  
    if (estadoSensor4 == LOW) {
      led2.on(); //caixa está em 60%, led da bomba acende
    } else {
      led2.off();      
    }
    
    Blynk.virtualWrite(V0, 20*estadoSensor1+20*estadoSensor2+20*estadoSensor3+20*estadoSensor4+20*estadoSensor5);
    lastTime = millis();
  //}
}
