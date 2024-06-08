# Tareas y Semáfors en ESP32

***Descripción***
En aquest code se gestiona per controlar un LED:

* ledSemaphore: Semáfor utilitzat per sincrontizar el LED.
* encenderLED(void * parameter): Tasca que controla el LED si s'encen o s'apaga. Toma el semáfor abans de encendre el  LED y el libera quan s'apaga.
* setup(): Configura el porto serial y el pin del LED, crea el semáfor y activa la tasca encenderLED.

**Funcionalidad del Semáforo**
El semáfor asegura que una instancia de la tarea encenderLED pugui controlar el LED al mateix temps. Aixo es útil en aplicacions on mmoltes tareas podrían intentar accedir al mateix LED, o en casos de futures practiques, altres tipus de recursos


### Código

```cpp
#include <Arduino.h>

void setup() {
    Serial.begin(112500);
    // Creación de una nueva tarea
    xTaskCreate(
        anotherTask,   // Función de la tarea
        "another Task", // Nombre de la tarea
        10000,          // Tamaño de la pila de la tarea
        NULL,           // Parámetro de la tarea
        1,              // Prioridad de la tarea
        NULL            // Manejador de la tarea
    );
}

// La función loop() es invocada por la tarea loopTask de Arduino ESP32
void loop() {
    Serial.println("this is ESP32 Task");
    delay(1000);
}

// Esta función será invocada cuando se cree la tarea anotherTask
void anotherTask(void * parameter) {
    // Bucle infinito
    for (;;) {
        Serial.println("this is another Task");
        delay(1000);
    }
    // Borrar la tarea cuando termine, esto nunca sucederá porque es un bucle infinito
    vTaskDelete(NULL);
}

## Progrma 2: Gestión de un Semáforo para Controlar un LED
 ### Código:
 #include <Arduino.h>
#include <WiFi.h>

SemaphoreHandle_t ledSemaphore; // Variable para el semáforo del LED
const int ledPin = 23; // Pin del LED

void encenderLED(void * parameter) {
    for (;;) {
        xSemaphoreTake(ledSemaphore, portMAX_DELAY); // Tomar el semáforo
        digitalWrite(ledPin, HIGH); // Encender el LED
        delay(1000); // Esperar 1 segundo
        digitalWrite(ledPin, LOW); // Apagar el LED
        delay(1000); // Esperar 1 segundo
        xSemaphoreGive(ledSemaphore); // Liberar el semáforo
    }
}

void setup() {
    Serial.begin(115200);
    pinMode(ledPin, OUTPUT); // Configurar el pin del LED como salida

    // Crear el semáforo para el LED
    ledSemaphore = xSemaphoreCreateBinary();
    if (ledSemaphore == NULL) {
        Serial.println("Error al crear el semáforo para el LED");
        while (1);
    }

    // Iniciar la tarea de encenderLED
    xTaskCreate(encenderLED, "encenderLED", 10000, NULL, 1, NULL);
}

void loop() {
    // El loop principal no se utiliza en este ejemplo
}

