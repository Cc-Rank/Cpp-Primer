#include <iostream>
#include <vector>
#include <algorithm>

#include "MyString.hpp"

using std::vector; using std::string;
using std::cin; using std::cout; using std::endl;

#define LOG(x) cout << x << endl;

void test()
{
	LOG("----------test_MyString----------");
	string s("str");
	//LOG(s.c_str());
	////s.push_back('s');
	////LOG(*s.begin());
	MyString ss("std");
	//
	//vector<MyString> msVec;
	//msVec.reserve(10);
	//msVec.push_back("str1");
	//msVec.push_back("str2");
	//msVec.push_back("str3");

	//LOG(msVec[0].begin());

	//std::for_each(ss.begin(), ss.end(), [](const char c) {cout << c << endl; });

	//LOG("----- 14.6 -----");
	//cout << s << endl;
	//cout << ss << endl;

	LOG("----- 14.16 ----- ");
	MyString ss_true("std");
	MyString ss_false("str");
	cout << (ss_true == ss) << ", " << (ss_false != ss) << endl;

	LOG("----- 14.18 ----- ");
	MyString ss_b("std1");
	cout << (ss < ss_b) << endl;

	LOG("----- 14.26 ----- ");
	cout << ss[0] << ", " << ss[4] << endl;

	cout << ss.begin() << endl;

}

int main()
{
	test();

	cin.get();
}