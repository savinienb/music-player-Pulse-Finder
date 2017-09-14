#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QTimer>

/*/////////////////////////////////////////////////////////////////////////////////////////////////
  Initialise the main window and the variable
/////////////////////////////////////////////////////////////////////////////////////////////////*/

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);//create the ui windows
    setWindowTitle("Savinien Bonheur Pulse Finder");


    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),this, SLOT(ShowContextMenu(const QPoint &)));//used for right click

    loopcreated=false;


    rainbow=false;

    set_domain(0);//declare the time domain as the initial domain
    ui->volumeSlider->setAudioOutput(&mediaout);//connect the Qphonon wich send data to the speaker and connect it to a volumne slider
    ui->seekSlider->setMediaObject(&media);//connect the Qphonon media (gather the data) and connect it to a seek slider

    timer = new QTimer(this);//Declare a Timer
    connect(timer, SIGNAL(timeout()), this,SLOT(clock())); //Connect the timer
    timer->start(10); //state the frequency in ms

    Music = new QMediaPlayer(); //Create a Qmedia object to play the metronome sound. This is pointer need to be destroyed in the destructor
    set_Metronomestate(false);//set off the metronome when the programm is launch
}


MainWindow::~MainWindow()
{
    delete this->Music;//delete the pointer used for the metronome
    delete timer;
    delete ui;

}

void MainWindow::ShowContextMenu(const QPoint &pos) //from http://stackoverflow.com/questions/24254006/rightclick-event-in-qt-to-open-a-context-menu
{
    QMenu contextMenu(tr("Context menu"), this);
    if ( pos.x()>11 && pos.y()>11 && pos.x()<590 && pos.y()<225){
        QAction action1("Time Domain", this);
        QAction action2("Frequency Domain", this);
        connect(&action1, SIGNAL(triggered()), this, SLOT(timedomain()));
        connect(&action2, SIGNAL(triggered()), this, SLOT(frequencydomain()));
        contextMenu.addAction(&action1);
        contextMenu.addAction(&action2);
        contextMenu.exec(mapToGlobal(pos));
    }
}


/*/////////////////////////////////////////////////////////////////////////////////////////////////
Draw the black rectangle and everything in it
/////////////////////////////////////////////////////////////////////////////////////////////////*/
void MainWindow::paintEvent(QPaintEvent*event){
    QPainter painter(this); //Declare Qpainter

    setFixedSize(600,476); //fix the size of the programm windows



    // Black windows
    QBrush Brush(QColor(0,0,0));
    painter.setBrush(Brush);
    painter.drawRect(10,10,578,215);
    //



    //cadrillage
    painter.setPen(QColor(166,166,166,60));

    for (int b=0;b<17;b++){ //vertical thin line
        painter.setBrush(QColor(0,255,0));
        painter.drawRect(30+b*34,225,0,-213);
    }

    for (int b=0;b<7;b++){//horizontal thin line
        painter.setBrush(QColor(0,255,0));
        painter.drawRect(11,205-b*29,576,0);
    }



    //ensure the Qpen color
    painter.setPen(QColor(0,200,0,100));




    //declare local variable
    int y = 0;
    int x = 0;
    int w=580;//width
    int b=3;
    int h = 272;//height
    int nSamples = audiodata.size();

    if (get_domain()==false){ //if the user want the time domain graph
        if (rainbow==true){
            painter.setPen(QColor(rand()%255,rand()%255,rand()%255,110));
        }

        for(int i =0; i < nSamples ; i++)//for all the value showable do
        {
            y = ((m_audiodata[Phonon::AudioDataOutput::LeftChannel][i])+(m_audiodata[Phonon::AudioDataOutput::LeftChannel][i]))/2;
            y=y/2*h/51070 + 205-b*29;//set the height of the graph
            x = (i*w)/nSamples+10;//set the distance between two value (dx)
            painter.drawLine(x,205-b*29,x,y);
        }

    }


    else{       //if the user want the the frequency domain graph

        int numberofvalues=0;
        int subbandnumber=0;


        //frequency axis value
        QFont font;
        font.setPixelSize(11);
        painter.setFont(font);
        painter.drawText(22,216,"0");
        painter.drawText(575,203,"HZ");
        painter.drawText(20,20,"x^10");
        font.setPixelSize(10);
        painter.setFont(font);

        for (int i=1;i<17;i++){//horizontal value
            int band=1378.125*i;
            painter.drawText(15+i*34,218,QString::number(band));
        }
        for (int i=1;i<8;i++){
            int band=(i*29);
            painter.drawText(11,205-i*29,QString::number(band));
        }


        //Calcul frequency's bin (add n value together)
        float bin=0;

        for(int i =0; i < nSamples/2 ; i++)//as the FFT is symetrics by is middle
        {
            complex<float> value;
            value=audiodata.at(i);

            numberofvalues=numberofvalues+1;

            if (numberofvalues==32)//every 32 value added draw is value
            {
                subbandnumber=subbandnumber+1;
                bin=bin+20*log10(sqrt(pow( value.real(),2) +pow( value.imag(),2) )) ;
                bin=bin/32;

                x = subbandnumber*34+3;
                y= (bin*h)/10;

                if (rainbow==true){
                    painter.setBrush(QColor(rand()%255,rand()%255,rand()%255,200));
                    painter.setPen(QColor(0,0,0,0));
                }

                else{
                    painter.setBrush(QColor(0,200,0,200));
                    painter.setPen(QColor(0,0,0,0));
                }

                painter.drawRect(x,h*0.75,21,-y);//draw a rectangle with a width of 21 pixel and a height of -y
                numberofvalues=0;

            }
        }

        if (rainbow==1){
            painter.setPen(QColor(255,255,255));//set pen color
        }

        else{
            painter.setPen(QColor(0,255,0,180));//set pen color
        }



        //Big axis
        painter.drawLine(20, 205, 576, 205);//horizontal axis for the frequency display
        painter.drawLine(30, 20, 30, 215);//vertical axis for for the frequency display

    }

}


