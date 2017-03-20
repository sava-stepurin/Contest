#include <iostream>
#include <cstdlib>
using namespace std;


class Rational {
private:
	int p;
	int q;

	void assign(const char *);
	void reduce()
	{
		int abs_p = abs(this->p);
		int abs_q = abs(this->q);
		while (abs_p != 0 && abs_q != 0) {
			if (abs_p > abs_q) {
				abs_p = abs_p % abs_q;
			}
			else {
				abs_q = abs_q % abs_p;
			}
		}
		this->p /= abs_p + abs_q;
		this->q /= abs_p + abs_q;
	}
	friend int a_bigger_b(const Rational &, const Rational &);

public:
	Rational();
	Rational(const int p, const int q = 1);
	Rational(const char *);
	Rational(const Rational &);
	int getNumerator() const;
	int getDenominator() const;
	friend istream &operator >> (istream &, Rational &);
	friend ostream &operator<<(ostream &, Rational &);
	friend Rational operator+(const Rational &, const Rational &);
	friend Rational operator+(const Rational &, const int &);
	friend Rational operator+(const int &, const Rational &);
	friend Rational operator-(const Rational &, const Rational &);
	friend Rational operator-(const Rational &, const int &);
	friend Rational operator-(const int &, const Rational &);
	friend Rational operator*(const Rational &, const Rational &);
	friend Rational operator*(const Rational &, const int &);
	friend Rational operator*(const int &, const Rational &);
	friend Rational operator/(const Rational &, const Rational &);
	friend Rational operator/(const Rational &, const int &);
	friend Rational operator/(const int &, const Rational &);
	Rational &operator=(const Rational &);
	Rational &operator=(const int &);
	Rational &operator+=(const Rational &);
	Rational &operator+=(const int &);
	Rational &operator-=(const Rational &);
	Rational &operator-=(const int &);
	Rational &operator*=(const Rational &);
	Rational &operator*=(const int &);
	Rational &operator/=(const Rational &);
	Rational &operator/=(const int &);
	friend bool operator>(const Rational &, const Rational &);
	friend bool operator>(const Rational &, const int &);
	friend bool operator>(const int &, const Rational &);
	friend bool operator>=(const Rational &, const Rational &);
	friend bool operator>=(const Rational &, const int &);
	friend bool operator>=(const int &, const Rational &);
	friend bool operator<(const Rational &, const Rational &);
	friend bool operator<(const Rational &, const int &);
	friend bool operator<(const int &, const Rational &);
	friend bool operator<=(const Rational &, const Rational &);
	friend bool operator<=(const Rational &, const int &);
	friend bool operator<=(const int &, const Rational &);
	friend bool operator==(const Rational &, const Rational &);
	friend bool operator==(const Rational &, const int &);
	friend bool operator==(const int &, const Rational &);
	friend bool operator!=(const Rational &, const Rational &);
	friend bool operator!=(const Rational &, const int &);
	friend bool operator!=(const int &, const Rational &);
	friend Rational operator-(const Rational &);
	friend Rational operator+(const Rational &);
	Rational &operator++();
	Rational operator++(int);
	Rational &operator--();
	Rational operator--(int);
};

Rational::Rational() {
	this->p = 0;
	this->q = 1;
}

Rational::Rational(const int p, const int q) {
	int sign = 1;
	if (p * q < 0) {
		sign = -1;
	}
	int abs_p = abs(p);
	int abs_q = abs(q);
	this->p = abs_p * sign;
	this->q = abs_q;
	this->reduce();
}

Rational::Rational(const Rational &that) {
	this->p = that.p;
	this->q = that.q;
}

void Rational::assign(const char *string) {
	int p = 0;
	int i = 0;
	int sign = 1;
	while (string[i] != '/' && string[i] != 0) {
		if (string[i] == '-') {
			sign = -1;
		}
		else {
			p = p * 10 + string[i] - '0';
		}
		i++;
	}
	p *= sign;
	int q = 0;
	if (string[i] == 0) {
		q = 1;
	}
	else {
		i++;
		while (string[i] != 0) {
			q = q * 10 + string[i] - '0';
			i++;
		}
	}
	this->p = p;
	this->q = q;
}

