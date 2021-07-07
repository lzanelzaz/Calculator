#include "token.h"

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

QString number_input (QString::const_iterator& c, const QString& list){ // example: 2.125; 2/-125
    QString s = *c; // get first char
    while (c+1 != list.end() &&
           ((c+1)->isDigit() || *(c+1) == '.' || *(c+1) == '/' || ( *(c+1) == '-' && *c == '/' ))
          ){
        s += *(++c);
    }
    return s;
}

// example: -1+-1; 2*(1+3); (1+3)*2; (1+5)*(4+2); 5/1 + 6/1
QList<Token> Tokenize(const QString& str) {
  QList<Token> tokens;
  for (QString::const_iterator c = str.begin(); c != str.end(); c++) {
    if (*c == '-' && (c+1)->isDigit() &&            // example: -1+-1
        (c == str.begin() || !(c-1)->isDigit())){
            c++;
            tokens.push_back({"-" + number_input(c, str), TokenType::OPERAND});
    } else if (c->isDigit()) {
        tokens.push_back({number_input(c, str), TokenType::OPERAND});
    } else if (*c == '(') {
        tokens.push_back({"(", TokenType::PAREN_LEFT});
    } else if (*c == ')') {
        tokens.push_back({")", TokenType::PAREN_RIGHT});
    } else {
        /* '/', '*', '-', '+' */
       tokens.push_back({*c, TokenType::LOGICAL_OP});
    }
  }
  return tokens;
}

bool operator== (const Token& a, const Token& b){
    if (a.value == b.value && a.type == b.type){
        return true;
    }
    return false;
}

