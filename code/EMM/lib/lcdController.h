#ifndef lcdController_h
#define lcdController_h

#include <Wire.h>
#include <LCD_I2C.h>

#define LCD_FILAS 2
#define LCD_COLUMNAS 16
#define LCD_ADDRESS_I2C 0x27

class ControladorLCD{
    public:
        ControladorLCD();
        void init();
        void testHelloWorld();
        void testFunciones();
        void testChars();

        void mostrarDatos(
            float tempDHT = 0, float hum = 0, float sensacionT = 0, 
            float lux = 0, 
            float ppmco2 = 0, 
            float pres = 0, float altitud = 0, float tempBMP = 0
            );

        void showInit();
        void infoConexion(
            boolean estado,
            const char* red,
            const char* broker,
            const char* userBroker,
            const char* ip = "void."
            );
    private:
        LCD_I2C pantalla;
};

#endif