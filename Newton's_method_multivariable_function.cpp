//Jakub Robak
#include <iostream>
#include <cmath>
#include <stdio.h>
using namespace std;

typedef void (*FuncPointer)(const double* x, double* y, double* Df);
void printVector(const double* x, unsigned N){
    for(unsigned i=0;i<N;++i)
        printf("%17.17f ",x[i]);
    printf("\n");
}

  //----------------------------1-------------------------------
void Newton_Method(double *y, double *Df, double *x)
{
    //cout<<"początek    ";
    // cout<<"df0 = "<<Df[0]<<"      Df4 = "<<Df[4]<<endl;
    double det=0;
    det= (Df[0]*Df[4])-(Df[3]*Df[1]);
    swap(Df[0],Df[4]);
    //  cout<<"df0 = "<<Df[0]<<"      Df4 = "<<Df[4]<<endl;
    Df[1]=-Df[1]*(1/det);
    Df[0]=Df[0]*(1/det);
    Df[3]=-Df[3]*(1/det);
    Df[4]=Df[4]*(1/det);
    double w1= (Df[0]*y[0])+(Df[1]*y[1]);
    double w2= (Df[3]*y[0])+(Df[4]*y[1]);

    x[0]=x[0]-w1;
    x[1]=x[1]-w2;
    // cout<<"koniec      ";
    // cout<<"x0 = "<<x[0]<<"      x1 = "<<x[1]<<endl;
}

void implicitCurve(const double* x, double* y, double* Df){
    // funkcja dana jest wzorem f(a,b,c) = (1-a^2-b^2-c^2, <---1 funkcja
    // (a+b+c)/(a^2+b^2+c^2)-1) <--- 2 funkcja
    // zmienne pomocnicze
    const double n = x[0]*x[0] + x[1]*x[1] + x[2]*x[2];
    const double s = x[0] + x[1] + x[2];

    // obliczam wartosc funkcji
    y[0] = 1. - n;
    y[1] = s/n - 1.;

    //obliczam pierwszy wiersz macierzy
    Df[0] = -2.*x[0];
    Df[1] = -2.*x[1];
    Df[2] = -2.*x[2];

    //obliczam drugi wiersz macierzy
    const double r = 1./n;
    const double r2 = 2.*y[1]*r;
    Df[3] = r - x[0]*r2;
    Df[4] = r - x[1]*r2;
    Df[5] = r - x[2]*r2;
}

int findCurve(FuncPointer f, double* x, unsigned k, double h)
{
    double y[2];
    double Df[sizeof(y)* sizeof(x)];

    for(int i=1;i<=k;i++)
    {

        x[2]+=h;
        f ( x,y,Df);

        double prev = max(abs(y[0]),abs(y[1]))*999999999999999;
        while(max(abs(y[0]),abs(y[1]))>1e-14)
        {

            if(prev*10<max(abs(y[0]),abs(y[1])))
                return i;
            else
                prev= max(abs(y[0]),abs(y[1]));
            Newton_Method(y,Df,x);
            f ( x,y,Df);
        }
        printVector(x,3);

    }
    return 0;

    // f ( x,y,Df);    //mamy liczby
    //printVector(Df,6);
    //return 0;
}

//----------------------------1-------------------------------
//----------------------------2-------------------------------

