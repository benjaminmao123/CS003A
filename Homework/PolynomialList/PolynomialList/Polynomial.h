#pragma once

#include <iostream>

#include "Term.h"
#include "SortedList.h"

class Poly
{
public:
    Poly();
    Poly(int term_array[], int order);

    //big three?
    Poly &operator+=(const Term &t);
    Poly &operator*=(const Term &t);

    Poly &operator+=(const Poly &RHS);
    Poly &operator*=(const Poly &RHS);
    Poly &operator-=(const Poly &RHS);



    friend Poly operator+(const Poly &left, const Poly &right);
    friend Poly operator-(const Poly &left, const Poly &right);
    friend Poly operator*(const Poly &left, const Poly &right);
    Poly operator-() const;


    friend Poly operator+(const Poly &left, const Term &t);
    friend Poly operator*(const Poly &left, const Term &t);

    friend std::ostream &operator<<(std::ostream &outs, const Poly &print_me);
    friend std::istream &operator>>(std::istream &outs, Poly &print_me);

private:
    List<Term> _poly; //descending sorted list  
    int _order;
};