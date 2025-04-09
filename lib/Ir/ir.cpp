#include "ir.h"

void IR::begin() {
    _ir.begin();
    _logger.info("IR initialized");
}

void IR::send(ACState state) {
    uint64_t irCommand = state.getIRCommand();

    char msg[64];
    snprintf(msg, sizeof(msg), "Sending IR: %llu", irCommand);
    _logger.info(msg);

    _ir.sendTeco(irCommand, 36);
}