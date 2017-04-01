#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <cstring>
using namespace std;

class MatrixWrongSizeError : logic_error {
public:
	MatrixWrongSizeError();
};

MatrixWrongSizeError::MatrixWrongSizeError() : logic_error("Error") {}

class MatrixIndexError : logic_error {
public:
	MatrixIndexError();
};

MatrixIndexError::MatrixIndexError() : logic_error("Error") {}

class MatrixIsDegenerateError : logic_error {
public:
	MatrixIsDegenerateError();
};

MatrixIsDegenerateError::MatrixIsDegenerateError() : logic_error("Error") {}

template <typename T>
class Matrix {
private:
	int rowsCnt;
	int colsCnt;
	T **values;
protected:
	Matrix();
	virtual void assign(const Matrix<T> &);
	void free_values();
	void set_size(const int, const int);
	void set_value(const int, const int, const T);
	void add_row(const int, const int, const T);
	void swap_rows(const int, const int);
public:
	Matrix(const int, const int);
	Matrix(const Matrix<T> &);
	virtual ~Matrix();
	Matrix<T> &operator=(const Matrix<T> &);
	Matrix<T> &operator+=(const Matrix<T> &);
	Matrix<T> &operator-=(const Matrix<T> &);
	Matrix<T> &operator*=(const Matrix<T> &);
	Matrix<T> &operator*=(const T);
	Matrix<T> &operator/=(const T);
	Matrix<T> &transpose();
	Matrix<T> getTransposed() const;
	int getRowsNumber() const;
	int getColumnsNumber() const;
	T operator()(const int, const int) const;
	T &operator()(const int, const int);

	Matrix<T> operator+(const Matrix<T> &) const;
	Matrix<T> operator-(const Matrix<T> &) const;

	Matrix<T> operator*(const Matrix<T> &) const;
	Matrix<T> operator*(const T &) const;
	template <typename C>
	friend Matrix<C> operator*(const C, const Matrix<C> &);

	Matrix<T> operator/(const T) const;

	template <typename C>
	friend std::istream &operator >> (std::istream &, Matrix<C> &);
	template <typename C>
	friend std::ostream &operator<<(std::ostream &, const Matrix<C> &);
};

//------------------------------------------------------------

template <typename T>
class SquareMatrix : public Matrix<T> {
protected:
	void assign(const Matrix<T> &);
	SquareMatrix<T> my_minor(const int, const int) const;
public:
	SquareMatrix(const int);
	SquareMatrix(const Matrix<T> &that);
	SquareMatrix<T> operator=(const SquareMatrix<T> &that);
	SquareMatrix<T> &operator+=(const SquareMatrix<T> &);
	SquareMatrix<T> &operator-=(const SquareMatrix<T> &);
	SquareMatrix<T> &operator*=(const SquareMatrix<T> &);
	SquareMatrix<T> &operator*=(const T);
	SquareMatrix<T> &operator/=(const T);
	SquareMatrix<T> &transpose();
	SquareMatrix<T> getTransposed() const;
	SquareMatrix<T> operator+(const SquareMatrix<T> &that) const;
	SquareMatrix<T> operator-(const SquareMatrix<T> &that) const;
	SquareMatrix<T> operator*(const SquareMatrix<T> &that) const;
	SquareMatrix<T> operator*(const T &coefficient) const;
	template<typename C>
	friend SquareMatrix<C> operator*(const C &coefficient, const SquareMatrix<C> matrix);
	SquareMatrix<T> operator/(const T &) const;

	SquareMatrix<T> getInverse() const;
	SquareMatrix<T> &invert();

	T getDeterminant() const;
	int getSize() const;
	T getTrace() const;
};

//----------------------------------------------------------------

class RationalDivisionByZero : logic_error {
public:
	RationalDivisionByZero();
};

RationalDivisionByZero::RationalDivisionByZero() : logic_error("Error") {}

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
	friend ostream &operator<<(ostream &, const Rational &);
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

//-----------------------------------------------------------------

template <typename T>
Matrix<T>::Matrix() {
	this->set_size(1, 1);
}

template <typename T>
void Matrix<T>::assign(const Matrix<T> &that) {
	this->set_size(that.rowsCnt, that.colsCnt);
	this->rowsCnt = that.rowsCnt;
	this->colsCnt = that.colsCnt;
	for (int row = 0; row < that.rowsCnt; row++) {
		for (int col = 0; col < that.colsCnt; col++) {
			this->values[row][col] = that.values[row][col];
		}
	}
}

template<typename T>
void Matrix<T>::free_values() {
	for (int row = 0; row < this->rowsCnt; row++) {
		delete[] this->values[row];
	}
	delete[] this->values;
	this->rowsCnt = 0;
	this->colsCnt = 0;
}

