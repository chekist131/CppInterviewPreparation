#pragma once
#include<iostream>

class complex {
	double re, im;
public:
	complex(double r, double i) :re{ r }, im{ i } {}
	complex(double r) : re{ r }, im{ 0 } {}
	complex() : re{ 0 }, im{ 0 } {}

	double real() const { return re; }
	void real(double d) { re = d; }
	double imag() const { return im; }
	void imag(double d) { im = d; }

	complex& operator+=(complex z) { re += z.re, im += z.im; return *this; }
	complex& operator-=(complex);

	//complex& operator*=(complex);
	//complex& operator/=(complex);
};

complex& complex::operator-=(complex z)
{
	re -= z.re, im -= z.im; return *this;
}

std::ostream& operator<<(std::ostream& os, complex c) 
{
	return os << "{re=" << c.real() << ", im=" << c.imag() << "}";
}

std::istream& operator>>(std::istream& is, complex& c)
{
	double re, im;
	is >> re >> im;
	c.real(re);
	c.imag(im);
	return is;
}

complex operator+(complex a, complex b) { return a += b; }
complex operator-(complex a, complex b) { return a -= b; }
complex operator-(complex a) { return { -a.real(), -a.imag() }; }
//complex operator*(complex a, complex b) { return a *= b; }
//complex operator/(complex a, complex b) { return a /= b; }

bool operator==(complex a, complex b)
{
	return a.real() == b.real() && a.imag() == b.imag();
}

bool operator!=(complex a, complex b)
{
	return !(a == b);
}



void complex_try()
{
	complex a{ 2.3 };
	complex b{ 1 - a };
	complex c{ a + b - complex{ 1,2.3 } };

	std::cout << c.real() << " " << c.imag() << std::endl;
}

namespace recursion
{
	int n_fact(int n)
	{
		if (n == 0)
			return 1;
		else
			return n * n_fact(n - 1);
	}
}