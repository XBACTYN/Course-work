#ifndef TESTBOX_H
#define TESTBOX_H

#include <QVector>
#include "test.h"
#include <QRandomGenerator>
#include <QDateTime>

class TestBox
{
public:
    QVector<Test> vec;
    TestBox();
    void Randomize();
};

#endif // TESTBOX_H
