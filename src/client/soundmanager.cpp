#include "soundmanager.h"

SoundManager::SoundManager(): incomingMessage(nullptr){
    soundSetting = false;
    incomingMessage = new QMediaPlayer;
    incomingMessage->setMedia(QUrl("qrc:/sounds/resources/new-message-woosh.wav"));

}
void SoundManager::newMessage(){
    if(soundSetting){
        incomingMessage->setVolume(200);
        incomingMessage->play();
    }
}
bool SoundManager::getSoundSetting(){
    return soundSetting;
}
void SoundManager::setSoundSetting(bool setting){
    soundSetting = setting;
}
