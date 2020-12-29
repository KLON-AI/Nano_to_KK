#include <Arduino.h>
#include <Servo.h>

#define onboard 13
int fromPi = 0;
bool ARMED = false;
//SERIAL VALUE CODES
// 1 == ARM
// 0 == DISARM
// ANY OTHER VALUE == THROTTLE VALUE
Servo ail, ele, thr, rud, aux; //The various signal values
int vail, vele, vthr, vrud, vaux;
//int val=100;

void led(int time){
  digitalWrite(onboard, HIGH);
  delay(time);
  digitalWrite(onboard, LOW);
  delay(time);
}

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
  ARMED = true;

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
  ARMED = true;
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

    if(fromPi == 'Z')
    {
      arm();
      // vthr= 1200;
      // normalize();
      // delay(5);
      led(50);


    }
    else if(fromPi == 'X')
    {
      vthr= 1000;
      normalize();
      delay(700);
      disarm();
      led(50);
    }


    else if(fromPi == 'J')
    {
      // Yaw LEFT
      Serial.println("Yaw Left");
      vrud = 1000;
      vthr= 1500;
      normalize();
      delay(5);
    }

    else if(fromPi == 'L')
    {
      // Yaw RIGHT
      Serial.println("Yaw Right");
      vrud = 2000;
      vthr= 1500;
      normalize();
      delay(5);
    }


    else if(fromPi == 'I')
    {
      // Throttle UP
      Serial.println("Throttle UP");
      vthr= 1200;
      normalize();
      delay(5);
      // led(10);

    }
    else if(fromPi == 'K')
    {
      // Throttle DOWN
      Serial.println("Throttle DOWN");
      vthr= 1900;
      normalize();
      delay(5);
    }

    else if(fromPi == 'A')
    {
      // Left
      Serial.println("Left");
      vail = 1000;
      vthr= 1500;
      normalize();
      delay(5);
    }

    else if(fromPi == 'D')
    {
      // Right
      Serial.println("Right");
      vail = 2000;
      vthr= 1500;
      normalize();
      delay(5);
    }


    else if(fromPi == 'W')
    {
      // Forward
      Serial.println("Forward");
      vele = 1000;
      vthr= 1500;
      normalize();
      delay(5);
      // led(10);

    }
    else if(fromPi == 'S')
    {
      // Backward
      Serial.println("Backward");
      vele = 2000;
      vthr= 1500;
      normalize();
      delay(5);
    }


    else if(fromPi == 'M')
    {
      // Stable
      Serial.println("Stable");
      vail = 1502;
      vele = 1502;
      vthr = 1500;
      vrud = 1502;
      vaux = 2000;
      normalize();
      delay(5);
    }
// 1300 = 19

// 1500 = 44

// 1800 = 82

// 2000= 108

    else if(fromPi == 'C')
    {
      // reset
      Serial.println("Test ON");
      // vail = 1502;
      // vele = 1502;
      vthr = 1200;
      // vrud = 1502;
      // vaux = 2000;
      normalize();
      delay(5);
    }

    else if(fromPi == 'V')
    {
      // Test off
      Serial.println("Test OFF");
      vail = 1502;
      vele = 1502;
      vthr = 1000;
      vrud = 1502;
      vaux = 2000;
      normalize();
      delay(5);
    }




// No Input
    else if(fromPi == 'N')
    {
      Serial.print("No Input");
    }
    else{
      Serial.println("No Input");
    }
  }
}
