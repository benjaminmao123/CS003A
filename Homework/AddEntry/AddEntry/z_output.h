#ifndef Z_OUTPUT_H
#define Z_OUTPUT_H
/*
***** ALL RESULTS ARE VERIFIED ******
//---------------------------------------------------------------------
// initial allocation and add entry:
//---------------------------------------------------------------------
list = allocate(list, capacity);
list = add_entry(list, 1, size, capacity);
list = add_entry(list, 2, size, capacity);
list = add_entry(list, 3, size, capacity);
------------ RESULTS --------------------
allocate: capacity: 3
List: 1
List: 1 2
List: 1 2 3


//---------------------------------------------------------------------
// allocation when size >= capacity:
//---------------------------------------------------------------------
list = add_entry(list, 1, size, capacity);
list = add_entry(list, 2, size, capacity);
list = add_entry(list, 3, size, capacity);
list = add_entry(list, 4, size, capacity);
------------ RESULTS --------------------
allocate: capacity: 3
List: 1
List: 1 2
List: 1 2 3
allocate: capacity: 6
List: 1 2 3 4


//---------------------------------------------------------------------
// remove entry middle:
//---------------------------------------------------------------------
list = remove_entry(list, 3, size, capacity);
------------ RESULTS --------------------
List: 1 2 4


//---------------------------------------------------------------------
// remove entry front:
//---------------------------------------------------------------------
list = remove_entry(list, 1, size, capacity);
------------ RESULTS --------------------
List: 2 3 4


//---------------------------------------------------------------------
// remove entry back:
//---------------------------------------------------------------------
list = remove_entry(list, 4, size, capacity);
------------ RESULTS --------------------
List: 1 2 3


//---------------------------------------------------------------------
// remove entry element does not exist:
//---------------------------------------------------------------------
list = remove_entry(list, 5, size, capacity);
------------ RESULTS --------------------
List: 1 2 3 4


//---------------------------------------------------------------------
// allocation when size <= capacity / 4:
//---------------------------------------------------------------------
list = remove_entry(list, 4, size, capacity);
list = remove_entry(list, 3, size, capacity);
list = remove_entry(list, 2, size, capacity);
list = remove_entry(list, 1, size, capacity);
------------ RESULTS --------------------
List: 1 2 3
List: 1 2
List: 1
allocate: capacity: 3
List: Empty


*/
#endif // Z_OUTPUT_H