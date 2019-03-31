const int pwm = 3;  //PWM control for motor outputs 1 and 2
const int dir = 2;  //direction control for motor outputs 1 and 2
const bool up = HIGH;
const bool down = LOW;

const int isUp = 0;
const int isDown = 1;
const int isMiddle = 2;


int motorP = isUp;


const int opticalPin = A0;
int opticalReading;


bool myBoolArr[3] = {false, false, false};
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);   // initialize serial for debugging
  pinMode(pwm, OUTPUT);  //Set control pins to be outputs
  pinMode(dir, OUTPUT);

  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  goUp();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(8)) {
    myBoolArr[0] = digitalRead(9);
    myBoolArr[1] = digitalRead(10);
    myBoolArr[2] = digitalRead(11);
    doIt();
  }

  delay(50);
}

void doIt()
{

  if (myBoolArr[0] == 1 && myBoolArr[1] == 0 && myBoolArr[2] == 0 && motorP != isUp) //go up
  {
    goUp();
  }
  else  if (myBoolArr[0] == 0 && myBoolArr[1] == 1 && myBoolArr[2] == 0 && motorP != isDown) //go down
  {
    goDown();
  }
  else  if (myBoolArr[0] == 1 && myBoolArr[1] == 1 && myBoolArr[2] == 0 && motorP != isMiddle)
  {
    goMiddle();
  }
  delay(1000);
}






void goUp()
{
  digitalWrite(13, 1);
  digitalWrite(dir, up);
  analogWrite(pwm, 120);

  opticalReading = digitalRead(opticalPin);
  while (opticalReading)
    opticalReading = digitalRead(opticalPin);

  digitalWrite(pwm, 0);
  digitalWrite(13, 0);
  motorP = isUp;
}


void goDown()
{
  if (motorP == isUp)
  {
    digitalWrite(13, 1);
    digitalWrite(dir, down);
    analogWrite(pwm, 120);
    delay(3000);
    digitalWrite(pwm, 0);
    digitalWrite(13, 0);
    motorP = isDown;
  }
  else if (motorP == isMiddle)
  {
    digitalWrite(13, 1);
    digitalWrite(dir, down);
    analogWrite(pwm, 120);
    delay(1500);
    digitalWrite(pwm, 0);
    digitalWrite(13, 0);
    motorP = isDown;
  }


}

void goMiddle()
{
  if (motorP == isUp)
  {
    digitalWrite(13, 1);
    digitalWrite(dir, down);
    analogWrite(pwm, 120);
    delay(1500);
    digitalWrite(pwm, 0);
    digitalWrite(13, 0);
    motorP = isMiddle;
  }
  else if (motorP == isDown)
  {
    digitalWrite(13, 1);
    digitalWrite(dir, up);
    analogWrite(pwm, 120);
    delay(1500);
    digitalWrite(pwm, 0);
    digitalWrite(13, 0);
    motorP = isMiddle;
  }
}
