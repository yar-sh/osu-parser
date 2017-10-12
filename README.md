# osu!parser
Parse any osu! related file *(in theory. Right now only \*.osr (osu!replay) files are supported)*
 
 
## Features
- Easy API
- No compilitaion required
- <a href="http://unlicense.org" target="_blank">Unlicense</a>
 
 
## Navigation
- [Requirements](#requirements)
- [Installation](#installation)
- [Code sample](#code-sample)
    - [Parse `*.osr`](#osr)
- [API](#api)
    - [Types](#api-types)
    - [Utils](#api-utils)
    - [OsString](#api-OsString)
    - [OsrParser](#api-OsrParser)
    - [OsuParser](#api-OsuParser)
- [TODO](#TODO)
 
 
## Requirements
- Has to be linked with [LZMA-SDK](http://www.7-zip.org/sdk.html)
 
 
## Installation
For Microsoft Visual Studio 2017:
1) Add path to `include/` directory as an additional include directory to the project
2) Add all `*.cpp` files from `src/` directory as exesting source files to the project
 
 
## Code sample
#### osr
```cpp
#include "osu!parse.h"
#include <fstream>

int main()
{
    std::ifstream file("file.osr", ios::binary);
    osuParser::OsrParser p(file);
    p.Parse();
    // p.[parsedValues]
}
```

