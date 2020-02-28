#pragma once

#include <ostream>

using namespace std;

struct Term {
    double _coef;
    int _exp;

    Term(double coef, int exp);
    friend bool operator ==(const Term &lhs, const Term &rhs);
    friend bool operator !=(const Term &lhs, const Term &rhs);
    friend bool operator >(const Term &lhs, const Term &rhs);
    friend bool operator <(const Term &lhs, const Term &rhs);

    //used in Poly division operator
    friend Term operator / (const Term &lhs, const Term &rhs);

    friend ostream &operator <<(ostream &outs, const Term &t);
};
