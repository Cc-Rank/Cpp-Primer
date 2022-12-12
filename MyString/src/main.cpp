#include <iostream>
#include <vector>
#include <algorithm>

#include "MyString.hpp"

using std::vector; using std::string;
using std::cin; using std::cout; using std::endl;

#define LOG(x) cout << x << endl;

void test()
{
	LOG("----------test----------");
	string s("str");
	LOG(s.c_str());
	//s.push_back('s');
	//LOG(*s.begin());
	//MyString ss("std");
	
	vector<MyString> msVec;
	msVec.reserve(10);
	msVec.push_back("str1");
	msVec.push_back("str2");
	msVec.push_back("str3");

	LOG(msVec[0].begin());

	//std::for_each(ss.begin(), ss.end(), [](const char c) {cout << c << endl; });
}

int main()
{
	test();

	cin.get();
}