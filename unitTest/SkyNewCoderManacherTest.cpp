#include "unitTest.h"
#include "Manacher.h"
#include "InTime.h"
#include<map>
class SkyNewCoderManacherTest:public UnitTestBase
{
    public:
        virtual void run()
        {
            InRandom random(0,4);
            InRandom random2(5,9);
            InRandom random3(1,400);
            InRandom random4(1,1000);
            int testNums = 500;
            Manacher find;
            InTime time;
            map<string,float> spendTime;
            spendTime.insert(make_pair("oriFindLcps", 0));
            spendTime.insert(make_pair("manacher", 0));
            for (int i = 0; i < testNums; i++)
            {
                stringstream s1,s2;
                int j = 0;
                int len = random3.getRandom()+100;
                while (j++ < len)
                {
                    s1 << random2.getRandom();
                }
                j = 0;
                while (j++ < random3.getRandom())
                {
                    s2 << random4.getRandom();
                }
                s2 << "*";
                string str1 = s1.str();
                s2 << str1;
                reverse(str1.begin(),str1.end());
                s2 << str1;
                s2 << "!";
                j=0;
                while (j++ < random3.getRandom())
                {
                    s2 << random4.getRandom();
                }
                string str2 = s2.str();
                //                str1 = "abcdefgabbcjjj";
                //                str2 = "abbc";
                TIME_START("");
                int res = find.maxLcpsLength(str2);
                spendTime["manacher"]+=TIME_END_RETURN;
                TIME_START("");
                int oriRes = find.maxLcpsLengthOri(str2);
                spendTime["oriFindLcps"]+=TIME_END_RETURN;
                GLASSERT(2*len==res);
                GLASSERT(2*len==oriRes);
                
            }
            for (auto iter: spendTime)
            {
                stringstream print;
                print << iter.first << ": " << iter.second<< endl;
                cout<<print.str();
            }
        }
        SkyNewCoderManacherTest(){}
        virtual ~SkyNewCoderManacherTest(){}
};

static UnitTestRegister<SkyNewCoderManacherTest> a("SkyNewCoderManacherTest");
