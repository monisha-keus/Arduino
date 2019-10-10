
void B_to_D(void);
void blink_led(void);

String receive_buffer = "";
char dec_arr[100];
bool stringComplete = false;  // whether the string is complete
char led_no,led_state;
uint8_t prv_state = LOW,state=LOW,val;
byte arr[8];
int dec_t=0;
int i = 0,j=0,end_t = 0;


void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(14,OUTPUT);
  pinMode(16,OUTPUT);
  pinMode(15,INPUT);
  pinMode(13,INPUT);
  pinMode(12,INPUT);
}

void loop() {
  
  // put your main code here, to run repeatedly:
  int inchar1 = digitalRead(13);
  int data = digitalRead(15);
  int clk_pin = digitalRead(12);

  if(inchar1 == HIGH && clk_pin==HIGH){
    prv_state = inchar1;
    if(data == LOW){
      val = 0;   
    }
    else if(data == HIGH){
      val = 1;
    }
    arr[i++] = val;
    if(i>8){
      i=0;  
    }
    if(i==8){
      B_to_D();
      dec_arr[j++] = (char)dec_t;
      blink_led();
      dec_t = 0;
      if(j>100){
        j=0;
      }
      i=0;    
    }
        delayMicroseconds(5);
 }
 if(prv_state == HIGH && inchar1 == LOW){
  i = 0;
  end_t =1;
//  count =0;
  dec_t = 0;
  prv_state =LOW;
 }
 if(end_t == 1){
  for(int k=0;k<j;k++)
  Serial.print(dec_arr[k]);
  j=0;
  end_t = 0;
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
//********************************************************************

void blink_led(void){
  if((j==1)||(j==5)||(j==9)||(j==13)){
        led_no = dec_arr[j-1];
      }
      if((j==3)||(j==7)||(j==11)||(j==15)){
      led_state = dec_arr[j-1];
        if(led_state == '0'){
          state = LOW;
        }
        else if(led_state == '1'){
          state = HIGH;
        }
      }
      if((led_no == '1')&&(led_state=='0' || led_state=='1')){
          digitalWrite(5,state);     
        }
        if((led_no == '2')&&(led_state=='0' || led_state=='1')){
          digitalWrite(4,state); 
          
        }
        if((led_no == '3')&&(led_state=='0' || led_state=='1')){
          digitalWrite(14,state);   
        }
        if((led_no == '4')&&(led_state=='0' || led_state=='1')){
          digitalWrite(16,state);    
        }               
}
