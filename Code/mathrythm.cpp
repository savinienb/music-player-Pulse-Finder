#include "mathrythm.h"
#include <phonon/AudioDataOutput>
#include <complex>
#include <math.h>
#include <fftmath.h>


/*/////////////////////////////////////////////////////////////////////////////////////////////////
This Class is here to interpret music frequency and extract from them the rythm (for the math explanation go to :http://archive.gamedev.net/archive/reference/programming/features/beatdetection/
/////////////////////////////////////////////////////////////////////////////////////////////////*/



mathrythm::mathrythm()
{
    //this declare the index number at first call to be sure of where we start
    set_Indexnumber(0);
}


/*/////////////////////////////////////////////////////////////////////////////////////////////////
This function is the main function of this class.It gather information from other function and then
decide via two threshold if there is a pulsation before returning a corresponding boolean (1 if there is a pulse)
/////////////////////////////////////////////////////////////////////////////////////////////////*/


bool mathrythm::pulse(const int &numberofbufferkept,const int &sizeoffft, QMap<Phonon::AudioDataOutput::Channel, QVector<qint16> >m_audiodata)
{
    //This variable will store the pulse result
    bool ispulse=0;

    //We create a vector wich will store the frequency
    vector < complex<float> > FFTvector;

    fftmath fft;//creating an class object


    fft.derivatehamming( sizeoffft,m_audiodata,&FFTvector); //We pass the audio data and a pointer to our frequency vector to fill it with the frequency result


    subbandhistoric(&FFTvector);//this function will fill and refresh a historic of frequency subband (frequency gathered with some criteria)


    frequencybinmean();//this function return us a vector compound of the mean of each subband inside the subband historic


    frequencyvariance();//this function return us a vector compound of the variance for each subband inside the subband historic

    for (int i=0; i<get_numberofbin(); i++)// Here we check each subbands
    {

        if ( get_subbandvalue( get_Indexnumber(),i)>(get_meanvalue(i) *get_meanthreshold()) && get_variancevalue(i)>get_variancethreshold())//for each subband we verify if our news subband value have peticular caracteristique when compare to the mean and the variance
        {
            ispulse=1;
            break;//is there is a pulse no need to check further
        }

    }

    set_Indexnumber(get_Indexnumber()+1);// We keep an eye on the index

    if (get_Indexnumber()==numberofbufferkept) //if the index is greater than the size of our subband historic we put it a zero
    {
        set_Indexnumber(0);
    }

    return ispulse;//return the result as a boolean

}



/*/////////////////////////////////////////////////////////////////////////////////////////////////
This function regroup frequency in kind of logarithmic way to take into account that we have frequency
between 0 and ~10000 Hz while musique is generally below 5000 Hz (~ Highest note on a piano) (and
so they re more important)
To do so we will regroup frequency until 5000 hertz by group of 2^2 frequency then to continue as follow :
2^3,2^3,2^4,2^5 ....  (we have two 2^3 as 2^n=(2^n-1)+(2^n-1))
It also calculate a quick magnitude (sum of absolute)
/////////////////////////////////////////////////////////////////////////////////////////////////*/