Rational::Rational(const char *string) {
	this->assign(string);
}

int Rational::getNumerator() const {
	return this->p;
}

int Rational::getDenominator() const {
	return this->q;
}

istream &operator >> (istream &is, Rational &value) {
	char str[1000];
	is >> str;
	value.assign(str);
	return is;
}

ostream &operator<<(ostream &os, Rational &value) {
	if (value.q == 1) {
		os << value.p;
	}
	else {
		os << value.p << '/' << value.q;
	}
	return os;
}

Rational operator+(const Rational &a, const Rational &b) {
	Rational res;
	res.p = a.p * b.q + a.q * b.p;
	res.q = a.q * b.q;
	res.reduce();
	return res;
}

Rational operator+(const Rational &a, const int &b) {
	return a + Rational(b);
}

Rational operator+(const int &a, const Rational &b) {
	return Rational(a) + b;
}

Rational operator-(const Rational &a, const Rational &b) {
	Rational res;
	res.p = a.p * b.q - a.q * b.p;
	res.q = a.q * b.q;
	res.reduce();
	return res;
}

Rational operator-(const Rational &a, const int &b) {
	return a - Rational(b);
}

Rational operator-(const int &a, const Rational &b) {
	return Rational(a) - b;
}

Rational operator*(const Rational &a, const Rational &b) {
	Rational res;
	res.p = a.p * b.p;
	res.q = a.q * b.q;
	res.reduce();
	return res;
}

Rational operator*(const Rational &a, const int &b) {
	return a * Rational(b);
}

Rational operator*(const int &a, const Rational &b) {
	return Rational(a) * b;
}

Rational operator/(const Rational &a, const Rational &b) {
	Rational res;
	int sign = 1;
	if (a.p * b.p < 0) {
		sign = -1;
	}
	res.p = abs(a.p * b.q) * sign;
	res.q = abs(a.q * b.p);
	res.reduce();
	return res;
}

Rational operator/(const Rational &a, const int &b) {
	return a / Rational(b);
}

Rational operator/(const int &a, const Rational &b) {
	return Rational(a) / b;
}

Rational &Rational::operator=(const Rational &that) {
	this->p = that.p;
	this->q = that.q;
	return *this;
}

Rational &Rational::operator=(const int &that) {
	this->p = that;
	this->q = 1;
	return *this;
}

Rational &Rational::operator+=(const Rational &that) {
	*this = *this + that;
	return *this;
}

Rational &Rational::operator+=(const int &that) {
	*this = *this + Rational(that);
	return *this;
}

Rational &Rational::operator-=(const Rational &that) {
	*this = *this - that;
	return *this;
}

Rational &Rational::operator-=(const int &that) {
	*this = *this - Rational(that);
	return *this;
}

Rational &Rational::operator*=(const Rational &that) {
	*this = *this * that;
	return *this;
}

Rational &Rational::operator*=(const int &that) {
	*this = *this * Rational(that);
	return *this;
}

Rational &Rational::operator/=(const Rational &that) {
	*this = *this / that;
	return *this;
}

Rational &Rational::operator/=(const int &that) {
	*this = *this / Rational(that);
	return *this;
}

int a_bigger_b(const Rational &a, const Rational &b) {
	int flag = 0;
	if (a.p * b.q > a.q * b.p) {
		flag = 1;
	}
	else if (a.p * b.q == a.q * b.p) {
		flag = 0;
	}
	else {
		flag = -1;
	}
	return flag;
}

bool operator>(const Rational &a, const Rational &b) {
	bool flag = false;
	if (a_bigger_b(a, b) == 1) {
		flag = true;
	}
	return flag;
}

bool operator>(const int &a, const Rational &b) {
	return Rational(a) > b;
}

bool operator>(const Rational &a, const int &b) {
	return a > Rational(b);
}

