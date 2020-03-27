#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H
#include <QtMultimedia/QMediaPlayer>
#include <QUrl>
#include <QString>

class SoundManager{
public:
    SoundManager();
    void newMessage();
private:
    QMediaPlayer *incomingMessage;
};

#endif // SOUNDMANAGER_H
