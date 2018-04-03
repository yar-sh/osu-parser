////////////////////////////////////////////////////////////////
//                                                            //
//      OsuParser.cpp                                         //
//      HaselLoyance 2017-2018, Unlicense                     //
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

// Goes through istream and reads all data
void OsuParser::Parse()
{
	_s->seekg(0);

	_GetBeatmapVersion();

	_ExtractStructure();

	_s->seekg(0);

	// GENERAL
	OsSection t = _GetSection("General");
	if (t != OsSection({}))
	{
		audioFilename = _ParseSectionField<string>(t, "AudioFilename", "Unknown");
		audioLeadIn = _ParseSectionField<OsTime>(t, "AudioLeadIn", 0);
		previewTime = _ParseSectionField<OsTime>(t, "PreviewTime", 0);
		countdown = _ParseSectionField<bool>(t, "Countdown", false);
		sampleSet = StringToEnum<SampleSet>(_ParseSectionField<string>(t, "SampleSet", "Unknown"), _sampleSetNames);
		// TODO: Implement this https://osu.ppy.sh/help/wiki/Beatmap_Editor/Song_Setup 
		stackLeniency = _ParseSectionField<double>(t, "StackLeniency", 0.7);
		mode = (GameMode)_ParseSectionField<int>(t, "Mode", 0);
		letterboxInBreaks = _ParseSectionField<bool>(t, "LetterboxInBreaks", false);
		widescreenStoryboard = _ParseSectionField<bool>(t, "WidescreenStoryboard", false);
	}

	// EDITOR
	t = _GetSection("Editor");
	if (t != OsSection({}))
	{
		bookmarks = _ParseSectionFieldAsList<OsTime>(t, "Bookmarks", ",");
		distanceSpacing = _ParseSectionField<double>(t, "DistanceSpacing", 1.22);
		beatDivisor = _ParseSectionField<int>(t, "BeatDivisor", 4); //-V112
		gridSize = _ParseSectionField<int>(t, "GridSize", 4); //-V112
		gridLevel = -round(log2(gridSize)) + 6;
		timelineZoom = _ParseSectionField<double>(t, "TimelineZoom", 1.0);
	}

	// METADATA
	t = _GetSection("Metadata");
	if (t != OsSection({}))
	{
		title = _ParseSectionField<string>(t, "Title", "Unknown");
		titleUnicode = _ParseSectionField<string>(t, "TitleUnicode", title);
		artist = _ParseSectionField<string>(t, "Artist", "Unknown");
		artistUnicode = _ParseSectionField<string>(t, "ArtistUnicode", artist);
		creator = _ParseSectionField<string>(t, "Creator", "Unknown");
		version = _ParseSectionField<string>(t, "Version", "Unknown");
		source = _ParseSectionField<string>(t, "Source", "Unknown");
		tags = _ParseSectionFieldAsList<string>(t, "Tags", " ");
		beatmapID = _ParseSectionField<OsInteger>(t, "BeatmapID", 0);
		beatmapSetID = _ParseSectionField<OsInteger>(t, "BeatmapSetID", 0);
	}

	// DIFFICULTY
	t = _GetSection("Difficulty");
	if (t != OsSection({}))
	{
		hpDrainRate = _ParseSectionField<double>(t, "HPDrainRate", 5.0);
		HP = hpDrainRate;
		circleSize = _ParseSectionField<double>(t, "CircleSize", 4.0);
		CS = circleSize;
		overallDifficulty = _ParseSectionField<double>(t, "OverallDifficulty", 6.0);
		OD = overallDifficulty;
		approachRate = _ParseSectionField<double>(t, "ApproachRate", 7.0);
		AR = approachRate;
		sliderMultiplier = _ParseSectionField<double>(t, "SliderMultiplier", 1.4);
		sliderTickRate = _ParseSectionField<double>(t, "SliderTickRate", 1.0);

		preemptMs = (AR < 5.0 || IsEqualDouble(AR, 5.0))
			? (1800.0 - 120.0 * AR)
			: (1950.0 - 150.0 * AR);

		fadeInMs = (AR < 5.0 || IsEqualDouble(AR, 5.0))
			? (1200.0 - 80.0 * AR)
			: (1300.0 - 100.0 * AR);

		circleRadiusPx = 54.4 - 4.48 * CS;

		hitWindow300 = 80.0 - 6.0 * OD;
		hitWindow100 = 140.0 - 8.0 * OD; 
		hitWindow50 = 200.0 - 10.0 * OD;

		requiredRPS = (OD < 5.0 || IsEqualDouble(OD, 5.0))
			? (3.0 - 2.0 / 5.0 * OD)
			: (5.0 - 5.0 / 2.0 + OD / 2.0);
	}

	// EVENTS
	t = _GetSection("Events");
	if (t != OsSection({}))
	{
		for (auto && f : t.second)
		{
			if (Event e = _ParseFieldAsEvent(f); e.type != eUnknown)
			{
				events.push_back(e);
			}
		}
	}

	// TIMING POINTS
	t = _GetSection("TimingPoints");
	if (t != OsSection({}))
	{
		for (auto && f : t.second)
		{
			timingPoints.push_back(_ParseFieldAsTimingPoint(msPerBeats, f));
		}

		lowestBPM = 1234567.0;
		highestBPM = -1234567.0;
		averageBPM = 0.0;

		for (auto && msPerBeat : msPerBeats)
		{
			double bpm = 60000.0 / msPerBeat;

			if (bpm > highestBPM)
			{
				highestBPM = bpm;
			}
			
			if (bpm < lowestBPM)
			{
				lowestBPM = bpm;
			}

			averageBPM += bpm;
		}

		averageBPM /= (double)msPerBeats.size();
	}
	
	// COLORS
	t = _GetSection("Colours");
	if (t != OsSection({}))
	{
		for (auto && f : t.second)
		{
			// Hmmm... so apparently there are "Special coloUrs" for slider
			// TODO (not a priority) them some time 


			colors.push_back(_ParseFieldAsRGBAColor(f));
		}
	}

	// HIT OBJECTS
	t = _GetSection("HitObjects");
	if (t != OsSection({}))
	{
		for (auto && f : t.second)
		{
			hitObjects.push_back(_ParseFieldAsHitObject(f));
		}
	}

	_b.clear();
}

