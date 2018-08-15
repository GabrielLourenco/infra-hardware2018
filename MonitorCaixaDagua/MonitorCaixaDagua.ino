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

const int pinoSensorCaixa1 = 48; //constante que define o pino digital 48 como do Sensor1.
const int pinoSensorCaixa2 = 46; //constante que define o pino digital 46 como do Sensor1.
const int pinoSensorCaixa3 = 44; //constante que define o pino digital 44 como do Sensor1.
const int pinoSensorCaixa4 = 42; //constante que define o pino digital 42 como do Sensor1.
const int pinoSensorCaixa5 = 40; //constante que define o pino digital 40 como do Sensor1.

const int pinoSensorCisterna1 = 38; //constante que define o pino digital 38 como do Sensor1.
const int pinoSensorCisterna2 = 36; //constante que define o pino digital 36 como do Sensor1.
const int pinoSensorCisterna3 = 34; //constante que define o pino digital 34 como do Sensor1.
const int pinoSensorCisterna4 = 32; //constante que define o pino digital 32 como do Sensor1.
const int pinoSensorCisterna5 = 30; //constante que define o pino digital 30 como do Sensor1.

int estadoSensorCaixa1 = 0; //Variável que conterá os estados do Sensor1 (0 LOW, 1 HIGH).
int estadoSensorCaixa2 = 0; //Variável que conterá os estados do Sensor1 (0 LOW, 1 HIGH).
int estadoSensorCaixa3 = 0; //Variável que conterá os estados do Sensor1 (0 LOW, 1 HIGH).
int estadoSensorCaixa4 = 0; //Variável que conterá os estados do Sensor1 (0 LOW, 1 HIGH).
int estadoSensorCaixa5 = 0; //Variável que conterá os estados do Sensor1 (0 LOW, 1 HIGH).

int estadoSensorCisterna1 = 0; //Variável que conterá os estados do Sensor1 (0 LOW, 1 HIGH).
int estadoSensorCisterna2 = 0; //Variável que conterá os estados do Sensor1 (0 LOW, 1 HIGH).
int estadoSensorCisterna3 = 0; //Variável que conterá os estados do Sensor1 (0 LOW, 1 HIGH).
int estadoSensorCisterna4 = 0; //Variável que conterá os estados do Sensor1 (0 LOW, 1 HIGH).
int estadoSensorCisterna5 = 0; //Variável que conterá os estados do Sensor1 (0 LOW, 1 HIGH).

const int pinoLedRequisicao = 28 //constante que define o pino digital 30 como do Led da Requisição de caixa dagua.
const int pinoLedBomba = 26 //constante que define o pino digital 30 como do Led da Bomba.
const int pinoLedCisterna = 24 //constante que define o pino digital 30 como do Led da Cisterna.

WidgetLED ledConexao(V1); //register to virtual pin
WidgetLED ledBomba(V2); //register to virtual pin
WidgetLED ledRequisicao(V3); //register to virtual pin
WidgetLED ledCisterna(V4); //register to virtual pin
WidgetTerminal terminal(V5);

int modoCritico

BLYNK_WRITE(V20){
    modoCritico = param.asInt();
    if(modoCritico == 1){
      Blynk.setProperty(V20, "color", "#D3435C");
      digitalClockDisplay("Modo Critico Ativado");
    }else{
      Blynk.setProperty(V20, "color", "#23C48E");
      digitalClockDisplay("Modo Critico Desativado");
    }
}

int estadoledConexao = 1; //Variável que conterá os estados do Sensor1 (0 LOW, 1 HIGH).

long lastTime1 = 0;
long lastTime2 = 0;
long lastTime3 = 0;

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


  pinMode(pinoSensorCaixa1,INPUT); //Definindo pino do Sensor1 como de entrada. 
  pinMode(pinoSensorCaixa2,INPUT); //Definindo pino do Sensor2 como de entrada.
  pinMode(pinoSensorCaixa3,INPUT); //Definindo pino do Sensor2 como de entrada.
  pinMode(pinoSensorCaixa4,INPUT); //Definindo pino do Sensor2 como de entrada.
  pinMode(pinoSensorCaixa5,INPUT); //Definindo pino do Sensor2 como de entrada.

  pinMode(pinoSensorCisterna1,INPUT); //Definindo pino do Sensor1 como de entrada. 
  pinMode(pinoSensorCisterna2,INPUT); //Definindo pino do Sensor2 como de entrada.
  pinMode(pinoSensorCisterna3,INPUT); //Definindo pino do Sensor2 como de entrada.
  pinMode(pinoSensorCisterna4,INPUT); //Definindo pino do Sensor2 como de entrada.
  pinMode(pinoSensorCisterna5,INPUT); //Definindo pino do Sensor2 como de entrada.

  pinMode(pinoLedRequisicao, OUTPUT);
  pinMode(pinoLedBomba, OUTPUT);
  pinMode(pinoLedCisterna, OUTPUT);

  ledConexao.off(); //desligando o ledConexao
  //led2.off(); //desligando o led2
  
}

