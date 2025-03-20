#define ONLINE 2
#define RECV   3
#define SEND   4
#define CLK    5
#define ERECV    6


int dataindex;
int data[] = {};

class Clock {

    public:
      void writeData() {
        digitalWrite(SEND, data[dataindex]);
        dataindex++;
      }
      void toggle(int time) {
        delay(time);
        digitalWrite(CLK, 0);
        if (digitalRead(ONLINE) == 1) {
             writeData();
        }
        delay(time);
        digitalWrite(CLK, 1);
      }
};
Clock clock;
int addresses[256];

void setup() {
  pinMode(CLK, OUTPUT);
  pinMode(SEND, OUTPUT);
  pinMode(ERECV, OUTPUT);

}
void loop() {
  clock.toggle(1000);
}
