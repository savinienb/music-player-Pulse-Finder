#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <fftmath.h>
#include <vector>
#include <complex>
#include <phonon/AudioDataOutput>
#include <phonon/MediaObject>
#include <audioclass.h>
#include <mathrythm.h>
#include <QtMultimediaKit/QMediaPlayer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QMap<Phonon::AudioDataOutput::Channel, QVector<qint16> > m_audiodata;


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);

private:

    Ui::MainWindow *ui;


    int is_checktempo,is_tempo, is_counttime,is_clock,is_bpm,is_blink,loading;
    bool is_metronomestate,is_thereanaudiosource,loopcreated,rainbow;

    //////////////////Sound and mathrythm


    bool is_domain; //this boolean serve the purpose of knowing wich audio signal we display (frequecy or time)

    QMediaPlayer * Music;
    Phonon::AudioOutput mediaout;
    Phonon::MediaObject media;//We create them here to connect easily the interface to them (seek bar and volume)

    fftmath fft;
    vector< complex<float> > audiodata;

    int get_Bpm() const { return is_bpm; }

    bool get_Metronomestate() const { return is_metronomestate; }

    void set_domain(const bool& foo){is_domain=foo;}
    bool get_domain()const{return is_domain;}

    int get_Tempo() const        { return is_tempo; }

    mathrythm mathryt;

    void pulsebutton(const bool& a);
    QString name;
    void set_name(const QString& filename){name=filename;}
    QString get_name()const {return name;}

    //////////////////Metronome

    Phonon::MediaObject *bellsound;
    Phonon::MediaObject *clicksound;
    Audioclass audio;

    void Set_Loadingvalue(int value);

    int get_Checktempo() const        { return is_checktempo; }
    void set_Checktempo( const int& checktempo)   {is_checktempo = checktempo; }


    void set_Tempo( const int& tempo)   {is_tempo = tempo; }


    int get_Counttime() const        { return is_counttime; }
    void set_Counttime( const int& counttime)   {is_counttime = counttime; }


    int get_Clock() const        { return is_clock; }
    void set_Clock( const int& clock)   {is_clock = clock; }


    void tempo();
    void metrosound();

    void set_Bpm( const int& n)   {is_bpm = n; }

    void set_Blink( const int& bpm)   {is_blink = bpm; }

    void set_Metronomestate( const int& metro)   {is_metronomestate = metro; }

    QTimer *timer;


public slots:
    void dataReceived(const QMap<Phonon::AudioDataOutput::Channel, QVector<qint16> >& data);


private slots:

    void Loadingvalue(const int &value){Set_Loadingvalue(value);}

    void on_Pulse_clicked();

    void on_Metrostate_clicked();

    void clock();

    void on_ModifyMetronome_clicked();

    //void on_Replay_clicked();

    void on_setaudiosource_clicked();

    void on_Play_clicked();

    void on_setryhtmvariable_clicked();

    void on_Stop_clicked();

    void ShowContextMenu(const QPoint &pos); //from http://stackoverflow.com/questions/24254006/rightclick-event-in-qt-to-open-a-context-menu

    void musicpath(const bool &is_filepathgood,const QString &filename);

    void timedomain(){set_domain(0);}

    void frequencydomain(){set_domain(1);}

    void on_pushButton_clicked();



signals:
    void changemusic(QString);
    void playmusic();
    void pausemusic();
    void setrythmvariable(int mean,int variance);
};

#endif // MAINWINDOW_H


