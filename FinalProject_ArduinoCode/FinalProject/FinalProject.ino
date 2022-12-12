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
#define PIN_BUTTON 34

//FOR JOYSTICK
int xyzPins[] = {23, 22, 21};

const char *ssid_Router     =  "The Ong Orb"; //Enter the router name
const char *password_Router =  "darfdar080870"; //Enter the router password
//#define     REMOTE_IP          "192.168.1.14"  //input the remote server which is you want to connect
//#define     REMOTE_PORT         8888       //input the remote port which is the remote provide
WiFiClient client;

//TEST
MqttClient mqttClient(client);

const char broker[] = "test.mosquitto.org";
int        port     = 1883;
const char topic[]  = "real_unique_topic";

//set interval for sending messages (milliseconds)
const long interval = 8000;
unsigned long previousMillis = 0;

int count = 0;
//TEST

void setup() {
  //FOR RESTART BUTTON
  pinMode(PIN_BUTTON, INPUT);
  
  //FOR JOYSTICK BUTTON/Z AXIS
  pinMode(xyzPins[0], INPUT);
  pinMode(xyzPins[1], INPUT);
  pinMode(xyzPins[2], INPUT_PULLUP);

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
  Serial.println(topic);
  Serial.println();

  mqttClient.subscribe(topic);

  Serial.print("Topic: ");
  Serial.println(topic);

  Serial.println();
}

void loop() {
  //FOR JOYSTICK INPUTS
  int xVal = analogRead(xyzPins[0]);
  int yVal = analogRead(xyzPins[1]);
  int zVal = digitalRead(xyzPins[2]);

  Serial.printf("X,Y,Z: %d,\t%d,\t%d\n", xVal, yVal, zVal);
  delay(500);

  // call poll() regularly to allow the library to send MQTT keep alive which
  // avoids being disconnected by the broker
  mqttClient.poll();

  unsigned long currentMillis = millis();

  //if (currentMillis - previousMillis >= interval) {
  if(digitalRead(PIN_BUTTON) == LOW){


    // save the last time a message was sent
    previousMillis = currentMillis;

    //record random value from A0, A1 and A2
    int Rvalue = 9;
    

    Serial.print("Sending message to topic: ");
    Serial.println(topic);
    //Serial.println(Rvalue);
    Serial.println("reset");

    // send message, the Print interface can be used to set the message contents
    mqttClient.beginMessage(topic);
    //mqttClient.print(Rvalue);
    mqttClient.print("reset");
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