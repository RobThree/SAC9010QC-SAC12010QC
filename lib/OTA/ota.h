#ifndef OTA_H
#define OTA_H

#include "../Logger/logger.h"
#include <ArduinoOTA.h>

class OTA {
  public:
    OTA(Logger &log) : _logger(log) {};
    void begin(const char *const hostname, const char *const password);
    void handle();

  private:
    Logger &_logger; // Reference to the logger
};

#endif // OTA_H
