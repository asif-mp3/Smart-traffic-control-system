const int trig1 = A0;
const int echo1 = A1;
const int trig2 = A2;
const int echo2 = A3;
const int trig3 = A4;
const int echo3 = A5;
const int IR1 = 11;
const int IR2 = 12;
const int IR3 = 13;
const int R1 = 2;
const int Y1 = 3;
const int G1 = 4;
const int R2 = 5;
const int Y2 = 6;
const int G2 = 7;
const int R3 = 8;
const int Y3 = 9;
const int G3 = 10;
float duration1,duration2,duration3,duration4,distance1,distance2,distance3,distance4;
void setup() {
  Serial.begin(9600);
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
  pinMode(trig3, OUTPUT);
  pinMode(echo3, INPUT);
  pinMode(R1, OUTPUT);
  pinMode(Y1, OUTPUT);
  pinMode(G1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(Y2, OUTPUT);
  pinMode(G2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(Y3, OUTPUT);
  pinMode(G3, OUTPUT);
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
}

void loop() {
  AllLightsON();
  //IR start
  int sensorStatus1 = digitalRead(IR1);
  int sensorStatus2 = digitalRead(IR2);
  int sensorStatus3 = digitalRead(IR3);
  //us 1
  digitalWrite(trig1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig1, LOW);
  duration1 = pulseIn(echo1, HIGH);
  distance1 = 0.017 * duration1;
  //us 2
  digitalWrite(trig2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig2, LOW);
  duration2 = pulseIn(echo2, HIGH);
  distance2 = 0.017 * duration2;
  //us 3
  digitalWrite(trig3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig3, LOW);
  duration3 = pulseIn(echo3, HIGH);
  distance3 = 0.017 * duration3;
  //checking if no vehicles
  if(sensorStatus1 == sensorStatus2 == sensorStatus3 == 0)
  {
    AllLightsON();
    delay(7000);
  }
  //checking if vehicle in only one lane
  if(sensorStatus1 == 1 || sensorStatus2 == 1 || sensorStatus3 == 1)
  {
    if(sensorStatus1 == 1)
    {
      digitalWrite(R1, LOW);
      digitalWrite(G1, HIGH);
      delay(7000);
    }
    if(sensorStatus2 == 1)
    {
      digitalWrite(R2, LOW);
      digitalWrite(G2, HIGH);
      delay(7000);
    }
    if(sensorStatus3 == 1)
    {
      digitalWrite(R3, LOW);
      digitalWrite(G3, HIGH);
      delay(7000);
    }
  }
  //checking if vehicle is present in any 2 lanes
  if(sensorStatus1 == 1 && sensorStatus2 == 1 && sensorStatus3 == 0)
  {
    if(distance2 > distance1)
    {
      digitalWrite(R1, LOW);
      digitalWrite(G1, HIGH);
      digitalWrite(R2, LOW);
      digitalWrite(Y2, HIGH);
      delay(7000);
      digitalWrite(R1, HIGH);
      digitalWrite(Y2, LOW);
      digitalWrite(G2, HIGH);
      delay(7000);
    }
    if(distance1 > distance2)
    {
      digitalWrite(R2, LOW);
      digitalWrite(G2, HIGH);
      digitalWrite(R1, LOW);
      digitalWrite(Y1, HIGH);
      delay(7000);
      digitalWrite(R2, HIGH);
      digitalWrite(Y1, LOW);
      digitalWrite(G1, HIGH);
      delay(7000);
    }
  }
  if(sensorStatus1 == 1 && sensorStatus3 == 1 && sensorStatus2 == 0)
  {
    if(distance3 > distance1)
    {
      digitalWrite(R1, LOW);
      digitalWrite(G1, HIGH);
      digitalWrite(R3, LOW);
      digitalWrite(Y3, HIGH);
      delay(7000);
      digitalWrite(R1, HIGH);
      digitalWrite(Y3, LOW);
      digitalWrite(G3, HIGH);
      delay(7000);
    }
    if(distance1 > distance3)
    {
      digitalWrite(R3, LOW);
      digitalWrite(G3, HIGH);
      digitalWrite(R1, LOW);
      digitalWrite(Y1, HIGH);
      delay(7000);
      digitalWrite(R3, HIGH);
      digitalWrite(Y1, LOW);
      digitalWrite(G1, HIGH);
      delay(7000);
    }
  }
  if(sensorStatus2 == 1 && sensorStatus3 == 1 && sensorStatus1 == 0)
  {
    if(distance2 > distance3)
    {
      digitalWrite(R3, LOW);
      digitalWrite(G3, HIGH);
      digitalWrite(R2, LOW);
      digitalWrite(Y2, HIGH);
      delay(7000);
      digitalWrite(R3, HIGH);
      digitalWrite(Y2, LOW);
      digitalWrite(G2, HIGH);
      delay(7000);
    }
    if(distance3 > distance2)
    {
      digitalWrite(R2, LOW);
      digitalWrite(G2, HIGH);
      digitalWrite(R3, LOW);
      digitalWrite(Y3, HIGH);
      delay(7000);
      digitalWrite(R2, HIGH);
      digitalWrite(Y3, LOW);
      digitalWrite(G3, HIGH);
      delay(7000);
    }
  }
  //checking if all the lanes have vehicles
  if(sensorStatus1 == 1 && sensorStatus2 == 1 && sensorStatus3 == 1)
  {
    if(distance1>=distance2 && distance2>=distance3)
    {
      digitalWrite(R3, LOW);
      digitalWrite(G3, HIGH);
      digitalWrite(R2, LOW);
      digitalWrite(Y2, HIGH);
      delay(7000);
      digitalWrite(R3, HIGH);                         // 3 2 1
      digitalWrite(Y2, LOW);
      digitalWrite(G2, HIGH);
      digitalWrite(R1, LOW);
      digitalWrite(Y1, HIGH);
      delay(7000);
      digitalWrite(R2, HIGH);
      digitalWrite(Y1, LOW);
      digitalWrite(G1, HIGH);
      delay(7000);
    }
    if(distance3>=distance2 && distance2 >= distance1)
    {
      digitalWrite(R1, LOW);
      digitalWrite(G1, HIGH);
      digitalWrite(R2, LOW);
      digitalWrite(Y2, HIGH);
      delay(7000);
      digitalWrite(R1, HIGH);                         // 1 2 3
      digitalWrite(Y2, LOW);
      digitalWrite(G2, HIGH);
      digitalWrite(R3, LOW);
      digitalWrite(Y3, HIGH);
      delay(7000);
      digitalWrite(R2, HIGH);
      digitalWrite(Y3, LOW);
      digitalWrite(G3, HIGH);
      delay(7000);
    }
    if(distance2>=distance3 && distance3 > distance1)
    {
      digitalWrite(R1, LOW);
      digitalWrite(G1, HIGH);
      digitalWrite(R3, LOW);
      digitalWrite(Y3, HIGH);
      delay(7000);
      digitalWrite(R1, HIGH);                         // 1 3 2
      digitalWrite(Y3, LOW);
      digitalWrite(G3, HIGH);
      digitalWrite(R2, LOW);
      digitalWrite(Y2, HIGH);
      delay(7000);
      digitalWrite(R3, HIGH);
      digitalWrite(Y2, LOW);
      digitalWrite(G2, HIGH);
      delay(7000);
    }
    if(distance2 >=distance1 && distance1>=distance3)
    {
      digitalWrite(R3, LOW);
      digitalWrite(G3, HIGH);
      digitalWrite(R1, LOW);
      digitalWrite(Y1, HIGH);
      delay(7000);
      digitalWrite(R3, HIGH);                         // 3 1 2
      digitalWrite(Y1, LOW);
      digitalWrite(G1, HIGH);
      digitalWrite(R2, LOW);
      digitalWrite(Y2, HIGH);
      delay(7000);
      digitalWrite(R1, HIGH);
      digitalWrite(Y2, LOW);
      digitalWrite(G2, HIGH);
      delay(7000);
    }
    if(distance3 >= distance1 && distance1 >=distance2)
    {
      digitalWrite(R2, LOW);
      digitalWrite(G2, HIGH);
      digitalWrite(R1, LOW);
      digitalWrite(Y1, HIGH);
      delay(7000);
      digitalWrite(R2, HIGH);                         // 2 1 3
      digitalWrite(Y1, LOW);
      digitalWrite(G1, HIGH);
      digitalWrite(R3, LOW);
      digitalWrite(Y3, HIGH);
      delay(7000);
      digitalWrite(R1, HIGH);
      digitalWrite(Y3, LOW);
      digitalWrite(G3, HIGH);
      delay(7000);
    }
    if(distance1 >= distance3 && distance3 >= distance2)
    {
      digitalWrite(R2, LOW);
      digitalWrite(G2, HIGH);
      digitalWrite(R3, LOW);
      digitalWrite(Y3, HIGH);
      delay(7000);
      digitalWrite(R2, HIGH);                         // 2 3 1
      digitalWrite(Y3, LOW);
      digitalWrite(G3, HIGH);
      digitalWrite(R1, LOW);
      digitalWrite(Y1, HIGH);
      delay(7000);
      digitalWrite(R3, HIGH);
      digitalWrite(Y1, LOW);
      digitalWrite(G1, HIGH);
      delay(7000);
    }
  }
}
void AllLightsON()
{
  digitalWrite(R1, HIGH);
  digitalWrite(R2, HIGH);
  digitalWrite(R3, HIGH);
}