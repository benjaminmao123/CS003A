#ifndef Z_OUTPUT_H
#define Z_OUTPUT_H
/*
***** ALL RESULTS ARE VERIFIED ******
//---------------------------------------------------------------------
// normal run:
//---------------------------------------------------------------------
:i
:5
:0
:0
:i
:6
:0
:1
:o
:5
:o
:6
:x
------------ RESULTS --------------------
Plane:
0 0 0 0
0 0 0
0 0

i. Login
o. Logout
x. Exit

Command: i

LOGIN
Labs: 4 3 2
ID: 5
Lab: 0
Station: 0

Success: You are logged in to lab 0 station 0

Plane:
5 0 0 0
0 0 0
0 0

i. Login
o. Logout
x. Exit

Command: i

LOGIN
Labs: 4 3 2
ID: 6
Lab: 0
Station: 1

Success: You are logged in to lab 0 station 1

Plane:
5 6 0 0
0 0 0
0 0

i. Login
o. Logout
x. Exit

Command: o

LOGOUT
ID: 5

Success: You have been logged out

Plane:
0 6 0 0
0 0 0
0 0

i. Login
o. Logout
x. Exit

Command: o

LOGOUT
ID: 6

Success: You have been logged out

Plane:
0 0 0 0
0 0 0
0 0

i. Login
o. Logout
x. Exit

Command: x


//---------------------------------------------------------------------
// Login with ID: 0:
//---------------------------------------------------------------------
:i
:0
------------ RESULTS --------------------
Plane:
0 0 0 0
0 0 0
0 0

i. Login
o. Logout
x. Exit

Command: i

LOGIN
Labs: 4 3 2
ID: 0
Error: ID cannot be 0


//---------------------------------------------------------------------
// Logout with ID: 0:
//---------------------------------------------------------------------
:o
:0
------------ RESULTS --------------------
Plane:
0 0 0 0
0 0 0
0 0

i. Login
o. Logout
x. Exit

Command: o

LOGOUT
ID: 0

Error: ID does not exist or you are not logged in


*/
#endif // Z_OUTPUT_H