#include "profile.h"
#include "ui_profile.h"

/*
 * constructor
 */
profile::profile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::profile)
{
    ui->setupUi(this);
}

/*
 * destructor
 */
profile::~profile(){
    delete ui;
}
/*
 * slot fuction:
 * closes the profile when button is clicked
 */
void profile::on_exitPushButton_clicked(){
    this->close();
}

/*
 * sets the username in the profile
 */
void profile::setUsername(QString username){
        ui->usernameLineEdit->setText("Username: "+ username);
}

/*
 * sets the online status
 * makes the background green if online
 * makes the background red if don't disturb
 */
void profile::setStatus(bool online){
    if(online == true){
        ui->onlineStatusLineEdit->setText("Online Status: Online");
        ui->backgroundListView->setStyleSheet("background: green;");
    }
    else if(online == false){
        ui->onlineStatusLineEdit->setText("Online Status: Don't Disturb");
        ui->backgroundListView->setStyleSheet("background: red;");
    }

}

/*
 * sets dark mode or light mode
 * if dark mode makes the profile into dark mode
 * if light mode makes the profile into light mode
 */
void profile::setDark(bool dark){
    if(dark == true){
        ui->darkModeLineEdit->setText("Dark Mode: Active");
        ui->onlineStatusLineEdit->setStyleSheet("background: rgb(80,80,80);"
                                         "color:white;");
        ui->darkModeLineEdit->setStyleSheet("background: rgb(80,80,80);"
                                         "color:white;");
        ui->soundLineEdit->setStyleSheet("background: rgb(80,80,80);"
                                         "color:white;");
        ui->usernameLineEdit->setStyleSheet("background: rgb(80,80,80);"
                                         "color:white;");
        ui->friendsLineEdit->setStyleSheet("background: rgb(80,80,80);"
                                         "color:white;");
        ui->proflieListView->setStyleSheet("background: gray;");
        ui->titleLineEdit->setStyleSheet("background: rgb(80,80,80);"
                                         "color:white;");
    }
    else
        ui->darkModeLineEdit->setText("Light Mode: Active");
}

/*
 * sets the number of friends
 */
void profile::setNumberOfFriends(int num){
    ui->friendsLineEdit->setText("Number of Friends: "+ QString::number(num) );
}

/*
 * sets the sound on or off in the profile
 */
void profile::setSound(bool sound){
    if(sound == true){
        ui->soundLineEdit->setText("Sound: On");
    }
    else
        ui->soundLineEdit->setText("Sound: Off");
}
