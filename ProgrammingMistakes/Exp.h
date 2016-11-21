#pragma once
#include "TimeMS.h"
#include <iostream>
#include <vector>
#include <map>
#include <typeinfo>
#include <string>
#include <algorithm>
#include <future>
#include <cassert>
namespace Test3 {
    class Subject;
    class Observer    {

    public:
        std::future<void> handle;
        virtual void notify(Subject* s) = 0;
        virtual ~Observer() {};
        virtual std::string id() = 0;
    };
    class Subject
    {
        std::map<std::string, Observer *> observers;
    protected:
        void notify_observers()
        {
            std::map<std::string, Observer *>::iterator iter;
            for (iter = observers.begin(); iter != observers.end(); ++iter) {
                Observer* observer = iter->second;
                observer->handle = std::async(std::launch::async, [observer,this]() { observer->notify(this); } );
            }
        }
        void getResult() {
            for(auto iter = observers.begin();  iter != observers.end(); ++iter) {
                Observer* observer = iter->second;
                observer->handle.get();
            }
        }

    public:
        virtual ~Subject() {};
        bool observer(Observer* o)
        {
            observers[o->id()] = o;
            return true;
        }
        bool observerFixed(Observer* o)
        {
            //std::pair<std::map<std::string, Observer *>::iterator,bool> ret;
            auto ret = observers.insert(std::pair<std::string, Observer *>(o->id(),o));
            assert( ret.second);
            return ret.second;
        }
        void unobserver(std::string id)
        {
            delete observers[id];
            observers.erase(id);
        }
    };
    template<typename Iter>
    class TestSort : public Subject
    {
        Iter mBeg, mEnd;
    public:

        TestSort(Iter beg, Iter end):mBeg(beg), mEnd(end) {};
        friend std::istream&  operator>>(std::istream& is, TestSort &ts);
        friend std::ostream&  operator<<(std::ostream& is, const TestSort &ts);
        void Triggerd()  {
            notify_observers();
            getResult();
        }

        Iter const beg(){ return mBeg; }
        Iter const end(){ return mEnd; }
    };
    template<typename Iter>
    std::istream&  operator>>(std::istream& is, TestSort<Iter> &ts) {
        is>>ts;
        return is;
    }
    template<typename Iter>
    std::ostream&  operator>>(std::ostream& os, const TestSort<Iter> &ts) {
        os<<ts;
        return os;
    }
    template<typename Iter, typename type>
    class Sort : public Observer {
        std::vector<long long> time;
    public:
        virtual void notify(Subject* s)
        {
            long long start = GetTimeMs64();
            TestSort<Iter> *a;
            a = dynamic_cast<TestSort<Iter> *>(s);
            std::vector<type> temp(a->beg(), a->end());

            sort(temp.begin(), temp.end());
            //std::copy(temp.begin(), temp.end(), std::ostream_iterator<type>(std::cout, ", "));
            std::cout<<std::endl;
            long long end = GetTimeMs64();
            time.push_back(end - start);
            std::cout<<this->id()<<'\t'<<end - start <<std::endl;
        }
        virtual std::vector<long long>& stat() {
            return time;
        }
    };

    template<typename Iter, typename type>
    class InsertionSort : public Sort<Iter, type>
    {
        void sort(Iter beg, Iter end) {
            for (Iter i = beg; i != end; ++i)
                std::rotate(std::upper_bound(beg, i, *i), i, i+1);
        }
    public:
        std::string id() {return "InsertionSort"; };


    };
    template<typename Iter, typename type>
    class MergeSort : public Sort<Iter, type>
    {
        void sort(Iter first, Iter last)
        {
            if (last - first > 1)
            {
                Iter middle = first + (last - first) / 2;
                sort(first, middle);
                sort(middle, last);
                std::inplace_merge(first, middle, last);
            }
        }
    public:
        std::string id() {return "MergeSort"; };
    };
    template<typename Iter, typename type>
    class SelectionSort : public Sort<Iter, type>
    {
        void sort(Iter begin, Iter end)
        {
            for(ForwardIterator i = begin; i != end; ++i)
                std::iter_swap(i, std::min_element(i, end));
        }
    public:
        std::string id() {return "SelectionSort"; };
    };
    template<typename Iter, typename type>
    class QuickSort : public Sort<Iter, type>
    {
        void sort(Iter first, Iter last)
        {
            if (last - first > 1)
            {
                RandomAccessIterator split = std::partition(first+1, last );
                std::iter_swap(first, split-1);
                quicksort(first, split-1);
                quicksort(split, last);
            }
        }
    public:
        std::string id() {return "QuickSort"; };
    };
    template<typename Iter, typename type>
    class CPPSort : public Sort<Iter, type>
    {
        void sort(Iter first, Iter last)
        {
            std::qsort(first, last);
        }
    public:
        std::string id() {return "CPPSort"; };
    };
    int test (bool bFixed)
    {
        bool (Subject::*pObserver)(Observer*) = (bFixed)?&Subject::observerFixed:&Subject::observer;
        std::vector<double> data(100000);
        std::generate(data.begin(), data.end(), [](){return rand() % 500;} ); 
        auto ts = TestSort<std::vector<double>::iterator >(data.begin(), data.end());

        auto is = new InsertionSort<std::vector<double>::iterator, double >();
        auto is1 = new InsertionSort<std::vector<double>::iterator, double >();
        auto ms = new MergeSort<std::vector<double>::iterator, double >();
        auto cs = new CPPSort<std::vector<double>::iterator, double >();
        auto ss = new SelectionSort<std::vector<double>::iterator, double >();
        auto qs = new QuickSort<std::vector<double>::iterator, double >();
        (ts.*(pObserver))(is);
        //(ts.*(pObserver))(is1);
        (ts.*(pObserver))(ms);
        (ts.*(pObserver))(cs);
        (ts.*(pObserver))(ss);
        (ts.*(pObserver))(qs);

        ts.Triggerd();
        ts.unobserver(is->id());
        //ts.unobserver(is1->id());
        ts.unobserver(ms->id());
        ts.unobserver(cs->id());
        ts.unobserver(ss->id());
        ts.unobserver(qs->id());
        return 0;
    }
};