//
// Created by Kuba on 2020-03-25.
//
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <algorithm>

#ifndef STATICMATRIX_STATICMATRIX_H
#define STATICMATRIX_STATICMATRIX_H
using namespace std;

class  without_initialization{};

class MatrixException : public virtual std::runtime_error
{public:
    //MatrixException() : std::runtime_error("") { }
    using std::runtime_error::runtime_error ;

};

template <typename T,size_t N,size_t M>
class Matrix
{
public:
    size_t numberOfColumns() const {return M;}
    size_t numberOfRows() const {return N;}
    size_t numberOfRowss=N;
    size_t numberOfCols=M;
    T data[N*M];
    T operator() (size_t i, size_t j) const {return data[(i-1)*M+j-1];}
    T & operator() (size_t i, size_t j)
    {
        return data [(i-1)*M+j-1];
    }        //do wpisywania
    Matrix()
    {
        std::fill_n(data,N*M,0.0);
        cout<<"constructor of static "<<N<<"x"<<M<<" matrix"<<endl;
    }
    Matrix(size_t rows, size_t cols)    //lista inicjalizacyjna wykonuje sie zanim obiekt zacznie istniec
            : numberOfRowss(rows), numberOfCols(cols){cout<<"constructor of static uninitialized matrix"<<endl;}
    Matrix(without_initialization, size_t numberOfRows =N, size_t numberOfColumns=M)
    {
        cout<<"constructor of static uninitialized matrix"<<endl;
    }

    Matrix(std::initializer_list < std::initializer_list<T> > list) //lista inicjalizacyjna wykonuje sie zanim obiekt zacznie istniec
    {
        T *p=data;
        for(auto row:list){     //uzupeĹ‚nianie zerami
            double *copyEnd = std::copy(row.begin(),row.end(),p);   //kopiujemy na p
            std::fill(copyEnd, p+M, 0.0);    //od ostatniego wyrazu do konca wypeĹ‚niami zerami/// wpisujemy do row
            p+=M;
        }
        cout<<"constructor of static matrix"<<N<<"x"<<M<<" matrix from initializer_list"<<endl;
    }

    Matrix(const Matrix &m)   //konstruktor kopiujÄ…cy

    {
        std::copy_n(m.data, N*M, data);
        cout<<"copy constructor of static matrix "<<endl;
    }
    template <size_t O, size_t P>
    friend Matrix<T,N,M> operator+ (Matrix<T,N,M> const &m, const Matrix <T, O, P> &m2){ //operator unarny
        if(N!=O||M!=P)
        {
            throw MatrixException("Incompatible dimensions in operator +");

        }
        without_initialization x;
        Matrix <T,N, M> new_m(x);

        for(size_t i=0; i<N*M;i++)
            new_m.data[i]=m2.data[i]+m.data[i];
        //cout<<"operacja +"<<endl;
        return new_m;
    }
    template <size_t O, size_t P>
    friend Matrix<T,N,P> operator* (const Matrix <T, N, M> &m, const Matrix <T, O, P> &m2) { //operator unarny
        without_initialization x;
        Matrix <T,N, P> new_m(x);
        //cout<<"n = "<<N<<" p= "<<P<<endl;
        if(M==O) {
            for (size_t i = 1; i <= N ; i++)
            {
                for(size_t i2=1; i2<=P;i2++)
                {
                    T sum=0.0;
                    for(size_t j=0;j<M;j++)
                    {
                        sum = sum + m(i,j+1)*m2(j+1,i2);
                    }
                    new_m.data[(i-1)*P+i2-1]=sum;
                }
            }

            return new_m;
        }
        throw MatrixException("Incompatible dimensions in operator *");
    }



    explicit operator Matrix<T,0,0>()       //zamiana
    {
        Matrix <T,0,0> new_m(N,M);
        for(size_t i=0;i<N*M;i++)
            new_m.data[i]=data[i];
        cout<<" conversion from static to dynamic matrix"<<endl;
        return  new_m;
    }

    //dodawanie dla obu typow
    friend Matrix<T,N,M> operator+ (Matrix<T,N,M> const &m, const Matrix <T, 0,0> &m2){ //operator unarny
        if(N!=m2.numberOfRows()||M!=m2.numberOfColumns())
        {
            throw MatrixException("Incompatible dimensions in operator +");

        }
        without_initialization x;
        Matrix <T,N, M> new_m(x);

        for(size_t i=0; i<N*M;i++)
            new_m.data[i]=m2.data[i]+m.data[i];
        //cout<<"operacja +"<<endl;
        return new_m;
    }

    friend Matrix<T,0,0> operator* (const Matrix <T, N, M> &m, const Matrix <T, 0, 0> &m2) { //operator unarny

        Matrix <T,0, 0> new_m(N,m2.numberOfColumns());
        //cout<<"n = "<<N<<" p= "<<P<<endl;
        if(M==m2.numberOfRows()) {
            for (size_t i = 1; i <= N ; i++)
            {
                for(size_t i2=1; i2<=m2.numberOfColumns();i2++)
                {
                    T sum=0.0;
                    for(size_t j=0;j<M;j++)
                    {
                        sum = sum + m(i,j+1)*m2(j+1,i2);
                    }
                    new_m.data[(i-1)*m2.numberOfColumns()+i2-1]=sum;
                }
            }

            return new_m;
        }
        throw MatrixException("Incompatible dimensions in operator *");
    }


};
/*int main(){
    cout <<fixed << setprecision(2);
    using DMatrix = Matrix<double, 3, 4>;

    DMatrix m0{}; // Matrix filled with zeroes
    printMatrix(m0);

    DMatrix m1({{1,  2,  3,  4},  // constructor from
                { 5,  6,  7,  8},  // initialization_list
                { 9, 10, 11, 12}});
    printMatrix(m1);

    DMatrix m2 = m1;              // copy constructor

    m2(2,1) = -5;  m2(3,2) = -20; // mutable access


    DMatrix m3 = m1 + m2;         // matrix sum (with equal sizes)

    printMatrix(m3);

    try {
     //auto mm = m1 * m2; // compilation ERROR

    } catch (const char* msg) {
        cerr << msg << endl;
    }

    Matrix<double, 4, 2> m4({
                                    {1.2, 1},
                                    {21, 2},
                                    {34, 2},
                                    {2, 32}});
    auto m5 = m1 * m4;    // matrix multiplication
    try {
       // auto mm = m1 + m4;   // compilation ERROR
       printMatrix(m5);
    } catch (const char* msg) {
        cerr << msg << endl;
    }
    return 0;
}

/*
 * Expected output (or similar)
 constructor of static 3x4 matrix
      0.00       0.00       0.00       0.00
      0.00       0.00       0.00       0.00
      0.00       0.00       0.00       0.00
 constructor of static 3x4 matrix from initializer_list
      1.00       2.00       3.00       4.00
      5.00       6.00       7.00       8.00
      9.00      10.00      11.00      12.00
 copy constructor of static matrix
 constructor of static uninitialized matrix
      2.00       4.00       6.00       8.00
      0.00      12.00      14.00      16.00
     18.00     -10.00      22.00      24.00
 constructor of static 4x2 matrix from initializer_list
 constructor of static uninitialized matrix
    153.20     139.00
    386.00     287.00
    618.80     435.00

*/
#endif //STATICMATRIX_STATICMATRIX_H