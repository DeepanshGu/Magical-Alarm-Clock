#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

#define TFT_SCLK 10
#define TFT_MOSI 11
#define TFT_RST  9
#define TFT_DC   5
#define TFT_CS   6
#define TFT_BL   7

// --- FILL THESE IN with your actual GPIO numbers ---
#define BTN_MODE  4   // cycles through modes
#define BTN_INC   3   // increases the value being set / (+)
#define BTN_DEC   2   // decreases the value being set / (-)
#define BTN_ALARM 1   // toggles alarm on/off, or silences a ringing alarm
#define BUZZER_PIN 8  // your buzzer's signal pin
// ----------------------------------------------------

class Custom_ST7789 : public Adafruit_ST7789 {
  public:
    Custom_ST7789(int8_t cs, int8_t dc, int8_t mosi, int8_t sclk, int8_t rst)
      : Adafruit_ST7789(cs, dc, mosi, sclk, rst) {}
    void setOffsets(int8_t col, int8_t row) {
      setColRowStart(col, row);
    }
};

Custom_ST7789 tft = Custom_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

// --- Clock state ---
int hours = 12;
int minutes = 0;
int seconds = 0;
unsigned long lastSecondTick = 0;

// --- Alarm state ---
int alarmHour = 7;
int alarmMinute = 0;
bool alarmEnabled = false;
bool alarmRinging = false;

// --- Modes ---
enum Mode { NORMAL, SET_HOUR, SET_MINUTE, SET_ALARM_HOUR, SET_ALARM_MINUTE };
Mode currentMode = NORMAL;

// --- Button edge-detection state ---
bool lastModeState  = HIGH;
bool lastIncState   = HIGH;
bool lastDecState   = HIGH;
bool lastAlarmState = HIGH;
  
void setup() {
Serial.begin(115200);

  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, LOW);   // turns backlight ON

  pinMode(BTN_MODE, INPUT_PULLUP);
  pinMode(BTN_INC, INPUT_PULLUP);
  pinMode(BTN_DEC, INPUT_PULLUP);
  pinMode(BTN_ALARM, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  tft.init(76, 284);
  tft.setOffsets(82, 18);
  tft.invertDisplay(false);
  tft.setRotation(1);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  Serial.println("TFT Initialized!");

  lastSecondTick = millis();
}

void loop() {
// --- Advance the clock, only while not setting something ---
  if (currentMode == NORMAL && millis() - lastSecondTick >= 1000) {
    lastSecondTick = millis();
    seconds++;
    if (seconds >= 60) { seconds = 0; minutes++; }
    if (minutes >= 60) { minutes = 0; hours++; }
    if (hours >= 24) { hours = 0; }

    // Check if it's time to ring
    if (alarmEnabled && !alarmRinging && hours == alarmHour && minutes == alarmMinute && seconds == 0) {
      alarmRinging = true;
    }
  }

  // --- Ring the buzzer while alarm is active ---
  if (alarmRinging) {
    digitalWrite(BUZZER_PIN, (millis() / 300) % 2); // simple on/off beep pattern
  } else {
    digitalWrite(BUZZER_PIN, LOW);
  }

  // --- MODE button: cycle through modes ---
  bool modeState = digitalRead(BTN_MODE);
  if (modeState == LOW && lastModeState == HIGH) {
    switch (currentMode) {
      case NORMAL:          currentMode = SET_HOUR; break;
      case SET_HOUR:        currentMode = SET_MINUTE; break;
      case SET_MINUTE:      currentMode = SET_ALARM_HOUR; break;
      case SET_ALARM_HOUR:  currentMode = SET_ALARM_MINUTE; break;
      case SET_ALARM_MINUTE:currentMode = NORMAL; break;
    }
    delay(150); // debounce
  }
  lastModeState = modeState;

  // --- INC (+) button ---
  bool incState = digitalRead(BTN_INC);
  if (incState == LOW && lastIncState == HIGH) {
    if (currentMode == SET_HOUR)          hours = (hours + 1) % 24;
    else if (currentMode == SET_MINUTE)   { minutes = (minutes + 1) % 60; seconds = 0; }
    else if (currentMode == SET_ALARM_HOUR)   alarmHour = (alarmHour + 1) % 24;
    else if (currentMode == SET_ALARM_MINUTE) alarmMinute = (alarmMinute + 1) % 60;
    delay(150);
  }
  lastIncState = incState;

  // --- DEC (-) button ---
  bool decState = digitalRead(BTN_DEC);
  if (decState == LOW && lastDecState == HIGH) {
    if (currentMode == SET_HOUR)          hours = (hours + 23) % 24;
    else if (currentMode == SET_MINUTE)   { minutes = (minutes + 59) % 60; seconds = 0; }
    else if (currentMode == SET_ALARM_HOUR)   alarmHour = (alarmHour + 23) % 24;
    else if (currentMode == SET_ALARM_MINUTE) alarmMinute = (alarmMinute + 59) % 60;
    delay(150);
  }
  lastDecState = decState;

  // --- ALARM button: silence if ringing, else toggle on/off ---
  bool alarmState = digitalRead(BTN_ALARM);
  if (alarmState == LOW && lastAlarmState == HIGH) {
    if (alarmRinging) {
      alarmRinging = false; // silence it
    } else {
      alarmEnabled = !alarmEnabled; // toggle armed/disarmed
    }
    delay(150);
  }
  lastAlarmState = alarmState;

  // --- Draw the screen ---
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 0);
  tft.setTextSize(4);

  char timeStr[9];
  sprintf(timeStr, "%02d:%02d:%02d", hours, minutes, seconds);
  tft.print(timeStr);

  tft.setTextSize(2);
  tft.setCursor(0, 45);

  switch (currentMode) {
    case SET_HOUR:         tft.print("SET HOUR"); break;
    case SET_MINUTE:       tft.print("SET MIN"); break;
    case SET_ALARM_HOUR:   tft.print("ALARM HOUR"); break;
    case SET_ALARM_MINUTE: tft.print("ALARM MIN"); break;
    default: break;
  }

  tft.setCursor(0, 62);
  char alarmStr[20];
  sprintf(alarmStr, "AL %02d:%02d %s", alarmHour, alarmMinute, alarmEnabled ? "ON" : "OFF");
  tft.print(alarmStr);

  if (alarmRinging) {
    tft.setCursor(150, 45);
    tft.print("RING!");
  }

  delay(80);

}
