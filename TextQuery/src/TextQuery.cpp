#include "TextQuery.h"

TextQuery::TextQuery(std::ifstream& infile) : file(new vector<string>)
{
	string text;
	while (getline(infile, text))
	{
		file->push_back(text);
		int n = file->size() - 1;
		std::istringstream line(text);
		string word;
		while (line >> word)
		{
			auto& lines = wm[word];
			if (!lines)
				lines.reset(new set<line_no>);
			lines->insert(n);
		}
	}
}

QueryResult
TextQuery::query(const string& sought) const {
	// we'll return a pointer to this set if we don't find sought
	static std::shared_ptr<set<line_no>> nodata(new set<line_no>);

	// use find and not a subscript to avoid adding words to wm!
	// cleanup_str removes punctuation and convert sought to lowercase
	auto loc = wm.find(sought);

	if (loc == wm.end())
		return QueryResult(sought, nodata, file);       // not found
	else
		return QueryResult(sought, loc->second, file);
}
