# PROYECTO_IOT_2023_G4
## Universidad Rafael Landívar 2023
## Proyecto Final - Internet de las Cosas: "Implemento Deportivo medidor de magnitudes físicas" 
Se presenta en el Siguiente Repositorio los códigos y pasos a seguir para la implementación del proyecto respecto al curso de Internet de las Cosas del segundo ciclo del 2023. 

El proyecto consta de una implementación combinada, se usa como MC Central, al ESP8266 que, envía data de 3 diferentes sensores por medio de PLatformIO (Una plataforma colaborativa), usando un Framework de Arduino. Además de ello, se muestra los cambios y documentación interna acerca de los pasos a realizar para la conexión con el cliente MQTT de la nube pública de AWS.


# Descripción general
Este proyecto se enfoca en crear un implemento deportivo o "Correa deportiva" que se coloca cruzada alrededor del pecho de un atleta. Su propósito es medir las principales variables físicas que se experimentan durante la práctica deportiva, proporcionando información relevante sobre el desempeño del deportista.

Se miden las magnitudes respecto a la humedad, a la presión y a la frecuencia cardíaca que está experimentando el atelta en el momento. Siendo la data recogida por medio del microcontrolador ESP23 8266, que se encarga de mandar la data por medio de WiFi hacia una base de datos DynamoDB en la nube pública de AWS, recibida por medio del cliente MQTT. Esta data luego es tomada por una función lambda que funge como parte del microservicio que se encarga en conjunto por medio del servicio API GATEWAY de enviar solicitudes http hacia un bot de telegram, indicando finalmente los parámetros solicitados para que el atleta pueda observarlos con recomendaciones de relajación, hidratación o parada de rutina. Según el tiempo que personalmente se decida entrenar. 


# Materiales necesarios

1. Microcontrolador ESP8266 NodeMCU-32 
2. Sensor de Humedad DTH11
3. Sensor de Presión Atmosférica BMP-280
4. Sensor de Frecuencia Cardíaca AD8232
5. Protoboard Para pruebas
6. 1 Batería de reloj de 3V
7. Correa/estuche del implemento. 


# Programas a utilizar
1. Visual Studio Code extensión PlatformIo con Framework de Arduino
2. Consola de AWS para el uso de DyanmoDB, IoT Core, API Gateway
3. Telegram 10.1.3


