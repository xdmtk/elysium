#ifndef ELYSIUM_SERVER_LOGGER_H
#define ELYSIUM_SERVER_LOGGER_H

#include <string>

class Logger {
public:
    static void info(std::string);
    static void debug(std::string);
    static void warn(std::string);
    static void error(std::string);
    static void fatal(std::string);
    static std::string getLatestBuildCommit();
    static std::string getDBScriptsDirectory();
    static std::string execShellCommand(const char *);
private:
    enum LogLevel {Info, Debug, Warn, Error, Fatal};
    static bool writeToConsole;
    static bool writeToFile;
    static bool terminateOnFatal;

    static void log(std::string, LogLevel);

    static std::string getCurrentDateString();
    static std::string getCurrentTimeString();
    static std::string getLogDirectory();
    static std::string getHomeDirectory();
};


#endif //ELYSIUM_SERVER_LOGGER_H
