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
	int assign_number(const int &);
	friend int a_bigger_b(const BigInt &, const BigInt &);
	friend BigInt abs_sum(const BigInt &, const BigInt &, int sign = 1);
	friend BigInt abs_diff(const BigInt &, const BigInt &, int sign = 1);
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
	friend BigInt operator-(const BigInt &, const BigInt &);
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

int BigInt::assign_number(const int &value) {
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
	return n;
}

BigInt::BigInt(const long long &value) {
	int number = abs(value);
	set_size(this->assign_number(value));
	for (int i = 0; i < this->size; i++) {
		this->values[i] = number % BASE;
		number = number / BASE;
	}
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
	int new_size = temp.real_size();
	if (new_size == 0) {
		os << '0';
	}
	else {
		if (temp.sign == -1) {
			os << '-';
		}
		for (int i = new_size - 1; i >= 0; i--) {
			int d = temp.BASE / 10;
			int &v = temp.values[i];
			while (d > v + 1 && i < new_size - 1) {
				os << '0';
				d /= 10;
			}
			os << v;
		}
	}
	return os;
}

void BigInt::assign(const char *string) {
	int length = (int)strlen(string);
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
	char str[10003];
	is >> str;
	value.assign(str);
	return is;
}

int a_bigger_b(const BigInt &a, const BigInt &b) {
	int flag = 0;
	int real_size_a = a.real_size();
	int real_size_b = b.real_size();
	if (real_size_a > real_size_b) {
		flag = 1;
	}
	else if (real_size_b > real_size_a) {
		flag = -1;
	}
	else {
		for (int i = real_size_a - 1; i >= 0 && flag == 0; --i) {
			if (a.values[i] > b.values[i]) {
				flag = 1;
			}
			if (a.values[i] < b.values[i]) {
				flag = -1;
			}
		}
	}
	return flag;
}

BigInt abs_sum(const BigInt &a, const BigInt &b, int sign) {
	size_t res_size;
	if (a_bigger_b(a, b) == 1) {
		res_size = a.size + 1;
	}
	else {
		res_size = b.size + 1;
	}
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
	res.sign = sign;
	return res;
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
		if (a_bigger_b(a, b) >= 0) {
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

int main() {
	BigInt a((size_t)1);
	BigInt b((size_t)1);
	std::cin >> a >> b;
	std::cout << a - b << std::endl;
	return 0;
}