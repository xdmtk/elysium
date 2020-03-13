#include <QList>
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
            addIncomingMessageToChat(QString::fromUtf8(temp.c_str()));
            break;
        case CoreSettings::Protocol::TypingIndicator:
        case CoreSettings::Protocol::NoTyping:
            chatWindow->setUsersTypingLabel(response, temp);
            break;
        case CoreSettings::Protocol::ClientReceiveOnlineStatus:
            updateOnlineUserlist(QString::fromUtf8(temp.c_str()));
            break;
        default:
            break;
    }
}

void CommandManager::addIncomingMessageToChat(QString msg) {
    chatWindow->display(msg);
}

void CommandManager::updateOnlineUserlist(QString userlistString) {
    QStringList userlist = userlistString.split(",");
    if (!userlist.empty()) {

    }
}
