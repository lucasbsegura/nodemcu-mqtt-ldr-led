
#include<ESP8266WiFi.h>
#include<PubSubClient.h>

const char* nome_wifi = "*****";
const char* senha_wifi = "*****";

const char* broker =  "*****"; 
const char* topico_mqtt = "*****";
const char* cliente_mqtt = "*****";
const int porta_mqtt = 0;

int pino_LDR = 5;

WiFiClient wifiClient;
PubSubClient client(broker, porta_mqtt, NULL, wifiClient);

void setup() {
  Serial.begin(9600);
  
  pinMode(pino_LDR, INPUT);

  conectarWiFi();
  conectarMQTT();
}

void loop() {
  float valor = analogRead(pino_LDR);
  Serial.print("Luminosidade: ");
  Serial.println(valor);
  
  if(!isnan(valor)){
    enviar("luminosidade", valor);  
  }

  delay(5000);
}

void conectarWiFi(){
  Serial.println(".");
  Serial.print("Initializing...");
  delay(500);
  Serial.print(".");
  delay(500);
  Serial.println(".");
  
  Serial.print("Connecting to WiFi Network..");
  WiFi.begin(nome_wifi, senha_wifi);

  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print("Connected to WiFi: ");
  Serial.println(WiFi.localIP());
}

void conectarMQTT(){
  Serial.print("Connecting to Mosquitto MQTT Broker..");

  client.setServer(broker, porta_mqtt);

  while(!client.connect(cliente_mqtt)){
    delay(500);
    Serial.print(".");
  }

  Serial.println("Connected to Mosquitto!");
}

void enviar(String nome_campo, float valor){
  if(!client.connected()){
    conectarMQTT();
  }

  String payload = String(valor);
  client.publish(topico_mqtt, (char*)payload.c_str());
}