void OsuParser::_GetBeatmapVersion()
{
	string fileVersionString = "";
	getline(*_s, fileVersionString);

	if (size_t len = fileVersionString.find('v'); len != string::npos)
	{
		fileVersionString.erase(0, len + 1);
		formatVersion = stoi(fileVersionString);
		
		return;
	}

	formatVersion = (uint8_t)-1;
}

void OsuParser::_ExtractStructure()
{
	string t;

	while (!_s->eof() && !_s->fail())
	{
		getline(*_s, t);
		TrimString(t);

		if (t.empty())
		{
			continue;
		}

		size_t sz = t.size();

		if (t[0] != '[' || t[sz - 1] != ']')
		{
			continue;
		}

		OsSection section;
		section.first = t.substr(1, sz - 2);

		while (true)
		{
			getline(*_s, t);
			TrimString(t);

			if (t.empty())
			{
				break;
			}

			// Skip commented lines
			if (t[0] == '#' || t.find("//") == 0)
			{
				continue;
			}

			section.second.push_back(t);
		}

		_b.push_back(section);
	}
}

OsSection OsuParser::_GetSection(const std::string & name)
{
	for (auto && section : _b)
	{
		if (section.first == name) 
		{
			return section;
		}
	}

	return {};
}

template<typename T>
T OsuParser::_ParseSectionField(const OsSection & section, const string & fieldName, const T & defaultTo)
{
	for (auto && field : section.second)
	{
		if (field.find(fieldName) == string::npos)
		{
			continue;
		}

		string f = field;
		if (size_t len = f.find(':'); len != string::npos)
		{
			f.erase(0, len + 1);

			// OH BOY, LOOK, THIS RANDOM constexpr OVER HERE MAKES IT WORK
			if constexpr (is_same_v<T, string>)
			{
				return f;
			}
			else
			{
				T t;
				stringstream(f) >> t;
				return t;
			}
		}
	}

	return defaultTo;
}

template<typename T>
vector<T> OsuParser::_ParseSectionFieldAsList(const OsSection & section, const string & fieldName, const string & delim)
{
	for (auto && field : section.second)
	{
		if (field.find(fieldName) == string::npos)
		{
			continue;
		}

		string f = field;
		if (size_t len = f.find(':'); len != string::npos)
		{
			f.erase(0, len + 1);

			vector<string> listValues;
			vector<T> listT;
			SplitString(f, delim, listValues);

			for (auto && val : listValues)
			{
				if constexpr (is_same_v<T, std::string>)
				{
					listT.push_back(val);
				}
				else
				{
					T t;
					stringstream(val) >> t;
					listT.push_back(t);
				}
			}

			return listT;
		}
	}

	return {};
}

