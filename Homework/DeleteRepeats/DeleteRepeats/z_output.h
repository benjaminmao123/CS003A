#ifndef Z_OUTPUT_H
#define Z_OUTPUT_H
/*
***** ALL RESULTS ARE VERIFIED ******
//---------------------------------------------------------------------
// normal run:
//---------------------------------------------------------------------
Array<char> arr = { 'a', 'a', 'c', 'd', 'e', 'f', 'e', 'c' };
Array<char> result = deleteRepeats(arr);
------------ RESULTS --------------------
Array before deleting duplicates: a a c d e f e c
New array after deleting duplicates: a c d e f


//---------------------------------------------------------------------
// empty array:
//---------------------------------------------------------------------
Array<char> arr = { };
Array<char> result = deleteRepeats(arr);
------------ RESULTS --------------------
Array before deleting duplicates: 
New array after deleting duplicates: 


//---------------------------------------------------------------------
// no duplicates:
//---------------------------------------------------------------------
Array<char> arr = { 'a', 'b', 'c', 'd' };
Array<char> result = deleteRepeats(arr);
------------ RESULTS --------------------
Array before deleting duplicates: a b c d
New array after deleting duplicates: a b c d


//---------------------------------------------------------------------
// entire array has duplicate:
//---------------------------------------------------------------------
Array<char> arr = { 'a', 'a', 'a', 'a' };
Array<char> result = deleteRepeats(arr);
------------ RESULTS --------------------
Array before deleting duplicates: a a a a
New array after deleting duplicates: a


*/
#endif // Z_OUTPUT_H