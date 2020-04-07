//
// Created by Kuba on 2020-04-03.
//
#include<algorithm>
#include <iomanip>
#include <iostream>
#include <cmath>
#ifndef RANGE_RANGE_H
#define RANGE_RANGE_H

using namespace std;


template <typename T>
class Range
{
public:
    T start;
    T stop;
    T step;
    T* data;
    Range(T start, T stop, T step)
            :start(start), stop(stop), step(step),data(new T[(int)ceil((stop-start)/step)]) {
        data[0]=start;
        for(int i=1;i<(int)ceil((stop-start)/step);i++)
            data[i]=start+(i*step);
    }

    Range(T start, T stop)
            :start(start), stop(stop), step(1.0),data(new T[(int)ceil((stop-start)/step)]) {
        data[0]=start;
        for(int i=1;i<(int)ceil((stop-start)/step);i++)
            data[i]=start+(i*step);
    }

    Range(T stop)
            :start(0.0), stop(stop), step(1.0),data(new T[(int)ceil((stop-start)/step)]) {
        data[0]=start;
        for(int i=1;i<(int)ceil((stop-start)/step);i++)
            data[i]=start+(i*step);
    }

    class iterator;
    friend class Range;

    class iterator{
        Range& r;
        unsigned int index;
    public:
        iterator(Range& r):r(r),index(0){}

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

            return r.data[index];
        }
        T* operator->() const{
            return &r.data[index];
        }
        bool operator<(const iterator& it) const{
            return index<it.index;
        }
        bool operator!=(const iterator& it) {
            return index != it.index;
        }
        friend class Range;
    };

    iterator begin(){
        return iterator(*this);
    }

    iterator end(){
        iterator ite(*this);
        ite.index=(int)ceil((stop-start)/step);
        return ite;
    }


};

template <typename T>
Range<T>  make_range(T a, T b, T c)
{
    Range <T> new_range(a,b,c);
    return new_range;
}

template <typename T>
Range<T>  make_range(T a)
{
    Range <T> new_range(a);
    return new_range;
}


template <typename T>
Range<T>  make_range(T a, T b)
{
    Range <T> new_range(a,b);
    return new_range;
}
#endif //RANGE_RANGE_H

