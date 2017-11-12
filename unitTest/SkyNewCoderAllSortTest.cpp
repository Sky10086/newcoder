#include "unitTest.h"
#include "ALSort.h"
class SkyNewCoderAllSortTest:public UnitTestBase
{
    public:
        virtual void run()
        {
            
            auto bubble = shared_ptr<SortBase<int>>(new BubbleSort<int>);
            bubble->onCreate();
            auto insertSort = shared_ptr<SortBase<int>>(new InsertSort<int>);
            insertSort->onCreate();
            auto selectSort = shared_ptr<SortBase<int>>(new ChooseSort<int>);
            selectSort->onCreate();
            auto quickSort = shared_ptr<SortBase<int>>(new QuickSort<int>);
            quickSort->onCreate();
            InRandom random(1,8000);
            
            for (int i = 0; i < 1; i++)
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
                bubble->onSort(bubbleRes);
                insertSort->onSort(insertRes);
                selectSort->onSort(selectRes);
                quickSort->onSort(quickRes);
                sort(compare.begin(), compare.end());
                for (int k = 0;k < compare.size();k++)
                {
                    GLASSERT(bubbleRes[k] == compare[k]);
                    GLASSERT(insertRes[k] == compare[k]);
                    GLASSERT(selectRes[k] == compare[k]);
                    GLASSERT(quickRes[k] == compare[k]);
                }
            }
        }
        SkyNewCoderAllSortTest(){}
        virtual ~SkyNewCoderAllSortTest(){}
};

static UnitTestRegister<SkyNewCoderAllSortTest> a("SkyNewCoderAllSortTest");
