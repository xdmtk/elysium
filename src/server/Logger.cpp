#include "Logger.h"

#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <csignal>
#include <fstream>
#include <ios>
#include <iostream>
#include <utility>
#include <sys/stat.h>

/**
 * Logger configuration settings
 */
bool Logger::writeToConsole = false;
bool Logger::writeToFile = true;
bool Logger::terminateOnFatal = true;


/** 
 * Helper function to Log the latest commit for the running instance.
 * Helpful in verifying which version of the server is being ran at
 * any given moment 
 */
std::string Logger::getLatestBuildCommit() {
    std::string gitDirectory = getHomeDirectory() + "/elysium";
    std::string gitLog = Logger::execShellCommand(
            std::string("cd " + gitDirectory + " && git log | head -1").c_str());
    return gitLog;
}

/**
 * Simple helper function to return the current year, month,
 * and date in the format MM-DD-YYYY
 * @return - Formatted string date, month, year
 */
std::string Logger::getCurrentDateString() {
    time_t currentUnixTime = time(0);
    tm * timeStructure = localtime(&currentUnixTime);

    int month = timeStructure->tm_mon+1;
    int day = timeStructure->tm_mday;
    int year = timeStructure->tm_year+1900;

    return (month < 10 ? "0" : "") + std::to_string(month)
           + "-" + (day  < 10 ? "0" : "") + std::to_string(day)
           + "-" + (year  < 10 ? "0" : "") + std::to_string(year);
}

/**
 * Simple helper function to return the current hour, minute,
 * and second in the format HH:MM:SS
 * @return - Formatted string hour, minute, second
 */
std::string Logger::getCurrentTimeString() {
    time_t currentUnixTime = time(0);
    tm * timeStructure = localtime(&currentUnixTime);

    int hour = timeStructure->tm_hour;
    int min = timeStructure->tm_min;
    int sec = timeStructure->tm_sec;

    return (hour < 10 ? "0" : "") + std::to_string(hour)
        + ":" + (min  < 10 ? "0" : "") + std::to_string(min)
        + ":" + (sec  < 10 ? "0" : "") + std::to_string(sec);
}

/**
 * Master function called by public shorthand functions for Logging
 * at various levels of importance.
 * @param msg
 * @param level
 */
void Logger::log(std::string msg, Logger::LogLevel level) {

    std::ofstream logStream(getLogDirectory() + getCurrentDateString() + ".log", std::fstream::out | std::fstream::app);
    std::string levelString;

    switch (level) {
        case LogLevel::Info: levelString = "INFO"; break;
        case LogLevel::Debug: levelString = "DEBUG"; break;
        case LogLevel::Warn: levelString = "WARN"; break;
        case LogLevel::Error: levelString = "Error"; break;
        case LogLevel::Fatal: levelString = "Fatal"; break;
    }
    msg = "[" + getCurrentDateString() + "]-[" + getCurrentTimeString() + "]-[" + levelString
          + "] - " + msg + "\n";

    if (logStream.is_open() && logStream.good() && writeToFile) {
        logStream.write(msg.c_str(), msg.size());
        logStream.close();
    }
    if (writeToConsole) {
        std::cout << msg;
    }
    if (terminateOnFatal && level == LogLevel::Fatal) {
        raise(SIGTERM);
    }
}

/**
 * Builds and returns a hidden directory at the running users home
 * directory for log file storage
 * @return
 */
std::string Logger::getLogDirectory() {
    std::string logDirectoryPath = getHomeDirectory() + "/.elysium-logs/";
    mkdir(logDirectoryPath.c_str(), 0777);
    return logDirectoryPath;
}

/**
 * Returns the executing users home directory
 * @return
 */
std::string Logger::getHomeDirectory() {
    return "/home/" + std::string(getenv("USER"));
}


/**
 * Function to execute a command on the server shell and return the response
 * as a string
 */
std::string Logger::execShellCommand(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        Logger::error("Popen() failed - Cannot execute shell command");
        return "";
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

/**
 * Series of public facing, static log functions to be inserted around the
 * application for debugging.
 * @param msg
 */
void Logger::info(std::string msg) {
    log(std::move(msg), LogLevel::Info);
}

void Logger::debug(std::string msg) {
    log(std::move(msg), LogLevel::Debug);
}

void Logger::warn(std::string msg){
    log(std::move(msg), LogLevel::Warn);
}

void Logger::error(std::string msg){
    log(std::move(msg), LogLevel::Error);
}

void Logger::fatal(std::string msg){
    log(std::move(msg), LogLevel::Info);
}


