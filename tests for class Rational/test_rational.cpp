#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
       os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

void TestConstructor() {
	Rational rational;
	
	AssertEqual(rational.Numerator(), 0, "Numerator = 0");
	AssertEqual(rational.Denominator(), 1, "Denominator = 1");
}

void TestFractionReduction() {
	Rational rational(4, 16);
	// 4/16 = 1/4
	AssertEqual(rational.Numerator(), 1, "Numerator = 1");
	AssertEqual(rational.Denominator(), 4, "Denominator = 4");
}

void TestNegativeFraction() {
	Rational rational(4, -16);
	// 4/-16 = -1/4
	AssertEqual(rational.Numerator(), -1, "Numerator = -1");
	AssertEqual(rational.Denominator(), 4, "Denominator = 4");
}

void TestPositiveFraction() {
	Rational rational(-2, -3);
	// -2/-3 = 2/3
	AssertEqual(rational.Numerator(), 2, "Numerator = 2");
	AssertEqual(rational.Denominator(), 3, "Denominator = 3");
}

void TestZeroNumerator() {
	Rational rational(0, 6);
	// 0/6 = 0/1
	AssertEqual(rational.Numerator(), 0, "Numerator = 0");
	AssertEqual(rational.Denominator(), 1, "Denominator = 1");
}

int main() {
  TestRunner runner;
  
  runner.RunTest(TestConstructor, "TestConstructor");
  runner.RunTest(TestFractionReduction, "TestFractionReduction");
  runner.RunTest(TestNegativeFraction, "TestNegativeFraction");
  runner.RunTest(TestPositiveFraction, "TestPositiveFraction");
  runner.RunTest(TestZeroNumerator, "TestZeroNumerator");

  return 0;
}
