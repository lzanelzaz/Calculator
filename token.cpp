#include "token.h"
#include "rational.h"
#include <QRegularExpression>
#include <QStringList>

template <typename T>
QString number_input (T& c, const QStringList& list){
    QString s = *c;
    if ( c+1 != list.end() && *(c+1) == "."){
        c = c+2;
        s += "." + *c;
    }
    return s;
}

QVector<Token> Tokenize(QString& str) {
  QVector<Token> tokens;
  QStringList list = str.split(QRegularExpression("\\b"));
  list.removeAll("");
  for (auto c = list.begin(); c != list.end(); c++) {
    if (*c == "-" && c == list.begin()){ // example: -1 + 1
            c++;
            tokens.push_back({"-" + number_input (c, list), TokenType::OPERAND});
    } else if (c->contains(QRegularExpression("\\d"))) {
        tokens.push_back({number_input (c, list), TokenType::OPERAND});
    } else {
        /* '/', '*', '-', '+', '(', ')' */
        tokens.push_back({(*c)[0], TokenType::LOGICAL_OP});
        if (c->count() == 2 ) { // example: -1 +- 1
            c++;
            tokens.push_back({"-" + number_input (c, list), TokenType::OPERAND});
        }
    }
  }
  return tokens;
}

