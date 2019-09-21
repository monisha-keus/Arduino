/**
** **Date : 6 sept 2019
*  **Blink Four Led on Switch Press
*/
//** this is commit to git hub
#define INTERVAL_500 500
#define INTERVAL_1000 1000
#define INTERVAL_1500 1500
#define INTERVAL_2000 2000

#define INTERVAL_400 400
#define INTERVAL_300 300
#define INTERVAL_200 200
#define INTERVAL_100 100

#define INTERVAL_80 80
#define INTERVAL_60 60
#define INTERVAL_40 40
#define INTERVAL_20 20

unsigned long time_1 = 0;
unsigned long time_2 = 0;
unsigned long time_3 = 0;
unsigned long time_4 = 0;

#define LED_3   5
#define LED_4   4
#define LED_5   14
#define LED_6   16
#define SW_5    2
#define SW_6    12
#define SW_7    13
#define SW_8    15

void Pattern_R1(void);
void Pattern_R2(void);
void Pattern_R3(void);
void Pattern_R4(void);
void Pattern_R5(void);
void Pattern_R6(void);


volatile byte interruptCounter1 = 0;
volatile byte interruptCounter2 = 0;

int numberOfInterrupts1 = 0;
int numberOfInterrupts2 = 0;

int current_SW5;
long milli_held_SW5;            // How long the button was held (milliseconds)
long  secs_held_SW5;           // How long the button was held (seconds)
long prev_secs_held_SW5;      // How long the button was held in the previous check
byte previous_SW5 = HIGH;
unsigned long firstTime_SW5;  // how long since the button was first pressed 

int current_SW6;
long milli_held_SW6;            // How long the button was held (milliseconds)
long  secs_held_SW6;           // How long the button was held (seconds)
long prev_secs_held_SW6;      // How long the button was held in the previous check
byte previous_SW6 = HIGH;
unsigned long firstTime_SW6;  // how long since the button was first pressed 

int hold_SW5_C2 = 0;
int hold_SW6_C2 = 0;
int hold_SW5_C4 = 0;
int hold_SW6_C4 = 0;


int read_SW7;
int read_SW8;
int read_SW5;
int read_SW6;

int state_3 = LOW;
int state_4 = LOW;
int state_5 = LOW;
int state_6 = LOW;


void setup() {
  Serial.begin(9600);
  pinMode(LED_3,OUTPUT);
  pinMode(LED_4,OUTPUT);
  pinMode(LED_5,OUTPUT);
  pinMode(LED_6,OUTPUT);
  pinMode(SW_5,INPUT);
  pinMode(SW_6,INPUT);
  pinMode(SW_7,INPUT);
  pinMode(SW_8,INPUT);
  attachInterrupt(digitalPinToInterrupt(SW_5),pushButton1_isr,FALLING); 
  attachInterrupt(digitalPinToInterrupt(SW_6),pushButton2_isr,FALLING); 
}

