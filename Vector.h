#pragma once
#include<iostream>
#include<stdexcept>

template<typename T>
T square(T);

template<typename T>
class Vector {
public:
	Vector(int s);
	//Vector(std::initializer_list<T>);

	Vector(const Vector&);
	Vector& operator=(const Vector&);
	~Vector();

	T& operator[](int i);
	int size();
private:
	T* elem;
	int sz;
};

void exc_try();