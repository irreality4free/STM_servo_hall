#define GET_A gpio_read_bit(GPIOB, 8)
#define GET_B gpio_read_bit(GPIOB, 7)
#define GET_Z gpio_read_bit(GPIOB, 6)

int pinA = PB8;
int pinB = PB7;
int pinZ = PB6;
volatile int bLED = LOW;
int period = 1000;
int latch_count = 0;
int prevA;
int calling;

volatile long count = 0;

void interruptFunctionA() {
  int A = GET_A;
  int B = GET_B;
//prevA==A ? calling=B : calling=A;
// if (calling == A){
//   A==B ? count-- : count++;
// }
// else{
//   A==B ? count++ : count--;
// }
// prevA=A;
  A > 0 == B > 0 ? count-- : count++;
}

void interruptFunctionB() {
  int A = GET_A;
  int B = GET_B;
  A > 0 == B > 0 ? count++ : count--;
}

void interruptFunctionZ() {
  latch_count = count;
}

void setup() {
  Serial.begin(9600);
  Serial.println("start");
  pinMode(pinA, INPUT);
  pinMode(pinB, INPUT);
  pinMode(pinZ, INPUT);
  attachInterrupt(pinA, interruptFunctionA, CHANGE);
  attachInterrupt(pinB, interruptFunctionB, CHANGE);
  attachInterrupt(pinZ, interruptFunctionZ, RISING);

}

void debug() {
  Serial.print("count: ");
  Serial.println(count);
  Serial.print("Latch-count: ");
  Serial.print(latch_count % 10000);
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

void loop() {
  long t = micros();
  long p = count;
  delay(400);
  debug();
  
  Serial.println (float(p-count)/10000*1000000*60/(micros()-t) );
//  long t = micros();
//  long i = 0;
//  for (long j = 0; j < 10000; j++)
//  {
//
//    i+= sqrt(j);
//  }
//  Serial.println("");
//  i  =10;
//  t = micros()-t;
//  Serial.println("END OF LOOP ");
//  Serial.println(t);
}
