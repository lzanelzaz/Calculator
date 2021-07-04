#include "expression_parser.h"
#include <QRegularExpression>
#include "token.h"
#include "rational.h"

Rational ParseOperation(QList<Token>& tokens);

Rational ParseExpression(QList<Token>& tokens, unsigned precedence);

Rational ParseOperation(QList<Token>& tokens) {
    Rational fOperand1 = Parser(tokens.takeFirst().value);
    QString strOperation = tokens.takeFirst().value;
    Rational fOperand2;
    if (tokens.first().value == "("){
        int index = tokens.indexOf({")", TokenType::PAREN_RIGHT});
        auto t = tokens.sliced(1, index-1);
      fOperand2 = ParseExpression(t, 1);

        tokens.remove(0, index+1);
    } else {
        fOperand2 = Parser(tokens.takeFirst().value);
    }
    Rational res;
    if (strOperation == "+") {
        res = fOperand1 + fOperand2;
    }
    else if (strOperation == "-"){
        res = fOperand1 - fOperand2;
    }
    else if (strOperation == "/") {
        res = fOperand1 / fOperand2;
    }
    else if (strOperation == "*") {
        res = fOperand1 * fOperand2;
    }
     tokens.prepend({res.toString(), TokenType::OPERAND});
     foreach(Token s, tokens){
         qDebug() << s.value;
     }
   qDebug() << '\n';
    return res;
}

Rational ParseExpression(QList<Token>& tokens, unsigned precedence) {
  if (tokens.begin() == tokens.end()) {
      qDebug() << "Impossible";
    return Rational(1,0);
  }
  Rational left;

  while (tokens.begin()+1 != tokens.end()) {
      if (tokens.at(1).type != TokenType::LOGICAL_OP) {
        qDebug() << "Expected logic operation";
      }
      if (precedence){}
/*
     const LogicalOperation logical_operation = tokens.contains({"/", TokenType::LOGICAL_OP}) || tokens.contains({"*", TokenType::LOGICAL_OP}) ?
                                                 LogicalOperation::Division_or_multiplication : LogicalOperation::Plus_or_minus;

      const unsigned current_precedence = static_cast<unsigned>(logical_operation);
      left = ParseExpression(tokens, current_precedence);
      if (current_precedence <= precedence) {

      } */
      if (tokens.first().type == TokenType::PAREN_LEFT) {
        // consume '('
        tokens.pop_front();
        left = ParseOperation(tokens);
        if (tokens.begin()+1 == tokens.end() || tokens.at(1).type != TokenType::PAREN_RIGHT) {
          qDebug() << "Missing right paren";
          return Rational(1,0);
        }
        // consume ')'
        tokens.remove(1, 1);
      } else {
        left = ParseOperation(tokens);
      }
  }
  return left;
}
// 2*(1-5) + 1/10
// 2*(1+(2-5))+1
Rational ParseCondition(const QString& is) {
  QList<Token> tokens = Tokenize(is);
  Rational ans = ParseExpression(tokens, 1);

  if (tokens.begin() + 1 != tokens.end()) {
    qDebug() << "Parse condition error";
    return Rational(1,0);
  }
  return ans;
}

