#include "testbox.h"

TestBox::TestBox()
{ qsrand (QDateTime::currentMSecsSinceEpoch());
    /*vec.push_back(Test("First","one",11));
    vec.push_back(Test("Second","two",22));
    vec.push_back(Test("Third","three",33));
    vec.push_back(Test("Fourth","four",44));
    vec.push_back(Test("Fifth","five",55));
    */
}

void TestBox::Randomize()
{
    //qsrand (QDateTime::currentMSecsSinceEpoch());
    int size = qrand()%12 + 1;
    for(int i=0;i<size;++i)
        vec.push_back(Test(QString::number(qrand()%100+1),qrand()%50+25,i));
}
