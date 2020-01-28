#ifndef ELYSIUM_SERVER_SIGNALMANAGER_H
#define ELYSIUM_SERVER_SIGNALMANAGER_H
#include <csignal>
class Server;
class SignalManager {
public:
    SignalManager(Server *);
private:
    Server * server;
    static volatile std::sig_atomic_t  signalNumber;
    int signalPollInterval;

    void setupSignalManagerConfig();
    void registerSignals();
    void listenForSignals();
    static void updateSignalNumber(int sn);

    bool trappedSignal();
    void handleSignal();
    void handleSigAbort();
    void handleSigSegfault();
    void handleSigInterrupt();
    void handleSigKill();
    void handleSigPipe();

};


#endif //ELYSIUM_SERVER_SIGNALMANAGER_H
