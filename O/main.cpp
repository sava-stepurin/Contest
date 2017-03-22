#include <iostream>
#include <cstdlib>
#include <cstring>


class BigInt {
private:
	static const int BASE = 10;
	static const int DIGIT_COUNT = 1;
	int *values;
	int size;
	int sign;
	void set_size(const int);
	void assign_number(const int &);
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
	friend BigInt operator*(const BigInt &, const BigInt &);
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
	size_t length = strlen(string);
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
	res.sign = sign;
	return res;
}


BigInt operator*(const BigInt &a, const BigInt &b) {
	return abs_mult(a, b, a.sign * b.sign);
}

int main() {
	BigInt a((size_t)1);
	BigInt b((size_t)1);
	std::cin >> a >> b;
	std::cout << a * b << std::endl;
	return 0;
}