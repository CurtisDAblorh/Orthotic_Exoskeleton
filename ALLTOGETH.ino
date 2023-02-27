
// Setting up EMG Sensors
const int EMG = 32;
// set pin numbers
const int touchPin = 13; 
const int touchPin22 =27;
const int ledPin = 33;
// change with your threshold value
const int thresholdL = 20;
//Average Code TOUCH PIN 1
const int numReadings = 5;
int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average
//Average Code TOUCH PIN 2
const int T2Readings = 5;
int T2readings[T2Readings];      // the readings from the analog input
int T2readIndex = 0;              // the index of the current reading
int T2total = 0;                  // the running total
int T2average = 0;                // the average
//Average Code EMG PIN
const int EMGReadings = 50;
int Ereadings[EMGReadings];      // the readings from the analog input
int EreadIndex = 0;              // the index of the current reading
int Etotal = 0;                  // the running total
int Eaverage = 0;  
//Average Code contract value
const int MVICEMGReadings = 50;
int MVICreadings[MVICEMGReadings];      // the readings from the analog input
int MVICreadIndex = 0;              // the index of the current reading
int MVICtotal = 0;                  // the running total
int MVICaverage = 0; 

int MVICButton;
int MVICVal;
int MVICReading[50];
//Average Code Rest Value
const int RestEMGReadings = 50;
int Restreadings[RestEMGReadings];      // the readings from the analog input
int RestreadIndex = 0;              // the index of the current reading
int Resttotal = 0;                  // the running total
int Restaverage = 0;

int RestButton;
int RestVal;
int RestReading[50];

//Defining Actuator Controls
const byte motA_AIN1 = 26;   //Reverse MOTOR A connected to M+
const byte motA_AIN2 = 25;  //Forward MOTOR A connected to M-

//setting PWM properties
const int freq = 5000;
const int pwmchannel1 = 0;
const int pwmchannel2 = 2;
const int resolution = 8;
//int dutyCycle = 200;


//Setting up Fucntions
//TouchPin Functions
void TouchPin1F(){
  // read the state of the pushbutton value:
  //touchValue = touchRead(touchPin);
  // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = touchRead(touchPin);
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }
  // calculate the average:
  average = total / numReadings;
  // send it to the computer as ASCII digits
  delay(1);        // delay in between reads for stability
//Serial.print(average);
  // check if the touchValue is below the threshold
  // if it is, set ledPin to HIGH
  if(average < thresholdL){
    // turn LED on
    digitalWrite(ledPin, HIGH);
    delay(50);
    digitalWrite(ledPin, LOW);
    delay(50);
    digitalWrite(ledPin, HIGH);
    delay(50);
    digitalWrite(ledPin, LOW);
    delay(50);
    //Serial.println(" - LED FLASH");
  }
  else{
    // turn LED off
    digitalWrite(ledPin, LOW);
    //Serial.println(" - LED off");
  }
}

void TouchPin2F(){
  //SECOND TOUCH PIN
   T2total = T2total - T2readings[T2readIndex];
  // read from the sensor:
  T2readings[T2readIndex] = touchRead(touchPin22);
  // add the reading to the total:
  T2total = T2total + T2readings[T2readIndex];
  // advance to the next position in the array:
  T2readIndex = T2readIndex + 1;

  // if we're at the end of the array...
  if (T2readIndex >= T2Readings) {
    // ...wrap around to the beginning:
    T2readIndex = 0;
  }
  // calculate the average:
  T2average = T2total / T2Readings;
  // send it to the computer as ASCII digits
  delay(1);        // delay in between reads for stability
//Serial.print(T2average);
  // check if the touchValue is below the threshold
  // if it is, set ledPin to HIGH
  if(T2average < thresholdL){
    // turn LED on
    digitalWrite(ledPin, HIGH);
    delay(50);
    //Serial.println(" - 2NDLED FLASH");
  }
  else{
    // turn LED off
    digitalWrite(ledPin, LOW);
    //Serial.println(" - LED off");
  }
}

