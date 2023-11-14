
#include "MecanumCar_v2.h"
#include "Servo.h"

mecanumCar mecanumCar(20, 21);  //sda-->20,scl-->21
Servo myservo;    //Define an instance of a servo

/*******Ultrasonic sensor interface*****/
#define EchoPin  4  //ECHO to GPIO4
#define TrigPin  3  //TRIG to GPIO3

/*******Define the pin of Line Tracking Sensor**********/
#define SensorLeft    16   //input pin of left sensor
#define SensorMiddle  17   //input pin of middle sensor
#define SensorRight   18   //input pin of right sensor

void setup() {
  pinMode(EchoPin, INPUT);    //The ECHO pin is set to input mode
  pinMode(TrigPin, OUTPUT);   //The TRIG pin is set to output mode
  myservo.attach(2);  // attaches the servo on GPIO2 to the servo object
  myservo.write(90); //Rotate to 90 degrees

  pinMode(SensorLeft, INPUT);
  pinMode(SensorMiddle, INPUT);
  pinMode(SensorRight, INPUT);

  mecanumCar.Init(); //Initialize the seven-color LED and the motor drive
}

void loop() {
  
  uint8_t SL = digitalRead(SensorLeft);   //Read the value of the left line tracking sensor
  uint8_t SM = digitalRead(SensorMiddle); //Read the value of the left line tracking sensor
  uint8_t SR = digitalRead(SensorRight);  //Read the value of the right line tracking sensor

  int distance = get_distance();  //Get the distance and save in the distance variable  
  Serial.println(distance);


 
  mecanumCar.right_led(0);  //Turn off the right seven-color LED
  mecanumCar.left_led(0);
  
  
  // Stop at the edge of stairs
 
  if (SR == HIGH && SM == HIGH && SL == HIGH)
  {
    mecanumCar.Stop();
    mecanumCar.right_led(1);  //Turn on the right seven-color LED
    mecanumCar.left_led(1);   //Turn on the left seven-color LED
    mecanumCar.Back(80, 80, 80, 80);
    delay(500);
    mecanumCar.Turn_Left(80, 80, 80, 80);
    delay(500);

  }

  else if (distance<20){
    mecanumCar.Stop();
    mecanumCar.right_led(1);  //Turn on the right seven-color LED
    mecanumCar.left_led(1);   //Turn on the left seven-color LED
    mecanumCar.Back(80, 80, 80, 80);
    mecanumCar.Turn_Right(80, 80, 80, 80);
    delay(500);

  }
  else {
    mecanumCar.Advance(45, 45, 45, 45);
    mecanumCar.right_led(0);  //Turn off the right seven-color LED
    mecanumCar.left_led(0);   //Turn off the left seven-color LED
  }


  
  
}


/*********************Ultrasonic detects the distance*******************************/
int get_distance(void) {    //Ultrasonic detects the distance
  int dis;
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH); //Give the TRIG a high level of at least 10 µ s to trigger
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  dis = pulseIn(EchoPin, HIGH) / 58.2; //Work out the distance

  delay(30);
  return dis;
}
