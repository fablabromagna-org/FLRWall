//
// Esempio di come comunicare i valori letti dai sensori a Max/Msp
//
// Aprire la patch ../MaxMsp/FLRSerialTest.maxpat con MaxMsp ...
// e selezionare la giusta COM port
//

#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_MPR121.h"

Adafruit_MPR121 cap = Adafruit_MPR121();
int xValue;

void setup() {
  Serial.begin(9600);

  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
}

void loop() {

  //
  // questo valore all'inizio aggiunge il riferimento all'asse X 
  // Così possiamo visualizzare un piccolo grafico dentro Max
  //
  Serial.print( xValue++ );
  Serial.print(" ");

  if( xValue > 500 )
    xValue = 0;
    
  for (uint8_t i=1; i<8; i++) {
    int val = cap.baselineData(i)-cap.filteredData(i);
    if( val < 0 )
      val=0;

    Serial.print( val );
    Serial.print(" ");
  }
  Serial.println();
}