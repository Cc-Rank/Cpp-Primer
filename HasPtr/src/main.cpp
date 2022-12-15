#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include "HasPtr.hpp"

using std::vector; using std::string;
using std::ifstream;
using std::istringstream;

void test()
{
	LOG("----------test----------");
	
	ifstream in_file("test.txt");

	string line;
	string word;
	vector<HasPtr> hsvec;
	hsvec.reserve(10);
	while (getline(in_file, line)) {
		istringstream in_line(line);           // 构造字符串流，读取单词
		while (in_line >> word)
		{
			hsvec.emplace_back(word);
			//LOG(hsvec.capacity());
		}
	}

	LOG("sort");
	std::sort(hsvec.begin(), hsvec.end());
	
}

int main()
{
	test();

	cin.get();
}