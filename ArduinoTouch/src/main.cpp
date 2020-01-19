//
// maurizio.conti@fablabromagna.org
// Gennaio 2020
//
// Esempio di monitor dei primi 8 canali MPR121
// Il canale 3 e 7 davano di matto... era il cuki che non toccava bene il filo
// con questo monitor ho potuto indagare il difetto!!
//
// Stampa sulla seriale i valori letti da MPR121

#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_MPR121.h"

Adafruit_MPR121 cap = Adafruit_MPR121();

void setup() {
  Serial.begin(9600);

  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring :-/");
    while (1);
  }
  
  Serial.println("MPR121 found!");
  Serial.println("1\t2\t3\t4\t5\t6\t7");
}

void loop() {

  for (uint8_t i=1; i<8; i++) {
    
    int val = cap.baselineData(i)-cap.filteredData(i);
    if( val < 0 )
      val=0;

    Serial.print( val );
    Serial.print("\t");
  }
  
  Serial.print("\r");
  Serial.print("                                                    ");
  Serial.print("\r");

  delay(100);
}