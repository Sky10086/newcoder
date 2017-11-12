#include "ALSort.h"



//template <class T>
//void BubbleSort<T>::onCreate()
//{
//    
//}



void swap(int &a,int &b);
void bubbleSort(std::vector<int> &arr)
{
    int length = arr.size();
    for(int i = length-1; i >= 0;i--)
    {
        for(int j = 0;j < i;j++)
        {
            if(arr[j] > arr[j+1])
            swap(arr[j],arr[j+1]);
        }
    }
}

void swap(int &a,int &b)
{
    /// a and b must not be the same adddress
    a = a ^ b;
    b = a^b;
    a = a^b;
}

void insertSort(std::vector<int> &arr)
{
    int length = arr.size();
    if(length <= 1)
        return;
    for(int i = 1;i < length ; i++)
    {
        for(int j = i-1; j >= 0 && arr[j+1] < arr[j];j--)
        {
            swap(arr[j],arr[j+1]);
        }
    }
}
void chooseSort(std::vector<int> &arr)
{
    int length = arr.size();
    if(length <= 1)
        return;
    for(int i = 1;i < length ; i++)
    {
        for(int j  =  i-1; j >= 0 && arr[j+1] < arr[j];j--)
        {
            swap(arr[j],arr[j+1]);
        }
    }
}
void quikSort(std::vector<int> &arr)
{
    int length = arr.size();
    if(length <= 1)
        return;
    for(int i = 1;i < length ; i++)
    {
        for(int j = i-1; j >= 0 && arr[j+1] < arr[j];j--)
        {
            swap(arr[j],arr[j+1]);
        }
    }
    return;
}
