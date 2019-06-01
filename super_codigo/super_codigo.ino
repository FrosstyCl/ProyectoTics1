#include <SPI.h>
#include <Ethernet.h>
EthernetServer servidor(80); // puerto de conexión
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //mac address
byte ip[] = { 192, 168, 2, 200 }; // ip de tu Arduino en la red
byte gateway[] = { 192, 168, 2, 1 }; // ip de tu router
byte subnet[] = { 255, 255, 255, 0 }; // subnet
String json,solicitud,prueba;

/*~~~~~~~~~~~~~~~~~~~~PUERTOS DE CONEXION ARDUINO~~~~~~~~~~~~~~~~~~~~~*/
int PuertoGas = A0;


/*VARIABLES DE SENSORES */ 
float valor_peso=0;
int pesoPin = 0;
int valor_gas=0;





/*~~~~~~~~~~~~~~~~~~~~~FUNCIONES ~~~~~~~~~~~~~~~+*/
void setup() {
Ethernet.begin(mac, ip, gateway, subnet); 
servidor.begin();
Serial.begin(9600);
}




void LeerGas(){
  valor_gas=analogRead(PuertoGas); 
  Serial.println(valor_gas);
  
  }



 /*~~~~~~~~~LOOP~~~~~~~~~~*/
void loop() { 
LeerGas();

EthernetClient cliente = servidor.available();
if (cliente.available()) {
char c = cliente.read();
if ( solicitud.length() < 100 ) { solicitud += c; }
if ( c == '\n' ) {
json = "{\"Peso\": \""+(String)valor_peso + "\", ";
json +="\"Gas\": \""+(String)valor_gas + "\"} ";
cliente.println("HTTP/1.1 200 OK"); // enviamos cabeceras
cliente.println("Cache-Control: no-store, no-cache, must-revalidate, max-age=0");
cliente.println("Content-Type: json/javascript");
cliente.println("Access-Control-Allow-Origin: *");
cliente.println();
cliente.println(json); //imprimimos datos
Serial.println("TODO OK");
delay(1000); // esperamos un poco
cliente.stop(); //cerramos la conexión
}
}
if ( !cliente.connected() ) { cliente.stop(); }
}
