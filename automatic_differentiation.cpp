//Jakub Robak
#include <iostream>
#include "funkcja.h"
#include <cmath>
using namespace std;

template <typename T>
class FDW
{
    public:
    T wartosc;
    T pochodna_x;
    T pochodna_y;
    T pochodna_x2;
    T pochodna_xy;
    T pochodna_y2;
    FDW()
    {   wartosc = 0;
        pochodna_x=0;
        pochodna_y = 0;
        pochodna_x2=0;
        pochodna_xy=0;
        pochodna_y2=0;
    }
    FDW(T zmienna)
    :wartosc(zmienna), pochodna_x(1) {
        pochodna_y = 0;
        pochodna_xy=0;
        pochodna_y2=0;
        pochodna_x2=0;
    }

    FDW(T zmienna,double a)
            :wartosc(zmienna), pochodna_y(a) {
        pochodna_x = 0;
        pochodna_xy=0;
        pochodna_y2=0;
        pochodna_x2=0;
    }

    FDW(const FDW &fdw)   //konstruktor kopiujÄ…cy
    {
        wartosc = fdw.wartosc;
        pochodna_x = fdw.pochodna_x;
        pochodna_y = fdw.pochodna_y;
        pochodna_x2 = fdw.pochodna_x2;
        pochodna_xy = fdw. pochodna_xy;
        pochodna_y2 = fdw.pochodna_y2;
    }

    //dzialania obiekt z obiektem
    friend FDW<T> operator  +(const FDW &x,FDW const &y)
    {
        FDW new_xy;
        new_xy.wartosc=x.wartosc+y.wartosc;
        new_xy.pochodna_x=x.pochodna_x+y.pochodna_x;
        new_xy.pochodna_y=x.pochodna_y+y.pochodna_y;
        new_xy.pochodna_x2=x.pochodna_x2+y.pochodna_x2;
        new_xy.pochodna_xy=x.pochodna_xy+y.pochodna_xy;
        new_xy.pochodna_y2=x.pochodna_y2+y.pochodna_y2;
        return new_xy;
    }

    friend FDW<T> operator  -(const FDW &x,FDW const &y)
    {
        FDW new_xy;
        new_xy.wartosc=x.wartosc-y.wartosc;
        new_xy.pochodna_x=x.pochodna_x-y.pochodna_x;
        new_xy.pochodna_y=x.pochodna_y-y.pochodna_y;
        new_xy.pochodna_x2=x.pochodna_x2-y.pochodna_x2;
        new_xy.pochodna_xy=x.pochodna_xy-y.pochodna_xy;
        new_xy.pochodna_y2=x.pochodna_y2-y.pochodna_y2;
        return new_xy;
    }

    friend FDW<T> operator  *(const FDW &x,FDW const &y)
    {
        FDW new_xy;
        new_xy.wartosc=x.wartosc*y.wartosc;
        new_xy.pochodna_x=(x.pochodna_x*y.wartosc)+(y.pochodna_x*x.wartosc);
        new_xy.pochodna_y=(x.pochodna_y*y.wartosc)+(y.pochodna_y*x.wartosc);

        new_xy.pochodna_x2=(x.pochodna_x2*y.wartosc)+(2*x.pochodna_x*y.pochodna_x)+(x.wartosc*y.pochodna_x2);
        new_xy.pochodna_xy=(x.pochodna_xy*y.wartosc)+(y.pochodna_x*x.pochodna_y)+(y.pochodna_xy*x.wartosc)+(x.pochodna_x*y.pochodna_y);
        new_xy.pochodna_y2=(x.pochodna_y2*y.wartosc)+(2*x.pochodna_y*y.pochodna_y)+(x.wartosc*y.pochodna_y2);;

         return new_xy;
    }

    friend FDW<T> operator  /(const FDW &x,FDW const &y)
    {
        FDW new_xy;
        new_xy.wartosc=x.wartosc/y.wartosc;
        new_xy.pochodna_x=(x.pochodna_x-(x.wartosc/y.wartosc)*y.pochodna_x)/y.wartosc;
        new_xy.pochodna_y=(x.pochodna_y-(x.wartosc/y.wartosc)*y.pochodna_y)/y.wartosc;

        new_xy.pochodna_x2=((((x.pochodna_x2*y.wartosc)-(x.wartosc*y.pochodna_x2))*y.wartosc*y.wartosc)-(2*y.wartosc*y.pochodna_x*((x.pochodna_x*y.wartosc)-(y.pochodna_x*x.wartosc))))/(y.wartosc*y.wartosc*y.wartosc*y.wartosc);
        new_xy.pochodna_xy=(((((x.pochodna_xy*y.wartosc)+(y.pochodna_x*x.pochodna_y))-((y.pochodna_xy*x.wartosc)+(x.pochodna_x*y.pochodna_y)))*(y.wartosc*y.wartosc))-((2*y.pochodna_x*y.wartosc)*((x.pochodna_y*y.wartosc)-(y.pochodna_y*x.wartosc))))/(y.wartosc*y.wartosc*y.wartosc*y.wartosc);
        new_xy.pochodna_y2=((((x.pochodna_y2*y.wartosc)-(x.wartosc*y.pochodna_y2))*y.wartosc*y.wartosc)-(2*y.wartosc*y.pochodna_y*((x.pochodna_y*y.wartosc)-(y.pochodna_y*x.wartosc))))/(y.wartosc*y.wartosc*y.wartosc*y.wartosc);

        return new_xy;
    }

