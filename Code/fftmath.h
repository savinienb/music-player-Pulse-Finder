#ifndef FFTMATH_H
#define FFTMATH_H
#include <complex>
#include <vector>
#include <phonon/AudioDataOutput>
#include <iostream>
using namespace std;


class fftmath
{
public:
    fftmath() ;
    ~fftmath() {}

    //return the value of the FFT for a given index
    complex<float> get_FFTvectorvalue (int row)const{return FFTvector->at(row) ;}

    //return the value at a given row of a precacultate twiddle exponential
    complex<float> get_Twiddlearrayvalue(int row)const{return *(is_twiddlearraypointer+row);}

    //return the size of the FFT
    int get_Size()const{return is_size;}

    //call a function to check,create and set(apply an hamming windowing) the element needed for the fft
    bool hamming(const int &size, QMap<Phonon::AudioDataOutput::Channel, QVector<qint16> >  m_audiodata,vector<complex<float> > * pointer);
    bool hamming(const int &size,vector<complex<float> > * pointer);

    //call a function to check,create and set(apply an hamming windowing and a derivation on the input data) the element needed for the fft
    bool derivatehamming(const int &size, QMap<Phonon::AudioDataOutput::Channel, QVector<qint16> >m_audiodata,vector<complex<float> > * pointer);

    bool derivatehamming(const int &size,vector<complex<float> > * pointer);

private:


    int is_size;
    complex<float>* is_twiddlearraypointer;
    vector<complex<float> > *FFTvector;

    //divide and conquer function
    void Cut(const int &N,const int &n);

    //math applied during the divide and conquer
    void FFT(const int &N,const int &n);

    //set the number of data process at once
    void set_Size ( const int& size ) {is_size = size;}



    bool iffthamming(const int &size,vector<complex<float> > * pointer);

    //set the value inside the vector
    void set_FFTvectorvalue (int row , complex<float> value){FFTvector->at(row)=value ;}

    //set the precalculate exponantial array value inside the vector
    void set_Twiddlearrayvalue(int row,complex<float> value){*(is_twiddlearraypointer+row)=value;}

    //Get a pointer to an array and store it
    void set_Twiddlearraypointer ( complex<float>* twiddlearray ){is_twiddlearraypointer=twiddlearray;}


};

#endif // FFTMATH_H
