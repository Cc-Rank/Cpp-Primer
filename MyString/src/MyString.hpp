#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

using std::istream; using std::ostream;
using std::vector; using std::string;
using std::cin; using std::cout; using std::endl;
using std::allocator;

#define LOG(x) cout << x << endl;

class MyString
{
	friend ostream& operator<<(ostream&, const MyString&);
	friend bool operator == (const MyString&, const MyString&);
	friend bool operator != (const MyString&, const MyString&);
	friend bool operator < (const MyString&, const MyString&);
public:
	MyString() :
		elements(nullptr), first_free(nullptr), cap(nullptr) { }
	MyString(const char*);
	MyString(const MyString&);
	MyString(MyString&&) noexcept;
	~MyString();
	MyString& operator = (const MyString&);
	MyString& operator = (MyString&&) noexcept;
	MyString& operator = (const char*);
	char& operator [] (size_t n) { return elements[n]; }
	const char& operator [] (size_t n) const { return elements[n]; }

	void push_back(const char);

	size_t length() const { return first_free - elements; }
	size_t size() const { return first_free - elements; }
	size_t capacity() const { return cap - elements; }
	char* begin() const { return elements; }
	char* end() const { return first_free; }
	const char* c_str() const { return elements; }

	void reserve(size_t);
	void resize(size_t, const char);

private:
	static allocator<char> alloc;	// 分配元素

	void chk_n_alloc() { if (size() == capacity()) reallocate(); }
	std::pair<char*, char*> alloc_n_copy(const char*, const char*);
	void free();
	void reallocate();

	char* elements;
	char* first_free;
	char* cap;
};

// 类中的static成员只是声明，还需要在类外进行定义；
allocator<char> MyString::alloc;

// 拷贝控制成员
MyString::MyString(const char* cp)
{
	LOG("construct");
	auto newdata = alloc_n_copy(cp, cp + strlen(cp) + 1);
	elements = newdata.first;
	first_free = cap = newdata.second;
}

MyString::MyString(const MyString& s)
{
	LOG("copy");
	auto newdata = alloc_n_copy(s.begin(), s.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}

MyString::MyString(MyString&& s) noexcept :
elements(s.elements), first_free(s.first_free), cap(s.cap)
{
	s.elements = s.first_free = s.cap = nullptr;
	LOG("move copy");
}

MyString::~MyString() { free(); }

MyString&
MyString::operator=(const MyString& rhs)
{
	LOG("assign");
	auto newdata = alloc_n_copy(rhs.begin(), rhs.end());
	free();
	elements = newdata.first;
	first_free = cap = newdata.second;
	return *this;
}

MyString& 
MyString::operator = (MyString&& rhs) noexcept
{
	if (this != &rhs)
	{
		elements = rhs.elements;
		first_free = rhs.first_free;
		cap = rhs.cap;
		rhs.elements = rhs.first_free = rhs.cap = nullptr;
	}
	LOG("move assign");
	return *this;
}

MyString&
MyString::operator=(const char* cp)
{
	auto newdata = alloc_n_copy(cp, cp + strlen(cp) + 1);
	free();
	elements = newdata.first;
	first_free = cap = newdata.second;
	return *this;
}

void MyString::push_back(const char c)
{
	chk_n_alloc();
	alloc.construct(first_free++, c);
}

std::pair<char*, char*>
MyString::alloc_n_copy(const char* b, const char* e)
{
	auto data = alloc.allocate(e - b);

	return { data, std::uninitialized_copy(b, e, data) };
}

void MyString::free()
{
	if (elements)
	{
		//for (auto p = first_free; p != elements; )
		//	alloc.destroy(--p);

		// for_each和lambda实现
		std::for_each(begin(), end(), [this](char& p) { alloc.destroy(&p); });

		alloc.deallocate(elements, cap - elements);
	}
}

void MyString::reallocate()
{
	auto newcapacity = size() ? 2 * size() : 1;
	auto newdata = alloc.allocate(newcapacity);	// 分配新内存

	// /* 移动构造函数和std::move */
	// auto dest = newdata;
	// auto elem = elements;
	// for (size_t i = 0; i != size(); ++i)
	// 	alloc.construct(dest++, std::move(*elem++));

	auto dest = std::uninitialized_copy(std::make_move_iterator(begin()),
		std::make_move_iterator(end()), newdata);

	free();
	elements = newdata;
	first_free = dest;
	cap = elements + newcapacity;
}

void MyString::reserve(size_t n)
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

void MyString::resize(size_t n, const char c = char())
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
			alloc.construct(first_free++, c);
	}
}

// 友元函数
ostream& operator<<(ostream& os, const MyString& s)
{
	return os << s.c_str();
}

bool operator == (const MyString& rhs, const MyString& lhs)
{
	//if (lhs.size() != rhs.size())
	//	return false;
	//auto p = rhs.elements;
	//auto q = lhs.elements;
	//while (*p)
	//{
	//	if (*p != *q)
	//		return false;
	//	p++; q++;
	//}
	//return true;
	return (lhs.size() == rhs.size() &&
		std::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

bool operator != (const MyString& rhs, const MyString& lhs)
{
	return !(rhs == lhs);
}

bool operator < (const MyString& lhs, const MyString& rhs)
{
	auto pl = lhs.begin(), pr = rhs.begin();
	while (pl != lhs.end() && pr != rhs.end())
	{
		if (*pl < *pr)
			return true;
		else if (*pl > *pr)
			return false;
		++pl, ++pr;
	}
	
	if (pl == lhs.end() && pr != rhs.end())
		return true;
	return false;
	//return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
	//	rhs.end());
}