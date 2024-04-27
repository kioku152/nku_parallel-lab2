#include <iostream>
#include<windows.h>


using namespace std;

const int n=100;

float run(){
    long long head, tail, freq;


    static float A[n][n];
    static float B[n];
    static float X[n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            A[i][j]=0;
    }
    for(int i=0;i<n;i++)
    {
        B[i]=1.0;
        A[i][i]=1.0;
        for(int j=i+1;j<n;j++)
            {
                A[i][j]= (rand() % 100)-50;
                B[i]+=A[i][j];
            }
    }

    for(int k=0;k<n;k++)
        for(int i=k+1;i<n;i++)
            {
                for(int j=0;j<n;j++)
                    A[i][j]+=A[k][j];
                B[i]+=B[k];
            }




    QueryPerformanceFrequency((LARGE_INTEGER*)&freq);

    QueryPerformanceCounter((LARGE_INTEGER*)&head);

    for(int k=0;k<n;k++)
    {
        for(int i=k+1;i<n;i++)
        {
            float factor=A[i][k]/A[k][k];
            for(int j=k+1;j<n;j++)
                A[i][j]=A[i][j]-factor*A[k][j];
            B[i]=B[i]-factor*B[k];

        }

    }




    X[n-1]=B[n-1]/A[n-1][n-1];
    for(int i=n-2;i>-1;i--)
    {
        float sum=B[i];
        for(int j=i+1;j<n;j++)
            sum=sum-A[i][j]*X[j];
        X[i]=sum/A[i][i];


    }


    QueryPerformanceCounter((LARGE_INTEGER*)&tail);
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
