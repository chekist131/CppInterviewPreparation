#pragma once

#include<vector>
#include<list>
#include<forward_list>

#include<set>

#include<stack>
#include<queue>
#include<deque>

#include<map>

#include<functional>

#include<iterator>

void try_iterator()
{
	const int n = 5;
	int a[] = { 1, 5, 2, 4, 1 };
	vector<int> v(a, a + n);
	list<double> l(a, a + n);
	set<int> s(a, a + n);
	for (int* it{ a }; it != a + n; ++it)
		cout << *it << " ";
	cout << endl;
	for (vector<int>::iterator it = v.begin(); it != v.end(); ++it)
		cout << *it << " ";
	cout << endl;
	for (list<double>::iterator it = l.begin(); it != l.end(); ++it)
		cout << *it << " ";
	cout << endl;
	for (set<int>::iterator it = s.begin(); it != s.end(); ++it)
		cout << *it << " ";
	cout << endl;
}

void try_iterator1()
{
	const int n = 5;
	int a[] = { 1, 5, 2, 4, 1 };
	vector<int> v(a, a + n);
	for (vector<int>::reverse_iterator it = v.rbegin(); it != v.rend(); ++it)
		cout << *it << " ";
	cout << endl;
}

void try_stack()
{
	//deque<T> is a default implementation for stack
	stack<int> stack_d;
	//stack<int, vector<int>> stack_v;
	//stack<int, list<int>> stack_l;
	stack_d.push(3);
	stack_d.push(4);
	cout << stack_d.top() << endl;
	stack_d.pop();
	cout << stack_d.top() << endl;
}

void try_queue()
{
	//deque<T> is a default implementation for queue
	//queue<int> q;
	queue<int, list<int>> q;
	q.push(3);
	q.push(4);
	cout << q.back() << " " << q.front() << endl;
	q.pop();
	cout << q.back() << " " << q.front() << endl;
}

//object function (functor)
template<typename T>
class less_then
{
	T t;
public:
	less_then(T _t) :t(_t) {}
	bool operator()(T x)
	{
		return x < t;
	}
};

void try_not_modifying_algoritms()
{
	const int n = 5;
	int a[] = { 1,4,2,3,4 };
	vector<int> v(a, a + n);
	for_each(v.begin(), v.end(), [n](int i) ->void { cout << i * n << " "; });
	cout << endl;
	vector<int>::iterator it = find(v.begin(), v.end(), 2);
	cout << *it << endl;
	it = find_if(v.begin(), v.end(), [](int x) -> bool {return x >= 3; });
	cout << *it << endl;
	it = find_if(v.begin(), v.end(), less_then<int>(3));
	cout << *it << endl;
}

void try_modifying_algoritms()
{
	vector<int> v;
	//istream_iterator
	copy(istream_iterator<int>(cin), istream_iterator<int>(), back_inserter(v));
	//reading until ctrl-z
	{
		vector<int> v1;
		//runtime exception
		//copy(v.begin(), v.end(), v1.begin());
		//push_back iterator
		copy(v.begin(), v.end(), back_inserter(v1));
		//front_inserter(for list)
	}
	//ostream_iterator
	copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
	{
		vector<int> v_reverse;
		v_reverse.resize(v.size());
		copy_backward(v.begin(), v.end(), v_reverse.end());
		copy(v_reverse.begin(), v_reverse.end(), ostream_iterator<int>(cout, " "));//??
		cout << endl;
	}
}

namespace stl_containers
{

	void map_try()
	{
		multimap<int, int> mm;
		mm.insert(pair<int, int>(3, 27));
		mm.insert(pair<int, int>(3, 9));
		mm.insert(pair<int, int>(1, 1));
		mm.insert(pair<int, int>(5, 25));
		mm.insert(pair<int, int>(3, 125));
		for (multimap<int, int>::iterator it = mm.begin(); it != mm.end(); ++it)
		{
			cout << it->first << ": " << it->second << endl;
			it->second = 4;
		}
	}

	void lets_try()
	{
		map_try();
	}

}

namespace iterators_try
{
	//iostreams iterators with copy
	void lets_try_copy()
	{
		vector<int> v;
		copy(istream_iterator<int>(cin), istream_iterator<int>(), back_inserter<vector<int>>(v));
		copy(begin(v), next(prev(end(v))), ostream_iterator<int>(cout, ", "));
		cout << endl;
	}

	//iostreams iterators without copy
	void lets_try_pure()
	{
		vector<int> v;
		istream_iterator<int> it_cin(cin);
		istream_iterator<int> it_eof;
		back_insert_iterator<vector<int>> bii(v);
		while (it_cin != it_eof)
			*bii++ = *it_cin++;
		ostream_iterator<int> osi(cout, ", ");
		for (auto it = v.rbegin(); it != v.rend(); ++it)
			*osi = *it;
		cout << endl;
	}
}

namespace algorithms_try
{
	void non_modifying()
	{
		const vector<int> v{ 1,2,3,4,5,6,7,8,9 };
		cout << all_of(v.begin(), v.end(), [](int x) { return x < 10; }) << endl;
		cout << all_of(v.begin(), v.end(), [](int x) { return x < 9; }) << endl;
		cout << none_of(v.begin(), v.end(), [](int x) { return x > 9; }) << endl;
		cout << none_of(v.begin(), v.end(), [](int x) { return x > 8; }) << endl;
		for_each(v.begin(), v.end(), [](int x) { cout << x << ", "; });
		cout << endl;
		cout << (find(v.begin(), v.end(), 4) != v.end()) << endl;
		cout << (find(v.begin(), v.end(), 10) != v.end()) << endl;
		cout << (find_if(v.begin(), v.end(), [](int x) { return x > 9; }) != v.end()) << endl;
		cout << (find_if(v.begin(), v.end(), [](int x) { return x > 8; }) != v.end()) << endl;
		//...
	}

	void modifying()
	{
		const vector<int> v{ 1,2,3,4,5,6,7,8,9 };
		copy_n(v.begin(), 4, ostream_iterator<int>(cout, ", "));
		cout << endl;
		copy_if(v.begin(), v.end(), ostream_iterator<int>(cout, ", "), [](int x) { return x % 2 == 0; });
		cout << endl;
		//!!
		transform(v.begin(), v.end(), ostream_iterator<int>(cout, ", "), [](int x) { return x * 2; });
		cout << endl;
		replace_copy_if(v.begin(), v.end(), ostream_iterator<int>(cout, ", "), [](int x) { return x % 2 == 0; }, 44);
		cout << endl;
		fill_n(ostream_iterator<int>(cout, ", "), 7, 14);
		cout << endl;
		{
			int i = 1;
			generate_n(ostream_iterator<int>(cout, ", "), 9, [&i]() { i *= 2; return i; });
			cout << endl;
		}
		//remove_copy: copy without value
		//swap parts
		rotate_copy(v.begin(), v.begin() + 5, v.end(), ostream_iterator<int>(cout, ", "));
		cout << endl;
		vector<int> v1(6);
		random_shuffle(v1.begin(), v1.end());
		copy(v1.begin(), v1.end(), ostream_iterator<int>(cout, ", "));
		cout << endl;
	}
}