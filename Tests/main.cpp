#include <QCoreApplication>
#include <QtTest/QTest>
#include "tests.h"

int main(int argc, char *argv[])
{
    freopen("testing.log", "w", stdout);
    QCoreApplication a(argc, argv);
    QTest::qExec(new Tests, argc, argv);
    return 0;
}
