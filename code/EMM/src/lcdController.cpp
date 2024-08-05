#include "../lib/lcdController.h"

ControladorLCD::ControladorLCD() : pantalla(LCD_ADDRESS_I2C, LCD_COLUMNAS, LCD_FILAS)
{
}

void ControladorLCD::init()
{
    this->pantalla.begin(); // If you are using more I2C devices using the Wire library use lcd.begin(false)
                            // this stop the library(LCD_I2C) from calling Wire.begin()
    this->pantalla.backlight();
}

void ControladorLCD::showInit()
{
    this->pantalla.print("Inicializando"); // You can make spaces using well... spaces
    this->pantalla.setCursor(0, 1);        // Or setting the cursor in the desired position.
    this->pantalla.print("Comunicación");
    this->pantalla.setCursor(0, 0); // Or setting the cursor in the desired position.
}

void ControladorLCD::infoConexion(
    boolean estado,
    const char *red,
    const char *broker,
    const char *userBroker,
    const char *ip)
{
    if (!estado)
    {
        this->pantalla.printf("Sin Conexión.");   // You can make spaces using well... spaces
        this->pantalla.setCursor(0, 1);           // Or setting the cursor in the desired position.
        this->pantalla.printf("Reintentando..."); // You can make spaces using well... spaces
        this->pantalla.setCursor(0, 0);
        delay(2000);
        this->pantalla.clear();
    }
    else
    {
        this->pantalla.printf("Conectado red:"); // You can make spaces using well... spaces
        this->pantalla.setCursor(0, 1);          // Or setting the cursor in the desired position.
        this->pantalla.printf("%s", red);        // You can make spaces using well... spaces
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
        this->pantalla.printf("%s", ip);        // You can make spaces using well... spaces
        this->pantalla.setCursor(0, 0);
        delay(2000);
        this->pantalla.clear();
    }
}

void ControladorLCD::mostrarDatos(
    float tempDHT, float hum, float sensacionT,
    float lux,
    float ppmco2,
    float pres, float altitud, float tempBMP)
{
    //  Mostrar los datos del DHT
    this->pantalla.printf("DHT22 °C %%HR");               // You can make spaces using well... spaces
    this->pantalla.setCursor(0, 1);                       // Or setting the cursor in the desired position.
    this->pantalla.printf("T:%.2f H:%.2f", tempDHT, hum); // You can make spaces using well... spaces
    this->pantalla.setCursor(0, 0);                       // Or setting the cursor in the desired position.
    delay(2000);
    this->pantalla.clear();
    //  Mostrar los datos del MQ135
    this->pantalla.printf("MQ135 ppm CO2");       // You can make spaces using well... spaces
    this->pantalla.setCursor(0, 1);               // Or setting the cursor in the desired position.
    this->pantalla.printf("ppmCO2:%.2f", ppmco2); // You can make spaces using well... spaces
    this->pantalla.setCursor(0, 0);               // Or setting the cursor in the desired position.
    delay(2000);
    this->pantalla.clear();
    //  Mostrar los datos del DHT
    this->pantalla.printf("BMP");                          // You can make spaces using well... spaces
    this->pantalla.setCursor(0, 1);                        // Or setting the cursor in the desired position.
    this->pantalla.printf("P:%.1f A:%.1f", pres, altitud); // You can make spaces using well... spaces
    this->pantalla.setCursor(0, 0);                        // Or setting the cursor in the desired position.
    delay(2000);
    this->pantalla.clear();
    //  Mostrar los datos del DHT
    this->pantalla.printf("BH1750 Lumenes"); // You can make spaces using well... spaces
    this->pantalla.setCursor(0, 1);          // Or setting the cursor in the desired position.
    this->pantalla.printf("L:%.2f", lux);    // You can make spaces using well... spaces
    this->pantalla.setCursor(0, 0);          // Or setting the cursor in the desired position.
    delay(2000);
    this->pantalla.clear();
    this->pantalla.clear();
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
