#pragma once
#include<string>
#include<iostream>
#include<vector>

#include<memory>
using namespace std;

class Person {
	string name;
	int age;
public:
	const string& get_name()const { return name; }
	void set_name(const string& _name) { this->name = _name; }
	int get_age()const { return age; }
	void set_age(int _age) { this->age = age; }

	//usual constuctor
	Person(const string& _name, int _age) :name{ _name }, age{ _age } { cout << "Person con" << endl; }

	//default constuctor
	//Person() :age{ 0 } { cout << "Person def constuctor" << endl; }

	//copy constructor
	Person(const Person& p) :name{ p.name }, age{ p.age } { cout << "Person CC" << endl; }

	//assign operation
	Person& operator=(const Person& p)
	{
		if (&p != this)
		{
			this->name = p.name;
			this->age = p.age;
		}
		cout << "Person AO" << endl;
		return *this;
	}

	//move constructor
	Person(Person&& p)
		:name{ move(p.name) }, age{ p.age }
	{
		p.name.clear();
		p.age = 0;
		cout << "Person MC" << endl;
	}

	//move assign operation
	Person& operator=(Person&& p)
	{
		if (this != &p)
		{
			name = move(name);
			age = move(age);
		}
		cout << "Person MAO" << endl;
		return *this;
	}

	//destructor
	//Parents POLYMORPHIC FUNCTION must be VIRTUAL, otherwise children POLYMORPHIC FUNCTIONS will not be called in polimorphism cases
	virtual ~Person(){ cout << "Person rem" << endl; }

	//polimorthic function
	//Parents DESTRUCTOR must be VIRTUAL, otherwise children DESTRUCTORS will not be called in polimorphism cases
	virtual void print()const
	{
		cout << "Person { name " << this->name << " } " << endl;
	}

	//pure virtual function
	//If class contains even one such function, class become abstract
	virtual void study() {};

	//polimorthic function for deep copy
	//this function is pure virtual becouse the class is abstract
	virtual Person* clone() = 0;

	void do_nothing() { cout << "Person is doing nothing" << endl; }
};

//ECPLICIT OVERRIDING: OVERRIDE key work after the functions force us to write VIRTUAL function in parents (check the names of the functions)
//only VIRTUAL functions can be pure( '=0' = abstract )

class Student : public Person {
	int* grades;
	int count_grades;
public:
	int& operator[](int i) { return grades[i]; }

	//usual constuctor
	//--Person constructor might not require if default Person consructor exists
	Student(const string& _name, int _age, int _count_grades)
		:Person{ _name, _age }, count_grades{ _count_grades }, grades {new int[_count_grades]}
	{ 
		cout << "Student con" << endl;
	}

	//default constuctor
	//--Person constructor might not require if default Person consructor exists
	//Student():count_grades{ 0 }, grades{ nullptr } { cout << "Student def contructor" << endl; }

	//copy constructor
	//--Person constructor might not require if default Person consructor exists
	Student(const Student& s)
		:Person(s), count_grades{ s.count_grades }, grades{ new int[s.count_grades] }
	{
		memcpy(grades, s.grades, sizeof(int)*s.count_grades);
		cout << "Student CC" << endl;
	}

	//assign operation
	Student& operator=(const Student& s)
	{
		if (this != &s)
		{
			Person::operator=(s);
			delete[] grades;
			grades = new int[s.count_grades];
			count_grades = s.count_grades;
			memcpy(grades, s.grades, sizeof(int)*s.count_grades);
		}
		cout << "Student AO" << endl;
		return *this;
	}

	//move constuctor
	Student(Student&& s)
		:Person(std::move(s)), grades{s.grades}, count_grades{s.count_grades}
	{
		s.grades = nullptr;
		s.count_grades = 0;
		cout << "Student MC" << endl;
	}

	//move assignment operation
	Student& operator=(Student&& s)
	{
		if (this != &s)
		{
			Person::operator=(std::move(s));
			delete[] grades;
			grades = s.grades;
			s.grades = nullptr;
			count_grades = s.count_grades;
			s.count_grades = 0;
		}
		cout << "Student MAO" << endl;
		return *this;
	}

	//destructor
	~Student()override{ delete[] grades; cout << "Student rem" << endl; }

	//polimorthic function
	void print()const override
	{
		cout << "Student {" << this->count_grades << " count of grades}";
		cout << " But I`m also a: ";
		Person::print();
	}

