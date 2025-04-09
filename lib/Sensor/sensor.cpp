#include "sensor.h"

float Sensor::readDistance() {
    float distance = distanceSensor.measureDistanceCm();
    if (distance < 0) {
        _logger.warn("Error reading distance");
        return -1;
    }
    return distance;
}