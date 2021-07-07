#pragma once

#include <QList>
#include "rational.h"

enum class TokenType;

struct Token;

QString number_input (QString::const_iterator& c, const QString& list);

QList<Token> Tokenize(const QString& str);

bool operator== (const Token& a, const Token& b);
