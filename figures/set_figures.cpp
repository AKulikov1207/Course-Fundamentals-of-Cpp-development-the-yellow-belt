#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <memory>
#include <iomanip>
#include <cmath>

using namespace std;

const double PI = 3.14;  // число ПИ

class Figure {
public:
	virtual string Name() const = 0;
	virtual double Perimeter() = 0;
	virtual double Area() = 0;

	virtual ~Figure() = default;
};

class Triangle : public Figure {
public:
	Triangle(double a, double b, double c) : a_{ a }, b_{ b }, c_{ c } {}

	string Name() const override { return name_; }
	double Perimeter() override { return a_ + b_ + c_; }
	double Area() override {
		double p = (a_ + b_ + c_) / 2;   // полупериметр
		double S = sqrt(p * (p - a_) * (p - b_) * (p - c_));
		return S;
	}

private:
	double a_, b_, c_;
	const string name_ = "TRIANGLE";
};

class Rect : public Figure {
public:
	Rect(double w, double h) : width_{ w }, height_{ h } {}

	string Name() const override { return name_; }
	double Perimeter() override { return 2 * (width_ + height_); }
	double Area() override { return width_ * height_; }

private:
	double width_, height_;
	const string name_ = "RECT";
};

class Circle : public Figure {
public:
	Circle(double r) : radius{ r } {}

	string Name() const override { return name_; }
	double Perimeter() override { return 2 * PI * radius; }
	double Area() override { return PI * radius * radius; }

private:
	double radius;
	const string name_ = "CIRCLE";
};

shared_ptr<Figure> CreateFigure(istringstream& is) {
	string fig;
	is >> fig;
	if (fig == "RECT") {
		int w, h;
		is >> w >> h;
		auto rect = make_shared<Rect>(w, h);
		return rect;
	}
	else if (fig == "CIRCLE") {
		int r;
		is >> r;
		auto circle = make_shared<Circle>(r);
		return circle;
	}
	else if (fig == "TRIANGLE") {
		int a, b, c;
		is >> a >> b >> c;
		auto triangle = make_shared<Triangle>(a, b, c);
		return triangle;
	}
	throw invalid_argument("invalid figure name was specified");
}

int main() {
	vector<shared_ptr<Figure>> figures;
	for (string line; getline(cin, line); ) {
		istringstream is(line);

		string command;
		is >> command;
		if (command == "ADD") {
			// Пропускаем "лишние" ведущие пробелы.
			is >> ws;
			figures.push_back(CreateFigure(is));
		}
		else if (command == "PRINT") {
			for (const auto& current_figure : figures) {
				cout << fixed << setprecision(3)
					<< current_figure->Name() << " "
					<< current_figure->Perimeter() << " "
					<< current_figure->Area() << endl;
			}
		}
	}
	return 0;
}
