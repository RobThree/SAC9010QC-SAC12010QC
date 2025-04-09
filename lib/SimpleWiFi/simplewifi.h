#ifndef SIMPLEWIFI_H
#define SIMPLEWIFI_H

#include "../Logger/logger.h"
#include <WiFiManager.h>

class SimpleWiFi {
  public:
    SimpleWiFi(Logger &log) : _logger(log) {}

    void begin(unsigned long portalTimeout, unsigned long wifiConnectTimeout, unsigned long wifiConnectRetries,
               const char *apName, const char *apPassword = (const char *)__null);
    void ensureConnected();
    String localIP();

  private:
    Logger &_logger; // Reference to the logger
    WiFiManager _wifiManager;
};

#endif // SIMPLEWIFI_H