time_t prevDisplay = 0; // when the digital clock was displayed
int horaagora = 0;
int cisterna = 0;
int bomba = 0;
int bombaAnterior = 0;


void loop()
{
     
  Blynk.run();
  
  if (millis() - lastTime2 > 500) {
    if (estadoledConexao == HIGH) {
      estadoledConexao = 0;
      ledConexao.off();
    } else {
      estadoledConexao = 1;
      ledConexao.on();
    }

    lastTime2 = millis();
  }
  
  if (millis() - lastTime1 > 500) {
    estadoSensorCaixa1 = digitalRead(pinoSensorCaixa1); //Lendo o estado do pino do Sensor1
    estadoSensorCaixa2 = digitalRead(pinoSensorCaixa2); //Lendo o estado do pino do Sensor2
    estadoSensorCaixa3 = digitalRead(pinoSensorCaixa3); //Lendo o estado do pino do Sensor2
    estadoSensorCaixa4 = digitalRead(pinoSensorCaixa4); //Lendo o estado do pino do Sensor2
    estadoSensorCaixa5 = digitalRead(pinoSensorCaixa5); //Lendo o estado do pino do Sensor2

    estadoSensorCisterna1 = digitalRead(pinoSensorCisterna1); //Lendo o estado do pino do Sensor1
    estadoSensorCisterna2 = digitalRead(pinoSensorCisterna2); //Lendo o estado do pino do Sensor2
    estadoSensorCisterna3 = digitalRead(pinoSensorCisterna3); //Lendo o estado do pino do Sensor2
    estadoSensorCisterna4 = digitalRead(pinoSensorCisterna4); //Lendo o estado do pino do Sensor2
    estadoSensorCisterna5 = digitalRead(pinoSensorCisterna5); //Lendo o estado do pino do Sensor2

    //Verifica se a cisterna está pronta com água para encher a caixa
    if(modoCritico == 1){
      if(estadoSensorCisterna1 == 1){
        ledCisterna.on();
        digitalWrite(pinoLedCisterna, HIGH);
        cisterna = 1;
      }else{
        ledCisterna.off();
        digitalWrite(pinoLedCisterna, LOW);
        cisterna = 0;
      }
    }else{
      if(estadoSensorCisterna2 == 1){
        ledCisterna.on();
        digitalWrite(pinoLedCisterna, HIGH);
        cisterna = 1;
      }else{
        ledCisterna.off();
        digitalWrite(pinoLedCisterna, LOW);
        cisterna = 0;
      }
    }

    //Verifica se a caixa necessita de água
    if(estadoSensorCaixa5 == 0){
      ledRequisicao.on();
      digitalWrite(pinoLedRequisicao, HIGH);
      if(cisterna == 1){
        ledBomba.on();
        digitalWrite(pinoLedBomba, HIGH);
        bomba = 1;        
      }else{
        ledBomba.off();
        digitalWrite(pinoLedBomba, LOW);
        bomba = 0;
      }
    }else{
      ledRequisicao.off();
      ledBomba.off();
      digitalWrite(pinoLedRequisicao, LOW);
      digitalWrite(pinoLedBomba, LOW);
    }

    if(bomba != bombaAnterior){
      
      if(bomba == 1){
        digitalClockDisplay("Bomba Ligada");
      }else{
        digitalClockDisplay("Bomba Desligada");
      }
      bombaAnterior = bomba;
    }


    Blynk.virtualWrite(V0,  20*estadoSensorCaixa1+20*estadoSensorCaixa2+20*estadoSensorCaixa3+20*estadoSensorCaixa4+20*estadoSensorCaixa5);
    Blynk.virtualWrite(V10, 25*estadoSensorCisterna2+25*estadoSensorCisterna3+25*estadoSensorCisterna4+25*estadoSensorCisterna5);
    
    lastTime1 = millis();
  }
}


void digitalClockDisplay(char mensagem){
  // digital clock display of the time
  terminal.print(mensagem);
  terminal.print(" as ");
  terminal.print(hour());
  printDigits(minute());
  printDigits(second());
  terminal.print(" ");
  terminal.print(day());
  terminal.print("-");
  terminal.print(month());
  terminal.print("-");
  terminal.print(year()); 
  terminal.println();
}

void printDigits(int digits){
  // utility for digital clock display: prints preceding colon and leading 0
  terminal.print(":");
  if(digits < 10)
    terminal.print('0');
  terminal.print(digits);
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
