 # Practica 7
## **Introducció**
En aquesta practica el que busquem es reproduir un Wave o un mp3 mediant el ESP32 i un altaveu. Per aixo necesitarem tambe una targeta SD
## **Hardware**
* ESP32-s3.
* El DAC MAX98357 (I2S).
* El lector de tarjeta SD.
* Un altaveu de 3W
## **Software**
### **- Capçalera del code**
A la capçalera afegirem las llibrerias necesarias, com per exemple la que ens permetira utilitzar la targeta D "SD.h" o la del control de audio "FS.h". També necesitarem els pins que utilitzarem per conectar els components de hardware. Els 4 primers per el lector SD i els demes el DAC. Sera necesari tambe definir un object Audio


### **- Estructura del Setup**
Per començar, inicilaitzarem el pin SD_CS com a sortida i despres el bus SPI amb els seus pins corresponents (MOAI, MISO, SCK). Fem un serial.begin() a la velocitar de comunicacem que volem en ms i iniciem la Tarjeta SD. Ell objecte audio que em declarat lo utilitzem definit els pinst de sortida (BCLK, LRC, DOUT), i fem un setVolum de 10 i realitzem la conexio per escollir archiu de la tarjeta SD

### **- Estructura del Loop**
El loop finalment fem sencillament la funcio de audio en un loop. Totes les funcions posteriors marcades com a opcional tenen la funcio de mostrar en pantalla informacio que podria necesitarse, com nom, temps...

## **Code**
```cpp
#include <Arduino.h>

#include "Audio.h"
#include "SD.h"
#include "FS.h"
// Digital I/O used
#define SD_CS 39
#define SPI_MOSI 35
#define SPI_MISO 37
#define SPI_SCK 36
#define I2S_DOUT 6
#define I2S_BCLK 4
#define I2S_LRC 5
Audio audio;
void setup(){
pinMode(SD_CS, OUTPUT);
digitalWrite(SD_CS, HIGH);
SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);
Serial.begin(115200);
SD.begin(SD_CS);
audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
audio.setVolume(10); // 0...21
audio.connecttoFS(SD, "so1.wav");
}
void loop(){
audio.loop();
}
// optional
void audio_info(const char *info){
Serial.print("info "); Serial.println(info);
}
void audio_id3data(const char *info){ //id3 metadata
Serial.print("id3data ");Serial.println(info);
}
void audio_eof_mp3(const char *info){ //end of file
Serial.print("eof_mp3 ");Serial.println(info);
}
void audio_showstation(const char *info){
Serial.print("station ");Serial.println(info);
}
void audio_showstreaminfo(const char *info){
Serial.print("streaminfo ");Serial.println(info);
}
void audio_showstreamtitle(const char *info){
Serial.print("streamtitle ");Serial.println(info);
}
void audio_bitrate(const char *info){
Serial.print("bitrate ");Serial.println(info);
}
void audio_commercial(const char *info){ //duration in sec
Serial.print("commercial ");Serial.println(info);
}
void audio_icyurl(const char *info){ //homepage
Serial.print("icyurl ");Serial.println(info);
}
void audio_lasthost(const char *info){ //stream URL played
Serial.print("lasthost ");Serial.println(info);
}
void audio_eof_speech(const char *info){
Serial.print("eof_speech ");Serial.println(info);
}
```