#if 1
#define LOG_INIT()      Serial.begin(115200)
#define LOG(s)          Serial.print(s)
#define LOGLN(s)        Serial.println(s)
#else
#define LOG_INIT() 
#define LOG(s)     
#define LOGLN(s)   
#endif


const int clk_pin1 = 2; // for movement
const int clk_pin2 = 4; // for movement
const int stp_pin  = 6; // for timer end
const int pulse_time = 30;
const int delay_time = 1000 - pulse_time;
const int clk_counter_default = 12; // 12 minutes
int clk_counter = clk_counter_default;
unsigned int total_counter = 0;
bool isLed = false;
bool isPin1 = false;
bool isFinished = false;

void pulse() {
  if (digitalRead(stp_pin)) {
    //digitalWrite(LED_BUILTIN, LOW);  // 停止
    //clk_counter = clk_counter_default;
    LOGLN("Stop");
    isFinished = true;
    return;
  }
  total_counter++;
  LOGLN(total_counter);
  digitalWrite(LED_BUILTIN, isLed);
  isLed = !isLed;
  if (--clk_counter > 0) {
    return;
  }
  clk_counter = clk_counter_default;
  LOG("L: ");
  LOG(clk_counter);
  
  if (isPin1) {
    digitalWrite(clk_pin1, HIGH);
    delay(pulse_time);
    digitalWrite(clk_pin1, LOW);
    LOGLN(" >");
  } 
  else {
    digitalWrite(clk_pin2, HIGH);
    delay(pulse_time);
    digitalWrite(clk_pin2, LOW);
    LOGLN(" <");
  }
  isPin1 = !isPin1;
}

void setup() {
  // put your setup code here, to run once:
  LOG_INIT();

  digitalWrite(clk_pin1, LOW);
  digitalWrite(clk_pin2, LOW);
  pinMode(clk_pin1, OUTPUT);
  pinMode(clk_pin2, OUTPUT);
  pinMode(stp_pin, INPUT_PULLUP); // 停止確認用
  //digitalWrite(stp_pin, HIGH);  // pull up by 20k
  pinMode(LED_BUILTIN, OUTPUT); // 動作確認用
}

void loop() {
  // put your main code here, to run repeatedly:
  pulse();
  if (isFinished) {
    for (;;) {
      // 高速点滅
      digitalWrite(LED_BUILTIN, HIGH);
      delay(100);
      digitalWrite(LED_BUILTIN, LOW);
      delay(100);
      if (!digitalRead(stp_pin)) {
        break;
      }
    }
    total_counter = 0;
    clk_counter = clk_counter_default;
    isFinished = false;
  }
  delay(delay_time);

  {
    int in = digitalRead(stp_pin);
    LOG(" => ");
    LOGLN(in);
  }
}
