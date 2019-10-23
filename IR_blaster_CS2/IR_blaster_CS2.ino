//******MODE
#define M_COOL          0x0C
#define M_FAN           0x06
#define M_HUMID         0x04

//******SWING
#define S_HORIZONTAL_ON     0xF0
#define S_HORIZONTAL_OFF    0x00
#define S_VERTICAL_ON       0xF0
#define S_VERTICAL_OFF      0x00

//*******FAN_SPEED

#define F1              0x02
#define F2              0x0A
#define F3              0x06
#define F4              0x0E
#define F_AUTO          0x05
#define F_NIGHT         0x0D
#define F_OFF           0x0C

#define ON              1
#define OFF             0
//********TEMPERATURE
#define temp_18              0x24
#define temp_19              0x64
#define temp_20              0x34
#define temp_21              0x54
#define temp_22              0x34
#define temp_23              0x74
#define temp_24              0x0C
#define temp_25              0x4C
#define temp_26              0x2C
#define temp_27              0x6C
#define temp_28              0x1C
#define temp_29              0x5C
#define temp_30              0x3C
#define temp_31              0x7C

void read_serial_data(void);
void fill_arr(void);
void format_converter();
void summation();
void print_msb(void);


uint8_t mode_t,swing_v_state_t,swing_H_state_t,Temp_t,FanSpeed_t;
unsigned char arr[]={0x88,0x5B,0xE4,0x0F,0x00,0x00,0x00,0x40,0x88,0x5B,0xE4,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x00};
unsigned char arr2[28];
uint8_t sum;
uint8_t mode,FanSpeed,Temp,swing_H_state,swing_v_state,AC_State;
String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
int i=0;
byte rcv_string[10] = {0};


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
// put your main code here, to run repeatedly:
  if (stringComplete){
    read_serial_data();
    fill_arr();
    print_arr();
    Serial.println("");
    Serial.println("LSB8:");
    format_converter();
    summation();
    print_msb();
    
  }
}

/*
 * **Read serial data From serial moniter and decode
 */
void read_serial_data(void){
  uint8_t j=0,i=0,comma=1;
  uint8_t count = inputString.length();
  String Ac_state_str ="";
  String mode_str = "";
  String swing_H_state_str ="";
  String FanSpeed_str ="";
  String swing_v_state_str = "";
  String  Temp_str = "";
  for(i=0;i<count;i++){
    if(inputString[i] != 44){
      if(comma == 1){
        Ac_state_str += inputString[i];
      } 
      if(comma == 2){
        mode_str += inputString[i];
      }
      if(comma == 3){
        Temp_str += inputString[i];
      }
      if(comma == 4){
        FanSpeed_str += inputString[i];
      }
      
      if(comma == 5){
       swing_v_state_str += inputString[i];
      }      
      if(comma == 6){
        swing_H_state_str += inputString[i];
      } 
    }    
    else if(inputString[i] == 44) {
      comma++;
    }    
  }
  inputString = "";
  stringComplete = false;
  i=0;
//////Convert str into int/////////////////////////////

  AC_State =Ac_state_str.toInt();
  mode = mode_str.toInt();
  Temp = Temp_str.toInt();
  FanSpeed =FanSpeed_str.toInt();
  swing_v_state = swing_v_state_str.toInt();
  swing_H_state =  swing_H_state_str.toInt();   
}

//****************************************

