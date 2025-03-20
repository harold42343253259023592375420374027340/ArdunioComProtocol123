#define ONLINE 0x02
#define RECV 0x03
#define SEND 0x04
#define CLK 0x05
#define ERECV 0x06

int currentBitOfByte = 0;
int currentByte[8];
int clock;

void setup() {
  Serial.begin(9600);
  pinMode(CLK, INPUT);
  pinMode(RECV, INPUT);
}

void readBits() {
  int value;
  value = digitalRead(RECV);
  currentByte[currentBitOfByte] = value;
  currentBitOfByte++;
  if (currentBitOfByte == 8) {
    currentBitOfByte = 0;
  }
  Serial.println(value);
}

void CheckClock() {
  clock = digitalRead(CLK);

  if (clock == 1) {
    readBits();
    delay(1000);

  }
}

void loop() {
  CheckClock();
}