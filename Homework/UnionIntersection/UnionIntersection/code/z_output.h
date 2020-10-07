#ifndef Z_OUTPUT_H
#define Z_OUTPUT_H
/*
***** ALL RESULTS ARE VERIFIED ******
//---------------------------------------------------------------------
// input is int:
//---------------------------------------------------------------------
int a[] = { 5, 10, 15, 20, 25, 30, 35, 40 };
int b[] = { 3, 10, 13, 20, 23, 28, 30, 33, 35 };
int* c = m_union(a, aSize, b, bSize, uSize);
int* d = intersection(a, aSize, b, bSize, iSize);
------------ RESULTS --------------------
Union: 3 5 10 13 15 20 23 25 28 30 33 35 40
Intersection: 10 20 30 35


//---------------------------------------------------------------------
// empty array:
//---------------------------------------------------------------------
int* c = m_union(a, 0, b, 0, uSize);
int* d = intersection(a, 0, b, 0, iSize);
------------ RESULTS --------------------
Union: 
Intersection: 


//---------------------------------------------------------------------
// all elements are unique:
//---------------------------------------------------------------------
int a[] = { 1, 2, 3, 4 };
int b[] = { 5, 6, 7, 8 };
int* c = m_union(a, aSize, b, bSize, uSize);
int* d = intersection(a, aSize, b, bSize, iSize);
------------ RESULTS --------------------
Union: 1 2 3 4 5 6 7 8
Intersection:


//---------------------------------------------------------------------
// input is char
//---------------------------------------------------------------------
char a[] = "acegkl";
char b[] = "abcdfhij";
char* c = m_union(a, aSize, b, bSize, uSize);
char* d = intersection(a, aSize, b, bSize, iSize);
------------ RESULTS --------------------
Union: a b c d e f g h i j k l
Intersection: a c


*/
#endif // Z_OUTPUT_H