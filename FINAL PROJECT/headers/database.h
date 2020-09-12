#pragma once

#include "date.h"

#include <map>
#include <set>
#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <utility>

class Record {
private:
	const Date date;
	const string event;

public:
	Record() {}
	Record(const Date& date_, const string& event_ = "") : date(date_), event(event_) {}

	Date GetDate()         const { return date; }
	string GetEvent()      const { return event; }
	string tostring()   const { return date.tostring() + " " + event; }
};

bool operator<(const Record& lhs, const Record& rhs);
bool operator==(const Record& lhs, const Record& rhs);
ostream& operator<<(ostream& os, const Record& record);

class Database {
public:
	using RecordList = vector<Record>;

	void Add(const Date& date_, const string& event_);
	void Print(ostream& os) const;

	template<class Predicate>
	int RemoveIf(Predicate p) {
		int count = 0;

		vector<Date> clean;

		for (auto& [date_, events] : db) {
			count += events.RemoveIf(date_, p);

			if (events.IsEmpty())
				clean.push_back(date_);
		}

		for (const auto& date_ : clean)
			db.erase(date_);

		return count;
	}

	template<class Predicate>
	RecordList FindIf(Predicate p) const {
		RecordList result;

		for (const auto& item : db) {
			auto events = item.second.Events();

			for (const auto& event_ : events) {
				if (p(item.first, event_))
					result.emplace_back(item.first, event_);
			}
		}

		return result;
	}

	Record Last(const Date& date) const;

private:
	class EventList {
		vector<string> events_;
		set<string> cache;

		public:

			void Add(const string& event_) {
				events_.push_back(event_);
				cache.insert(event_);
			}

			bool Contains(const string& event_)  const { return cache.count(event_) != 0; }
			const vector<string>& Events()      const { return events_; }
			string Last()                       const { return events_.back(); }
			bool IsEmpty()                      const { return events_.empty(); }

			void Print(ostream& os, const Date& date) const;

			template <typename Predicate>
			int RemoveIf(const Date& date, Predicate p) {
				auto it = stable_partition(events_.begin(), events_.end(), [&](const string& items) {
						return !p(date, items);
					});

				if (it == events_.end())
					return 0;

				int count = 0;

				for (auto it_next = it; it_next != events_.end(); it_next++)
				{
					cache.erase(*it_next);
					count++;
				}

				events_.erase(it, events_.end());

				return count;
			}

	};

	map<Date, EventList> db;
};