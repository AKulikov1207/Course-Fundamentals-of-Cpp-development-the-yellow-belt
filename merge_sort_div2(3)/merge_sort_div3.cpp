#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Часть 2. Реализация с разбиением на 3 части
template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	// 1. Если диапазон содержит меньше 2 элементов, выходим из функции
	if (range_end - range_begin < 2)
		return;

	// 2. Создаем вектор, содержащий все элементы текущего диапазона
	vector<typename RandomIt::value_type> elements(range_begin, range_end);

	// 3. Разбиваем вектор на три равные части
	auto it = elements.begin() + elements.size() / 3;
	auto it2 = it + elements.size() / 3;

	// 4. Вызываем функцию MergeSort от каждой трети вектора
	MergeSort(elements.begin(), it);
	MergeSort(it, it2);
	MergeSort(it2, elements.end());

	// 5. С помощью алгоритма merge cливаем первые две трети во временный вектор
	vector<typename RandomIt::value_type> tmp;
	merge(elements.begin(), it, it, it2, back_inserter(tmp));

	// 6. С помощью алгоритма merge сливаем отсортированные части
	merge(tmp.begin(), tmp.end(), it2, elements.end(), range_begin);
}

int main() {
	vector<int> v = { 6, 4, 7, 6, 4, 4, 0, 1 };
	MergeSort(begin(v), end(v));
	for (int x : v) {
		cout << x << " ";
	}
	cout << endl;
	return 0;
}