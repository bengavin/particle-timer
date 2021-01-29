/*
 * Project particle-timer
 * Description: Particle based Kitchen timer
 * Author: Ben Gavin
 * Date: 2021-01-25
 */

#include <Wire.h>
#include <gfxfont.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Debounce.h>
#include "display-helpers.h"
#include "timer-screen.h"
#include "timer-manager.h"
#include "home-screen.h"

// Turn off cloud capabilities for local testing
SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);

Adafruit_SH110X display = Adafruit_SH110X(64, 128, &Wire);

// OLED FeatherWing buttons map to different pins depending on board:
#if defined(ESP8266)
#define BUTTON_A 0
#define BUTTON_B 16
#define BUTTON_C 2
#elif defined(ESP32)
#define BUTTON_A 15
#define BUTTON_B 32
#define BUTTON_C 14
#elif defined(ARDUINO_STM32_FEATHER)
#define BUTTON_A PA15
#define BUTTON_B PC7
#define BUTTON_C PC5
#elif defined(TEENSYDUINO)
#define BUTTON_A 4
#define BUTTON_B 3
#define BUTTON_C 8
#elif defined(ARDUINO_NRF52832_FEATHER)
#define BUTTON_A 31
#define BUTTON_B 30
#define BUTTON_C 27
#elif defined(PLATFORM_ID) // Particle devices define this
#define BUTTON_A D4
#define BUTTON_B D3
#define BUTTON_C D2
#else // 32u4, M0, M4, nrf52840 and 328p
#define BUTTON_A 9
#define BUTTON_B 6
#define BUTTON_C 5
#endif

// Timer Buttons
Debounce hrButton = Debounce();
Debounce minButton = Debounce();
Debounce multiButton = Debounce();

// A button is considered 'held' if it's pressed for more than 3 seconds
#define BUTTON_HELD_TIMEOUT 3 * 1000

// static uint8_t _hrs = 0;
// static uint8_t _mins = 0;
// static uint8_t _textSize = 1;
// static uint8_t _font = 0;

TimerScreen *currentScreen;
TimerManager timerManager = TimerManager(System.millis());

// setup() runs once, when the device is first turned on.
void setup()
{
  // Put initialization like pinMode and begin functions here.
  Serial.begin(115200);

  Serial.println("Particle Kitchen Timer");
  display.begin(0x3C, true); // Address 0x3C default

  Serial.println("OLED begun");

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(1000);

  // Clear the buffer.
  display.clearDisplay();
  display.display();

  display.setRotation(1);

  pinMode(BUTTON_A, INPUT_PULLUP);
  hrButton.attach(BUTTON_A);
  pinMode(BUTTON_B, INPUT);
  minButton.attach(BUTTON_B);
  pinMode(BUTTON_C, INPUT_PULLUP);
  multiButton.attach(BUTTON_C);

  // Setup a test timer for now...
  TimerInstance *timerTest = timerManager.add_timer();
  //timerTest->add_hours(1);
  timerTest->add_minutes(2);
  timerTest->start(System.millis());

  currentScreen = new HomeScreen(&timerManager);
}

static void updateButtons(void)
{
  hrButton.update();
  minButton.update();
  multiButton.update();
}

// loop() runs over and over again, as quickly as it can execute.
void loop()
{
  timerManager.update(System.millis());

  updateButtons();

  if (hrButton.fell() && hrButton.read() == LOW)
  {
    currentScreen->button_pressed(BUTTON_1);
  }

  if (minButton.fell() && minButton.read() == LOW)
  {
    currentScreen->button_pressed(BUTTON_2);
  }

  // For now, just reset
  if (multiButton.fell() && multiButton.read() == LOW)
  {
    currentScreen->button_pressed(BUTTON_3);
  }

  display.clearDisplay();
  currentScreen->render(&display);
  display.display();

  yield();
}