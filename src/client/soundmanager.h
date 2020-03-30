#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H
#include <QtMultimedia/QMediaPlayer>
#include <QUrl>
#include <QString>

class SoundManager{
public:
    SoundManager();
    void newMessage();
    bool getSoundSetting();
    void setSoundSetting(bool setting);
private:
    QMediaPlayer *incomingMessage;
    bool soundSetting;
};

#endif // SOUNDMANAGER_H
