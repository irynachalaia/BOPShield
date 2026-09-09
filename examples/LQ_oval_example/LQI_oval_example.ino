#include <SamplingServo.h>
#include <BOP_Shield.h>
#include <BasicLinearAlgebra.h>

using namespace BLA;

const float Ts_ms = 50.0;   
const float Ts = 0.05;      

float rX ;
float rY ;

float x = 0.0;
float y = 0.0;

float xPrev = 0.0;
float yPrev = 0.0;

float dx = 0.0;
float dy = 0.0;

float intX = 0.0;
float intY = 0.0;

float uX = 0.0;
float uY = 0.0;

Matrix<2, 6> K = {
  -0.43,   -0.11,    0.0000,   -0.0000,    0.2,   -0.0000,
   -0.0000,   -0.0000,   -0.27,   -0.07,   -0.0000,    0.13
};

void setup() {
  Serial.begin(115200);

  BOPShield.begin();
  delay(1000);
  BOPShield.calibration();

  Matrix<2, 1> XY = BOPShield.sensorRead();
  x = XY(0);
  y = XY(1);

  xPrev = x;
  yPrev = y;

  Serial.println("x, y, rX, rY, dx, dy, intX, intY, uX, uY");
}

void loop() {

  Matrix<2, 1> XY = BOPShield.sensorRead();

  x = XY(0);
  y = XY(1);
  BLA :: Matrix <2 ,1 > XYsetpoint = BOPShield.oval(analogRead(_P)) ;
    rX = XYsetpoint(0);
    rY = XYsetpoint(1);
 
  dx = (x - xPrev) / Ts;
  dy = (y - yPrev) / Ts;

  float eX = rX - x;
  float eY = rY - y;

  intX = intX + Ts * eX;
  intY = intY + Ts * eY;

  intX = constrain(intX, -100.0, 100.0);
  intY = constrain(intY, -100.0, 100.0);

  
  Matrix<6, 1> Xa = {
    x - rX,
    dx,
    y - rY,
    dy,
    intX,
    intY
  };

 
  Matrix<2, 1> U = K * Xa;

  uX = U(0);
  uY = U(1);

  uX = constrain(uX, -10.0, 10.0);
  uY = constrain(uY, -10.0, 10.0);

  BOPShield.actuatorWrite(uX, uY);

  xPrev = x;
  yPrev = y;

  Serial.print(x);       Serial.print(" ");
  Serial.print(y);       Serial.print(" ");
  Serial.print(rX);      Serial.print(" ");
  Serial.print(rY);      Serial.print(", ");
  Serial.print(dx);      Serial.print(", ");
  Serial.print(dy);      Serial.print(", ");
  Serial.print(intX);    Serial.print(", ");
  Serial.print(intY);    Serial.print(", ");
  Serial.print(uX);      Serial.print(", ");
  Serial.println(uY);

  delay(Ts_ms);
}