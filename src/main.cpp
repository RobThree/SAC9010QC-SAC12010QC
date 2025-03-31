#include <ArduinoJson.h>
#include <ArduinoOTA.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <LittleFS.h>
#include <WiFiManager.h>
#include <WiFiUdp.h>
#include <config.h>

IRsend irsend(IRLED);

ESP8266WebServer server(80);
ESP8266HTTPUpdateServer httpUpdateServer;

enum acMode { AUTO = 0, COOL = 1, DEHUMIDIFY = 2, FAN = 3, HEAT = 4 };

struct state {
    uint8_t temperature = 20, fanspeed = 0, timer = 0;
    acMode mode;
    bool powerOn, swing, sleep, humid, light, ionizer, save;
};
state acState;

void setStatus(const String &status) {
    // Someday I might add a little OLED display
    Serial.println(status);
}

void restart(const String &status) {
    setStatus(status);
    delay(3000);
    ESP.restart();
}

inline const char *acModeToString(acMode mode) {
    switch (mode) {
    case AUTO:
        return "AUTO";
    case COOL:
        return "COOL";
    case DEHUMIDIFY:
        return "DEHUMIDIFY";
    case FAN:
        return "FAN";
    case HEAT:
        return "HEAT";
    default:
        return "[Unknown acMode]";
    }
}

inline const uint64_t getIRCommand() {
    // Initial state
    uint64_t v = 0b001001010000000000000000000000000000;

    // Calculate timer value
    uint8_t timer = 0b00000000;
    timer |= acState.timer > 0 ? 0b1000 : 0;  // On/off bit
    timer |= acState.timer % 2 == 0 ? 0 : 1;  // Half hour bit
    timer |= ((acState.timer / 2) % 10) << 4; // 1s digit
    timer |= ((acState.timer / 2) / 10) << 1; // 10s digit

    // Calculate the rest of the state
    v |= acState.mode;
    v |= acState.powerOn << 3;
    v |= (acState.fanspeed && 0b11) << 4;
    v |= acState.swing << 6;
    v |= acState.sleep << 7;
    v |= ((acState.temperature - 16) & 0b1111) << 8;
    v |= timer << 12;
    v |= acState.humid << 20;
    v |= acState.light << 21;
    v |= acState.ionizer << 22;
    v |= acState.save << 23;

    return v;
}

acMode stringToAcMode(const char *modeStr) {
    acMode modes[] = {AUTO, COOL, DEHUMIDIFY, FAN, HEAT};

    for (uint i = 0; i < sizeof(modes) / sizeof(modes[0]); i++) {
        if (strcasecmp(modeStr, acModeToString(modes[i])) == 0)
            return modes[i];
    }

    return AUTO;
}

String getStateAsJson() {
    JsonDocument root;

    root["power"] = acState.powerOn;
    root["temperature"] = acState.temperature;
    root["fanspeed"] = acState.fanspeed;
    root["mode"] = acModeToString(acState.mode);
    root["swing"] = acState.swing;
    root["sleep"] = acState.sleep;
    root["humid"] = acState.humid;
    root["light"] = acState.light;
    root["ionizer"] = acState.ionizer;
    root["save"] = acState.save;
    root["timer"] = acState.timer; // Number of 30 minute increments (0 .. 48)
    root["rssi"] = WiFi.RSSI();

    String output;
    serializeJson(root, output);
    return output;
}

void blastIR() {
    uint64_t irCommand = getIRCommand();
    Serial.print("Sending IR: ");
    Serial.println(irCommand, BIN);
    irsend.sendTeco(irCommand, 36);
}

void setup() {
    irsend.begin();

    Serial.begin(SERIAL_BAUDRATE, SERIAL_8N1, SERIAL_TX_ONLY);

    WiFiManager wifiManager;
    wifiManager.setConfigPortalTimeout(PORTALTIMEOUT);
    wifiManager.setConnectTimeout(WIFICONNECTTIMEOUT);
    wifiManager.setConnectRetries(WIFICONNECTRETRIES);
    wifiManager.setWiFiAutoReconnect(true);
    if (!wifiManager.autoConnect(DEVICENAME)) {
        restart("Autconnect failed...");
    }

    httpUpdateServer.setup(&server);
    server.on("/state", HTTP_PUT, []() {
        setStatus("PUT /state");
        JsonDocument root;
        DeserializationError error = deserializeJson(root, server.arg("plain"));
        if (error) {
            server.send(404, "text/plain", "FAIL. " + server.arg("plain"));
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
                acState.mode = stringToAcMode(root["mode"]);
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

            server.send(200, "text/plain", getStateAsJson());
            blastIR();
        }
    });

    server.on("/state", HTTP_GET, []() {
        setStatus("GET /state");
        server.send(200, "text/plain", getStateAsJson());
    });

    server.on("/mac", HTTP_GET, []() {
        setStatus("GET /mac");

        server.send(200, "text/plain", WiFi.macAddress());
    });

    server.on("/reset", HTTP_PUT, []() {
        setStatus("Resetting");
        server.send(200, "text/html", "reset");
        delay(100);
        ESP.restart();
    });

    server.on("/", HTTP_GET, []() {
        File file = LittleFS.open("/index.html", "r");
        if (!file) {
            server.send(404, "text/plain", "File not found");
            return;
        }
        server.streamFile(file, "text/html");
        file.close();
    });

    server.onNotFound([]() { server.send(404, "text/plain", "File not found"); });

    blastIR(); // Initialize AC to our state
    server.begin();

    ArduinoOTA.setPassword(OTAPASSWORD);
    ArduinoOTA.setHostname(DEVICENAME); // Set the OTA device hostname
    ArduinoOTA.onStart([]() {
        String type = (ArduinoOTA.getCommand() == U_FLASH) ? "sketch" : "filesystem";
        setStatus("Start updating " + type);
    });
    ArduinoOTA.onEnd([]() { setStatus("Update Complete"); });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        setStatus("Progress: " + String((progress * 100) / total) + "%");
    });
    ArduinoOTA.onError([](ota_error_t error) {
        setStatus("Error: " + String(error));
        if (error == OTA_AUTH_ERROR)
            setStatus("Auth Failed");
        else if (error == OTA_BEGIN_ERROR)
            setStatus("Begin Failed");
        else if (error == OTA_CONNECT_ERROR)
            setStatus("Connect Failed");
        else if (error == OTA_RECEIVE_ERROR)
            setStatus("Receive Failed");
        else if (error == OTA_END_ERROR)
            setStatus("End Failed");
    });

    setStatus("Starting OTA server");
    ArduinoOTA.begin();

    setStatus(WiFi.localIP().toString());
    
    if (!LittleFS.begin()) {
        setStatus("Failed to mount filesystem");
    }

    delay(2000);
}

void loop() {
    server.handleClient();
    ArduinoOTA.handle();
    if ((WiFi.status() != WL_CONNECTED)) {
        setStatus("WiFi not connected, reconnecting...");
        WiFi.reconnect();
        unsigned long start = millis();

        while (WiFi.status() != WL_CONNECTED && millis() - start < 10000) {
            delay(100);
        }

        if (WiFi.status() == WL_CONNECTED) {
            setStatus("WiFi reconnected");
        } else {
            setStatus("Failed to reconnect to WiFi. Retrying...");
            delay(1000);
        }
    }
}