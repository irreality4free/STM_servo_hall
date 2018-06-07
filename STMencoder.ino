#define GET_A gpio_read_bit(GPIOB, 8)
#define GET_B gpio_read_bit(GPIOB, 7)
#define GET_Z gpio_read_bit(GPIOB, 6)

int pinA = PB8;
int pinB = PB7;
int pinZ = PB6;
volatile int bLED = LOW;
int period = 1000;
int latch_count = 0;

int count = 0;

void interruptFunctionA() {
  int A=GET_A;
  int B=GET_B;
  A==B ? count-- : count++;
  }

void interruptFunctionB() {
  int A=GET_A;
  int B=GET_B;
  A==B ? count++ : count--;
  }
//
void interruptFunctionZ() {
latch_count = count;
//detachInterrupt(pinZ);
  }

void setup() {
   Serial.begin(9600);
   Serial.println('start');
   pinMode(pinA, INPUT);
   pinMode(pinB, INPUT);
   pinMode(pinZ, INPUT);
   attachInterrupt(pinA, interruptFunctionA, CHANGE);
   attachInterrupt(pinB, interruptFunctionB, CHANGE);
   attachInterrupt(pinZ, interruptFunctionZ, CHANGE);
   
}

void loop() {
  delay(500);
  
  Serial.print("count: ");
  Serial.println(count);
  Serial.print("Latch-count: ");
  Serial.print(latch_count%10000);
  Serial.print("    ----    ");
  Serial.print(latch_count);
  Serial.println();
  Serial.print("A - ");
  Serial.println(GET_A);
  Serial.print("B - ");
  Serial.println(GET_B);
  Serial.print("Z - ");
  Serial.println(GET_Z);
  Serial.println();
  
}
