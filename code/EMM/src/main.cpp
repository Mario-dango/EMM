#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "../lib/LeerSensores.h"
#include "../lib/config.h"
#include "../lib/lcdController.h"

LeerSensoresControlador controlador;
ControladorLCD pantalla;

#define ssid RED_SSID_WIFI
#define pass PASSWORD_WIFI
#define brokerUser USUARIO_BROKER
#define brokerPass PASSWORD_BROKER
#define broker DIRECCION_BROKER

//  Topicos del Broker Mosquitto MQTT
#define senBH1750 "EMM/bh1750"
#define senBMP180 "EMM/bmp180"
#define senDHT11 "EMM/dht11"
#define senMQ135 "EMM/mq135"
#define chau "EMM/test"
//  Topicos Del broker ETec
#define temperaturaDHT "temp"
#define humedadDHT "hum"
#define presionBMP "bp"
#define luminosidad "luz"
#define calidadAire "aire"
#define velocidadViento "velocidad"
#define direccionViento "direccion"
#define sensorDeLluvia "lluvia"

char mensaje[80];

WiFiClient esp_EMM;
const char *ipEMM;
PubSubClient client(esp_EMM);

void setupWifi()
{
  delay(100);
  Serial.print("\nConectando a ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print(".-");
  }

  ipEMM = WiFi.localIP().toString().c_str();
  Serial.print("\nConectado a la red: ");
  Serial.println(ssid);
  Serial.print("\nCon la siguiente IP: ");
  Serial.println(ipEMM);
}

void reconectar()
{
  Serial.print("\nConectando al broker: ");
  Serial.println(broker);
  while (!client.connected())
  {
    if (client.connect("EMM"))
    {
      Serial.print("\nConectado al broker: ");
      Serial.println(broker);
      client.subscribe(chau);
    }
    else
    {
      Serial.print("Error de conexión, rc=");
      Serial.print(client.state());
      Serial.println(".-");
      delay(1000);
    }
  }
}

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Mensaje recibido: ");
  Serial.println(topic);
  for (unsigned int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

unsigned long delayTime;

void envioMQTT()
{
  //  Reconectar si se ha desconectado del Broker
  if (!client.connected())
  {
    pantalla.infoConexion(!client.connected(), ssid, broker, brokerUser);
    reconectar();
  }
  client.loop();
  pantalla.infoConexion(!client.connected(), ssid, broker, brokerUser, ipEMM);

  //  Declaración de variables de lectura para sensores tomando cómo estructura de datos la de la clase LeerSensoresControlador
  LeerSensoresControlador::datosBMP bmpData;
  LeerSensoresControlador::datosDHT dhtData;
  LeerSensoresControlador::datosMQ mqData;
  float bh1750Data;

  //  Lectura y asignación de párametros de los sensores
  dhtData = controlador.leerDHT();
  bmpData = controlador.leerBMP();
  bh1750Data = controlador.leerBH();
  mqData = controlador.leerMQ(dhtData.temperatura, dhtData.humedadRelativa);
  // mqData = controlador.leerMQ();

  bool local = false;

  if (!local)
  {
    // Publicar temperatura ETec_broker
    snprintf(mensaje, 20, "%.2f °C", (bmpData.temperatura + dhtData.temperatura) / 2);
    client.publish(temperaturaDHT, mensaje);
    // Publicar humedad ETec_broker
    snprintf(mensaje, 20, "%.2f %%HR", dhtData.humedadRelativa);
    client.publish(humedadDHT, mensaje);
    // Publicar presion ETec_broker
    snprintf(mensaje, 20, "%.2f Pa", bmpData.presionAbsoluta);
    client.publish(presionBMP, mensaje);
    // Publicar luz ETec_broker
    snprintf(mensaje, 20, "%.2f lux", bh1750Data);
    client.publish(luminosidad, mensaje);
    // Publicar ppmCO2 ETec_broker
    snprintf(mensaje, 20, "%.2f ppmCO2", mqData.ppmCO2);
    client.publish(calidadAire, mensaje);
    // Publicar velocidad del Viento ETec_broker
    snprintf(mensaje, 20, "Proximamente");
    client.publish(velocidadViento, mensaje);
    // Publicar dirección del viento ETec_broker
    snprintf(mensaje, 20, "Proximamente");
    client.publish(direccionViento, mensaje);
    // Publicar lluvia ETec_broker
    snprintf(mensaje, 20, "Proximamente");
    client.publish(sensorDeLluvia, mensaje);
  }
  else
  {
    // Publicar datos del BMP180
    snprintf(mensaje, 75,
             "estado:OK temperatura:%.2f presAbs:%.2f presNivlMar:%.2f altit:%.2f",
             // bmpData.estado,
             bmpData.temperatura,
             bmpData.presionAbsoluta,
             bmpData.presionAlNivelDelMar,
             bmpData.altitud);
    client.publish(senBMP180, mensaje);

    // Publicar datos del BH1750
    snprintf(mensaje, 20, "Lux:%.2f", bh1750Data);
    client.publish(senBH1750, mensaje);

    // Publicar datos del DHT11
    snprintf(mensaje, 40, "hum:%.2f temp:%.2f sensacionTerm:%.2f",
             // dhtData.estado,
             dhtData.humedadRelativa,
             dhtData.temperatura,
             dhtData.sensacionTermica);
    client.publish(senDHT11, mensaje);

    // Publicar datos del MQ135
    snprintf(mensaje, 75, "rzero:%.2f correctRZero:%.2f res:%.2f ppmCO2:%.2f ppmCorreg:%.2f",
             mqData.rzero,
             mqData.zeroCorregido,
             mqData.resistencia,
             mqData.ppmCO2,
             mqData.ppmCorregidas);
    client.publish(senMQ135, mensaje);
  }

  pantalla.mostrarDatos(
      dhtData.temperatura, dhtData.humedadRelativa, dhtData.sensacionTermica,
      bh1750Data,
      mqData.ppmCO2,
      bmpData.presionAbsoluta, bmpData.altitud, bmpData.temperatura);
}

void setup()
{
  Serial.begin(115200);
  String thisBoard = ARDUINO_BOARD;
  Serial.println(thisBoard);

  //  Inicializar controlador de pantalla
  pantalla.init();
  pantalla.showInit();

  //  Inicializar controlador de sensores
  controlador.initControlador(BMP_TYPE_280);

  //  Inicializar conexión a la red
  setupWifi();
  client.setServer(broker, 1883);
  client.setCallback(callback);

  envioMQTT();
  // ESP.deepSleep(15*60*1000000);    // DEEP sleep 15 minutos
  ESP.deepSleep(5 * 1000000); // DEEP sleep de 5 segundos
}

void loop()
{
}
