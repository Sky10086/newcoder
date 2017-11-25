//
//  Manacher.cpp
//  sky_newcoder
//
//  Created by xiaosheng on 25/11/2017.
//
//

#include <stdio.h>
#include <sstream>
#include <vector>
#include "Manacher.h"

void Manacher::insertChar(string &str)
{
    stringstream s;
    for (auto c :str)
    {
        s << '#' << c;
    }
    s<<'#';
    str = s.str();
    return;
}

int Manacher::maxLcpsLength(string str)
{
    if (str.length() < 1)
    {
        return 0;
    }
    insertChar(str);
    /// the most right border
    int maxR = -1;
    /// the first center
    int c = -1;
    vector<int> ratio(str.length(),1);
    int length = str.length();
    int tempRatio = 0;
    int maxRatio = 1;
    for (int index = 0; index < length; index++)
    {
        if (index >= maxR)
        {
            tempRatio = 1;
        }
        else
        {
            tempRatio = min(ratio[2*c -index],maxR-index);
        }
        while (index-tempRatio >= 0 && index+tempRatio  < length && str[index-tempRatio] == str[index+tempRatio])
        {
            tempRatio++;
        }
        if (index+tempRatio > maxR)
        {
            maxR = index+tempRatio;
            c = index;
        }
        ratio[index] = tempRatio;
        maxRatio = max(tempRatio,maxRatio);
    }
    return (2*maxRatio-1)/2;
}

int Manacher::maxLcpsLengthOri(string str)
{
    if (str.length() < 1)
    {
        return 0;
    }
    insertChar(str);
    int maxRatio = 0;
    for (int i = 0; i < str.length(); i++)
    {
        int ratio = 1;
        while (i -ratio > -1 && i+ratio<str.length() && str[i-ratio]==str[i+ratio])
        {
            ratio++;
        }
        maxRatio = max(maxRatio,ratio);
    }
    return (2*maxRatio-1)/2;
}
