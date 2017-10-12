////////////////////////////////////////////////////////////////
//                                                            //
//      OsString.cpp                                          //
//      HaselLoyance 2017, Unlicense                          //
//      https://github.com/HaselLoyance/osu-parser            //
//                                                            //
////////////////////////////////////////////////////////////////

#include "OsString.h"

using namespace osuParser;
using namespace std;

OsString::OsString(const string & str)
{
	assign(str);
}

OsString::~OsString() {};

// Splits an osu string into chunks
// Eg: "1|2|3,4|5|6" -> ["1|2|3","4|5|6"]
//   chunks, &OsChunks, where splitted chunks will be written
void OsString::GetChunks(OsChunks & chunks) const
{
	int pos = 0;
	int offset = 0;

	while (true)
	{
		if (operator[](pos + offset) == ',')
		{
			chunks.push_back(string(&operator[](pos), &operator[](pos + offset)));
			pos += offset + 1;
			offset = 0;
		}

		if (pos + offset - 1 == size() - 1)
		{
			break;
		}

		offset++;
	}
}

// Splits an osu string chunks into values
// Eg: ["1|2|3"] -> ["1","2","3"]
//   values, string[], where splitted chunk values will be written
void OsString::GetChunkValues(string values[]) const
{
	int pos = 0;
	int offset = 0;
	int i = 0;

	while (true)
	{
		if (operator[](pos + offset) == '|')
		{
			values[i] = string(&operator[](pos), &operator[](pos + offset));
			pos += offset + 1;
			offset = 0;
			i++;
		}

		if (pos + offset - 1 == size() - 1)
		{
			values[i] = string(&operator[](pos), &operator[](pos + offset));
			i++;
			break;
		}

		offset++;
	}
}