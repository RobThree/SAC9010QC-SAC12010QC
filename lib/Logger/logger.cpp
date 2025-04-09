#include "logger.h"

Logger::Logger(Stream &output) : _output(output), _logLevel(INFO) {}

void Logger::setLogLevel(Level level) { _logLevel = level; }

void Logger::log(Level level, const char *message) {
    if (level >= _logLevel) {
        _output.print("[");
        _output.print(levelToString(level));
        _output.print("] ");
        _output.println(message);
    }
}

void Logger::log(Level level, const String &message) {
    log(level, message.c_str()); // Convert String to const char*
}

void Logger::debug(const char *message) { log(DEBUG, message); }
void Logger::info(const char *message) { log(INFO, message); }
void Logger::warn(const char *message) { log(WARN, message); }
void Logger::error(const char *message) { log(ERROR, message); }

void Logger::debug(const String &message) { log(DEBUG, message); }
void Logger::info(const String &message) { log(INFO, message); }
void Logger::warn(const String &message) { log(WARN, message); }
void Logger::error(const String &message) { log(ERROR, message); }

const char *Logger::levelToString(Level level) {
    switch (level) {
    case DEBUG:
        return "DEBUG";
    case INFO:
        return "INFO";
    case WARN:
        return "WARN";
    case ERROR:
        return "ERROR";
    default:
        return "UNKNOWN";
    }
}
