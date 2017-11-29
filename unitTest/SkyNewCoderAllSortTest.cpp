#include "unitTest.h"
#include "ALSort.h"
#include <map>
class SkyNewCoderAllSortTest:public UnitTestBase
{
    public:
        virtual void run()
        {
            InTime time;
            map<string,float> spendTime;
            spendTime.insert(make_pair("bubble", 0));
            spendTime.insert(make_pair("insert", 0));
            spendTime.insert(make_pair("select", 0));
            spendTime.insert(make_pair("quick", 0));
            spendTime.insert(make_pair("merge", 0));
            spendTime.insert(make_pair("heap", 0));
            spendTime.insert(make_pair("radix", 0));
            spendTime.insert(make_pair("system", 0));
            auto bubble = shared_ptr<SortBase<int>>(new BubbleSort<int>);
            bubble->onCreate();
            auto insertSort = shared_ptr<SortBase<int>>(new InsertSort<int>);
            insertSort->onCreate();
            auto selectSort = shared_ptr<SortBase<int>>(new ChooseSort<int>);
            selectSort->onCreate();
            auto quickSort = shared_ptr<SortBase<int>>(new QuickSort<int>);
            quickSort->onCreate();
//            auto quickSortInt = shared_ptr<SortBase<int>>(new QuickSortInt);
//            quickSortInt->onCreate();
            auto mergeSort =  shared_ptr<SortBase<int>>(new MergeSort<int>);
            mergeSort->onCreate();
            auto heapSort =  shared_ptr<SortBase<int>>(new HeapSort<int>);
            heapSort->onCreate();
            auto radixSort =  shared_ptr<SortBase<int>>(new RadixSort<int>);
            radixSort->onCreate();
            InRandom random(1,8000);
            
            for (int i = 0; i < 500; i++)
            {
                vector<int> array;
                for (int j = 0; j < 1000; j++)
                {
                    array.push_back(random.getRandom());
                }
                auto compare = (array);
                auto bubbleRes = array;
                auto insertRes = array;
                auto selectRes = array;
                auto quickRes = array;
                auto mergeRes = array;
                auto heapRes = array;
                auto radixRes = array;
                auto quickIntRes = array;
                TIME_START(spendTime.find("bubble")->first);
                bubble->onSort(bubbleRes);
                spendTime["bubble"]+=TIME_END_RETURN;
            
                TIME_START(spendTime.find("insert")->first);
                insertSort->onSort(insertRes);
                spendTime["insert"]+=TIME_END_RETURN;
                
                TIME_START(spendTime.find("select")->first);
                selectSort->onSort(selectRes);
                spendTime["select"]+=TIME_END_RETURN;
                
                TIME_START(spendTime.find("quick")->first);
                quickSort->onSort(quickRes);
                spendTime["quick"]+=TIME_END_RETURN;
                
                spendTime["merge"]+=mergeSort->onSort(mergeRes);
                
                spendTime["heap"]+=heapSort->onSort(heapRes);
                
                spendTime["radix"]+=radixSort->onSort(radixRes);
                
//                quickSortInt->onSort(quickIntRes);
                TIME_START(spendTime.find("system")->first);
                /// the speed is slower 200 times then the algorithm`s sort
                for (int k = 0; k < 100; k++)
                {
                    sort(compare.begin(), compare.end());
                }
                spendTime["system"]+=TIME_END_RETURN;
                for (int k = 0;k < compare.size();k++)
                {
                    GLASSERT(bubbleRes[k] == compare[k]);
                    GLASSERT(insertRes[k] == compare[k]);
                    GLASSERT(selectRes[k] == compare[k]);
                    GLASSERT(quickRes[k] == compare[k]);
                    GLASSERT(mergeRes[k] == compare[k]);
                    GLASSERT(heapRes[k] == compare[k]);
                    GLASSERT(radixRes[k] == compare[k]);
                }
            }
            
            for (auto iter: spendTime)
            {
                stringstream print;
                print << iter.first << ": " << iter.second<< endl;
                cout<<print.str();
            }
        }
        SkyNewCoderAllSortTest(){}
        virtual ~SkyNewCoderAllSortTest(){}
};

static UnitTestRegister<SkyNewCoderAllSortTest> a("SkyNewCoderAllSortTest");
