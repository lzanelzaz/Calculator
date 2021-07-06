#pragma once

#include <QString>

class Rational
{
public:
    Rational();
    Rational(int numerator, int denominator);

    QString toString() const;

    qreal toDecimal() const;

    int Numerator() const;
    int Denominator() const;

protected:
    int p;
    int q;
};

int abs(int x); // absolute value
int pow_base10(int x); // x raised to the power of 10

Rational Parser(QString str); // parser from string to rational

bool operator == (const Rational a, const Rational b);

Rational operator + (const Rational& a, const Rational& b);

Rational operator - (const Rational& a, const Rational& b);

Rational operator * (const Rational& a, const Rational& b);

Rational operator / (const Rational& a, const Rational& b);




