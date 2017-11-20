
//  Header.h
//  sky_newcoder
//
//  Created by xiaosheng on 11/11/2017.
//
//

#ifndef ALSort_h
#define ALSort_h

#include<iostream>
#include<vector>
#include "GLDebug.h"
#include "InTime.h"
using namespace std;


template <class T>
class SortBase
{
public:
    virtual void onCreate() = 0;
    virtual float onSort(vector<T>& array) = 0;
    void sky_swap(vector<T> &array,int i,int j);
    void sky_swap(T& a,T& b );
    /// just for practice the lambda
    function<bool(vector<T> &array)> mSortFunc;
    virtual ~SortBase()
    {
        
    }
private:
};

#define SWAP(a,b) SortBase<T>::sky_swap((a),(b));\

#define SWAP_INDEX(arr,a,b) SortBase<T>::sky_swap((arr),(a),(b));\

/// the template class`s declear and define must be one file!!
template<class T> void SortBase<T>::sky_swap(vector<T> &array, int i, int j)
{
    T temp = array[i];
    array[i] = array[j];
    array[j] = temp;
    return;
}

template <class T>
void SortBase<T>::sky_swap(T &a, T &b)
{
    /// when &a != &b .they can`t have the same address
    //    a = a^b;
    //    b = a^b;
    //    a = a^b;
    T temp = a;
    a = b;
    b = temp;
    return;
}




/// the bubble sort
template <class T>
class BubbleSort : public SortBase<T>
{
public:
    
    virtual void onCreate();
    virtual float onSort(vector<T>& array)
    {
        InTime time;
        TIME_START("");
        SortBase<T>::mSortFunc(array);
        return TIME_END_RETURN;
    }
    virtual ~BubbleSort()
    {
        
    }
};


template <class T>
void BubbleSort<T>::onCreate()
{
    SortBase<T>::mSortFunc = [&](vector<T> &array)
    {
        int length = array.size();
        if (length <= 1)
        {
            return true;
        }
        for (int i = length - 1; i >= 0 ; i--)
        {
            for (int j = 0; j < i; j++)
            {
                GLASSERT(i < length && j < length);
                if (array[j] > array[j+1])
                {
                    SortBase<T>::sky_swap(array[j],array[j+1]);
                }
            }
        }
        return true;
        
    };
}

/// the insert sort
template <class T>
class InsertSort : public SortBase<T>
{
public:
    typedef  SortBase<T> base;
    
    virtual void onCreate();
    virtual float onSort(vector<T>& array)
    {
        InTime time;
        TIME_START("");
        SortBase<T>::mSortFunc(array);
        return TIME_END_RETURN;
    }
    virtual ~InsertSort()
    {
        
    }
};

template <class T>
void InsertSort<T>::onCreate()
{
    
    /**
     insert sort function,the insert sort algorithm is like get the poker one by one,and the pokers in your hand is always sorted.
     and this algrithm,is sorted from the local-orderly to the entirety-orderly,the bubble-sort and the chose-sort is sorted from the overall in the begining.
     
     time complexity : Big O(N^2)
     stable : yes
     
     @param array the input array to be sorted
     @return sort success or not
     */
    base::mSortFunc = [&](vector<T> &array){
        int length = array.size();
        if (length <= 1)
        {
            return  true;
        }
        for (int i = 1; i < length; i++)
        {
            for (int j = i - 1; j >=0; j--)
            {
                GLASSERT(i < length && j < length);
                if (array[j+1] < array[j])
                {
                    base::sky_swap(array[j],array[j+1]);
                }
            }
        }
        return true;
    };
}



/// the chose sort
template <class T>
class ChooseSort : public SortBase<T>
{
public:
    typedef  SortBase<T> base;
    
    virtual void onCreate();
    virtual float onSort(vector<T>& array)
    {
        InTime time;
        TIME_START("");
        base::mSortFunc(array);
        return TIME_END_RETURN;
    }
    virtual ~ChooseSort()
    {
        
    }
};

