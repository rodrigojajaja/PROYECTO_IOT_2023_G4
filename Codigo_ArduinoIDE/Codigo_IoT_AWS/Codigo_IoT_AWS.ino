#include "Secrets.h"
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "WiFi.h"

#include <Adafruit_BMP085.h>
Adafruit_BMP085 bmp;

#include "DHT.h"
#define DHTPIN 15     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11

#include <PulseSensorPlayground.h>
const int PulseWire = 0; //Pin analogico al cual se conecta la señal.
int Threshold = 550; //Default para ayuda de ruido y verificar que cosa es un latido o no.


#define AWS_IOT_PUBLISH_TOPIC   "esp32/pub"
#define AWS_IOT_SUBSCRIBE_TOPIC "esp32/sub"
 
float h;
float t;
float p;
float a;
int myBPM;
 
DHT dht(DHTPIN, DHTTYPE);
 
WiFiClientSecure net = WiFiClientSecure();
PubSubClient client(net);

//Este metodo es el encargado de la conexion a WIFI y AWS.
void connectAWS()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
 
  Serial.println("Connecting to Wi-Fi");
 
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
 
  // Configure WiFiClientSecure to use the AWS IoT device credentials
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);
 
  // Connect to the MQTT broker on the AWS endpoint we defined earlier
  client.setServer(AWS_IOT_ENDPOINT, 8883);
 
  // Create a message handler
  client.setCallback(messageHandler);
 
  Serial.println("Connecting to AWS IOT");
 
  while (!client.connect(THINGNAME))
  {
    Serial.print(".");
    delay(100);
  }
 
  if (!client.connected())
  {
    Serial.println("AWS IoT Timeout!");
    return;
  }
 
  // Subscribe to a topic
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);
 
  Serial.println("AWS IoT Connected!");
}

//Este metodo se utiliza para enviar los mensajes al MQTT 
void publishMessage()
{
  StaticJsonDocument<400> doc;
  
  doc["humidity"] = h;
  doc["temperature"] = t;
  doc["altitude"] = a;
  doc["pressure"] = p;
  doc["BPM"] = myBPM;

  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer); // print to client
  
  client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
}

//Este metodo se utiliza para manejar los mensajes recibidos desde MQTT 
void messageHandler(char* topic, byte* payload, unsigned int length)
{
  Serial.print("incoming: ");
  Serial.println(topic);
 
  StaticJsonDocument<200> doc;
  deserializeJson(doc, payload);
  const char* message = doc["message"];
  Serial.println(message);
}

//Inicializa los sensores y metodos.
void setup()
{
  Serial.begin(115200);
  connectAWS();
  dht.begin();

  pulseSensor.analogInput(PulseWire);   
  pulseSensor.setThreshold(Threshold);   
}

void loop()
{
  //Lectura de humedad desde DHT11
  h = dht.readHumidity();

  //La lectura de la temperatura se puede realizar con BMP_180 o DHT11
  //t = dht.readTemperature();
  t = bmp.readTemperature();

  //Para medir la presión a nivel del mar se utiliza:
  //p = bmp.readSealevelPressure();
  p = bmp.readPressure();
  
  //Se puede hacer más precisa la medicion de altura si se agrega la presion actual a nivel del mar en Pascales
  //Ejemplo, si la presion actual es de 101500 pascales, seria:
  //a = bmp.readAltitude(101500);
  a = bmp.readAltitude();
 

  //Se utiliza para verificar si el DHT11 está leyendo humedad:
  if (isnan(h))  
  {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  //Se utiliza para verificar si el BMP180 está leyendo presion, temperatura y altitud:
  if (isnan(p) || isnan(t) || isnan(a))  
  {
    Serial.println(F("Failed to read from BMP sensor!"));
    return;
  }

  //Verifica si se encuentran latidos en el sensor
  if (pulseSensor.sawStartOfBeat()) {            
    myBPM = pulseSensor.getBeatsPerMinute();
    Serial.println("♥"); 
    Serial.print(F("BPM: "));                         
    Serial.println(myBPM);                        
  }


  /Imprime el resto de datos en el monitor serial.
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.println(F("°C "));
  Serial.print(F("Pressure: "));
  Serial.print(p);
  Serial.print(F("Pa Altitude: "));
  Serial.print(a);
  Serial.println(F( "m."));

  //Envia el mensaje MQTT
  publishMessage();
  client.loop();
  delay(1000);
}