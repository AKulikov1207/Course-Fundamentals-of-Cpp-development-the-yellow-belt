#include "database.h"

using namespace std;

bool operator<(const Record& lhs, const Record& rhs)
{
	return lhs.GetDate() < rhs.GetDate();
}

bool operator==(const Record& lhs, const Record& rhs)
{
	return lhs.GetDate() == rhs.GetDate() && lhs.GetEvent() == rhs.GetEvent();
}

ostream& operator<<(ostream& os, const Record& record)
{
	os << record.GetDate() << " " << record.GetEvent();
	return os;
}

void Database::EventList::Print(ostream& os, const Date& date) const
{
	for (const auto& event : events_)
		os << date << " " << event << endl;
}

void Database::Add(const Date& date_, const string& event_)
{
	auto it = db.find(date_);

	if (it != db.end()) {
		auto& events = it->second;

		if (events.Contains(event_))
			return;

		events.Add(event_);
	}
	else {
		db[date_].Add(event_);
	}
}

void Database::Print(ostream& os) const {
	for (const auto& [date_, events] : db) {
		events.Print(os, date_);
	}
}

Record Database::Last(const Date& date) const {
	if (db.empty())
		throw invalid_argument("Empty database");

	auto it = db.lower_bound(date);

	if (it == db.cbegin() && date < it->first)
		throw invalid_argument("No entries for requested date");

	if (it == db.cend() || it->first != date)
		it = prev(it);

	return Record(it->first, it->second.Last());
}