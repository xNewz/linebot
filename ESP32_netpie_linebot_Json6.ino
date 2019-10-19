// Sample code for ESP32  //

#include <WiFi.h>
#include <MicroGear.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid     = "*********";         //change this to your SSID
const char* password = "*********";         //change this to your PASSWORD

const char* host =  "http://HerokuAppName.herokuapp.com/bot.php"; //PUT your Heroku App Name ex.http://mylinebot.herokuapp.com/bot.php
//NETPIE-Info
#define APPID       "NETPIE_APPID_NAME"    //Same data at Line#3 of pub.php
#define KEY         "NETPIE_KEY_ID"        //Same data at Line#4 of pub.php
#define SECRET      "NETPIE_SECRET_ID"     //Same data at Line#5 of pub.php

#define ALIAS   "ESP32"                    //set name of device

WiFiClient client;
int timer = 0;
MicroGear microgear(client);

void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) {
  Serial.print("LINE MSG is");
  msg[msglen] = '\0';
  Serial.println((char *)msg);
  String msgLINE = (char *)msg;
  if ( msgLINE == "ON" || msgLINE == "On" || msgLINE == "on" ) {
    send_json("Turn on LED");
    digitalWrite(16, HIGH);         // LED on
  } 
  else if ( msgLINE == "OFF" || msgLINE == "Off"  || msgLINE == "off" ) {
    send_json("Turn off LED");
    digitalWrite(16, LOW);          // LED off
  }
  else if ( msgLINE == "RESET" || msgLINE == "Reset"  || msgLINE == "reset" ) {
    send_json("System Resetting");
    delay(5000);
    ESP.restart();
  }
  else {
    send_json("Syntax error command");
  }
}

void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) {
  Serial.println("NETPIE is connected");
  microgear.setName(ALIAS);
}

void send_json(String data) {
  StaticJsonDocument<300> JSONencoder;

  JSONencoder["ESP"] = data;

  JsonArray values = JSONencoder.createNestedArray("values"); //JSON array
  values.add(20); //Add value to array
  values.add(21); //Add value to array
  values.add(23); //Add value to array

  char JSONmessageBuffer[300];
  serializeJsonPretty(JSONencoder, JSONmessageBuffer, sizeof(JSONmessageBuffer));
  Serial.println(JSONmessageBuffer);

  HTTPClient http;

  http.begin(host);
  http.addHeader("Content-Type", "application/json");

  int httpCode = http.POST(JSONmessageBuffer);
  String payload = http.getString();

  Serial.println(httpCode);
  Serial.println(payload);

  http.end();
}

void setup() {
  microgear.setEEPROMOffset(3000);
  microgear.on(MESSAGE, onMsghandler);
  microgear.on(CONNECTED, onConnected);

  Serial.begin(115200);
  Serial.println("Starting...");

  pinMode(16, OUTPUT);

  if (WiFi.begin(ssid, password)) {
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
  }

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  microgear.resetToken();
  microgear.init(KEY, SECRET, ALIAS);
  microgear.connect(APPID);
  digitalWrite(16, HIGH);   // LED on
}

void loop() {
  if (microgear.connected()) {
    Serial.println("NETPIE is connecting!");
    microgear.loop();
    timer = 0;
  }
  else {
    Serial.println("NETPIE is reconnecting...");
    if (timer >= 5000) {
      microgear.connect(APPID);
      timer = 0;
    }
    else timer += 100;
  }
  delay(100);
}
