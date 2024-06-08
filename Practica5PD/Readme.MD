# Monitor de Temperatura y Humedad con ESP32, Sensor AHT10/AHT20 y Pantalla OLED

El seguent programa activara els sensors AHT10 i AHT20 amb ESP32 para captar la temperatura y humitat i mostra les daddes en una pantalla OLED

 ## Funcionamient del code

1. Configuració del Hardware:

- Per utilitzar tot el hardware mencionat abans incluim les biblitoeques:
  - Adafruit_AHTX0 () (sensors de temperatura i humitat)
  - Adafruit_GFX i Adafruit_SSD1306 (pantalla OLED)
- Sobre la pantalla OLED, tambe s'ha de espeificar las dimensions i el directori I2C

2. Inicialització setup():

- Se inicialtiza el bus I2C (Wire.begin()).
- Se inicia la comunicació serial para el monitoreig mitjançant el port serie.
- Se inicialtiza el sensor AHT10/AHT20 (aht.begin()).
- Se inicialitza la pantalla OLED (- display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)). (Si qualsevol de les dos inicialitzacions anteriors fallan, el programa es deté)

3. Medició y Visualizació loop():

- S'obté les dades de mesura dels sensor (aht.getEvent(&humidity, &temp)).
- Es neteja la pantalla (- display.clearDisplay()) i es configuran los parámetres del text
- S'envien les dades a la pantalla i el programa espera mig segon abans de una nueva obtencio de mesures


## Código

```cpp
#include <Adafruit_AHTX0.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define SCREEN_WIDTH 128 // Ancho de la pantalla OLED, en píxeles
#define SCREEN_HEIGHT 32 // Alto de la pantalla OLED, en píxeles

#define OLED_RESET -1 // Pin de reset (o -1 si se comparte el pin de reset del Arduino)
#define SCREEN_ADDRESS 0x3C // Dirección de la pantalla OLED; 0x3D para 128x64, 0x3C para 128x32

Adafruit_AHTX0 aht;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
    Wire.begin();
    Serial.begin(115200);
    Serial.println("Adafruit AHT10/AHT20 demo!");

    if (!aht.begin()) {
        Serial.println("¡No se pudo encontrar el AHT! ¡Verifique la conexión!");
        while (1) delay(10);
    }
    Serial.println("AHT10 o AHT20 encontrado");

    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("¡Error al asignar memoria para SSD1306!"));
        for (;;);
    }

    display.display();
    delay(2000);
    display.clearDisplay();
}

void loop() {
    sensors_event_t humidity, temp;
    aht.getEvent(&humidity, &temp); // Obtener los objetos de temperatura y humedad con datos actualizados

    display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print("Temperatura: ");
    display.println(temp.temperature);
    display.print("Humedad: ");
    display.println(humidity.relative_humidity);

    display.display();
    Serial.print("Temperatura: ");
    Serial.print(temp.temperature);
    Serial.println(" grados C");
    Serial.print("Humedad: ");
    Serial.print(humidity.relative_humidity);
    Serial.println("% HR");

    delay(500);
}
