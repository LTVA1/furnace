# effect list

some of the effect numbers are taken from ProTracker / FastTracker 2.

however, effects are continuous (unless specified), which means you only need to type it once and then stop it with an effect value of `00` or no effect value at all.

## volume

- `0Axy`: **Volume slide.**
  - if `x` is 0 then this slides volume down by `y` each tick.
  - if `y` is 0 then this slides volume up by `x` each tick.
- `FAxy`: **Fast volume slide.** same as `0Axy` above but 4× faster.
- `F3xx`: **Fine volume slide up.** same as `0Ax0` but 64× slower.
- `F4xx`: **Fine volume slide down.** same as `0A0x` but 64× slower.
- `F8xx`: **Single tick volume slide up.** adds `xx` to volume on first tick only.
- `F9xx`: **Single tick volume slide down.** subtracts `xx` from volume on first tick only.
  - ---
- `D8xx`: **Set volume slide bottom boundary.**
  - the default is 0.
- `D9xx`: **Set volume slide top boundary.**
  - the default is the channel's maximum volume.
- `DCxx`: **Delayed mute.** sets volume to 0 after `xx` ticks.
  - ---
- `07xy`: **Tremolo.** changes volume to be "wavy" with a sine LFO. `x` is the speed. `y` is the depth.
  - tremolo is downward only.
  - maximum tremolo depth is -60 volume steps.

## pitch

- `E5xx`: **Set pitch.** `00` is -1 semitone, `80` is base pitch, `FF` is nearly +1 semitone.
- `01xx`: **Pitch slide up.**
- `02xx`: **Pitch slide down.**
- `F1xx`: **Single tick pitch slide up.**
- `F2xx`: **Single tick pitch slide down.**
  - ---
- `03xx`: **Portamento.** slides the currently playing note's pitch toward the new note. `x` is the slide speed.
  - a note _must_ be present with this effect for it to work.
  - the effect stops automatically when it reaches the new note.
- `E1xy`: **Note slide up.** `x` is the speed, while `y` is how many semitones to slide up.
- `E2xy`: **Note slide down.** `x` is the speed, while `y` is how many semitones to slide down.
  - ---
- `EAxx`: **Toggle legato.** while on, new notes instantly change the pitch of the currently playing sound instead of starting it over.
- `E6xy`: **Delayed note transpose.** (works like `Txy` in FamiTracker) instantly transposes note up or down after certain number of ticks. `x` dictates the delay and the direction of transpose: when `x` is between `0` and `7` note is transposed *up* after `x` ticks. when `x` is between `8` and `F` note is transposed *down* after `(x - 7)` ticks. so the MSB of `x` dictates the direction. `y` is how many semitones to transpose up/down.
- `E8xy`: **Delayed note transpose up.** transposes note up by `y` semitones after `x` ticks.
- `E9xy`: **Delayed note transpose down.** transposes note down by `y` semitones after `x` ticks.
- `00xy`: **Arpeggio.** this effect produces a rapid cycle between the current note, the note plus `x` semitones and the note plus `y` semitones.
- `E0xx`: **Set arpeggio speed.** this sets the number of ticks between arpeggio values. default is 1.
  - ---
- `04xy`: **Vibrato.** makes the pitch oscillate. `x` is the speed, while `y` is the depth.
  - maximum vibrato depth is ±1 semitone.
- `E3xx`: **Set vibrato shape.** `xx` may be one of the following:
  - `00`: sine (default)
  - `01`: sine (upper portion only)
  - `02`: sine (lower portion only)
  - `03`: triangle
  - `04`: ramp up
  - `05`: ramp down
  - `06`: square
  - `07`: random
  - `08`: square (up)
  - `09`: square (down)
  - `0a`: half sine (up)
  - `0b`: half sine (down)
- `E4xx`: **Set vibrato range** in 1/16th of a semitone. 

## panning

not all chips support these effects.

- `08xy`: **Set panning.** changes stereo volumes independently. `x` is the left channel and `y` is the right one.
- `88xy`: **Set rear panning.** changes rear channel volumes independently. `x` is the rear left channel and `y` is the rear right one.
- `81xx`: **Set volume of left channel** (from `00` to `FF`).
- `82xx`: **Set volume of right channel** (from `00` to `FF`).
- `89xx`: **Set volume of rear left channel** (from `00` to `FF`).
- `8Axx`: **Set volume of rear right channel** (from `00` to `FF`).
  - ---
- `80xx`: **Set panning (linear).** this effect behaves more like other trackers:
  - `00` is left.
  - `80` is center.
  - `FF` is right.
  - ---
- `83xy`: **Panning slide.**
  - if `y` is 0 then this pans to the left by `x` each tick.
  - if `x` is 0 then this pans to the right by `y` each tick.
  - be noted that panning macros override this effect.
