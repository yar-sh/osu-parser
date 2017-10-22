////////////////////////////////////////////////////////////////
//                                                            //
//      OsString.cpp                                          //
//      HaselLoyance 2017, Unlicense                          //
//      https://github.com/HaselLoyance/osu-parser            //
//                                                            //
////////////////////////////////////////////////////////////////

#include "OsString.h"
#include <iostream>
using namespace osuParser;
using namespace std;

OsString::OsString() { }

OsString::OsString(const string & str)
{
	assign(str);
}

OsString::~OsString() {};

// Splits a string into multiple parts with given delimiter
//   delimiter, string, in what places to split the string
//   output, vector<string>, all parts of splitter string
// Eg: "1|2|3,4|5|6" -> .split(',', output) -> ["1|2|3","4|5|5"]
void OsString::split(const string & delim, vector<OsString> & output) const
{
	size_t prev = 0, pos = 0;
	do
	{
		pos = find(delim, prev);

		if (pos == string::npos)
		{
			pos = length();
		}

		output.push_back(substr(prev, pos - prev));

		prev = pos + delim.length();
	} while (pos < length() && prev < length());
}
