//#include <WiFi.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

const char* ssid = "********"; // Aqui nombre de la red WIFI
const char* password = "******";    //Aqui contraseña

AsyncWebServer server(80);

String request;
DynamicJsonDocument doc(200);

const int pinLED = 5;

void onRequest(AsyncWebServerRequest *request) {
    // dummy callback function for handling params, etc.
}

void onFileUpload(AsyncWebServerRequest *request, const String& filename, size_t index, uint8_t *data, size_t len, bool final) {
    // dummy callback function signature, not in used in our code
}

void onBody(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
    DeserializationError error = deserializeJson(doc, (char*)data);
    if (!error) {
      bool estado = doc["dato"];
      Serial.print("Dato recibido ---> ");
      Serial.println(estado);
      StaticJsonDocument<200> respuesta;
      if(estado){
        digitalWrite(pinLED, HIGH);
        respuesta["estado"] = true;  
      }else{
        digitalWrite(pinLED, LOW);
        respuesta["estado"] = false; 
      }
      String response;
      serializeJson(respuesta, response);
      request->send(200, "application/json", response);
    }else{
      request->send(400, "application/json", "{\"estado\":\"JSON invalido\"}");  
    }
}

void setup() {
  pinMode(pinLED, OUTPUT);
  digitalWrite(pinLED, LOW);
  // Inicializar el puerto serie
  Serial.begin(115200);
  
  // Conectar a la red WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }
  Serial.println("Conectado a la red WiFi");
  IPAddress ip = WiFi.localIP();
  Serial.print("Dirección IP: http://");
  Serial.println(ip);
  
  // Configurar las rutas de la página web
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    String html = R"HTML(
    <!DOCTYPE html>
    <html lang="es">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta http-equiv="Access-Control-Allow-Origin" content="*"/>
        <title>Esp8266</title>
        <style>
             /* The switch - the box around the slider */
            .switch {
            position: relative;
            display: inline-block;
            width: 60px;
            height: 34px;
            }
    
            .switch input {
            opacity: 0;
            width: 0;
            height: 0;
            }
    
            .slider {
            position: absolute;
            cursor: pointer;
            top: 0;
            left: 0;
            right: 0;
            bottom: 0;
            background-color: #ccc;
            -webkit-transition: .4s;
            transition: .4s;
            }
    
            .slider:before {
            position: absolute;
            content: "";
            height: 26px;
            width: 26px;
            left: 4px;
            bottom: 4px;
            background-color: white;
            -webkit-transition: .4s;
            transition: .4s;
            }
    
            input:checked + .slider {
            background-color: #2196F3;
            }
    
            input:focus + .slider {
            box-shadow: 0 0 1px #2196F3;
            }
    
            input:checked + .slider:before {
            -webkit-transform: translateX(26px);
            -ms-transform: translateX(26px);
            transform: translateX(26px);
            }
    
        .contenedorPadre {
            position: relative;
            /* background: rebeccapurple; */
            height: 95vh;
            text-align: center;
        }
    
        .contenedorHijo{
            position: absolute;
            top: 0;
            bottom: 0;
            left: 0;
            right: 0;
            width: 50%;
            height: 30%;
            margin: auto;
            box-shadow: 5px 10px #888888;
            border-radius: 7%;
            background-image: linear-gradient(to right top, #bbc9dd, #afbed8, #a6b2d3, #9ea6ce, #9899c7);
        }
        @media (max-width: 768px) {
            .contenedorHijo {
                width: 100%;
            }
        }
    
        </style>
    </head>
    <body>
        <div class="contenedorPadre">
            <div class="contenedorHijo">
                <h2>Encender Led usando 8266</h2>
                <span>Apagado</span>
                    <label class="switch">
                        <input type="checkbox" id="myCheck">
                        <span class="slider"></span>
                    </label>
                <span>Encendido</span>
            </div>
        </div>
    </body>
    <script>
        const toogle = document.querySelector("#myCheck");  
        toogle.addEventListener("change", (event) => {
            let data = {dato:toogle.checked};
            postJSON(data);
        });
    
        async function postJSON(data) {
        try {
            const response = await fetch("post/", {
                method: "POST", 
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify(data),
            });
            const result = await response.json();
            if(result.estado == true){
              document.getElementById("myCheck").checked = true;
            }else{
              document.getElementById("myCheck").checked = false;
            }
            console.log("Success:", result);
        } catch (error) {
            console.error("Error:", error);
            }
        }
    </script>
    </html>
  )HTML";
    request->send(200, "text/html", html);
  });

  // Configurar la ruta para recibir la petición POST
  server.on("/post", HTTP_POST, onRequest, onFileUpload, onBody);
  // Configurar la ruta para archivos no enccontrados
  server.onNotFound([](AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
  });
  server.begin();
}

void loop() {
  // No se requiere código adicional en el bucle principal
}
