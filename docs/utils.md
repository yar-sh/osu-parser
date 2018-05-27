## Utils
* void **SplitString(str, delimiter, output)**: Splits a string into multiple parts with given delimiter
    - *str*, **string**, string to split
    - *delimiter*, **string**, in what places to split the string
    - *output*, **ref vector\<string>**, all parts of the splitted string
* void **TrimString(str)**: Trims (removes whitespace) passed string
    - *str*, **ref string**, string to trim
* void **DecompressLZMA(inBuf, outBuf)**: Decompress LZMA-compressed buffer
    - *inBuf*, **vector\<uint8_t>**, input buffer with LZMA-compressed bytes
    - *outBuf*, **ref vector\<uint8_t>**, output buffer where decompressed data will be written
* bool **IsEqualDouble(a, b)**: Checks to see if two double values are equal
<br>Returns true if both values are equal, false otherwise
    - *a*, **double**, first value to check
    - *b*, **double**, second value to check
* template\<typename **T**>, string **EnumToString(val, names, defaultTo)**: Converts any enumerated type value to the string from associated vector of string values
<br>Returns a string representation of the enumerated type value
    - **\<T>**: enumerated type
    - *val*, **T**, value of the enumerated type
    - *names*, **vector\<string>**, dictionary of string values for enum
    - *defaultTo*, **string**, what to default return value to if there is no associated string value, defaults to *"Unknown"*
* template\<typename **T**>, T **StringToEnum(val, names, defaultTo)**: Converts string value to any enumerated type value via associated vector of string values
<br>Returns a T representation of the string value
    - **\<T>**: enumerated type
    - *val*, **string**, string value
    - *names*, **vector\<string>**, dictionary of string values for enum
    - *defaultTo*, **T**, what to default return value to if there is no associated enumerated type value, defaults to *T(0)*
* const *_modNames*, **vector\<string>**, string names for each available mod
* const *_modeNames*, **vector\<string>**, string names for each available game mode
* const *_sampleSetNames*, **vector\<string>**, string names for each available sample set
* const *_eventNames*, **vector\<string>**, string names for each available beatmap event
* const *_hitSoundNames*, **vector\<string>**, string names for each available hit sound type
* const *_sliderNames*, **vector\<string>**, string names for each available slider type
