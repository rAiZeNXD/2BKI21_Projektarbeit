#include <Arduino.h>

// Ventil 4 am Pin 23
#define V4 23

// Ventil 3 am Pin 22
#define V3 22

// Ventil 2 am Pin 21
#define V2 21

// Ventil 1 am Pin 19
#define V1 19

// CharArray für 
char dataSent[30];

// Index für die while-Schleife in der checkSerial() Funktion
int i = 0;

// Enum für Betriebmodus
//enum Betriebmodus { start, debug, manual, automatic };
//Betriebmodus modus;
int state;

enum Zustaende { open, closed };
Zustaende stateV1, stateV2, stateV3, stateV4;

// 
String dataRecieved;

// 
long timeNow, timePrev;

// Funktionsprototypen (Notwendig in PlatformIO)
void steuerung(void);
void states(void);

void setup() 
{
  pinMode(V1, INPUT);
  pinMode(V2, INPUT);
  pinMode(V3, INPUT);
  pinMode(V4, INPUT);
  delay(750);
  Serial.begin(115200);
}

void loop() 
{
    steuerung();
    states();
    delay(500);
}

/* Diese Funktion überprüft ob etwas über die Serielle Schnitstelle gesendet wurde
#  Wenn ja, dann speichert es die einzele Bits in CharArray und dann umwandelt CharArray in String um */ 
void steuerung()
{
  while (Serial.available() > 0 && Serial.available() < 30)
  {
    dataSent[i++] = Serial.read();
  }
  dataRecieved = dataSent;
  //Serial.println("DEBUG (dataRecoeved): " + dataRecieved);    Gibt ein String aus was über die Serielle Schnitstelle empafngen wurde (Debug)

  if (dataRecieved == "debug") { state = 1; }
  else if (dataRecieved == "manual") { state = 2; }
  else if (dataRecieved == "automatic") { state = 3; }

  // Befehle für Debug Steuerung
  else if (dataRecieved == "1 open") { stateV1 = open; }
  else if (dataRecieved == "1 close") { stateV1 = closed; }
  else if (dataRecieved == "2 open") { stateV2 = open; }
  else if (dataRecieved == "2 close") { stateV2 = closed; }
  else if (dataRecieved == "3 open") { stateV3 = open; }
  else if (dataRecieved == "3 close") { stateV3 = closed; }
  else if (dataRecieved == "4 open") { stateV4 = open; }
  else if (dataRecieved == "4 close") { stateV1 = closed; }
  
  i = 0;
  dataRecieved = ""; 
  
  // Bug
  
}

void states()
{
  switch (state)
  {
    case 1: // Debug Steuerung
      Serial.println("debug");
      /*if (stateV1 == open) 
      { 
        digitalWrite(V1, HIGH); 
        Serial.println("DEBUG (Zustand): 1 open");
      }
      else if (stateV1 == closed) 
      { 
        digitalWrite(V1, LOW);
        Serial.println("DEBUG (Zustand): 1 closed");  
      }
      else if (stateV2 == open) 
      { 
        digitalWrite(V2, HIGH);
        Serial.println("DEBUG (Zustand): 2 open");
      }
      else if (stateV2 == closed) 
      { 
        digitalWrite(V2, LOW);
        Serial.println("DEBUG (Zustand): 2 closed");
      }
      else if (stateV3 == open) 
      { 
        digitalWrite(V3, HIGH);
        Serial.println("DEBUG (Zustand): 3 open");
      }
      else if (stateV3 == closed) 
      { 
        digitalWrite(V3, LOW);
        Serial.println("DEBUG (Zustand): 3 closed");   
      } 
      else if (stateV4 == open) 
      { 
        digitalWrite(V4, HIGH);
        Serial.println("DEBUG (Zustand): 4 open");
      }
      else if (stateV4 == closed)
      { 
        digitalWrite(V4, LOW);
        Serial.println("DEBUG (Zustand): 4 closed");
      }*/
    break;

    case 2: // Manuelle Steuerung
      Serial.println("manual");
    
    break;

    case 3: // Automatische Steuerung
      Serial.println("auto");
    
    break;

    default:
    break;
  }
}