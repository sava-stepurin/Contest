#include <iostream>
#include <cstdlib>
#include <cstring>
#include <stdexcept>

class BigIntegerDivisionByZero : std::logic_error {
public:
	BigIntegerDivisionByZero();
};

BigIntegerDivisionByZero::BigIntegerDivisionByZero() : std::logic_error("Division by zero") {}

class BigIntegerOverflow : std::runtime_error {
public:
	BigIntegerOverflow();
};

BigIntegerOverflow::BigIntegerOverflow() : std::runtime_error("Division by zero") {}


class BigInt {
private:
	static const int BASE = 1000000;
	static const int DIGIT_COUNT = 6;
	static const int MAX = 20000 / DIGIT_COUNT + 2;
	int *values;
	int size;
	int sign;
	void set_size(const int);
	void assign_number(const int &);
	friend BigInt abs_sum(const BigInt &, const BigInt &, int sign = 1);
	friend BigInt abs_diff(const BigInt &, const BigInt &, int sign = 1);
	friend BigInt abs_mult(const BigInt &, const BigInt &, int sign = 1);
	int real_size() const;
	void assign(const char *);
public:
	BigInt(const char *);
	BigInt(const long long &);
	BigInt(const BigInt &);
	BigInt(const size_t &);
	~BigInt();
	friend std::ostream &operator<<(std::ostream &, const BigInt &);
	friend std::istream &operator >> (std::istream &, BigInt &);
	friend int abs_a_bigger_b(const BigInt &, const BigInt &);
	BigInt &operator=(const BigInt &);
	BigInt &operator=(const char *);
	BigInt &operator=(const long long &);
	BigInt &operator+=(const BigInt &);
	BigInt &operator+=(const long long &);
	BigInt &operator-=(const BigInt &);
	BigInt &operator-=(const long long &);
	BigInt &operator*=(const BigInt &);
	BigInt &operator*=(const long long &);
	BigInt &operator/=(const BigInt &);
	BigInt &operator/=(const long long &);
	BigInt &operator++();
	BigInt operator++(int);
	BigInt &operator--();
	BigInt operator--(int);
	friend BigInt operator+(const BigInt &, const BigInt &);
	friend BigInt operator+(const BigInt &, const long long &);
	friend BigInt operator+(const long long &, const BigInt &);
	friend BigInt operator-(const BigInt &, const BigInt &);
	friend BigInt operator-(const BigInt &, const long long &);
	friend BigInt operator-(const long long &, const BigInt &);
	friend BigInt operator*(const BigInt &, const BigInt &);
	friend BigInt operator*(const BigInt &, const long long &);
	friend BigInt operator*(const long long &, const BigInt &);
	friend BigInt operator/(const BigInt &, const BigInt &);
	friend BigInt operator/(const BigInt &, const long long &);
	friend BigInt operator/(const long long &, const BigInt &);
};

int BigInt::real_size() const {
	int new_size = this->size;
	while (new_size > 0 && this->values[new_size - 1] == 0) {
		new_size--;
	}
	return new_size;
}

BigInt::BigInt(const char *string) {
	assign(string);
}

void BigInt::set_size(const int size) {
	if (size > this->MAX) {
		throw BigIntegerOverflow();
	}
	this->size = size;
	this->values = new int[this->size];
	for (int i = 0; i < this->size; i++) {
		this->values[i] = 0;
	}
}

void BigInt::assign_number(const int &value) {
	int number = abs(value);
	if (value < 0) {
		this->sign = -1;
	}
	else {
		this->sign = 1;
	}
	int v = BASE;
	int n = 1;
	while (v < number) {
		v *= BASE;
		n++;
	}
	set_size(n);
	for (int i = 0; i < this->size; i++) {
		this->values[i] = number % BASE;
		number = number / BASE;
	}
}

BigInt::BigInt(const long long &value) {
	assign_number(value);
}

BigInt::BigInt(const BigInt &that) {
	this->sign = that.sign;
	set_size(that.size);
	std::memcpy(this->values, that.values, that.size * sizeof(int));
}

BigInt::BigInt(const size_t &size) {
	this->set_size(size);
}

BigInt::~BigInt() {
	delete[]this->values;
}