template <typename T>
void Matrix<T>::set_size(const int rowsCnt, const int colsCnt) {
	this->rowsCnt = rowsCnt;
	this->colsCnt = colsCnt;
	this->values = new T *[rowsCnt];
	for (int row = 0; row < rowsCnt; row++) {
		this->values[row] = new T[colsCnt];
		for (int col = 0; col < colsCnt; col++) {
			values[row][col] = 0;
		}
	}
}

template <typename T>
void Matrix<T>::set_value(const int row, const int col, const T value) {
	this->values[row][col] = value;
}

template <typename T>
void Matrix<T>::add_row(const int this_row, const int that_row, const T coefficient) {
	for (int i = 0; i < this->colsCnt; i++) {
		this->set_value(this_row, i, this->values[this_row][i] + this->values[that_row][i] * coefficient);
	}
}

template <typename T>
void Matrix<T>::swap_rows(const int first_row, const int second_row) {
	for (int i = 0; i < this->colsCnt; i++) {
		T temp = this->values[first_row][i];
		this->values[first_row][i] = this->values[second_row][i];
		this->values[second_row][i] = -temp;
	}
}

template <typename T>
Matrix<T>::Matrix(const int rowsCnt, const int colsCnt) {
	this->set_size(rowsCnt, colsCnt);
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T> &that) {
	this->assign(that);
}

template <typename T>
Matrix<T>::~Matrix() {
	for (int row = 0; row < this->rowsCnt; row++) {
		delete[] this->values[row];
	}
	delete[] this->values;
}

