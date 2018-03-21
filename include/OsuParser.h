////////////////////////////////////////////////////////////////
//                                                            //
//      OsuParser.h                                           //
//      HaselLoyance 2017, Unlicense                          //
//      https://github.com/HaselLoyance/osu-parser            //
//                                                            //
////////////////////////////////////////////////////////////////

#ifndef OSU_PARSER_OSU_H
#define OSU_PARSER_OSU_H

#include "OsTypes.h"
#include "OsUtils.h"

namespace osuParser
{
	// Object for parsing "*.osu" files from preloaded stream
	// For file format please visit: LINK
	class OsuParser
	{
	public:

		// Creates a parser from ifstream
		OsuParser(std::istream * filestream);
		~OsuParser();

		// Goes through ifstream and assigns data
		void Parse();

	private:

		// Pointer to the passed ifstream in constructor
		std::istream * _s;
	};
}
#endif
