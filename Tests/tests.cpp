#include "tests.h"

Tests::Tests() {}

enum class TokenType {
  OPERAND,      // number
  LOGICAL_OP,   // '/', '*', '-', '+'
  PAREN_LEFT,   // '('
  PAREN_RIGHT   // ')'
};

struct Token {
  QString value;
  TokenType type;
};

void Tests::Test_Token(){

    {
        QList<Token> t = { {"-2.1234", TokenType::OPERAND} };
        QCOMPARE(Tokenize("-2.1234"), t);
    }
    {
        QList<Token> t = { {"2", TokenType::OPERAND},
                           {"*", TokenType::LOGICAL_OP},
                           {"(", TokenType::PAREN_LEFT},
                           {"2.1234", TokenType::OPERAND},
                           {"+", TokenType::LOGICAL_OP},
                           {"-1/10", TokenType::OPERAND},
                           {")", TokenType::PAREN_RIGHT}
                         };
        QCOMPARE(Tokenize("2*(2.1234+-1/10)"), t);
    }
    {
        QList<Token> t = { {"8/-2", TokenType::OPERAND} };
        QCOMPARE(Tokenize("8/-2"), t);
    }
}

void Tests::Test_Rational(){

    QCOMPARE(abs(0), 0);
    QCOMPARE(abs(10), 10);
    QCOMPARE(abs(-10), 10);

    QCOMPARE(pow_base10(1), 10);
    QCOMPARE(pow_base10(2), 100);
    QCOMPARE(pow_base10(3), 1000);

    // constructor
    QCOMPARE(Rational(3, 10).toString(), "3/10");
    QCOMPARE(Rational(8, 12).toString(), "2/3");
    QCOMPARE(Rational(-4, 6).toString(), "-2/3");
    QCOMPARE(Rational(4, -6).toString(), "-2/3");
    QCOMPARE(Rational(0, 15).toString(), "0/1");

    // operators
    QCOMPARE(Rational(4, 6), Rational(2, 3));
    QCOMPARE(Rational(2, 3) + Rational(4, 3), Rational(2, 1));
    QCOMPARE(Rational(5, 7) - Rational(2, 9), Rational(31, 63));
    QCOMPARE(Rational(2, 3) * Rational(4, 3), Rational(8, 9));
    QCOMPARE(Rational(5, 4) / Rational(15, 8), Rational(2, 3));
    QCOMPARE(Rational(8, 1) / Rational(-2, 1), Rational(-4, 1));

    QCOMPARE(Parser("0.2"), Rational(2, 10));
    QCOMPARE(Parser("0.125"), Rational(1, 8));
    QCOMPARE(Parser("0.1125"), Rational(9, 80));
    QCOMPARE(Parser("2/10"), Rational(2, 10));
    QCOMPARE(Parser("2"), Rational(2, 1));

    QCOMPARE(Rational(2, 10).toDecimal(), 0.2);
}

void Tests::Test_Expression_Parser(){

    // ParseParentheses
    {
        QList t = Tokenize("(2+1)");
        QCOMPARE(ParseParentheses(t), Rational(3, 1));
    }
    {
        QList t = Tokenize("2");
        QCOMPARE(ParseParentheses(t), Rational(2, 1));
    }
    // ParseOperation
    {
        QList t = Tokenize("(2+1)/2");
        QCOMPARE(ParseOperation(t), Rational(3, 2));
    }
    {
        QList t = Tokenize("2+1");
        QCOMPARE(ParseOperation(t), Rational(3, 1));
    }
    {
        QList t = Tokenize("2*(-2+1)");
        QCOMPARE(ParseOperation(t), Rational(-2, 1));
    }
    // ParseExpression
    {
        QList t = Tokenize("(1+2)*(1+3)/(1+4)");
        QCOMPARE(ParseExpression(t), Rational(12, 5));
    }
    {
        QList t = Tokenize("1+5-1/10");
        QCOMPARE(ParseExpression(t), Rational(59, 10));
    }
    {
        QList t = Tokenize("-1+-1");
        QCOMPARE(ParseExpression(t), Rational(-2, 1));
    }
    {
        QList t = Tokenize("5/1+6/1");
        QCOMPARE(ParseExpression(t), Rational(11, 1));
    }
    {
        QList t = Tokenize("1+(2-5)*2");
        QCOMPARE(ParseExpression(t), Rational(-5, 1));
    }
    {
        QList t = Tokenize("1+2*(2-5)");
        QCOMPARE(ParseExpression(t), Rational(-5, 1));
    }
    // ParseCondition
    QCOMPARE(ParseCondition("1+2*8/-2"), Rational(-7, 1));
    QCOMPARE(ParseCondition("-9"), Rational(-9, 1));
    QCOMPARE(ParseCondition("3.285").toDecimal(), 3.285);
}
