#define ONLINE 2
#define RECV   3
#define SEND   4
#define CLK    5
#define ERECV    6


int dataindex;
int data[] = {'1', '0', '1', '0', '1', '1', '1', '0', '0', '1', '0', '1', '1', '1', '0', '1', '1', '1', '1', '1', '0', '1', '0', '1', '0', '1', '0', '1', '1', '0', '1', '0', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1', '1', '1', '0', '1', '0', '0', '0', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0'};

class Clock {

    public:
      void writeData() {
        digitalWrite(SEND, data[dataindex]);
        dataindex++;
      }
      void toggle(int time) {
        delay(time);
        digitalWrite(CLK, 0);
        writeData();
        delay(time);
        digitalWrite(CLK, 1);
      }
};
Clock clock;

void setup() {
  // put your setup code here, to run once:
  int ips[256];
  pinMode(CLK, OUTPUT);
  pinMode(SEND, OUTPUT);
}
void loop() {
  // put your main code here, to run repeatedly:
  clock.toggle(1000);
}
