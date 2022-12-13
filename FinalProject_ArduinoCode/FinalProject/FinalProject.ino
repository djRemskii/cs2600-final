/**********************************************************************
  Filename    : WiFi Client
  Description : Use ESP32's WiFi client feature to connect and communicate with a remote IP.
  Auther      : www.freenove.com
  Modification: 2020/07/11
**********************************************************************/
#include <WiFi.h>
#include <ArduinoMqttClient.h>
#include <string.h>

//FOR RESTART BUTTON
#define RESET_BUTTON 23

//FOR SEND BUTTON
#define SEND_BUTTON 22

//FOR LED DEFINITIONS
#define PIN_LED_1 19
#define PIN_LED_2 18
#define PIN_LED_3 5
#define PIN_LED_4 0
#define PIN_LED_5 2
#define PIN_LED_6 15
#define PIN_LED_7 32
#define PIN_LED_8 33
#define PIN_LED_9 25

//FOR JOYSTICK
int xyzPins[] = {36, 39, 21};

const char *ssid_Router     =  "The Ong Orb"; //Enter the router name
const char *password_Router =  "darfdar080870"; //Enter the router password
//#define     REMOTE_IP          "192.168.1.14"  //input the remote server which is you want to connect
//#define     REMOTE_PORT         8888       //input the remote port which is the remote provide
WiFiClient client;

//TEST
MqttClient mqttClient(client);

const char broker[] = "test.mosquitto.org";
int        port     = 1883;
const char outtopic[]  = "ong_arduino";
const char intopic[] = "ong_tictactoe";

//set interval for sending messages (milliseconds)
const long interval = 8000;
unsigned long previousMillis = 0;

int count = 0;
//TEST

void setup() {
  //FOR RESTART/SEND BUTTONS
  pinMode(RESET_BUTTON, INPUT);
  pinMode(SEND_BUTTON, INPUT);
  
  //FOR JOYSTICK BUTTON/Z AXIS
  pinMode(xyzPins[0], INPUT);
  pinMode(xyzPins[1], INPUT);
  pinMode(xyzPins[2], INPUT_PULLUP);

  //FOR LED GRID
  pinMode(PIN_LED_1, OUTPUT);
  pinMode(PIN_LED_2, OUTPUT);
  pinMode(PIN_LED_3, OUTPUT);
  pinMode(PIN_LED_4, OUTPUT);
  pinMode(PIN_LED_5, OUTPUT);
  pinMode(PIN_LED_6, OUTPUT);
  pinMode(PIN_LED_7, OUTPUT);
  pinMode(PIN_LED_8, OUTPUT);
  pinMode(PIN_LED_9, OUTPUT);

  Serial.begin(115200);
  delay(10);

  WiFi.begin(ssid_Router, password_Router);
  Serial.print("\nWaiting for WiFi... ");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  delay(500);

  //TEST
  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1);
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();


  //Recieve messages
  mqttClient.onMessage(onMqttMessage);

  Serial.print("Subscribing to topic: ");
  Serial.println(intopic);
  Serial.println();

  mqttClient.subscribe(intopic);

  Serial.print("Topic: ");
  Serial.println(outtopic);

  Serial.println();
}

