#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h> // Required for Serial and String handling

class Logger {
  public:
    enum Level { DEBUG, INFO, WARN, ERROR };

    Logger(Stream &output); // Constructor

    void setLogLevel(Level level);
    void log(Level level, const char *message);
    void log(Level level, const String &message);

    void debug(const char *message);
    void info(const char *message);
    void warn(const char *message);
    void error(const char *message);

    void debug(const String &message);
    void info(const String &message);
    void warn(const String &message);
    void error(const String &message);

  private:
    Stream &_output;
    Level _logLevel;
    const char *levelToString(Level level);
};

#endif // LOGGER_H
