#ifndef AUDIOCLASS_H
#define AUDIOCLASS_H
#include <phonon/audiodataoutput.h>
#include <phonon>
#include <QFile>
#include <complex>
#include <vector>

using namespace std;


/*/////////////////////////////////////////////////////////////////////////////////////////////////
This Class as for purpose to deal with audio data. It goes from gathering to sending them to another
Class or to the Speaker
/////////////////////////////////////////////////////////////////////////////////////////////////*/



class Audioclass : public QObject
{
    Q_OBJECT
    QMap<Phonon::AudioDataOutput::Channel, QVector<qint16> > m_audiodata;


public:

    Audioclass();
    ~Audioclass(){}


    void startbuffer(QObject *mainwindow,Phonon::MediaObject* media,Phonon::AudioOutput* mediaout,const int& buffersize);

    QString get_currentpath() const{return currentpath;}

    void streamsource();

    void Bigdataget(const int &buffersize,Phonon::MediaObject *media,vector< complex<float> > *);

private:

    vector< complex<float> > * store;

    void set_buffersize(const int &buff){buffersize=buff;}
    int get_buffersize()const {return buffersize;}
    int buffersize;

    QAudioInput* stream;
    QFile streamdestinationfile;

    //medias is a media object use to load the data from the file
    Phonon::MediaObject* loadfiletomedia;

    //mediato speaker fetch the data from the media object to send them to the software
    Phonon::AudioDataOutput mediatoprogramm;

    //current path hold the path of the file currently playing
    QString currentpath;
    void set_currentpath(const QString &path){currentpath= path;}

    //function to switch from an audio file to another
    void changepath(const QString &path);

    bool athalf;

    QAudioOutput *audioOut;
    QAudioInput  *audioIn;
    QAudioFormat formatIn,formatOut;

    vector<complex<float> >* Bigdata;

    void Bigdatastream();

private slots:

    void pausemusic() {loadfiletomedia->pause();}

    void playmusic(){loadfiletomedia->play();}

    void changemusic(const QString &path){changepath(path);}

    void BigdataReceived(const QMap<Phonon::AudioDataOutput::Channel, QVector<qint16> >& data){ m_audiodata=data;    Bigdatastream();}

signals:

    //this signal send info to the main windows
    void musicinfo(const bool &is_audiopathvalid,const QString &Metadata);

};


#endif // AUDIOCLASS_H

