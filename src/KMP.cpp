//
//  KMP.cpp
//  sky_newcoder
//
//  Created by xiaosheng on 25/11/2017.
//
//

#include "KMP.h"

bool KMP::isIncludeOri(string s1, string s2)
{
#ifdef FIRST_CODE
    for (int i = 0; i < s1.length();i++)
    {
        int  index1 = i;
        for (int j = 0; j < s2.length(); j++)
        {
            if (s1[index1] == s2[j])
            {
                index1++;
                if (j == s2.length()-1)
                {
                    return true;
                }
                if (index1 == s1.length())
                {
                    return false;
                }
            }
            else
            {
                break;
            }
        }
    }
    return false;
#endif
    
    int i1 = 0;
    int i2 = 0;
    /// for back the i1 index
    int len = 0;
    while (i1 < s1.length() && i2 < s2.length())
    {
        if (s1[i1] == s2[i2])
        {
            i1++;
            i2++;
            len++;
        }
        else if(i2 == 0)
        {
            i1++;
            len = 0;
        }
        else
        {
            i2 = 0;
            i1 -= (len-1);
            len = 0;
        }
    }
    return i2 == s2.length();
}


void KMP::createNextArr(string s, vector<int>& next)
{
    GLASSERT(s.length()>1);
    next[0] = -1;
    next[1] = 0;
    for (int i = 2; i < s.length(); i++)
    {
        int aimInex = next[i-1];
        while (aimInex != -1 && s[aimInex] != s[i-1])
        {
            aimInex = next[aimInex];
        }
        next[i] = aimInex+1;
    }
}

bool KMP::isInclude(string s1, string s2)
{
    if (s2.length() > s1.length() || s2.length() < 1)
    {
        return false;
    }
    if (s2.length() == 1)
    {
        for (int i = 0; i < s1.length(); i++)
        {
            if (s2[0] == s1[i])
            {
                return true;
            }
        }
    }
    vector<int> next(s2.length());
    createNextArr(s2, next);
    int indexS2 = 0;
    int indexS1 = 0;
    while (indexS1 < s1.length() && indexS2 < s2.length())
    {
        if (s1[indexS1] == s2[indexS2])
        {
            indexS1++;
            indexS2++;
        }
        else if(next[indexS2] == -1)
        {
            indexS1++;
        }
        else
        {
            indexS2 = next[indexS2];
        }
    }
    return indexS2 == s2.length();
    
/// the code above is much clearness to read,the result are both right
#ifdef FIRST_CODE
    for (; indexS1 < s1.length();)
    {
        while (s1[indexS1] == s2[indexS2])
        {
            indexS1++;
            indexS2++;
            if (indexS2 == s2.length())
            {
                return true;
            }
            if (indexS1 == s1.length())
            {
                return false;
            }
        }
        indexS2 = next[indexS2];
        if (indexS2 == -1)
        {
            indexS2 = 0;
            indexS1++;
        }
    }
    return false;
#endif
}
