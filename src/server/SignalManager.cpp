#include <csignal>
#include <thread>
#include <chrono>

#include "Logger.h"
#include "SignalManager.h"


/**
 * The SignalManager class should register and handle the most common signals
 * that could be trapped by application.
 *
 * Most importantly it should handle the kill signal, properly clean up
 * all open sockets, and gracefully exit the application.
 */
volatile int SignalManager::signalNumber = -1;
SignalManager::SignalManager(Server * s){

    /* SignalManager requires a pointer back to the caller to perform
     * clean-up tasks outside the scope of the class */
    server = s;

    setupSignalManagerConfig();
    registerSignals();
    listenForSignals();
}

/**
 * Function to setup all configuration values for SignalManager
 */
void SignalManager::setupSignalManagerConfig() {

    // Sets the polling interval on the listening thread in seconds
    signalPollInterval = 1;
}

/**
 * Opens a listener thread that polls the current signal number every second
 * to determine if a signal has been caught. If so, handleSignal() is called
 * and dealt with
 */
void SignalManager::listenForSignals() {
    std::thread([&] {
        while (true) {
            if (trappedSignal()) {
                handleSignal();
            }
            std::this_thread::sleep_for(std::chrono::seconds(signalPollInterval));
        }
    }).detach();
}

/**
 * Registers common signals that require special handling
 */
void SignalManager::registerSignals() {
    std::signal(SIGKILL, &SignalManager::updateSignalNumber);
    std::signal(SIGINT, &SignalManager::updateSignalNumber);
    std::signal(SIGSEGV, &SignalManager::updateSignalNumber);
    std::signal(SIGABRT, &SignalManager::updateSignalNumber);
    std::signal(SIGTERM, &SignalManager::updateSignalNumber);
    std::signal(SIGPIPE, &SignalManager::updateSignalNumber);
}

/**
 * The signal registry callback that updates a static class
 * global with the integer representing the trapped signal
 *
 * @param sn - Signal number integer
 */
void SignalManager::updateSignalNumber(int sn) {
    SignalManager::signalNumber = sn;
}

/**
 * Returns whether the application has trapped a signal. -1
 * is the default value and represents that no signal has been caught
 * @return
 */
bool SignalManager::trappedSignal() {
    return SignalManager::signalNumber != -1;
}

/**
 * Called when the signal trap flag has been set, handles
 * the signal appropriately
 */
void SignalManager::handleSignal() {
    switch (SignalManager::signalNumber) {

        // TODO: Implement functions to handle these signals
        case SIGABRT:
            handleSigAbort(); break;
        case SIGSEGV:
            handleSigSegfault(); break;
        case SIGINT:
            handleSigInterrupt(); break;
        case SIGKILL:
            handleSigKill(); break;
        case SIGPIPE:
            handleSigPipe(); break;
        default:
            // For unregistered signals, let quick_exit() deal with any clean up
            std::quick_exit(-1);
    }
}

/**
 * Signal handler functions, needs implementation
 */
void SignalManager::handleSigAbort() {
    Logger::warn("Caught SIGABORT");
}
void SignalManager::handleSigSegfault() {
    Logger::warn("Caught SIGSEGV");
}
void SignalManager::handleSigInterrupt() {
    Logger::warn("Caught SIGINT");
}
void SignalManager::handleSigKill() {
    Logger::warn("Caught SIGKILL");
}
void SignalManager::handleSigPipe() {
    Logger::warn("Caught SIGPIPE");
}
