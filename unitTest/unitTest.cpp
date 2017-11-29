#include <iostream>
#include "unitTest.h"
#include "InTime.h"
using namespace std;

/// why here can visit the private static member,but in hte function ,it can not be visited.answer,this is not called be visited,this is a define statement,is initialized! int a = 0;(this is define and initial) a = 2;(this is called be visited,and this statement is invalid in the global domain)
//shared_ptr<TestInstanse> TestInstanse::gTestInstance;
TestInstanse* TestInstanse::gTestInstance=NULL;

/// why in the global domain,can not write the logic statement

//shared_ptr<TestInstanse> TestInstanse::get()
//{
//    if (NULL == gTestInstance.get())
//    {
//        gTestInstance = std::shared_ptr<TestInstanse>(new TestInstanse);
//    }
//    return gTestInstance;
//}

TestInstanse* TestInstanse::get()
{
    if (NULL == gTestInstance)
    {
        gTestInstance = (new TestInstanse);
    }
    return gTestInstance;
}

void TestInstanse::insert(shared_ptr<UnitTestBase> unit, string name)
{
    unit->mName = name;
    mUnitTest.push_back(unit);
}

void TestInstanse::runUnitTest()
{
    get();
    InTime time;
    for (int i = 0; i < gTestInstance->mUnitTest.size(); i++)
    {
        auto unitTest = gTestInstance->mUnitTest[i];
        TIME_START(unitTest->mName);
        unitTest->run();
        TIME_END;
    }
    return;
}