void mathrythm::subbandlogdivision( vector<float>* vec, vector<complex<float> >* FFTvector)
{

    int counter=0;//a stupid counter
    int logpower=3;//above ~5000 Hz we will start to regroup 2^logpower frequency together(the point is to regroup more and more frequency with a 2^n+3 progression at each iteration)

    complex<float> complexnumber;//temporary complex number

    float temporarynumber=0;//temporary number

    for (uint i=0; i<FFTvector->size()/2; i++) //We take half of our frequency (as our FFT is mirrored we don't care about the other half)
    {

        if (i<(FFTvector->size()/4))
        {

            complexnumber=FFTvector->at(i);//get the Frequency value at i

            temporarynumber=temporarynumber+abs(complexnumber.real())+abs(complexnumber.imag());//extract a quick magnitude from the frequency;

            counter=counter+1;

            if (counter==4) //each 2^2 frequency value addition, store the value inside an vector
            {

                vec->push_back(temporarynumber) ; //add the frequncy bin to a vector pass by another function

                counter=0;//set a 0 for the next loop
                temporarynumber=0;//set a 0 for the next loop
            }

        }

        else if(i==FFTvector->size()/4) //here the first 2^3
        {

            complexnumber=FFTvector->at(i);

            temporarynumber=temporarynumber+abs(complexnumber.real())+abs(complexnumber.imag());//

            counter=counter+1;


            if (counter==pow(2,logpower)) //at 2^3 ....
            {

                vec->push_back(temporarynumber) ;

                counter=0;
                temporarynumber=0;
            }



        }


        else //here a progression from 2^3 to 2^x
        {
            counter=counter+1;

            complexnumber=FFTvector->at(i);

            temporarynumber=temporarynumber+abs(complexnumber.real())+abs(complexnumber.imag());//+abs(FFTvector->real());

            if (counter==pow(2,logpower))//when 2^n frequency are add ....
            {

                vec->push_back(temporarynumber) ;

                counter=0;
                temporarynumber=0;
                logpower=logpower+1;//at each operation we increase the power of 2
            }
        }
    }
}


/*/////////////////////////////////////////////////////////////////////////////////////////////////
This function divide the frequency into equally large band of value
/////////////////////////////////////////////////////////////////////////////////////////////////*/
void mathrythm::historicdivision(vector<complex<float> >* FFTvector)
{

    vector<complex <float> >  vec;

    complex<float> complexnumber;//temporary complex number

    for (int j=0;j<2;j++){

        for (uint i=0+j*(FFTvector->size()/2); i<FFTvector->size()/2+j*(FFTvector->size()/2); i++) //We take cut our frequency in half
        {   
            vec.push_back(FFTvector->at(i)) ;
        }

        edit_complexsubbandhistoric((j),vec);
    }
}


/*/////////////////////////////////////////////////////////////////////////////////////////////////
This function simply calculate a mean
/////////////////////////////////////////////////////////////////////////////////////////////////*/

void mathrythm::frequencybinmean()
{
    float temporarynumber=0;//This temporary value will hold the sum wich is needed for the mean
    set_sizemeanvaluevector(get_numberofbin()); //set the size of the vector wich will store the mean value for each calculate log frequency subband

    for (int i=0; i<get_numberofbin(); i++)
    {
        for (int j=0; j<getsize_Subbandhistoric(); j++)
        {

            temporarynumber=temporarynumber+get_subbandvalue(j,i); // Addition of all the stored value for the j log subband

        }
        set_meanvalue(i,temporarynumber/getsize_Subbandhistoric()); //result divid by the number of element to  get the mean the store inside a vector at index i
        temporarynumber=0;//reset of the mean varaible

    }
}


/*/////////////////////////////////////////////////////////////////////////////////////////////////
This function simply calculate a variance (for working details see the mean as they have the same internal construction)
/////////////////////////////////////////////////////////////////////////////////////////////////*/

void mathrythm::frequencyvariance()
{

    float temporarynumber=0;
    set_sizevariancevaluevector(get_numberofbin());

    for (int i=0; i<get_numberofbin(); i++)
    {
        for (int j=0; j<getsize_Subbandhistoric(); j++)
        {

            temporarynumber=temporarynumber+abs(get_subbandvalue(j,i)-get_meanvalue(i)); //variance calculus

        }
        set_variancevalue(i,temporarynumber/getsize_Subbandhistoric());
        temporarynumber=0;
    }
}