std::ostream &operator<<(std::ostream &os, const BigInt &temp) {
	int size = temp.real_size();
	if (size == 0) {
		os << '0';
	}
	else {
		if (temp.sign == -1) {
			os << '-';
		}
		for (int i = size - 1; i >= 0; i--) {
			int d = temp.BASE / 10;
			int &v = temp.values[i];
			while (d > v + 1 && i < size - 1) {
				os << '0';
				d /= 10;
			}
			os << v;
		}
	}
	return os;
}

void BigInt::assign(const char *string) {
	int length = strlen(string);
	int k = 0;
	if (string[0] == '-') {
		this->sign = -1;
		length--;
		k = 1;
	}
	else {
		this->sign = 1;
	}
	set_size(length / DIGIT_COUNT + (length % DIGIT_COUNT != 0));
	for (int i = 0; i < this->size; i++) {
		int value = 0;
		for (int j = length - (i + 1) * DIGIT_COUNT + k; j < length - i * DIGIT_COUNT + k; ++j) {
			if (j >= 0 && string[j] != '-') {
				value = (value * 10) + (string[j] - '0');
			}
		}
		this->values[i] = value;
	}
}

std::istream &operator >> (std::istream &is, BigInt &value) {
	char str[10005];
	is >> str;
	value.assign(str);
	return is;
}

BigInt &BigInt::operator=(const BigInt &that) {
	this->sign = that.sign;
	if (that.size > this->size) {
		delete[]this->values;
		set_size(that.size);
	}
	std::memcpy(this->values, that.values, that.size * sizeof(int));
	for (int i = this->size - 1; i >= that.size; --i) {
		this->values[i] = 0;
	}
	return *this;
}

BigInt &BigInt::operator=(const char *string) {
	delete[]this->values;
	this->assign(string);
	return *this;
}

BigInt &BigInt::operator=(const long long &value) {
	delete[]this->values;
	this->assign_number(value);
	return *this;
}

BigInt &BigInt::operator+=(const BigInt &that) {
	*this = *this + that;
	return *this;
}

BigInt &BigInt::operator+=(const long long &that) {
	*this = *this + that;
	return *this;
}

BigInt &BigInt::operator-=(const BigInt &that) {
	*this = *this - that;
	return *this;
}

BigInt &BigInt::operator-=(const long long &that) {
	*this = *this - that;
	return *this;
}

BigInt &BigInt::operator*=(const BigInt &that) {
	*this = *this * that;
	return *this;
}

BigInt &BigInt::operator*=(const long long &that) {
	*this = *this * that;
	return *this;
}

BigInt &BigInt::operator/=(const BigInt &that) {
	*this = *this / that;
	return *this;
}

BigInt &BigInt::operator/=(const long long &that) {
	*this = *this / that;
	return *this;
}

BigInt &BigInt::operator++() {
	*this += 1;
	return *this;
}

BigInt BigInt::operator++(int) {
	BigInt old(*this);
	++*this;
	return old;
}

BigInt &BigInt::operator--() {
	*this -= 1;
	return *this;
}

BigInt BigInt::operator--(int) {
	BigInt old(*this);
	--*this;
	return old;
}

int abs_a_bigger_b(const BigInt &a, const BigInt &b) {
	int flag = 0;
	int real_size_a = a.real_size();
	int real_size_b = b.real_size();
	if (real_size_a != real_size_b) {
		flag = real_size_a - real_size_b;
	}
	else {
		int i = real_size_a - 1;
		while (i >= 0 && a.values[i] == b.values[i]) {
			i--;
		}
		flag = a.values[i] - b.values[i];
	}
	return flag;
}

BigInt abs_sum(const BigInt &a, const BigInt &b, int sign) {
	size_t res_size;
	res_size = (a.size < b.size ? b.size : a.size) + 1;
	BigInt res((size_t)res_size);
	int rest = 0;
	int sum = 0;
	for (int i = 0; i < res.size || rest != 0; i++) {
		sum = 0;
		if (i < b.size) {
			sum += b.values[i];
		}
		if (i < a.size) {
			sum += a.values[i];
		}
		res.values[i] = (sum + rest) % res.BASE;
		rest = (sum + rest) / res.BASE;
	}
	if (res.real_size() > res.MAX) {
		throw BigIntegerOverflow();
	}
	res.sign = sign;
	return res;
}

