//Jakub Robak
//#include "source.cpp"
#include <iostream>
#include <cmath>
using namespace std;

double wyznaczMiejsceZerowe(double(*f)(double),double a, double b, int M, double eps, double delta)
{
    int i=0;
    double c=a;
    double fa=f(a);
    double fb=f(b);
    double fc=fa;
    int new_M =M;
    new_M=new_M-2;
    bool czy_byla_bisekcja=false;

    for(i;i<M;i++)
    {
        if(new_M==0)
            return c;
        if(abs(fa)<eps)
            return a;
        if(abs(fb)<eps)
            return b;
        if(abs((a-b)/2)<delta)
            return abs((a-b)/2);

        // cout<<"a="<<a<<" b="<<b<<endl;
        if(fa*fb<=0&&abs((a-b))>0.04) //robimy metodÄ bisekcji
        {
            czy_byla_bisekcja=true;
            // cout<<"bisekcja m="<<i<<endl;
            c=(a+b)/2;
            fc=f(c);
            new_M--;
            if(abs((a-b)/2)<delta||abs(fc)<eps)
                return c;
            if(fc*fa<0)
            {
                b=c;
                fb=fc;
            }
            else
            {
                a=c;
                fa=fc;
            }
            //  cout<<"abs((a-b))="<<abs((a-b))<<endl;
//cout<<"c="<<c<<endl;
        }
        else
        {
            sieczne:
            if(new_M==0)
                return c;
            // cout<<"sieczne m="<<i<<endl;
            c=b-(fb*(b-a))/(fb-fa);
            fc= f(c);
            new_M--;
            // cout<<"fc = "<<fc<<endl;
            if(abs(fc)<eps||abs(b-c)<delta||abs(a-c)<delta)
            {
                // cout<<"tutaj"<<endl;
                return c;
            }

            else
            {
                a=b;
                fa=fb;
                b=c;
                fb=fc;
            }
           if(czy_byla_bisekcja)
               goto sieczne;

        }
    }

//cout<<"m="<<i<<endl;

//cout<<"nie udaĹo siÄ"<<endl;
    return c;
}