template <typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix<T> &that) {
	if (this != &that) {
		this->free_values();
		this->assign(that);
	}
	return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::operator+=(const Matrix<T> &that) {
	*this = *this + that;
	return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::operator-=(const Matrix<T> &that) {
	*this = *this - that;
	return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::operator*=(const Matrix<T> &that) {
	*this = *this * that;
	return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::operator*=(const T that) {
	*this = *this * that;
	return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::operator/=(const T that) {
	*this = *this / that;
	return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::transpose() {
	*this = this->getTransposed();
	return *this;
}

template <typename T>
Matrix<T> Matrix<T>::getTransposed() const {
	Matrix<T> result(this->colsCnt, this->rowsCnt);
	for (int row = 0; row < this->rowsCnt; row++) {
		for (int col = 0; col < this->colsCnt; col++) {
			result.values[col][row] = this->values[row][col];
		}
	}
	return result;
}

template <typename T>
int Matrix<T>::getRowsNumber() const {
	return this->rowsCnt;
}

template <typename T>
int Matrix<T>::getColumnsNumber() const {
	return this->colsCnt;
}

template <typename T>
T Matrix<T>::operator()(const int row, const int column) const {
	if (row >= this->rowsCnt || column >= this->colsCnt) {
		throw MatrixIndexError();
	}
	return this->values[row][column];
}

template <typename T>
T &Matrix<T>::operator()(const int row, const int column) {
	if (row >= this->rowsCnt || column >= this->colsCnt) {
		throw MatrixIndexError();
	}
	return this->values[row][column];
}

template <typename C>
std::istream &operator >> (std::istream &is, Matrix<C> &that) {
	for (int row = 0; row < that.rowsCnt; row++) {
		for (int col = 0; col < that.colsCnt; col++) {
			is >> that.values[row][col];
		}
	}
	return is;
}

template <typename C>
std::ostream &operator<<(std::ostream &os, const Matrix<C> &that) {
	for (int row = 0; row < that.rowsCnt; row++) {
		for (int col = 0; col < that.colsCnt; col++) {
			os << that.values[row][col] << ' ';
		}
		os << std::endl;
	}
	return os;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &a) const {
	if (this->rowsCnt != a.rowsCnt || this->colsCnt != a.colsCnt) {
		throw MatrixWrongSizeError();
	}
	Matrix<T> result(a.rowsCnt, a.colsCnt);
	for (int row = 0; row < a.rowsCnt; ++row) {
		for (int col = 0; col < a.colsCnt; ++col) {
			result.values[row][col] = a.values[row][col] + this->values[row][col];
		}
	}
	return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &a) const {
	if (this->rowsCnt != a.rowsCnt || this->colsCnt != a.colsCnt) {
		throw MatrixWrongSizeError();
	}
	Matrix<T> result(a.rowsCnt, a.colsCnt);
	for (int row = 0; row < a.rowsCnt; ++row) {
		for (int col = 0; col < a.colsCnt; ++col) {
			result.values[row][col] = this->values[row][col] - a.values[row][col];
		}
	}
	return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &b) const {
	if (this->colsCnt != b.rowsCnt) {
		throw MatrixWrongSizeError();
	}
	Matrix<T> result(this->rowsCnt, b.colsCnt);
	for (int row = 0; row < this->rowsCnt; ++row) {
		for (int col = 0; col < b.colsCnt; ++col) {
			result.values[row][col] = 0;
			for (int i = 0; i < this->colsCnt; i++) {
				result.values[row][col] += this->values[row][i] * b.values[i][col];
			}
		}
	}
	return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const T &b) const {
	Matrix<T> result(this->rowsCnt, this->colsCnt);
	for (int row = 0; row < this->rowsCnt; ++row) {
		for (int col = 0; col < this->colsCnt; ++col) {
			result.values[row][col] = this->values[row][col] * b;
		}
	}
	return result;
}

template <typename C>
Matrix<C> operator*(const C a, const Matrix<C> &b) {
	return b * a;
}


template <typename T>
Matrix<T> Matrix<T>::operator/(const T b) const {
	Matrix<T> result(this->rowsCnt, this->colsCnt);
	for (int row = 0; row < this->rowsCnt; ++row) {
		for (int col = 0; col < this->colsCnt; ++col) {
			result.values[row][col] = this->values[row][col] / b;
		}
	}
	return result;
}


//-----------------------------------

template <typename T>
void SquareMatrix<T>::assign(const Matrix<T> &that) {
	this->Matrix<T>::assign(that);
}

template <typename T>
SquareMatrix<T>::SquareMatrix(const int size) {
	this->set_size(size, size);
}

template <typename T>
SquareMatrix<T>::SquareMatrix(const Matrix<T> &that) {
	this->assign(that);
}

template <typename T>
SquareMatrix<T> SquareMatrix<T>::operator=(const SquareMatrix<T> &that) {
	if (this != &that) {
		this->free_values();
		this->assign(that);
	}
	return *this;
}

template <typename T>
SquareMatrix<T> &SquareMatrix<T>::operator+=(const SquareMatrix<T> &that) {
	*this = *this + that;
	return *this;
}

template <typename T>
SquareMatrix<T> &SquareMatrix<T>::operator-=(const SquareMatrix<T> &that) {
	*this = *this - that;
	return *this;
}

template <typename T>
SquareMatrix<T> &SquareMatrix<T>::operator*=(const SquareMatrix<T> &that) {
	*this = *this * that;
	return *this;
}

template <typename T>
SquareMatrix<T> &SquareMatrix<T>::operator*=(const T coefficient) {
	*this = *this * coefficient;
	return *this;
}

template <typename T>
SquareMatrix<T> &SquareMatrix<T>::operator/=(const T coefficient) {
	*this = *this / coefficient;
	return *this;
}

template <typename T>
SquareMatrix<T> SquareMatrix<T>::getTransposed() const {
	return Matrix<T>::getTransposed();
}

template<typename T>
SquareMatrix<T> &SquareMatrix<T>::transpose() {
	*this = this->getTransposed();
	return *this;
}

template <typename T>
SquareMatrix<T> SquareMatrix<T>::operator+(const SquareMatrix<T> &that) const {
	return Matrix<T>::operator+(that);
}

template <typename T>
SquareMatrix<T> SquareMatrix<T>::operator-(const SquareMatrix<T> &that) const {
	return Matrix<T>::operator-(that);
}

template <typename T>
SquareMatrix<T> SquareMatrix<T>::operator*(const SquareMatrix<T> &that) const {
	return Matrix<T>::operator*(that);
}

template <typename T>
SquareMatrix<T> SquareMatrix<T>::operator*(const T &coefficient) const {
	return Matrix<T>::operator*(coefficient);
}

template <typename C>
SquareMatrix<C> operator*(const C &coefficient, const SquareMatrix<C> matrix) {
	return matrix * coefficient;
}

template <typename T>
SquareMatrix<T> SquareMatrix<T>::operator/(const T &coefficient) const {
	return Matrix<T>::operator/(coefficient);
}

template <typename T>
T SquareMatrix<T>::getDeterminant() const {
	SquareMatrix<T> temp = *this;
	bool flag = true;
	T det = T(1);
	for (int col = 0; col < temp.getColumnsNumber() && flag; col++) {
		int j = col;
		while (j < temp.getRowsNumber() && temp.operator()(j, col) == T(0)) {
			j++;
		}
		if (j == temp.getRowsNumber()) {
			flag = false;
		}
		else {
			if (j != col) {
				temp.swap_rows(col, j);
			}
			for (int k = col + 1; k < temp.getRowsNumber(); k++) {
				T coefficient = temp.operator()(k, col) / temp.operator()(col, col);
				temp.add_row(k, col, -coefficient);
			}
		}
		det *= temp.operator()(col, col);
	}
	if (!flag) {
		det = T(0);
	}
	return det;
}

template <typename T>
SquareMatrix<T> SquareMatrix<T>::my_minor(const int without_row, const int without_col) const {
	SquareMatrix<T> result(this->getSize() - 1);
	for (int row = 0; row < this->getRowsNumber(); row++) {
		for (int col = 0; col < this->getColumnsNumber(); col++) {
			if (row != without_row && col != without_col) {
				int i = row;
				int j = col;
				if (row > without_row) {
					i = row - 1;
				}
				if (col > without_col) {
					j = col - 1;
				}
				result.operator()(i, j) = this->operator()(row, col);
			}
		}
	}
	return result;
}

template <typename T>
SquareMatrix<T> SquareMatrix<T>::getInverse() const {
	if (this->getDeterminant() == T(0)) {
		throw MatrixIsDegenerateError();
	}
	SquareMatrix<T> result(this->getSize());
	T this_det = this->getDeterminant();
	for (int row = 0; row < this->getRowsNumber(); row++) {
		for (int col = 0; col < this->getColumnsNumber(); col++) {
			result.operator()(row, col) = this->my_minor(row, col).getDeterminant() / this_det;
			if ((row + col) % 2 == 1) {
				result.operator()(row, col) *= -1;
			}
		}
	}
	result.transpose();
	return result;
}


template <typename T>
SquareMatrix<T> &SquareMatrix<T>::invert() {
	*this = this->getInverse();
	return *this;
}

template <typename T>
int SquareMatrix<T>::getSize() const {
	return this->getRowsNumber();
}

template <typename T>
T SquareMatrix<T>::getTrace() const {
	T sum = T(0);
	for (int row = 0; row < this->getRowsNumber(); row++) {
		sum += this->operator()(row, row);
	}
	return sum;
}

//-----------------------------------------------------------

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

ostream &operator<<(ostream &os, const Rational &value) {
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
	if (b.p == 0) {
		throw RationalDivisionByZero();
	}
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
	this->p += this->q;
	return *this;
}

Rational Rational::operator++(int) {
	Rational old(*this);
	++*this;
	return old;
}

Rational &Rational::operator--() {
	this->p -= this->q;
	return *this;
}

Rational Rational::operator--(int) {
	Rational old(*this);
	--*this;
	return old;
}

//---------------------------------------------------------

int main() {
	int m, n, p, q;
	cin >> m >> n >> p >> q;

	Matrix<int> A(m, n), B(p, q);
	cin >> A >> B;

	A = A;
	try {
		cout << A + B * 2 - m * A << endl;
		cout << (A -= B += A *= 2) << endl;
		cout << (((A -= B) += A) *= 2) << endl;
	}
	catch (const MatrixWrongSizeError&) {
		cout << "A and B are of different size." << endl;
	}
	B = A;
	cout << B << endl;

	Rational r;
	cin >> r;
	Matrix<Rational> C(m, n), D(p, q);
	cin >> C >> D;
	try {
		cout << C * D << endl;
		cout << (C *= D) << endl;
		cout << C << endl;
	}
	catch (const MatrixWrongSizeError&) {
		cout << "C and D have not appropriate sizes for multiplication." << endl;
	}
	cout << C.getTransposed() * (r * C) << endl;
	cout << C.transpose() << endl;
	cout << C << endl;

	SquareMatrix<Rational> S(m);
	cin >> S;

	SquareMatrix<Rational> P(S);
	const SquareMatrix<Rational>& rS = S;
	cout << rS.getSize() << ' ' << rS.getDeterminant() << ' ' << rS.getTrace() << endl;
	cout << (S = S) * (S + rS) << endl;
	cout << (S *= S) << endl;
	C.transpose();
	cout << rS * C << endl;
	cout << S << endl;
	S = P;
	cout << (Rational(1, 2) * S).getDeterminant() << endl;
	try {
		cout << rS(0, 0) << endl;
		(S(0, 0) *= 2) /= 2;
		cout << rS(0, m) << endl;
	}
	catch (const MatrixIndexError&) {
		cout << "Index out of range." << endl;
	}
	cout << rS.getTransposed() << endl;
	try {
		cout << rS.getInverse() << endl;
		cout << S.invert().getTransposed().getDeterminant() << endl;
		cout << S << endl;
	}
	catch (const MatrixIsDegenerateError&) {
		cout << "Cannot inverse S." << endl;
	}
	return 0;
}