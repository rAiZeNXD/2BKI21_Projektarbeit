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
enum Betriebmodus { start, debug, manual, automatic };
Betriebmodus modus;

enum Zustaende { open, closed };
Zustaende stateV1, stateV2, stateV3, stateV4;

// 
String dataRecieved;

// 
long timeNow, timePrev;

// Funktionsprototypen (Notwendig in PlatformIO)
void steuerung(void);

void setup() 
{
  pinMode(V1, INPUT);
  pinMode(V2, INPUT);
  pinMode(V3, INPUT);
  pinMode(V4, INPUT);
  delay(750);
  Serial.begin(115200);
  modus = start;
}

void loop() 
{
    steuerung();
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

  if (dataRecieved == "debug") { modus = debug; }
  else if (dataRecieved == "manual") { modus = manual; }
  else if (dataRecieved == "automatic") { modus = automatic; }

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

  switch (modus)
  {
    case debug: // Debug Steuerung
      Serial.println("debug");
      if (stateV1 == open) 
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
      } 
    break;

    case manual: // Manuelle Steuerung
      Serial.println("manual");
     
    break;

    case automatic: // Automatische Steuerung
      Serial.println("auto");
    
    break;

    default:
    break;
  }
}
