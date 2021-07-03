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

private:
    int p;
    int q;
};

int Pow_base10(int n);

Rational Parser(QString str);

bool operator == (const Rational a, const Rational b);

Rational operator + (const Rational& a, const Rational& b);

Rational operator - (const Rational& a, const Rational& b);

Rational operator * (const Rational& a, const Rational& b);

Rational operator / (const Rational& a, const Rational& b);




