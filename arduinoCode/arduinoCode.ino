#define ONLINE 0x02
#define RECV 0x03 // recieving
#define SEND 0x04 
#define CLK 0x05 // clock
#define ERECV 0x06 // enable recieving
#define ESEND 0x07 // enable sending

//Keeps track of how many bits into the byte we are currently at
int currentBitOfByte = 0;
int currentByte[8];
int charInt = 0;

//char inputMessage[]; // keeps track of the characters translated from bytes (what size should it be??)

char charset[] = {
  'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 
  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 
  '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
  '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/', ':', ';', '<', '=', '>', '?', '@', '[', '\\', ']', '^', '_', 
  '`', '{', '|', '}', '~',
  ' '
};
//Used to keep track of the intervals recieved from the clock
int clock;

//setup Serial/All pins
void setup() {
  Serial.begin(9600);
  pinMode(CLK, INPUT);
  pinMode(RECV, INPUT);
  pinMode(ESEND,OUTPUT);
}

void translateIntToChar() {
  //charset[charInt]
}

// you'll never guess what this does
void translateByteToInt() {
  int translateValue = 0;
  if (currentByte[7] == 1){
    translateValue = translateValue + 1;
  }
  if (currentByte[6] == 1){
    translateValue = translateValue + 2;
  }
  if (currentByte[5] == 1){
    translateValue = translateValue + 4;
  }
  if (currentByte[4] == 1){
    translateValue = translateValue + 8;
  }
  if (currentByte[3] == 1){
    translateValue = translateValue + 16;
  }
  if (currentByte[2] == 1){
    translateValue = translateValue + 32;
  }
  if (currentByte[1] == 1){
    translateValue = translateValue + 64;
  }
  if (currentByte[0] == 1){
    translateValue = translateValue + 128;
  }
  charInt = translateValue;
}

//Create local value variable and put a bit from the recieve pin in it, put that bit into the current bit of the byte we're on,
//and once we hit the end of the byte, call translateByteToInt and TranslateIntToChar, then reset the current bit.
void readBits() {
  int value;
  value = digitalRead(RECV);
  currentByte[currentBitOfByte] = value;
  currentBitOfByte++;
  if (currentBitOfByte == 8) {
    translateByteToInt();
    translateIntToChar();
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