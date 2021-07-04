#include "token.h"
#include "rational.h"
template <typename T>
QString number_input (T& c, const QString& list){ // example: 2.125
    QString s = *c;
    while (c+1 != list.end() && ((c+1)->isDigit() || (*(c+1) == '.' || *(c+1) == '/'))){
        s += *(++c);
    }
    return s;
}
// example: -1+-1; 2*(1+3); (1+3)*2; (1+5)*(4+2); 5/1 + 6/1
QList<Token> Tokenize(const QString& str) {
  QList<Token> tokens;
  for (auto c = str.begin(); c != str.end(); c++) {
    if (*c == '-' && (c+1)->isDigit() && (c == str.begin() || !(c-1)->isDigit())){ // example: -1+-1
            c++;
            tokens.push_back({"-" + number_input(c, str), TokenType::OPERAND});
    } else if (c->isDigit()) {
        tokens.push_back({number_input (c, str), TokenType::OPERAND});
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
