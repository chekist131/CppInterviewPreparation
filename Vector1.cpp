#include"Vector.h"

template<typename T>
T square(T d)
{
	return d * d;
}

template<typename T>
Vector<T>::Vector(int s)
{
	if (s < 0)
		throw std::length_error{"Vector::Vector(int)"};
	elem = new T[s];
	sz = s;
}

/*template<typename T>
Vector<T>::Vector(std::initializer_list<T> lst)
	:elem{new T[lst.size()]}, sz{static_cast<int>(lst.size())}
{
	std::copy(lst.begin(), lst.end(), elem);
}*/

template<typename T>
Vector<T>::Vector(const Vector& v) 
	: elem{ new T[v.sz] }, sz{ v.sz }
{
	std::copy(v.elem, v.elem + v.sz, elem);
	std::cout << "CC" << std::endl;
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& v)
{
	std::cout << "AO" << std::endl;
	if (this != &v)
	{
		delete[] elem;
		sz = v.sz;
		elem = new T[sz];
		std::copy(v.elem, v.elem + v.sz, elem);
	}
	return *this;
}

template<typename T>
Vector<T>::~Vector()
{
	delete[] elem;
	std::cout << "end" << std::endl;
}

template<typename T>
T& Vector<T>::operator[](int i)
{
	if (i < 0 || i >= size())
		throw std::out_of_range{"Vector::operator[]" };
	return elem[i];
}

template<typename T>
int Vector<T>::size()
{
	return sz;
}

void exc_try()
{
	try {
		Vector<int> v(10);
		v = v;
		v[8] = 777;
		std::cout << v[8] << std::endl;
	}
	catch (std::out_of_range) {
		std::cout << "bounds" << std::endl;
	}
	catch (std::length_error) {
		std::cout << "len" << std::endl;
	}
	catch (...) {
		std::cout << "other err" << std::endl;
	}
	//static_assert(1 == 1, "111");

	//Vector v{ 1,2,3 };
	//cout << v[1] << endl;
}