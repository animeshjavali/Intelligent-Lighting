 #include <ESP8266WiFi.h>
#include <PubSubClient.h>
#define mqtt_topic_pub "my_iot"
#define mqtt_topic_sub "my_iot"

//-------------------VARIABLES GLOBALES--------------------------
char *ssid = "Ani";
char *password= "ibringit";
const char *mqtt_server = "m10.cloudmqtt.com";
const int mqtt_port = 18172;
 char *mqtt_user = "iytoiwss";
 char *mqtt_pwd = "3nCzHJC94OLH";

//-------------------------------------------------------------------------
WiFiClient espClient;
PubSubClient client(espClient);

//------------------------CALLBACK-----------------------------
void callback(char* topic, byte* payload, unsigned int length) {

String msg="";  
 /* Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");*/
 for (int i = 0; i < length; i++) {
    msg += (char)payload[i];
  } 
  Serial.println(msg);
// char data=(char)payload;
 //Serial.println(data);
 if(msg[0]=='1' && msg[1]!='0')digitalWrite(D0,HIGH);
 else if(msg[0]=='0')digitalWrite(D0,LOW);
/*if(msg[0]=='1' && msg[1]!='0')digitalWrite(D0,HIGH);
else if(msg[0]=='2')digitalWrite(D0,LOW);


if(msg[0]=='3')digitalWrite(D1,HIGH);
else if(msg[0]=='4')digitalWrite(D1,LOW);
if(msg[0]=='5')digitalWrite(D2,HIGH);
else if(msg[0]=='6')digitalWrite(D2,LOW);
if(msg[0]=='7')digitalWrite(D3,HIGH);
else if(msg[0]=='8')digitalWrite(D3,LOW);
if(msg[0]=='9')digitalWrite(D4,HIGH);
else if(msg[0]=='1' && msg[1]=='0')digitalWrite(D4,LOW);
if(msg[0]=='1' && msg[1]=='1')digitalWrite(D5,HIGH);
else if(msg[0]=='1' && msg[1]=='2')digitalWrite(D5,LOW);
if(msg[0]=='1' && msg[1]=='3')digitalWrite(D6,HIGH);
else if(msg[0]=='1' && msg[1]=='4')digitalWrite(D6,LOW);
if(msg[0]=='1' && msg[1]=='5')digitalWrite(D7,HIGH);
else if(msg[0]=='1' && msg[1]=='6')digitalWrite(D7,LOW);
else if(msg[0]=='1' && msg[1]=='7')digitalWrite(D8,HIGH);
else if(msg[0]=='1' && msg[1]=='8')digitalWrite(D8,LOW);
*/
}

//------------------------RECONNECT-----------------------------
void reconnect(){
  while (!client.connected()) {
    Serial.print("Attempting to connect to MQTT...");
    if (client.connect("ESP8266Client", mqtt_user, mqtt_pwd)) {
      Serial.println("connected");
      client.subscribe(mqtt_topic_sub);
     } 
    else {
      Serial.print("failed, ro=");
      Serial.print(client.state());
      Serial.println("Try again in 5 seconds");
      delay(5000);
    }
   }
 }

//------------------------SETUP-----------------------------
void setup() {

  Serial.begin(115200);
  Serial.println("");
  pinMode(D0,OUTPUT);  pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);  pinMode(D3,OUTPUT);
  pinMode(D4,OUTPUT);  pinMode(D5,OUTPUT);
  pinMode(D6,OUTPUT);  pinMode(D7,OUTPUT);
  pinMode(D8,OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

//--------------------------LOOP--------------------------------
void loop() {
 if (!client.connected()) {
   reconnect();
   }
client.loop();
}

