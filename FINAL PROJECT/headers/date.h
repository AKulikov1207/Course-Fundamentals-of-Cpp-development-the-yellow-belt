#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <stdexcept>

using namespace std;

class Date {
public:
	Date();
	Date(int y, int m, int d);

	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;

	string tostring() const;
private:
	const int year;
	const int month;
	const int day;
};

bool operator<(const Date& lhs, const Date& rhs);
bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);

Date ParseDate(istream& date_is);

ostream& operator<<(ostream& os, const Date& date);