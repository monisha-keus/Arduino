#include <EEPROM.h>

void B_to_D(void);
void writeString(int add,String data);
String read_String(int add);

int preAdr = 0;
int addr = 1;
int addrs =0;
char fun_name[10];
char scene_name[20];
uint8_t tx_pin = 0;
String receive_buffer = "";
char chr_arr[100];
bool stringComplete = false;  // whether the string is complete
char led_no,led_state;
uint8_t prv_state = LOW,state=LOW,val;
uint8_t count = 0;
byte arr[8];
volatile int arr1[50];
int dec_t;
int i = 0,j=0,end_t = 0,end_t1=0;
String recivedData;

/*****serial wire connections 
 * * Arduino       ESP
 *     3            13(Ack Pin)
 *     4            15(Data Pin)
 *     5            12(clk_Pin)
 */
//******************************************************************

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(4,INPUT);//data pin
  pinMode(3,INPUT);//Ack Pin
  pinMode(5,INPUT);//clk_pin
  String data = "Hello World";
  Serial.print("Writing Data:");
  Serial.println(data);
  //delay(5);
   preAdr = EEPROM.read(addrs);
   addrs = addrs+1;
  Serial.print("preAdr : ");
  Serial.println(preAdr);
  recivedData = read_String(0);
  delay(5);
  int length_t =recivedData.length();
  Serial.print("recivedData : ");
  Serial.println(recivedData);
  Serial.print("length_t :");
  Serial.println(length_t);
}
//****************************Loop

void loop(){
  // put your main code here, to run repeatedly:
  int inchar1 = digitalRead(3);
  int clk_pin = digitalRead(5);
 
  if(inchar1 == HIGH && clk_pin==HIGH){
    int data    = digitalRead(4);
    prv_state = inchar1;
    if(data == LOW){
      val = 0;   
    }
    else if(data == HIGH){
      val = 1;
    }
    Serial.print(val);
    arr[i++] = val;
    if(i>50){
      i=0;  
    }
    
    if(i==8){
      B_to_D();
      chr_arr[j++] = (char)dec_t;            
      dec_t = 0;
      
      if(j>100){
        j=0;
      }
      i=0;    
    }
    delay(15); 
 }
 if(prv_state == HIGH && inchar1 == LOW){
  i = 0;
  end_t =1;
  count =0;
  dec_t = 0;
  prv_state =LOW;
 }
  
 if(end_t == 1){
  uint8_t i = 0,comma = 0,m=0;
  Serial.println("");
  for(int k=0;k<j;k++){
    Serial.print(chr_arr[k]);    
    //writeString(0+k, chr_arr[k]);
  }
  Serial.println("");
  Serial.print("fun_name ");
   while((chr_arr[i] != ',')&&(comma==0)){
      fun_name[m] = chr_arr[i];
      Serial.print(fun_name[m]); 
       i++;
       m++;
    }
    comma++;
    i++;
    m=0;
    
     Serial.println("");
     Serial.print("scene_name "); 
    while((chr_arr[i] != ',')&&(comma==1)){
      scene_name[m] = chr_arr[i];
      Serial.print(scene_name[m]); 
       i++;
       m++;
    }
    comma++;
    i++;
    m=0;
  Serial.println("");
  Serial.print(fun_name); 
  //if(fun_name == "add"){
          Serial.println("writing...."); 
     writeString(preAdr,chr_arr+3); 
 // }
  
//   delay(5);
  j=0;
  end_t = 0;
  tx_pin = 1;
 }
//**************************Tx
 if(tx_pin == 1){

  byte thisstring[8] = {'0'};
  String sceneInfo;
  inchar1 = LOW;
  clk_pin = LOW;
  //delay(5);  
  recivedData = read_String(1);
  sceneInfo = recivedData;
//  Serial.print("sceneInfo : ");
//  Serial.println(sceneInfo);
  delay(5);
  
  pinMode(4,OUTPUT);//data pin
  pinMode(3,OUTPUT);//Ack Pin
  pinMode(5,OUTPUT);//clk_pin

 uint8_t count = recivedData.length();
  //Serial.println(count);
// for(uint8_t j=0;j<count;j++){
//      for(int k =7;k>=0;k--){
//        thisstring[k]= bitRead(sceneInfo[j],k);
//        Serial.print(thisstring[k]);
//        digitalWrite(3,HIGH);
//        digitalWrite(5,HIGH);
//        digitalWrite(4,thisstring[k]);
//        delay(5);
//        digitalWrite(5,LOW);
//        
//      }  
//    }
//    digitalWrite(3,LOW);
//    sceneInfo = "";
//    count = 0;   
    tx_pin = 0;
    delay(5);
  pinMode(4,INPUT);//data pin
  pinMode(3,INPUT);//Ack Pin
  pinMode(5,INPUT);//clk_pin  
 }
}

void B_to_D(void){
  int k,base=1;
    for(k=7;k>=0;k--)
    {
        dec_t = dec_t + arr[k] * base;
        base = base * 2;        
    }
}


void writeString(int add,String data)
{
  int _size = data.length();
  Serial.print("add ");
  Serial.println(add);
  Serial.print("_size ");
  Serial.println(_size);
  int i;
  for(i=0;i<=_size;i++)
  {
    EEPROM.write(add+i,data[i]);
  }
  EEPROM.write(add+_size,'\0');   //Add termination null character for String Data
 preAdr = preAdr + _size;
 if(preAdr >200){
  preAdr = 1;
  _size = 0;
 }
  EEPROM.write(0,preAdr);
} 

String read_String(int add)
{
  int i;
  char data[100]; //Max 100 Bytes
  int len=0;
//  Serial.println("preadd ");
//  Serial.println(preAdr);
  unsigned char k;
  k=EEPROM.read(add);
  while(k != '\0' && len<200)   //Read until null character
  {    
    k=EEPROM.read(add+len);
    data[len]=k;
    len++;
  }

  data[len]='\0';
  return String(data);
}
