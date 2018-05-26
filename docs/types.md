## Types
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
