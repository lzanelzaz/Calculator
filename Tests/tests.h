#pragma once

#include <QtTest/QTest>

#include "../expression_parser.h"
#include "../rational.h"
#include "../token.h"

class Tests : public QObject
{
    Q_OBJECT
public:
    explicit Tests();
private slots:
    void Test_Token();
    void Test_Rational();
    void Test_Expression_Parser();
};
