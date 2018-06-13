int pwm = 5;
int val = 0;
int percentage=100;

void setup() {
  pinMode(pwm, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  val = int(255 * percentage/100);
  Serial.print(percentage);
  analogWrite(pwm, val);
  delay(10000);
//  percentage =100;
//  percentage -= 10; 
//   analogWrite(pwm, 150);
//  delay(1000); 

//  for (int i=0; i<255; i++){
//    analogWrite(pwm, 255);
//    Serial.println(i);
//  }
//  delay(1000);
//
//  for (int i=255; i>0; i--){
//    analogWrite(pwm, i);
//    Serial.println(i);
////    delay(100);
//  }
  
}
