#include "QueryResult.h"

inline string make_plural(size_t ctr, const string& word, const string& ending)
{
	return (ctr > 1) ? word + ending : word;
}

ostream& print(ostream& os, const QueryResult& qr)
{
	os << qr.sought << " occurs " << qr.lines->size() << " "
		<< make_plural(qr.lines->size(), "time", "s") << endl;

	for (auto num : *qr.lines)
	{
		os << "\t(line " << num + 1 << ") "
			<< *(qr.file->begin() + num) << endl;
	}

	return os;
}