bool operator>=(const Rational &a, const Rational &b) {
	bool flag = false;
	if (a_bigger_b(a, b) >= 0) {
		flag = true;
	}
	return flag;
}

bool operator>=(const int &a, const Rational &b) {
	return Rational(a) >= b;
}

bool operator>=(const Rational &a, const int &b) {
	return a >= Rational(b);
}

bool operator<(const Rational &a, const Rational &b) {
	bool flag = false;
	if (a_bigger_b(a, b) == -1) {
		flag = true;
	}
	return flag;
}

bool operator<(const int &a, const Rational &b) {
	return Rational(a) < b;
}

bool operator<(const Rational &a, const int &b) {
	return a < Rational(b);
}

bool operator<=(const Rational &a, const Rational &b) {
	bool flag = false;
	if (a_bigger_b(a, b) <= 0) {
		flag = true;
	}
	return flag;
}

bool operator<=(const int &a, const Rational &b) {
	return Rational(a) <= b;
}

bool operator<=(const Rational &a, const int &b) {
	return a <= Rational(b);
}

bool operator==(const Rational &a, const Rational &b) {
	bool flag = false;
	if (a_bigger_b(a, b) == 0) {
		flag = true;
	}
	return flag;
}

bool operator==(const int &a, const Rational &b) {
	return Rational(a) == b;
}

bool operator==(const Rational &a, const int &b) {
	return a == Rational(b);
}

bool operator!=(const Rational &a, const Rational &b) {
	bool flag = false;
	if (a_bigger_b(a, b) != 0) {
		flag = true;
	}
	return flag;
}

bool operator!=(const int &a, const Rational &b) {
	return Rational(a) != b;
}

bool operator!=(const Rational &a, const int &b) {
	return a != Rational(b);
}

Rational operator-(const Rational &that) {
	Rational res(that);
	res.p *= -1;
	return res;
}

Rational operator+(const Rational &that) {
	Rational res(that);
	return res;
}

Rational &Rational::operator++() {
	*this += Rational(1);
	return *this;
}

Rational Rational::operator++(int) {
	Rational old(*this);
	++*this;
	return old;
}

Rational &Rational::operator--() {
	*this -= Rational(1);
	return *this;
}

Rational Rational::operator--(int) {
	Rational old(*this);
	--*this;
	return old;
}

int main(int argc, char** argv) {
	int a;
	cin >> a;

	int p, q;
	cin >> p >> q;
	const Rational rc(p, q);
	cout << rc.getNumerator() << ' ' << rc.getDenominator() << endl;

	Rational r1, r2;
	cin >> r1 >> r2;

	cout << r1 << endl;
	cout << r2 << endl;

	cout << (r1 < r2) << endl;
	cout << (r1 <= r2) << endl;
	cout << (r1 > r2) << endl;
	cout << (r1 >= r2) << endl;
	cout << (r1 == r2) << endl;
	cout << (r1 != r2) << endl;

	cout << (r1 < a) << endl;
	cout << (r1 <= a) << endl;
	cout << (r1 > a) << endl;
	cout << (r1 >= a) << endl;
	cout << (r1 == a) << endl;
	cout << (r1 != a) << endl;

	cout << (a < r2) << endl;
	cout << (a <= r2) << endl;
	cout << (a > r2) << endl;
	cout << (a >= r2) << endl;
	cout << (a == r2) << endl;
	cout << (a != r2) << endl;

	cout << rc + a << endl
		<< a + rc << endl
		<< -rc * r1 << endl
		<< (+r1 - r2 * rc) * a << endl;

	cout << ++r1 << endl;
	cout << r1 << endl;
	cout << r1++ << endl;
	cout << r1 << endl;
	cout << --r1 << endl;
	cout << r1 << endl;
	cout << r1-- << endl;
	cout << r1 << endl;
	cout << ++++r1 << endl;
	cout << r1 << endl;

	cout << ((((r1 += r2) /= Rational(-5, 3)) -= rc) *= a) << endl;
	cout << (r1 += r2 /= 3) << endl;
	cout << r1 << endl;
	cout << r2 << endl;
	system("pause");
	return 0;
}