#include "expression_parser.h"
#include "token.h"
#include "rational.h"

Rational ParseOperation(QList<Token>& tokens);  // 2 numbers and operator between them

Rational ParseExpression(QList<Token>& tokens); // whole expression

Rational ParseParentheses(QList<Token>& tokens){
    if (tokens.first().value == "("){                                       // example: (1+2)*(1+3)
        int index = tokens.indexOf({")", TokenType::PAREN_RIGHT});
        auto t = tokens.first(index+1);                                     // slice of expression with parentheses
        while (t.count({"(", TokenType::PAREN_LEFT}) !=                     // example: (1+(2-5))*8
               t.count({")", TokenType::PAREN_RIGHT})){
            index = tokens.indexOf({")", TokenType::PAREN_RIGHT}, index+1); // move to next right parenthesis
            t = tokens.first(index+1);
        }
        t = tokens.sliced(1, index-1);  // slice of expression within parentheses
        tokens.remove(0, index+1);      // remove expression with parentheses

        return ParseExpression(t);      // value of expression within parentheses
    }   // else
    return Parser(tokens.takeFirst().value);    // pop number
}

Rational ParseOperation(QList<Token>& tokens) {
    Rational fOperand1 = ParseParentheses(tokens);
    QString strOperation = tokens.takeFirst().value;
    Rational fOperand2 = ParseParentheses(tokens);
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
     tokens.prepend({res.toString(), TokenType::OPERAND});  // replace expression with it's value
    return res;
}

Rational ParseExpression(QList<Token>& tokens) {

  Rational left;

  while (tokens.begin()+1 != tokens.end()) { // until it is the only number (answer)
      int index = 0; // logical_op can not be at 0 position
      if (tokens.contains({"*", TokenType::LOGICAL_OP}) &&  // first priority is '/', '*'
          tokens.contains({"/", TokenType::LOGICAL_OP})){   // last is '-', '+'
          int index_multiply = tokens.indexOf({"*", TokenType::LOGICAL_OP});
          int index_divide = tokens.indexOf({"/", TokenType::LOGICAL_OP});
          if (index_multiply < index_divide){   // if '/' after '*'
              index = index_multiply;
          } else {
              index = index_divide;
          }
      } else if (tokens.contains({"*", TokenType::LOGICAL_OP})){    // if '*' is the only first priority
          index = tokens.indexOf({"*", TokenType::LOGICAL_OP});
      } else if (tokens.contains({"/", TokenType::LOGICAL_OP})){    // if '/' is the only first priority
          index = tokens.indexOf({"/", TokenType::LOGICAL_OP});
      }
      if (index &&      // if index == 0 and not ..._(...) nor (...)_...
          !(tokens.at(index-1).value == ")" || tokens.at(index+1).value == "(")){
          tokens.insert(index-1, {"(", TokenType::PAREN_LEFT});     // (x_y
          tokens.insert(index+3, {")", TokenType::PAREN_RIGHT});    // (x_y)
      } else if (index &&   // if index == 0 and ..._(...) or (...)_...
                 (tokens.at(index-1).value == ")" || tokens.at(index+1).value == "(")){
          if (tokens.at(index-1).value == ")" &&    // if (...)_(...)
              tokens.at(index+1).value == "("){
                tokens.insert(tokens.indexOf({"(", TokenType::PAREN_LEFT}),
                              {"(", TokenType::PAREN_LEFT});                            // ((...)_(...)
                tokens.insert(tokens.indexOf({")", TokenType::PAREN_RIGHT}, index+1),
                              {")", TokenType::PAREN_RIGHT});                           // ((...)_(...))
          } else if (tokens.at(index-1).value == ")"){  // if ..._(...)
               tokens.insert(index+2,
                             {")", TokenType::PAREN_RIGHT});                // ..._(...))
               tokens.insert(tokens.indexOf({"(", TokenType::PAREN_LEFT}),
                             {"(", TokenType::PAREN_LEFT});                 // (..._(...))
          }
          else if (tokens.at(index+1).value == "("){    // if (...)_...
               tokens.insert(index-1,
                             {"(", TokenType::PAREN_LEFT});                 // ((...)_...
               tokens.insert(tokens.indexOf({")", TokenType::PAREN_RIGHT}),
                             {")", TokenType::PAREN_RIGHT});                // ((...)_...)
          }
      }
      if (tokens.first().type == TokenType::PAREN_LEFT) {   // (x_y)
        tokens.pop_front(); // consume '('
        left = ParseOperation(tokens);
        if (tokens.begin()+1 == tokens.end() ||
            tokens.at(1).type != TokenType::PAREN_RIGHT) {
          //qDebug() << "Missing right paren";
          return Rational(1,0); // error
        }
        tokens.removeAt(1); // consume ')'
      } else {  // x_y
        left = ParseOperation(tokens);
      }
  }
  return left;
}

Rational ParseCondition(const QString& is) {
  QList<Token> tokens = Tokenize(is);
  if (tokens.begin()+1 == tokens.end()){    // if it is the only number (answer)
      return Parser(tokens.first().value);
  }
  Rational ans = ParseExpression(tokens);

  if (tokens.begin() + 1 != tokens.end()) {
    //qDebug() << "Parse condition error";
    return Rational(1,0);   // error
  }
  return ans;
}

