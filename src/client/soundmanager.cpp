#include "soundmanager.h"

SoundManager::SoundManager(): incomingMessage(nullptr){
    incomingMessage = new QMediaPlayer;
    incomingMessage->setMedia(QUrl("qrc:/sounds/resources/new-message-woosh.wav"));

}
void SoundManager::newMessage(){
    incomingMessage->setVolume(200);
    incomingMessage->play();
}
