#ifndef MATHRYTHM_H
#define MATHRYTHM_H

#include <audioclass.h>
#include <QObject>
#include <QtGui>

class mathrythm :public QObject
{
    Q_OBJECT
    QMap<Phonon::AudioDataOutput::Channel, QVector<qint16> > m_audiodata;

public:
    mathrythm();
    ~mathrythm(){}

    int getsongbpm();

    int get_numberofbin()const{return is_numberofbin;}

    int get_Indexnumber()const{return is_indexnumber;}

    float get_meanvalue(const int &row)const{return is_frequencymeanvector.at(row);}
    float get_meanthreshold()const{return is_meanthreshold;}
    void set_meanthreshold(const int &mean){is_meanthreshold=mean;}

    float get_variancevalue(int row)const{return is_frequencyvariancevector.at(row);}
    void set_variancethreshold(const int &variance){is_variancethreshold=variance;}
    int get_variancethreshold()const{return is_variancethreshold;}

    float get_subbandvalue(int vectorkey,int valueindex)const{vector<float> temp=is_subbandhistoric.at(vectorkey);return temp.at(valueindex);}
    int getsize_Subbandhistoric()const{return is_subbandhistoric.size();}

    complex<float> get_complexsubbandvalue(int vectorkey,int valueindex)const{vector<complex <float> > temp=is_complexsubbandhistoric.at(vectorkey);return temp.at(valueindex);}
    int getsize_complexSubbandhistoric()const{return is_complexsubbandhistoric.size();}

    bool pulse(const int& numberofbufferkept,const int& sizeoffft,QMap<Phonon::AudioDataOutput::Channel, QVector<qint16> > m_audiodata);

private:

    int is_variancethreshold;

    vector<float> is_frequencyvariancevector;
    void set_variancevalue(const int &row,const float &value){is_frequencyvariancevector.at(row)=value;}
    void set_sizevariancevaluevector(const int & size){is_frequencyvariancevector.resize(size);}

    void frequencyvariance();
    void frequencybinmean();


    int is_meanthreshold;
    void set_meanvalue(const int &row,const float &value){is_frequencymeanvector.at(row)=value;}
    vector<float> is_frequencymeanvector;

    void subbandhistoric(vector<complex<float> > *FFTvector);

    map < int, vector<float> > is_subbandhistoric;
    void edit_subbandhistoric(const int &nindex,vector<float> vec){is_subbandhistoric[nindex].swap(vec) ;}

    map < int, vector< complex <float> > > is_complexsubbandhistoric;
    void edit_complexsubbandhistoric(const int &nindex,vector< complex<float> > vec){is_complexsubbandhistoric[nindex].swap(vec) ;}

    void bpmtest(const int &infvalue,const int &maxvalue,const int &step);

    pair<int,double>  bpmandweight;

    void historicdivision(vector<complex<float> > *FFTvector);
    void subbandlogdivision(vector<float>* vec,vector<complex<float> >* FFT);


    void set_sizemeanvaluevector(const int &size){is_frequencymeanvector.resize(size);}


    int is_numberofbin;
    void set_numberofbin(const int &numberofbin){is_numberofbin=numberofbin;}


    int is_indexnumber;
    void set_Indexnumber(const int& index){is_indexnumber=index;}


    vector <pair<int,double > > bpmandweighthistoric;

    void impulsesignal(int bpm );

    map <int,vector<complex<float> > > combfilter;

public slots :
    void dataReceived(const QMap<Phonon::AudioDataOutput::Channel, QVector<qint16> >& data){m_audiodata=data;}

signals:
    void loadingvaluechanged(const int&);

};

#endif // MATHRYTHM_H
