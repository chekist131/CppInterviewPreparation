#pragma once

#ifndef __Simple_h
#define __Simple_h

#include<iostream>
#include<string>
#include<vector>
#include<chrono>
#include<numeric>
#include<random>
#include<set>
using namespace std;

int i;

namespace simple
{
	namespace unsimple
	{
		int s;
	}

	typedef unsigned char byte;
	typedef int arr[3];
	typedef int matrix[2][3];

	void simple_try()
	{
		byte b = 255;
		arr a{ 1,2,3 };
		matrix m{ { 1,2,3 },{ 2,3,4 } };
	}
}

namespace func_pointers
{
	int mult2(int i)
	{
		return i * 2;
	}

	typedef int(*PFUN)(int);

	void print_func_res(int(*)(int), int);

	void print_func_res(int(*pf)(int), int a)
	{
		std::cout << pf(a) << std::endl;
	}

	void func_try()
	{
		int(*pf)(int) = &mult2;
		PFUN pf1 = pf;
		print_func_res(&mult2, 3);
	}
}

void swap_pointer(int* a, int* b)
{
	int v = *a;
	*a = *b;
	*b = v;
}

void swap_pointer1(int*& a, int*& b)
{
	int* v = a;
	a = b;
	b = v;
}

void swap_ref(int& a, int&b)
{
	int v = a;
	a = b;
	b = v;
}


template<typename T>
inline T maxx(T a, T b)
{
	return a > b ? a : b;
}
inline const char* max(const char* a, const char* b)
{
	return strcmp(a, b) < 0 ? a : b;
}
void templates_try()
{
	cout << maxx<double>(2, 3) << endl;
	cout << maxx<double>(2, 3.4) << endl;
	cout << maxx("Hallo", "Hello") << endl;
}

namespace function_as_argument
{
	template<typename T>
	void swap(T& a, T& b)
	{
		T t{ a };
		a = b;
		b = t;
	}

	template<typename T, typename C>
	void ssort(T* b, int n, C cmp)
	{
		for (int i{ 0 }; i < n; ++i)
			for (int j{ n - 1 }; j > i; --j)
				if (cmp(b[j], b[j - 1]))
					swap(b[j], b[j - 1]);
	}

	struct database
	{
		string name;
		int age;
	};

	void print(database* mas, int n)
	{
		for (int i{ 0 }; i < n; ++i)
			cout << mas[i].name << " " << mas[i].age << endl;
	}

	template<typename T>
	void print(T* mas, int n)
	{
		for (int i{ 0 }; i < n; ++i)
			cout << mas[i] << " ";
		cout << endl;
	}

	int less(const string& i, const string& j) { return i < j; }

	template<typename T>
	int less(const T& i, const T& j) { return i < j; }

	template<typename T>
	int greater(const T& i, const T& j) { return i > j; }

	int lessname(const database& i, const database& j)
	{
		return i.name < j.name;
	}

	int greaterage(const database& i, const database& j)
	{
		return i.age > j.age;
	}

	void to_try()
	{
		const int n = 10, m = 5;
		int mas[n] = { 1,5,2,6,3,7,12,-1,6,-3 };
		/*string strmas[n] = { "adg","dfgj","jk","asg","gjh",
			"sdh","hj","sd","kfj","sdadgh" };*/
		database d[m] = { { "Petrov",32 },
		{ "Ivanov",24 },{ "Kozlov",21 },
		{ "Oslov",20 },{ "Popov",18 } };

		ssort(mas, n, less<int>);
		print(mas, n);
		ssort(mas, n, greater<int>);
		print(mas, n);
		/*ssort(strmas, n, less<char*>);
		print(strmas, n);*/
		ssort(d, m, lessname);
		print(d, m);
		ssort(d, m, greaterage);
		print(d, m);

	}

}

namespace virtual_chain
{
	struct A {
		virtual void print() { cout << "A" << endl; }
	};

	struct B : public A {
		void print() override { cout << "B" << endl; }
	};

	struct C : public B {
		virtual void print() { cout << "C" << endl; }
	};

	struct D : public C {
		void print() { cout << "D" << endl; }
	};

	void try_it()
	{
		A* a0 = new A();
		a0->print();
		A* a1 = new B();
		a1->print();
		A* a2 = new C();
		a2->print();
		A* a3 = new D();
		a3->print();
		B* a4 = new B();
		a4->print();
		B* a5 = new C();
		a5->print();
		B* a6 = new D();
		a6->print();
		C* a7 = new C();
		a7->print();
		C* a8 = new D();
		a8->print();
		D* a9 = new D();
		a9->print();
	}
}

