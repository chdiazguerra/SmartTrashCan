#define trigpin1 5
#define trigpin2 14
#define echopin1 4
#define echopin2 12
#define ledr 2
#define ledy 13
#define ledg 15
#define nchange 5
#define delaytime 1000

#define debug true

#include <WiFiClientSecure.h>
#include "StateChange.h"
#include "States.h"
#include "WebConnection.h"
#include "WebPageCertificate.h"

const float conversionConst = 29.1;
const float minGreen = 20;
const float minYellow = 10;

float distance, distancia1, distancia2, duration, currentTime;
int decoded, state = 0;
bool hasChanged;

const String serverName = "YOUR_WEBPAGE";
WiFiClientSecure client;
X509List cert(WEBPAGE_CERTIFICATE);
const String ID = "6f20b65f89d4ccd";
const float delaySend = 20000;

StateChange stateChange(nchange, ledg, ledy, ledr);
WebConnection webConnection(serverName, client, ID, debug, delaySend);

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";


float medir(int trigpin, int echopin){
  digitalWrite(trigpin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigpin, LOW);
  duration = pulseIn(echopin, HIGH);
  distance = (duration/2)/conversionConst;
  if (distance > 300){ //Evitar error de muy cerca
    distance = 2.0;
  }
  return distance;
}

int decode(float distance){
  if (distance > minGreen){
    return States::GREEN;
  } else if (distance > minYellow){
    return States::YELLOW;
  } else {
    return States::RED;
  }
}


void print(String msg, bool newline = true){
  if (debug){
    Serial.print(msg);
    if (newline){
      Serial.println();
    }
  }
}

void print(float msg, bool newline = true){
  if (debug){
    Serial.print(msg);
    if (newline){
      Serial.println();
    }
  }
}

void print(char msg, bool newline = true){
  if (debug){
    Serial.print(msg);
    if (newline){
      Serial.println();
    }
  }
}

void print(int msg, bool newline = true){
  if (debug){
    Serial.print(msg);
    if (newline){
      Serial.println();
    }
  }
}

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  print("Connecting to WiFi ..", false);
  while (WiFi.status() != WL_CONNECTED) {
    print('.', false);
    delay(1000);
  }
  print("Connected");
}


void setup()
{
  if (debug){
    Serial.begin(9600);
  }
  pinMode(trigpin1, OUTPUT);
  pinMode(echopin1, INPUT);
  pinMode(trigpin2, OUTPUT);
  pinMode(echopin2, INPUT);
  pinMode(ledr, OUTPUT);
  pinMode(ledy, OUTPUT);
  pinMode(ledg, OUTPUT);

  initWiFi();

  client.setTrustAnchors(&cert);
  configTime(0, 0, "pool.ntp.org");

}

void loop()
{
  distancia1 = medir(trigpin1, echopin1);
  print("Distancia 1: ", false);
  print(distancia1);
  
  distancia2 = medir(trigpin2, echopin2);
  print("Distancia 2: ", false);
  print(distancia2);

  distance = (distancia1+distancia2)/2;
  print("Distancia promedio: ", false);
  print(distance);

  decoded = decode(distance);
  print("Decoded: ", false);
  print(decoded);

  hasChanged = stateChange.medicion(decoded);
  state = stateChange.getCurrent();
  if (hasChanged){
    stateChange.changeState(hasChanged);
    print("State changed: ", false);
    print(state);
  }
  
  webConnection.sendData(state);

  delay(delaytime);
}
