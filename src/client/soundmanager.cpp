#include "soundmanager.h"

SoundManager::SoundManager(): incomingMessage(nullptr){
    soundSetting = true;
    incomingMessage = new QMediaPlayer;
    incomingMessage->setMedia(QUrl("qrc:/sounds/resources/imrcv.wav"));
    sendMsg = new QMediaPlayer;
    userEnters = new QMediaPlayer;
    userLeaves = new QMediaPlayer;
    sendMsg->setMedia(QUrl("qrc:/sounds/resources/aimsend.wav"));
    userEnters->setMedia(QUrl("qrc:/sounds/resources/userEnter.wav"));
    userLeaves->setMedia(QUrl("qrc:/sounds/resources/userLeave.wav"));


}
void SoundManager::incMessage(){
    if(soundSetting){
        incomingMessage->setVolume(200);
        incomingMessage->play();
    }
}
void SoundManager::sendMessage(){
    if(soundSetting){
        sendMsg->setVolume(200);
        sendMsg->play();
    }
}
void SoundManager::userEntersChat(){
    if(soundSetting){
        userEnters->setVolume(200);
        userEnters->play();
    }
}
void SoundManager::userLeavesChat(){
    if(soundSetting){
        userLeaves->setVolume(200);
        userLeaves->play();
    }
}
bool SoundManager::getSoundSetting(){
    return soundSetting;
}
void SoundManager::setSoundSetting(bool setting){
    soundSetting = setting;
}
