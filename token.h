#pragma once

#include <QString>
#include <QList>

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

QList<Token> Tokenize(const QString& cl);

bool operator== (const Token& a, const Token& b);
