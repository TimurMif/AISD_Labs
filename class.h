#pragma once
#include <cmath>
#include <random>
#include <iostream>
#include <typeinfo>
#include <random>
#include <complex>
#include <exception>


std::complex<double> randomise(std::complex<double> left_limit, std::complex<double>  right_limit) {
		std::random_device rand;
		std::mt19937 gen(rand());
		std::uniform_real_distribution<>dis(left_limit.real(), right_limit.real());
		std::complex<double> compdoub(dis(rand), dis(rand));
		return compdoub;
	
}

std::complex<float> randomise(std::complex<float> left_limit, std::complex<float>  right_limit) {
		std::random_device rand;
		std::mt19937 gen(rand());
		std::uniform_real_distribution<>dis(left_limit.real(), right_limit.real());
		std::complex<float> compflow(dis(rand), dis(rand));
		return compflow;
}

template <typename T>
T randomise(T left_limit, T right_limit) {

	std::string str2 = "int";
	std::string str3 = "double";
	std::string str4= "float";

	if (typeid(left_limit).name() == str2) {
		std::random_device rand;
		std::mt19937 gen(rand());
		std::uniform_int_distribution<>dis(left_limit, right_limit);
		int num = dis(rand);
		return num;
	}
	else if (typeid(left_limit).name() == str3) {
		std::random_device rand;
		std::mt19937 gen(rand());
		std::uniform_real_distribution<>dis(left_limit, right_limit);
		double num = dis(rand);
		return num;
	}
	else if (typeid(left_limit).name() == str4) {
		std::random_device rand;
		std::mt19937 gen(rand());
		std::uniform_real_distribution<>dis(left_limit, right_limit);
		float num = dis(rand);
		return num;
	}
	else {
	   return -1;
	}
}




template <typename T>


class Polyline {
	
	struct Point {
		T _x;
		T _y;
	};

	Point* Line;

	int _size;
	int _capacity;

public:

	Polyline(T x, T y) {
		Line = new Point[1];
		_size = 1;
		_capacity = 1;
		Line[0]._x = x;
		Line[0]._y = y;
	}

	Polyline(int capacity) {
		Line = new Point[capacity]{0};
		_capacity = capacity;
		_size = 0;
	}

	Polyline() {
		Line = new Point[1]{0};
		_capacity = 1;
		_size = 0;
	}

	Polyline(const Polyline<T>& pol) {
		Line = new Point[pol._capacity];
		_capacity = pol._capacity;
		_size = pol._size;
		memcpy(Line, pol.Line, sizeof(Point)* _capacity);
	}

	Polyline(T m1,T m2, int number) {
		Line = new Point[number];

		_size = number;
		_capacity = number;
		for (int i = 0; i < number; i++) {
		   Line[i]._x = randomise(m1, m2);
		   Line[i]._y = randomise(m1, m2);
		}
	}

	void swap(Polyline<T>& other) noexcept {
		std::swap(Line, other.Line);
		std::swap(_size, other._size);
		std::swap(_capacity, other._capacity);
	}

	Polyline<T>& operator=(Polyline<T>& other) {
		swap(other);
		return *this;
	}


	T get_x_by_index(int index) {
		return Line[index]._x;
	}

	T get_y_by_index(int index) {
		return Line[index]._y;
	}

	double len() {
		double sumlen = 0;
		std::string str = "class std::complex<double>";
		std::string str2 = "class std::complex<float>";
		if (_size <= 1) {
			return -1;
		}else if ( _size > 1) {
		   for (int i = 0; i < _size - 1; i++) {
			   sumlen += sqrt((Line[i]._x - Line[i + 1]._x) * (Line[i]._x - Line[i + 1]._x) + (Line[i]._y - Line[i + 1]._y) * (Line[i]._y - Line[i + 1]._y));
		   }
		   return sumlen;
		}	
	}


	void append(T x, T y) {
		if (_size >= _capacity) {
			Polyline tmp(_capacity * 2);
			for (int i = 0; i < _size; i++) {
				tmp.Line[i] = Line[i];
				tmp._size++;
			}
			tmp.Line[_size]._x = x;
			tmp.Line[_size]._y = y;
			tmp._size++;
			swap(tmp);
		} else {
			Line[_size]._x = x;
			Line[_size]._y = y;
			_size++;
		}
	}

	void append(Point* point) {
		if (_size >= _capacity) {
			Polyline tmp(_capacity * 2);
			for (int i = 0; i < _size; i++) {
				tmp.Line[i] = Line[i];
				tmp._size++;
			}
			tmp.Line[_size]._x = point->_x;
			tmp.Line[_size]._y = point->_y;
			tmp._size++;
			swap(tmp);
		}
		else {
			Line[_size]._x = point->_x;
			Line[_size]._y = point->_y;
			_size++;
		}
	}

