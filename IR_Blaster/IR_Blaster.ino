//******MODE
#define M_COOL          0x0C
#define M_FAN           0x06
#define M_HUMID         0x04

//******SWING
#define S_HORIZONTAL    0xF0
#define S_VERTICAL_ON   0xF0
#define S_VERTICAL_OFF   0x00

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


unsigned char arr[]={0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
unsigned char mode,FanSpeed,Temp,swing_H,swing_v_state,AC_State;
void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  int loop;
 //*************************************************************** 
   
   mode          =  M_COOL;
   FanSpeed      =  F1; 
   swing_v_state =  S_VERTICAL_OFF;
   swing_H       =  S_HORIZONTAL;
   Temp          =  temp_30;
   AC_State      =  OFF;
   
//*** AC_On******************************************************

  if(AC_State == ON){ 
   mode      =  mode|0x80;
   FanSpeed  = FanSpeed | swing_v_state; 

   if(mode == M_HUMID){
        Temp      =   0x03;
        FanSpeed  =   (F_AUTO | swing_v_state);
   }
   
  else if(mode == M_FAN){
       Temp =   temp_25;  
       }
//***************************************************************
   arr[8] = S_HORIZONTAL;
   arr[9]=   FanSpeed;
   arr[11] = Temp;
   arr[12] = mode;
   
  Serial.println("Array elements are:    \n");
  for(loop=12;loop>=0;loop--){
   Serial.print(arr[loop],HEX);
   Serial.print(" ");
  }
  Serial.println("");
  }
  //*****AC_OFF*************************************
  
  else if (AC_State == OFF) {
   mode =       (mode | 0x00);
   FanSpeed   = FanSpeed | swing_v_state; 
   arr[12] =  mode; 
   arr[8] =   S_HORIZONTAL;
   arr[9]=    FanSpeed;
   arr[11] =  Temp;
   
  Serial.println("Array elements are:    \n");
    for(loop=12;loop>=0;loop--){
     Serial.print(arr[loop],HEX);
     Serial.print(" ");
    }
    Serial.println("");

  }
}
 
void loop() {
  // put your main code here, to run repeatedly:
  
 
 }
