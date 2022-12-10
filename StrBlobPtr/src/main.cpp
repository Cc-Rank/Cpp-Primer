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
#include "StrBlob.h"
#include "StrBlobPtr.h"

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

void test_StrBolb()
{
	LOG("----------test_StrBlob----------");
	std::ifstream ifile("hello.txt");
	if (!ifile)
	{
		cerr << "no file!" << endl;
		return;
	}

	StrBlob sb;
	string line;
	while (getline(ifile, line))
	{
		sb.push_back(line);
	}
	//sb.print();
	for (auto sb_it(sb.begin()); sb_it != sb.end(); sb_it.incr())
		cout << sb_it.deref() << endl;


	//const StrBlob csb = { "Hello", "World", "!" };
	//for (auto sbp_it(csb.begin()), sbp_end(csb.end()); sbp_it != sbp_end; sbp_it.incr())
	//	cout << sbp_it.deref() << endl;

}
static int cnt = 1;
class Point
{
public:
	int i = 1;
	Point() 
	{
		LOG("Point");
	}
	Point(int oi) : i(oi)
	{
		LOG("Point_i")
	}
	Point(const Point& p) :i(p.i) 
	{
		LOG("Copy");
		LOG(cnt++);
	}
};

Point global;
Point foo_bar(Point arg) // 1
{
	Point local = arg, * heap = new Point(global); // 2, 3
	*heap = local;
	Point pa[4] = { local, *heap }; // 4, 5
	return *heap; // 6
}

void test()
{
	LOG("----------test----------");

	vector<int> ivec = { 1, 2, 3 ,4 ,5 };
	vector<string> istr;

	LOG(sizeof(ivec))
	LOG(sizeof(istr))

    cin.get();
}	

int main()
{
	test_StrBolb();

    test();
}