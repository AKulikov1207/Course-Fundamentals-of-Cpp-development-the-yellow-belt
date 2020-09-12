#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Часть 1. Группировка по символу
template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, char prefix) {
	string goal1 = { prefix };
	// Все строки, начинающиеся с '<prefix>', больше или равны строке "<prefix>"
	auto left = lower_bound(range_begin, range_end, goal1);

	// Составим следующий в алфавите символ.
    // Не страшно, если prefix = 'z':
    // в этом случае мы получим следующий за 'z' символ в таблице символов
	auto next = static_cast<char>(prefix + 1);

	// Строка "<goal2>" в рамках буквенных строк
    // является точной верхней гранью
    // множества строк, начнающихся с '<prefix>'
	string goal2 = { next };
	auto right = upper_bound(range_begin, range_end, goal2);

	return make_pair(left, right);
}