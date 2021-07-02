#include "rational.h"
#include <QRegularExpression>

/* default = 0/1 */
Rational::Rational()
{
    p = 0;
    q = 1;
}

Rational::Rational(int numerator, int denominator)
{
    int a = numerator, b = denominator;
    /* Find Greatest Common Denominator - Euclidean algorithm */
    if (a != 1){
        while (a > 0 && b > 0) {
            if (a > b) {
                a %= b;
            }
            else {
                b %= a;
            }
        }
        a += b;
    }
    p = numerator / a;
    q = denominator / a;
    if (q < 0) {
        p = -p;
        q = -q;
    }
}

/* returns the value of n raise to the power of 10 *
 * in order to not use additional library          */
int Pow_base10(int n){
    int res = 1;
    while (n--){
        res *= 10;
    }
    return res;
}

Rational Parser(QString str)
{   /* if decimal */
    if (str.contains('.')) {
        int index = str.indexOf('.') + 1;
        index = str.length() - index;
        index = Pow_base10(index);
        return Rational(static_cast<int>(str.toDouble()*index), index);
    }
    /* if fraction */
    int index = str.indexOf(QRegularExpression("/")) + 1;
    /* if integer */
    if (index == 0){
        return Rational(str.toInt(), 1);
    }
    else {
        index = str.length() - index;
        return Rational(str.left(index).toInt(), str.right(index).toInt());
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
