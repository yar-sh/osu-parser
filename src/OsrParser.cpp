////////////////////////////////////////////////////////////////
//                                                            //
//      OsrParser.cpp                                         //
//      HaselLoyance 2017, Unlicensed                         //
//      https://github.com/HaselLoyance/osu-parser            //
//                                                            //
////////////////////////////////////////////////////////////////

#include "OsrParser.h"

using namespace std;
using namespace osuParser;

// Creates a parser from ifstream
OsrParser::OsrParser(ifstream * filestream)
{
	_s = filestream;
	mode = gmStandard;
	version = 0;
	player = "";
	beatmapHash = "";
	replayHash = "";
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
	_s->read(reinterpret_cast<char *>(&b), sizeof(uint16_t));
	return b;
}

uint32_t OsrParser::_GetStreamInteger()
{
	uint32_t b = 0;
	_s->read(reinterpret_cast<char *>(&b), sizeof(uint32_t));
	return b;
}

uint64_t OsrParser::_GetStreamLong()
{
	uint64_t b = 0;
	_s->read(reinterpret_cast<char *>(&b), sizeof(uint64_t));
	return b;
}

uint64_t OsrParser::_GetStreamULEB128()
{
	uint64_t result = 0;
	unsigned shift = 0;

	while (true)
	{
		uint8_t byte = _s->get();

		result |= (byte & ~(1 << 7)) << shift;

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

	for (int i = 0; i < sizeof(modsMask); i++)
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

	if (IsBitSet(modsMask, 0))
	{
		modsStringVector.push_back("NoFail");
	}

	if (IsBitSet(modsMask, 1))
	{
		modsStringVector.push_back("Easy");
	}

	if (IsBitSet(modsMask, 2))
	{
		modsStringVector.push_back("NoVideo");
	}

	if (IsBitSet(modsMask, 3))
	{
		modsStringVector.push_back("Hidden");
	}

	if (IsBitSet(modsMask, 4))
	{
		modsStringVector.push_back("HardRock");
	}

	if (IsBitSet(modsMask, 5))
	{
		modsStringVector.push_back("SuddenDeath");
	}

	if (IsBitSet(modsMask, 6))
	{
		modsStringVector.push_back("DoubleTime");
	}

	if (IsBitSet(modsMask, 7))
	{
		modsStringVector.push_back("Relax");
	}

	if (IsBitSet(modsMask, 8))
	{
		modsStringVector.push_back("HalfTime");
	}

	if (IsBitSet(modsMask, 9))
	{
		modsStringVector.push_back("Nightcore");
	}

	if (IsBitSet(modsMask, 10))
	{
		modsStringVector.push_back("Flashlight");
	}

	if (IsBitSet(modsMask, 11))
	{
		modsStringVector.push_back("Autoplay");
	}

	if (IsBitSet(modsMask, 12))
	{
		modsStringVector.push_back("SpunOut");
	}

	if (IsBitSet(modsMask, 13))
	{
		modsStringVector.push_back("Relax2");
	}

	if (IsBitSet(modsMask, 14))
	{
		modsStringVector.push_back("Perfect");
	}

	if (IsBitSet(modsMask, 15))
	{
		modsStringVector.push_back("Key4");
	}

	if (IsBitSet(modsMask, 16))
	{
		modsStringVector.push_back("Key5");
	}

	if (IsBitSet(modsMask, 17))
	{
		modsStringVector.push_back("Key6");
	}

	if (IsBitSet(modsMask, 18))
	{
		modsStringVector.push_back("Key7");
	}

	if (IsBitSet(modsMask, 19))
	{
		modsStringVector.push_back("Key8");
	}

	if (IsBitSet(modsMask, 20))
	{
		modsStringVector.push_back("FadeIn");
	}

	if (IsBitSet(modsMask, 21))
	{
		modsStringVector.push_back("Random");
	}

	if (IsBitSet(modsMask, 22))
	{
		modsStringVector.push_back("LastMod");
	}

	if (IsBitSet(modsMask, 23))
	{
		modsStringVector.push_back("TargetPractice");
	}

	if (IsBitSet(modsMask, 24))
	{
		modsStringVector.push_back("Key9");
	}

	if (IsBitSet(modsMask, 25))
	{
		modsStringVector.push_back("Coop");
	}

	if (IsBitSet(modsMask, 26))
	{
		modsStringVector.push_back("Key1");
	}

	if (IsBitSet(modsMask, 27))
	{
		modsStringVector.push_back("Key3");
	}

	if (IsBitSet(modsMask, 28))
	{
		modsStringVector.push_back("Key2");
	}
}

void OsrParser::_CalcLifebar()
{
	OsString data = _GetStreamString();

	vector<OsString> chunks;
	data.GetChunks(chunks);

	for (auto i = 0; i < chunks.size(); i++)
	{
		string * values = new string[2];
		chunks[i].GetChunkValues(values);

		lifebar.push_back({
			atoll(values[0].c_str()),
			strtod(values[1].c_str(), nullptr)
		});

		delete[] values;
	}
}


void OsrParser::_CalcActions()
{
	uint32_t actionsLength = _GetStreamInteger();
	vector<uint8_t> compressedBytes(actionsLength);
	vector<uint8_t> decompressedBytes;

	_s->read((char*)&compressedBytes[0], actionsLength);
	DecompressLZMA(compressedBytes, decompressedBytes);

	vector<OsString> chunks;
	OsString(string(decompressedBytes.begin(), decompressedBytes.end())).GetChunks(chunks);

	for (auto i = 0; i < chunks.size(); i++)
	{
		string * values = new string[4];
		chunks[i].GetChunkValues(values);

		actions.push_back({
			atoll(values[0].c_str()),
			stod(values[1].c_str(), nullptr),
			stod(values[2].c_str(), nullptr),
			(uint8_t)strtoul(values[3].c_str(), nullptr, 10),
		});

		delete[] values;
	}
}

OsrParser::~OsrParser() {};