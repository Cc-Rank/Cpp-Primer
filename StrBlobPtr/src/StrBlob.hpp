#pragma once
#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include <iostream>
using std::string; using std::vector;
using std::initializer_list; using std::shared_ptr;
using std::out_of_range;


class StrBlobPtr;
class ConstStrBlobPtr;
class StrBlob {
	friend bool operator == (const StrBlob&, const StrBlob&);
	friend bool operator != (const StrBlob&, const StrBlob&);
	friend bool operator < (const StrBlob&, const StrBlob&);
public:
	friend class StrBlobPtr;
	friend class ConstStrBlobPtr;
	StrBlobPtr begin();
	StrBlobPtr end();

	ConstStrBlobPtr cbegin() const;
	ConstStrBlobPtr cend() const;

	typedef vector<string>::size_type size_type;
	StrBlob() : 
		data(std::make_shared<vector<string>>()) { }
	StrBlob(initializer_list <string> il) :
		data(std::make_shared<vector<string>>(il)) { }
	StrBlob(const StrBlob& sb) :
		data(std::make_shared<vector<string>>(*sb.data)) {};

	StrBlob& operator=(const StrBlob& sb);
	string& operator [] (size_t n);
	const string& operator [] (size_t n) const;

	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }

	// ��Ӻ�ɾ��Ԫ��
	void push_back(const string& t) { data->push_back(t); }
	void push_back(string&& t) { data->push_back(std::move(t)); }
	void pop_back();

	// Ԫ�ط���
	string& front();
	const string& front() const;
	string& back();
	const string& back() const;

	void print();

private:
	shared_ptr<vector<string>> data;

	// ��� data[i] ���Ϸ����׳�һ���쳣
	void check(size_type i, const string& msg) const;
};