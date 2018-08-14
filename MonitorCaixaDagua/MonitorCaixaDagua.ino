#define BLYNK_PRINT Serial


#include <SPI.h>
#include <Ethernet.h>
#include <TimeLib.h>
#include <EthernetUdp.h>
#include <BlynkSimpleEthernet.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "78177ea4b1c044be83be484f66d977e6";
byte mac[] = {  0x00, 0x00, 0xAA, 0xBB, 0xCC, 0xDD};

const int timeZone = -3;
EthernetUDP Udp;
unsigned int localPort = 8888;  // local port to listen for UDP packets


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
long lastTime3 = 0;

WidgetLED led1(V1); //register to virtual pin
WidgetLED led2(V2); //register to virtual pin

void setup()
{
  // Debug console
  Serial.begin(9600);

  delay(250);
  if (Ethernet.begin(mac) == 0) {
    // no point in carrying on, so do nothing forevermore:
    while (1) {
      Serial.println("Failed to configure Ethernet using DHCP");
      delay(10000);
    }
  }
  Serial.print("IP number assigned by DHCP is ");
  Serial.println(Ethernet.localIP());
  Udp.begin(localPort);
  Serial.println("waiting for sync");
  setSyncProvider(getNtpTime);
  
  Blynk.begin(auth);

  pinMode(pinoSensor1,INPUT); //Definindo pino do Sensor1 como de entrada. 
  pinMode(pinoSensor2,INPUT); //Definindo pino do Sensor2 como de entrada.
  pinMode(pinoSensor3,INPUT); //Definindo pino do Sensor2 como de entrada.
  pinMode(pinoSensor4,INPUT); //Definindo pino do Sensor2 como de entrada.
  pinMode(pinoSensor5,INPUT); //Definindo pino do Sensor2 como de entrada.

  led1.off(); //desligando o led1
  //led2.off(); //desligando o led2
  
}

time_t prevDisplay = 0; // when the digital clock was displayed
horaagora = 0;

void loop()
{
  if (timeStatus() != timeNotSet) {
    if (now() != prevDisplay) { //update the display only if time has changed
      prevDisplay = now();
      if(hour() - horaagora > 1){
          //fazer algo
          horaagora = hour()
        }
    }
  }
    
  Blynk.run();
  
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
    
    
    lastTime1 = millis();
  }
}


/*-------- NTP code ----------*/

const int NTP_PACKET_SIZE = 48; // NTP time is in the first 48 bytes of message
byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming & outgoing packets

time_t getNtpTime()
{
  while (Udp.parsePacket() > 0) ; // discard any previously received packets
  Serial.println("Transmit NTP Request");
  sendNTPpacket(timeServer);
  uint32_t beginWait = millis();
  while (millis() - beginWait < 1500) {
    int size = Udp.parsePacket();
    if (size >= NTP_PACKET_SIZE) {
      Serial.println("Receive NTP Response");
      Udp.read(packetBuffer, NTP_PACKET_SIZE);  // read packet into the buffer
      unsigned long secsSince1900;
      // convert four bytes starting at location 40 to a long integer
      secsSince1900 =  (unsigned long)packetBuffer[40] << 24;
      secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
      secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
      secsSince1900 |= (unsigned long)packetBuffer[43];
      return secsSince1900 - 2208988800UL + timeZone * SECS_PER_HOUR;
    }
  }
  Serial.println("No NTP Response :-(");
  return 0; // return 0 if unable to get the time
}

// send an NTP request to the time server at the given address
void sendNTPpacket(IPAddress &address)
{
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:                 
  Udp.beginPacket(address, 123); //NTP requests are to port 123
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();
}
