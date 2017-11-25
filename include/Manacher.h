//
//  Manacher.h
//  sky_newcoder
//
//  Created by xiaosheng on 25/11/2017.
//
//

#ifndef Manacher_h
#define Manacher_h
#include <string>
using namespace std;

class Manacher
{
    private:
    /// 123 -> #1#2#3#
    void insertChar(string &str);
    public:
    /// time complex :O(N*N)
    int maxLcpsLengthOri(string str);
    /// time complex :O(N)
    int maxLcpsLength(string str);
};


#endif /* Manacher_h */
