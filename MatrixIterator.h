//
// Created by Kuba on 2020-04-03.
//
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
#ifndef MATRIXITERATOR_MATRIXITERATOR_H
#define MATRIXITERATOR_MATRIXITERATOR_H
using namespace std;
class  without_initialization{};

template <typename T,int N,int M>
class Matrix
{
public:
    int numberOfColumns() const {return M;}
    int numberOfRows() const {return N;}
    T data[N*M];
    T operator() (int i, int j) const {return data[(i-1)*M+j-1];}
    T & operator() (int i, int j)
    {
        return data [(i-1)*M+j-1];
    }        //do wpisywania
    Matrix()
    {
        std::fill_n(data,N*M,0.0);
        cout<<"constructor of static "<<N<<"x"<<M<<" matrix"<<endl;
    }
    Matrix(without_initialization, int numberOfRows =N, int numberOfColumns=M)
    {
        cout<<"constructor of static uninitialized matrix"<<endl;
    }

    Matrix(std::initializer_list < std::initializer_list<T> > list) //lista inicjalizacyjna wykonuje sie zanim obiekt zacznie istniec
    {
        for(int i=0;i<N;i++)
            for(int j=0;j<M;j++)
                data[j+i*M]=*((*(list.begin()+i)).begin()+j);
        cout<<"constructor of "<<N<<"x"<<M<<" matrix from initializer_list"<<endl;
    }

    Matrix & operator = (const Matrix & m){

            std::copy_n(m.data, N*M, data);

        return *this;
    }


    Matrix(const Matrix &m)   //konstruktor kopiujÄ…cy

    {
        std::copy_n(m.data, N*M, data);
        cout<<"copy constructor "<<endl;
    }
    template <int O, int P>
    friend Matrix<T,N,M> operator+ (Matrix<T,N,M> const &m, const Matrix <T, O, P> &m2){ //operator unarny
        if(N!=O||M!=P)
        {
            throw "compilation ERROR";

        }
        without_initialization x;
        Matrix <T,N, M> new_m(x);

        for(int i=0; i<N*M;i++)
            new_m.data[i]=m2.data[i]+m.data[i];
        //cout<<"operacja +"<<endl;
        return new_m;
    }
    template <int O, int P>
    friend Matrix<T,N,P> operator* (const Matrix <T, N, M> &m, const Matrix <T, O, P> &m2) { //operator unarny
        without_initialization x;
        Matrix <T,N, P> new_m(x);
        //cout<<"n = "<<N<<" p= "<<P<<endl;
        if(M==O) {
            for (int i = 1; i <= N ; i++)
            {
                for(int i2=1; i2<=P;i2++)
                {
                    T sum=0.0;
                    for(int j=0;j<M;j++)
                    {
                        sum = sum + m(i,j+1)*m2(j+1,i2);
                    }
                    new_m.data[(i-1)*P+i2-1]=sum;
                }
            }

            return new_m;
        }
        throw "compilation ERROR";
    }

    class iterator;




    class iterator
    {
        Matrix& m;
        unsigned int index;


        public:
                iterator(Matrix& m):m(m),index(0){}

        const iterator& operator++(){
            ++index;
            return *this;
        }
        iterator operator++(int){
            iterator it(*this);
            ++index;
            return it;
        }
        T& operator*() const{

            return m.data[index];
        }
        T* operator->() const{
            return &m.data[index];
        }
        bool operator<(const iterator& it) const{
            return index<it.index;
        }
        bool operator==(const iterator& it) {
            return index == it.index;
        }
        bool operator!=(const iterator& it) {
            return index != it.index;
        }
        friend class Matrix;
    };

    iterator begin(){
        return iterator(*this);
    }

    iterator end(){
        iterator ite(*this);
        ite.index=N*M;
        return ite;
    }



    class row_iterator
    {
        Matrix& m;
        unsigned int index;


    public:
        row_iterator(Matrix& m):m(m),index(0){}

        const row_iterator& operator++(){
            ++index;
            return *this;
        }
        row_iterator operator++(int){
            row_iterator it(*this);
            ++index;
            return it;
        }
        T& operator*() const{

            return m.data[index];
        }
        T* operator->() const{
            return &m.data[index];
        }
        bool operator<(const row_iterator& it) const{
            return index<it.index;
        }
        bool operator==(const row_iterator& it) {
            return index == it.index;
        }
        bool operator!=(const row_iterator& it) {
            return index != it.index;
        }
        friend class Matrix;
    };

    row_iterator row_begin(int n){
        row_iterator ite(*this);
        ite.index=M*(n-1);
        return ite;
    }

    row_iterator row_end(int n){
        row_iterator ite(*this);
        ite.index=M*n;
        return ite;
    }


    class col_iterator
    {
        Matrix& m;
        unsigned int index;


    public:
        col_iterator(Matrix& m):m(m),index(0){}

        const col_iterator& operator++(){
            index=index+M;
            return *this;
        }
        col_iterator operator++(int){
            col_iterator it(*this);
            index=index+M;
            return it;
        }
        T& operator*() const{

            return m.data[index];
        }
        T* operator->() const{
            return &m.data[index];
        }
        bool operator<(const col_iterator& it) const{
            return index<it.index;
        }
        bool operator==(const col_iterator& it) {
            return index == it.index;
        }
        bool operator!=(const col_iterator& it) {
            return index != it.index;
        }
        friend class Matrix;
    };

    col_iterator col_begin(int n){
        //return iterator(*this);
        col_iterator ite(*this);
        ite.index=n-1;
        return ite;
    }

    col_iterator col_end(int n){
        col_iterator ite(*this);
        ite.index=(N*M)+n-1;
        return ite;
    }
};
#endif //MATRIXITERATOR_MATRIXITERATOR_H
