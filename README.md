# PROYECTO_IOT_2023_G4
Se presenta en el Siguiente Repositorio los códigos y pasos a seguir para la implementación del proyecto respecto al curso de Internet de las Cosas del segundo ciclo del 2023. 

El proyecto consta de una implementación combinada, se usa como MC Central, al ESP8266 que, envía data de 3 diferentes sensores por medio de PLatformIO (Una plataforma colaborativa), usando un Framework de Arduino. 
Además de ello, se muestra los cambios y documentación interna acerca de los pasos a realizar para la conexión con el cliente MQTT de la nube pública de AWS.




# Descripción general
Este proyecto se enfoca en crear un implemento deportivo o "Correa deportiva" que se coloca cruzada alrededor del pecho de un atleta. Su propósito es medir las principales variables físicas que se experimentan durante la práctica deportiva, proporcionando información relevante sobre el desempeño del deportista.

Se miden las magnitudes respecto a la humedad, a la presión y a la frecuencia cardíaca que está experimentando el atelta en el momento. Siendo la data recogida por medio del microcontrolador ESP23 8266, que se encarga de mandar la data por medio de WiFi hacia una base de datos DynamoDB en la nube pública de AWS, recibida por medio del cliente MQTT. Esta data luego es tomada por una función lambda que funge como parte del microservicio que se encarga en conjunto por medio del servicio API GATEWAY de enviar solicitudes http hacia un bot de telegram, indicando finalmente los parámetros solicitados para que el atleta pueda observarlos con recomendaciones de relajación, hidratación o parada de rutina. Según el tiempo que personalmente se decida entrenar. 


# Materiales necesarios

-Microcontrolador ESP8266 NodeMCU-32 
-Sensor de Humedad DTH11
-Sensor de Presión Atmosférica BMP-280
-Sensor de Frecuencia Cardíaca AD8232
-Protoboard Para pruebas
-1 Batería de reloj de 3V
-Correa/estuche del implemento. 


# Programas a utilizar
-Visual Studio Code extensión PlatformIo con Framework de Arduino
-Consola de AWS para el uso de DyanmoDB, IoT Core, API Gateway
-Telegram 10.1.3


# Diagramas
Diagrama de Conexión
![1](https://github.com/rodrigojajaja/PROYECTO_IOT_2023_G4/assets/110866741/f5e830f7-8967-447a-83ab-77075eea5770)

Diagrama de Microservicios
![2](https://github.com/rodrigojajaja/PROYECTO_IOT_2023_G4/assets/110866741/f2626859-2ef3-4ce3-be4c-7bf4bd24b1bd)

Diagrama de Circuito

![diagramabonito](https://github.com/rodrigojajaja/PROYECTO_IOT_2023_G4/assets/110866741/ea6902a8-e99d-4ca1-9346-d4eee67c0123)

# Fotografías de conexión

# Prototipo

