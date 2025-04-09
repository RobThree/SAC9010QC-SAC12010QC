#ifndef IR_H
#define IR_H

#include "../ACState/acstate.h"
#include "../Logger/logger.h"
#include <IRremoteESP8266.h>
#include <IRsend.h>

class IR {
  public:
    IR(Logger &log, uint16_t irLedPin) : _logger(log), _ir(irLedPin) {};
    void begin();
    void send(ACState state);

  private:
    Logger &_logger; // Reference to the logger
    IRsend _ir;
};

#endif // IR_H