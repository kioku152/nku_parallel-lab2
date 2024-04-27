#include <iostream>
#include <xmmintrin.h>
#include <windows.h>

using namespace std;

const int n = 1000;

float run(){
    long long head, tail, freq;


    static float A[n][n];
    static float B[n];
    static float X[n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            A[i][j] = 0;
    }
    for (int i = 0; i < n; i++)
    {
        B[i] = 1.0;
        A[i][i] = 1.0;
        for (int j = i + 1; j < n; j++)
        {
            A[i][j] = (rand() % 100) - 50;
            B[i] += A[i][j];
        }
    }
    for(int k=0;k<n;k++)
        for(int i=k+1;i<n;i++)
            {
                for(int j=0;j<n;j++)
                    A[i][j]+=A[k][j];
                B[i]+=B[k];
            }



    QueryPerformanceFrequency((LARGE_INTEGER *)&freq);
    QueryPerformanceCounter((LARGE_INTEGER *)&head);


    for (int k = 0; k < n; k++)
    {
        for (int i = k + 1; i < n; i++)
        {
            for (int j = 0; j < n; j += 4)
            {
                __m128 Aik = _mm_loadu_ps(&A[i][j]);
                __m128 Akj = _mm_loadu_ps(&A[k][j]);
                __m128 factor_ = _mm_div_ps(Aik, _mm_set1_ps(A[k][k]));


                Aik = _mm_sub_ps(Aik, _mm_mul_ps(factor_, Akj));
                _mm_storeu_ps(&A[i][j], Aik);


            }
            float factor = A[i][k]/A[k][k];
            B[i] -= factor * B[k];
        }
    }

    X[n - 1] = B[n - 1] / A[n - 1][n - 1];
    for (int i = n - 2; i >= 0; i--)
    {
        __m128 sum_ = _mm_set1_ps(B[i]);
        for (int j = i + 1; j < n; j += 4)
        {
            __m128 Xj = _mm_loadu_ps(&X[j]);
            __m128 Aj = _mm_loadu_ps(&A[i][j]);
            sum_ = _mm_sub_ps(sum_, _mm_mul_ps(Aj, Xj));
        }
        float sum = sum_[0] + sum_[1]+sum_[2] + sum_[3];
        X[i] = sum / A[i][i];
    }

    QueryPerformanceCounter((LARGE_INTEGER *)&tail);

    /*for (int i = 0; i < n; i++)
        cout << X[i] << endl;*/

    //cout << (tail - head) * 1000.0 / freq << "ms" << endl;

    float answer=(float)((tail - head) * 1000.0 / freq);
    return answer ;
}

int main()
{
    float time_sum;
    int count1=0;

    while(count1<20)
    {
        count1+=1;
        time_sum+=run();
    }

    cout<<time_sum/20.0<<endl;


    return 0;
}