/*/////////////////////////////////////////////////////////////////////////////////////////////////
 Disable the radio button without affecting is color as it will be if we disable the button.
/////////////////////////////////////////////////////////////////////////////////////////////////*/
void MainWindow::on_Pulse_clicked()
{
    if(ui->Pulse->isChecked()) {//if the user check the button we uncheck it
        ui->Pulse->setChecked(false);
    }
    else {//if the user uncheck the button we check it again
        ui->Pulse->setChecked(true);
    }
}














/*/////////////////////////////////////////////////////////////////////////////////////////////////
  This function is a clock used to keep time
/////////////////////////////////////////////////////////////////////////////////////////////////*/
void MainWindow::clock(){//this function is called every 10 ms
    set_Counttime(get_Counttime()+10);//this edit the clock counter
    tempo();
}


/*/////////////////////////////////////////////////////////////////////////////////////////////////
Keep track of the tempo and of the bpm to play sound and display colors change accordingly
/////////////////////////////////////////////////////////////////////////////////////////////////*/
void MainWindow::tempo(){
    if (get_Counttime() == 100) { //this is usefull to keep thebpulse button on during 0.1 second
        ui->Pulse->setChecked(false); //extinct the rythm round button
        ui->Bigtemp->setText(" "); //change the rectangle color for white
    }

    if (get_Metronomestate()==false){}//stop the metronome

    else if (get_Counttime()>=60000/get_Bpm() ){ //Divide the time in bpm

        set_Counttime(0);// set the clock to zero
        ui->Pulse->setChecked(true);//check the radio button
        set_Checktempo(get_Checktempo()+1);//count the time

        Music->setMedia(QUrl("qrc:/metro/click.wav")); //Give to the variable the Sound from the ressources


        if (get_Tempo()==get_Checktempo()) { //check if the number of time elapsed is equal to the number of time by measure

            QLineEdit lineEdit;//change the color of the cube
            QFont font("Arial Black", 72,QFont::Bold,true); //change the color
            lineEdit.setFont(font); //change the color of the cube
            ui->Bigtemp->setText("m"); //change the rectangle color by inputing a giant m in it
            set_Checktempo(0);

            Music->setMedia(QUrl("qrc:/metro/bell.wav")); //Give to the variable the Sound from the ressources

        }
        Music->play();//play
    }

}


/*/////////////////////////////////////////////////////////////////////////////////////////////////
 Stop or Start the metronome
/////////////////////////////////////////////////////////////////////////////////////////////////*/
void MainWindow::on_Metrostate_clicked()
{
    if ( get_Metronomestate() == false ){ // if you start the metronome

        ui->Metrostate->setText("Stop Metronome");
        set_Metronomestate(true);//set a boolean to 1
        ui->tab->setDisabled(true); // disable the other table
        ui->tab_2->setDisabled(true);//
        ui->seekSlider->setDisabled(true);//disable the slider
        ui->volumeSlider->setDisabled(true);//disable the volumne slider
        on_ModifyMetronome_clicked(); //go get the bpm value and the number of time per measure

    }

    else {//if you stop the metronome

        set_Metronomestate(false); //set a boolean to 0
        ui->Metrostate->setText("Start Metronome");
        ui->tab->setEnabled(true);//enable the other tab
        ui->tab_2->setEnabled(true);//enable the other tab
        ui->seekSlider->setEnabled(true);//enable the seek slider
        ui->volumeSlider->setEnabled(true);//enable the volumne slider

    }
}