# Diagramas
Diagrama de Conexión
![1](https://github.com/rodrigojajaja/PROYECTO_IOT_2023_G4/assets/110866741/f5e830f7-8967-447a-83ab-77075eea5770)

Diagrama de Microservicios
![2](https://github.com/rodrigojajaja/PROYECTO_IOT_2023_G4/assets/110866741/f2626859-2ef3-4ce3-be4c-7bf4bd24b1bd)

Diagrama de Circuito

![diagramabonito](https://github.com/rodrigojajaja/PROYECTO_IOT_2023_G4/assets/110866741/ea6902a8-e99d-4ca1-9346-d4eee67c0123)

# Fotografías de conexión

# Prototipo


## Fases del Desarrollo del Proyecto

El proyecto consta de diferentes fases, preferiblemente desarrolladas en el orden dictado a continuación. Se da una introducción y el seguimiento de pasos a realizar para la puesta en marcha del "Implemento Deportivo medidor de magnitudes físicas". Como resumen, se muestran las fases a continuación y se desarrollan con profundidad en las siguientes secciones: 

1. Configuraciones Iniciales de Hardware
2. Configuraciones Iniciales de Software
3. Configuraciones Iniciales en la Nube AWS
4. Gestión de la conexión entre el circuito y la Nube
5. Gestión del almacenamiento de la Data
6. Bot de Telegram
7. Manejo del envío de Data de la Nube al bot de Telegram
8. Integración final
9. Presentación y funcionamiento final



### 1. Configuraciones Iniciales de Hardware

Para la puesta en marcha de este proyecto, se considera necesario el hecho de que puede ser implementado cualquier tipo de sensor tanto análogo como digital. En este proyecto se utilizan los sentores DTH11, BMP280 y de pulso cardíaco, pero se considera que la persona que desee continuar con este proyecto, puede utilizar los que se desee. 

Al momento de conectar/soldar los sensores a la placa de cobre o a un protoboard en dado caso, se recomienda tener puesta una pulsera electroestática, dado que son sensores sensibles a las cargas eléctricas humanas. 


El proyecto se puede realizar de dos maneras según los materiales que se tengan: 

-Hacer uso de un módulo ESP32 01 y un microcontrolador por aparte: Tomar en cuenta que la programación tanto del módulo WIFI como del MC se realizan por aparte, se porporciona un ejemplo de ello, hallado en la carpeta 'sensor_data_separada'. Encontrándose los archivos 'secrets' y 'main', tanto del ESP01 como del MC a elección de la familia de arduino.

-Hacer uso de un módulo ESP8266: Ya como tal desarrollarlo por medio de este Sistema Embebido, se necesitó solamente ajustar el código para tener una sentencia de reglas en un mismo archivo 'main'.

Ambas soluciones son válidas, pero para fines de este proyecto fue utilizada la opción 02. 

### 2. Configuraciones Iniciales de Software

El proyecto primero, debe desarrollarsen en varias plataformas que trabajan en conjunto. Una para la programación de los microcontroladores y el envío de la toma de data, y otra para el procesamiento y re envío a la aplicación final. 

Se tomó la decisión, para fines de este proyecto, de utilizar el IDE de Visual Studio Code en su extensión PlatformIO, aunque también se pudo haber utilizado el IDE propio de Arduino. Por decisión propia y asesoramiento del docente del curso, se optó por escoger la opción 01. 

En qué se diferencian ambos IDES? Existe una mejoría de una respecto a otra? 

El Arduino IDE es una opción simple y amigable, ideal para principiantes y proyectos específicos de Arduino, con librerías integradas. Visual Studio Code con PlatformIO es más versátil, ofreciendo soporte para diversas placas y microcontroladores, gestión avanzada de proyectos, integración con Git y extensibilidad para características avanzadas. La elección depende de el fin que el usuario próximo a seguir con el proyecto, evalúe. 


#### Instalación de Platform IO

Paso 01. Instalación de Visual Studio
Paso 02. Dirigirse a la pestaña de extensiones
Paso 03. Buscar "PlatformIO IDE" en el Marketplace
Paso 04. Hacer click en "Install" para iniciar 
Paso 05. Reiniciar Visual Studio Code. 

#### Instalación de librerías necesarias. 

Para la realización de este proyecto es necesario el uso de algunas librerías, con la finalidad de tener mayor versatilidad en los protocolos y data que se maneja y envía fuera del MC. Se necesitan las librerías: ArduinoJson y PubSubClient, que podrán ser buscadas en la siguiente ubicación: 

![image](https://github.com/rodrigojajaja/PROYECTO_IOT_2023_G4/assets/110866741/321bcc77-49c3-43b7-892f-fe4f6115ae3f)

Las librerías son las correspondientes a la autoría de Benoit Blanchon y Nick O'Leary, respectivamente. 
Cada que se tengan ubicadas ya las librerías, se realiza click en 'Add to Project' y se elige el nombre del proyecto que se ha creado. 

![image](https://github.com/rodrigojajaja/PROYECTO_IOT_2023_G4/assets/110866741/762e8e96-93f9-4f6f-8931-41003d85e560)

Ahora existirá la facilidad de conectar con el cliente MQTT de la nube a elección y 

### 3. Configuraciones Iniciales en la Nube AWS
### 4. Gestión de la conexión entre el circuito y la Nube
### 5. Gestión del almacenamiento de la Data
### 6. Bot de Telegram
### 7. Manejo del envío de Data de la Nube al bot de Telegram
### 8. Integración final
### 9. Presentación y funcionamiento final



















