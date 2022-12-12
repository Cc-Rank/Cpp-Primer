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
class StrBlob {
public:
	friend class StrBlobPtr;
	StrBlobPtr begin();
	StrBlobPtr end();

	StrBlobPtr begin() const;
	StrBlobPtr end() const;

	typedef vector<string>::size_type size_type;
	StrBlob() : 
		data(std::make_shared<vector<string>>()) { }
	StrBlob(initializer_list <string> il) :
		data(std::make_shared<vector<string>>(il)) { }
	StrBlob(const StrBlob& sb) :
		data(std::make_shared<vector<string>>(*sb.data)) {};

	StrBlob& operator=(const StrBlob& sb);

	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }

	// ��Ӻ�ɾ��Ԫ��
	void push_back(const string& t) { data->push_back(t); }
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
