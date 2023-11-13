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

Ahora existirá la facilidad de conectar con el cliente MQTT de la nube a elección y se podrán empezar a conectar los objetos directamente para hacer las operaciones siguientes necesarias.

### 3. Configuraciones Iniciales en la Nube AWS

Se debe de tener un acercamiento primero a la conexión en la nube, específicamente tener un conocimiento del servicio de AWS IoT Core, mismo que servirá como base para el proyecto. 
Se realizarán ciertos pasos para conectar nuestros sensores o dispositivos.

1.	Creación de un Objeto

Se debe de crear un objeto o "Thing" en la consola de AWS para que su información pueda ser manejada por este medio. 

Paso 01. Se accede al servicio de IoT Core en el apartado Todos los Dispositivos > Objetos

![image](https://github.com/rodrigojajaja/PROYECTO_IOT_2023_G4/assets/110866741/5b445cfb-4275-4291-beb5-ed18bc8286dd)

Paso 02. Hacer Click en Crear objetos > Crear un único objeto > Siguiente

![image](https://github.com/rodrigojajaja/PROYECTO_IOT_2023_G4/assets/110866741/7c8009fc-1875-486c-88bc-831398d9f2f8)

Paso 03. Ingresar los datos necesarios (Nombre y seleccionar "Sin Sombra")

![image](https://github.com/rodrigojajaja/PROYECTO_IOT_2023_G4/assets/110866741/ccf4db59-7976-42b4-9e5a-2e674edfe2d6)


Paso 04. Hacer Click en "Siguiente" > "Auto generar un nuevo certificado" > Siguiente

![image](https://github.com/rodrigojajaja/PROYECTO_IOT_2023_G4/assets/110866741/3af2c942-70bd-4aab-9346-4e6c61baa553)


2.	Creación de Políticas

Paso 05. En el apartado de políticas o "Policies", asignar una política existente o crear una; en este caso se creará una nueva. Hacer click en Crear política para abrirla en otra ventana y darle un nombre. 

![image](https://github.com/rodrigojajaja/PROYECTO_IOT_2023_G4/assets/110866741/e1ae0332-96a1-428b-8321-dc550ed47402)

Paso 06. En el apartado de permisos, asignar todos los permisos con el caracter "*" en los recuadros de acciones y recursos, seguidamente hacer click en "Crear"

![image](https://github.com/rodrigojajaja/PROYECTO_IOT_2023_G4/assets/110866741/681ee633-5f38-4ce4-b3fc-68f2b145968b)


Paso 06. Relacionar la política creada con el "Objeto" creado y dar click en "Create Thing"

![image](https://github.com/rodrigojajaja/PROYECTO_IOT_2023_G4/assets/110866741/bb24d3ba-2dc7-4c08-8256-a9b7e5ea8d7e)


3.	Certificados

Paso 07. Descargar los siguientes certificados: 
   a. Certificado de dispositivo
   b. Certificado de clave pública
   c. certificado de clave privada
   d. Certificado CA1

No olvidar hacerlo desde este momento ya que posteriormente no se podrán volver a descargar y será necesario recrear todo el proceso. 

Seguidamente hacer click en "Done"

![image](https://github.com/rodrigojajaja/PROYECTO_IOT_2023_G4/assets/110866741/63caf758-4c38-45ef-a8d0-cc33d5e8c592)


El objeto ha sido creado!

![image](https://github.com/rodrigojajaja/PROYECTO_IOT_2023_G4/assets/110866741/2739f604-26b1-41bb-8899-df90a637bf77)


Con este paso hecho, se puede pasar directamente a la conexión de cada uno de los sensores. 

### 4. Gestión de la conexión entre el circuito y la Nube

Dadas las primeras configuraciones en la nube pública, se debe dirigir al código proporcionado en 'main.cpp' y en 'secrets.'
En el codigo de 'main', se colocan las instrucciones tanto para leer los datos como para poder observar su envío por medio del puerto serial. Sse debe configurar el tema de envío hacia el cliente de MQTT en AWS, con un nombre genérico. Además acá se deben de agregar cuantos códigos sean necesarios para cada sensor a utilizar. Para el caso de este proyecto, se considera el código de lectura y envío de 2 sensores, leyendo 3 magnitudes: altura, presión, temperatura y pulso cardíaco. 


1.	Integración de códigos

###### Archivo 'main.ino'.
Contiene la lógica empleada para establecer la comunicación WiFi, conectarse al broker MQTT, e interactuar por puerto serial con el Arduino

![image](https://github.com/rodrigojajaja/PROYECTO_IOT_2023_G4/assets/110866741/c0853b0a-71c4-466f-8df0-2bfca13da8d3)


![image](https://github.com/rodrigojajaja/PROYECTO_IOT_2023_G4/assets/110866741/66838b5e-495e-4efb-b4ca-b84bfb90f207)

###### Archivo 'secrets.h'.
Este código contiene las partes necesarias para la conexión con AWS. Acá se deben agregar los certificados de dispositivo, privado y el CA1. Estos certificados fueron los descargados en el paso 07 de la sección anterior. Se deben de abrir por medio de un bloc de notas dando click derecho en "Abrir con > Bloc de notas", para copiarlos y pegarlos en los espacios indicados

![image](https://github.com/rodrigojajaja/PROYECTO_IOT_2023_G4/assets/110866741/f7feda8f-3a45-4e47-8c6b-a63aaba7542f)
![image](https://github.com/rodrigojajaja/PROYECTO_IOT_2023_G4/assets/110866741/731ab0b9-5409-4e70-949b-351430b42ce8)
![image](https://github.com/rodrigojajaja/PROYECTO_IOT_2023_G4/assets/110866741/3f4665a3-aaea-4366-bc76-252be0d7ee28)

Recordar que se deben de indicar los puertos a donde se esté conectando la tarjeta, la mera tarjeta, los temas de MQTT, las redes WIFI con sus contraseñas para el envío, la zona horaria en la que se encuentre desplegado el dispositivo y sobre todo el end point de AWS. Hallado en la siguiente ubicación: 

a. Settings > Device data endpoint. 

![image](https://github.com/rodrigojajaja/PROYECTO_IOT_2023_G4/assets/110866741/9878697b-1ccc-4b49-ba0d-039431c6f141)


   
2. Conexión con el Cliente de MQTT

A partir del código cargado en el ESP8266 se debe de verificar como en el puerto serie se espera con la conexión, saliendo efectiva si hemos realizado los pasos a cabalidad. Podemos ver el siguiente mensaje en el puerto serie: 

![image](https://github.com/rodrigojajaja/PROYECTO_IOT_2023_G4/assets/110866741/d54c5142-e7a8-4ede-a591-e3d0849b4343)

Y si nos vamos a la consola del clente de MQTT y asignamos el tema que habíamos definido en la sección anterior, tal y como muestra la imagen: 

![image](https://github.com/rodrigojajaja/PROYECTO_IOT_2023_G4/assets/110866741/e0244e2d-07a0-4b63-a982-fd9c8dbbb340)

Vamos a poder directamente ya recibir data en nuestro cliente. 

3. Envío y recibimiento de datos

Luego de asignar el tema en el cliente de MQTT podremos ver los siguientes ítems, llegando ante nuestros ojos demostrando que hemos hecho correctamente la conexión. 

![image](https://github.com/rodrigojajaja/PROYECTO_IOT_2023_G4/assets/110866741/c927554a-5845-494a-96a0-7412ffe1c5f8)

Estos datos sólamente están llegando, pero hace falta la creación de una base de datos en donde los guardaremos para posteriormente exportarlos a nuetro bot de Telegram, realizado en secciones posteriores. 


### 5. Gestión del almacenamiento de la Data

Posterior al envío y recibimiento de la data, se desea guardar en algún lugar, por lo que es necesaria la creación de una función lambda, que toma los valores del cliente y los almacena en una base de datos no relacional proveída por el servicio DynamoDB.

Se lleva a cabo, realizando los siguientes pasos: 

Paso 01. Como primer paso se busca el servicio DynamoDB y se busca la sección de Tables y 
el botón Create Table, para crear una nueva tabla. En este paso se define el nombre 
de la tabla y la Partition Key por medio de una función lambda y una Sort key para 
poder enviar como parte del mensaje MQTT definida por el sensor a utilizar.

![image](https://github.com/rodrigojajaja/PROYECTO_IOT_2023_G4/assets/110866741/5269a2e3-c683-4858-a26c-3e56c7232f16)

Paso 02. En la sección Table Setings del cuadro Create Table se selecciona la opción Default 
Settings para dejar los valores por defecto, y luego crear la tabla en el botón Create 
Table.

![image](https://github.com/rodrigojajaja/PROYECTO_IOT_2023_G4/assets/110866741/f0e0850c-e270-473e-abf6-70ea16457d22)

Paso 03. Al haber creado la tabla, lo que prosigue es crear una función Lambda buscando el 
servicio Lambda el cual proporciona funciones serverless dentro de AWS. En la 
sección Functions se debe de seleccionar la opción de Create Function para poder 
definir el nombre de la función, el runtime que se utilizará y seleccionar la opción 
Create Function.

![image](https://github.com/rodrigojajaja/PROYECTO_IOT_2023_G4/assets/110866741/02a0c8e7-1252-4944-8279-a075d7fe2faa)

Paso 04. Al haber creado la función, hay que dirigirse al apartado de configuración de la función lambda. En el apartado de Permissions se encuentra el link de rol asociado a la 
función. Al hacer click sobre el link nos llevará a la política de permisos asociada a la 
función

![image](https://github.com/rodrigojajaja/PROYECTO_IOT_2023_G4/assets/110866741/466918cf-e5c6-4a0a-b564-ecde191d5bd9)

Paso 05. Seleccionar la opción edit para modificar la política asignada a la función. Aquí se 
deberá agregar el permiso necesario para escribir sobre la tabla creada al inicio del 
laboratorio. Para esto deberá de obtener el identificador ARN de la tabla. En el servicio 
DynamoDB hay que dirigirse a la tabla creada anteriormente y expandir la sección 
Additional Information y copiar el ARN de la tabla.

![image](https://github.com/rodrigojajaja/PROYECTO_IOT_2023_G4/assets/110866741/95d7ff06-f636-42fa-9d50-46a921308919)


Paso 06. Hacer click en "Edit" y se procede a agregar el ARN de la tabla en la configuración de la política 

![image](https://github.com/rodrigojajaja/PROYECTO_IOT_2023_G4/assets/110866741/56701cd5-c517-4e07-a5e3-123afe943e79)

Paso 07: Dentro del apartado de funciones de Lambda, seleccionamos la función creada y 
luego nos dirigimos a la sección de Code Source. Este código lo que realiza es la 
creación de ciertas variables al activarse el evento descrito en la función lambda. Se 
crea un ID para que pueda ser unido a las variables creadas a partir de la Partition 
Key que en mi caso sería la de temperatura

![image](https://github.com/rodrigojajaja/PROYECTO_IOT_2023_G4/assets/110866741/0b4dc077-2b39-4e95-98d2-cedbadc9c629)

Paso 08: Teniendo definido el código, se procede a seleccionar la flecha al lado de text, en la configuración de un evento para poder recibir los datos en la tabla por medio de MQTT

![image](https://github.com/rodrigojajaja/PROYECTO_IOT_2023_G4/assets/110866741/141a3eca-9c0d-47e7-81b0-cd2d9b93b27e)

Paso 09: Se crea un nuevo evento JSON llamado MQTT-input el cual contiene las entradas de 
la tabla las cuales se envían al activarse el evento de la función lambda

![image](https://github.com/rodrigojajaja/PROYECTO_IOT_2023_G4/assets/110866741/4ec903fa-8dfd-423f-8b33-6a728bba144c)


Paso 10: Para que la función lambda pueda funcionar debe de tener los accesos necesarios 
para realizar cambios en la tabla, por lo que hay que buscar el servicio IAM, en el apartado de roles hay que crear un rol para una función lambda y al darle click en next, hay que agregarle los permisos respectivos los cuales se tienen que buscar y lleva por nombre AmazonDynamoDBFullAccess. Por último este rol se asigna a la  función lambda para poder concederle los permisos mencionados

![image](https://github.com/rodrigojajaja/PROYECTO_IOT_2023_G4/assets/110866741/b9148348-9a96-4196-b4df-1cdfd9d2d746)

Paso 11: Se procede a seleccionar la opción Test para enviar el mensaje por medio del evento 
de la función lambda. Dándole un nombre y datos de ejemplo a almacenar. 

![image](https://github.com/rodrigojajaja/PROYECTO_IOT_2023_G4/assets/110866741/dbe5b479-4628-40c8-9e84-173e877b400c)

Paso 12: Si el código no presenta errores y los permisos de escritura en el rol de la función 
fueron asignados correctamente deberá observar el código 200 de la línea de estado de la respuesta HTTP de la API utilizada por el servicio lambda de AWS

![image](https://github.com/rodrigojajaja/PROYECTO_IOT_2023_G4/assets/110866741/8981f0ea-70fe-43fc-93d0-4ed2287b5466)

Paso 13: Al ubicar la tabla en el servicio DynamoDB, en la sección de Explore Items, se 
observará el registro creado desde la función lambda en la tabla

![image](https://github.com/rodrigojajaja/PROYECTO_IOT_2023_G4/assets/110866741/3481695a-09eb-472b-b4bc-eedd601200f0)


Esto se realizó con la finalidad de comenzar a explorar la tabla, pero como se observó, el envío fue manual y es necesario que el almacenamiento sea dinámico, por lo que es necesaria la implementación de una herramienta denominada "Desencadenadores", que permitirán automatizar esos procesos. Se presenta a continuacíón el procedimiento para llevarlo a cabo. 

Paso 14: En la consola AWS dirigirse a la sección de servicios para poder ingresar a as funciones lambda. (Services > Lambda)

![image](https://github.com/rodrigojajaja/PROYECTO_IOT_2023_G4/assets/110866741/c0322a1f-5eff-4def-be0a-2bebcf2e0940)

Paso 15: Se selecciona la función lambda creada anteriormente. 

![image](https://github.com/rodrigojajaja/PROYECTO_IOT_2023_G4/assets/110866741/87bc3ce3-f074-4f81-85db-b6b3b43be51e)

PASO 16: Dentro de la función lambda se selecciona la opción para agregar un desencadenador haciendo click en "Add trigger > AWS IoT"

![image](https://github.com/rodrigojajaja/PROYECTO_IOT_2023_G4/assets/110866741/1ea0ccf0-da17-46ac-8432-8de245b20ac8)

Paso 17: Luego de haber sleccionado la opción AWS IoT, se configura el desencadenador como 
Custom IoT Rule y Create a New Rule. En el apartado de Rule Name se coloca el nombre que se le asignará a la regla, en Rule Query Statement se creará un statement SQL para que cada vez que se tenga un registro de entrada en IoT Core se produzca la ejecución de la función. . La instancia SQL se ve de la siguiente manera: 

SELECT*FROM’<TEMA_MQTT>’ en este caso se modificó y el tema será esp32/pub

![image](https://github.com/rodrigojajaja/PROYECTO_IOT_2023_G4/assets/110866741/3d681e65-09cf-4c0f-a465-d5a70419fcad)


Paso 18: Se recomienda dividir la pantalla para tener una mejor visibilidad de las ventanas que se deben de abrir ahora. 

Se debe de abrir los servicios de DynamoDB para observar los datos provenientes del sensor escritos en la tabla y Se debe de abrir el cliente de MQTT. 

Paso 19: Se procede a conectar el módulo IoT. Como ejemplo se toma la combinación del Esp8266 y el sensor de temperatura y humedad. Recordando que se debe de suscribir al tema previsto. Esto es lo realizado en el el apartado 2 de la sección 3. 

![image](https://github.com/rodrigojajaja/PROYECTO_IOT_2023_G4/assets/110866741/460312ad-8989-4696-90fe-efd445f9bfc9)

Paso 20. Se ve cómo estos registros son directamente almacenados directamente cuando son recibidos en el cliente MQTT. Siendo escritos en la tabla creada a partir de los permisos necesarios y de la definición de la función lambda. 

Se puede observar que se le asignó un Timestamp con formato Date-Time a cada uno de ellos en forma de string, que permitirá reconocer cada una de las entradas en la tabla. 

![image](https://github.com/rodrigojajaja/PROYECTO_IOT_2023_G4/assets/110866741/ae00bc95-eafa-4427-9020-011de58efdfc)

Para la realización de estos pasos, se tomó en cuenta solamente un sensor. Y para más sensores a utilizar solamente se deben de agregar al código principal los que se deseen ya que el procedimiento será el mismo. Recordar que a cada sensor se le trata diferente pero el proceso de envío y recibimiento de data es el mismo, solamente se debe ajustar a gusto. 

Posterior a estos pasos, se desea la vista y envio a nuestro bot de telegram, que se consideró como objetivo final del proyecto, mostrar los datos y dar recomendaciones. Por lo que en las próximas secciones se estará realizando este proceso. 

### 6. Bot de Telegram
### 7. Manejo del envío de Data de la Nube al bot de Telegram
### 8. Integración final
### 9. Presentación y funcionamiento final



















