
String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
int led;
int state = LOW;
int count = 0;
int val,i,j;
byte thisstring[8];
void setup() {
  // initialize serial:
  Serial.begin(9600);
  pinMode(4,OUTPUT);//data pin
  pinMode(3,OUTPUT);//
  pinMode(5,OUTPUT);//clk_pin
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}

void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {
    count = inputString.length();
    //Serial.println(inputString);
    //Serial.println("count ");
    ////Serial.print(count);
    for(j=0;j<count-1;j++){
      //inputString1[j] = inputString[j];
      for(int k =7;k>=0;k--){
        thisstring[k]= bitRead(inputString[j],k);
        Serial.print(thisstring[k]);
        digitalWrite(3,HIGH);
        digitalWrite(4,thisstring[k]);
        digitalWrite(5,HIGH);
        delayMicroseconds(5);
        digitalWrite(5,LOW);
        
      }  
    }
    digitalWrite(3,LOW);
    inputString = "";
    stringComplete = false;
    count = 0;
  }
    
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    if (inChar != '\n')
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
