# Задание по программированию: Разбиение на слова
Напишите функцию SplitIntoWords, разбивающую строку на слова по пробелам.
```
vector<string> SplitIntoWords(const string& s);
```
Гарантируется, что:
* строка непуста;
* строка состоит лишь из латинских букв и пробелов;
* первый и последний символы строки не являются пробелами;
* строка не содержит двух пробелов подряд.
## Пример кода
```
int main() {
  string s = "C Cpp Java Python";

  vector<string> words = SplitIntoWords(s);
  cout << words.size() << " ";
  for (auto it = begin(words); it != end(words); ++it) {
    if (it != begin(words)) {
      cout << "/";
    }
    cout << *it;
  }
  cout << endl;
  
  return 0;
}
```
## Вывод
```
4 С/Cpp/Java/Python
```