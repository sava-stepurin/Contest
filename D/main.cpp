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
class Segment;
class Line;
class Ray;

class Shape {
public:
	virtual void replace(const Vector &) = 0;
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
	double distance(const Point &) const;
	void replace(const Vector &);
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
	void replace(const Vector &);
	bool contains_point(const Point &);
	bool cross_segment(const Segment &);
};

class Line : public Shape {
	double a;
	double b;
	double c;
public:
	Line();
	Line(const Point &, const Point &);
	Line(const Line &);
	Line &operator=(const Line &);
	void replace(const Vector &);
	bool contains_point(const Point &);
	bool cross_segment(const Segment &);
};

class Ray : public Shape {
	Point start;
	Point lay_on_ray;
public:
	Ray();
	Ray(const Point &, const Point &);
	Ray(const Ray &);
	Ray &operator=(const Ray &);
	void replace(const Vector &);
	bool contains_point(const Point &);
	bool cross_segment(const Segment &);
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

Line &Line::operator=(const Line &that) {
	this->a = that.a;
	this->b = that.b;
	this->c = that.c;
	return *this;
}

void Line::replace(const Vector &that) {
	this->c += this->a * that.get_x() + this->b * that.get_y();
}

bool Line::contains_point(const Point &that) {
	return this->a * that.get_x() + this->b * that.get_y() + this->c == 0;
}

bool Line::cross_segment(const Segment &that) {
	return (this->a * that.get_left().get_x() + this->b * that.get_left().get_y() + this->c) * (this->a * that.get_right().get_x() + this->b * that.get_right().get_y() + this->c) <= 0;
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

void Ray::replace(const Vector &that) {
	this->start.replace(that);
	this->lay_on_ray.replace(that);
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

int main() {
	Point c;
	Point a, b;
	std::cin >> c >> a >> b;
	Line our_line(a, b);
	Segment our_segment(a, b);
	Ray our_ray(a, b);
	if (our_line.contains_point(c)) {
		std::cout << "YES" << std::endl;
	}
	else {
		std::cout << "NO" << std::endl;
	}
	if (our_ray.contains_point(c)) {
		std::cout << "YES" << std::endl;
	}
	else {
		std::cout << "NO" << std::endl;
	}
	if (our_segment.contains_point(c)) {
		std::cout << "YES" << std::endl;
	}
	else {
		std::cout << "NO" << std::endl;
	}
	return 0;
}