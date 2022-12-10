#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <set>
#include <sstream>
#include "QueryResult.h"

using std::vector; using std::string;
using std::map; using std::set;

class QueryResult;
class TextQuery
{
public:
	using line_no = vector<string>::size_type;
	TextQuery(std::ifstream&);
	QueryResult query(const string&) const;

private:
	std::shared_ptr<vector<string>> file;     // input file
	// maps each word to the set of the lines in which that word appears
	map<string, std::shared_ptr<set<line_no>>> wm;
};