	void insert(T x, T y, int index) {
		if (index >= 0) {
			if (_size >= _capacity) {
				Polyline tmp(_capacity * 2);
				for (int i = 0; i < _size; i++) {
					tmp.Line[i] = Line[i];
					tmp._size++;
				}
				tmp.Line[index]._x = x;
				tmp.Line[index]._y = y;
				tmp._size++;
				swap(tmp);
			} else {
				Line[index]._x = x;
				Line[index]._y = y;
				_size++;
			}
		}
	}


	
	Polyline<T> operator+(Polyline<T>& pol2) const {
		Polyline<T> new_poly( this->_capacity + pol2.capacity() );
		int index = 0;

		for (int i = 0; i < this->_capacity; i++) {
			new_poly.insert(this->Line[i]._x, this->Line[i]._y, index);
			index++;
		}
		for (int j = 0; j < this->_capacity; j++) {
			new_poly.insert(pol2.Line[j]._x, pol2.Line[j]._y, index);
			index++;

		}

		return new_poly;
	}

	Polyline<T>& operator+=(Polyline<T>& pol2) {
		Polyline<T> new_poly(this->_capacity + pol2.capacity());
		int index = 0;
		for (int i = 0; i < this->_capacity; i++) {
			new_poly.insert(this->Line[i]._x, this->Line[i]._y, index);
			index++;
		}
		for (int j = 0; j < this->_capacity; j++) {
			new_poly.insert(pol2.Line[j]._x, pol2.Line[j]._y, index);
			index++;

		}

		*this = new_poly;

		return *this;
	}

	Polyline<T>& operator+(Point& point) {
		this->append(point._x, point._y);
		return *this;
	}

	Point get_elem_by_index(int index) {
		if (index >= 0 && index < _size) {
			return Line[index];
		}
		else {
			throw std::range_error("Index incorrect");
		}
	}

	Point operator[](size_t index) const {
		if (index < _size && index >= 0) {
			return Line[index];
		}
		else {
			throw std::range_error("Index incorrect");
		}
	}

	Point& operator[](size_t index) {
		if (index < _size && index >= 0) {
			return Line[index];
		}
		else {
			throw std::range_error("Index incorrect");
		}
	}

	int size() {
		return _size;
	}

	int size() const {
		return _size;
	}

	int capacity() {
		return _capacity;
	}

	int capacity() const {
		return _capacity;
	}

	~Polyline(){
		delete[] Line;
	}
};

template <typename T>

std::ostream& operator <<(std::ostream &os, Polyline<T>& obj) noexcept {
	std::cout << "\n|Polyline|" << std::endl;
	for (size_t i = 0; i < obj.size(); i++) {
		std::cout << i+1 << "# Point (" << obj[i]._x << "," << obj[i]._y << ")" << std::endl;
	}
	return os;
}

template <typename T>

double len(Polyline<T>& object) {
	double sumlen = 0;
	std::string str = "class std::complex<double>";
	std::string str2 = "class std::complex<float>";
	if (object.size() <= 1) {
		return -1;
	}
	else if (object.size() > 1) {
		if (typeid( object[0]._x ).name() == str || typeid( object[0]._x ).name() == str2) {
			for (int i = 0; i < object.size() - 1; i++) {
				sumlen += sqrt((object[i]._x.real() - object[i + 1]._x.real()) * (object[i + 1]._x.real() - object[i + 1]._x.real()) + (object[i]._y.real() - object[i + 1]._y.real()) * (object[i]._y.real() - object[i + 1]._y.real()));
			}
		}
		return sumlen;
	}
}

template <typename T> 
struct Point {
	T _x;
	T _y;

	T get_x() {
		return _x;
	}
	T get_y() {
		return _y;
	}
};

template <typename T>
Polyline<T> operator+(Point<T>& point, Polyline<T>& polyline) noexcept {
	Polyline<T> new_poly(polyline.capacity());
	new_poly.insert(point.get_x(), point.get_y(), 0);
	for (int i = 0; i < polyline.size(); i++) {
		new_poly.insert(polyline[i]._x, polyline[i]._y, i+1);
	}
	polyline = new_poly;
	return new_poly;
}

template <typename T>
bool operator==(Polyline<T>& polyline1, Polyline<T>& polyline2) {
	if (polyline1.size() != polyline2.size()) {
		return false;
	}
	else {
		for (int i = 0; i < polyline1.size(); i++) {
			if (polyline1[i]._x != polyline2[i]._x) {
				return false;
			}
		}
	}
	return true;
}
