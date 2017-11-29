#include "unitTest.h"
#include "BFPRT.h"
#include "ALSort.h"
#include "InTime.h"
#include <map>
using namespace std;
class SkyNewCoderBFPRTTest:public UnitTestBase
{
    public:
        virtual void run()
        {
            InTime time;
            map<string,float> spendTime;
            spendTime.insert(make_pair("BFPRT", 0));
            spendTime.insert(make_pair("quickSortKth", 0));
            auto quickSort = new QuickSort<int>;
            quickSort->onCreate();
            BFPRT<int> find;
            InRandom random(1,8000);
            for (int i = 0; i < 500; i++)
            {
                vector<int> arr;
                int j = 0;
                int len = 10000;
                while (j++ < len)
                {
                    arr.push_back(random.getRandom());
                }
                
                int start = 0;
                int end = len-1;
                random.setRange(1, end-start);
                int k = random.getRandom();
                TIME_START("");
                int num = find.findKthNum(arr, start, end,k);
                spendTime["BFPRT"]+=TIME_END_RETURN;
                
                TIME_START("");
//                for(int i= 0;i < 100;i++)
//                sort(arr.begin()+start,arr.begin()+end+1);
                quickSort->onSort(arr);
                spendTime["quickSortKth"]+=TIME_END_RETURN;
                GLASSERT(arr[start+k-1] == num);
            }
            for (auto iter: spendTime)
            {
                stringstream print;
                print << iter.first << ": " << iter.second<< endl;
                cout<<print.str();
            }
            delete quickSort;
        }
        SkyNewCoderBFPRTTest(){}
        virtual ~SkyNewCoderBFPRTTest(){}
};

static UnitTestRegister<SkyNewCoderBFPRTTest> a("SkyNewCoderBFPRTTest");
