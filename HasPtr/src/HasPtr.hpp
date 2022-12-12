#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

using std::vector; using std::string;
using std::cin; using std::cout; using std::endl;

#define LOG(x) cout << x << endl

class HasPtr {
	friend void swap(HasPtr&, HasPtr&);
	friend bool operator<(const HasPtr& lhs, const HasPtr& rhs);
public:
	HasPtr(const string& s = string("default")) :
		ps(new string(s)), i(0), use(new std::size_t(1)) {LOG(*ps + " user++");}
	HasPtr(const HasPtr& hp) :
		ps(hp.ps), i(0), use(hp.use) 
	{
		LOG(*ps + " user++");
		++* use;
	}

	HasPtr& operator=(const HasPtr&);
	//HasPtr& operator=(HasPtr);	// swap版本的赋值运算符

	~HasPtr()
	{
		/*LOG(*ps + " user--");*/
		if (--*use == 0)
		{
			/*LOG(*ps + " destruction");*/
			delete ps;
			delete use;
		}
	}

private:
	string* ps;
	int i;
	std::size_t* use;
};

HasPtr&
HasPtr::operator=(const HasPtr& hp)
{
	++* hp.use;
	//LOG(*hp.ps + " user++");
	//LOG(*ps + " user--");
	if (--*use == 0)
	{
		//LOG(*ps + " destruction");
		delete ps;
		delete use;
	}
	ps = hp.ps;
	i = hp.i;
	use = hp.use;
	return *this;
}

//HasPtr& 
//HasPtr::operator=(HasPtr rhs)	// swap版本的赋值运算符
//{
//	swap(*this, rhs);
//	return *this;
//}

inline 
void swap(HasPtr& lhs, HasPtr& rhs)
{
	using std::swap;
	LOG(*lhs.ps + " swapped " + *rhs.ps);
	swap(lhs.ps, rhs.ps);
	swap(lhs.i, rhs.i);
}

inline
bool operator<(const HasPtr& lhs, const HasPtr& rhs)
{
	return *lhs.ps < *rhs.ps;
}