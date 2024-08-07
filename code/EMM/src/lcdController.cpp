#include "../lib/lcdController.h"

ControladorLCD::ControladorLCD() : pantalla(LCD_ADDRESS_I2C, LCD_COLUMNAS, LCD_FILAS)
{
}

void ControladorLCD::init()
{
    this->pantalla.begin(); // If you are using more I2C devices using the Wire library use lcd.begin(false)
                            // this stop the library(LCD_I2C) from calling Wire.begin()

    // Crear los caracteres personalizados
    this->pantalla.createChar(0, a_acute);
    this->pantalla.createChar(1, e_acute);
    this->pantalla.createChar(2, i_acute);
    this->pantalla.createChar(3, o_acute);
    this->pantalla.createChar(4, u_acute);
    this->pantalla.createChar(5, n_tilde);
    this->pantalla.createChar(6, grado);
    this->pantalla.createChar(7, caraV);
    this->pantalla.backlight();
}

void ControladorLCD::showInit()
{
    this->pantalla.print("Inicializando"); // You can make spaces using well... spaces
    this->pantalla.setCursor(0, 1);        // Or setting the cursor in the desired position.
    this->pantalla.print("Comunicaci");
    this->pantalla.write(3);
    this->pantalla.print("n");
    this->pantalla.setCursor(0, 0); // Or setting the cursor in the desired position.
    delay(1500);
    this->pantalla.clear();
}

void ControladorLCD::initWiFi(boolean estado, const char *red, String IP)
{
    if (estado)
    {
        this->pantalla.clear();
        this->pantalla.printf("Se ha unido al"); // You can make spaces using well... spaces
        this->pantalla.setCursor(0, 1);          // Or setting the cursor in the desired position.
        this->pantalla.printf("WiFi:%s", red);   // You can make spaces using well... spaces
        this->pantalla.setCursor(0, 0);
        delay(1800);
        this->pantalla.clear();
        
        this->pantalla.printf("La direcci"); // You can make spaces using well... spaces
        this->pantalla.write(3);
        this->pantalla.printf("n IP"); 
        this->pantalla.setCursor(0, 1);
        this->pantalla.print(IP);   // You can make spaces using well... spaces
        this->pantalla.setCursor(0, 0);
        delay(1800);
    }
    else
    {
        this->pantalla.clear();
        this->pantalla.printf("Conectando a la"); // You can make spaces using well... spaces
        this->pantalla.setCursor(0, 1);           // Or setting the cursor in the desired position.
        this->pantalla.printf("red WiFi -> EMs"); // You can make spaces using well... spaces
        this->pantalla.setCursor(0, 0);
        delay(1800);
    }
}

void ControladorLCD::initMQTT(boolean estado, const char *broker)
{
    if (estado)
    {
        this->pantalla.clear();
        this->pantalla.printf("Canal al Broker"); // You can make spaces using well... spaces
        this->pantalla.setCursor(0, 1);           // Or setting the cursor in the desired position.
        this->pantalla.printf("Establecido !");   // You can make spaces using well... spaces
        this->pantalla.setCursor(0, 0);
        delay(1800);
        this->pantalla.setCursor(0, 0);
    }
    else
    {
        this->pantalla.clear();
        this->pantalla.printf("MQTT conectando"); // You can make spaces using well... spaces
        this->pantalla.setCursor(0, 1);           // Or setting the cursor in the desired position.
        this->pantalla.printf("%s", broker);      // You can make spaces using well... spaces
        this->pantalla.setCursor(0, 0);
        delay(1800);
    }
}

void ControladorLCD::enviandoDatos()
{

    this->pantalla.printf("EMM operativa!");   // You can make spaces using well... spaces
    this->pantalla.setCursor(0, 1);            // Or setting the cursor in the desired position.
    this->pantalla.printf("Enviando datos.."); // You can make spaces using well... spaces
    this->pantalla.setCursor(0, 0);
    delay(1800);
}

void ControladorLCD::reconectando(
    const char *red,
    const char *broker,
    const char *userBroker)
{
    this->pantalla.clear();
    this->pantalla.printf("Red WiFi:"); // You can make spaces using well... spaces
    this->pantalla.setCursor(0, 1);     // Or setting the cursor in the desired position.
    this->pantalla.printf("%s", red);   // You can make spaces using well... spaces
    this->pantalla.setCursor(0, 0);
    delay(2000);
    this->pantalla.clear();
    this->pantalla.printf("Usuario MQTT:");  // You can make spaces using well... spaces
    this->pantalla.setCursor(0, 1);          // Or setting the cursor in the desired position.
    this->pantalla.printf("%s", userBroker); // You can make spaces using well... spaces
    this->pantalla.setCursor(0, 0);
    delay(2000);
    this->pantalla.clear();
    this->pantalla.printf("IP del Broker:"); // You can make spaces using well... spaces
    this->pantalla.setCursor(0, 1);          // Or setting the cursor in the desired position.
    this->pantalla.printf("%s", broker);     // You can make spaces using well... spaces
    this->pantalla.setCursor(0, 0);
    delay(2000);
}

