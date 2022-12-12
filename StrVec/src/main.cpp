#include <iostream>
#include <vector>
#include <algorithm>

#include "StrVec.hpp"

using std::vector; using std::string;
using std::cin; using std::cout; using std::endl;

#define LOG(x) cout << x << endl;

void test()
{
	LOG("----------test----------");

	StrVec sv{"hello", "world"};
	string ss;
	ss.push_back('s');
	ss.resize(10);
	
	std::for_each(ss.begin(), ss.end(), [](const char p) {cout << p << ","; });
	LOG("-----------")

	for (auto sv_it = sv.begin(); sv_it != sv.end(); ++sv_it)
	{
		cout << *sv_it << endl;
	}
}

int main() 
{
	test();

	cin.get();
}