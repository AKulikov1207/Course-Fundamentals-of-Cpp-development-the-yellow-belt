#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, const string& prefix) {
	return equal_range(range_begin, range_end, prefix, [&prefix](const string& a, const string& b) {
		return a.compare(0, prefix.length(), b.substr(0, prefix.length())) < 0;
	});
}