namespace sort
{
	//stable, O(n^2)
	void bubble(vector<int>& v)
	{
		for (int i = 0; i < v.size(); ++i)
			for (int j = i; j < v.size(); ++j)
				if (v[i] > v[j])
					swap(v[i], v[j]);
	}

	//stable, O(n^2)
	void insertion(vector<int>& v)
	{
		for (int i = 0; i < v.size(); ++i)
		{
			int x = v[i];
			int j = i;
			for (; j > 0 && v[j - 1] > x; --j)
			{
				v[j] = v[j - 1];
			}
			v[j] = x;
		}
	}

	//unstable, O(n^2)
	void selection(vector<int>& v)
	{
		for (int i = 0; i < v.size(); ++i)
		{
			int min_id = i;
			for (int j = i + 1; j < v.size(); ++j)
				if (v[j] < v[min_id])
					min_id = j;
			if (min_id != i)
				swap(v[i], v[min_id]);
		}
	}

	void quick_recur(vector<int>& arr, int left, int right) {
		int i = left;
		int	j = right;
		int pivot = arr[(left + right) / 2];
		/* partition */
		while (i <= j) {
			for (; arr[i] < pivot; ++i);
			for (; arr[j] > pivot; --j);
			if (i <= j) {
				swap(arr[i], arr[j]);
				++i;
				--j;
			}
		};

		/* recursion */
		if (left < j)
			quick_recur(arr, left, j);
		if (i < right)
			quick_recur(arr, i, right);
	}

	//Hoare sort
	//best time = O(n*log(n))
	//worst time = n^2
	//unstable
	void quick(vector<int>& v)
	{
		quick_recur(v, 0, v.size()-1);
	}

	//stable, n^2
	void gnome(vector<int>& v)
	{
		for (int i{ 0 }; i < v.size();)
		{
			if (i == 0 || v[i - 1] <= v[i])
				++i;
			else
			{
				swap(v[i], v[i - 1]);
				--i;
			}
		}
	}

	void for_time(string alg_name, void(*alg)(vector<int>&), vector<int> v, int times, bool print_sorted = false)
	{
		vector<unsigned int> res(times);
		for (int i{ 0 }; i < times; ++i)
		{
			auto start_time = chrono::high_resolution_clock::now();
			alg(v);
			auto end_time = chrono::high_resolution_clock::now();
			res.push_back(chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count());
		}
		int r = std::accumulate(res.begin(), res.end(), 0) / res.size();
		cout << alg_name << ": " << r << "ms" << endl;
		if (print_sorted)
		{
			for (int x : v)
				cout << x << " ";
			cout << endl;
		}
	}

	//2000 int`s in [1..100000]
	//quick(3ms) < insertions(38ms) < gnome(97ms) < selection(677ms) < bubble(709ms)
	void lets_try(bool print_unsorted = false, int times = 10)
	{
		std::random_device rd;  //Will be used to obtain a seed for the random number engine
		std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
		std::uniform_int_distribution<> dis(1, 100000);

		size_t v_size = 2000;
		vector<int> v;
		v.reserve(v_size);
		for (int n = 0; n < v_size; ++n)
		{
			//Use dis to transform the random unsigned int generated by gen into an int in [.., ..]
			int x = dis(gen);
			if (print_unsorted)
				cout << x << " ";
			v.push_back(x);
		}
		if (print_unsorted)
			cout << endl;
		for_time("Bubble", bubble, v, times);
		for_time("Insertion", insertion, v, times);
		for_time("Selection", selection, v, times);
		for_time("Quick", quick, v, times);
		for_time("Gnome", gnome, v, times);
	}
}

namespace combinatorics
{
	
	namespace variations
	{
		void variations(const set<int>& s, vector<int> v, int k, vector<vector<int>>& res, bool is_repeats)
		{
			for (set<int>::iterator it = s.begin(); it != s.end(); ++it)
			{
				if (find(v.begin(), v.end(), *it) == v.end() || is_repeats)
				{
					v.push_back(*it);
					if (k == 1)
						res.push_back(v);
					else if (k > 1)
						variations(s, v, k - 1, res, is_repeats);
					v.pop_back();
				}
			}
		}

		int variations_count(unsigned n, unsigned k, bool is_repeats)
		{
			if (k > n)
				throw std::length_error("k must be less then n");
			if (is_repeats)
				return pow(n, k);//n^k
			else
			{
				int prod = 1;
				for (unsigned nn{ n }; nn > (n - k); --nn)
					//n * (n-1) * ... (n-k+1)
					prod *= nn;
				return prod;//n!/(n-k)!
			}
		}

