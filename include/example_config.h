// COPY THIS FILE AND RENAME IT TO "config.h" AND ENTER ALL YOUR CONFIGURATION DATA BELOW

#ifndef CONFIG_H
#define CONFIG_H

#define DEVICENAME          "devicename-here"
#define OTAPASSWORD         "my_ota_secret"
#define TEMPERATUREOFFSET   -7.0    // Temperature offset / correction

#define PORTALTIMEOUT       90
#define WIFICONNECTTIMEOUT  10
#define WIFICONNECTRETRIES  255

#define HTTP_PORT           80
#define SERIAL_BAUDRATE     115200
#define UPDATEINTERVAL      2000    // Update interval in milliseconds

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#endif