- `84xy`: **Panbrello.** makes panning oscillate. `x` is the speed, while `y` is the depth.
  - be noted that panning macros override this effect.

## time

- `09xx`: **Set speed/groove.** if no grooves are defined, this sets speed. if alternating speeds are active, this sets the first speed.
- `0Fxx`: **Set speed 2.** during alternating speeds or a groove, this sets the second speed.
  - ---
- `Cxxx`: **Set tick rate.** changes tick rate to `xxx` Hz (ticks per second).
  - `xxx` may be from `000` to `3FF`.
- `F0xx`: **Set BPM.** changes tick rate according to beats per minute. range is `01` to `FF`.
  - ---
- `FDxx`: **Set virtual tempo numerator.** sets the virtual tempo's numerator to the effect value.
- `FExx`: **Set virtual tempo denominator.** sets the virtual tempo's denominator to the effect value.
  - ---
- `0Bxx`: **Jump to order.** `x` is the order to play after the current row.
  - this marks the end of a loop with order `x` as the loop start.
- `0Dxx`: **Jump to next pattern.** skips the current row and remainder of current order. `x` is the row at which to start playing the next pattern.
  - this can be used to shorten the current order as though it had a different pattern length.
- `FFxx`: **Stop song.** stops playback and ends the song. `x` is ignored.

## note

- `0Cxx`: **Retrigger.** repeats current note every `xx` ticks.
  - this effect is not continuous; it must be entered on every row.
- `ECxx`: **Note cut.** triggers note off after `xx` ticks. this triggers key off in FM/hardware envelope chips, or cuts note otherwise.
- `EDxx`: **Note delay.** delays note by `xx` ticks.
- `FCxx`: **Note release.** (works like `Lxx` in FamiTracker) releases current note after `xx` ticks. this releases macros and triggers key off in FM/hardware envelope chips.
- `E7xx`: **Macro release.** releases macros after `xx` ticks. this does not trigger key off.

## sample offset

these effects make the current playing sample on the channel jump to a specific position.
only some chips support this effect.

sample offset is a 24-bit (3 byte) number.

- `90xx`: **Set sample offset (first byte).**
- `91xx`: **Set sample offset (second byte).**
- `92xx`: **Set sample offset (third byte).**

you may use these effects simultaneously in a row.

if you do not set a byte, its last value will be used.

in previous versions of Furnace a `9xxx` effect existed which set the sample position to `$xxx00` (`xxx` was effectively multiplied by 256). this maps to `920x 91xx` in current Furnace.

## other

- `EBxx`: **Set LEGACY sample mode bank.** selects sample bank. used only for compatibility.
  - does not apply on Amiga.
- `EExx`: **Send external command.**
  - this effect is currently incomplete.
- `F5xx`: **Disable macro.**
- `F6xx`: **Enable macro.**
- `F7xx`: **Restart macro.**
  - see macro table at the end of this document for possible values.

additionally, [each chip has its own effects](../7-systems/README.md).

## macro table

 ID  | macro
-----|-----------------------------
`00` | volume
`01` | arpeggio
`02` | duty/noise
`03` | waveform
`04` | pitch
`05` | extra 1
`06` | extra 2
`07` | extra 3
`08` | extra A (ALG)
`09` | extra B (FM)
`0A` | extra C (FMS)
`0B` | extra D (AMS)
`0C` | panning left
`0D` | panning right
`0E` | phase reset
`0F` | extra 4
`10` | extra 5
`11` | extra 6
`12` | extra 7
`13` | extra 8
`14` | extra 9
`15` | extra 10
`16` | extra 11
`17` | extra 12
`18` | extra 13
`19` | extra 14
`1A` | extra 15
`1B` | extra 16
`1C` | extra 17
`1D` | extra 18
`0E` | extra 19
`1F` | extra 20
|    | **operator 1 macros**
`20` | AM
`21` | AR
`22` | DR
`23` | MULT
`24` | RR
`25` | SL
`26` | TL
`27` | DT2
`28` | RS
`29` | DT
`2A` | D2R
`2B` | SSG-EG
`2C` | DAM
`2D` | DVB
`2E` | EGT
`2F` | KSL
`30` | SUS
`31` | VIB
`32` | WS
`33` | KSR
`34` | extra 1
`35` | extra 2
`36` | extra 3
`37` | extra 4
`38` | extra 5
`39` | extra 6
`3A` | extra 7
`3B` | extra 8
`3C` | extra 9
`3D` | extra 10
`3E` | extra 11
`3F` | extra 12
`40` | **operator 2 macros**
`60` | **operator 3 macros**
`80` | **operator 4 macros**

