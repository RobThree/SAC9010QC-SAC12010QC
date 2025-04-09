#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "../Logger/logger.h"
#include <ArduinoJson.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266WebServer.h>
#include <LittleFS.h>

class Webserver {
  public:
    Webserver(Logger &log, FS fs, int port = 80) : _logger(log), _fs(fs), _server(port) {
        _fs.begin();
        _httpUpdateServer.setup(&_server);
        _server.onNotFound([this]() { _server.send(404, "text/plain", "File not found"); });
    };
    void useDefaultEndpoints();
    void begin();
    void handleClient();
    void sendJson(const JsonDocument &json, int httpCode = 200);
    void sendText(const String &content, int httpCode = 200);
    const String &arg(const String &name) const;
    void serveStatic(const char *, const char *path, const char *cacheheader = "max-age=300");
    void on(const String &uri, ESP8266WebServer::THandlerFunction fn) { _server.on(uri, fn); }
    void on(const String &uri, HTTPMethod method, ESP8266WebServer::THandlerFunction fn) {
        _server.on(uri, method, fn);
    }
    void on(const String &uri, HTTPMethod method, ESP8266WebServer::THandlerFunction fn,
            ESP8266WebServer::THandlerFunction ufn) {
        _server.on(uri, method, fn, ufn);
    }

  private:
    Logger &_logger; // Reference to the logger
    FS _fs;
    ESP8266WebServer _server;
    ESP8266HTTPUpdateServer _httpUpdateServer;
};

#endif // WEBSERVER_H