	//polimorthic function
	void study()override
	{
		cout << "Student is learning" << endl;
	}

	//polimorthic function for deep copy
	Student* clone()override
	{
		return new Student(*this);
	}

	void do_nothing()
	{
		cout << "Student is doing nothing" << endl;
	}
};

class Student_advanced : public Person {
	vector<int> grades;
public:
	int& operator[](int i) { return grades[i]; }

	//usual constuctor
	Student_advanced(const string& _name, int _age, int _grades_count) 
		:Person(_name, _age), grades(_grades_count) { cout << "Student_advanced con" << endl; }

	~Student_advanced()override{ cout << "Student_advanced rem" << endl; }

	//copy constructor
	//If MOVE CONSTUCTOR defined, then COPY CONSTRUCTOR must be defined
	Student_advanced(const Student_advanced& s)
		:Person(s), grades{ s.grades }
	{
		cout << "Student_advanced CC" << endl;
	}

	//assign constructor
	//If MOVE ASSIGN OPERATION defined, then ASSIGN OPERATION must be defined
	Student_advanced& operator=(const Student_advanced& s)
	{
		if (this != &s)
		{
			Person::operator=(s);
			grades = s.grades;
		}
		cout << "Student_advanced AO" << endl;
		return *this;
	}

	//move constuctor
	Student_advanced(Student_advanced&& s)
		:Person(std::move(s)), grades{ std::move(s.grades) }
	{
		cout << "Student_advanced MC" << endl;
	}

	//move assignment operation
	Student_advanced& operator=(Student_advanced&& s)
	{
		if (this != &s)
		{
			Person::operator=(move(s));
			grades = move(s.grades);
		}
		cout << "Student_advanced MAO" << endl;
		return *this;
	}

	//polimorthic function
	void print()const override
	{
		cout << "Advanced Student { " << grades.size() << " grades }";
		cout << " But I`m also a: ";
		Person::print();
	}

	//polimorthic function
	void study() override
	{
		cout << "Advanced student is learning hard" << endl;
	}

	//polimorthic function for deep copy
	Student_advanced* clone() override
	{
		return new Student_advanced(*this);
	}
};

void try_student()
{
	Student s("John", 20, 10);
	Student s1("Snow", 21, 5);
	s1 = s;
	s.set_name("Sten");
	s.do_nothing();
	cout << s1.get_name() << endl;
	Student_advanced s2("Snow", 21, 5);
	s2.do_nothing();
}

void try_polymorphic_container_pointers()
{
	vector<Person*> people;
	people.reserve(3);
	//people.push_back(new Person("Sergio", 9));
	people.push_back(new Student("John", 25, 6));
	people.push_back(new Student_advanced("Pite", 22, 14));
	vector<Person*> people_new;
	people_new.reserve(3);
	//deep copy sample
	for (Person* man : people)
		people_new.push_back(man->clone());
	for (Person* man : people)
		delete man;
	for (Person* man : people_new)
		man->print();
	for (Person* man : people_new)
		delete man;
}

//unique_ptr
void try_unique_ptr()
{
	unique_ptr<Person> p0;
	{
		vector<unique_ptr<Person>> people;
		people.push_back(unique_ptr<Student>(new Student("John", 25, 6)));
		people.push_back(unique_ptr<Student_advanced>(new Student_advanced("Pite", 22, 14)));
		/*for (unique_ptr<Person> man : people)
		man->print();*/
		
		//not allowed
		//p = people[0];
	}
	//p->print();
}

//shared_ptr
void try_shared_ptr()
{
	shared_ptr<Person> p0;
	{
		shared_ptr<Person> p(new Student("John", 25, 6));
		p0 = p;
	}
	p0->print();
}

//move constructor try
Student get_stud()
{
	Student s("Ivan", 14, 4);
	return s;
}

Student_advanced get_adv_stud()
{
	Student_advanced s("Ivan", 14, 4);
	return s;
}

void try_move_contructor()
{
	{
		Student s = get_stud();
		s.print();
	}
	{
		Student_advanced s = get_adv_stud();
		s.print();
	}
}

//move assignment try
void try_move_assignment()
{
	{
		Student s("Ivan", 14, 4);
		Student s1("Ivan", 14, 4);
		s = s1;
		s = std::move(s1);
	}
	{
		Student_advanced s("Ivan", 14, 4);
		Student_advanced s1("Ivan", 14, 4);
		s = s1;
		s = move(s1);
	}
}