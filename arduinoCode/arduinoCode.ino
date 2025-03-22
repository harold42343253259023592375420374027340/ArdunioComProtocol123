#define ONLINE 0x02
#define RECV 0x03 // recieving
#define SEND 0x04 
#define CLK 0x05 // clock
#define ERECV 0x06 // enable recieving
#define ESEND 0x07 // enable sending

//Keeps track of how many bits into the byte we are currently at
int currentBitOfByte = 0;

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
  pinMode(ERECV,INPUT);
  pinMode(ONLINE,OUTPUT);
}

char translateIntToChar(int charInt) {
  return charset[charInt];
}

// you'll never guess what this does
/* 
                      Me when i saw your old code
⡠⠒⢦⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡼⠉⠙⢦
⡇⠀⡔⠛⠲⡄⠀⠀⠀⢀⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠹⣤⠒⠚⢧⡀
⠱⣼⠀⢀⡠⠧⠤⣀⢠⠃⠀⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⠀⠀⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ ⣀⣀⡀⠀⠀⣿⣆⠀⠀⡇
⠀⢹⢀⡎⠀⠀⠀⢈⠏⠀⢠⠚⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⡾⠟⠛⠛⠛⠻⣶⣶⢤⣀⠀⠀⠀⠀⠀⠀⠀⣯⠀⠀⢱⠀⢠⢧⠛⠒⢦⡇
⠀⠈⣾⠀⠀⡔⠋⠁⠀⢀⡏⠀⠀⠀⠀⠀⠀⠀⡠⠞⠛⣋⣀⣀⠀⠀⠀⣤⣤⣀⠀⠈⠙⢦⡀⠀⠀⠀⠀⠈⢣⠀⢸⢀⠞⠸⣄⠀⠀⢱
⠀⠀⠘⡆⠀⠃⠀⠀⠀⢸⡄⠀⠀⠀⠀⠀⣠⠎⣠⠴⣿⣿⠟⠀⠀⠀⠀⠘⣿⣿⠑⢦⡀⠀⠙⢦⡀⠀⠀⠀⢸⠀⠀⡁⠀⠀⡜⠇⠀⢸
⠀⠀⠀⢣⠀⠀⠀⠙⢄⢀⠇⠀⠀⠀⠀⡼⠁ ⠈⠀ ⠈⣁⠴⠚⠉⠉⠉⠙⠢⢄⠀⠀⠀⠀⠀⠈⢣⡀⠀⠀⢸⢀⡏⠁⠀⠈⠀⠀⡰⠃
⠀⠀⠀⠀⠣⡀⠀⠀⢸⠋⠀⠀⠀⠀⣸⠁⠀⠀⠀⢀⡞⠁⠀⠀⠀⠀⠀⠀⠀⠀ ⠱⣄⠀⠀⠀⠀⠀ ⢧⠀⠀⠀⠻⣇⠀⠀⢀⡴⠊
⠀⠀⠀⠀⠀⠈⠉⠉⠁⠀⠀⠀⠀⢠⡏⠀⠀⠀⢀⠎⠀⢀⣾⣿⣆⠀⣰⣿⣦⠀⠀⠘⣆⠀⠀⠀⠀⢸⡇⠀⠀⠀⠈⠉⠉⠉
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠁⠀⠀⠀⡎⠀⠀⣾⣿⣿⣿⣶⣿⣿⣿⡄⠀⠀⠘⡆⠀⠀⠀⠀⡇
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⠀⠀⠸⠁⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣧⠀⠀⠀⢰⡀⠀⠀⠀⡇
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡄⠀⢀⡇⠀⠀⠀⢿⠟⠋⠁⠀⠈⠙⠻⡏⠀⠀⠀⠀⣇⠀⠀⠀⡇
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢷⠀⢸⠀⠀⠀⡴⠃⠀⠀⠀⠀⠀⠀⠀⠘⢢⠀⠀⠀⢸⡀⠀⣸⠃
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⡇⢸⠀⢀⡜⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠳⣄⠀⢸⠇⣶
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢧⠈⠉⡡⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ ⠓⠊⠀⣿
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠳⠚⢧⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢈⡵⠦⠤⠃
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠛⠶⢤⣄⣀⣀⣀⣀⣀⡤⠴⠚⠁
    -- Finn H 
    (Harold)
*/
int translateByteToInt(int *currentByte) {
    int translateValue = 0;

    // Loop through each bit, from the most significant bit to the least significant bit
    for (int i = 0; i < 8; ++i) {
        translateValue |= (currentByte[i] << (7 - i));
    }

    return translateValue;
}

//Create local value variable and put a bit from the recieve pin in it, put that bit into the current bit of the byte we're on,
//and once we hit the end of the byte, call translateByteToInt and TranslateIntToChar, then reset the current bit.
void readBits() {
  int currentByte[8];
  int value;
  int temp;
  value = digitalRead(RECV);
  //Serial.println(value);
  currentByte[currentBitOfByte] = value;
  currentBitOfByte++;
  if (currentBitOfByte == 8) {
    temp = translateByteToInt(currentByte);
    if (temp == 255) {
      Serial.println();
    }
    Serial.print(translateIntToChar(temp));
    currentBitOfByte = 0;
  }
}

//If the clock value from the server is 1, read a bit.
void CheckClock() {
  clock = digitalRead(CLK);
      digitalWrite(ONLINE,HIGH);

  if (clock == 1) {
    if (digitalRead(ERECV) == 1) {
      readBits();
    }
    delay(500);

  }
}

//loop
void loop() {
  CheckClock();
}