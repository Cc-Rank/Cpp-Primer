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
	friend bool operator == (const StrVec&, const StrVec&);
	friend bool operator != (const StrVec&, const StrVec&);
	friend bool operator < (const StrVec&, const StrVec&);
public:
	StrVec() :
		elements(nullptr), first_free(nullptr), cap(nullptr) { }
	StrVec(const StrVec&);
	StrVec(StrVec&&) noexcept;
	StrVec(std::initializer_list<string>);
	~StrVec();

	StrVec& operator = (const StrVec&);
	StrVec& operator = (StrVec&&) noexcept;
	StrVec& operator = (std::initializer_list<string>);
	string& operator [] (size_t n) { return elements[n]; }
	const string& operator [] (size_t n) const { return elements[n]; }

	void push_back(const string&);
	void push_back(string&&);

	size_t size() const { return first_free - elements; }
	size_t capacity() const { return cap - elements; }
	std::string* begin() const { return elements; }
	std::string* end() const { return first_free; }

	void reserve(size_t);
	void resize(size_t);
	void resize(size_t, const string&);

private:
	static allocator<std::string> alloc;	// ����Ԫ��

	void chk_n_alloc() { if (size() == capacity()) reallocate(); }
	std::pair<std::string*, std::string*> alloc_n_copy(const std::string*, const std::string*);
	void free();
	void reallocate();

	std::string* elements;
	std::string* first_free;
	std::string* cap;
};

// ���е�static��Աֻ������������Ҫ��������ж��壻
allocator<std::string> StrVec::alloc;

// �������Ƴ�Ա
StrVec::StrVec(const StrVec& s)
{
	auto newdata = alloc_n_copy(s.begin(), s.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}

StrVec::StrVec(StrVec&& s) noexcept :
elements(s.elements), first_free(s.first_free), cap(s.cap)
{
	s.elements = s.first_free = s.cap = nullptr;
}

StrVec::StrVec(std::initializer_list<string> il)
{
	auto newdata = alloc_n_copy(il.begin(), il.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}

StrVec::~StrVec() { free(); }

StrVec&
StrVec::operator = (const StrVec& rhs)
{
	auto newdata = alloc_n_copy(rhs.begin(), rhs.end());
	free();
	elements = newdata.first;
	first_free = cap = newdata.second;
	return *this;
}

StrVec&
StrVec::operator = (StrVec&& rhs) noexcept
{
	if (this != &rhs)
	{
		free();
		elements = rhs.elements;
		first_free = rhs.first_free;
		cap = rhs.cap;
		rhs.elements = rhs.first_free = rhs.cap = nullptr;
	}
	return *this;
}

StrVec& 
StrVec::operator = (std::initializer_list<string> il)
{
	auto data = alloc_n_copy(il.begin(), il.end());
	free();
	elements = data.first;
	first_free = cap = data.second;
	return *this;
}

void StrVec::push_back(const string& s)
{
	chk_n_alloc();
	alloc.construct(first_free++, s);
	LOG("LValue");
}

void StrVec::push_back(string&& s)
{
	chk_n_alloc();
	alloc.construct(first_free++, std::move(s));
	LOG("RValue");
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
		
		// for_each��lambdaʵ��
		for_each(begin(), end(), [](string& p) { alloc.destroy(&p); });

		alloc.deallocate(elements, cap - elements);
	}
}

void StrVec::reallocate()
{
	auto newcapacity = size() ? 2 * size() : 1;
	auto newdata = alloc.allocate(newcapacity);	// �������ڴ�

	// /* �ƶ����캯����std::move */
	// auto dest = newdata;
	// auto elem = elements;
	// for (size_t i = 0; i != size(); ++i)
	// 	alloc.construct(dest++, std::move(*elem++));
	// /* �ƶ������� make_move_iterator */
	auto dest = uninitialized_copy(make_move_iterator(begin()),
		make_move_iterator(end()), newdata);
	
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
	auto newdata = alloc.allocate(newcapacity);	// �������ڴ�

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

// ��Ԫ����
bool operator == (const StrVec& lhs, const StrVec& rhs)
{
	return (lhs.size() == rhs.size() &&
		std::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

bool operator != (const StrVec& lhs, const StrVec& rhs)
{
	return !(lhs == rhs);
}

bool operator < (const StrVec& lhs, const StrVec& rhs)
{
	//auto pl = lhs.begin(), pr = rhs.begin();
	//while (pl != lhs.end() && pr != rhs.end())
	//{
	//	if (*pl < *pr)
	//		return true;
	//	else if (*pl > *pr)
	//		return false;
	//	++pl, ++pr;
	//}
	//
	//if (pl == lhs.end() && pr != rhs.end())
	//	return true;
	//return false;
	return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
		rhs.end());
}