#include <Arduino.h>

// Ventil 4 am Pin 23
#define V4 23

// Ventil 3 am Pin 22
#define V3 22

// Ventil 2 am Pin 21
#define V2 21

// Ventil 1 am Pin 19
#define V1 19

// CharArray weil per Serielle Schnittstelle werden nur einzelne Zeichen gesendet die dann in String konvertiert werde
char dataSent[30];

// Index für die while-Schleife in der checkSerial() Funktion
int i = 0;

// Enum für Betriebmodus
enum Betriebmodus { stop, debug, manual, automatic };
Betriebmodus modus;

enum Zustaende { open, closed };
Zustaende stateV1, stateV2, stateV3, stateV4;

// Hier werden empfangene Befehle gespeichert
String dataRecieved;

// 
long timeNow, timePrev;

// Funktionsprototypen (Notwendig in PlatformIO)
void serialCheck(void);
void steuerung(void);

void setup() 
{
  modus = stop;
  pinMode(V1, INPUT);
  pinMode(V2, INPUT);
  pinMode(V3, INPUT);
  pinMode(V4, INPUT);
  stateV1 = closed;
  stateV2 = closed;
  stateV3 = closed;
  stateV4 = closed;
  delay(750);
  Serial.begin(115200);
}

void loop() 
{
  serialCheck();
  steuerung();
  delay(500);
}

/* Diese Funktion überprüft ob etwas über die Serielle Schnitstelle gesendet wurde
#  Wenn ja, dann speichert es die einzele Bits in CharArray und dann umwandelt CharArray in String um */ 
void serialCheck()
{
  while (Serial.available() > 0 && Serial.available() < 30)
    dataSent[i++] = Serial.read();

  // dataSent[i-1] = '\0'; Arduino Serielle Schnittstelle
  dataSent[i] = '\0';   // hterm Serielle Schnittstelle 
  dataRecieved = dataSent;
  //Serial.println("DEBUG (dataRecoeved): " + dataRecieved);    Gibt ein String aus was über die Serielle Schnitstelle empafngen wurde (Debug)

  if (dataRecieved == "debug")
    modus = debug;
  else if (dataRecieved == "manual") 
    modus = manual;
  else if (dataRecieved == "automatic")
    modus = automatic;
  else if (dataRecieved == "stop")
    modus = stop;  

  // Befehle für Debug Steuerung
  else if (dataRecieved == "1 open" && modus == debug)
    stateV1 = open;
  else if (dataRecieved == "1 close" && modus == debug)
    stateV1 = closed;
  else if (dataRecieved == "2 open" && modus == debug)
    stateV2 = open;
  else if (dataRecieved == "2 close" && modus == debug)
    stateV2 = closed;
  else if (dataRecieved == "3 open" && modus == debug)
    stateV3 = open;
  else if (dataRecieved == "3 close" && modus == debug)
    stateV3 = closed;
  else if (dataRecieved == "4 open" && modus == debug)
    stateV4 = open;
  else if (dataRecieved == "4 close" && modus == debug) 
    stateV1 = closed;

  // Befehle für automatische Steuerung
  
  i = 0;
  dataRecieved = "";
}

void steuerung()
{
  switch (modus)
  {
    case debug: // Einzelne Ventile können angesteurert werden
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

    case stop: // Schließt alle Ventile
      digitalWrite(V1, LOW);
      digitalWrite(V2, LOW);
      digitalWrite(V3, LOW);
      digitalWrite(V4, LOW);
    break;

    default:
      digitalWrite(V1, LOW);
      digitalWrite(V2, LOW);
      digitalWrite(V3, LOW);
      digitalWrite(V4, LOW);
      Serial.println("Fehler! Ungültiger Zustand. Alle Ventile wurden geschlossen.");
    break;
  }
}