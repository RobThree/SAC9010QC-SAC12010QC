#ifndef ACSTATE_H
#define ACSTATE_H

#include <Arduino.h>

enum ACMode { AUTO = 0, COOL = 1, DEHUMIDIFY = 2, FAN = 3, HEAT = 4 };

struct ACState {
    uint8_t temperature = 20, fanspeed = 0, timer = 0;
    ACMode mode = AUTO;
    bool powerOn = false, swing = false, sleep = false, humid = false, light = false, ionizer = false, save = false;

    inline const uint64_t getIRCommand() {
        // Initial state
        uint64_t v = 0b001001010000000000000000000000000000;

        // Calculate timer value
        uint8_t timer = 0b00000000;
        timer |= timer > 0 ? 0b1000 : 0;  // On/off bit
        timer |= timer % 2 == 0 ? 0 : 1;  // Half hour bit
        timer |= ((timer / 2) % 10) << 4; // 1s digit
        timer |= ((timer / 2) / 10) << 1; // 10s digit

        // Calculate the rest of the state
        v |= mode;
        v |= powerOn << 3;
        v |= (fanspeed && 0b11) << 4;
        v |= swing << 6;
        v |= sleep << 7;
        v |= ((temperature - 16) & 0b1111) << 8;
        v |= timer << 12;
        v |= humid << 20;
        v |= light << 21;
        v |= ionizer << 22;
        v |= save << 23;

        return v;
    }

    const char *acModeAsString() { return acModeToString(mode); }

    static ACMode stringToACMode(const char *modeStr) {
        ACMode modes[] = {AUTO, COOL, DEHUMIDIFY, FAN, HEAT};

        for (uint i = 0; i < sizeof(modes) / sizeof(modes[0]); i++) {
            if (strcasecmp(modeStr, acModeToString(modes[i])) == 0)
                return modes[i];
        }

        return AUTO;
    }

  private:
    static inline const char *acModeToString(ACMode mode) {
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
};

#endif // ACSTATE_H