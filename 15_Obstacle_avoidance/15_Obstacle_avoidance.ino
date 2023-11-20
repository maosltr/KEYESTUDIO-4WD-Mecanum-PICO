
#include "MecanumCar_v2.h"
#include "Servo.h"

mecanumCar mecanumCar(20, 21); // sda-->20,scl-->21
Servo myservo;                 // Define an instance of a servo

/*******Ultrasonic sensor interface*****/
#define EchoPin 4 // ECHO to GPIO4
#define TrigPin 3 // TRIG to GPIO3

/*******Define the pin of Line Tracking Sensor**********/
#define SensorLeft 16   // input pin of left sensor
#define SensorMiddle 17 // input pin of middle sensor
#define SensorRight 18  // input pin of right sensor

void setup()
{
  pinMode(EchoPin, INPUT);  // The ECHO pin is set to input mode
  pinMode(TrigPin, OUTPUT); // The TRIG pin is set to output mode
  myservo.attach(2);        // attaches the servo on GPIO2 to the servo object
  myservo.write(90);        // Rotate to 90 degrees

  pinMode(SensorLeft, INPUT);
  pinMode(SensorMiddle, INPUT);
  pinMode(SensorRight, INPUT);

  mecanumCar.Init(); // Initialize the seven-color LED and the motor drive
}

void loop()
{

  int pos;
  int distance;
  int newDistance;

  for (pos = 45; pos <= 135; pos += 10)
  { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos); // tell servo to go to position in variable 'pos'
    mecanumCar.Advance();
    distance = get_distance();
    if (distance <= 30)
    {
      mecanumCar.Stop();
      delay(20000);
    }
  }
  for (pos = 135; pos >= 45; pos -= 10)
  {                     // goes from 180 degrees to 0 degrees
    myservo.write(pos); // tell servo to go to position in variable 'pos'
    mecanumCar.Advance();
    distance = get_distance();
    if (distance <= 30)
    {
      mecanumCar.Stop();
      delay(20000);
    }
  }

  /*
    while (distance < 20)
    {
      distance = get_distance();
      Serial.print(distance);
      Serial.println("cm");

      if (pos < 90)
      {
        myservo.write(91);

        while (distance < 60)
        {
          distance = get_distance();
          Serial.print(distance);
          Serial.println("cm DL");
          mecanumCar.drift_left();
        }
      }
      else
      {
        myservo.write(89);

        while (distance < 60)
        {
          distance = get_distance();
          Serial.print(distance);
          Serial.println(" cm DR");
          mecanumCar.drift_right();
        }
      }
    }
    delay(1000);
  */
}

/*********************Ultrasonic detects the distance*******************************/
int get_distance(void)
{ // Ultrasonic detects the distance
  int dis;
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH); // Give the TRIG a high level of at least 10 µ s to trigger
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  dis = pulseIn(EchoPin, HIGH) / 58.2; // Work out the distance

  delay(30);
  return dis;
}
