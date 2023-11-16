#include <pgmspace.h>
 
#define SECRET
#define THINGNAME ""                         //Nombre definido en AWS
 
const char WIFI_SSID[] = "";               //Nombre de la Red Wifi
const char WIFI_PASSWORD[] = "";           //Contraseña de la Red WiFi
const char AWS_IOT_ENDPOINT[] = "";  //End point en AWS
 
// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
-----END CERTIFICATE-----
)EOF";
 
// Device Certificate                                               
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
-----END CERTIFICATE-----
 
)KEY";
 
// Device Private Key                                               
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
-----END RSA PRIVATE KEY-----
  
)KEY";