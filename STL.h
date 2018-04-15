#pragma once

#include<vector>
#include<list>
#include<set>

#include<stack>
#include<queue>
#include<deque>

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