# Lectura de Archiu desde una Tarjeta SD amb Arduino

## Objetiu
El objectiu es llegir un archiu de text desde una tarjeta SD

***setup():***

- Intenta inicialtizar la tarjeta SD llamando a SD.begin(5).
- Si la inicialtzació falla, fa un print de un missatge de error i termina el programa, si funciona,
es fa un print amb un missatge exitos
- Intenta obrir el archiu archivo.txt amb un SD.open("/archivo.txt").
- Com la inicialitzacio fa un print de error i es termina o de exit


***Lectura de Archiu:***

- while (myFile.available()): Llegeix byte a byte el archiu
- Serial.write(myFile.read()): Escriu cada byte de lo llegit en el while.
- myFile.close(): Fa un close del archiu quan termina el while
- Explicació de las Funcions Clau
- SD.begin(5): Inicialitza la tarjeta SD. El (5) especifica el pin de selecció del chip (CS).
- SD.open("/archivo.txt"): Abre el archiu archivo.txt en la tarjeta SD para lectura.
- myFile.available():Fa una consulta del numero de bytes disponibles
- myFile.read(): Fa una lectura de un byte desde el archiu
- myFile.close()

***Uso Práctico***

Es util per aplicacions o programas que necesiten llegir dades almacenadas en tarjetas SD. Com la lectura de configuracions, registres de dades o almacenament de dades.
El code seguent es un exemple efectiu de com es pot interactuar amb aquesta tarjeta SD.


## Código

```cpp
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

File myFile;

void setup() {
    Serial.begin(115200);
    Serial.print("Iniciando SD ...");

    if (!SD.begin(5)) {
        Serial.println("No se pudo inicializar");
        return;
    }

    Serial.println("inicializacion exitosa");
    myFile = SD.open("/archivo.txt"); // abrimos el archivo

    if (myFile) {
        Serial.println("archivo.txt:");
        while (myFile.available()) {
            Serial.write(myFile.read());
        }
        myFile.close(); // cerramos el archivo
    } else {
        Serial.println("Error al abrir el archivo");
    }
}

void loop() {
    // El loop principal no se utiliza en este ejemplo
}
