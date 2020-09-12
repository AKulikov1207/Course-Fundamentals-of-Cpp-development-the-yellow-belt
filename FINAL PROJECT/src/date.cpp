#include "date.h"

using namespace std;

Date::Date() : year{ 1 }, month{ 1 }, day{ 1 } {}
Date::Date(int y, int m, int d) : year{ y }, month{ m }, day{ d } {
	if (!(m >= 1 && m <= 12))
	throw logic_error("Month value is invalid: " + to_string(m));

	if (!(d >= 1 && d <= 31))
	throw logic_error("Day value is invalid: " + to_string(d));

	if (!(y >= 0 && y <= 9999))
	throw logic_error("Year value is invalid: " + to_string(y));
}

int Date::GetYear() const { return year; };
int Date::GetMonth() const { return month; };
int Date::GetDay() const { return day; };


bool operator<(const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() < rhs.GetYear())
		return true;

	if (lhs.GetYear() > rhs.GetYear())
		return false;

	if (lhs.GetMonth() > rhs.GetMonth())
		return false;

	if (lhs.GetMonth() < rhs.GetMonth())
		return true;

	return lhs.GetDay() < rhs.GetDay();
};

bool operator==(const Date& lhs, const Date& rhs) {
	return lhs.GetYear() == rhs.GetYear() && lhs.GetMonth() == rhs.GetMonth()&& lhs.GetDay() == rhs.GetDay();
}

bool operator!=(const Date& lhs, const Date& rhs) {
	return !(lhs == rhs);
}

bool operator<=(const Date& lhs, const Date& rhs) {
	return (lhs < rhs) || (lhs == rhs);
}

bool operator>(const Date& lhs, const Date& rhs) {
	return (lhs != rhs) && !(lhs < rhs);
}

bool operator>=(const Date& lhs, const Date& rhs) {
	return (lhs > rhs) || (lhs == rhs);
}

Date ParseDate(istream& date_is) {
	bool check = true;

	int year = 1, month = 1, day = 1;
	check = check && (date_is >> year);
	check = check && (date_is.peek() == '-');
	date_is.ignore(1);

	check = check && (date_is >> month);
	check = check && (date_is.peek() == '-');
	date_is.ignore(1);

	check = check && (date_is >> day);

	if (!check) {
		throw logic_error("Wrong date format: " + to_string(year) + "-" + to_string(month) + "-" + to_string(day));
	}

	return Date(year, month, day);
}

ostream& operator<<(ostream& os, const Date& date) {
	os << setfill('0') << setw(4) << to_string(date.GetYear()) << "-";
	os << setfill('0') << setw(2) << to_string(date.GetMonth()) << "-";
	os << setfill('0') << setw(2) << to_string(date.GetDay());
	return os;
}

string Date::tostring() const {
	ostringstream ss; 
	ss << *this;
	return ss.str();
}