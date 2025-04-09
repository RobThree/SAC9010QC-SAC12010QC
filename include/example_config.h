// This file will be ignored by git

#ifndef CONFIG_H
#define CONFIG_H

// #define MYHOME // This is VERY specific to MY home setup, DO NOT UNCOMMENT

#define IRLED D2

#ifdef MYHOME
#define TRIGGERPIN D7
#define ECHOPIN D8
#endif
#define IRLED D2

#define DEVICENAME "AC Remote Control"
#define OTAPASSWORD "YOURSECRETHERE"

#define PORTALTIMEOUT 90
#define WIFICONNECTTIMEOUT 10
#define WIFICONNECTRETRIES 255

#define HTTP_PORT 80
#define SERIAL_BAUDRATE 115200
#define UPDATEINTERVAL 5000

#endif