void loop() {
  read_SW7 = digitalRead(SW_7);
  read_SW8 = digitalRead(SW_8);
  read_SW5 =  digitalRead(SW_5);
  read_SW6 =  digitalRead(SW_6);
  
  current_SW5 = digitalRead(SW_5);
  current_SW6 = digitalRead(SW_6);

  if (current_SW5 == LOW && previous_SW5 == HIGH && (millis() - firstTime_SW5) > 200) {
    firstTime_SW5 = millis();
  }
  
  if (current_SW6 == LOW && previous_SW6 == HIGH && (millis() - firstTime_SW6) > 200) {
    firstTime_SW6 = millis();
  }
  
  milli_held_SW5 = (millis() - firstTime_SW5);
  secs_held_SW5 = milli_held_SW5 / 1000;
  //Serial.println(secs_held_SW5);

  milli_held_SW6 = (millis() - firstTime_SW6);
  secs_held_SW6 = milli_held_SW6 / 1000;
  //Serial.println(secs_held_SW6);

  
  if(milli_held_SW5>50){
  if (current_SW5 == LOW && secs_held_SW5 > prev_secs_held_SW5) {
       //  Serial.print("More 3 sec");
       if((read_SW7 == HIGH)&&(read_SW8 == HIGH)){
        hold_SW5_C2 = !hold_SW5_C2;
       }
       if((read_SW7 == LOW)&&(read_SW8 == LOW)){
         hold_SW5_C4 = !hold_SW5_C4;
       }
       //Serial.print("hold_SW5_C2 ");
         //Serial.println(hold_SW5_C2);
       
    }
  }
  if(milli_held_SW5>50){
  if (current_SW6 == LOW && secs_held_SW6 > prev_secs_held_SW6) {
        if((read_SW7 == HIGH)&&(read_SW8 == HIGH)){
        hold_SW6_C2 = !hold_SW6_C2;
       }
       if((read_SW7 == LOW)&&(read_SW8 == LOW)){
         hold_SW6_C4 = !hold_SW6_C4;
       }
        Serial.print("hold_SW6_C2 ");
        Serial.println(hold_SW6_C2);
       // digitalWrite(14,HIGH);
    }
  }
    prev_secs_held_SW5 = secs_held_SW5;
    prev_secs_held_SW6 = secs_held_SW6;
    previous_SW5 = current_SW5;
    previous_SW6 = current_SW6;


      //Serial.print("prev_secs_held ");
      //Serial.println(prev_secs_held_SW6);
  
//*********************************************************************
  
  if((read_SW7 == HIGH) && (read_SW8 == HIGH)){
   // Serial.println("in case1");
    if(interruptCounter1>0){
      numberOfInterrupts1++;
      if(numberOfInterrupts1>0){
        //Serial.println(hold_SW5_C2);
        if(hold_SW5_C2){
                  Pattern_R2();
                  Serial.println("Pattern_R2");
        }
        else{
        Pattern_R1();
         Serial.println(" R_1");
        }

      }
            
    }
    else if(interruptCounter2>0){
      
      numberOfInterrupts2++;
      if(numberOfInterrupts2>0){
        if(hold_SW6_C2){
          
                  Pattern_R3();
                  Serial.println("Pattern_R3");
        }
        else{
        Pattern_R4();
         Serial.println(" R_4");
        }
     }
    }
  }
//*******************************************************
  else if((read_SW7 == LOW)&&(read_SW8 == LOW)){
        //Serial.println("in case2");
    if(interruptCounter1>0){
      numberOfInterrupts1++;
      if(numberOfInterrupts1>0){
        if(hold_SW5_C4){
                  Pattern_R4();
                  Serial.println("Pattern_R4");
        }
        else{
          Pattern_R3();
          Serial.println("Pattern_R3");
        }


      }
            
    }
    else if(interruptCounter2>0){
      
      numberOfInterrupts2++;
      if(numberOfInterrupts2>0){
        if(hold_SW6_C4){
                  Pattern_R1();
                  Serial.println("Pattern_R1");
        }
        else{
         Pattern_R2();
         Serial.println(" R_2");
        }
     }
    }
  }
  //************************************
  else if((read_SW7 == HIGH)&&(read_SW8 == LOW)){
       // Serial.println("in case3");

    if(interruptCounter1>0){
      interruptCounter1--;
      numberOfInterrupts2 = 0;
      numberOfInterrupts1 = 0;
    }
    else if(interruptCounter2>0){
      interruptCounter2--;
      numberOfInterrupts1 = 0;
      numberOfInterrupts2 = 0;
    }
        Pattern_R5();
                 //Serial.println(" R_5");

  }

 //*******************************************************
 else if((read_SW8 == HIGH)&&(read_SW7 == LOW)){
      //Serial.println("in case4");

    if(interruptCounter1>0){
      interruptCounter1--;
      numberOfInterrupts1 = 0;
      numberOfInterrupts2 = 0;
    }
    else if(interruptCounter2>0){
      interruptCounter2--;
      numberOfInterrupts1 = 0;
      numberOfInterrupts2 = 0;
    }
        Pattern_R6();
                 //Serial.println(" R_6");

  } 
    
  //********************************************************
  else{
    Serial.println("other_case");
    numberOfInterrupts1 = 0;
    numberOfInterrupts2 = 0;
    digitalWrite(LED_3,LOW);
    digitalWrite(LED_4,LOW);
    digitalWrite(LED_5,LOW);
    digitalWrite(LED_6,LOW);

  }
  
}
//******R1 Blinking Pattern
void Pattern_R1(void){
//Serial.println("pattern_R1");

  if(millis() > time_1 + INTERVAL_500){
        state_3 = !state_3;
        time_1 = millis();
        digitalWrite(LED_3,state_3);
    }
   
    if(millis() > time_2 + INTERVAL_1000){
        state_4 = !state_4;
        time_2 = millis();
        digitalWrite(LED_4,state_4);
    }
   
    if(millis() > time_3 + INTERVAL_1500){
        state_5 = !state_5;
        time_3 = millis();
        digitalWrite(LED_5,state_5);
       // print_time(time_3);
       // Serial.println(" LED is the 5th.");
    }
   
    if(millis() > time_4 + INTERVAL_2000){
        state_6 = !state_6;
        time_4 = millis();
        digitalWrite(LED_6,state_6);
    }

}

