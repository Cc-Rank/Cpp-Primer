#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <forward_list>
#include <array>
#include <list>
#include <algorithm>
#include <set>
#include <map>
#include "StrBlob.hpp"
#include "StrBlobPtr.hpp"
#include <functional>

using std::cout; using std::cin; using std::endl; using std::cerr;
using std::string; using std::vector;
using std::ifstream; using std::ofstream;
using std::istringstream; using std::ostringstream;

#define LOG(x) std::cout << x << std::endl;

class Singleton
{
public:
	static Singleton& Get()
	{
		static Singleton instance;
		return instance;
	}

	void Hello() {};
};

class GetInput {
public:
	GetInput(std::istream& i = std::cin) : is(i) {}
	std::string operator()() const
	{
		std::string str;
		std::getline(is, str);
		return is ? str : std::string();
	}

private:
	std::istream& is;
};

void test_others()
{
    //GetInput getInput;
    //std::cout << getInput() << std::endl;

	//std::plus<int> inAdd;
	//std::negate<int> intNegate;

	//int sum = intNegate(inAdd(10, 30));
	//cout << sum << endl;

	//int a = 65;
	//int* ap = &a;
	//char* as = reinterpret_cast<char*>(ap);
	//while (*as)
	//{
	//	cout << *as << endl;
	//	as++;
	//}
}

void test()
{
	LOG("----------test_StrBlob----------");

	vector<string> ivec = { "hello", "world" };
	//vector<string> istr;

	//LOG(sizeof(ivec))
	//LOG(sizeof(istr))

	LOG("----- 14.18 -----");
	//auto ivec_begin = ivec.begin();
	//auto ivec_end = ivec.end();
	//vector<int> ivec2(ivec);
	//ivec2.push_back(1);
	//auto ivec2_begin = ivec2.begin();

	//cout << (ivec_begin < ivec_end) << endl;
	//cout << (ivec_begin <= ivec_begin) << endl;
	////cout << (ivec_begin <= ivec2_begin) << endl;
	//cout << (ivec > ivec2) << endl;

	StrBlob sb = { "hello", "world" };
	StrBlob sb_b = { "hello", "worle" };
	StrBlob sb_s = { "hello", "worlc" };
	StrBlob sb_e = { "hello", "world", "!" };

	cout << (sb < sb_b) << ", " << (sb < sb_s) << endl;
	cout << (sb < sb_s) << endl;

	LOG("----- 14.26 -----");
	cout << sb[0] << ", " << sb[1] << endl;

	LOG("----- 14.28 -----"); 
	vector<string>::iterator ivec_it = ivec.begin();
	//auto temp_it = 5 + ivec_it;
	//ivec_it += 5;
	//cout << *temp_it << endl;
	//temp_it = ivec_it + 1;
	//cout << *temp_it << endl;
	StrBlobPtr sbp(sb);
	StrBlobPtr sbp_temp = sbp + 1;

	cout << sbp_temp.deref() << endl;

	cout << ivec_it->c_str() << endl;

    cin.get();
}	

int main()
{
	test_others();

    //test();
}