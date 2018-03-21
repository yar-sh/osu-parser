////////////////////////////////////////////////////////////////
//                                                            //
//      OsuParser.cpp                                         //
//      HaselLoyance 2017, Unlicense                          //
//      https://github.com/HaselLoyance/osu-parser            //
//                                                            //
////////////////////////////////////////////////////////////////

#include "OsuParser.h"

using namespace std;
using namespace osuParser;

// Creates a parser from ifstream
OsuParser::OsuParser(istream * filestream)
{
	_s = filestream;
}

OsuParser::~OsuParser() {};

// Goes through ifstream and reads all data
void OsuParser::Parse()
{
}
