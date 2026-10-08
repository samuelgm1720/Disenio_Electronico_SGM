# Prácticas de Diseño Electrónico

**Autor:** Samuel Gil Morales

Prácticas de laboratorio con un ESP32 (TTGO T-Display) y un sensor DHT11 conectados a la plataforma IoT [Ubidots](https://ubidots.com/). El ESP32 mide temperatura y humedad, las muestra en su pantalla y las publica en la nube; desde el dashboard de Ubidots se controlan dos interruptores que se reflejan en la pantalla del dispositivo.

## Contenido

| Práctica | Qué se hizo | Archivos |
|---|---|---|
| [Práctica 1](practica-1/) | Envío de temperatura, humedad y lectura del ADC a Ubidots, y dashboard con termómetro y medidor | Informe en PDF y capturas |
| [Práctica 2](practica-2/) | Control desde Ubidots: dos switches del dashboard encienden indicadores en la pantalla del ESP32 | Informe en PDF, código y fotos |
| [Práctica 3](practica-3/) | Portal de configuración WiFi en modo AP: la red se configura desde el navegador, se guarda en la EEPROM y la placa pasa a publicar en Ubidots | Informe en PDF, código y capturas |

## Hardware

- ESP32 TTGO T-Display (pantalla TFT integrada)
- Sensor de temperatura y humedad DHT11, con la señal de datos en el GPIO 27
- Entrada analógica en el GPIO 33
- Botón integrado en el GPIO 0, usado en la Práctica 3 para volver al modo de configuración

## Librerías

| Librería | Uso | Repositorio |
|---|---|---|
| `UbidotsEsp32Mqtt` | Conexión WiFi y MQTT con Ubidots | [ubidots/esp32-mqtt](https://github.com/ubidots/esp32-mqtt) |
| `PubSubClient` | Dependencia de la librería de Ubidots | [knolleary/pubsubclient](https://github.com/knolleary/pubsubclient) |
| `DHT sensor library` | Lectura del DHT11 | [adafruit/DHT-sensor-library](https://github.com/adafruit/DHT-sensor-library) |
| `TFT_eSPI` | Manejo de la pantalla TFT | [Bodmer/TFT_eSPI](https://github.com/Bodmer/TFT_eSPI) |

`TFT_eSPI` se configura por archivo: en `User_Setup_Select.h` hay que dejar activa la línea `#include <User_Setups/Setup25_TTGO_T_Display.h>`, que es la configuración que trae la librería para esta placa.

La Práctica 3 usa además `WiFi`, `WebServer` y `EEPROM`, que vienen con el soporte de ESP32 para Arduino y no se instalan aparte.

## Cómo ejecutar el código

**Práctica 2**

1. Instalar el soporte de ESP32 en el Arduino IDE y las librerías de la tabla.
2. Abrir `practica-2/Practica2/Practica2.ino`.
3. Reemplazar `TU_TOKEN_DE_UBIDOTS` por el token de la cuenta propia de Ubidots y ajustar `WIFI_SSID` y `WIFI_PASS`.
4. Cargar el programa en la placa.

**Práctica 3**

El código es un proyecto de PlatformIO (`practica-3/src/main.cpp`). Depende de `data.h` y `Settings.h`, que no están en el informe y por eso no están en el repositorio; hay que agregarlos en `src/` para compilar. Los detalles están en el [README de la práctica](practica-3/).

> El token de Ubidots es una credencial: no se sube al repositorio. Por eso aparece como marcador en el código y tapado en los informes de las Prácticas 2 y 3.

## Estructura

```
.
├── README.md
├── practica-1/
│   ├── README.md
│   ├── Practica1_SamuelGil.pdf
│   └── img/
├── practica-2/
│   ├── README.md
│   ├── Practica2_SamuelGil.pdf
│   ├── Practica2/
│   │   └── Practica2.ino
│   └── img/
└── practica-3/
    ├── README.md
    ├── Practica3_SamuelGil.pdf
    ├── src/
    │   └── main.cpp
    └── img/
```
