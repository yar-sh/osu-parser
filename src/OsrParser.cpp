////////////////////////////////////////////////////////////////
//                                                            //
//      OsrParser.cpp                                         //
//      HaselLoyance 2017, Unlicense                          //
//      https://github.com/HaselLoyance/osu-parser            //
//                                                            //
////////////////////////////////////////////////////////////////

#include "OsrParser.h"

using namespace std;
using namespace osuParser;

// String names for each of the available mods
const vector<string> OsrParser::modNames = {
	"NoFail", "Easy", "NoVideo", "Hidden", "HardRock", "SuddenDeath", "DoubleTime", "Relax",
	"HalfTime", "Nightcore", "Flashlight", "Autoplay", "SpunOut", "Relax2", "Perfect", "Key4",
	"Key5", "Key6", "Key7", "Key8", "FadeIn", "Random", "LastMod", "TargetPractice", "Key9",
	"Coop", "Key1", "Key3", "key2",
};

// Creates a parser from ifstream
OsrParser::OsrParser(ifstream * filestream)
{
	_s = filestream;
	mode = gmStandard;
	version = 0;
	player.clear();
	beatmapHash.clear();
	replayHash.clear();
	n300s = 0;
	n100s = 0;
	n50s = 0;
	nGekis = 0;
	nKatus = 0;
	nMisses = 0;
	score = 0;
	combo = 0;
	isFC = false;
	modsMask = 0;
	modsVector = {};
	modsStringVector = {};
	timestamp = 0;
	actions = {};
	unknown = 0;
}

OsrParser::~OsrParser() {};

// Goes through ifstream and reads all data
void OsrParser::Parse()
{
	_s->seekg(0);

	mode = static_cast<GameMode>(_GetStreamByte());

	_CalcGameModeString();

	version = _GetStreamInteger();

	beatmapHash = _GetStreamString();

	player = _GetStreamString();

	replayHash = _GetStreamString();

	n300s = _GetStreamShort();

	n100s = _GetStreamShort();

	n50s = _GetStreamShort();

	nGekis = _GetStreamShort();

	nKatus = _GetStreamShort();

	nMisses = _GetStreamShort();

	score = _GetStreamInteger();

	combo = _GetStreamShort();

	isFC = _GetStreamByte();

	modsMask = _GetStreamInteger();

	_CalcModsVector();

	_CalcModsStringVector();

	_CalcLifebar();

	timestamp = _GetStreamLong();

	_CalcActions();

	unknown = _GetStreamLong();

	_s->seekg(0);
}


uint8_t OsrParser::_GetStreamByte()
{
	uint8_t b = 0;
	b = _s->get();
	return b;
}

uint16_t OsrParser::_GetStreamShort()
{
	uint16_t b = 0;
	_s->read((char *)&b, sizeof(uint16_t));
	return b;
}

uint32_t OsrParser::_GetStreamInteger()
{
	uint32_t b = 0;

	// Requires explicit conversion to read bytes
	_s->read((char *)&b, sizeof(uint32_t)); //-V206
	return b;
}

uint64_t OsrParser::_GetStreamLong()
{
	uint64_t b = 0;

	// Requires explicit conversion to read bytes
	_s->read((char *)&b, sizeof(uint64_t)); //-V206
	return b;
}

uint64_t OsrParser::_GetStreamULEB128()
{
	uint64_t result = 0;
	uint8_t shift = 0;

	while (true)
	{
		uint8_t byte = _s->get();

		// In our case the size of ULEB128 can never be > 8 bytes
		// 8*8 = 64 bits, so shift value will always be under 1 byte size
		result |= (byte & ~(1 << 7)) << shift; //-V629

		if (!IsBitSet(byte, 7))
		{
			return result;
		}

		shift += 7;
	}
}

string OsrParser::_GetStreamString()
{
	if (_GetStreamByte() != 0x0b)
	{
		return "";
	}

	uint64_t strLength = _GetStreamULEB128();
	string output(strLength, NULL);

	_s->read(&output[0], strLength);

	return output;
}

void OsrParser::_CalcGameModeString()
{
	switch (mode)
	{
	case gmStandard: modeString = "Standard"; break;
	case gmTaiko: modeString = "Taiko"; break;
	case gmCTB: modeString = "Catch The Beat"; break;
	case gmMania: modeString = "Mania"; break;
	default: modeString = "Unknown"; break;
	}
}

void OsrParser::_CalcModsVector()
{
	modsVector.clear();

	for (auto i = 0; i < sizeof(modsMask); i++)
	{
		if (IsBitSet(modsMask, i))
		{
			modsVector.push_back(static_cast<ModType>(i));
		}
	}
}

void OsrParser::_CalcModsStringVector()
{
	modsStringVector.clear();

	for (auto i = 0; i < modNames.size(); i++)
	{
		if (IsBitSet(modsMask, i))
		{
			modsStringVector.push_back(modNames[i]);
		}
	}
}

void OsrParser::_CalcLifebar()
{
	string data = _GetStreamString();

	vector<string> chunks;
	SplitString(data, ",", chunks);

	{
		vector<string> values;
		SplitString(chunk, "|", values);

		if (values.size() == LIFE_BAR_POINT_LENGTH)
		{
			lifebar.push_back({
				atoll(values[0].c_str()),
				strtod(values[1].c_str(), nullptr)
			});
		}
	}
}

void OsrParser::_CalcActions()
{
	OsTime msSinceStart = 0;
	uint32_t actionsLength = _GetStreamInteger();
	vector<uint8_t> compressedBytes(actionsLength);
	vector<uint8_t> decompressedBytes;

	_s->read((char*)&compressedBytes[0], actionsLength);
	DecompressLZMA(compressedBytes, decompressedBytes);

	vector<string> chunks;
	SplitString({ decompressedBytes.begin(), decompressedBytes.end() }, ",", chunks);

	for (auto && chunk : chunks)
	{
		vector<string> values;
		SplitString(chunk, "|", values);

		if (actions.size() > 0)
		{
			msSinceStart += actions.back().msSinceLast;
		}

		if (values.size() == ACTION_LENGTH)
		{
			actions.push_back({
				atoll(values[0].c_str()),
				msSinceStart,
				stod(values[1].c_str(), nullptr),
				stod(values[2].c_str(), nullptr),
				(uint8_t)strtoul(values[3].c_str(), nullptr, 10),
			});
		}
	}
}