Event OsuParser::_ParseFieldAsEvent(const string & field)
{
	string f = field;

	for (size_t i = 0; i < f.size(); i++)
	{
		if (f[i] == ',')
		{
			f[i] = ' ';
		}
	}

	string arg1, arg2, arg3;
	stringstream ss(f);
	ss >> arg1 >> arg2 >> arg3;

	if (arg1 == "0")
	{
		return { eBackground, arg3 };
	}
	else if (arg1 == "2")
	{
		return { eBreak, "", stoll(arg2), stoll(arg3) };
	}
	else if (arg1 == "Video")
	{
		size_t sz = f.find('"') + 1;
		return { eVideo, string(f, sz, f.find_last_of('"') - sz), stoll(arg2) };
	}

	return { eUnknown };
}

TimingPoint OsuParser::_ParseFieldAsTimingPoint(std::vector<double> & msPerBeats, const string & field)
{
	string f = field;

	for (size_t i = 0; i < f.size(); i++)
	{
		if (f[i] == ',')
		{
			f[i] = ' ';
		}
	}

	string arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8;
	stringstream ss(f);
	ss >> arg1 >> arg2 >> arg3 >> arg4 >> arg5 >> arg6 >> arg7 >> arg8;

	TimingPoint tp;

	tp.offset = stoll(arg1);
	tp.msPerBeat = stod(arg2);

	if (tp.msPerBeat > 0)
	{
		tp.adjustedMsPerBeat = tp.msPerBeat;

		msPerBeats.push_back(tp.msPerBeat);
	}
	else
	{
		tp.adjustedMsPerBeat = (tp.msPerBeat / -100.0) * msPerBeats.back();
	}

	tp.beatsPerMeasure = (uint8_t)stoi(arg3);
	tp.sampleSet = (SampleSet)stoi(arg4);
	tp.sampleIndex = (uint8_t)stoi(arg5);
	tp.volume = (uint8_t)stoi(arg6);
	tp.isInheritable = (bool)stoi(arg7);
	tp.isKiaiMode = (bool)stoi(arg8);

	return tp;
}

RGBAColor OsuParser::_ParseFieldAsRGBAColor(const string & field)
{
	string f = field;

	if (size_t len = f.find(':'); len != string::npos)
	{
		f.erase(0, len + 1);
		for (size_t i = 0; i < f.size(); i++)
		{
			if (f[i] == ',')
			{
				f[i] = ' ';
			}
		}

		string arg1, arg2, arg3;
		stringstream ss(f);
		ss >> arg1 >> arg2 >> arg3;

		return {
			(uint8_t)stoi(arg1),
			(uint8_t)stoi(arg2),
			(uint8_t)stoi(arg3),
		};
	}

	return {};
}

HitObject OsuParser::_ParseFieldAsHitObject(const string & field)
{
	string f = field;

	for (size_t i = 0; i < f.size(); i++)
	{
		if (f[i] == ',')
		{
			f[i] = ' ';
		}
	}

	string arg1, arg2, arg3, arg4, arg5;
	stringstream ss(f);
	ss >> arg1 >> arg2 >> arg3 >> arg4 >> arg5;

	HitObject o;
	
	o.x = (uint16_t)stoi(arg1);
	o.y = (uint16_t)stoi(arg2);
	o.time = stoll(arg3);
	o.mask = (HitObjectMask)stoi(arg4);

	if (IsBitSet(o.mask, 0))
	{
		o.type = oCircle;
	}
	else if (IsBitSet(o.mask, 1))
	{
		o.type = oSlider;
	} 
	else if (IsBitSet(o.mask, 3))
	{
		o.type = oSpinner;
	} 
	else if (IsBitSet(o.mask, 4))
	{
		o.type = oHoldNote;
	}

	o.isNewCombo = IsBitSet(o.mask, 2);

	if (o.isNewCombo)
	{
		o.skipComboColors =
			((uint8_t)IsBitSet(o.mask, 4) << 0) |
			((uint8_t)IsBitSet(o.mask, 5) << 1) |
			((uint8_t)IsBitSet(o.mask, 6) << 2);
	}

	o.soundMask = (HitSoundMask)stoi(arg5);

	return o;
}
