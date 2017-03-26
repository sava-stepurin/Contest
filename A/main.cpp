#include <iostream>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <iomanip>

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
class Segment;
class Line;
class Ray;
class Polygon;

class Shape {
public:
	virtual void remove(const Vector &) = 0;
	virtual bool contains_point(const Point &) = 0;
	virtual bool cross_segment(const Segment &) = 0;
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
	bool operator==(const Point &) const;
	double distance(const Point &) const;
	void remove(const Vector &);
	bool contains_point(const Point &);
	bool cross_segment(const Segment &);
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
	void remove(const Vector &);
	bool contains_point(const Point &);
	bool cross_segment(const Segment &); 
	double distance_point(const Point &) const;
	double distance_segment(const Segment &);
};

class Line : public Shape {
	double a;
	double b;
	double c;
public:
	Line();
	Line(const Point &, const Point &);
	Line(const Line &);
	Line(const double, const double, const double);
	Line &operator=(const Line &);
	void remove(const Vector &);
	bool contains_point(const Point &);
	bool cross_segment(const Segment &);
	bool parallel(const Line &);
	double distance_point(const Point &) const;
	Point find_point();
	Point line_intersection(const Line &);
	Vector direct_vector();
};

class Ray : public Shape {
	Point start;
	Point lay_on_ray;
public:
	Ray();
	Ray(const Point &, const Point &);
	Ray(const Ray &);
	Ray &operator=(const Ray &);
	void remove(const Vector &);
	bool contains_point(const Point &);
	bool cross_segment(const Segment &);
	double distance_point(const Point &) const;
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
	void remove(const Vector &);
	bool contains_point(const Point &);
	bool cross_segment(const Segment &);
	bool convex();
	double square();
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

bool Point::operator==(const Point &that) const {
	return this->x == that.x && this->y == that.y;
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

void Point::remove(const Vector &that) {
	this->x += that.get_x();
	this->y += that.get_y();
}

bool Point::contains_point(const Point &that) {
	return (this->x == that.x) && (this->y == that.y);
}

bool Point::cross_segment(const Segment &that) {
	Vector a(that.get_right().get_x() - that.get_left().get_x(), that.get_right().get_y() - that.get_left().get_y());
	Vector b(this->x - that.get_left().get_x(), this->y - that.get_left().get_y());
	Vector c(this->x - that.get_right().get_x(), this->y - that.get_right().get_y());
	return a.vector_mult(b) == 0 && b * c <= 0;
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

void Segment::remove(const Vector &that) {
	this->left.remove(that);
	this->right.remove(that);
}

bool Segment::contains_point(const Point &that) {
	Vector left_right(this->right.get_x() - this->left.get_x(), this->right.get_y() - this->left.get_y());
	Vector left_point(that.get_x() - this->left.get_x(), that.get_y() - this->left.get_y());
	Vector right_point(that.get_x() - this->right.get_x(), that.get_y() - this->right.get_y());
	return left_right.vector_mult(left_point) == 0 && left_point * right_point <= 0;
}

bool Segment::cross_segment(const Segment &that) {
	Line this_line(this->get_left(), this->get_right());
	Line that_line(that.get_left(), that.get_right());

	bool flag1 = this_line.cross_segment(that);
	bool flag2 = that_line.cross_segment(*this);
	double x1, y1, x2, y2, x3, y3, x4, y4;
	x1 = this->left.get_x() >= this->right.get_x() ? this->right.get_x() : this->left.get_x();
	x2 = this->left.get_x() < this->right.get_x() ? this->right.get_x() : this->left.get_x();
	y1 = this->left.get_y() >= this->right.get_y() ? this->right.get_y() : this->left.get_y();
	y2 = this->left.get_y() < this->right.get_y() ? this->right.get_y() : this->left.get_y();
	x3 = that.left.get_x() >= that.right.get_x() ? that.right.get_x() : that.left.get_x();
	x4 = that.left.get_x() < that.right.get_x() ? that.right.get_x() : that.left.get_x();
	y3 = that.left.get_y() >= that.right.get_y() ? that.right.get_y() : that.left.get_y();
	y4 = that.left.get_y() < that.right.get_y() ? that.right.get_y() : that.left.get_y();
	bool flag3 = (x2 >= x3) && (x1 <= x4) && (y2 >= y3) && (y1 <= y4);
	return flag1 && flag2 && flag3;
}

double Segment::distance_point(const Point &that) const {
	Ray ab(this->left, this->right);
	Ray ba(this->right, this->left);
	double res = (ab.distance_point(that) > ba.distance_point(that)) ? ab.distance_point(that) : ba.distance_point(that);
	return res;
}

double Segment::distance_segment(const Segment &that) {
	double res;
	if (this->left == this->right) {
		if (that.left == that.right) {
			res = this->left.distance(that.left);
		}
		else {
			res = that.distance_point(this->left);
		}
	}
	else if (that.left == that.right) {
		res = this->distance_point(that.left);
	}
	else if (this->cross_segment(that)) {
		res = 0;
	}
	else {
		double min1 = (this->distance_point(that.left) > this->distance_point(that.right)) ? this->distance_point(that.right) : this->distance_point(that.left);
		double min2 = (that.distance_point(this->left) > that.distance_point(this->right)) ? that.distance_point(this->right) : that.distance_point(this->left);
		res = (min1 > min2) ? min2 : min1;
	}
	return res;
}


//-------------------------------------

Line::Line() {
	this->a = 0;
	this->b = 0;
	this->c = 0;
}

Line::Line(const Point& a, const Point &b) {
	this->a = b.get_y() - a.get_y();
	this->b = a.get_x() - b.get_x();
	this->c = a.get_y() * b.get_x() - a.get_x() * b.get_y();
}

Line::Line(const Line &that) {
	this->a = that.a;
	this->b = that.b;
	this->c = that.c;
}

Line::Line(const double a, const double b, const double c) {
	this->a = a;
	this->b = b;
	this->c = c;
}

Line &Line::operator=(const Line &that) {
	this->a = that.a;
	this->b = that.b;
	this->c = that.c;
	return *this;
}

void Line::remove(const Vector &that) {
	this->c += this->a * that.get_x() + this->b * that.get_y();
}

bool Line::contains_point(const Point &that) {
	return this->a * that.get_x() + this->b * that.get_y() + this->c == 0;
}

bool Line::cross_segment(const Segment &that) {
	return (this->a * that.get_left().get_x() + this->b * that.get_left().get_y() + this->c) * (this->a * that.get_right().get_x() + this->b * that.get_right().get_y() + this->c) <= 0;
}

bool Line::parallel(const Line &that) {
	return this->a * that.b - this->b * that.a == 0;
}

Point Line::find_point() {
	Point res;
	if (this->a != 0) {
		res = Point(-1 * this->c / this->a, 0);
	}
	else {
		res = Point(0, -1 * this->c / this->b);
	}
	return res;
}

double Line::distance_point(const Point &that) const {
	return abs(this->a * that.get_x() + this->b * that.get_y() + this->c) / sqrt(this->a * this->a + this->b * this->b);
}

Point Line::line_intersection(const Line &that) {
	Point res((this->b * that.c - this->c * that.b) / (this->a * that.b - this->b * that.a), (this->c * that.a - this->a * that.c) / (this->a * that.b - this->b * that.a));
	return res;
}

Vector Line::direct_vector() {
	Vector res(-1 * this->b, this->a);
	return res;
}

//----------------------------------------------------------

Ray::Ray() {
	this->start = Point(0, 0);
	this->lay_on_ray = Point(0, 0);
}

Ray::Ray(const Point &a, const Point &b) {
	this->start = a;
	this->lay_on_ray = b;
}

Ray::Ray(const Ray &that) {
	this->start = that.start;
	this->lay_on_ray = that.lay_on_ray;
}

Ray &Ray::operator=(const Ray &that) {
	this->start = that.start;
	this->lay_on_ray = that.lay_on_ray;
	return *this;
}

void Ray::remove(const Vector &that) {
	this->start.remove(that);
	this->lay_on_ray.remove(that);
}

bool Ray::contains_point(const Point &that) {
	Vector start_lay_on_ray(this->lay_on_ray.get_x() - this->start.get_x(), this->lay_on_ray.get_y() - this->start.get_y());
	Vector start_point(that.get_x() - this->start.get_x(), that.get_y() - this->start.get_y());
	return start_lay_on_ray.vector_mult(start_point) == 0 && start_lay_on_ray * start_point >= 0;
}

bool Ray::cross_segment(const Segment &that) {
	Line ray_line(this->start, this->lay_on_ray);
	bool flag = false;
	if (ray_line.contains_point(that.get_left()) || ray_line.contains_point(that.get_right())) {
		flag = this->contains_point(that.get_left()) || this->contains_point(that.get_right());
	}
	else {
		Line start_that_left(this->start, that.get_left());
		Segment right_ray_on_line(that.get_right(), this->lay_on_ray);
		flag = ray_line.cross_segment(that) && !(start_that_left.cross_segment(right_ray_on_line));
	}
	return flag;
}

double Ray::distance_point(const Point &that) const {
	Vector ray_vector(this->lay_on_ray.get_x() - this->start.get_x(), this->lay_on_ray.get_y() - this->start.get_y());
	Vector point_ray_vector(that.get_x() - this->start.get_x(), that.get_y() - this->start.get_y());
	Line ray_line(lay_on_ray, start);
	double res = 0;
	if (ray_vector * point_ray_vector >= 0) {
		res = ray_line.distance_point(that);
	}
	else {
		res = that.distance(this->start);
	}
	return res;
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

void Polygon::remove(const Vector &that) {
	for (int i = 0; i < this->amount; i++) {
		this->data[i].remove(that);
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

bool Polygon::cross_segment(const Segment &that) {
	bool flag = false;
	Segment edge(this->data[this->amount - 1], this->data[0]);
	if (edge.cross_segment(that)) {
		flag = true;
	}
	for (int i = 0; i < this->amount - 1; i++) {
		edge = Segment(this->data[i], this->data[i + 1]);
		if (edge.cross_segment(that)) {
			flag = true;
		}
	}
	if (flag == false) {
		if (this->contains_point(that.get_left())) {
			flag = true;
		}
	}
	return flag;
}

bool Polygon::convex() {
	Vector first(this->data[0].get_x() - this->data[this->amount - 1].get_x(), this->data[0].get_y() - this->data[this->amount - 1].get_y());
	Vector second(this->data[1].get_x() - this->data[0].get_x(), this->data[1].get_y() - this->data[0].get_y());
	bool flag = true;
	double mult = first.vector_mult(second);
	for (int i = 0; i < this->amount - 1; i++) {
		if (i == this->amount - 2) {
			first = Vector(this->data[this->amount - 1].get_x() - this->data[this->amount - 2].get_x(), this->data[this->amount - 1].get_y() - this->data[this->amount - 2].get_y());
			second = Vector(this->data[0].get_x() - this->data[this->amount - 1].get_x(), this->data[0].get_y() - this->data[this->amount - 1].get_y());
		}
		else {
			first = Vector(this->data[i + 1].get_x() - this->data[i].get_x(), this->data[i + 1].get_y() - this->data[i].get_y());
			second = Vector(this->data[i + 2].get_x() - this->data[i + 1].get_x(), this->data[i + 2].get_y() - this->data[i + 1].get_y());
		}
		if (mult == 0) {
			mult = first.vector_mult(second);
		}
		if (first.vector_mult(second) * mult < 0) {
			flag = false;
		}
	}
	return flag;
}

double Polygon::square() {
	Vector first, second;
	second = Vector(this->data[0].get_x(), this->data[0].get_y());
	double res = 0;
	for (int i = 0; i < this->amount; i++) {
		first = second;
		if (i == this->amount - 1) {
			second = Vector(this->data[0].get_x(), this->data[0].get_y());
		}
		else {
			second = Vector(this->data[i + 1].get_x(), this->data[i + 1].get_y());
		}
		res += first.vector_mult(second) / 2;
	}
	return abs(res);
}

int main() {}