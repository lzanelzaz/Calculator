#include "token.h"
#include "expression_parser.h"
#include <QDebug>

template <typename It> Rational ParseOperation(It& current) {
    Rational fOperand1 = Parser(current->value);
    ++current;
    QString strOperation = current->value;
    ++current;
    Rational fOperand2 = Parser(current->value);
    ++current;
    if (strOperation == "+") {
        return fOperand1 + fOperand2;
    }
    else if (strOperation == "-"){
        return fOperand1 - fOperand2;
    }
    else if (strOperation == "/") {
        return fOperand1 / fOperand2;
    }
    else if (strOperation == "*") {
        return fOperand1 * fOperand2;
    }
    return Rational();
}

template <typename It>
Rational ParseExpression(It& current, It end, unsigned precedence) {
  if (current == end) {
    return Rational();
  }

  Rational left;

  if (current->type == TokenType::PAREN_LEFT) {
    ++current; // consume '('
    left = ParseExpression(current, end, 0u);
    if (current == end || current->type != TokenType::PAREN_RIGHT) {
      qDebug() << "Missing right paren";
    }
    ++current; // consume ')'
  } else {
    left = ParseOperation(current);
  }
/*
  const map<LogicalOperation, unsigned> precedences = {
      {LogicalOperation::Or, 1}, {LogicalOperation::And, 2}
  };

  while (current != end && current->type != TokenType::PAREN_RIGHT) {
    if (current->type != TokenType::LOGICAL_OP) {
      qDebug() << "Expected logic operation";
    }

    const LogicalOperation logical_operation = current->value == "AND" ? LogicalOperation::And
                                                           : LogicalOperation::Or;
    const unsigned current_precedence = precedences.at(logical_operation);
    if (current_precedence <= precedence) {
      break;
    }

    ++current; // consume op

    left = make_shared<LogicalOperationNode>(
        logical_operation, left, ParseExpression(current, end, current_precedence)
    );
  }
*/
  return left;
}


Rational ParseCondition(QString is) {
  QVector<Token> tokens = Tokenize(is);
  auto current = tokens.begin();
  Rational top_node = ParseExpression(current, tokens.end(), 0u);

  if (current != tokens.end()) {
    qDebug() << "Parse condition error";
  }

  return top_node;
}

