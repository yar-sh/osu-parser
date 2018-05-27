## Types
* **OsTime**, typedef *int64_t*, representation of time in milliseconds
* **OsByte**, typedef *uint8_t*, osu BYTE (1 byte)
* **OsShort**, typedef *uint16_t*, osu SHORT (2 bytes)
* **OsInteger**, typedef *uint32_t*, osu INTEGER (4 bytes)
* **OsLong**, typedef *uint64_t*, osu LONG (8 bytes)
* **ModMask**, typedef *OsInteger*, representation of active mods in a replay as a bit mask
* **InputMask**, typedef *OsByte*, representation of active inputs in a replay as a bit mask
* **HitObjectMask**, typedef *OsByte*, representation of hit object data in a beatmap as a bit mask
* **HitSoundMask**, typedef *OsByte*, representation of active sounds in a beatmap as a bit mask
* **InputType**, enum, valid input key values. Enum values represent the bits' number that are active in **InputMask**
* **ModType**, enum, valid mods values. Enum values represent the bits' number that are active in **ModMask**
* **GameMode**, enum, valid game mode values
* **SampleSet**, enum, valid sample set values
* **EventType**, enum, valid events for beatmap [Events] section
* **HitObjectType**, enum, valid hit object values for beatmap [HitObjects] section. Enum values represent the bits' number that are active in **HitObjectMask**
* **HitSoundType**, enum, valid hit sound values. Enum values represent the bits' number that are active in **HitSoundMask**
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
    - *isKiaiMode*, **bool**, whether or not Kiai Time effects are active
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
    - *filename*, **string**, names an audio file in the folder to play instead of sounds from sample sets
* **CurvePoint**, struct, curve point data for sliders:
    - *x*, **uint16_t**, x coordinate describing position of the control point
    - *y*, **uint16_t**, y coordinate describing position of the control point
* **EdgeAddition**, struct, additional sample sets to apply to the circles of the slider:
    - *sampleSet*, **SampleSet**, changes the sample set of the normal hit sound
    - *additionSet*, **SampleSet**, changes the sample set for the other hit sounds (whistle, finish, clap)
* **SpinnerData**, struct, information about spinner hit object:
    - *isSpinner*, **bool**, if the hit object is actually a spinner
    - *duration*, **OsTime**, duration of the spinner
    - *end*, **OsTime**, when the spinner will end
* **SliderData**, struct, information about slider hit object:
    - *isSlider*, **bool**, if the hit object is actually a slider
    - *curvePoints*, **vector\<CurvePoint>**, points of the slider (including initial x and y)
    - *nRepeats*, **uint8_t**, number of slider repeats
    - *length*, **double**, total length of the slider in osu!pixels
    - *duration*, **OsTime**, duration of the slider
    - *end*, **OsTime**, when the slider will end
    - *edgeHitSounds*, **vector\<HitSoundMask>**, hit sounds to apply to the circles of the slider
    - *edgeAdditions*, **vector\<EdgeAddition>**, samples sets to apply to the circles of the slider
    - *adjustedEdgeAdditions*, **vector\<EdgeAddition>**, if for *sampleSet* or *additionSet* in *edgeAdditions* value is **ssAuto** then those values in *adjustedEdgeAdditions* will be inherited from the last related timing point (as it says to do so in format docs)
* **HitObject**, struct, beatmap hit object in [HitObjects] section:
    - *x*, **uint16_t**, x position of the center of the hit object in osu!pixels
    - *y*, **uint16_t**, y position of the center of the hit object in osu!pixels
    - *time*, **OsTime**, number of milliseconds from the beginning of the song, and specifies when the hit begins
    - *mask*, **HitObjectMask**, bitmap specifying the object type and attributes
    - *type*, **HitObjectType**, type of the hit object (from bits 0/1/3/7 in mask)
    - *isNewCombo*, **bool**, whether or not this hit object starts a new combo (from bit 2 in mask)
    - *skipComboColors*, **uint8_t**, number of combo colours to skip (from bits 4-6 in mask). The combo skip value is ignored when the new combo bit is not set
    - *soundMask*, **HitSoundMask**, sounds to play when the hit object is successfully hit
    - *extra*, **Extra**, additional parameters related to the hit sound samples
    - *adjustedExtra*, **Extra**, if for any of *sampleSet*/*additionSet*/*customIndex* in extra value is **ssAuto** then those values in *adjustedExtra* will be inherited from the last related timing point (as it says to do so in format docs)
    - *spinner*, **SpinnerData**, spinner information (if type==oSpinner)
    - *slider*, **SliderData**, slider information (if type==oSlider)
