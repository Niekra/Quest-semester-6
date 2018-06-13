#include <Wire.h>
#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 30
#define DATA_PIN 6
#define pwm 5
#define FORWARD 0
#define BACKWARD 1
#define SLOW 250
#define MEDIUM 50
#define FAST 5

CRGB leds[NUM_LEDS];

boolean direction = FORWARD;


void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
  Serial.println("slave");

  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
  randomSeed(analogRead(0));
  pinMode(pwm, OUTPUT);
  //analogWrite(pwm, 255);
  digitalWrite(pwm, LOW);
  rainbow(0,NULL);
}


void control_Stand(uint8_t stand){
  switch(stand){
    case 0:
      stand_0();
    break;
    case 1:
      stand_1();
    break;
    case 2:
      stand_2();
    break;
    case 3:
      stand_3();
    break;
    case 4:
      stand_4();
    break;
    default:
      stand_0();
    break;
  }


//  theaterChase
  
}

void control_Intensiteit(){
  
}


void control_Audio(){
  
}


void loop() {
  delay(100);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
//  while (1 < Wire.available()) { // loop through all but the last
   char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character

    if(c == 'S'){
      uint8_t stand = Wire.read();
      Serial.println(stand);
      control_Stand(stand);
      return;
    }
    else if (c == 'I'){
      int intensiteit = Wire.read();
      Serial.println(stand);
      Serial.println(intensiteit);
      control_Intensiteit();
      return;
    }
    else if (c == 'A'){
      int persoon = Wire.read();
      int nummer = Wire.read();
      control_Audio();
      return;    
    }
    else{
      int stand = Wire.read();
      Serial.println("Ongeldige data");
      Serial.println(c);
      Serial.println(stand);
      return;
    }
//  }
//  int x = Wire.read();    // receive byte as an integer
//  Serial.println(x);         // print the integer
}

  
 

