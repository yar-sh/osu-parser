////////////////////////////////////////////////////////////////
//                                                            //
//      OsUtils.cpp                                           //
//      HaselLoyance 2017-2018, Unlicense                     //
//      https://github.com/HaselLoyance/osu-parser            //
//                                                            //
////////////////////////////////////////////////////////////////

#include "OsUtils.h"

using namespace osuParser;
using namespace std;

// Splits a string into multiple parts with given delimiter
//   str, string, string to split
//   delimiter, string, in what places to split the string
//   output, ref vector<string>, all parts of the splitted string
// Eg: SplitString("1|2|3,4|5|6", ',', output) -> ["1|2|3","4|5|6"]
void osuParser::SplitString(const string & str, const string & delim, vector<string> & output)
{
	size_t prev = 0;
	size_t pos = 0;

	while (true)
	{
		pos = str.find(delim, prev);

		if (pos == string::npos)
		{
			pos = str.length();
		}

		output.push_back(str.substr(prev, pos - prev));

		prev = pos + delim.length();

		if (pos >= str.length() || prev >= str.length())
		{
			break;
		}
	}
}

// Trims (removes whitespace) passed string
//   str, ref string, string to trim
void osuParser::TrimString(string & str) {
	str.erase(str.begin(), find_if(str.begin(), str.end(), [](int ch) {
		return !isspace(static_cast<unsigned char>(ch));
	}));
}

// Checks if input is active in an input mask
//   inputs, InputMask, inputs mask
//   input, InputType, input to check if is active
// Returns true if input is active in an input mask, false otherwise
bool osuParser::IsInputActive(const InputMask & inputs, const InputType & input)
{
	return IsBitSet(inputs, input);
}

// Checks if mod is active in a mod mask
//   mods, ModMask, mods mask
//   mod, ModType, mod to check if is active
// Returns true if mod is active in a mod mask, false otherwise
bool osuParser::IsModActive(const ModMask & mods, const ModType & mod)
{
	return IsBitSet(mods, mod);
}

// Decompress LZMA-compressed buffer
//   inBuf, vector<uint8_t>, input buffer with LZMA-compressed bytes
//   outBuf, ref vector<uint8_t>, output buffer where decompressed data will be written
void osuParser::DecompressLZMA(const vector<uint8_t> &inBuf, vector<uint8_t> & outBuf)
{
	outBuf.clear();
	// Reserves N bytes, shrinks to fit after decompression
	outBuf.resize(inBuf.size() * 4); //-V112
	size_t dstLen = outBuf.size();
	size_t srcLen = inBuf.size() - LZMA_PROPS_SIZE - 8;
	LzmaUncompress(&outBuf[0], &dstLen, &inBuf[LZMA_PROPS_SIZE + 8], &srcLen, &inBuf[0], LZMA_PROPS_SIZE);
	outBuf.resize(dstLen);
}

// Check to see if two double values are equal
//   a, double, first value to check
//   b, double, second value to check
// Returns true if both values are equal, false otherwise
bool osuParser::IsEqualDouble(const double & a, const double & b)
{
	return fabs(a - b) < DBL_EPSILON;
}

// String names for each of the available mods
const vector<string> osuParser::_modNames = {
	"NoFail", "Easy", "NoVideo", "Hidden", "HardRock", "SuddenDeath", "DoubleTime",
	"Relax", "HalfTime", "Nightcore", "Flashlight", "Autoplay", "SpunOut", "Relax2",
	"Perfect", "Key4", "Key5", "Key6", "Key7", "Key8", "FadeIn", "Random", "LastMod",
	"TargetPractice", "Key9", "Coop", "Key1", "Key3", "Key2",
};

// String names for each of the available game modes
const vector<string> osuParser::_modeNames = {
	"Standard", "Taiko", "Catch The Beat", "Mania"
};

// String names for each of the available sample sets
const vector<string> osuParser::_sampleSetNames = {
	"Auto", "Normal", "Soft", "Drum"
};

// String names for each of the available beatmap events
const vector<string> osuParser::_eventNames = {
	"Background", "Video", "Break", "Unknown"
};

// String names for each of the available hit object types
const vector<string> osuParser::_hitObjectNames = {
	"Circle", "Slider", "Spinner", "HoldNote"
};

// String names for each of the available hit sound types
const vector<string> osuParser::_hitSoundNames = {
	"Normal", "Whistle", "Finish", "Clap"
};