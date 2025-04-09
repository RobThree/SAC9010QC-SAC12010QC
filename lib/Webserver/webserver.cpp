#include "webserver.h"

void Webserver::useDefaultEndpoints() {
    _server.on("/reset", HTTP_PUT, [this]() {
        sendText("reset");
        _logger.warn("Restarting");
        ESP.restart();
    });
    _server.on("/mac", HTTP_GET, [this]() { sendText(WiFi.macAddress()); });
}

void Webserver::serveStatic(const char *uri, const char *path, const char *cacheheader) {
    _server.serveStatic(uri, _fs, path, cacheheader);
}

void Webserver::begin() {
    _server.begin();
    _logger.info("HTTP server started");
}

void Webserver::handleClient() { _server.handleClient(); }

void Webserver::sendJson(const JsonDocument &json, int httpCode) {
    String response;
    serializeJson(json, response);
    _server.send(httpCode, "application/json", response);
}
void Webserver::sendText(const String &content, int httpCode) { _server.send(httpCode, "text/plain", content); }

const String &Webserver::arg(const String &name) const { return _server.arg(name); }