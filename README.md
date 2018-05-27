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
- [Documentation](#documentation)
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
 
 
## Documentation
For detailed markdown description of available methods and fields, see [documentation](docs).
 
 
## TODO
- Parse .db files
- Test other game modes for \*.osr and \*.osu
