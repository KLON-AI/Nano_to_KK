#include <Arduino.h>
#include <Servo.h>

#define onboard 13
int fromPi = 0;

//SERIAL VALUE CODES
// 1 == ARM
// 0 == DISARM
// ANY OTHER VALUE == THROTTLE VALUE
Servo ail, ele, thr, rud, aux; //The various signal values
int vail, vele, vthr, vrud, vaux;
//int val=100;

//This function sends updated values to all the signals to the kk2.1
void normalize()
{
  ail.writeMicroseconds(vail);
  ele.writeMicroseconds(vele);
  thr.writeMicroseconds(vthr);
  rud.writeMicroseconds(vrud);
  aux.writeMicroseconds(vaux);
}

void arm()
{
  if (vthr > 1000)
  {
    Serial.println("Throttle not zero");
    return;
  }
  vrud = 1000;
  normalize();
  delay(3000);
  vrud = 1502;
  normalize();
  Serial.println("ARMED");

  digitalWrite(onboard, HIGH);
  delay(10);
  digitalWrite(onboard, LOW);
  delay(10);
}

void disarm()
{
  if (vthr > 1000)
  {
    Serial.println("Throttle not zero");
    return;
  }
  vrud = 2000;
  normalize();
  delay(3000);
  vrud = 1502;
  normalize();
  Serial.println("DISARMED");

  digitalWrite(onboard, HIGH);
  delay(10);
  digitalWrite(onboard, LOW);
  delay(10);
}

void setup()
{
  pinMode(onboard, OUTPUT);
  Serial.begin(115200);
  //initialization
  vail = 1502;
  vele = 1502;
  vthr = 1000;
  vrud = 1502;
  vaux = 2000;
  //attach servo objects
  ail.attach(3); //Roll
  ele.attach(5); //Pitch
  thr.attach(6); //Up Down
  rud.attach(9); //Yaw
  aux.attach(10);
  delay(1);
  normalize();
}

void loop()
{
  Serial.println("ACK");
  delay(20);

  if(Serial.available() > 0)
  {
    fromPi = Serial.read();
    // Serial.print("I Received: ");
    // Serial.print(fromPi,DEC);
    // Serial.print(fromPi);
    // delay(500);

    if(fromPi == 'A')
    {
      // Serial.print("ARM");
      arm();
      digitalWrite(onboard, HIGH);
      delay(100);
      digitalWrite(onboard, LOW);
      delay(100);
      digitalWrite(onboard, HIGH);
      delay(100);
      digitalWrite(onboard, LOW);
      delay(100);
    }
    else if(fromPi == 'D')
    {
      // Serial.print("DISARM");
      disarm();
      digitalWrite(onboard, HIGH);
      delay(100);
      digitalWrite(onboard, LOW);
      delay(100);
      digitalWrite(onboard, HIGH);
      delay(100);
      digitalWrite(onboard, LOW);
      delay(100);
      digitalWrite(onboard, HIGH);
      delay(100);
      digitalWrite(onboard, LOW);
      delay(100);
    }



    else if(fromPi == 'F')
    {
      // Throttle UP
      digitalWrite(onboard, HIGH);
      delay(100);
      digitalWrite(onboard, LOW);
      delay(100);
      digitalWrite(onboard, HIGH);
      delay(100);
      digitalWrite(onboard, LOW);
      delay(100);
    }
    else if(fromPi == 'B')
    {
      // Throttle DOWN
      digitalWrite(onboard, HIGH);
      delay(100);
      digitalWrite(onboard, LOW);
      delay(100);
      digitalWrite(onboard, HIGH);
      delay(100);
      digitalWrite(onboard, LOW);
      delay(100);
    }




// No Input
    else if(fromPi == 'N')
    {
      Serial.print("No Input");
    }
    else{
      Serial.print("No Input");
    }
  }
}
