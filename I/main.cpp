#include <iostream>
#include <cstdlib>
#include <iostream>
#include <cmath>

class Vector {
	double x;
	double y;
public:
	double get_x() const;
	double get_y() const;
	Vector();
	Vector(const double x, const double y);
	Vector(const Vector &that);

	friend double abs(const Vector&);
	double operator*(const Vector &);
	Vector operator+(const Vector &);
	Vector operator-(const Vector &);
	friend std::ostream &operator<<(std::ostream &, const Vector &);
	friend std::istream &operator >> (std::istream &, Vector &);
	double vector_mult(const Vector &);
};

class Point;
class Polygon;

class Shape {
public:
	virtual void replace(const Vector &) = 0;
	virtual bool contains_point(const Point &) = 0;
};

class Point : public Shape {
	double x;
	double y;
public:
	double get_x() const;
	double get_y() const;
	Point();
	Point(const double x, const double y);
	Point(const Point&);
	Point &operator=(const Point &);
	double distance(const Point &) const;
	void replace(const Vector &);
	bool contains_point(const Point &);
	friend std::ostream &operator<<(std::ostream &, const Point &);
	friend std::istream &operator >> (std::istream &, Point &);
};

class Segment : public Shape {
	Point left;
	Point right;
public:
	Point get_left() const;
	Point get_right() const;
	Segment();
	Segment(const Point &, const Point &);
	Segment(const Segment &);
	Segment &operator=(const Segment &);
	void replace(const Vector &);
	bool contains_point(const Point &);
};

class Polygon : public Shape {
	Point *data;
	int amount;
public:
	Polygon();
	Polygon(const int);
	void add_point(const Point &, const int place);
	Polygon(const Polygon &);
	Polygon &operator=(const Polygon &);
	~Polygon();
	void replace(const Vector &);
	bool contains_point(const Point &);
};

Vector::Vector() {
	this->x = 0;
	this->y = 0;
}

Vector::Vector(const double x, const double y) {
	this->x = x;
	this->y = y;
}

Vector::Vector(const Vector &that) {
	this->x = that.x;
	this->y = that.y;
}

double Vector::get_x() const {
	return this->x;
}

double Vector::get_y() const {
	return this->y;
}

double abs(const Vector &a) {
	return sqrt(a.x * a.x + a.y * a.y);
}


double Vector::operator*(const Vector &that) {
	return this->x * that.x + this->y * that.y;
}

Vector Vector::operator+(const Vector &that) {
	Vector res(this->x + that.x, this->y + that.y);
	return res;
}

Vector Vector::operator-(const Vector &that) {
	Vector res(this->x - that.x, this->y - that.y);
	return res;
}

std::ostream &operator<<(std::ostream &os, const Vector &temp) {
	os << temp.x << ' ' << temp.y;
	return os;
}

std::istream &operator >> (std::istream &is, Vector &temp) {
	int x, y;
	is >> x >> y;
	temp.x = x;
	temp.y = y;
	return is;
}

double Vector::vector_mult(const Vector &that) {
	return this->x * that.y - this->y * that.x;
}

//------------------------------------------------------------

Point::Point() {
	this->x = 0;
	this->y = 0;
}

Point::Point(const double x, const double y) {
	this->x = x;
	this->y = y;
}

Point::Point(const Point &that) {
	this->x = that.x;
	this->y = that.y;
}

double Point::get_x() const {
	return this->x;
}

double Point::get_y() const {
	return this->y;
}

Point &Point::operator=(const Point &that) {
	this->x = that.x;
	this->y = that.y;
	return *this;
}

double Point::distance(const Point &that) const {
	return sqrt((this->x - that.x) * (this->x - that.x) + (this->y - that.y) * (this->y - that.y));
}

std::ostream &operator<<(std::ostream &os, const Point &temp) {
	os << temp.x << ' ' << temp.y;
	return os;
}

std::istream &operator >> (std::istream &is, Point &temp) {
	int x, y;
	is >> x >> y;
	temp.x = x;
	temp.y = y;
	return is;
}

void Point::replace(const Vector &that) {
	this->x += that.get_x();
	this->y += that.get_y();
}

