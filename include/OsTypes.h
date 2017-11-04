////////////////////////////////////////////////////////////////
//                                                            //
//      OsTypes.h                                             //
//      HaselLoyance 2017, Unlicense                          //
//      https://github.com/HaselLoyance/osu-parser            //
//                                                            //
////////////////////////////////////////////////////////////////

#ifndef OSU_PARSER_TYPES_H
#define OSU_PARSER_TYPES_H

#include <stdint.h>
#include <vector>

#define LIFE_BAR_POINT_LENGTH 2
#define ACTION_LENGTH 4

namespace osuParser
{
	// For readability and to follow format docs I'm typedefing all over the place
	// NOTE: OsTime will always be represneted in milliseconds
	typedef int64_t OsTime;
	typedef uint8_t OsByte;
	typedef uint16_t OsShort;
	typedef uint32_t OsInteger;
	typedef uint64_t OsLong;
	typedef OsInteger ModMask;
	typedef OsByte InputMask;

	// Valid keys values. Used in InputMask (OsByte). Enum values represent the bits' number 
	// that are active in InputMask
	enum InputType
	{
		iMouse1 = 0,
		iMouse2 = 1,
		iKey1 = 2,
		iKey2 = 3,
	};

	// Valid mods values. Used in ModMask (OsInteger). Enum values represent the bits' number 
	// that are active in ModMask
	enum ModType
	{
		mNoFail = 0,
		mEasy = 1,
		mNoVideo = 2,
		mHidden = 3,
		mHardRock = 4,
		mSuddenDeath = 5,
		mDoubleTime = 6,
		mRelax = 7,
		mHalfTime = 8,
		mNightcore = 9,
		mFlashlight = 10,
		mAutoplay = 11,
		mSpunOut = 12,
		mRelax2 = 13,
		mPerfect = 14,
		mKey4 = 15,
		mKey5 = 16,
		mKey6 = 17,
		mKey7 = 18,
		mKey8 = 19,
		mkeyMod = 20,
		mFadeIn = 21,
		mRandom = 22,
		mLastMod = 23,
		mTargetPractice = 24,
		mKey9 = 25,
		mCoop = 26,
		mKey1 = 27,
		mKey3 = 28,
		mKey2 = 29,
	};

	// Valid game mode values
	enum GameMode
	{
		gmStandard = 0,
		gmTaiko = 1,
		gmCTB = 2,
		gmMania = 3,
	};

	// A point on the lifebar graph
	//   timePoint, OsTime, time of the point on lifebar graph
	//   life, double, value of the lifebar from 0.0 (empty) to 1.0 (full)
	struct LifeBarPoint
	{
		OsTime timePoint = 0;
		double life = 0.0;
	};

	// A replay action
	//   msSinceLast, OsTime, action time since last action
	//   msSinceStart, OsTime, action time since the start of the song
	//   x, double, x position of the cursor (in osu!pixels)
	//   y, double, y position of the cursor (in osu!pixels)
	//   inputs, InputMask, active inputs in this action
	struct Action
	{
		OsTime msSinceLast = 0;
		OsTime msSinceStart = 0;
		double x = 0.0;
		double y = 0.0;
		InputMask inputs = 0;
	};
}

#endif
