#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H
#include <QtMultimedia/QMediaPlayer>
#include <QUrl>
#include <QString>

class SoundManager{
public:
    SoundManager();
    void incMessage();
    void sendMessage();
    void userEntersChat();
    void userLeavesChat();
    bool getSoundSetting();
    void setSoundSetting(bool setting);
private:
    QMediaPlayer *incomingMessage;
    QMediaPlayer *sendMsg;
    QMediaPlayer *userEnters;
    QMediaPlayer *userLeaves;
    bool soundSetting;
};

#endif // SOUNDMANAGER_H
