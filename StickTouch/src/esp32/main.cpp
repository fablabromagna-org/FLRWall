
// 
// maurizio.conti@fablabromagna.org
// Gennaio 2020
//
// Esempio di generatore di flussi DMX512 (Artnet) per sperimentare Mad-Map  
// Versione per  M5Stick
//
// Ricordarsi di
// - mettere M5Stick e il notebok sulla stessa rete wifi
// - cambiare in questo sorgente l'IP del notebook.
// - configurare mad-map per accettare flussi DMX512 sull'universo 1
//

#include <Arduino.h>
#include <M5StickC.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLE2902.h>

#include <driver/adc.h>

#include <Wire.h>
#include "Adafruit_MPR121.h"
#include "Artnet.h"

// I2C and MPR121 Stuff
TwoWire tw = TwoWire( 0x5A );
Adafruit_MPR121 mpr121 = Adafruit_MPR121();

// WiFi stuff
const char* ssid = "--";
const char* pwd = "...";

ArtnetSender artnet;
uint32_t universe = 1;

const uint16_t size = 512;
uint8_t data[size];
uint8_t value = 0;

void ClearScreen()
{
    M5.Lcd.fillScreen(TFT_BLACK);
    M5.Lcd.setTextColor(TFT_WHITE);  // Adding a background colour erases previous text automatically
    
    M5.Lcd.setCursor(3, 3);  
    M5.Lcd.setTextSize( 3 );
}

//
// Setup
//
void setup()   {

  M5.begin();
  M5.MPU6886.Init();

  //M5.Lcd.setBrightness((uint8_t)100);
  M5.Lcd.setRotation(3);
  ClearScreen();

  // Trick!!! ;-)
  // Su M5Stick-C la porta grove è usabile come I2C
  // pin esterno grove (giallo) SCL su M5StickC = 33
  // pin interno grove (bianco) SDA su M5StickC = 32
  // E' necessario creare un oggetto TwoWire e configurarlo 
  // su pin diversi da quelli standard...
  tw.begin( 32, 33 );
  
  // ... poi si passa l'oggetto tw all'oggetto I2C insieme all'indirizzo I2C
  if ( !mpr121.begin( 0x5A, &tw ) ) {
    M5.Lcd.print("Touch not found :-/");  
    while(1);
  }

  M5.Lcd.print("Touch OK");  
  delay(50);
  
  // WiFi stuff
  WiFi.begin(ssid, pwd);
  int cntDelay = 10;

  while (WiFi.status() != WL_CONNECTED) 
  { 
    M5.Lcd.print("."); delay(400);
    cntDelay--;
    if(cntDelay <=0 )
       break;
  }
  
  if(cntDelay >0)
     Serial.print("WiFi connected, IP = "); Serial.println(WiFi.localIP());

  //
  // Indirizzo dell'altro endpoint (notebook) al quale inviare il flusso DMX512
  //  
  artnet.begin("192.168.254.46");
  int cnt = 511;
  
  while(cnt>0)
  {
    data[cnt] = 0;
    cnt--;
  }

  ClearScreen();
  M5.Lcd.print(WiFi.localIP());  
  delay(1000);

}

int values[20];
int soglia = 50;


//
// Loop principale
//
void loop() {
  
  ClearScreen();

  for( int idx=1 ; idx<8 ; idx++ ) {
    values[idx] = mpr121.baselineData(idx) - mpr121.filteredData(idx);

    if( values[idx] > soglia ) {
      M5.Lcd.setTextColor(TFT_WHITE);
      
      uint16_t val = 0xff;
      memset( data+(idx*2), val, 2 );
      artnet.set(idx, data, size);
      artnet.streaming();
    }
    else {
      M5.Lcd.setTextColor(TFT_RED);

      uint16_t val = 0x32;
      memset( data+(idx*2), val, 2 );
      artnet.set(idx, data, size);
      artnet.streaming();
    }

    M5.Lcd.print( String( idx ) );  
  }
  
  M5.update();
  delay(40);
}
