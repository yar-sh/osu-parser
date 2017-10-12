////////////////////////////////////////////////////////////////
//                                                            //
//      OsUtils.h                                             //
//      HaselLoyance 2017, Unlicensed                         //
//      https://github.com/HaselLoyance/osu-parser            //
//                                                            //
////////////////////////////////////////////////////////////////

#ifndef OSU_PARSER_UTILS_H
#define OSU_PARSER_UTILS_H

#include <vector>

#include "OsTypes.h"
#include "LzmaLib.h"

namespace osuParser
{
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
	//   outBuf, &vector<uint8_t>, output buffer where decompressed data will be written
	void DecompressLZMA(const std::vector<uint8_t> &inBuf, std::vector<uint8_t> & outBuf);
}

#endif