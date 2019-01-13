#ifndef TST_GAUSSTESTS_H
#define TST_GAUSSTESTS_H

#include <QtTest>

class GaussTests : public QObject
{

    Q_OBJECT
private slots:
    void int2x2();
    void float2x2();
    void inconsistent2x2();

    void inconsistentRealCase();
};

#endif // TST_GAUSSTESTS_H
