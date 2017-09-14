#include "fftmath.h"
#include <phonon/AudioDataOutput>
#include <complex>


/*/////////////////////////////////////////////////////////////////////////////////////////////////
This class is a Cooley/Tukey FFT algorithm with radix 2 incorporating some improvement :
-Precalculated Twiddle exponantial
-All the work is made on the original array (no thousand of temporary array around)

It's also include feature :
-Hamming windowing
-input derivation

If you re not familiar with Cooley/Tukey FFT and want to understand this code I suggest you to go to :

/////////////////////////////////////////////////////////////////////////////////////////////////*/



fftmath::fftmath()
{
}



/*/////////////////////////////////////////////////////////////////////////////////////////////////
Those function :
-check if the FFT size is good (must be 2^n as it's a radix 2 algorithm.)
-create an array of twiddle precalculate exponential (to avoid to calculate them at each iteration of my divide and conquer)
-fill the FFTvector with Hamming windowed audiodata or use a already filled vector
/////////////////////////////////////////////////////////////////////////////////////////////////*/

bool fftmath::hamming(const int &size, QMap<Phonon::AudioDataOutput::Channel, QVector<qint16> >  m_audiodata,vector<complex<float> > * pointer)
{
    int a=log2(size);
    float b=log2(size);
    //check if the size is under the form (2^n) and return false if not
    if (a!=b){
        cout<<"the FFT size must be under the form 2^n"<<endl;
        return false;
    }

    else{

       static const float pi=3.141592653589793238460;

        //create an imaginary number 0+i*1
       static const complex<int> ij(0, 1);

        set_Size(size);

        //create an array of precalculated twiddle exponantial for later processing (an array is slightly faster than a vector)
        complex<float> twiddlearray[get_Size()/2];

        //store a pointer to the first member of the array for latter acess from another function
        set_Twiddlearraypointer(&twiddlearray[0]);

        //Create a temporary number to store calculate the twiddle exponantial value
        complex<float> temporarynumber;

        //A temporary complex number for later Hamming Windowing
        complex<float> hammingwindowing;

        //Calculate all the value for the twiddle exponantial array
        for ( int i=0 ; i < (get_Size()/2); i++)
        {
            temporarynumber.real( cos( pi * (-2) * (i) / get_Size() ));
            temporarynumber.imag( sin( pi * (-2) * (i) / get_Size() ));
            set_Twiddlearrayvalue( i , temporarynumber );
        }

        //Set the FFTvector pointer to the vector pointer pass a a function variable so the FFT variable can be accesible outside of the class with the passed vector pointer
        FFTvector=pointer;

        //Set the size of FFT vector to his final size
        FFTvector->resize(get_Size());

        //For all the value from 0 to the size of the FFT we will set the FFT value
        for (int i=0; i<get_Size(); i++ )
        {

            //As music sound are in stereo (2 stream) we store one stream as the real part of a complex number and the other one as the imaginary part of the complex number
            temporarynumber.real( m_audiodata[Phonon::AudioDataOutput::LeftChannel][i]);
            temporarynumber.imag(  m_audiodata[Phonon::AudioDataOutput::RightChannel][i]);

            //Here we apply a Hamming windowing to our data to get a better result as the FFT output
            hammingwindowing.real(0.53836-(0.46164*cos( 2 * pi * i /get_Size() ))*(temporarynumber.real()));
            hammingwindowing.imag(0.53836-(0.46164*cos( 2 * pi * i /get_Size() ))*(temporarynumber.imag()));

            //We store the value into the vector at the case i
            set_FFTvectorvalue(i ,hammingwindowing);
        }

        //Call the FFT Cooley/Tukey algorythm
        FFT(get_Size(),0);
        return true;

    }
}

