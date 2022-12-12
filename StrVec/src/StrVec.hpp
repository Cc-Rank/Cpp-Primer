#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

using std::vector; using std::string;
using std::cin; using std::cout; using std::endl;
using std::allocator;

#define LOG(x) cout << x << endl;

class StrVec
{
public:
	StrVec() :
		elements(nullptr), first_free(nullptr), cap(nullptr) { }
	StrVec(const StrVec&);
	StrVec(std::initializer_list<string>);
	StrVec& operator = (const StrVec&);
	~StrVec();

	void push_back(const string&);

	size_t size() const { return first_free - elements; }
	size_t capacity() const { return cap - elements; }
	std::string* begin() const { return elements; }
	std::string* end() const { return first_free; }

	void reserve(size_t);
	void resize(size_t);
	void resize(size_t, const string&);

private:
	static allocator<std::string> alloc;	// 分配元素

	void chk_n_alloc() { if (size() == capacity()) reallocate(); }
	std::pair<std::string*, std::string*> alloc_n_copy(const std::string*, const std::string*);
	void free();
	void reallocate();

	std::string* elements;
	std::string* first_free;
	std::string* cap;
};

// 类中的static成员只是声明，还需要在类外进行定义；
allocator<std::string> StrVec::alloc;

void StrVec::push_back(const string& s)
{
	chk_n_alloc();
	alloc.construct(first_free++, s);
}

std::pair<string*, string*>
StrVec::alloc_n_copy(const std::string* b, const std::string* e)
{
	auto data = alloc.allocate(e - b);

	return { data, uninitialized_copy(b, e, data) };
}

void StrVec::free()
{
	if (elements)
	{
		//for (auto p = first_free; p != elements; )
		//	alloc.destroy(--p);
		
		// for_each和lambda实现
		for_each(begin(), end(), [](string& p) { alloc.destroy(&p); });

		alloc.deallocate(elements, cap - elements);
	}
}

// 拷贝控制成员
StrVec::StrVec(const StrVec& s)
{
	auto newdata = alloc_n_copy(s.begin(), s.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}

StrVec::StrVec(std::initializer_list<string> il)
{
	auto newdata = alloc_n_copy(il.begin(), il.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}

StrVec::~StrVec() { free(); }

StrVec&
StrVec::operator=(const StrVec& rhs)
{
	auto newdata = alloc_n_copy(rhs.begin(), rhs.end());
	free();
	elements = newdata.first;
	first_free = cap = newdata.second;
	return *this;
}

// 移动构造函数和std::move
void StrVec::reallocate()
{
	auto newcapacity = size() ? 2 * size() : 1;
	auto newdata = alloc.allocate(newcapacity);	// 分配新内存

	auto dest = newdata;
	auto elem = elements;
	for (size_t i = 0; i != size(); ++i)
		alloc.construct(dest++, std::move(*elem++));
	
	free();
	elements = newdata;
	first_free = dest;
	cap = elements + newcapacity;
}

void StrVec::reserve(size_t n)
{
	if (n < capacity())
		return;

	auto newcapacity = n;
	auto newdata = alloc.allocate(newcapacity);	// 分配新内存

	auto dest = newdata;
	auto elem = elements;
	for (size_t i = 0; i != size(); ++i)
		alloc.construct(dest++, std::move(*elem++));

	free();
	elements = newdata;
	first_free = dest;
	cap = elements + newcapacity;
}

void StrVec::resize(size_t n)
{
	resize(n, string());
}

void StrVec::resize(size_t n, const string& s)
{
	if (n < size())
	{
		for (auto p = first_free; p != elements; )
			alloc.destroy(--p);
	}
	else
	{
		if (n > capacity())
		{
			reserve(n);
		}
		for (size_t i = 0; i != n - size(); ++i)
			alloc.construct(first_free++, s);
	}
}