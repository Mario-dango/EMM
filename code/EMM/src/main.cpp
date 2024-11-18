#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include "../lib/LeerSensores.h"
#include "../lib/config.h"
#include "../lib/lcdController.h"

LeerSensoresControlador controlador;
ControladorLCD pantalla;

#define ssid RED_SSID_WIFI
#define pass PASSWORD_WIFI
#define serverName "https://emetec.wetec.um.edu.ar/emmapi"  // Actualizar la URL aquí

// Variables de ejemplo de los sensores (temperatura, humedad, etc.)
float temperature, humidity, bmpTemperature, bmpPressure, bmpAltitude;
float bh1750Data, ppmCO2;

// Conectar WiFi
void setupWifi() {
  delay(100);
  Serial.print("\nConectando a ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  pantalla.initWiFi(false, ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".-");
  }
  
  String ipEMM = WiFi.localIP().toString();
  Serial.print("Conectado a la red: ");
  Serial.println(ssid);
  Serial.print("Con la siguiente IP: ");
  Serial.println(ipEMM);
  pantalla.initWiFi(true, ssid, ipEMM);
}

// Enviar los datos a través de HTTP POST en formato JSON
void enviarDatosHTTP() {
  // Crear cliente seguro para HTTPS
  WiFiClientSecure client;
  client.setInsecure(); // Para entorno de pruebas sin certificado

  // Obtener datos de los sensores
  LeerSensoresControlador::datosBMP bmpData = controlador.leerBMP();
  LeerSensoresControlador::datosDHT dhtData = controlador.leerDHT();
  bh1750Data = controlador.leerBH();
  LeerSensoresControlador::datosMQ mqData = controlador.leerMQ(dhtData.temperatura, dhtData.humedadRelativa);  

  temperature = dhtData.temperatura;
  humidity = dhtData.humedadRelativa;
  bmpTemperature = bmpData.temperatura;
  bmpPressure = bmpData.presionAbsoluta;
  bmpAltitude = bmpData.altitud;
  ppmCO2 = mqData.ppmCO2;

  // Crear el objeto JSON para enviar
  String postData = "{\"EME_n0/dht/temp\":" + String(temperature) + 
                    ",\"EME_n0/dht/hum\":" + String(humidity) + 
                    ",\"EME_n0/dht/senst\":" + String(dhtData.sensacionTermica) + 
                    ",\"EME_n0/bmp/temp\":" + String(bmpTemperature) + 
                    ",\"EME_n0/bmp/pres\":" + String(bmpPressure) + 
                    ",\"EME_n0/bmp/alt\":" + String(bmpAltitude) + 
                    ",\"EME_n0/bmp/presnm\":" + String(bmpData.presionAlNivelDelMar) + 
                    ",\"EME_n0/bh/presnm\":" + String(bh1750Data) + 
                    ",\"EME_n0/mq/ppmco2\":" + String(ppmCO2) + 
                    ",\"EME_n0/yl/lluv\":\"Proximamente\"," +  // Asumiendo que el valor es estático
                    "\"EME_n0/viento/vel\":\"Proximamente\"," +  // Asumiendo que el valor es estático
                    "\"EME_n0/viento/dir\":\"Proximamente\"}";  // Asumiendo que el valor es estático

  // Conectar al servidor
  pantalla.initMQTT(true, serverName);
  if (client.connect("emetec.wetec.um.edu.ar", 443)) {
    Serial.println("Conectado al servidor HTTPS");

    // Enviar solicitud HTTP POST
    client.println("POST /emmapi HTTP/1.1");  // Cambié la ruta aquí
    client.println("Host: emetec.wetec.um.edu.ar");
    client.println("User-Agent: ESP8266");
    client.println("Content-Type: application/json");
    client.print("Content-Length: ");
    client.println(postData.length());
    client.println();  // Línea vacía para indicar fin de encabezados
    client.println(postData);  // Cuerpo de la solicitud (datos)


    // Leer la respuesta del servidor
    while (client.connected()) {
      String line = client.readStringUntil('\n');
      if (line == "\r") {
        Serial.println("Cuerpo de la respuesta:");
        break;
      }
    }

    // Imprimir la respuesta del servidor
    String response = client.readString();
    Serial.println(response);

    pantalla.enviandoDatos();
    pantalla.mostrarDatos(
      dhtData.temperatura, dhtData.humedadRelativa, dhtData.sensacionTermica,
      bh1750Data,
      mqData.ppmCO2,
      bmpData.presionAbsoluta, bmpData.altitud, bmpData.temperatura);

  } else {
    Serial.println("Fallo al conectar al servidor HTTPS");
    pantalla.initMQTT(false, serverName);
  }

  // Finalizar la conexión
  client.stop();
}

void setup() {
  Serial.begin(115200);
  String thisBoard = ARDUINO_BOARD;
  Serial.println(thisBoard);

  // Inicializar controlador de pantalla
  pantalla.init();
  pantalla.showInit();

  // Inicializar controlador de sensores
  controlador.initControlador(BMP_TYPE_280);

  // Conectar a la red WiFi
  setupWifi();

  // Enviar los datos a través de HTTP
  enviarDatosHTTP();

  // Poner en modo de sueño profundo
  Serial.println("\n*** Entrando al modo Deep Sleep***\n");
  pantalla.deepSleep();
  
  ESP.deepSleep(5 * 1000000); // 5 segundos de Deep Sleep
}

void loop() {
  // No es necesario hacer nada en el loop
}
