////////////////////////////////////////////////////////////////
//                                                            //
//      OsString.h                                            //
//      HaselLoyance 2017, Unlicense                          //
//      https://github.com/HaselLoyance/osu-parser            //
//                                                            //
////////////////////////////////////////////////////////////////

#ifndef OSU_PARSER_STRING_H
#define OSU_PARSER_STRING_H

#include <string>
#include <vector>

#include "OsTypes.h"

namespace osuParser
{
	// A derived class from std::string to add functions for operating with
	// osu strings (eg: "1|2|3,4|5|6")
	class OsString : public std::string
	{
	public:
		OsString();
		OsString(const std::string & str);
		~OsString();

		// Splits a string into multiple parts with given delimiter
		//   delimiter, string, in what places to split the string
		//   output, vector<string>, all parts of splitter string
		// Eg: "1|2|3,4|5|6" -> .split(',', output) -> ["1|2|3","4|5|5"]
		void OsString::split(const std::string & delim, std::vector<OsString> & output) const;
	};
}

#endif
