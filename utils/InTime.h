//
// Created by xiaosheng on 2017/9/20.
//

#ifndef MAGICTOON_INTIME_H
#define MAGICTOON_INTIME_H

#include <chrono>
#include "GLDebug.h"
#include <string>
#include <sstream>
#include <random>
#include <stack>

//TODO add a func for debug show the time,release not
#ifdef BUILD_RELEASE
#define TIME_START(x) 
#define TIME_END
#else
#define TIME_START(x) time.start(x)
#define TIME_END time.endWithPrint()
#endif

class InTime
{
public:
    InTime()
    {
        
    }
    virtual ~InTime(){}
    void start(std::string tag)
    {
        mClock.push(std::chrono::steady_clock::now());
        mTag.push(tag);
    }
    const char* end()
    {
        std::chrono::duration<float > spend = std::chrono::steady_clock::now() - mClock.top();
        std::stringstream out;
        out << mTag.top() << " : ";
        out << spend.count();
        mClock.pop();
        mTag.pop();
        return out.str().c_str();
    }
    
    void endWithPrint()
    {
        std::chrono::duration<float > spend = std::chrono::steady_clock::now() - mClock.top();
        std::stringstream out;
        out << mTag.top() << " : ";
        out << spend.count();
        auto time = out.str().c_str();
        FUNC_PRINT_ALL(time, s);
        mClock.pop();
        mTag.pop();
    }
private:
    std::stack<std::chrono::time_point<std::chrono::steady_clock,std::chrono::duration<float >>> mClock;
    std::stack<std::string> mTag;
};
class InRandom
{
public:
    InRandom(int start,int end)
    {
        std::default_random_engine generator(time(NULL));
        std::uniform_int_distribution<int> dis(start,end);
        mGenerator = generator;
        mDis = dis;
        mStart =start;
        mEnd =end;
    }
    void setRange(int start,int end)
    {
        mStart = start;
        mEnd =end;
        std::uniform_int_distribution<int> dis(start,end);
        mDis = dis;
    }
    int getRandom()
    {
        return mDis(mGenerator);
    }
private:
    int mStart;
    int mEnd;
    std::uniform_int_distribution<int> mDis;
    std::default_random_engine mGenerator;
};

#endif //MAGICTOON_INTIME_H
