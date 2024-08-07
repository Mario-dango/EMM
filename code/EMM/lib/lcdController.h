#ifndef lcdController_h
#define lcdController_h

#include <Wire.h>
#include <LCD_I2C.h>

#define LCD_FILAS 2
#define LCD_COLUMNAS 16
#define LCD_ADDRESS_I2C 0x27

class ControladorLCD
{
public:
    ControladorLCD();
    void init();
    void testHelloWorld();
    void testFunciones();
    void testChars();

    void enviandoDatos();
    void mostrarDatos(
        float tempDHT = 0, float hum = 0, float sensacionT = 0,
        float lux = 0,
        float ppmco2 = 0,
        float pres = 0, float altitud = 0, float tempBMP = 0);

    void deepSleep();

    void initWiFi(
        boolean estado,
        const char *red,
        String ip = "x");
    void initMQTT(
        boolean estado,
        const char *broker);
    void reconectando(
        const char *red,
        const char *broker,
        const char *userBroker);
    void showInit();
    void infoConexion(
        boolean estado,
        const char *red,
        const char *broker,
        const char *userBroker,
        String ip);

private:
    LCD_I2C pantalla;

    //****Para armar caracteres ver: https://www.miki.pro/diseno-lcd.html****/

    // Definir los caracteres personalizados
    byte a_acute[8] = {
        B00100,
        B00000,
        B01110,
        B00001,
        B01111,
        B10001,
        B01111,
        B00000};

    byte e_acute[8] = {
        B00100,
        B00000,
        B01110,
        B10001,
        B11111,
        B10000,
        B01111,
        B00000};

    byte i_acute[8] = {
        B00100,
        B00000,
        B00100,
        B00000,
        B00100,
        B00100,
        B00100,
        B00000};

    byte o_acute[8] = {
        B00100,
        B00000,
        B01110,
        B10001,
        B10001,
        B10001,
        B01110,
        B00000};

    byte u_acute[8] = {
        B00100,
        B00000,
        B10001,
        B10001,
        B10001,
        B10011,
        B01101,
        B00000};

    byte n_tilde[8] = {
        B01010,
        B00101,
        B01101,
        B10011,
        B10001,
        B10001,
        B10001,
        B00000};

    byte grado[8] = {
        B00110,
        B01001,
        B01001,
        B00110,
        B00000,
        B00000,
        B00000,
        B00000};

    // literalmente ->  :v
    byte caraV[8] = {
        B00100,
        B10100,
        B10000,
        B00011,
        B01100,
        B10000,
        B01100,
        B00011};
};

#endif