////////////////////////////////////////////////////////////////
//                                                            //
//      OsUtils.h                                             //
//      HaselLoyance 2017, Unlicense                          //
//      https://github.com/HaselLoyance/osu-parser            //
//                                                            //
////////////////////////////////////////////////////////////////

#ifndef OSU_PARSER_UTILS_H
#define OSU_PARSER_UTILS_H

#include <vector>
#include <string>

#include "OsTypes.h"
#include "LzmaLib.h"

#define IsBitSet(variable, bitNumber) bool((variable) & (1 << (bitNumber)))

namespace osuParser
{
	// Splits a string into multiple parts with given delimiter
	//   str, string, string to split
	//   delimiter, string, in what places to split the string
	//   output, ref vector<string>, all parts of the splitted string
	// Eg: SplitString("1|2|3,4|5|6", ',', output) -> ["1|2|3","4|5|6"]
	void SplitString(const std::string & str, const std::string & delim, std::vector<std::string> & output);

	// Checks if input is active in an input mask
	//   inputs, InputMask, inputs mask
	//   input, InputType, input to check if is active
	// Returns true if input is active in an input mask, false otherwise
	bool IsInputActive(const InputMask & inputs, const InputType & input);

	// Checks if mod is active in a mod mask
	//   mods, ModMask, mods mask
	//   mod, ModType, mod to check if is active
	// Returns true if mod is active in a mod mask, false otherwise
	bool IsModActive(const ModMask & mods, const ModType & mod);

	// Decompress LZMA-compressed buffer
	//   inBuf, vector<uint8_t>, input buffer with LZMA-compressed bytes
	//   outBuf, ref vector<uint8_t>, output buffer where decompressed data will be written
	void DecompressLZMA(const std::vector<uint8_t> &inBuf, std::vector<uint8_t> & outBuf);
}

#endif
