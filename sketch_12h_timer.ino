const int clk_pin1 = 2; // for movement
const int clk_pin2 = 4; // for movement
const int stp_pin  = 5; // for timer end
const int pulse_time = 30;
const int delay_time = 1000 - pulse_time;
const int clk_counter_default = 12; // 12 minutes
int clk_counter = clk_counter_default;
bool isLed = false;
bool isPin1 = false;

void pulse() {
  if (digitalRead(stp_pin)) {
    digitalWrite(LED_BUILTIN, LOW);  // 停止
    clk_counter = clk_counter_default;
    return;
  }
  digitalWrite(LED_BUILTIN, isLed);
  isLed = !isLed;
  if (--clk_counter > 0) {
    return;
  }
  clk_counter = clk_counter_default;
  
  if (isPin1) {
    digitalWrite(clk_pin1, HIGH);
    delay(pulse_time);
    digitalWrite(clk_pin1, LOW);
  } 
  else {
    digitalWrite(clk_pin2, HIGH);
    delay(pulse_time);
    digitalWrite(clk_pin2, LOW);
  }
  isPin1 = !isPin1;
}

void setup() {
  // put your setup code here, to run once:
  digitalWrite(clk_pin1, LOW);
  digitalWrite(clk_pin2, LOW);
  pinMode(clk_pin1, OUTPUT);
  pinMode(clk_pin2, OUTPUT);
  pinMode(stp_pin, INPUT); // 停止確認用
  pinMode(LED_BUILTIN, OUTPUT); // 動作確認用
}

void loop() {
  // put your main code here, to run repeatedly:
  pulse();
  delay(delay_time);
}
