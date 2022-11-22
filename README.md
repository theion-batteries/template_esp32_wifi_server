# template_esp32_wifi_server
this repo contains a simple template how to use a wifi for esp32 and create a server that listen to incoming communication with built in command parser.

# platformio.ini
; PlatformIO Project Configuration File
;   Build options: build flags, source filter
;   Upload options: custom upload port, speed and extra flags
;   Library options: dependencies, extra library storages
;   Advanced options: extra scripting
; Please visit documentation for the other options and examples
; https://docs.platformio.org/page/projectconf.html

[env:wemos_d1_mini32]
platform = espressif32
board = wemos_d1_mini32
;framework = espidf
framework = arduino
build_flags = -std=gnu++17
build_unflags = -std=gnu++11
monitor_speed = 115200