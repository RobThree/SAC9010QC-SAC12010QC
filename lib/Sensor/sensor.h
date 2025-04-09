#ifndef SENSOR_H
#define SENSOR_H

#include "../Logger/logger.h"
#include <HCSR04.h>

class Sensor {
  public:
    Sensor(Logger &log, byte triggerPin, byte echoPin) : _logger(log), distanceSensor(triggerPin, echoPin) {};
    float readDistance();

  private:
    Logger &_logger; // Reference to the logger
    UltraSonicDistanceSensor distanceSensor;
};

#endif // SENSOR_H