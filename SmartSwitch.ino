
static const uint8_t CD0 = 16;
static const uint8_t CD1 = 5;
static const uint8_t CD2 = 4;
static const uint8_t CD3 = 0;
static const uint8_t CD4 = 2;
static const uint8_t CD5 = 14;
static const uint8_t CD6 = 12;
static const uint8_t CD7 = 13;
static const uint8_t CD8 = 15;

unsigned long previousMillis = 0;

const long interval = 300000;

void setup() {
  Serial.begin(115200);

  pinMode(CD1, OUTPUT);
  pinMode(CD2, OUTPUT);
  pinMode(CD3, OUTPUT);
  pinMode(CD4, OUTPUT);
  pinMode(CD5, OUTPUT);
  pinMode(CD6, OUTPUT);
  pinMode(CD7, OUTPUT);
  pinMode(CD8, OUTPUT);
  pinMode(CD0, OUTPUT);

  wifiSetup();

  mqttSetup();
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    
    previousMillis = currentMillis;

    publish("Stay");
  }
  
  mqttLoop();
  delay(100);
}

void switchOn(char* state){
  if(state == "D1ON"){
    Serial.println("TURN ON LIGHT D1");
    digitalWrite(CD1, HIGH);
  }else if(state == "D2ON"){
    digitalWrite(CD2, HIGH);
  }
  else if(state == "D3ON"){
    digitalWrite(CD3, HIGH);
  }else if(state == "D4ON"){
    digitalWrite(CD4, HIGH);
  }else if(state == "D5ON"){
    digitalWrite(CD5, HIGH);
  }else if(state == "D6ON"){
    digitalWrite(CD6, HIGH);
  }else if(state == "D7ON"){
    digitalWrite(CD7, HIGH);
  }else if(state == "D8ON"){
    digitalWrite(CD8, HIGH);
  }else if (state == "D9ON"){
    digitalWrite(CD0, HIGH);
  }
//  publish(state);
  delay(100);
}

void switchOff(char* state){
  if(state == "D1OFF"){
    Serial.println("BRO PLS OFF D1");
    digitalWrite(CD1, LOW);
  }else if(state == "D2OFF"){
    digitalWrite(CD2, LOW);
  }
  else if(state == "D3OFF"){
    digitalWrite(CD3, LOW);
  }else if(state == "D4OFF"){
    digitalWrite(CD4, LOW);
  }else if(state == "D5OFF"){
    digitalWrite(CD5, LOW);
  }else if(state == "D6OFF"){
    digitalWrite(CD6, LOW);
  }else if(state == "D7OFF"){
    digitalWrite(CD7, LOW);
  }else if(state == "D8OFF"){
    digitalWrite(CD8, LOW);
  }else if(state == "D9OFF"){
    digitalWrite(CD0, LOW);
  }
//  publish(state);
  delay(100);
}