BigInt operator+(const BigInt &a, const BigInt &b) {
	if (a.sign == b.sign) {
		return abs_sum(a, b, a.sign);
	}
	else {
		if (abs_a_bigger_b(a, b) >= 0) {
			return abs_diff(a, b, a.sign);
		}
		else {
			return abs_diff(b, a, b.sign);
		}
	}
}

BigInt operator+(const BigInt &a, const long long &b) {
	return a + BigInt((long long)b);
}

BigInt operator+(const long long &a, const BigInt &b) {
	return b + BigInt((long long)a);
}

BigInt abs_diff(const BigInt &a, const BigInt &b, int sign) {
	BigInt res((size_t)a.size);
	int temp = 0;
	for (int i = 0; i < a.size; i++) {
		res.values[i] = a.values[i];
		int add = 0;
		if (i < b.size) {
			add = b.values[i];
		}
		if (res.values[i] < add + temp) {
			res.values[i] += res.BASE;
			res.values[i] -= add + temp;
			temp = 1;
		}
		else {
			res.values[i] -= add + temp;
			temp = 0;
		}
	}
	res.sign = sign;
	return res;
}

BigInt operator-(const BigInt &a, const BigInt &b) {
	if (a.sign == b.sign) {
		if (abs_a_bigger_b(a, b) >= 0) {
			return abs_diff(a, b, a.sign);
		}
		else {
			return abs_diff(b, a, -1 * a.sign);
		}
	}
	else {
		return abs_sum(a, b, a.sign);
	}
}

BigInt operator-(const BigInt &a, const long long &b) {
	return a - BigInt((long long)b);
}

BigInt operator-(const long long &a, const BigInt &b) {
	return BigInt((long long)a) - b;
}


BigInt abs_mult(const BigInt &a, const BigInt &b, int sign) {
	BigInt res((size_t)(a.size + b.size));
	long long rest = 0;
	long long mult = 0;
	for (int i = 0; i < a.size; i++) {
		rest = 0;
		mult = 0;
		for (int j = 0; j < b.size || rest != 0; j++) {
			if (j < b.size) {
				mult = res.values[j + i] + a.values[i] * b.values[j] + rest;
			}
			else {
				mult = res.values[j + i] + rest;
			}
			res.values[j + i] = mult % res.BASE;
			rest = mult / res.BASE;
		}
	}
	if (res.real_size() > res.MAX) {
		throw BigIntegerOverflow();
	}
	res.sign = sign;
	return res;
}


BigInt operator*(const BigInt &a, const BigInt &b) {
	return abs_mult(a, b, a.sign * b.sign);
}

BigInt operator*(const BigInt &a, const long long &b) {
	return a * BigInt((long long)b);
}

BigInt operator*(const long long &a, const BigInt &b) {
	return BigInt((long long)a) * b;
}

BigInt operator/(const BigInt &a, const BigInt &b) {
	BigInt zero((long long)0);
	if (abs_a_bigger_b(b, zero) == 0) {
		throw BigIntegerDivisionByZero();
	}
	if (abs_a_bigger_b(a, b) < 0) {
		BigInt res((long long)0);
		res.sign = 1;
		return res;
	}
	else {
		int real_size_a = a.real_size();
		int real_size_b = b.real_size();
		BigInt res((size_t)real_size_a - real_size_b + 1);
		BigInt temp((size_t)real_size_b + 1);
		for (int i = real_size_a - real_size_b; i < real_size_a; i++) {
			temp.values[i - real_size_a + real_size_b] = a.values[i];
		}
		int k = real_size_a - real_size_b;
		int res_value;
		while (k >= 0) {
			res_value = 0;
			while (abs_a_bigger_b(temp, b) >= 0) {
				temp = abs_diff(temp, b);
				res_value++;
			}
			res.values[k] = res_value;
			if (k > 0) {
				for (int i = real_size_b - 1; i >= 0; i--) {
					temp.values[i + 1] = temp.values[i];
				}
				temp.values[0] = a.values[k - 1];
			}
			k--;
		}
		res.sign = 1;
		return res;
	}
}

BigInt operator/(const BigInt &a, const long long &b) {
	return a / BigInt((long long)b);
}

BigInt operator/(const long long &a, const BigInt &b) {
	return BigInt((long long)a) / b;
}

int main() {}