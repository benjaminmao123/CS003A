#ifndef Z_OUTPUT_H
#define Z_OUTPUT_H
/*
***** ALL RESULTS ARE VERIFIED ******
//---------------------------------------------------------------------
// normal run:
//---------------------------------------------------------------------
size = 6
copy(dest, src, size)
------------ RESULTS --------------------
Source array: 1 2 3 4 5 6
Destination array before copy: 0 0 0 0 0 0
Destination array after copy: 1 2 3 4 5 6


//---------------------------------------------------------------------
// empty array:
//---------------------------------------------------------------------
size = 0
copy(dest, src, size)
------------ RESULTS --------------------
Source array: 1 2 3 4 5 6
Destination array before copy: 0 0 0 0 0 0
Destination array after copy: 0 0 0 0 0 0


//---------------------------------------------------------------------
// array is null:
//---------------------------------------------------------------------
int* src = null
copy(dest, src, 6)
------------ RESULTS --------------------
Source array: Array is NULL
Destination array before copy: 0 0 0 0 0 0
Destination array after copy: 0 0 0 0 0 0


*/
#endif // Z_OUTPUT_H