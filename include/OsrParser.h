////////////////////////////////////////////////////////////////
//                                                            //
//      OsrParser.h                                           //
//      HaselLoyance 2017, Unlicense                          //
//      https://github.com/HaselLoyance/osu-parser            //
//                                                            //
////////////////////////////////////////////////////////////////

#ifndef OSU_PARSER_OSR_H
#define OSU_PARSER_OSR_H

#include <fstream>
#include "OsTypes.h"
#include "OsUtils.h"

namespace osuParser
{
	// Object for parsing "*.osr" files from preloaded stream
	// For file format please visit: https://osu.ppy.sh/help/wiki/osu!_File_Formats/Osr_(file_format)
	class OsrParser
	{
	public:
		// String names for each of the available mods
		const static std::vector<std::string> modNames;

		// Creates a parser from ifstream
		OsrParser(std::ifstream * filestream);
		~OsrParser();

		// Goes through ifstream and assigns data
		void Parse();

		// Game mode of the replay
		GameMode mode;

		// Game mode of the replay (in string form)
		std::string modeString;

		// Version of the game where the replay was created
		OsLong version;

		// osu! beatmap MD5 hash
		std::string beatmapHash;

		// Player name
		std::string player;

		// osu! replay MD5 hash
		std::string replayHash;

		// Number of 300s
		OsShort n300s;

		// Number of 100s in standard, 150s in Taiko, 100s in CTB, 200s in mania
		OsShort n100s;

		// Number of 50s in standard, small fruit in CTB, 50s in mania
		OsShort n50s;

		// Number of Gekis in standard, Max 300s in mania
		OsShort nGekis;

		// Number of Katus in standard, 100s in mania
		OsShort nKatus;

		// Number of misses
		OsShort nMisses;

		// Total score displayed on the score report
		OsInteger score;

		// Greatest combo displayed on the score report
		OsShort combo;

		// Perfect/full combo (1 = no misses and no slider breaks and no early finished sliders)
		bool isFC;

		// Mods used. See IsModActive and ModType
		ModMask modsMask;

		// Mods used in a vector of ModType
		std::vector<ModType> modsVector;

		// Mods used in a vector of strings
		std::vector<std::string> modsStringVector;

		// Life bar graph. Represents the amount of life you have at the given time
		std::vector<LifeBarPoint> lifebar;

		// Time stamp (https://msdn.microsoft.com/en-us/library/system.datetime.ticks(v=vs.110).aspx)
		OsLong timestamp;

		// Vector of actions. See Action struct
		std::vector<Action> actions;

		// Last 4 bytes of replay file - unknown
		OsLong unknown;

	private:
		// Stream reading operations
		uint8_t _GetStreamByte();
		uint16_t _GetStreamShort();
		uint32_t _GetStreamInteger();
		uint64_t _GetStreamLong();
		uint64_t _GetStreamULEB128();
		std::string _GetStreamString();

		// Data extraction which requires more work than just
		// reading byte values
		void _CalcGameModeString();
		void _CalcModsVector();
		void _CalcModsStringVector();
		void _CalcLifebar();
		void _CalcActions();

		// Pointer to the passed ifstream in constructor
		std::ifstream * _s;
	};
}
#endif
