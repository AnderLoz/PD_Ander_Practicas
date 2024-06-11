# Practica 7.1

## **Introducció**
Les dades de so es magatzema com una matriu a la RAM interna del ESP32, llavors utilitzarem la placa MAX98357 I2S com a convertidor DAC. Per tant, utilitzarem el protocol I2S per conservar lo millor posible les dades del so digital

## **Hardware**
* ESP32-S3.
* El DAC MAX98357 (I2S).
* Un altaveu de 3W.
## **Software**
### **- Capçalera del code**
Afegim a la capçalera del programa las llibrerias de audio i 3 punters que serviran per llegir el archiu de audio, descodificar aquesta lectura i enviar el resultat analogic.


### **- Estructura del Setup**
Començem la estructura del setup amb un punter 'in' amb els parametres de la mostra del archiu aac i la mida de aquest. Tambe definirem un altre punter que codificara el aac i aquest cop el audio de sortida. Tambe caldra inicialitzar una ganancia de 0.125 i els pins on van conectats el conversor.


### **- Estructura del Loop**
En el loop, es verifica que el aac s'estigui executant correctament fins a estar sencerament descodificat. Quan ho estigui, se acabara la execucio i es printara per pantalla:
"Sound Generator"

## **Codigo completo**
```cpp
#include <Arduino.h>
#include "AudioGeneratorAAC.h"
#include "AudioOutputI2S.h"
#include "AudioFileSourcePROGMEM.h"
#include "sampleaac.h"
AudioFileSourcePROGMEM *in;
AudioGeneratorAAC *aac;
AudioOutputI2S *out;

void setup(){
Serial.begin(115200);
in = new AudioFileSourcePROGMEM(sampleaac, sizeof(sampleaac));
aac = new AudioGeneratorAAC();
out = new AudioOutputI2S();
out -> SetGain(0.125);
out -> SetPinout(4,5,6);
aac->begin(in, out);
}

void loop(){
if (aac->isRunning()) {
aac->loop();
} else {
aac -> stop();
Serial.printf("Sound Generator\n");
delay(1000);
}
}
```