void MVICAVERAGEF(){

//Max Voluntary Isometric Contraction AVERAGE
//Calibration for MVIC Valu
if(average < thresholdL){
  MVICButton=1;
  MVICtotal = MVICtotal - MVICreadings[MVICreadIndex];
  // read from the sensor:
  MVICreadings[MVICreadIndex] = analogRead(EMG);
  // add the reading to the total:
  MVICtotal= MVICtotal + MVICreadings[MVICreadIndex];
  // advance to the next position in the array:
  MVICreadIndex = MVICreadIndex + 1;

  // if we're at the end of the array...
  if (MVICreadIndex >= MVICEMGReadings) {
    // ...wrap around to the beginning:
    MVICreadIndex = 0;
  }
  // calculate the average:
  MVICaverage = MVICtotal / MVICEMGReadings;
  // send it to the computer as ASCII digits
  delay(1);
 
}
  else{
    MVICButton=0; //if the button was not pressed, MVIC button is 0
  } 
}

void RESTAVERAGEF(){
//REST VALUE AVERAGE
 if(T2average < thresholdL){
  RestButton=1;
 Resttotal = Resttotal - Restreadings[RestreadIndex];
  // read from the sensor:
  Restreadings[RestreadIndex] = analogRead(EMG);
  // add the reading to the total:
  Resttotal= Resttotal + Restreadings[RestreadIndex];
  // advance to the next position in the array:
  RestreadIndex = RestreadIndex + 1;

  // if we're at the end of the array...
  if (RestreadIndex >= RestEMGReadings) {
    // ...wrap around to the beginning:
    RestreadIndex = 0;
  }
  // calculate the average:
  Restaverage = Resttotal / RestEMGReadings;
  // send it to the computer as ASCII digits
  delay(1);
 
}
  else{
    RestButton=0; //if the button was not pressed, MVIC button is 0
  } 
}

void EMGAVERAGEF(){
  //FINAL EMG AVERAGE 
Etotal = Etotal - Ereadings[EreadIndex];
  // read from the sensor:
  Ereadings[EreadIndex] = analogRead(EMG);
  // add the reading to the total:
  Etotal= Etotal + Ereadings[EreadIndex];
  // advance to the next position in the array:
  EreadIndex = EreadIndex + 1;

  // if we're at the end of the array...
  if (EreadIndex >= EMGReadings) {
    // ...wrap around to the beginning:
    EreadIndex = 0;
  }
  // calculate the average:
  Eaverage = Etotal / EMGReadings;
  // send it to the computer as ASCII digits
  }
  void Closehand(){
 ledcWrite(2, 0); 
    ledcWrite(0, 255); 
  //ledcWrite(pwmchannel2, 255);
    //delay(15);    
        Serial.println("Enable Extension");
  }
   void Openhand(){
 ledcWrite(2, 255); 
    ledcWrite(0, 0); 
  //ledcWrite(pwmchannel2, 255);
    //delay(15);    
   Serial.println("Enable Flexion");
  }
  
void HandOperation(){
  if(Eaverage < (Restaverage*1.1)){
  Closehand();

}
  else{
    Openhand(); //if the button was not pressed, MVIC button is 0
  } 
}



void setup(){
  Serial.begin(115200);
  delay(100); // give me time to bring up serial monitor
  // initialize the LED pin as an output:
  pinMode (ledPin, OUTPUT);
   for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
  for (int thisT2Reading = 0; thisT2Reading < T2Readings; thisT2Reading++) {
    T2readings[thisT2Reading] = 0;
  }
  for (int thisEReading = 0; thisEReading < EMGReadings; thisEReading++) {
    Ereadings[thisEReading] = 0;
  }
  for (int thisMVICReading = 0; thisMVICReading < MVICEMGReadings; thisMVICReading++) {
    MVICreadings[thisMVICReading] = 0;
  }
    for (int thisRestReading = 0; thisRestReading < RestEMGReadings; thisRestReading++) {
    Restreadings[thisRestReading] = 0;
  }
  // attach the channel to the GPIO to be controlled
 ledcAttachPin(motA_AIN1, pwmchannel1);
 ledcAttachPin(motA_AIN2, pwmchannel2);

 // configure LED PWM functionalitites
 ledcSetup(pwmchannel1, freq, resolution);
  ledcSetup(pwmchannel2, freq, resolution);
  
}


void loop(){
 TouchPin1F();
TouchPin2F();
MVICAVERAGEF();
RESTAVERAGEF();
EMGAVERAGEF();
HandOperation();
delay(1);        // delay in between reads for stability
  Serial.print(Restaverage);  // To freeze the lower limit
Serial.print("          ");
Serial.print(MVICaverage);  // To freeze the upper limit
Serial.print("          ");
Eaverage = constrain(Eaverage, Restaverage, MVICaverage);
Serial.println(Eaverage);  // To send all three 'data' points to the plotter
   }
   
