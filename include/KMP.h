//
//  KMP.hpp
//  sky_newcoder
//
//  Created by xiaosheng on 25/11/2017.
//
//

#ifndef KMP_h
#define KMP_h

#include <stdio.h>
#include <string>
#include <vector>
#include "GLDebug.h"
using namespace std;
class KMP
{
    public:
    /// use the ori func time complex: O(N*M)
    bool isIncludeOri(string s1,string s2);
    /// use the kmp algorithm O(N)
    bool isInclude(string s1,string s2);
    private:
    void createNextArr(string s,vector<int>& next);
};

#endif /* KMP_h */
