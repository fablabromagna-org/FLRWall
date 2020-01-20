# FLRWall
Raccolta di materiali (in divenire) utili alla realizzazione di un Interactive Wall

## ArduinoTouch

Stampa con Serial.print i primi 8 canali di MPR121


## ArduinoTouchMaxMsp

Esempio di come comunicare i valori letti dai sensori a Max/Msp

Aprire la patch ../MaxMsp/FLRSerialTest.maxpat con MaxMsp e selezionare la giusta COM port

## StickTouch
Esempio di generatore di flussi DMX512 (Artnet) per sperimentare Mad-Map - Versione per  M5Stick

Ricordarsi di

- mettere M5Stick e il notebok sulla stessa rete wifi
- cambiare (lato Stick) l'IP del notebook al quale spedire i pacchetti.
- configurare mad-map per accettare flussi DMX512 sull'universo 1


## Note

*I progetti Arduino UNO e M5Stick sono stati testati su PlatformIO*

*L'esempio ArduinoTouchMaxMsp contiene una patch FLRSerialTest nella cartella MaxMsp*