void ControladorLCD::infoConexion(
    boolean estado,
    const char *red,
    const char *broker,
    const char *userBroker,
    String ip)
{
    this->pantalla.clear();
    if (!estado)
    {
        this->pantalla.printf("Sin Conexi"); // You can make spaces using well... spaces
        this->pantalla.write(3);
        this->pantalla.printf("n."); // You can make spaces using well... spaces

        this->pantalla.setCursor(0, 1);           // Or setting the cursor in the desired position.
        this->pantalla.printf("Reintentando..."); // You can make spaces using well... spaces
        this->pantalla.setCursor(0, 0);
        delay(2000);
        this->pantalla.clear();
    }
    else
    {
        this->pantalla.printf("Conectado a red:"); // You can make spaces using well... spaces
        this->pantalla.setCursor(0, 1);            // Or setting the cursor in the desired position.
        this->pantalla.printf("%s", red);          // You can make spaces using well... spaces
        this->pantalla.setCursor(0, 0);
        delay(2000);
        this->pantalla.clear();
        this->pantalla.printf("Usuario MQTT:");  // You can make spaces using well... spaces
        this->pantalla.setCursor(0, 1);          // Or setting the cursor in the desired position.
        this->pantalla.printf("%s", userBroker); // You can make spaces using well... spaces
        this->pantalla.setCursor(0, 0);
        delay(2000);
        this->pantalla.clear();
        this->pantalla.printf("IP del Broker:"); // You can make spaces using well... spaces
        this->pantalla.setCursor(0, 1);          // Or setting the cursor in the desired position.
        this->pantalla.printf("%s", broker);     // You can make spaces using well... spaces
        this->pantalla.setCursor(0, 0);
        delay(2000);
        this->pantalla.clear();
        this->pantalla.printf("IP de la EMM:"); // You can make spaces using well... spaces
        this->pantalla.setCursor(0, 1);         // Or setting the cursor in the desired position.
        this->pantalla.print(ip);        // You can make spaces using well... spaces
        this->pantalla.setCursor(0, 0);
        delay(2000);
        this->pantalla.clear();
    }
}

void ControladorLCD::mostrarDatos(
    float tempDHT, float hum, float sensacionT,
    float lm,
    float ppmco2,
    float pres, float altitud, float tempBMP)
{
    //  Limpiar pantalla luego de indicar que se envían los datos
    this->pantalla.clear();
    //  Mostrar los datos del DHT
    this->pantalla.printf("DHT22 ");
    this->pantalla.write(6);
    this->pantalla.printf("C y %%HR");                    // You can make spaces using well... spaces
    this->pantalla.setCursor(0, 1);                       // Or setting the cursor in the desired position.
    this->pantalla.printf("T:%.2f H:%.2f", tempDHT, hum); // You can make spaces using well... spaces
    this->pantalla.setCursor(0, 0);                       // Or setting the cursor in the desired position.
    delay(3000);
    this->pantalla.clear();
    //  Mostrar los datos del DHT
    this->pantalla.printf("Sensaci");
    this->pantalla.write(3);
    this->pantalla.printf("n "); // You can make spaces using well... spaces
    this->pantalla.setCursor(0, 1);
    this->pantalla.printf("T");
    this->pantalla.write(1);
    this->pantalla.printf("rmica: %.2f", sensacionT);
    this->pantalla.write(6);
    this->pantalla.printf("C");
    this->pantalla.setCursor(0, 0); // Or setting the cursor in the desired position.
    delay(3000);
    this->pantalla.clear();
    //  Mostrar los datos del MQ135
    this->pantalla.printf("MQ135 ppm de CO2");     // You can make spaces using well... spaces
    this->pantalla.setCursor(0, 1);                // Or setting the cursor in the desired position.
    this->pantalla.printf("ppmCO2: %.2f", ppmco2); // You can make spaces using well... spaces
    this->pantalla.setCursor(0, 0);                // Or setting the cursor in the desired position.
    delay(3000);
    this->pantalla.clear();
    //  Mostrar los datos del DHT
    this->pantalla.printf("BMP280 hPa y m");              // You can make spaces using well... spaces
    this->pantalla.setCursor(0, 1);                       // Or setting the cursor in the desired position.
    this->pantalla.printf("P:%.1fA:%.1f", pres, altitud); // You can make spaces using well... spaces
    this->pantalla.setCursor(0, 0);                       // Or setting the cursor in the desired position.
    delay(3000);
    this->pantalla.clear();
    //  Mostrar los datos del DHT
    this->pantalla.printf("BH1750 Lumenes");   // You can make spaces using well... spaces
    this->pantalla.setCursor(0, 1);            // Or setting the cursor in the desired position.
    this->pantalla.printf("L: %.2f lm", lm); // You can make spaces using well... spaces
    this->pantalla.setCursor(0, 0);            // Or setting the cursor in the desired position.
    delay(3000);
    this->pantalla.clear();
}

