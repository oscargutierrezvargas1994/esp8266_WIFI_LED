# Encender led con 8266 a traves de la red
## Circuito
![Sketch](https://github.com/oscargutierrezvargas1994/esp8266_WIFI_LED/blob/main/Sketch%202_bb.png)

## Requisitos hardware

- Modulo ESP8266.
- LED 5mm.
- Resistencia.
- Protoboard de 100 o mas puntos.
- 4 cables dupont macho - macho de 10 cm o mas.  
---

## Requisitos de sofware

- Arduino IDE 1.8.16.
- Navegador web de tu eleccion (Firefox, Chrome , safari, etc.)  
---

## Intrucciones

1.- Descargar el archivo [esp8266_WIFI_LED](https://github.com/oscargutierrezvargas1994/esp8266_WIFI_LED/archive/refs/heads/main.zip).zip del repositorio

2.- Abrir el archivo **servidor_web.ino** de la carpeta **servidor_web** con Arduino IDE

3.- Descargar biblioteca **esp8266** , **ArduinoJson** y **ESPAsyncWebSrv** de Herramientas -> Administrar bibliotecas... 

4.- Descargar las libreria [ESPAsyncTCP.zip](https://github.com/me-no-dev/ESPAsyncTCP), para posteriormente subirlo a Arduino IDE  a traves de las opciones de Programa -> Añadir fichero ... (selecionar archivo descargado)    

5.- Conectar y seleccionar la placa como **Generic ESP8266 Module** con el puerto correspodiente 

6.- Verificar el codigo con Arduino IDE para revisar errores

7.- Subir el codigo a la esp8266

8.- Abrir **Monitor serie** para obtener IP local del esp8266

9.- Copiar ruta entregada http://192.1... y pegar al URL de cualquier navegador de su pc, celular o tablet dentro de la  misma red.

  
*Se puede agregar  una resistencia entre 1 - 100 ohmnios para reducir la luz del led 
