# Sonic

Librería simple para controlar sensores ultrasónicos con Arduino.  

Permite “gritar” con el sensor y medir la distancia en centímetros de manera clara, con timeout configurable. Devuelve `-1` si no se obtiene medición válida.

## Instalación

### Manual
1. Descarga el repositorio como ZIP o clona `https://github.com/Axxel-otl/Sonic`.
2. Copia la carpeta `Sonic/` en tu carpeta `libraries/` del Arduino IDE.
3. Reinicia el IDE.

### Uso básico

```cpp
#include <Sonic.h>

Sonic hldr;
long distance;

void setup() {
  Serial.begin(9600);
  hldr.attach(9, 10); // trig en pin 9, echo en pin 10
}

void loop() {
  hldr.scream(distance, 30); // límite 30 cm

  if (distance == -1) {
    Serial.println("Fuera de rango");
  } else {
    Serial.print("Distancia: ");
    Serial.print(distance);
    Serial.println(" cm");
  }

  delay(500);
}
