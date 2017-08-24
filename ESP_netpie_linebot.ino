#include <ESP8266WiFi.h>
#include <MicroGear.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
const char* ssid     = "your SSID"; //change this to your SSID
const char* password = "your PASSWORD"; //change this to your PASSWORD

const char* host = "your linebot server";//change this to your linebot server ex.http://numpapick-linebot.herokuapp.com/bot.php
#define APPID   "your APPID"     //change this to your APPID
#define KEY     "your KEY"     //change this to your KEY
#define SECRET  "your SECRET"     //change this to your SECRET

#define ALIAS   "NodeMCU1" //set name of drvice
#define TargetWeb "switch" //set target name of web

WiFiClient client;
String uid = "";
int timer = 0;
MicroGear microgear(client);

void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) { // 
    Serial.print("Incoming message -->");
    msg[msglen] = '\0';
Serial.println((char *)msg);
    if(*(char *)msg == '1'){
        digitalWrite(LED_BUILTIN, LOW);   // LED on
        //microgear.chat(TargetWeb,"1");
        //send_data("ESP_LED_ON");
        send_json("ESP LED ON");
    }else{
        digitalWrite(LED_BUILTIN, HIGH);  // LED off
      //microgear.chat(TargetWeb,"0");
      //send_data("ESP_LED_OFF");
      send_json("ESP LED OFF");
    }
}

void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) {
    Serial.println("Connected to NETPIE...");
    microgear.setName(ALIAS);
}


void setup() {
    microgear.on(MESSAGE,onMsghandler);
    microgear.on(CONNECTED,onConnected);

    Serial.begin(115200);
    Serial.println("Starting...");

    pinMode(LED_BUILTIN, OUTPUT);
  
    if (WiFi.begin(ssid, password)) {
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }
    }

Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    microgear.init(KEY,SECRET,ALIAS);
    microgear.connect(APPID);
     digitalWrite(LED_BUILTIN, HIGH);   // LED on
}

void send_json(String data){
  StaticJsonBuffer<300> JSONbuffer;   //Declaring static JSON buffer
    JsonObject& JSONencoder = JSONbuffer.createObject(); 
 
    JSONencoder["ESP"] = data;
 
    JsonArray& values = JSONencoder.createNestedArray("values"); //JSON array
    values.add(20); //Add value to array
    values.add(21); //Add value to array
    values.add(23); //Add value to array
 
 
    char JSONmessageBuffer[300];
    JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
    Serial.println(JSONmessageBuffer);
 
    HTTPClient http;    //Declare object of class HTTPClient
 
    http.begin(host);      //Specify request destination
    http.addHeader("Content-Type", "application/json");  //Specify content-type header
 
    int httpCode = http.POST(JSONmessageBuffer);   //Send the request
    String payload = http.getString();                                        //Get the response payload
 
    Serial.println(httpCode);   //Print HTTP return code
    Serial.println(payload);    //Print request response payload
 
    http.end();  //Close connection
}
void loop() {
    if (microgear.connected()) {
        Serial.println("..."); 
        microgear.loop();
        timer = 0;
    }
    else {
        Serial.println("connection lost, reconnect...");
        if (timer >= 5000) {
            microgear.connect(APPID); 
            timer = 0;
        }
        else timer += 100;
    }
    delay(100);
}
