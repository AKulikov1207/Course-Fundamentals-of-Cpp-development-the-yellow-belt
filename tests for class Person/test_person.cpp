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

void TestIncognito() {
	Person person;
	person.ChangeFirstName(1965, "Bjarne");
	person.ChangeLastName(1967, "Stroustrup");
	AssertEqual(person.GetFullName(1900), "Incognito");
}

void TestUnknownFirstName() {
	Person person;
	person.ChangeLastName(1967, "Stroustrup");
	person.ChangeFirstName(1995, "Bjarne");
	AssertEqual(person.GetFullName(1970), "Stroustrup with unknown first name");
}

void TestUnknownLastName() {
	Person person;
	person.ChangeFirstName(1965, "Bjarne");
	person.ChangeLastName(1967, "Stroustrup");
	AssertEqual(person.GetFullName(1965), "Bjarne with unknown last name");
}

void TestChangeFirstName() {
	Person person;
	person.ChangeFirstName(1965, "Bjarne");
	person.ChangeLastName(1967, "Stroustrup");
	person.ChangeFirstName(1970, "Dennis");
	AssertEqual(person.GetFullName(1970), "Dennis Stroustrup");
}

void TestChangeLastName() {
	Person person;
	person.ChangeFirstName(1965, "Bjarne");
	person.ChangeLastName(1967, "Stroustrup");
	person.ChangeFirstName(1970, "Dennis");
	person.ChangeLastName(1968, "Ritchie");
	AssertEqual(person.GetFullName(1969), "Bjarne Ritchie");
}

void TestChangeBothName() {
	Person person;
	person.ChangeFirstName(1965, "Bjarne");
	person.ChangeLastName(1967, "Stroustrup");
	person.ChangeFirstName(1970, "Dennis");
	person.ChangeLastName(1968, "Ritchie");
	AssertEqual(person.GetFullName(1970), "Dennis Ritchie");
}

void TestBothName() {
	Person person;
	person.ChangeFirstName(1965, "Bjarne");
	person.ChangeLastName(1967, "Stroustrup");
	AssertEqual(person.GetFullName(1990), "Bjarne Stroustrup");
}

void TestSaveFirstName() {
	Person person;
	person.ChangeFirstName(1965, "Bjarne");
	person.ChangeLastName(1967, "Stroustrup");
	person.ChangeFirstName(1970, "Dennis");
	AssertEqual(person.GetFullName(1969), "Bjarne Stroustrup");
}

int main() {
	TestRunner runner;
	
	runner.RunTest(TestIncognito, "Test_Incognito");
	runner.RunTest(TestUnknownFirstName, "Test_UnknownFirstName");
	runner.RunTest(TestUnknownLastName, "Test_UnknownLastName");
	runner.RunTest(TestChangeFirstName, "Test_ChangeFirstName");
	runner.RunTest(TestChangeLastName, "Test_ChangeLastName");
	runner.RunTest(TestChangeBothName, "Test_ChangeBothName");
	runner.RunTest(TestBothName, "Test_BothName");
	runner.RunTest(TestSaveFirstName, "Test_SaveFirstName");
	return 0;
}