void ControladorLCD::deepSleep()
{
    this->pantalla.print("Entrando en"); // You can make spaces using well... spaces
    this->pantalla.setCursor(0, 1);      // Or setting the cursor in the desired position.
    this->pantalla.print("modo DeepSleep");
    this->pantalla.setCursor(0, 0); // Or setting the cursor in the desired position.
    delay(1500);
    this->pantalla.clear();
    this->pantalla.noBacklight();
}

void ControladorLCD::testHelloWorld()
{

    this->pantalla.print("UwU  Hello"); // You can make spaces using well... spaces
    this->pantalla.setCursor(5, 1);     // Or setting the cursor in the desired position.
    this->pantalla.print("World!");
    this->pantalla.setCursor(0, 0); // Or setting the cursor in the desired position.
    delay(500);

    // Flashing the backlight
    for (int i = 0; i < 5; ++i)
    {
        this->pantalla.backlight();
        delay(50);
        this->pantalla.noBacklight();
        delay(50);
    }

    this->pantalla.backlight();
    this->pantalla.clear();
    delay(500);
}

void ControladorLCD::testFunciones()
{
    /*
     * When using lcd.print() (and almost everywhere you use string literals),
     * is a good idea to use the macro F(String literal).
     * This tells the compiler to store the string array in the flash memory
     * instead of the ram memory. Usually you have more spare flash than ram.
     * More info: https://www.arduino.cc/reference/en/language/variables/utilities/progmem/
     */

    // Autoscroll
    this->pantalla.setCursor(5, 0);
    this->pantalla.print(F("Autoscrolling"));
    this->pantalla.setCursor(10, 1);
    this->pantalla.autoscroll();

    for (int i = 0; i < 10; i++)
    {
        this->pantalla.print(i);
        delay(200);
    }

    this->pantalla.noAutoscroll();
    this->pantalla.clear();

    // Scroll left and right
    this->pantalla.setCursor(10, 0);
    this->pantalla.print(F("To the left!"));
    for (int i = 0; i < 10; i++)
    {
        this->pantalla.scrollDisplayLeft();
        delay(200);
    }
    this->pantalla.clear();
    this->pantalla.print(F("To the right!"));
    for (int i = 0; i < 10; i++)
    {
        this->pantalla.scrollDisplayRight();
        delay(200);
    }
    this->pantalla.clear();

    // Cursor
    this->pantalla.setCursor(0, 0);
    this->pantalla.cursor();
    this->pantalla.print(F("Cursor"));
    delay(3000);
    this->pantalla.clear();

    // Cursor blink
    this->pantalla.setCursor(0, 0);
    this->pantalla.blink();
    this->pantalla.print(F("Cursor blink"));
    delay(3000);
    this->pantalla.clear();

    // Blink without cursor
    this->pantalla.setCursor(0, 0);
    this->pantalla.noCursor();
    this->pantalla.print(F("Just blink"));
    delay(3000);
    this->pantalla.noBlink();
    this->pantalla.clear();
}

void ControladorLCD::testChars()
{

    uint8_t happy[8] =
        {
            0b00000,
            0b10001,
            0b00000,
            0b00000,
            0b10001,
            0b01110,
            0b00000,
            0b00000,
        };

    uint8_t wow[8] =
        {
            0b00000,
            0b10001,
            0b00000,
            0b01110,
            0b10001,
            0b01110,
            0b00000,
            0b00000,
        };

    uint8_t anchor[8] =
        {
            0b01110,
            0b01010,
            0b01110,
            0b00100,
            0b10101,
            0b10101,
            0b01110,
            0b00100};

    uint8_t snow[8] =
        {
            0b01000,
            0b11101,
            0b01011,
            0b00001,
            0b00100,
            0b01110,
            0b00100,
            0b10000};

    this->pantalla.backlight();

    this->pantalla.createChar(0, happy);
    this->pantalla.createChar(1, wow);
    this->pantalla.createChar(2, anchor);
    this->pantalla.createChar(3, snow);

    this->pantalla.write(0);
    this->pantalla.write(1);
    this->pantalla.write(2);
    this->pantalla.write(3);
}
