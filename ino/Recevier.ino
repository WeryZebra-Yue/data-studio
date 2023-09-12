// // #include <ESP8266WiFi.h>
// // #include <espnow.h>
// // #include <PubSubClient.h>

// // #define CHANNEL 1

// // /** MQTT client class to access MQTT broker */
// // WiFiClient espClient;
// // PubSubClient mqttClient(espClient);
// // /** MQTT broker URL */
// // const char* mqttBroker = "xx.xx.xx.xx";
// // /** MQTT connection id */
// // const char* mqttID = "ESP8266";
// // /** MQTT user name */
// // const char* mqttUser = "esp8266";
// // /** MQTT password */
// // const char* mqttPwd = "PASSWORD";

// // void OnDataRecv(uint8_t *mac_addr, uint8_t *data, uint8_t data_len);

// // // Init ESP Now with fallback
// // void InitESPNow() {
// //   if (esp_now_init() == 0) {
// //     Serial.println("ESPNow Init Success");
// //   }
// //   else {
// //     Serial.println("ESPNow Init Failed");
// //     ESP.restart();
// //   }
// // }

// // // Configuring the device as an Access Point
// // void configDeviceAP() {
// //   String Prefix = "Slave:";
// //   String Mac = WiFi.macAddress();
// //   String SSID = Prefix + Mac;
// //   String Password = "123456789";
// //   bool result = WiFi.softAP(SSID.c_str(), Password.c_str(), CHANNEL, 0);
// //   if (!result) {
// //     Serial.println("AP Config failed.");
// //   } else {
// //     Serial.println("AP Config Success. Broadcasting with AP: " + SSID);
// //   }
// // }

// // void setup() {
// //   Serial.begin(9600);
// //   Serial.println("ESPNow/Basic/Slave Example for ESP8266");

// //   // Set device in AP mode to begin with
// //   WiFi.mode(WIFI_AP_STA);
// //   WiFi.begin("Fiber 4G", "fiberpass147");
// //   // Configure device AP mode
// //   configDeviceAP();
// //   // This is the MAC address of the Slave in AP Mode
// //   Serial.print("AP MAC: "); Serial.println(WiFi.softAPmacAddress());

// //   // Connect to MQTT broker
// //   mqttClient.setServer(mqttBroker, 1883);
// //   Serial.println("Connecting to MQTT broker");

// //   int connectTimeout = 0;

// //   while (!mqttClient.connect(mqttID, mqttUser, mqttPwd)) {
// //     delay(100);
// //     connectTimeout++;
// //     if (connectTimeout > 10) { // Wait for 1 second to connect
// //       Serial.println("Can't connect to MQTT broker");
// //       ESP.restart();
// //     }
// //   }
// //   Serial.println("Connected to MQTT");

// //   // Init ESP Now with a fallback logic
// //   InitESPNow();
// //   // Once ESP Now is successfully Init, we will register for recv CB to
// //   // get recv packet info.
// //   esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
// //   esp_now_register_recv_cb(OnDataRecv);
// // }

// // // Callback when data is received from Master
// // void OnDataRecv(uint8_t *mac_addr, uint8_t *data, uint8_t data_len) {
// //   char macStr[18];
// //   snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
// //            mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
// //   Serial.print("Last Packet Recv from: "); Serial.println(macStr);
// //   Serial.print("Last Packet Recv Data: "); Serial.println(*data);
// //   Serial.println("");
// //   mqttClient.publish("/debug", ("[INFO] Last Packet Recv from: " + String(macStr)).c_str());
// //   mqttClient.publish("/debug", ("[INFO] Last Packet Recv Data: " + String(*data)).c_str());
// // }

// // void loop() {
// //   // Chill
// // }
// /*
//  * This Code will configure ESP8266 in SoftAP mode and allow different devices (Laptop, Mobile, PCs) connect to it
//  */
// #include <ESP8266WiFi.h> 
 
// const char* ap_ssid = "ESP8266"; //Access Point SSID
// const char* ap_password= "embedded-robotics"; //Access Point Password
// uint8_t max_connections=8;//Maximum Connection Limit for AP
// int current_stations=0, new_stations=0;
 