    //dzialania na stalych
    friend FDW<T> operator  +(const FDW &x,T const &y)
    {
        FDW new_xy;
        new_xy.wartosc=y;

        return x+new_xy;
    }

    friend FDW<T> operator  -(const FDW &x,T const &y)
    {
        FDW new_xy;
        new_xy.wartosc=y;

        return x-new_xy;
    }

    friend FDW<T> operator  *(const FDW &x,T const &y)
    {
        FDW new_xy;
        new_xy.wartosc=x.wartosc*y;

        return x*new_xy;
    }


    friend FDW<T> operator  /(const FDW &x,T const &y)
    {
        FDW new_xy;
        new_xy.wartosc=y;

        return x/new_xy;
    }


    friend FDW<T> operator  +(T const &y,const FDW &x)
    {
        FDW new_xy;
        new_xy.wartosc=y;

        return new_xy+x;
    }

    friend FDW<T> operator  -(T const &y,const FDW &x)
    {
        FDW new_xy;
        new_xy.wartosc=y;

        return new_xy-x;
    }

    friend FDW<T> operator  *(T const &y,const FDW &x)
    {
        FDW new_xy;
        new_xy.wartosc=y;

        return new_xy*x;
    }


    friend FDW<T> operator  /(T const &y,const FDW &x)
    {
        FDW new_xy;
        new_xy.wartosc=y;

        return new_xy/x;
    }

    //funkcje ell
    friend FDW sin(FDW const &x)
   {
       FDW new_xy;
       new_xy.wartosc=std::sin (x.wartosc);
       new_xy.pochodna_x=std::cos(x.wartosc)*x.pochodna_x;
       new_xy.pochodna_y=std::cos(x.wartosc)*x.pochodna_y;
       new_xy.pochodna_x2=(x.pochodna_x2*std::cos(x.wartosc))-(std::sin(x.wartosc)*x.pochodna_x*x.pochodna_x);
       new_xy.pochodna_xy=(x.pochodna_xy*std::cos(x.wartosc))-(std::sin(x.wartosc)*x.pochodna_y*x.pochodna_x);
       new_xy.pochodna_y2=(x.pochodna_y2*cos(x.wartosc))-(std::sin(x.wartosc)*x.pochodna_y*x.pochodna_y);
       return new_xy;
   }

    friend FDW cos(FDW const &x)
    {
        FDW new_xy;
        new_xy.wartosc=std::cos (x.wartosc);
        new_xy.pochodna_x=std::sin(x.wartosc)*x.pochodna_x*(-1);
        new_xy.pochodna_y=std::sin(x.wartosc)*x.pochodna_y*(-1);
        new_xy.pochodna_x2=(x.pochodna_x2*std::sin(x.wartosc)*(-1))-(std::cos(x.wartosc)*x.pochodna_x*x.pochodna_x);
        new_xy.pochodna_xy=(x.pochodna_xy*std::sin(x.wartosc)*(-1))-(std::cos(x.wartosc)*x.pochodna_y*x.pochodna_x);
        new_xy.pochodna_y2=(x.pochodna_y2*sin(x.wartosc)*(-1))-(std::cos(x.wartosc)*x.pochodna_y*x.pochodna_y);
        return new_xy;
    }


    friend FDW exp(FDW const &x)
    {
        FDW new_xy;
        new_xy.wartosc=std::exp(x.wartosc);
        new_xy.pochodna_x=std::exp(x.wartosc)*x.pochodna_x;
        new_xy.pochodna_y=std::exp(x.wartosc)*x.pochodna_y;
        new_xy.pochodna_x2=(exp(x.wartosc)*x.pochodna_x*x.pochodna_x)+(x.pochodna_x2*exp(x.wartosc));
        new_xy.pochodna_xy=(exp(x.wartosc)*x.pochodna_x*x.pochodna_y)+(x.pochodna_xy*exp(x.wartosc));
        new_xy.pochodna_y2=(exp(x.wartosc)*x.pochodna_y*x.pochodna_y)+(x.pochodna_y2*exp(x.wartosc));
        return new_xy;
    }

     FDW operator  -() const
    {
        FDW new_xy;
        new_xy.wartosc=wartosc*(-1);
        new_xy.pochodna_x=pochodna_x*(-1);
        new_xy.pochodna_y=pochodna_y*(-1);
        new_xy.pochodna_x2=pochodna_x2*(-1);
        new_xy.pochodna_xy=pochodna_xy*(-1);
        new_xy.pochodna_y2=pochodna_y2*(-1);
        return new_xy;
    }

    FDW<T> operator  =(const FDW & x)
    {
        wartosc = x.wartosc;
        pochodna_x=x.pochodna_x;
        pochodna_y = x.pochodna_y;
        pochodna_x2=x.pochodna_x2;
        pochodna_xy=x.pochodna_xy;
        pochodna_y2=x.pochodna_y2;
        return *this;
    }
};

int main() {
    cout.precision(17);
    int M;
    cin>>M;
    double x; double y;
    for(int i=0;i<M;i++)
    {
        cin>>x;
        cin>>y;

        FDW <double> X(x);
        FDW <double> Y(y,(double)1);

        FDW <double> result = funkcja(X,Y);   //i będziemy po kolei wypisywać FDW.w artosc FDW.pochodna
        cout<<result.wartosc<<" ";
        cout<<result.pochodna_x<<" ";
        cout<<result.pochodna_y<<" ";
        cout<<result.pochodna_x2<<" ";
        cout<<result.pochodna_xy<<" ";
        cout<<result.pochodna_y2;
        cout<<endl;
    }
}