//******R2 Blinking Pattern

void Pattern_R2(void){
//Serial.println("pattern_R2");

    if(millis() > time_1 + INTERVAL_500){
        state_6 = !state_6;
        time_1 = millis();
        digitalWrite(LED_6,state_6);
       // Serial.println("isr2_LED6");
    }
   
    if(millis() > time_2 + INTERVAL_1000){
        state_5 = !state_5;
        time_2 = millis();
        digitalWrite(LED_5,state_5);
         //Serial.println("isr2_LED5");
    }
   
    if(millis() > time_3 + INTERVAL_1500){
        state_4 = !state_4;
        time_3 = millis();
        digitalWrite(LED_4,state_4);
          //Serial.println("isr2_LED4");

       // print_time(time_3);
       // Serial.println(" LED is the 5th.");
    }
   
    if(millis() > time_4 + INTERVAL_2000){
        state_3 = !state_3;
        time_4 = millis();
        digitalWrite(LED_3,state_3);
         //Serial.println("isr2_LED3");
       // Serial.println("Message four is in the house!");
    }

}
//****R4 Blink Pattern

void Pattern_R4(void){
//Serial.println("pattern_R4");


  if(millis() > time_1 + INTERVAL_400){
        state_3 = !state_3;
        time_1 = millis();
        digitalWrite(LED_3,state_3);
    }
   
    if(millis() > time_2 + INTERVAL_300){
        state_4 = !state_4;
        time_2 = millis();
        digitalWrite(LED_4,state_4);
    }
   
    if(millis() > time_3 + INTERVAL_200){
        state_5 = !state_5;
        time_3 = millis();
        digitalWrite(LED_5,state_5);
       // print_time(time_3);
        //Serial.println(" LED is the 5th.");
    }
   
    if(millis() > time_4 + INTERVAL_100){
        state_6 = !state_6;
        time_4 = millis();
        digitalWrite(LED_6,state_6);
        //Serial.println("Message four is in the house!");
    }

}
//*********************R3_Blink_Pattern

void Pattern_R3(void){
//Serial.println("pattern_R3");


  if(millis() > time_1 + INTERVAL_100){
        state_3 = !state_3;
        time_1 = millis();
        digitalWrite(LED_3,state_3);
    }
   
    if(millis() > time_2 + INTERVAL_200){
        state_4 = !state_4;
        time_2 = millis();
        digitalWrite(LED_4,state_4);
    }
   
    if(millis() > time_3 + INTERVAL_300){
        state_5 = !state_5;
        time_3 = millis();
        digitalWrite(LED_5,state_5);
       // print_time(time_3);
       // Serial.println(" LED is the 5th.");
    }
   
    if(millis() > time_4 + INTERVAL_400){
        state_6 = !state_6;
        time_4 = millis();
        digitalWrite(LED_6,state_6);
        //Serial.println("Message four is in the house!");
    }

}

