#include "commandmanager.h"
#include "chatwindow.h"

CommandManager::CommandManager(ChatWindow * cw, SocketManager * s) {
    chatWindow = cw;
    socket = s;
}


void CommandManager::handleIncomingMessage() {
    std::string temp;
    QString qInput,userName;

    temp = socket->readServerData();
    CoreSettings::Protocol response = static_cast<CoreSettings::Protocol>(temp[0]);
    temp = temp.substr(1);

    switch (response){

        case CoreSettings::Protocol::ServerBroadcastMessage:
            chatWindow->display(QString::fromUtf8(temp.c_str()));
            break;
        case CoreSettings::Protocol::TypingIndicator:
        case CoreSettings::Protocol::NoTyping:
            chatWindow->setUsersTypingLabel(response, temp);
            break;
        default:
            break;
    }
}