/*/////////////////////////////////////////////////////////////////////////////////////////////////
This function call take roughly 5.9 s of the song in is middle then apply a convolution with different combfilter to see
wich correspond the most
/////////////////////////////////////////////////////////////////////////////////////////////////*/
int mathrythm::getsongbpm(){
    Audioclass audio;

    Phonon::MediaObject media;
    vector< complex<float> > store;


    qDebug()<<"Wait ...";
    emit loadingvaluechanged(1);//advancement

    audio.Bigdataget(131072*2+1,&media,&store); //taking roughly 5.9s of song in the middle

    emit loadingvaluechanged(50);//advancement

    fftmath fft;
    fft.derivatehamming(store.size()-1,&store);//FFT it with a derivative

    historicdivision(&store);//Divide into different subband

    emit loadingvaluechanged(52);

    bpmtest(60,200,10);//convolutionne the comb filter and the signal by multiplying their fft

    double temporary=0;
    double totalweight=0;

    pair<int,double> bpmandweight;

    //this for loop calculate the barycenter
    for (uint i=0;i<bpmandweighthistoric.size();i++){
        bpmandweight=bpmandweighthistoric.at(i);
        temporary=temporary+(bpmandweight.first*bpmandweight.second);
        totalweight=totalweight+bpmandweight.second;
    }

    qDebug()<<"The bpm is : " <<temporary/totalweight;
    return (temporary/totalweight);
}


/*/////////////////////////////////////////////////////////////////////////////////////////////////
This function take care of keeping an historic of logarithmcaly regrouped frequency
/////////////////////////////////////////////////////////////////////////////////////////////////*/


void mathrythm::subbandhistoric(vector<complex<float> >* FFTvector)
{

    vector<float> vec; // create a vector to be passed inside the log function


    subbandlogdivision(&vec,FFTvector); //regroup logarithmicaly the frequencies

    set_numberofbin(vec.size()); //look and store for later computation how much frequency group the log function created

    edit_subbandhistoric(get_Indexnumber(),vec);// Add the vec to a map with Index number as the key. The addition is done by swapping wich is done by reference and so is fast

}


/*/////////////////////////////////////////////////////////////////////////////////////////////////
This function create a combfilter corresponding to a given bpm .
This combfilter is then passed into the frequency domain.
/////////////////////////////////////////////////////////////////////////////////////////////////*/
void mathrythm::impulsesignal(int bpm){

    int samplefrequency=44100;//the sample frequency of the sound
    int Ti=samplefrequency*60/bpm ;//Ti is how many dirak should compoud the dirack comb

    vector <float> size;
    complex <float> dirac;
    dirac.real(1);//create a dirak pic

    vector<complex<float> >  vec(262144,262144); //create a vector full a 0

    for (int i=0;i<4;i++){ //create the comb by adding dirak inside the 0 vector

        vec.at(i*Ti)=dirac;

    }

    fftmath fft;
    fft.hamming(vec.size(),&vec);//pass the comb filter inside frequency domain

    combfilter[bpm].swap(vec) ;//add the combfilter into a map

}


/*/////////////////////////////////////////////////////////////////////////////////////////////////
Compare each comb filter with each subband and store the best correspondance
/////////////////////////////////////////////////////////////////////////////////////////////////*/
void mathrythm::bpmtest(const int &infvalue,const int &maxvalue,const int &step){

    vector<complex <float> >  vec;
    int bpm;
    double temporarynumber;

    for (int bpm=infvalue;bpm<=maxvalue;){ //for each bpm create the combfilter

        impulsesignal(bpm);

        bpm=bpm+step;

    }

    for (int i=0;i<getsize_complexSubbandhistoric();i++){ //for each subband

        int loadingvalue=i/(getsize_Subbandhistoric()-1)*0.48;
        emit loadingvaluechanged(52+loadingvalue);

        vec=is_complexsubbandhistoric.at(i);

        bpmandweight.second=0;

        for (bpm=infvalue;bpm<=maxvalue;){ //pass the combfilter for each bpm on the subband

            temporarynumber=0;

            for (uint j=0;j<vec.size();j++){  //convolution the comb filter and the audio signal
                complex<float> num=abs(vec.at(j))*abs(combfilter[bpm].at(j));
                temporarynumber=temporarynumber+(num.real()+num.imag());
            }

            if (bpmandweight.second<temporarynumber){ //if the multiplication between the comb filter and the subband is greater than a previous one keep that value
                bpmandweight.first=bpm;bpmandweight.second=temporarynumber;
            }
            bpm=bpm+step;
        }

        bpmandweighthistoric.push_back(bpmandweight);//add the best bpm and is "weight" to a vector of pair for latter computation

    }

}
