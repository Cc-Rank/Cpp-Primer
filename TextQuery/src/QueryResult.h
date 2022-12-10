#pragma once
#include <iostream>
#include <string>
#include <set>
#include <vector>
using std::ostream;
using std::shared_ptr;
using std::string; using std::vector; using std::set;
using std::endl;

class QueryResult {
	friend ostream& print(ostream&, const QueryResult&);
public:
	typedef vector<string>::size_type line_no;
	QueryResult(string s,
		shared_ptr<set<line_no>> p,
		shared_ptr<vector<string>> f) :
		sought(s), lines(p), file(f) { }
private:
	string sought;      // word this query represents
	shared_ptr<set<line_no>> lines;     // lines it's on
	shared_ptr<vector<string>> file;        // input file
};