## Utils
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
