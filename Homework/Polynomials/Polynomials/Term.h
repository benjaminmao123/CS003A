#pragma once

#include <ostream>

struct Term
{
    Term(const double coef, const unsigned int exp);

    friend bool operator==(const Term &lhs, const Term &rhs);
    friend bool operator!=(const Term &lhs, const Term &rhs);
    friend bool operator>(const Term &lhs, const Term &rhs);
    friend bool operator<(const Term &lhs, const Term &rhs);

    //used in Poly division operator
    friend Term operator/(const Term &lhs, const Term &rhs);

    friend std::ostream &operator<<(std::ostream &outs, const Term &t);

    double _coef;
    unsigned int _exp;
};