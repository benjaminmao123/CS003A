#pragma once

#include <iostream>

struct Term 
{
    Term();
    Term(double coef, int order);

    Term &operator+=(const Term &rhs);
    Term &operator-=(const Term &rhs);
    Term &operator*=(const Term &rhs);
    Term &operator/=(const Term &rhs);

    bool operator>=(const Term &rhs) const;
    bool operator<=(const Term &rhs) const;
    bool operator>(const Term &rhs) const;
    bool operator<(const Term &rhs) const;
    bool operator==(const Term &rhs) const;
    bool operator!=(const Term &rhs) const;

    //used in Poly division operator
    friend Term operator+(const Term &lhs, const Term &rhs);
    friend Term operator-(const Term &lhs, const Term &rhs);
    friend Term operator*(const Term &lhs, const Term &rhs);
    friend Term operator/(const Term &lhs, const Term &rhs);

    friend std::ostream &operator<<(std::ostream &outs, const Term &t);
    friend std::istream &operator>>(std::istream &ins, Term &t);
    Term operator-() const; //unary operator

    double _coef;
    int _exp;
};