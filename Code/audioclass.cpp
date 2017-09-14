#include "audioclass.h"
#include <phonon/audiooutput.h>
#include <phonon/audiodataoutput.h>
#include <phonon/mediaobject.h>
#include <QAudioFormat>
#include <QAudioOutput>
#include <mathrythm.h>
#include <vector>
#include <complex>

/*/////////////////////////////////////////////////////////////////////////////////////////////////
This Class as for purpose to deal with audio data. It goes from gathering to sending them to another
Class or to the Speaker
(for more detail go to : http://doc.qt.io/qt-4.8/phonon-overview.html)
/////////////////////////////////////////////////////////////////////////////////////////////////*/


Audioclass::Audioclass(){}



/*/////////////////////////////////////////////////////////////////////////////////////////////////
This function create a loop wich gather data then send them to the speaker and to the Mainwindow by slot and signal
/////////////////////////////////////////////////////////////////////////////////////////////////*/

void Audioclass::startbuffer(QObject *mainwindow,Phonon::MediaObject* media,Phonon::AudioOutput* mediatospeaker,const int &buffersize){


    //QString paths = ":";

    //here we copy the media pointer to the media object of this class so we could use it outside the function as a Class attribute
    loadfiletomedia=media;

    //We connect the sound file to the a sink we will later be useful to fetch data for the software
    Phonon::createPath(loadfiletomedia, &mediatoprogramm);


    //We connect the sound file data to the speaker
    Phonon::createPath(loadfiletomedia, mediatospeaker);

    //Set the size of the buffer (how much data we should gather before sending them)
    mediatoprogramm.setDataSize(buffersize);


    //Here we tell the computer "whenever a buffer is full send it to the mainwindow"
    loadfiletomedia->connect( &mediatoprogramm, SIGNAL(dataReady(const QMap<Phonon::AudioDataOutput::Channel, QVector<qint16> >&)),
                              mainwindow, SLOT(dataReceived(const QMap<Phonon::AudioDataOutput::Channel, QVector<qint16> >&)));

    //send file information from this window
    loadfiletomedia->connect(this,SIGNAL(musicinfo(bool,QString)),mainwindow,SLOT(musicpath(bool,QString)));


    //get the signal to play music from the mainwindow
    loadfiletomedia->connect( mainwindow, SIGNAL(playmusic()), this, SLOT(playmusic()));


    //get the signal to pause music from the mainwindow
    loadfiletomedia->connect( mainwindow, SIGNAL(pausemusic()), this, SLOT(pausemusic()));


    //get the signal to change music from the mainwindow
    loadfiletomedia->connect( mainwindow, SIGNAL(changemusic(QString)), this, SLOT(changemusic(QString)));


}


/*/////////////////////////////////////////////////////////////////////////////////////////////////
This function is here to check a file path of the signal and, if it's good, to set it.
It also send back to the mainwindow if the path is good and file info
/////////////////////////////////////////////////////////////////////////////////////////////////*/

void Audioclass::changepath(const QString &path){

    //create a bool to check if the path is good
    bool ispathgood=false;

    //Create a source object to use is possibility of path checking
    Phonon::MediaSource source(path);

    //Check if the file path is not already used (if so no need to change it)
    if (path!=get_currentpath() || path.compare("rainbow")==0){

        //Check the path type (-1 is invalid and 0 is path that we can use)
        if (source.type()==0){

            ispathgood=true;

            //change the file path (the music is automaticaly stopped
            loadfiletomedia->setCurrentSource(path);
            set_currentpath(path);

        }

        //Create a Qtfile object to get the name of the music
        QFileInfo fileInfo(path);
        QString filename(fileInfo.fileName());
        //emit a signal containing if the path is valid and the music name
        emit musicinfo(ispathgood ,filename);
    }
}


/*/////////////////////////////////////////////////////////////////////////////////////////////////
This function connect te different part needed to get song audiodata and call another function to get the middle of the song
/////////////////////////////////////////////////////////////////////////////////////////////////*/

void Audioclass::Bigdataget(const int &buffsize,Phonon::MediaObject* media,vector< complex<float> > * vector){

    QEventLoop a;//This is a dirty trick to force the programm to run by buffering is heavy mathematical computation to the programm exit
                 // A Qthread would have been needed for a proper implementation

    loadfiletomedia=media;
    QString paths = "/home/jellyo/Downloads/As It Is - Sorry.mp3"; //the file is input by hand as this part is in beta state
    Bigdata=vector;
    //We connect the sound file to the a sink we will later be useful to fetch data for the software
    Phonon::createPath(loadfiletomedia, &mediatoprogramm);

    //Set the size of the buffer (how much data we should gather before sending them)
    loadfiletomedia->setCurrentSource(paths);

    loadfiletomedia->connect( &mediatoprogramm, SIGNAL(dataReady(const QMap<Phonon::AudioDataOutput::Channel, QVector<qint16> >&)),
                              this, SLOT(BigdataReceived(const QMap<Phonon::AudioDataOutput::Channel, QVector<qint16> >&)));

    mediatoprogramm.setDataSize(buffsize);//set the number of data that we will take (we need around 5 second)

    loadfiletomedia->play();//play the file
    a.exec();
}

void Audioclass::Bigdatastream(){
    if(athalf==false){

        qint64 half= loadfiletomedia->remainingTime()/2; //check the duration of the song
        loadfiletomedia->seek(half);//go at half of the song
        athalf=true;

    }
    else {

        complex<float> temporary;

        athalf=false;

        for (int i=0;i<mediatoprogramm.dataSize();i++){//store the stereo input as the real and the imaginary part inside a vector

            temporary.real()=m_audiodata[Phonon::AudioDataOutput::LeftChannel][i];
            temporary.imag()=m_audiodata[Phonon::AudioDataOutput::RightChannel][i];
            Bigdata->push_back(temporary);

        }


        qDebug()<<"To get the result exit the GUI windows";
        loadfiletomedia->stop();//stop the file as we took all the needed data
    }
}
