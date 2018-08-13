#define BLYNK_PRINT Serial

#include <SPI.h>
#include <Ethernet.h>
#include <BlynkSimpleEthernet.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "23988228d5244a64910de5ce99fa9894";

#define W5100_CS  10

const int pinoSensor1 = 8; //constante que define o pino digital 8 como do Sensor1.
const int pinoSensor2 = 9; //constante que define o pino digital 9 como do Sensor2.
int lastTime = 0;
int estadoSensor1 = 0; //Variável que conterá os estados do Sensor1 (0 LOW, 1 HIGH).
int estadoSensor2 = 0; //Variável que conterá os estados do Sensor2 (0 LOW, 1 HIGH).

WidgetLED led1(V1); //registra o led1 no virtual pino 1
WidgetLED led2(V2); //registra o led2 no virtual pino 2
WidgetLED led3(V3); //registra o led2 no virtual pino 2

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth);

  pinMode(pinoSensor1,INPUT); //Definindo pino do Sensor1 como de entrada. 
  pinMode(pinoSensor2,INPUT); //Definindo pino do Sensor2 como de entrada. 

  led1.off(); //desligando o led1
  led2.off(); //desligando o led2
  led3.on();
  

  Blynk.virtualWrite(V0, 0);
}

void conectarBlynk(){
  led3.on();
  led1.off();
  bool result = Blynk.connect(1000);
  if(result){
    Blynk.run();
    led1.on();
    led3.off();
  }

}

void loop()
{
  
  //if (millis() - lastTime > 500) {
    conectarBlynk();
    
    estadoSensor1 = digitalRead(pinoSensor1); //Lendo o estado do pino do Sensor1
    estadoSensor2 = digitalRead(pinoSensor2); //Lendo o estado do pino do Sensor2
  
    if (estadoSensor1 == LOW) {
      led2.on(); //Sensor1 fechado, acende o led1.
    } else if (estadoSensor2 == HIGH) {
      led2.off(); //Sensor1 aberto, apaga o led1.    
    } else {
      led2.on();      
    }
    
    Blynk.virtualWrite(V0, 20*estadoSensor1+20*estadoSensor2);//+20*estadoSensor3+20*estadoSensor4+20*estadoSensor5);
    lastTime = millis();
  //}
}

