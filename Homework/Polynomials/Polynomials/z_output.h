#ifndef Z_OUTPUT_H
#define Z_OUTPUT_H
/*
***** ALL RESULTS ARE VERIFIED ******
//---------------------------------------------------------------------
// normal run:
//---------------------------------------------------------------------
: p
: 6 x5 +4 x3 -2 x1 +3 x0
: q
: 3 x8
: p
: 2 x12
------------ RESULTS --------------------
------------------------------------
P: [3.0x^3 + 2.0x^2 + x + 5.0]
Q: [4.0x^4 + 3.0x^3 + 2.0x^2 + x + 5.0]

------- p + q ----------------------
[3.0x^3 + 2.0x^2 + x + 5.0] + [4.0x^4 + 3.0x^3 + 2.0x^2 + x + 5.0]
      = [4.0x^4 + 6.0x^3 + 4.0x^2 + 2.0x + 10.0]  VERIFIED

------- q + p ----------------------
[4.0x^4 + 3.0x^3 + 2.0x^2 + x + 5.0] + [3.0x^3 + 2.0x^2 + x + 5.0]
      = [4.0x^4 + 6.0x^3 + 4.0x^2 + 2.0x + 10.0]  VERIFIED

------- p - q ----------------------
[3.0x^3 + 2.0x^2 + x + 5.0] - [4.0x^4 + 3.0x^3 + 2.0x^2 + x + 5.0]
      = [-4.0x^4]  VERIFIED

------- q - p ----------------------
[3.0x^3 + 2.0x^2 + x + 5.0] - [4.0x^4 + 3.0x^3 + 2.0x^2 + x + 5.0]
      = [-4.0x^4]  VERIFIED

------- p * q ----------------------
[3.0x^3 + 2.0x^2 + x + 5.0] * [4.0x^4 + 3.0x^3 + 2.0x^2 + x + 5.0]
      = [12.0x^7 + 17.0x^6 + 16.0x^5 + 30.0x^4 + 34.0x^3 + 21.0x^2 + 10.0x + 25.0]  VERIFIED

------- q * p ----------------------
[3.0x^3 + 2.0x^2 + x + 5.0] * [4.0x^4 + 3.0x^3 + 2.0x^2 + x + 5.0]
      = [12.0x^7 + 17.0x^6 + 16.0x^5 + 30.0x^4 + 34.0x^3 + 21.0x^2 + 10.0x + 25.0]  VERIFIED

------- p / q ----------------------
[3.0x^3 + 2.0x^2 + x + 5.0] / [4.0x^4 + 3.0x^3 + 2.0x^2 + x + 5.0]
      = []  rem = [3.0x^3 + 2.0x^2 + x + 5.0]  VERIFIED

------- q / p ----------------------
[4.0x^4 + 3.0x^3 + 2.0x^2 + x + 5.0] / [3.0x^3 + 2.0x^2 + x + 5.0]
      = [1.3x + 0.1]  rem = [0.4x^2 - 5.8x + 4.4]  VERIFIED

[P] [Q] E[x]it p
[P]: 6 x5 +4 x3 -2 x1 +3 x0

------------------------------------
P: [6.0x^5 + 4.0x^3 - 2.0x + 3.0]
Q: [4.0x^4 + 3.0x^3 + 2.0x^2 + x + 5.0]

------- p + q ----------------------
[6.0x^5 + 4.0x^3 - 2.0x + 3.0] + [4.0x^4 + 3.0x^3 + 2.0x^2 + x + 5.0]
      = [6.0x^5 + 4.0x^4 + 7.0x^3 + 2.0x^2 - x + 8.0]  VERIFIED

------- q + p ----------------------
[4.0x^4 + 3.0x^3 + 2.0x^2 + x + 5.0] + [6.0x^5 + 4.0x^3 - 2.0x + 3.0]
      = [6.0x^5 + 4.0x^4 + 7.0x^3 + 2.0x^2 - x + 8.0]  VERIFIED

------- p - q ----------------------
[6.0x^5 + 4.0x^3 - 2.0x + 3.0] - [4.0x^4 + 3.0x^3 + 2.0x^2 + x + 5.0]
      = [6.0x^5 - 4.0x^4 + x^3 - 2.0x^2 - 3.0x - 2.0]  VERIFIED

------- q - p ----------------------
[6.0x^5 + 4.0x^3 - 2.0x + 3.0] - [4.0x^4 + 3.0x^3 + 2.0x^2 + x + 5.0]
      = [6.0x^5 - 4.0x^4 + x^3 - 2.0x^2 - 3.0x - 2.0]  VERIFIED

------- p * q ----------------------
[6.0x^5 + 4.0x^3 - 2.0x + 3.0] * [4.0x^4 + 3.0x^3 + 2.0x^2 + x + 5.0]
      = [24.0x^9 + 18.0x^8 + 28.0x^7 + 18.0x^6 + 30.0x^5 + 10.0x^4 + 25.0x^3 + 4.0x^2 - 7.0x + 15.0]  VERIFIED

------- q * p ----------------------
[6.0x^5 + 4.0x^3 - 2.0x + 3.0] * [4.0x^4 + 3.0x^3 + 2.0x^2 + x + 5.0]
      = [24.0x^9 + 18.0x^8 + 28.0x^7 + 18.0x^6 + 30.0x^5 + 10.0x^4 + 25.0x^3 + 4.0x^2 - 7.0x + 15.0]  VERIFIED

------- p / q ----------------------
[6.0x^5 + 4.0x^3 - 2.0x + 3.0] / [4.0x^4 + 3.0x^3 + 2.0x^2 + x + 5.0]
      = [1.5x - 1.1]  rem = [4.4x^3 + 0.8x^2 - 8.4x + 8.6]  VERIFIED

------- q / p ----------------------
[4.0x^4 + 3.0x^3 + 2.0x^2 + x + 5.0] / [6.0x^5 + 4.0x^3 - 2.0x + 3.0]
      = []  rem = [4.0x^4 + 3.0x^3 + 2.0x^2 + x + 5.0]  VERIFIED

[P] [Q] E[x]it q
[Q]: 3 x8

------------------------------------
P: [6.0x^5 + 4.0x^3 - 2.0x + 3.0]
Q: [3.0x^8]

------- p + q ----------------------
[6.0x^5 + 4.0x^3 - 2.0x + 3.0] + [3.0x^8]
      = [3.0x^8 + 6.0x^5 + 4.0x^3 - 2.0x + 3.0]  VERIFIED

------- q + p ----------------------
[3.0x^8] + [6.0x^5 + 4.0x^3 - 2.0x + 3.0]
      = [3.0x^8 + 6.0x^5 + 4.0x^3 - 2.0x + 3.0]  VERIFIED

------- p - q ----------------------
[6.0x^5 + 4.0x^3 - 2.0x + 3.0] - [3.0x^8]
      = [-3.0x^8 + 6.0x^5 + 4.0x^3 - 2.0x + 3.0]  VERIFIED

------- q - p ----------------------
[6.0x^5 + 4.0x^3 - 2.0x + 3.0] - [3.0x^8]
      = [-3.0x^8 + 6.0x^5 + 4.0x^3 - 2.0x + 3.0]  VERIFIED

------- p * q ----------------------
[6.0x^5 + 4.0x^3 - 2.0x + 3.0] * [3.0x^8]
      = [18.0x^13 + 12.0x^11 - 6.0x^9 + 9.0x^8]  VERIFIED

------- q * p ----------------------
[6.0x^5 + 4.0x^3 - 2.0x + 3.0] * [3.0x^8]
      = [18.0x^13 + 12.0x^11 - 6.0x^9 + 9.0x^8]  VERIFIED

------- p / q ----------------------
[6.0x^5 + 4.0x^3 - 2.0x + 3.0] / [3.0x^8]
      = []  rem = [6.0x^5 + 4.0x^3 - 2.0x + 3.0]  VERIFIED

------- q / p ----------------------
[3.0x^8] / [6.0x^5 + 4.0x^3 - 2.0x + 3.0]
      = [0.5x^3 - 0.3x]  rem = [2.3x^4 - 1.5x^3 - 0.7x^2 + x]  VERIFIED

[P] [Q] E[x]it p
[P]: 2 x12

------------------------------------
P: [2.0x^12]
Q: [3.0x^8]

------- p + q ----------------------
[2.0x^12] + [3.0x^8]
      = [2.0x^12 + 3.0x^8]  VERIFIED

------- q + p ----------------------
[3.0x^8] + [2.0x^12]
      = [2.0x^12 + 3.0x^8]  VERIFIED

------- p - q ----------------------
[2.0x^12] - [3.0x^8]
      = [2.0x^12 - 3.0x^8]  VERIFIED

------- q - p ----------------------
[2.0x^12] - [3.0x^8]
      = [2.0x^12 - 3.0x^8]  VERIFIED

------- p * q ----------------------
[2.0x^12] * [3.0x^8]
      = [6.0x^20]  VERIFIED

------- q * p ----------------------
[2.0x^12] * [3.0x^8]
      = [6.0x^20]  VERIFIED

------- p / q ----------------------
[2.0x^12] / [3.0x^8]
      = [0.7x^4]  rem = []  VERIFIED

------- q / p ----------------------
[3.0x^8] / [2.0x^12]
      = []  rem = [3.0x^8]  VERIFIED

[P] [Q] E[x]it


//---------------------------------------------------------------------
//  run:
//---------------------------------------------------------------------
: 
------------ RESULTS --------------------
*/
#endif // Z_OUTPUT_H