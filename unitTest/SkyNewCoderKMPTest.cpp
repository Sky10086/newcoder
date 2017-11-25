#include "unitTest.h"
#include "KMP.h"
#include "InTime.h"
#include<map>
class SkyNewCoderKMPTest:public UnitTestBase
{
    public:
        virtual void run()
        {
            InRandom random(0,2);
            int testNums = 900;
            KMP find;
            InTime time;
            map<string,float> spendTime;
            spendTime.insert(make_pair("ori", 0));
            spendTime.insert(make_pair("kmp", 0));
            spendTime.insert(make_pair("systemFind", 0));
            for (int i = 0; i < testNums; i++)
            {
                stringstream s1,s2;
                int j = 0;
                while (j++ < 1000)
                {
                    s1 << random.getRandom();
                }
                j = 0;
                while (j++ < 18)
                {
                    s2 << random.getRandom();
                }
                string str1 = s1.str();
                string str2 = s2.str();
//                str1 = "abcdefgabbcjjj";
//                str2 = "abbc";
                TIME_START("");
                bool res = find.isInclude(str1, str2);
                spendTime["kmp"]+=TIME_END_RETURN;
                TIME_START("");
                bool resOri = find.isIncludeOri(str1, str2);
                spendTime["ori"]+=TIME_END_RETURN;
                TIME_START("");
                bool answer = str1.find(str2) != string::npos;
                spendTime["systemFind"]+=TIME_END_RETURN;
                GLASSERT(res == answer);
                GLASSERT(resOri == answer);
                if (answer)
                {
                    FUNC_PRINT_ALL("find!", s);
                }
            }
            for (auto iter: spendTime)
            {
                stringstream print;
                print << iter.first << ": " << iter.second<< endl;
                cout<<print.str();
            }
        }
        SkyNewCoderKMPTest(){}
        virtual ~SkyNewCoderKMPTest(){}
};

static UnitTestRegister<SkyNewCoderKMPTest> a("SkyNewCoderKMPTest");