the interpretation of duty, wave and extra macros depends on chip/instrument type:

ex | FM     | OPM       | OPZ       | OPLL  | AY-3-8910  | AY8930     | Lynx     | C64          |
---|--------|-----------|-----------|-------|------------|------------|----------|--------------|
 D | NoiseF | NoiseFreq |           |       | NoiseFreq  | NoiseFreq  | Duty/Int | Duty         |
 W |        | LFO Shape | LFO Shape | Patch | Waveform   | Waveform   |          | Waveform     |
 1 |        | AMD       | AMD       |       |            | Duty       |          | FilterMode   |
 2 |        | PMD       | PMD       |       | Envelope   | Envelope   |          | Resonance    |
 3 | LFOSpd | LFO Speed | LFO Speed |       | AutoEnvNum | AutoEnvNum |          | Filt. on/off |
 A | ALG    | ALG       | ALG       |       | AutoEnvDen | AutoEnvDen |          | Cutoff       |
 B | FB     | FB        | FB        |       |            | Noise AND  |          |              |
 C | FMS    | FMS       | FMS       |       |            | Noise OR   |          |              |
 D | AMS    | AMS       | AMS       |       |            |            |          |              |
 4 | OpMask | OpMask    |           |       |  Raw freq. |  Raw freq. |          | Special      |
 5 |        |           | AMD2      |       |Raw env. fr.|Raw env. fr.|          | Attack       |
 6 |        |           | PMD2      |       |            |            |          | Decay        |
 7 |        |           | LFO2Speed |       |            |            |          | Sustain      |
 8 |        |           | LFO2Shape |       |            |            |          | Release      |

ex | SAA1099  | X1-010     | Namco 163  | FDS       | Sound Unit | ES5506    | MSM6258  |
---|----------|------------|------------|-----------|------------|-----------|----------|
 D |          |            | Wave Pos   |           | Duty       | Filt Mode | FreqDiv  |
 W | Waveform | Waveform   | Waveform   | Waveform  | Waveform   |           |          |
 1 | Envelope | EnvMode    | WaveLen    | Mod Depth | Cutoff     | Filter K1 | ClockDiv |
 2 |          | Envelope   | WaveUpdate | Mod Speed | Resonance  | Filter K2 |          |
 3 |          | AutoEnvNum | WaveLoad W |           | Control    | Env Count |          |
 A |          | AutoEnvDen | WaveLoad P |           |            | Control   |          |
 B |          |            | WaveLoad L |           |            |           |          |
 C |          |            | WaveLoad T |           |            |           |          |
 D |          |            |            |           |            |           |          |
 4 |          |            |            |           | PResetTime | EnvRampL  |          |
 5 |          |            |            |           |            | EnvRampR  |          |
 6 |          |            |            |           |            | EnvRampK1 |          |
 7 |          |            |            |           |            | EnvRampK2 |          |
 8 |          |            |            |           |            | Env Mode  |          |

ex | QSound       | SNES      | MSM5232   |    ESFM    |   ES5503    |    DAVE     |     TIA     |
---|--------------|-----------|-----------|------------|-------------|-------------|-------------|
 D | Echo Level   | NoiseFreq | GroupCtrl | OP4NoiMode |  Osc. mode  |  NoiseFreq  |             |
 W |              | Waveform  |           |  Waveform  |  Waveform   |  Waveform   |             |
 1 | EchoFeedback | Special   | GroupAtk  |            |  Wave pos   |   Control   |  Raw freq.  |
 2 | Echo Length  | Gain      | GroupDec  |            | Osc. output |  Raw freq.  |             |
 3 |              |           | Noise     |            |             |             |             |
 A |              |           |           |            |             |             |             |
 B |              |           |           |            |             |             |             |
 C |              |           |           |            |             |             |             |
 D |              |           |           |            |             |             |             |
 4 |              |           |           |            |             |             |             |
 5 |              |           |           |            |             |             |             |
 6 |              |           |           |            |             |             |             |
 7 |              |           |           |            |             |             |             |
 8 |              |           |           |            |             |             |             |

ex |   SID2       |    POKEY     |
---|--------------|--------------|
 D | Duty         |    AUDCTL    |
 W | Waveform     |   Waveform   |
 1 | FilterMode   |   Raw freq.  |
 2 | Resonance    |              |
 3 | Filt. on/off |              |
 A | Cutoff       |              |
 B |              |              |
 C |              |              |
 D |              |              |
 4 | Special      |              |
 5 | Attack       |              |
 6 | Decay        |              |
 7 | Sustain      |              |
 8 | Release      |              |
 9 | Env. reset   |              |
10 | Noise mode   |              |
11 | Wave mix mode|              |