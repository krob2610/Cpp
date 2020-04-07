//
// Created by Kuba on 2020-04-02.
//
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "staticMatrix.h"
using namespace std;
#ifndef STATICMATRIX_DYNAMICMATRIX_H
#define STATICMATRIX_DYNAMICMATRIX_H

template <typename T, size_t N, size_t M>
Matrix<T,M,N> transpose(const Matrix<T,N,M> &m )
{

    int number=0;
    Matrix <T,M, N> new_m(m.numberOfCols,m.numberOfRowss);
    for(size_t i= 0; i<m.numberOfCols;i++)
        for(size_t j=0;j<m.numberOfRowss;j++)
        {
            new_m.data[number]=m.data[(j)*(m.numberOfColumns())+i];
            number++;
        }
    return  new_m;

}

template <typename  T>
class Matrix<T,0,0>{
    public:
     size_t numberOfRowss;
     size_t numberOfCols;
    std::unique_ptr<T []> data;

    size_t numberOfColumns() const {return numberOfCols;}
    size_t numberOfRows() const {return numberOfRowss;}

    Matrix()
            : numberOfCols(0), numberOfRowss(0), data(nullptr){}
    Matrix(size_t rows, size_t cols)    //lista inicjalizacyjna wykonuje sie zanim obiekt zacznie istniec
            : numberOfRowss(rows), numberOfCols(cols),
              data(new T[rows*cols])     //dodajemy nawias ĹĽeby byĹ‚o 0 value_initialization()
    {
        std::fill_n(data.get(),rows*cols,0.0);
        cout<<"constructor of  dynamic"<<rows<<"x"<<cols<<" matrix"<<endl;
    }

    Matrix(std::initializer_list < std::initializer_list<T> > list){   //z listy
        numberOfRowss=list.size();   //iloĹ›Ä‡ wierszy to wielkoĹ›Ä‡ listy
        size_t maxSize=0;
        for(const auto & row : list){   //row to jakiĹ› podzbiĂł w liscie
            maxSize = std::max(maxSize, row.size());
        }
        numberOfCols=maxSize;   //mamy najdĹ‚uzszy podzbior
        data.reset(new T[numberOfCols*numberOfRowss]);
        T *p=data.get();
        for(auto row:list){     //uzupeĹ‚nianie zerami
            T *copyEnd = std::copy(row.begin(),row.end(),p);   //kopiujemy na p
            std::fill(copyEnd, p+numberOfCols, 0.0);    //od ostatniego wyrazu do konca wypeĹ‚niami zerami/// wpisujemy do row
            p+=numberOfCols;
        }
        cout<<"constructor of dynamic"<<numberOfRowss<<"x"<<numberOfCols<<" matrix from initializer_list"<<endl;
    }


    double operator()(size_t row, size_t col) const{
        return data[(row-1)*numberOfCols+col-1];
    }

    double & operator()(size_t row, size_t col) {
        return data[(row-1)*numberOfCols+col-1];
    }

    Matrix(const Matrix &m)   //konstruktor kopiujÄ…cy
            :numberOfRowss(m.numberOfRowss), numberOfCols(m.numberOfCols), data(new double [numberOfCols*numberOfRowss])
    {
        std::copy_n(m.data.get(), numberOfCols*numberOfRowss, data.get());
        cout<<"copy constructor of dynamic matrix "<<endl;
    }

    Matrix(Matrix &&m)
            : numberOfRowss(std::move(m.numberOfRowss)), numberOfCols(std::move(m.numberOfCols))
    {
        data=std::move(m.data);
        m.data= nullptr;

        cout<<"move constructor of dynamic Matrix"<<endl;
    }
//    template <size_t O, size_t P>
    friend Matrix<T,0,0> operator+ (Matrix<T,0,0> const &m, const Matrix <T, 0, 0> &m2) { //operator unarny

        if(m.numberOfRowss!=m2.numberOfRowss||m.numberOfCols!=m2.numberOfCols)
        {
            throw MatrixException("Incompatible dimensions in operator +");

        }
       // without_initialization x;
        Matrix <T,0, 0> new_m(m.numberOfRowss,m.numberOfCols);

        for(size_t i=0; i<m.numberOfCols*m.numberOfRowss;i++)
            new_m.data[i]=m2.data[i]+m.data[i];
        //cout<<"operacja +"<<endl;
        return new_m;
    }

    friend Matrix<T,0,0> operator* (const Matrix <T, 0, 0> &m, const Matrix <T, 0, 0> &m2) { //operator unarny


        if(m.numberOfCols==m2.numberOfRowss) {
            Matrix <T,0, 0> new_m(m.numberOfRowss,m2.numberOfCols);
            for (size_t i = 1; i <= m.numberOfRowss ; i++)
            {
                for(size_t i2=1; i2<=m2.numberOfCols;i2++)
                {
                    T sum=0.0;
                    for(size_t j=0;j<m.numberOfCols;j++)
                    {
                        sum = sum + m(i,j+1)*m2(j+1,i2);
                    }
                    new_m.data[(i-1)*m2.numberOfCols+i2-1]=sum;
                }
            }

            return new_m;
        }
        throw MatrixException("Incompatible dimensions in operator *");
    }

    template <std::size_t N, std::size_t M> //conversion
    explicit operator Matrix<T,N,M>()
    {
        Matrix <T,N,M> new_m;
        for(size_t i=0;i<N*M;i++)
            new_m.data[i]=data[i];
        cout<<" conversion from dynamic to static matrix"<<endl;
        return  new_m;
    }
        //union of dynamic and static
        template <std::size_t N, std::size_t M>
        friend Matrix<T,N,M> operator+ (Matrix<T,0,0> const &m, const Matrix <T, N, M> &m2) { //operator unarny

            if(m.numberOfRowss!=N||m.numberOfCols!=M)
            {
                throw MatrixException("Incompatible dimensions in operator +");

            }
            without_initialization x;
            Matrix <T,N, M> new_m(x);

            for(size_t i=0; i<m.numberOfCols*m.numberOfRowss;i++)
                new_m.data[i]=m2.data[i]+m.data[i];
            //cout<<"operacja +"<<endl;
            return new_m;
        }

    template <std::size_t N, std::size_t M>
    friend Matrix<T,0,0> operator* (const Matrix <T, 0, 0> &m, const Matrix <T, N, M> &m2) { //operator unarny


        if(m.numberOfCols==N) {
            Matrix <T,0, 0> new_m(m.numberOfRowss,M);
            for (size_t i = 1; i <= m.numberOfRowss ; i++)
            {
                for(size_t i2=1; i2<=M;i2++)
                {
                    T sum=0.0;
                    for(size_t j=0;j<m.numberOfCols;j++)
                    {
                        sum = sum + m(i,j+1)*m2(j+1,i2);
                    }
                    new_m.data[(i-1)*M+i2-1]=sum;
                }
            }

            return new_m;
        }
        throw MatrixException("Incompatible dimensions in operator *");
    }

};
#endif //STATICMATRIX_DYNAMICMATRIX_H
