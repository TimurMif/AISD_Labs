#include <iostream>
#include "class.h"
#include <complex>
#include <typeinfo>

using namespace std;

template <typename T>
Polyline<T> create_trapezoid(T a, T b, T h) noexcept {
	if (a < 0 || b < 0 || h < 0) {
		throw std::range_error("Out of range");
	}
	Polyline<T> trapezoid(4);
	//Left up angle
	trapezoid.insert(0, 0, 0);
	//Right up angle
	trapezoid.insert(trapezoid[0]._x + a, trapezoid[0]._y, 1);
	//Right bottom angle
	trapezoid.insert(trapezoid[1]._x + (b - a), trapezoid[1]._y - h, 2);
	//Left bottom angle
	trapezoid.insert(trapezoid[0]._x, trapezoid[0]._y - h, 3);
	return trapezoid;
}



int main() {
	Polyline<double> new_poly(2, 4);

	new_poly.append(5.2, 6.7);
	new_poly.append(5.3, 12.7);
	new_poly.append(31.3, 12.7);
	cout << "First polyline" << endl;
	cout << new_poly;
	cout << "Len: " << new_poly.len() << endl;

	cout << "Access by index to element: " << new_poly[1]._x << endl;
	new_poly[1]._x = 10.2;
	cout << "Repeat cout first Polyline" << endl;
	cout << new_poly;

	double doubl( 3.0 );
	double doubl1( 2.4 );

	//Complex_numbers
	std::complex<float> comp(2.4, 4.2);
	std::complex<float> comp1(3.2,6.5);

	std::complex<float> comp2(6.4, 6.2);
	std::complex<float> comp3(9.1, 11.4);


	cout << "\ncomplex::float Polyline";
	Polyline<std::complex<float>> poly_complex_float(comp, comp1, 5);
	cout << poly_complex_float;
	cout << "Len: " << len(poly_complex_float) << endl;

	cout << "\ncomplex::double Polyline";
	Polyline<std::complex<double>> poly_complex_double(comp2, comp3, 5);
	cout << poly_complex_double;
	cout << "Len: " << len(poly_complex_double) << endl;

	cout << "\ndouble Polyline";
	Polyline<double> poly_double(3.2, 5.4, 2);
	cout << poly_double;
	cout << "Len: " << poly_double.len() << endl;

	cout << "\nint Polyline";
	Polyline<int> poly_int(5, 8, 3);
	cout << poly_int;
	cout << "Len: " << poly_int.len() << endl;

	cout << "\nfloat Polyline";
	Polyline<float> poly_float(3.5, 6.8, 4);
	cout << poly_float;
	cout << "Len: " << poly_float.len() << endl;
	cout << "||End_iniyialize||" << endl;

	cout << "||Poly_trapez||" << endl;
	Polyline<double> poly_trapez(5);
	poly_trapez = create_trapezoid(3.8, 5.7, 2.4);
	cout << poly_trapez << endl;

	cout << "True or false: " << (poly_complex_float == poly_complex_float) << endl;
	cout << "True or false: " << (poly_trapez == poly_double) << endl;

	cout << "|Result operator +=|" << endl;
	poly_int += poly_int;
	std::cout << poly_int << endl;

	cout << "|Result operator +|" << endl;
    Polyline<int> poly_result_int(6);
	poly_result_int = (poly_int + poly_int);
	std::cout << poly_result_int;

	
	Polyline<int> new_poly_int(11, 16, 4);
	cout << new_poly_int;
	cout << "Len: " << new_poly_int.len() << endl;

	cout << "|Result operator: Polyline + Point|" << endl;
	poly_int + new_poly_int[2];
	std::cout << poly_int;

	cout << "|Result operator: Point + Polyline|" << endl;
	Point<int> new_point{ 2, 5 };
	new_point + poly_int;
	cout << poly_int;

	cout << "|Result operator: complex Point + Polyline|" << endl;
	Point<std::complex<float>> new_point_complex{ comp2, comp3 };
	new_point_complex + poly_complex_float;
	cout << poly_complex_float;


	return 0;
}