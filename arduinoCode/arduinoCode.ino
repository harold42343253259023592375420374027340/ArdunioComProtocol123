#define ONLINE 0x02
#define RECV 0x03
#define SEND 0x04
#define CLK 0x05
  int value;
  int clock;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(CLK, INPUT);
  pinMode(RECV, INPUT);
}

void CheckClock() {
  clock = digitalRead(CLK);

  if (clock == 1) {
    value = digitalRead(RECV);
    Serial.println(value);
    delay(1000);

  }
}

void loop() {
  // put your main code here, to run repeatedly:
  CheckClock();
}