bool fftmath::hamming(const int &size,vector<complex<float> > * pointer)
{
    int a=log2(size);
    float b=log2(size);
    //check if the size is under the form (2^n) and return false if not
    if (a!=b){
        cout<<"the FFT size must be under the form 2^n"<<endl;
        return false;
    }

    else{


      static  const float pi=3.141592653589793238460;

        //create an imaginary number 0+i*1
        static const complex<int> ij(0, 1);

        set_Size(size);

        //create an array of precalculated twiddle exponantial for later processing (an array is slightly faster than a vector)
        complex<float> twiddlearray[get_Size()/2];

        //store a pointer to the first member of the array for latter acess from another function
        set_Twiddlearraypointer(&twiddlearray[0]);

        //Create a temporary number to store calculate the twiddle exponantial value
        complex<float> temporarynumber;

        //A temporary complex number for later Hamming Windowing
        complex<float> hammingwindowing;

        //Calculate all the value for the twiddle exponantial array
        for ( int i=0 ; i < (get_Size()/2); i++)
        {
            temporarynumber.real( cos( pi * (-2) * (i) / get_Size() ));
            temporarynumber.imag( sin( pi * (-2) * (i) / get_Size() ));
            set_Twiddlearrayvalue( i , temporarynumber );
        }

        //Set the FFTvector pointer to the vector pointer pass a a function variable so the FFT variable can be accesible outside of the class with the passed vector pointer
        FFTvector=pointer;

        //Set the size of FFT vector to his final size
        FFTvector->resize(get_Size());

        //For all the value from 0 to the size of the FFT we will set the FFT value
        for (int i=0; i<get_Size(); i++ )
        {

            //As music sound are in stereo (2 stream) we store one stream as the real part of a complex number and the other one as the imaginary part of the complex number


            temporarynumber=get_FFTvectorvalue(i);

            //Here we apply a Hamming windowing to our data to get a better result as the FFT output
            hammingwindowing.real(0.53836-(0.46164*cos( 2 * pi * i /get_Size() ))*(temporarynumber.real()));
            hammingwindowing.imag(0.53836-(0.46164*cos( 2 * pi * i /get_Size() ))*(temporarynumber.imag()));

            //We store the value into the vector at the case i
            set_FFTvectorvalue(i ,hammingwindowing);
        }

        //Call the FFT Cooley/Tukey algorythm
        FFT(get_Size(),0);
        return true;

    }
}






/*/////////////////////////////////////////////////////////////////////////////////////////////////
This function :
-check if the FFT size is good (must be 2^n as it's a radix 2 algorithm.)
-create an array of twiddle precalculate exponential (to avoid to calculate them at each iteration of my divide and conquer)
-fill the FFTvector with Hamming windowed audiodata
/////////////////////////////////////////////////////////////////////////////////////////////////*/

bool fftmath::derivatehamming(const int &size, QMap<Phonon::AudioDataOutput::Channel, QVector<qint16> >  m_audiodata,vector<complex<float> > * pointer)
{

    int a=log2(size);
    float b=log2(size);
    //check if the size is under the form (2^n) and return false if not
    if (a!=b){
        cout<<"the FFT size must be under the form 2^n"<<endl;
        return false;
    }

    else{


       static const float pi=3.141592653589793238460;

        //create an imaginary number 0+i*1
       static const complex<int> ij(0, 1);

        set_Size(size);

        //create an array of precalculated twiddle exponantial for later processing (an array is slightly faster than a vector)
        complex<float> twiddlearray[get_Size()/2];

        //store a pointer to the first member of the array for latter acess from another function
        set_Twiddlearraypointer(&twiddlearray[0]);

        //Create a temporary number to store calculate the twiddle exponantial value
        complex<float> temporarynumber;

        //A temporary complex number for later Hamming Windowing
        complex<float> hammingwindowing;

        //Calculate all the value for the twiddle exponantial array
        for ( int i=0 ; i < (get_Size()/2); i++)
        {
            temporarynumber.real( cos( pi * (-2) * (i) / get_Size() ));
            temporarynumber.imag( sin( pi * (-2) * (i) / get_Size() ));
            set_Twiddlearrayvalue( i , temporarynumber );
        }

        //Set the FFTvector pointer to the vector pointer pass a a function variable so the FFT variable can be accesible outside of the class with the passed vector pointer
        FFTvector=pointer;

        //Set the size of FFT vector to his final size
        FFTvector->resize(get_Size());

        //For all the value from 0 to the size of the FFT we will set the FFT value
        for (int i=0; i<get_Size(); i++ )
        {


            complex<float>  temporarynumber2;
            temporarynumber.real( m_audiodata[Phonon::AudioDataOutput::LeftChannel][i+1]);
            temporarynumber.imag(  m_audiodata[Phonon::AudioDataOutput::RightChannel][i+1]);




            temporarynumber.real( m_audiodata[Phonon::AudioDataOutput::LeftChannel][i]);
            temporarynumber.imag(  m_audiodata[Phonon::AudioDataOutput::RightChannel][i]);



            temporarynumber.real(temporarynumber2.real()- temporarynumber.real());

            temporarynumber.imag(temporarynumber2.imag()-temporarynumber.imag());


            //Here we apply a Hamming windowing to our data to get a better result as the FFT output
            hammingwindowing.real(0.53836-(0.46164*cos( 2 * pi * i /get_Size() ))*(temporarynumber.real()));
            hammingwindowing.imag(0.53836-(0.46164*cos( 2 * pi * i /get_Size() ))*(temporarynumber.imag()));

            //We store the value into the vector at the case i
            set_FFTvectorvalue(i ,hammingwindowing);
        }

        //Call the FFT Cooley/Tukey algorythm
        FFT(get_Size(),0);


        return true;


    }
}

