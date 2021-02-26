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

// Enum für die Steuerung von Ventilen (Zustände) 
enum states { open, closed };
states controlsV1 ,controlsV2, controlsV3, controlsV4;

// 
String dataRecieved;

// 
long timeNow, timePrev;

// Funktionsprototypen (Notwendig in PlatformIO)
void checkSerial(void);
void automatSteuerung(void);

void setup() {
  pinMode(V1, INPUT);
  pinMode(V2, INPUT);
  pinMode(V3, INPUT);
  pinMode(V4, INPUT);
  Serial.begin(115200);
}

void loop() {
    checkSerial();
    automatSteuerung();
    delay(700);
}

/* Diese Funktion überprüft ob etwas über die Serielle Schnitstelle gesendet wurde
#  Wenn ja, dann speichert es die einzele Bits in CharArray und dann umwandelt CharArray in String um */ 
void checkSerial()
{
  while (Serial.available() > 0 && Serial.available() < 30)
  {
    dataSent[i++] = Serial.read();
  }
  dataRecieved = dataSent;
  Serial.println("DEBUG (dataRecoeved): " + dataRecieved);    //Gibt ein String aus was über die Serielle Schnitstelle empafngen wurde (Debug)
  i = 0; 

  if (dataRecieved == "1 open") { controlsV1 = open; }
  else if (dataRecieved == "1 close") { controlsV1 = closed; }
  else if (dataRecieved == "2 open") { controlsV2 = open; }
  else if (dataRecieved == "2 close") { controlsV2 = closed; }
  else if (dataRecieved == "3 open") { controlsV3 = open; }
  else if (dataRecieved == "3 close") { controlsV3 = closed; }
  else if (dataRecieved == "4 open") { controlsV4 = open; }
  else if (dataRecieved == "4 close") { controlsV4 = closed; }
}

void automatSteuerung()
{
  if (controlsV1 == open) 
  { 
    digitalWrite(V1, HIGH); 
    Serial.println("DEBUG (Zustand): 1 open"); 
  }
  else if (controlsV1 == closed) 
  { 
    digitalWrite(V1, LOW);
    Serial.println("DEBUG (Zustand): 1 closed");  
  }
  else if (controlsV2 == open) 
  { 
    digitalWrite(V2, HIGH);
    Serial.println("DEBUG (Zustand): 2 open");
  }
  else if (controlsV2 == closed) 
  { 
    digitalWrite(V2, LOW);
    Serial.println("DEBUG (Zustand): 2 closed");
  }
  else if (controlsV3 == open) 
  { 
    digitalWrite(V3, HIGH);
    Serial.println("DEBUG (Zustand): 3 open");
  }
  else if (controlsV3 == closed) 
  { 
    digitalWrite(V3, LOW);
    Serial.println("DEBUG (Zustand): 3 closed");   
  } 
  else if (controlsV4 == open) 
  { 
    digitalWrite(V4, HIGH);
    Serial.println("DEBUG (Zustand): 4 open");
  }
  else if (controlsV4 == closed)
  { 
    digitalWrite(V4, LOW);
    Serial.println("DEBUG (Zustand): 4 closed");
  }
}