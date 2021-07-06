#include "rational.h"

/* default = 0/1 */
Rational::Rational()
{
    p = 0;
    q = 1;
}

int abs(int x){     // absolute value
    if (x >= 0){
        return x;
    }
    return -x;
}

Rational::Rational(int numerator, int denominator)
{
    int a = numerator, b = denominator;
    /* Find Greatest Common Denominator - Euclidean algorithm */
    if (b == 1) {
        p = a;
        q = 1;
    }
    else if (b == -1){
        p = -a;
        q = 1;
    } else {
        while (abs(a) > 0 && abs(b) > 0) {
            if (abs(a) > abs(b)) {
                a %= b;
            }
            else {
                b %= a;
            }
        }
        a += b;
        p = numerator / a;
        q = denominator / a;
        if (q < 0) {
            p = -p;
            q = -q;
        }
    }
}

int pow_base10(int x){  // x raised to the power of 10
    int result = 1;
    while (x--){
        result *= 10;
    }
    return result;
}

Rational Parser(QString str)
{   /* if decimal */
    if (str.contains('.')) {
        int index = str.indexOf('.') + 1;
        index = str.length() - index;   // how many symbols after '.'
        index = pow_base10(index);
        return Rational(static_cast<int>(str.toDouble()*index), index);
    }
    /* if fraction */
    int index = str.indexOf("/") + 1;
    /* if integer */
    if (index == 0){
        return Rational(str.toInt(), 1);
    }
    else {
        return Rational(str.left(index-1).toInt(), str.right(str.length() - index).toInt());
    }
}

QString Rational::toString() const {
    return QString::number(p) + '/' + QString::number(q);
}

qreal Rational::toDecimal() const {
    qreal _p = p;
    return _p/q;
}

int Rational::Numerator() const
{
    return p;
}

int Rational::Denominator() const
{
    return q;
}

bool operator == (const Rational a, const Rational b) {
    if (a.Numerator() == b.Numerator() && a.Denominator() == b.Denominator()) {
        return true;
    }
    return false;
}

Rational operator + (const Rational& a, const Rational& b) {
    return Rational(a.Numerator() * b.Denominator() + b.Numerator() * a.Denominator(), a.Denominator() * b.Denominator());
}

Rational operator - (const Rational& a, const Rational& b) {
    return Rational(a.Numerator() * b.Denominator() - b.Numerator() * a.Denominator(), a.Denominator() * b.Denominator());
}

Rational operator * (const Rational& a, const Rational& b) {
    return Rational(a.Numerator() * b.Numerator(), a.Denominator() * b.Denominator());
}

Rational operator / (const Rational& a, const Rational& b) {
    return Rational(a.Numerator() * b.Denominator(), a.Denominator() * b.Numerator());
}
