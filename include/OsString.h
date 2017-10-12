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
		OsString(const std::string & str);
		~OsString();

		// Splits an osu string into chunks
		// Eg: "1|2|3,4|5|6" -> ["1|2|3","4|5|6"]
		//   chunks, &OsChunks, where splitted chunks will be written
		void GetChunks(OsChunks & chunks) const;

		// Splits an osu string chunks into values
		// Eg: ["1|2|3"] -> ["1","2","3"]
		//   values, string[], where splitted chunk values will be written
		void GetChunkValues(std::string values[]) const;
	};
}

#endif