bool fftmath::derivatehamming(const int &size,vector<complex<float> > * pointer)
{

    int a=log2(size);
    float b=log2(size);
    //check if the size is under the form (2^n) and return false if not
    if (a!=b){
        cout<<"the FFT size must be under the form 2^n"<<endl;
        return false;
    }
    else{

      static  const float pi=3.141592653589793238460;

        //create an imaginary number 0+i*1
        static const complex<int> ij(0, 1);

        set_Size(size);

        //create an array of precalculated twiddle exponantial for later processing (an array is slightly faster than a vector)
        complex<float> twiddlearray[get_Size()/2];

        //store a pointer to the first member of the array for latter acess from another function
        set_Twiddlearraypointer(&twiddlearray[0]);

        //Create a temporary number to store calculate the twiddle exponantial value
        complex<float> temporarynumber;

        //A temporary complex number for later Hamming Windowing
        complex<float> hammingwindowing;

        //Calculate all the value for the twiddle exponantial array
        for ( int i=0 ; i < (get_Size()/2); i++)
        {
            temporarynumber.real( cos( pi * (-2) * (i) / get_Size() ));
            temporarynumber.imag( sin( pi * (-2) * (i) / get_Size() ));
            set_Twiddlearrayvalue( i , temporarynumber );
        }

        //Set the FFTvector pointer to the vector pointer pass a a function variable so the FFT variable can be accesible outside of the class with the passed vector pointer
        FFTvector=pointer;

        //For all the value from 0 to the size of the FFT we will set the FFT value
        for (int i=0; i<get_Size(); i++ )
        {

            complex<float>  temporarynumber2= get_FFTvectorvalue(i+1);

            temporarynumber=get_FFTvectorvalue(i);

            temporarynumber.real(temporarynumber2.real()- temporarynumber.real());

            temporarynumber.imag(temporarynumber2.imag()-temporarynumber.imag());

            //Here we apply a Hamming windowing to our data to get a better result as the FFT output
            hammingwindowing.real(0.53836-(0.46164*cos( 2 * pi * i /get_Size() ))*(temporarynumber.real()));
            hammingwindowing.imag(0.53836-(0.46164*cos( 2 * pi * i /get_Size() ))*(temporarynumber.imag()));

            //We store the value into the vector at the case i
            set_FFTvectorvalue(i ,hammingwindowing);
        }

        //Call the FFT Cooley/Tukey algorythm
        FFT(get_Size(),0);
        return true;

    }
}

/*/////////////////////////////////////////////////////////////////////////////////////////////////
This function Divide and Conquer by sorting even indexes element together and odd indexes element together.
This funtion Divide and Conquer while always working on the input array (if you stop the algorithm at different
moment you will see different order inside the initial array
/////////////////////////////////////////////////////////////////////////////////////////////////*/

void fftmath::Cut(const int &N, const int& n)  //N is the size of the array to work on and n is a factor to find the index of the first element of the array that we work on (we cut our initial array to extract a temporary array,work on it and inject it back)
{
    {
        if (N>=2) // No need to divide and conquer an array of size 1
        {
            //We create two temporarys arrays
            complex<float> copy[N/2];
            complex<float> temp[N];

            //j will be the index of the array where we will put each element, it will increase a each copy
            int j=0;

            for (int k = 0+(n*(N/2)); k < (N+n*N/2) ; k++)
            {
                temp[j]=get_FFTvectorvalue(k);//copy the a part of the array to divide and conquer on it
                j=j+1;
            }
            for (int k=(0); k<=(N-1)/2; k++)
            {
                copy[k]=temp[k*2+1];//copy the odd index out of the array
                temp[k]=temp[2*k];//move the even index in the second half of the array
            }
            for (int k=1; k<=((N-1)/2+1); k++)
            {
                temp[k+(N-1)/2]=copy[k-1];//Copy the odd array back into the array in is first half
            }

            j=0;//set j at 0 to use it as an index again
            for (int k=0+(n*(N/2)); k<(N+n*N/2); k++)
            {
                set_FFTvectorvalue(k,temp[j]);//copy back the temporary array sorted by odd/even into the initial array
                j=j+1;
            }
        }
    }
    FFTvector->resize(get_Size());
}