void fill_arr(void){
  if(mode  == 1){
   mode_t = M_HUMID;
  }
  else if(mode  == 2){
   mode_t = M_FAN;
  }
  else if(mode  == 3){
   mode_t = M_COOL;   
  }
  
//////////////////////////////////////////////
  if(Temp == 18){
    Temp_t   =  temp_18;
  }
  
  else if(Temp == 19){
    Temp_t   =  temp_19; 
  }
  else if(Temp == 20){
    Temp_t   =  temp_20;   
  }
  else if(Temp == 21){
    Temp_t   =  temp_21;
  }
  
  else if(Temp == 22){
    Temp_t   =  temp_22;
  }
  else if(Temp == 23){
    Temp_t   =  temp_23;
  }
  else if(Temp == 24){
    Temp_t   =  temp_24;
  }
  else if(Temp == 25){
    Temp_t   =  temp_25;
  }
  else if(Temp == 26){
   Temp_t   =  temp_26;
  }
  else if(Temp == 27){
    Temp_t   =  temp_27;
  }
  
  else if(Temp == 28){
    Temp_t   =  temp_28;
  }
  else if(Temp == 29){
    Temp_t   =  temp_29;
  }
  
  else if(Temp == 30){
    Temp_t   =  temp_30;
  }
  else if(Temp == 31){
    Temp_t   =  temp_31;
  }
  
//***************************************************
  if(FanSpeed == 0){
    FanSpeed_t = F_OFF;
  }
  else if(FanSpeed == 1){
    FanSpeed_t = F1;
  }
  
  else if(FanSpeed == 2){
    FanSpeed_t = F2;
  }
  else if(FanSpeed == 3){
    FanSpeed_t = F3;
  }
  else if(FanSpeed == 4){
    FanSpeed_t = F4;
  }
  else if(FanSpeed == 5){
   FanSpeed_t = F_AUTO;
  }
  else if(FanSpeed == 6){
   FanSpeed_t = F_NIGHT;
  }
  
//*************************************************************** 
  
  if(swing_v_state == 0){
    swing_v_state_t = S_VERTICAL_OFF;
  }
  else if(swing_v_state == 1){
    swing_v_state_t = S_VERTICAL_ON;
  }
  if(swing_H_state == 0){
   swing_H_state_t = S_HORIZONTAL_OFF;
  }
  if(swing_H_state == 1){
   swing_H_state_t = S_HORIZONTAL_ON;
  }
}

//***************************************************

void print_arr(void){
  
//*** AC_On******************************************************
  int n=0;
  uint8_t l=0,m=0;
  uint8_t val = 0;
  uint8_t sum=0x00;
  
  if(AC_State == 1){ 
   FanSpeed_t  = FanSpeed_t | swing_v_state_t; 
   if(mode_t == M_HUMID){
       //mode_t      =  mode_t|0x80;
        Temp_t      =   0x03;
        FanSpeed_t  =   F_AUTO | swing_v_state_t;
   }
   
  if(mode_t == M_FAN){
       //mode_t      =  mode_t|0x80;
       Temp_t =   temp_25;  
       }
   mode_t      =  mode_t|0x80;
//***************************************************************
   arr[18]   = swing_H_state_t;
   arr[17]   = FanSpeed_t;
   arr[15]  = Temp_t;
   arr[14]  = mode_t;
  }
  //*****AC_OFF*************************************
  
  else if (AC_State == 0) {
   mode_t =    (mode_t | 0x00);
   FanSpeed_t   = FanSpeed_t | swing_v_state_t; 
   arr[18]   = swing_H_state_t;
   arr[17]   = FanSpeed_t;
   arr[15]  = Temp_t;
   arr[14]  = mode_t;  

  }
}
/**
**Function to convert MSB to LSB8 format
**/
void format_converter(){
Serial.println("");
uint8_t reverse_num = 0;
uint8_t val = 0;
 for (uint8_t j=0; j<27; j++){
  for (uint8_t i=0; i<8; i++){
    val = (arr[j] & (1 << i));
    if(val)
    reverse_num |= (1 << ((8 - 1) - i));
  }
  arr2[j] = reverse_num;
  Serial.print(arr2[j], HEX);
  Serial.print(" ");
  val = 0;
  reverse_num = 0;
 } 
Serial.println(""); 
}

/*
 * **Function To calculate checksum
 */
void summation(){
 uint8_t sum_t =0,sum2=0;
 sum = 0;
for(int k=8;k<26;k++){
     // Serial.println(k);
       sum += arr2[k];
   }
   for (uint8_t i=0; i<8; i++){
    sum_t = (sum & (1 << i));
    if(sum_t)
    sum2 |= (1 << ((8 - 1) - i));
  } 
  sum = sum2;
  arr[27]  = sum;
}

/*
 * **Function to print arr in MSB format
 */
void print_msb(void){
  int loop_t;  
  Serial.println("MSB :    \n");
  for(loop_t=0;loop_t<28;loop_t++){
   Serial.print(arr[loop_t],HEX);
   Serial.print(" ");
  }
  
  Serial.println("");
}

 /*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar= (char)Serial.read();
    // add it to the inputString:
   // if(inChar !=)
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
