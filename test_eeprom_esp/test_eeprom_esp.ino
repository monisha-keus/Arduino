#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <EEPROM.h>

void B_to_D(void);

uint8_t prv_state = LOW,state=LOW,val;
byte arr[500];
char dec_arr[100];
int dec_t =0;
int end_t = 0;
uint8_t m=0,n=0;


int preAdr = 0;
// the current address in the EEPROM (i.e. which byte
// we're going to write to next)
int addr = 1;
int addrs =0;
const char* ssid = "Vikilabs";
const char* password = "quicksilver";

//const char* ssid = "motog5s+";
//const char* password = "monisha@123";

String sceneName = "0";
String sceneId = "0";
String sceneArgName[10];
String sceneArg;
uint8_t newSceneInfo = 0;
String message ="0";
String scene_1,scene_2;
String sceneInfo;
byte this_sceneInfo[8]={'0'};

  struct DeviceId{
    char SwitchId[4];
    char SwitchState;
  };

struct SceneInfo {
  String SceneName = "0";
  String SceneId = "0";
  DeviceId Device_1;
  };

 struct SceneInfo Sceneinfo_1,Sceneinfo_2;

 
ESP8266WebServer server(80);

const int led = 5;

void handleRoot() {
 digitalWrite(led, 1);
 server.send(200, "text/plain", "hello from esp8266!");
 //digitalWrite(led, 0);
}
//********************************************************

void getSceneInfo() {
 uint8 totalArgs = server.args();
uint8 i ;
int scene=0;
 for ( i = 0; i < totalArgs; i++) {
    sceneArgName[i] = server.argName(i);
    sceneArg = server.arg(i);
    uint8_t count = sceneArg.length();
   for(uint8_t j = 0;j<count;j++){
    sceneInfo +=sceneArg[j];
   }
   count =0;
   sceneArg = "";
 }
 Serial.print("sceneInfo ");
 Serial.println(sceneInfo);
 newSceneInfo = 1; 
 message = "SceneAdded";
// if(server.arg(0) == "scene_1"){
//   Sceneinfo_1.SceneName = server.arg(0);
//  Sceneinfo_1.SceneId  = server.arg(1);
//  Serial.println(" scene_1");
//   message = "scene info";
//   message += "scene name : ";
//   message += server.arg(0);
//   message += "  scene Id : ";
//   message += server.arg(1);
//}  
// 
// 
// else if(server.arg(0) == "scene_2"){
//  Sceneinfo_2.SceneName = server.arg(0);
//  Sceneinfo_2.SceneId  = server.arg(1);
//    //Serial.println(" scene_2");
//
//   message = "scene info";
//   message += "scene name : ";
//   message += Sceneinfo_2.SceneName;
//   message += "  scene Id : ";
//   message += server.arg(1);
//   //server.send(200, "text/plain",message );
// }
// else{
//   message = "given scene id and scene name didn't match";
// }

 server.send(200, "text/plain",message );
}
//***********************************************************

void handleNotFound() {
 digitalWrite(5, 1);
 String message = "File Not Found\n\n";
 message += "URI: ";
 message += server.uri();
 message += "\nMethod: ";
 message += (server.method() == HTTP_GET) ? "GET" : "POST";
 message += "\nArguments: ";
 message += server.args();
 message += "\n";
 for (uint8_t i = 0; i < server.args(); i++) {
   message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
 }
 server.send(404, "text/plain", message);
 digitalWrite(led, 0);
}
//****************************************************************

void setup(void) {
 pinMode(led, OUTPUT);
 digitalWrite(led, 0);
 Serial.begin(9600);
  pinMode(4,OUTPUT);//LED 3
  pinMode(5,OUTPUT);
  pinMode(14,OUTPUT);
  pinMode(16,OUTPUT);
  pinMode(15,INPUT);  //Data Pin
  pinMode(13,INPUT);  //Ack Pin
  pinMode(12,INPUT); //Clk Pin
 WiFi.mode(WIFI_STA);
 WiFi.begin(ssid, password);
 Serial.println("");

 // Wait for connection
 while (WiFi.status() != WL_CONNECTED) {
   delay(500);
   Serial.print(".");
 }
 Serial.println("");
 Serial.print("Connected to ");
 Serial.println(ssid);
 Serial.print("IP address: ");
 Serial.println(WiFi.localIP());

 if (MDNS.begin("esp8266")) {
   Serial.println("MDNS responder started");
 }

 server.on("/", handleRoot);

 server.on("/getSceneinfo", getSceneInfo);
 
 server.on("/inline", []() {
   server.send(200, "text/plain", "this works as well");
 });

 server.onNotFound(handleNotFound);

 server.begin();
 Serial.println("HTTP server started");
}

//************************************************************

void loop(void) {
  uint8_t m;
 server.handleClient();

//******************Rx
// int inchar1 = digitalRead(13);
// int clk_pin = digitalRead(12);
// if(inchar1 == HIGH && clk_pin==HIGH){
//   int data = digitalRead(15);
//  prv_state = inchar1;
//  if(data == LOW){
//    val = 0;   
//   }
//  else if(data == HIGH){
//     val = 1;
//   }
//    
////    Serial.print(val);
////    Serial.print("val of m = ");
////    Serial.print(m);
//
//    arr[m] = val;
//    m++;
//    Serial.print("val of m = ");
//    Serial.print(m);
//    if(m>500){
//      m=0;  
//    }
//    if(m==8){
//      B_to_D();
//      dec_arr[n++] = (char)dec_t;
//      dec_t = 0;
//      if(n>100){
//        n=0;
//      }
//      n=0;    
//    }
//    delay(5); 
// }
// if(prv_state == HIGH && inchar1 == LOW){
//  //i = 0;
//  end_t =1;
////  Serial.println("end_t ");
////  Serial.print(end_t);
//  //count =0;
//  dec_t = 0;
//  prv_state = LOW;
// }
// if(end_t == 1){
//  
//  for(int k=0;k<n;k++){
//  Serial.println("dec_arr");
//  Serial.print(dec_arr[k]);
//  }
//  n=0;
//  end_t = 0;
// }
 
 //****************Tx
 if(newSceneInfo==1){
  pinMode(15,OUTPUT);  //Data Pin
  pinMode(13,OUTPUT);  //Ack Pin
  pinMode(12,OUTPUT); //Clk Pin
  uint8_t count = sceneInfo.length();
  
    Serial.print("count ");
    Serial.println(count);
    for(uint8_t p=0;p<count;p++){
      Serial.print("sceneInfo 2nd ");
     Serial.println(sceneInfo[p]);
      for(int q =7;q>=0;q--){
         this_sceneInfo[q]= bitRead(sceneInfo[p],q);
        Serial.println(this_sceneInfo[q]);
        digitalWrite(13,HIGH);
        digitalWrite(12,HIGH);
        digitalWrite(15,this_sceneInfo[q]);
        delay(15);
        digitalWrite(12,LOW);
      }
    }
    digitalWrite(13,LOW);
    //delay(5);
    sceneInfo = "";
    count = 0;
     newSceneInfo = 0;
  pinMode(15,INPUT);  //Data Pin
  pinMode(13,INPUT);  //Ack Pin
  pinMode(12,INPUT); //Clk Pin
 }
}

void B_to_D(void){
  int k,base=1;
    for(k=7;k>=0;k--)
    {
        dec_t = dec_t + arr[k] * base;
        base = base * 2;        
    }
    Serial.print("dec_t ");
    Serial.println(dec_t);
}
