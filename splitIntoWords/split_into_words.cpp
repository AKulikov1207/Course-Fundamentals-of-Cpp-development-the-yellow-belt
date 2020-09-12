#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<string> SplitIntoWords(const string& s) {
	// Готовим вектор, в который будем сохранять слова
	vector<string> tmp;
	// ch будет двигаться вправо
	auto ch = s.begin();

	for (auto it = s.begin(); it != s.end(); ++it) {
		// Находим первый пробел в текущем «хвосте» строки
		if (*it == *find(it, s.end(), ' ')) {
			tmp.push_back({ ch, it });         // Полуинтервал [ch, it) — очередное слово
			ch = ++it;                         // первый символ после пробела — начало очередного слова.
										       // Туда и подвинем str_begin
		}
	}
	tmp.push_back({ ch, s.end() });

	return tmp;
}