template <class T>
void ChooseSort<T>::onCreate()
{
    
    /**
     choose sort,this algorithm is choose the minest one every time
     time complexity : big O(N^2)
     stably : no

     @param array input array
     @return sorted success or not
     */
    base::mSortFunc = [&](vector<T> &array)
    {
        int len = array.size();
        if (len < 2)
        {
            FUNC_PRINT_ALL("the length of array is too short", s);
            return true;
        }
        for (int i = 0; i < len-1; i++)
        {
            int index = i;
            for (int j = i+1; j < len; j++)
            {
                GLASSERT(i < len && j < len);
                index = array[j] < array[index] ? j : index;
            }
            base::sky_swap(array[i],array[index]);
        }
        return true;
    };
}


/// the quick sort
template <class T>
class QuickSort : public SortBase<T>
{
public:
    typedef  SortBase<T> base;
    
    virtual void onCreate();
    virtual float onSort(vector<T>& array)
    {
        InTime time;
        TIME_START("");
        base::mSortFunc(array);
        return TIME_END_RETURN;
    }
    virtual ~QuickSort()
    {
        
    }
    private:
    function<void(vector<T>&,int,int,int&,int&)> mPartitionFunc;
    function<void(vector<T>&,int,int)> mQuickHelp;
};

template <class T>
void QuickSort<T>::onCreate()
{
    mPartitionFunc = [&](vector<T> &array,int start,int end,int &lessEnd,int& moreBegin){
        int less = start - 1;
        int more = end;
        while (start < more)
        {
            if (array[start] < array[end])
            {
                base::sky_swap(array[++less],array[start++]);
            }
            else if(array[ start] > array[end ])
            {
                base::sky_swap(array[ --more],array[start ]);
            }
            else
            {
                start++;
            }
        }
        // the more is the first index of the more domain,and after swap,the more become the last index of the equal domain
        base::sky_swap(array,more,end);
        lessEnd = less;
        moreBegin = more+1;
    };
    
    mQuickHelp = [&](vector<T> &array,int start,int end)
    {
        if (start < end)
        {
            /// the random will get [start,end) ?
            auto index = InRandom(start,end).getRandom();
            base::sky_swap(array[index], array[end]);
            int lessEnd = 0;
            int moreBegin = 0;
            mPartitionFunc(array,start,end,lessEnd,moreBegin);
            mQuickHelp(array,start,lessEnd);
            mQuickHelp(array,moreBegin,end);
        }
        return ;
    };
    
    base::mSortFunc = [&](vector<T> &array)
    {
        int len = array.size();
        if (len < 2)
        {
            FUNC_PRINT_ALL("the length of array is too short", s);
            return true;
        }
        mQuickHelp(array,0,len-1);
        return true;
    };
}


class QuickSortInt : public SortBase<int>
{
    public:
    virtual void onCreate();
    virtual float onSort(vector<int>& array)
    {
        InTime time;
        TIME_START("");
        SortBase<int>::mSortFunc(array);
        return TIME_END_RETURN;
    }
    virtual ~QuickSortInt()
    {
        
    }
    private:
    function<void(vector<int>&,int,int)> quickHelp;
    
};

void QuickSortInt::onCreate()
{
    auto patitionFunc = [&](vector<int> &array,int start,int end,int &lessEnd,int &moreBegin)
    {
        int less = start -1;
        int more = end;
        while(start < more)
        {
            if (array[start] < array[end])
            {
                SortBase<int>::sky_swap(array[++less], array[start++]);
            }
            else if(array[start] > array[end])
            {
                SortBase<int>::sky_swap(array, --more, start);
            }
            else
            {
                start++;
            }
        }
        SortBase<int>::sky_swap(array, more, end);
        lessEnd = less;
        moreBegin = more+1;
    };
    
    quickHelp = [patitionFunc,this](vector<int>& array,int start,int end)
    {
        if(start < end)
        {
            int lessEnd = 0;
            int moreBegin = 0;
            patitionFunc(array,start,end,lessEnd,moreBegin);
            quickHelp(array,start,lessEnd);
            quickHelp(array,moreBegin,end);
        }
        return;
    };
    
    // when lambda need use the temp variate,we should capture it with the value(this will copy a clone to store for the lambda).if we capture it with the quote,when the action scope is finshed,the temp variate is freed,and the quote is becomed a bad_access error
    mSortFunc = [=](vector<int> &array)
    {
        int length = array.size();
        if(length < 2)
        {
            FUNC_PRINT_ALL("the length of array is too short", s);
            return true;
        }
        quickHelp(array,0,length-1);
        return true;
    };
}


#endif /* ALSort_h */
