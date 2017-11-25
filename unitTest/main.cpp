//
//  main.cpp
     //  sky_newcoder
//
//  Created by xiaosheng on 11/11/2017.
//
//

#include "unitTest.h"

template <class T>
void testfunc(T &a,vector<T> &array)
{
    function<T(vector<T>&,T&)> add2 = [&](vector<T>&array,T& a){
        a++;
        array[0]++;
        return a;
    };
    
    function<T(T&)> add = [&](T& a){
        a++;
        if (a < 100)
        {
            add2(array,a);
        }
        return 0;
    };
    add(a);
}

bool compare(int a,int b)
{
    return a-b >= 0;
}

int main()
{
    TestInstanse::runUnitTest();
    
//    int a = 9;
//    vector<int> v{1,5,4,1,8,9,0,33};
//    v.erase(v.begin());
//    sort(v.begin(), v.end(), &compare);
//    testfunc<int>(a,v);
//    cout<<a<<endl;
//    return 0;
}


