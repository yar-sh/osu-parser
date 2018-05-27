## OsrParser
Please refer to [osr file format documentation](https://osu.ppy.sh/help/wiki/osu!_File_Formats/Osr_(file_format)) for more details
* constructor **OsrParser(stream)**: Constructs an object for parsing "\*.osr" files from input stream
    - *stream*, **istream**, input data stream
* void **Parse()**: Goes through istream and reads all data
<br>After calling **.Parse()** the following data members will be filled and available:
    - *mode*, **GameMode**, game mode of the replay
    - *version*, **OsLong**, version of the game where the replay was created
    - *beatmapHash*, **string**, osu! beatmap MD5 hash
    - *player*, **string**, player name
    - *replayHash*, **string**, osu! replay MD5 hash
    - *n300s*, **OsShort**, number of 300s
    - *n100s*, **OsShort**, number of 100s in standard, 150s in Taiko, 100s in CTB, 200s in mania
    - *n50s*, **OsShort**, number of 50s in standard, small fruit in CTB, 50s in mania
    - *nGekis*, **OsShort**, number of Gekis in standard, Max 300s in mania
    - *nKatus*, **OsShort**, number of Katus in standard, 100s in mania
    - *nMisses*, **OsShort**, number of misses
    - *score*, **OsInteger**, total score displayed on the score report
    - *combo*, **OsShort**, greatest combo displayed on the score report
    - *isFC*, **bool**, perfect/full combo (true = no misses and no slider breaks and no early finished sliders)
    - *modsMask*, **ModMask**, mods used in a mask form
    - *modsVector*, **vector\<ModType>**, mods used in a vector of ModType
    - *modsStringVector*, **vector\<string>**, mods used in a vector of strings
    - *lifebar*, **vector\<LifeBarPoint>**, life bar graph. Represents the amount of life you have at the given time
    - *timestamp*, **OsShort**, [time stamp](https://msdn.microsoft.com/en-us/library/system.datetime.ticks(v=vs.110).aspx)
    - *actions*, **vector\<Action>**, vector of replay actions
    - *unknown*, **OsLong**, last 4 bytes of replay file - unknown, usually 00 00 00 00

