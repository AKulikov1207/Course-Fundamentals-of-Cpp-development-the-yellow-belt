#include <iostream>
#include <deque>
#include <string>

using namespace std;

enum class QueryType {
	ADD,
	SUB,
	MUL,
	DIV
};

// Определим структуру для удобной организации данных
struct Query {
	QueryType type;
	string expr;
};

istream& operator >> (istream& is, Query& q) {
	string op;
	is >> op;

	if (op == "+") {
		q.type = QueryType::ADD;
		is >> q.expr;
	}
	else if (op == "-") {
		q.type = QueryType::SUB;
		is >> q.expr;
	}
	else if (op == "*") {
		q.type = QueryType::MUL;
		is >> q.expr;
	}
	else if (op == "/") {
		q.type = QueryType::DIV;
		is >> q.expr;
	}

	return is;
}

int main() {
	int initial_number;
	cin >> initial_number;

	int N;
	cin >> N;

	Query q;
	Query p;
	deque<string> expression;
	expression.push_back(to_string(initial_number));

	for (int i = 0; i < N; ++i) {
		cin >> q;
		switch (q.type) {
			case QueryType::ADD:
				expression.push_back("+");
				expression.push_back(q.expr);
				p = q;
				break;
			case QueryType::SUB:
				expression.push_back("-");
				expression.push_back(q.expr);
				p = q;
				break;
			case QueryType::MUL:
				if (p.type == QueryType::ADD || p.type == QueryType::SUB) {
					expression.push_front("(");
					expression.push_back(")");
				}
				expression.push_back("*");
				expression.push_back(q.expr);
				p = q;
				break;
			case QueryType::DIV:
				if (p.type == QueryType::ADD || p.type == QueryType::SUB) {
					expression.push_front("(");
					expression.push_back(")");
				}
				expression.push_back("/");
				expression.push_back(q.expr);
				p = q;
				break;
		}
	}

	for (const auto& s : expression) {
		if (s == "+" || s == "-" || s == "*" || s == "/") {
			cout << " " << s << " ";
		}
		else {
			cout << s;
		}
	}

	return 0;
}