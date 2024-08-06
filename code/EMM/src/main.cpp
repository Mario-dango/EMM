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
  // Mostrar en el LCD que se está conectando a la red
  pantalla.initWiFi(false, ssid);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print(".-");
  }
  pantalla.initWiFi(true, ssid);
  ipEMM = WiFi.localIP().toString().c_str();
  // Serial.printf("IPADDRESS: %s", WiFi.localIP());   // No sirve para parsear la IPADDRESS cómo string
  Serial.print(WiFi.localIP().toString());
  Serial.print("\nConectado a la red: ");
  Serial.println(ssid);
  Serial.print("Con la siguiente IP: ");
  Serial.println(ipEMM);
  // // Mostrar en el LCD que se pudo conectar a la red
  // pantalla.infoConexion(WiFi.status(), ssid, broker, brokerUser, ipEMM);
}

void reconectar()
{
  Serial.print("\nConectando al broker: ");
  Serial.println(broker);
  pantalla.initMQTT(false, broker);
  while (!client.connected())
  {
    if (client.connect("EMM"))
    {
      Serial.print("\nConectado al broker: ");
      Serial.println(broker);
      client.subscribe(chau);
      pantalla.initMQTT(true, broker);
      // Mostrar en el LCD que se pudo conectar a la red
      Serial.print("Se ha REconecatado re loco");
      pantalla.infoConexion(client.connected(), ssid, broker, brokerUser, WiFi.localIP().toString());
    }
    else
    {
      Serial.print("Error de conexión, rc=");
      Serial.print(client.state());
      Serial.println(".-");
      pantalla.initMQTT(false, broker);

      // Mostrar en el LCD que se pudo conectar a la red
      pantalla.reconectando(ssid, broker, brokerUser);
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
    reconectar();
  }
  client.loop();
  pantalla.enviandoDatos();

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
  // bool local = true;

  if (!local)
  {
    // Publicar temperatura ETec_broker
    snprintf(mensaje, 20, "%.2f °C", dhtData.temperatura);
    client.publish(TOPIC_DHT_TEMP, mensaje);
    // Publicar humedad ETec_broker
    snprintf(mensaje, 20, "%.2f %%HR", dhtData.humedadRelativa);
    client.publish(TOPIC_DHT_HUM, mensaje);
    // Publicar sensación térmica ETec_broker
    snprintf(mensaje, 20, "%.2f °C", dhtData.sensacionTermica);
    client.publish(TOPIC_DHT_SENST, mensaje);

    // Publicar temperatura bmp ETec_broker
    snprintf(mensaje, 20, "%.2f hPa", bmpData.temperatura);
    client.publish(TOPIC_BMP_TEMP, mensaje);
    // Publicar presion ETec_broker
    snprintf(mensaje, 20, "%.2f hPa", bmpData.presionAbsoluta);
    client.publish(TOPIC_BMP_PRES, mensaje);
    // Publicar altitud ETec_broker
    snprintf(mensaje, 20, "%.2f hPa", bmpData.altitud);
    client.publish(TOPIC_BMP_ALT, mensaje);
    // Publicar presion a nivel del mar ETec_broker
    snprintf(mensaje, 20, "%.2f hPa", bmpData.presionAlNivelDelMar);
    client.publish(TOPIC_BMP_PRESNM, mensaje);

    // Publicar luz ETec_broker
    snprintf(mensaje, 20, "%.2f lux", bh1750Data);
    client.publish(TOPIC_BH_LUZ, mensaje);

    // Publicar ppmCO2 ETec_broker
    snprintf(mensaje, 20, "%.2f ppmCO2", mqData.ppmCO2);
    client.publish(TOPIC_MQ_PPMCO2, mensaje);

    // Publicar velocidad del Viento ETec_broker
    snprintf(mensaje, 20, "Proximamente");
    client.publish(TOPIC_VIENTO_VELOCIDAD, mensaje);
    // Publicar dirección del viento ETec_broker
    snprintf(mensaje, 20, "Proximamente");
    client.publish(TOPIC_VIENTO_DIRECCION, mensaje);

    // Publicar lluvia ETec_broker
    snprintf(mensaje, 20, "Proximamente");
    client.publish(TOPIC_YL_LLUVIA, mensaje);
  }
  else
  {
    //**************************Envio de datos a servidor local de Mario
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

  Serial.print("\n*** Entrando al modo Deep Sleep***\n");
  pantalla.deepSleep();

  //****Para ESP8266****/
  // ESP.deepSleep(15*60*1000000);    // DEEP sleep 15 minutos
  ESP.deepSleep(5 * 1000000); // DEEP sleep de 5 segundos
}

void loop()
{
}
