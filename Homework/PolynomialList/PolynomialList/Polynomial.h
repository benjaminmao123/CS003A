#pragma once

#include <iostream>

#include "Term.h"
#include "SortedList.h"

class Poly
{
public:
    Poly();
    Poly(double term_array[], int order);

    //big three?
    Poly &operator+=(const Term &t);
    Poly &operator*=(const Term &t);

    Poly &operator+=(const Poly &RHS);
    Poly &operator*=(const Poly &RHS);
    Poly &operator-=(const Poly &RHS);
    Poly operator-() const;

    friend Poly operator/(const Poly &lhs, const Poly &rhs);
    friend Poly operator+(const Poly &left, const Poly &right);
    friend Poly operator-(const Poly &left, const Poly &right);
    friend Poly operator*(const Poly &left, const Poly &right);

    friend Poly operator+(const Poly &left, const Term &t);
    friend Poly operator*(const Poly &left, const Term &t);

    friend Poly operator%(const Poly &lhs, const Poly &rhs);

    bool operator==(const Poly &rhs) const;

    friend std::ostream &operator<<(std::ostream &outs, const Poly &print_me);
    friend std::istream &operator>>(std::istream &ins, Poly &poly);

private:
    void fix_order();

    List<Term> _poly; //descending sorted list  
    int _order;
};