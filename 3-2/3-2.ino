const int ledPin = 3;      // 老師指定 D3
const int buttonPin = 6;   // 你的按鈕腳位

int state = 0;             // 0~3：0=恆亮(初始),1=慢閃,2=中閃,3=快閃
bool lastButton = HIGH;

unsigned long previousMillis = 0;
bool ledOn = true;         // 因為初始恆亮

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);  // 按鈕只接 D6 & GND

  // 初始狀態：恆亮
  digitalWrite(ledPin, HIGH);
}

void loop() {
  // ---------- 按鈕偵測 ----------
  bool currentButton = digitalRead(buttonPin);

  // 偵測「剛按下」(HIGH -> LOW)
  if (lastButton == HIGH && currentButton == LOW) {
    state = (state + 1) % 4;     // 0→1→2→3→0
    previousMillis = millis();   // 切狀態時重置計時

    // 切狀態時先把 LED 狀態整理好，避免看起來怪跳
    if (state == 0) {
      ledOn = true;
      digitalWrite(ledPin, HIGH); // 回到恆亮
    } else {
      ledOn = false;
      digitalWrite(ledPin, LOW);  // 進入閃爍先從熄滅開始
    }
  }
  lastButton = currentButton;

  // ---------- LED 狀態 ----------
  unsigned long now = millis();

  if (state == 0) {
    // 恆亮（什麼都不用做）
    return;
  }
  else if (state == 1) {
    // 慢閃：1 秒
    blink(1000, now);
  }
  else if (state == 2) {
    // 不快不慢：0.5 秒
    blink(500, now);
  }
  else if (state == 3) {
    // 快閃：0.2 秒
    blink(200, now);
  }
}

void blink(unsigned long interval, unsigned long now) {
  if (now - previousMillis >= interval) {
    previousMillis = now;
    ledOn = !ledOn;
    digitalWrite(ledPin, ledOn ? HIGH : LOW);
  }
}