void loop() {
  //FOR JOYSTICK INPUTS
  int xVal = analogRead(xyzPins[0]);
  int yVal = analogRead(xyzPins[1]);
  int zVal = digitalRead(xyzPins[2]);

  int gridNum = 0;
  
  //GRID SELECTION CODE
  if ((-1 < yVal) && (yVal < 400)){
    if((-1 < xVal) && (xVal < 400)){ //TOP LEFT GRID 1
      gridNum = 1;
      digitalWrite(PIN_LED_1,HIGH);

      digitalWrite(PIN_LED_2,LOW);
      digitalWrite(PIN_LED_3,LOW);
      digitalWrite(PIN_LED_4,LOW);
      digitalWrite(PIN_LED_5,LOW);
      digitalWrite(PIN_LED_6,LOW);
      digitalWrite(PIN_LED_7,LOW);
      digitalWrite(PIN_LED_8,LOW);
      digitalWrite(PIN_LED_9,LOW);

    } else
    if((1400 < xVal) && (xVal < 2400)){ //TOP MID GRID 2
      gridNum = 2;
      digitalWrite(PIN_LED_2,HIGH);

      digitalWrite(PIN_LED_1,LOW);
      digitalWrite(PIN_LED_3,LOW);
      digitalWrite(PIN_LED_4,LOW);
      digitalWrite(PIN_LED_5,LOW);
      digitalWrite(PIN_LED_6,LOW);
      digitalWrite(PIN_LED_7,LOW);
      digitalWrite(PIN_LED_8,LOW);
      digitalWrite(PIN_LED_9,LOW);
    } else
    if(xVal > 3000){  //TOP RIGHT GRID 3
      gridNum = 3;
      digitalWrite(PIN_LED_3,HIGH);

      digitalWrite(PIN_LED_2,LOW);
      digitalWrite(PIN_LED_1,LOW);
      digitalWrite(PIN_LED_4,LOW);
      digitalWrite(PIN_LED_5,LOW);
      digitalWrite(PIN_LED_6,LOW);
      digitalWrite(PIN_LED_7,LOW);
      digitalWrite(PIN_LED_8,LOW);
      digitalWrite(PIN_LED_9,LOW);
    }
  } else 
  if ((1400 < yVal) && (yVal < 2400)){
    if((-1 < xVal) && (xVal < 400)){ //MID LEFT GRID 4
      gridNum = 4;
      digitalWrite(PIN_LED_4,HIGH);

      digitalWrite(PIN_LED_2,LOW);
      digitalWrite(PIN_LED_3,LOW);
      digitalWrite(PIN_LED_1,LOW);
      digitalWrite(PIN_LED_5,LOW);
      digitalWrite(PIN_LED_6,LOW);
      digitalWrite(PIN_LED_7,LOW);
      digitalWrite(PIN_LED_8,LOW);
      digitalWrite(PIN_LED_9,LOW);
    } else
    if((1400 < xVal) && (xVal < 2400)){ //MID MID GRID 5
      gridNum = 5;
      digitalWrite(PIN_LED_5,HIGH);

      digitalWrite(PIN_LED_2,LOW);
      digitalWrite(PIN_LED_3,LOW);
      digitalWrite(PIN_LED_4,LOW);
      digitalWrite(PIN_LED_1,LOW);
      digitalWrite(PIN_LED_6,LOW);
      digitalWrite(PIN_LED_7,LOW);
      digitalWrite(PIN_LED_8,LOW);
      digitalWrite(PIN_LED_9,LOW);
    } else
    if(xVal > 3000){  //MID RIGHT GRID 6
      gridNum = 6;
      digitalWrite(PIN_LED_6,HIGH);

      digitalWrite(PIN_LED_2,LOW);
      digitalWrite(PIN_LED_3,LOW);
      digitalWrite(PIN_LED_4,LOW);
      digitalWrite(PIN_LED_5,LOW);
      digitalWrite(PIN_LED_1,LOW);
      digitalWrite(PIN_LED_7,LOW);
      digitalWrite(PIN_LED_8,LOW);
      digitalWrite(PIN_LED_9,LOW);
    }
  } else 
  if (3000 < yVal){
    if((-1 < xVal) && (xVal < 400)){ //BOTTOM LEFT GRID 7
      gridNum = 7;
      digitalWrite(PIN_LED_7,HIGH);

      digitalWrite(PIN_LED_2,LOW);
      digitalWrite(PIN_LED_3,LOW);
      digitalWrite(PIN_LED_4,LOW);
      digitalWrite(PIN_LED_5,LOW);
      digitalWrite(PIN_LED_6,LOW);
      digitalWrite(PIN_LED_1,LOW);
      digitalWrite(PIN_LED_8,LOW);
      digitalWrite(PIN_LED_9,LOW);
    } else
    if((1400 < xVal) && (xVal < 2400)){ //BOTTOM MID GRID 8
      gridNum = 8;
      digitalWrite(PIN_LED_8,HIGH);

      digitalWrite(PIN_LED_2,LOW);
      digitalWrite(PIN_LED_3,LOW);
      digitalWrite(PIN_LED_4,LOW);
      digitalWrite(PIN_LED_5,LOW);
      digitalWrite(PIN_LED_6,LOW);
      digitalWrite(PIN_LED_7,LOW);
      digitalWrite(PIN_LED_1,LOW);
      digitalWrite(PIN_LED_9,LOW);
    } else
    if(xVal > 3000){  //BOTTOM RIGHT GRID 9
      gridNum = 9;
      digitalWrite(PIN_LED_9,HIGH);

      digitalWrite(PIN_LED_2,LOW);
      digitalWrite(PIN_LED_3,LOW);
      digitalWrite(PIN_LED_4,LOW);
      digitalWrite(PIN_LED_5,LOW);
      digitalWrite(PIN_LED_6,LOW);
      digitalWrite(PIN_LED_7,LOW);
      digitalWrite(PIN_LED_8,LOW);
      digitalWrite(PIN_LED_1,LOW);
    }
  } 

  Serial.printf("X,Y,Z: %d,\t%d,\t%d\n", xVal, yVal, zVal);
  Serial.printf("gridNum: %d\n", gridNum);
  delay(500);

  // call poll() regularly to allow the library to send MQTT keep alive which
  // avoids being disconnected by the broker
  mqttClient.poll();


  //SEND RESET SIGNAL
  if(digitalRead(RESET_BUTTON) == LOW){

    Serial.print("Sending message to topic: ");
    Serial.println(outtopic);
    Serial.println("reset");

    // send message, the Print interface can be used to set the message contents
    mqttClient.beginMessage(outtopic);
    mqttClient.print("reset");
    mqttClient.endMessage();

    Serial.println();

    delay(1000);
  }

  //SEND GRIDNUM SIGNAL
  if((digitalRead(SEND_BUTTON) == LOW) || (zVal == 0)){

    Serial.print("Sending message to topic: ");
    Serial.println(outtopic);
    Serial.println(gridNum);

    // send message, the Print interface can be used to set the message contents
    mqttClient.beginMessage(outtopic);
    mqttClient.print(gridNum);
    mqttClient.endMessage();

    Serial.println();

    delay(1000);
  }
}

void onMqttMessage(int messageSize){
  // we received a message, print out the topic and contents
  Serial.println("Received a message with topic '");
  Serial.print(mqttClient.messageTopic());
  Serial.print("', length ");
  Serial.print(messageSize);
  Serial.println(" bytes:");

  // use the Stream interface to print the contents
  while (mqttClient.available()) {
    Serial.print((char)mqttClient.read());
  }
  Serial.println();
  Serial.println();
}