#pragma once

#include <iostream>

struct Term 
{
    double _coef;
    int _exp;

    Term();
    Term(double coef, int order);

    Term &operator+=(const Term &rhs);
    Term &operator-=(const Term &rhs);
    Term &operator*=(const Term &rhs);
    Term &operator/=(const Term &rhs);

    friend bool operator==(const Term &lhs, const Term &rhs);
    friend bool operator!=(const Term &lhs, const Term &rhs);
    friend bool operator>(const Term &lhs, const Term &rhs);
    friend bool operator<(const Term &lhs, const Term &rhs);

    //used in Poly division operator
    friend Term operator+(const Term &lhs, const Term &rhs);
    friend Term operator-(const Term &lhs, const Term &rhs);
    friend Term operator*(const Term &lhs, const Term &rhs);
    friend Term operator/(const Term &lhs, const Term &rhs);

    friend std::ostream &operator<<(std::ostream &outs, const Term &t);
    friend std::istream &operator>>(std::istream &ins, Term &t);
    Term operator-() const; //unary operator
};