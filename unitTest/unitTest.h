#include<iostream>
#include <vector>
#include <memory>
using namespace std;

class UnitTestBase
{
    friend class TestInstanse;
public:
    UnitTestBase()
    {
        
    }
    virtual void run() = 0;
    virtual ~UnitTestBase()
    {
        
    }
private:
    string mName;
};

class TestInstanse
{
public:
    virtual ~TestInstanse()
    {
        
    }
    static shared_ptr<TestInstanse> get();
    static void runUnitTest();
    void insert(shared_ptr<UnitTestBase> unit,string name);
    
private:
    TestInstanse(){}
    vector<shared_ptr<UnitTestBase>> mUnitTest;
    static shared_ptr<TestInstanse> gTestInstance;
};

template <class T>
class UnitTestRegister
{
    public:
    UnitTestRegister(string name)
    {
        auto unit = std::shared_ptr<UnitTestBase>(new T);
        TestInstanse::get()->insert(unit, name);
    }
};
