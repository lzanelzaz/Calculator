#pragma once

#include "token.h"

Rational ParseCondition(const QString& is);

Rational ParseOperation(QList<Token>& tokens);      // 2 numbers and operator between them

Rational ParseExpression(QList<Token>& tokens);     // whole expression

Rational ParseParentheses(QList<Token>& tokens);    // example: (1+2)
