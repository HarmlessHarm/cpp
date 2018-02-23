#include <iostream>
#include <stdlib.h>
using namespace std;

#include "assignment1.cpp"

// Leap year every 4 years, except every 100 years, except except every 400 years
// Year % 4 == 0   : Leapyear
// Year % 100 == 0 : No leapyear
// Year % 400 == 0 : Leapyear

int main() {
	int daysOfMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	int reps = 100000;
	int correct = 0;
	int year, month, day, dow, tdow;
	srand(time(NULL));
	for (int i = 0; i < reps; i++) {
		year = rand() % 200 + 1900;
		month = rand() % 12 + 1;
		if (month != 1) {
			day = rand() % daysOfMonth[month - 1] + 1;
		}
		else {
			if (year % 4 == 0 && year % 100 != 0 && year % 400 != 0) {
				day = rand() % 29 + 1;
			}
			else {
				day = rand() % 28 + 1;
			}	
		}
		dow = rand() % 7 + 1;
		tdow = dayOfTheWeek(year, month, day);
		if (dow == tdow) {
			correct++;
		}
	}
	cout << "        1 / 7 = " << float(1) / 7 << endl;
	cout << "correct/total = " << float(correct) / reps << endl;

}