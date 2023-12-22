#pragma once

#include <FastLED.h>

// RX Communication -------------------------------
#define FC_SERIAL_RX_PIN 5
#define FC_SERIAL_TX_PIN 19
// software serial on esp8266 is limited to 57600 baud for stable communication
#define FC_BAUD 57600

// LOGGING ---------------------------------------
#define LOGGING_ENABLE
#define LOGGING_BAUD 57600

// #define USE_SOFTWARE_SERIAL_FOR_LOGGING
// #define LOGGING_SERIAL_TX_PIN 2
// #define LOGGING_SERIAL_RX_PIN 10

// LED -------------------------------------------
#define TAIL_NUM_LEDS 42
#define TAIL_LED_PIN 2
#define TAIL_LED_TYPE WS2812
#define TAIL_LED_COLOR_ORDER GRB
#define TAIL_LED_START_OFFSET 0
#define TAIL_LED_IS_INVERTED false

#define LEFT_NUM_LEDS 42
#define LEFT_LED_PIN 4
#define LEFT_LED_TYPE WS2812
#define LEFT_LED_COLOR_ORDER GRB
#define LEFT_LED_START_OFFSET 0
#define LEFT_LED_IS_INVERTED false

#define RIGHT_NUM_LEDS 42
#define RIGHT_LED_PIN 3
#define RIGHT_LED_TYPE WS2812
#define RIGHT_LED_COLOR_ORDER GRB
#define RIGHT_LED_START_OFFSET 0
#define RIGHT_LED_IS_INVERTED false

// https://github.com/FastLED/FastLED/wiki/Pixel-reference#setting-hsv-colors-
#define BOOT_ANIMATION_DURATION_MS 3000
#define LED_FPS 240

// WiFi OTA --------------------------------------

// uncomment and set these if you want to connect to your home wifi
// #define WIFI_SSID "ssid"
// #define WIFI_PASSWORD "password"

// how many times shall we try to connect to the wifi before we create a hotspot? (each attempt is 200ms)
#define WIFI_MAX_CONNECT_ATTEMPTS 300 // 300 * 200ms = 1 minute
#define WIFI_HOTSPOT_SSID "Drone Visualizer"
#define WIFI_HOTSPOT_PASSWORD "blinkyblink"
// wifi will automatically shut down after 3 minutes of waiting for OTA connections
#define WIFI_HOTSPOT_TIMEOUT 180000 // 3 minutes in ms (3 * 60 * 1000)


// MSP -------------------------------------------

#define FC_RX_PIN 6
#define FC_TX_PIN 4

#define FC_LED_PINIO_PIN 5

#define MSP_BAUD_RATE 115200
#define MSP_ARM_CHANNEL 5
#define MSP_LED_CHANNEL 7