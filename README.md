# Estación Meteorológica Estática
## ¿Qué es una estación meteorológica?
Una estación meteorológica es un dispositivo tecnológico de características electrónica e informática que permite nuclear parámetros relevantes para realizar estudios y sacar conclusiones frente a fenómenos físicos.
## ¿Qué es EME?
Este es un proyecto institucional y surge de la necesidad de poder comparar los biomas entre Godoy Cruz, Mendoza y el departamento de lavalle puntualmente entre el colegio ETec de la universidad de Mendoza y los diversos puntos que parada que se tienen en otro proyecto institucional de salida a lavalle llamado “Viaje a las Raíces”.
## Los modulos incorporados

  - [ESP8266](#ESP8266)
  - [BMP180](#BMP180)
  - [DHT22](#DHT22)
  - [BMS 2S](#BMS-2S)
  - [Baterías 18650](#Baterías-18650)
  - [BH1750](#BH1750)
  - [MQ-135](#MQ-135)
 
### ESP8266
#### WeMos Mini D1 (ESP8266)
La placa ESP32 (DOIT ESP32 Devkit V1) es un módulo basado en el microcontrolador ESP32, conocido por su capacidad de conexión Wi-Fi y Bluetooth. En nuestra estación meteorológica, esta placa desempeñará un papel vital al ofrecer una base solida para la  recopilación y transmisión de datos ambientales. Con su capacidad para manejar múltiples sensores y su compatibilidad con entornos de desarrollo como Arduino IDE, la ESP32 garantiza un funcionamiento continuo incluso en condiciones adversas, asegurando la integridad y precisión de las mediciones meteorológicas.

<img src= "https://mimitoi.com/wp-content/uploads/2024/01/D_NQ_NP_657703-MCO70581862267_072023-O.webp" width="270px"> 


### BMP280
El sensor BMP280 es un modulo el cual es utilizado para medir la presión atmosférica y la altitud a nivel del mar con un alto nivel de precisión. Es conocido por su pequeño tamaño y por su simplicidad al momento de realizar mediciones. 

<img src= "https://alltopnotch.co.uk/wp-content/uploads/imported/4/BMP280-I2C-Precision-Digital-Barometric-Pressure-Sensor-Board-Module-33v-232729413184-2.JPG" width="270px">


### DHT22
El sensor DHT22 es un componente crucial en el campo de la electrónica y la monitorización ambiental. 
Su función principal es medir con precisión la temperatura ambiente y la humedad relativa del entorno en el que se encuentra la estación meteorológica. Este sensor incorpora un termistor para la medición de la temperatura y un elemento especializado para medir la humedad relativa.

<img src= "https://http2.mlstatic.com/D_NQ_NP_863339-MLU75748316379_042024-O.webp" width="270px">


### BMS 2S
El módulo BMS 2S es esencial para la carga de las baterías, ya que desempeña un papel crucial en la regulación del voltaje que reciben durante el proceso de carga. Este módulo garantiza que las baterías reciban el voltaje adecuado para una carga segura y eficiente. Este sirve apara para utilizar 2 baterias 18650 en serie

<img src= "https://media.discordapp.net/attachments/1254855337148678175/1269453259085451314/D_NQ_NP_882318-MLA74839026632_032024-O.png?ex=66b01dfa&is=66aecc7a&hm=c727c877df2b933ebc3f8a5308c33e36751a8c014739cce6ed26e87c8e01f9ce&=&format=webp&quality=lossless&width=477&height=402">

### Baterías 18650
Las baterías 18650 son células recargables de iones de litio conocidas por su alta densidad de energía y fiabilidad. En nuestra estación meteorológica, estas baterías desempeñarán un papel vital al ofrecer una fuente de alimentación constante y duradera, lo que garantizará un funcionamiento continuo incluso en condiciones adversas en las que el panel solar no pueda suministrar la potencia nominal.

<img src= "https://http2.mlstatic.com/D_918072-MLA70473561138_072023-C.jpg" width="290px">

### BH1750
El sensor BH1750 es un sensor el cual está diseñado para medir la intensidad de la luz de manera precisa. Es altamente valorado por su facilidad de uso y su capacidad de obtener lecturas rápidas en una amplia variedad de ambientes. Su pequeño tamaño y alta precisión lo hacen el más querido de los sensores de luz.

<img src= "https://http2.mlstatic.com/D_NQ_NP_787293-MLA52961083887_122022-O.webp" width="280px">

### MQ-135
El sensor MQ135 es un componente el cual permite detectar gases nocivos para el aire, como el amoníaco, sulfuro de hidrógeno, dióxido de carbono, y otros compuestos orgánicos volátiles. Es conocido por la capacidad de proporcionar alertas tempranas sobre la presencia de estos gases.
De este sensor podemos tomar datos analógicos del comportamiento de la mezcla de gases y la capacidad de marcar un umbral de disparo para una salida digital de ser requerida, para ello es necesario acceder manualmente al trimmer de su pcb y calibrar el disparo del mismo

<img src= "https://http2.mlstatic.com/D_NQ_NP_892623-MLA52961069097_122022-O.webp" width="330px" width="25px">

### Módulo Step-Down (MP2307)
Este módulo nos sirve para bajar el voltaje que entregan las baterías y funcione correctamente la placa de desarrollo Weomos Mini

<img src= "https://media.discordapp.net/attachments/1254855337148678175/1269452802778988614/D_NQ_NP_918866-MLA69553697542_052023-O.png?ex=66b01d8d&is=66aecc0d&hm=3d55018e7e977f68e922f4e8ec70c05a9814f18b56ccd566812ff1befd8cd09c&=&format=webp&quality=lossless" width="505px">

### Módulo Step-Up (MT3608-USB)
Este módulo nos sirve para subir el voltaje que entrega el cargador de las baterias y poder caragrlas a el voltaje que requiere el BMS 2S

<img src= "[https://media.discordapp.net/attachments/1254855337148678175/1269452802778988614/D_NQ_NP_918866-MLA69553697542_052023-O.png?ex=66b01d8d&is=66aecc0d&hm=3d55018e7e977f68e922f4e8ec70c05a9814f18b56ccd566812ff1befd8cd09c&=&format=webp&quality=lossless](https://media.discordapp.net/attachments/1254855337148678175/1269455871340187780/D_NQ_NP_862216-MLA51111797118_082022-O.png?ex=66b02069&is=66aecee9&hm=873195268fef1096919e49cb3b88b9be4729959a8c4992d56d7043ce41aeed6d&=&format=webp&quality=lossless)" width="505px">
