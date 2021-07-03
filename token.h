#pragma once

#include <QString>
#include <QVector>
#include <QStack>

enum class TokenType {
  OPERAND,
  LOGICAL_OP,
  PAREN_LEFT,
  PAREN_RIGHT
};

struct Token {
  QString value;
  TokenType type;
};

QVector<Token> Tokenize(QString& cl);
