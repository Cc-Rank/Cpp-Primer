#include <iostream>
#include <vector>
#include <algorithm>

#include "StrVec.hpp"

using std::vector; using std::string;
using std::cin; using std::cout; using std::endl;

#define LOG(x) cout << x << endl;

void test()
{
	LOG("----------test_StrVec----------");

	StrVec sv{ "hello", "world" };

	//string s = "this is ";

	//sv.push_back(s);
	//sv.push_back("C++ Primer");

	//LOG("-----Print Results------");
	//for (auto sv_it = sv.begin(); sv_it != sv.end(); ++sv_it)
	//{
	//	cout << *sv_it << endl;
	//}

	LOG("----- 14.16 ----- ");
	StrVec sv_t(sv);
	StrVec sv_f{ "hello", "world!" };

	cout << (sv_t == sv) << ", " << (sv_f != sv) << endl;

	LOG("----- 14.18 ----- ");
	StrVec sv_b{ "hello", "worle" };

	cout << (sv < sv_b) << endl;

}

int main() 
{
	test();

	cin.get();
}