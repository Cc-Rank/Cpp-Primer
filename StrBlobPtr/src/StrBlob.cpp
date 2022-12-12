#include "StrBlob.h"
#include "StrBlobPtr.h"

StrBlob&
StrBlob::operator=(const StrBlob& sb)
{
	data = sb.data;
	return* this;
}

void StrBlob::check(vector<string>::size_type i, const string& msg) const {
	if (i >= data->size())
		throw out_of_range(msg);
}

string& StrBlob::front() {
	check(0, "front on empty StrBlob");
	return data->front();
}

// const 版本 front
const string& StrBlob::front() const {
	check(0, "front on empty StrBlob");
	return data->front();
}

string& StrBlob::back() {
	check(0, "back on empty StrBlob");
	return data->back();
}

// const 版本 back
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

// StrBlob 的 begin 和 end 成员的定义
StrBlobPtr StrBlob::begin() {
	return StrBlobPtr(*this);
}
StrBlobPtr StrBlob::end() {
	auto ret = StrBlobPtr(*this, data->size());
	return ret;
}

StrBlobPtr StrBlob::begin() const {
	return StrBlobPtr(*this);
}
StrBlobPtr StrBlob::end() const {
	auto ret = StrBlobPtr(*this, data->size());
	return ret;
}