const int clockPin = 10;    
const int outputPin = 13;
const int ratePin = A0;    // select the input pin for the potentiometer
const int widthPin = A1;    // select the input pin for the potentiometer

int pulseWidth = 100; 

unsigned int count = 1; 
byte clockHigh = 0; 

void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);

  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Clock Divider - Take one");

  pinMode(clockPin, INPUT);
}

void trigger(){ 
  digitalWrite(outputPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(pulseWidth);              // wait for a second
  digitalWrite(outputPin, LOW);    // turn the LED off by making the voltage LOW
}


void loop() {
  
  byte clockState = digitalRead(clockPin);
  byte rateValue = analogRead(ratePin);
  rateValue = map(rateValue, 0, 1023, 0, 64);

  pulseWidth = analogRead( widthPin);
  
  // check if clock was received, if so increment
  if (clockState == HIGH && clockHigh == 0) {
    Serial.println(count);
    clockHigh = 1;
    count++; 
  } else if (clockState == HIGH && clockHigh == 1) {
    
  } else { 
    clockHigh = 0; 
  }
  
  // clock divider
    if (count / rateValue == 1 || count > rateValue){ 
    // do something every 16th note 
    trigger();            // wait for a second
    Serial.println("Trigger");
    Serial.println(rateValue);
    count = 1;
  }
  
}