		vector<vector<int>> variations_init(const set<int>& _set, int k, bool repeats)
		{
			if (k > _set.size())
				throw std::length_error("k must be less then n");
			vector<vector<int>> res;
			vector<int> temp;
			temp.reserve(2);
			variations(_set, temp, k, res, repeats);
			return res;
		}

		void lets_try(const set<int>& _set, int k, bool is_repeats, bool is_print = false)
		{
			vector<vector<int>> res = variations_init(_set, k, is_repeats);
			cout << "result size = " << res.size() << endl;
			cout << "formula = " << variations_count(_set.size(), k, is_repeats) << endl;
			if (is_print)
			{
				for (vector<int>& v : res)
				{
					for (int x : v)
						cout << x << " ";
					cout << endl;
				}
			}
		}
	}

	namespace permutations
	{
		void permutations_recur(const vector<int>::iterator begin, const vector<int>::iterator end, vector<vector<int>>& res, vector<int>& temp)
		{
			if (begin == end)
			{
				res.push_back(temp);
				return;
			}
			else
				for (vector<int>::iterator it = begin; it != end; ++it)
				{
					swap(*it, *begin);
					temp.push_back(*begin);
					permutations_recur(begin + 1, end, res, temp);
					temp.pop_back();
					swap(*it, *begin);
				}
		}

		vector<vector<int>> permutations_init(vector<int>::iterator begin, vector<int>::iterator end)
		{
			vector<vector<int>> res;
			vector<int> t;
			permutations_recur(begin, end, res, t);
			return res;
		}

		int permutations_formula(unsigned n)
		{
			unsigned prod = 1;
			for (int i{ 1 }; i <= n; ++i)
				prod *= i;
			return prod;//n!
		}

		void lets_try(vector<int> _vector, bool is_print)
		{
			vector<vector<int>> res = permutations_init(_vector.begin(), _vector.end());
			cout << "result size = " << res.size() << endl;
			cout << "Formula =  " << permutations_formula(_vector.size()) << endl;
			if (is_print)
			{
				for (vector<int>& v : res)
				{
					for (int x : v)
						cout << x << " ";
					cout << endl;
				}
			}
		}
	}

	namespace combinations
	{
		void combinations_rec(const vector<int>::iterator begin, const vector<int>::iterator end, int k, vector<int>& temp, vector<vector<int>>& res, bool repeats)
		{
			if (k == 0)
				res.push_back(temp);
			else
				for (vector<int>::iterator it = begin; it != end; ++it)
				{
					temp.push_back(*it);
					combinations_rec(repeats ? it : it + 1, end, k - 1, temp, res, repeats);
					temp.pop_back();
				}
		}

		vector<vector<int>> combinations_init(vector<int>& v, int k, bool repeats)
		{
			vector<vector<int>> res;
			vector<int> temp;
			temp.reserve(k);
			combinations_rec(v.begin(), v.end(), k, temp, res, repeats);
			return res;
		}

		int combinations_formula(int n, int k, bool repeats)
		{
			if (repeats)
			{
				int prod = 1;
				for (int i{ k + 1 }; i <= n + k - 1; ++i)
					prod *= i;
				for (int i{ 1 }; i <= n - 1; ++i)
					prod /= i;
				return prod;//(n+k-1)!/(k!*(n-1)!)
			}
			else
			{
				int prod = 1;
				for (int i{ n }; i > k; --i)
					prod *= i;
				for (int i{ 1 }; i <= n - k; ++i)
					prod /= i;
				return prod;//n!/(k!*(n-k)!)
			}
		}

		void lets_try(vector<int> v, int k, bool repeats, bool is_print)
		{
			vector<vector<int>> res = combinations_init(v, k, repeats);
			cout << "result size = " << res.size() << endl;
			cout << "Formula =  " << combinations_formula(v.size(), k, repeats) << endl;
			if (is_print)
			{
				for (vector<int>& v : res)
				{
					for (int x : v)
						cout << x << " ";
					cout << endl;
				}
			}
		}
	}

	void lets_try()
	{
		set<int> s{ 1,2,3,4,5};
		variations::lets_try(s, 3, false, false);//A(n, k)
		vector<int> v(s.begin(), s.end());
		permutations::lets_try(v, false);//P(n)
		//P(n)=A(n,n)
		combinations::lets_try(v, 2, true, true);
		//A(n, k) = C(n, k) * P(k)
	}
}

#endif // !__Simple_h