/*/////////////////////////////////////////////////////////////////////////////////////////////////
 Allow change in the metronome bpm
/////////////////////////////////////////////////////////////////////////////////////////////////*/
void MainWindow::on_ModifyMetronome_clicked()//if you change the parameters
{
    set_Counttime(0);//reinitialize counttime
    set_Checktempo(0); //reinitialize check tempo
    set_Tempo(ui->Measure->text().toUInt());
    set_Bpm(ui->BPM->text().toInt());
}

/*/////////////////////////////////////////////////////////////////////////////////////////////////
Change the path and check if is good
/////////////////////////////////////////////////////////////////////////////////////////////////*/

void MainWindow::on_setaudiosource_clicked()
{

    if (loopcreated == false)
    {
        loopcreated=true;
        audio.startbuffer(this,&media,&mediaout,1025);//set the file reading
    }

    emit changemusic(ui->path->text()); //emit a to Audioclass signal containing the path to audio class
}


/*/////////////////////////////////////////////////////////////////////////////////////////////////
 Play the music and disable tabs
/////////////////////////////////////////////////////////////////////////////////////////////////*/
void MainWindow::on_Play_clicked()
{
    emit playmusic();
    ui->tab_2->setDisabled(true);
    ui->tab_3->setDisabled(true);
}


/*/////////////////////////////////////////////////////////////////////////////////////////////////
 Pause the music
/////////////////////////////////////////////////////////////////////////////////////////////////*/
void MainWindow::on_Stop_clicked()
{
    emit pausemusic();//emit a signal toward audioclass to stop the media
    ui->tab_2->setDisabled(false);
    ui->tab_3->setDisabled(false);
}


/*/////////////////////////////////////////////////////////////////////////////////////////////////
 Change the threshold in the live detection
/////////////////////////////////////////////////////////////////////////////////////////////////*/
void MainWindow::on_setryhtmvariable_clicked()
{
    QString meanstring=ui->meanvariable->text();
    QString variancestring=ui->variancevariable->text();
    mathryt.set_meanthreshold(meanstring.toInt());
    mathryt.set_variancethreshold(variancestring.toInt());
}












/*/////////////////////////////////////////////////////////////////////////////////////////////////
On Precise BPM cliked start the calcul process.
Those operation should be done in a Qthread to run in parallel but as it's not working i didn't do it
/////////////////////////////////////////////////////////////////////////////////////////////////*/
void MainWindow::on_pushButton_clicked()
{
    QObject::connect(&mathryt,SIGNAL(loadingvaluechanged(int)),this,SLOT(Loadingvalue(const int &)));//connect a signal from the mathrythm class to send is advancement value to the main window
    int bpm=mathryt.getsongbpm();//call the function to get the bpm
    ui->BPMlineedit->setText(QString::number(bpm));//write the bpm into a line edit
}

//Change the value of the loading bar
void MainWindow::Set_Loadingvalue(int value){
    ui->progressBar->setValue(value);
}








/*/////////////////////////////////////////////////////////////////////////////////////////////////
Check if the pass is good and change the color of the line edit accordingly
/////////////////////////////////////////////////////////////////////////////////////////////////*/
void MainWindow::musicpath(const bool &is_filepathgood,const QString &filename){
    if (is_filepathgood==1){
        set_name(filename);
    }
    if (filename.compare("rainbow")==0){
        if (rainbow==false){rainbow=true;}
        else if (rainbow==true){rainbow=false;}
    }

    if (is_filepathgood == 0){ //if the pass is wrong
        ui->path->setStyleSheet("QLineEdit { background: rgb(235, 100, 100);  }");//change the color of line edit to red if the path is not usable
    }

    else{ //if the pass is good
        ui->path->setStyleSheet("QLineEdit { background: rgb(100, 225, 100);  }"); //change the color of line edit to green if the path is usable
        ui->setaudiosource->setText("Change audio source");
        ui->Tag->setText(name);
    }

    //a one second timer
    QTime dieTime= QTime::currentTime().addSecs(1);//http://stackoverflow.com/questions/3752742/how-do-i-create-a-pause-wait-function-using-qt
    while (QTime::currentTime()<dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

    ui->path->setStyleSheet("QLineEdit { background: rgb(255, 255, 255);  }");//set back the line edit to white}
}

/*/////////////////////////////////////////////////////////////////////////////////////////////////
  Get the data from the audio and fetch it to pulse detection and display
/////////////////////////////////////////////////////////////////////////////////////////////////*/
void MainWindow::dataReceived(const QMap<Phonon::AudioDataOutput::Channel, QVector<qint16> >& data)
{   m_audiodata=data;
    fft.hamming( data[Phonon::AudioDataOutput::LeftChannel].size()-1,data,&audiodata);
    bool rythm=mathryt.pulse(127, data[Phonon::AudioDataOutput::LeftChannel].size()-1,data);//call the function to know if there is a beat
    ui->Pulse->setChecked(rythm);
    update();}

