#include <ESP8266WiFi.h>

#include <PubSubClient.h>

const char* ssid = "InnoHome@DITT";
const char* passw = "password@ditt";
//const char* ssid = "BiTC";
//const char* passw = "bitc2018";

// IP address of server containing MQTT broker
const char* mqttServerIP("192.168.4.1");

//
char roomID[32] = "r1"; // r2, r3, r4... r9
char* deviceID = "ihn001"; //

long lastReconnectAttempt = 0;

// instance of wifi client
WiFiClient wifiClient;
// instance of MQTT client based on wifiClient
PubSubClient MQTTclient(wifiClient);

// time at which last messsage was published, in millis() 
long lastMsgTime = 0;
// buffer for holding messages to be sent or have been recieved
char msg[64];
// topic in which to publish a message
char topic[32];
// state of switch (on of off)
boolean switchState = false;

// callback function each time a message is published to the subscribed topic
void mqttCallback(char* topic, byte* payload, unsigned int length) {
  memcpy(msg, payload, length);
  msg[length] = '\0';

  // for debugging
  if(!Serial){
    Serial.begin(115200);
  }
  Serial.println(msg);

  // Act on message recieved
  if(strcmp(msg, "D1ON") == 0){
    Serial.println("D1 is onning");
    switchOn("D1ON");
   }else if(strcmp(msg, "D1OFF") == 0){
    switchOff("D1OFF");
   }else if(strcmp(msg, "D2ON") == 0){
    switchOn("D2ON");
   }else if(strcmp(msg, "D2OFF") == 0){
    switchOff("D2OFF");
   }else if(strcmp(msg, "D3ON") == 0){
    switchOn("D3ON");
   }else if(strcmp(msg, "D3OFF") == 0){
    switchOff("D3OFF");
   }else if(strcmp(msg, "D4ON") == 0){
    switchOn("D4ON");
   }else if(strcmp(msg, "D4OFF") == 0){
    switchOff("D4OFF");
   }else if(strcmp(msg, "D5ON") == 0){
    switchOn("D5ON");
   }else if(strcmp(msg, "D5OFF") == 0){
    switchOff("D5OFF");
   }else if(strcmp(msg, "D6ON") == 0){
    switchOn("D6ON");
   }else if(strcmp(msg, "D6OFF") == 0){
    switchOff("D6OFF");
   }else if(strcmp(msg, "D7ON") == 0){
    switchOn("D7ON");
   }else if(strcmp(msg, "D7OFF") == 0){
    switchOff("D7OFF");
   }else if(strcmp(msg, "D8ON") == 0){
    switchOn("D8ON");
   }else if(strcmp(msg, "D8OFF") == 0){
    switchOff("D8OFF");
   }else if(strcmp(msg, "D0ON") == 0){
    switchOn("D9ON");
   }else if(strcmp(msg, "D0OFF") == 0){
    switchOff("D9OFF");
   }
}

void wifiSetup() {
  delay(10);
  if(!Serial) {
      Serial.begin(115200);
    }

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, passw);

  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }

  Serial.print("Successfully connected to ");
  Serial.println(WiFi.localIP());
}

void mqttSetup() {
  MQTTclient.setServer(mqttServerIP, 1883);
  MQTTclient.setCallback(mqttCallback);
  lastReconnectAttempt = 0;
}

void checkMQTT(){
  if(!MQTTclient.connected()){
    long now = millis();
    if(now-lastReconnectAttempt>6000){
      lastReconnectAttempt=now;
      if(reconnect()){
        lastReconnectAttempt=0;
      }
    }
    delay(6000);
  } else {
    MQTTclient.loop();
  }
}

void mqttLoop(){
  while (!MQTTclient.connected()){
    Serial.print("Attempting to connect to MQTT broker at ");
    Serial.println(mqttServerIP);
    if (MQTTclient.connect(deviceID)){
      Serial.println("Connected to MQTT broker");
      // publish announcement to ToHost/deviceID topic
//      snprintf(topic, 32, "toAll/%s", roomID);
//      snprintf(msg, 64, "CONNECT", deviceID);
//      MQTTclient.publish(topic, msg);
      MQTTclient.subscribe(roomID);
      //subscribe to topics meant for all devices
//      MQTTclient.subscribe("toAll/status");
    }
    else {
      Serial.print("Connection to MQTT server failed, rc=");
      Serial.print(MQTTclient.state());
      Serial.println("trying again in 5 seconds");
      delay(5000);
    }
  }
  MQTTclient.loop();
}

boolean reconnect(){

      Serial.print("Attempting to connect to MQTT broker at ");
      Serial.println(mqttServerIP);
  
      if (MQTTclient.connect(deviceID)){
  
        Serial.println("Connected to MQTT broker");
        MQTTclient.publish("toAll/status", "Connected");
        MQTTclient.subscribe(roomID);
        Serial.print("Subscribed to ");
        Serial.println(topic);
      }
  return MQTTclient.connected();
}


void publish(char* msg){
  char m[64] = "";
  strcat(m, msg);
  strcat(roomID, msg);
  MQTTclient.publish("toAll/status", m);
    
}
