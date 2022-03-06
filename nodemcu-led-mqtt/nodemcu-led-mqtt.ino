#include<ESP8266WiFi.h>
#include<PubSubClient.h>

const char* nome_wifi = "*****";
const char* senha_wifi = "*****";

const char* broker =  "*****"; 
const char* topico_mqtt = "*****";
const char* cliente_mqtt = "*****";
const int porta_mqtt = 0;

#define LED D7

WiFiClient wifiClient;

void callback(char* topico, byte* valor, unsigned int comprimento);

PubSubClient client(broker, porta_mqtt, callback, wifiClient);

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  conectarWiFi();
  conectarMQTT();
}

void loop() {
  if (!client.loop()){
    conectarMQTT();
  }
}

void conectarWiFi(){
  Serial.print("CONN WiFi");
  WiFi.begin(nome_wifi, senha_wifi);

  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print("CONNECTED TO WiFi: ");
  Serial.println(WiFi.localIP());
}

void conectarMQTT(){
  Serial.print("CONN Broker");

  client.setServer(broker, porta_mqtt);
  client.setCallback(callback);

  while(!client.connect(cliente_mqtt)){
    delay(500);
    Serial.print(".");
  }

  Serial.println("CONNECTED TO Broker");
  client.subscribe(topico_mqtt);
}

void callback(char* topico, byte* valor, unsigned int comprimento){
  char comando = (char)valor[0];

  Serial.print("Valor recebido: ");
  Serial.println(comando);

  if (comando == '1'){
    digitalWrite(LED, HIGH);
    Serial.println("LED ON");
  }
  if (comando == '0'){
    digitalWrite(LED, LOW);
    Serial.println("LED OFF");
  }
}