//******************************R5 Blink_Pattern

void Pattern_R5(void){

if(micros() > time_1 + 200){
        state_3 = !state_3;
        time_1 = micros();
        digitalWrite(LED_3,state_3);
    }
   
    if(micros() > time_2 + 400){
        state_4 = !state_4;
        time_2 = micros();
        digitalWrite(LED_4,state_4);
    }
   
    if(micros() > time_3 + 600){
        state_5 = !state_5;
        time_3 = micros();
        digitalWrite(LED_5,state_5);
    }
   
    if(micros() > time_4 + 800){
        state_6 = !state_6;
        time_4 = micros();
        digitalWrite(LED_6,state_6);
    }
 /* if(millis() > time_1 + INTERVAL_20){
        state_3 = !state_3;
        time_1 = millis();
        digitalWrite(LED_3,state_3);
    }
   
    if(millis() > time_2 + INTERVAL_40){
        state_4 = !state_4;
        time_2 = millis();
        digitalWrite(LED_4,state_4);
    }
   
    if(millis() > time_3 + INTERVAL_60){
        state_5 = !state_5;
        time_3 = millis();
        digitalWrite(LED_5,state_5);
    }
   
    if(millis() > time_4 + INTERVAL_80){
        state_6 = !state_6;
        time_4 = millis();
        digitalWrite(LED_6,state_6);
    }*/

}

//*********************R6 Blink_Pattern

void Pattern_R6(void){
if(micros() > time_1 + 80){
        state_3 = !state_3;
        time_1 = micros();
        digitalWrite(LED_3,state_3);
    }
   
    if(micros() > time_2 + 60){
        state_4 = !state_4;
        time_2 = micros();
        digitalWrite(LED_4,state_4);
    }
   
    if(micros() > time_3 + 40){
        state_5 = !state_5;
        time_3 = micros();
        digitalWrite(LED_5,state_5);
    }
   
    if(micros() > time_4 + 20){
        state_6 = !state_6;
        time_4 =micros();
        digitalWrite(LED_6,state_6);
    }
  /*if(millis() > time_1 + INTERVAL_80){
        state_3 = !state_3;
        time_1 = millis();
        digitalWrite(LED_3,state_3);
    }
   
    if(millis() > time_2 + INTERVAL_60){
        state_4 = !state_4;
        time_2 = millis();
        digitalWrite(LED_4,state_4);
    }
   
    if(millis() > time_3 + INTERVAL_40){
        state_5 = !state_5;
        time_3 = millis();
        digitalWrite(LED_5,state_5);
    }
   
    if(millis() > time_4 + INTERVAL_20){
        state_6 = !state_6;
        time_4 = millis();
        digitalWrite(LED_6,state_6);
    }*/

}

//********ISR
ICACHE_RAM_ATTR
void pushButton1_isr() {

 static unsigned long last_interrupt_time = 0;
 unsigned long interrupt_time = millis(); 
 // If interrupts come faster than 200ms, assume it's a bounce and ignore
 if (interrupt_time - last_interrupt_time > 200)
 {
     interruptCounter2 = 0;
     interruptCounter1++;
     //state = !state;

 } 
 last_interrupt_time = interrupt_time;
}

void pushButton2_isr() {

 static unsigned long last_interrupt_time = 0;
 unsigned long interrupt_time = millis(); 
 // If interrupts come faster than 200ms, assume it's a bounce and ignore
 if (interrupt_time - last_interrupt_time > 200)
 {
     interruptCounter1 = 0;
     interruptCounter2++;
 } 
 last_interrupt_time = interrupt_time;
}
