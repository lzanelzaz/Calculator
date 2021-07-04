#pragma once

#include "rational.h"

Rational ParseCondition(const QString& is);

enum class LogicalOperation {
    Division_or_multiplication = 1u,
    Plus_or_minus = 2u
};
