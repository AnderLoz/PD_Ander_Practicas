#include <Arduino.h>
#include <WiFi.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////// PARTE 1/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
#include <Arduino.h>

void setup()
{
Serial.begin(112500);
//we create a new task here 
xTaskCreate(
anotherTask, //Task function. 
"another Task", // name of task. 
10000, // Stack size of task /
NULL, //parameter of the task /
1, // priority of the task /
NULL); // Task handle to keep track of created task /
}
// the forever loop() function is invoked by Arduino ESP32 loopTask //
void loop()
{
Serial.println("this is ESP32 Task");
delay(1000);
}
// this function will be invoked when additionalTask was created //
void anotherTask( void * parameter )
{
//loop forever /
for(;;)
{
Serial.println("this is another Task");
delay(1000);
}
/// delete a task when finish,
Practica4.MD 2024-03-12
6 / 6
this will never happen because this is infinity loop //
vTaskDelete( NULL );
}
*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////// PARTE 2 /////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
} // Paréntesis de cierre de setup() estaba ausente, se ha añadido


void loop() {
  // El loop principal no se utiliza en este ejemplo
}
