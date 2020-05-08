#pragma once

/*
	01. Print an integer vertically.
	02. Count up to a number (one on each line)
	03. Count down to a number.
	04. Count down to 1, then count up
	05. Hip Hip Hurrah!! (int i) //this is the output for i=3
	06. n-1 Hips and a Hurrah
	07. Hurrah and then n-1 Hips
	08. n-1 Hips, Hurrah, then n-1 Hips
	09. n/2 Hips, Hurrah, then n/2 Hips
	10. n asterisks, a vertical bar, then n exclamation marks
*/
namespace RecursionDrills
{
	void PrintIntVertically(int num);
	void CountUp(int start, int end);
	void CountDown(int start, int end);
	void CountDownToOneCountUp(int num);
	void HipHurrah(int n);
	void HurrahHip(int n);
	void HipHurrahHip1(int n);
	void HipHurrahHip2(int n);
	void StarsBarExclamation(int n);
};