void implicitSurface(const double* x, double* y, double* Df){
    // funkcja dana jest wzorem f(a,b,c) = (a+b+c)/(a^2+b^2+c^2)-1
    // zmienne pomocnicze
    const double n = x[0]*x[0] + x[1]*x[1] + x[2]*x[2];
    const double s = x[0] + x[1] + x[2];

    // obliczam wartosc funkcji
    *y = s/n - 1.;
    //obliczam pierwszy i jedyny wiersz macierzy
    const double r = 1./n;
    const double r2 = 2.*(*y)*r;
    Df[0] = r - x[0]*r2;
    Df[1] = r - x[1]*r2;
    Df[2] = r - x[2]*r2;
}
int findSurface(FuncPointer f, double* x, unsigned k1, unsigned k2, double h1, double h2)
{
    double y=0;
    double Df[sizeof(x)];
    double x2_copy = x[2];
   // double x0_coppy = x[0];
    for(int i =1;i<=k1;i++)
    {   x[1]+=h1;
        x[2]=x2_copy;
       // x[0]=x0_coppy;
        for(int j=1;j<=k2;j++)
        {
            x[2]+=h2;

            f(x,&y,Df);
            //cout<<"siema2";
            double check = y/Df[0];
            double prev = check*999999999999999;
            while((abs(check))>1e-14)
            {
               // if(prev*5<abs(check))
                 //   return i*k1+j;
                f(x,&y,Df);
                check = y/Df[0];

                x[0]=x[0]-check;
            }
            f(x,&y,Df);
            if(abs(y)>1e-14)
                return i*k1+j;
           // pochodna_zero:
            printVector(x,3);

        }
        cout<<endl;
    }
    return  0;
}

//----------------------------2-------------------------------
//----------------------------3-------------------------------

void henon(const double* x, double* y, double* Df){
    // funkcja dana jest wzorem henon(x,y,a,b) = (1+y-a*x^2,b*x)
    const double x2 = x[0]*x[0];

    y[0] = 1 + x[1] - x[2]*x2;
    y[1] = x[3]*x[0];

    //obliczam pierwszy wiersz macierzy
    Df[0] = -2*x[2]*x[0];
    Df[1] = 1.;
    Df[2] = -x2;
    Df[3] = 0.;

    //obliczam drugi wiersz macierzy
    Df[4] = x[3];
    Df[5] = 0.;
    Df[6] = 0.;
    Df[7] = x[0];
}

void Newton_Method_v2(double *y, double *Df, double *x)
{
    double det=0;
    det= (Df[0]*Df[5])-(Df[1]*Df[4]);

    swap(Df[0],Df[5]);
    //  cout<<"df0 = "<<Df[0]<<"      Df4 = "<<Df[4]<<endl;
    Df[1]=-Df[1]*(1/det);
    Df[0]=Df[0]*(1/det);
    Df[4]=-Df[4]*(1/det);
    Df[5]=Df[5]*(1/det);
    double w1= (Df[0]*y[0])+(Df[1]*y[1]);
    double w2= (Df[4]*y[0])+(Df[5]*y[1]);

    x[0]=x[0]-w1;
    x[1]=x[1]-w2;
    // cout<<"koniec      ";
    // cout<<"x0 = "<<x[0]<<"      x1 = "<<x[1]<<endl;
}

int findFixedPoints(FuncPointer f, double* x, unsigned k1, unsigned k2, double h1, double h2)
{
    double y[2];
    double Df[sizeof(y)* sizeof(x)];
    double x3_copy = x[3];
    for(int i=1;i<=k1;i++)
    {
        x[2]+=h1;
        x[3]=x3_copy;
        for(int j=1;j<=k2;j++)
        {

            x[3]+=h2;

            f ( x,y,Df);
            y[0]=y[0]-x[0];
            y[1]=y[1]-x[1];
            Df[0]=Df[0]-1;
            Df[5]=Df[5]-1;

           // f ( x,y,Df);
           // cout<<"x0 = "<<x[0]<<" x1 = "<<x[1]<<endl;
          //  cout<<"y0 = "<<y[0]<<" y1 = "<<y[1]<<endl;
            while(max(abs(y[0]),abs(y[1]))>1e-14)
            {
                //cout<<"+";
                 Newton_Method_v2 (y,Df,x);
                f ( x,y,Df);
                y[0]=y[0]-x[0];
                y[1]=y[1]-x[1];
                Df[0]=Df[0]-1;
                Df[5]=Df[5]-1;
            }
            f ( x,y,Df);
            y[0]=y[0]-x[0];
            y[1]=y[1]-x[1];
            Df[0]=Df[0]-1;
            Df[5]=Df[5]-1;
            if(max(abs(y[0]),abs(y[1]))>1e-14)
                return i*k1+j;


            printVector(x,4);
        }
        cout<<endl;
    }
    return 0;
}

//------------------------------------------3-----------------------------------------
