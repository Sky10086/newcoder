
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
    function<void(vector<T>&,int,int)> mQuickSort;
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
    
    mQuickSort = [&](vector<T> &array,int start,int end)
    {
        if (start < end)
        {
            /// the random will get [start,end) ?
            auto index = InRandom(start,end).getRandom();
            base::sky_swap(array[index], array[end]);
            int lessEnd = 0;
            int moreBegin = 0;
            mPartitionFunc(array,start,end,lessEnd,moreBegin);
            mQuickSort(array,start,lessEnd);
            mQuickSort(array,moreBegin,end);
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
        mQuickSort(array,0,len-1);
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
    function<void(vector<int>&,int,int)> mQuickSort;
    
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
    
    mQuickSort = [patitionFunc,this](vector<int>& array,int start,int end)
    {
        if(start < end)
        {
            int lessEnd = 0;
            int moreBegin = 0;
            patitionFunc(array,start,end,lessEnd,moreBegin);
            mQuickSort(array,start,lessEnd);
            mQuickSort(array,moreBegin,end);
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
        mQuickSort(array,0,length-1);
        return true;
    };
}


/**
 mergeSort:
 1 part the array to arr1 and arr2 with the length n/2
 2 recursion 1 ,until the subArray.lengh is 1
 3 merge the subArr1(orderd,when it`s len is 1 ,is ordered of course),subArr2(the same as subArr1) ,from the buttom to the top(from subArr`s len 1 to n/2)
 
 example:
 [2]  [1]   [4]   [5]   [8]    [7]       ---------bottom
    |        |        |         |
  [1 2]      [4]    [5 8]       [7]
         |                  |
      [1 2 4]           [5 7 8]
                |
        [1 2 4 5 7 8]                    ---------top
 this is the 3 step,merge from bottom to top
 */
template <class T>
class MergeSort : public SortBase<T>
{
    typedef SortBase<T> base;
    public:
    virtual void onCreate();
    virtual float onSort(vector<T> &array)
    {
        InTime time;
        TIME_START("");
        base::mSortFunc(array);
        return TIME_END_RETURN;
    }
    private:
    function<void(vector<T>&,int,int)> mMergeSort;
    function<void(vector<T>&,int,int,int)> mMerge;
};

template <class T>
void MergeSort<T>::onCreate()
{
    base::mSortFunc = [&](vector<T>&array)
    {
        int len = array.size();
        if (len < 2)
        {
            FUNC_PRINT_ALL("array len < 2", s)
            return false;
        }
        mMergeSort(array,0,len-1);
        return true;
    };
    
    mMergeSort = [&](vector<T>&array,int start,int end)
    {
        if (start < end)
        {
//            int mid = (start+end)/2;
            // better avoid overflow
            int mid = start + (end-start)/2;
            mMergeSort(array,start,mid);
            mMergeSort(array,mid+1,end);
            mMerge(array,start,end,mid);
        }
        return;
    };
    
    mMerge = [](vector<T>&array,int start,int end,int mid)
    {
        vector<T> tempArr(end-start+1);
        int index = 0;
        int arrSta1 = start;
        int arrSta2 = mid+1;
        while (arrSta1 <= mid && arrSta2 <= end)
        {
            if (array[arrSta1] < array[arrSta2])
            {
//                tempArr.push_back(array[arrSta1++]);
                // better avoid malloc too much times
                tempArr[index++] = array[arrSta1++];
            }
            else
            {
//                tempArr.push_back(array[arrSta2++]);
                tempArr[index++] = array[arrSta2++];
            }
        }
        
        while (arrSta2 <= end)
        {
//            tempArr.push_back(array[arrSta2++]);
            tempArr[index++] = array[arrSta2++];
        }
        while (arrSta1 <= mid)
        {
//            tempArr.push_back(array[arrSta1++]);
            tempArr[index++] = array[arrSta1++];
        }
        for (int i =start; i <= end; i++)
        {
            array[i] = tempArr[i-start];
        }
    };
}

/**
 heapSort:
 we think of the array as a entirely binary-tree,we also call it as 'heap'
 so the left child of array[i] is array[2*i+1] ,right child is array[2*i+2]
 the father of array[i] is array[(i-1)/2]
 wo sort the array by these steps:
 1 crate the Big-Root-Heap(the heap which all father is biger than its all children(include the subChildren))
 2 adjust the Big-Root-Heap,every time swap the root to the end of the array,and the heap`s length mins 1
 3 when heap`s length is 1,the array is sorted
 */
template <class T>
class HeapSort : public SortBase<T>
{
    typedef SortBase<T> base;
    public:
    
    virtual void onCreate();
    virtual float onSort(vector<T> &array)
    {
        InTime time;
        TIME_START("");
        base::mSortFunc(array);
        return TIME_END_RETURN;
    }
    private:
    function<void(vector<T>&,int,int)> mCreateBigHeap;
    function<void(vector<T>&,int,int)> mAdjHeap;
};

template <class T>
void HeapSort<T>:: onCreate()
{
    base::mSortFunc = [&](vector<T>&array)
    {
        int len = array.size();
        if (len < 2)
        {
            FUNC_PRINT_ALL("array len < 2", s)
            return false;
        }
        mCreateBigHeap(array,0,len-1);
        mAdjHeap(array,0,len-1);
        return true;
    };
    
    mCreateBigHeap = [&](vector<T>&array,int start,int end)
    {
        for (int i = start; i <= end; i++)
        {
            int fatherIndex = (i-1)/2;
            int aimIndex = i;
            while (fatherIndex >= start && array[fatherIndex]< array[aimIndex])
            {
                base::sky_swap(array,fatherIndex,aimIndex);
                aimIndex = fatherIndex;
                fatherIndex = (fatherIndex-1)/2;
            }
        }
    };
    mAdjHeap = [&](vector<T>&array,int start,int end)
    {
        while (end > start)
        {
            base::sky_swap(array,start,end);
            end--;
            int adjIndex = start;
            
//            while ((2*adjIndex+2) <= end && array[adjIndex] < max(array[2*adjIndex+1],array[2*adjIndex+2]))
//            {
//                int bigIndex = array[2*adjIndex+1] > array[2*adjIndex+2] ? 2*adjIndex+1 : 2*adjIndex+2;
//                base::sky_swap(array,adjIndex,bigIndex);
//                adjIndex = bigIndex;
//            }
//            if(2*adjIndex+1 <= end && array[2*adjIndex+1] > array[ adjIndex])
//            {
//                base::sky_swap(array,adjIndex,2*adjIndex+1);
//            }
            
            // both result is right
            int left = 2*adjIndex+1;
            while (left <= end)
            {
                int bigChild = left;
                if(left+1 <= end && array[left+1] > array[left])
                {
                    bigChild = left+1;
                }
                if(array[adjIndex] > array[bigChild])
                {
                    break;
                }
                base::sky_swap(array,bigChild,adjIndex);
                adjIndex = bigChild;
                left = 2*adjIndex+1;
            }
        }
    };
}

template <class T>
class RadixSort :public SortBase<T>
{
    typedef SortBase<T> base;
    public:
    virtual void onCreate();
    virtual float onSort(vector<T> &array)
    {
        InTime time;
        TIME_START("");
        base::mSortFunc(array);
        return TIME_END_RETURN;
    }
    public:
};

template <class T>
void RadixSort<T>::onCreate()
{
    auto getRadixLen = [](int num){
        int len = 0;
        while (num)
        {
            len++;
            num /= 10;
        }
        return len;
    };
    auto getDigit = [](int num,int d){
        while (--d)
        {
            num/=10;
        }
        return num%10;
    };
    base::mSortFunc = [getRadixLen,getDigit,this](vector<T>&array){
        int len = array.size();
        if (len < 2)
        {
            FUNC_PRINT_ALL("len is less than 2", s);
            return true;
        }
        vector<int> countArr(10);
        int max = array[0];
        for (auto num : array)
        {
            max = num > max ? num : max;
        }
        int sortTimes = getRadixLen(max);
        vector<T> tempSortArr(len);
        for (int i = 1; i <= sortTimes; i++)
        {
            for (auto num : array)
            {
                int digit = getDigit(num,i);
                while (digit<10)
                {
                    countArr[digit++]++;
                }
            }
            for (int j = len-1; j >=0; j--)
            {
                int digit = getDigit(array[j],i);
                tempSortArr[--countArr[digit]] = array[j];
            }
            array = tempSortArr;
            countArr.assign(10, 0);
        }
        return true;
    };
}
#endif /* ALSort_h */
