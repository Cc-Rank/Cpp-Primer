#include "StrBlob.hpp"
#include "StrBlobPtr.hpp"
#include "ConstStrBlobPtr.hpp"

StrBlob&
StrBlob::operator=(const StrBlob& sb)
{
	data = sb.data;
	return* this;
}

string& StrBlob::operator [] (size_t n)
{
	check(n, "out of range.");
	return data->at(n);
}

const string& StrBlob::operator [] (size_t n) const
{
	check(n, "out of range.");
	return data->at(n);
}

void StrBlob::check(vector<string>::size_type i, const string& msg) const {
	if (i >= data->size())
		throw out_of_range(msg);
}

string& StrBlob::front() {
	check(0, "front on empty StrBlob");
	return data->front();
}

// const �汾 front
const string& StrBlob::front() const {
	check(0, "front on empty StrBlob");
	return data->front();
}

string& StrBlob::back() {
	check(0, "back on empty StrBlob");
	return data->back();
}

// const �汾 back
const string& StrBlob::back() const {
	check(0, "back on empty StrBlob");
	return data->back();
}

void StrBlob::pop_back() {
	check(0, "pop_back on empty StrBlob");
	data->pop_back();
}

void StrBlob::print()
{
	for (auto word : *data)
	{
		std::cout << word << std::endl;
	}
}

// StrBlob �� begin �� end ��Ա�Ķ���
StrBlobPtr StrBlob::begin() {
	return StrBlobPtr(*this);
}
StrBlobPtr StrBlob::end() {
	auto ret = StrBlobPtr(*this, data->size());
	return ret;
}

ConstStrBlobPtr StrBlob::cbegin() const {
	return ConstStrBlobPtr(*this);
}
ConstStrBlobPtr StrBlob::cend() const {
	auto ret = ConstStrBlobPtr(*this, data->size());
	return ret;
}

// ��Ԫ����
bool operator == (const StrBlob& lhs, const StrBlob& rhs)
{
	return *lhs.data == *rhs.data;
}

bool operator != (const StrBlob& lhs, const StrBlob& rhs)
{
	return !(lhs == rhs);
}

bool operator < (const StrBlob& lhs, const StrBlob& rhs)
{
	return *lhs.data < *rhs.data;
}