const int pinA = 2;
const int pinB = 3;
const int sel0 = 4;
const int sel1 = 5;
const int sel2 = 6;

const int resultPin = 9;
const int carryPin = 10;
const int ledOp0 = 11;
const int ledOp1 = 12;
const int ledOp2 = 13;

void setup() {
  pinMode(pinA, INPUT);
  pinMode(pinB, INPUT);
  pinMode(sel0, INPUT);
  pinMode(sel1, INPUT);
  pinMode(sel2, INPUT);

  pinMode(resultPin, OUTPUT);
  pinMode(carryPin, OUTPUT);
  pinMode(ledOp0, OUTPUT);
  pinMode(ledOp1, OUTPUT);
  pinMode(ledOp2, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int A = digitalRead(pinA);
  int B = digitalRead(pinB);

  int s0 = digitalRead(sel0);
  int s1 = digitalRead(sel1);
  int s2 = digitalRead(sel2);
  int selector = (s2 << 2) | (s1 << 1) | s0;

  int result = 0;
  int carry = 0;

  switch (selector) {
    case 0: // Suma
      result = A ^ B;
      carry = A & B;
      break;
    case 1: // Resta
      result = A ^ B;
      carry = (!A & B);
      break;
    case 2: // Multiplicación
      result = A & B;
      carry = 0;
      break;
    case 3: // División
      if (B == 0) {
        result = 0;
        carry = 1;
      } else {
        result = A;
        carry = 0;
      }
      break;
    case 4: // AND
      result = A & B;
      carry = 0;
      break;
    case 5: // XOR
      result = A ^ B;
      carry = 0;
      break;
    case 6: // OR
      result = A | B;
      carry = 0;
      break;
    default:
      result = 0;
      carry = 0;
      break;
  }

  digitalWrite(resultPin, result);
  digitalWrite(carryPin, carry);

  // Indicadores visuales de la operación
  digitalWrite(ledOp0, s0);
  digitalWrite(ledOp1, s1);
  digitalWrite(ledOp2, s2);

  // Para monitoreo por serial
  Serial.print("A: "); Serial.print(A);
  Serial.print(" B: "); Serial.print(B);
  Serial.print(" | Selector: "); Serial.print(selector, BIN);
  Serial.print(" | Resultado: "); Serial.print(result);
  Serial.print(" | Acarreo/Error: "); Serial.println(carry);

  delay(300); // Pequeño delay para estabilizar lectura
}
