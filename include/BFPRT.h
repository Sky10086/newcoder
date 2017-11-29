//
//  BFPRT.h
//  sky_newcoder
//
//  Created by xiaosheng on 26/11/2017.
//
//

#ifndef BFPRT_h
#define BFPRT_h
#include <vector>
#include "GLDebug.h"
#include<functional>
using namespace std;

template <class T>
class BFPRT
{
    public:
    
    /**
     find the Kth num in the array from start index to the end index
     time complexity O(N)

     @param array
     @param k
     @return
     */
    T findKthNum(vector<T> array,int start,int end,int k);
    
};

/// every sub array hava NUM_VALUE numbers
#define NUM_VALUE 5

template <class T>
T BFPRT<T>::findKthNum(vector<T> array, int start,int end,int k)
{
    if (start == end)
    {
        return array[start];
    }
    GLASSERT(end > start);
//    GLASSERT(end-start+1>= k);
    GLASSERT(k > 0);
    auto getMidNum = [=](vector<T> array,int start,int end){
        int length = end - start +1;
        int offset = length%NUM_VALUE;
        int subArrNum = length/NUM_VALUE+(offset==0?0:1);
        vector<T> midArr(subArrNum);
        auto begin = array.begin();
        for (int i = start; i <= end-NUM_VALUE+1; i+=NUM_VALUE)
        {
//            sort(array.begin(), array.begin()+5);
            sort(begin+i,begin+i+NUM_VALUE);
            midArr[(i-start)/NUM_VALUE] = *(begin+i+(NUM_VALUE-1)/2);
        }
        if (offset)
        {
            int idxLen = offset-1;
            sort(begin+end-idxLen, begin+end+1);
            midArr[subArrNum-1] = (*(begin+end-idxLen+idxLen/2));
        }
        return findKthNum(midArr, 0, subArrNum-1,(subArrNum)/2);
    };
    auto swap = [](vector<T> &arr,int a,int b)
    {
        T temp = arr[a];
        arr[a] = arr[b];
        arr[b] = temp;
    };
    auto partionSort = [swap](vector<T>& array,int start,int end,int p,int& lessEnd,int& moreBegin)
    {
        int less = start-1;
        int more = end+1;
        while (start < more)
        {
            if (array[start] < p)
            {
                // the less domain`s next is the equal ,so just swap and start++, actually,when the equal domain length is 0,this is the less+1 == start,is swaped by itself,this also can be reprasent by this code
                swap(array,++less,start++);
            }
            else if(array[start] > p)
            {
                swap(array,--more,start);
            }
            else
            {
                start++;
            }
        }
        lessEnd = less;
        moreBegin = more;
    };
    
    function<T(vector<T>&,int,int,int)> select = [&](vector<T>&array,int start,int end,int index)
    {
        int mid = getMidNum(array,start,end);
        int lessEnd = -1;
        int moreBegin = -1;
        partionSort(array,start,end,mid,lessEnd,moreBegin);
        if (lessEnd < index && index < moreBegin)
        {
            //reruen array[index];
            return mid;
        }
        else if(index >= moreBegin)
        {
            return select(array, moreBegin, end, index);
        }
        else
        {
            return select(array, start, lessEnd, index);
        }
    };
    return select(array,start,end,start+k-1);
}


#endif /* BFPRT_h */