bool Point::contains_point(const Point &that) {
	return (this->x == that.x) && (this->y == that.y);
}

//---------------------

Segment::Segment() {
	this->left = Point(0, 0);
	this->right = Point(0, 0);
}

Segment::Segment(const Point &a, const Point &b) {
	this->left = a;
	this->right = b;
}

Segment::Segment(const Segment &that) {
	this->left = that.left;
	this->right = that.right;
}

Segment &Segment::operator=(const Segment &that) {
	this->left = that.left;
	this->right = that.right;
	return *this;
}

Point Segment::get_left() const {
	return this->left;
}

Point Segment::get_right() const {
	return this->right;
}

void Segment::replace(const Vector &that) {
	this->left.replace(that);
	this->right.replace(that);
}

bool Segment::contains_point(const Point &that) {
	Vector left_right(this->right.get_x() - this->left.get_x(), this->right.get_y() - this->left.get_y());
	Vector left_point(that.get_x() - this->left.get_x(), that.get_y() - this->left.get_y());
	Vector right_point(that.get_x() - this->right.get_x(), that.get_y() - this->right.get_y());
	return left_right.vector_mult(left_point) == 0 && left_point * right_point <= 0;
}

//-----------------------------------------------------

Polygon::Polygon() {
	this->data = new Point[1];
	this->data[0] = Point(0, 0);
	this->amount = 1;
}

Polygon::Polygon(const int amount) {
	this->amount = amount;
	this->data = new Point[this->amount];
}

Polygon::Polygon(const Polygon &that) {
	this->amount = that.amount;
	this->data = new Point[this->amount];
	for (int i = 0; i < this->amount; i++) {
		this->data[i] = that.data[i];
	}
}

void Polygon::add_point(const Point &that, const int place) {
	this->data[place] = that;
}

Polygon &Polygon::operator=(const Polygon &that) {
	if (this->amount != that.amount) {
		delete[] this->data;
		this->amount = that.amount;
		this->data = new Point[this->amount];
	}
	for (int i = 0; i < this->amount; i++) {
		this->data[i] = that.data[i];
	}
	return *this;
}

Polygon::~Polygon() {
	delete[] this->data;
}

void Polygon::replace(const Vector &that) {
	for (int i = 0; i < this->amount; i++) {
		this->data[i].replace(that);
	}
}

bool Polygon::contains_point(const Point &that) {
	bool flag = false;
	Segment edge(this->data[this->amount - 1], this->data[0]);
	if (edge.contains_point(that)) {
		flag = true;
	}
	for (int i = 0; i < this->amount - 1; i++) {
		edge = Segment(this->data[i], this->data[i + 1]);
		if (edge.contains_point(that)) {
			flag = true;
		}
	}
	if (flag == false) {
		double sum = 0;
		Vector first(this->data[this->amount - 1].get_x() - that.get_x(), this->data[this->amount - 1].get_y() - that.get_y());
		Vector second(this->data[0].get_x() - that.get_x(), this->data[0].get_y() - that.get_y());
		int sign = 1;
		if (first.vector_mult(second) < 0) {
			sign = -1;
		}
		sum += (acos(first * second / abs(first) / abs(second))  * sign);
		for (int i = 0; i < this->amount - 1; i++) {
			first = second;
			second = Vector(this->data[i + 1].get_x() - that.get_x(), this->data[i + 1].get_y() - that.get_y());
			sign = 1;
			if (first.vector_mult(second) < 0) {
				sign = -1;
			}
			sum += (acos(first * second / abs(first) / abs(second))  * sign);
		}
		flag = !(fabs(sum - 0) < 1e-8);
	}
	return flag;
}

int main() {
	int n;
	std::cin >> n;
	Point a;
	std::cin >> a;
	Polygon p(n);
	for (int i = 0; i < n; i++) {
		Point b;
		std::cin >> b;
		p.add_point(b, i);
	}
	if (p.contains_point(a)) {
		std::cout << "YES" << std::endl;
	}
	else {
		std::cout << "NO" << std::endl;
	}
	return 0;
}