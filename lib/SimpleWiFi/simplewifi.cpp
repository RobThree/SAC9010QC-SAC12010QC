#include "simplewifi.h"

void SimpleWiFi::begin(unsigned long portalTimeout, unsigned long wifiConnectTimeout, unsigned long wifiConnectRetries,
                       const char *apName, const char *apPassword) {
    _logger.info("Starting WiFi");
    _wifiManager.setConfigPortalTimeout(portalTimeout);
    _wifiManager.setConnectTimeout(wifiConnectTimeout);
    _wifiManager.setConnectRetries(wifiConnectRetries);
    _wifiManager.setWiFiAutoReconnect(true);
    if (!_wifiManager.autoConnect(apName, apPassword)) {
        _logger.error("Autoconnect failed. Restarting");
        delay(3000);
        ESP.restart();
    }
}

void SimpleWiFi::ensureConnected() {
    if ((WiFi.status() != WL_CONNECTED)) {
        _logger.warn("WiFi not connected, reconnecting");
        WiFi.reconnect();
        unsigned long start = millis();

        while (WiFi.status() != WL_CONNECTED && millis() - start < 10000) {
            delay(100);
        }

        if (WiFi.status() == WL_CONNECTED) {
            _logger.info("WiFi reconnected");
        } else {
            _logger.warn("Failed to reconnect to WiFi. Retrying...");
            delay(1000);
        }
    }
}

String SimpleWiFi::localIP() { return WiFi.localIP().toString(); }