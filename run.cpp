#include <iostream>
using namespace std;

#include "assignment1.cpp"

int main() {
	const char* weekday[] = {"Monday", "Tuesday", "Wednesday", "Thursday",
						"Friday", "Saturday", "Sunday"};

	date current = getCurrentDate();
	date birth = getBirthInput();

	int years = yearsOld(current.year, current.month, current.day, birth.year, birth.month, birth.day);
	int months = monthsOld(current.year, current.month, current.day, birth.year, birth.month, birth.day);
	int dow = dayOfTheWeek(birth.year, birth.month, birth.day);
	cout << "You are: " << years << " years old." << endl;
	cout << "You are: " << months << " months old." << endl;
	cout << "You were born on a " << weekday[dow - 1] << "." << endl;
	return 0;
}