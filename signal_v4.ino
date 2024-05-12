#define S0_2 26
#define S1_2 32
#define S2_2 33
#define S3_2 25
#define EN_2 34
#define SIG_2 19
const int SER = 16;
const int LATCH = 5;
const int CLK = 18;
int LedOut1 = 0, LedOut2 = 0;
bool leds[16];
bool s0, s1, s2, s3;
int Pins[16];

void setup() {
pinMode(SER, OUTPUT);
pinMode(LATCH, OUTPUT);
pinMode(CLK, OUTPUT);

  pinMode(EN_2, OUTPUT);
  pinMode(S0_2, OUTPUT);
  pinMode(S1_2, OUTPUT);
  pinMode(S2_2, OUTPUT); 
  pinMode(S3_2, OUTPUT); 
  pinMode(SIG_2, INPUT_PULLUP);
}

void Shift16Leds()
{
int reg[8] = {128,64,32,16,8,4,2,1};
for (int i = 0; i<=7;i++) 
{
LedOut1 = LedOut1 + (leds[i]*reg[i]);
}
for (int i = 8; i<=15;i++) 
{
LedOut2 = LedOut2 + (leds[i]*reg[i-8]);
}
    digitalWrite(LATCH, LOW);
    shiftOut(SER, CLK, MSBFIRST, LedOut1);
    shiftOut(SER, CLK, MSBFIRST, LedOut2);
    digitalWrite(LATCH, HIGH);
  //  delay(1000);
    LedOut1 = 0;
    LedOut2 = 0;
}
void MUXin()
{
  for (int i=0; i<=15; i++)
  {
  s0 = i%2;
  s1 = i/2%2;
  s2 = i/4%2;
  s3 = i/8%2;
  digitalWrite(EN_2, HIGH);
  digitalWrite(S0_2, s0);
  digitalWrite(S1_2, s1);
  digitalWrite(S2_2, s2);
  digitalWrite(S3_2, s3);
  digitalWrite(EN_2, LOW);
  delay(5);
  Pins[i] = (1-digitalRead(SIG_2))*(i+1);
  leds[i] = 1-digitalRead(SIG_2);
  }
}

void loop() {
  MUXin();
  Shift16Leds();
}
