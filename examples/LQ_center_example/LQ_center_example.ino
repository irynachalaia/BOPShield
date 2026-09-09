/*
  BOPShield LQI centre point control.
*/
#include <SamplingServo.h>
#include <BOP_Shield.h>
#include <BasicLinearAlgebra.h>

using namespace BLA;

const float Ts_ms = 50.0;   // sampling period in milliseconds
const float Ts = 0.05;      // sampling period in seconds

// Reference position
float rX = 51.0;
float rY = 30.0;

// Measured position
float x = 0.0;
float y = 0.0;

// Previous measured position
float xPrev = 0.0;
float yPrev = 0.0;

// Estimated velocities from measured position
float dx = 0.0;
float dy = 0.0;

// Integral states
float intX = 0.0;
float intY = 0.0;

// Control signals
float uX = 0.0;
float uY = 0.0;

// LQI gain matrix
Matrix<2, 6> K = {
  -0.43,   -0.11,    0.0000,   -0.0000,    0.2,   -0.0000,
   -0.0000,   -0.0000,   -0.27,   -0.07,   -0.0000,    0.13
};

void setup() {
  Serial.begin(115200);
  BOPShield.begin();
  delay(1000);
  BOPShield.calibration();

  // First sensor reading for initialization
  Matrix<2, 1> XY = BOPShield.sensorRead();
  x = XY(0);
  y = XY(1);

  xPrev = x;
  yPrev = y;

  Serial.println("x, y, rX, rY, dx, dy, intX, intY, uX, uY");
}

void loop() {

  // Read measured position
  Matrix<2, 1> XY = BOPShield.sensorRead();

  x = XY(0);
  y = XY(1);

  // Calculate velocities from measured position
  dx = (x - xPrev) / Ts;
  dy = (y - yPrev) / Ts;

  // Position errors
  float eX = rX - x;
  float eY = rY - y;

  // Integral states
  intX = intX + Ts * eX;
  intY = intY + Ts * eY;

  // Anti-windup limitation
  intX = constrain(intX, -100.0, 100.0);
  intY = constrain(intY, -100.0, 100.0);

  // Augmented state vector for LQI
  Matrix<6, 1> Xa = {
    x - rX,
    dx,
    y - rY,
    dy,
    intX,
    intY
  };

  // LQI control law
  Matrix<2, 1> U = K * Xa;

  uX = U(0);
  uY = U(1);

  // Saturation of control signals
  uX = constrain(uX, -10.0, 10.0);
  uY = constrain(uY, -10.0, 10.0);

  // Send control to servos
  BOPShield.actuatorWrite(uX, uY);

  // Save previous position
  xPrev = x;
  yPrev = y;

  Serial.print(x);       Serial.print(" ");
  Serial.print(y);       Serial.print(" ");
  Serial.print(rX);      Serial.print(" ");
  Serial.print(rY);      Serial.print(", ");
  Serial.print(dx);  Serial.print(", ");
  Serial.print(dy);  Serial.print(", ");
  Serial.print(intX);    Serial.print(", ");
  Serial.print(intY);    Serial.print(", ");
  Serial.print(uX);      Serial.print(", ");
  Serial.println(uY);

  delay(Ts_ms);
}