// void setup()
// {
//   //Start the serial communication channel
//   Serial.begin(115200);
//   Serial.println();
   
//   //Setting the AP Mode with SSID, Password, and Max Connection Limit
//   if(WiFi.softAP(ap_ssid,ap_password,1,false,max_connections)==true)
//   {
//     Serial.print("Access Point is Creadted with SSID: ");
//     Serial.println(ap_ssid);
//     Serial.print("Max Connections Allowed: ");
//     Serial.println(max_connections);
//     Serial.print("Access Point IP: ");
//     Serial.println(WiFi.softAPIP());
//   }
//   else
//   {
//     Serial.println("Unable to Create Access Point");
//   }
// }
 
// void loop()
// {
//   //Continuously check how many stations are connected to Soft AP and notify whenever a new station is connected or disconnected
 
//   new_stations=WiFi.softAPgetStationNum();
   
//   if(current_stations<new_stations)//Device is Connected
//   {
//     current_stations=new_stations;
//     Serial.print("New Device Connected to SoftAP... Total Connections: ");
//     Serial.println(current_stations);
//   }
   
//   if(current_stations>new_stations)//Device is Disconnected
//   {
//     current_stations=new_stations;
//     Serial.print("Device disconnected from SoftAP... Total Connections: ");
//     Serial.println(current_stations);
//   }
   
// }
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <Firebase_ESP_Client.h>

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"
#include "time.h"


// Insert Firebase project API Key
#define API_KEY "AIzaSyCVzXCZSzLihSLFfi7KhXJS4CczUbRYcic"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://wery-754ba.firebaseio.com/"



const char* ssid = "server1";
const char* password = "qwertyuiop"; 
int max_connection = 8;

String URL;
int httpCode;
String payload;
String ID;
String state;
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;
FirebaseJson json;

unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;


ESP8266WebServer server(80);
HTTPClient http;

IPAddress ip (10, 10, 10, 1);
IPAddress gateway (10, 10, 10, 1);
IPAddress subnet (255, 255, 255, 0);
const char* ntpServer = "pool.ntp.org";

void setup() {
    configTime(0, 0, ntpServer);

  Serial.begin(115200);
  WiFi.mode(WIFI_AP_STA);
  Serial.println("Setup Access point");
  Serial.println("Disconnect from any other modes");
  WiFi.disconnect();
  Serial.println("stating access point with SSID" +String(ssid)); 
  WiFi.softAP(ssid, password, 1, false, max_connection); 
  WiFi.softAPConfig(ip, gateway, subnet);
  IPAddress myIP = WiFi.softAPIP();
  Serial.println(myIP);
  // server.on("/",handleroot);
  server.on("/feed2",feed2);
  server.on("/feed1",feed1);
  server.begin();
  WiFi.begin("Fiber 4G", "fiberpass147");
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println(".");
  }
  Serial.println("Connected to the WiFi network");
  config.api_key = API_KEY;

  config.database_url = DATABASE_URL;

  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  config.token_status_callback = tokenStatusCallback; 
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  
}

void handleroot(){
  server.send(200,"text/plain","hello");
}
unsigned long getTime() {
  time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    //Serial.println("Failed to obtain time");
    return(0);
  }
  time(&now);
  return now;
}

void feed1(){
  String type = server.arg("type");
  Serial.println(type);
  if (type == "temperature"){
    String id = server.arg("id");
    String temp = server.arg("temp");
    String humid = server.arg("humid");
    String time = String(getTime());
    json.clear();
    json.add("temperature",temp);
    json.add("humidity",humid);
    json.add("time",time);
    Firebase.RTDB.set(&fbdo, "/readings/"+id, &json);
  }
 
}
void feed2(){
  String type = server.arg("type");
  Serial.println(type);
  
  if(type == "distance"){
  String id = server.arg("id");
  String distance = server.arg("distance");
  String time = String(getTime());

  json.clear();
  json.add("distance",distance);
  json.add("time",time);
  Firebase.RTDB.set(&fbdo, "/readings/"+id, &json);
  }
}


void loop (){
  server.handleClient();  
}
