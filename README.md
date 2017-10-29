# osu!parser
Parse any osu! related file *(in theory. Right now only \*.osr (osu!replay) files are supported)*
 
 
## Features
- Easy API
- No compilitaion required
- Cross-platform
- [Unlicense](http://unlicense.org)
 
 
## Navigation
- [Requirements](#requirements)
- [Installation](#installation)
- [Code sample](#code-sample)
    - [Parse `*.osr`](#osr)
- [API](#api)
    - [Types](#types)
    - [Utils](#utils)
    - [OsrParser](#OsrParser)
    - [OsuParser](#OsuParser)
- [TODO](#TODO)
 
 
## Requirements
- Has to be linked with [LZMA-SDK](http://www.7-zip.org/sdk.html)
 
 
## Installation
For Microsoft Visual Studio 2017:
1) Add path to `include/` directory as an additional include directory to the project
2) Add all `*.cpp` files from `src/` directory as exesting source files to the project
 
 
## Code sample
#### **osr** (Refer to [osr file format documentation]([osr](https://osu.ppy.sh/help/wiki/osu!_File_Formats/Osr_(file_format)) for details)
```cpp
#include "osu!parser.h"
#include <fstream>

int main()
{
    std::ifstream file("file.osr", std::ios::binary);
    osuParser::OsrParser p(file);
    p.Parse();
    // p.[parsedValues]
}
```
 
 
## API
#### **Types**
* `typedef int64_t`**`OsTime`** representation of time in milliseconds
* `typedef uint8_t`**`OsByte`** osr byte (1 byte)
* `typedef uint16_t`**`OsShort`** osr short (2 bytes)
* `typedef uint32_t`**`OsInteger`** osr integer (4 bytes)
* `typedef uint64_t`**`OsLong`** osr long (8 bytes)
* `typedef OsInteger`**`ModMask`** representation of active mods as a bit mask
* `typedef OsByte`**`InputMask`** representation of active inputsas a bit mask
* `enum`**`InputType`** valid input values, numeric values represent an active bit position in **InputMask**
* `enum`**`ModType`** valid mod values, numeric values represent an active bit position in **ModMask**
* `enum`**`GameMode`** valid game mode values

