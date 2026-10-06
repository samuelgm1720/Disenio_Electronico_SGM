# Práctica 1 — Temperatura y humedad en Ubidots

El ESP32 lee el sensor DHT11 y publica los datos en un dispositivo de Ubidots llamado `esp32`, con tres variables: `temperatura`, `humedad` y `adc`. Los datos se visualizan en un dashboard (`Temp-Hum`) con un termómetro y un medidor tipo gauge.

Informe: [Practica1_SamuelGil.pdf](Practica1_SamuelGil.pdf). El informe de esta práctica contiene solo las evidencias; no incluye código.

## Evidencias

**Variables recibidas en Ubidots**

![Dispositivo esp32 en Ubidots con las variables temperatura, humedad y adc](img/01-ubidots-variables.jpg)

**Montaje: TTGO T-Display con el DHT11**

<img src="img/02-montaje-ttgo-dht11.jpg" alt="ESP32 TTGO T-Display mostrando temperatura y humedad, conectado al sensor DHT11" width="320">

**Dashboard**

![Dashboard Temp-Hum con medidor de humedad y termómetro](img/03-dashboard.jpg)