/*/////////////////////////////////////////////////////////////////////////////////////////////////
This function is a recursive FFT function wich will build a divide and conquer tree and apply an
mathematical operation at each node in order to transform data from time domain to frequency
/////////////////////////////////////////////////////////////////////////////////////////////////*/

void fftmath::FFT(const int &N, const int &n)  //recursive fft
{
    if(N<=1)//at the bottom of the tree do nothing
    {
        return;
    }

    else
    {
        Cut(N,n);//Sort array numbers by odd and even

        FFT( N/2 , n*2 );//first half of the array numbers fft
        FFT( N/2 , (n+1)*2 ); //second half of the array fft


      static  const complex<float> j( 0 , 1 ); //complex number (0+i*1)
        int g = 0;//this variable is useful to navigate inside the precalculate twiddle exponantial

        for (int k = 0+(n*(N/2)) ; k < n*N/2+N/2 ; k++ ) //select a portion of the array
        {
            complex<float> comp= get_Twiddlearrayvalue(g)  *  (get_FFTvectorvalue(k+N/2)); //multiply the precalculate twiddle exponantial with an FFTvector value to get the Twiddle number (see wikipedia)

            g=g+(get_Size())/(N); //We dont navigate the same is the precalculate twiddle exponantial depending of the size of the array

            complex<float> v=(get_FFTvectorvalue(k)); //Get the FFTvector at k
            set_FFTvectorvalue(k,v+comp) ;            //Calculate and set the new value at k
            set_FFTvectorvalue(k+N/2,v-comp);         //Calculate and set the new value at k+N/2 (half a array away)
        }
    }
}


/*/////////////////////////////////////////////////////////////////////////////////////////////////
Work the same as the FFT but without a minus in the exponantial
/////////////////////////////////////////////////////////////////////////////////////////////////*/

bool fftmath::iffthamming(const int &size,vector<complex<float> > * pointer)
{

    //check if the size is under the form (2^n) and return false if not
    float b=log2(pointer->size());
    int a=log2(pointer->size());
    if (a!=b){
        cout<<"the FFT size must be under the form 2^n"<<endl;
        return false;
    }

    else{


       static const float pi=3.141592653589793238460;

        //create an imaginary number 0+i*1
       static const complex<int> ij(0, 1);

        set_Size(size);

        //create an array of precalculated twiddle exponantial for later processing (an array is slightly faster than a vector)
        complex<float> twiddlearray[get_Size()/2];

        //store a pointer to the first member of the array for latter acess from another function
        set_Twiddlearraypointer(&twiddlearray[0]);

        //Create a temporary number to store calculate the twiddle exponantial value
        complex<float> temporarynumber;

        //A temporary complex number for later Hamming Windowing
        complex<float> antihammingwindowing;

        //Calculate all the value for the twiddle exponantial array
        for ( int i=0 ; i < (get_Size()/2); i++)
        {
            temporarynumber.real( cos( pi * (2) * (i) / get_Size() ));
            temporarynumber.imag( sin( pi * (2) * (i) / get_Size() ));
            set_Twiddlearrayvalue( i , temporarynumber );
        }

        //Set the FFTvector pointer to the vector pointer pass a a function variable so the FFT variable can be accesible outside of the class with the passed vector pointer
        FFTvector=pointer;

        //Set the size of FFT vector to his final size
        FFTvector->resize(get_Size());

        //Call the IFFT algorythm
        FFT(get_Size(),0);

        //For all the value from 0 to the size of the FFT we will set the FFT value
        for (int i=0; i<get_Size(); i++ )
        {

            //AntiHamming windowing
            antihammingwindowing.real((temporarynumber.real()/get_Size())/0.53836-(0.46164*cos( 2 * pi * i /get_Size())));
            antihammingwindowing.imag((temporarynumber.imag()/get_Size())/0.53836-(0.46164*cos( 2 * pi * i /get_Size() )));

            set_FFTvectorvalue(i ,get_FFTvectorvalue(i));

        }

        return true;

    }
}

