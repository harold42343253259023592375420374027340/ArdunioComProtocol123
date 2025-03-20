
#define ONLINE 0x02
#define RECV 0x03
#define SEND 0x04
#define CLK 0x05

int dataindex;
int data[] = {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
class Clock {

    public:
      void toggle(int time) {
        delay(time);
        digitalWrite(CLK, 0);
        delay(time);
        digitalWrite(CLK, 1);
        digitalWrite(SEND, data[dataindex]);
        dataindex++;
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
