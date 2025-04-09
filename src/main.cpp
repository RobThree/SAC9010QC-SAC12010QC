#include "ir.h"
#include "ota.h"
#include "simplewifi.h"
#include "webserver.h"
#include <ArduinoJson.h>
#include <config.h>

Logger logger(Serial);
OTA ota(logger);
SimpleWiFi wifi(logger);
Webserver server(logger, LittleFS, HTTP_PORT);
IR ir(logger, IRLED);

ACState acState;

void handleReading();
void handleApply();
JsonDocument getStateAsJson();

void setup() {
    Serial.begin(SERIAL_BAUDRATE, SERIAL_8N1, SERIAL_TX_ONLY);

    ir.begin();

    wifi.begin(PORTALTIMEOUT, WIFICONNECTTIMEOUT, WIFICONNECTRETRIES, DEVICENAME);

    server.serveStatic("/", "/index.html");
    server.serveStatic("/css", "/main.css");
    server.serveStatic("/js", "/app.js");
    server.serveStatic("/favicon.ico", "/favicon.svg");
    server.serveStatic("/manifest.json", "/manifest.json");
    server.serveStatic("/ati120.png", "/ati120.png");
    server.serveStatic("/ati152.png", "/ati152.png");
    server.serveStatic("/ati180.png", "/ati180.png");
    server.on("/state", HTTP_GET, handleReading);
    server.on("/state", HTTP_PUT, handleApply);
    server.useDefaultEndpoints();
    server.begin();

    ir.send(acState); // Initialize AC to our state

    ota.begin(DEVICENAME, OTAPASSWORD);

    logger.info(wifi.localIP());
}

void loop() {
    server.handleClient();
    ota.handle();
    wifi.ensureConnected();
}

void handleReading() { server.sendJson(getStateAsJson()); }

void handleApply() {
    JsonDocument root;
    DeserializationError error = deserializeJson(root, server.arg("plain"));
    if (error) {
        server.sendText("FAIL. " + server.arg("plain"), 404);
    } else {
        if (root["power"].is<bool>()) {
            acState.powerOn = root["power"];
        }
        if (root["temperature"].is<int>()) {
            acState.temperature = constrain((uint8_t)root["temperature"], 16, 30);
        }
        if (root["fanspeed"].is<int>()) {
            acState.fanspeed = constrain((uint8_t)root["fanspeed"], 0, 3);
        }
        if (root["mode"].is<const char *>()) {
            acState.mode = ACState::stringToACMode(root["mode"]);
        }
        if (root["swing"].is<bool>()) {
            acState.swing = root["swing"];
        }
        if (root["sleep"].is<bool>()) {
            acState.sleep = root["sleep"];
        }
        if (root["humid"].is<bool>()) {
            acState.humid = root["humid"];
        }
        if (root["light"].is<bool>()) {
            acState.light = root["light"];
        }
        if (root["ionizer"].is<bool>()) {
            acState.ionizer = root["ionizer"];
        }
        if (root["save"].is<bool>()) {
            acState.save = root["save"];
        }
        if (root["timer"].is<int>()) {
            acState.timer = constrain(root["timer"], 0, 48);
        }

        server.sendJson(getStateAsJson());
        ir.send(acState);
    }
}

JsonDocument getStateAsJson() {
    JsonDocument root;

    root["power"] = acState.powerOn;
    root["temperature"] = acState.temperature;
    root["fanspeed"] = acState.fanspeed;
    root["mode"] = acState.acModeAsString();
    root["swing"] = acState.swing;
    root["sleep"] = acState.sleep;
    root["humid"] = acState.humid;
    root["light"] = acState.light;
    root["ionizer"] = acState.ionizer;
    root["save"] = acState.save;
    root["timer"] = acState.timer; // Number of 30 minute increments (0 .. 48)
    root["rssi"] = WiFi.RSSI();
    root["devicename"] = DEVICENAME;

    return root;
}
