#define ONLINE 0x02
#define RECV 0x03
#define SEND 0x04
#define CLK 0x05
#define ERECV 0x06

//Keeps track of how many bits into the byte we are currently at
int currentBitOfByte = 0;
int currentByte[8];

//Used to keep track of the intervals recieved from the clock
int clock;

//setup Serial/All pins
void setup() {
  Serial.begin(9600);
  pinMode(CLK, INPUT);
  pinMode(RECV, INPUT);
}

//Create local value variable and put a bit from the recieve pin in it, put that bit into the current bit of the byte we're on,
//and reset the current bit if we've hit the end. (Its important, I promise)
void readBits() {
  int value;
  value = digitalRead(RECV);
  currentByte[currentBitOfByte] = value;
  currentBitOfByte++;
  if (currentBitOfByte == 7) {
    currentBitOfByte = 0;
  }
  Serial.println(value);
}

//If the clock value from the server is 1, read a bit.
void CheckClock() {
  clock = digitalRead(CLK);

  if (clock == 1) {
    readBits();
    delay(1000);

  }
}

//loop
void loop() {
  CheckClock();
}