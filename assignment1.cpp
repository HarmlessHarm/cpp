#include <iostream>
#include <time.h>
// #include <ctime>
#include <string>
using namespace std;


// Leap year every 4 years, except every 100 years, except except every 400 years
// Year % 4 == 0   : Leapyear
// Year % 100 == 0 : No leapyear
// Year % 400 == 0 : Leapyear

// 1-1-1900 was a monday
int START_YEAR = 1900;
int START_MONTH = 1;
int START_DAY = 1;
int START_DOW = 1;

int MONTH_RANGE[2] = {1, 12};
int DAYS_IN_MONTH[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

struct date {
	int year;
	int month;
	int day;	
}birth, current;

date getBirthInput() {
	string birthDate;
	int valid = 0;
	date birth;
	while (valid == 0) {
		cout << "Whats your birth date yyyy-mm-dd ?" << endl;
		cin >> birthDate;
		if( birthDate.length() == 10) {
			string dateString[3];
			int p = 0;
			for (int i = 0; i < 10; i++) {
				if (birthDate[i] == '-') {
					p++;
					continue;
				}
				dateString[p] += birthDate[i];
			}
			// Check if inputs are all valid length
			if (dateString[0].length() == 4 && dateString[1].length() == 2 &&
				dateString[2].length() == 2) {
				birth.year = stoi(dateString[0]);
				birth.month = stoi(dateString[1]);
				birth.day = stoi(dateString[2]);
				valid = 1;
			}
			else {
				cout << "Your date didn't parse correctly" << endl;
			}
		} else {
			cout << "Your date is not in the right length" << endl;
		}
	}
	return birth;
}

date getCurrentDate() {
	time_t currentTime;
	time(&currentTime);
	tm* timePtr = localtime(&currentTime);
	date current;
	current.year = timePtr->tm_year + 1900;
	current.month = timePtr->tm_mon + 1;
	current.day = timePtr->tm_mday;
	return current;
}

tm make_tm(int year, int month, int day)
{
    tm tm = {0};
    tm.tm_year = year - 1900; // years count from 1900
    tm.tm_mon = month - 1;    // months count from January=0
    tm.tm_mday = day;         // days count from 1
    return tm;
}

int yearsOld(int currentYear, int currentMonth, int currentDay, 
			 int birthYear, int birthMonth, int birthDay) {

	int yearDiff = currentYear - birthYear - 1;
	if (currentMonth > birthMonth) {
		yearDiff++;
	}
	else if (currentMonth == birthMonth && currentDay >= birthDay) {
		yearDiff++;
	}
	return yearDiff;
}

int monthsOld(int currentYear, int currentMonth, int currentDay, 
			  int birthYear, int birthMonth, int birthDay) {

	int yearDiff = (currentYear - birthYear) * 12;
	int monthCorr = currentMonth - birthMonth;

	if (currentDay <= birthDay) {
		monthCorr --;
	}
	int monthDiff = yearDiff + monthCorr;
	return monthDiff;
}

int dayOfTheWeek(int birthYear,int birthMonth,int birthDay) {
	// Caculate days from 1900
	time_t t;
	struct tm* timeinfo;

	time(&t);
	timeinfo = localtime(&t);
	timeinfo->tm_year = birthYear - 1900;
	timeinfo->tm_mon = birthMonth - 1;
	timeinfo->tm_mday = birthDay;

	mktime(timeinfo);
	int dow = timeinfo->tm_wday;
	if (dow == 0) { dow = 7; }
	return dow;
}