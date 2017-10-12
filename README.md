# osu!parser
Parse any osu! related file *(in theory. Right now only \*.osr (osu!replay) are supported)*
 
 
## Features
- Easy API
- No compilitaion required
- [Unlicense](http://unlicense.org)
 
 
## Navigation
- [Installation](#installation)
- [Code sample](#code-sample)
    - [Parse `*.osr`](#osr)
- [API](#API)
    - [Types](#API-types)
    - [Utils](#API-utils)
    - [OsString](#API-OsString)
    - [OsrParser](#API-OsrParser)
- [TODO](#TODO)
 
 
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

