#include <Arduino.h>
#include <analogWrite.h>

int value_sensor[16];
//#define tst_bit(y, bit) (y & (1 << bit))
#define AI1 18
#define AI2 19
#define BI1 17
#define BI2 16
#define A1 0
#define A2 1
#define B1 2
#define B2 3

/// Aciona o mux na ordem certa e lê todos os sensores
void Read_Sensors()
{
  for (int i = 0; i < 16; i++)
  {
    if (i % 2)
      digitalWrite(14, HIGH);
    else
      digitalWrite(14, LOW);

    if (i / 2 % 2)
      digitalWrite(27, HIGH);
    else
      digitalWrite(27, LOW);

    if (i / 4 % 2)
      digitalWrite(26, HIGH);
    else
      digitalWrite(26, LOW);

    if (i / 8 % 2)
      digitalWrite(25, HIGH);
    else
      digitalWrite(25, LOW);

    delay(1);
    value_sensor[i] = analogRead(36);
    Serial.print(value_sensor[i]);
    Serial.print(" ");
  }
  Serial.println();
}

/// Transforma os valores de 0 a 1023 em valores binarios de branco e preto
void BinSensorConvert()
{
}

/// Aciona os motores em qualquer sentido
void Motor(signed int velocidade1, signed int velocidade2)
{
  if (abs(velocidade1) < 20)
    velocidade1 = 0;
  if (abs(velocidade2) < 20)
    velocidade2 = 0;

  if (velocidade1 > 0)
  {
    ledcWrite(A1, velocidade1);
    ledcWrite(A2, 0);
  }
  else
  {
    if (velocidade1 == 0)
    {
      ledcWrite(A1, 0);
      ledcWrite(A2, 0);
    }
    else
    {
      ledcWrite(A1, 0);
      ledcWrite(A2, -velocidade1);
    }
  }

  if (velocidade2 > 0)
  {
    ledcWrite(B1, velocidade2);
    ledcWrite(B2, 0);
  }
  else
  {
    if (velocidade2 == 0)
    {
      ledcWrite(B1, 0);
      ledcWrite(B2, 0);
    }
    else
    {
      ledcWrite(B1, 0);
      ledcWrite(B2, -velocidade2);
    }
  }
}

void setup()
{
  pinMode(36, INPUT);
  pinMode(14, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(AI1, OUTPUT);
  digitalWrite(AI1, LOW);
  pinMode(AI2, OUTPUT);
  digitalWrite(AI2, LOW);
  pinMode(BI1, OUTPUT);
  digitalWrite(BI1, LOW);
  pinMode(BI2, OUTPUT);
  digitalWrite(BI2, LOW);

  pinMode(2, OUTPUT);

  ledcSetup(0, 5000, 8);
  ledcAttachPin(AI1, 0);
  ledcSetup(1, 5000, 8);
  ledcAttachPin(AI2, 1);
  ledcSetup(2, 5000, 8);
  ledcAttachPin(BI1, 2);
  ledcSetup(3, 5000, 8);
  ledcAttachPin(BI2, 3);

  Serial.begin(115200);
}

void loop()
{
  Read_Sensors();
  // BinSensorConvert();
  /*
  for (int i = -255; i < 255; i++) {
    //analogWrite(2, i);
    Motor(i, i);
    delay(100);
  }
*/
}