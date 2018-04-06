# оsu!рarsеr
Parse any osu! related file *(in theory. Right now only \*.osr (replays) and \*.osu (beatmaps) files are supported)*  
 
 
## Features
- Easy API
- No compilation required
- Cross-platform
- [Unlicense](http://unlicense.org)
 
 
## Navigation
- [Status](#status)
- [Requirements](#requirements)
- [Installation](#installation)
- [Code sample](#code-sample)
    - [Parse `*.osr`](#osr)
    - [Parse `*.osu`](#osu)
- [API](#api)
    - [Types](#types)
    - [Utils](#utils)
    - [OsrParser](#osrparser)
    - [OsuParser](#osuparser)
- [TODO](#todo)
 
  
## Status
- osr: Tested with valid osu!standard replays
- osu: Tested (but not thoroughly) with valid osu!standard beatmaps
- WARNING: In all other cases behavior might be unpredictable
 
 
## Requirements
- Has to be linked and compiled with [LZMA-SDK](http://www.7-zip.org/sdk.html)
 
 
## Installation
For Microsoft Visual Studio 2017:
1) Add path to `include/` directory as an additional include directory to the project
2) Add all `*.cpp` files from `src/` directory as existing source files to the project
 
 
## Code sample
#### **osr**
```cpp
#include "osu!parser.h"
#include <fstream>

int main()
{
    std::ifstream file("replay.osr", std::ios::binary);
    osuParser::OsrParser p(file);
    p.Parse();
    // p.<parsedValues>
}
```
(Refer to [osr file format documentation](https://osu.ppy.sh/help/wiki/osu!_File_Formats/Osr_(file_format)) for details)
#### **osu**
```cpp
#include "osu!parser.h"
#include <fstream>

int main()
{
    std::ifstream file("beatmap.osu");
    osuParser::OsuParser p(file);
    p.Parse();
    // p.<parsedValues>
}
```
(Refer to [osu file format documentation](https://osu.ppy.sh/help/wiki/osu!_File_Formats/Osu_(file_format)) for details)
 
 
## API
#### **Types**
* **OsTime**, typedef *int64_t*, representation of time in milliseconds
* **OsByte**, typedef *uint8_t*, osr byte (1 byte)
* **OsShort**, typedef *uint16_t*, osr short (2 bytes)
* **OsInteger**, typedef *uint32_t*, osr integer (4 bytes)
* **OsLong**, typedef *uint64_t*, osr long (8 bytes)
* **ModMask**, typedef *OsInteger*, representation of active mods as a bit mask
* **InputMask**, typedef *OsByte*, representation of active inputs as a bit mask
* **HitObjectMask**, typedef *OsByte*, representation of hit object data as a bit mask
* **HitSoundMask**, typedef *OsByte*, representation of active sounds as a bit mask
* **InputType**, enum, valid key values. Enum values represent the bits' number that are active in **InputMask**
* **ModType**, enum, valid mods values. Enum values represent the bits' number that are active in **ModMask**
* **GameMode**, enum, valid game mode values
* **SampleSet**, enum, valid sample set values
* **EventType**, enum, valid events for beatmap [Events] section
* **HitObjectType**, enum, valid hit object values for beatmap [HitObjects] section. Enum values represent the bits' number that are active in **HitObjectMask**
* **HitSoundType**, enum, valid hit sounds values. Enum values represent the bits' number that are active in **HitSoundMask**
* **SliderType**, enum, valid slider types for slider hit objects
* **LifeBarPoint**, struct, point on the lifebar graph:
    - *time*, **OsTime**, time of the point on lifebar graph
    - *life*, **double**, value of the lifebar from 0.0 (empty) to 1.0 (full)
* **Action**, struct, replay action:
    - *sinceLast*, **OsTime**, action time since last action
    - *sinceStart*, **OsTime**, action time since the start of the song
    - *x*, **double**, x position of the cursor in osu!pixels
    - *y*, **double**, y position of the cursor in osu!pixels
    - *inputs*, **InputMask**, active inputs in this action
* **Event**, struct, beatmap event in [Events] section:
    - *type*, **EventType**, type of the event
    - *file*, **string**, name of the file that is specified for event
    - *begin*, **OsTime**, when event should begin
    - *end*, **OsTime**, when event should end
* **TimingPoint**, struct, beatmap timing point in [TimingPoints] section:
    - *offset*, **OsTime**, when the timing point starts
    - *msPerBeat*, **double**, defines the duration of one beat. When positive, it is faithful to its name. When negative, it is a percentage of previous non-negative milliseconds per beat, which is stored in adjustedMsPerBeat
    - *adjustedMsPerBeat*, **double**, adjusted duration of each bit based on the sign of msPerBeat
    - *beatsPerMeasure*, **uint8_t**, number of beats in a measure
    - *sampleSet*, **SampleSet**, default sample set for hit objects
    - *sampleIndex*, **uint8_t**, default custom index
    - *isInheritable*, **bool**, if the timing point can be inherited from
    - *KiaiMode*, **bool**, whether or not Kiai Time effects are active
* **RGBAColor**, struct, beatmap combo color in [Colours] section:
    - *r*, **uint8_t**, value of red channel
    - *g*, **uint8_t**, value of green channel
    - *b*, **uint8_t**, value of blue channel
    - *a*, **uint8_t**, value of alpha channel
* **Extra**, struct, additional parameters related to the hit sound samples:
    - *sampleSet*, **SampleSet**, changes the sample set of the normal hit sound
    - *additionSet*, **SampleSet**, changes the sample set for the other hit sounds (whistle, finish, clap)
    - *customIndex*, **uint8_t**, custom sample set index
    - *volume*, **uint8_t**, volume of the sample
    - *filename*, **string**,  names an audio file in the folder to play instead of sounds from sample sets
#### **Utils**
* void **SplitString(str, delimiter, output)**: Splits a string into multiple parts with given delimiter
    - *str*, **string**, string to split
    - *delimiter*, **string**, in what places to split the string
    - *output*, **ref vector\<string>**, all parts of the splitted string
* bool **IsInputActive(inputs, input)**: Checks if input is active in an input mask
<br>Returns true if input is active in an input mask, false otherwise
    - *inputs*, **InputMask**, inputs mask
    - *input*, **InputType**, input to check if is active
* bool **IsModActive(mods, mod)**: Checks if mod is active in a mod mask
<br>Returns true if mod is active in a mod mask, false otherwise
    - *mods*, **ModMask**, mods mask
    - *mod*, **ModType**, mod to check if is active
* void **DecompressLZMA(inBuf, outBuf)**: Decompress LZMA-compressed buffer
    - *inBuf*, **vector\<uint8_t>**, input buffer with LZMA-compressed bytes
    - *outBuf*, **ref vector\<uint8_t>**, output buffer where decompressed data will be written
* string **ModeToString(mode)**: String value of the game mode name
<br>Returns a string representation of the game mode value
    - *mode*, **GameMode**, value of the game mode
* string **ModToString(mod)**: String value of the mod name
<br>Returns a string representation of the mod value
    - *mod*, **ModType**, mod value
* const *_modNames*, **vector\<string>**, string names for each of the available mods
* const *_modeNames*, **vector\<string>**, string names for each of the game modes
#### **OsrParser**
* constructor **OsrParser(stream)**: Constructs an object for parsing "*.osr" files from input stream
    - *stream*, **\*istream**, input data stream
* void **Parse()**: Goes through input data stream and collects/processes data
<br>After calling **.Parse()** the following data members will be filled and available:
    - *mode*, **GameMode**, game mode of the replay
    - *modeString*, **string**, game mode of the replay (in string form)
    - *version*, **OsLong**, version of the game where the replay was created
    - *beatmapHash*, **string**, osu! beatmap MD5 hash
    - *player*, **string**, Player name
    - *replayHash*, **string**, game mode of the replay
    - *n300s*, **OsShort**, number of 300s
    - *n100s*, **OsShort**, number of 100s in standard, 150s in Taiko, 100s in CTB, 200s in mania
    - *n50s*, **OsShort**, number of 50s in standard, small fruit in CTB, 50s in mania
    - *nGekis*, **OsShort**, number of Gekis in standard, Max 300s in mania
    - *nKatus*, **OsShort**, number of Katus in standard, 100s in mania
    - *nMisses*, **OsShort**, number of misses
    - *score*, **OsInteger**, total score displayed on the score report
    - *combo*, **OsShort**, greatest combo displayed on the score report
    - *isFC*, **bool**, perfect/full combo (1 = no misses and no slider breaks and no early finished sliders)
    - *modsMask*, **ModMask**, mods used. See IsModActive and ModType
    - *modsVector*, **vector\<ModType>**, mods used in a vector of ModType
    - *modsStringVector*, **vector\<string>**, mods used in a vector of strings
    - *lifebar*, **vector\<LifeBarPoint>**, life bar graph. Represents the amount of life you have at the given time
    - *timestamp*, **OsShort**, [time stamp](https://msdn.microsoft.com/en-us/library/system.datetime.ticks(v=vs.110).aspx)
    - *actions*, **vector\<Action>**, vector of actions. See Action struct
    - *unknown*, **OsLong**, last 4 bytes of replay file - unknown
#### **OsuParser**
*WIP*

## TODO
- Parse .db files
- Test other game modes for \*.osr and \*.osu
