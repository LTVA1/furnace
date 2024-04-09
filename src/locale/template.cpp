#include <map>
#include <string>
#include "locale.h"

#include "template.h"

int getPluralIndexTemplate(int n)
{
    return n > 1 ? 1 : 0;
    //here you can provide plural forms indices based on the integer.
    //you can find one-liners for common languages here:
    //https://www.gnu.org/software/gettext/manual/html_node/Plural-forms.html
    //these would need some adaptation to work in this code
    //see russian.cpp file for example of adapted statement
}

static const ImGuiLocEntry GLocalizationEntriesTmTM[] =
{
    { ImGuiLocKey_VersionStr,           "=Dear ImGui " IMGUI_VERSION " (" IM_STRINGIFY(IMGUI_VERSION_NUM) ")" },
    { ImGuiLocKey_TableSizeOne,         "=Size column to fit###SizeOne"          },
    { ImGuiLocKey_TableSizeAllFit,      "=Size all columns to fit###SizeAll"     },
    { ImGuiLocKey_TableSizeAllDefault,  "=Size all columns to default###SizeAll" },
    { ImGuiLocKey_TableResetOrder,      "=Reset order###ResetOrder"              },
    { ImGuiLocKey_WindowingMainMenuBar, "=(Main menu bar)"                       },
    { ImGuiLocKey_WindowingPopup,       "=(Popup)"                               },
    { ImGuiLocKey_WindowingUntitled,    "=(Untitled)"                            },
    { ImGuiLocKey_DockingHideTabBar,    "=Hide tab bar###HideTabBar"             },
};

class DivLocale;

void DivLocale::addTranslationsTemplate()
{
    ImGui::LocalizeRegisterEntries(GLocalizationEntriesTmTM, IM_ARRAYSIZE(GLocalizationEntriesTmTM));

    strings["<nothing>##test"].plurals[0] = "=<nothing>##test";

    // everything in a string after the ## or ### must remain as is
    //   unless it's one of these purely-for-translation codes
    // example: "Sparkles!##sgab1" means the second instance of "Sparkles!"
    //   in `src/gui/about.cpp`.

    //progress tracker
    //   code  is the hashcode prefix (derived from path)

    //   sg**  src/gui/
    //   sgab  src/gui/about.cpp
    //   sgch  src/gui/channels.cpp
    //   sgco  src/gui/chanOsc.cpp
    //   sgcl  src/gui/clock.cpp
    //   sgcp  src/gui/commandPalette.cpp
    //   sgcf  src/gui/compatFlags.cpp
    //   sgcs  src/gui/csPlayer.cpp
    //   sgdl  src/gui/dataList.cpp
    //   sgda  src/gui/doAction.cpp
    //   sgec  src/gui/editControls.cpp
    //   sged  src/gui/editing.cpp
    //   sgef  src/gui/effectList.cpp
    //   sgeo  src/gui/exportOptions.cpp
    //   sgfd  src/gui/fileDialog.cpp
    //   sgfr  src/gui/findReplace.cpp
    //   sgfm  src/gui/fmPreview.cpp
    //   sgfo  src/gui/fonts.cpp
    //   sggd  src/gui/gradient.cpp
    //   sggv  src/gui/grooves.cpp
    //   sggu  src/gui/gui.cpp
    //   sggc  src/gui/guiConst.cpp
    //   sgim  src/gui/image.cpp
    //   sgie  src/gui/insEdit.cpp
    //   sgmm  src/gui/midiMap.cpp
    //   sgmx  src/gui/mixer.cpp
    //   sgns  src/gui/newSong.cpp
    //   sgme  src/gui/memory.cpp
    //   sgor  src/gui/orders.cpp
    //   sgos  src/gui/osc.cpp
    //   sgpm  src/gui/patManager.cpp
    //   sgpa  src/gui/pattern.cpp
    //   sgpi  src/gui/piano.cpp
    //   sgpr  src/gui/presets.cpp
    //   sgrv  src/gui/regView.cpp
    //  sgsed  src/gui/sampleEdit.cpp
    //   sgse  src/gui/settings.cpp
    //   sgsi  src/gui/songInfo.cpp
    //   sgsn  src/gui/songNotes.cpp
    //   sgsp  src/gui/speed.cpp
    //   sgst  src/gui/stats.cpp
    //   sgss  src/gui/subSongs.cpp
    //   sgsc  src/gui/sysConf.cpp
    //   sgsm  src/gui/sysManager.cpp
    //   sgsa  src/gui/sysPartNumber.cpp
    //   sgsp  src/gui/sysPicker.cpp
    //   sgut  src/gui/util.cpp
    //   sgvm  src/gui/volMeter.cpp
    //   sgwe  src/gui/waveEdit.cpp
    //   sgxy  src/gui/xyOsc.cpp

    //   sgab  src/gui/about.cpp

    strings["About Furnace###About Furnace"].plurals[0] = "=About Furnace###About Furnace";

    strings["and Furnace-B developers##sgab"].plurals[0] = "=and Furnace-B developers";
    strings["are proud to present##sgab"].plurals[0] = "=are proud to present";
    strings["the biggest multi-system chiptune tracker!##sgab"].plurals[0] = "=the biggest multi-system chiptune tracker!";
    strings["featuring DefleMask song compatibility.##sgab"].plurals[0] = "=featuring DefleMask song compatibility.";

    strings["> CREDITS <##sgab"].plurals[0] = "=> CREDITS <";
    strings["-- program --##sgab"].plurals[0] = "=-- program --";
    strings["A M 4 N (intro tune)##sgab"].plurals[0] = "=A M 4 N (intro tune)";
    strings["-- graphics/UI design --##sgab"].plurals[0] = "=-- graphics/UI design --";
    strings["-- documentation --##sgab"].plurals[0] = "=-- documentation --";
    strings["-- demo songs --##sgab"].plurals[0] = "=-- demo songs --";
    strings["-- additional feedback/fixes --##sgab"].plurals[0] = "=-- additional feedback/fixes --";
    strings["-- translations and related work --##sgab"].plurals[0] = "=-- translations and related work --";
    strings["LTVA1 (Russian translation)##sgab"].plurals[0] = "=LTVA1 (Russian translation)";
    strings["Kagamiin~ (Portuguese translation)##sgab"].plurals[0] = "=Kagamiin~ (Portuguese translation)";
    strings["freq-mod (Polish translation)##sgab"].plurals[0] = "=freq-mod (Polish translation)";

    strings["powered by:##sgab"].plurals[0] = "=powered by:";
    strings["Dear ImGui by Omar Cornut##sgab"].plurals[0] = "=Dear ImGui by Omar Cornut";
    strings["SDL2 by Sam Lantinga##sgab"].plurals[0] = "=SDL2 by Sam Lantinga";
    strings["zlib by Jean-loup Gailly##sgab"].plurals[0] = "=zlib by Jean-loup Gailly";
    strings["and Mark Adler##sgab"].plurals[0] = "=and Mark Adler";
    strings["libsndfile by Erik de Castro Lopo##sgab"].plurals[0] = "=libsndfile by Erik de Castro Lopo";
    strings["Portable File Dialogs by Sam Hocevar##sgab"].plurals[0] = "=Portable File Dialogs by Sam Hocevar";
    strings["Native File Dialog by Frogtoss Games##sgab"].plurals[0] = "=Native File Dialog by Frogtoss Games";
    strings["Weak-JACK by x42##sgab"].plurals[0] = "=Weak-JACK by x42";
    strings["RtMidi by Gary P. Scavone##sgab"].plurals[0] = "=RtMidi by Gary P. Scavone";
    strings["FFTW by Matteo Frigo and Steven G. Johnson##sgab"].plurals[0] = "=FFTW by Matteo Frigo and Steven G. Johnson";
    strings["backward-cpp by Google##sgab"].plurals[0] = "=backward-cpp by Google";
    strings["adpcm by superctr##sgab"].plurals[0] = "=adpcm by superctr";
    strings["adpcm-xq by David Bryant##sgab"].plurals[0] = "=adpcm-xq by David Bryant";
    strings["Nuked-OPL3/OPLL/OPM/OPN2/PSG by nukeykt##sgab"].plurals[0] = "=Nuked-OPL3/OPLL/OPM/OPN2/PSG by nukeykt";
    strings["YM3812-LLE, YMF262-LLE and YMF276-LLE by nukeykt##sgab"].plurals[0] = "=YM3812-LLE, YMF262-LLE and YMF276-LLE by nukeykt";
    strings["ymfm by Aaron Giles##sgab"].plurals[0] = "=ymfm by Aaron Giles";
    strings["emu2413 by Digital Sound Antiques##sgab"].plurals[0] = "=emu2413 by Digital Sound Antiques";
    strings["MAME SN76496 by Nicola Salmoria##sgab"].plurals[0] = "=MAME SN76496 by Nicola Salmoria";
    strings["MAME AY-3-8910 by Couriersud##sgab"].plurals[0] = "=MAME AY-3-8910 by Couriersud";
    strings["with AY8930 fixes by Eulous, cam900 and Grauw##sgab"].plurals[0] = "=with AY8930 fixes by Eulous, cam900 and Grauw";
    strings["MAME SAA1099 by Juergen Buchmueller and Manuel Abadia##sgab"].plurals[0] = "=MAME SAA1099 by Juergen Buchmueller and Manuel Abadia";
    strings["MAME Namco WSG by Nicola Salmoria and Aaron Giles##sgab"].plurals[0] = "=MAME Namco WSG by Nicola Salmoria and Aaron Giles";
    strings["MAME RF5C68 core by Olivier Galibert and Aaron Giles##sgab"].plurals[0] = "=MAME RF5C68 core by Olivier Galibert and Aaron Giles";
    strings["MAME MSM5232 core by Jarek Burczynski and Hiromitsu Shioya##sgab"].plurals[0] = "=MAME MSM5232 core by Jarek Burczynski and Hiromitsu Shioya";
    strings["MAME MSM6258 core by Barry Rodewald##sgab"].plurals[0] = "=MAME MSM6258 core by Barry Rodewald";
    strings["MAME YMZ280B core by Aaron Giles##sgab"].plurals[0] = "=MAME YMZ280B core by Aaron Giles";
    strings["MAME GA20 core by Acho A. Tang and R. Belmont##sgab"].plurals[0] = "=MAME GA20 core by Acho A. Tang and R. Belmont";
    strings["MAME SegaPCM core by Hiromitsu Shioya and Olivier Galibert##sgab"].plurals[0] = "=MAME SegaPCM core by Hiromitsu Shioya and Olivier Galibert";
    strings["SAASound by Dave Hooper and Simon Owen##sgab"].plurals[0] = "=SAASound by Dave Hooper and Simon Owen";
    strings["SameBoy by Lior Halphon##sgab"].plurals[0] = "=SameBoy by Lior Halphon";
    strings["Mednafen PCE, WonderSwan, T6W28 and Virtual Boy audio cores##sgab"].plurals[0] = "=Mednafen PCE, WonderSwan, T6W28 and Virtual Boy audio cores";
    strings["SNES DSP core by Blargg##sgab"].plurals[0] = "=SNES DSP core by Blargg";
    strings["puNES (NES, MMC5 and FDS) by FHorse##sgab"].plurals[0] = "=puNES (NES, MMC5 and FDS) by FHorse";
    strings["NSFPlay (NES and FDS) by Brad Smith and Brezza##sgab"].plurals[0] = "=NSFPlay (NES and FDS) by Brad Smith and Brezza";
    strings["reSID by Dag Lem##sgab"].plurals[0] = "=reSID by Dag Lem";
    strings["reSIDfp by Dag Lem, Antti Lankila##sgab"].plurals[0] = "=reSIDfp by Dag Lem, Antti Lankila";
    strings["and Leandro Nini##sgab"].plurals[0] = "=and Leandro Nini";
    strings["dSID by DefleMask Team based on jsSID##sgab"].plurals[0] = "=dSID by DefleMask Team based on jsSID";
    strings["Stella by Stella Team##sgab"].plurals[0] = "=Stella by Stella Team";
    strings["QSound emulator by superctr and Valley Bell##sgab"].plurals[0] = "=QSound emulator by superctr and Valley Bell";
    strings["VICE VIC-20 sound core by Rami Rasanen and viznut##sgab"].plurals[0] = "=VICE VIC-20 sound core by Rami Rasanen and viznut";
    strings["VICE TED sound core by Andreas Boose, Tibor Biczo##sgab"].plurals[0] = "=VICE TED sound core by Andreas Boose, Tibor Biczo";
    strings["and Marco van den Heuvel##sgab"].plurals[0] = "=and Marco van den Heuvel";
    strings["VERA sound core by Frank van den Hoef##sgab"].plurals[0] = "=VERA sound core by Frank van den Hoef";
    strings["mzpokeysnd POKEY emulator by Michael Borisov##sgab"].plurals[0] = "=mzpokeysnd POKEY emulator by Michael Borisov";
    strings["ASAP POKEY emulator by Piotr Fusik##sgab"].plurals[0] = "=ASAP POKEY emulator by Piotr Fusik";
    strings["ported by laoo to C++##sgab"].plurals[0] = "=ported by laoo to C++";
    strings["vgsound_emu (second version, modified version) by cam900##sgab"].plurals[0] = "=vgsound_emu (second version, modified version) by cam900";
    strings["SM8521 emulator (modified version) by cam900##sgab"].plurals[0] = "=SM8521 emulator (modified version) by cam900";
    strings["D65010G031 emulator (modified version) by cam900##sgab"].plurals[0] = "=D65010G031 emulator (modified version) by cam900";
    strings["Namco C140/C219 emulator (modified version) by cam900##sgab"].plurals[0] = "=Namco C140/C219 emulator (modified version) by cam900";
    strings["ESFMu emulator (modified version) by Kagamiin~##sgab"].plurals[0] = "=ESFMu emulator (modified version) by Kagamiin~";
    strings["PowerNoise emulator by scratchminer##sgab"].plurals[0] = "=PowerNoise emulator by scratchminer";
    strings["ep128emu by Istvan Varga##sgab"].plurals[0] = "=ep128emu by Istvan Varga";
    strings["SID2 emulator (modification of reSID) by LTVA##sgab"].plurals[0] = "=SID2 emulator (modification of reSID) by LTVA";
    strings["5E01 emulator (modification of NSFPlay) by Euly##sgab"].plurals[0] = "=5E01 emulator (modification of NSFPlay) by Euly";
    strings["NDS sound emulator by cam900##sgab"].plurals[0] = "=NDS sound emulator by cam900";

    strings["greetings to:##sgab"].plurals[0] = "=greetings to:";
    strings["NEOART Costa Rica##sgab"].plurals[0] = "=NEOART Costa Rica";
    strings["Xenium Demoparty##sgab"].plurals[0] = "=Xenium Demoparty";
    strings["all members of Deflers of Noice!##sgab"].plurals[0] = "=all members of Deflers of Noice!";

    strings["copyright © 2021-2024 tildearrow##sgab"].plurals[0] = "=copyright © 2021-2024 tildearrow";
    strings["(and contributors).##sgab"].plurals[0] = "=(and contributors).";
    strings["licensed under GPLv2+! see##sgab"].plurals[0] = "=licensed under GPLv2+! see";
    strings["LICENSE for more information.##sgab"].plurals[0] = "=LICENSE for more information.";

    strings["help Furnace grow:##sgab"].plurals[0] = "=help Furnace grow:";
    strings["help Furnace-B:##sgab"].plurals[0] = "=help Furnace-B:";

    strings["contact tildearrow at:##sgab"].plurals[0] = "=contact tildearrow at:";

    strings["disclaimer:##sgab"].plurals[0] = "=disclaimer:";
    strings["despite the fact this program works##sgab"].plurals[0] = "=despite the fact this program works";
    strings["with the .dmf file format, it is NOT##sgab"].plurals[0] = "=with the .dmf file format, it is NOT";
    strings["affiliated with Delek or DefleMask in##sgab"].plurals[0] = "=affiliated with Delek or DefleMask in";
    strings["any way, nor it is a replacement for##sgab"].plurals[0] = "=any way, nor it is a replacement for";
    strings["the original program.##sgab"].plurals[0] = "=the original program.";

    strings["it also comes with ABSOLUTELY NO WARRANTY.##sgab"].plurals[0] = "=it also comes with ABSOLUTELY NO WARRANTY.";

    strings["thanks to all contributors/bug reporters!##sgab"].plurals[0] = "=thanks to all contributors/bug reporters!";

    //   sgch  src/gui/channels.cpp

    strings["Channels###Channels"].plurals[0] = "=Channels###Channels";
    strings["Pat##sgch"].plurals[0] = "=Pat";
    strings["Osc##sgch"].plurals[0] = "=Osc";
    strings["Swap##sgch"].plurals[0] = "=Swap";
    strings["Name##sgch"].plurals[0] = "=Name";
    strings["Show in pattern##sgch"].plurals[0] = "=Show in pattern";
    strings["Show in per-channel oscilloscope##sgch"].plurals[0] = "=Show in per-channel oscilloscope";
    strings["%s #%d\n(drag to swap channels)##sgch"].plurals[0] = "=%s #%d\n(drag to swap channels)";

    //   sgco  src/gui/chanOsc.cpp

    strings["None (0%)##sgco"].plurals[0] = "=None (0%)";
    strings["None (50%)##sgco"].plurals[0] = "=None (50%)";
    strings["None (100%)##sgco"].plurals[0] = "=None (100%)";
    strings["Frequency##sgco"].plurals[0] = "=Frequency";
    strings["Volume##sgco"].plurals[0] = "=Volume";
    strings["Channel##sgco"].plurals[0] = "=Channel";
    strings["Brightness##sgco"].plurals[0] = "=Brightness";
    strings["Note Trigger##sgco"].plurals[0] = "=Note Trigger";
    strings["Off##sgco"].plurals[0] = "=Off";
    strings["Mode 1##sgco"].plurals[0] = "=Mode 1";
    strings["Mode 2##sgco"].plurals[0] = "=Mode 2";
    strings["Mode 3##sgco"].plurals[0] = "=Mode 3";

    strings["Oscilloscope (per-channel)###Oscilloscope (per-channel)"].plurals[0] = "=Oscilloscope (per-channel)###Oscilloscope (per-channel)";

    strings["Columns##sgco"].plurals[0] = "=Columns";
    strings["Size (ms)##sgco"].plurals[0] = "=Size (ms)";
    strings["Automatic columns##sgco"].plurals[0] = "=Automatic columns";
    strings["Center waveform##sgco"].plurals[0] = "=Center waveform";
    strings["Randomize phase on note##sgco"].plurals[0] = "=Randomize phase on note";
    strings["Amplitude##sgco"].plurals[0] = "=Amplitude";
    strings["Line size##sgco"].plurals[0] = "=Line size";
    strings["Gradient##sgco"].plurals[0] = "=Gradient";
    strings["Color##sgco0"].plurals[0] = "=Color";
    strings["Distance##sgco"].plurals[0] = "=Distance";
    strings["Spread##sgco"].plurals[0] = "=Spread";
    strings["Remove##sgco"].plurals[0] = "=Remove";
    strings["Background##sgco"].plurals[0] = "=Background";
    strings["X Axis##AxisX"].plurals[0] = "=X Axis##AxisX";
    strings["Y Axis##AxisY"].plurals[0] = "=Y Axis##AxisY";
    strings["Color##sgco1"].plurals[0] = "=Color";
    strings["Text format:##sgco"].plurals[0] = "=Text format:";

    strings["format guide:\n"
            "- %c: channel name\n"
            "- %C: channel short name\n"
            "- %d: channel number (starting from 0)\n"
            "- %D: channel number (starting from 1)\n"
            "- %n: channel note\n"
            "- %i: instrument name\n"
            "- %I: instrument number (decimal)\n"
            "- %x: instrument number (hex)\n"
            "- %s: chip name\n"
            "- %p: chip part number\n"
            "- %S: chip ID\n"
            "- %v: volume (decimal)\n"
            "- %V: volume (percentage)\n"
            "- %b: volume (hex)\n"
            "- %l: new line\n"
            "- %%: percent sign##sgco"].plurals[0] = 

            "=format guide:\n"
            "=- %c: channel name\n"
            "=- %C: channel short name\n"
            "=- %d: channel number (starting from 0)\n"
            "=- %D: channel number (starting from 1)\n"
            "=- %n: channel note\n"
            "=- %i: instrument name\n"
            "=- %I: instrument number (decimal)\n"
            "=- %x: instrument number (hex)\n"
            "=- %s: chip name\n"
            "=- %p: chip part number\n"
            "=- %S: chip ID\n"
            "=- %v: volume (decimal)\n"
            "=- %V: volume (percentage)\n"
            "=- %b: volume (hex)\n"
            "=- %l: new line\n"
            "=- %%: percent sign";

    strings["Text color##sgco"].plurals[0] = "=Text color";
    strings["Error!##sgco"].plurals[0] = "=Error!";
    strings["\nquiet##sgco"].plurals[0] = "=\nquiet";

    //   sgcl  src/gui/clock.cpp

    strings["Clock###Clock"].plurals[0] = "=Clock###Clock";

    //   sgcp  src/gui/commandPalette.cpp

    strings["Search...##sgcp"].plurals[0] = "=Search...";
    strings["Search recent files...##sgcp"].plurals[0] = "=Search recent files...";
    strings["Search instruments...##sgcp"].plurals[0] = "=Search instruments...";
    strings["Search samples...##sgcp"].plurals[0] = "=Search samples...";
    strings["Search instruments (to change to)...##sgcp"].plurals[0] = "=Search instruments (to change to)...";
    strings["Search chip (to add)...##sgcp"].plurals[0] = "=Search chip (to add)...";
    strings["Cancel##sgcp"].plurals[0] = "=Cancel";
    strings["cannot add chip! (##sgcp"].plurals[0] = "=cannot add chip! (";
    strings["- None -"].plurals[0] = "=- None -";

    //   sgcf  src/gui/compatFlags.cpp

    strings["Compatibility Flags###Compatibility Flags"].plurals[0] = "=Compatibility Flags###Compatibility Flags";
    strings["these flags are designed to provide better DefleMask/older Furnace compatibility.\nit is recommended to disable most of these unless you rely on specific quirks.##sgcf"].plurals[0] = "=these flags are designed to provide better DefleMask/older Furnace compatibility.\nit is recommended to disable most of these unless you rely on specific quirks.";
    strings["Game Boy instrument duty is wave volume##sgcf"].plurals[0] = "=Game Boy instrument duty is wave volume";
    strings["if enabled, an instrument with duty macro in the wave channel will be mapped to wavetable volume.##sgcf"].plurals[0] = "=if enabled, an instrument with duty macro in the wave channel will be mapped to wavetable volume.";
    strings["Restart macro on portamento##sgcf"].plurals[0] = "=Restart macro on portamento";
    strings["when enabled, a portamento effect will reset the channel's macro if used in combination with a note.##sgcf"].plurals[0] = "=when enabled, a portamento effect will reset the channel's macro if used in combination with a note.";
    strings["Ignore duplicate slide effects##sgcf"].plurals[0] = "=Ignore duplicate slide effects";
    strings["if this is on, only the first slide of a row in a channel will be considered.##sgcf"].plurals[0] = "=if this is on, only the first slide of a row in a channel will be considered.";
    strings["Ignore 0Dxx on the last order##sgcf"].plurals[0] = "=Ignore 0Dxx on the last order";
    strings["if this is on, a jump to next row effect will not take place when it is on the last order of a song.##sgcf"].plurals[0] = "=if this is on, a jump to next row effect will not take place when it is on the last order of a song.";
    strings["Don't apply Game Boy envelope on note-less instrument change##sgcf"].plurals[0] = "=Don't apply Game Boy envelope on note-less instrument change";
    strings["if this is on, an instrument change will not affect the envelope.##sgcf"].plurals[0] = "=if this is on, an instrument change will not affect the envelope.";
    strings["Ignore DAC mode change outside of intended channel in ExtCh mode##sgcf"].plurals[0] = "=Ignore DAC mode change outside of intended channel in ExtCh mode";
    strings["if this is on, 17xx has no effect on the operator channels in YM2612.##sgcf"].plurals[0] = "=if this is on, 17xx has no effect on the operator channels in YM2612.";
    strings["SN76489 duty macro always resets phase##sgcf"].plurals[0] = "=SN76489 duty macro always resets phase";
    strings["when enabled, duty macro will always reset phase, even if its value hasn't changed.##sgcf"].plurals[0] = "=when enabled, duty macro will always reset phase, even if its value hasn't changed.";
    strings["Don't persist volume macro after it finishes##sgcf"].plurals[0] = "=Don't persist volume macro after it finishes";
    strings["when enabled, a value in the volume column that happens after the volume macro is done will disregard the macro.##sgcf"].plurals[0] = "=when enabled, a value in the volume column that happens after the volume macro is done will disregard the macro.";
    strings[".mod import##sgcf"].plurals[0] = "=.mod import";
    strings["Don't slide on the first tick of a row##sgcf"].plurals[0] = "=Don't slide on the first tick of a row";
    strings["simulates ProTracker's behavior of not applying volume/pitch slides on the first tick of a row.##sgcf"].plurals[0] = "=simulates ProTracker's behavior of not applying volume/pitch slides on the first tick of a row.";
    strings["Reset arpeggio position on row change##sgcf"].plurals[0] = "=Reset arpeggio position on row change";
    strings["simulates ProTracker's behavior of arpeggio being bound to the current tick of a row.##sgcf"].plurals[0] = "=simulates ProTracker's behavior of arpeggio being bound to the current tick of a row.";
    strings["Pitch/Playback##sgcf"].plurals[0] = "=Pitch/Playback";
    strings["Pitch linearity:##sgcf"].plurals[0] = "=Pitch linearity:";
    strings["None##sgcf"].plurals[0] = "=None";
    strings["like ProTracker/FamiTracker##sgcf"].plurals[0] = "=like ProTracker/FamiTracker";
    strings["Full##sgcf"].plurals[0] = "=Full";
    strings["like Impulse Tracker##sgcf"].plurals[0] = "=like Impulse Tracker";
    strings["Pitch slide speed multiplier##sgcf"].plurals[0] = "=Pitch slide speed multiplier";
    strings["Loop modality:##sgcf"].plurals[0] = "=Loop modality:";
    strings["Reset channels##sgcf"].plurals[0] = "=Reset channels";
    strings["select to reset channels on loop. may trigger a voltage click on every loop!##sgcf"].plurals[0] = "=select to reset channels on loop. may trigger a voltage click on every loop!";
    strings["Soft reset channels##sgcf"].plurals[0] = "=Soft reset channels";
    strings["select to turn channels off on loop.##sgcf"].plurals[0] = "=select to turn channels off on loop.";
    strings["Do nothing##sgcf"].plurals[0] = "=Do nothing";
    strings["select to not reset channels on loop.##sgcf"].plurals[0] = "=select to not reset channels on loop.";
    strings["Cut/delay effect policy:##sgcf"].plurals[0] = "=Cut/delay effect policy:";
    strings["Strict##sgcf"].plurals[0] = "=Strict";
    strings["only when time is less than speed (like DefleMask/ProTracker)##sgcf"].plurals[0] = "=only when time is less than speed (like DefleMask/ProTracker)";
    strings["Lax##sgcf"].plurals[0] = "=Lax";
    strings["no checks##sgcf"].plurals[0] = "=no checks";
    strings["Simultaneous jump (0B+0D) treatment:##sgcf"].plurals[0] = "=Simultaneous jump (0B+0D) treatment:";
    strings["Normal##sgcf"].plurals[0] = "=Normal";
    strings["accept 0B+0D to jump to a specific row of an order##sgcf"].plurals[0] = "=accept 0B+0D to jump to a specific row of an order";
    strings["Other##sgcf"].plurals[0] = "=Other";
    strings["Auto-insert one tick gap between notes##sgcf"].plurals[0] = "=Auto-insert one tick gap between notes";
    strings["when enabled, a one-tick note cut will be inserted between non-legato/non-portamento notes.\nthis simulates the behavior of some Amiga/SNES music engines.\n\nineffective on C64.##sgcf"].plurals[0] = "=when enabled, a one-tick note cut will be inserted between non-legato/non-portamento notes.\nthis simulates the behavior of some Amiga/SNES music engines.\n\nineffective on C64.";
    strings["Don't reset slides after note off##sgcf"].plurals[0] = "=Don't reset slides after note off";
    strings["when enabled, note off will not reset the channel's slide effect.##sgcf"].plurals[0] = "=when enabled, note off will not reset the channel's slide effect.";
    strings["Don't reset portamento after reaching target##sgcf"].plurals[0] = "=Don't reset portamento after reaching target";
    strings["when enabled, the slide effect will not be disabled after it reaches its target.##sgcf"].plurals[0] = "=when enabled, the slide effect will not be disabled after it reaches its target.";
    strings["Continuous vibrato##sgcf"].plurals[0] = "=Continuous vibrato";
    strings["when enabled, vibrato phase/position will not be reset on a new note.##sgcf"].plurals[0] = "=when enabled, vibrato phase/position will not be reset on a new note.";
    strings["Pitch macro is not linear##sgcf"].plurals[0] = "=Pitch macro is not linear";
    strings["when enabled, the pitch macro of an instrument is in frequency/period space.##sgcf"].plurals[0] = "=when enabled, the pitch macro of an instrument is in frequency/period space.";
    strings["Reset arpeggio effect position on new note##sgcf"].plurals[0] = "=Reset arpeggio effect position on new note";
    strings["when enabled, arpeggio effect (00xy) position is reset on a new note.##sgcf"].plurals[0] = "=when enabled, arpeggio effect (00xy) position is reset on a new note.";
    strings["Volume scaling rounds up##sgcf"].plurals[0] = "=Volume scaling rounds up";
    strings["when enabled, volume macros round up when applied\nthis prevents volume scaling from causing vol=0, which is silent on some chips\n\nineffective on logarithmic channels##sgcf"].plurals[0] = "=when enabled, volume macros round up when applied\nthis prevents volume scaling from causing vol=0, which is silent on some chips\n\nineffective on logarithmic channels";
    strings["Stop NES pulse channels hardware sweep on new note##sgcf"].plurals[0] = "=Stop NES pulse channels hardware sweep on new note";
    strings["Do not stop volume slide after reaching zero or full volume##sgcf"].plurals[0] = "=Do not stop volume slide after reaching zero or full volume";
    strings["Stop E1xy/E2xy effects on new note##sgcf"].plurals[0] = "=Stop E1xy/E2xy effects on new note";
    strings["Slower 0Axy volume slide##sgcf"].plurals[0] = "=Slower 0Axy volume slide";

    //   sgcs  src/gui/csPlayer.cpp

    strings["Command Stream Player###Command Stream Player"].plurals[0] = "=Command Stream Player###Command Stream Player";
    strings["Load##sgcs"].plurals[0] = "=Load";
    strings["Kill##sgcs"].plurals[0] = "=Kill";
    strings["Burn Current Song##sgcs"].plurals[0] = "=Burn Current Song";
    strings["Status##sgcs"].plurals[0] = "=Status";
    strings["Hex##sgcs"].plurals[0] = "=Hex";

    //   sgdl  src/gui/dataList.cpp

    strings["Bug!##sgdl"].plurals[0] = "=Bug!";
    strings["Unknown##sgdl"].plurals[0] = "=Unknown";
    strings["duplicate##sgdl0"].plurals[0] = "=duplicate";
    strings["replace...##sgdl0"].plurals[0] = "=replace...";
    strings["save##sgdl0"].plurals[0] = "=save";
    strings["export (.dmp)##sgdl"].plurals[0] = "=export (.dmp)";
    strings["delete##sgdl0"].plurals[0] = "=delete";
    strings["%.2X: <INVALID>##sgdl"].plurals[0] = "=%.2X: <INVALID>";
    strings["- None -##sgdl"].plurals[0] = "=- None -";
    strings["out of memory for this sample!##sgdl"].plurals[0] = "=out of memory for this sample!";
    strings["make instrument##sgdl"].plurals[0] = "=make instrument";
    strings["make me a drum kit##sgdl"].plurals[0] = "=make me a drum kit";
    strings["duplicate##sgdl1"].plurals[0] = "=duplicate";
    strings["replace...##sgdl1"].plurals[0] = "=replace...";
    strings["save##sgdl1"].plurals[0] = "=save";
    strings["delete##sgdl1"].plurals[0] = "=delete";
    strings["Instruments###Instruments"].plurals[0] = "=Instruments###Instruments";
    strings["Add##sgdl0"].plurals[0] = "=Add";
    strings["Duplicate##sgdl2"].plurals[0] = "=Duplicate";
    strings["Open##sgdl0"].plurals[0] = "=Open";
    strings["replace instrument...##sgdl"].plurals[0] = "=replace instrument...";
    strings["load instrument from TX81Z##sgdl"].plurals[0] = "=load instrument from TX81Z";
    strings["replace wavetable...##sgdl"].plurals[0] = "=replace wavetable...";
    strings["replace sample...##sgdl"].plurals[0] = "=replace sample...";
    strings["import raw sample...##sgdl"].plurals[0] = "=import raw sample...";
    strings["import raw sample (replace)...##sgdl"].plurals[0] = "=import raw sample (replace)...";
    strings["replace...##sgdl2"].plurals[0] = "=replace...";
    strings["load from TX81Z##sgdl"].plurals[0] = "=load from TX81Z";
    strings["Open (insert; right-click to replace)##sgdl"].plurals[0] = "=Open (insert; right-click to replace)";
    strings["Save##sgdl2"].plurals[0] = "=Save";
    strings["save instrument as .dmp...##sgdl"].plurals[0] = "=save instrument as .dmp...";
    strings["save wavetable as .dmw...##sgdl"].plurals[0] = "=save wavetable as .dmw...";
    strings["save raw wavetable...##sgdl"].plurals[0] = "=save raw wavetable...";
    strings["save raw sample...##sgdl"].plurals[0] = "=save raw sample...";
    strings["save as .dmp...##sgdl"].plurals[0] = "=save as .dmp...";
    strings["Toggle folders/standard view##sgdl0"].plurals[0] = "=Toggle folders/standard view";
    strings["Move up##sgdl0"].plurals[0] = "=Move up";
    strings["Move down##sgdl0"].plurals[0] = "=Move down";
    strings["Create##sgdl0"].plurals[0] = "=Create";
    strings["New folder##sgdl0"].plurals[0] = "=New folder";
    strings["Preview (right click to stop)##sgdl0"].plurals[0] = "=Preview (right click to stop)";
    strings["Delete##sgdl2"].plurals[0] = "=Delete";
    strings["Instruments##sgdl"].plurals[0] = "=Instruments";
    strings["<uncategorized>##sgdl0"].plurals[0] = "=<uncategorized>";
    strings["rename...##sgdl0"].plurals[0] = "=rename...";
    strings["delete##sgdl3"].plurals[0] = "=delete";
    strings["Wavetables##sgdl"].plurals[0] = "=Wavetables";
    strings["Samples##sgdl"].plurals[0] = "=Samples";
    strings["Wavetables###Wavetables"].plurals[0] = "=Wavetables###Wavetables";
    strings["Add##sgdl2"].plurals[0] = "=Add";
    strings["Duplicate##sgdl3"].plurals[0] = "=Duplicate";
    strings["Open##sgdl1"].plurals[0] = "=Open";
    strings["replace...##sgdl3"].plurals[0] = "=replace...";
    strings["Save##sgdl3"].plurals[0] = "=Save";
    strings["save as .dmw...##sgdl"].plurals[0] = "=save as .dmw...";
    strings["save raw...##sgdl0"].plurals[0] = "=save raw...";
    strings["Toggle folders/standard view##sgdl1"].plurals[0] = "=Toggle folders/standard view";
    strings["Move up##sgdl1"].plurals[0] = "=Move up";
    strings["Move down##sgdl1"].plurals[0] = "=Move down";
    strings["Create##sgdl1"].plurals[0] = "=Create";
    strings["New folder##sgdl1"].plurals[0] = "=New folder";
    strings["Delete##sgdl4"].plurals[0] = "=Delete";
    strings["Samples###Samples"].plurals[0] = "=Samples###Samples";
    strings["Add##sgdl3"].plurals[0] = "=Add";
    strings["Duplicate##sgdl4"].plurals[0] = "=Duplicate";
    strings["Open##sgdl2"].plurals[0] = "=Open";
    strings["replace...##sgdl4"].plurals[0] = "=replace...";
    strings["import raw...##sgdl"].plurals[0] = "=import raw...";
    strings["import raw (replace)...##sgdl"].plurals[0] = "=import raw (replace)...";
    strings["Save##sgdl4"].plurals[0] = "=Save";
    strings["save raw...##sgdl1"].plurals[0] = "=save raw...";
    strings["Toggle folders/standard view##sgdl2"].plurals[0] = "=Toggle folders/standard view";
    strings["Move up##sgdl2"].plurals[0] = "=Move up";
    strings["Move down##sgdl2"].plurals[0] = "=Move down";
    strings["Create##sgdl2"].plurals[0] = "=Create";
    strings["New folder##sgdl2"].plurals[0] = "=New folder";
    strings["Preview (right click to stop)##sgdl1"].plurals[0] = "=Preview (right click to stop)";
    strings["Delete##sgdl5"].plurals[0] = "=Delete";
    strings["<uncategorized>##sgdl1"].plurals[0] = "=<uncategorized>";
    strings["rename...##sgdl1"].plurals[0] = "=rename...";
    strings["delete##sgdl6"].plurals[0] = "=delete";
    strings["rename...##sgdl2"].plurals[0] = "=rename...";
    strings["delete##sgdl7"].plurals[0] = "=delete";

    //   sggu  src/gui/gui.cpp

    strings["Instrument %d##sggu"].plurals[0] = "=Instrument %d";
    strings["Sample %d"].plurals[0] = "=Sample %d";
    strings["the song is over!##sggu0"].plurals[0] = "=the song is over!";
    strings["the song is over!##sggu1"].plurals[0] = "=the song is over!";
    strings["Open File##sggu"].plurals[0] = "=Open File";
    strings["compatible files##sggu0"].plurals[0] = "=compatible files";
    strings["all files##sggu0"].plurals[0] = "=all files";
    strings["no backups made yet!##sggu"].plurals[0] = "=no backups made yet!";
    strings["Restore Backup##sggu"].plurals[0] = "=Restore Backup";
    strings["Furnace or Furnace-B song##sggu"].plurals[0] = "=Furnace or Furnace-B song";
    strings["Furnace song##sggu0"].plurals[0] = "=Furnace song";
    strings["Save File##sggu0"].plurals[0] = "=Save File";
    strings["DefleMask 1.1.3 module##sggu"].plurals[0] = "=DefleMask 1.1.3 module";
    strings["Save File##sggu1"].plurals[0] = "=Save File";
    strings["DefleMask 1.0/legacy module##sggu"].plurals[0] = "=DefleMask 1.0/legacy module";
    strings["Save File##sggu2"].plurals[0] = "=Save File";
    strings["Furnace-B song##sggu"].plurals[0] = "=Furnace-B song";
    strings["Load Instrument##sggu"].plurals[0] = "=Load Instrument";
    strings["all compatible files##sggu1"].plurals[0] = "=all compatible files";
    strings["Furnace instrument##sggu0"].plurals[0] = "=Furnace instrument";
    strings["DefleMask preset##sggu0"].plurals[0] = "=DefleMask preset";
    strings["TFM Music Maker instrument##sggu"].plurals[0] = "=TFM Music Maker instrument";
    strings["VGM Music Maker instrument##sggu"].plurals[0] = "=VGM Music Maker instrument";
    strings["Scream Tracker 3 instrument##sggu"].plurals[0] = "=Scream Tracker 3 instrument";
    strings["SoundBlaster instrument##sggu"].plurals[0] = "=SoundBlaster instrument";
    strings["Wohlstand OPL instrument##sggu"].plurals[0] = "=Wohlstand OPL instrument";
    strings["Wohlstand OPN instrument##sggu"].plurals[0] = "=Wohlstand OPN instrument";
    strings["Gens KMod patch dump##sggu"].plurals[0] = "=Gens KMod patch dump";
    strings["BNK file (AdLib)##sggu"].plurals[0] = "=BNK file (AdLib)";
    strings["FF preset bank##sggu"].plurals[0] = "=FF preset bank";
    strings["2612edit GYB preset bank##sggu"].plurals[0] = "=2612edit GYB preset bank";
    strings["VOPM preset bank##sggu"].plurals[0] = "=VOPM preset bank";
    strings["Wohlstand WOPL bank##sggu"].plurals[0] = "=Wohlstand WOPL bank";
    strings["Wohlstand WOPN bank##sggu"].plurals[0] = "=Wohlstand WOPN bank";
    strings["all files##sggu1"].plurals[0] = "=all files";
    strings["Save Instrument##sggu0"].plurals[0] = "=Save Instrument";
    strings["Furnace instrument##sggu1"].plurals[0] = "=Furnace instrument";
    strings["Save Instrument##sggu1"].plurals[0] = "=Save Instrument";
    strings["DefleMask preset##sggu1"].plurals[0] = "=DefleMask preset";
    strings["Load Wavetable##sggu"].plurals[0] = "=Load Wavetable";
    strings["compatible files##sggu2"].plurals[0] = "=compatible files";
    strings["all files##sggu2"].plurals[0] = "=all files";
    strings["Save Wavetable##sggu0"].plurals[0] = "=Save Wavetable";
    strings["Furnace wavetable##sggu"].plurals[0] = "=Furnace wavetable";
    strings["Save Wavetable##sggu1"].plurals[0] = "=Save Wavetable";
    strings["DefleMask wavetable##sggu"].plurals[0] = "=DefleMask wavetable";
    strings["Save Wavetable##sggu2"].plurals[0] = "=Save Wavetable";
    strings["raw data##sggu"].plurals[0] = "=raw data";
    strings["Load Sample##sggu"].plurals[0] = "=Load Sample";
    strings["compatible files##sggu3"].plurals[0] = "=compatible files";
    strings["all files##sggu3"].plurals[0] = "=all files";
    strings["Load Raw Sample##sggu"].plurals[0] = "=Load Raw Sample";
    strings["all files##sggu4"].plurals[0] = "=all files";
    strings["Save Sample##sggu"].plurals[0] = "=Save Sample";
    strings["Wave file##sggu0"].plurals[0] = "=Wave file";
    strings["Save Raw Sample##sggu"].plurals[0] = "=Save Raw Sample";
    strings["all files##sggu5"].plurals[0] = "=all files";
    strings["Export Audio##sggu0"].plurals[0] = "=Export Audio";
    strings["Wave file##sggu1"].plurals[0] = "=Wave file";
    strings["Export Audio##sggu1"].plurals[0] = "=Export Audio";
    strings["Wave file##sggu2"].plurals[0] = "=Wave file";
    strings["Export Audio##sggu2"].plurals[0] = "=Export Audio";
    strings["Wave file##sggu3"].plurals[0] = "=Wave file";
    strings["Export VGM##sggu"].plurals[0] = "=Export VGM";
    strings["VGM file##sggu"].plurals[0] = "=VGM file";
    strings["Export ZSM##sggu"].plurals[0] = "=Export ZSM";
    strings["ZSM file##sggu"].plurals[0] = "=ZSM file";
    strings["Export Command Stream##sggu0"].plurals[0] = "=Export Command Stream";
    strings["text file##sggu0"].plurals[0] = "=text file";
    strings["Export Command Stream##sggu1"].plurals[0] = "=Export Command Stream";
    strings["text file##sggu1"].plurals[0] = "=text file";
    strings["Export Command Stream##sggu2"].plurals[0] = "=Export Command Stream";
    strings["binary file##sggu"].plurals[0] = "=binary file";
    strings["Export Furnace song##sggu"].plurals[0] = "=Export Furnace song";
    strings["Furnace song##sggu2"].plurals[0] = "=Furnace song";
    strings["Coming soon!##sggu"].plurals[0] = "=Coming soon!";
    strings["Select Font##sggu0"].plurals[0] = "=Select Font";
    strings["compatible files##sggu4"].plurals[0] = "=compatible files";
    strings["Select Font##sggu1"].plurals[0] = "=Select Font";
    strings["compatible files##sggu5"].plurals[0] = "=compatible files";
    strings["Select Font##sggu2"].plurals[0] = "=Select Font";
    strings["compatible files##sggu6"].plurals[0] = "=compatible files";
    strings["Select Color File##sggu"].plurals[0] = "=Select Color File";
    strings["configuration files##sggu0"].plurals[0] = "=configuration files";
    strings["Select Keybind File##sggu"].plurals[0] = "=Select Keybind File";
    strings["configuration files##sggu1"].plurals[0] = "=configuration files";
    strings["Select Layout File##sggu"].plurals[0] = "=Select Layout File";
    strings[".ini files##sggu0"].plurals[0] = "=.ini files";
    strings["Export Colors##sggu"].plurals[0] = "=Export Colors";
    strings["configuration files##sggu2"].plurals[0] = "=configuration files";
    strings["Export Keybinds##sggu"].plurals[0] = "=Export Keybinds";
    strings["configuration files##sggu3"].plurals[0] = "=configuration files";
    strings["Export Layout##sggu"].plurals[0] = "=Export Layout";
    strings[".ini files##sggu1"].plurals[0] = "=.ini files";
    strings["Load ROM##sggu"].plurals[0] = "=Load ROM";
    strings["compatible files##sggu7"].plurals[0] = "=compatible files";
    strings["all files##sggu6"].plurals[0] = "=all files";
    strings["Play Command Stream##sggu"].plurals[0] = "=Play Command Stream";
    strings["command stream##sggu"].plurals[0] = "=command stream";
    strings["all files##sggu7"].plurals[0] = "=all files";
    strings["Open Test##sggu"].plurals[0] = "=Open Test";
    strings["compatible files##sggu8"].plurals[0] = "=compatible files";
    strings["another option##sggu0"].plurals[0] = "=another option";
    strings["all files##sggu8"].plurals[0] = "=all files";
    strings["Open Test (Multi)##sggu"].plurals[0] = "=Open Test (Multi)";
    strings["compatible files##sggu9"].plurals[0] = "=compatible files";
    strings["another option##sggu1"].plurals[0] = "=another option";
    strings["all files##sggu9"].plurals[0] = "=all files";
    strings["Save Test##sggu"].plurals[0] = "=Save Test";
    strings["Furnace song##sggu"].plurals[0] = "=Furnace song";
    strings["DefleMask module##sggu"].plurals[0] = "=DefleMask module";
    strings["you have loaded a backup!\nif you need to, please save it somewhere.\n\nDO NOT RELY ON THE BACKUP SYSTEM FOR AUTO-SAVE!\nFurnace will not save backups of backups.##sggu"].plurals[0] = "=you have loaded a backup!\nif you need to, please save it somewhere.\n\nDO NOT RELY ON THE BACKUP SYSTEM FOR AUTO-SAVE!\nFurnace will not save backups of backups.";
    strings["cut##sggu"].plurals[0] = "=cut";
    strings["copy##sggu"].plurals[0] = "=copy";
    strings["paste##sggu0"].plurals[0] = "=paste";
    strings["paste special...##sggu"].plurals[0] = "=paste special...";
    strings["paste mix##sggu"].plurals[0] = "=paste mix";
    strings["paste mix (background)##sggu"].plurals[0] = "=paste mix (background)";
    strings["paste with ins (foreground)##sggu"].plurals[0] = "=paste with ins (foreground)";
    strings["no instruments available##sggu0"].plurals[0] = "=no instruments available";
    strings["paste with ins (background)##sggu"].plurals[0] = "=paste with ins (background)";
    strings["no instruments available##sggu1"].plurals[0] = "=no instruments available";
    strings["paste flood##sggu"].plurals[0] = "=paste flood";
    strings["paste overflow##sggu"].plurals[0] = "=paste overflow";
    strings["delete##sggu0"].plurals[0] = "=delete";
    strings["select all##sggu"].plurals[0] = "=select all";
    strings["operation mask...##sggu"].plurals[0] = "=operation mask...";
    strings["delete##sggu1"].plurals[0] = "=delete";
    strings["pull delete##sggu"].plurals[0] = "=pull delete";
    strings["insert##sggu"].plurals[0] = "=insert";
    strings["paste##sggu1"].plurals[0] = "=paste";
    strings["transpose (note)##sggu"].plurals[0] = "=transpose (note)";
    strings["transpose (value)##sggu"].plurals[0] = "=transpose (value)";
    strings["interpolate##sggu0"].plurals[0] = "=interpolate";
    strings["fade##sggu"].plurals[0] = "=fade";
    strings["invert values##sggu0"].plurals[0] = "=invert values";
    strings["scale##sggu"].plurals[0] = "=scale";
    strings["randomize##sggu"].plurals[0] = "=randomize";
    strings["flip##sggu"].plurals[0] = "=flip";
    strings["collapse/expand##sggu"].plurals[0] = "=collapse/expand";
    strings["input latch##sggu"].plurals[0] = "=input latch";
    strings["&&: selected instrument\n..: no instrument##sggu"].plurals[0] = "=&&: selected instrument\n..: no instrument";
    strings["Set##sggu"].plurals[0] = "=Set";
    strings["Reset##sggu"].plurals[0] = "=Reset";
    strings["note up##sggu"].plurals[0] = "=note up";
    strings["note down##sggu"].plurals[0] = "=note down";
    strings["octave up##sggu"].plurals[0] = "=octave up";
    strings["octave down##sggu"].plurals[0] = "=octave down";
    strings["values up##sggu"].plurals[0] = "=values up";
    strings["values down##sggu"].plurals[0] = "=values down";
    strings["values up (+16)##sggu"].plurals[0] = "=values up (+16)";
    strings["values down (-16)##sggu"].plurals[0] = "=values down (-16)";
    strings["transpose##sggu"].plurals[0] = "=transpose";
    strings["Notes##sggu"].plurals[0] = "=Notes";
    strings["Values##sggu"].plurals[0] = "=Values";
    strings["interpolate##sggu1"].plurals[0] = "=interpolate";
    strings["change instrument...##sggu"].plurals[0] = "=change instrument...";
    strings["no instruments available##sggu"].plurals[0] = "=no instruments available";
    strings["gradient/fade...##sggu"].plurals[0] = "=gradient/fade...";
    strings["Start##sggu"].plurals[0] = "=Start";
    strings["End##sggu"].plurals[0] = "=End";
    strings["Nibble mode##sggu0"].plurals[0] = "=Nibble mode";
    strings["Go ahead##sggu"].plurals[0] = "=Go ahead";
    strings["scale...##sggu"].plurals[0] = "=scale...";
    strings["Scale##sggu"].plurals[0] = "=Scale";
    strings["randomize...##sggu"].plurals[0] = "=randomize...";
    strings["Minimum##sggu"].plurals[0] = "=Minimum";
    strings["Maximum##sggu"].plurals[0] = "=Maximum";
    strings["Nibble mode##sggu1"].plurals[0] = "=Nibble mode";
    strings["Randomize##sggu"].plurals[0] = "=Randomize";
    strings["invert values##sggu1"].plurals[0] = "=invert values";
    strings["flip selection##sggu"].plurals[0] = "=flip selection";
    strings["collapse/expand amount##CollapseAmount"].plurals[0] = "=collapse/expand amount##CollapseAmount";
    strings["collapse##sggu"].plurals[0] = "=collapse";
    strings["expand##sggu"].plurals[0] = "=expand";
    strings["collapse pattern##sggu"].plurals[0] = "=collapse pattern";
    strings["expand pattern##sggu"].plurals[0] = "=expand pattern";
    strings["collapse song##sggu"].plurals[0] = "=collapse song";
    strings["expand song##sggu"].plurals[0] = "=expand song";
    strings["find/replace##sggu"].plurals[0] = "=find/replace";
    strings["Furnace has been started in Safe Mode.\nthis means that:\n\n- software rendering is being used\n- audio output may not work\n- font loading is disabled\n\ncheck any settings which may have made Furnace start up in this mode.\nfont loading is one of these.##sggu"].plurals[0] = "=Furnace has been started in Safe Mode.\nthis means that:\n\n- software rendering is being used\n- audio output may not work\n- font loading is disabled\n\ncheck any settings which may have made Furnace start up in this mode.\nfont loading is one of these.";
    strings["Unsaved changes! Save changes before opening file?##sggu0"].plurals[0] = "=Unsaved changes! Save changes before opening file?";
    strings["Unsaved changes! Save changes before opening file?##sggu2"].plurals[0] = "=Unsaved changes! Save changes before opening file?";
    strings["Error while loading file! (%s)##sggu0"].plurals[0] = "=Error while loading file! (%s)";
    strings["Unsaved changes! Save changes before quitting?##sggu"].plurals[0] = "=Unsaved changes! Save changes before quitting?";
    strings["error while loading fonts! please check your settings.##sggu0"].plurals[0] = "=error while loading fonts! please check your settings.";
    strings["File##menubar"].plurals[0] = "=File##menubar";
    strings["file##menubar"].plurals[0] = "=file##menubar";
    strings["new...##sggu"].plurals[0] = "=new...";
    strings["Unsaved changes! Save changes before creating a new song?##sggu"].plurals[0] = "=Unsaved changes! Save changes before creating a new song?";
    strings["open...##sggu"].plurals[0] = "=open...";
    strings["Unsaved changes! Save changes before opening another file?##sggu"].plurals[0] = "=Unsaved changes! Save changes before opening another file?";
    strings["open recent##sggu"].plurals[0] = "=open recent";
    strings["Unsaved changes! Save changes before opening file?##sggu1"].plurals[0] = "=Unsaved changes! Save changes before opening file?";
    strings["nothing here yet##sggu"].plurals[0] = "=nothing here yet";
    strings["clear history##sggu"].plurals[0] = "=clear history";
    strings["Are you sure you want to clear the recent file list?##sggu"].plurals[0] = "=Are you sure you want to clear the recent file list?";
    strings["save##sggu"].plurals[0] = "=save";
    strings["Error while saving file! (%s)##sggu0"].plurals[0] = "=Error while saving file! (%s)";
    strings["save as...##sggu"].plurals[0] = "=save as...";
    strings["export audio...##sggu0"].plurals[0] = "=export audio...";
    strings["export VGM...##sggu0"].plurals[0] = "=export VGM...";
    strings["export .dmf (1.1.3+)...##sggu0"].plurals[0] = "=export .dmf (1.1.3+)...";
    strings["export .dmf (1.0/legacy)...##sggu0"].plurals[0] = "=export .dmf (1.0/legacy)...";
    strings["export ZSM...##sggu0"].plurals[0] = "=export ZSM...";
    strings["export Amiga validation data...##sggu0"].plurals[0] = "=export Amiga validation data...";
    strings["export text...##sggu0"].plurals[0] = "=export text...";
    strings["export command stream...##sggu0"].plurals[0] = "=export command stream...";
    strings["export Furnace module...##sggu"].plurals[0] = "=export Furnace module...";
    strings["export audio...##sggu1"].plurals[0] = "=export audio...";
    strings["export VGM...##sggu1"].plurals[0] = "=export VGM...";
    strings["export .dmf (1.1.3+)...##sggu1"].plurals[0] = "=export .dmf (1.1.3+)...";
    strings["export .dmf (1.0/legacy)...##sggu1"].plurals[0] = "=export .dmf (1.0/legacy)...";
    strings["export ZSM...##sggu1"].plurals[0] = "=export ZSM...";
    strings["export Amiga validation data...##sggu1"].plurals[0] = "=export Amiga validation data...";
    strings["export text...##sggu1"].plurals[0] = "=export text...";
    strings["export command stream...##sggu1"].plurals[0] = "=export command stream...";
    strings["export...##sggu"].plurals[0] = "=export...";
    strings["manage chips##sggu"].plurals[0] = "=manage chips";
    strings["add chip...##sggu"].plurals[0] = "=add chip...";
    strings["cannot add chip! (##sggu"].plurals[0] = "=cannot add chip! (";
    strings["configure chip...##sggu"].plurals[0] = "=configure chip...";
    strings["change chip...##sggu"].plurals[0] = "=change chip...";
    strings["Preserve channel positions##sggu0"].plurals[0] = "=Preserve channel positions";
    strings["remove chip...##sggu"].plurals[0] = "=remove chip...";
    strings["Preserve channel positions##sggu1"].plurals[0] = "=Preserve channel positions";
    strings["cannot remove chip! (##sggu"].plurals[0] = "=cannot remove chip! (";
    strings["cannot change chip! (##sggu"].plurals[0] = "=cannot change chip! (";
    strings["open built-in assets directory##sggu"].plurals[0] = "=open built-in assets directory";
    strings["restore backup##sggu"].plurals[0] = "=restore backup";
    strings["exit...##sggu"].plurals[0] = "=exit...";
    strings["Unsaved changes! Save before quitting?##sggu"].plurals[0] = "=Unsaved changes! Save before quitting?";
    strings["Edit##menubar"].plurals[0] = "=Edit##menubar";
    strings["edit##menubar"].plurals[0] = "=edit##menubar";
    strings["undo##sggu"].plurals[0] = "=undo";
    strings["redo##sggu"].plurals[0] = "=redo";
    strings["clear...##sggu"].plurals[0] = "=clear...";
    strings["Settings##menubar"].plurals[0] = "=Settings##menubar";
    strings["settings##menubar"].plurals[0] = "=settings##menubar";
    strings["full screen##sggu"].plurals[0] = "=full screen";
    strings["lock layout##sggu"].plurals[0] = "=lock layout";
    strings["pattern visualizer##sggu"].plurals[0] = "=pattern visualizer";
    strings["reset layout##sggu"].plurals[0] = "=reset layout";
    strings["Are you sure you want to reset the workspace layout?##sggu"].plurals[0] = "=Are you sure you want to reset the workspace layout?";
    strings["switch to mobile view##sggu"].plurals[0] = "=switch to mobile view";
    strings["manage presets...##sggu"].plurals[0] = "=manage presets...";
    strings["settings...##sggu"].plurals[0] = "=settings...";
    strings["Window##menubar"].plurals[0] = "=Window##menubar";
    strings["window##menubar"].plurals[0] = "=window##menubar";
    strings["song information##sggu"].plurals[0] = "=song information";
    strings["subsongs##sggu"].plurals[0] = "=subsongs";
    strings["speed##sggu"].plurals[0] = "=speed";
    strings["assets##sggu"].plurals[0] = "=assets";
    strings["instruments##sggu"].plurals[0] = "=instruments";
    strings["wavetables##sggu"].plurals[0] = "=wavetables";
    strings["samples##sggu"].plurals[0] = "=samples";
    strings["orders##sggu"].plurals[0] = "=orders";
    strings["pattern##sggu"].plurals[0] = "=pattern";
    strings["mixer##sggu"].plurals[0] = "=mixer";
    strings["grooves##sggu"].plurals[0] = "=grooves";
    strings["channels##sggu"].plurals[0] = "=channels";
    strings["pattern manager##sggu"].plurals[0] = "=pattern manager";
    strings["chip manager##sggu"].plurals[0] = "=chip manager";
    strings["compatibility flags##sggu"].plurals[0] = "=compatibility flags";
    strings["song##sggu"].plurals[0] = "=song";
    strings["visualizers##sggu"].plurals[0] = "=visualizers";
    strings["tempo##sggu"].plurals[0] = "=tempo";
    strings["debug##sggu"].plurals[0] = "=debug";
    strings["song comments##sggu"].plurals[0] = "=song comments";
    strings["instrument editor##sggu"].plurals[0] = "=instrument editor";
    strings["wavetable editor##sggu"].plurals[0] = "=wavetable editor";
    strings["sample editor##sggu"].plurals[0] = "=sample editor";
    strings["play/edit controls##sggu"].plurals[0] = "=play/edit controls";
    strings["piano/input pad##sggu"].plurals[0] = "=piano/input pad";
    strings["oscilloscope (master)##sggu"].plurals[0] = "=oscilloscope (master)";
    strings["oscilloscope (per-channel)##sggu"].plurals[0] = "=oscilloscope (per-channel)";
    strings["oscilloscope (X-Y)##sggu"].plurals[0] = "=oscilloscope (X-Y)";
    strings["volume meter##sggu"].plurals[0] = "=volume meter";
    strings["clock##sggu"].plurals[0] = "=clock";
    strings["register view##sggu"].plurals[0] = "=register view";
    strings["log viewer##sggu"].plurals[0] = "=log viewer";
    strings["statistics##sggu"].plurals[0] = "=statistics";
    strings["memory composition##sggu"].plurals[0] = "=memory composition";
    strings["spoiler##sggu"].plurals[0] = "=spoiler";
    strings["Help##menubar"].plurals[0] = "=Help##menubar";
    strings["help##menubar"].plurals[0] = "=help##menubar";
    strings["effect list##sggu"].plurals[0] = "=effect list";
    strings["debug menu##sggu"].plurals[0] = "=debug menu";
    strings["inspector##sggu"].plurals[0] = "=inspector";
    strings["panic##sggu"].plurals[0] = "=panic";
    strings["about...##sggu"].plurals[0] = "=about...";
    strings["| Speed %d:%d##sggu"].plurals[0] = "=| Speed %d:%d";
    strings["| Speed %d##sggu"].plurals[0] = "=| Speed %d";
    strings["| Groove##sggu"].plurals[0] = "=| Groove";
    strings[" @ %gHz (%g BPM) ##sggu"].plurals[0] = "= @ %gHz (%g BPM) ";
    strings["| Order %.2X/%.2X ##sggu"].plurals[0] = "=| Order %.2X/%.2X ";
    strings["| Order %d/%d ##sggu"].plurals[0] = "=| Order %d/%d ";
    strings["| Row %.2X/%.2X ##sggu"].plurals[0] = "=| Row %.2X/%.2X ";
    strings["| Row %d/%d ##sggu"].plurals[0] = "=| Row %d/%d ";
    strings["Don't you have anything better to do?##sggu"].plurals[0] = "=Don't you have anything better to do?";
    strings["%d years ##sggu"].plurals[0] = "=%d year ";
    strings["%d years ##sggu"].plurals[1] = "=%d years ";
    strings["%d months ##sggu"].plurals[0] = "=%d month ";
    strings["%d months ##sggu"].plurals[1] = "=%d months ";
    strings["%d days ##sggu"].plurals[0] = "=%d day ";
    strings["%d days ##sggu"].plurals[1] = "=%d days ";
    strings["Note off (cut)##sggu"].plurals[0] = "=Note off (cut)";
    strings["Note off (release)##sggu"].plurals[0] = "=Note off (release)";
    strings["Macro release only##sggu"].plurals[0] = "=Macro release only";
    strings["Note on: %s##sggu"].plurals[0] = "=Note on: %s";
    strings["Ins %d: <invalid>##sggu"].plurals[0] = "=Ins %d: <invalid>";
    strings["Ins %d: %s##sggu"].plurals[0] = "=Ins %d: %s";
    strings["Set volume: %d (%.2X, INVALID!)##sggu"].plurals[0] = "=Set volume: %d (%.2X, INVALID!)";
    strings["Set volume: %d (%.2X, %d%%)##sggu"].plurals[0] = "=Set volume: %d (%.2X, %d%%)";
    strings["| modified##sggu"].plurals[0] = "=| modified";
    strings["there was an error in the file dialog! you may want to report this issue to:\nhttps://github.com/tildearrow/furnace/issues\ncheck the Log Viewer (window > log viewer) for more information.\n\nfor now please disable the system file picker in Settings > General.##sggu"].plurals[0] = "=there was an error in the file dialog! you may want to report this issue to:\nhttps://github.com/tildearrow/furnace/issues\ncheck the Log Viewer (window > log viewer) for more information.\n\nfor now please disable the system file picker in Settings > General.";
    strings["can't do anything without Storage permissions!##sggu"].plurals[0] = "=can't do anything without Storage permissions!";
    strings["Zenity/KDialog not available!\nplease install one of these, or disable the system file picker in Settings > General.##sggu"].plurals[0] = "=Zenity/KDialog not available!\nplease install one of these, or disable the system file picker in Settings > General.";
    strings["Error while loading file! (%s)##sggu2"].plurals[0] = "=Error while loading file! (%s)";
    strings["Error while saving file! (%s)##sggu1"].plurals[0] = "=Error while saving file! (%s)";
    strings["Error while loading file! (%s)##sggu3"].plurals[0] = "=Error while loading file! (%s)";
    strings["Error while saving file! (%s)##sggu2"].plurals[0] = "=Error while saving file! (%s)";
    strings["Error while saving file! (%s)##sggu3"].plurals[0] = "=Error while saving file! (%s)";
    strings["error while saving instrument! only the following instrument types are supported:\n- FM (OPN)\n- SN76489/Sega PSG\n- Game Boy\n- PC Engine\n- NES\n- C64\n- FM (OPLL)\n- FDS##sggu##sggu"].plurals[0] = "=error while saving instrument! only the following instrument types are supported:\n- FM (OPN)\n- SN76489/Sega PSG\n- Game Boy\n- PC Engine\n- NES\n- C64\n- FM (OPLL)\n- FDS";
    strings["there were some errors while loading samples:\n#sggu"].plurals[0] = "=there were some errors while loading samples:\n";
    strings["...but you haven't selected a sample!##sggu0"].plurals[0] = "=...but you haven't selected a sample!";
    strings["could not save sample! open Log Viewer for more information.##sggu0"].plurals[0] = "=could not save sample! open Log Viewer for more information.";
    strings["could not save sample! open Log Viewer for more information.##sggu1"].plurals[0] = "=could not save sample! open Log Viewer for more information.";
    strings["there were some warnings/errors while loading instruments:\n#sggu"].plurals[0] = "=there were some warnings/errors while loading instruments:\n";
    strings["> %s: cannot load instrument! (%s)\n#sggu"].plurals[0] = "=> %s: cannot load instrument! (%s)\n";
    strings["...but you haven't selected an instrument!##sggu0"].plurals[0] = "=...but you haven't selected an instrument!";
    strings["cannot load instrument! (##sggu"].plurals[0] = "=cannot load instrument! (";
    strings["congratulations! you managed to load nothing.\nyou are entitled to a bug report.##sggu"].plurals[0] = "=congratulations! you managed to load nothing.\nyou are entitled to a bug report.";
    strings["there were some errors while loading wavetables:\n##sggu"].plurals[0] = "=there were some errors while loading wavetables:\n";
    strings["cannot load wavetable! (##sggu"].plurals[0] = "=cannot load wavetable! (";
    strings["...but you haven't selected a wavetable!##sggu"].plurals[0] = "=...but you haven't selected a wavetable!";
    strings["could not open file!##sggu"].plurals[0] = "=could not open file!";
    strings["Could not write ZSM! (%s)##sggu"].plurals[0] = "=Could not write ZSM! (%s)";
    strings["could not write text! (%s)##sggu"].plurals[0] = "=could not write text! (%s)";
    strings["could not write command stream! (%s)##sggu"].plurals[0] = "=could not write command stream! (%s)";
    strings["could not write tildearrow version Furnace module! (%s)##sggu"].plurals[0] = "=could not write tildearrow version Furnace module! (%s)";
    strings["Error while loading file! (%s)##sggu4"].plurals[0] = "=Error while loading file! (%s)";
    strings["You opened: %s##sggu"].plurals[0] = "=You opened: %s";
    strings["You opened:##sggu"].plurals[0] = "=You opened:##sggu";
    strings["You saved: %s##sggu"].plurals[0] = "=You saved: %s";
    strings["Rendering...###Rendering..."].plurals[0] = "=Rendering...###Rendering...";
    strings["Please wait...##sggu"].plurals[0] = "=Please wait...";
    strings["Abort##sggu"].plurals[0] = "=Abort";
    strings["New Song###New Song"].plurals[0] = "=New Song###New Song";
    strings["Export###Export"].plurals[0] = "=Export###Export";
    strings["Error###Error"].plurals[0] = "=Error###Error";
    strings["OK##sggu0"].plurals[0] = "=OK";
    strings["Warning###Warning"].plurals[0] = "=Warning###Warning";
    strings["Yes##sggu0"].plurals[0] = "=Yes";
    strings["No##sggu0"].plurals[0] = "=No";
    strings["Yes##sggu1"].plurals[0] = "=Yes";
    strings["No##sggu1"].plurals[0] = "=No";
    strings["Yes##sggu2"].plurals[0] = "=Yes";
    strings["No##sggu2"].plurals[0] = "=No";
    strings["Yes##sggu3"].plurals[0] = "=Yes";
    strings["No##sggu3"].plurals[0] = "=No";
    strings["Yes##sggu7"].plurals[0] = "=Yes";
    strings["Yes##sggu8"].plurals[0] = "=Yes";
    strings["Yes##sggu9"].plurals[0] = "=Yes";
    strings["Yes##sggu10"].plurals[0] = "=Yes";
    strings["Yes##sggu11"].plurals[0] = "=Yes";
    strings["No##sggu8"].plurals[0] = "=No";
    strings["No##sggu9"].plurals[0] = "=No";
    strings["No##sggu10"].plurals[0] = "=No";
    strings["No##sggu11"].plurals[0] = "=No";
    strings["No##sggu12"].plurals[0] = "=No";
    strings["Cancel##sggu4"].plurals[0] = "=Cancel";
    strings["Cancel##sggu5"].plurals[0] = "=Cancel";
    strings["Cancel##sggu6"].plurals[0] = "=Cancel";
    strings["Cancel##sggu7"].plurals[0] = "=Cancel";
    strings["Cancel##sggu8"].plurals[0] = "=Cancel";
    strings["Cancel##sggu0"].plurals[0] = "=Cancel";
    strings["Erasing##sggu"].plurals[0] = "=Erasing";
    strings["All subsongs##sggu"].plurals[0] = "=All subsongs";
    strings["Current subsong##sggu"].plurals[0] = "=Current subsong";
    strings["Orders##sggu"].plurals[0] = "=Orders";
    strings["Pattern##sggu"].plurals[0] = "=Pattern";
    strings["Instruments##sggu"].plurals[0] = "=Instruments";
    strings["Wavetables##sggu"].plurals[0] = "=Wavetables";
    strings["Samples##sggu"].plurals[0] = "=Samples";
    strings["Optimization##sggu"].plurals[0] = "=Optimization";
    strings["De-duplicate patterns##sggu"].plurals[0] = "=De-duplicate patterns";
    strings["Remove unused instruments##sggu"].plurals[0] = "=Remove unused instruments";
    strings["Remove unused samples##sggu"].plurals[0] = "=Remove unused samples";
    strings["Never mind! Cancel##sggu1"].plurals[0] = "=Never mind! Cancel";
    strings["Yes##sggu4"].plurals[0] = "=Yes";
    strings["No##sggu4"].plurals[0] = "=No";
    strings["Yes##sggu5"].plurals[0] = "=Yes";
    strings["No##sggu5"].plurals[0] = "=No";
    strings["Yes##sggu6"].plurals[0] = "=Yes";
    strings["No##sggu6"].plurals[0] = "=No";
    strings["OK##sggu1"].plurals[0] = "=OK";
    strings["Drum kit mode:##sggu"].plurals[0] = "=Drum kit mode:";
    strings["Normal##sggu"].plurals[0] = "=Normal";
    strings["12 samples per octave##sggu"].plurals[0] = "=12 samples per octave";
    strings["Starting octave##sggu"].plurals[0] = "=Starting octave";
    strings["too many instruments!##sggu"].plurals[0] = "=too many instruments!";
    strings["too many wavetables!##sggu"].plurals[0] = "=too many wavetables!";
    strings["Select Instrument###Select Instrument"].plurals[0] = "=Select Instrument###Select Instrument";
    strings["this is an instrument bank! select which one to use:##sggu"].plurals[0] = "=this is an instrument bank! select which one to use:";
    strings["this is an instrument bank! select which ones to load:##sggu"].plurals[0] = "=this is an instrument bank! select which ones to load:";
    strings["All##sggu"].plurals[0] = "=All";
    strings["None##sggu"].plurals[0] = "=None";
    strings["OK##sggu2"].plurals[0] = "=OK";
    strings["Cancel##sggu2"].plurals[0] = "=Cancel";
    strings["...but you haven't selected an instrument!##sggu1"].plurals[0] = "=...but you haven't selected an instrument!";
    strings["Import Raw Sample###Import Raw Sample"].plurals[0] = "=Import Raw Sample###Import Raw Sample";
    strings["Data type:##sggu"].plurals[0] = "=Data type:";
    strings["Sample rate##sggu"].plurals[0] = "=Sample rate";
    strings["Channels##sggu"].plurals[0] = "=Channels";
    strings["(will be mixed down to mono)##sggu"].plurals[0] = "=(will be mixed down to mono)";
    strings["Unsigned##sggu"].plurals[0] = "=Unsigned";
    strings["Big endian##sggu"].plurals[0] = "=Big endian";
    strings["Swap nibbles##sggu"].plurals[0] = "=Swap nibbles";
    strings["Swap words##sggu"].plurals[0] = "=Swap words";
    strings["Encoding:##sggu"].plurals[0] = "=Encoding:";
    strings["Reverse bit order##sggu"].plurals[0] = "=Reverse bit order";
    strings["OK##sggu3"].plurals[0] = "=OK";
    strings["...but you haven't selected a sample!##sggu1"].plurals[0] = "=...but you haven't selected a sample!";
    strings["Cancel##sggu3"].plurals[0] = "=Cancel";
    strings["Error! No string provided!##sggu"].plurals[0] = "=Error! No string provided!";
    strings["OK##sggu4"].plurals[0] = "=OK";
    strings["%.0fµs##sggu"].plurals[0] = "=%.0fµs";
    strings["error while loading fonts! please check your settings.##sggu1"].plurals[0] = "=error while loading fonts! please check your settings.";
    strings["it appears I couldn't load these fonts. any setting you can check?##sggu"].plurals[0] = "=it appears I couldn't load these fonts. any setting you can check?";
    strings["could not init renderer! %s##sggu"].plurals[0] = "=could not init renderer! %s";
    strings["\r\nthe render driver has been set to a safe value. please restart Furnace.##sggu"].plurals[0] = "=\r\nthe render driver has been set to a safe value. please restart Furnace.";
    strings["could not open window! %s##sggu"].plurals[0] = "=could not open window! %s";
    strings["error while loading fonts! please check your settings.##sggu2"].plurals[0] = "=error while loading fonts! please check your settings.";
    strings["could NOT save layout! %s##sggu"].plurals[0] = "=could NOT save layout! %s";

    //   sggc  src/gui/guiConst.cpp

    strings["Generic Sample##sggc"].plurals[0] = "=Generic Sample";
    strings["Beeper##sggc"].plurals[0] = "=Beeper";
    strings["VRC6 (saw)##sggc"].plurals[0] = "=VRC6 (saw)";
    strings["OPL (drums)##sggc"].plurals[0] = "=OPL (drums)";
    strings["PowerNoise (noise)##sggc"].plurals[0] = "=PowerNoise (noise)";
    strings["PowerNoise (slope)##sggc"].plurals[0] = "=PowerNoise (slope)";
    strings["Forward##sggc"].plurals[0] = "=Forward";
    strings["Backward##sggc"].plurals[0] = "=Backward";
    strings["Ping pong##sggc"].plurals[0] = "=Ping pong";
    strings["1-bit PCM##sggc"].plurals[0] = "=1-bit PCM";
    strings["1-bit DPCM##sggc"].plurals[0] = "=1-bit DPCM";
    strings["8-bit PCM##sggc"].plurals[0] = "=8-bit PCM";
    strings["8-bit µ-law PCM##sggc"].plurals[0] = "=8-bit µ-law PCM";
    strings["16-bit PCM##sggc"].plurals[0] = "=16-bit PCM";
    strings["none##sggc"].plurals[0] = "=none";
    strings["linear##sggc"].plurals[0] = "=linear";
    strings["cubic spline##sggc"].plurals[0] = "=cubic spline";
    strings["blep synthesis##sggc"].plurals[0] = "=blep synthesis";
    strings["sinc##sggc"].plurals[0] = "=sinc";
    strings["best possible##sggc"].plurals[0] = "=best possible";
    strings["Pitch##sggc"].plurals[0] = "=Pitch";
    strings["Song##sggc"].plurals[0] = "=Song";
    strings["Time##sggc"].plurals[0] = "=Time";
    strings["Speed##sggc0"].plurals[0] = "=Speed";
    strings["Panning##sggc"].plurals[0] = "=Panning";
    strings["Volume##sggc"].plurals[0] = "=Volume";
    strings["System (Primary)##sggc"].plurals[0] = "=System (Primary)";
    strings["System (Secondary)##sggc"].plurals[0] = "=System (Secondary)";
    strings["Miscellaneous##sggc"].plurals[0] = "=Miscellaneous";
    strings["Invalid##sggc"].plurals[0] = "=Invalid";

    strings["---Global##sggc"].plurals[0] = "=---Global";
    strings["New##sggc"].plurals[0] = "=New";
    strings["Open file##sggc"].plurals[0] = "=Open file";
    strings["Restore backup##sggc"].plurals[0] = "=Restore backup";
    strings["Save file##sggc"].plurals[0] = "=Save file";
    strings["Save as##sggc"].plurals[0] = "=Save as";
    strings["Export##sggc"].plurals[0] = "=Export";
    strings["Undo##sggc"].plurals[0] = "=Undo";
    strings["Redo##sggc"].plurals[0] = "=Redo";
    strings["Exit##sggc"].plurals[0] = "=Exit";
    strings["Play/Stop (toggle)##sggc"].plurals[0] = "=Play/Stop (toggle)";
    strings["Play##sggc"].plurals[0] = "=Play";
    strings["Stop##sggc"].plurals[0] = "=Stop";
    strings["Play (from beginning)##sggc"].plurals[0] = "=Play (from beginning)";
    strings["Play (repeat pattern)##sggc"].plurals[0] = "=Play (repeat pattern)";
    strings["Play from cursor##sggc"].plurals[0] = "=Play from cursor";
    strings["Step row##sggc"].plurals[0] = "=Step row";
    strings["Octave up##sggc"].plurals[0] = "=Octave up";
    strings["Octave down##sggc"].plurals[0] = "=Octave down";
    strings["Previous instrument##sggc"].plurals[0] = "=Previous instrument";
    strings["Next instrument##sggc"].plurals[0] = "=Next instrument";
    strings["Increase edit step##sggc"].plurals[0] = "=Increase edit step";
    strings["Decrease edit step##sggc"].plurals[0] = "=Decrease edit step";
    strings["Toggle edit mode##sggc"].plurals[0] = "=Toggle edit mode";
    strings["Metronome##sggc"].plurals[0] = "=Metronome";
    strings["Toggle repeat pattern##sggc"].plurals[0] = "=Toggle repeat pattern";
    strings["Follow orders##sggc"].plurals[0] = "=Follow orders";
    strings["Follow pattern##sggc"].plurals[0] = "=Follow pattern";
    strings["Toggle full-screen##sggc"].plurals[0] = "=Toggle full-screen";
    strings["Request voice from TX81Z##sggc"].plurals[0] = "=Request voice from TX81Z";
    strings["Panic##sggc"].plurals[0] = "=Panic";
    strings["Clear song data##sggc"].plurals[0] = "=Clear song data";
    strings["Command Palette##sggc"].plurals[0] = "=Command Palette";
    strings["Recent files (Palette)##sggc"].plurals[0] = "=Recent files (Palette)";
    strings["Instruments (Palette)##sggc"].plurals[0] = "=Instruments (Palette)";
    strings["Samples (Palette)##sggc"].plurals[0] = "=Samples (Palette)";
    strings["Change instrument (Palette)##sggc"].plurals[0] = "=Change instrument (Palette)";
    strings["Add chip (Palette)##sggc"].plurals[0] = "=Add chip (Palette)";
    strings["Edit Controls##sggc"].plurals[0] = "=Edit Controls";
    strings["Orders##sggc"].plurals[0] = "=Orders";
    strings["Instrument List##sggc"].plurals[0] = "=Instrument List";
    strings["Instrument Editor##sggc"].plurals[0] = "=Instrument Editor";
    strings["Song Information##sggc"].plurals[0] = "=Song Information";
    strings["Speed##sggc1"].plurals[0] = "=Speed";
    strings["Pattern##sggc"].plurals[0] = "=Pattern";
    strings["Wavetable List##sggc"].plurals[0] = "=Wavetable List";
    strings["Wavetable Editor##sggc"].plurals[0] = "=Wavetable Editor";
    strings["Sample List##sggc"].plurals[0] = "=Sample List";
    strings["Sample Editor##sggc"].plurals[0] = "=Sample Editor";
    strings["About##sggc"].plurals[0] = "=About";
    strings["Settings##sggc"].plurals[0] = "=Settings";
    strings["Mixer##sggc"].plurals[0] = "=Mixer";
    strings["Debug Menu##sggc"].plurals[0] = "=Debug Menu";
    strings["Oscilloscope (master)##sggc"].plurals[0] = "=Oscilloscope (master)";
    strings["Volume Meter##sggc"].plurals[0] = "=Volume Meter";
    strings["Statistics##sggc"].plurals[0] = "=Statistics";
    strings["Compatibility Flags##sggc"].plurals[0] = "=Compatibility Flags";
    strings["Piano##sggc"].plurals[0] = "=Piano";
    strings["Song Comments##sggc"].plurals[0] = "=Song Comments";
    strings["Channels##sggc"].plurals[0] = "=Channels";
    strings["Pattern Manager##sggc"].plurals[0] = "=Pattern Manager";
    strings["Chip Manager##sggc"].plurals[0] = "=Chip Manager";
    strings["Register View##sggc"].plurals[0] = "=Register View";
    strings["Log Viewer##sggc"].plurals[0] = "=Log Viewer";
    strings["Effect List##sggc"].plurals[0] = "=Effect List";
    strings["Oscilloscope (per-channel)##sggc"].plurals[0] = "=Oscilloscope (per-channel)";
    strings["Subsongs##sggc"].plurals[0] = "=Subsongs";
    strings["Find/Replace##sggc"].plurals[0] = "=Find/Replace";
    strings["Clock##sggc"].plurals[0] = "=Clock";
    strings["Grooves##sggc"].plurals[0] = "=Grooves";
    strings["Oscilloscope (X-Y)##sggc"].plurals[0] = "=Oscilloscope (X-Y)";
    strings["Memory Composition##sggc"].plurals[0] = "=Memory Composition";
    strings["Command Stream Player##sggc"].plurals[0] = "=Command Stream Player";
    strings["User Presets##sggc"].plurals[0] = "=User Presets";
    strings["Collapse/expand current window##sggc"].plurals[0] = "=Collapse/expand current window";
    strings["Close current window##sggc"].plurals[0] = "=Close current window";
    strings["---Pattern##sggc"].plurals[0] = "=---Pattern";
    strings["Transpose (+1)##sggc"].plurals[0] = "=Transpose (+1)";
    strings["Transpose (-1)##sggc"].plurals[0] = "=Transpose (-1)";
    strings["Transpose (+1 octave)##sggc"].plurals[0] = "=Transpose (+1 octave)";
    strings["Transpose (-1 octave)##sggc"].plurals[0] = "=Transpose (-1 octave)";
    strings["Increase values (+1)##sggc"].plurals[0] = "=Increase values (+1)";
    strings["Increase values (-1)##sggc"].plurals[0] = "=Increase values (-1)";
    strings["Increase values (+16)##sggc"].plurals[0] = "=Increase values (+16)";
    strings["Increase values (-16)##sggc"].plurals[0] = "=Increase values (-16)";
    strings["Select all##sggc0"].plurals[0] = "=Select all";
    strings["Cut##sggc0"].plurals[0] = "=Cut";
    strings["Copy##sggc0"].plurals[0] = "=Copy";
    strings["Paste##sggc0"].plurals[0] = "=Paste";
    strings["Paste Mix (foreground)##sggc"].plurals[0] = "=Paste Mix (foreground)";
    strings["Paste Mix (background)##sggc"].plurals[0] = "=Paste Mix (background)";
    strings["Paste Flood##sggc"].plurals[0] = "=Paste Flood";
    strings["Paste Overflow##sggc"].plurals[0] = "=Paste Overflow";
    strings["Move cursor up##sggc"].plurals[0] = "=Move cursor up";
    strings["Move cursor down##sggc"].plurals[0] = "=Move cursor down";
    strings["Move cursor left##sggc"].plurals[0] = "=Move cursor left";
    strings["Move cursor right##sggc"].plurals[0] = "=Move cursor right";
    strings["Move cursor up by one (override Edit Step)##sggc"].plurals[0] = "=Move cursor up by one (override Edit Step)";
    strings["Move cursor down by one (override Edit Step)##sggc"].plurals[0] = "=Move cursor down by one (override Edit Step)";
    strings["Move cursor to previous channel##sggc"].plurals[0] = "=Move cursor to previous channel";
    strings["Move cursor to next channel##sggc"].plurals[0] = "=Move cursor to next channel";
    strings["Move cursor to next channel (overflow)##sggc"].plurals[0] = "=Move cursor to next channel (overflow)";
    strings["Move cursor to previous channel (overflow)##sggc"].plurals[0] = "=Move cursor to previous channel (overflow)";
    strings["Move cursor to beginning of pattern##sggc"].plurals[0] = "=Move cursor to beginning of pattern";
    strings["Move cursor to end of pattern##sggc"].plurals[0] = "=Move cursor to end of pattern";
    strings["Move cursor up (coarse)##sggc"].plurals[0] = "=Move cursor up (coarse)";
    strings["Move cursor down (coarse)##sggc"].plurals[0] = "=Move cursor down (coarse)";
    strings["Expand selection upwards##sggc"].plurals[0] = "=Expand selection upwards";
    strings["Expand selection downwards##sggc"].plurals[0] = "=Expand selection downwards";
    strings["Expand selection to the left##sggc"].plurals[0] = "=Expand selection to the left";
    strings["Expand selection to the right##sggc"].plurals[0] = "=Expand selection to the right";
    strings["Expand selection upwards by one (override Edit Step)##sggc"].plurals[0] = "=Expand selection upwards by one (override Edit Step)";
    strings["Expand selection downwards by one (override Edit Step)##sggc"].plurals[0] = "=Expand selection downwards by one (override Edit Step)";
    strings["Expand selection to beginning of pattern##sggc"].plurals[0] = "=Expand selection to beginning of pattern";
    strings["Expand selection to end of pattern##sggc"].plurals[0] = "=Expand selection to end of pattern";
    strings["Expand selection upwards (coarse)##sggc"].plurals[0] = "=Expand selection upwards (coarse)";
    strings["Expand selection downwards (coarse)##sggc"].plurals[0] = "=Expand selection downwards (coarse)";
    strings["Delete##sggc"].plurals[0] = "=Delete";
    strings["Pull delete##sggc"].plurals[0] = "=Pull delete";
    strings["Insert##sggc"].plurals[0] = "=Insert";
    strings["Mute channel at cursor##sggc"].plurals[0] = "=Mute channel at cursor";
    strings["Solo channel at cursor##sggc"].plurals[0] = "=Solo channel at cursor";
    strings["Unmute all channels##sggc"].plurals[0] = "=Unmute all channels";
    strings["Go to next order##sggc"].plurals[0] = "=Go to next order";
    strings["Go to previous order##sggc"].plurals[0] = "=Go to previous order";
    strings["Collapse channel at cursor##sggc"].plurals[0] = "=Collapse channel at cursor";
    strings["Increase effect columns##sggc"].plurals[0] = "=Increase effect columns";
    strings["Decrease effect columns##sggc"].plurals[0] = "=Decrease effect columns";
    strings["Interpolate##sggc"].plurals[0] = "=Interpolate";
    strings["Fade##sggc"].plurals[0] = "=Fade";
    strings["Invert values##sggc"].plurals[0] = "=Invert values";
    strings["Flip selection##sggc"].plurals[0] = "=Flip selection";
    strings["Collapse rows##sggc"].plurals[0] = "=Collapse rows";
    strings["Expand rows##sggc"].plurals[0] = "=Expand rows";
    strings["Collapse pattern##sggc"].plurals[0] = "=Collapse pattern";
    strings["Expand pattern##sggc"].plurals[0] = "=Expand pattern";
    strings["Collapse song##sggc"].plurals[0] = "=Collapse song";
    strings["Expand song##sggc"].plurals[0] = "=Expand song";
    strings["Set note input latch##sggc"].plurals[0] = "=Set note input latch";
    strings["Change mobile scroll mode##sggc"].plurals[0] = "=Change mobile scroll mode";
    strings["Clear note input latch##sggc"].plurals[0] = "=Clear note input latch";
    strings["---Instrument list##sggc"].plurals[0] = "=---Instrument list";
    strings["Add instrument##sggc0"].plurals[0] = "=Add instrument";
    strings["Duplicate instrument##sggc0"].plurals[0] = "=Duplicate instrument";
    strings["Open instrument##sggc0"].plurals[0] = "=Open instrument";
    strings["Open instrument (replace current)##sggc0"].plurals[0] = "=Open instrument (replace current)";
    strings["Save instrument##sggc0"].plurals[0] = "=Save instrument";
    strings["Export instrument (.dmp)##sggc"].plurals[0] = "=Export instrument (.dmp)";
    strings["Move instrument up in list##sggc0"].plurals[0] = "=Move instrument up in list";
    strings["Move instrument down in list##sggc0"].plurals[0] = "=Move instrument down in list";
    strings["Delete instrument##sggc0"].plurals[0] = "=Delete instrument";
    strings["Edit instrument##sggc0"].plurals[0] = "=Edit instrument";
    strings["Instrument cursor up##sggc0"].plurals[0] = "=Instrument cursor up";
    strings["Instrument cursor down##sggc0"].plurals[0] = "=Instrument cursor down";
    strings["Instruments: toggle folders/standard view##sggc0"].plurals[0] = "=Instruments: toggle folders/standard view";
    strings["---Wavetable list##sggc"].plurals[0] = "=---Wavetable list";
    strings["Add wavetable##sggc1"].plurals[0] = "=Add wavetable";
    strings["Duplicate wavetable##sggc1"].plurals[0] = "=Duplicate wavetable";
    strings["Open wavetable##sggc1"].plurals[0] = "=Open wavetable";
    strings["Open wavetable (replace current)##sggc1"].plurals[0] = "=Open wavetable (replace current)";
    strings["Save wavetable##sggc1"].plurals[0] = "=Save wavetable";
    strings["Save wavetable (.dmw)##sggc"].plurals[0] = "=Save wavetable (.dmw)";
    strings["Save wavetable (raw)##sggc0"].plurals[0] = "=Save wavetable (raw)";
    strings["Move wavetable up in list##sggc1"].plurals[0] = "=Move wavetable up in list";
    strings["Move wavetable down in list##sggc1"].plurals[0] = "=Move wavetable down in list";
    strings["Delete wavetable##sggc1"].plurals[0] = "=Delete wavetable";
    strings["Edit wavetable##sggc1"].plurals[0] = "=Edit wavetable";
    strings["Wavetable cursor up##sggc1"].plurals[0] = "=Wavetable cursor up";
    strings["Wavetable cursor down##sggc1"].plurals[0] = "=Wavetable cursor down";
    strings["Wavetables: toggle folders/standard view##sggc1"].plurals[0] = "=Wavetables: toggle folders/standard view";
    strings["Paste wavetables from clipboard##sggc"].plurals[0] = "=Paste wavetables from clipboard";
    strings["Paste local wavetables from clipboard##sggc1"].plurals[0] = "=Paste local wavetables from clipboard";
    strings["---Sample list##sggc"].plurals[0] = "=---Sample list";
    strings["Add sample##sggc2"].plurals[0] = "=Add sample";
    strings["Duplicate sample##sggc2"].plurals[0] = "=Duplicate sample";
    strings["Open sample##sggc2"].plurals[0] = "=Open sample";
    strings["Open sample (replace current)##sggc2"].plurals[0] = "=Open sample (replace current)";
    strings["Import raw sample data##sggc"].plurals[0] = "=Import raw sample data";
    strings["Import raw sample data (replace current)##sggc"].plurals[0] = "=Import raw sample data (replace current)";
    strings["Save sample##sggc2"].plurals[0] = "=Save sample";
    strings["Save sample (raw)##sggc1"].plurals[0] = "=Save sample (raw)";
    strings["Move sample up in list##sggc2"].plurals[0] = "=Move sample up in list";
    strings["Move sample down in list##sggc2"].plurals[0] = "=Move sample down in list";
    strings["Delete sample##sggc2"].plurals[0] = "=Delete sample";
    strings["Edit sample##sggc2"].plurals[0] = "=Edit sample";
    strings["Sample cursor up##sggc2"].plurals[0] = "=Sample cursor up";
    strings["Sample cursor down##sggc2"].plurals[0] = "=Sample cursor down";
    strings["Sample preview##sggc"].plurals[0] = "=Sample preview";
    strings["Stop sample preview##sggc"].plurals[0] = "=Stop sample preview";
    strings["Samples: Toggle folders/standard view##sggc2"].plurals[0] = "=Samples: Toggle folders/standard view";
    strings["Samples: Make me a drum kit##sggc"].plurals[0] = "=Samples: Make me a drum kit";
    strings["---Sample editor##sggc"].plurals[0] = "=---Sample editor";
    strings["Sample editor mode: Select##sggc"].plurals[0] = "=Sample editor mode: Select";
    strings["Sample editor mode: Draw##sggc"].plurals[0] = "=Sample editor mode: Draw";
    strings["Sample editor: Cut##sggc1"].plurals[0] = "=Sample editor: Cut";
    strings["Sample editor: Copy##sggc1"].plurals[0] = "=Sample editor: Copy";
    strings["Sample editor: Paste##sggc1"].plurals[0] = "=Sample editor: Paste";
    strings["Sample editor: Paste replace##sggc"].plurals[0] = "=Sample editor: Paste replace";
    strings["Sample editor: Paste mix##sggc"].plurals[0] = "=Sample editor: Paste mix";
    strings["Sample editor: Select all##sggc1"].plurals[0] = "=Sample editor: Select all";
    strings["Sample editor: Resize##sggc"].plurals[0] = "=Sample editor: Resize";
    strings["Sample editor: Resample##sggc"].plurals[0] = "=Sample editor: Resample";
    strings["Sample editor: Amplify##sggc"].plurals[0] = "=Sample editor: Amplify";
    strings["Sample editor: Normalize##sggc"].plurals[0] = "=Sample editor: Normalize";
    strings["Sample editor: Fade in##sggc"].plurals[0] = "=Sample editor: Fade in";
    strings["Sample editor: Fade out##sggc"].plurals[0] = "=Sample editor: Fade out";
    strings["Sample editor: Apply silence##sggc"].plurals[0] = "=Sample editor: Apply silence";
    strings["Sample editor: Insert silence##sggc"].plurals[0] = "=Sample editor: Insert silence";
    strings["Sample editor: Delete##sggc3"].plurals[0] = "=Sample editor: Delete";
    strings["Sample editor: Trim##sggc"].plurals[0] = "=Sample editor: Trim";
    strings["Sample editor: Reverse##sggc"].plurals[0] = "=Sample editor: Reverse";
    strings["Sample editor: Invert##sggc"].plurals[0] = "=Sample editor: Invert";
    strings["Sample editor: Signed/unsigned exchange##sggc"].plurals[0] = "=Sample editor: Signed/unsigned exchange";
    strings["Sample editor: Apply filter##sggc"].plurals[0] = "=Sample editor: Apply filter";
    strings["Sample editor: Crossfade loop points##sggc"].plurals[0] = "=Sample editor: Crossfade loop points";
    strings["Sample editor: Preview sample##sggc"].plurals[0] = "=Sample editor: Preview sample";
    strings["Sample editor: Stop sample preview##sggc"].plurals[0] = "=Sample editor: Stop sample preview";
    strings["Sample editor: Zoom in##sggc"].plurals[0] = "=Sample editor: Zoom in";
    strings["Sample editor: Zoom out##sggc"].plurals[0] = "=Sample editor: Zoom out";
    strings["Sample editor: Toggle auto-zoom##sggc"].plurals[0] = "=Sample editor: Toggle auto-zoom";
    strings["Sample editor: Create instrument from sample##sggc"].plurals[0] = "=Sample editor: Create instrument from sample";
    strings["Sample editor: Set loop to selection##sggc"].plurals[0] = "=Sample editor: Set loop to selection";
    strings["Sample editor: Create wavetable from selection##sggc"].plurals[0] = "=Sample editor: Create wavetable from selection";
    strings["---Orders##sggc"].plurals[0] = "=---Orders";
    strings["Previous order##sggc"].plurals[0] = "=Previous order";
    strings["Next order##sggc"].plurals[0] = "=Next order";
    strings["Order cursor left##sggc"].plurals[0] = "=Order cursor left";
    strings["Order cursor right##sggc"].plurals[0] = "=Order cursor right";
    strings["Increase order value##sggc"].plurals[0] = "=Increase order value";
    strings["Decrease order value##sggc"].plurals[0] = "=Decrease order value";
    strings["Switch order edit mode##sggc"].plurals[0] = "=Switch order edit mode";
    strings["Order: toggle alter entire row##sggc"].plurals[0] = "=Order: toggle alter entire row";
    strings["Add order##sggc3"].plurals[0] = "=Add order";
    strings["Duplicate order##sggc3"].plurals[0] = "=Duplicate order";
    strings["Deep clone order##sggc"].plurals[0] = "=Deep clone order";
    strings["Copy current order to end of song##sggc"].plurals[0] = "=Copy current order to end of song";
    strings["Deep clone current order to end of song##sggc"].plurals[0] = "=Deep clone current order to end of song";
    strings["Remove order##sggc"].plurals[0] = "=Remove order";
    strings["Move order up##sggc3"].plurals[0] = "=Move order up";
    strings["Move order down##sggc3"].plurals[0] = "=Move order down";
    strings["Replay order##sggc"].plurals[0] = "=Replay order";

    strings["All chips##sggc"].plurals[0] = "=All chips";
    strings["Square##sggc"].plurals[0] = "=Square";
    strings["Wavetable##sggc"].plurals[0] = "=Wavetable";
    strings["Special##sggc"].plurals[0] = "=Special";
    strings["Sample##sggc"].plurals[0] = "=Sample";
    strings["Modern/fantasy##sggc"].plurals[0] = "=Modern/fantasy";

    //   sgda  src/gui/doAction.cpp

    strings["Unsaved changes! Save changes before creating a new song?##sgda"].plurals[0] = "=Unsaved changes! Save changes before creating a new song?";
    strings["Unsaved changes! Save changes before opening another file?##sgda"].plurals[0] = "=Unsaved changes! Save changes before opening another file?";
    strings["Unsaved changes! Save changes before opening backup?##sgda"].plurals[0] = "=Unsaved changes! Save changes before opening backup?";
    strings["Error while saving file! (%s)##sgda"].plurals[0] = "=Error while saving file! (%s)";
    strings["Error while sending request (MIDI output not configured?)##sgda"].plurals[0] = "=Error while sending request (MIDI output not configured?)";
    strings["Select an option: (cannot be undone!)##sgda"].plurals[0] = "=Select an option: (cannot be undone!)";
    strings["too many instruments!##sgda0"].plurals[0] = "=too many instruments!";
    strings["too many instruments!##sgda1"].plurals[0] = "=too many instruments!";
    strings["too many wavetables!##sgda0"].plurals[0] = "=too many wavetables!";
    strings["too many wavetables!##sgda1"].plurals[0] = "=too many wavetables!";
    strings["too many samples!##sgda0"].plurals[0] = "=too many samples!";
    strings["too many samples!##sgda1"].plurals[0] = "=too many samples!";
    strings["couldn't paste! make sure your sample is 8 or 16-bit.##sgda"].plurals[0] = "=couldn't paste! make sure your sample is 8 or 16-bit.";
    strings["too many instruments!##sgda2"].plurals[0] = "=too many instruments!";
    strings["select at least one sample!##sgda"].plurals[0] = "=select at least one sample!";
    strings["maximum size is 256 samples!##sgda"].plurals[0] = "=maximum size is 256 samples!";
    strings["too many wavetables!##sgda2"].plurals[0] = "=too many wavetables!";

    //   sgec  src/gui/editControls.cpp

    strings["Mobile Edit###MobileEdit"].plurals[0] = "=Mobile Edit###MobileEdit";
    strings["Mobile Controls###Mobile Controls"].plurals[0] = "=Mobile Controls###Mobile Controls";
    strings["Mobile Menu###Mobile Menu"].plurals[0] = "=Mobile Menu###Mobile Menu";
    strings["Pattern##sgec0"].plurals[0] = "=Pattern";
    strings["Orders##sgec0"].plurals[0] = "=Orders";
    strings["Ins##sgec"].plurals[0] = "=Ins";
    strings["Wave##sgec"].plurals[0] = "=Wave";
    strings["Sample##sgec"].plurals[0] = "=Sample";
    strings["Song##sgec"].plurals[0] = "=Song";
    strings["Channels##sgec"].plurals[0] = "=Channels";
    strings["Chips##sgec"].plurals[0] = "=Chips";
    strings["Mixer##sgec"].plurals[0] = "=Mixer";
    strings["Other##sgec"].plurals[0] = "=Other";
    strings["New##sgec"].plurals[0] = "=New";
    strings["Unsaved changes! Save changes before creating a new song?##sgec"].plurals[0] = "=Unsaved changes! Save changes before creating a new song?";
    strings["Open##sgec"].plurals[0] = "=Open";
    strings["Save##sgec"].plurals[0] = "=Save";
    strings["Save as...##sgec"].plurals[0] = "=Save as...";
    strings["Legacy .dmf##sgec"].plurals[0] = "=Legacy .dmf";
    strings["Export##sgec"].plurals[0] = "=Export";
    strings["Restore Backup##sgec"].plurals[0] = "=Restore Backup";
    strings["Song Info##sgec"].plurals[0] = "=Song Info";
    strings["Subsongs##sgec"].plurals[0] = "=Subsongs";
    strings["Speed##sgec"].plurals[0] = "=Speed";
    strings["Channels here...##sgec"].plurals[0] = "=Channels here...";
    strings["Chips here...##sgec"].plurals[0] = "=Chips here...";
    strings["What the hell...##sgec"].plurals[0] = "=What the hell...";
    strings["Osc##sgec"].plurals[0] = "=Osc";
    strings["ChanOsc##sgec"].plurals[0] = "=ChanOsc";
    strings["RegView##sgec"].plurals[0] = "=RegView";
    strings["Stats##sgec"].plurals[0] = "=Stats";
    strings["Grooves##sgec"].plurals[0] = "=Grooves";
    strings["Compat Flags##sgec"].plurals[0] = "=Compat Flags";
    strings["XYOsc##sgec"].plurals[0] = "=XYOsc";
    strings["Panic##sgec"].plurals[0] = "=Panic";
    strings["Settings##sgec"].plurals[0] = "=Settings";
    strings["Log##sgec"].plurals[0] = "=Log";
    strings["Debug##sgec"].plurals[0] = "=Debug";
    strings["About##sgec"].plurals[0] = "=About";
    strings["Switch to Desktop Mode##sgec"].plurals[0] = "=Switch to Desktop Mode";
    strings["this is NOT ROM export! only use for making sure the\n"
            "Furnace Amiga emulator is working properly by\n"
            "comparing it with real Amiga output."].plurals[0] = 

            "=this is NOT ROM export! only use for making sure the\n"
            "=Furnace Amiga emulator is working properly by\n"
            "=comparing it with real Amiga output.";
    strings["Directory##sgec"].plurals[0] = "=Directory";
    strings["Bake Data##sgec"].plurals[0] = "=Bake Data";
    strings["Done! Baked %d files.##sgec"].plurals[0] = "=Done! Baked %d file.";
    strings["Done! Baked %d files.##sgec"].plurals[1] = "=Done! Baked %d files.";
    strings["Play/Edit Controls###Play/Edit Controls"].plurals[0] = "=Play/Edit Controls###Play/Edit Controls";
    strings["Octave##sgec0"].plurals[0] = "=Octave";
    strings["Edit Step##sgec0"].plurals[0] = "=Edit Step";
    strings["Play##sgec0"].plurals[0] = "=Play";
    strings["Stop##sgec0"].plurals[0] = "=Stop";
    strings["Edit##sgec0"].plurals[0] = "=Edit";
    strings["Metronome##sgec0"].plurals[0] = "=Metronome";
    strings["Follow##sgec0"].plurals[0] = "=Follow";
    strings["Orders##sgec1"].plurals[0] = "=Orders";
    strings["Pattern##sgec1"].plurals[0] = "=Pattern";
    strings["Repeat pattern##sgec0"].plurals[0] = "=Repeat pattern";
    strings["Step one row##sgec0"].plurals[0] = "=Step one row";
    strings["Poly##PolyInput"].plurals[0] = "=Poly##PolyInput";
    strings["Mono##PolyInput"].plurals[0] = "=Mono##PolyInput";
    strings["Polyphony##sgec0"].plurals[0] = "=Polyphony";
    strings["Stop##sgec1"].plurals[0] = "=Stop";
    strings["Play##sgec1"].plurals[0] = "=Play";
    strings["Step one row##sgec1"].plurals[0] = "=Step one row";
    strings["Repeat pattern##sgec1"].plurals[0] = "=Repeat pattern";
    strings["Edit##sgec1"].plurals[0] = "=Edit";
    strings["Metronome##sgec1"].plurals[0] = "=Metronome";
    strings["Octave##sgec1"].plurals[0] = "=Octave";
    strings["Edit Step##sgec1"].plurals[0] = "=Edit Step";
    strings["Follow##sgec1"].plurals[0] = "=Follow";
    strings["Orders##sgec2"].plurals[0] = "=Orders";
    strings["Pattern##sgec2"].plurals[0] = "=Pattern";
    strings["Poly##PolyInput"].plurals[0] = "=Poly##PolyInput";
    strings["Mono##PolyInput"].plurals[0] = "=Mono##PolyInput";
    strings["Polyphony##sgec1"].plurals[0] = "=Polyphony";
    strings["Play##sgec2"].plurals[0] = "=Play";
    strings["Stop##sgec2"].plurals[0] = "=Stop";
    strings["Step one row##sgec2"].plurals[0] = "=Step one row";
    strings["Repeat pattern##sgec2"].plurals[0] = "=Repeat pattern";
    strings["Edit##sgec2"].plurals[0] = "=Edit";
    strings["Metronome##sgec2"].plurals[0] = "=Metronome";
    strings["Oct.##sgec"].plurals[0] = "=Oct.";
    strings["Octave##sgec2"].plurals[0] = "=Octave";
    strings["Step##sgec0"].plurals[0] = "=Step";
    strings["Foll.##sgec"].plurals[0] = "=Foll.";
    strings["Follow##sgec2"].plurals[0] = "=Follow";
    strings["Ord##FollowOrders"].plurals[0] = "=Ord##FollowOrders";
    strings["Orders##sgec3"].plurals[0] = "=Orders";
    strings["Pat##FollowPattern"].plurals[0] = "=Pat##FollowPattern";
    strings["Pattern##sgec3"].plurals[0] = "=Pattern";
    strings["Poly##PolyInput"].plurals[0] = "=Poly##PolyInput";
    strings["Mono##PolyInput"].plurals[0] = "=Mono##PolyInput";
    strings["Polyphony##sgec2"].plurals[0] = "=Polyphony";
    strings["Play Controls###Play Controls"].plurals[0] = "=Play Controls###Play Controls";
    strings["Stop##sgec3"].plurals[0] = "=Stop";
    strings["Play##sgec3"].plurals[0] = "=Play";
    strings["Play from the beginning of this pattern##sgec"].plurals[0] = "=Play from the beginning of this pattern";
    strings["Repeat from the beginning of this pattern##sgec"].plurals[0] = "=Repeat from the beginning of this pattern";
    strings["Step one row##sgec3"].plurals[0] = "=Step one row";
    strings["Edit##sgec3"].plurals[0] = "=Edit";
    strings["Metronome##sgec3"].plurals[0] = "=Metronome";
    strings["Repeat pattern##sgec3"].plurals[0] = "=Repeat pattern";
    strings["Poly##PolyInput"].plurals[0] = "=Poly##PolyInput";
    strings["Mono##PolyInput"].plurals[0] = "=Mono##PolyInput";
    strings["Polyphony##sgec3"].plurals[0] = "=Polyphony";
    strings["Edit Controls###Edit Controls"].plurals[0] = "=Edit Controls###Edit Controls";
    strings["Octave##sgec3"].plurals[0] = "=Octave";
    strings["Step##sgec1"].plurals[0] = "=Step";
    strings["Follow orders##sgec"].plurals[0] = "=Follow orders";
    strings["Follow pattern##sgec"].plurals[0] = "=Follow pattern";

    //   sged  src/gui/editing.cpp

    strings["can't collapse any further!##sged"].plurals[0] = "=can't collapse any further!";
    strings["can't expand any further!##sged"].plurals[0] = "=can't expand any further!";

    //   sgef  src/gui/effectList.cpp

    strings["Effect List###Effect List"].plurals[0] = "=Effect List###Effect List";
    strings["Chip at cursor: %s##sgef"].plurals[0] = "=Chip at cursor: %s";
    strings["Search##sgef"].plurals[0] = "=Search";
    strings["Effect types to show:##sgef"].plurals[0] = "=Effect types to show:";
    strings["All##sgef"].plurals[0] = "=All";
    strings["None##sgef"].plurals[0] = "=None";
    strings["Name##sgef"].plurals[0] = "=Name";
    strings["Description##sgef"].plurals[0] = "=Description";
    strings["ERROR##sgef"].plurals[0] = "=ERROR";

    //   sgeo  src/gui/exportOptions.cpp

    strings["one file##sgeo"].plurals[0] = "=one file";
    strings["multiple files (one per chip)##sgeo"].plurals[0] = "=multiple files (one per chip)";
    strings["multiple files (one per channel)##sgeo"].plurals[0] = "=multiple files (one per channel)";
    strings["Loops##sgeo"].plurals[0] = "=Loops";
    strings["Fade out (seconds)##sgeo"].plurals[0] = "=Fade out (seconds)";
    strings["Cancel##sgeo0"].plurals[0] = "=Cancel";
    strings["Export##sgeo0"].plurals[0] = "=Export";
    strings["settings:##sgeo"].plurals[0] = "=settings:";
    strings["format version##sgeo"].plurals[0] = "=format version";
    strings["loop##sgeo0"].plurals[0] = "=loop";
    strings["loop trail:##sgeo"].plurals[0] = "=loop trail:";
    strings["auto-detect##sgeo"].plurals[0] = "=auto-detect";
    strings["add one loop##sgeo1"].plurals[0] = "=add one loop";
    strings["custom##sgeo"].plurals[0] = "=custom";
    strings["add pattern change hints##sgeo"].plurals[0] = "=add pattern change hints";
    strings["inserts data blocks on pattern changes.\n"
            "useful if you are writing a playback routine.\n\n"
            "the format of a pattern change data block is:\n"
            "67 66 FE ll ll ll ll 01 oo rr pp pp pp ...\n"
            "- ll: length, a 32-bit little-endian number\n"
            "- oo: order\n"
            "- rr: initial row (a 0Dxx effect is able to select a different row)\n"
            "- pp: pattern index (one per channel)\n\n"
            "pattern indexes are ordered as they appear in the song."].plurals[0] = 

            "=inserts data blocks on pattern changes.\n"
            "=useful if you are writing a playback routine.\n\n"
            "=the format of a pattern change data block is:\n"
            "=67 66 FE ll ll ll ll 01 oo rr pp pp pp ...\n"
            "=- ll: length, a 32-bit little-endian number\n"
            "=- oo: order\n"
            "=- rr: initial row (a 0Dxx effect is able to select a different row)\n"
            "=- pp: pattern index (one per channel)\n\n"
            "=pattern indexes are ordered as they appear in the song.";
    strings["direct stream mode##sgeo"].plurals[0] = "=direct stream mode";
    strings["required for DualPCM and MSM6258 export.\n\n"
            "allows for volume/direction changes when playing samples,\n"
            "at the cost of a massive increase in file size."].plurals[0] = 

            "=required for DualPCM and MSM6258 export.\n\n"
            "=allows for volume/direction changes when playing samples,\n"
            "=at the cost of a massive increase in file size.";
    strings["chips to export:##sgeo"].plurals[0] = "=chips to export:";
    strings["this chip is only available in VGM %d.%.2x and higher!##sgeo"].plurals[0] = "=this chip is only available in VGM %d.%.2x and higher!";
    strings["this chip is not supported by the VGM format!##sgeo"].plurals[0] = "=this chip is not supported by the VGM format!";
    strings["select the chip you wish to export, but only up to %d of each type.##sgeo"].plurals[0] = "=select the chip you wish to export, but only up to %d of each type.";
    strings["select the chip you wish to export, but only up to %d of each type.##sgeo"].plurals[1] = "=select the chip you wish to export, but only up to %d of each type.";
    strings["Cancel##sgeo1"].plurals[0] = "=Cancel";
    strings["Export##sgeo1"].plurals[0] = "=Export";
    strings["nothing to export##sgeo2"].plurals[0] = "=nothing to export";
    strings["Cancel##sgeo2"].plurals[0] = "=Cancel";
    strings["Commander X16 Zsound Music File##sgeo"].plurals[0] = "=Commander X16 Zsound Music File";
    strings["Tick Rate (Hz)##sgeo"].plurals[0] = "=Tick Rate (Hz)";
    strings["loop##sgeo2"].plurals[0] = "=loop";
    strings["optimize size##sgeo"].plurals[0] = "=optimize size";
    strings["Cancel##sgeo3"].plurals[0] = "=Cancel";
    strings["Export##sgeo3"].plurals[0] = "=Export";
    strings["DefleMask file (1.1.3+)##sgeo"].plurals[0] = "=DefleMask file (1.1.3+)";
    strings["Cancel##sgeo4"].plurals[0] = "=Cancel";
    strings["Export##sgeo4"].plurals[0] = "=Export";
    strings["DefleMask file (1.0/legacy)##sgeo"].plurals[0] = "=DefleMask file (1.0/legacy)";
    strings["Cancel##sgeo5"].plurals[0] = "=Cancel";
    strings["Export##sgeo5"].plurals[0] = "=Export";
    strings["this is NOT ROM export! only use for making sure the\n"
            "Furnace Amiga emulator is working properly by\n"
            "comparing it with real Amiga output."].plurals[0] = 

            "=this is NOT ROM export! only use for making sure the\n"
            "=Furnace Amiga emulator is working properly by\n"
            "=comparing it with real Amiga output.";
    strings["Directory##sgeo"].plurals[0] = "=Directory";
    strings["Cancel##sgeo6"].plurals[0] = "=Cancel";
    strings["Bake Data##sgeo"].plurals[0] = "=Bake Data";
    strings["Done! Baked %d files.##sgeo"].plurals[0] = "=Done! Baked %d file.";
    strings["Done! Baked %d files.##sgeo"].plurals[1] = "=Done! Baked %d files.";
    strings["this option exports the song to a text file.\n##sgeo"].plurals[0] = "=this option exports the song to a text file.\n";
    strings["Cancel##sgeo7"].plurals[0] = "=Cancel";
    strings["Export##sgeo6"].plurals[0] = "=Export";
    strings["this option exports a binary file which\n"
            "contains a dump of the internal command stream\n"
            "produced when playing the song.\n\n"
            "technical/development use only!"].plurals[0] = 

            "=this option exports a binary file which\n"
            "=contains a dump of the internal command stream\n"
            "=produced when playing the song.\n\n"
            "=technical/development use only!";
    strings["Cancel##sgeo8"].plurals[0] = "=Cancel";
    strings["Export##sgeo"].plurals[0] = "=Export";
    strings["this option exports a module which is\n"
            "compatible with tildearrow Furnace app.\n\n"

            "not all chips and inst macros will be supported!"].plurals[0] = 

            "=this option exports a module which is\n"
            "compatible with tildearrow Furnace app.\n\n"

            "not all chips and inst macros will be supported!";
    strings["Cancel##sgeo9"].plurals[0] = "=Cancel";
    strings["Export##sgeo7"].plurals[0] = "=Export";
    strings["Audio##sgeo"].plurals[0] = "=Audio";
    strings["DMF (1.0/legacy)##sgeo"].plurals[0] = "=DMF (1.0/legacy)";
    strings["Amiga Validation##sgeo"].plurals[0] = "=Amiga Validation";
    strings["Text##sgeo"].plurals[0] = "=Text";
    strings["Command Stream##sgeo"].plurals[0] = "=Command Stream";
    strings["Furnace##sgeo"].plurals[0] = "=Furnace";
    strings["congratulations! you've unlocked a secret panel.##sgeo"].plurals[0] = "=congratulations! you've unlocked a secret panel.";
    strings["Toggle hidden systems##sgeo"].plurals[0] = "=Toggle hidden systems";
    strings["Toggle all instrument types##sgeo"].plurals[0] = "=Toggle all instrument types";
    strings["Set pitch linearity to Partial##sgeo"].plurals[0] = "=Set pitch linearity to Partial";
    strings["Enable multi-threading settings##sgeo"].plurals[0] = "=Enable multi-threading settings";
    strings["Set fat to max##sgeo"].plurals[0] = "=Set fat to max";
    strings["Set muscle and fat to zero##sgeo"].plurals[0] = "=Set muscle and fat to zero";
    strings["Tell tildearrow this must be a mistake##sgeo"].plurals[0] = "=Tell tildearrow this must be a mistake";
    strings["yeah, it's a bug. write a bug report in the GitHub page and tell me how did you get here.##sgeo"].plurals[0] = "=yeah, it's a bug. write a bug report in the GitHub page and tell me how did you get here.";

    //   sgfr  src/gui/findReplace.cpp

    strings["ignore##sgfr"].plurals[0] = "=ignore";
    strings["equals##sgfr"].plurals[0] = "=equals";
    strings["not equal##sgfr"].plurals[0] = "=not equal";
    strings["between##sgfr"].plurals[0] = "=between";
    strings["not between##sgfr"].plurals[0] = "=not between";
    strings["any##sgfr"].plurals[0] = "=any";
    strings["none##sgfr"].plurals[0] = "=none";
    strings["set##sgfr"].plurals[0] = "=set";
    strings["add##sgfr"].plurals[0] = "=add";
    strings["add (overflow)##sgfr"].plurals[0] = "=add (overflow)";
    strings["scale %##sgfr"].plurals[0] = "=scale %";
    strings["clear##sgfr"].plurals[0] = "=clear";

    strings["Find/Replace###Find/Replace"].plurals[0] = "=Find/Replace###Find/Replace";
    strings["Find##sgfr0"].plurals[0] = "=Find";
    strings["order##sgfr0"].plurals[0] = "=order";
    strings["row##sgfr0"].plurals[0] = "=row";
    strings["order##sgfr1"].plurals[0] = "=order";
    strings["row##sgfr1"].plurals[0] = "=row";
    strings["channel##sgfr"].plurals[0] = "=channel";
    strings["go##sgfr"].plurals[0] = "=go";
    strings["no matches found!##sgfr"].plurals[0] = "=no matches found!";
    strings["Back##sgfr"].plurals[0] = "=Back";
    strings["Note##sgfr0"].plurals[0] = "=Note";
    strings["Ins##sgfr0"].plurals[0] = "=Ins";
    strings["Volume##sgfr0"].plurals[0] = "=Volume";
    strings["Effect##sgfr0"].plurals[0] = "=Effect";
    strings["Value##sgfr0"].plurals[0] = "=Value";
    strings["Delete query##sgfr"].plurals[0] = "=Delete query";
    strings["Add effect##sgfr0"].plurals[0] = "=Add effect";
    strings["Remove effect##sgfr0"].plurals[0] = "=Remove effect";
    strings["Search range:##sgfr"].plurals[0] = "=Search range:";
    strings["Song##sgfr"].plurals[0] = "=Song";
    strings["Selection##sgfr"].plurals[0] = "=Selection";
    strings["Pattern##sgfr"].plurals[0] = "=Pattern";
    strings["Confine to channels##sgfr"].plurals[0] = "=Confine to channels";
    strings["From##sgfr"].plurals[0] = "=From";
    strings["To##sgfr"].plurals[0] = "=To";
    strings["Match effect position:##sgfr"].plurals[0] = "=Match effect position:";
    strings["No##sgfr"].plurals[0] = "=No";
    strings["match effects regardless of position.##sgfr"].plurals[0] = "=match effects regardless of position.";
    strings["Lax##sgfr"].plurals[0] = "=Lax";
    strings["match effects only if they appear in-order.##sgfr"].plurals[0] = "=match effects only if they appear in-order.";
    strings["Strict##sgfr"].plurals[0] = "=Strict";
    strings["match effects only if they appear exactly as specified.##sgfr"].plurals[0] = "=match effects only if they appear exactly as specified.";
    strings["Find##sgfr1"].plurals[0] = "=Find";
    strings["Replace##sgfr"].plurals[0] = "=Replace";
    strings["Note##sgfr1"].plurals[0] = "=Note";
    strings["INVALID##sgfr"].plurals[0] = "=INVALID";
    strings["Ins##sgfr1"].plurals[0] = "=Ins";
    strings["Volume##sgfr1"].plurals[0] = "=Volume";
    strings["Effect##sgfr1"].plurals[0] = "=Effect";
    strings["Value##sgfr1"].plurals[0] = "=Value";
    strings["Add effect##sgfr1"].plurals[0] = "=Add effect";
    strings["Remove effect##sgfr1"].plurals[0] = "=Remove effect";
    strings["Effect replace mode:##sgfr"].plurals[0] = "=Effect replace mode:";
    strings["Replace matches only##sgfr"].plurals[0] = "=Replace matches only";
    strings["Replace matches, then free spaces##sgfr"].plurals[0] = "=Replace matches, then free spaces";
    strings["Clear effects##sgfr"].plurals[0] = "=Clear effects";
    strings["Insert in free spaces##sgfr"].plurals[0] = "=Insert in free spaces";
    strings["Replace##QueryReplace"].plurals[0] = "=Replace##QueryReplace";

    //   sggv  src/gui/grooves.cpp

    strings["Grooves###Grooves"].plurals[0] = "=Grooves###Grooves";
    strings["use effect 09xx to select a groove pattern.##sggv"].plurals[0] = "=use effect 09xx to select a groove pattern.##sggv";
    strings["pattern##sggv"].plurals[0] = "=pattern##sggv";
    strings["remove##sggv"].plurals[0] = "=remove##sggv";

    //   sgie  src/gui/insEdit.cpp

    strings["Name##sgie"].plurals[0] = "=Name";
    strings["Open##sgie0"].plurals[0] = "=Open";
    strings["Save##sgie"].plurals[0] = "=Save";
    strings["export .dmp...##sgie"].plurals[0] = "=export .dmp...";
    strings["Type##sgie"].plurals[0] = "=Type";
    strings["Unknown##sgie"].plurals[0] = "=Unknown";
    strings["none of the currently present chips are able to play this instrument type!##sgie"].plurals[0] = "=none of the currently present chips are able to play this instrument type!";
    strings["Error##sgie"].plurals[0] = "=Error";
    strings["invalid instrument type! change it first.##sgie"].plurals[0] = "=invalid instrument type! change it first.";
    strings["Instrument Editor###Instrument Editor"].plurals[0] = "=Instrument Editor###Instrument Editor";
    strings["waiting...##sgie0"].plurals[0] = "=waiting...";
    strings["waiting...##sgie1"].plurals[0] = "=waiting...";
    strings["no instrument selected##sgie0"].plurals[0] = "=no instrument selected";
    strings["no instrument selected##sgie1"].plurals[0] = "=no instrument selected";
    strings["select one...##sgie"].plurals[0] = "=select one...";
    strings["or##sgie0"].plurals[0] = "=or";
    strings["Open##sgie1"].plurals[0] = "=Open";
    strings["or##sgie1"].plurals[0] = "=or";
    strings["Create New##sgie"].plurals[0] = "=Create New";
    strings["copy##sgie"].plurals[0] = "=copy";
    strings["paste##sgie"].plurals[0] = "=paste";
    strings["clear contents##sgie"].plurals[0] = "=clear contents";
    strings["offset...##sgie"].plurals[0] = "=offset...";
    strings["offset##sgie"].plurals[0] = "=offset";
    strings["scale...##sgie"].plurals[0] = "=scale...";
    strings["scale##sgie"].plurals[0] = "=scale";
    strings["randomize...##sgie"].plurals[0] = "=randomize...";
    strings["Min##sgie"].plurals[0] = "=Min";
    strings["Max##sgie"].plurals[0] = "=Max";
    strings["randomize##sgie"].plurals[0] = "=randomize";

    //   sgmx  src/gui/mixer.cpp

    strings["input##sgmx"].plurals[0] = "=input";
    strings["output##sgmx"].plurals[0] = "=output";
    strings["Mixer##sgmx"].plurals[0] = "=Mixer";
    strings["Master Volume##sgmx"].plurals[0] = "=Master Volume";
    strings["Invert##sgmx"].plurals[0] = "=Invert";
    strings["Volume##sgmx"].plurals[0] = "=Volume";
    strings["Panning##sgmx"].plurals[0] = "=Panning";
    strings["Front/Rear##sgmx"].plurals[0] = "=Front/Rear";
    strings["Patchbay##sgmx"].plurals[0] = "=Patchbay";
    strings["Automatic patchbay##sgmx"].plurals[0] = "=Automatic patchbay";
    strings["Display hidden ports##sgmx"].plurals[0] = "=Display hidden ports";
    strings["Display internal##sgmx"].plurals[0] = "=Display internal";
    strings["System##sgmx0"].plurals[0] = "=System";
    strings["Sample Preview##sgmx"].plurals[0] = "=Sample Preview";
    strings["Metronome##sgmx"].plurals[0] = "=Metronome";
    strings["System##sgmx1"].plurals[0] = "=System";
    strings["disconnect all##sgmx"].plurals[0] = "=disconnect all";

    //   sgns  src/gui/newSong.cpp

    strings["Choose a System!##sgns"].plurals[0] = "=Choose a System!";
    strings["Search...##sgns"].plurals[0] = "=Search...";
    strings["Categories##sgns"].plurals[0] = "=Categories";
    strings["Systems##sgns"].plurals[0] = "=Systems";
    strings["no systems here yet!##sgns"].plurals[0] = "=no systems here yet!";
    strings["no results##sgns"].plurals[0] = "=no results";
    strings["I'm feeling lucky##sgns"].plurals[0] = "=I'm feeling lucky";
    strings["no categories available! what in the world.##sgns"].plurals[0] = "=no categories available! what in the world.";
    strings["Cancel##sgns"].plurals[0] = "=Cancel";

    //   sgme  src/gui/memory.cpp

    strings["Memory Composition###Memory Composition"].plurals[0] = "=Memory Composition###Memory Composition";
    strings["bank %d##sgme"].plurals[0] = "=bank %d";
    strings["%d-%d ($%x-$%x): %d bytes ($%x)##sgme"].plurals[0] = "=%d-%d ($%x-$%x): %d bytes ($%x)";
    strings["%d-%d ($%x-$%x): %dK ($%x)##sgme"].plurals[0] = "=%d-%d ($%x-$%x): %dK ($%x)";
    strings["no chips with memory##sgme"].plurals[0] = "=no chips with memory";

    //   sgor  src/gui/orders.cpp

    strings["Orders###Orders"].plurals[0] = "=Orders###Orders";
    strings["Add new order##sgor"].plurals[0] = "=Add new order";
    strings["Remove order##sgor"].plurals[0] = "=Remove order";
    strings["Duplicate order (right-click to deep clone)##sgor"].plurals[0] = "=Duplicate order (right-click to deep clone)";
    strings["Move order up##sgor"].plurals[0] = "=Move order up";
    strings["Move order down##sgor"].plurals[0] = "=Move order down";
    strings["Place copy of current order at end of song (right-click to deep clone)##sgor"].plurals[0] = "=Place copy of current order at end of song (right-click to deep clone)";
    strings["Order change mode: entire row##sgor"].plurals[0] = "=Order change mode: entire row";
    strings["Order change mode: one##sgor"].plurals[0] = "=Order change mode: one";
    strings["Order edit mode: Select and type (scroll vertically)##sgor"].plurals[0] = "=Order edit mode: Select and type (scroll vertically)";
    strings["Order edit mode: Select and type (scroll horizontally)##sgor"].plurals[0] = "=Order edit mode: Select and type (scroll horizontally)";
    strings["Order edit mode: Select and type (don't scroll)##sgor"].plurals[0] = "=Order edit mode: Select and type (don't scroll)";
    strings["Order edit mode: Click to change##sgor"].plurals[0] = "=Order edit mode: Click to change";

    //   sgos  src/gui/osc.cpp

    strings["Oscilloscope###Oscilloscope"].plurals[0] = "=Oscilloscope###Oscilloscope";
    strings["zoom: %.2fx (%.1fdB)##sgos"].plurals[0] = "=zoom: %.2fx (%.1fdB)";
    strings["window size: %.1fms##sgos"].plurals[0] = "=window size: %.1fms";
    strings["(-Infinity)dB##sgos"].plurals[0] = "=(-Infinity)dB";

    //   sgpm  src/gui/patManager.cpp

    strings["Pattern Manager###Pattern Manager"].plurals[0] = "=Pattern Manager###Pattern Manager";
    strings["Global Tasks:##sgpm"].plurals[0] = "=Global Tasks:";
    strings["De-duplicate patterns##sgpm"].plurals[0] = "=De-duplicate patterns";
    strings["Re-arrange patterns##sgpm"].plurals[0] = "=Re-arrange patterns";
    strings["Sort orders##sgpm"].plurals[0] = "=Sort orders";
    strings["Make patterns unique##sgpm"].plurals[0] = "=Make patterns unique";
    strings["Pattern %.2X\n- not allocated##sgpm"].plurals[0] = "=Pattern %.2X\n- not allocated";
    strings["Pattern %.2X\n- use count: %d (%.0f%%)\n\nright-click to erase##sgpm"].plurals[0] = "=Pattern %.2X\n- use count: %d (%.0f%%)\n\nright-click to erase";

    //   sgpa  src/gui/pattern.cpp

    strings["Pattern###Pattern"].plurals[0] = "=Pattern###Pattern";
    strings["there aren't any channels to show.##sgpa"].plurals[0] = "=there aren't any channels to show.";
    strings["click for pattern options (effect columns/pattern names/visualizer)##sgpa"].plurals[0] = "=click for pattern options (effect columns/pattern names/visualizer)";
    strings["Options:##sgpa"].plurals[0] = "=Options:";
    strings["Effect columns/collapse##sgpa"].plurals[0] = "=Effect columns/collapse";
    strings["Pattern names##sgpa"].plurals[0] = "=Pattern names";
    strings["Channel group hints##sgpa"].plurals[0] = "=Channel group hints";
    strings["Visualizer##sgpa"].plurals[0] = "=Visualizer";
    strings["Channel status:##sgpa"].plurals[0] = "=Channel status:";
    strings["No##_PCS0"].plurals[0] = "=No##_PCS0";
    strings["Yes##_PCS1"].plurals[0] = "=Yes##_PCS1";
    strings["WARNING!!##sgpa"].plurals[0] = "=WARNING!!";
    strings["this instrument cannot be previewed because##sgpa"].plurals[0] = "=this instrument cannot be previewed because";
    strings["none of the chips can play it##sgpa"].plurals[0] = "=none of the chips can play it";
    strings["your instrument is in peril!! be careful...##sgpa"].plurals[0] = "=your instrument is in peril!! be careful...";

    //   sgpi  src/gui/piano.cpp

    strings["Piano###Piano"].plurals[0] = "=Piano###Piano";
    strings["Options##sgpi"].plurals[0] = "=Options";
    strings["Key layout:##sgpi"].plurals[0] = "=Key layout:";
    strings["Automatic##sgpi"].plurals[0] = "=Automatic";
    strings["Standard##sgpi"].plurals[0] = "=Standard";
    strings["Continuous##sgpi"].plurals[0] = "=Continuous";
    strings["Value input pad:##sgpi"].plurals[0] = "=Value input pad:";
    strings["Disabled##sgpi"].plurals[0] = "=Disabled";
    strings["Replace piano##sgpi"].plurals[0] = "=Replace piano";
    strings["Split (automatic)##sgpi"].plurals[0] = "=Split (automatic)";
    strings["Split (always visible)##sgpi"].plurals[0] = "=Split (always visible)";
    strings["Share play/edit offset/range##sgpi"].plurals[0] = "=Share play/edit offset/range";
    strings["Read-only (can't input notes)##sgpi"].plurals[0] = "=Read-only (can't input notes)";
    strings["Input Pad###Input Pad"].plurals[0] = "=Input Pad###Input Pad";

    //   sgpr  src/gui/presets.cpp

    strings["Game consoles##sgpr"].plurals[0] = "=Game consoles";
    strings["let's play some chiptune making games!##sgpr"].plurals[0] = "=let's play some chiptune making games!";
    strings["Sega Genesis (extended channel 3)##sgpr"].plurals[0] = "=Sega Genesis (extended channel 3)";
    strings["Sega Genesis (DualPCM, extended channel 3)##sgpr"].plurals[0] = "=Sega Genesis (DualPCM, extended channel 3)";
    strings["Sega Genesis (with Sega CD)##sgpr"].plurals[0] = "=Sega Genesis (with Sega CD)";
    strings["Sega Genesis (extended channel 3 with Sega CD)##sgpr"].plurals[0] = "=Sega Genesis (extended channel 3 with Sega CD)";
    strings["Sega Genesis (CSM with Sega CD)##sgpr"].plurals[0] = "=Sega Genesis (CSM with Sega CD)";
    strings["Sega Master System (with FM expansion)##sgpr"].plurals[0] = "=Sega Master System (with FM expansion)";
    strings["Sega Master System (with FM expansion in drums mode)##sgpr"].plurals[0] = "=Sega Master System (with FM expansion in drums mode)";
    strings["Game Boy Advance (no software mixing)##sgpr"].plurals[0] = "=Game Boy Advance (no software mixing)";
    strings["Game Boy Advance (with MinMod)##sgpr"].plurals[0] = "=Game Boy Advance (with MinMod)";
    strings["Famicom with Konami VRC6##sgpr"].plurals[0] = "=Famicom with Konami VRC6";
    strings["Famicom with Konami VRC7##sgpr0"].plurals[0] = "=Famicom with Konami VRC7";
    strings["Famicom with MMC5##sgpr"].plurals[0] = "=Famicom with MMC5";
    strings["Famicom with Sunsoft 5B##sgpr"].plurals[0] = "=Famicom with Sunsoft 5B";
    strings["Famicom with Namco 163##sgpr"].plurals[0] = "=Famicom with Namco 163";
    strings["Neo Geo AES (extended channel 2)##sgpr"].plurals[0] = "=Neo Geo AES (extended channel 2)";
    strings["Neo Geo AES (extended channel 2 and CSM)##sgpr"].plurals[0] = "=Neo Geo AES (extended channel 2 and CSM)";
    strings["Computers##sgpr"].plurals[0] = "=Computers";
    strings["let's get to work on chiptune today.##sgpr"].plurals[0] = "=let's get to work on chiptune today.";
    strings["Commodore 64 (C64, 6581 SID + Sound Expander in drums mode)##sgpr"].plurals[0] = "=Commodore 64 (C64, 6581 SID + Sound Expander in drums mode)";
    strings["Commodore 64 (C64, 8580 SID + Sound Expander in drums mode)##sgpr"].plurals[0] = "=Commodore 64 (C64, 8580 SID + Sound Expander in drums mode)";
    strings["Commodore 64 (C64, 6581 SID + FM-YAM in drums mode)##sgpr"].plurals[0] = "=Commodore 64 (C64, 6581 SID + FM-YAM in drums mode)";
    strings["Commodore 64 (C64, 8580 SID + FM-YAM in drums mode)##sgpr"].plurals[0] = "=Commodore 64 (C64, 8580 SID + FM-YAM in drums mode)";
    strings["MSX + MSX-AUDIO (drums mode)##sgpr"].plurals[0] = "=MSX + MSX-AUDIO (drums mode)";
    strings["MSX + MSX-MUSIC (drums mode)##sgpr"].plurals[0] = "=MSX + MSX-MUSIC (drums mode)";
    strings["MSX + Neotron (extended channel 2)##sgpr"].plurals[0] = "=MSX + Neotron (extended channel 2)";
    strings["MSX + Neotron (extended channel 2 and CSM)##sgpr"].plurals[0] = "=MSX + Neotron (extended channel 2 and CSM)";
    strings["MSX + Neotron (with YM2610B)##sgpr"].plurals[0] = "=MSX + Neotron (with YM2610B)";
    strings["MSX + Neotron (with YM2610B; extended channel 3)##sgpr"].plurals[0] = "=MSX + Neotron (with YM2610B; extended channel 3)";
    strings["MSX + Neotron (with YM2610B; extended channel 3 and CSM)##sgpr"].plurals[0] = "=MSX + Neotron (with YM2610B; extended channel 3 and CSM)";
    strings["NEC PC-88 (with PC-8801-10)##sgpr"].plurals[0] = "=NEC PC-88 (with PC-8801-10)";
    strings["NEC PC-88 (with PC-8801-11)##sgpr"].plurals[0] = "=NEC PC-88 (with PC-8801-11)";
    strings["NEC PC-88 (with PC-8801-11; extended channel 3)##sgpr"].plurals[0] = "=NEC PC-88 (with PC-8801-11; extended channel 3)";
    strings["NEC PC-88 (with PC-8801-11; extended channel 3 and CSM)##sgpr"].plurals[0] = "=NEC PC-88 (with PC-8801-11; extended channel 3 and CSM)";
    strings["NEC PC-88 (with PC-8801-23)##sgpr"].plurals[0] = "=NEC PC-88 (with PC-8801-23)";
    strings["NEC PC-88 (with PC-8801-23; extended channel 3)##sgpr"].plurals[0] = "=NEC PC-88 (with PC-8801-23; extended channel 3)";
    strings["NEC PC-88 (with PC-8801-23; extended channel 3 and CSM)##sgpr"].plurals[0] = "=NEC PC-88 (with PC-8801-23; extended channel 3 and CSM)";
    strings["NEC PC-88 (with HMB-20 HIBIKI-8800)##sgpr"].plurals[0] = "=NEC PC-88 (with HMB-20 HIBIKI-8800)";
    strings["NEC PC-8801mk2SR (with PC-8801-10)##sgpr"].plurals[0] = "=NEC PC-8801mk2SR (with PC-8801-10)";
    strings["NEC PC-8801mk2SR (with PC-8801-10; extended channel 3)##sgpr"].plurals[0] = "=NEC PC-8801mk2SR (with PC-8801-10; extended channel 3)";
    strings["NEC PC-8801mk2SR (with PC-8801-10; extended channel 3 and CSM)##sgpr"].plurals[0] = "=NEC PC-8801mk2SR (with PC-8801-10; extended channel 3 and CSM)";
    strings["NEC PC-8801mk2SR (with PC-8801-11)##sgpr"].plurals[0] = "=NEC PC-8801mk2SR (with PC-8801-11)";
    strings["NEC PC-8801mk2SR (with PC-8801-11; extended channel 3 on internal OPN)##sgpr"].plurals[0] = "=NEC PC-8801mk2SR (with PC-8801-11; extended channel 3 on internal OPN)";
    strings["NEC PC-8801mk2SR (with PC-8801-11; extended channel 3 on external OPN)##sgpr"].plurals[0] = "=NEC PC-8801mk2SR (with PC-8801-11; extended channel 3 on external OPN)";
    strings["NEC PC-8801mk2SR (with PC-8801-11; extended channel 3 on both OPNs)##sgpr"].plurals[0] = "=NEC PC-8801mk2SR (with PC-8801-11; extended channel 3 on both OPNs)";
    strings["NEC PC-8801mk2SR (with PC-8801-11; extended channel 3 and CSM on both OPNs)##sgpr"].plurals[0] = "=NEC PC-8801mk2SR (with PC-8801-11; extended channel 3 and CSM on both OPNs)";
    strings["NEC PC-8801mk2SR (with PC-8801-23)##sgpr"].plurals[0] = "=NEC PC-8801mk2SR (with PC-8801-23)";
    strings["NEC PC-8801mk2SR (with PC-8801-23; extended channel 3 on internal OPN)##sgpr"].plurals[0] = "=NEC PC-8801mk2SR (with PC-8801-23; extended channel 3 on internal OPN)";
    strings["NEC PC-8801mk2SR (with PC-8801-23; extended channel 3 and CSM on internal OPN)##sgpr"].plurals[0] = "=NEC PC-8801mk2SR (with PC-8801-23; extended channel 3 and CSM on internal OPN)";
    strings["NEC PC-8801mk2SR (with PC-8801-23; extended channel 3 on external OPN)##sgpr"].plurals[0] = "=NEC PC-8801mk2SR (with PC-8801-23; extended channel 3 on external OPN)";
    strings["NEC PC-8801mk2SR (with PC-8801-23; extended channel 3 and CSM on external OPN)##sgpr"].plurals[0] = "=NEC PC-8801mk2SR (with PC-8801-23; extended channel 3 and CSM on external OPN)";
    strings["NEC PC-8801mk2SR (with PC-8801-23; extended channel 3 on both OPNs)##sgpr"].plurals[0] = "=NEC PC-8801mk2SR (with PC-8801-23; extended channel 3 on both OPNs)";
    strings["NEC PC-8801mk2SR (with PC-8801-23; extended channel 3 and CSM on both OPNs)##sgpr"].plurals[0] = "=NEC PC-8801mk2SR (with PC-8801-23; extended channel 3 and CSM on both OPNs)";
    strings["NEC PC-8801mk2SR (with HMB-20 HIBIKI-8800)##sgpr"].plurals[0] = "=NEC PC-8801mk2SR (with HMB-20 HIBIKI-8800)";
    strings["NEC PC-8801mk2SR (with HMB-20 HIBIKI-8800; extended channel 3)##sgpr"].plurals[0] = "=NEC PC-8801mk2SR (with HMB-20 HIBIKI-8800; extended channel 3)";
    strings["NEC PC-8801mk2SR (with HMB-20 HIBIKI-8800; extended channel 3 and CSM)##sgpr"].plurals[0] = "=NEC PC-8801mk2SR (with HMB-20 HIBIKI-8800; extended channel 3 and CSM)";
    strings["NEC PC-8801FA (with PC-8801-10)##sgpr"].plurals[0] = "=NEC PC-8801FA (with PC-8801-10)";
    strings["NEC PC-8801FA (with PC-8801-10; extended channel 3)##sgpr"].plurals[0] = "=NEC PC-8801FA (with PC-8801-10; extended channel 3)";
    strings["NEC PC-8801FA (with PC-8801-11)##sgpr"].plurals[0] = "=NEC PC-8801FA (with PC-8801-11)";
    strings["NEC PC-8801FA (with PC-8801-11; extended channel 3 on internal OPN)##sgpr"].plurals[0] = "=NEC PC-8801FA (with PC-8801-11; extended channel 3 on internal OPN)";
    strings["NEC PC-8801FA (with PC-8801-11; extended channel 3 on external OPN)##sgpr"].plurals[0] = "=NEC PC-8801FA (with PC-8801-11; extended channel 3 on external OPN)";
    strings["NEC PC-8801FA (with PC-8801-11; extended channel 3 and CSM on external OPN)##sgpr"].plurals[0] = "=NEC PC-8801FA (with PC-8801-11; extended channel 3 and CSM on external OPN)";
    strings["NEC PC-8801FA (with PC-8801-11; extended channel 3 on both OPNs)##sgpr"].plurals[0] = "=NEC PC-8801FA (with PC-8801-11; extended channel 3 on both OPNs)";
    strings["NEC PC-8801FA (with PC-8801-11; extended channel 3 and CSM on both OPNs)##sgpr"].plurals[0] = "=NEC PC-8801FA (with PC-8801-11; extended channel 3 and CSM on both OPNs)";
    strings["NEC PC-8801FA (with PC-8801-23)##sgpr"].plurals[0] = "=NEC PC-8801FA (with PC-8801-23)";
    strings["NEC PC-8801FA (with PC-8801-23; extended channel 3 on internal OPN)##sgpr"].plurals[0] = "=NEC PC-8801FA (with PC-8801-23; extended channel 3 on internal OPN)";
    strings["NEC PC-8801FA (with PC-8801-23; extended channel 3 and CSM on internal OPN)##sgpr"].plurals[0] = "=NEC PC-8801FA (with PC-8801-23; extended channel 3 and CSM on internal OPN)";
    strings["NEC PC-8801FA (with PC-8801-23; extended channel 3 on external OPN)##sgpr"].plurals[0] = "=NEC PC-8801FA (with PC-8801-23; extended channel 3 on external OPN)";
    strings["NEC PC-8801FA (with PC-8801-23; extended channel 3 and CSM on external OPN)##sgpr"].plurals[0] = "=NEC PC-8801FA (with PC-8801-23; extended channel 3 and CSM on external OPN)";
    strings["NEC PC-8801FA (with PC-8801-23; extended channel 3 on both OPNs)##sgpr"].plurals[0] = "=NEC PC-8801FA (with PC-8801-23; extended channel 3 on both OPNs)";
    strings["NEC PC-8801FA (with PC-8801-23; extended channel 3 and CSM on both OPNs)##sgpr"].plurals[0] = "=NEC PC-8801FA (with PC-8801-23; extended channel 3 and CSM on both OPNs)";
    strings["NEC PC-8801FA (with HMB-20 HIBIKI-8800)##sgpr"].plurals[0] = "=NEC PC-8801FA (with HMB-20 HIBIKI-8800)";
    strings["NEC PC-8801FA (with HMB-20 HIBIKI-8800; extended channel 3)##sgpr"].plurals[0] = "=NEC PC-8801FA (with HMB-20 HIBIKI-8800; extended channel 3)";
    strings["NEC PC-8801FA (with HMB-20 HIBIKI-8800; extended channel 3 and CSM)##sgpr"].plurals[0] = "=NEC PC-8801FA (with HMB-20 HIBIKI-8800; extended channel 3 and CSM)";
    strings["NEC PC-98 (with PC-9801-26/K)##sgpr"].plurals[0] = "=NEC PC-98 (with PC-9801-26/K)";
    strings["NEC PC-98 (with PC-9801-26/K; extended channel 3)##sgpr"].plurals[0] = "=NEC PC-98 (with PC-9801-26/K; extended channel 3)";
    strings["NEC PC-98 (with PC-9801-26/K; extended channel 3 and CSM)##sgpr"].plurals[0] = "=NEC PC-98 (with PC-9801-26/K; extended channel 3 and CSM)";
    strings["NEC PC-98 (with Sound Orchestra)##sgpr"].plurals[0] = "=NEC PC-98 (with Sound Orchestra)";
    strings["NEC PC-98 (with Sound Orchestra; extended channel 3)##sgpr"].plurals[0] = "=NEC PC-98 (with Sound Orchestra; extended channel 3)";
    strings["NEC PC-98 (with Sound Orchestra; extended channel 3 and CSM)##sgpr"].plurals[0] = "=NEC PC-98 (with Sound Orchestra; extended channel 3 and CSM)";
    strings["NEC PC-98 (with Sound Orchestra in drums mode)##sgpr"].plurals[0] = "=NEC PC-98 (with Sound Orchestra in drums mode)";
    strings["NEC PC-98 (with Sound Orchestra in drums mode; extended channel 3)##sgpr"].plurals[0] = "=NEC PC-98 (with Sound Orchestra in drums mode; extended channel 3)";
    strings["NEC PC-98 (with Sound Orchestra in drums mode; extended channel 3 and CSM)##sgpr"].plurals[0] = "=NEC PC-98 (with Sound Orchestra in drums mode; extended channel 3 and CSM)";
    strings["NEC PC-98 (with Sound Orchestra V)##sgpr"].plurals[0] = "=NEC PC-98 (with Sound Orchestra V)";
    strings["NEC PC-98 (with Sound Orchestra V; extended channel 3)##sgpr"].plurals[0] = "=NEC PC-98 (with Sound Orchestra V; extended channel 3)";
    strings["NEC PC-98 (with Sound Orchestra V; extended channel 3 and CSM)##sgpr"].plurals[0] = "=NEC PC-98 (with Sound Orchestra V; extended channel 3 and CSM)";
    strings["NEC PC-98 (with Sound Orchestra V in drums mode)##sgpr"].plurals[0] = "=NEC PC-98 (with Sound Orchestra V in drums mode)";
    strings["NEC PC-98 (with Sound Orchestra V in drums mode; extended channel 3)##sgpr"].plurals[0] = "=NEC PC-98 (with Sound Orchestra V in drums mode; extended channel 3)";
    strings["NEC PC-98 (with Sound Orchestra V in drums mode; extended channel 3 and CSM)##sgpr"].plurals[0] = "=NEC PC-98 (with Sound Orchestra V in drums mode; extended channel 3 and CSM)";
    strings["NEC PC-98 (with PC-9801-86)##sgpr"].plurals[0] = "=NEC PC-98 (with PC-9801-86)";
    strings["NEC PC-98 (with PC-9801-86; extended channel 3)##sgpr"].plurals[0] = "=NEC PC-98 (with PC-9801-86; extended channel 3)";
    strings["NEC PC-98 (with PC-9801-86; extended channel 3 and CSM)##sgpr"].plurals[0] = "=NEC PC-98 (with PC-9801-86; extended channel 3 and CSM)";
    strings["NEC PC-98 (with PC-9801-86) stereo##sgpr"].plurals[0] = "=NEC PC-98 (with PC-9801-86) stereo";
    strings["NEC PC-98 (with PC-9801-86; extended channel 3) stereo##sgpr"].plurals[0] = "=NEC PC-98 (with PC-9801-86; extended channel 3) stereo";
    strings["NEC PC-98 (with PC-9801-86; extended channel 3 and CSM) stereo##sgpr"].plurals[0] = "=NEC PC-98 (with PC-9801-86; extended channel 3 and CSM) stereo";
    strings["NEC PC-98 (with PC-9801-73)##sgpr"].plurals[0] = "=NEC PC-98 (with PC-9801-73)";
    strings["NEC PC-98 (with PC-9801-73; extended channel 3)##sgpr"].plurals[0] = "=NEC PC-98 (with PC-9801-73; extended channel 3)";
    strings["NEC PC-98 (with PC-9801-73; extended channel 3 and CSM)##sgpr"].plurals[0] = "=NEC PC-98 (with PC-9801-73; extended channel 3 and CSM)";
    strings["NEC PC-98 (with Sound Blaster 16 for PC-9800 w/PC-9801-26/K compatible)##sgpr"].plurals[0] = "=NEC PC-98 (with Sound Blaster 16 for PC-9800 w/PC-9801-26/K compatible)";
    strings["NEC PC-98 (with Sound Blaster 16 for PC-9800 w/PC-9801-26/K compatible; extended channel 3)##sgpr"].plurals[0] = "=NEC PC-98 (with Sound Blaster 16 for PC-9800 w/PC-9801-26/K compatible; extended channel 3)";
    strings["NEC PC-98 (with Sound Blaster 16 for PC-9800 w/PC-9801-26/K compatible; extended channel 3 and CSM)##sgpr"].plurals[0] = "=NEC PC-98 (with Sound Blaster 16 for PC-9800 w/PC-9801-26/K compatible; extended channel 3 and CSM)";
    strings["NEC PC-98 (with Sound Blaster 16 for PC-9800 w/PC-9801-26/K compatible in drums mode)##sgpr"].plurals[0] = "=NEC PC-98 (with Sound Blaster 16 for PC-9800 w/PC-9801-26/K compatible in drums mode)";
    strings["NEC PC-98 (with Sound Blaster 16 for PC-9800 w/PC-9801-26/K compatible in drums mode; extended channel 3)##sgpr"].plurals[0] = "=NEC PC-98 (with Sound Blaster 16 for PC-9800 w/PC-9801-26/K compatible in drums mode; extended channel 3)";
    strings["NEC PC-98 (with Sound Blaster 16 for PC-9800 w/PC-9801-26/K compatible in drums mode; extended channel 3 and CSM)##sgpr"].plurals[0] = "=NEC PC-98 (with Sound Blaster 16 for PC-9800 w/PC-9801-26/K compatible in drums mode; extended channel 3 and CSM)";
    strings["ZX Spectrum (48K, SFX-like engine)##sgpr"].plurals[0] = "=ZX Spectrum (48K, SFX-like engine)";
    strings["ZX Spectrum (48K, QuadTone engine)##sgpr"].plurals[0] = "=ZX Spectrum (48K, QuadTone engine)";
    strings["ZX Spectrum (128K) with TurboSound##sgpr"].plurals[0] = "=ZX Spectrum (128K) with TurboSound";
    strings["ZX Spectrum (128K) with TurboSound FM##sgpr"].plurals[0] = "=ZX Spectrum (128K) with TurboSound FM";
    strings["ZX Spectrum (128K) with TurboSound FM (extended channel 3 on first OPN)##sgpr"].plurals[0] = "=ZX Spectrum (128K) with TurboSound FM (extended channel 3 on first OPN)";
    strings["ZX Spectrum (128K) with TurboSound FM (extended channel 3 and CSM on first OPN)##sgpr"].plurals[0] = "=ZX Spectrum (128K) with TurboSound FM (extended channel 3 and CSM on first OPN)";
    strings["ZX Spectrum (128K) with TurboSound FM (extended channel 3 on second OPN)##sgpr"].plurals[0] = "=ZX Spectrum (128K) with TurboSound FM (extended channel 3 on second OPN)";
    strings["ZX Spectrum (128K) with TurboSound FM (extended channel 3 and CSM on second OPN)##sgpr"].plurals[0] = "=ZX Spectrum (128K) with TurboSound FM (extended channel 3 and CSM on second OPN)";
    strings["ZX Spectrum (128K) with TurboSound FM (extended channel 3 on both OPNs)##sgpr"].plurals[0] = "=ZX Spectrum (128K) with TurboSound FM (extended channel 3 on both OPNs)";
    strings["ZX Spectrum (128K) with TurboSound FM (extended channel 3 and CSM on both OPNs)##sgpr"].plurals[0] = "=ZX Spectrum (128K) with TurboSound FM (extended channel 3 and CSM on both OPNs)";
    strings["Atari 800 (stereo)##sgpr"].plurals[0] = "=Atari 800 (stereo)";
    strings["PC (beeper)##sgpr"].plurals[0] = "=PC (beeper)";
    strings["PC + AdLib (drums mode)##sgpr"].plurals[0] = "=PC + AdLib (drums mode)";
    strings["PC + Sound Blaster (drums mode)##sgpr"].plurals[0] = "=PC + Sound Blaster (drums mode)";
    strings["PC + Sound Blaster w/Game Blaster Compatible##sgpr"].plurals[0] = "=PC + Sound Blaster w/Game Blaster Compatible";
    strings["PC + Sound Blaster w/Game Blaster Compatible (drums mode)##sgpr"].plurals[0] = "=PC + Sound Blaster w/Game Blaster Compatible (drums mode)";
    strings["PC + Sound Blaster Pro (drums mode)##sgpr"].plurals[0] = "=PC + Sound Blaster Pro (drums mode)";
    strings["PC + Sound Blaster Pro 2 (drums mode)##sgpr"].plurals[0] = "=PC + Sound Blaster Pro 2 (drums mode)";
    strings["PC + ESS AudioDrive ES1488 (native ESFM mode)##sgpr"].plurals[0] = "=PC + ESS AudioDrive ES1488 (native ESFM mode)";
    strings["Sharp X1 + FM addon##sgpr"].plurals[0] = "=Sharp X1 + FM addon";
    strings["FM Towns (extended channel 3)##sgpr"].plurals[0] = "=FM Towns (extended channel 3)";
    strings["Commander X16 (VERA only)##sgpr0"].plurals[0] = "=Commander X16 (VERA only)";
    strings["Commander X16 (with OPM)##sgpr"].plurals[0] = "=Commander X16 (with OPM)";
    strings["Commander X16 (with Twin OPL3)##sgpr"].plurals[0] = "=Commander X16 (with Twin OPL3)";
    strings["Arcade systems##sgpr"].plurals[0] = "=Arcade systems";
    strings["INSERT COIN##sgpr"].plurals[0] = "=INSERT COIN";
    strings["Williams/Midway Y/T unit w/ADPCM sound board##sgpr"].plurals[0] = "=Williams/Midway Y/T unit w/ADPCM sound board";
    strings["Konami Battlantis (drums mode on first OPL2)##sgpr"].plurals[0] = "=Konami Battlantis (drums mode on first OPL2)";
    strings["Konami Battlantis (drums mode on second OPL2)##sgpr"].plurals[0] = "=Konami Battlantis (drums mode on second OPL2)";
    strings["Konami Battlantis (drums mode on both OPL2s)##sgpr"].plurals[0] = "=Konami Battlantis (drums mode on both OPL2s)";
    strings["Konami Haunted Castle (drums mode)##sgpr"].plurals[0] = "=Konami Haunted Castle (drums mode)";
    strings["Konami S.P.Y. (drums mode)##sgpr"].plurals[0] = "=Konami S.P.Y. (drums mode)";
    strings["Konami Rollergames (drums mode)##sgpr"].plurals[0] = "=Konami Rollergames (drums mode)";
    strings["Sega System E (with FM expansion)##sgpr"].plurals[0] = "=Sega System E (with FM expansion)";
    strings["Sega System E (with FM expansion in drums mode)##sgpr"].plurals[0] = "=Sega System E (with FM expansion in drums mode)";
    strings["Sega Hang-On (extended channel 3)##sgpr"].plurals[0] = "=Sega Hang-On (extended channel 3)";
    strings["Sega Hang-On (extended channel 3 and CSM)##sgpr"].plurals[0] = "=Sega Hang-On (extended channel 3 and CSM)";
    strings["Sega System 18 (extended channel 3 on first OPN2C)##sgpr"].plurals[0] = "=Sega System 18 (extended channel 3 on first OPN2C)";
    strings["Sega System 18 (extended channel 3 and CSM on first OPN2C)##sgpr"].plurals[0] = "=Sega System 18 (extended channel 3 and CSM on first OPN2C)";
    strings["Sega System 18 (extended channel 3 on second OPN2C)##sgpr"].plurals[0] = "=Sega System 18 (extended channel 3 on second OPN2C)";
    strings["Sega System 18 (extended channel 3 and CSM on second OPN2C)##sgpr"].plurals[0] = "=Sega System 18 (extended channel 3 and CSM on second OPN2C)";
    strings["Sega System 18 (extended channel 3 on both OPN2Cs)##sgpr"].plurals[0] = "=Sega System 18 (extended channel 3 on both OPN2Cs)";
    strings["Sega System 18 (extended channel 3 and CSM on both OPN2Cs)##sgpr"].plurals[0] = "=Sega System 18 (extended channel 3 and CSM on both OPN2Cs)";
    strings["Sega System 32 (extended channel 3 on first OPN2C)##sgpr"].plurals[0] = "=Sega System 32 (extended channel 3 on first OPN2C)";
    strings["Sega System 32 (extended channel 3 and CSM on first OPN2C)##sgpr"].plurals[0] = "=Sega System 32 (extended channel 3 and CSM on first OPN2C)";
    strings["Sega System 32 (extended channel 3 on second OPN2C)##sgpr"].plurals[0] = "=Sega System 32 (extended channel 3 on second OPN2C)";
    strings["Sega System 32 (extended channel 3 and CSM on second OPN2C)##sgpr"].plurals[0] = "=Sega System 32 (extended channel 3 and CSM on second OPN2C)";
    strings["Sega System 32 (extended channel 3 on both OPN2Cs)##sgpr"].plurals[0] = "=Sega System 32 (extended channel 3 on both OPN2Cs)";
    strings["Sega System 32 (extended channel 3 and CSM on both OPN2Cs)##sgpr"].plurals[0] = "=Sega System 32 (extended channel 3 and CSM on both OPN2Cs)";
    strings["Capcom Arcade##sgpr"].plurals[0] = "=Capcom Arcade";
    strings["Capcom Arcade (extended channel 3 on first OPN)##sgpr"].plurals[0] = "=Capcom Arcade (extended channel 3 on first OPN)";
    strings["Capcom Arcade (extended channel 3 and CSM on first OPN)##sgpr"].plurals[0] = "=Capcom Arcade (extended channel 3 and CSM on first OPN)";
    strings["Capcom Arcade (extended channel 3 on second OPN)##sgpr"].plurals[0] = "=Capcom Arcade (extended channel 3 on second OPN)";
    strings["Capcom Arcade (extended channel 3 and CSM on second OPN)##sgpr"].plurals[0] = "=Capcom Arcade (extended channel 3 and CSM on second OPN)";
    strings["Capcom Arcade (extended channel 3 on both OPNs)##sgpr"].plurals[0] = "=Capcom Arcade (extended channel 3 on both OPNs)";
    strings["Capcom Arcade (extended channel 3 and CSM on both OPNs)##sgpr"].plurals[0] = "=Capcom Arcade (extended channel 3 and CSM on both OPNs)";
    strings["Jaleco Ginga NinkyouDen (drums mode)##sgpr"].plurals[0] = "=Jaleco Ginga NinkyouDen (drums mode)";
    strings["NMK 16-bit Arcade##sgpr"].plurals[0] = "=NMK 16-bit Arcade";
    strings["NMK 16-bit Arcade (extended channel 3)##sgpr"].plurals[0] = "=NMK 16-bit Arcade (extended channel 3)";
    strings["NMK 16-bit Arcade (extended channel 3 and CSM)##sgpr"].plurals[0] = "=NMK 16-bit Arcade (extended channel 3 and CSM)";
    strings["NMK 16-bit Arcade (w/NMK112 bankswitching)##sgpr"].plurals[0] = "=NMK 16-bit Arcade (w/NMK112 bankswitching)";
    strings["NMK 16-bit Arcade (w/NMK112 bankswitching, extended channel 3)##sgpr"].plurals[0] = "=NMK 16-bit Arcade (w/NMK112 bankswitching, extended channel 3)";
    strings["NMK 16-bit Arcade (w/NMK112 bankswitching, extended channel 3 and CSM)##sgpr"].plurals[0] = "=NMK 16-bit Arcade (w/NMK112 bankswitching, extended channel 3 and CSM)";
    strings["Atlus Power Instinct 2 (extended channel 3)##sgpr"].plurals[0] = "=Atlus Power Instinct 2 (extended channel 3)";
    strings["Atlus Power Instinct 2 (extended channel 3 and CSM)##sgpr"].plurals[0] = "=Atlus Power Instinct 2 (extended channel 3 and CSM)";
    strings["Kaneko DJ Boy (extended channel 3)##sgpr"].plurals[0] = "=Kaneko DJ Boy (extended channel 3)";
    strings["Kaneko DJ Boy (extended channel 3 and CSM)##sgpr"].plurals[0] = "=Kaneko DJ Boy (extended channel 3 and CSM)";
    strings["Kaneko Air Buster (extended channel 3)##sgpr"].plurals[0] = "=Kaneko Air Buster (extended channel 3)";
    strings["Kaneko Air Buster (extended channel 3 and CSM)##sgpr"].plurals[0] = "=Kaneko Air Buster (extended channel 3 and CSM)";
    strings["Tecmo Ninja Gaiden (extended channel 3 on first OPN)##sgpr"].plurals[0] = "=Tecmo Ninja Gaiden (extended channel 3 on first OPN)";
    strings["Tecmo Ninja Gaiden (extended channel 3 and CSM on first OPN)##sgpr"].plurals[0] = "=Tecmo Ninja Gaiden (extended channel 3 and CSM on first OPN)";
    strings["Tecmo Ninja Gaiden (extended channel 3 on second OPN)##sgpr"].plurals[0] = "=Tecmo Ninja Gaiden (extended channel 3 on second OPN)";
    strings["Tecmo Ninja Gaiden (extended channel 3 and CSM on second OPN)##sgpr"].plurals[0] = "=Tecmo Ninja Gaiden (extended channel 3 and CSM on second OPN)";
    strings["Tecmo Ninja Gaiden (extended channel 3 on both OPNs)##sgpr"].plurals[0] = "=Tecmo Ninja Gaiden (extended channel 3 on both OPNs)";
    strings["Tecmo Ninja Gaiden (extended channel 3 and CSM on both OPNs)##sgpr"].plurals[0] = "=Tecmo Ninja Gaiden (extended channel 3 and CSM on both OPNs)";
    strings["Tecmo System (drums mode)##sgpr"].plurals[0] = "=Tecmo System (drums mode)";
    strings["Seibu Kaihatsu Raiden (drums mode)##sgpr"].plurals[0] = "=Seibu Kaihatsu Raiden (drums mode)";
    strings["Sunsoft Arcade##sgpr"].plurals[0] = "=Sunsoft Arcade";
    strings["Sunsoft Arcade (extended channel 3)##sgpr"].plurals[0] = "=Sunsoft Arcade (extended channel 3)";
    strings["Sunsoft Arcade (extended channel 3 and CSM)##sgpr"].plurals[0] = "=Sunsoft Arcade (extended channel 3 and CSM)";
    strings["Atari Rampart (drums mode)##sgpr"].plurals[0] = "=Atari Rampart (drums mode)";
    strings["Data East Karnov (extended channel 3)##sgpr"].plurals[0] = "=Data East Karnov (extended channel 3)";
    strings["Data East Karnov (extended channel 3 and CSM)##sgpr"].plurals[0] = "=Data East Karnov (extended channel 3 and CSM)";
    strings["Data East Karnov (drums mode)##sgpr"].plurals[0] = "=Data East Karnov (drums mode)";
    strings["Data East Karnov (extended channel 3; drums mode)##sgpr"].plurals[0] = "=Data East Karnov (extended channel 3; drums mode)";
    strings["Data East Karnov (extended channel 3 and CSM; drums mode)##sgpr"].plurals[0] = "=Data East Karnov (extended channel 3 and CSM; drums mode)";
    strings["Data East Arcade##sgpr"].plurals[0] = "=Data East Arcade";
    strings["Data East Arcade (extended channel 3)##sgpr"].plurals[0] = "=Data East Arcade (extended channel 3)";
    strings["Data East Arcade (extended channel 3 and CSM)##sgpr"].plurals[0] = "=Data East Arcade (extended channel 3 and CSM)";
    strings["Data East Arcade (drums mode)##sgpr"].plurals[0] = "=Data East Arcade (drums mode)";
    strings["Data East Arcade (extended channel 3; drums mode)##sgpr"].plurals[0] = "=Data East Arcade (extended channel 3; drums mode)";
    strings["Data East Arcade (extended channel 3 and CSM; drums mode)##sgpr"].plurals[0] = "=Data East Arcade (extended channel 3 and CSM; drums mode)";
    strings["Data East PCX (extended channel 3)##sgpr"].plurals[0] = "=Data East PCX (extended channel 3)";
    strings["Data East PCX (extended channel 3 and CSM)##sgpr"].plurals[0] = "=Data East PCX (extended channel 3 and CSM)";
    strings["Data East Dark Seal (extended channel 3)##sgpr"].plurals[0] = "=Data East Dark Seal (extended channel 3)";
    strings["Data East Dark Seal (extended channel 3 and CSM)##sgpr"].plurals[0] = "=Data East Dark Seal (extended channel 3 and CSM)";
    strings["SNK Ikari Warriors (drums mode on first OPL)##sgpr"].plurals[0] = "=SNK Ikari Warriors (drums mode on first OPL)";
    strings["SNK Ikari Warriors (drums mode on second OPL)##sgpr"].plurals[0] = "=SNK Ikari Warriors (drums mode on second OPL)";
    strings["SNK Ikari Warriors (drums mode on both OPLs)##sgpr"].plurals[0] = "=SNK Ikari Warriors (drums mode on both OPLs)";
    strings["SNK Triple Z80 (drums mode on Y8950)##sgpr"].plurals[0] = "=SNK Triple Z80 (drums mode on Y8950)";
    strings["SNK Triple Z80 (drums mode on OPL)##sgpr"].plurals[0] = "=SNK Triple Z80 (drums mode on OPL)";
    strings["SNK Triple Z80 (drums mode on Y8950 and OPL)##sgpr"].plurals[0] = "=SNK Triple Z80 (drums mode on Y8950 and OPL)";
    strings["SNK Chopper I (drums mode on Y8950)##sgpr"].plurals[0] = "=SNK Chopper I (drums mode on Y8950)";
    strings["SNK Chopper I (drums mode on OPL2)##sgpr"].plurals[0] = "=SNK Chopper I (drums mode on OPL2)";
    strings["SNK Chopper I (drums mode on Y8950 and OPL2)##sgpr"].plurals[0] = "=SNK Chopper I (drums mode on Y8950 and OPL2)";
    strings["SNK Touchdown Fever (drums mode on OPL)##sgpr"].plurals[0] = "=SNK Touchdown Fever (drums mode on OPL)";
    strings["SNK Touchdown Fever (drums mode on Y8950)##sgpr"].plurals[0] = "=SNK Touchdown Fever (drums mode on Y8950)";
    strings["SNK Touchdown Fever (drums mode on OPL and Y8950)##sgpr"].plurals[0] = "=SNK Touchdown Fever (drums mode on OPL and Y8950)";
    strings["Alpha denshi Alpha-68K (extended channel 3)##sgpr"].plurals[0] = "=Alpha denshi Alpha-68K (extended channel 3)";
    strings["Alpha denshi Alpha-68K (extended channel 3 and CSM)##sgpr"].plurals[0] = "=Alpha denshi Alpha-68K (extended channel 3 and CSM)";
    strings["Alpha denshi Alpha-68K (drums mode)##sgpr"].plurals[0] = "=Alpha denshi Alpha-68K (drums mode)";
    strings["Alpha denshi Alpha-68K (extended channel 3; drums mode)##sgpr"].plurals[0] = "=Alpha denshi Alpha-68K (extended channel 3; drums mode)";
    strings["Alpha denshi Alpha-68K (extended channel 3 and CSM; drums mode)##sgpr"].plurals[0] = "=Alpha denshi Alpha-68K (extended channel 3 and CSM; drums mode)";
    strings["Neo Geo MVS (extended channel 2)##sgpr"].plurals[0] = "=Neo Geo MVS (extended channel 2)";
    strings["Neo Geo MVS (extended channel 2 and CSM)##sgpr"].plurals[0] = "=Neo Geo MVS (extended channel 2 and CSM)";
    strings["Namco (3-channel WSG)##sgpr"].plurals[0] = "=Namco (3-channel WSG)";
    strings["Taito Arcade##sgpr"].plurals[0] = "=Taito Arcade";
    strings["Taito Arcade (extended channel 3)##sgpr"].plurals[0] = "=Taito Arcade (extended channel 3)";
    strings["Taito Arcade (extended channel 3 and CSM)##sgpr"].plurals[0] = "=Taito Arcade (extended channel 3 and CSM)";
    strings["Seta 1 + FM addon##sgpr"].plurals[0] = "=Seta 1 + FM addon";
    strings["Seta 1 + FM addon (extended channel 3)##sgpr"].plurals[0] = "=Seta 1 + FM addon (extended channel 3)";
    strings["Seta 1 + FM addon (extended channel 3 and CSM)##sgpr"].plurals[0] = "=Seta 1 + FM addon (extended channel 3 and CSM)";
    strings["Coreland Cyber Tank (drums mode)##sgpr"].plurals[0] = "=Coreland Cyber Tank (drums mode)";
    strings["Toaplan 1 (drums mode)##sgpr"].plurals[0] = "=Toaplan 1 (drums mode)";
    strings["Dynax/Nakanihon 3rd generation hardware##sgpr"].plurals[0] = "=Dynax/Nakanihon 3rd generation hardware";
    strings["Dynax/Nakanihon 3rd generation hardware (drums mode)##sgpr"].plurals[0] = "=Dynax/Nakanihon 3rd generation hardware (drums mode)";
    strings["Dynax/Nakanihon Real Break (drums mode)##sgpr"].plurals[0] = "=Dynax/Nakanihon Real Break (drums mode)";
    strings["User##sgpr"].plurals[0] = "=User";
    strings["system presets that you have saved.##sgpr"].plurals[0] = "=system presets that you have saved.";
    strings["chips which use frequency modulation (FM) to generate sound.\nsome of these also pack more (like square and sample channels).\nActually \"FM\" here stands for phase modulation,\nbut these two are indistinguishable\nif you use sine waves.##sgpr"].plurals[0] = "=chips which use frequency modulation (FM) to generate sound.\nsome of these also pack more (like square and sample channels).\nActually \"FM\" here stands for phase modulation,\nbut these two are indistinguishable\nif you use sine waves.";
    strings["Yamaha YM2203 (extended channel 3)##sgpr"].plurals[0] = "=Yamaha YM2203 (extended channel 3)";
    strings["Yamaha YM2203 (extended channel 3 and CSM)##sgpr"].plurals[0] = "=Yamaha YM2203 (extended channel 3 and CSM)";
    strings["Yamaha YM2608 (extended channel 3)##sgpr"].plurals[0] = "=Yamaha YM2608 (extended channel 3)";
    strings["Yamaha YM2608 (extended channel 3 and CSM)##sgpr"].plurals[0] = "=Yamaha YM2608 (extended channel 3 and CSM)";
    strings["Yamaha YM2610 (extended channel 2)##sgpr"].plurals[0] = "=Yamaha YM2610 (extended channel 2)";
    strings["Yamaha YM2610 (extended channel 2 and CSM)##sgpr"].plurals[0] = "=Yamaha YM2610 (extended channel 2 and CSM)";
    strings["Yamaha YM2610B (extended channel 3)##sgpr"].plurals[0] = "=Yamaha YM2610B (extended channel 3)";
    strings["Yamaha YM2610B (extended channel 3 and CSM)##sgpr"].plurals[0] = "=Yamaha YM2610B (extended channel 3 and CSM)";
    strings["Yamaha YM2612 (extended channel 3)##sgpr"].plurals[0] = "=Yamaha YM2612 (extended channel 3)";
    strings["Yamaha YM2612 (OPN2) with DualPCM##sgpr"].plurals[0] = "=Yamaha YM2612 (OPN2) with DualPCM";
    strings["Yamaha YM2612 (extended channel 3) with DualPCM and CSM##sgpr"].plurals[0] = "=Yamaha YM2612 (extended channel 3) with DualPCM and CSM";
    strings["Yamaha YMF276 (extended channel 3)##sgpr"].plurals[0] = "=Yamaha YMF276 (extended channel 3)";
    strings["Yamaha YMF276 with DualPCM##sgpr"].plurals[0] = "=Yamaha YMF276 with DualPCM";
    strings["Yamaha YMF276 (extended channel 3) with DualPCM and CSM##sgpr"].plurals[0] = "=Yamaha YMF276 (extended channel 3) with DualPCM and CSM";
    strings["Yamaha YM2413 (drums mode)##sgpr"].plurals[0] = "=Yamaha YM2413 (drums mode)";
    strings["Yamaha YM3438 (extended channel 3)##sgpr"].plurals[0] = "=Yamaha YM3438 (extended channel 3)";
    strings["Yamaha YM3438 (OPN2C) with DualPCM##sgpr"].plurals[0] = "=Yamaha YM3438 (OPN2C) with DualPCM";
    strings["Yamaha YM3438 (extended channel 3) with DualPCM and CSM##sgpr"].plurals[0] = "=Yamaha YM3438 (extended channel 3) with DualPCM and CSM";
    strings["Yamaha YM3526 (drums mode)##sgpr"].plurals[0] = "=Yamaha YM3526 (drums mode)";
    strings["Yamaha Y8950 (drums mode)##sgpr"].plurals[0] = "=Yamaha Y8950 (drums mode)";
    strings["Yamaha YM3812 (drums mode)##sgpr"].plurals[0] = "=Yamaha YM3812 (drums mode)";
    strings["Yamaha YMF262 (drums mode)##sgpr"].plurals[0] = "=Yamaha YMF262 (drums mode)";
    strings["Yamaha YMF289B (drums mode)##sgpr"].plurals[0] = "=Yamaha YMF289B (drums mode)";
    strings["ESS ES1xxx series (ESFM)##sgpr"].plurals[0] = "=ESS ES1xxx series (ESFM)";
    strings["Square##sgpr"].plurals[0] = "=Square";
    strings["these chips generate square/pulse tones only (but may include noise).##sgpr"].plurals[0] = "=these chips generate square/pulse tones only (but may include noise).";
    strings["Tandy PSSJ 3-voice sound##sgpr"].plurals[0] = "=Tandy PSSJ 3-voice sound";
    strings["Sega PSG (SN76489-like)##sgpr"].plurals[0] = "=Sega PSG (SN76489-like)";
    strings["Sega PSG (SN76489-like, Stereo)##sgpr"].plurals[0] = "=Sega PSG (SN76489-like, Stereo)";
    strings["PC Speaker##sgpr"].plurals[0] = "=PC Speaker";
    strings["Sample##sgpr"].plurals[0] = "=Sample";
    strings["chips/systems which use PCM or ADPCM samples for sound synthesis.##sgpr"].plurals[0] = "=chips/systems which use PCM or ADPCM samples for sound synthesis.";
    strings["Generic PCM DAC##sgpr"].plurals[0] = "=Generic PCM DAC";
    strings["Wavetable##sgpr"].plurals[0] = "=Wavetable";
    strings["chips which use user-specified waveforms to generate sound.##sgpr"].plurals[0] = "=chips which use user-specified waveforms to generate sound.";
    strings["Namco C15 (8-channel mono)##sgpr"].plurals[0] = "=Namco C15 (8-channel mono)";
    strings["Namco C30 (8-channel stereo)##sgpr"].plurals[0] = "=Namco C30 (8-channel stereo)";
    strings["Famicom Disk System (chip)##sgpr"].plurals[0] = "=Famicom Disk System (chip)";
    strings["Specialized##sgpr"].plurals[0] = "=Specialized";
    strings["chips/systems with unique sound synthesis methods.##sgpr"].plurals[0] = "=chips/systems with unique sound synthesis methods.";
    strings["Commodore PET (pseudo-wavetable)##sgpr"].plurals[0] = "=Commodore PET (pseudo-wavetable)";
    strings["ZX Spectrum (beeper only, SFX-like engine)##sgpr"].plurals[0] = "=ZX Spectrum (beeper only, SFX-like engine)";
    strings["ZX Spectrum (beeper only, QuadTone engine)##sgpr"].plurals[0] = "=ZX Spectrum (beeper only, QuadTone engine)";
    strings["Modern/fantasy##sgpr"].plurals[0] = "=Modern/fantasy";
    strings["chips/systems which do not exist in reality or were made just several years ago.##sgpr"].plurals[0] = "=chips/systems which do not exist in reality or were made just several years ago.";
    strings["Commander X16 (VERA only)##sgpr1"].plurals[0] = "=Commander X16 (VERA only)";
    strings["DefleMask-compatible##sgpr"].plurals[0] = "=DefleMask-compatible";
    strings["these configurations are compatible with DefleMask.\nselect this if you need to save as .dmf or work with that program.##sgpr"].plurals[0] = "=these configurations are compatible with DefleMask.\nselect this if you need to save as .dmf or work with that program.";
    strings["Sega Genesis (extended channel 3)##sgpr1"].plurals[0] = "=Sega Genesis (extended channel 3)";
    strings["Sega Master System (with FM expansion)##sgpr1"].plurals[0] = "=Sega Master System (with FM expansion)";
    strings["Famicom with Konami VRC7##sgpr1"].plurals[0] = "=Famicom with Konami VRC7";
    strings["Arcade (YM2151 and SegaPCM)##sgpr1"].plurals[0] = "=Arcade (YM2151 and SegaPCM)";
    strings["Neo Geo CD (extended channel 2)##sgpr1"].plurals[0] = "=Neo Geo CD (extended channel 2)";

    //   sgrv  src/gui/regView.cpp

    strings["Register View###Register View"].plurals[0] = "=Register View###Register View";
    strings["- no register pool available##sgrv"].plurals[0] = "=- no register pool available";

    //  sgsed  src/gui/sampleEdit.cpp

    strings["%s: maximum sample rate is %d##sgsed"].plurals[0] = "=%s: maximum sample rate is %d";
    strings["%s: minimum sample rate is %d##sgsed"].plurals[0] = "=%s: minimum sample rate is %d";
    strings["%s: sample rate must be %d##sgsed"].plurals[0] = "=%s: sample rate must be %d";
    strings["Sample Editor###Sample Editor"].plurals[0] = "=Sample Editor###Sample Editor";
    strings["no sample selected##sgsed"].plurals[0] = "=no sample selected";
    strings["select one...##sgsed"].plurals[0] = "=select one...";
    strings["or##sgsed0"].plurals[0] = "=or";
    strings["Open##sgsed0"].plurals[0] = "=Open";
    strings["or##sgsed1"].plurals[0] = "=or";
    strings["Create New##sgsed"].plurals[0] = "=Create New";
    strings["Invalid##sgsed0"].plurals[0] = "=Invalid";
    strings["Invalid##sgsed1"].plurals[0] = "=Invalid";
    strings["%d: %s"].plurals[0] = "=%d: %s";
    strings["Open##sgsed1"].plurals[0] = "=Open";
    strings["import raw...##sgsed"].plurals[0] = "=import raw...";
    strings["Save##sgsed"].plurals[0] = "=Save";
    strings["save raw...##sgsed"].plurals[0] = "=save raw...";
    strings["Name##sgsed"].plurals[0] = "=Name";
    strings["SNES: loop start must be a multiple of 16 (try with %d)##sgsed"].plurals[0] = "=SNES: loop start must be a multiple of 16 (try with %d)";
    strings["SNES: loop end must be a multiple of 16 (try with %d)##sgsed"].plurals[0] = "=SNES: loop end must be a multiple of 16 (try with %d)";
    strings["SNES: sample length will be padded to multiple of 16##sgsed"].plurals[0] = "=SNES: sample length will be padded to multiple of 16";
    strings["QSound: loop cannot be longer than 32767 samples##sgsed"].plurals[0] = "=QSound: loop cannot be longer than 32767 samples";
    strings["QSound: maximum sample length is 65535##sgsed"].plurals[0] = "=QSound: maximum sample length is 65535";
    strings["NES: loop point ignored on DPCM (may only loop entire sample)##sgsed"].plurals[0] = "=NES: loop point ignored on DPCM (may only loop entire sample)";
    strings["NES: maximum DPCM sample length is 32648##sgsed"].plurals[0] = "=NES: maximum DPCM sample length is 32648";
    strings["X1-010: samples can't loop##sgsed"].plurals[0] = "=X1-010: samples can't loop";
    strings["X1-010: maximum sample length is 131072##sgsed"].plurals[0] = "=X1-010: maximum sample length is 131072";
    strings["GA20: samples can't loop##sgsed"].plurals[0] = "=GA20: samples can't loop";
    strings["YM2608: loop point ignored on ADPCM (may only loop entire sample)##sgsed"].plurals[0] = "=YM2608: loop point ignored on ADPCM (may only loop entire sample)";
    strings["YM2608: sample length will be padded to multiple of 512##sgsed"].plurals[0] = "=YM2608: sample length will be padded to multiple of 512";
    strings["YM2610: ADPCM-A samples can't loop##sgsed"].plurals[0] = "=YM2610: ADPCM-A samples can't loop";
    strings["YM2610: loop point ignored on ADPCM-B (may only loop entire sample)##sgsed"].plurals[0] = "=YM2610: loop point ignored on ADPCM-B (may only loop entire sample)";
    strings["YM2610: sample length will be padded to multiple of 512##sgsed"].plurals[0] = "=YM2610: sample length will be padded to multiple of 512";
    strings["YM2610: maximum ADPCM-A sample length is 2097152##sgsed"].plurals[0] = "=YM2610: maximum ADPCM-A sample length is 2097152";
    strings["Y8950: loop point ignored on ADPCM (may only loop entire sample)##sgsed"].plurals[0] = "=Y8950: loop point ignored on ADPCM (may only loop entire sample)";
    strings["Y8950: sample length will be padded to multiple of 512##sgsed"].plurals[0] = "=Y8950: sample length will be padded to multiple of 512";
    strings["Amiga: loop start must be a multiple of 2##sgsed"].plurals[0] = "=Amiga: loop start must be a multiple of 2";
    strings["Amiga: loop end must be a multiple of 2##sgsed"].plurals[0] = "=Amiga: loop end must be a multiple of 2";
    strings["Amiga: maximum sample length is 131070##sgsed"].plurals[0] = "=Amiga: maximum sample length is 131070";
    strings["SegaPCM: maximum sample length is 65280##sgsed"].plurals[0] = "=SegaPCM: maximum sample length is 65280";
    strings["K053260: loop point ignored (may only loop entire sample)##sgsed"].plurals[0] = "=K053260: loop point ignored (may only loop entire sample)";
    strings["K053260: maximum sample length is 65535##sgsed"].plurals[0] = "=K053260: maximum sample length is 65535";
    strings["C140: maximum sample length is 65535##sgsed"].plurals[0] = "=C140: maximum sample length is 65535";
    strings["C219: loop start must be a multiple of 2##sgsed"].plurals[0] = "=C219: loop start must be a multiple of 2";
    strings["C219: loop end must be a multiple of 2##sgsed"].plurals[0] = "=C219: loop end must be a multiple of 2";
    strings["C219: maximum sample length is 131072##sgsed"].plurals[0] = "=C219: maximum sample length is 131072";
    strings["MSM6295: samples can't loop##sgsed"].plurals[0] = "=MSM6295: samples can't loop";
    strings["MSM6295: maximum bankswitched sample length is 129024##sgsed"].plurals[0] = "=MSM6295: maximum bankswitched sample length is 129024";
    strings["GBA DMA: loop start must be a multiple of 4##sgsed"].plurals[0] = "=GBA DMA: loop start must be a multiple of 4##sgsed";
    strings["GBA DMA: loop length must be a multiple of 16##sgsed"].plurals[0] = "=GBA DMA: loop length must be a multiple of 16##sgsed";
    strings["GBA DMA: sample length will be padded to multiple of 16##sgsed"].plurals[0] = "=GBA DMA: sample length will be padded to multiple of 16##sgsed";
    strings["ES5506: backward loop mode isn't supported##sgsed"].plurals[0] = "=ES5506: backward loop mode isn't supported";
    strings["backward/ping-pong only supported in Generic PCM DAC\nping-pong also on ES5506##sgsed"].plurals[0] = "=backward/ping-pong only supported in Generic PCM DAC\nping-pong also on ES5506";
    strings["Info##sgsed"].plurals[0] = "=Info";
    strings["Rate##sgsed0"].plurals[0] = "=Rate";
    strings["Compat Rate##sgsed"].plurals[0] = "=Compat Rate";
    strings["used in DefleMask-compatible sample mode (17xx), in where samples are mapped to an octave.##sgsed"].plurals[0] = "=used in DefleMask-compatible sample mode (17xx), in where samples are mapped to an octave.";
    strings["Loop (length: %d)##Loop"].plurals[0] = "=Loop (length: %d)";
    strings["Loop##sgsed"].plurals[0] = "=Loop";
    strings["changing the loop in a BRR sample may result in glitches!##sgsed0"].plurals[0] = "=changing the loop in a BRR sample may result in glitches!";
    strings["Chips##sgsed"].plurals[0] = "=Chips";
    strings["Type##sgsed"].plurals[0] = "=Type";
    strings["BRR emphasis##sgsed"].plurals[0] = "=BRR emphasis";
    strings["this is a BRR sample.\nenabling this option will muffle it (only affects non-SNES chips).##sgsed"].plurals[0] = "=this is a BRR sample.\nenabling this option will muffle it (only affects non-SNES chips).";
    strings["enable this option to slightly boost high frequencies\nto compensate for the SNES' Gaussian filter's muffle.##sgsed"].plurals[0] = "=enable this option to slightly boost high frequencies\nto compensate for the SNES' Gaussian filter's muffle.";
    strings["8-bit dither##sgsed"].plurals[0] = "=8-bit dither";
    strings["dither the sample when used on a chip that only supports 8-bit samples.##sgsed"].plurals[0] = "=dither the sample when used on a chip that only supports 8-bit samples.";
    strings["Hz##sgsed"].plurals[0] = "=Hz";
    strings["Note##sgsed"].plurals[0] = "=Note";
    strings["%s"].plurals[0] = "=%s";
    strings["Fine##sgsed"].plurals[0] = "=Fine";
    strings["Mode##sgsed"].plurals[0] = "=Mode";
    strings["Start##sgsed"].plurals[0] = "=Start";
    strings["changing the loop in a BRR sample may result in glitches!##sgsed1"].plurals[0] = "=changing the loop in a BRR sample may result in glitches!";
    strings["End##sgsed"].plurals[0] = "=End";
    strings["changing the loop in a BRR sample may result in glitches!##sgsed2"].plurals[0] = "=changing the loop in a BRR sample may result in glitches!";
    strings["%s\n%d bytes free##sgsed"].plurals[0] = "=%s\n%d byte free";
    strings["%s\n%d bytes free##sgsed"].plurals[1] = "=%s\n%d bytes free";
    strings["%s (%s)\n%d bytes free##sgsed"].plurals[0] = "=%s (%s)\n%d byte free";
    strings["%s (%s)\n%d bytes free##sgsed"].plurals[1] = "=%s (%s)\n%d bytes free";
    strings["\n\nnot enough memory for this sample!##sgsed"].plurals[0] = "=\n\nnot enough memory for this sample!";
    strings["Edit mode: Select##sgsed"].plurals[0] = "=Edit mode: Select";
    strings["Edit mode: Draw##sgsed"].plurals[0] = "=Edit mode: Draw";
    strings["Resize##sgsed0"].plurals[0] = "=Resize";
    strings["Samples##sgsed0"].plurals[0] = "=Samples";
    strings["Resize##sgsed1"].plurals[0] = "=Resize";
    strings["couldn't resize! make sure your sample is 8 or 16-bit.##sgsed"].plurals[0] = "=couldn't resize! make sure your sample is 8 or 16-bit.";
    strings["Resample##sgsed0"].plurals[0] = "=Resample";
    strings["Rate##sgsed1"].plurals[0] = "=Rate";
    strings["Factor##sgsed"].plurals[0] = "=Factor";
    strings["Filter##sgsed"].plurals[0] = "=Filter";
    strings["Resample##sgsed1"].plurals[0] = "=Resample";
    strings["couldn't resample! make sure your sample is 8 or 16-bit.##sgsed"].plurals[0] = "=couldn't resample! make sure your sample is 8 or 16-bit.";
    strings["Undo##sgsed"].plurals[0] = "=Undo";
    strings["Redo##sgsed"].plurals[0] = "=Redo";
    strings["Amplify##sgsed"].plurals[0] = "=Amplify";
    strings["Volume##sgsed"].plurals[0] = "=Volume";
    strings["Apply##sgsed0"].plurals[0] = "=Apply";
    strings["Normalize##sgsed"].plurals[0] = "=Normalize";
    strings["Fade in##sgsed"].plurals[0] = "=Fade in";
    strings["Fade out##sgsed"].plurals[0] = "=Fade out";
    strings["Insert silence##sgsed"].plurals[0] = "=Insert silence";
    strings["Samples##sgsed1"].plurals[0] = "=Samples";
    strings["Go##sgsed"].plurals[0] = "=Go";
    strings["couldn't insert! make sure your sample is 8 or 16-bit.##sgsed"].plurals[0] = "=couldn't insert! make sure your sample is 8 or 16-bit.";
    strings["Apply silence##sgsed"].plurals[0] = "=Apply silence";
    strings["Delete##sgsed"].plurals[0] = "=Delete";
    strings["Trim##sgsed"].plurals[0] = "=Trim";
    strings["Reverse##sgsed"].plurals[0] = "=Reverse";
    strings["Invert##sgsed"].plurals[0] = "=Invert";
    strings["Signed/unsigned exchange##sgsed"].plurals[0] = "=Signed/unsigned exchange";
    strings["Apply filter##sgsed"].plurals[0] = "=Apply filter";
    strings["Cutoff:##sgsed"].plurals[0] = "=Cutoff:";
    strings["From##sgsed"].plurals[0] = "=From";
    strings["To##sgsed"].plurals[0] = "=To";
    strings["Resonance##sgsed"].plurals[0] = "=Resonance";
    strings["Power##sgsed"].plurals[0] = "=Power";
    strings["Low-pass##sgsed"].plurals[0] = "=Low-pass";
    strings["Band-pass##sgsed"].plurals[0] = "=Band-pass";
    strings["High-pass##sgsed"].plurals[0] = "=High-pass";
    strings["Apply##sgsed1"].plurals[0] = "=Apply";
    strings["Crossfade loop points##sgsed"].plurals[0] = "=Crossfade loop points";
    strings["Number of samples##sgsed"].plurals[0] = "=Number of samples";
    strings["Linear <-> Equal power##sgsed"].plurals[0] = "=Linear <-> Equal power";
    strings["Apply##sgsed2"].plurals[0] = "=Apply";
    strings["Crossfade: length would go out of bounds. Aborted...##sgsed"].plurals[0] = "=Crossfade: length would go out of bounds. Aborted...";
    strings["Crossfade: length would overflow loopStart. Try a smaller random value.##sgsed"].plurals[0] = "=Crossfade: length would overflow loopStart. Try a smaller random value.";
    strings["Preview sample##sgsed"].plurals[0] = "=Preview sample";
    strings["Stop sample preview##sgsed"].plurals[0] = "=Stop sample preview";
    strings["Create instrument from sample##sgsed"].plurals[0] = "=Create instrument from sample";
    strings["Zoom##sgsed0"].plurals[0] = "=Zoom";
    strings["Zoom##sgsed1"].plurals[0] = "=Zoom";
    strings["%dms"].plurals[0] = "=%dms";
    strings["Auto##sgsed"].plurals[0] = "=Auto";
    strings["cut##sgsed"].plurals[0] = "=cut";
    strings["copy##sgsed"].plurals[0] = "=copy";
    strings["paste##sgsed"].plurals[0] = "=paste";
    strings["paste (replace)##sgsed"].plurals[0] = "=paste (replace)";
    strings["paste (mix)##sgsed"].plurals[0] = "=paste (mix)";
    strings["select all##sgsed"].plurals[0] = "=select all";
    strings["set loop to selection##sgsed"].plurals[0] = "=set loop to selection";
    strings["create wavetable from selection##sgsed"].plurals[0] = "=create wavetable from selection";
    strings["Draw##sgsed"].plurals[0] = "=Draw";
    strings["Select##sgsed"].plurals[0] = "=Select";
    strings["%d samples##sgsed"].plurals[0] = "=%d sample";
    strings["%d samples##sgsed"].plurals[1] = "=%d samples";
    strings["%d bytes##sgsed"].plurals[0] = "=%d byte";
    strings["%d bytes##sgsed"].plurals[1] = "=%d bytes";
    strings[" (%d-%d: %d samples)##sgsed"].plurals[0] = "= (%d-%d: %d sample)";
    strings[" (%d-%d: %d samples)##sgsed"].plurals[1] = "= (%d-%d: %d samples)";
    strings["Non-8/16-bit samples cannot be edited without prior conversion.##sgsed"].plurals[0] = "=Non-8/16-bit samples cannot be edited without prior conversion.";

    //   sgsi  src/gui/songInfo.cpp

    strings["Song Info###Song Information"].plurals[0] = "=Song Info###Song Information";
    strings["Name##sgsi"].plurals[0] = "=Name";
    strings["Author##sgsi"].plurals[0] = "=Author";
    strings["Album##sgsi"].plurals[0] = "=Album";
    strings["System##sgsi"].plurals[0] = "=System";
    strings["Auto##sgsi"].plurals[0] = "=Auto";
    strings["Tuning (A-4)##sgsi"].plurals[0] = "=Tuning (A-4)";

    // # sgsn  src/gui/songNotes.cpp

    strings["Song Comments###Song Comments"].plurals[0] = "=Song Comments###Song Comments";

    //   sgsp  src/gui/speed.cpp

    strings["Speed###Speed"].plurals[0] = "=Speed###Speed";
    strings["Base Tempo##TempoOrHz"].plurals[0] = "=Base Tempo##TempoOrHz";
    strings["Tick Rate##TempoOrHz"].plurals[0] = "=Tick Rate##TempoOrHz";
    strings["click to display tick rate##sgsp"].plurals[0] = "=click to display tick rate";
    strings["click to display base tempo##sgsp"].plurals[0] = "=click to display base tempo";
    strings["Groove##sgsp"].plurals[0] = "=Groove";
    strings["click for one speed##sgsp"].plurals[0] = "=click for one speed";
    strings["Speeds##sgsp"].plurals[0] = "=Speeds";
    strings["click for groove pattern##sgsp"].plurals[0] = "=click for groove pattern";
    strings["Speed##sgsp"].plurals[0] = "=Speed";
    strings["click for two (alternating) speeds##sgsp"].plurals[0] = "=click for two (alternating) speeds";
    strings["Virtual Tempo##sgsp"].plurals[0] = "=Virtual Tempo";
    strings["Numerator##sgsp"].plurals[0] = "=Numerator";
    strings["Denominator (set to base tempo)##sgsp"].plurals[0] = "=Denominator (set to base tempo)";
    strings["Divider##sgsp"].plurals[0] = "=Divider";
    strings["Highlight##sgsp"].plurals[0] = "=Highlight";
    strings["Pattern Length##sgsp"].plurals[0] = "=Pattern Length";
    strings["Song Length##sgsp"].plurals[0] = "=Song Length";

    //   sgst  src/gui/stats.cpp

    strings["Statistics###Statistics"].plurals[0] = "=Statistics###Statistics";
    strings["Audio load##sgst"].plurals[0] = "=Audio load";

    //   sgss  src/gui/subSongs.cpp

    strings["Subsongs###Subsongs"].plurals[0] = "=Subsongs###Subsongs";
    strings["%d. <no name>##sgss0"].plurals[0] = "=%d. <no name>";
    strings["%d. <no name>##sgss1"].plurals[0] = "=%d. <no name>";
    strings["Move up##sgss"].plurals[0] = "=Move up";
    strings["Move down##sgss"].plurals[0] = "=Move down";
    strings["too many subsongs!##sgss0"].plurals[0] = "=too many subsongs!";
    strings["Add##sgss"].plurals[0] = "=Add";
    strings["too many subsongs!##sgss1"].plurals[0] = "=too many subsongs!";
    strings["Duplicate##sgss"].plurals[0] = "=Duplicate";
    strings["this is the only subsong!##sgss"].plurals[0] = "=this is the only subsong!";
    strings["are you sure you want to remove this subsong?##sgss"].plurals[0] = "=are you sure you want to remove this subsong?";
    strings["Remove##sgss"].plurals[0] = "=Remove";
    strings["Name##sgss"].plurals[0] = "=Name";

    //   sgsc  src/gui/sysConf.cpp

    strings["Clock rate:##sgsc0"].plurals[0] = "=Clock rate:";
    strings["Chip type:##sgsc0"].plurals[0] = "=Chip type:";
    strings["YM3438 (9-bit DAC)##sgsc"].plurals[0] = "=YM3438 (9-bit DAC)";
    strings["YM2612 (9-bit DAC with distortion)##sgsc"].plurals[0] = "=YM2612 (9-bit DAC with distortion)";
    strings["YMF276 (external DAC)##sgsc"].plurals[0] = "=YMF276 (external DAC)";
    strings["Disable ExtCh FM macros (compatibility)##sgsc0"].plurals[0] = "=Disable ExtCh FM macros (compatibility)";
    strings["Ins change in ExtCh operator 2-4 affects FB (compatibility)##sgsc0"].plurals[0] = "=Ins change in ExtCh operator 2-4 affects FB (compatibility)";
    strings["Clock rate:##sgsc1"].plurals[0] = "=Clock rate:";
    strings["1.79MHz (Half NTSC)##sgsc"].plurals[0] = "=1.79MHz (Half NTSC)";
    strings["Chip type:##sgsc1"].plurals[0] = "=Chip type:";
    strings["TI SN76489 with Atari-like short noise##sgsc"].plurals[0] = "=TI SN76489 with Atari-like short noise";
    strings["Tandy PSSJ 3-voice sound##sgsc"].plurals[0] = "=Tandy PSSJ 3-voice sound";
    strings["Disable noise period change phase reset##sgsc"].plurals[0] = "=Disable noise period change phase reset";
    strings["Disable easy period to note mapping on upper octaves##sgsc0"].plurals[0] = "=Disable easy period to note mapping on upper octaves";
    strings["Pseudo-PAL##sgsc0"].plurals[0] = "=Pseudo-PAL";
    strings["Disable anti-click##sgsc0"].plurals[0] = "=Disable anti-click";
    strings["Chip revision:##sgsc0"].plurals[0] = "=Chip revision:";
    strings["HuC6280 (original)##sgsc"].plurals[0] = "=HuC6280 (original)";
    strings["CPU rate:##sgsc"].plurals[0] = "=CPU rate:";
    strings["Sample memory:##sgsc"].plurals[0] = "=Sample memory:";
    strings["8K (rev A/B/E)##sgsc"].plurals[0] = "=8K (rev A/B/E)";
    strings["64K (rev D/F)##sgsc"].plurals[0] = "=64K (rev D/F)";
    strings["DAC resolution:##sgsc"].plurals[0] = "=DAC resolution:";
    strings["16-bit (rev A/B/D/F)##sgsc"].plurals[0] = "=16-bit (rev A/B/D/F)";
    strings["8-bit + TDM (rev C/E)##sgsc"].plurals[0] = "=8-bit + TDM (rev C/E)";
    strings["Enable echo##sgsc0"].plurals[0] = "=Enable echo";
    strings["Swap echo channels##sgsc"].plurals[0] = "=Swap echo channels";
    strings["Echo delay:##sgsc0"].plurals[0] = "=Echo delay:";
    strings["Echo resolution:##sgsc"].plurals[0] = "=Echo resolution:";
    strings["Echo feedback:##sgsc0"].plurals[0] = "=Echo feedback:";
    strings["Echo volume:##sgsc0"].plurals[0] = "=Echo volume:";
    strings["Disable anti-click##sgsc1"].plurals[0] = "=Disable anti-click";
    strings["Chip revision:##sgsc1"].plurals[0] = "=Chip revision:";
    strings["Original (DMG)##sgsc"].plurals[0] = "=Original (DMG)";
    strings["Game Boy Color (rev C)##sgsc"].plurals[0] = "=Game Boy Color (rev C)";
    strings["Game Boy Color (rev E)##sgsc"].plurals[0] = "=Game Boy Color (rev E)";
    strings["Wave channel orientation:##sgsc"].plurals[0] = "=Wave channel orientation:";
    strings["Normal##sgsc"].plurals[0] = "=Normal";
    strings["Inverted##sgsc"].plurals[0] = "=Inverted";
    strings["Exact data (inverted)##sgsc"].plurals[0] = "=Exact data (inverted)";
    strings["Exact output (normal)##sgsc"].plurals[0] = "=Exact output (normal)";
    strings["Pretty please one more compat flag when I use arpeggio and my sound length##sgsc"].plurals[0] = "=Pretty please one more compat flag when I use arpeggio and my sound length";
    strings["Clock rate:##sgsc2"].plurals[0] = "=Clock rate:";
    strings["Pretty please one more compat flag when I use arpeggio and my sound length##sgsc"].plurals[0] = "=Pretty please one more compat flag when I use arpeggio and my sound length##sgsc";
    strings["DAC bit depth (reduces output rate):##sgsc"].plurals[0] = "=DAC bit depth (reduces output rate):";
    strings["Volume scale:##sgsc"].plurals[0] = "=Volume scale:";
    strings["Mix buffers (allows longer echo delay):##sgsc"].plurals[0] = "=Mix buffers (allows longer echo delay):";
    strings["Channel limit:##sgsc"].plurals[0] = "=Channel limit:";
    strings["Sample rate:##sgsc"].plurals[0] = "=Sample rate:";
    strings["Actual sample rate: %d Hz##sgsc"].plurals[0] = "=Actual sample rate: %d Hz";
    strings["Max mixer CPU usage: %.0f%%##sgsc"].plurals[0] = "=Max mixer CPU usage: %.0f%%";
    strings["Arcade (4MHz)##sgsc"].plurals[0] = "=Arcade (4MHz)";
    strings["Half NTSC (1.79MHz)##sgsc"].plurals[0] = "=Half NTSC (1.79MHz)";
    strings["Patch set:##sgsc"].plurals[0] = "=Patch set:";
    strings["Ignore top/hi-hat frequency changes##sgsc"].plurals[0] = "=Ignore top/hi-hat frequency changes";
    strings["Apply fixed frequency to all drums at once##sgsc"].plurals[0] = "=Apply fixed frequency to all drums at once";
    strings["Broken pitch macro/slides (compatibility)##sgsc0"].plurals[0] = "=Broken pitch macro/slides (compatibility)";
    strings["Pseudo-PAL##sgsc1"].plurals[0] = "=Pseudo-PAL";
    strings["Broken pitch macro/slides (compatibility)##sgsc1"].plurals[0] = "=Broken pitch macro/slides (compatibility)";
    strings["Clock rate:##sgsc20"].plurals[0] = "=Clock rate:";
    strings["DPCM channel mode:##sgsc"].plurals[0] = "=DPCM channel mode:";
    strings["DPCM (muffled samples; low CPU usage)##sgsc"].plurals[0] = "=DPCM (muffled samples; low CPU usage)";
    strings["PCM (crisp samples; high CPU usage)##sgsc"].plurals[0] = "=PCM (crisp samples; high CPU usage)";
    strings["Clock rate:##sgsc18"].plurals[0] = "=Clock rate:";
    strings["Clock rate:##sgsc19"].plurals[0] = "=Clock rate:";
    strings["Global parameter priority:##sgsc0"].plurals[0] = "=Global parameter priority:";
    strings["Left to right##sgsc0"].plurals[0] = "=Left to right";
    strings["Last used channel##sgsc0"].plurals[0] = "=Last used channel";
    strings["Hard reset envelope:##sgsc"].plurals[0] = "=Hard reset envelope:";
    strings["Attack##sgsc"].plurals[0] = "=Attack";
    strings["Decay##sgsc"].plurals[0] = "=Decay";
    strings["Sustain##sgsc"].plurals[0] = "=Sustain";
    strings["Release##sgsc"].plurals[0] = "=Release";
    strings["Envelope reset time:##sgsc"].plurals[0] = "=Envelope reset time:";
    strings["- 0 disables envelope reset. not recommended!\n- 1 may trigger SID envelope bugs.\n- values that are too high may result in notes being skipped.##sgsc"].plurals[0] = "=- 0 disables envelope reset. not recommended!\n- 1 may trigger SID envelope bugs.\n- values that are too high may result in notes being skipped.";
    strings["Disable 1Exy env update (compatibility)##sgsc"].plurals[0] = "=Disable 1Exy env update (compatibility)";
    strings["Relative duty and cutoff macros are coarse (compatibility)##sgsc"].plurals[0] = "=Relative duty and cutoff macros are coarse (compatibility)";
    strings["Cutoff macro race conditions (compatibility)##sgsc"].plurals[0] = "Cutoff macro race conditions (compatibility)";
    strings["Disable ExtCh FM macros (compatibility)##sgsc1"].plurals[0] = "=Disable ExtCh FM macros (compatibility)";
    strings["Ins change in ExtCh operator 2-4 affects FB (compatibility)##sgsc1"].plurals[0] = "=Ins change in ExtCh operator 2-4 affects FB (compatibility)";
    strings["SSG Volume##sgsc0"].plurals[0] = "=SSG Volume";
    strings["FM/ADPCM Volume##sgsc0"].plurals[0] = "=FM/ADPCM Volume";
    strings["Clock rate:##sgsc3"].plurals[0] = "=Clock rate:";
    strings["0.83MHz (Pre-divided Sunsoft 5B on PAL)##sgsc"].plurals[0] = "=0.83MHz (Pre-divided Sunsoft 5B on PAL)";
    strings["0.89MHz (Pre-divided Sunsoft 5B)##sgsc"].plurals[0] = "=0.89MHz (Pre-divided Sunsoft 5B)";
    strings["Chip type:##sgsc2"].plurals[0] = "=Chip type:";
    strings["note: AY-3-8914 is not supported by the VGM format!##sgsc"].plurals[0] = "=note: AY-3-8914 is not supported by the VGM format!";
    strings["Stereo##_AY_STEREO"].plurals[0] = "=Stereo##_AY_STEREO";
    strings["Separation##sgsc"].plurals[0] = "=Separation";
    strings["Half Clock divider##_AY_CLKSEL"].plurals[0] = "=Half Clock divider##_AY_CLKSEL";
    strings["Stereo separation:##sgsc"].plurals[0] = "=Stereo separation:";
    strings["Model:##sgsc"].plurals[0] = "=Model:";
    strings["Chip memory:##sgsc"].plurals[0] = "=Chip memory:";
    strings["2MB (ECS/AGA max)##sgsc"].plurals[0] = "=2MB (ECS/AGA max)";
    strings["512KB (OCS max)##sgsc"].plurals[0] = "=512KB (OCS max)";
    strings["Bypass frequency limits##sgsc"].plurals[0] = "=Bypass frequency limits";
    strings["Mixing mode:##sgsc"].plurals[0] = "=Mixing mode:";
    strings["Mono##sgsc"].plurals[0] = "=Mono";
    strings["Mono (no distortion)##sgsc"].plurals[0] = "=Mono (no distortion)";
    strings["Stereo##sgsc0"].plurals[0] = "=Stereo";
    strings["Clock rate:##sgsc4"].plurals[0] = "=Clock rate:";
    strings["Speaker type:##sgsc"].plurals[0] = "=Speaker type:";
    strings["Unfiltered##sgsc"].plurals[0] = "=Unfiltered";
    strings["Cone##sgsc"].plurals[0] = "=Cone";
    strings["Piezo##sgsc"].plurals[0] = "=Piezo";
    strings["Use system beeper (Linux only!)##sgsc"].plurals[0] = "=Use system beeper (Linux only!)";
    strings["Reset phase on frequency change##sgsc"].plurals[0] = "=Reset phase on frequency change";
    strings["Echo delay:##sgsc1"].plurals[0] = "=Echo delay:";
    strings["Echo feedback:##sgsc1"].plurals[0] = "=Echo feedback:";
    strings["Clock rate:##sgsc5"].plurals[0] = "=Clock rate:";
    strings["Stereo##sgsc1"].plurals[0] = "=Stereo";
    strings["Bankswitched (Seta 2)##sgsc"].plurals[0] = "=Bankswitched (Seta 2)";
    strings["Clock rate:##sgsc6"].plurals[0] = "=Clock rate:";
    strings["Initial channel limit:##sgsc0"].plurals[0] = "=Initial channel limit:";
    strings["Disable hissing##sgsc"].plurals[0] = "=Disable hissing";
    strings["Scale frequency to wave length##sgsc"].plurals[0] = "=Scale frequency to wave length";
    strings["Initial channel limit:##sgsc1"].plurals[0] = "=Initial channel limit:";
    strings["Volume scale:##sgsc0"].plurals[0] = "=Volume scale:";
    strings["Clock rate:##sgsc7"].plurals[0] = "=Clock rate:";
    strings["Output rate:##sgsc0"].plurals[0] = "=Output rate:";
    strings["FM: clock / 72, SSG: clock / 16##sgsc0"].plurals[0] = "=FM: clock / 72, SSG: clock / 16";
    strings["FM: clock / 36, SSG: clock / 8##sgsc"].plurals[0] = "=FM: clock / 36, SSG: clock / 8";
    strings["FM: clock / 24, SSG: clock / 4##sgsc"].plurals[0] = "=FM: clock / 24, SSG: clock / 4";
    strings["SSG Volume##sgsc1"].plurals[0] = "=SSG Volume";
    strings["FM Volume##sgsc"].plurals[0] = "=FM Volume";
    strings["Disable ExtCh FM macros (compatibility)##sgsc2"].plurals[0] = "=Disable ExtCh FM macros (compatibility)";
    strings["Ins change in ExtCh operator 2-4 affects FB (compatibility)##sgsc2"].plurals[0] = "=Ins change in ExtCh operator 2-4 affects FB (compatibility)";
    strings["Clock rate:##sgsc8"].plurals[0] = "=Clock rate:";
    strings["8MHz (Arcade)##sgsc"].plurals[0] = "=8MHz (Arcade)";
    strings["Output rate:##sgsc1"].plurals[0] = "=Output rate:";
    strings["FM: clock / 144, SSG: clock / 32##sgsc"].plurals[0] = "=FM: clock / 144, SSG: clock / 32";
    strings["FM: clock / 72, SSG: clock / 16##sgsc1"].plurals[0] = "=FM: clock / 72, SSG: clock / 16";
    strings["FM: clock / 48, SSG: clock / 8##sgsc"].plurals[0] = "=FM: clock / 48, SSG: clock / 8";
    strings["SSG Volume##sgsc2"].plurals[0] = "=SSG Volume";
    strings["FM/ADPCM Volume##sgsc1"].plurals[0] = "=FM/ADPCM Volume";
    strings["Disable ExtCh FM macros (compatibility)##sgsc3"].plurals[0] = "=Disable ExtCh FM macros (compatibility)";
    strings["Ins change in ExtCh operator 2-4 affects FB (compatibility)##sgsc3"].plurals[0] = "=Ins change in ExtCh operator 2-4 affects FB (compatibility)";
    strings["Clock rate:##sgsc9"].plurals[0] = "=Clock rate:";
    strings["Chip type:##sgsc3"].plurals[0] = "=Chip type:";
    strings["RF5C68 (10-bit output)##sgsc"].plurals[0] = "=RF5C68 (10-bit output)";
    strings["RF5C164 (16-bit output)##sgsc"].plurals[0] = "=RF5C164 (16-bit output)";
    strings["Clock rate:##sgsc10"].plurals[0] = "=Clock rate:";
    strings["Sample rate table:##sgsc"].plurals[0] = "=Sample rate table:";
    strings["divider \\ clock##sgsc"].plurals[0] = "=divider \\ clock";
    strings["full##sgsc"].plurals[0] = "=full";
    strings["half##sgsc"].plurals[0] = "=half";
    strings["Clock rate:##sgsc11"].plurals[0] = "=Clock rate:";
    strings["Output rate:##sgsc2"].plurals[0] = "=Output rate:";
    strings["clock / 132##sgsc"].plurals[0] = "=clock / 132";
    strings["clock / 165##sgsc"].plurals[0] = "=clock / 165";
    strings["Bankswitched (NMK112)##sgsc"].plurals[0] = "=Bankswitched (NMK112)";
    strings["Clock rate:##sgsc12"].plurals[0] = "=Clock rate:";
    strings["1.5MHz (Arcade)##sgsc"].plurals[0] = "=1.5MHz (Arcade)";
    strings["Consistent frequency across all duties##sgsc"].plurals[0] = "=Consistent frequency across all duties";
    strings["note: only works for an initial LFSR value of 0!##sgsc"].plurals[0] = "=note: only works for an initial LFSR value of 0!";
    strings["Clock rate:##sgsc13"].plurals[0] = "=Clock rate:";
    strings["Clock rate:##sgsc14"].plurals[0] = "=Clock rate:";
    strings["Chip type:##sgsc4"].plurals[0] = "=Chip type:";
    strings["Compatible panning (0800)##sgsc"].plurals[0] = "=Compatible panning (0800)";
    strings["Clock rate:##sgsc15"].plurals[0] = "=Clock rate:";
    strings["Output rate:##sgsc3"].plurals[0] = "=Output rate:";
    strings["Output bit depth:##sgsc"].plurals[0] = "=Output bit depth:";
    strings["Stereo##sgsc2"].plurals[0] = "=Stereo";
    strings["Interpolation:##sgsc"].plurals[0] = "=Interpolation:";
    strings["None##sgsc"].plurals[0] = "=None";
    strings["Linear##sgsc"].plurals[0] = "=Linear";
    strings["Cubic##sgsc"].plurals[0] = "=Cubic";
    strings["Sinc##sgsc"].plurals[0] = "=Sinc";
    strings["Volume scale:##sgsc1"].plurals[0] = "=Volume scale:";
    strings["Left##VolScaleL"].plurals[0] = "=Left##VolScaleL";
    strings["Right##VolScaleL"].plurals[0] = "=Right##VolScaleL";
    strings["Enable echo##sgsc1"].plurals[0] = "=Enable echo";
    strings["Initial echo state:##sgsc"].plurals[0] = "=Initial echo state:";
    strings["Delay##EchoDelay"].plurals[0] = "=Delay##EchoDelay";
    strings["Feedback##EchoFeedback"].plurals[0] = "=Feedback##EchoFeedback";
    strings["Echo volume:##sgsc1"].plurals[0] = "=Echo volume:";
    strings["Left##EchoVolL"].plurals[0] = "=Left##EchoVolL";
    strings["Right##EchoVolL"].plurals[0] = "=Right##EchoVolL";
    strings["Echo filter:##sgsc"].plurals[0] = "=Echo filter:";
    strings["Hex##SNESFHex"].plurals[0] = "=Hex##SNESFHex";
    strings["Dec##SNESFHex"].plurals[0] = "=Dec##SNESFHex";
    strings["sum: %d##sgsc"].plurals[0] = "=sum: %d";
    strings["Detune##sgsc"].plurals[0] = "=Detune";
    strings["Capacitor values (nF):##sgsc"].plurals[0] = "=Capacitor values (nF):";
    strings["Initial part volume (channel 1-4):##sgsc"].plurals[0] = "=Initial part volume (channel 1-4):";
    strings["Initial part volume (channel 5-8):##sgsc"].plurals[0] = "=Initial part volume (channel 5-8):";
    strings["Envelope mode (channel 1-4):##sgsc"].plurals[0] = "=Envelope mode (channel 1-4):";
    strings["Capacitor (attack/decay)##EM00"].plurals[0] = "=Capacitor (attack/decay)##EM00";
    strings["External (volume macro)##EM01"].plurals[0] = "=External (volume macro)##EM01";
    strings["Envelope mode (channel 5-8):##sgsc"].plurals[0] = "=Envelope mode (channel 5-8):";
    strings["Capacitor (attack/decay)##EM10"].plurals[0] = "=Capacitor (attack/decay)##EM10";
    strings["External (volume macro)##EM11"].plurals[0] = "=External (volume macro)##EM11";
    strings["Global vibrato:##sgsc"].plurals[0] = "=Global vibrato:";
    strings["Speed##sgsc"].plurals[0] = "=Speed";
    strings["Depth##sgsc"].plurals[0] = "=Depth";
    strings["Disable easy period to note mapping on upper octaves##sgsc1"].plurals[0] = "=Disable easy period to note mapping on upper octaves";
    strings["Stereo##sgsc3"].plurals[0] = "=Stereo";
    strings["Waveform storage mode:##sgsc0"].plurals[0] = "=Waveform storage mode:";
    strings["RAM##sgsc"].plurals[0] = "=RAM";
    strings["ROM (up to 8 waves)##sgsc"].plurals[0] = "=ROM (up to 8 waves)";
    strings["Compatible noise frequencies##sgsc"].plurals[0] = "=Compatible noise frequencies";
    strings["Legacy slides and pitch (compatibility)##sgsc"].plurals[0] = "=Legacy slides and pitch (compatibility)";
    strings["Clock rate:##sgsc16"].plurals[0] = "=Clock rate:";
    strings["Clock rate:##sgsc17"].plurals[0] = "=Clock rate:";
    strings["Global parameter priority:##sgsc1"].plurals[0] = "=Global parameter priority:";
    strings["Left to right##sgsc1"].plurals[0] = "=Left to right";
    strings["Last used channel##sgsc1"].plurals[0] = "=Last used channel";
    strings["Banking style:##sgsc"].plurals[0] = "=Banking style:";
    strings["Raw (16MB; no VGM export!)##sgsc"].plurals[0] = "=Raw (16MB; no VGM export!)";
    strings["Waveform storage mode:##sgsc1"].plurals[0] = "=Waveform storage mode:";
    strings["Dynamic (unconfirmed)##sgsc"].plurals[0] = "=Dynamic (unconfirmed)";
    strings["Static (up to 5 waves)##sgsc"].plurals[0] = "=Static (up to 5 waves)";
    strings["DS (4MB RAM)##sgsc"].plurals[0] = "=DS (4MB RAM)";
    strings["DSi (16MB RAM)##sgsc"].plurals[0] = "=DSi (16MB RAM)";
    strings["nothing to configure##sgsc"].plurals[0] = "=nothing to configure";
    strings["Downmix chip output to mono##sgsc"].plurals[0] = "=Downmix chip output to mono";
    strings["Reserved blocks for wavetables:##sgsc"].plurals[0] = "=Reserved blocks for wavetables:";
    strings["Reserve this many blocks 256 bytes each in sample memory.\nEach block holds one wavetable (is used for one wavetable channel),\nso reserve as many as you need.##sgsc"].plurals[0] = "=Reserve this many blocks 256 bytes each in sample memory.\nEach block holds one wavetable (is used for one wavetable channel),\nso reserve as many as you need.";
    strings["Custom clock rate##sgsc"].plurals[0] = "=Custom clock rate";
    strings["Hz##sgscHz"].plurals[0] = "=Hz##sgscHz";
    strings["1MB##sgsc"].plurals[0] = "=1MB";
    strings["256KB##sgsc"].plurals[0] = "=256KB";
    strings["Namco System 2 (2MB)##sgsc"].plurals[0] = "=Namco System 2 (2MB)";
    strings["Namco System 21 (4MB)##sgsc"].plurals[0] = "=Namco System 21 (4MB)";


    //   sgsm  src/gui/sysManager.cpp

    strings["Chip Manager###Chip Manager"].plurals[0] = "=Chip Manager###Chip Manager";
    strings["Preserve channel order##sgsm"].plurals[0] = "=Preserve channel order";
    strings["Clone channel data##sgsm"].plurals[0] = "=Clone channel data";
    strings["Clone at end##sgsm"].plurals[0] = "=Clone at end";
    strings["Name##sgsm"].plurals[0] = "=Name";
    strings["Actions##sgsm"].plurals[0] = "=Actions";
    strings["(drag to swap chips)##sgsm"].plurals[0] = "=(drag to swap chips)";
    strings["Clone##SysDup"].plurals[0] = "=Clone##SysDup";
    strings["cannot duplicate chip! (##sgsm"].plurals[0] = "=cannot duplicate chip! (";
    strings["max number of systems is %d##sgsm"].plurals[0] = "=max number of systems is %d";
    strings["max number of total channels is %d##sgsm"].plurals[0] = "=max number of total channels is %d";
    strings["Change##SysChange"].plurals[0] = "=Change##SysChange";
    strings["Are you sure you want to remove this chip?##sgsm"].plurals[0] = "=Are you sure you want to remove this chip?";
    strings["Remove##sgsm"].plurals[0] = "=Remove";
    strings["cannot add chip! (##sgsm"].plurals[0] = "=cannot add chip! (";

    //   sgsa  src/gui/sysPartNumber.cpp

    strings["ZXS Beeper##sgsa"].plurals[0] = "=ZXS Beeper";

    //   sgsp  src/gui/sysPicker.cpp

    strings["Search...##sgsp"].plurals[0] = "=Search...";

    // # sgvm  src/gui/volMeter.cpp

    strings["Volume Meter###Volume Meter"].plurals[0] = "=Volume Meter###Volume Meter";

    //   sgwe  src/gui/waveEdit.cpp

    strings["Sine##sgwe0"].plurals[0] = "=Sine";
    strings["Triangle##sgwe0"].plurals[0] = "=Triangle";
    strings["Saw##sgwe0"].plurals[0] = "=Saw";
    strings["Pulse##sgwe"].plurals[0] = "=Pulse";

    strings["None##sgwe"].plurals[0] = "=None";
    strings["Linear##sgwe"].plurals[0] = "=Linear";
    strings["Cosine##sgwe"].plurals[0] = "=Cosine";
    strings["Cubic##sgwe"].plurals[0] = "=Cubic";

    strings["Sine##sgwe1"].plurals[0] = "=Sine";
    strings["Rect. Sine##sgwe"].plurals[0] = "=Rect. Sine";
    strings["Abs. Sine##sgwe"].plurals[0] = "=Abs. Sine";
    strings["Quart. Sine##sgwe"].plurals[0] = "=Quart. Sine";
    strings["Squish. Sine##sgwe"].plurals[0] = "=Squish. Sine";
    strings["Abs. Squish. Sine##sgwe"].plurals[0] = "=Abs. Squish. Sine";
    strings["Square##sgwe"].plurals[0] = "=Square";
    strings["rectSquare##sgwe"].plurals[0] = "=rectSquare";
    strings["Saw##sgwe1"].plurals[0] = "=Saw";
    strings["Rect. Saw##sgwe"].plurals[0] = "=Rect. Saw";
    strings["Abs. Saw##sgwe"].plurals[0] = "=Abs. Saw";
    strings["Cubed Saw##sgwe"].plurals[0] = "=Cubed Saw";
    strings["Rect. Cubed Saw##sgwe"].plurals[0] = "=Rect. Cubed Saw";
    strings["Abs. Cubed Saw##sgwe"].plurals[0] = "=Abs. Cubed Saw";
    strings["Cubed Sine##sgwe"].plurals[0] = "=Cubed Sine";
    strings["Rect. Cubed Sine##sgwe"].plurals[0] = "=Rect. Cubed Sine";
    strings["Abs. Cubed Sine##sgwe"].plurals[0] = "=Abs. Cubed Sine";
    strings["Quart. Cubed Sine##sgwe"].plurals[0] = "=Quart. Cubed Sine";
    strings["Squish. Cubed Sine##sgwe"].plurals[0] = "=Squish. Cubed Sine";
    strings["Squish. Abs. Cub. Sine##sgwe"].plurals[0] = "=Squish. Abs. Cub. Sine";
    strings["Triangle##sgwe1"].plurals[0] = "=Triangle";
    strings["Rect. Triangle##sgwe"].plurals[0] = "=Rect. Triangle";
    strings["Abs. Triangle##sgwe"].plurals[0] = "=Abs. Triangle";
    strings["Quart. Triangle##sgwe"].plurals[0] = "=Quart. Triangle";
    strings["Squish. Triangle##sgwe"].plurals[0] = "=Squish. Triangle";
    strings["Abs. Squish. Triangle##sgwe"].plurals[0] = "=Abs. Squish. Triangle";
    strings["Cubed Triangle##sgwe"].plurals[0] = "=Cubed Triangle";
    strings["Rect. Cubed Triangle##sgwe"].plurals[0] = "=Rect. Cubed Triangle";
    strings["Abs. Cubed Triangle##sgwe"].plurals[0] = "=Abs. Cubed Triangle";
    strings["Quart. Cubed Triangle##sgwe"].plurals[0] = "=Quart. Cubed Triangle";
    strings["Squish. Cubed Triangle##sgwe"].plurals[0] = "=Squish. Cubed Triangle";
    strings["Squish. Abs. Cub. Triangle##sgwe"].plurals[0] = "=Squish. Abs. Cub. Triangle";

    strings["Wavetable Editor###Wavetable Editor"].plurals[0] = "=Wavetable Editor###Wavetable Editor";
    strings["no wavetable selected##sgwe0"].plurals[0] = "=no wavetable selected";
    strings["no wavetable selected##sgwe1"].plurals[0] = "=no wavetable selected";
    strings["select one...##sgwe"].plurals[0] = "=select one...";
    strings["or##sgwe0"].plurals[0] = "=or";
    strings["Open##sgwe0"].plurals[0] = "=Open";
    strings["or##sgwe1"].plurals[0] = "=or";
    strings["Create New##sgwe"].plurals[0] = "=Create New";
    strings["Open##sgwe1"].plurals[0] = "=Open";
    strings["Save##sgwe"].plurals[0] = "=Save";
    strings["export .dmw...##sgwe"].plurals[0] = "=export .dmw...";
    strings["export raw...##sgwe"].plurals[0] = "=export raw...";
    strings["Steps##sgwe"].plurals[0] = "=Steps";
    strings["Lines##sgwe"].plurals[0] = "=Lines";
    strings["Width##sgwe"].plurals[0] = "=Width";
    strings["use a width of:\n- any on Amiga/N163\n- 32 on Game Boy, PC Engine, SCC, Konami Bubble System, Namco WSG, Virtual Boy and WonderSwan\n- 64 on FDS\n- 128 on X1-010\n- 256 for ES5503\nany other widths will be scaled during playback.##sgwe"].plurals[0] = "=use a width of:\n- any on Amiga/N163\n- 32 on Game Boy, PC Engine, SCC, Konami Bubble System, Namco WSG, Virtual Boy and WonderSwan\n- 64 on FDS\n- 128 on X1-010\n- 256 for ES5503\nany other widths will be scaled during playback.";
    strings["Height##sgwe"].plurals[0] = "=Height";
    strings["use a height of:\n- 16 for Game Boy, WonderSwan, Namco WSG, Konami Bubble System, X1-010 Envelope shape and N163\n- 32 for PC Engine\n- 64 for FDS and Virtual Boy\n- 256 for X1-010, SCC and ES5503\nany other heights will be scaled during playback.##sgwe"].plurals[0] = "=use a height of:\n- 16 for Game Boy, WonderSwan, Namco WSG, Konami Bubble System, X1-010 Envelope shape and N163\n- 32 for PC Engine\n- 64 for FDS and Virtual Boy\n- 256 for X1-010, SCC and ES5503\nany other heights will be scaled during playback.";
    strings["Shapes##sgwe"].plurals[0] = "=Shapes";
    strings["Duty##sgwe"].plurals[0] = "=Duty";
    strings["Exponent##sgwe"].plurals[0] = "=Exponent";
    strings["XOR Point##sgwe"].plurals[0] = "=XOR Point";
    strings["Amplitude/Phase##sgwe"].plurals[0] = "=Amplitude/Phase";
    strings["Op##sgwe0"].plurals[0] = "=Op";
    strings["Level##sgwe"].plurals[0] = "=Level";
    strings["Mult##sgwe"].plurals[0] = "=Mult";
    strings["FB##sgwe"].plurals[0] = "=FB";
    strings["Op##sgwe1"].plurals[0] = "=Op";
    strings["Waveform##sgwe"].plurals[0] = "=Waveform";
    strings["Connection Diagram##sgwe0"].plurals[0] = "=Connection Diagram";
    strings["Connection Diagram##sgwe1"].plurals[0] = "=Connection Diagram";
    strings["Out##sgwe"].plurals[0] = "=Out";
    strings["WaveTools##sgwe"].plurals[0] = "=WaveTools";
    strings["Scale X##sgwe"].plurals[0] = "=Scale X";
    strings["wavetable longer than 256 samples!##sgwe"].plurals[0] = "=wavetable longer than 256 samples!";
    strings["Scale Y##sgwe"].plurals[0] = "=Scale Y";
    strings["Offset X##sgwe"].plurals[0] = "=Offset X";
    strings["Offset Y##sgwe"].plurals[0] = "=Offset Y";
    strings["Smooth##sgwe"].plurals[0] = "=Smooth";
    strings["Amplify##sgwe"].plurals[0] = "=Amplify";
    strings["Normalize##sgwe"].plurals[0] = "=Normalize";
    strings["Invert##sgwe"].plurals[0] = "=Invert";
    strings["Reverse##sgwe"].plurals[0] = "=Reverse";
    strings["Half##sgwe"].plurals[0] = "=Half";
    strings["Double##sgwe"].plurals[0] = "=Double";
    strings["Convert Signed/Unsigned##sgwe"].plurals[0] = "=Convert Signed/Unsigned";
    strings["Randomize##sgwe"].plurals[0] = "=Randomize";
    strings["Dec##sgwe"].plurals[0] = "=Dec";
    strings["Hex##sgwe"].plurals[0] = "=Hex";
    strings["Signed/Unsigned##sgwe"].plurals[0] = "=Signed/Unsigned";

    //   sgxy  src/gui/xyOsc.cpp

    strings["Oscilloscope (X-Y)###Oscilloscope (X-Y)"].plurals[0] = "=Oscilloscope (X-Y)###Oscilloscope (X-Y)";
    strings["X Channel##sgxy"].plurals[0] = "=X Channel";
    strings["Invert##X"].plurals[0] = "=Invert";
    strings["Y Channel##sgxy"].plurals[0] = "=Y Channel";
    strings["Invert##Y"].plurals[0] = "=Invert";
    strings["Zoom##sgxy"].plurals[0] = "=Zoom";
    strings["Samples##sgxy"].plurals[0] = "=Samples";
    strings["Decay Time (ms)##sgxy"].plurals[0] = "=Decay Time (ms)";
    strings["Intensity##sgxy"].plurals[0] = "=Intensity";
    strings["Line Thickness##sgxy"].plurals[0] = "=Line Thickness";
    strings["OK##sgxy"].plurals[0] = "=OK";
    strings["(-Infinity)dB,(-Infinity)dB##sgxy"].plurals[0] = "=(-Infinity)dB,(-Infinity)dB";
    strings["(-Infinity)dB,%.1fdB##sgxy"].plurals[0] = "=(-Infinity)dB,%.1fdB";
    strings["%.1fdB,(-Infinity)dB##sgxy"].plurals[0] = "=%.1fdB,(-Infinity)dB";
    
    //MACRO EDITOR

    //macro hover notes

    strings["exponential##sgmu"].plurals[0] = "=exponential";
    strings["linear##sgmu"].plurals[0] = "=linear";
    strings["direct##sgmu"].plurals[0] = "=direct";

    strings["Release"].plurals[0] = "=Release";
    strings["Loop"].plurals[0] = "=Loop";

    strings["HP/K2, HP/K2##sgmu"].plurals[0] = "=HP/K2, HP/K2";
    strings["HP/K2, LP/K1##sgmu"].plurals[0] = "=HP/K2, LP/K1";
    strings["LP/K2, LP/K2##sgmu"].plurals[0] = "=LP/K2, LP/K2";
    strings["LP/K2, LP/K1##sgmu"].plurals[0] = "=LP/K2, LP/K1";

    strings["Saw##sgmu"].plurals[0] = "=Saw";
    strings["Square##sgmu"].plurals[0] = "=Square";
    strings["Triangle##sgmu"].plurals[0] = "=Triangle";
    strings["Random##sgmu"].plurals[0] = "=Random";

    //   sgse  src/gui/settings.cpp

    strings["<Use system font>##sgse0"].plurals[0] = "=<Use system font>";
    strings["<Custom...>##sgse0"].plurals[0] = "=<Custom...>";
    strings["<Use system font>##sgse1"].plurals[0] = "=<Use system font>";
    strings["<Custom...>##sgse1"].plurals[0] = "=<Custom...>";
    strings["<Use system font>##sgse2"].plurals[0] = "=<Use system font>";
    strings["<Custom...>##sgse2"].plurals[0] = "=<Custom...>";
    strings["Mono##sgse0"].plurals[0] = "=Mono";
    strings["Stereo##sgse"].plurals[0] = "=Stereo";
    strings["What?##sgse0"].plurals[0] = "=What?";
    strings["Quadraphonic##sgse"].plurals[0] = "=Quadraphonic";
    strings["What?##sgse1"].plurals[0] = "=What?";
    strings["5.1 Surround##sgse"].plurals[0] = "=5.1 Surround";
    strings["What?##sgse2"].plurals[0] = "=What?";
    strings["7.1 Surround##sgse"].plurals[0] = "=7.1 Surround";
    strings["High##sgse"].plurals[0] = "=High";
    strings["Low##sgse"].plurals[0] = "=Low";
    strings["ASAP (C++ port)##sgse"].plurals[0] = "=ASAP (C++ port)";
    strings["ESFMu (fast)##sgse"].plurals[0] = "=ESFMu (fast)";
    strings["Lower##sgse"].plurals[0] = "=Lower";
    strings["Low##sgse1"].plurals[0] = "=Low";
    strings["Medium##sgse"].plurals[0] = "=Medium";
    strings["High##sgse"].plurals[0] = "=High";
    strings["Ultra##sgse"].plurals[0] = "=Ultra";
    strings["Ultimate##sgse"].plurals[0] = "=Ultimate";
    strings["KIOCSOUND on /dev/tty1##sgse"].plurals[0] = "=KIOCSOUND on /dev/tty1";
    strings["KIOCSOUND on standard output##sgse"].plurals[0] = "=KIOCSOUND on standard output";
    strings["Disabled/custom##sgse0"].plurals[0] = "=Disabled/custom";
    strings["Two octaves (0 is C-4, F is D#5)##sgse"].plurals[0] = "=Two octaves (0 is C-4, F is D#5)";
    strings["Raw (note number is value)##sgse"].plurals[0] = "=Raw (note number is value)";
    strings["Two octaves alternate (lower keys are 0-9, upper keys are A-F)##sgse"].plurals[0] = "=Two octaves alternate (lower keys are 0-9, upper keys are A-F)";
    strings["Use dual control change (one for each nibble)##sgse0"].plurals[0] = "=Use dual control change (one for each nibble)";
    strings["Use 14-bit control change##sgse0"].plurals[0] = "=Use 14-bit control change";
    strings["Use single control change (imprecise)##sgse0"].plurals[0] = "=Use single control change (imprecise)";
    strings["Disabled/custom##sgse1"].plurals[0] = "=Disabled/custom";
    strings["Use dual control change (one for each nibble)##sgse1"].plurals[0] = "=Use dual control change (one for each nibble)";
    strings["Use 14-bit control change##sgse1"].plurals[0] = "=Use 14-bit control change";
    strings["Use single control change (imprecise)##sgse1"].plurals[0] = "=Use single control change (imprecise)";
    strings["--select--##sgse"].plurals[0] = "=--select--";
    strings["Note Off##sgse"].plurals[0] = "=Note Off";
    strings["Note On##sgse"].plurals[0] = "=Note On";
    strings["Aftertouch##sgse"].plurals[0] = "=Aftertouch";
    strings["Control##sgse"].plurals[0] = "=Control";
    strings["Program##sgse0"].plurals[0] = "=Program";
    strings["ChanPressure##sgse"].plurals[0] = "=ChanPressure";
    strings["Pitch Bend##sgse"].plurals[0] = "=Pitch Bend";
    strings["SysEx##sgse"].plurals[0] = "=SysEx";
    strings["Instrument##sgse0"].plurals[0] = "=Instrument";
    strings["Volume##sgse0"].plurals[0] = "=Volume";
    strings["Effect 1 type##sgse"].plurals[0] = "=Effect 1 type";
    strings["Effect 1 value##sgse"].plurals[0] = "=Effect 1 value";
    strings["Effect 2 type##sgse"].plurals[0] = "=Effect 2 type";
    strings["Effect 2 value##sgse"].plurals[0] = "=Effect 2 value";
    strings["Effect 3 type##sgse"].plurals[0] = "=Effect 3 type";
    strings["Effect 3 value##sgse"].plurals[0] = "=Effect 3 value";
    strings["Effect 4 type##sgse"].plurals[0] = "=Effect 4 type";
    strings["Effect 4 value##sgse"].plurals[0] = "=Effect 4 value";
    strings["Effect 5 type##sgse"].plurals[0] = "=Effect 5 type";
    strings["Effect 5 value##sgse"].plurals[0] = "=Effect 5 value";
    strings["Effect 6 type##sgse"].plurals[0] = "=Effect 6 type";
    strings["Effect 6 value##sgse"].plurals[0] = "=Effect 6 value";
    strings["Effect 7 type##sgse"].plurals[0] = "=Effect 7 type";
    strings["Effect 7 value##sgse"].plurals[0] = "=Effect 7 value";
    strings["Effect 8 type##sgse"].plurals[0] = "=Effect 8 type";
    strings["Effect 8 value##sgse"].plurals[0] = "=Effect 8 value";

    strings["Press key...##sgse"].plurals[0] = "=Press key...";
    strings["Settings###Settings"].plurals[0] = "=Settings###Settings";
    strings["Do you want to save your settings?##sgse"].plurals[0] = "=Do you want to save your settings?";

    strings["General##sgse"].plurals[0] = "=General";
    strings["Program##sgse1"].plurals[0] = "=Program";
    strings["Render backend##sgse"].plurals[0] = "=Render backend";
    strings["Software##sgse"].plurals[0] = "=Software";
    strings["Software"].plurals[0] = "=Software"; //sigh
    strings["you may need to restart Furnace for this setting to take effect.##sgse0"].plurals[0] = "=you may need to restart Furnace for this setting to take effect.";
    strings["Render driver##sgse"].plurals[0] = "=Render driver";
    strings["Automatic##sgse0"].plurals[0] = "=Automatic";
    strings["Automatic##sgse1"].plurals[0] = "=Automatic";
    strings["you may need to restart Furnace for this setting to take effect.##sgse1"].plurals[0] = "=you may need to restart Furnace for this setting to take effect.";
    strings["current backend: %s\n%s\n%s\n%s##sgse"].plurals[0] = "=current backend: %s\n%s\n%s\n%s";
    strings["VSync##sgse"].plurals[0] = "=VSync";
    strings["Frame rate limit##sgse"].plurals[0] = "=Frame rate limit";
    strings["only applies when VSync is disabled.##sgse"].plurals[0] = "=only applies when VSync is disabled.";
    strings["Display render time##sgse"].plurals[0] = "=Display render time";
    strings["Late render clear##sgse"].plurals[0] = "=Late render clear";
    strings["calls rend->clear() after rend->present(). might reduce UI latency by one frame in some drivers.##sgse"].plurals[0] = "=calls rend->clear() after rend->present(). might reduce UI latency by one frame in some drivers.";
    strings["Power-saving mode##sgse"].plurals[0] = "=Power-saving mode";
    strings["saves power by lowering the frame rate to 2fps when idle.\nmay cause issues under Mesa drivers!##sgse"].plurals[0] = "=saves power by lowering the frame rate to 2fps when idle.\nmay cause issues under Mesa drivers!";
    strings["Disable threaded input (restart after changing!)##sgse"].plurals[0] = "=Disable threaded input (restart after changing!)";
    strings["threaded input processes key presses for note preview on a separate thread (on supported platforms), which reduces latency.\nhowever, crashes have been reported when threaded input is on. enable this option if that is the case.##sgse"].plurals[0] = "=threaded input processes key presses for note preview on a separate thread (on supported platforms), which reduces latency.\nhowever, crashes have been reported when threaded input is on. enable this option if that is the case.";
    strings["Enable event delay##sgse"].plurals[0] = "=Enable event delay";
    strings["may cause issues with high-polling-rate mice when previewing notes.##sgse"].plurals[0] = "=may cause issues with high-polling-rate mice when previewing notes.";
    strings["Per-channel oscilloscope threads##sgse"].plurals[0] = "=Per-channel oscilloscope threads";
    strings["you're being silly, aren't you? that's enough.##sgse"].plurals[0] = "=you're being silly, aren't you? that's enough.";
    strings["what are you doing? stop!##sgse"].plurals[0] = "=what are you doing? stop!";
    strings["it is a bad idea to set this number higher than your CPU core count (%d)!##sgse"].plurals[0] = "=it is a bad idea to set this number higher than your CPU core count (%d)!";
    strings["Oscilloscope rendering engine:##sgse"].plurals[0] = "=Oscilloscope rendering engine:";
    strings["ImGui line plot##sgse"].plurals[0] = "=ImGui line plot";
    strings["render using Dear ImGui's built-in line drawing functions.##sgse"].plurals[0] = "=render using Dear ImGui's built-in line drawing functions.";
    strings["GLSL (if available)##sgse"].plurals[0] = "=GLSL (if available)";
    strings["render using shaders that run on the graphics card.\nonly available in OpenGL ES 2.0 render backend.##sgse"].plurals[0] = "=render using shaders that run on the graphics card.\nonly available in OpenGL ES 2.0 render backend.";
    strings["render using shaders that run on the graphics card.\nonly available in OpenGL 3.0 render backend.##sgse"].plurals[0] = "=render using shaders that run on the graphics card.\nonly available in OpenGL 3.0 render backend.";
    strings["File##sgse"].plurals[0] = "=File";
    strings["Use system file picker##sgse"].plurals[0] = "=Use system file picker";
    strings["Number of recent files##sgse"].plurals[0] = "=Number of recent files";
    strings["Compress when saving##sgse"].plurals[0] = "=Compress when saving";
    strings["use zlib to compress saved songs.##sgse"].plurals[0] = "=use zlib to compress saved songs.";
    strings["Save unused patterns##sgse"].plurals[0] = "=Save unused patterns";
    strings["Use new pattern format when saving##sgse"].plurals[0] = "=Use new pattern format when saving";
    strings["use a packed format which saves space when saving songs.\ndisable if you need compatibility with older Furnace and/or tools\nwhich do not support this format.##sgse"].plurals[0] = "=use a packed format which saves space when saving songs.\ndisable if you need compatibility with older Furnace and/or tools\nwhich do not support this format.";
    strings["Don't apply compatibility flags when loading .dmf##sgse"].plurals[0] = "=Don't apply compatibility flags when loading .dmf";
    strings["do not report any issues arising from the use of this option!##sgse"].plurals[0] = "=do not report any issues arising from the use of this option!";
    strings["Play after opening song:##sgse"].plurals[0] = "=Play after opening song:";
    strings["No##pol0"].plurals[0] = "=No##pol0";
    strings["Only if already playing##pol1"].plurals[0] = "=Only if already playing##pol1";
    strings["Yes##pol0"].plurals[0] = "=Yes##pol0";
    strings["Audio export loop/fade out time:##sgse"].plurals[0] = "=Audio export loop/fade out time:";
    strings["Set to these values on start-up:##fot0"].plurals[0] = "=Set to these values on start-up:##fot0";
    strings["Loops##sgse"].plurals[0] = "=Loops";
    strings["Fade out (seconds)##sgse"].plurals[0] = "=Fade out (seconds)";
    strings["Remember last values##fot1"].plurals[0] = "=Remember last values##fot1";
    strings["Store instrument name in .fui##sgse"].plurals[0] = "=Store instrument name in .fui";
    strings["when enabled, saving an instrument will store its name.\nthis may increase file size.##sgse"].plurals[0] = "=when enabled, saving an instrument will store its name.\nthis may increase file size.";
    strings["Load instrument name from .fui##sgse"].plurals[0] = "=Load instrument name from .fui";
    strings["when enabled, loading an instrument will use the stored name (if present).\notherwise, it will use the file name.##sgse"].plurals[0] = "=when enabled, loading an instrument will use the stored name (if present).\notherwise, it will use the file name.";
    strings["New Song##sgse"].plurals[0] = "=New Song";
    strings["Initial system:##sgse"].plurals[0] = "=Initial system:";
    strings["Current system##sgse"].plurals[0] = "=Current system";
    strings["Randomize##sgse"].plurals[0] = "=Randomize";
    strings["Reset to defaults##sgse"].plurals[0] = "=Reset to defaults";
    strings["Name##sgse"].plurals[0] = "=Name";
    strings["Invert##sgse0"].plurals[0] = "=Invert";
    strings["Invert##sgse1"].plurals[0] = "=Invert";
    strings["Volume##sgse1"].plurals[0] = "=Volume";
    strings["Panning##sgse"].plurals[0] = "=Panning";
    strings["Front/Rear##sgse"].plurals[0] = "=Front/Rear";
    strings["Configure##sgse"].plurals[0] = "=Configure";
    strings["When creating new song:##sgse"].plurals[0] = "=When creating new song:";
    strings["Display system preset selector##NSB0"].plurals[0] = "=Display system preset selector##NSB0";
    strings["Start with initial system##NSB1"].plurals[0] = "=Start with initial system##NSB1";
    strings["Default author name##sgse"].plurals[0] = "=Default author name";
    strings["Start-up##sgse"].plurals[0] = "=Start-up";
    strings["Disable fade-in during start-up##sgse"].plurals[0] = "=Disable fade-in during start-up";
    strings["About screen party time##sgse"].plurals[0] = "=About screen party time";
    strings["Warning: may cause epileptic seizures.##sgse"].plurals[0] = "=Warning: may cause epileptic seizures.";
    strings["Behavior##sgse"].plurals[0] = "=Behavior";
    strings["New instruments are blank##sgse"].plurals[0] = "=New instruments are blank";
    strings["Language##sgse"].plurals[0] = "=Language";
    strings["GUI language##sgse"].plurals[0] = "=GUI language";
    strings["Translate channel names in pattern header##sgse"].plurals[0] = "=Translate channel names in pattern header";
    strings["Translate channel names in channel oscilloscope label##sgse"].plurals[0] = "=Translate channel names in channel oscilloscope label";
    strings["Translate short channel names (in orders and other places)##sgse"].plurals[0] = "=Translate short channel names (in orders and other places)";
    strings["test##sgse"].plurals[0] = "=test";
    strings["iulserghiueshgui##sgse"].plurals[0] = "=iulserghiueshgui";
    strings["Audio##sgse"].plurals[0] = "=Audio";
    strings["Output##sgse"].plurals[0] = "=Output";
    strings["Backend##sgse"].plurals[0] = "=Backend";
    strings["Driver##sgse"].plurals[0] = "=Driver";
    strings["Automatic##sgse2"].plurals[0] = "=Automatic";
    strings["you may need to restart Furnace for this setting to take effect.##sgse2"].plurals[0] = "=you may need to restart Furnace for this setting to take effect.";
    strings["Device##sgse"].plurals[0] = "=Device";
    strings["<click on OK or Apply first>##sgse"].plurals[0] = "=<click on OK or Apply first>";
    strings["ALERT - TRESPASSER DETECTED##sgse"].plurals[0] = "=ALERT - TRESPASSER DETECTED";
    strings["you have been arrested for trying to engage with a disabled combo box.##sgse"].plurals[0] = "=you have been arrested for trying to engage with a disabled combo box.";
    strings["<System default>##sgse0"].plurals[0] = "=<System default>";
    strings["<System default>##sgse1"].plurals[0] = "=<System default>";
    strings["Sample rate##sgse"].plurals[0] = "=Sample rate";
    strings["Outputs##sgse"].plurals[0] = "=Outputs";
    strings["Channels##sgse"].plurals[0] = "=Channels";
    strings["What?##sgse3"].plurals[0] = "=What?";
    strings["Buffer size##sgse"].plurals[0] = "=Buffer size";
    strings["%d (latency: ~%.1fms)##sgse"].plurals[0] = "=%d (latency: ~%.1fms)";
    strings["Multi-threaded (EXPERIMENTAL)##sgse"].plurals[0] = "=Multi-threaded (EXPERIMENTAL)";
    strings["runs chip emulation on separate threads.\nmay increase performance when using heavy emulation cores.\n\nwarnings:\n- experimental!\n- only useful on multi-chip songs.##sgse"].plurals[0] = "=runs chip emulation on separate threads.\nmay increase performance when using heavy emulation cores.\n\nwarnings:\n- experimental!\n- only useful on multi-chip songs.";
    strings["Number of threads##sgse"].plurals[0] = "=Number of threads";
    strings["that's the limit!##sgse"].plurals[0] = "=that's the limit!";
    strings["it is a VERY bad idea to set this number higher than your CPU core count (%d)!##sgse"].plurals[0] = "=it is a VERY bad idea to set this number higher than your CPU core count (%d)!";
    strings["Low-latency mode##sgse"].plurals[0] = "=Low-latency mode";
    strings["reduces latency by running the engine faster than the tick rate.\nuseful for live playback/jam mode.\n\nwarning: only enable if your buffer size is small (10ms or less).##sgse"].plurals[0] = "=reduces latency by running the engine faster than the tick rate.\nuseful for live playback/jam mode.\n\nwarning: only enable if your buffer size is small (10ms or less).";
    strings["Force mono audio##sgse"].plurals[0] = "=Force mono audio";
    strings["Exclusive mode##sgse"].plurals[0] = "=Exclusive mode";
    strings["want: %d samples @ %.0fHz (%d %s)##sgse"].plurals[0] = "=want: %d samples @ %.0fHz (%d %s)";
    strings["channel##sgse"].plurals[0] = "=channel";
    strings["channel##sgse"].plurals[1] = "=channels";
    strings["got: %d samples @ %.0fHz (%d %s)##sgse"].plurals[0] = "=got: %d samples @ %.0fHz (%d %s)";
    strings["Mixing##sgse"].plurals[0] = "=Mixing";
    strings["Quality##sgse"].plurals[0] = "=Quality";
    strings["Software clipping##sgse"].plurals[0] = "=Software clipping";
    strings["DC offset correction##sgse"].plurals[0] = "=DC offset correction";
    strings["Metronome##sgse"].plurals[0] = "=Metronome";
    strings["Volume##sgse2"].plurals[0] = "=Volume";
    strings["Sample preview##sgse"].plurals[0] = "=Sample preview";
    strings["Volume##sgse3"].plurals[0] = "=Volume";
    strings["MIDI##sgse"].plurals[0] = "=MIDI";
    strings["MIDI input##sgse0"].plurals[0] = "=MIDI input";
    strings["MIDI input##sgse1"].plurals[0] = "=MIDI input";
    strings["<disabled>##sgse0"].plurals[0] = "=<disabled>";
    strings["<disabled>##sgse1"].plurals[0] = "=<disabled>";
    strings["Re-scan MIDI devices##sgse"].plurals[0] = "=Re-scan MIDI devices";
    strings["Note input##sgse0"].plurals[0] = "=Note input";
    strings["Velocity input##sgse"].plurals[0] = "=Velocity input";
    strings["Map MIDI channels to direct channels##sgse"].plurals[0] = "=Map MIDI channels to direct channels";
    strings["Program change pass-through##sgse"].plurals[0] = "=Program change pass-through";
    strings["Map Yamaha FM voice data to instruments##sgse"].plurals[0] = "=Map Yamaha FM voice data to instruments";
    strings["Program change is instrument selection##sgse"].plurals[0] = "=Program change is instrument selection";
    strings["Listen to MIDI clock##sgse"].plurals[0] = "=Listen to MIDI clock";
    strings["Listen to MIDI time code##sgse"].plurals[0] = "=Listen to MIDI time code";
    strings["Value input style##sgse0"].plurals[0] = "=Value input style";
    strings["Value input style##sgse1"].plurals[0] = "=Value input style";
    strings["Control##valueCCS"].plurals[0] = "=Control##valueCCS";
    strings["CC of upper nibble##valueCC1"].plurals[0] = "=CC of upper nibble##valueCC1";
    strings["MSB CC##valueCC1"].plurals[0] = "=MSB CC##valueCC1";
    strings["CC of lower nibble##valueCC2"].plurals[0] = "=CC of lower nibble##valueCC2";
    strings["LSB CC##valueCC2"].plurals[0] = "=LSB CC##valueCC2";
    strings["Per-column control change##sgse"].plurals[0] = "=Per-column control change";
    strings["Control##valueCCS"].plurals[0] = "=Control##valueCCS";
    strings["CC of upper nibble##valueCC1"].plurals[0] = "=CC of upper nibble##valueCC1";
    strings["MSB CC##valueCC1"].plurals[0] = "=MSB CC##valueCC1";
    strings["CC of lower nibble##valueCC2"].plurals[0] = "=CC of lower nibble##valueCC2";
    strings["LSB CC##valueCC2"].plurals[0] = "=LSB CC##valueCC2";
    strings["Volume curve##sgse0"].plurals[0] = "=Volume curve";
    strings["Volume curve##sgse1"].plurals[0] = "=Volume curve";
    strings["Actions:##sgse"].plurals[0] = "=Actions:";
    strings["(learning! press a button or move a slider/knob/something on your device.)##sgse"].plurals[0] = "=(learning! press a button or move a slider/knob/something on your device.)";
    strings["Type##sgse0"].plurals[0] = "=Type";
    strings["Channel##sgse0"].plurals[0] = "=Channel";
    strings["Note/Control##sgse"].plurals[0] = "=Note/Control";
    strings["Velocity/Value##sgse"].plurals[0] = "=Velocity/Value";
    strings["Action##sgse"].plurals[0] = "=Action";
    strings["Any##sgse0"].plurals[0] = "=Any";
    strings["Any##sgse1"].plurals[0] = "=Any";
    strings["Any##sgse2"].plurals[0] = "=Any";
    strings["Any##sgse3"].plurals[0] = "=Any";
    strings["--none--##sgse"].plurals[0] = "=--none--";
    strings["waiting...##BLearn"].plurals[0] = "=waiting...##BLearn";
    strings["Learn##BLearn"].plurals[0] = "=Learn##BLearn";
    strings["MIDI output##sgse0"].plurals[0] = "=MIDI output";
    strings["MIDI output##sgse1"].plurals[0] = "=MIDI output";
    strings["<disabled>##sgse2"].plurals[0] = "=<disabled>";
    strings["<disabled>##sgse3"].plurals[0] = "=<disabled>";
    strings["Output mode:##sgse"].plurals[0] = "=Output mode:";
    strings["Off (use for TX81Z)##sgse"].plurals[0] = "=Off (use for TX81Z)";
    strings["Melodic##sgse"].plurals[0] = "=Melodic";
    strings["Light Show (use for Launchpad)##sgse"].plurals[0] = "=Light Show (use for Launchpad)";
    strings["Send Program Change##sgse"].plurals[0] = "=Send Program Change";
    strings["Send MIDI clock##sgse"].plurals[0] = "=Send MIDI clock";
    strings["Send MIDI timecode##sgse"].plurals[0] = "=Send MIDI timecode";
    strings["Timecode frame rate:##sgse"].plurals[0] = "=Timecode frame rate:";
    strings["Closest to Tick Rate##sgse"].plurals[0] = "=Closest to Tick Rate";
    strings["Film (24fps)##sgse"].plurals[0] = "=Film (24fps)";
    strings["PAL (25fps)##sgse"].plurals[0] = "=PAL (25fps)";
    strings["NTSC drop (29.97fps)##sgse"].plurals[0] = "=NTSC drop (29.97fps)";
    strings["NTSC non-drop (30fps)##sgse"].plurals[0] = "=NTSC non-drop (30fps)";
    strings["Emulation##sgse"].plurals[0] = "=Emulation";
    strings["Cores##sgse"].plurals[0] = "=Cores";
    strings["System##sgse"].plurals[0] = "=System";
    strings["Playback Core(s)##sgse"].plurals[0] = "=Playback Core(s)";
    strings["used for playback##sgse"].plurals[0] = "=used for playback";
    strings["Render Core(s)##sgse"].plurals[0] = "=Render Core(s)";
    strings["used in audio export##sgse"].plurals[0] = "=used in audio export";
    strings["Quality##sgse1"].plurals[0] = "=Quality";
    strings["Playback##sgse"].plurals[0] = "=Playback";
    strings["Render##sgse"].plurals[0] = "=Render";
    strings["Other##sgse"].plurals[0] = "=Other";
    strings["PC Speaker strategy##sgse"].plurals[0] = "=PC Speaker strategy";
    strings["Sample ROMs:##sgse"].plurals[0] = "=Sample ROMs:";
    strings["OPL4 YRW801 path##sgse"].plurals[0] = "=OPL4 YRW801 path";
    strings["MultiPCM TG100 path##sgse"].plurals[0] = "=MultiPCM TG100 path";
    strings["MultiPCM MU5 path##sgse"].plurals[0] = "=MultiPCM MU5 path";
    strings["Keyboard##sgse0"].plurals[0] = "=Keyboard";
    strings["Keyboard##sgse1"].plurals[0] = "=Keyboard";
    strings["Import##sgse0"].plurals[0] = "=Import";
    strings["Export##sgse0"].plurals[0] = "=Export";
    strings["Reset defaults##sgse0"].plurals[0] = "=Reset defaults";
    strings["Are you sure you want to reset the keyboard settings?##sgse"].plurals[0] = "=Are you sure you want to reset the keyboard settings?";
    strings["Global hotkeys##sgse"].plurals[0] = "=Global hotkeys";
    strings["Window activation##sgse"].plurals[0] = "=Window activation";
    strings["Note input##sgse1"].plurals[0] = "=Note input";
    strings["Key##sgse"].plurals[0] = "=Key";
    strings["Type##sgse1"].plurals[0] = "=Type";
    strings["Value##sgse"].plurals[0] = "=Value";
    strings["Remove##sgse"].plurals[0] = "=Remove";
    strings["Macro release##SNType_%d"].plurals[0] = "=Macro release##SNType_%d";
    strings["Note release##SNType_%d"].plurals[0] = "=Note release##SNType_%d";
    strings["Note off##SNType_%d"].plurals[0] = "=Note off##SNType_%d";
    strings["Note##SNType_%d"].plurals[0] = "=Note##SNType_%d";
    strings["Add...##sgse"].plurals[0] = "=Add...";
    strings["Pattern##sgse0"].plurals[0] = "=Pattern";
    strings["Instrument list##sgse"].plurals[0] = "=Instrument list";
    strings["Wavetable list##sgse"].plurals[0] = "=Wavetable list";
    strings["Local wavetables list##sgse"].plurals[0] = "=Local wavetables list";
    strings["Sample list##sgse"].plurals[0] = "=Sample list";
    strings["Orders##sgse0"].plurals[0] = "=Orders";
    strings["Sample editor##sgse"].plurals[0] = "=Sample editor";
    strings["Interface##sgse0"].plurals[0] = "=Interface";
    strings["Layout##sgse"].plurals[0] = "=Layout";
    strings["Workspace layout:##sgse"].plurals[0] = "=Workspace layout:";
    strings["Import##sgse1"].plurals[0] = "=Import";
    strings["Export##sgse1"].plurals[0] = "=Export";
    strings["Reset##sgse"].plurals[0] = "=Reset";
    strings["Are you sure you want to reset the workspace layout?##sgse"].plurals[0] = "=Are you sure you want to reset the workspace layout?";
    strings["Allow docking editors##sgse"].plurals[0] = "=Allow docking editors";
    strings["Remember window position##sgse"].plurals[0] = "=Remember window position";
    strings["remembers the window's last position on start-up.##sgse"].plurals[0] = "=remembers the window's last position on start-up.";
    strings["Only allow window movement when clicking on title bar##sgse"].plurals[0] = "=Only allow window movement when clicking on title bar";
    strings["Center pop-up windows##sgse"].plurals[0] = "=Center pop-up windows";
    strings["Play/edit controls layout:##sgse"].plurals[0] = "=Play/edit controls layout:";
    strings["Classic##ecl0"].plurals[0] = "=Classic##ecl0";
    strings["Compact##ecl1"].plurals[0] = "=Compact##ecl1";
    strings["Compact (vertical)##ecl2"].plurals[0] = "=Compact (vertical)##ecl2";
    strings["Split##ecl3"].plurals[0] = "=Split##ecl3";
    strings["Position of buttons in Orders:##sgse"].plurals[0] = "=Position of buttons in Orders:";
    strings["Top##obp0"].plurals[0] = "=Top##obp0";
    strings["Left##obp1"].plurals[0] = "=Left##obp1";
    strings["Right##obp2"].plurals[0] = "=Right##obp2";
    strings["Mouse##sgse"].plurals[0] = "=Mouse";
    strings["Double-click time (seconds)##sgse"].plurals[0] = "=Double-click time (seconds)";
    strings["Don't raise pattern editor on click##sgse"].plurals[0] = "=Don't raise pattern editor on click";
    strings["Focus pattern editor when selecting instrument##sgse"].plurals[0] = "=Focus pattern editor when selecting instrument";
    strings["Note preview behavior:##sgse"].plurals[0] = "=Note preview behavior:";
    strings["Never##npb0"].plurals[0] = "=Never##npb0";
    strings["When cursor is in Note column##npb1"].plurals[0] = "=When cursor is in Note column##npb1";
    strings["When cursor is in Note column or not in edit mode##npb2"].plurals[0] = "=When cursor is in Note column or not in edit mode##npb2";
    strings["Always##npb3"].plurals[0] = "=Always##npb3";
    strings["Allow dragging selection:##sgse"].plurals[0] = "=Allow dragging selection:";
    strings["No##dms0"].plurals[0] = "=No##dms0";
    strings["Yes##dms1"].plurals[0] = "=Yes##dms1";
    strings["Yes (while holding Ctrl only)##dms2"].plurals[0] = "=Yes (while holding Ctrl only)##dms2";
    strings["Toggle channel solo on:##sgse"].plurals[0] = "=Toggle channel solo on:";
    strings["Right-click or double-click##soloA"].plurals[0] = "=Right-click or double-click##soloA";
    strings["Right-click##soloR"].plurals[0] = "=Right-click##soloR";
    strings["Double-click##soloD"].plurals[0] = "=Double-click##soloD";
    strings["Double click selects entire column##sgse"].plurals[0] = "=Double click selects entire column";
    strings["Cursor behavior##sgse"].plurals[0] = "=Cursor behavior";
    strings["Insert pushes entire channel row##sgse"].plurals[0] = "=Insert pushes entire channel row";
    strings["Pull delete affects entire channel row##sgse"].plurals[0] = "=Pull delete affects entire channel row";
    strings["Push value when overwriting instead of clearing it##sgse"].plurals[0] = "=Push value when overwriting instead of clearing it";
    strings["Effect input behavior:##sgse"].plurals[0] = "=Effect input behavior:";
    strings["Move down##eicb0"].plurals[0] = "=Move down##eicb0";
    strings["Move to effect value (otherwise move down)##eicb1"].plurals[0] = "=Move to effect value (otherwise move down)##eicb1";
    strings["Move to effect value/next effect and wrap around##eicb2"].plurals[0] = "=Move to effect value/next effect and wrap around##eicb2";
    strings["Delete effect value when deleting effect##sgse"].plurals[0] = "=Delete effect value when deleting effect";
    strings["Change current instrument when changing instrument column (absorb)##sgse"].plurals[0] = "=Change current instrument when changing instrument column (absorb)";
    strings["Remove instrument value when inserting note off/release##sgse"].plurals[0] = "=Remove instrument value when inserting note off/release";
    strings["Remove volume value when inserting note off/release##sgse"].plurals[0] = "=Remove volume value when inserting note off/release";
    strings["Cursor movement##sgse"].plurals[0] = "=Cursor movement";
    strings["Wrap horizontally:##sgse"].plurals[0] = "=Wrap horizontally:";
    strings["No##wrapH0"].plurals[0] = "=No##wrapH0";
    strings["Yes##wrapH1"].plurals[0] = "=Yes##wrapH1";
    strings["Yes, and move to next/prev row##wrapH2"].plurals[0] = "=Yes, and move to next/prev row##wrapH2";
    strings["Wrap vertically:##sgse"].plurals[0] = "=Wrap vertically:";
    strings["No##wrapV0"].plurals[0] = "=No##wrapV0";
    strings["Yes##wrapV1"].plurals[0] = "=Yes##wrapV1";
    strings["Yes, and move to next/prev pattern##wrapV2"].plurals[0] = "=Yes, and move to next/prev pattern##wrapV2";
    strings["Yes, and move to next/prev pattern (wrap around)##wrapV2"].plurals[0] = "=Yes, and move to next/prev pattern (wrap around)##wrapV2";
    strings["Cursor movement keys behavior:##sgse"].plurals[0] = "=Cursor movement keys behavior:";
    strings["Move by one##cmk0"].plurals[0] = "=Move by one##cmk0";
    strings["Move by Edit Step##cmk1"].plurals[0] = "=Move by Edit Step##cmk1";
    strings["Move cursor by edit step on delete##sgse"].plurals[0] = "=Move cursor by edit step on delete";
    strings["Move cursor by edit step on insert (push)##sgse"].plurals[0] = "=Move cursor by edit step on insert (push)";
    strings["Move cursor up on backspace-delete##sgse"].plurals[0] = "=Move cursor up on backspace-delete";
    strings["Move cursor to end of clipboard content when pasting##sgse"].plurals[0] = "=Move cursor to end of clipboard content when pasting";
    strings["Scrolling##sgse"].plurals[0] = "=Scrolling";
    strings["Change order when scrolling outside of pattern bounds:##sgse"].plurals[0] = "=Change order when scrolling outside of pattern bounds:";
    strings["No##pscroll0"].plurals[0] = "=No##pscroll0";
    strings["Yes##pscroll1"].plurals[0] = "=Yes##pscroll1";
    strings["Yes, and wrap around song##pscroll2"].plurals[0] = "=Yes, and wrap around song##pscroll2";
    strings["Cursor follows current order when moving it##sgse"].plurals[0] = "=Cursor follows current order when moving it";
    strings["applies when playback is stopped.##sgse"].plurals[0] = "=applies when playback is stopped.";
    strings["Don't scroll when moving cursor##sgse"].plurals[0] = "=Don't scroll when moving cursor";
    strings["Move cursor with scroll wheel:##sgse"].plurals[0] = "=Move cursor with scroll wheel:";
    strings["No##csw0"].plurals[0] = "=No##csw0";
    strings["Yes##csw1"].plurals[0] = "=Yes##csw1";
    strings["Inverted##csw2"].plurals[0] = "=Inverted##csw2";
    strings["How many steps to move with each scroll wheel step?##sgse"].plurals[0] = "=How many steps to move with each scroll wheel step?";
    strings["One##cws0"].plurals[0] = "=One##cws0";
    strings["Edit Step##cws1"].plurals[0] = "=Edit Step##cws1";
    strings["Assets##sgse0"].plurals[0] = "=Assets";
    strings["Display instrument type menu when adding instrument##sgse"].plurals[0] = "=Display instrument type menu when adding instrument";
    strings["Select asset after opening one##sgse"].plurals[0] = "=Select asset after opening one";
    strings["Appearance##sgse"].plurals[0] = "=Appearance";
    strings["Scaling##sgse"].plurals[0] = "=Scaling";
    strings["Automatic UI scaling factor##sgse"].plurals[0] = "=Automatic UI scaling factor";
    strings["UI scaling factor##sgse"].plurals[0] = "=UI scaling factor";
    strings["Icon size##sgse"].plurals[0] = "=Icon size";
    strings["Text##sgse"].plurals[0] = "=Text";
    strings["Font renderer##sgse"].plurals[0] = "=Font renderer";
    strings["Main font##sgse"].plurals[0] = "=Main font";
    strings["Size##MainFontSize"].plurals[0] = "=Size##MainFontSize";
    strings["Header font##sgse"].plurals[0] = "=Header font";
    strings["Size##HeadFontSize"].plurals[0] = "=Size##HeadFontSize";
    strings["Pattern font##sgse"].plurals[0] = "=Pattern font";
    strings["Size##PatFontSize"].plurals[0] = "=Size##PatFontSize";
    strings["Anti-aliased fonts##sgse"].plurals[0] = "=Anti-aliased fonts";
    strings["Support bitmap fonts##sgse"].plurals[0] = "=Support bitmap fonts";
    strings["Hinting:##sgse"].plurals[0] = "=Hinting:";
    strings["Off (soft)##fh0"].plurals[0] = "=Off (soft)##fh0";
    strings["Slight##fh1"].plurals[0] = "=Slight##fh1";
    strings["Normal##fh2"].plurals[0] = "=Normal##fh2";
    strings["Full (hard)##fh3"].plurals[0] = "=Full (hard)##fh3";
    strings["Auto-hinter:##sgse"].plurals[0] = "=Auto-hinter:";
    strings["Disable##fah0"].plurals[0] = "=Disable##fah0";
    strings["Enable##fah1"].plurals[0] = "=Enable##fah1";
    strings["Force##fah2"].plurals[0] = "=Force##fah2";
    strings["Display Japanese characters##sgse"].plurals[0] = "=Display Japanese characters";
    strings["Only toggle this option if you have enough graphics memory.\n"
            "This is a temporary solution until dynamic font atlas is implemented in Dear ImGui.\n\n"
            "このオプションは、十分なグラフィックメモリがある場合にのみ切り替えてください。\n"
            "これは、Dear ImGuiにダイナミックフォントアトラスが実装されるまでの一時的な解決策です。##sgse"].plurals[0] = 
            
            "=Only toggle this option if you have enough graphics memory.\n"
            "This is a temporary solution until dynamic font atlas is implemented in Dear ImGui.\n\n"
            "このオプションは、十分なグラフィックメモリがある場合にのみ切り替えてください。\n"
            "これは、Dear ImGuiにダイナミックフォントアトラスが実装されるまでの一時的な解決策です。";
    strings["Display Chinese (Simplified) characters##sgse"].plurals[0] = "=Display Chinese (Simplified) characters";
    strings["Only toggle this option if you have enough graphics memory.\n"
            "This is a temporary solution until dynamic font atlas is implemented in Dear ImGui.\n\n"
            "请在确保你有足够的显存后再启动此设定\n"
            "这是一个在ImGui实现动态字体加载之前的临时解决方案##sgse"].plurals[0] = 
            
            "=Only toggle this option if you have enough graphics memory.\n"
            "This is a temporary solution until dynamic font atlas is implemented in Dear ImGui.\n\n"
            "请在确保你有足够的显存后再启动此设定\n"
            "这是一个在ImGui实现动态字体加载之前的临时解决方案";
    
    strings["Display Chinese (Traditional) characters##sgse"].plurals[0] = "=Display Chinese (Traditional) characters";
    strings["Only toggle this option if you have enough graphics memory.\n"
            "This is a temporary solution until dynamic font atlas is implemented in Dear ImGui.\n\n"
            "請在確保你有足夠的顯存后再啟動此設定\n"
            "這是一個在ImGui實現動態字體加載之前的臨時解決方案##sgse"].plurals[0] = 
            
            "=Only toggle this option if you have enough graphics memory.\n"
            "This is a temporary solution until dynamic font atlas is implemented in Dear ImGui.\n\n"
            "請在確保你有足夠的顯存后再啟動此設定\n"
            "這是一個在ImGui實現動態字體加載之前的臨時解決方案";
    strings["Display Korean characters##sgse"].plurals[0] = "=Display Korean characters";
    strings["Only toggle this option if you have enough graphics memory.\n"
            "This is a temporary solution until dynamic font atlas is implemented in Dear ImGui.\n\n"
            "그래픽 메모리가 충분한 경우에만 이 옵션을 선택하십시오.\n"
            "이 옵션은 Dear ImGui에 동적 글꼴 아틀라스가 구현될 때까지 임시 솔루션입니다.##sgse"].plurals[0] = 
            
            "=Only toggle this option if you have enough graphics memory.\n"
            "This is a temporary solution until dynamic font atlas is implemented in Dear ImGui.\n\n"
            "그래픽 메모리가 충분한 경우에만 이 옵션을 선택하십시오.\n"
            "이 옵션은 Dear ImGui에 동적 글꼴 아틀라스가 구현될 때까지 임시 솔루션입니다.";
    strings["Program##sgse2"].plurals[0] = "=Program";
    strings["Title bar:##sgse"].plurals[0] = "=Title bar:";
    strings["Furnace-B##tbar0"].plurals[0] = "=Furnace-B##tbar0";
    strings["Song Name - Furnace-B##tbar1"].plurals[0] = "=Song Name - Furnace-B##tbar1";
    strings["file_name.fur - Furnace-B##tbar2"].plurals[0] = "=file_name.fur - Furnace-B##tbar2";
    strings["/path/to/file.fur - Furnace-B##tbar3"].plurals[0] = "=/path/to/file.fur - Furnace-B##tbar3";
    strings["Display system name on title bar##sgse"].plurals[0] = "=Display system name on title bar";
    strings["Display chip names instead of \"multi-system\" in title bar##sgse"].plurals[0] = "=Display chip names instead of \"multi-system\" in title bar##sgse";
    strings["Status bar:##sgse"].plurals[0] = "=Status bar:";
    strings["Cursor details##sbar0"].plurals[0] = "=Cursor details##sbar0";
    strings["File path##sbar1"].plurals[0] = "=File path##sbar1";
    strings["Cursor details or file path##sbar2"].plurals[0] = "=Cursor details or file path##sbar2";
    strings["Nothing##sbar3"].plurals[0] = "=Nothing##sbar3";
    strings["Display playback status when playing##sgse"].plurals[0] = "=Display playback status when playing";
    strings["Export options layout:##sgse"].plurals[0] = "=Export options layout:";
    strings["Sub-menus in File menu##eol0"].plurals[0] = "=Sub-menus in File menu##eol0";
    strings["Modal window with tabs##eol1"].plurals[0] = "=Modal window with tabs##eol1";
    strings["Modal windows with options in File menu##eol2"].plurals[0] = "=Modal windows with options in File menu##eol2";
    strings["Capitalize menu bar##sgse"].plurals[0] = "=Capitalize menu bar";
    strings["Display add/configure/change/remove chip menus in File menu##sgse"].plurals[0] = "=Display add/configure/change/remove chip menus in File menu";
    strings["Orders##sgse1"].plurals[0] = "=Orders";
    strings["Highlight channel at cursor in Orders##sgse"].plurals[0] = "=Highlight channel at cursor in Orders";
    strings["Orders row number format:##sgse"].plurals[0] = "=Orders row number format:";
    strings["Decimal##orbD"].plurals[0] = "=Decimal##orbD";
    strings["Hexadecimal##orbH"].plurals[0] = "=Hexadecimal##orbH";
    strings["Pattern##sgse1"].plurals[0] = "=Pattern";
    strings["Center pattern view##sgse"].plurals[0] = "=Center pattern view";
    strings["Overflow pattern highlights##sgse"].plurals[0] = "=Overflow pattern highlights";
    strings["Display previous/next pattern##sgse"].plurals[0] = "=Display previous/next pattern";
    strings["Pattern row number format:##sgse"].plurals[0] = "=Pattern row number format:";
    strings["Decimal##prbD"].plurals[0] = "=Decimal##prbD";
    strings["Hexadecimal##prbH"].plurals[0] = "=Hexadecimal##prbH";
    strings["Pattern view labels:##sgse"].plurals[0] = "=Pattern view labels:";
    strings["Note off (3-char)##sgse"].plurals[0] = "=Note off (3-char)";
    strings["Note release (3-char)##sgse"].plurals[0] = "=Note release (3-char)";
    strings["Macro release (3-char)##sgse"].plurals[0] = "=Macro release (3-char)";
    strings["Empty field (3-char)##sgse"].plurals[0] = "=Empty field (3-char)";
    strings["Empty field (2-char)##sgse"].plurals[0] = "=Empty field (2-char)";
    strings["Pattern view spacing after:##sgse"].plurals[0] = "=Pattern view spacing after:";
    strings["Note##sgse"].plurals[0] = "=Note";
    strings["Instrument##sgse1"].plurals[0] = "=Instrument";
    strings["Volume##sgse4"].plurals[0] = "=Volume";
    strings["Effect##sgse"].plurals[0] = "=Effect";
    strings["Effect value##sgse"].plurals[0] = "=Effect value";
    strings["Single-digit effects for 00-0F##sgse"].plurals[0] = "=Single-digit effects for 00-0F";
    strings["Use flats instead of sharps##sgse"].plurals[0] = "=Use flats instead of sharps";
    strings["Use German notation##sgse"].plurals[0] = "=Use German notation";
    strings["Channel##sgse1"].plurals[0] = "=Channel";
    strings["Channel style:##sgse"].plurals[0] = "=Channel style:";
    strings["Classic##CHS0"].plurals[0] = "=Classic##CHS0";
    strings["Line##CHS1"].plurals[0] = "=Line##CHS1";
    strings["Round##CHS2"].plurals[0] = "=Round##CHS2";
    strings["Split button##CHS3"].plurals[0] = "=Split button##CHS3";
    strings["Square border##CHS4"].plurals[0] = "=Square border##CHS4";
    strings["Round border##CHS5"].plurals[0] = "=Round border##CHS5";
    strings["Channel volume bar:##sgse"].plurals[0] = "=Channel volume bar:";
    strings["Non##CHV0"].plurals[0] = "=Non##CHV0";
    strings["Simple##CHV1"].plurals[0] = "=Simple##CHV1";
    strings["Stereo##CHV2"].plurals[0] = "=Stereo##CHV2";
    strings["Real##CHV3"].plurals[0] = "=Real##CHV3";
    strings["Real (stereo)##CHV4"].plurals[0] = "=Real (stereo)##CHV4";
    strings["Channel feedback style:##sgse"].plurals[0] = "=Channel feedback style:";
    strings["Off##CHF0"].plurals[0] = "=Off##CHF0";
    strings["Note##CHF1"].plurals[0] = "=Note##CHF1";
    strings["Volume##CHF2"].plurals[0] = "=Volume##CHF2";
    strings["Active##CHF3"].plurals[0] = "=Active##CHF3";
    strings["Channel font:##sgse"].plurals[0] = "=Channel font:";
    strings["Regular##CHFont0"].plurals[0] = "=Regular##CHFont0";
    strings["Monospace##CHFont1"].plurals[0] = "=Monospace##CHFont1";
    strings["Center channel name##sgse"].plurals[0] = "=Center channel name";
    strings["Channel colors:##sgse"].plurals[0] = "=Channel colors:";
    strings["Single##CHC0"].plurals[0] = "=Single##CHC0";
    strings["Channel type##CHC1"].plurals[0] = "=Channel type##CHC1";
    strings["Instrument type##CHC2"].plurals[0] = "=Instrument type##CHC2";
    strings["Channel name colors:##sgse"].plurals[0] = "=Channel name colors:";
    strings["Single##CTC0"].plurals[0] = "=Single##CTC0";
    strings["Channel type##CTC1"].plurals[0] = "=Channel type##CTC1";
    strings["Instrument type##CTC2"].plurals[0] = "=Instrument type##CTC2";
    strings["Assets##sgse1"].plurals[0] = "=Assets";
    strings["Unified instrument/wavetable/sample list##sgse"].plurals[0] = "=Unified instrument/wavetable/sample list";
    strings["Horizontal instrument list##sgse"].plurals[0] = "=Horizontal instrument list";
    strings["Instrument list icon style:##sgse"].plurals[0] = "=Instrument list icon style:";
    strings["None##iis0"].plurals[0] = "=None##iis0";
    strings["Graphical icons##iis1"].plurals[0] = "=Graphical icons##iis1";
    strings["Letter icons##iis2"].plurals[0] = "=Letter icons##iis2";
    strings["Colorize instrument editor using instrument type##sgse"].plurals[0] = "=Colorize instrument editor using instrument type";
    strings["Macro Editor##sgse0"].plurals[0] = "=Macro Editor";
    strings["Macro editor layout:##sgse"].plurals[0] = "=Macro editor layout:";
    strings["Unified##mel0"].plurals[0] = "=Unified##mel0";
    strings["Grid##mel2"].plurals[0] = "=Grid##mel2";
    strings["Single (with list)##mel3"].plurals[0] = "=Single (with list)##mel3";
    strings["Use classic macro editor vertical slider##sgse"].plurals[0] = "=Use classic macro editor vertical slider";
    strings["Wave Editor##sgse"].plurals[0] = "=Wave Editor";
    strings["Use compact wave editor##sgse"].plurals[0] = "=Use compact wave editor";
    strings["FM Editor##sgse0"].plurals[0] = "=FM Editor";
    strings["FM parameter names:##sgse"].plurals[0] = "=FM parameter names:";
    strings["Friendly##fmn0"].plurals[0] = "=Friendly##fmn0";
    strings["Technical##fmn1"].plurals[0] = "=Technical##fmn1";
    strings["Technical (alternate)##fmn2"].plurals[0] = "=Technical (alternate)##fmn2";
    strings["Use standard OPL waveform names##sgse"].plurals[0] = "=Use standard OPL waveform names";
    strings["FM parameter editor layout:##sgse"].plurals[0] = "=FM parameter editor layout:";
    strings["Modern##fml0"].plurals[0] = "=Modern##fml0";
    strings["Compact (2x2, classic)##fml1"].plurals[0] = "=Compact (2x2, classic)##fml1";
    strings["Compact (1x4)##fml2"].plurals[0] = "=Compact (1x4)##fml2";
    strings["Compact (4x1)##fml3"].plurals[0] = "=Compact (4x1)##fml3";
    strings["Alternate (2x2)##fml4"].plurals[0] = "=Alternate (2x2)##fml4";
    strings["Alternate (1x4)##fml5"].plurals[0] = "=Alternate (1x4)##fml5";
    strings["Alternate (4x1)##fml6"].plurals[0] = "=Alternate (4x1)##fml6";
    strings["Position of Sustain in FM editor:##sgse"].plurals[0] = "=Position of Sustain in FM editor:";
    strings["Between Decay and Sustain Rate##susp0"].plurals[0] = "=Between Decay and Sustain Rate##susp0";
    strings["After Release Rate##susp1"].plurals[0] = "=After Release Rate##susp1";
    strings["Use separate colors for carriers/modulators in FM editor##sgse"].plurals[0] = "=Use separate colors for carriers/modulators in FM editor";
    strings["Unsigned FM detune values##sgse"].plurals[0] = "=Unsigned FM detune values";
    strings["Memory Composition##sgse"].plurals[0] = "=Memory Composition";
    strings["Chip memory usage unit:##sgse"].plurals[0] = "=Chip memory usage unit:";
    strings["Bytes##MUU0"].plurals[0] = "=Bytes##MUU0";
    strings["Kilobytes##MUU1"].plurals[0] = "=Kilobytes##MUU1";
    strings["Oscilloscope##set"].plurals[0] = "=Oscilloscope##set";
    strings["Rounded corners##sgse"].plurals[0] = "=Rounded corners";
    strings["Border##sgse"].plurals[0] = "=Border";
    strings["Mono##sgse1"].plurals[0] = "=Mono";
    strings["Anti-aliased##sgse"].plurals[0] = "=Anti-aliased";
    strings["Fill entire window##sgse"].plurals[0] = "=Fill entire window";
    strings["Waveform goes out of bounds##sgse"].plurals[0] = "=Waveform goes out of bounds";
    strings["Line size##sgse"].plurals[0] = "=Line size";
    strings["Windows##sgse"].plurals[0] = "=Windows";
    strings["Rounded window corners##sgse"].plurals[0] = "=Rounded window corners";
    strings["Rounded buttons##sgse"].plurals[0] = "=Rounded buttons";
    strings["Rounded tabs##sgse"].plurals[0] = "=Rounded tabs";
    strings["Rounded scrollbars##sgse"].plurals[0] = "=Rounded scrollbars";
    strings["Rounded menu corners##sgse"].plurals[0] = "=Rounded menu corners";
    strings["Borders around widgets##sgse"].plurals[0] = "=Borders around widgets";
    strings["Misc##sgse"].plurals[0] = "=Misc";
    strings["Wrap text##sgse"].plurals[0] = "=Wrap text";
    strings["Wrap text in song/subsong comments window.##sgse"].plurals[0] = "=Wrap text in song/subsong comments window.";
    strings["Frame shading in text windows##sgse"].plurals[0] = "=Frame shading in text windows";
    strings["Apply frame shading to the multiline text fields\nsuch as song/subsong info/comments.##sgse"].plurals[0] = "=Apply frame shading to the multiline text fields\nsuch as song/subsong info/comments.";
    strings["Show chip info in chip manager##sgse"].plurals[0] = "=Show chip info in chip manager";
    strings["Display tooltip in chip manager when hovering over the chip. Tooltip shows chip name and description.##sgse"].plurals[0] = "=Display tooltip in chip manager when hovering over the chip. Tooltip shows chip name and description.";
    strings["Color##sgse"].plurals[0] = "=Color";
    strings["Color scheme##sgse"].plurals[0] = "=Color scheme";
    strings["Import##sgse2"].plurals[0] = "=Import";
    strings["Export##sgse2"].plurals[0] = "=Export";
    strings["Reset defaults##sgse1"].plurals[0] = "=Reset defaults";
    strings["Are you sure you want to reset the color scheme?##sgse"].plurals[0] = "=Are you sure you want to reset the color scheme?";
    strings["Interface##sgse1"].plurals[0] = "=Interface";
    strings["Frame shading##sgse"].plurals[0] = "=Frame shading";
    strings["Interface (other)##sgse"].plurals[0] = "=Interface (other)";
    strings["Miscellaneous##sgse"].plurals[0] = "=Miscellaneous";
    strings["File Picker (built-in)##sgse"].plurals[0] = "=File Picker (built-in)";
    strings["Oscilloscope##sgse"].plurals[0] = "=Oscilloscope";
    strings["Wave (non-mono)##sgse"].plurals[0] = "=Wave (non-mono)";
    strings["Volume Meter##sgse"].plurals[0] = "=Volume Meter";
    strings["Orders##sgse2"].plurals[0] = "=Orders";
    strings["Envelope View##sgse"].plurals[0] = "=Envelope View";
    strings["FM Editor##sgse1"].plurals[0] = "=FM Editor";
    strings["Macro Editor##sgse1"].plurals[0] = "=Macro Editor";
    strings["Instrument Types##sgse"].plurals[0] = "=Instrument Types";
    strings["Channel##sgse2"].plurals[0] = "=Channel";
    strings["Pattern##sgse2"].plurals[0] = "=Pattern";
    strings["Sample Editor##sgse"].plurals[0] = "=Sample Editor";
    strings["Pattern Manager##sgse"].plurals[0] = "=Pattern Manager";
    strings["Piano##sgse"].plurals[0] = "=Piano";
    strings["Clock##sgse"].plurals[0] = "=Clock";
    strings["Patchbay##sgse"].plurals[0] = "=Patchbay";
    strings["Memory Composition##sgse"].plurals[0] = "=Memory Composition##sgse";
    strings["Log Viewer##sgse"].plurals[0] = "=Log Viewer";

    // these are messy, but the ##CC_GUI... is required.
    strings["Button##CC_GUI_COLOR_BUTTON"].plurals[0] = "=Button##CC_GUI_COLOR_BUTTON";
    strings["Button (hovered)##CC_GUI_COLOR_BUTTON_HOVER"].plurals[0] = "=Button (hovered)##CC_GUI_COLOR_BUTTON_HOVER";
    strings["Button (active)##CC_GUI_COLOR_BUTTON_ACTIVE"].plurals[0] = "=Button (active)##CC_GUI_COLOR_BUTTON_ACTIVE";
    strings["Tab##CC_GUI_COLOR_TAB"].plurals[0] = "=Tab##CC_GUI_COLOR_TAB";
    strings["Tab (hovered)##CC_GUI_COLOR_TAB_HOVER"].plurals[0] = "=Tab (hovered)##CC_GUI_COLOR_TAB_HOVER";
    strings["Tab (active)##CC_GUI_COLOR_TAB_ACTIVE"].plurals[0] = "=Tab (active)##CC_GUI_COLOR_TAB_ACTIVE";
    strings["Tab (unfocused)##CC_GUI_COLOR_TAB_UNFOCUSED"].plurals[0] = "=Tab (unfocused)##CC_GUI_COLOR_TAB_UNFOCUSED";
    strings["Tab (unfocused and active)##CC_GUI_COLOR_TAB_UNFOCUSED_ACTIVE"].plurals[0] = "=Tab (unfocused and active)##CC_GUI_COLOR_TAB_UNFOCUSED_ACTIVE";
    strings["ImGui header##CC_GUI_COLOR_IMGUI_HEADER"].plurals[0] = "=ImGui header##CC_GUI_COLOR_IMGUI_HEADER";
    strings["ImGui header (hovered)##CC_GUI_COLOR_IMGUI_HEADER_HOVER"].plurals[0] = "=ImGui header (hovered)##CC_GUI_COLOR_IMGUI_HEADER_HOVER";
    strings["ImGui header (active)##CC_GUI_COLOR_IMGUI_HEADER_ACTIVE"].plurals[0] = "=ImGui header (active)##CC_GUI_COLOR_IMGUI_HEADER_ACTIVE";
    strings["Resize grip##CC_GUI_COLOR_RESIZE_GRIP"].plurals[0] = "=Resize grip##CC_GUI_COLOR_RESIZE_GRIP";
    strings["Resize grip (hovered)##CC_GUI_COLOR_RESIZE_GRIP_HOVER"].plurals[0] = "=Resize grip (hovered)##CC_GUI_COLOR_RESIZE_GRIP_HOVER";
    strings["Resize grip (active)##CC_GUI_COLOR_RESIZE_GRIP_ACTIVE"].plurals[0] = "=Resize grip (active)##CC_GUI_COLOR_RESIZE_GRIP_ACTIVE";
    strings["Widget background##CC_GUI_COLOR_WIDGET_BACKGROUND"].plurals[0] = "=Widget background##CC_GUI_COLOR_WIDGET_BACKGROUND";
    strings["Widget background (hovered)##CC_GUI_COLOR_WIDGET_BACKGROUND_HOVER"].plurals[0] = "=Widget background (hovered)##CC_GUI_COLOR_WIDGET_BACKGROUND_HOVER";
    strings["Widget background (active)##CC_GUI_COLOR_WIDGET_BACKGROUND_ACTIVE"].plurals[0] = "=Widget background (active)##CC_GUI_COLOR_WIDGET_BACKGROUND_ACTIVE";
    strings["Slider grab##CC_GUI_COLOR_SLIDER_GRAB"].plurals[0] = "=Slider grab##CC_GUI_COLOR_SLIDER_GRAB";
    strings["Slider grab (active)##CC_GUI_COLOR_SLIDER_GRAB_ACTIVE"].plurals[0] = "=Slider grab (active)##CC_GUI_COLOR_SLIDER_GRAB_ACTIVE";
    strings["Title background (active)##CC_GUI_COLOR_TITLE_BACKGROUND_ACTIVE"].plurals[0] = "=Title background (active)##CC_GUI_COLOR_TITLE_BACKGROUND_ACTIVE";
    strings["Checkbox/radio button mark##CC_GUI_COLOR_CHECK_MARK"].plurals[0] = "=Checkbox/radio button mark##CC_GUI_COLOR_CHECK_MARK";
    strings["Text selection##CC_GUI_COLOR_TEXT_SELECTION"].plurals[0] = "=Text selection##CC_GUI_COLOR_TEXT_SELECTION";
    strings["Line plot##CC_GUI_COLOR_PLOT_LINES"].plurals[0] = "=Line plot##CC_GUI_COLOR_PLOT_LINES";
    strings["Line plot (hovered)##CC_GUI_COLOR_PLOT_LINES_HOVER"].plurals[0] = "=Line plot (hovered)##CC_GUI_COLOR_PLOT_LINES_HOVER";
    strings["Histogram plot##CC_GUI_COLOR_PLOT_HISTOGRAM"].plurals[0] = "=Histogram plot##CC_GUI_COLOR_PLOT_HISTOGRAM";
    strings["Histogram plot (hovered)##CC_GUI_COLOR_PLOT_HISTOGRAM_HOVER"].plurals[0] = "=Histogram plot (hovered)##CC_GUI_COLOR_PLOT_HISTOGRAM_HOVER";
    strings["Table row (even)##CC_GUI_COLOR_TABLE_ROW_EVEN"].plurals[0] = "=Table row (even)##CC_GUI_COLOR_TABLE_ROW_EVEN";
    strings["Table row (odd)##CC_GUI_COLOR_TABLE_ROW_ODD"].plurals[0] = "=Table row (odd)##CC_GUI_COLOR_TABLE_ROW_ODD";

    strings["Background##CC_GUI_COLOR_BACKGROUND"].plurals[0] = "=Background##CC_GUI_COLOR_BACKGROUND";
    strings["Window background##CC_GUI_COLOR_FRAME_BACKGROUND"].plurals[0] = "=Window background##CC_GUI_COLOR_FRAME_BACKGROUND";
    strings["Sub-window background##CC_GUI_COLOR_FRAME_BACKGROUND_CHILD"].plurals[0] = "=Sub-window background##CC_GUI_COLOR_FRAME_BACKGROUND_CHILD";
    strings["Pop-up background##CC_GUI_COLOR_FRAME_BACKGROUND_POPUP"].plurals[0] = "=Pop-up background##CC_GUI_COLOR_FRAME_BACKGROUND_POPUP";
    strings["Modal backdrop##CC_GUI_COLOR_MODAL_BACKDROP"].plurals[0] = "=Modal backdrop##CC_GUI_COLOR_MODAL_BACKDROP";
    strings["Header##CC_GUI_COLOR_HEADER"].plurals[0] = "=Header##CC_GUI_COLOR_HEADER";
    strings["Text##CC_GUI_COLOR_TEXT"].plurals[0] = "=Text##CC_GUI_COLOR_TEXT";
    strings["Text (disabled)##CC_GUI_COLOR_TEXT_DISABLED"].plurals[0] = "=Text (disabled)##CC_GUI_COLOR_TEXT_DISABLED";
    strings["Title bar (inactive)##CC_GUI_COLOR_TITLE_INACTIVE"].plurals[0] = "=Title bar (inactive)##CC_GUI_COLOR_TITLE_INACTIVE";
    strings["Title bar (collapsed)##CC_GUI_COLOR_TITLE_COLLAPSED"].plurals[0] = "=Title bar (collapsed)##CC_GUI_COLOR_TITLE_COLLAPSED";
    strings["Menu bar##CC_GUI_COLOR_MENU_BAR"].plurals[0] = "=Menu bar##CC_GUI_COLOR_MENU_BAR";
    strings["Border##CC_GUI_COLOR_BORDER"].plurals[0] = "=Border##CC_GUI_COLOR_BORDER";
    strings["Border shadow##CC_GUI_COLOR_BORDER_SHADOW"].plurals[0] = "=Border shadow##CC_GUI_COLOR_BORDER_SHADOW";
    strings["Scroll bar##CC_GUI_COLOR_SCROLL"].plurals[0] = "=Scroll bar##CC_GUI_COLOR_SCROLL";
    strings["Scroll bar (hovered)##CC_GUI_COLOR_SCROLL_HOVER"].plurals[0] = "=Scroll bar (hovered)##CC_GUI_COLOR_SCROLL_HOVER";
    strings["Scroll bar (clicked)##CC_GUI_COLOR_SCROLL_ACTIVE"].plurals[0] = "=Scroll bar (clicked)##CC_GUI_COLOR_SCROLL_ACTIVE";
    strings["Scroll bar background##CC_GUI_COLOR_SCROLL_BACKGROUND"].plurals[0] = "=Scroll bar background##CC_GUI_COLOR_SCROLL_BACKGROUND";
    strings["Separator##CC_GUI_COLOR_SEPARATOR"].plurals[0] = "=Separator##CC_GUI_COLOR_SEPARATOR";
    strings["Separator (hover)##CC_GUI_COLOR_SEPARATOR_HOVER"].plurals[0] = "=Separator (hover)##CC_GUI_COLOR_SEPARATOR_HOVER";
    strings["Separator (active)##CC_GUI_COLOR_SEPARATOR_ACTIVE"].plurals[0] = "=Separator (active)##CC_GUI_COLOR_SEPARATOR_ACTIVE";
    strings["Docking preview##CC_GUI_COLOR_DOCKING_PREVIEW"].plurals[0] = "=Docking preview##CC_GUI_COLOR_DOCKING_PREVIEW";
    strings["Docking empty##CC_GUI_COLOR_DOCKING_EMPTY"].plurals[0] = "=Docking empty##CC_GUI_COLOR_DOCKING_EMPTY";
    strings["Table header##CC_GUI_COLOR_TABLE_HEADER"].plurals[0] = "=Table header##CC_GUI_COLOR_TABLE_HEADER";
    strings["Table border (hard)##CC_GUI_COLOR_TABLE_BORDER_HARD"].plurals[0] = "=Table border (hard)##CC_GUI_COLOR_TABLE_BORDER_HARD";
    strings["Table border (soft)##CC_GUI_COLOR_TABLE_BORDER_SOFT"].plurals[0] = "=Table border (soft)##CC_GUI_COLOR_TABLE_BORDER_SOFT";
    strings["Drag and drop target##CC_GUI_COLOR_DRAG_DROP_TARGET"].plurals[0] = "=Drag and drop target##CC_GUI_COLOR_DRAG_DROP_TARGET";
    strings["Window switcher (highlight)##CC_GUI_COLOR_NAV_WIN_HIGHLIGHT"].plurals[0] = "=Window switcher (highlight)##CC_GUI_COLOR_NAV_WIN_HIGHLIGHT";
    strings["Window switcher backdrop##CC_GUI_COLOR_NAV_WIN_BACKDROP"].plurals[0] = "=Window switcher backdrop##CC_GUI_COLOR_NAV_WIN_BACKDROP";

    strings["Toggle on##CC_GUI_COLOR_TOGGLE_ON"].plurals[0] = "=Toggle on##CC_GUI_COLOR_TOGGLE_ON";
    strings["Toggle off##CC_GUI_COLOR_TOGGLE_OFF"].plurals[0] = "=Toggle off##CC_GUI_COLOR_TOGGLE_OFF";
    strings["Playback status##CC_GUI_COLOR_PLAYBACK_STAT"].plurals[0] = "=Playback status##CC_GUI_COLOR_PLAYBACK_STAT";
    strings["Destructive hint##CC_GUI_COLOR_DESTRUCTIVE"].plurals[0] = "=Destructive hint##CC_GUI_COLOR_DESTRUCTIVE";
    strings["Warning hint##CC_GUI_COLOR_WARNING"].plurals[0] = "=Warning hint##CC_GUI_COLOR_WARNING";
    strings["Error hint##CC_GUI_COLOR_ERROR"].plurals[0] = "=Error hint##CC_GUI_COLOR_ERROR";

    strings["Directory##CC_GUI_COLOR_FILE_DIR"].plurals[0] = "=Directory##CC_GUI_COLOR_FILE_DIR";
    strings["Song (native)##CC_GUI_COLOR_FILE_SONG_NATIVE"].plurals[0] = "=Song (native)##CC_GUI_COLOR_FILE_SONG_NATIVE";
    strings["Song (import)##CC_GUI_COLOR_FILE_SONG_IMPORT"].plurals[0] = "=Song (import)##CC_GUI_COLOR_FILE_SONG_IMPORT";
    strings["Instrument##CC_GUI_COLOR_FILE_INSTR"].plurals[0] = "=Instrument##CC_GUI_COLOR_FILE_INSTR";
    strings["Audio##CC_GUI_COLOR_FILE_AUDIO"].plurals[0] = "=Audio##CC_GUI_COLOR_FILE_AUDIO";
    strings["Wavetable##CC_GUI_COLOR_FILE_WAVE"].plurals[0] = "=Wavetable##CC_GUI_COLOR_FILE_WAVE";
    strings["VGM##CC_GUI_COLOR_FILE_VGM"].plurals[0] = "=VGM##CC_GUI_COLOR_FILE_VGM";
    strings["ZSM##CC_GUI_COLOR_FILE_ZSM"].plurals[0] = "=ZSM##CC_GUI_COLOR_FILE_ZSM";
    strings["Font##CC_GUI_COLOR_FILE_FONT"].plurals[0] = "=Font##CC_GUI_COLOR_FILE_FONT";
    strings["Other##CC_GUI_COLOR_FILE_OTHER"].plurals[0] = "=Other##CC_GUI_COLOR_FILE_OTHER";

    strings["Border##CC_GUI_COLOR_OSC_BORDER"].plurals[0] = "=Border##CC_GUI_COLOR_OSC_BORDER";
    strings["Background (top-left)##CC_GUI_COLOR_OSC_BG1"].plurals[0] = "=Background (top-left)##CC_GUI_COLOR_OSC_BG1";
    strings["Background (top-right)##CC_GUI_COLOR_OSC_BG2"].plurals[0] = "=Background (top-right)##CC_GUI_COLOR_OSC_BG2";
    strings["Background (bottom-left)##CC_GUI_COLOR_OSC_BG3"].plurals[0] = "=Background (bottom-left)##CC_GUI_COLOR_OSC_BG3";
    strings["Background (bottom-right)##CC_GUI_COLOR_OSC_BG4"].plurals[0] = "=Background (bottom-right)##CC_GUI_COLOR_OSC_BG4";
    strings["Waveform##CC_GUI_COLOR_OSC_WAVE"].plurals[0] = "=Waveform##CC_GUI_COLOR_OSC_WAVE";
    strings["Waveform (clip)##CC_GUI_COLOR_OSC_WAVE_PEAK"].plurals[0] = "=Waveform (clip)##CC_GUI_COLOR_OSC_WAVE_PEAK";
    strings["Reference##CC_GUI_COLOR_OSC_REF"].plurals[0] = "=Reference##CC_GUI_COLOR_OSC_REF";
    strings["Guide##CC_GUI_COLOR_OSC_GUIDE"].plurals[0] = "=Guide##CC_GUI_COLOR_OSC_GUIDE";

    strings["Waveform (1)##CC_GUI_COLOR_OSC_WAVE_CH0"].plurals[0] = "=Waveform (1)##CC_GUI_COLOR_OSC_WAVE_CH0";
    strings["Waveform (2)##CC_GUI_COLOR_OSC_WAVE_CH1"].plurals[0] = "=Waveform (2)##CC_GUI_COLOR_OSC_WAVE_CH1";
    strings["Waveform (3)##CC_GUI_COLOR_OSC_WAVE_CH2"].plurals[0] = "=Waveform (3)##CC_GUI_COLOR_OSC_WAVE_CH2";
    strings["Waveform (4)##CC_GUI_COLOR_OSC_WAVE_CH3"].plurals[0] = "=Waveform (4)##CC_GUI_COLOR_OSC_WAVE_CH3";
    strings["Waveform (5)##CC_GUI_COLOR_OSC_WAVE_CH4"].plurals[0] = "=Waveform (5)##CC_GUI_COLOR_OSC_WAVE_CH4";
    strings["Waveform (6)##CC_GUI_COLOR_OSC_WAVE_CH5"].plurals[0] = "=Waveform (6)##CC_GUI_COLOR_OSC_WAVE_CH5";
    strings["Waveform (7)##CC_GUI_COLOR_OSC_WAVE_CH6"].plurals[0] = "=Waveform (7)##CC_GUI_COLOR_OSC_WAVE_CH6";
    strings["Waveform (8)##CC_GUI_COLOR_OSC_WAVE_CH7"].plurals[0] = "=Waveform (8)##CC_GUI_COLOR_OSC_WAVE_CH7";
    strings["Waveform (9)##CC_GUI_COLOR_OSC_WAVE_CH8"].plurals[0] = "=Waveform (9)##CC_GUI_COLOR_OSC_WAVE_CH8";
    strings["Waveform (10)##CC_GUI_COLOR_OSC_WAVE_CH9"].plurals[0] = "=Waveform (10)##CC_GUI_COLOR_OSC_WAVE_CH9";
    strings["Waveform (11)##CC_GUI_COLOR_OSC_WAVE_CH10"].plurals[0] = "=Waveform (11)##CC_GUI_COLOR_OSC_WAVE_CH10";
    strings["Waveform (12)##CC_GUI_COLOR_OSC_WAVE_CH11"].plurals[0] = "=Waveform (12)##CC_GUI_COLOR_OSC_WAVE_CH11";
    strings["Waveform (13)##CC_GUI_COLOR_OSC_WAVE_CH12"].plurals[0] = "=Waveform (13)##CC_GUI_COLOR_OSC_WAVE_CH12";
    strings["Waveform (14)##CC_GUI_COLOR_OSC_WAVE_CH13"].plurals[0] = "=Waveform (14)##CC_GUI_COLOR_OSC_WAVE_CH13";
    strings["Waveform (15)##CC_GUI_COLOR_OSC_WAVE_CH14"].plurals[0] = "=Waveform (15)##CC_GUI_COLOR_OSC_WAVE_CH14";
    strings["Waveform (16)##CC_GUI_COLOR_OSC_WAVE_CH15"].plurals[0] = "=Waveform (16)##CC_GUI_COLOR_OSC_WAVE_CH15";

    strings["Low##CC_GUI_COLOR_VOLMETER_LOW"].plurals[0] = "=Low##CC_GUI_COLOR_VOLMETER_LOW";
    strings["High##CC_GUI_COLOR_VOLMETER_HIGH"].plurals[0] = "=High##CC_GUI_COLOR_VOLMETER_HIGH";
    strings["Clip##CC_GUI_COLOR_VOLMETER_PEAK"].plurals[0] = "=Clip##CC_GUI_COLOR_VOLMETER_PEAK";

    strings["Order number##CC_GUI_COLOR_ORDER_ROW_INDEX"].plurals[0] = "=Order number##CC_GUI_COLOR_ORDER_ROW_INDEX";
    strings["Playing order background##CC_GUI_COLOR_ORDER_ACTIVE"].plurals[0] = "=Playing order background##CC_GUI_COLOR_ORDER_ACTIVE";
    strings["Song loop##CC_GUI_COLOR_SONG_LOOP"].plurals[0] = "=Song loop##CC_GUI_COLOR_SONG_LOOP";
    strings["Selected order##CC_GUI_COLOR_ORDER_SELECTED"].plurals[0] = "=Selected order##CC_GUI_COLOR_ORDER_SELECTED";
    strings["Similar patterns##CC_GUI_COLOR_ORDER_SIMILAR"].plurals[0] = "=Similar patterns##CC_GUI_COLOR_ORDER_SIMILAR";
    strings["Inactive patterns##CC_GUI_COLOR_ORDER_INACTIVE"].plurals[0] = "=Inactive patterns##CC_GUI_COLOR_ORDER_INACTIVE";

    strings["Envelope##CC_GUI_COLOR_FM_ENVELOPE"].plurals[0] = "=Envelope##CC_GUI_COLOR_FM_ENVELOPE";
    strings["Sustain guide##CC_GUI_COLOR_FM_ENVELOPE_SUS_GUIDE"].plurals[0] = "=Sustain guide##CC_GUI_COLOR_FM_ENVELOPE_SUS_GUIDE";
    strings["Release##CC_GUI_COLOR_FM_ENVELOPE_RELEASE"].plurals[0] = "=Release##CC_GUI_COLOR_FM_ENVELOPE_RELEASE";

    strings["Algorithm background##CC_GUI_COLOR_FM_ALG_BG"].plurals[0] = "=Algorithm background##CC_GUI_COLOR_FM_ALG_BG";
    strings["Algorithm lines##CC_GUI_COLOR_FM_ALG_LINE"].plurals[0] = "=Algorithm lines##CC_GUI_COLOR_FM_ALG_LINE";
    strings["Modulator##CC_GUI_COLOR_FM_MOD"].plurals[0] = "=Modulator##CC_GUI_COLOR_FM_MOD";
    strings["Carrier##CC_GUI_COLOR_FM_CAR"].plurals[0] = "=Carrier##CC_GUI_COLOR_FM_CAR";

    strings["SSG-EG##CC_GUI_COLOR_FM_SSG"].plurals[0] = "=SSG-EG##CC_GUI_COLOR_FM_SSG";
    strings["Waveform##CC_GUI_COLOR_FM_WAVE"].plurals[0] = "=Waveform##CC_GUI_COLOR_FM_WAVE";

    strings["Mod. accent (primary)##CC_GUI_COLOR_FM_PRIMARY_MOD"].plurals[0] = "=Mod. accent (primary)##CC_GUI_COLOR_FM_PRIMARY_MOD";
    strings["Mod. accent (secondary)##CC_GUI_COLOR_FM_SECONDARY_MOD"].plurals[0] = "=Mod. accent (secondary)##CC_GUI_COLOR_FM_SECONDARY_MOD";
    strings["Mod. border##CC_GUI_COLOR_FM_BORDER_MOD"].plurals[0] = "=Mod. border##CC_GUI_COLOR_FM_BORDER_MOD";
    strings["Mod. border shadow##CC_GUI_COLOR_FM_BORDER_SHADOW_MOD"].plurals[0] = "=Mod. border shadow##CC_GUI_COLOR_FM_BORDER_SHADOW_MOD";

    strings["Car. accent (primary)##CC_GUI_COLOR_FM_PRIMARY_CAR"].plurals[0] = "=Car. accent (primary)##CC_GUI_COLOR_FM_PRIMARY_CAR";
    strings["Car. accent (secondary)##CC_GUI_COLOR_FM_SECONDARY_CAR"].plurals[0] = "=Car. accent (secondary)##CC_GUI_COLOR_FM_SECONDARY_CAR";
    strings["Car. border##CC_GUI_COLOR_FM_BORDER_CAR"].plurals[0] = "=Car. border##CC_GUI_COLOR_FM_BORDER_CAR";
    strings["Car. border shadow##CC_GUI_COLOR_FM_BORDER_SHADOW_CAR"].plurals[0] = "=Car. border shadow##CC_GUI_COLOR_FM_BORDER_SHADOW_CAR";

    strings["Volume##CC_GUI_COLOR_MACRO_VOLUME"].plurals[0] = "=Volume##CC_GUI_COLOR_MACRO_VOLUME";
    strings["Pitch##CC_GUI_COLOR_MACRO_PITCH"].plurals[0] = "=Pitch##CC_GUI_COLOR_MACRO_PITCH";
    strings["Wave##CC_GUI_COLOR_MACRO_WAVE"].plurals[0] = "=Wave##CC_GUI_COLOR_MACRO_WAVE";
    strings["Other##CC_GUI_COLOR_MACRO_OTHER"].plurals[0] = "=Other##CC_GUI_COLOR_MACRO_OTHER";

    strings["FM (OPN)##CC_GUI_COLOR_INSTR_FM"].plurals[0] = "=FM (OPN)##CC_GUI_COLOR_INSTR_FM";
    strings["SN76489/Sega PSG##CC_GUI_COLOR_INSTR_STD"].plurals[0] = "=SN76489/Sega PSG##CC_GUI_COLOR_INSTR_STD";
    strings["T6W28##CC_GUI_COLOR_INSTR_T6W28"].plurals[0] = "=T6W28##CC_GUI_COLOR_INSTR_T6W28";
    strings["Game Boy##CC_GUI_COLOR_INSTR_GB"].plurals[0] = "=Game Boy##CC_GUI_COLOR_INSTR_GB";
    strings["C64##CC_GUI_COLOR_INSTR_C64"].plurals[0] = "=C64##CC_GUI_COLOR_INSTR_C64";
    strings["Amiga/Generic Sample##CC_GUI_COLOR_INSTR_AMIGA"].plurals[0] = "=Amiga/Generic Sample##CC_GUI_COLOR_INSTR_AMIGA";
    strings["PC Engine##CC_GUI_COLOR_INSTR_PCE"].plurals[0] = "=PC Engine##CC_GUI_COLOR_INSTR_PCE";
    strings["AY-3-8910/SSG##CC_GUI_COLOR_INSTR_AY"].plurals[0] = "=AY-3-8910/SSG##CC_GUI_COLOR_INSTR_AY";
    strings["AY8930##CC_GUI_COLOR_INSTR_AY8930"].plurals[0] = "=AY8930##CC_GUI_COLOR_INSTR_AY8930";
    strings["TIA##CC_GUI_COLOR_INSTR_TIA"].plurals[0] = "=TIA##CC_GUI_COLOR_INSTR_TIA";
    strings["SAA1099##CC_GUI_COLOR_INSTR_SAA1099"].plurals[0] = "=SAA1099##CC_GUI_COLOR_INSTR_SAA1099";
    strings["VIC##CC_GUI_COLOR_INSTR_VIC"].plurals[0] = "=VIC##CC_GUI_COLOR_INSTR_VIC";
    strings["PET##CC_GUI_COLOR_INSTR_PET"].plurals[0] = "=PET##CC_GUI_COLOR_INSTR_PET";
    strings["VRC6##CC_GUI_COLOR_INSTR_VRC6"].plurals[0] = "=VRC6##CC_GUI_COLOR_INSTR_VRC6";
    strings["VRC6 (saw)##CC_GUI_COLOR_INSTR_VRC6_SAW"].plurals[0] = "=VRC6 (saw)##CC_GUI_COLOR_INSTR_VRC6_SAW";
    strings["FM (OPLL)##CC_GUI_COLOR_INSTR_OPLL"].plurals[0] = "=FM (OPLL)##CC_GUI_COLOR_INSTR_OPLL";
    strings["FM (OPL)##CC_GUI_COLOR_INSTR_OPL"].plurals[0] = "=FM (OPL)##CC_GUI_COLOR_INSTR_OPL";
    strings["FDS##CC_GUI_COLOR_INSTR_FDS"].plurals[0] = "=FDS##CC_GUI_COLOR_INSTR_FDS";
    strings["Virtual Boy##CC_GUI_COLOR_INSTR_VBOY"].plurals[0] = "=Virtual Boy##CC_GUI_COLOR_INSTR_VBOY";
    strings["Namco 163##CC_GUI_COLOR_INSTR_N163"].plurals[0] = "=Namco 163##CC_GUI_COLOR_INSTR_N163";
    strings["Konami SCC##CC_GUI_COLOR_INSTR_SCC"].plurals[0] = "=Konami SCC##CC_GUI_COLOR_INSTR_SCC";
    strings["FM (OPZ)##CC_GUI_COLOR_INSTR_OPZ"].plurals[0] = "=FM (OPZ)##CC_GUI_COLOR_INSTR_OPZ";
    strings["POKEY##CC_GUI_COLOR_INSTR_POKEY"].plurals[0] = "=POKEY##CC_GUI_COLOR_INSTR_POKEY";
    strings["PC Beeper##CC_GUI_COLOR_INSTR_BEEPER"].plurals[0] = "=PC Beeper##CC_GUI_COLOR_INSTR_BEEPER";
    strings["WonderSwan##CC_GUI_COLOR_INSTR_SWAN"].plurals[0] = "=WonderSwan##CC_GUI_COLOR_INSTR_SWAN";
    strings["Lynx##CC_GUI_COLOR_INSTR_MIKEY"].plurals[0] = "=Lynx##CC_GUI_COLOR_INSTR_MIKEY";
    strings["VERA##CC_GUI_COLOR_INSTR_VERA"].plurals[0] = "=VERA##CC_GUI_COLOR_INSTR_VERA";
    strings["X1-010##CC_GUI_COLOR_INSTR_X1_010"].plurals[0] = "=X1-010##CC_GUI_COLOR_INSTR_X1_010";
    strings["ES5506##CC_GUI_COLOR_INSTR_ES5506"].plurals[0] = "=ES5506##CC_GUI_COLOR_INSTR_ES5506";
    strings["MultiPCM##CC_GUI_COLOR_INSTR_MULTIPCM"].plurals[0] = "=MultiPCM##CC_GUI_COLOR_INSTR_MULTIPCM";
    strings["SNES##CC_GUI_COLOR_INSTR_SNES"].plurals[0] = "=SNES##CC_GUI_COLOR_INSTR_SNES";
    strings["Sound Unit##CC_GUI_COLOR_INSTR_SU"].plurals[0] = "=Sound Unit##CC_GUI_COLOR_INSTR_SU";
    strings["Namco WSG##CC_GUI_COLOR_INSTR_NAMCO"].plurals[0] = "=Namco WSG##CC_GUI_COLOR_INSTR_NAMCO";
    strings["FM (OPL Drums)##CC_GUI_COLOR_INSTR_OPL_DRUMS"].plurals[0] = "=FM (OPL Drums)##CC_GUI_COLOR_INSTR_OPL_DRUMS";
    strings["FM (OPM)##CC_GUI_COLOR_INSTR_OPM"].plurals[0] = "=FM (OPM)##CC_GUI_COLOR_INSTR_OPM";
    strings["NES##CC_GUI_COLOR_INSTR_NES"].plurals[0] = "=NES##CC_GUI_COLOR_INSTR_NES";
    strings["MSM6258##CC_GUI_COLOR_INSTR_MSM6258"].plurals[0] = "=MSM6258##CC_GUI_COLOR_INSTR_MSM6258";
    strings["MSM6295##CC_GUI_COLOR_INSTR_MSM6295"].plurals[0] = "=MSM6295##CC_GUI_COLOR_INSTR_MSM6295";
    strings["ADPCM-A##CC_GUI_COLOR_INSTR_ADPCMA"].plurals[0] = "=ADPCM-A##CC_GUI_COLOR_INSTR_ADPCMA";
    strings["ADPCM-B##CC_GUI_COLOR_INSTR_ADPCMB"].plurals[0] = "=ADPCM-B##CC_GUI_COLOR_INSTR_ADPCMB";
    strings["Sega PCM##CC_GUI_COLOR_INSTR_SEGAPCM"].plurals[0] = "=Sega PCM##CC_GUI_COLOR_INSTR_SEGAPCM";
    strings["QSound##CC_GUI_COLOR_INSTR_QSOUND"].plurals[0] = "=QSound##CC_GUI_COLOR_INSTR_QSOUND";
    strings["YMZ280B##CC_GUI_COLOR_INSTR_YMZ280B"].plurals[0] = "=YMZ280B##CC_GUI_COLOR_INSTR_YMZ280B";
    strings["RF5C68##CC_GUI_COLOR_INSTR_RF5C68"].plurals[0] = "=RF5C68##CC_GUI_COLOR_INSTR_RF5C68";
    strings["MSM5232##CC_GUI_COLOR_INSTR_MSM5232"].plurals[0] = "=MSM5232##CC_GUI_COLOR_INSTR_MSM5232";
    strings["K007232##CC_GUI_COLOR_INSTR_K007232"].plurals[0] = "=K007232##CC_GUI_COLOR_INSTR_K007232";
    strings["GA20##CC_GUI_COLOR_INSTR_GA20"].plurals[0] = "=GA20##CC_GUI_COLOR_INSTR_GA20";
    strings["Pokémon Mini##CC_GUI_COLOR_INSTR_POKEMINI"].plurals[0] = "=Pokémon Mini##CC_GUI_COLOR_INSTR_POKEMINI";
    strings["SM8521##CC_GUI_COLOR_INSTR_SM8521"].plurals[0] = "=SM8521##CC_GUI_COLOR_INSTR_SM8521";
    strings["PV-1000##CC_GUI_COLOR_INSTR_PV1000"].plurals[0] = "=PV-1000##CC_GUI_COLOR_INSTR_PV1000";
    strings["K053260##CC_GUI_COLOR_INSTR_K053260"].plurals[0] = "=K053260##CC_GUI_COLOR_INSTR_K053260";
    strings["C140##CC_GUI_COLOR_INSTR_C140"].plurals[0] = "=C140##CC_GUI_COLOR_INSTR_C140";
    strings["C219##CC_GUI_COLOR_INSTR_C219"].plurals[0] = "=C219##CC_GUI_COLOR_INSTR_C219";
    strings["ESFM##CC_GUI_COLOR_INSTR_ESFM"].plurals[0] = "=ESFM##CC_GUI_COLOR_INSTR_ESFM";
    strings["ES5503##CC_GUI_COLOR_INSTR_ES5503"].plurals[0] = "=ES5503##CC_GUI_COLOR_INSTR_ES5503";
    strings["PowerNoise (noise)##CC_GUI_COLOR_INSTR_POWERNOISE"].plurals[0] = "=PowerNoise (noise)##CC_GUI_COLOR_INSTR_POWERNOISE";
    strings["PowerNoise (slope)##CC_GUI_COLOR_INSTR_POWERNOISE_SLOPE"].plurals[0] = "=PowerNoise (slope)##CC_GUI_COLOR_INSTR_POWERNOISE_SLOPE";
    strings["Other/Unknown##CC_GUI_COLOR_INSTR_UNKNOWN"].plurals[0] = "=Other/Unknown##CC_GUI_COLOR_INSTR_UNKNOWN";

    strings["Single color (background)##CC_GUI_COLOR_CHANNEL_BG"].plurals[0] = "=Single color (background)##CC_GUI_COLOR_CHANNEL_BG";
    strings["Single color (text)##CC_GUI_COLOR_CHANNEL_FG"].plurals[0] = "=Single color (text)##CC_GUI_COLOR_CHANNEL_FG";
    strings["FM##CC_GUI_COLOR_CHANNEL_FM"].plurals[0] = "=FM##CC_GUI_COLOR_CHANNEL_FM";
    strings["Pulse##CC_GUI_COLOR_CHANNEL_PULSE"].plurals[0] = "=Pulse##CC_GUI_COLOR_CHANNEL_PULSE";
    strings["Noise##CC_GUI_COLOR_CHANNEL_NOISE"].plurals[0] = "=Noise##CC_GUI_COLOR_CHANNEL_NOISE";
    strings["PCM##CC_GUI_COLOR_CHANNEL_PCM"].plurals[0] = "=PCM##CC_GUI_COLOR_CHANNEL_PCM";
    strings["Wave##CC_GUI_COLOR_CHANNEL_WAVE"].plurals[0] = "=Wave##CC_GUI_COLOR_CHANNEL_WAVE";
    strings["FM operator##CC_GUI_COLOR_CHANNEL_OP"].plurals[0] = "=FM operator##CC_GUI_COLOR_CHANNEL_OP";
    strings["Muted##CC_GUI_COLOR_CHANNEL_MUTED"].plurals[0] = "=Muted##CC_GUI_COLOR_CHANNEL_MUTED";

    strings["Playhead##CC_GUI_COLOR_PATTERN_PLAY_HEAD"].plurals[0] = "=Playhead##CC_GUI_COLOR_PATTERN_PLAY_HEAD";
    strings["Editing##CC_GUI_COLOR_EDITING"].plurals[0] = "=Editing##CC_GUI_COLOR_EDITING";
    strings["Editing (will clone)##CC_GUI_COLOR_EDITING_CLONE"].plurals[0] = "=Editing (will clone)##CC_GUI_COLOR_EDITING_CLONE";
    strings["Cursor##CC_GUI_COLOR_PATTERN_CURSOR"].plurals[0] = "=Cursor##CC_GUI_COLOR_PATTERN_CURSOR";
    strings["Cursor (hovered)##CC_GUI_COLOR_PATTERN_CURSOR_HOVER"].plurals[0] = "=Cursor (hovered)##CC_GUI_COLOR_PATTERN_CURSOR_HOVER";
    strings["Cursor (clicked)##CC_GUI_COLOR_PATTERN_CURSOR_ACTIVE"].plurals[0] = "=Cursor (clicked)##CC_GUI_COLOR_PATTERN_CURSOR_ACTIVE";
    strings["Selection##CC_GUI_COLOR_PATTERN_SELECTION"].plurals[0] = "=Selection##CC_GUI_COLOR_PATTERN_SELECTION";
    strings["Selection (hovered)##CC_GUI_COLOR_PATTERN_SELECTION_HOVER"].plurals[0] = "=Selection (hovered)##CC_GUI_COLOR_PATTERN_SELECTION_HOVER";
    strings["Selection (clicked)##CC_GUI_COLOR_PATTERN_SELECTION_ACTIVE"].plurals[0] = "=Selection (clicked)##CC_GUI_COLOR_PATTERN_SELECTION_ACTIVE";
    strings["Highlight 1##CC_GUI_COLOR_PATTERN_HI_1"].plurals[0] = "=Highlight 1##CC_GUI_COLOR_PATTERN_HI_1";
    strings["Highlight 2##CC_GUI_COLOR_PATTERN_HI_2"].plurals[0] = "=Highlight 2##CC_GUI_COLOR_PATTERN_HI_2";
    strings["Row number##CC_GUI_COLOR_PATTERN_ROW_INDEX"].plurals[0] = "=Row number##CC_GUI_COLOR_PATTERN_ROW_INDEX";
    strings["Row number (highlight 1)##CC_GUI_COLOR_PATTERN_ROW_INDEX_HI1"].plurals[0] = "=Row number (highlight 1)##CC_GUI_COLOR_PATTERN_ROW_INDEX_HI1";
    strings["Row number (highlight 2)##CC_GUI_COLOR_PATTERN_ROW_INDEX_HI2"].plurals[0] = "=Row number (highlight 2)##CC_GUI_COLOR_PATTERN_ROW_INDEX_HI2";
    strings["Note##CC_GUI_COLOR_PATTERN_ACTIVE"].plurals[0] = "=Note##CC_GUI_COLOR_PATTERN_ACTIVE";
    strings["Note (highlight 1)##CC_GUI_COLOR_PATTERN_ACTIVE_HI1"].plurals[0] = "=Note (highlight 1)##CC_GUI_COLOR_PATTERN_ACTIVE_HI1";
    strings["Note (highlight 2)##CC_GUI_COLOR_PATTERN_ACTIVE_HI2"].plurals[0] = "=Note (highlight 2)##CC_GUI_COLOR_PATTERN_ACTIVE_HI2";
    strings["Blank##CC_GUI_COLOR_PATTERN_INACTIVE"].plurals[0] = "=Blank##CC_GUI_COLOR_PATTERN_INACTIVE";
    strings["Blank (highlight 1)##CC_GUI_COLOR_PATTERN_INACTIVE_HI1"].plurals[0] = "=Blank (highlight 1)##CC_GUI_COLOR_PATTERN_INACTIVE_HI1";
    strings["Blank (highlight 2)##CC_GUI_COLOR_PATTERN_INACTIVE_HI2"].plurals[0] = "=Blank (highlight 2)##CC_GUI_COLOR_PATTERN_INACTIVE_HI2";
    strings["Instrument##CC_GUI_COLOR_PATTERN_INS"].plurals[0] = "=Instrument##CC_GUI_COLOR_PATTERN_INS";
    strings["Instrument (invalid type)##CC_GUI_COLOR_PATTERN_INS_WARN"].plurals[0] = "=Instrument (invalid type)##CC_GUI_COLOR_PATTERN_INS_WARN";
    strings["Instrument (out of range)##CC_GUI_COLOR_PATTERN_INS_ERROR"].plurals[0] = "=Instrument (out of range)##CC_GUI_COLOR_PATTERN_INS_ERROR";
    strings["Volume (0%)##CC_GUI_COLOR_PATTERN_VOLUME_MIN"].plurals[0] = "=Volume (0%)##CC_GUI_COLOR_PATTERN_VOLUME_MIN";
    strings["Volume (50%)##CC_GUI_COLOR_PATTERN_VOLUME_HALF"].plurals[0] = "=Volume (50%)##CC_GUI_COLOR_PATTERN_VOLUME_HALF";
    strings["Volume (100%)##CC_GUI_COLOR_PATTERN_VOLUME_MAX"].plurals[0] = "=Volume (100%)##CC_GUI_COLOR_PATTERN_VOLUME_MAX";
    strings["Invalid effect##CC_GUI_COLOR_PATTERN_EFFECT_INVALID"].plurals[0] = "=Invalid effect##CC_GUI_COLOR_PATTERN_EFFECT_INVALID";
    strings["Pitch effect##CC_GUI_COLOR_PATTERN_EFFECT_PITCH"].plurals[0] = "=Pitch effect##CC_GUI_COLOR_PATTERN_EFFECT_PITCH";
    strings["Volume effect##CC_GUI_COLOR_PATTERN_EFFECT_VOLUME"].plurals[0] = "=Volume effect##CC_GUI_COLOR_PATTERN_EFFECT_VOLUME";
    strings["Panning effect##CC_GUI_COLOR_PATTERN_EFFECT_PANNING"].plurals[0] = "=Panning effect##CC_GUI_COLOR_PATTERN_EFFECT_PANNING";
    strings["Song effect##CC_GUI_COLOR_PATTERN_EFFECT_SONG"].plurals[0] = "=Song effect##CC_GUI_COLOR_PATTERN_EFFECT_SONG";
    strings["Time effect##CC_GUI_COLOR_PATTERN_EFFECT_TIME"].plurals[0] = "=Time effect##CC_GUI_COLOR_PATTERN_EFFECT_TIME";
    strings["Speed effect##CC_GUI_COLOR_PATTERN_EFFECT_SPEED"].plurals[0] = "=Speed effect##CC_GUI_COLOR_PATTERN_EFFECT_SPEED";
    strings["Primary specific effect##CC_GUI_COLOR_PATTERN_EFFECT_SYS_PRIMARY"].plurals[0] = "=Primary specific effect##CC_GUI_COLOR_PATTERN_EFFECT_SYS_PRIMARY";
    strings["Secondary specific effect##CC_GUI_COLOR_PATTERN_EFFECT_SYS_SECONDARY"].plurals[0] = "=Secondary specific effect##CC_GUI_COLOR_PATTERN_EFFECT_SYS_SECONDARY";
    strings["Miscellaneous##CC_GUI_COLOR_PATTERN_EFFECT_MISC"].plurals[0] = "=Miscellaneous##CC_GUI_COLOR_PATTERN_EFFECT_MISC";
    strings["External command output##CC_GUI_COLOR_EE_VALUE"].plurals[0] = "=External command output##CC_GUI_COLOR_EE_VALUE";
    strings["Status: off/disabled##CC_GUI_COLOR_PATTERN_STATUS_OFF"].plurals[0] = "=Status: off/disabled##CC_GUI_COLOR_PATTERN_STATUS_OFF";
    strings["Status: off + macro rel##CC_GUI_COLOR_PATTERN_STATUS_REL"].plurals[0] = "=Status: off + macro rel##CC_GUI_COLOR_PATTERN_STATUS_REL";
    strings["Status: on + macro rel##CC_GUI_COLOR_PATTERN_STATUS_REL_ON"].plurals[0] = "=Status: on + macro rel##CC_GUI_COLOR_PATTERN_STATUS_REL_ON";
    strings["Status: on##CC_GUI_COLOR_PATTERN_STATUS_ON"].plurals[0] = "=Status: on##CC_GUI_COLOR_PATTERN_STATUS_ON";
    strings["Status: volume##CC_GUI_COLOR_PATTERN_STATUS_VOLUME"].plurals[0] = "=Status: volume##CC_GUI_COLOR_PATTERN_STATUS_VOLUME";
    strings["Status: pitch##CC_GUI_COLOR_PATTERN_STATUS_PITCH"].plurals[0] = "=Status: pitch##CC_GUI_COLOR_PATTERN_STATUS_PITCH";
    strings["Status: panning##CC_GUI_COLOR_PATTERN_STATUS_PANNING"].plurals[0] = "=Status: panning##CC_GUI_COLOR_PATTERN_STATUS_PANNING";
    strings["Status: chip (primary)##CC_GUI_COLOR_PATTERN_STATUS_SYS1"].plurals[0] = "=Status: chip (primary)##CC_GUI_COLOR_PATTERN_STATUS_SYS1";
    strings["Status: chip (secondary)##CC_GUI_COLOR_PATTERN_STATUS_SYS2"].plurals[0] = "=Status: chip (secondary)##CC_GUI_COLOR_PATTERN_STATUS_SYS2";
    strings["Status: mixing##CC_GUI_COLOR_PATTERN_STATUS_MIXING"].plurals[0] = "=Status: mixing##CC_GUI_COLOR_PATTERN_STATUS_MIXING";
    strings["Status: DSP effect##CC_GUI_COLOR_PATTERN_STATUS_DSP"].plurals[0] = "=Status: DSP effect##CC_GUI_COLOR_PATTERN_STATUS_DSP";
    strings["Status: note altering##CC_GUI_COLOR_PATTERN_STATUS_NOTE"].plurals[0] = "=Status: note altering##CC_GUI_COLOR_PATTERN_STATUS_NOTE";
    strings["Status: misc color 1##CC_GUI_COLOR_PATTERN_STATUS_MISC1"].plurals[0] = "=Status: misc color 1##CC_GUI_COLOR_PATTERN_STATUS_MISC1";
    strings["Status: misc color 2##CC_GUI_COLOR_PATTERN_STATUS_MISC2"].plurals[0] = "=Status: misc color 2##CC_GUI_COLOR_PATTERN_STATUS_MISC2";
    strings["Status: misc color 3##CC_GUI_COLOR_PATTERN_STATUS_MISC3"].plurals[0] = "=Status: misc color 3##CC_GUI_COLOR_PATTERN_STATUS_MISC3";
    strings["Status: attack##CC_GUI_COLOR_PATTERN_STATUS_ATTACK"].plurals[0] = "=Status: attack##CC_GUI_COLOR_PATTERN_STATUS_ATTACK";
    strings["Status: decay##CC_GUI_COLOR_PATTERN_STATUS_DECAY"].plurals[0] = "=Status: decay##CC_GUI_COLOR_PATTERN_STATUS_DECAY";
    strings["Status: sustain##CC_GUI_COLOR_PATTERN_STATUS_SUSTAIN"].plurals[0] = "=Status: sustain##CC_GUI_COLOR_PATTERN_STATUS_SUSTAIN";
    strings["Status: release##CC_GUI_COLOR_PATTERN_STATUS_RELEASE"].plurals[0] = "=Status: release##CC_GUI_COLOR_PATTERN_STATUS_RELEASE";
    strings["Status: decrease linear##CC_GUI_COLOR_PATTERN_STATUS_DEC_LINEAR"].plurals[0] = "=Status: decrease linear##CC_GUI_COLOR_PATTERN_STATUS_DEC_LINEAR";
    strings["Status: decrease exp##CC_GUI_COLOR_PATTERN_STATUS_DEC_EXP"].plurals[0] = "=Status: decrease exp##CC_GUI_COLOR_PATTERN_STATUS_DEC_EXP";
    strings["Status: increase##CC_GUI_COLOR_PATTERN_STATUS_INC"].plurals[0] = "=Status: increase##CC_GUI_COLOR_PATTERN_STATUS_INC";
    strings["Status: bent##CC_GUI_COLOR_PATTERN_STATUS_BENT"].plurals[0] = "=Status: bent##CC_GUI_COLOR_PATTERN_STATUS_BENT";
    strings["Status: direct##CC_GUI_COLOR_PATTERN_STATUS_DIRECT"].plurals[0] = "=Status: direct##CC_GUI_COLOR_PATTERN_STATUS_DIRECT";

    strings["Background##CC_GUI_COLOR_SAMPLE_BG"].plurals[0] = "=Background##CC_GUI_COLOR_SAMPLE_BG";
    strings["Waveform##CC_GUI_COLOR_SAMPLE_FG"].plurals[0] = "=Waveform##CC_GUI_COLOR_SAMPLE_FG";
    strings["Time background##CC_GUI_COLOR_SAMPLE_TIME_BG"].plurals[0] = "=Time background##CC_GUI_COLOR_SAMPLE_TIME_BG";
    strings["Time text##CC_GUI_COLOR_SAMPLE_TIME_FG"].plurals[0] = "=Time text##CC_GUI_COLOR_SAMPLE_TIME_FG";
    strings["Loop region##CC_GUI_COLOR_SAMPLE_LOOP"].plurals[0] = "=Loop region##CC_GUI_COLOR_SAMPLE_LOOP";
    strings["Center guide##CC_GUI_COLOR_SAMPLE_CENTER"].plurals[0] = "=Center guide##CC_GUI_COLOR_SAMPLE_CENTER";
    strings["Grid##CC_GUI_COLOR_SAMPLE_GRID"].plurals[0] = "=Grid##CC_GUI_COLOR_SAMPLE_GRID";
    strings["Selection##CC_GUI_COLOR_SAMPLE_SEL"].plurals[0] = "=Selection##CC_GUI_COLOR_SAMPLE_SEL";
    strings["Selection points##CC_GUI_COLOR_SAMPLE_SEL_POINT"].plurals[0] = "=Selection points##CC_GUI_COLOR_SAMPLE_SEL_POINT";
    strings["Preview needle##CC_GUI_COLOR_SAMPLE_NEEDLE"].plurals[0] = "=Preview needle##CC_GUI_COLOR_SAMPLE_NEEDLE";
    strings["Playing needles##CC_GUI_COLOR_SAMPLE_NEEDLE_PLAYING"].plurals[0] = "=Playing needles##CC_GUI_COLOR_SAMPLE_NEEDLE_PLAYING";
    strings["Loop markers##CC_GUI_COLOR_SAMPLE_LOOP_POINT"].plurals[0] = "=Loop markers##CC_GUI_COLOR_SAMPLE_LOOP_POINT";
    strings["Chip select: disabled##CC_GUI_COLOR_SAMPLE_CHIP_DISABLED"].plurals[0] = "=Chip select: disabled##CC_GUI_COLOR_SAMPLE_CHIP_DISABLED";
    strings["Chip select: enabled##CC_GUI_COLOR_SAMPLE_CHIP_ENABLED"].plurals[0] = "=Chip select: enabled##CC_GUI_COLOR_SAMPLE_CHIP_ENABLED";
    strings["Chip select: enabled (failure)##CC_GUI_COLOR_SAMPLE_CHIP_WARNING"].plurals[0] = "=Chip select: enabled (failure)##CC_GUI_COLOR_SAMPLE_CHIP_WARNING";

    strings["Unallocated##CC_GUI_COLOR_PAT_MANAGER_NULL"].plurals[0] = "=Unallocated##CC_GUI_COLOR_PAT_MANAGER_NULL";
    strings["Unused##CC_GUI_COLOR_PAT_MANAGER_UNUSED"].plurals[0] = "=Unused##CC_GUI_COLOR_PAT_MANAGER_UNUSED";
    strings["Used##CC_GUI_COLOR_PAT_MANAGER_USED"].plurals[0] = "=Used##CC_GUI_COLOR_PAT_MANAGER_USED";
    strings["Overused##CC_GUI_COLOR_PAT_MANAGER_OVERUSED"].plurals[0] = "=Overused##CC_GUI_COLOR_PAT_MANAGER_OVERUSED";
    strings["Really overused##CC_GUI_COLOR_PAT_MANAGER_EXTREMELY_OVERUSED"].plurals[0] = "=Really overused##CC_GUI_COLOR_PAT_MANAGER_EXTREMELY_OVERUSED";
    strings["Combo Breaker##CC_GUI_COLOR_PAT_MANAGER_COMBO_BREAKER"].plurals[0] = "=Combo Breaker##CC_GUI_COLOR_PAT_MANAGER_COMBO_BREAKER";

    strings["Background##CC_GUI_COLOR_PIANO_BACKGROUND"].plurals[0] = "=Background##CC_GUI_COLOR_PIANO_BACKGROUND";
    strings["Upper key##CC_GUI_COLOR_PIANO_KEY_TOP"].plurals[0] = "=Upper key##CC_GUI_COLOR_PIANO_KEY_TOP";
    strings["Upper key (feedback)##CC_GUI_COLOR_PIANO_KEY_TOP_HIT"].plurals[0] = "=Upper key (feedback)##CC_GUI_COLOR_PIANO_KEY_TOP_HIT";
    strings["Upper key (pressed)##CC_GUI_COLOR_PIANO_KEY_TOP_ACTIVE"].plurals[0] = "=Upper key (pressed)##CC_GUI_COLOR_PIANO_KEY_TOP_ACTIVE";
    strings["Lower key##CC_GUI_COLOR_PIANO_KEY_BOTTOM"].plurals[0] = "=Lower key##CC_GUI_COLOR_PIANO_KEY_BOTTOM";
    strings["Lower key (feedback)##CC_GUI_COLOR_PIANO_KEY_BOTTOM_HIT"].plurals[0] = "=Lower key (feedback)##CC_GUI_COLOR_PIANO_KEY_BOTTOM_HIT";
    strings["Lower key (pressed)##CC_GUI_COLOR_PIANO_KEY_BOTTOM_ACTIVE"].plurals[0] = "=Lower key (pressed)##CC_GUI_COLOR_PIANO_KEY_BOTTOM_ACTIVE";

    strings["Clock text##CC_GUI_COLOR_CLOCK_TEXT"].plurals[0] = "=Clock text##CC_GUI_COLOR_CLOCK_TEXT";
    strings["Beat (off)##CC_GUI_COLOR_CLOCK_BEAT_LOW"].plurals[0] = "=Beat (off)##CC_GUI_COLOR_CLOCK_BEAT_LOW";
    strings["Beat (on)##CC_GUI_COLOR_CLOCK_BEAT_HIGH"].plurals[0] = "=Beat (on)##CC_GUI_COLOR_CLOCK_BEAT_HIGH";

    strings["PortSet##CC_GUI_COLOR_PATCHBAY_PORTSET"].plurals[0] = "=PortSet##CC_GUI_COLOR_PATCHBAY_PORTSET";
    strings["Port##CC_GUI_COLOR_PATCHBAY_PORT"].plurals[0] = "=Port##CC_GUI_COLOR_PATCHBAY_PORT";
    strings["Port (hidden/unavailable)##CC_GUI_COLOR_PATCHBAY_PORT_HIDDEN"].plurals[0] = "=Port (hidden/unavailable)##CC_GUI_COLOR_PATCHBAY_PORT_HIDDEN";
    strings["Connection (selected)##CC_GUI_COLOR_PATCHBAY_CONNECTION"].plurals[0] = "=Connection (selected)##CC_GUI_COLOR_PATCHBAY_CONNECTION";
    strings["Connection (other)##CC_GUI_COLOR_PATCHBAY_CONNECTION_BG"].plurals[0] = "=Connection (other)##CC_GUI_COLOR_PATCHBAY_CONNECTION_BG";

    strings["Background##CC_GUI_COLOR_MEMORY_BG"].plurals[0] = "=Background##CC_GUI_COLOR_MEMORY_BG";
    strings["Unknown##CC_GUI_COLOR_MEMORY_FREE"].plurals[0] = "=Unknown##CC_GUI_COLOR_MEMORY_FREE";
    strings["Reserved##CC_GUI_COLOR_MEMORY_RESERVED"].plurals[0] = "=Reserved##CC_GUI_COLOR_MEMORY_RESERVED";
    strings["Sample##CC_GUI_COLOR_MEMORY_SAMPLE"].plurals[0] = "=Sample##CC_GUI_COLOR_MEMORY_SAMPLE";
    strings["Sample (alternate 1)##CC_GUI_COLOR_MEMORY_SAMPLE_ALT1"].plurals[0] = "=Sample (alternate 1)##CC_GUI_COLOR_MEMORY_SAMPLE_ALT1";
    strings["Sample (alternate 2)##CC_GUI_COLOR_MEMORY_SAMPLE_ALT2"].plurals[0] = "=Sample (alternate 2)##CC_GUI_COLOR_MEMORY_SAMPLE_ALT2";
    strings["Sample (alternate 3)##CC_GUI_COLOR_MEMORY_SAMPLE_ALT3"].plurals[0] = "=Sample (alternate 3)##CC_GUI_COLOR_MEMORY_SAMPLE_ALT3";
    strings["Wave RAM##CC_GUI_COLOR_MEMORY_WAVE_RAM"].plurals[0] = "=Wave RAM##CC_GUI_COLOR_MEMORY_WAVE_RAM";
    strings["Wavetable (static)##CC_GUI_COLOR_MEMORY_WAVE_STATIC"].plurals[0] = "=Wavetable (static)##CC_GUI_COLOR_MEMORY_WAVE_STATIC";
    strings["Echo buffer##CC_GUI_COLOR_MEMORY_ECHO"].plurals[0] = "=Echo buffer##CC_GUI_COLOR_MEMORY_ECHO";
    strings["Namco 163 load pos##CC_GUI_COLOR_MEMORY_N163_LOAD"].plurals[0] = "=Namco 163 play pos##CC_GUI_COLOR_MEMORY_N163_LOAD";
    strings["Namco 163 play pos##CC_GUI_COLOR_MEMORY_N163_PLAY"].plurals[0] = "=Namco 163 play pos##CC_GUI_COLOR_MEMORY_N163_PLAY";
    strings["Sample (bank 0)##CC_GUI_COLOR_MEMORY_BANK0"].plurals[0] = "=Sample (bank 0)##CC_GUI_COLOR_MEMORY_BANK0";
    strings["Sample (bank 1)##CC_GUI_COLOR_MEMORY_BANK1"].plurals[0] = "=Sample (bank 1)##CC_GUI_COLOR_MEMORY_BANK1";
    strings["Sample (bank 2)##CC_GUI_COLOR_MEMORY_BANK2"].plurals[0] = "=Sample (bank 2)##CC_GUI_COLOR_MEMORY_BANK2";
    strings["Sample (bank 3)##CC_GUI_COLOR_MEMORY_BANK3"].plurals[0] = "=Sample (bank 3)##CC_GUI_COLOR_MEMORY_BANK3";
    strings["Sample (bank 4)##CC_GUI_COLOR_MEMORY_BANK4"].plurals[0] = "=Sample (bank 4)##CC_GUI_COLOR_MEMORY_BANK4";
    strings["Sample (bank 5)##CC_GUI_COLOR_MEMORY_BANK5"].plurals[0] = "=Sample (bank 5)##CC_GUI_COLOR_MEMORY_BANK5";
    strings["Sample (bank 6)##CC_GUI_COLOR_MEMORY_BANK6"].plurals[0] = "=Sample (bank 6)##CC_GUI_COLOR_MEMORY_BANK6";
    strings["Sample (bank 7)##CC_GUI_COLOR_MEMORY_BANK7"].plurals[0] = "=Sample (bank 7)##CC_GUI_COLOR_MEMORY_BANK7";

    strings["Log level: Error##CC_GUI_COLOR_LOGLEVEL_ERROR"].plurals[0] = "=Log level: Error##CC_GUI_COLOR_LOGLEVEL_ERROR";
    strings["Log level: Warning##CC_GUI_COLOR_LOGLEVEL_WARNING"].plurals[0] = "=Log level: Warning##CC_GUI_COLOR_LOGLEVEL_WARNING";
    strings["Log level: Info##CC_GUI_COLOR_LOGLEVEL_INFO"].plurals[0] = "=Log level: Info##CC_GUI_COLOR_LOGLEVEL_INFO";
    strings["Log level: Debug##CC_GUI_COLOR_LOGLEVEL_DEBUG"].plurals[0] = "=Log level: Debug##CC_GUI_COLOR_LOGLEVEL_DEBUG";
    strings["Log level: Trace/Verbose##CC_GUI_COLOR_LOGLEVEL_TRACE"].plurals[0] = "=Log level: Trace/Verbose##CC_GUI_COLOR_LOGLEVEL_TRACE";

    strings["OK##SettingsOK"].plurals[0] = "=OK##SettingsOK";
    strings["Cancel##SettingsCancel"].plurals[0] = "=Cancel##SettingsCancel";
    strings["Apply##SettingsApply"].plurals[0] = "=Apply##SettingsApply";

    //   sgut  src/gui/util.cpp
    strings["<nothing>##sgut"].plurals[0] = "=<nothing>";
    strings["Unknown##sgut0"].plurals[0] = "=Unknown";
    strings["Unknown##sgut1"].plurals[0] = "=Unknown";

    // instruments
    //      icon   is the letter icon for the instrument

    //   sgi**     src/gui/inst/
    //   sgiPCMA   src/gui/inst/adpcma.cpp
    //   sgiPCMB   src/gui/inst/adpcmb.cpp
    //   sgiSAMPLE src/gui/inst/amiga.cpp
    //   sgiAY     src/gui/inst/ay.cpp
    //   sgi8930   src/gui/inst/ay8930.cpp
    //   sgiB      src/gui/inst/beeper.cpp
    //   sgiC140   src/gui/inst/c140.cpp
    //   sgiC219   src/gui/inst/c219.cpp
    //   sgiC64    src/gui/inst/c64.cpp
    //   sgiDAVE   src/gui/inst/dave.cpp
    //   sgi5503   src/gui/inst/es5503.cpp
    //   sgiOTTO   src/gui/inst/es5506.cpp
    //   sgiESFM   src/gui/inst/esfm.cpp
    //   sgiFDS    src/gui/inst/fds.cpp
    //   sgifmeu   src/gui/inst/fmEnvUtil.cpp
    //   sgifmeh   src/gui/inst/fmEnvUtil.h
    //   sgiGA20   src/gui/inst/ga20.cpp
    //   sgiGB     src/gui/inst/gb.cpp
    //   sgiGBADMA src/gui/inst/gbadma.cpp
    //sgiGBAMINMOD src/gui/inst/gbaminmod.cpp
    //   sgiK00    src/gui/inst/k007232.cpp
    //   sgiK05    src/gui/inst/k053260.cpp
    //   sgimcd    src/gui/inst/macroDraw.cpp
    //   sgimcdu   src/gui/inst/macroDrawUtil.cpp
    //   sgiLYNX   src/gui/inst/mikey.cpp
    //   sgi5232   src/gui/inst/msm5232.cpp
    //   sgi6258   src/gui/inst/msm6258.cpp
    //   sgi6295   src/gui/inst/msm6295.cpp
    //   sgiMULPCM src/gui/inst/multipcm.cpp
    //   sgiN163   src/gui/inst/n163.cpp
    //   sgiWSG    src/gui/inst/namco.cpp
    //   sgiNDS    src/gui/inst/nds.cpp
    //   sgiNES    src/gui/inst/nes.cpp
    //   sgiOPL    src/gui/inst/opl.cpp
    //   sgiOPLL   src/gui/inst/opll.cpp
    //   sgiOPM    src/gui/inst/opm.cpp
    //   sgiOPN    src/gui/inst/opn.cpp
    //   sgiOPZ    src/gui/inst/opz.cpp
    //   sgiPCE    src/gui/inst/pce.cpp
    //   sgiPET    src/gui/inst/pet.cpp
    //   sgiPMQT   src/gui/inst/pokemini.cpp
    //   sgiPOKEY  src/gui/inst/pokey.cpp
    //   sgiPNN    src/gui/inst/powernoise.cpp
    //   sgiPNS    src/gui/inst/powernoise_slope.cpp
    //   sgiPV     src/gui/inst/pv1000.cpp
    //   sgiQ      src/gui/inst/qsound.cpp
    //   sgiRF5    src/gui/inst/rf5c68.cpp
    //   sgiSAA    src/gui/inst/saa1099.cpp
    //   sgismpd   src/gui/inst/sampleDraw.cpp
    //   sgiSCC    src/gui/inst/scc.cpp
    //   sgiSEGA   src/gui/inst/segapcm.cpp
    //   sgiSID2   src/gui/inst/sid2.cpp
    //   sgiSM     src/gui/inst/sm8521.cpp
    //   sgiSNES   src/gui/inst/snes.cpp
    //   sgiPSG    src/gui/inst/std.cpp
    //   sgistru   src/gui/inst/stringsUtil.cpp
    //   sgiSU     src/gui/inst/su.cpp
    //   sgiSWAN   src/gui/inst/swan.cpp
    //   sgiT6W    src/gui/inst/t6w28.cpp
    //   sgiTED    src/gui/inst/ted.cpp
    //   sgiTIA    src/gui/inst/tia.cpp
    //   sgiVB     src/gui/inst/vboy.cpp
    //   sgiVERA   src/gui/inst/vera.cpp
    //   sgiVIC    src/gui/inst/vic.cpp
    //   sgiVRC6   src/gui/inst/vrc6.cpp
    //   sgiVRC6S  src/gui/inst/vrc6saw.cpp
    //   sgiwave   src/gui/inst/wavetable.cpp
    //   sgiX1     src/gui/inst/x1_010.cpp
    //   sgiYMZ    src/gui/inst/ymz280b.cpp

    //   sgiPCMA  src/gui/inst/adpcma.cpp

    strings["Macros##sgiPCMA"].plurals[0] = "=Macros";
    strings["Volume##sgiPCMA"].plurals[0] = "=Volume";
    strings["Global Volume##sgiPCMA"].plurals[0] = "=Global Volume";
    strings["Panning##sgiPCMA"].plurals[0] = "=Panning";
    strings["Phase Reset##sgiPCMA"].plurals[0] = "=Phase Reset";

    //   sgiPCMB   src/gui/inst/adpcmb.cpp

    strings["Macros##sgiPCMB"].plurals[0] = "=Macros";
    strings["Volume##sgiPCMB"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiPCMB"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiPCMB"].plurals[0] = "=Pitch";
    strings["Panning##sgiPCMB"].plurals[0] = "=Panning";
    strings["Phase Reset##sgiPCMB"].plurals[0] = "=Phase Reset";

    //   sgiSAMPLE src/gui/inst/amiga.cpp

    strings["Macros##sgiSAMPLE"].plurals[0] = "=Macros";
    strings["Volume##sgiSAMPLE"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiSAMPLE"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiSAMPLE"].plurals[0] = "=Pitch";
    strings["Panning##sgiSAMPLE"].plurals[0] = "=Panning";
    strings["Panning (left)##sgiSAMPLE"].plurals[0] = "=Panning (left)";
    strings["Surround##sgiSAMPLE"].plurals[0] = "=Surround";
    strings["Panning (right)##sgiSAMPLE"].plurals[0] = "=Panning (right)";
    strings["Waveform##sgiSAMPLE"].plurals[0] = "=Waveform";
    strings["Phase Reset##sgiSAMPLE"].plurals[0] = "=Phase Reset";

    //   sgiAY     src/gui/inst/ay.cpp

    strings["Macros##sgiAY"].plurals[0] = "=Macros";
    strings["Volume##sgiAY"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiAY"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiAY"].plurals[0] = "=Pitch";
    strings["Noise Freq##sgiAY"].plurals[0] = "=Noise Freq";
    strings["Waveform##sgiAY"].plurals[0] = "=Waveform";
    strings["Raw Period##sgiAY"].plurals[0] = "=Raw Period";
    strings["Raw Envelope Period##sgiAY"].plurals[0] = "=Raw Envelope Period";
    strings["Phase Reset##sgiAY"].plurals[0] = "=Phase Reset";
    strings["Envelope##sgiAY"].plurals[0] = "=Envelope";
    strings["AutoEnv Num##sgiAY"].plurals[0] = "=AutoEnv Num";
    strings["AutoEnv Den##sgiAY"].plurals[0] = "=AutoEnv Den";

    //   sgi8930   src/gui/inst/ay8930.cpp

    strings["Macros##sgi8930"].plurals[0] = "=Macros";
    strings["Volume##sgi8930"].plurals[0] = "=Volume";
    strings["Arpeggio##sgi8930"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgi8930"].plurals[0] = "=Pitch";
    strings["Noise Freq##sgi8930"].plurals[0] = "=Noise Freq";
    strings["Waveform##sgi8930"].plurals[0] = "=Waveform";
    strings["Raw Period##sgi8930"].plurals[0] = "=Raw Period";
    strings["Raw Envelope Period##sgi8930"].plurals[0] = "=Raw Envelope Period";
    strings["Phase Reset##sgi8930"].plurals[0] = "=Phase Reset";
    strings["Duty##sgi8930"].plurals[0] = "=Duty";
    strings["Envelope##sgi8930"].plurals[0] = "=Envelope";
    strings["AutoEnv Num##sgi8930"].plurals[0] = "=AutoEnv Num";
    strings["AutoEnv Den##sgi8930"].plurals[0] = "=AutoEnv Den";
    strings["Noise AND Mask##sgi8930"].plurals[0] = "=Noise AND Mask";
    strings["Noise OR Mask##sgi8930"].plurals[0] = "=Noise OR Mask";

    //   sgiB      src/gui/inst/beeper.cpp

    strings["Macros##sgiB"].plurals[0] = "=Macros";
    strings["Volume##sgiB"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiB"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiB"].plurals[0] = "=Pitch";
    strings["Pulse Width##sgiB"].plurals[0] = "=Pulse Width";

    //   sgiC140   src/gui/inst/c140.cpp

    strings["Macros##sgiC140"].plurals[0] = "=Macros";
    strings["Volume##sgiC140"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiC140"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiC140"].plurals[0] = "=Pitch";
    strings["Panning (left)##sgiC140"].plurals[0] = "=Panning (left)";
    strings["Panning (right)##sgiC140"].plurals[0] = "=Panning (right)";
    strings["Phase Reset##sgiC140"].plurals[0] = "=Phase Reset";

    //   sgiC219   src/gui/inst/c219.cpp

    strings["Macros##sgiC219"].plurals[0] = "=Macros";
    strings["Volume##sgiC219"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiC219"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiC219"].plurals[0] = "=Pitch";
    strings["Control##sgiC219"].plurals[0] = "=Control";
    strings["Panning (left)##sgiC219"].plurals[0] = "=Panning (left)";
    strings["Panning (right)##sgiC219"].plurals[0] = "=Panning (right)";
    strings["Phase Reset##sgiC219"].plurals[0] = "=Phase Reset";

    //   sgiC64    src/gui/inst/c64.cpp

    strings["Waveform##sgiC640"].plurals[0] = "=Waveform";
    strings["tri##sgiC64"].plurals[0] = "=tri";
    strings["saw##sgiC64"].plurals[0] = "=saw";
    strings["pulse##sgiC64"].plurals[0] = "=pulse";
    strings["noise##sgiC64"].plurals[0] = "=noise";
    strings["A##sgiC640"].plurals[0] = "=A";
    strings["A##sgiC641"].plurals[0] = "=A";
    strings["D##sgiC640"].plurals[0] = "=D";
    strings["D##sgiC641"].plurals[0] = "=D";
    strings["S##sgiC640"].plurals[0] = "=S";
    strings["S##sgiC641"].plurals[0] = "=S";
    strings["R##sgiC640"].plurals[0] = "=R";
    strings["R##sgiC641"].plurals[0] = "=R";
    strings["Envelope##sgiC640"].plurals[0] = "=Envelope";
    strings["Envelope##sgiC641"].plurals[0] = "=Envelope";
    strings["Duty##sgiC640"].plurals[0] = "=Duty";
    strings["Ring Modulation##sgiC64"].plurals[0] = "=Ring Modulation";
    strings["Oscillator Sync##sgiC64"].plurals[0] = "=Oscillator Sync";
    strings["Enable filter##sgiC64"].plurals[0] = "=Enable filter";
    strings["Initialize filter##sgiC64"].plurals[0] = "=Initialize filter";
    strings["Cutoff##sgiC640"].plurals[0] = "=Cutoff";
    strings["Resonance##sgiC640"].plurals[0] = "=Resonance";
    strings["Filter Mode##sgiC640"].plurals[0] = "=Filter Mode";
    strings["low##sgiC64"].plurals[0] = "=low";
    strings["band##sgiC64"].plurals[0] = "=band";
    strings["high##sgiC64"].plurals[0] = "=high";
    strings["ch3off##sgiC64"].plurals[0] = "=ch3off";
    strings["Absolute Cutoff Macro##sgiC64"].plurals[0] = "=Absolute Cutoff Macro";
    strings["Absolute Duty Macro##sgiC64"].plurals[0] = "=Absolute Duty Macro";
    strings["Don't test before new note##sgiC64"].plurals[0] = "=Don't test before new note";
    strings["Macros##sgiC64"].plurals[0] = "=Macros";
    strings["Volume##sgiC64"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiC64"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiC64"].plurals[0] = "=Pitch";
    strings["Duty##sgiC641"].plurals[0] = "=Duty";
    strings["Waveform##sgiC641"].plurals[0] = "=Waveform";
    strings["Cutoff##sgiC641"].plurals[0] = "=Cutoff";
    strings["Filter Mode##sgiC641"].plurals[0] = "=Filter Mode";
    strings["Filter Toggle##sgiC64"].plurals[0] = "=Filter Toggle";
    strings["Resonance##sgiC641"].plurals[0] = "=Resonance";
    strings["Special##sgiC64"].plurals[0] = "=Special";
    strings["Attack##sgiC64"].plurals[0] = "=Attack";
    strings["Decay##sgiC64"].plurals[0] = "=Decay";
    strings["Sustain##sgiC64"].plurals[0] = "=Sustain";
    strings["Release##sgiC64"].plurals[0] = "=Release";

    //   sgiDAVE   src/gui/inst/dave.cpp

    strings["Macros##sgiDAVE"].plurals[0] = "=Macros";
    strings["Volume##sgiDAVE"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiDAVE"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiDAVE"].plurals[0] = "=Pitch";
    strings["Noise Freq##sgiDAVE"].plurals[0] = "=Noise Freq";
    strings["Waveform##sgiDAVE"].plurals[0] = "=Waveform";
    strings["Panning (left)##sgiDAVE"].plurals[0] = "=Panning (left)";
    strings["Panning (right)##sgiDAVE"].plurals[0] = "=Panning (right)";
    strings["Phase Reset##sgiDAVE"].plurals[0] = "=Phase Reset";
    strings["Control##sgiDAVE"].plurals[0] = "=Control";
    strings["Raw Frequency##sgiDAVE"].plurals[0] = "=Raw Frequency";

    //   sgi5503   src/gui/inst/es5503.cpp

    strings["Oscillator mode:##sgi5503"].plurals[0] = "=Oscillator mode:";
    strings["Freerun##sgi5503"].plurals[0] = "=Freerun";
    strings["Oneshot##sgi5503"].plurals[0] = "=Oneshot";
    strings["Sync/AM##sgi5503"].plurals[0] = "=Sync/AM";
    strings["Swap##sgi5503"].plurals[0] = "=Swap";
    strings["Virtual softpan channel##sgi5503"].plurals[0] = "=Virtual softpan channel";
    strings["Combines odd and next even channel into one virtual channel with 256-step panning.\nInstrument, volume and effects need to be placed on the odd channel (e.g. 1st, 3rd, 5th etc.)##sgi5503"].plurals[0] = "=Combines odd and next even channel into one virtual channel with 256-step panning.\nInstrument, volume and effects need to be placed on the odd channel (e.g. 1st, 3rd, 5th etc.)";
    strings["Phase reset on key-on##sgi5503"].plurals[0] = "=Phase reset on key-on";
    strings["Macros##sgi5503"].plurals[0] = "=Macros";
    strings["Volume##sgi5503"].plurals[0] = "=Volume";
    strings["Arpeggio##sgi5503"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgi5503"].plurals[0] = "=Pitch";
    strings["Osc. mode##sgi5503"].plurals[0] = "=Osc. mode";
    strings["Panning (left)##sgi5503"].plurals[0] = "=Panning (left)";
    strings["Panning (right)##sgi5503"].plurals[0] = "=Panning (right)";
    strings["Waveform##sgi5503"].plurals[0] = "=Waveform";
    strings["Phase Reset##sgi5503"].plurals[0] = "=Phase Reset";
    strings["Wave/sample pos.##sgi5503"].plurals[0] = "=Wave/sample pos.";
    strings["Osc. output##sgi5503"].plurals[0] = "=Osc. output";

    //   sgiOTTO   src/gui/inst/es5506.cpp

    strings["Filter Mode##sgiOTTO0"].plurals[0] = "=Filter Mode";
    strings["Filter K1##sgiOTTO0"].plurals[0] = "=Filter K1";
    strings["Filter K2##sgiOTTO0"].plurals[0] = "=Filter K2";
    strings["Envelope length##sgiOTTO"].plurals[0] = "=Envelope length";
    strings["Envelope count##sgiOTTO"].plurals[0] = "=Envelope count";
    strings["Left Volume Ramp##sgiOTTO"].plurals[0] = "=Left Volume Ramp";
    strings["Right Volume Ramp##sgiOTTO"].plurals[0] = "=Right Volume Ramp";
    strings["Filter K1 Ramp##sgiOTTO"].plurals[0] = "=Filter K1 Ramp";
    strings["Filter K2 Ramp##sgiOTTO"].plurals[0] = "=Filter K2 Ramp";
    strings["K1 Ramp Slowdown##sgiOTTO"].plurals[0] = "=K1 Ramp Slowdown";
    strings["K2 Ramp Slowdown##sgiOTTO"].plurals[0] = "=K2 Ramp Slowdown";
    strings["Macros##sgiOTTO"].plurals[0] = "=Macros";
    strings["Volume##sgiOTTO"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiOTTO"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiOTTO"].plurals[0] = "=Pitch";
    strings["Panning (left)##sgiOTTO"].plurals[0] = "=Panning (left)";
    strings["Panning (right)##sgiOTTO"].plurals[0] = "=Panning (right)";
    strings["Phase Reset##sgiOTTO"].plurals[0] = "=Phase Reset";
    strings["Filter Mode##sgiOTTO1"].plurals[0] = "=Filter Mode";
    strings["Filter K1##sgiOTTO1"].plurals[0] = "=Filter K1";
    strings["Filter K2##sgiOTTO1"].plurals[0] = "=Filter K2";
    strings["Outputs##sgiOTTO"].plurals[0] = "=Outputs";
    strings["Control##sgiOTTO"].plurals[0] = "=Control";

    //   sgiESFM   src/gui/inst/esfm.cpp

    strings["Other##sgiESFM0"].plurals[0] = "=Other";
    strings["Other##sgiESFM1"].plurals[0] = "=Other";
    strings["Envelope##sgiESFM0"].plurals[0] = "=Envelope";
    strings["Envelope##sgiESFM1"].plurals[0] = "=Envelope";
    strings["op%d##sgiESFM0"].plurals[0] = "=op%d";
    strings["OP%d##sgiESFM1"].plurals[0] = "=OP%d";
    strings["Detune in semitones##sgiESFM0"].plurals[0] = "=Detune in semitones";
    strings["Detune in fractions of semitone.\n128 = +1 semitone, -128 = -1 semitone.##sgiESFM0"].plurals[0] = "=Detune in fractions of semitone.\n128 = +1 semitone, -128 = -1 semitone.";
    strings["If operator outputs sound, enable left channel output.##sgiESFM0"].plurals[0] = "=If operator outputs sound, enable left channel output.";
    strings["If operator outputs sound, enable right channel output.##sgiESFM0"].plurals[0] = "=If operator outputs sound, enable right channel output.";
    strings["Block##sgiESFM0"].plurals[0] = "=Block";
    strings["FreqNum##sgiESFM0"].plurals[0] = "=FreqNum";
    strings["op%d##sgiESFM2"].plurals[0] = "=op%d";
    strings["Operator %d##sgiESFM"].plurals[0] = "=Operator %d";
    strings["Waveform##sgiESFM"].plurals[0] = "=Waveform";
    strings["Envelope##sgiESFM"].plurals[0] = "=Envelope";
    strings["Blk##sgiESFM"].plurals[0] = "=Blk";
    strings["Block##sgiESFM1"].plurals[0] = "=Block";
    strings["F##sgiESFM"].plurals[0] = "=F";
    strings["Frequency (F-Num)##sgiESFM"].plurals[0] = "=Frequency (F-Num)";
    strings["Detune in semitones##sgiESFM1"].plurals[0] = "=Detune in semitones";
    strings["Detune in fractions of semitone.\n128 = +1 semitone, -128 = -1 semitone.##sgiESFM1"].plurals[0] = "=Detune in fractions of semitone.\n128 = +1 semitone, -128 = -1 semitone.";
    strings["If operator outputs sound, enable left channel output.##sgiESFM1"].plurals[0] = "=If operator outputs sound, enable left channel output.";
    strings["If operator outputs sound, enable right channel output.##sgiESFM1"].plurals[0] = "=If operator outputs sound, enable right channel output.";
    strings["op%d##sgiESFM3"].plurals[0] = "=op%d";
    strings["OP%d##sgiESFM4"].plurals[0] = "=OP%d";
    strings["Block##sgiESFM2"].plurals[0] = "=Block";
    strings["FreqNum##sgiESFM1"].plurals[0] = "=FreqNum";
    strings["Detune in semitones##sgiESFM2"].plurals[0] = "=Detune in semitones";
    strings["Detune in fractions of semitone.\n128 = +1 semitone, -128 = -1 semitone.##sgiESFM2"].plurals[0] = "=Detune in fractions of semitone.\n128 = +1 semitone, -128 = -1 semitone.";
    strings["If operator outputs sound, enable left channel output.##sgiESFM2"].plurals[0] = "=If operator outputs sound, enable left channel output.";
    strings["If operator outputs sound, enable right channel output.##sgiESFM2"].plurals[0] = "=If operator outputs sound, enable right channel output.";
    strings["OP%d Macros##sgiESFM"].plurals[0] = "=OP%d Macros";
    strings["Block##sgiESFM3"].plurals[0] = "=Block";
    strings["FreqNum##sgiESFM2"].plurals[0] = "=FreqNum";
    strings["Op. Arpeggio##sgiESFM"].plurals[0] = "=Op. Arpeggio";
    strings["Op. Pitch##sgiESFM"].plurals[0] = "=Op. Pitch";
    strings["Op. Panning##sgiESFM"].plurals[0] = "=Op. Panning";
    strings["Macros##sgiESFM"].plurals[0] = "=Macros";
    strings["Volume##sgiESFM"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiESFM"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiESFM"].plurals[0] = "=Pitch";
    strings["OP4 Noise Mode##sgiESFM"].plurals[0] = "=OP4 Noise Mode";
    strings["Panning##sgiESFM"].plurals[0] = "=Panning";
    strings["Phase Reset##sgiESFM"].plurals[0] = "=Phase Reset";

    //   sgiFDS    src/gui/inst/fds.cpp

    strings["Compatibility mode##sgiFDS"].plurals[0] = "=Compatibility mode";
    strings["only use for compatibility with .dmf modules!\n- initializes modulation table with first wavetable\n- does not alter modulation parameters on instrument change##sgiFDS"].plurals[0] = "=only use for compatibility with .dmf modules!\n- initializes modulation table with first wavetable\n- does not alter modulation parameters on instrument change";
    strings["Modulation depth##sgiFDS"].plurals[0] = "=Modulation depth";
    strings["Modulation speed##sgiFDS"].plurals[0] = "=Modulation speed";
    strings["Modulation table##sgiFDS"].plurals[0] = "=Modulation table";
    strings["Macros##sgiFDS"].plurals[0] = "=Macros";
    strings["Volume##sgiFDS"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiFDS"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiFDS"].plurals[0] = "=Pitch";
    strings["Waveform##sgiFDS"].plurals[0] = "=Waveform";
    strings["Mod Depth##sgiFDS"].plurals[0] = "=Mod Depth";
    strings["Mod Speed##sgiFDS"].plurals[0] = "=Mod Speed";
    strings["Mod Position##sgiFDS"].plurals[0] = "=Mod Position";

    //   sgifmeu   src/gui/inst/fmEnvUtil.cpp

    strings["left click to restart\nmiddle click to pause\nright click to see algorithm##sgifmeu"].plurals[0] = "=left click to restart\nmiddle click to pause\nright click to see algorithm";
    strings["left click to configure TL scaling\nright click to see FM preview##sgifmeu"].plurals[0] = "=left click to configure TL scaling\nright click to see FM preview";
    strings["right click to see FM preview##sgifmeu"].plurals[0] = "=right click to see FM preview";
    strings["operator level changes with volume?##sgifmeu"].plurals[0] = "=operator level changes with volume?";
    strings["AUTO##OPKVS"].plurals[0] = "=AUTO##OPKVS";
    strings["NO##OPKVS"].plurals[0] = "=NO##OPKVS";
    strings["YES##OPKVS"].plurals[0] = "=YES##OPKVS";

    //   sgifmeh   src/gui/inst/fmEnvUtil.h

    strings["(copying)##sgifmeh"].plurals[0] = "=(copying)";
    strings["(swapping)##sgifmeh"].plurals[0] = "=(swapping)";
    strings["- drag to swap operator\n- shift-drag to copy operator##sgifmeh"].plurals[0] = "=- drag to swap operator\n- shift-drag to copy operator";

    //   sgiGA20   src/gui/inst/ga20.cpp

    strings["Macros##sgiGA20"].plurals[0] = "=Macros";
    strings["Volume##sgiGA20"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiGA20"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiGA20"].plurals[0] = "=Pitch";
    strings["Phase Reset##sgiGA20"].plurals[0] = "=Phase Reset";

    //   sgiGB     src/gui/inst/gb.cpp

    strings["Game Boy##sgiGB"].plurals[0] = "=Game Boy";
    strings["Use software envelope##sgiGB"].plurals[0] = "=Use software envelope";
    strings["Initialize envelope on every note##sgiGB"].plurals[0] = "=Initialize envelope on every note";
    strings["Volume##sgiGB0"].plurals[0] = "=Volume";
    strings["Length##sgiGB"].plurals[0] = "=Length";
    strings["Sound Length##sgiGB0"].plurals[0] = "=Sound Length";
    strings["Infinity##sgiGB"].plurals[0] = "=Infinity";
    strings["Direction##sgiGB"].plurals[0] = "=Direction";
    strings["Up##sgiGB0"].plurals[0] = "=Up";
    strings["Down##sgiGB0"].plurals[0] = "=Down";
    strings["Hardware Sequence##sgiGB"].plurals[0] = "=Hardware Sequence";
    strings["Tick##sgiGB"].plurals[0] = "=Tick";
    strings["Command##sgiGB"].plurals[0] = "=Command";
    strings["Move/Remove##sgiGB"].plurals[0] = "=Move/Remove";
    strings["Volume##sgiGB1"].plurals[0] = "=Volume";
    strings["Env Length##sgiGB"].plurals[0] = "=Env Length";
    strings["Sound Length##sgiGB1"].plurals[0] = "=Sound Length";
    strings["Up##sgiGB1"].plurals[0] = "=Up";
    strings["Down##sgiGB1"].plurals[0] = "=Down";
    strings["Shift##sgiGB"].plurals[0] = "=Shift";
    strings["Speed##sgiGB"].plurals[0] = "=Speed";
    strings["Up##sgiGB2"].plurals[0] = "=Up";
    strings["Down##sgiGB2"].plurals[0] = "=Down";
    strings["Ticks##sgiGB"].plurals[0] = "=Ticks";
    strings["Position##sgiGB"].plurals[0] = "=Position";
    strings["Macros##sgiGB"].plurals[0] = "=Macros";
    strings["Volume##sgiGB2"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiGB"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiGB"].plurals[0] = "=Pitch";
    strings["Duty/Noise##sgiGB"].plurals[0] = "=Duty/Noise";
    strings["Waveform##sgiGB"].plurals[0] = "=Waveform";
    strings["Panning##sgiGB"].plurals[0] = "=Panning";
    strings["Phase Reset##sgiGB"].plurals[0] = "=Phase Reset";

    //   sgiGBADMA src/gui/inst/gbadma.cpp

    strings["Macros##sgiGBADMA"].plurals[0] = "=Macros";
    strings["Volume##sgiGBADMA"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiGBADMA"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiGBADMA"].plurals[0] = "=Pitch";
    strings["Waveform##sgiGBADMA"].plurals[0] = "=Waveform";
    strings["Panning##sgiGBADMA"].plurals[0] = "=Panning";
    strings["Phase Reset##sgiGBADMA"].plurals[0] = "=Phase Reset";

    //sgiGBAMINMOD src/gui/inst/gbaminmod.cpp

    strings["Macros##sgiGBAMINMOD"].plurals[0] = "=Macros";
    strings["Volume##sgiGBAMINMOD"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiGBAMINMOD"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiGBAMINMOD"].plurals[0] = "=Pitch";
    strings["Waveform##sgiGBAMINMOD"].plurals[0] = "=Waveform";
    strings["Panning (left)##sgiGBAMINMOD"].plurals[0] = "=Panning (left)";
    strings["Panning (right)##sgiGBAMINMOD"].plurals[0] = "=Panning (right)";
    strings["Special##sgiGBAMINMOD"].plurals[0] = "=Special";
    strings["Phase Reset##sgiGBAMINMOD"].plurals[0] = "=Phase Reset";

    //   sgiK00    src/gui/inst/k007232.cpp

    strings["Macros##sgiK00"].plurals[0] = "=Macros";
    strings["Volume##sgiK00"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiK00"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiK00"].plurals[0] = "=Pitch";
    strings["Waveform##sgiK00"].plurals[0] = "=Waveform";
    strings["Panning (left)##sgiK00"].plurals[0] = "=Panning (left)";
    strings["Panning (right)##sgiK00"].plurals[0] = "=Panning (right)";
    strings["Phase Reset##sgiK00"].plurals[0] = "=Phase Reset";

    //   sgiK05    src/gui/inst/k053260.cpp

    strings["Macros##sgiK05"].plurals[0] = "=Macros";
    strings["Volume##sgiK05"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiK05"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiK05"].plurals[0] = "=Pitch";
    strings["Panning##sgiK05"].plurals[0] = "=Panning";
    strings["Phase Reset##sgiK05"].plurals[0] = "=Phase Reset";

    //   sgimcd    src/gui/inst/macroDraw.cpp

    strings["Triangle##sgimcd"].plurals[0] = "=Triangle";
    strings["Saw##sgimcd"].plurals[0] = "=Saw";
    strings["Square##sgimcd"].plurals[0] = "=Square";
    strings["How did you even##sgimcd0"].plurals[0] = "=How did you even";
    strings["Bottom##sgimcd0"].plurals[0] = "=Bottom";
    strings["Top##sgimcd0"].plurals[0] = "=Top";
    strings["Attack##sgimcd"].plurals[0] = "=Attack";
    strings["Sustain##sgimcd"].plurals[0] = "=Sustain";
    strings["Hold##sgimcd"].plurals[0] = "=Hold";
    strings["SusTime##sgimcd"].plurals[0] = "=SusTime";
    strings["Decay##sgimcd"].plurals[0] = "=Decay";
    strings["SusDecay##sgimcd"].plurals[0] = "=SusDecay";
    strings["Release##sgimcd"].plurals[0] = "=Release";
    strings["Bottom##sgimcd1"].plurals[0] = "=Bottom";
    strings["Top##sgimcd1"].plurals[0] = "=Top";
    strings["Speed##sgimcd"].plurals[0] = "=Speed";
    strings["Phase##sgimcd"].plurals[0] = "=Phase";
    strings["Shape##sgimcd"].plurals[0] = "=Shape";
    strings["Macro type: Sequence##sgimcd"].plurals[0] = "=Macro type: Sequence";
    strings["Macro type: ADSR##sgimcd"].plurals[0] = "=Macro type: ADSR";
    strings["Macro type: LFO##sgimcd"].plurals[0] = "=Macro type: LFO";
    strings["Macro type: What's going on here?##sgimcd"].plurals[0] = "=Macro type: What's going on here?";
    strings["Delay/Step Length##sgimcd"].plurals[0] = "=Delay/Step Length";
    strings["Step Length (ticks)##IMacroSpeed"].plurals[0] = "=Step Length (ticks)##IMacroSpeed";
    strings["Delay##IMacroDelay"].plurals[0] = "=Delay##IMacroDelay";
    strings["Release mode: Active (jump to release pos)##sgimcd"].plurals[0] = "=Release mode: Active (jump to release pos)";
    strings["Release mode: Passive (delayed release)##sgimcd"].plurals[0] = "=Release mode: Passive (delayed release)";
    strings["Tabs##sgimcd"].plurals[0] = "=Tabs";
    strings["Length##sgimcd"].plurals[0] = "=Length";
    strings["StepLen##sgimcd"].plurals[0] = "=StepLen";
    strings["Delay##sgimcd"].plurals[0] = "=Delay";
    strings["The heck? No, this isn't even working correctly...##sgimcd"].plurals[0] = "=The heck? No, this isn't even working correctly...";
    strings["The only problem with that selectedMacro is that it's a bug...##sgimcd"].plurals[0] = "=The only problem with that selectedMacro is that it's a bug...";
    strings["Single (combo box)##sgimcd"].plurals[0] = "=Single (combo box)";

    //   sgiLYNX   src/gui/inst/mikey.cpp

    strings["Macros##sgiLYNX"].plurals[0] = "=Macros";
    strings["Volume##sgiLYNX"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiLYNX"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiLYNX"].plurals[0] = "=Pitch";
    strings["Duty/Int##sgiLYNX"].plurals[0] = "=Duty/Int";
    strings["Panning (left)##sgiLYNX"].plurals[0] = "=Panning (left)";
    strings["Panning (right)##sgiLYNX"].plurals[0] = "=Panning (right)";
    strings["Phase Reset##sgiLYNX"].plurals[0] = "=Phase Reset";
    strings["Load LFSR##sgiLYNX"].plurals[0] = "=Load LFSR";

    //   sgi5232   src/gui/inst/msm5232.cpp

    strings["Macros##sgi5232"].plurals[0] = "=Macros";
    strings["Volume##sgi5232"].plurals[0] = "=Volume";
    strings["Arpeggio##sgi5232"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgi5232"].plurals[0] = "=Pitch";
    strings["Group Ctrl##sgi5232"].plurals[0] = "=Group Ctrl";
    strings["Group Attack##sgi5232"].plurals[0] = "=Group Attack";
    strings["Group Decay##sgi5232"].plurals[0] = "=Group Decay";
    strings["Noise##sgi5232"].plurals[0] = "=Noise";

    //   sgi6258   src/gui/inst/msm6258.cpp

    strings["Macros##sgi6258"].plurals[0] = "=Macros";
    strings["Frequency Divider##sgi6258"].plurals[0] = "=Frequency Divider";
    strings["Panning##sgi6258"].plurals[0] = "=Panning";
    strings["Phase Reset##sgi6258"].plurals[0] = "=Phase Reset";
    strings["Clock Divider##sgi6258"].plurals[0] = "=Clock Divider";

    //   sgi6295   src/gui/inst/msm6295.cpp

    strings["Macros##sgi6295"].plurals[0] = "=Macros";
    strings["Volume##sgi6295"].plurals[0] = "=Volume";
    strings["Frequency Divider##sgi6295"].plurals[0] = "=Frequency Divider";
    strings["Phase Reset##sgi6295"].plurals[0] = "=Phase Reset";

    //   sgiMULPCM src/gui/inst/multipcm.cpp

    strings["MultiPCM##sgiMULPCM"].plurals[0] = "=MultiPCM";
    strings["AR##sgiMULPCM0"].plurals[0] = "=AR";
    strings["AR##sgiMULPCM1"].plurals[0] = "=AR";
    strings["Attack Rate##sgiMULPCM"].plurals[0] = "=Attack Rate";
    strings["D1R##sgiMULPCM0"].plurals[0] = "=D1R";
    strings["D1R##sgiMULPCM1"].plurals[0] = "=D1R";
    strings["Decay 1 Rate##sgiMULPCM"].plurals[0] = "=Decay 1 Rate";
    strings["DL##sgiMULPCM0"].plurals[0] = "=DL";
    strings["DL##sgiMULPCM1"].plurals[0] = "=DL";
    strings["Decay Level##sgiMULPCM"].plurals[0] = "=Decay Level";
    strings["D2R##sgiMULPCM0"].plurals[0] = "=D2R";
    strings["D2R##sgiMULPCM1"].plurals[0] = "=D2R";
    strings["Decay 2 Rate##sgiMULPCM"].plurals[0] = "=Decay 2 Rate";
    strings["RR##sgiMULPCM0"].plurals[0] = "=RR";
    strings["RR##sgiMULPCM1"].plurals[0] = "=RR";
    strings["Release Rate##sgiMULPCM"].plurals[0] = "=Release Rate";
    strings["RC##sgiMULPCM0"].plurals[0] = "=RC";
    strings["RC##sgiMULPCM1"].plurals[0] = "=RC";
    strings["Rate Correction##sgiMULPCM"].plurals[0] = "=Rate Correction";
    strings["Envelope##sgiMULPCM0"].plurals[0] = "=Envelope";
    strings["Envelope##sgiMULPCM1"].plurals[0] = "=Envelope";
    strings["LFO Rate##sgiMULPCM"].plurals[0] = "=LFO Rate";
    strings["PM Depth##sgiMULPCM"].plurals[0] = "=PM Depth";
    strings["AM Depth##sgiMULPCM"].plurals[0] = "=AM Depth";
    strings["Macros##sgiMULPCM"].plurals[0] = "=Macros";
    strings["Volume##sgiMULPCM"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiMULPCM"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiMULPCM"].plurals[0] = "=Pitch";
    strings["Panning##sgiMULPCM"].plurals[0] = "=Panning";
    strings["Phase Reset##sgiMULPCM"].plurals[0] = "=Phase Reset";

    //   sgiN163   src/gui/inst/n163.cpp

    strings["Namco 163##sgiN163"].plurals[0] = "=Namco 163";
    strings["Load waveform##sgiN163"].plurals[0] = "=Load waveform";
    strings["when enabled, a waveform will be loaded into RAM.\nwhen disabled, only the offset and length change.##sgiN163"].plurals[0] = "=when enabled, a waveform will be loaded into RAM.\nwhen disabled, only the offset and length change.";
    strings["Waveform##WAVE"].plurals[0] = "=Waveform##WAVE";
    strings["Per-channel wave position/length##sgiN163"].plurals[0] = "=Per-channel wave position/length";
    strings["Ch##sgiN163"].plurals[0] = "=Ch";
    strings["Position##sgiN163"].plurals[0] = "=Position";
    strings["Length##sgiN163"].plurals[0] = "=Length";
    strings["Position##WAVEPOS"].plurals[0] = "=Position##WAVEPOS";
    strings["Length##WAVELEN"].plurals[0] = "=Length##WAVELEN";
    strings["Macros##sgiN163"].plurals[0] = "=Macros";
    strings["Volume##sgiN163"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiN163"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiN163"].plurals[0] = "=Pitch";
    strings["Wave Pos##sgiN163"].plurals[0] = "=Wave Pos";
    strings["Waveform##sgiN163"].plurals[0] = "=Waveform";
    strings["Wave Length##sgiN163"].plurals[0] = "=Wave Length";

    //   sgiWSG    src/gui/inst/namco.cpp

    strings["Macros##sgiWSG"].plurals[0] = "=Macros";
    strings["Volume##sgiWSG"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiWSG"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiWSG"].plurals[0] = "=Pitch";
    strings["Noise##sgiWSG"].plurals[0] = "=Noise";
    strings["Waveform##sgiWSG"].plurals[0] = "=Waveform";
    strings["Panning (left)##sgiWSG"].plurals[0] = "=Panning (left)";
    strings["Panning (right)##sgiWSG"].plurals[0] = "=Panning (right)";

    //   sgiNDS    src/gui/inst/nds.cpp

    strings["Macros##sgiNDS"].plurals[0] = "=Macros";
    strings["Volume##sgiNDS"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiNDS"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiNDS"].plurals[0] = "=Pitch";
    strings["Duty##sgiNDS"].plurals[0] = "=Duty";
    strings["Panning##sgiNDS"].plurals[0] = "=Panning";
    strings["Phase Reset##sgiNDS"].plurals[0] = "=Phase Reset";

    //   sgiNES    src/gui/inst/nes.cpp

    strings["Macros##sgiNES"].plurals[0] = "=Macros";
    strings["Volume##sgiNES"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiNES"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiNES"].plurals[0] = "=Pitch";
    strings["Duty/Noise##sgiNES"].plurals[0] = "=Duty/Noise";
    strings["Phase Reset##sgiNES"].plurals[0] = "=Phase Reset";

    //   sgiOPL    src/gui/inst/opl.cpp

    strings["4-op##sgiOPL"].plurals[0] = "=4-op";
    strings["Drums##sgiOPL"].plurals[0] = "=Drums";
    strings["Fixed frequency mode##sgiOPL"].plurals[0] = "=Fixed frequency mode";
    strings["when enabled, drums will be set to the specified frequencies, ignoring the note.##sgiOPL"].plurals[0] = "=when enabled, drums will be set to the specified frequencies, ignoring the note.";
    strings["Drum##sgiOPL"].plurals[0] = "=Drum";
    strings["Block##sgiOPL"].plurals[0] = "=Block";
    strings["FreqNum##sgiOPL"].plurals[0] = "=FreqNum";
    strings["Kick##sgiOPL0"].plurals[0] = "=Kick";
    strings["Snare/Hi-hat##sgiOPL"].plurals[0] = "=Snare/Hi-hat";
    strings["Tom/Top##sgiOPL"].plurals[0] = "=Tom/Top";
    strings["Other##sgiOPL0"].plurals[0] = "=Other";
    strings["Other##sgiOPL1"].plurals[0] = "=Other";
    strings["Envelope##sgiOPL0"].plurals[0] = "=Envelope";
    strings["Envelope##sgiOPL1"].plurals[0] = "=Envelope";
    strings["op%d##sgiOPL0"].plurals[0] = "=op%d";
    strings["Kick##sgiOPL1"].plurals[0] = "=Kick";
    strings["Env##sgiOPL"].plurals[0] = "=Env";
    strings["OP%d##sgiOPL1"].plurals[0] = "=OP%d";
    strings["OPL2/3 only (last 4 waveforms are OPL3 only)##sgiOPL0"].plurals[0] = "=OPL2/3 only (last 4 waveforms are OPL3 only)";
    strings["op%d##sgiOPL2"].plurals[0] = "=op%d";
    strings["Envelope 2 (kick only)##sgiOPL0"].plurals[0] = "=Envelope 2 (kick only)";
    strings["Envelope##sgiOPL2"].plurals[0] = "=Envelope";
    strings["Operator %d##sgiOPL"].plurals[0] = "=Operator %d";
    strings["Waveform##sgiOPL"].plurals[0] = "=Waveform";
    strings["Envelope##sgiOPL3"].plurals[0] = "=Envelope";
    strings["OPL2/3 only (last 4 waveforms are OPL3 only)##sgiOPL1"].plurals[0] = "=OPL2/3 only (last 4 waveforms are OPL3 only)";
    strings["op%d##sgiOPL3"].plurals[0] = "=op%d";
    strings["Envelope 2 (kick only)##sgiOPL1"].plurals[0] = "=Envelope 2 (kick only)";
    strings["Envelope##sgiOPL4"].plurals[0] = "=Envelope";
    strings["OP%d##sgiOPL4"].plurals[0] = "=OP%d";
    strings["OPL2/3 only (last 4 waveforms are OPL3 only)##sgiOPL2"].plurals[0] = "=OPL2/3 only (last 4 waveforms are OPL3 only)";
    strings["FM Macros##sgiOPL"].plurals[0] = "=FM Macros";
    strings["OP%d Macros##sgiOPL"].plurals[0] = "=OP%d Macros";
    strings["Macros##sgiOPL"].plurals[0] = "=Macros";
    strings["Volume##sgiOPL"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiOPL"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiOPL"].plurals[0] = "=Pitch";
    strings["Panning##sgiOPL"].plurals[0] = "=Panning";
    strings["Phase Reset##sgiOPL"].plurals[0] = "=Phase Reset";

    //   sgiOPLL   src/gui/inst/opll.cpp

    strings["%s name##sgiOPLL"].plurals[0] = "=%s name";
    strings["Fixed frequency mode##sgiOPLL"].plurals[0] = "=Fixed frequency mode";
    strings["when enabled, drums will be set to the specified frequencies, ignoring the note.##sgiOPLL"].plurals[0] = "=when enabled, drums will be set to the specified frequencies, ignoring the note.";
    strings["Drum##sgiOPLL"].plurals[0] = "=Drum";
    strings["Block##sgiOPLL"].plurals[0] = "=Block";
    strings["FreqNum##sgiOPLL"].plurals[0] = "=FreqNum";
    strings["Kick##sgiOPLL"].plurals[0] = "=Kick";
    strings["Snare/Hi-hat##sgiOPLL"].plurals[0] = "=Snare/Hi-hat";
    strings["Tom/Top##sgiOPLL"].plurals[0] = "=Tom/Top";
    strings["Volume##TL"].plurals[0] = "=Volume##TL";
    strings["this volume slider only works in compatibility (non-drums) system.##sgiOPLL"].plurals[0] = "=this volume slider only works in compatibility (non-drums) system.";
    strings["Other##sgiOPLL0"].plurals[0] = "=Other";
    strings["Other##sgiOPLL1"].plurals[0] = "=Other";
    strings["Envelope##sgiOPLL0"].plurals[0] = "=Envelope";
    strings["Envelope##sgiOPLL1"].plurals[0] = "=Envelope";
    strings["op%d##sgiOPLL0"].plurals[0] = "=op%d";
    strings["OP%d##sgiOPLL1"].plurals[0] = "=OP%d";
    strings["op%d##sgiOPLL2"].plurals[0] = "=op%d";
    strings["Operator %d##sgiOPLL"].plurals[0] = "=Operator %d";
    strings["Waveform##sgiOPLL"].plurals[0] = "=Waveform";
    strings["Envelope##sgiOPLL2"].plurals[0] = "=Envelope";
    strings["op%d##sgiOPLL3"].plurals[0] = "=op%d";
    strings["OP%d##sgiOPLL4"].plurals[0] = "=OP%d";
    strings["SSG On##sgiOPLL"].plurals[0] = "=SSG On";
    strings["FM Macros##sgiOPLL"].plurals[0] = "=FM Macros";
    strings["OP%d Macros##sgiOPLL"].plurals[0] = "=OP%d Macros";
    strings["Macros##sgiOPLL"].plurals[0] = "=Macros";
    strings["Volume##sgiOPLL"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiOPLL"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiOPLL"].plurals[0] = "=Pitch";
    strings["Patch##sgiOPLL"].plurals[0] = "=Patch";
    strings["Phase Reset##sgiOPLL"].plurals[0] = "=Phase Reset";

    //   sgiOPM    src/gui/inst/opm.cpp

    strings["Envelope##sgiOPM0"].plurals[0] = "=Envelope";
    strings["op%d##sgiOPM0"].plurals[0] = "=op%d";
    strings["OP%d##sgiOPM3"].plurals[0] = "=OP%d";
    strings["op%d##sgiOPM1"].plurals[0] = "=op%d";
    strings["Operator %d##sgiOPM"].plurals[0] = "=Operator %d";
    strings["Waveform##sgiOPM"].plurals[0] = "=Waveform";
    strings["Envelope##sgiOPM1"].plurals[0] = "=Envelope";
    strings["op%d##sgiOPM2"].plurals[0] = "=op%d";
    strings["OP%d##sgiOPM4"].plurals[0] = "=OP%d";
    strings["FM Macros##sgiOPM"].plurals[0] = "=FM Macros";
    strings["AM Depth##sgiOPM"].plurals[0] = "=AM Depth";
    strings["PM Depth##sgiOPM"].plurals[0] = "=PM Depth";
    strings["LFO Speed##sgiOPM"].plurals[0] = "=LFO Speed";
    strings["LFO Shape##sgiOPM"].plurals[0] = "=LFO Shape";
    strings["OpMask##sgiOPM"].plurals[0] = "=OpMask";
    strings["OP%d Macros##sgiOPM"].plurals[0] = "=OP%d Macros";
    strings["Macros##sgiOPM"].plurals[0] = "=Macros";
    strings["Volume##sgiOPM"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiOPM"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiOPM"].plurals[0] = "=Pitch";
    strings["Noise Freq##sgiOPM"].plurals[0] = "=Noise Freq";
    strings["Panning##sgiOPM"].plurals[0] = "=Panning";
    strings["Phase Reset##sgiOPM"].plurals[0] = "=Phase Reset";

    //   sgiOPN    src/gui/inst/opn.cpp

    strings["Envelope##sgiOPN0"].plurals[0] = "=Envelope";
    strings["Envelope##sgiOPN1"].plurals[0] = "=Envelope";
    strings["op%d##sgiOPN0"].plurals[0] = "=op%d";
    strings["OP%d##sgiOPN1"].plurals[0] = "=OP%d";
    strings["op%d##sgiOPN2"].plurals[0] = "=op%d";
    strings["Operator %d##sgiOPN"].plurals[0] = "=Operator %d";
    strings["SSG-EG##sgiOPN"].plurals[0] = "=SSG-EG";
    strings["Envelope##sgiOPN2"].plurals[0] = "=Envelope";
    strings["op%d##sgiOPN3"].plurals[0] = "=op%d";
    strings["OP%d##sgiOPN4"].plurals[0] = "=OP%d";
    strings["SSG On##sgiOPN"].plurals[0] = "=SSG On";
    strings["FM Macros##sgiOPN"].plurals[0] = "=FM Macros";
    strings["LFO Speed##sgiOPN"].plurals[0] = "=LFO Speed";
    strings["OpMask##sgiOPN"].plurals[0] = "=OpMask";
    strings["OP%d Macros##sgiOPN"].plurals[0] = "=OP%d Macros";
    strings["Macros##sgiOPN"].plurals[0] = "=Macros";
    strings["Volume##sgiOPN"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiOPN"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiOPN"].plurals[0] = "=Pitch";
    strings["Panning##sgiOPN"].plurals[0] = "=Panning";
    strings["Phase Reset##sgiOPN"].plurals[0] = "=Phase Reset";

    //   sgiOPZ    src/gui/inst/opz.cpp

    strings["Request from TX81Z##sgiOPZ"].plurals[0] = "=Request from TX81Z";
    strings["Other##sgiOPZ0"].plurals[0] = "=Other";
    strings["Other##sgiOPZ1"].plurals[0] = "=Other";
    strings["Envelope##sgiOPZ0"].plurals[0] = "=Envelope";
    strings["Envelope##sgiOPZ1"].plurals[0] = "=Envelope";
    strings["op%d##sgiOPZ0"].plurals[0] = "=op%d";
    strings["OP%d##sgiOPZ1"].plurals[0] = "=OP%d";
    strings["Fixed##sgiOPZ0"].plurals[0] = "=Fixed";
    strings["Block##sgiOPZ0"].plurals[0] = "=Block";
    strings["FreqNum##sgiOPZ0"].plurals[0] = "=FreqNum";
    strings["op%d##sgiOPZ2"].plurals[0] = "=op%d";
    strings["Operator %d##sgiOPZ"].plurals[0] = "=Operator %d";
    strings["Waveform##sgiOPZ"].plurals[0] = "=Waveform";
    strings["Envelope##sgiOPZ2"].plurals[0] = "=Envelope";
    strings["Block##sgiOPZ1"].plurals[0] = "=Block";
    strings["Freq##sgiOPZ"].plurals[0] = "=Freq";
    strings["Fixed##sgiOPZ1"].plurals[0] = "=Fixed";
    strings["op%d##sgiOPZ3"].plurals[0] = "=op%d";
    strings["OP%d##sgiOPZ4"].plurals[0] = "=OP%d";
    strings["Fixed##sgiOPZ2"].plurals[0] = "=Fixed";
    strings["Block##sgiOPZ2"].plurals[0] = "=Block";
    strings["FreqNum##sgiOPZ1"].plurals[0] = "=FreqNum";
    strings["FM Macros##sgiOPZ"].plurals[0] = "=FM Macros";
    strings["AM Depth##sgiOPZ"].plurals[0] = "=AM Depth";
    strings["PM Depth##sgiOPZ"].plurals[0] = "=PM Depth";
    strings["LFO Speed##sgiOPZ"].plurals[0] = "=LFO Speed";
    strings["LFO Shape##sgiOPZ"].plurals[0] = "=LFO Shape";
    strings["AM Depth 2##sgiOPZ"].plurals[0] = "=AM Depth 2";
    strings["PM Depth 2##sgiOPZ"].plurals[0] = "=PM Depth 2";
    strings["LFO2 Speed##sgiOPZ"].plurals[0] = "=LFO2 Speed";
    strings["LFO2 Shape##sgiOPZ"].plurals[0] = "=LFO2 Shape";
    strings["OP%d Macros##sgiOPZ"].plurals[0] = "=OP%d Macros";
    strings["Macros##sgiOPZ"].plurals[0] = "=Macros";
    strings["Volume##sgiOPZ"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiOPZ"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiOPZ"].plurals[0] = "=Pitch";
    strings["Noise Freq##sgiOPZ"].plurals[0] = "=Noise Freq";
    strings["Panning##sgiOPZ"].plurals[0] = "=Panning";
    strings["Phase Reset##sgiOPZ"].plurals[0] = "=Phase Reset";

    //   sgiPCE    src/gui/inst/pce.cpp

    strings["Macros##sgiPCE"].plurals[0] = "=Macros";
    strings["Volume##sgiPCE"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiPCE"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiPCE"].plurals[0] = "=Pitch";
    strings["Noise##sgiPCE"].plurals[0] = "=Noise";
    strings["Waveform##sgiPCE"].plurals[0] = "=Waveform";
    strings["Panning (left)##sgiPCE"].plurals[0] = "=Panning (left)";
    strings["Panning (right)##sgiPCE"].plurals[0] = "=Panning (right)";
    strings["Phase Reset##sgiPCE"].plurals[0] = "=Phase Reset";

    //   sgiPET    src/gui/inst/pet.cpp

    strings["Macros##sgiPET"].plurals[0] = "=Macros";
    strings["Volume##sgiPET"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiPET"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiPET"].plurals[0] = "=Pitch";
    strings["Waveform##sgiPET"].plurals[0] = "=Waveform";

    //   sgiPMQT   src/gui/inst/pokemini.cpp

    strings["Macros##sgiPMQT"].plurals[0] = "=Macros";
    strings["Volume##sgiPMQT"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiPMQT"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiPMQT"].plurals[0] = "=Pitch";
    strings["Pulse Width##sgiPMQT"].plurals[0] = "=Pulse Width";

    //   sgiPOKEY  src/gui/inst/pokey.cpp

    strings["16-bit raw period macro##sgiPOKEY"].plurals[0] = "=16-bit raw period macro";
    strings["Macros##sgiPOKEY"].plurals[0] = "=Macros";
    strings["Volume##sgiPOKEY"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiPOKEY"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiPOKEY"].plurals[0] = "=Pitch";
    strings["Waveform##sgiPOKEY"].plurals[0] = "=Waveform";
    strings["Raw Period##sgiPOKEY"].plurals[0] = "=Raw Period";

    //   sgiPNN    src/gui/inst/powernoise.cpp

    strings["Octave offset##sgiPNN"].plurals[0] = "=Octave offset";
    strings["go to Macros for other parameters.##sgiPNN"].plurals[0] = "=go to Macros for other parameters.";
    strings["Macros##sgiPNN"].plurals[0] = "=Macros";
    strings["Volume##sgiPNN"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiPNN"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiPNN"].plurals[0] = "=Pitch";
    strings["Panning (left)##sgiPNN"].plurals[0] = "=Panning (left)";
    strings["Panning (right)##sgiPNN"].plurals[0] = "=Panning (right)";
    strings["Phase Reset##sgiPNN"].plurals[0] = "=Phase Reset";
    strings["Control##sgiPNN"].plurals[0] = "=Control";
    strings["Tap A Location##sgiPNN"].plurals[0] = "=Tap A Location";
    strings["Tap B Location##sgiPNN"].plurals[0] = "=Tap B Location";
    strings["Load LFSR##sgiPNN"].plurals[0] = "=Load LFSR";

    //   sgiPNS    src/gui/inst/powernoise_slope.cpp

    strings["Octave offset##sgiPNS"].plurals[0] = "=Octave offset";
    strings["go to Macros for other parameters.##sgiPNS"].plurals[0] = "=go to Macros for other parameters.";
    strings["Macros##sgiPNS"].plurals[0] = "=Macros";
    strings["Volume##sgiPNS"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiPNS"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiPNS"].plurals[0] = "=Pitch";
    strings["Panning (left)##sgiPNS"].plurals[0] = "=Panning (left)";
    strings["Panning (right)##sgiPNS"].plurals[0] = "=Panning (right)";
    strings["Phase Reset##sgiPNS"].plurals[0] = "=Phase Reset";
    strings["Control##sgiPNS"].plurals[0] = "=Control";
    strings["Portion A Length##sgiPNS"].plurals[0] = "=Portion A Length";
    strings["Portion B Length##sgiPNS"].plurals[0] = "=Portion B Length";
    strings["Portion A Offset##sgiPNS"].plurals[0] = "=Portion A Offset";
    strings["Portion B Offset##sgiPNS"].plurals[0] = "=Portion B Offset";

    //   sgiPV     src/gui/inst/pv1000.cpp

    strings["Macros##sgiPV"].plurals[0] = "=Macros";
    strings["Volume##sgiPV"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiPV"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiPV"].plurals[0] = "=Pitch";
    strings["Raw Frequency##sgiPV"].plurals[0] = "=Raw Frequency";

    //   sgiQ      src/gui/inst/qsound.cpp

    strings["Macros##sgiQ"].plurals[0] = "=Macros";
    strings["Volume##sgiQ"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiQ"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiQ"].plurals[0] = "=Pitch";
    strings["Panning##sgiQ"].plurals[0] = "=Panning";
    strings["Surround##sgiQ"].plurals[0] = "=Surround";
    strings["Phase Reset##sgiQ"].plurals[0] = "=Phase Reset";
    strings["Echo Level##sgiQ"].plurals[0] = "=Echo Level";
    strings["Echo Feedback##sgiQ"].plurals[0] = "=Echo Feedback";
    strings["Echo Length##sgiQ"].plurals[0] = "=Echo Length";

    //   sgiRF5    src/gui/inst/rf5c68.cpp

    strings["Macros##sgiRF5"].plurals[0] = "=Macros";
    strings["Volume##sgiRF5"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiRF5"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiRF5"].plurals[0] = "=Pitch";
    strings["Panning (left)##sgiRF5"].plurals[0] = "=Panning (left)";
    strings["Panning (right)##sgiRF5"].plurals[0] = "=Panning (right)";
    strings["Phase Reset##sgiRF5"].plurals[0] = "=Phase Reset";

    //   sgiSAA    src/gui/inst/saa1099.cpp

    strings["Macros##sgiSAA"].plurals[0] = "=Macros";
    strings["Volume##sgiSAA"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiSAA"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiSAA"].plurals[0] = "=Pitch";
    strings["Duty/Noise##sgiSAA"].plurals[0] = "=Duty/Noise";
    strings["Waveform##sgiSAA"].plurals[0] = "=Waveform";
    strings["Panning (left)##sgiSAA"].plurals[0] = "=Panning (left)";
    strings["Panning (right)##sgiSAA"].plurals[0] = "=Panning (right)";
    strings["Envelope##sgiSAA"].plurals[0] = "=Envelope";

    //   sgismpd   src/gui/inst/sampleDraw.cpp

    strings["Sample##sgismpd0"].plurals[0] = "=Sample";
    strings["DPCM##sgismpd"].plurals[0] = "=DPCM";
    strings["new DPCM features disabled (compatibility)!##sgismpd"].plurals[0] = "=new DPCM features disabled (compatibility)!";
    strings["click here to enable them.##sgismpd"].plurals[0] = "=click here to enable them.";
    strings["none selected##sgismpd"].plurals[0] = "=none selected";
    strings["Use sample##sgismpd"].plurals[0] = "=Use sample";
    strings["Sample bank slot##BANKSLOT"].plurals[0] = "=Sample bank slot##BANKSLOT";
    strings["Sample##sgismpd1"].plurals[0] = "=Sample";
    strings["Use wavetable (Amiga/Generic DAC only)##sgismpd"].plurals[0] = "=Use wavetable (Amiga/Generic DAC only)";
    strings["Use wavetable##sgismpd"].plurals[0] = "=Use wavetable";
    strings["Width##sgismpd"].plurals[0] = "=Width";
    strings["Use sample map##sgismpd"].plurals[0] = "=Use sample map";
    strings["pitch##sgismpd"].plurals[0] = "=pitch";
    strings["loop##sgismpd"].plurals[0] = "=loop";
    strings["delta##sgismpd"].plurals[0] = "=delta";
    strings["note##sgismpd"].plurals[0] = "=note";
    strings["sample name##sgismpd"].plurals[0] = "=sample name";
    strings["L##L%d"].plurals[0] = "=L##L%d";
    strings["set entire map to this pitch##sgismpd"].plurals[0] = "=set entire map to this pitch";
    strings["set entire map to this delta counter value##sgismpd"].plurals[0] = "=set entire map to this delta counter value";
    strings["set entire map to this note##sgismpd"].plurals[0] = "=set entire map to this note";
    strings["set entire map to this sample##sgismpd"].plurals[0] = "=set entire map to this sample";
    strings["reset pitches##sgismpd"].plurals[0] = "=reset pitches";
    strings["clear delta counter values##sgismpd"].plurals[0] = "=clear delta counter values";
    strings["reset notes##sgismpd"].plurals[0] = "=reset notes";
    strings["clear map samples##sgismpd"].plurals[0] = "=clear map samples";

    //   sgiSCC    src/gui/inst/scc.cpp

    strings["Macros##sgiSCC"].plurals[0] = "=Macros";
    strings["Volume##sgiSCC"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiSCC"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiSCC"].plurals[0] = "=Pitch";
    strings["Waveform##sgiSCC"].plurals[0] = "=Waveform";

    //   sgiSEGA   src/gui/inst/segapcm.cpp

    strings["Macros##sgiSEGA"].plurals[0] = "=Macros";
    strings["Volume##sgiSEGA"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiSEGA"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiSEGA"].plurals[0] = "=Pitch";
    strings["Panning (left)##sgiSEGA"].plurals[0] = "=Panning (left)";
    strings["Panning (right)##sgiSEGA"].plurals[0] = "=Panning (right)";
    strings["Phase Reset##sgiSEGA"].plurals[0] = "=Phase Reset";

    //   sgiSID2   src/gui/inst/sid2.cpp

    strings["Waveform##sgiSID2"].plurals[0] = "=Waveform";
    strings["tri##sgiSID2"].plurals[0] = "=tri";
    strings["saw##sgiSID2"].plurals[0] = "=saw";
    strings["pulse##sgiSID2"].plurals[0] = "=pulse";
    strings["noise##sgiSID2"].plurals[0] = "=noise";
    strings["A##sgiSID2"].plurals[0] = "=A";
    strings["D##sgiSID2"].plurals[0] = "=D";
    strings["S##sgiSID2"].plurals[0] = "=S";
    strings["R##sgiSID2"].plurals[0] = "=R";
    strings["VOL##sgiSID2"].plurals[0] = "=VOL";
    strings["Envelope##sgiSID2"].plurals[0] = "=Envelope";
    strings["Duty##sgiSID2"].plurals[0] = "=Duty";
    strings["Ring Modulation##sgiSID2"].plurals[0] = "=Ring Modulation";
    strings["Oscillator Sync##sgiSID2"].plurals[0] = "=Oscillator Sync";
    strings["Enable filter##sgiSID2"].plurals[0] = "=Enable filter";
    strings["Initialize filter##sgiSID2"].plurals[0] = "=Initialize filter";
    strings["Cutoff##sgiSID2"].plurals[0] = "=Cutoff";
    strings["Resonance##sgiSID2"].plurals[0] = "=Resonance";
    strings["Filter Mode##sgiSID2"].plurals[0] = "=Filter Mode";
    strings["low##sgiSID2"].plurals[0] = "=low";
    strings["band##sgiSID2"].plurals[0] = "=band";
    strings["high##sgiSID2"].plurals[0] = "=high";
    strings["Noise Mode##sgiSID2"].plurals[0] = "=Noise Mode";
    strings["Wave Mix Mode##sgiSID2"].plurals[0] = "=Wave Mix Mode";
    strings["Absolute Cutoff Macro##sgiSID2"].plurals[0] = "=Absolute Cutoff Macro";
    strings["Absolute Duty Macro##sgiSID2"].plurals[0] = "=Absolute Duty Macro";
    strings["Macros##sgiSID2"].plurals[0] = "=Macros";
    strings["Volume##sgiSID2"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiSID2"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiSID2"].plurals[0] = "=Pitch";
    strings["Duty##sgiSID21"].plurals[0] = "=Duty";
    strings["Waveform##sgiSID21"].plurals[0] = "=Waveform";
    strings["Noise Mode##sgiSID21"].plurals[0] = "=Noise Mode";
    strings["Wave Mix Mode##sgiSID21"].plurals[0] = "=Wave Mix Mode";
    strings["Cutoff##sgiSID21"].plurals[0] = "=Cutoff";
    strings["Filter Mode##sgiSID21"].plurals[0] = "=Filter Mode";
    strings["Filter Toggle##sgiSID2"].plurals[0] = "=Filter Toggle";
    strings["Resonance##sgiSID21"].plurals[0] = "=Resonance";
    strings["Phase Reset##sgiSID2"].plurals[0] = "=Phase Reset";
    strings["Envelope Reset/Key Control##sgiSID2"].plurals[0] = "=Envelope Reset/Key Control";
    strings["Special##sgiSID2"].plurals[0] = "=Special";
    strings["Attack##sgiSID2"].plurals[0] = "=Attack";
    strings["Decay##sgiSID2"].plurals[0] = "=Decay";
    strings["Sustain##sgiSID2"].plurals[0] = "=Sustain";
    strings["Release##sgiSID2"].plurals[0] = "=Release";

    //   sgiSM     src/gui/inst/sm8521.cpp

    strings["Macros##sgiSM"].plurals[0] = "=Macros";
    strings["Volume##sgiSM"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiSM"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiSM"].plurals[0] = "=Pitch";
    strings["Waveform##sgiSM"].plurals[0] = "=Waveform";

    //   sgiSNES   src/gui/inst/snes.cpp

    strings["Use envelope##sgiSNES"].plurals[0] = "=Use envelope";
    strings["Envelope##sgiSNES0"].plurals[0] = "=Envelope";
    strings["Envelope##sgiSNES1"].plurals[0] = "=Envelope";
    strings["Sustain/release mode:##sgiSNES"].plurals[0] = "=Sustain/release mode:";
    strings["Direct (cut on release)##sgiSNES"].plurals[0] = "=Direct (cut on release)";
    strings["Effective (linear decrease)##sgiSNES"].plurals[0] = "=Effective (linear decrease)";
    strings["Effective (exponential decrease)##sgiSNES"].plurals[0] = "=Effective (exponential decrease)";
    strings["Delayed (write R on release)##sgiSNES"].plurals[0] = "=Delayed (write R on release)";
    strings["Gain Mode##sgiSNES0"].plurals[0] = "=Gain Mode";
    strings["Gain Mode##sgiSNES1"].plurals[0] = "=Gain Mode";
    strings["Gain##sgiSNES0"].plurals[0] = "=Gain";
    strings["Gain##sgiSNES1"].plurals[0] = "=Gain";
    strings["Direct##sgiSNES"].plurals[0] = "=Direct";
    strings["Decrease (linear)##sgiSNES"].plurals[0] = "=Decrease (linear)";
    strings["Decrease (logarithmic)##sgiSNES"].plurals[0] = "=Decrease (logarithmic)";
    strings["Increase (linear)##sgiSNES"].plurals[0] = "=Increase (linear)";
    strings["Increase (bent line)##sgiSNES"].plurals[0] = "=Increase (bent line)";
    strings["using decrease modes will not produce any sound at all, unless you know what you are doing.\nit is recommended to use the Gain macro for decrease instead.##sgiSNES"].plurals[0] = "=using decrease modes will not produce any sound at all, unless you know what you are doing.\nit is recommended to use the Gain macro for decrease instead.";
    strings["Macros##sgiSNES"].plurals[0] = "=Macros";
    strings["Volume##sgiSNES"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiSNES"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiSNES"].plurals[0] = "=Pitch";
    strings["Noise Freq##sgiSNES"].plurals[0] = "=Noise Freq";
    strings["Waveform##sgiSNES"].plurals[0] = "=Waveform";
    strings["Panning (left)##sgiSNES"].plurals[0] = "=Panning (left)";
    strings["Panning (right)##sgiSNES"].plurals[0] = "=Panning (right)";
    strings["Special##sgiSNES"].plurals[0] = "=Special";
    strings["Gain##sgiSNES2"].plurals[0] = "=Gain";

    //   sgiPSG    src/gui/inst/std.cpp

    strings["Macros##sgiPSG"].plurals[0] = "=Macros";
    strings["Volume##sgiPSG"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiPSG"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiPSG"].plurals[0] = "=Pitch";
    strings["Duty##sgiPSG"].plurals[0] = "=Duty";
    strings["Panning##sgiPSG"].plurals[0] = "=Panning";
    strings["Phase Reset##sgiPSG"].plurals[0] = "=Phase Reset";

    //   sgistru   src/gui/inst/stringsUtil.cpp

    strings["Down Down Down##sgistru"].plurals[0] = "=Down Down Down";
    strings["Down.##sgistru"].plurals[0] = "=Down.";
    strings["Down Up Down Up##sgistru"].plurals[0] = "=Down Up Down Up";
    strings["Down UP##sgistru"].plurals[0] = "=Down UP";
    strings["Up Up Up##sgistru"].plurals[0] = "=Up Up Up";
    strings["Up.##sgistru"].plurals[0] = "=Up.";
    strings["Up Down Up Down##sgistru"].plurals[0] = "=Up Down Up Down";
    strings["Up DOWN##sgistru"].plurals[0] = "=Up DOWN";
    strings["Algorithm##sgistru"].plurals[0] = "=Algorithm";
    strings["Feedback##sgistru"].plurals[0] = "=Feedback";
    strings["LFO > Freq##sgistru"].plurals[0] = "=LFO > Freq";
    strings["LFO > Amp##sgistru"].plurals[0] = "=LFO > Amp";
    strings["Attack##sgistru"].plurals[0] = "=Attack";
    strings["Decay##sgistru"].plurals[0] = "=Decay";
    strings["Decay 2##sgistru"].plurals[0] = "=Decay 2";
    strings["Release##sgistru"].plurals[0] = "=Release";
    strings["Sustain##sgistru0"].plurals[0] = "=Sustain";
    strings["Level##sgistru"].plurals[0] = "=Level";
    strings["EnvScale##sgistru"].plurals[0] = "=EnvScale";
    strings["Multiplier##sgistru"].plurals[0] = "=Multiplier";
    strings["Detune##sgistru0"].plurals[0] = "=Detune";
    strings["Detune 2##sgistru"].plurals[0] = "=Detune 2";
    strings["SSG-EG##sgistru"].plurals[0] = "=SSG-EG";
    strings["AM Depth##sgistru"].plurals[0] = "=AM Depth";
    strings["Vibrato Depth##sgistru"].plurals[0] = "=Vibrato Depth";
    strings["Sustained##sgistru0"].plurals[0] = "=Sustained";
    strings["Sustained##sgistru1"].plurals[0] = "=Sustained";
    strings["Level Scaling##sgistru"].plurals[0] = "=Level Scaling";
    strings["Sustain##sgistru1"].plurals[0] = "=Sustain";
    strings["Vibrato##sgistru"].plurals[0] = "=Vibrato";
    strings["Waveform##sgistru"].plurals[0] = "=Waveform";
    strings["Scale Rate##sgistru"].plurals[0] = "=Scale Rate";
    strings["OP2 Half Sine##sgistru"].plurals[0] = "=OP2 Half Sine";
    strings["OP1 Half Sine##sgistru"].plurals[0] = "=OP1 Half Sine";
    strings["EnvShift##sgistru"].plurals[0] = "=EnvShift";
    strings["Reverb##sgistru"].plurals[0] = "=Reverb";
    strings["Fine##sgistru0"].plurals[0] = "=Fine";
    strings["LFO2 > Freq##sgistru"].plurals[0] = "=LFO2 > Freq";
    strings["LFO2 > Amp##sgistru"].plurals[0] = "=LFO2 > Amp";
    strings["Fine##sgistru1"].plurals[0] = "=Fine";
    strings["Fine##sgistru2"].plurals[0] = "=Fine";
    strings["OP4 Noise Mode##sgistru0"].plurals[0] = "=OP4 Noise Mode";
    strings["Envelope Delay##sgistru"].plurals[0] = "=Envelope Delay";
    strings["Output Level##sgistru0"].plurals[0] = "=Output Level";
    strings["Modulation Input Level##sgistru"].plurals[0] = "=Modulation Input Level";
    strings["Left Output##sgistru"].plurals[0] = "=Left Output";
    strings["Right Output##sgistru"].plurals[0] = "=Right Output";
    strings["Coarse Tune (semitones)##sgistru"].plurals[0] = "=Coarse Tune (semitones)";
    strings["Detune##sgistru1"].plurals[0] = "=Detune";
    strings["Fixed Frequency Mode##sgistru"].plurals[0] = "=Fixed Frequency Mode";
    strings["OP4 Noise Mode##sgistru1"].plurals[0] = "=OP4 Noise Mode";
    strings["Env. Delay##sgistru"].plurals[0] = "=Env. Delay";
    strings["Output Level##sgistru1"].plurals[0] = "=Output Level";
    strings["ModInput##sgistru"].plurals[0] = "=ModInput";
    strings["Left##sgistru"].plurals[0] = "=Left";
    strings["Right##sgistru"].plurals[0] = "=Right";
    strings["Tune##sgistru"].plurals[0] = "=Tune";
    strings["Detune##sgistru2"].plurals[0] = "=Detune";
    strings["Fixed##sgistru0"].plurals[0] = "=Fixed";
    strings["Fine##sgistru3"].plurals[0] = "=Fine";
    strings["Fine##sgistru4"].plurals[0] = "=Fine";
    strings["Fine##sgistru5"].plurals[0] = "=Fine";
    strings["User##sgistru0"].plurals[0] = "=User";
    strings["1. Violin##sgistru"].plurals[0] = "=1. Violin";
    strings["2. Guitar##sgistru0"].plurals[0] = "=2. Guitar";
    strings["3. Piano##sgistru0"].plurals[0] = "=3. Piano";
    strings["4. Flute##sgistru0"].plurals[0] = "=4. Flute";
    strings["5. Clarinet##sgistru0"].plurals[0] = "=5. Clarinet";
    strings["6. Oboe##sgistru"].plurals[0] = "=6. Oboe";
    strings["7. Trumpet##sgistru0"].plurals[0] = "=7. Trumpet";
    strings["8. Organ##sgistru"].plurals[0] = "=8. Organ";
    strings["9. Horn##sgistru"].plurals[0] = "=9. Horn";
    strings["10. Synth##sgistru"].plurals[0] = "=10. Synth";
    strings["11. Harpsichord##sgistru"].plurals[0] = "=11. Harpsichord";
    strings["12. Vibraphone##sgistru0"].plurals[0] = "=12. Vibraphone";
    strings["13. Synth Bass##sgistru"].plurals[0] = "=13. Synth Bass";
    strings["14. Acoustic Bass##sgistru"].plurals[0] = "=14. Acoustic Bass";
    strings["15. Electric Guitar##sgistru"].plurals[0] = "=15. Electric Guitar";
    strings["Drums##sgistru0"].plurals[0] = "=Drums";
    strings["User##sgistru1"].plurals[0] = "=User";
    strings["1. Electric String##sgistru"].plurals[0] = "=1. Electric String";
    strings["2. Bow wow##sgistru"].plurals[0] = "=2. Bow wow";
    strings["3. Electric Guitar##sgistru0"].plurals[0] = "=3. Electric Guitar";
    strings["4. Organ##sgistru"].plurals[0] = "=4. Organ";
    strings["5. Clarinet##sgistru1"].plurals[0] = "=5. Clarinet";
    strings["6. Saxophone##sgistru"].plurals[0] = "=6. Saxophone";
    strings["7. Trumpet##sgistru1"].plurals[0] = "=7. Trumpet";
    strings["8. Street Organ##sgistru"].plurals[0] = "=8. Street Organ";
    strings["9. Synth Brass##sgistru"].plurals[0] = "=9. Synth Brass";
    strings["10. Electric Piano##sgistru"].plurals[0] = "=10. Electric Piano";
    strings["11. Bass##sgistru"].plurals[0] = "=11. Bass";
    strings["12. Vibraphone##sgistru1"].plurals[0] = "=12. Vibraphone";
    strings["13. Chime##sgistru"].plurals[0] = "=13. Chime";
    strings["14. Tom Tom II##sgistru"].plurals[0] = "=14. Tom Tom II";
    strings["15. Noise##sgistru"].plurals[0] = "=15. Noise";
    strings["Drums##sgistru1"].plurals[0] = "=Drums";
    strings["User##sgistru2"].plurals[0] = "=User";
    strings["1. Strings##sgistru"].plurals[0] = "=1. Strings";
    strings["2. Guitar##sgistru1"].plurals[0] = "=2. Guitar";
    strings["3. Electric Guitar##sgistru1"].plurals[0] = "=3. Electric Guitar";
    strings["4. Electric Piano##sgistru"].plurals[0] = "=4. Electric Piano";
    strings["5. Flute##sgistru"].plurals[0] = "=5. Flute";
    strings["6. Marimba##sgistru"].plurals[0] = "=6. Marimba";
    strings["7. Trumpet##sgistru2"].plurals[0] = "=7. Trumpet";
    strings["8. Harmonica##sgistru"].plurals[0] = "=8. Harmonica";
    strings["9. Tuba##sgistru"].plurals[0] = "=9. Tuba";
    strings["10. Synth Brass##sgistru"].plurals[0] = "=10. Synth Brass";
    strings["11. Short Saw##sgistru"].plurals[0] = "=11. Short Saw";
    strings["12. Vibraphone##sgistru2"].plurals[0] = "=12. Vibraphone";
    strings["13. Electric Guitar 2##sgistru"].plurals[0] = "=13. Electric Guitar 2";
    strings["14. Synth Bass##sgistru"].plurals[0] = "=14. Synth Bass";
    strings["15. Sitar##sgistru"].plurals[0] = "=15. Sitar";
    strings["Drums##sgistru2"].plurals[0] = "=Drums";
    strings["User##sgistru3"].plurals[0] = "=User";
    strings["1. Bell##sgistru"].plurals[0] = "=1. Bell";
    strings["2. Guitar##sgistru2"].plurals[0] = "=2. Guitar";
    strings["3. Piano##sgistru1"].plurals[0] = "=3. Piano";
    strings["4. Flute##sgistru1"].plurals[0] = "=4. Flute";
    strings["5. Clarinet##sgistru2"].plurals[0] = "=5. Clarinet";
    strings["6. Rattling Bell##sgistru"].plurals[0] = "=6. Rattling Bell";
    strings["7. Trumpet##sgistru3"].plurals[0] = "=7. Trumpet";
    strings["8. Reed Organ##sgistru"].plurals[0] = "=8. Reed Organ";
    strings["9. Soft Bell##sgistru"].plurals[0] = "=9. Soft Bell";
    strings["10. Xylophone##sgistru"].plurals[0] = "=10. Xylophone";
    strings["11. Vibraphone##sgistru"].plurals[0] = "=11. Vibraphone";
    strings["12. Brass##sgistru"].plurals[0] = "=12. Brass";
    strings["13. Bass Guitar##sgistru"].plurals[0] = "=13. Bass Guitar";
    strings["14. Synth##sgistru"].plurals[0] = "=14. Synth";
    strings["15. Chorus##sgistru"].plurals[0] = "=15. Chorus";
    strings["Drums##sgistru3"].plurals[0] = "=Drums";
    strings["Sine##sgistru0"].plurals[0] = "=Sine";
    strings["Half Sine##sgistru0"].plurals[0] = "=Half Sine";
    strings["Absolute Sine##sgistru0"].plurals[0] = "=Absolute Sine";
    strings["Quarter Sine##sgistru"].plurals[0] = "=Quarter Sine";
    strings["Squished Sine##sgistru0"].plurals[0] = "=Squished Sine";
    strings["Squished AbsSine##sgistru0"].plurals[0] = "=Squished AbsSine";
    strings["Square##sgistru0"].plurals[0] = "=Square";
    strings["Derived Square##sgistru0"].plurals[0] = "=Derived Square";
    strings["Sine##sgistru1"].plurals[0] = "=Sine";
    strings["Half Sine##sgistru1"].plurals[0] = "=Half Sine";
    strings["Absolute Sine##sgistru1"].plurals[0] = "=Absolute Sine";
    strings["Pulse Sine##sgistru"].plurals[0] = "=Pulse Sine";
    strings["Sine (Even Periods)##sgistru"].plurals[0] = "=Sine (Even Periods)";
    strings["AbsSine (Even Periods)##sgistru"].plurals[0] = "=AbsSine (Even Periods)";
    strings["Square##sgistru1"].plurals[0] = "=Square";
    strings["Derived Square##sgistru1"].plurals[0] = "=Derived Square";
    strings["Sine##sgistru2"].plurals[0] = "=Sine";
    strings["Triangle##sgistru"].plurals[0] = "=Triangle";
    strings["Cut Sine##sgistru"].plurals[0] = "=Cut Sine";
    strings["Cut Triangle##sgistru"].plurals[0] = "=Cut Triangle";
    strings["Squished Sine##sgistru1"].plurals[0] = "=Squished Sine";
    strings["Squished Triangle##sgistru"].plurals[0] = "=Squished Triangle";
    strings["Squished AbsSine##sgistru1"].plurals[0] = "=Squished AbsSine";
    strings["Squished AbsTriangle##sgistru"].plurals[0] = "=Squished AbsTriangle";
    strings["Snare##sgistru0"].plurals[0] = "=Snare";
    strings["Tom##sgistru"].plurals[0] = "=Tom";
    strings["Top##sgistru0"].plurals[0] = "=Top";
    strings["HiHat##sgistru0"].plurals[0] = "=HiHat";
    strings["Normal##sgistru"].plurals[0] = "=Normal";
    strings["Snare##sgistru1"].plurals[0] = "=Snare";
    strings["HiHat##sgistru1"].plurals[0] = "=HiHat";
    strings["Top##sgistru1"].plurals[0] = "=Top";
    strings["Noise disabled##sgistru"].plurals[0] = "=Noise disabled";
    strings["Square + noise##sgistru"].plurals[0] = "=Square + noise";
    strings["Ringmod from OP3 + noise##sgistru"].plurals[0] = "=Ringmod from OP3 + noise";
    strings["Ringmod from OP3 + double pitch ModInput\nWARNING - has emulation issues, subject to change##sgistru"].plurals[0] = "=Ringmod from OP3 + double pitch ModInput\nWARNING - has emulation issues, subject to change";
    strings["op1##sgistru"].plurals[0] = "=op1";
    strings["op2##sgistru"].plurals[0] = "=op2";
    strings["op3##sgistru"].plurals[0] = "=op3";
    strings["op4##sgistru"].plurals[0] = "=op4";
    strings["triangle##sgistru"].plurals[0] = "=triangle";
    strings["saw##sgistru"].plurals[0] = "=saw";
    strings["pulse##sgistru"].plurals[0] = "=pulse";
    strings["noise##sgistru0"].plurals[0] = "=noise";
    strings["tone##sgistru"].plurals[0] = "=tone";
    strings["noise##sgistru1"].plurals[0] = "=noise";
    strings["envelope##sgistru"].plurals[0] = "=envelope";
    strings["hold##sgistru"].plurals[0] = "=hold";
    strings["alternate##sgistru"].plurals[0] = "=alternate";
    strings["direction##sgistru0"].plurals[0] = "=direction";
    strings["enable##sgistru0"].plurals[0] = "=enable";
    strings["enabled##sgistru0"].plurals[0] = "=enabled";
    strings["mirror##sgistru"].plurals[0] = "=mirror";
    strings["loop##sgistru0"].plurals[0] = "=loop";
    strings["cut##sgistru"].plurals[0] = "=cut";
    strings["direction##sgistru1"].plurals[0] = "=direction";
    strings["resolution##sgistru"].plurals[0] = "=resolution";
    strings["fixed##sgistru1"].plurals[0] = "=fixed";
    strings["N/A##sgistru"].plurals[0] = "=N/A";
    strings["enabled##sgistru1"].plurals[0] = "=enabled";
    strings["noise##sgistru2"].plurals[0] = "=noise";
    strings["echo##sgistru"].plurals[0] = "=echo";
    strings["pitch mod##sgistru"].plurals[0] = "=pitch mod";
    strings["invert right##sgistru"].plurals[0] = "=invert right";
    strings["invert left##sgistru"].plurals[0] = "=invert left";
    strings["low##sgistru"].plurals[0] = "=low";
    strings["band##sgistru"].plurals[0] = "=band";
    strings["high##sgistru"].plurals[0] = "=high";
    strings["ch3off##sgistru"].plurals[0] = "=ch3off";
    strings["gate##sgistru"].plurals[0] = "=gate";
    strings["sync##sgistru"].plurals[0] = "=sync";
    strings["ring##sgistru"].plurals[0] = "=ring";
    strings["test##sgistru"].plurals[0] = "=test";
    strings["15kHz##sgistru"].plurals[0] = "=15kHz";
    strings["filter 2+4##sgistru"].plurals[0] = "=filter 2+4";
    strings["filter 1+3##sgistru"].plurals[0] = "=filter 1+3";
    strings["16-bit 3+4##sgistru"].plurals[0] = "=16-bit 3+4";
    strings["16-bit 1+2##sgistru"].plurals[0] = "=16-bit 1+2";
    strings["high3##sgistru"].plurals[0] = "=high3";
    strings["high1##sgistru"].plurals[0] = "=high1";
    strings["poly9##sgistru"].plurals[0] = "=poly9";
    strings["int##sgistru"].plurals[0] = "=int";
    strings["sustain##sgistru2"].plurals[0] = "=sustain";
    strings["square##sgistru2"].plurals[0] = "=square";
    strings["noise##sgistru3"].plurals[0] = "=noise";
    strings["noise##sgistru4"].plurals[0] = "=noise";
    strings["invert##sgistru"].plurals[0] = "=invert";
    strings["surround##sgistru"].plurals[0] = "=surround";
    strings["enable##sgistru1"].plurals[0] = "=enable";
    strings["oneshot##sgistru"].plurals[0] = "=oneshot";
    strings["split L/R##sgistru"].plurals[0] = "=split L/R";
    strings["HinvR##sgistru"].plurals[0] = "=HinvR";
    strings["VinvR##sgistru"].plurals[0] = "=VinvR";
    strings["HinvL##sgistru"].plurals[0] = "=HinvL";
    strings["VinvL##sgistru"].plurals[0] = "=VinvL";
    strings["ring mod##sgistru"].plurals[0] = "=ring mod";
    strings["low pass##sgistru"].plurals[0] = "=low pass";
    strings["high pass##sgistru"].plurals[0] = "=high pass";
    strings["band pass##sgistru"].plurals[0] = "=band pass";
    strings["HP/K2, HP/K2##sgistru"].plurals[0] = "=HP/K2, HP/K2";
    strings["HP/K2, LP/K1##sgistru"].plurals[0] = "=HP/K2, LP/K1";
    strings["LP/K2, LP/K2##sgistru"].plurals[0] = "=LP/K2, LP/K2";
    strings["LP/K2, LP/K1##sgistru"].plurals[0] = "=LP/K2, LP/K1";
    strings["right##sgistru"].plurals[0] = "=right";
    strings["left##sgistru"].plurals[0] = "=left";
    strings["rear right##sgistru"].plurals[0] = "=rear right";
    strings["rear left##sgistru"].plurals[0] = "=rear left";
    strings["enable tap B##sgistru"].plurals[0] = "=enable tap B";
    strings["AM with slope##sgistru"].plurals[0] = "=AM with slope";
    strings["invert B##sgistru"].plurals[0] = "=invert B";
    strings["invert A##sgistru"].plurals[0] = "=invert A";
    strings["reset B##sgistru"].plurals[0] = "=reset B";
    strings["reset A##sgistru"].plurals[0] = "=reset A";
    strings["clip B##sgistru"].plurals[0] = "=clip B";
    strings["clip A##sgistru"].plurals[0] = "=clip A";
    strings["on##sgistru"].plurals[0] = "=on";
    strings["k1 slowdown##sgistru"].plurals[0] = "=k1 slowdown";
    strings["k2 slowdown##sgistru"].plurals[0] = "=k2 slowdown";
    strings["pause##sgistru"].plurals[0] = "=pause";
    strings["reverse##sgistru"].plurals[0] = "=reverse";
    strings["high pass##sgistru1"].plurals[0] = "=high pass";
    strings["ring mod##sgistru1"].plurals[0] = "=ring mod";
    strings["swap counters (noise)##sgistru"].plurals[0] = "=swap counters (noise)";
    strings["low pass (noise)##sgistru"].plurals[0] = "=low pass (noise)";
    strings["sync##sgistru1"].plurals[0] = "=sync";
    strings["ring##sgistru1"].plurals[0] = "=ring";
    strings["low##sgistru1"].plurals[0] = "=low";
    strings["band##sgistru1"].plurals[0] = "=band";
    strings["high##sgistru1"].plurals[0] = "=high";
    strings["8580 SID##sgistru"].plurals[0] = "=8580 SID";
    strings["bitwise AND##sgistru"].plurals[0] = "=bitwise AND";
    strings["bitwise OR##sgistru"].plurals[0] = "=bitwise OR";
    strings["bitwise XOR##sgistru"].plurals[0] = "=bitwise XOR";
    strings["None##sgistru"].plurals[0] = "=None";
    strings["Invert##sgistru"].plurals[0] = "=Invert";
    strings["Add##sgistru"].plurals[0] = "=Add";
    strings["Subtract##sgistru"].plurals[0] = "=Subtract";
    strings["Average##sgistru"].plurals[0] = "=Average";
    strings["Phase##sgistru"].plurals[0] = "=Phase";
    strings["Chorus##sgistru"].plurals[0] = "=Chorus";
    strings["None (dual)##sgistru"].plurals[0] = "=None (dual)";
    strings["Wipe##sgistru"].plurals[0] = "=Wipe";
    strings["Fade##sgistru"].plurals[0] = "=Fade";
    strings["Fade (ping-pong)##sgistru"].plurals[0] = "=Fade (ping-pong)";
    strings["Overlay##sgistru"].plurals[0] = "=Overlay";
    strings["Negative Overlay##sgistru"].plurals[0] = "=Negative Overlay";
    strings["Slide##sgistru"].plurals[0] = "=Slide";
    strings["Mix Chorus##sgistru"].plurals[0] = "=Mix Chorus";
    strings["Phase Modulation##sgistru"].plurals[0] = "=Phase Modulation";
    strings["Envelope##sgistru"].plurals[0] = "=Envelope";
    strings["Sweep##sgistru"].plurals[0] = "=Sweep";
    strings["Wait##sgistru0"].plurals[0] = "=Wait";
    strings["Wait for Release##sgistru0"].plurals[0] = "=Wait for Release";
    strings["Loop##sgistru1"].plurals[0] = "=Loop";
    strings["Loop until Release##sgistru0"].plurals[0] = "=Loop until Release";
    strings["Volume Sweep##sgistru"].plurals[0] = "=Volume Sweep";
    strings["Frequency Sweep##sgistru"].plurals[0] = "=Frequency Sweep";
    strings["Cutoff Sweep##sgistru"].plurals[0] = "=Cutoff Sweep";
    strings["Wait##sgistru1"].plurals[0] = "=Wait";
    strings["Wait for Release##sgistru1"].plurals[0] = "=Wait for Release";
    strings["Loop##sgistru2"].plurals[0] = "=Loop";
    strings["Loop until Release##sgistru1"].plurals[0] = "=Loop until Release";
    strings["Direct##sgistru"].plurals[0] = "=Direct";
    strings["Decrease (linear)##sgistru"].plurals[0] = "=Decrease (linear)";
    strings["Decrease (logarithmic)##sgistru"].plurals[0] = "=Decrease (logarithmic)";
    strings["Increase (linear)##sgistru"].plurals[0] = "=Increase (linear)";
    strings["Increase (bent line)##sgistru"].plurals[0] = "=Increase (bent line)";
    strings["Fixed##sgistru2"].plurals[0] = "=Fixed";
    strings["Relative##sgistru"].plurals[0] = "=Relative";
    strings["QSound##sgistru"].plurals[0] = "=QSound";
    strings["Bug##sgistru"].plurals[0] = "=Bug";

    strings["Fixed"].plurals[0] = "=Fixed";
    strings["Relative"].plurals[0] = "=Relative";
    strings["Local"].plurals[0] = "=Local";
    strings["Global"].plurals[0] = "=Global";

    //   sgiSU     src/gui/inst/su.cpp

    strings["Sound Unit##sgiSU"].plurals[0] = "=Sound Unit";
    strings["Switch roles of frequency and phase reset timer##sgiSU"].plurals[0] = "=Switch roles of frequency and phase reset timer";
    strings["Hardware Sequence##sgiSU"].plurals[0] = "=Hardware Sequence";
    strings["Tick##sgiSU0"].plurals[0] = "=Tick";
    strings["Command##sgiSU0"].plurals[0] = "=Command";
    strings["Move/Remove##sgiSU0"].plurals[0] = "=Move/Remove";
    strings["Period##sgiSU0"].plurals[0] = "=Period";
    strings["Amount##sgiSU0"].plurals[0] = "=Amount";
    strings["Bound##sgiSU0"].plurals[0] = "=Bound";
    strings["Up##sgiSU0"].plurals[0] = "=Up";
    strings["Down##sgiSU0"].plurals[0] = "=Down";
    strings["Loop##sgiSU"].plurals[0] = "=Loop";
    strings["Flip##sgiSU"].plurals[0] = "=Flip";
    strings["Period##sgiSU1"].plurals[0] = "=Period";
    strings["Amount##sgiSU1"].plurals[0] = "=Amount";
    strings["Bound##sgiSU1"].plurals[0] = "=Bound";
    strings["Up##sgiSU1"].plurals[0] = "=Up";
    strings["Down##sgiSU1"].plurals[0] = "=Down";
    strings["Ticks##sgiSU"].plurals[0] = "=Ticks";
    strings["Position##sgiSU"].plurals[0] = "=Position";
    strings["Macros##sgiSU"].plurals[0] = "=Macros";
    strings["Volume##sgiSU"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiSU"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiSU"].plurals[0] = "=Pitch";
    strings["Duty/Noise##sgiSU"].plurals[0] = "=Duty/Noise";
    strings["Waveform##sgiSU"].plurals[0] = "=Waveform";
    strings["Panning##sgiSU"].plurals[0] = "=Panning";
    strings["Phase Reset##sgiSU"].plurals[0] = "=Phase Reset";
    strings["Cutoff##sgiSU"].plurals[0] = "=Cutoff";
    strings["Resonance##sgiSU"].plurals[0] = "=Resonance";
    strings["Control##sgiSU"].plurals[0] = "=Control";
    strings["Phase Reset Timer##sgiSU"].plurals[0] = "=Phase Reset Timer";

    //   sgiSWAN   src/gui/inst/swan.cpp

    strings["Macros##sgiSWAN"].plurals[0] = "=Macros";
    strings["Volume##sgiSWAN"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiSWAN"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiSWAN"].plurals[0] = "=Pitch";
    strings["Noise##sgiSWAN"].plurals[0] = "=Noise";
    strings["Waveform##sgiSWAN"].plurals[0] = "=Waveform";
    strings["Phase Reset##sgiSWAN"].plurals[0] = "=Phase Reset";

    //   sgiT6W    src/gui/inst/t6w28.cpp

    strings["Macros##sgiT6W"].plurals[0] = "=Macros";
    strings["Volume##sgiT6W"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiT6W"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiT6W"].plurals[0] = "=Pitch";
    strings["Panning (left)##sgiT6W"].plurals[0] = "=Panning (left)";
    strings["Panning (right)##sgiT6W"].plurals[0] = "=Panning (right)";
    strings["Noise Type##sgiT6W"].plurals[0] = "=Noise Type";
    strings["Phase Reset##sgiT6W"].plurals[0] = "=Phase Reset";

    //   sgiTED    src/gui/inst/ted.cpp

    strings["Macros##sgiTED"].plurals[0] = "=Macros";
    strings["Volume##sgiTED"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiTED"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiTED"].plurals[0] = "=Pitch";
    strings["Square/Noise##sgiTED"].plurals[0] = "=Square/Noise";
    strings["Phase Reset##sgiTED"].plurals[0] = "=Phase Reset";

    //   sgiTIA    src/gui/inst/tia.cpp

    strings["Macros##sgiTIA"].plurals[0] = "=Macros";
    strings["Volume##sgiTIA"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiTIA"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiTIA"].plurals[0] = "=Pitch";
    strings["Raw Period##sgiTIA"].plurals[0] = "=Raw Period";
    strings["Waveform##sgiTIA"].plurals[0] = "=Waveform";

    //   sgiVB     src/gui/inst/vboy.cpp

    strings["Set modulation table (channel 5 only)##sgiVB"].plurals[0] = "=Set modulation table (channel 5 only)";
    strings["Hex##MTHex"].plurals[0] = "=Hex##MTHex";
    strings["Dec##MTHex"].plurals[0] = "=Dec##MTHex";
    strings["Macros##sgiVB"].plurals[0] = "=Macros";
    strings["Volume##sgiVB"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiVB"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiVB"].plurals[0] = "=Pitch";
    strings["Noise Length##sgiVB"].plurals[0] = "=Noise Length";
    strings["Waveform##sgiVB"].plurals[0] = "=Waveform";
    strings["Panning (left)##sgiVB"].plurals[0] = "=Panning (left)";
    strings["Panning (right)##sgiVB"].plurals[0] = "=Panning (right)";
    strings["Phase Reset##sgiVB"].plurals[0] = "=Phase Reset";

    //   sgiVERA   src/gui/inst/vera.cpp

    strings["Macros##sgiVERA"].plurals[0] = "=Macros";
    strings["Volume##sgiVERA"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiVERA"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiVERA"].plurals[0] = "=Pitch";
    strings["Duty##sgiVERA"].plurals[0] = "=Duty";
    strings["Waveform##sgiVERA"].plurals[0] = "=Waveform";
    strings["Panning##sgiVERA"].plurals[0] = "=Panning";

    //   sgiVIC    src/gui/inst/vic.cpp

    strings["Macros##sgiVIC"].plurals[0] = "=Macros";
    strings["Volume##sgiVIC"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiVIC"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiVIC"].plurals[0] = "=Pitch";
    strings["On/Off##sgiVIC"].plurals[0] = "=On/Off";
    strings["Waveform##sgiVIC"].plurals[0] = "=Waveform";

    //   sgiVRC6   src/gui/inst/vrc6.cpp

    strings["Macros##sgiVRC6"].plurals[0] = "=Macros";
    strings["Volume##sgiVRC6"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiVRC6"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiVRC6"].plurals[0] = "=Pitch";
    strings["Duty##sgiVRC6"].plurals[0] = "=Duty";
    strings["Waveform##sgiVRC6"].plurals[0] = "=Waveform";
    strings["Phase Reset##sgiVRC6"].plurals[0] = "=Phase Reset";

    //   sgiVRC6S  src/gui/inst/vrc6saw.cpp

    strings["Macros##sgiVRC6S"].plurals[0] = "=Macros";
    strings["Volume##sgiVRC6S"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiVRC6S"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiVRC6S"].plurals[0] = "=Pitch";

    //   sgiwave   src/gui/inst/wavetable.cpp

    strings["Wavetable##sgiwave"].plurals[0] = "=Wavetable";
    strings["Enable synthesizer##sgiwave"].plurals[0] = "=Enable synthesizer";
    strings["Single-waveform##sgiwave"].plurals[0] = "=Single-waveform";
    strings["Dual-waveform##sgiwave"].plurals[0] = "=Dual-waveform";
    strings["Wave 1##sgiwave0"].plurals[0] = "=Wave 1";
    strings["Wave 2##sgiwave0"].plurals[0] = "=Wave 2";
    strings["Result##sgiwave"].plurals[0] = "=Result";
    strings["Wave 1 ##sgiwave"].plurals[0] = "=Wave 1 ";
    strings["waveform macro is controlling wave 1!\nthis value will be ineffective.##sgiwave"].plurals[0] = "=waveform macro is controlling wave 1!\nthis value will be ineffective.";
    strings["Wave 1##sgiwave1"].plurals[0] = "=Wave 1";
    strings["Wave 2##sgiwave1"].plurals[0] = "=Wave 2";
    strings["Resume preview##sgiwave"].plurals[0] = "=Resume preview";
    strings["Pause preview##sgiwave"].plurals[0] = "=Pause preview";
    strings["Restart preview##sgiwave"].plurals[0] = "=Restart preview";
    strings["too many wavetables!##sgiwave"].plurals[0] = "=too many wavetables!";
    strings["Copy to new wavetable##sgiwave"].plurals[0] = "=Copy to new wavetable";
    strings["Update Rate##sgiwave"].plurals[0] = "=Update Rate";
    strings["Speed##sgiwave"].plurals[0] = "=Speed";
    strings["Amount##sgiwave"].plurals[0] = "=Amount";
    strings["Power##sgiwave"].plurals[0] = "=Power";
    strings["Global##sgiwave"].plurals[0] = "=Global";
    strings["Global##sgiwave1"].plurals[0] = "=Global";
    strings["Global##sgiwave2"].plurals[0] = "=Global##jesus";
    strings["wavetable synthesizer disabled.\nuse the Waveform macro to set the wave for this instrument.##sgiwave"].plurals[0] = "=wavetable synthesizer disabled.\nuse the Waveform macro to set the wave for this instrument.";
    strings["Local Waves##sgiwave"].plurals[0] = "=Local Waves";

    //   sgiX1     src/gui/inst/x1_010.cpp

    strings["Macros##sgiX1"].plurals[0] = "=Macros";
    strings["Volume##sgiX1"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiX1"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiX1"].plurals[0] = "=Pitch";
    strings["Waveform##sgiX1"].plurals[0] = "=Waveform";
    strings["Panning (left)##sgiX1"].plurals[0] = "=Panning (left)";
    strings["Panning (right)##sgiX1"].plurals[0] = "=Panning (right)";
    strings["Phase Reset##sgiX1"].plurals[0] = "=Phase Reset";
    strings["Envelope##sgiX1"].plurals[0] = "=Envelope";
    strings["Envelope Mode##sgiX1"].plurals[0] = "=Envelope Mode";
    strings["AutoEnv Num##sgiX1"].plurals[0] = "=AutoEnv Num";
    strings["AutoEnv Den##sgiX1"].plurals[0] = "=AutoEnv Den";

    //   sgiYMZ    src/gui/inst/ymz280b.cpp

    strings["Macros##sgiYMZ"].plurals[0] = "=Macros";
    strings["Volume##sgiYMZ"].plurals[0] = "=Volume";
    strings["Arpeggio##sgiYMZ"].plurals[0] = "=Arpeggio";
    strings["Pitch##sgiYMZ"].plurals[0] = "=Pitch";
    strings["Panning##sgiYMZ"].plurals[0] = "=Panning";
    strings["Phase Reset##sgiYMZ"].plurals[0] = "=Phase Reset";

    //   se**    src/engine/
    //   seen    src/engine/engine.cpp
    //   sesd    src/engine/sysDef.cpp

    //           src/engine/cmdStream.cpp

    strings["not a command stream"].plurals[0] = "=not a command stream";

    //   seen    src/engine/engine.cpp

    strings["00xy: Arpeggio##seen"].plurals[0] = "00xy: =Arpeggio";
    strings["01xx: Pitch slide up##seen"].plurals[0] = "01xx: =Pitch slide up";
    strings["02xx: Pitch slide down##seen"].plurals[0] = "02xx: =Pitch slide down";
    strings["03xx: Portamento##seen"].plurals[0] = "03xx: =Portamento";
    strings["04xy: Vibrato (x: speed; y: depth)##seen"].plurals[0] = "04xy: =Vibrato (x: speed; y: depth)";
    strings["05xy: Volume slide + vibrato (compatibility only!)##seen"].plurals[0] = "05xy: =Volume slide + vibrato (compatibility only!)";
    strings["06xy: Volume slide + portamento (compatibility only!)##seen"].plurals[0] = "06xy: =Volume slide + portamento (compatibility only!)";
    strings["07xy: Tremolo (x: speed; y: depth)##seen"].plurals[0] = "07xy: =Tremolo (x: speed; y: depth)";
    strings["08xy: Set panning (x: left; y: right)##seen"].plurals[0] = "08xy: =Set panning (x: left; y: right)";
    strings["09xx: Set groove pattern (speed 1 if no grooves exist)##seen"].plurals[0] = "09xx: =Set groove pattern (speed 1 if no grooves exist)";
    strings["0Axy: Volume slide (0y: down; x0: up)##seen"].plurals[0] = "0Axy: =Volume slide (0y: down; x0: up)";
    strings["0Bxx: Jump to pattern##seen"].plurals[0] = "0Bxx: =Jump to pattern";
    strings["0Cxx: Retrigger##seen"].plurals[0] = "0Cxx: =Retrigger";
    strings["0Dxx: Jump to next pattern##seen"].plurals[0] = "0Dxx: =Jump to next pattern";
    strings["0Fxx: Set speed (speed 2 if no grooves exist)##seen"].plurals[0] = "0Fxx: =Set speed (speed 2 if no grooves exist)";
    strings["80xx: Set panning (00: left; 80: center; FF: right)##seen"].plurals[0] = "80xx: =Set panning (00: left; 80: center; FF: right)";
    strings["81xx: Set panning (left channel)##seen"].plurals[0] = "81xx: =Set panning (left channel)";
    strings["82xx: Set panning (right channel)##seen"].plurals[0] = "82xx: =Set panning (right channel)";
    strings["88xy: Set panning (rear channels; x: left; y: right)##seen"].plurals[0] = "88xy: =Set panning (rear channels; x: left; y: right)";
    strings["89xx: Set panning (rear left channel)##seen"].plurals[0] = "89xx: =Set panning (rear left channel)";
    strings["8Axx: Set panning (rear right channel)##seen"].plurals[0] = "8Axx: =Set panning (rear right channel)";
    strings["Cxxx: Set tick rate (hz)##seen"].plurals[0] = "Cxxx: =Set tick rate (hz)";
    strings["E0xx: Set arp speed##seen"].plurals[0] = "E0xx: =Set arp speed";
    strings["E1xy: Note slide up (x: speed; y: semitones)##seen"].plurals[0] = "E1xy: =Note slide up (x: speed; y: semitones)";
    strings["E2xy: Note slide down (x: speed; y: semitones)##seen"].plurals[0] = "E2xy: =Note slide down (x: speed; y: semitones)";
    strings["E3xx: Set vibrato shape (0: up/down; 1: up only; 2: down only)##seen"].plurals[0] = "E3xx: =Set vibrato shape (0: up/down; 1: up only; 2: down only)";
    strings["E4xx: Set vibrato range##seen"].plurals[0] = "E4xx: =Set vibrato range";
    strings["E5xx: Set pitch (80: center)##seen"].plurals[0] = "E5xx: =Set pitch (80: center)";
    strings["E6xy: Delayed note transpose (x: 0-7 = up, 8-F = down (after (x % 7) ticks); y: semitones)##seen"].plurals[0] = "E6xy: =Delayed note transpose (x: 0-7 = up, 8-F = down (after (x % 7) ticks); y: semitones)";
    strings["E7xx: Macro release##seen"].plurals[0] = "E7xx: =Macro release";
    strings["E8xy: Delayed note transpose up (x: ticks; y: semitones)##seen"].plurals[0] = "E8xy: =Delayed note transpose up (x: ticks; y: semitones)";
    strings["E9xy: Delayed note transpose down (x: ticks; y: semitones)##seen"].plurals[0] = "E9xy: =Delayed note transpose down (x: ticks; y: semitones)";
    strings["EAxx: Legato##seen"].plurals[0] = "EAxx: =Legato";
    strings["EBxx: Set LEGACY sample mode bank##seen"].plurals[0] = "EBxx: =Set LEGACY sample mode bank";
    strings["ECxx: Note cut##seen"].plurals[0] = "ECxx: =Note cut";
    strings["EDxx: Note delay##seen"].plurals[0] = "EDxx: =Note delay";
    strings["EExx: Send external command##seen"].plurals[0] = "EExx: =Send external command";
    strings["F0xx: Set tick rate (bpm)##seen"].plurals[0] = "F0xx: =Set tick rate (bpm)";
    strings["F1xx: Single tick note slide up##seen"].plurals[0] = "F1xx: =Single tick note slide up";
    strings["F2xx: Single tick note slide down##seen"].plurals[0] = "F2xx: =Single tick note slide down";
    strings["F3xx: Fine volume slide up##seen"].plurals[0] = "F3xx: =Fine volume slide up";
    strings["F4xx: Fine volume slide down##seen"].plurals[0] = "F4xx: =Fine volume slide down";
    strings["F5xx: Disable macro (see manual)##seen"].plurals[0] = "F5xx: =Disable macro (see manual)";
    strings["F6xx: Enable macro (see manual)##seen"].plurals[0] = "F6xx: =Enable macro (see manual)";
    strings["F7xx: Restart macro (see manual)##seen"].plurals[0] = "F7xx: =Restart macro (see manual)";
    strings["F8xx: Single tick volume slide up##seen"].plurals[0] = "F8xx: =Single tick volume slide up";
    strings["F9xx: Single tick volume slide down##seen"].plurals[0] = "F9xx: =Single tick volume slide down";
    strings["FAxx: Fast volume slide (0y: down; x0: up)##seen"].plurals[0] = "FAxx: =Fast volume slide (0y: down; x0: up)";
    strings["FCxx: Note release##seen"].plurals[0] = "FCxx: =Note release";
    strings["FDxx: Set virtual tempo numerator##seen"].plurals[0] = "FDxx: =Set virtual tempo numerator";
    strings["FExx: Set virtual tempo denominator##seen"].plurals[0] = "FExx: =Set virtual tempo denominator";
    strings["FFxx: Stop song##seen"].plurals[0] = "FFxx: =Stop song";
    strings["9xxx: Set sample offset*256##seen"].plurals[0] = "9xxx: =Set sample offset*256";

    strings["on seek: %s"].plurals[0] = "=on seek: %s";
    strings["on pre tell: %s"].plurals[0] = "=on pre tell: %s";
    strings["file is empty"].plurals[0] = "=file is empty";
    strings["on tell: %s"].plurals[0] = "=on tell: %s";
    strings["ROM size mismatch, expected: %d bytes, was: %d"].plurals[0] = "=ROM size mismatch, expected: %d bytes, was: %d";
    strings["on get size: %s"].plurals[0] = "=on get size: %s";
    strings["on read: %s"].plurals[0] = "=on read: %s";
    strings["invalid index"].plurals[0] = "=invalid index";
    strings["max number of total channels is %d"].plurals[0] = "=max number of total channels is %d";
    strings["max number of systems is %d"].plurals[0] = "=max number of systems is %d";
    strings["cannot remove the last one"].plurals[0] = "=cannot remove the last one";
    strings["source and destination are equal"].plurals[0] = "=source and destination are equal";
    strings["invalid source index"].plurals[0] = "=invalid source index";
    strings["invalid destination index"].plurals[0] = "=invalid destination index";
    strings["too many wavetables!"].plurals[0] = "=too many wavetables!";
    strings["could not seek to end: %s"].plurals[0] = "=could not seek to end: %s";
    strings["could not determine file size: %s"].plurals[0] = "=could not determine file size: %s";
    strings["file size is invalid!"].plurals[0] = "=file size is invalid!";
    strings["could not seek to beginning: %s"].plurals[0] = "=could not seek to beginning: %s";
    strings["could not read entire file: %s"].plurals[0] = "=could not read entire file: %s";
    strings["invalid wavetable header/data!"].plurals[0] = "=invalid wavetable header/data!";
    strings["premature end of file"].plurals[0] = "=premature end of file";
    strings["too many samples!"].plurals[0] = "=too many samples!";
    strings["no free patterns in channel %d!"].plurals[0] = "=no free patterns in channel %d!";

    //           src/engine/fileOps.cpp

    strings["this module was created with a more recent version of Furnace!"].plurals[0] = "=this module was created with a more recent version of Furnace!";
    strings["couldn't seek to info header!"].plurals[0] = "=couldn't seek to info header!";
    strings["invalid info header!"].plurals[0] = "=invalid info header!";
    strings["pattern length is negative!"].plurals[0] = "=pattern length is negative!";
    strings["pattern length is too large!"].plurals[0] = "=pattern length is too large!";
    strings["song length is negative!"].plurals[0] = "=song length is negative!";
    strings["song is too long!"].plurals[0] = "=song is too long!";
    strings["invalid instrument count!"].plurals[0] = "=invalid instrument count!";
    strings["invalid wavetable count!"].plurals[0] = "=invalid wavetable count!";
    strings["invalid sample count!"].plurals[0] = "=invalid sample count!";
    strings["invalid pattern count!"].plurals[0] = "=invalid pattern count!";
    strings["unrecognized system ID %.2x!"].plurals[0] = "=unrecognized system ID %.2x!";
    strings["zero chips!"].plurals[0] = "=zero chips!";
    strings["channel %d has too many effect columns! (%d)"].plurals[0] = "=channel %d has too many effect columns! (%d)";
    strings["couldn't seek to chip %d flags!"].plurals[0] = "=couldn't seek to chip %d flags!";
    strings["invalid flag header!"].plurals[0] = "=invalid flag header!";
    strings["couldn't read instrument directory"].plurals[0] = "=couldn't read instrument directory";
    strings["invalid instrument directory data!"].plurals[0] = "=invalid instrument directory data!";
    strings["couldn't read wavetable directory"].plurals[0] = "=couldn't read wavetable directory";
    strings["invalid wavetable directory data!"].plurals[0] = "=invalid wavetable directory data!";
    strings["couldn't read sample directory"].plurals[0] = "=couldn't read sample directory";
    strings["invalid sample directory data!"].plurals[0] = "=invalid sample directory data!";
    strings["couldn't seek to subsong %d!"].plurals[0] = "=couldn't seek to subsong %d!";
    strings["invalid subsong header!"].plurals[0] = "=invalid subsong header!";
    strings["couldn't seek to instrument %d!"].plurals[0] = "=couldn't seek to instrument %d!";
    strings["invalid instrument header/data!"].plurals[0] = "=invalid instrument header/data!";
    strings["couldn't seek to wavetable %d!"].plurals[0] = "=couldn't seek to wavetable %d!";
    strings["couldn't seek to sample %d!"].plurals[0] = "=couldn't seek to sample %d!";
    strings["invalid sample header/data!"].plurals[0] = "=invalid sample header/data!";
    strings["couldn't seek to pattern in %x!"].plurals[0] = "=couldn't seek to pattern in %x!";
    strings["invalid pattern header!"].plurals[0] = "=invalid pattern header!";
    strings["pattern channel out of range!"].plurals[0] = "=pattern channel out of range!";
    strings["pattern index out of range!"].plurals[0] = "=pattern index out of range!";
    strings["pattern subsong out of range!"].plurals[0] = "=pattern subsong out of range!";
    strings["incomplete file"].plurals[0] = "=incomplete file";
    strings["file is too small"].plurals[0] = "=file is too small";
    strings["not a .dmf/.fur/.fub song"].plurals[0] = "=not a .dmf/.fur/.fub song";
    strings["unknown decompression error"].plurals[0] = "=unknown decompression error";
    strings["decompression error: %s"].plurals[0] = "=decompression error: %s";
    strings["unknown decompression finish error"].plurals[0] = "=unknown decompression finish error";
    strings["decompression finish error: %s"].plurals[0] = "=decompression finish error: %s";
    strings["not a compatible song/instrument"].plurals[0] = "=not a compatible song/instrument";
    strings["maximum number of instruments is 256"].plurals[0] = "=maximum number of instruments is 256";
    strings["maximum number of wavetables is 256"].plurals[0] = "=maximum number of wavetables is 256";
    strings["maximum number of samples is 256"].plurals[0] = "=maximum number of samples is 256";

    //           src/engine/fileOpsIns.cpp

    strings["did not read entire instrument file!"].plurals[0] = "=did not read entire instrument file!";
    strings["this instrument is made with a more recent version of Furnace!"].plurals[0] = "=this instrument is made with a more recent version of Furnace!";
    strings["unknown instrument format"].plurals[0] = "=unknown instrument format";
    strings["there is more data at the end of the file! what happened here!"].plurals[0] = "=there is more data at the end of the file! what happened here!";
    strings["exactly %d bytes, if you are curious"].plurals[0] = "=exactly %d bytes, if you are curious";

    //           src/engine/fileOpsSample.cpp

    strings["could not open file! (%s)"].plurals[0] = "=could not open file! (%s)";
    strings["could not get file length! (%s)"].plurals[0] = "=could not get file length! (%s)";
    strings["file is empty!"].plurals[0] = "=file is empty!";
    strings["file is invalid!"].plurals[0] = "=file is invalid!";
    strings["could not seek to beginning of file! (%s)"].plurals[0] = "=could not seek to beginning of file! (%s)";
    strings["wait... is that right? no I don't think so..."].plurals[0] = "=wait... is that right? no I don't think so...";
    strings["BRR sample is empty!"].plurals[0] = "=BRR sample is empty!";
    strings["possibly corrupt BRR sample!"].plurals[0] = "=possibly corrupt BRR sample!";
    strings["could not read file! (%s)"].plurals[0] = "=could not read file! (%s)";
    strings["Furnace was not compiled with libsndfile!"].plurals[0] = "=Furnace was not compiled with libsndfile!";
    strings["could not open file! (%s %s)"].plurals[0] = "=could not open file! (%s %s)";
    strings["could not open file! (%s)\nif this is raw sample data, you may import it by right-clicking the Load Sample icon and selecting \"import raw\"."].plurals[0] = "=could not open file! (%s)\nif this is raw sample data, you may import it by right-clicking the Load Sample icon and selecting \"import raw\".";
    strings["this sample is too big! max sample size is 16777215."].plurals[0] = "=this sample is too big! max sample size is 16777215.";

    //           src/engine/importExport/bnk.cpp

    strings["GEMS BNK currently not supported."].plurals[0] = "=GEMS BNK currently not supported.";

    //           src/engine/importExport/dmf.cpp

    strings["this version is not supported by Furnace yet"].plurals[0] = "=this version is not supported by Furnace yet";
    strings["system not supported. running old version?"].plurals[0] = "=system not supported. running old version?";
    strings["Yamaha YMU759 emulation is incomplete! please migrate your song to the OPL3 system."].plurals[0] = "=Yamaha YMU759 emulation is incomplete! please migrate your song to the OPL3 system.";
    strings["order at %d, %d out of range! (%d)"].plurals[0] = "=order at %d, %d out of range! (%d)";
    strings["file is corrupt or unreadable at operators"].plurals[0] = "=file is corrupt or unreadable at operators";
    strings["file is corrupt or unreadable at wavetables"].plurals[0] = "=file is corrupt or unreadable at wavetables";
    strings["file is corrupt or unreadable at effect columns"].plurals[0] = "=file is corrupt or unreadable at effect columns";
    strings["file is corrupt or unreadable at samples"].plurals[0] = "=file is corrupt or unreadable at samples";
    strings["invalid version to save in! this is a bug!"].plurals[0] = "=invalid version to save in! this is a bug!";
    strings["multiple systems not possible on .dmf"].plurals[0] = "=multiple systems not possible on .dmf";
    strings["YMU759 song saving is not supported"].plurals[0] = "=YMU759 song saving is not supported";
    strings["Master System FM expansion not supported in 1.0/legacy .dmf!"].plurals[0] = "=Master System FM expansion not supported in 1.0/legacy .dmf!";
    strings["NES + VRC7 not supported in 1.0/legacy .dmf!"].plurals[0] = "=NES + VRC7 not supported in 1.0/legacy .dmf!";
    strings["FDS not supported in 1.0/legacy .dmf!"].plurals[0] = "=FDS not supported in 1.0/legacy .dmf!";
    strings["this system is not possible on .dmf"].plurals[0] = "=this system is not possible on .dmf";
    strings["maximum .dmf song length is 127"].plurals[0] = "=maximum .dmf song length is 127";
    strings["maximum number of instruments in .dmf is 128"].plurals[0] = "=maximum number of instruments in .dmf is 128";
    strings["maximum number of wavetables in .dmf is 64"].plurals[0] = "=maximum number of wavetables in .dmf is 64";
    strings["order %d, %d is out of range (0-127)"].plurals[0] = "=order %d, %d is out of range (0-127)";
    strings["only the currently selected subsong will be saved"].plurals[0] = "=only the currently selected subsong will be saved";
    strings["grooves will not be saved"].plurals[0] = "=grooves will not be saved";
    strings["only the first two speeds will be effective"].plurals[0] = "=only the first two speeds will be effective";
    strings[".dmf format does not support virtual tempo"].plurals[0] = "=.dmf format does not support virtual tempo";
    strings[".dmf format does not support tuning"].plurals[0] = "=.dmf format does not support tuning";
    strings["absolute duty/cutoff macro not available in .dmf!"].plurals[0] = "=absolute duty/cutoff macro not available in .dmf!";
    strings["duty precision will be lost"].plurals[0] = "=duty precision will be lost";
    strings[".dmf format does not support arbitrary-pitch sample mode"].plurals[0] = "=.dmf format does not support arbitrary-pitch sample mode";
    strings["no FM macros in .dmf format"].plurals[0] = "=no FM macros in .dmf format";
    strings[".dmf only supports volume or cutoff macro in C64, but not both. volume macro will be lost."].plurals[0] = "=.dmf only supports volume or cutoff macro in C64, but not both. volume macro will be lost.";
    strings["note/macro release will be converted to note off!"].plurals[0] = "=note/macro release will be converted to note off!";
    strings["samples' rates will be rounded to nearest compatible value"].plurals[0] = "=samples' rates will be rounded to nearest compatible value";

    //           src/engine/importExport/dmp.cpp

    strings["unknown instrument type %d!"].plurals[0] = "=unknown instrument type %d!";

    //           src/engine/importExport/fc.cpp

    strings["invalid header!"].plurals[0] = "=invalid header!";

    //           src/engine/importExport/ftm.cpp

    strings["incompatible version"].plurals[0] = "=incompatible version";
    strings["channel counts do not match"].plurals[0] = "=channel counts do not match";
    strings["too many instruments/out of range"].plurals[0] = "=too many instruments/out of range";
    strings["invalid instrument type"].plurals[0] = "=invalid instrument type";
    strings["too many sequences"].plurals[0] = "=too many sequences";
    strings["sequences block version is too old"].plurals[0] = "=sequences block version is too old";
    strings["unknown block "].plurals[0] = "=unknown block ";
    strings["incomplete block "].plurals[0] = "=incomplete block ";
    strings[" [VRC6 copy]"].plurals[0] = " [=VRC6 copy]";
    strings[" [VRC6 saw copy]"].plurals[0] = " [=VRC6 saw copy]";
    strings[" [NES copy]"].plurals[0] = " [=NES copy]";

    //           src/engine/importExport/gyb.cpp

    strings["GYBv3 file appears to have invalid data offsets."].plurals[0] = "=GYBv3 file appears to have invalid data offsets.";
    strings["Invalid value found in patch file. %s"].plurals[0] = "=Invalid value found in patch file. %s";

    //           src/engine/importExport/s3i.cpp

    strings["S3I PCM samples currently not supported."].plurals[0] = "=S3I PCM samples currently not supported.";

    //           src/engine/vgmOps.cpp

    strings["VGM version is too low"].plurals[0] = "=VGM version is too low";

    //names of memory composition memories

    strings["DPCM"].plurals[0] = "=DPCM";
    strings["Chip Memory"].plurals[0] = "=Chip Memory";
    strings["Sample ROM"].plurals[0] = "=Sample ROM";
    strings["Sample Memory"].plurals[0] = "=Sample Memory";
    strings["SPC/DSP Memory"].plurals[0] = "=SPC/DSP Memory";
    strings["Sample RAM"].plurals[0] = "=Sample RAM";
    strings["ADPCM"].plurals[0] = "=ADPCM";

    //names of memory entries

    strings["Sample"].plurals[0] = "=Sample";
    strings["Wave RAM"].plurals[0] = "=Wave RAM";
    strings["End of Sample"].plurals[0] = "=End of Sample";
    strings["Wavetable RAM"].plurals[0] = "=Wavetable RAM";
    strings["Reserved wavetable RAM"].plurals[0] = "=Reserved wavetable RAM";
    strings["Phrase Book"].plurals[0] = "=Phrase Book";
    strings["Channel %d (load)"].plurals[0] = "=Channel %d (load)";
    strings["Channel %d (play)"].plurals[0] = "=Channel %d (play)";
    strings["Channel %d"].plurals[0] = "=Channel %d";
    strings["Buffer %d Left"].plurals[0] = "=Buffer %d Left";
    strings["Buffer %d Right"].plurals[0] = "=Buffer %d Right";
    strings["Registers"].plurals[0] = "=Registers";
    strings["PCM"].plurals[0] = "=PCM";
    strings["ADPCM"].plurals[0] = "=ADPCM";
    strings["State"].plurals[0] = "=State";
    strings["Sample Directory"].plurals[0] = "=Sample Directory";
    strings["Echo Buffer"].plurals[0] = "=Echo Buffer";
    strings["Mix/Echo Buffer"].plurals[0] = "=Mix/Echo Buffer";
    strings["Main Memory"].plurals[0] = "=Main Memory";

    //   sesd    src/engine/sysDef.cpp

    strings["help! what's going on!"].plurals[0] = "=help! what's going on!";
    strings["Sunsoft 5B standalone##sesd"].plurals[0] = "=Sunsoft 5B standalone";
    strings["Sunsoft 5B standalone (PAL)##sesd"].plurals[0] = "=Sunsoft 5B standalone (PAL)";
    strings["Overclocked Sunsoft 5B##sesd"].plurals[0] = "=Overclocked Sunsoft 5B";
    strings["Sega Genesis Extended Channel 3##sesd0"].plurals[0] = "=Sega Genesis Extended Channel 3";
    strings["NTSC-J Sega Master System + drums##sesd"].plurals[0] = "=NTSC-J Sega Master System + drums";
    strings["MSX-MUSIC + drums##sesd"].plurals[0] = "=MSX-MUSIC + drums";
    strings["Commodore 64 with dual 6581##sesd"].plurals[0] = "=Commodore 64 with dual 6581";
    strings["Commodore 64 with dual 8580##sesd"].plurals[0] = "=Commodore 64 with dual 8580";
    strings["YM2151 + SegaPCM Arcade (compatibility)##sesd"].plurals[0] = "=YM2151 + SegaPCM Arcade (compatibility)";
    strings["YM2151 + SegaPCM Arcade##sesd"].plurals[0] = "=YM2151 + SegaPCM Arcade";
    strings["Game Boy with AY expansion##sesd"].plurals[0] = "=Game Boy with AY expansion";
    strings["multi-system##sesd"].plurals[0] = "=multi-system";
    strings["Unknown##sesd"].plurals[0] = "=Unknown";
    strings["15xx: Set raw period##sesd"].plurals[0] = "=15xx: Set raw period";
    strings["16xx: Set raw period higher nybble (0-F)##sesd"].plurals[0] = "=16xx: Set raw period higher nybble (0-F)";
    strings["20xx: Set channel mode (bit 0: square; bit 1: noise; bit 2: envelope)##sesd"].plurals[0] = "=20xx: Set channel mode (bit 0: square; bit 1: noise; bit 2: envelope)";
    strings["21xx: Set noise frequency (0 to 1F)##sesd"].plurals[0] = "=21xx: Set noise frequency (0 to 1F)";
    strings["22xy: Set envelope mode (x: shape, y: enable for this channel)##sesd"].plurals[0] = "=22xy: Set envelope mode (x: shape, y: enable for this channel)";
    strings["23xx: Set envelope period low byte##sesd"].plurals[0] = "=23xx: Set envelope period low byte";
    strings["24xx: Set envelope period high byte##sesd"].plurals[0] = "=24xx: Set envelope period high byte";
    strings["25xx: Envelope slide up##sesd0"].plurals[0] = "=25xx: Envelope slide up";
    strings["26xx: Envelope slide down##sesd0"].plurals[0] = "=26xx: Envelope slide down";
    strings["29xy: Set auto-envelope (x: numerator; y: denominator)##sesd0"].plurals[0] = "=29xy: Set auto-envelope (x: numerator; y: denominator)";
    strings["2Exx: Write to I/O port A##sesd"].plurals[0] = "=2Exx: Write to I/O port A";
    strings["2Fxx: Write to I/O port B##sesd"].plurals[0] = "=2Fxx: Write to I/O port B";
    strings["12xx: Set duty cycle (0 to 8)##sesd"].plurals[0] = "=12xx: Set duty cycle (0 to 8)";
    strings["16xx: Set raw period higher byte##sesd"].plurals[0] = "=16xx: Set raw period higher byte";
    strings["27xx: Set noise AND mask##sesd"].plurals[0] = "=27xx: Set noise AND mask";
    strings["28xx: Set noise OR mask##sesd"].plurals[0] = "=28xx: Set noise OR mask";
    strings["2Dxx: NOT TO BE EMPLOYED BY THE COMPOSER##sesd"].plurals[0] = "=2Dxx: NOT TO BE EMPLOYED BY THE COMPOSER";
    strings["30xx: Toggle hard envelope reset on new notes##sesd"].plurals[0] = "=30xx: Toggle hard envelope reset on new notes";
    strings["18xx: Toggle extended channel 3 mode##sesd"].plurals[0] = "=18xx: Toggle extended channel 3 mode";
    strings["17xx: Toggle PCM mode (LEGACY)##sesd0"].plurals[0] = "=17xx: Toggle PCM mode (LEGACY)";
    strings["DFxx: Set sample playback direction (0: normal; 1: reverse)##sesd0"].plurals[0] = "=DFxx: Set sample playback direction (0: normal; 1: reverse)";
    strings["18xx: Toggle drums mode (1: enabled; 0: disabled)##sesd"].plurals[0] = "=18xx: Toggle drums mode (1: enabled; 0: disabled)";
    strings["11xx: Set feedback (0 to 7)##sesd0"].plurals[0] = "=11xx: Set feedback (0 to 7)";
    strings["12xx: Set level of operator 1 (0 highest, 7F lowest)##sesd"].plurals[0] = "=12xx: Set level of operator 1 (0 highest, 7F lowest)";
    strings["13xx: Set level of operator 2 (0 highest, 7F lowest)##sesd"].plurals[0] = "=13xx: Set level of operator 2 (0 highest, 7F lowest)";
    strings["14xx: Set level of operator 3 (0 highest, 7F lowest)##sesd"].plurals[0] = "=14xx: Set level of operator 3 (0 highest, 7F lowest)";
    strings["15xx: Set level of operator 4 (0 highest, 7F lowest)##sesd"].plurals[0] = "=15xx: Set level of operator 4 (0 highest, 7F lowest)";
    strings["16xy: Set operator multiplier (x: operator from 1 to 4; y: multiplier)##sesd0"].plurals[0] = "=16xy: Set operator multiplier (x: operator from 1 to 4; y: multiplier)";
    strings["19xx: Set attack of all operators (0 to 1F)##sesd"].plurals[0] = "=19xx: Set attack of all operators (0 to 1F)";
    strings["1Axx: Set attack of operator 1 (0 to 1F)##sesd"].plurals[0] = "=1Axx: Set attack of operator 1 (0 to 1F)";
    strings["1Bxx: Set attack of operator 2 (0 to 1F)##sesd"].plurals[0] = "=1Bxx: Set attack of operator 2 (0 to 1F)";
    strings["1Cxx: Set attack of operator 3 (0 to 1F)##sesd"].plurals[0] = "=1Cxx: Set attack of operator 3 (0 to 1F)";
    strings["1Dxx: Set attack of operator 4 (0 to 1F)##sesd"].plurals[0] = "=1Dxx: Set attack of operator 4 (0 to 1F)";
    strings["50xy: Set AM (x: operator from 1 to 4 (0 for all ops); y: AM)##sesd0"].plurals[0] = "=50xy: Set AM (x: operator from 1 to 4 (0 for all ops); y: AM)";
    strings["51xy: Set sustain level (x: operator from 1 to 4 (0 for all ops); y: sustain)##sesd0"].plurals[0] = "=51xy: Set sustain level (x: operator from 1 to 4 (0 for all ops); y: sustain)";
    strings["52xy: Set release (x: operator from 1 to 4 (0 for all ops); y: release)##sesd0"].plurals[0] = "=52xy: Set release (x: operator from 1 to 4 (0 for all ops); y: release)";
    strings["53xy: Set detune (x: operator from 1 to 4 (0 for all ops); y: detune where 3 is center)##sesd"].plurals[0] = "=53xy: Set detune (x: operator from 1 to 4 (0 for all ops); y: detune where 3 is center)";
    strings["54xy: Set envelope scale (x: operator from 1 to 4 (0 for all ops); y: scale from 0 to 3)##sesd0"].plurals[0] = "=54xy: Set envelope scale (x: operator from 1 to 4 (0 for all ops); y: scale from 0 to 3)";
    strings["56xx: Set decay of all operators (0 to 1F)##sesd"].plurals[0] = "=56xx: Set decay of all operators (0 to 1F)";
    strings["57xx: Set decay of operator 1 (0 to 1F)##sesd"].plurals[0] = "=57xx: Set decay of operator 1 (0 to 1F)";
    strings["58xx: Set decay of operator 2 (0 to 1F)##sesd"].plurals[0] = "=58xx: Set decay of operator 2 (0 to 1F)";
    strings["59xx: Set decay of operator 3 (0 to 1F)##sesd"].plurals[0] = "=59xx: Set decay of operator 3 (0 to 1F)";
    strings["5Axx: Set decay of operator 4 (0 to 1F)##sesd"].plurals[0] = "=5Axx: Set decay of operator 4 (0 to 1F)";
    strings["5Bxx: Set decay 2 of all operators (0 to 1F)##sesd"].plurals[0] = "=5Bxx: Set decay 2 of all operators (0 to 1F)";
    strings["5Cxx: Set decay 2 of operator 1 (0 to 1F)##sesd"].plurals[0] = "=5Cxx: Set decay 2 of operator 1 (0 to 1F)";
    strings["5Dxx: Set decay 2 of operator 2 (0 to 1F)##sesd"].plurals[0] = "=5Dxx: Set decay 2 of operator 2 (0 to 1F)";
    strings["5Exx: Set decay 2 of operator 3 (0 to 1F)##sesd"].plurals[0] = "=5Exx: Set decay 2 of operator 3 (0 to 1F)";
    strings["5Fxx: Set decay 2 of operator 4 (0 to 1F)##sesd"].plurals[0] = "=5Fxx: Set decay 2 of operator 4 (0 to 1F)";
    strings["10xx: Set noise frequency (xx: value; 0 disables noise)##sesd"].plurals[0] = "=10xx: Set noise frequency (xx: value; 0 disables noise)";
    strings["17xx: Set LFO speed##sesd"].plurals[0] = "=17xx: Set LFO speed";
    strings["18xx: Set LFO waveform (0 saw, 1 square, 2 triangle, 3 noise)##sesd"].plurals[0] = "=18xx: Set LFO waveform (0 saw, 1 square, 2 triangle, 3 noise)";
    strings["1Exx: Set AM depth (0 to 7F)##sesd"].plurals[0] = "=1Exx: Set AM depth (0 to 7F)";
    strings["1Fxx: Set PM depth (0 to 7F)##sesd"].plurals[0] = "=1Fxx: Set PM depth (0 to 7F)";
    strings["55xy: Set detune 2 (x: operator from 1 to 4 (0 for all ops); y: detune from 0 to 3)##sesd"].plurals[0] = "=55xy: Set detune 2 (x: operator from 1 to 4 (0 for all ops); y: detune from 0 to 3)";
    strings["24xx: Set LFO 2 speed##sesd"].plurals[0] = "=24xx: Set LFO 2 speed";
    strings["25xx: Set LFO 2 waveform (0 saw, 1 square, 2 triangle, 3 noise)##sesd"].plurals[0] = "=25xx: Set LFO 2 waveform (0 saw, 1 square, 2 triangle, 3 noise)";
    strings["26xx: Set AM 2 depth (0 to 7F)##sesd"].plurals[0] = "=26xx: Set AM 2 depth (0 to 7F)";
    strings["27xx: Set PM 2 depth (0 to 7F)##sesd"].plurals[0] = "=27xx: Set PM 2 depth (0 to 7F)";
    strings["28xy: Set reverb (x: operator from 1 to 4 (0 for all ops); y: reverb from 0 to 7)##sesd"].plurals[0] = "=28xy: Set reverb (x: operator from 1 to 4 (0 for all ops); y: reverb from 0 to 7)";
    strings["2Axy: Set waveform (x: operator from 1 to 4 (0 for all ops); y: waveform from 0 to 7)##sesd0"].plurals[0] = "=2Axy: Set waveform (x: operator from 1 to 4 (0 for all ops); y: waveform from 0 to 7)";
    strings["2Bxy: Set envelope generator shift (x: operator from 1 to 4 (0 for all ops); y: shift from 0 to 3)##sesd"].plurals[0] = "=2Bxy: Set envelope generator shift (x: operator from 1 to 4 (0 for all ops); y: shift from 0 to 3)";
    strings["2Cxy: Set fine multiplier (x: operator from 1 to 4 (0 for all ops); y: fine)##sesd"].plurals[0] = "=2Cxy: Set fine multiplier (x: operator from 1 to 4 (0 for all ops); y: fine)";
    strings["3xyy: Set fixed frequency of operator 1 (x: octave from 0 to 7; y: frequency)##sesd"].plurals[0] = "=3xyy: Set fixed frequency of operator 1 (x: octave from 0 to 7; y: frequency)";
    strings["3xyy: Set fixed frequency of operator 2 (x: octave from 8 to F; y: frequency)##sesd"].plurals[0] = "=3xyy: Set fixed frequency of operator 2 (x: octave from 8 to F; y: frequency)";
    strings["4xyy: Set fixed frequency of operator 3 (x: octave from 0 to 7; y: frequency)##sesd"].plurals[0] = "=4xyy: Set fixed frequency of operator 3 (x: octave from 0 to 7; y: frequency)";
    strings["4xyy: Set fixed frequency of operator 4 (x: octave from 8 to F; y: frequency)##sesd"].plurals[0] = "=4xyy: Set fixed frequency of operator 4 (x: octave from 8 to F; y: frequency)";
    strings["10xy: Setup LFO (x: enable; y: speed)##sesd"].plurals[0] = "=10xy: Setup LFO (x: enable; y: speed)";
    strings["55xy: Set SSG envelope (x: operator from 1 to 4 (0 for all ops); y: 0-7 on, 8 off)##sesd"].plurals[0] = "=55xy: Set SSG envelope (x: operator from 1 to 4 (0 for all ops); y: 0-7 on, 8 off)";
    strings["1Fxx: Set ADPCM-A global volume (0 to 3F)##sesd"].plurals[0] = "=1Fxx: Set ADPCM-A global volume (0 to 3F)";
    strings["11xx: Set feedback (0 to 7)##sesd1"].plurals[0] = "=11xx: Set feedback (0 to 7)";
    strings["12xx: Set level of operator 1 (0 highest, 3F lowest)##sesd0"].plurals[0] = "=12xx: Set level of operator 1 (0 highest, 3F lowest)";
    strings["13xx: Set level of operator 2 (0 highest, 3F lowest)##sesd0"].plurals[0] = "=13xx: Set level of operator 2 (0 highest, 3F lowest)";
    strings["16xy: Set operator multiplier (x: operator from 1 to 2; y: multiplier)##sesd"].plurals[0] = "=16xy: Set operator multiplier (x: operator from 1 to 2; y: multiplier)";
    strings["19xx: Set attack of all operators (0 to F)##sesd0"].plurals[0] = "=19xx: Set attack of all operators (0 to F)";
    strings["1Axx: Set attack of operator 1 (0 to F)##sesd0"].plurals[0] = "=1Axx: Set attack of operator 1 (0 to F)";
    strings["1Bxx: Set attack of operator 2 (0 to F)##sesd0"].plurals[0] = "=1Bxx: Set attack of operator 2 (0 to F)";
    strings["50xy: Set AM (x: operator from 1 to 2 (0 for all ops); y: AM)##sesd"].plurals[0] = "=50xy: Set AM (x: operator from 1 to 2 (0 for all ops); y: AM)";
    strings["51xy: Set sustain level (x: operator from 1 to 2 (0 for all ops); y: sustain)##sesd"].plurals[0] = "=51xy: Set sustain level (x: operator from 1 to 2 (0 for all ops); y: sustain)";
    strings["52xy: Set release (x: operator from 1 to 2 (0 for all ops); y: release)##sesd"].plurals[0] = "=52xy: Set release (x: operator from 1 to 2 (0 for all ops); y: release)";
    strings["53xy: Set vibrato (x: operator from 1 to 2 (0 for all ops); y: enabled)##sesd"].plurals[0] = "=53xy: Set vibrato (x: operator from 1 to 2 (0 for all ops); y: enabled)";
    strings["54xy: Set envelope scale (x: operator from 1 to 2 (0 for all ops); y: scale from 0 to 3)##sesd"].plurals[0] = "=54xy: Set envelope scale (x: operator from 1 to 2 (0 for all ops); y: scale from 0 to 3)";
    strings["55xy: Set envelope sustain (x: operator from 1 to 2 (0 for all ops); y: enabled)##sesd"].plurals[0] = "=55xy: Set envelope sustain (x: operator from 1 to 2 (0 for all ops); y: enabled)";
    strings["56xx: Set decay of all operators (0 to F)##sesd0"].plurals[0] = "=56xx: Set decay of all operators (0 to F)";
    strings["57xx: Set decay of operator 1 (0 to F)##sesd0"].plurals[0] = "=57xx: Set decay of operator 1 (0 to F)";
    strings["58xx: Set decay of operator 2 (0 to F)##sesd0"].plurals[0] = "=58xx: Set decay of operator 2 (0 to F)";
    strings["5Bxy: Set whether key will scale envelope (x: operator from 1 to 2 (0 for all ops); y: enabled)##sesd"].plurals[0] = "=5Bxy: Set whether key will scale envelope (x: operator from 1 to 2 (0 for all ops); y: enabled)";
    strings["10xx: Set global AM depth (0: 1dB, 1: 4.8dB)##sesd"].plurals[0] = "=10xx: Set global AM depth (0: 1dB, 1: 4.8dB)";
    strings["11xx: Set feedback (0 to 7)##sesd2"].plurals[0] = "=11xx: Set feedback (0 to 7)";
    strings["12xx: Set level of operator 1 (0 highest, 3F lowest)##sesd1"].plurals[0] = "=12xx: Set level of operator 1 (0 highest, 3F lowest)";
    strings["13xx: Set level of operator 2 (0 highest, 3F lowest)##sesd1"].plurals[0] = "=13xx: Set level of operator 2 (0 highest, 3F lowest)";
    strings["14xx: Set level of operator 3 (0 highest, 3F lowest)##sesd0"].plurals[0] = "=14xx: Set level of operator 3 (0 highest, 3F lowest)";
    strings["15xx: Set level of operator 4 (0 highest, 3F lowest)##sesd0"].plurals[0] = "=15xx: Set level of operator 4 (0 highest, 3F lowest)";
    strings["16xy: Set operator multiplier (x: operator from 1 to 4; y: multiplier)##sesd1"].plurals[0] = "=16xy: Set operator multiplier (x: operator from 1 to 4; y: multiplier)";
    strings["17xx: Set global vibrato depth (0: normal, 1: double)##sesd"].plurals[0] = "=17xx: Set global vibrato depth (0: normal, 1: double)";
    strings["19xx: Set attack of all operators (0 to F)##sesd1"].plurals[0] = "=19xx: Set attack of all operators (0 to F)";
    strings["1Axx: Set attack of operator 1 (0 to F)##sesd1"].plurals[0] = "=1Axx: Set attack of operator 1 (0 to F)";
    strings["1Bxx: Set attack of operator 2 (0 to F)##sesd1"].plurals[0] = "=1Bxx: Set attack of operator 2 (0 to F)";
    strings["1Cxx: Set attack of operator 3 (0 to F)##sesd0"].plurals[0] = "=1Cxx: Set attack of operator 3 (0 to F)";
    strings["1Dxx: Set attack of operator 4 (0 to F)##sesd0"].plurals[0] = "=1Dxx: Set attack of operator 4 (0 to F)";
    strings["2Axy: Set waveform (x: operator from 1 to 4 (0 for all ops); y: waveform from 0 to 3 in OPL2 and 0 to 7 in OPL3)##sesd"].plurals[0] = "=2Axy: Set waveform (x: operator from 1 to 4 (0 for all ops); y: waveform from 0 to 3 in OPL2 and 0 to 7 in OPL3)";
    strings["50xy: Set AM (x: operator from 1 to 4 (0 for all ops); y: AM)##sesd1"].plurals[0] = "=50xy: Set AM (x: operator from 1 to 4 (0 for all ops); y: AM)";
    strings["51xy: Set sustain level (x: operator from 1 to 4 (0 for all ops); y: sustain)##sesd1"].plurals[0] = "=51xy: Set sustain level (x: operator from 1 to 4 (0 for all ops); y: sustain)";
    strings["52xy: Set release (x: operator from 1 to 4 (0 for all ops); y: release)##sesd1"].plurals[0] = "=52xy: Set release (x: operator from 1 to 4 (0 for all ops); y: release)";
    strings["53xy: Set vibrato (x: operator from 1 to 4 (0 for all ops); y: enabled)##sesd0"].plurals[0] = "=53xy: Set vibrato (x: operator from 1 to 4 (0 for all ops); y: enabled)";
    strings["54xy: Set envelope scale (x: operator from 1 to 4 (0 for all ops); y: scale from 0 to 3)##sesd1"].plurals[0] = "=54xy: Set envelope scale (x: operator from 1 to 4 (0 for all ops); y: scale from 0 to 3)";
    strings["55xy: Set envelope sustain (x: operator from 1 to 4 (0 for all ops); y: enabled)##sesd0"].plurals[0] = "=55xy: Set envelope sustain (x: operator from 1 to 4 (0 for all ops); y: enabled)";
    strings["56xx: Set decay of all operators (0 to F)##sesd1"].plurals[0] = "=56xx: Set decay of all operators (0 to F)";
    strings["57xx: Set decay of operator 1 (0 to F)##sesd1"].plurals[0] = "=57xx: Set decay of operator 1 (0 to F)";
    strings["58xx: Set decay of operator 2 (0 to F)##sesd1"].plurals[0] = "=58xx: Set decay of operator 2 (0 to F)";
    strings["59xx: Set decay of operator 3 (0 to F)##sesd0"].plurals[0] = "=59xx: Set decay of operator 3 (0 to F)";
    strings["5Axx: Set decay of operator 4 (0 to F)##sesd0"].plurals[0] = "=5Axx: Set decay of operator 4 (0 to F)";
    strings["5Bxy: Set whether key will scale envelope (x: operator from 1 to 4 (0 for all ops); y: enabled)##sesd0"].plurals[0] = "=5Bxy: Set whether key will scale envelope (x: operator from 1 to 4 (0 for all ops); y: enabled)";
    strings["10xx: Set waveform (bit 0: triangle; bit 1: saw; bit 2: pulse; bit 3: noise)##sesd"].plurals[0] = "=10xx: Set waveform (bit 0: triangle; bit 1: saw; bit 2: pulse; bit 3: noise)";
    strings["11xx: Set coarse cutoff (not recommended; use 4xxx instead)##sesd"].plurals[0] = "=11xx: Set coarse cutoff (not recommended; use 4xxx instead)";
    strings["12xx: Set coarse pulse width (not recommended; use 3xxx instead)##sesd"].plurals[0] = "=12xx: Set coarse pulse width (not recommended; use 3xxx instead)";
    strings["13xx: Set resonance (0 to F)##sesd"].plurals[0] = "=13xx: Set resonance (0 to F)";
    strings["14xx: Set filter mode (bit 0: low pass; bit 1: band pass; bit 2: high pass)##sesd"].plurals[0] = "=14xx: Set filter mode (bit 0: low pass; bit 1: band pass; bit 2: high pass)";
    strings["15xx: Set envelope reset time##sesd"].plurals[0] = "=15xx: Set envelope reset time";
    strings["1Axx: Disable envelope reset for this channel (1 disables; 0 enables)##sesd"].plurals[0] = "=1Axx: Disable envelope reset for this channel (1 disables; 0 enables)";
    strings["1Bxy: Reset cutoff (x: on new note; y: now)##sesd"].plurals[0] = "=1Bxy: Reset cutoff (x: on new note; y: now)";
    strings["1Cxy: Reset pulse width (x: on new note; y: now)##sesd"].plurals[0] = "=1Cxy: Reset pulse width (x: on new note; y: now)";
    strings["1Exy: Change other parameters (LEGACY)##sesd"].plurals[0] = "=1Exy: Change other parameters (LEGACY)";
    strings["20xy: Set attack/decay (x: attack; y: decay)##sesd"].plurals[0] = "=20xy: Set attack/decay (x: attack; y: decay)";
    strings["21xy: Set sustain/release (x: sustain; y: release)##sesd"].plurals[0] = "=21xy: Set sustain/release (x: sustain; y: release)";
    strings["22xx: Pulse width slide up##sesd"].plurals[0] = "=22xx: Pulse width slide up";
    strings["23xx: Pulse width slide down##sesd"].plurals[0] = "=23xx: Pulse width slide down";
    strings["24xx: Cutoff slide up##sesd"].plurals[0] = "=24xx: Cutoff slide up";
    strings["25xx: Cutoff slide down##sesd"].plurals[0] = "=25xx: Cutoff slide down";
    strings["3xxx: Set pulse width (0 to FFF)##sesd"].plurals[0] = "=3xxx: Set pulse width (0 to FFF)";
    strings["4xxx: Set cutoff (0 to 7FF)##sesd"].plurals[0] = "=4xxx: Set cutoff (0 to 7FF)";
    strings["10xx: Set waveform##sesd0"].plurals[0] = "=10xx: Set waveform";
    strings["13xx: Set waveform (local)##sesd"].plurals[0] = "13xx: =Set waveform (local)";
    strings["11xx: Set raw period##sesd"].plurals[0] = "=11xx: Set raw period (0-1F)";
    strings["11xx: Set waveform (local)##sesd"].plurals[0] = "=11xx: Set waveform (local)";
    strings["20xx: Set PCM frequency##sesd"].plurals[0] = "=20xx: Set PCM frequency";
    strings["10xy: Set AM depth (x: operator from 1 to 4 (0 for all ops); y: depth (0: 1dB, 1: 4.8dB))##sesd"].plurals[0] = "=10xy: Set AM depth (x: operator from 1 to 4 (0 for all ops); y: depth (0: 1dB, 1: 4.8dB))";
    strings["12xx: Set level of operator 1 (0 highest, 3F lowest)##sesd2"].plurals[0] = "=12xx: Set level of operator 1 (0 highest, 3F lowest)";
    strings["13xx: Set level of operator 2 (0 highest, 3F lowest)##sesd2"].plurals[0] = "=13xx: Set level of operator 2 (0 highest, 3F lowest)";
    strings["14xx: Set level of operator 3 (0 highest, 3F lowest)##sesd1"].plurals[0] = "=14xx: Set level of operator 3 (0 highest, 3F lowest)";
    strings["15xx: Set level of operator 4 (0 highest, 3F lowest)##sesd1"].plurals[0] = "=15xx: Set level of operator 4 (0 highest, 3F lowest)";
    strings["16xy: Set operator multiplier (x: operator from 1 to 4; y: multiplier)##sesd2"].plurals[0] = "=16xy: Set operator multiplier (x: operator from 1 to 4; y: multiplier)";
    strings["17xy: Set vibrato depth (x: operator from 1 to 4 (0 for all ops); y: depth (0: normal, 1: double))##sesd"].plurals[0] = "=17xy: Set vibrato depth (x: operator from 1 to 4 (0 for all ops); y: depth (0: normal, 1: double))";
    strings["19xx: Set attack of all operators (0 to F)##sesd"].plurals[0] = "=19xx: Set attack of all operators (0 to F)";
    strings["1Axx: Set attack of operator 1 (0 to F)##sesd2"].plurals[0] = "=1Axx: Set attack of operator 1 (0 to F)";
    strings["1Bxx: Set attack of operator 2 (0 to F)##sesd2"].plurals[0] = "=1Bxx: Set attack of operator 2 (0 to F)";
    strings["1Cxx: Set attack of operator 3 (0 to F)##sesd1"].plurals[0] = "=1Cxx: Set attack of operator 3 (0 to F)";
    strings["1Dxx: Set attack of operator 4 (0 to F)##sesd1"].plurals[0] = "=1Dxx: Set attack of operator 4 (0 to F)";
    strings["20xy: Set panning of operator 1 (x: left; y: right)##sesd"].plurals[0] = "=20xy: Set panning of operator 1 (x: left; y: right)";
    strings["21xy: Set panning of operator 2 (x: left; y: right)##sesd"].plurals[0] = "=21xy: Set panning of operator 2 (x: left; y: right)";
    strings["22xy: Set panning of operator 3 (x: left; y: right)##sesd"].plurals[0] = "=22xy: Set panning of operator 3 (x: left; y: right)";
    strings["23xy: Set panning of operator 4 (x: left; y: right)##sesd"].plurals[0] = "=23xy: Set panning of operator 4 (x: left; y: right)";
    strings["24xy: Set output level register (x: operator from 1 to 4 (0 for all ops); y: level from 0 to 7)##sesd"].plurals[0] = "=24xy: Set output level register (x: operator from 1 to 4 (0 for all ops); y: level from 0 to 7)";
    strings["25xy: Set modulation input level (x: operator from 1 to 4 (0 for all ops); y: level from 0 to 7)##sesd"].plurals[0] = "=25xy: Set modulation input level (x: operator from 1 to 4 (0 for all ops); y: level from 0 to 7)";
    strings["26xy: Set envelope delay (x: operator from 1 to 4 (0 for all ops); y: delay from 0 to 7)##sesd"].plurals[0] = "=26xy: Set envelope delay (x: operator from 1 to 4 (0 for all ops); y: delay from 0 to 7)";
    strings["27xx: Set noise mode for operator 4 (x: mode from 0 to 3)##sesd"].plurals[0] = "=27xx: Set noise mode for operator 4 (x: mode from 0 to 3)";
    strings["2Axy: Set waveform (x: operator from 1 to 4 (0 for all ops); y: waveform from 0 to 7)##sesd1"].plurals[0] = "=2Axy: Set waveform (x: operator from 1 to 4 (0 for all ops); y: waveform from 0 to 7)";
    strings["2Fxy: Set fixed frequency block (x: operator from 1 to 4; y: octave from 0 to 7)##sesd"].plurals[0] = "=2Fxy: Set fixed frequency block (x: operator from 1 to 4; y: octave from 0 to 7)";
    strings["40xx: Set detune of operator 1 (80: center)##sesd"].plurals[0] = "=40xx: Set detune of operator 1 (80: center)";
    strings["41xx: Set detune of operator 2 (80: center)##sesd"].plurals[0] = "=41xx: Set detune of operator 2 (80: center)";
    strings["42xx: Set detune of operator 3 (80: center)##sesd"].plurals[0] = "=42xx: Set detune of operator 3 (80: center)";
    strings["43xx: Set detune of operator 4 (80: center)##sesd"].plurals[0] = "=43xx: Set detune of operator 4 (80: center)";
    strings["50xy: Set AM (x: operator from 1 to 4 (0 for all ops); y: AM)##sesd2"].plurals[0] = "=50xy: Set AM (x: operator from 1 to 4 (0 for all ops); y: AM)";
    strings["51xy: Set sustain level (x: operator from 1 to 4 (0 for all ops); y: sustain)##sesd2"].plurals[0] = "=51xy: Set sustain level (x: operator from 1 to 4 (0 for all ops); y: sustain)";
    strings["52xy: Set release (x: operator from 1 to 4 (0 for all ops); y: release)##sesd2"].plurals[0] = "=52xy: Set release (x: operator from 1 to 4 (0 for all ops); y: release)";
    strings["53xy: Set vibrato (x: operator from 1 to 4 (0 for all ops); y: enabled)##sesd1"].plurals[0] = "=53xy: Set vibrato (x: operator from 1 to 4 (0 for all ops); y: enabled)";
    strings["54xy: Set envelope scale (x: operator from 1 to 4 (0 for all ops); y: scale from 0 to 3)##sesd2"].plurals[0] = "=54xy: Set envelope scale (x: operator from 1 to 4 (0 for all ops); y: scale from 0 to 3)";
    strings["55xy: Set envelope sustain (x: operator from 1 to 4 (0 for all ops); y: enabled)##sesd1"].plurals[0] = "=55xy: Set envelope sustain (x: operator from 1 to 4 (0 for all ops); y: enabled)";
    strings["56xx: Set decay of all operators (0 to F)##sesd2"].plurals[0] = "=56xx: Set decay of all operators (0 to F)";
    strings["57xx: Set decay of operator 1 (0 to F)##sesd2"].plurals[0] = "=57xx: Set decay of operator 1 (0 to F)";
    strings["58xx: Set decay of operator 2 (0 to F)##sesd2"].plurals[0] = "=58xx: Set decay of operator 2 (0 to F)";
    strings["59xx: Set decay of operator 3 (0 to F)##sesd1"].plurals[0] = "=59xx: Set decay of operator 3 (0 to F)";
    strings["5Axx: Set decay of operator 4 (0 to F)##sesd1"].plurals[0] = "=5Axx: Set decay of operator 4 (0 to F)";
    strings["5Bxy: Set whether key will scale envelope (x: operator from 1 to 4 (0 for all ops); y: enabled)##sesd1"].plurals[0] = "=5Bxy: Set whether key will scale envelope (x: operator from 1 to 4 (0 for all ops); y: enabled)";
    strings["3xyy: Set fixed frequency F-num of operator 1 (x: high 2 bits from 0 to 3; y: low 8 bits of F-num)##sesd"].plurals[0] = "=3xyy: Set fixed frequency F-num of operator 1 (x: high 2 bits from 0 to 3; y: low 8 bits of F-num)";
    strings["3xyy: Set fixed frequency F-num of operator 2 (x: high 2 bits from 4 to 7; y: low 8 bits of F-num)##sesd"].plurals[0] = "=3xyy: Set fixed frequency F-num of operator 2 (x: high 2 bits from 4 to 7; y: low 8 bits of F-num)";
    strings["3xyy: Set fixed frequency F-num of operator 3 (x: high 2 bits from 8 to B; y: low 8 bits of F-num)##sesd"].plurals[0] = "=3xyy: Set fixed frequency F-num of operator 3 (x: high 2 bits from 8 to B; y: low 8 bits of F-num)";
    strings["3xyy: Set fixed frequency F-num of operator 4 (x: high 2 bits from C to F; y: low 8 bits of F-num)##sesd"].plurals[0] = "=3xyy: Set fixed frequency F-num of operator 4 (x: high 2 bits from C to F; y: low 8 bits of F-num)";
    strings["10xx: Set waveform (bit 0: triangle; bit 1: saw; bit 2: pulse; bit 3: noise)##sesd1"].plurals[0] = "=10xx: Set waveform (bit 0: triangle; bit 1: saw; bit 2: pulse; bit 3: noise)";
    strings["11xx: Set resonance (0 to FF)##sesd"].plurals[0] = "=11xx: Set resonance (0 to FF)";
    strings["12xx: Set filter mode (bit 0: low pass; bit 1: band pass; bit 2: high pass)##sesd"].plurals[0] = "=12xx: Set filter mode (bit 0: low pass; bit 1: band pass; bit 2: high pass)";
    strings["13xx: Disable envelope reset for this channel (1 disables; 0 enables)##sesd"].plurals[0] = "=13xx: Disable envelope reset for this channel (1 disables; 0 enables)";
    strings["14xy: Reset cutoff (x: on new note; y: now)##sesd"].plurals[0] = "=14xy: Reset cutoff (x: on new note; y: now)";
    strings["15xy: Reset pulse width (x: on new note; y: now)##sesd"].plurals[0] = "=15xy: Reset pulse width (x: on new note; y: now)";
    strings["16xy: Change other parameters##sesd"].plurals[0] = "=16xy: Change other parameters";
    strings["17xx: Pulse width slide up##sesd"].plurals[0] = "=17xx: Pulse width slide up";
    strings["18xx: Pulse width slide down##sesd"].plurals[0] = "=18xx: Pulse width slide down";
    strings["19xx: Cutoff slide up##sesd"].plurals[0] = "=19xx: Cutoff slide up";
    strings["1Axx: Cutoff slide down##sesd"].plurals[0] = "=1Axx: Cutoff slide down";
    strings["3xxx: Set pulse width (0 to FFF)##sesd1"].plurals[0] = "=3xxx: Set pulse width (0 to FFF)";
    strings["4xxx: Set cutoff (0 to FFF)##sesd1"].plurals[0] = "=4xxx: Set cutoff (0 to FFF)";
    strings["a chip which found its way inside mobile phones in the 2000's.\nas proprietary as it is, it passed away after losing to MP3 in the mobile hardware battle.##sesd"].plurals[0] = "=a chip which found its way inside mobile phones in the 2000's.\nas proprietary as it is, it passed away after losing to MP3 in the mobile hardware battle.";
    strings["<COMPOUND SYSTEM!>##sesd0"].plurals[0] = "=<COMPOUND SYSTEM!>";
    strings["Sega Genesis Extended Channel 3##sesd1"].plurals[0] = "=Sega Genesis Extended Channel 3";
    strings["<COMPOUND SYSTEM!>##sesd1"].plurals[0] = "=<COMPOUND SYSTEM!>";
    strings["a square/noise sound chip found on the Sega Master System, ColecoVision, Tandy, TI's own 99/4A and a few other places.##sesd"].plurals[0] = "=a square/noise sound chip found on the Sega Master System, ColecoVision, Tandy, TI's own 99/4A and a few other places.";
    strings["20xy: Set noise mode (x: preset freq/ch3 freq; y: thin pulse/noise)##sesd"].plurals[0] = "=20xy: Set noise mode (x: preset freq/ch3 freq; y: thin pulse/noise)";
    strings["<COMPOUND SYSTEM!>##sesd2"].plurals[0] = "=<COMPOUND SYSTEM!>";
    strings["the most popular portable game console of the era.##sesd"].plurals[0] = "=the most popular portable game console of the era.";
    strings["10xx: Set waveform##sesd1"].plurals[0] = "=10xx: Set waveform";
    strings["11xx: Set noise length (0: long; 1: short)##sesd"].plurals[0] = "=11xx: Set noise length (0: long; 1: short)";
    strings["12xx: Set duty cycle (0 to 3)##sesd"].plurals[0] = "=12xx: Set duty cycle (0 to 3)";
    strings["13xy: Setup sweep (x: time; y: shift)##sesd"].plurals[0] = "=13xy: Setup sweep (x: time; y: shift)";
    strings["14xx: Set sweep direction (0: up; 1: down)##sesd"].plurals[0] = "=14xx: Set sweep direction (0: up; 1: down)";
    strings["15xx: Set waveform (local)##sesd"].plurals[0] = "=15xx: Set waveform (local)";
    strings["an '80s game console with a wavetable sound chip, popular in Japan.##sesd"].plurals[0] = "=an '80s game console with a wavetable sound chip, popular in Japan.";
    strings["10xx: Set waveform##sesd2"].plurals[0] = "=10xx: Set waveform";
    strings["11xx: Toggle noise mode##sesd0"].plurals[0] = "=11xx: Toggle noise mode";
    strings["12xx: Setup LFO (0: disabled; 1: 1x depth; 2: 16x depth; 3: 256x depth)##sesd"].plurals[0] = "=12xx: Setup LFO (0: disabled; 1: 1x depth; 2: 16x depth; 3: 256x depth)";
    strings["13xx: Set LFO speed##sesd"].plurals[0] = "=13xx: Set LFO speed";
    strings["17xx: Toggle PCM mode (LEGACY)##sesd1"].plurals[0] = "=17xx: Toggle PCM mode (LEGACY)";
    strings["18xx: Set waveform (local)##sesd"].plurals[0] = "=18xx: Set waveform (local)";
    strings["also known as Famicom in Japan, it's the most well-known game console of the '80s.##sesd"].plurals[0] = "=also known as Famicom in Japan, it's the most well-known game console of the '80s.";
    strings["11xx: Write to delta modulation counter (0 to 7F)##sesd"].plurals[0] = "=11xx: Write to delta modulation counter (0 to 7F)";
    strings["12xx: Set duty cycle/noise mode (pulse: 0 to 3; noise: 0 or 1)##sesd0"].plurals[0] = "=12xx: Set duty cycle/noise mode (pulse: 0 to 3; noise: 0 or 1)";
    strings["13xy: Sweep up (x: time; y: shift)##sesd"].plurals[0] = "=13xy: Sweep up (x: time; y: shift)";
    strings["14xy: Sweep down (x: time; y: shift)##sesd"].plurals[0] = "=14xy: Sweep down (x: time; y: shift)";
    strings["15xx: Set envelope mode (0: envelope, 1: length, 2: looping, 3: constant)##sesd"].plurals[0] = "=15xx: Set envelope mode (0: envelope, 1: length, 2: looping, 3: constant)";
    strings["16xx: Set length counter (refer to manual for a list of values)##sesd"].plurals[0] = "=16xx: Set length counter (refer to manual for a list of values)";
    strings["17xx: Set frame counter mode (0: 4-step, 1: 5-step)##sesd"].plurals[0] = "=17xx: Set frame counter mode (0: 4-step, 1: 5-step)";
    strings["18xx: Select PCM/DPCM mode (0: PCM; 1: DPCM)##sesd"].plurals[0] = "=18xx: Select PCM/DPCM mode (0: PCM; 1: DPCM)";
    strings["19xx: Set triangle linear counter (0 to 7F; 80 and higher halt)##sesd"].plurals[0] = "=19xx: Set triangle linear counter (0 to 7F; 80 and higher halt)";
    strings["20xx: Set DPCM frequency (0 to F)##sesd"].plurals[0] = "=20xx: Set DPCM frequency (0 to F)";
    strings["<COMPOUND SYSTEM!>##sesd3"].plurals[0] = "=<COMPOUND SYSTEM!>";
    strings["<COMPOUND SYSTEM!>##sesd4"].plurals[0] = "=<COMPOUND SYSTEM!>";
    strings["this computer is powered by the SID chip, which had synthesizer features like a filter and ADSR.##sesd"].plurals[0] = "=this computer is powered by the SID chip, which had synthesizer features like a filter and ADSR.";
    strings["this computer is powered by the SID chip, which had synthesizer features like a filter and ADSR.\nthis is the newer revision of the chip.##sesd"].plurals[0] = "=this computer is powered by the SID chip, which had synthesizer features like a filter and ADSR.\nthis is the newer revision of the chip.";
    strings["<COMPOUND SYSTEM!>##sesd5"].plurals[0] = "=<COMPOUND SYSTEM!>";
    strings["like Neo Geo, but lacking the ADPCM-B channel since they couldn't connect the pins.##sesd"].plurals[0] = "=like Neo Geo, but lacking the ADPCM-B channel since they couldn't connect the pins.";
    strings["Neo Geo CD Extended Channel 2##sesd"].plurals[0] = "=Neo Geo CD Extended Channel 2";
    strings["like Neo Geo, but lacking the ADPCM-B channel since they couldn't connect the pins.\nthis one is in Extended Channel mode, which turns the second FM channel into four operators with independent notes/frequencies.##sesd"].plurals[0] = "=like Neo Geo, but lacking the ADPCM-B channel since they couldn't connect the pins.\nthis one is in Extended Channel mode, which turns the second FM channel into four operators with independent notes/frequencies.";
    strings["this chip is everywhere! ZX Spectrum, MSX, Amstrad CPC, Intellivision, Vectrex...\nthe discovery of envelope bass helped it beat the SN76489 with ease.##sesd"].plurals[0] = "=this chip is everywhere! ZX Spectrum, MSX, Amstrad CPC, Intellivision, Vectrex...\nthe discovery of envelope bass helped it beat the SN76489 with ease.";
    strings["a computer from the '80s with full sampling capabilities, giving it a sound ahead of its time.##sesd"].plurals[0] = "=a computer from the '80s with full sampling capabilities, giving it a sound ahead of its time.";
    strings["10xx: Toggle filter (0 disables; 1 enables)##sesd"].plurals[0] = "=10xx: Toggle filter (0 disables; 1 enables)";
    strings["11xx: Toggle AM with next channel##sesd"].plurals[0] = "=11xx: Toggle AM with next channel";
    strings["12xx: Toggle period modulation with next channel##sesd"].plurals[0] = "=12xx: Toggle period modulation with next channel";
    strings["13xx: Set waveform##sesd"].plurals[0] = "=13xx: Set waveform";
    strings["14xx: Set waveform (local)##sesd"].plurals[0] = "=14xx: Set waveform (local)";
    strings["this was Yamaha's first integrated FM chip.\nit was used in several synthesizers, computers and arcade boards.##sesd"].plurals[0] = "=this was Yamaha's first integrated FM chip.\nit was used in several synthesizers, computers and arcade boards.";
    strings["this chip is mostly known for being in the Sega Genesis (but it also was on the FM Towns computer).##sesd"].plurals[0] = "=this chip is mostly known for being in the Sega Genesis (but it also was on the FM Towns computer).";
    strings["it's a challenge to make music on this chip which barely has musical capabilities...##sesd"].plurals[0] = "=it's a challenge to make music on this chip which barely has musical capabilities...";
    strings["supposedly an upgrade from the AY-3-8910, this was present on the Creative Music System (Game Blaster) and SAM Coupé.##sesd"].plurals[0] = "=supposedly an upgrade from the AY-3-8910, this was present on the Creative Music System (Game Blaster) and SAM Coupé.";
    strings["10xy: Set channel mode (x: noise; y: tone)##sesd"].plurals[0] = "=10xy: Set channel mode (x: noise; y: tone)";
    strings["11xx: Set noise frequency##sesd"].plurals[0] = "=11xx: Set noise frequency";
    strings["12xx: Setup envelope (refer to docs for more information)##sesd"].plurals[0] = "=12xx: Setup envelope (refer to docs for more information)";
    strings["an improved version of the AY-3-8910 with a bigger frequency range, duty cycles, configurable noise and per-channel envelopes!##sesd"].plurals[0] = "=an improved version of the AY-3-8910 with a bigger frequency range, duty cycles, configurable noise and per-channel envelopes!";
    strings["Commodore's successor to the PET.\nits square wave channels are more than just square...##sesd"].plurals[0] = "=Commodore's successor to the PET.\nits square wave channels are more than just square...";
    strings["one channel of 1-bit wavetable which is better (and worse) than the PC Speaker.##sesd"].plurals[0] = "=one channel of 1-bit wavetable which is better (and worse) than the PC Speaker.";
    strings["FM? nah... samples! Nintendo's answer to Sega.##sesd"].plurals[0] = "=FM? nah... samples! Nintendo's answer to Sega.";
    strings["18xx: Enable echo buffer##sesd"].plurals[0] = "=18xx: Enable echo buffer";
    strings["19xx: Set echo delay (0 to F)##sesd"].plurals[0] = "=19xx: Set echo delay (0 to F)";
    strings["1Axx: Set left echo volume##sesd"].plurals[0] = "=1Axx: Set left echo volume";
    strings["1Bxx: Set right echo volume##sesd"].plurals[0] = "=1Bxx: Set right echo volume";
    strings["1Cxx: Set echo feedback##sesd"].plurals[0] = "=1Cxx: Set echo feedback";
    strings["1Exx: Set dry output volume (left)##sesd"].plurals[0] = "=1Exx: Set dry output volume (left)";
    strings["1Fxx: Set dry output volume (right)##sesd"].plurals[0] = "=1Fxx: Set dry output volume (right)";
    strings["30xx: Set echo filter coefficient 0##sesd"].plurals[0] = "=30xx: Set echo filter coefficient 0";
    strings["31xx: Set echo filter coefficient 1##sesd"].plurals[0] = "=31xx: Set echo filter coefficient 1";
    strings["32xx: Set echo filter coefficient 2##sesd"].plurals[0] = "=32xx: Set echo filter coefficient 2";
    strings["33xx: Set echo filter coefficient 3##sesd"].plurals[0] = "=33xx: Set echo filter coefficient 3";
    strings["34xx: Set echo filter coefficient 4##sesd"].plurals[0] = "=34xx: Set echo filter coefficient 4";
    strings["35xx: Set echo filter coefficient 5##sesd"].plurals[0] = "=35xx: Set echo filter coefficient 5";
    strings["36xx: Set echo filter coefficient 6##sesd"].plurals[0] = "=36xx: Set echo filter coefficient 6";
    strings["37xx: Set echo filter coefficient 7##sesd"].plurals[0] = "=37xx: Set echo filter coefficient 7";
    strings["10xx: Set waveform##sesd3"].plurals[0] = "=10xx: Set waveform";
    strings["11xx: Toggle noise mode##sesd1"].plurals[0] = "=11xx: Toggle noise mode";
    strings["12xx: Toggle echo on this channel##sesd"].plurals[0] = "=12xx: Toggle echo on this channel";
    strings["13xx: Toggle pitch modulation##sesd"].plurals[0] = "=13xx: Toggle pitch modulation";
    strings["14xy: Toggle invert (x: left; y: right)##sesd"].plurals[0] = "=14xy: Toggle invert (x: left; y: right)";
    strings["15xx: Set envelope mode (0: ADSR, 1: gain/direct, 2: dec, 3: exp, 4: inc, 5: bent)##sesd"].plurals[0] = "=15xx: Set envelope mode (0: ADSR, 1: gain/direct, 2: dec, 3: exp, 4: inc, 5: bent)";
    strings["16xx: Set gain (00 to 7F if direct; 00 to 1F otherwise)##sesd"].plurals[0] = "=16xx: Set gain (00 to 7F if direct; 00 to 1F otherwise)";
    strings["17xx: Set waveform (local)##sesd"].plurals[0] = "=17xx: Set waveform (local)";
    strings["1Dxx: Set noise frequency (00 to 1F)##sesd"].plurals[0] = "=1Dxx: Set noise frequency (00 to 1F)";
    strings["20xx: Set attack (0 to F)##sesd"].plurals[0] = "=20xx: Set attack (0 to F)";
    strings["21xx: Set decay (0 to 7)##sesd"].plurals[0] = "=21xx: Set decay (0 to 7)";
    strings["22xx: Set sustain (0 to 7)##sesd"].plurals[0] = "=22xx: Set sustain (0 to 7)";
    strings["23xx: Set release (00 to 1F)##sesd"].plurals[0] = "=23xx: Set release (00 to 1F)";
    strings["an expansion chip for the Famicom, featuring a quirky sawtooth channel.##sesd"].plurals[0] = "=an expansion chip for the Famicom, featuring a quirky sawtooth channel.";
    strings["12xx: Set duty cycle (pulse: 0 to 7)##sesd"].plurals[0] = "=12xx: Set duty cycle (pulse: 0 to 7)";
    strings["17xx: Toggle PCM mode (LEGACY)##sesd2"].plurals[0] = "=17xx: Toggle PCM mode (LEGACY)";
    strings["cost-reduced version of the OPL with 16 patches and only one of them is user-configurable.##sesd"].plurals[0] = "=cost-reduced version of the OPL with 16 patches and only one of them is user-configurable.";
    strings["Famicom Disk System (chip)##sesd"].plurals[0] = "=Famicom Disk System (chip)";
    strings["a disk drive for the Famicom which also contains one wavetable channel.##sesd"].plurals[0] = "=a disk drive for the Famicom which also contains one wavetable channel.";
    strings["10xx: Set waveform##sesd4"].plurals[0] = "=10xx: Set waveform";
    strings["11xx: Set modulation depth##sesd"].plurals[0] = "=11xx: Set modulation depth";
    strings["12xy: Set modulation speed high byte (x: enable; y: value)##sesd"].plurals[0] = "=12xy: Set modulation speed high byte (x: enable; y: value)";
    strings["13xx: Set modulation speed low byte##sesd"].plurals[0] = "=13xx: Set modulation speed low byte";
    strings["14xx: Set modulator position##sesd"].plurals[0] = "=14xx: Set modulator position";
    strings["15xx: Set modulator table to waveform##sesd"].plurals[0] = "=15xx: Set modulator table to waveform";
    strings["16xx: Set waveform (local)##sesd"].plurals[0] = "=16xx: Set waveform (local)";
    strings["an expansion chip for the Famicom, featuring a little-known PCM channel.##sesd"].plurals[0] = "=an expansion chip for the Famicom, featuring a little-known PCM channel.";
    strings["12xx: Set duty cycle/noise mode (pulse: 0 to 3; noise: 0 or 1)##sesd1"].plurals[0] = "=12xx: Set duty cycle/noise mode (pulse: 0 to 3; noise: 0 or 1)";
    strings["an expansion chip for the Famicom, with full wavetable.##sesd"].plurals[0] = "=an expansion chip for the Famicom, with full wavetable.";
    strings["18xx: Change channel limits (0 to 7, x + 1)##sesd"].plurals[0] = "=18xx: Change channel limits (0 to 7, x + 1)";
    strings["20xx: Load a waveform into memory##sesd"].plurals[0] = "=20xx: Load a waveform into memory";
    strings["21xx: Set position for wave load##sesd"].plurals[0] = "=21xx: Set position for wave load";
    strings["10xx: Select waveform##sesd"].plurals[0] = "=10xx: Select waveform";
    strings["11xx: Set waveform position in RAM##sesd"].plurals[0] = "=11xx: Set waveform position in RAM";
    strings["12xx: Set waveform length in RAM (04 to FC in steps of 4)##sesd"].plurals[0] = "=12xx: Set waveform length in RAM (04 to FC in steps of 4)";
    strings["15xx: Set waveform load position##sesd"].plurals[0] = "=15xx: Set waveform load position";
    strings["16xx: Set waveform load length (04 to FC in steps of 4)##sesd"].plurals[0] = "=16xx: Set waveform load length (04 to FC in steps of 4)";
    strings["17xx: Select waveform (local)##sesd1"].plurals[0] = "=17xx: Select waveform (local)";
    strings["cost-reduced version of the OPM with a different register layout and no stereo...\n...but it has a built-in AY-3-8910! (actually an YM2149)##sesd"].plurals[0] = "=cost-reduced version of the OPM with a different register layout and no stereo...\n...but it has a built-in AY-3-8910! (actually an YM2149)";
    strings["Yamaha YM2203 (OPN) Extended Channel 3##sesd"].plurals[0] = "=Yamaha YM2203 (OPN) Extended Channel 3";
    strings["cost-reduced version of the OPM with a different register layout and no stereo...\n...but it has a built-in AY-3-8910! (actually an YM2149)\nthis one is in Extended Channel mode, which turns the third FM channel into four operators with independent notes/frequencies##sesd"].plurals[0] = "=cost-reduced version of the OPM with a different register layout and no stereo...\n...but it has a built-in AY-3-8910! (actually an YM2149)\nthis one is in Extended Channel mode, which turns the third FM channel into four operators with independent notes/frequencies";
    strings["cost-reduced version of the OPM with a different register layout and no stereo...\n...but it has a built-in AY-3-8910! (actually an YM2149)\nthis one is in Extended Channel mode, which turns the third FM channel into four operators with independent notes/frequencies.\nthis one includes CSM mode control for special effects on Channel 3.##sesd"].plurals[0] = "=cost-reduced version of the OPM with a different register layout and no stereo...\n...but it has a built-in AY-3-8910! (actually an YM2149)\nthis one is in Extended Channel mode, which turns the third FM channel into four operators with independent notes/frequencies.\nthis one includes CSM mode control for special effects on Channel 3.";
    strings["OPN but twice the FM channels, stereo makes a come-back and has rhythm and ADPCM channels.##sesd"].plurals[0] = "=OPN but twice the FM channels, stereo makes a come-back and has rhythm and ADPCM channels.";
    strings["Yamaha YM2608 (OPNA) Extended Channel 3##sesd"].plurals[0] = "=Yamaha YM2608 (OPNA) Extended Channel 3";
    strings["OPN but twice the FM channels, stereo makes a come-back and has rhythm and ADPCM channels.\nthis one is in Extended Channel mode, which turns the third FM channel into four operators with independent notes/frequencies.##sesd"].plurals[0] = "=OPN but twice the FM channels, stereo makes a come-back and has rhythm and ADPCM channels.\nthis one is in Extended Channel mode, which turns the third FM channel into four operators with independent notes/frequencies.";
    strings["Yamaha YM2608 (OPNA) Extended Channel 3 and CSM##sesd"].plurals[0] = "=Yamaha YM2608 (OPNA) Extended Channel 3 and CSM";
    strings["OPN but twice the FM channels, stereo makes a come-back and has rhythm and ADPCM channels.\nthis one is in Extended Channel mode, which turns the third FM channel into four operators with independent notes/frequencies.\nthis one includes CSM mode control for special effects on Channel 3.##sesd"].plurals[0] = "=OPN but twice the FM channels, stereo makes a come-back and has rhythm and ADPCM channels.\nthis one is in Extended Channel mode, which turns the third FM channel into four operators with independent notes/frequencies.\nthis one includes CSM mode control for special effects on Channel 3.";
    strings["OPN, but what if you only had two operators, no stereo, no detune and a lower ADSR parameter range?##sesd"].plurals[0] = "=OPN, but what if you only had two operators, no stereo, no detune and a lower ADSR parameter range?";
    strings["OPL, but what if you had more waveforms to choose than the normal sine?##sesd"].plurals[0] = "=OPL, but what if you had more waveforms to choose than the normal sine?";
    strings["OPL2, but what if you had twice the channels, 4-op mode, stereo and even more waveforms?##sesd"].plurals[0] = "=OPL2, but what if you had twice the channels, 4-op mode, stereo and even more waveforms?";
    strings["how many channels of PCM do you want?\nMultiPCM: yes##sesd"].plurals[0] = "=how many channels of PCM do you want?\nMultiPCM: yes";
    strings["PC Speaker##sesd"].plurals[0] = "=PC Speaker";
    strings["good luck! you get one square and no volume control.##sesd"].plurals[0] = "=good luck! you get one square and no volume control.";
    strings["please don't use this chip. it was added as a joke.##sesd"].plurals[0] = "=please don't use this chip. it was added as a joke.";
    strings["TIA, but better and more flexible.\nused in the Atari 8-bit family of computers (400/800/XL/XE).##sesd"].plurals[0] = "=TIA, but better and more flexible.\nused in the Atari 8-bit family of computers (400/800/XL/XE).";
    strings["10xx: Set waveform (0 to 7)##sesd0"].plurals[0] = "=10xx: Set waveform (0 to 7)";
    strings["11xx: Set AUDCTL##sesd"].plurals[0] = "=11xx: Set AUDCTL";
    strings["12xx: Toggle two-tone mode##sesd"].plurals[0] = "=12xx: Toggle two-tone mode";
    strings["13xx: Set raw period##sesd"].plurals[0] = "=13xx: Set raw period";
    strings["14xx: Set raw period (higher byte; only for 16-bit mode)##sesd"].plurals[0] = "=14xx: Set raw period (higher byte; only for 16-bit mode)";
    strings["this is like SNES' sound chip but without interpolation and the rest of nice bits.##sesd"].plurals[0] = "=this is like SNES' sound chip but without interpolation and the rest of nice bits.";
    strings["developed by the makers of the Game Boy and the Virtual Boy...##sesd"].plurals[0] = "=developed by the makers of the Game Boy and the Virtual Boy...";
    strings["10xx: Set waveform##sesd5"].plurals[0] = "=10xx: Set waveform";
    strings["11xx: Setup noise mode (0: disabled; 1-8: enabled/tap)##sesd"].plurals[0] = "=11xx: Setup noise mode (0: disabled; 1-8: enabled/tap)";
    strings["12xx: Setup sweep period (0: disabled; 1-20: enabled/period)##sesd"].plurals[0] = "=12xx: Setup sweep period (0: disabled; 1-20: enabled/period)";
    strings["13xx: Set sweep amount##sesd"].plurals[0] = "=13xx: Set sweep amount";
    strings["17xx: Toggle PCM mode (LEGACY)##sesd3"].plurals[0] = "=17xx: Toggle PCM mode (LEGACY)";
    strings["18xx: Set waveform (local)##sesd1"].plurals[0] = "=18xx: Set waveform (local)";
    strings["like OPM, but with more waveforms, fixed frequency mode and totally... undocumented.\nused in the Yamaha TX81Z and some other synthesizers.##sesd"].plurals[0] = "=like OPM, but with more waveforms, fixed frequency mode and totally... undocumented.\nused in the Yamaha TX81Z and some other synthesizers.";
    strings["2Fxx: Toggle hard envelope reset on new notes##sesd"].plurals[0] = "=2Fxx: Toggle hard envelope reset on new notes";
    strings["this one is like PC Speaker but has duty cycles.##sesd"].plurals[0] = "=this one is like PC Speaker but has duty cycles.";
    strings["used in some Sega arcade boards (like OutRun), and usually paired with a YM2151.##sesd"].plurals[0] = "=used in some Sega arcade boards (like OutRun), and usually paired with a YM2151.";
    strings["a console which failed to sell well due to its headache-inducing features.##sesd"].plurals[0] = "=a console which failed to sell well due to its headache-inducing features.";
    strings["10xx: Set waveform##sesd6"].plurals[0] = "=10xx: Set waveform";
    strings["11xx: Set noise length (0 to 7)##sesd"].plurals[0] = "=11xx: Set noise length (0 to 7)";
    strings["12xy: Setup envelope (x: enabled/loop (1: enable, 3: enable+loop); y: speed/direction (0-7: down, 8-F: up))##sesd"].plurals[0] = "=12xy: Setup envelope (x: enabled/loop (1: enable, 3: enable+loop); y: speed/direction (0-7: down, 8-F: up))";
    strings["13xy: Setup sweep (x: speed; y: shift; channel 5 only)##sesd"].plurals[0] = "=13xy: Setup sweep (x: speed; y: shift; channel 5 only)";
    strings["14xy: Setup modulation (x: enabled/loop (1: enable, 3: enable+loop); y: speed; channel 5 only)##sesd"].plurals[0] = "=14xy: Setup modulation (x: enabled/loop (1: enable, 3: enable+loop); y: speed; channel 5 only)";
    strings["15xx: Set modulation waveform (x: wavetable; channel 5 only)##sesd"].plurals[0] = "=15xx: Set modulation waveform (x: wavetable; channel 5 only)";
    strings["16xx: Set waveform (local)##sesd1"].plurals[0] = "=16xx: Set waveform (local)";
    strings["like OPLL, but even more cost reductions applied. three less FM channels, and no drums mode...##sesd"].plurals[0] = "=like OPLL, but even more cost reductions applied. three less FM channels, and no drums mode...";
    strings["so Taito asked Yamaha if they could get the two missing FM channels back, and Yamaha gladly provided them with this chip.##sesd"].plurals[0] = "=so Taito asked Yamaha if they could get the two missing FM channels back, and Yamaha gladly provided them with this chip.";
    strings["ZX Spectrum Beeper##sesd"].plurals[0] = "=ZX Spectrum Beeper";
    strings["the ZX Spectrum only had a basic beeper capable of...\n...a bunch of thin pulses and tons of other interesting stuff!\nFurnace provides a thin pulse system.##sesd"].plurals[0] = "=the ZX Spectrum only had a basic beeper capable of...\n...a bunch of thin pulses and tons of other interesting stuff!\nFurnace provides a thin pulse system.";
    strings["12xx: Set pulse width##sesd0"].plurals[0] = "=12xx: Set pulse width";
    strings["17xx: Trigger overlay drum##sesd"].plurals[0] = "=17xx: Trigger overlay drum";
    strings["Yamaha YM2612 (OPN2) Extended Channel 3##sesd"].plurals[0] = "=Yamaha YM2612 (OPN2) Extended Channel 3";
    strings["this chip is mostly known for being in the Sega Genesis (but it also was on the FM Towns computer).\nthis one is in Extended Channel mode, which turns the third FM channel into four operators with independent notes/frequencies.##sesd"].plurals[0] = "=this chip is mostly known for being in the Sega Genesis (but it also was on the FM Towns computer).\nthis one is in Extended Channel mode, which turns the third FM channel into four operators with independent notes/frequencies.";
    strings["this chip is mostly known for being in the Sega Genesis (but it also was on the FM Towns computer).\nthis one includes CSM mode control for special effects on Channel 3.##sesd"].plurals[0] = "=this chip is mostly known for being in the Sega Genesis (but it also was on the FM Towns computer).\nthis one includes CSM mode control for special effects on Channel 3.";
    strings["a wavetable chip made by Konami for use with the MSX.\nthe last channel shares its wavetable with the previous one though.##sesd"].plurals[0] = "=a wavetable chip made by Konami for use with the MSX.\nthe last channel shares its wavetable with the previous one though.";
    strings["Yamaha YM3526 (OPL) with drums##sesd"].plurals[0] = "=Yamaha YM3526 (OPL) with drums";
    strings["the OPL chip but with drums mode enabled.##sesd"].plurals[0] = "=the OPL chip but with drums mode enabled.";
    strings["Yamaha YM3812 (OPL2) with drums##sesd"].plurals[0] = "=Yamaha YM3812 (OPL2) with drums";
    strings["the OPL2 chip but with drums mode enabled.##sesd"].plurals[0] = "=the OPL2 chip but with drums mode enabled.";
    strings["Yamaha YMF262 (OPL3) with drums##sesd"].plurals[0] = "=Yamaha YMF262 (OPL3) with drums";
    strings["the OPL3 chip but with drums mode enabled.##sesd"].plurals[0] = "=the OPL3 chip but with drums mode enabled.";
    strings["this chip was used in SNK's Neo Geo arcade board and video game console.\nit's like OPNA but the rhythm channels are ADPCM channels and two FM channels went missing.##sesd"].plurals[0] = "=this chip was used in SNK's Neo Geo arcade board and video game console.\nit's like OPNA but the rhythm channels are ADPCM channels and two FM channels went missing.";
    strings["Yamaha YM2610 (OPNB) Extended Channel 2##sesd"].plurals[0] = "=Yamaha YM2610 (OPNB) Extended Channel 2";
    strings["this chip was used in SNK's Neo Geo arcade board and video game console.\nit's like OPNA but the rhythm channels are ADPCM channels and two FM channels went missing.\nthis one is in Extended Channel mode, which turns the second FM channel into four operators with independent notes/frequencies.##sesd"].plurals[0] = "=this chip was used in SNK's Neo Geo arcade board and video game console.\nit's like OPNA but the rhythm channels are ADPCM channels and two FM channels went missing.\nthis one is in Extended Channel mode, which turns the second FM channel into four operators with independent notes/frequencies.";
    strings["this chip was used in SNK's Neo Geo arcade board and video game console.\nit's like OPNA but the rhythm channels are ADPCM channels and two FM channels went missing.\nthis one is in Extended Channel mode, which turns the second FM channel into four operators with independent notes/frequencies.\nthis one includes CSM mode control for special effects on Channel 2.##sesd"].plurals[0] = "=this chip was used in SNK's Neo Geo arcade board and video game console.\nit's like OPNA but the rhythm channels are ADPCM channels and two FM channels went missing.\nthis one is in Extended Channel mode, which turns the second FM channel into four operators with independent notes/frequencies.\nthis one includes CSM mode control for special effects on Channel 2.";
    strings["Yamaha YM2413 (OPLL) with drums##sesd"].plurals[0] = "=Yamaha YM2413 (OPLL) with drums";
    strings["the OPLL chip but with drums mode turned on.##sesd"].plurals[0] = "=the OPLL chip but with drums mode turned on.";
    strings["3xxx: Load LFSR (0 to FFF)##sesd"].plurals[0] = "=3xxx: Load LFSR (0 to FFF)";
    strings["a portable console made by Atari. it has all of Atari's trademark waveforms.##sesd"].plurals[0] = "=a portable console made by Atari. it has all of Atari's trademark waveforms.";
    strings["10xx: Set echo feedback level (00 to FF)##sesd"].plurals[0] = "=10xx: Set echo feedback level (00 to FF)";
    strings["11xx: Set channel echo level (00 to FF)##sesd"].plurals[0] = "=11xx: Set channel echo level (00 to FF)";
    strings["12xx: Toggle QSound algorithm (0: disabled; 1: enabled)##sesd"].plurals[0] = "=12xx: Toggle QSound algorithm (0: disabled; 1: enabled)";
    strings["3xxx: Set echo delay buffer length (000 to AA5)##sesd"].plurals[0] = "=3xxx: Set echo delay buffer length (000 to AA5)";
    strings["used in some of Capcom's arcade boards. surround-like sampled sound with echo.##sesd"].plurals[0] = "=used in some of Capcom's arcade boards. surround-like sampled sound with echo.";
    strings["the chip used in a computer design created by The 8-Bit Guy.##sesd"].plurals[0] = "=the chip used in a computer design created by The 8-Bit Guy.";
    strings["20xx: Set waveform##sesd"].plurals[0] = "=20xx: Set waveform";
    strings["22xx: Set duty cycle (0 to 3F)##sesd"].plurals[0] = "=22xx: Set duty cycle (0 to 3F)";
    strings["Yamaha YM2610B (OPNB2) Extended Channel 3##sesd"].plurals[0] = "=Yamaha YM2610B (OPNB2) Extended Channel 3";
    strings["so Taito asked Yamaha if they could get the two missing FM channels back, and Yamaha gladly provided them with this chip.\nthis one is in Extended Channel mode, which turns the third FM channel into four operators with independent notes/frequencies.##sesd"].plurals[0] = "=so Taito asked Yamaha if they could get the two missing FM channels back, and Yamaha gladly provided them with this chip.\nthis one is in Extended Channel mode, which turns the third FM channel into four operators with independent notes/frequencies.";
    strings["so Taito asked Yamaha if they could get the two missing FM channels back, and Yamaha gladly provided them with this chip.\nthis one is in Extended Channel mode, which turns the third FM channel into four operators with independent notes/frequencies.\nthis one includes CSM mode control for special effects on Channel 3.##sesd"].plurals[0] = "=so Taito asked Yamaha if they could get the two missing FM channels back, and Yamaha gladly provided them with this chip.\nthis one is in Extended Channel mode, which turns the third FM channel into four operators with independent notes/frequencies.\nthis one includes CSM mode control for special effects on Channel 3.";
    strings["SegaPCM (compatible 5-channel mode)##sesd"].plurals[0] = "=SegaPCM (compatible 5-channel mode)";
    strings["this is the same thing as SegaPCM, but only exposes 5 of the channels for compatibility with DefleMask.##sesd"].plurals[0] = "=this is the same thing as SegaPCM, but only exposes 5 of the channels for compatibility with DefleMask.";
    strings["a sound chip used in several Seta/Allumer-manufactured arcade boards with too many channels of wavetable sound, which also are capable of sampled sound.##sesd"].plurals[0] = "=a sound chip used in several Seta/Allumer-manufactured arcade boards with too many channels of wavetable sound, which also are capable of sampled sound.";
    strings["10xx: Set waveform##sesd7"].plurals[0] = "=10xx: Set waveform";
    strings["11xx: Set envelope shape##sesd"].plurals[0] = "=11xx: Set envelope shape";
    strings["12xx: Set sample bank slot (0 to 7)##sesd"].plurals[0] = "=12xx: Set sample bank slot (0 to 7)";
    strings["17xx: Toggle PCM mode (LEGACY)##sesd4"].plurals[0] = "=17xx: Toggle PCM mode (LEGACY)";
    strings["18xx: Set waveform (local)##sesd2"].plurals[0] = "=18xx: Set waveform (local)";
    strings["20xx: Set PCM frequency (1 to FF)##sesd"].plurals[0] = "=20xx: Set PCM frequency (1 to FF)";
    strings["22xx: Set envelope mode (bit 0: enable; bit 1: one-shot; bit 2: split shape to L/R; bit 3/5: H.invert right/left; bit 4/6: V.invert right/left)##sesd"].plurals[0] = "=22xx: Set envelope mode (bit 0: enable; bit 1: one-shot; bit 2: split shape to L/R; bit 3/5: H.invert right/left; bit 4/6: V.invert right/left)";
    strings["23xx: Set envelope period##sesd"].plurals[0] = "=23xx: Set envelope period";
    strings["25xx: Envelope slide up##sesd1"].plurals[0] = "=25xx: Envelope slide up";
    strings["26xx: Envelope slide down##sesd1"].plurals[0] = "=26xx: Envelope slide down";
    strings["29xy: Set auto-envelope (x: numerator; y: denominator)##sesd1"].plurals[0] = "=29xy: Set auto-envelope (x: numerator; y: denominator)";
    strings["this is the wavetable part of the Bubble System, which also had two AY-3-8910s.##sesd"].plurals[0] = "=this is the wavetable part of the Bubble System, which also had two AY-3-8910s.";
    strings["like OPL3, but this time it also has a 24-channel version of MultiPCM.##sesd"].plurals[0] = "=like OPL3, but this time it also has a 24-channel version of MultiPCM.";
    strings["Yamaha YMF278B (OPL4) with drums##sesd"].plurals[0] = "=Yamaha YMF278B (OPL4) with drums";
    strings["the OPL4 but with drums mode turned on.##sesd"].plurals[0] = "=the OPL4 but with drums mode turned on.";
    strings["11xx: Set filter mode (00 to 03)##sesd"].plurals[0] = "=11xx: Set filter mode (00 to 03)";
    strings["14xx: Set filter coefficient K1 low byte (00 to FF)##sesd"].plurals[0] = "=14xx: Set filter coefficient K1 low byte (00 to FF)";
    strings["15xx: Set filter coefficient K1 high byte (00 to FF)##sesd"].plurals[0] = "=15xx: Set filter coefficient K1 high byte (00 to FF)";
    strings["16xx: Set filter coefficient K2 low byte (00 to FF)##sesd"].plurals[0] = "=16xx: Set filter coefficient K2 low byte (00 to FF)";
    strings["17xx: Set filter coefficient K2 high byte (00 to FF)##sesd"].plurals[0] = "=17xx: Set filter coefficient K2 high byte (00 to FF)";
    strings["18xx: Set filter coefficient K1 slide up (00 to FF)##sesd"].plurals[0] = "=18xx: Set filter coefficient K1 slide up (00 to FF)";
    strings["19xx: Set filter coefficient K1 slide down (00 to FF)##sesd"].plurals[0] = "=19xx: Set filter coefficient K1 slide down (00 to FF)";
    strings["1Axx: Set filter coefficient K2 slide up (00 to FF)##sesd"].plurals[0] = "=1Axx: Set filter coefficient K2 slide up (00 to FF)";
    strings["1Bxx: Set filter coefficient K2 slide down (00 to FF)##sesd"].plurals[0] = "=1Bxx: Set filter coefficient K2 slide down (00 to FF)";
    strings["22xx: Set envelope left volume ramp (signed) (00 to FF)##sesd"].plurals[0] = "=22xx: Set envelope left volume ramp (signed) (00 to FF)";
    strings["23xx: Set envelope right volume ramp (signed) (00 to FF)##sesd"].plurals[0] = "=23xx: Set envelope right volume ramp (signed) (00 to FF)";
    strings["24xx: Set envelope filter coefficient k1 ramp (signed) (00 to FF)##sesd"].plurals[0] = "=24xx: Set envelope filter coefficient k1 ramp (signed) (00 to FF)";
    strings["25xx: Set envelope filter coefficient k1 ramp (signed, slower) (00 to FF)##sesd"].plurals[0] = "=25xx: Set envelope filter coefficient k1 ramp (signed, slower) (00 to FF)";
    strings["26xx: Set envelope filter coefficient k2 ramp (signed) (00 to FF)##sesd"].plurals[0] = "=26xx: Set envelope filter coefficient k2 ramp (signed) (00 to FF)";
    strings["27xx: Set envelope filter coefficient k2 ramp (signed, slower) (00 to FF)##sesd"].plurals[0] = "=27xx: Set envelope filter coefficient k2 ramp (signed, slower) (00 to FF)";
    strings["DFxx: Set sample playback direction (0: normal; 1: reverse)##sesd1"].plurals[0] = "=DFxx: Set sample playback direction (0: normal; 1: reverse)";
    strings["120x: Set pause (bit 0)##sesd"].plurals[0] = "=120x: Set pause (bit 0)";
    strings["2xxx: Set envelope count (000 to 1FF)##sesd"].plurals[0] = "=2xxx: Set envelope count (000 to 1FF)";
    strings["3xxx: Set filter coefficient K1 (000 to FFF)##sesd"].plurals[0] = "=3xxx: Set filter coefficient K1 (000 to FFF)";
    strings["4xxx: Set filter coefficient K2 (000 to FFF)##sesd"].plurals[0] = "=4xxx: Set filter coefficient K2 (000 to FFF)";
    strings["a sample chip made by Ensoniq, which is the basis for the GF1 chip found in Gravis' Ultrasound cards.##sesd"].plurals[0] = "=a sample chip made by Ensoniq, which is the basis for the GF1 chip found in Gravis' Ultrasound cards.";
    strings["like OPL but with an ADPCM channel.##sesd"].plurals[0] = "=like OPL but with an ADPCM channel.";
    strings["Yamaha Y8950 with drums##sesd"].plurals[0] = "=Yamaha Y8950 with drums";
    strings["the Y8950 chip, in drums mode.##sesd"].plurals[0] = "=the Y8950 chip, in drums mode.";
    strings["this is a variant of Konami's SCC chip with the last channel's wavetable being independent.##sesd"].plurals[0] = "=this is a variant of Konami's SCC chip with the last channel's wavetable being independent.";
    strings["10xx: Set waveform (0 to 7)##sesd1"].plurals[0] = "=10xx: Set waveform (0 to 7)";
    strings["12xx: Set pulse width (0 to 7F)##sesd"].plurals[0] = "=12xx: Set pulse width (0 to 7F)";
    strings["13xx: Set resonance (0 to FF)##sesd"].plurals[0] = "=13xx: Set resonance (0 to FF)";
    strings["14xx: Set filter mode (bit 0: ring mod; bit 1: low pass; bit 2: high pass; bit 3: band pass)##sesd"].plurals[0] = "=14xx: Set filter mode (bit 0: ring mod; bit 1: low pass; bit 2: high pass; bit 3: band pass)";
    strings["15xx: Set frequency sweep period low byte##sesd"].plurals[0] = "=15xx: Set frequency sweep period low byte";
    strings["16xx: Set frequency sweep period high byte##sesd"].plurals[0] = "=16xx: Set frequency sweep period high byte";
    strings["17xx: Set volume sweep period low byte##sesd"].plurals[0] = "=17xx: Set volume sweep period low byte";
    strings["18xx: Set volume sweep period high byte##sesd"].plurals[0] = "=18xx: Set volume sweep period high byte";
    strings["19xx: Set cutoff sweep period low byte##sesd"].plurals[0] = "=19xx: Set cutoff sweep period low byte";
    strings["1Axx: Set cutoff sweep period high byte##sesd"].plurals[0] = "=1Axx: Set cutoff sweep period high byte";
    strings["1Bxx: Set frequency sweep boundary##sesd"].plurals[0] = "=1Bxx: Set frequency sweep boundary";
    strings["1Cxx: Set volume sweep boundary##sesd"].plurals[0] = "=1Cxx: Set volume sweep boundary";
    strings["1Dxx: Set cutoff sweep boundary##sesd"].plurals[0] = "=1Dxx: Set cutoff sweep boundary";
    strings["1Exx: Set phase reset period low byte##sesd"].plurals[0] = "=1Exx: Set phase reset period low byte";
    strings["1Fxx: Set phase reset period high byte##sesd"].plurals[0] = "=1Fxx: Set phase reset period high byte";
    strings["20xx: Toggle frequency sweep (bit 0-6: speed; bit 7: direction is up)##sesd"].plurals[0] = "=20xx: Toggle frequency sweep (bit 0-6: speed; bit 7: direction is up)";
    strings["21xx: Toggle volume sweep (bit 0-4: speed; bit 5: direction is up; bit 6: loop; bit 7: alternate)##sesd"].plurals[0] = "=21xx: Toggle volume sweep (bit 0-4: speed; bit 5: direction is up; bit 6: loop; bit 7: alternate)";
    strings["22xx: Toggle cutoff sweep (bit 0-6: speed; bit 7: direction is up)##sesd"].plurals[0] = "=22xx: Toggle cutoff sweep (bit 0-6: speed; bit 7: direction is up)";
    strings["4xxx: Set cutoff (0 to FFF)##sesd"].plurals[0] = "=4xxx: Set cutoff (0 to FFF)";
    strings["tildearrow's fantasy sound chip. put SID, AY and VERA in a blender, and you get this!##sesd"].plurals[0] = "=tildearrow's fantasy sound chip. put SID, AY and VERA in a blender, and you get this!";
    strings["an ADPCM sound chip manufactured by OKI and used in many arcade boards.##sesd"].plurals[0] = "=an ADPCM sound chip manufactured by OKI and used in many arcade boards.";
    strings["20xx: Set chip output rate (0: clock/132; 1: clock/165)##sesd"].plurals[0] = "=20xx: Set chip output rate (0: clock/132; 1: clock/165)";
    strings["an ADPCM sound chip manufactured by OKI and used in the Sharp X68000.##sesd"].plurals[0] = "=an ADPCM sound chip manufactured by OKI and used in the Sharp X68000.";
    strings["20xx: Set frequency divider (0-2)##sesd"].plurals[0] = "=20xx: Set frequency divider (0-2)";
    strings["21xx: Select clock rate (0: full; 1: half)##sesd"].plurals[0] = "=21xx: Select clock rate (0: full; 1: half)";
    strings["used in some arcade boards. Can play back either 4-bit ADPCM, 8-bit PCM or 16-bit PCM.##sesd"].plurals[0] = "=used in some arcade boards. Can play back either 4-bit ADPCM, 8-bit PCM or 16-bit PCM.";
    strings["10xx: Set waveform##sesd8"].plurals[0] = "=10xx: Set waveform";
    strings["11xx: Select waveform (local)##sesd1"].plurals[0] = "=11xx: Select waveform (local)";
    strings["10xx: Set waveform##sesd9"].plurals[0] = "=10xx: Set waveform";
    strings["11xx: Toggle noise mode##sesd2"].plurals[0] = "=11xx: Toggle noise mode";
    strings["a wavetable sound chip used in Pac-Man, among other early Namco arcade games.##sesd"].plurals[0] = "=a wavetable sound chip used in Pac-Man, among other early Namco arcade games.";
    strings["successor of the original Namco WSG chip, used in later Namco arcade games.##sesd"].plurals[0] = "=successor of the original Namco WSG chip, used in later Namco arcade games.";
    strings["like Namco C15 but with stereo sound.##sesd"].plurals[0] = "=like Namco C15 but with stereo sound.";
    strings["a square wave additive synthesis chip made by OKI. used in some arcade machines and instruments.##sesd"].plurals[0] = "=a square wave additive synthesis chip made by OKI. used in some arcade machines and instruments.";
    strings["10xy: Set group control (x: sustain; y: part toggle bitmask)##sesd"].plurals[0] = "=10xy: Set group control (x: sustain; y: part toggle bitmask)";
    strings["11xx: Set noise mode##sesd0"].plurals[0] = "=11xx: Set noise mode";
    strings["12xx: Set group attack (0 to 5)##sesd"].plurals[0] = "=12xx: Set group attack (0 to 5)";
    strings["13xx: Set group decay (0 to 11)##sesd"].plurals[0] = "=13xx: Set group decay (0 to 11)";
    strings["Yamaha YM2612 (OPN2) with DualPCM##sesd"].plurals[0] = "=Yamaha YM2612 (OPN2) with DualPCM";
    strings["this chip is mostly known for being in the Sega Genesis (but it also was on the FM Towns computer).\nthis system uses software mixing to provide two sample channels.##sesd"].plurals[0] = "=this chip is mostly known for being in the Sega Genesis (but it also was on the FM Towns computer).\nthis system uses software mixing to provide two sample channels.";
    strings["Yamaha YM2612 (OPN2) Extended Channel 3 with DualPCM and CSM##sesd"].plurals[0] = "=Yamaha YM2612 (OPN2) Extended Channel 3 with DualPCM and CSM";
    strings["this chip is mostly known for being in the Sega Genesis (but it also was on the FM Towns computer).\nthis system uses software mixing to provide two sample channels.\nthis one is in Extended Channel mode, which turns the third FM channel into four operators with independent notes/frequencies.\nthis one includes CSM mode control for special effects on Channel 3.##sesd"].plurals[0] = "=this chip is mostly known for being in the Sega Genesis (but it also was on the FM Towns computer).\nthis system uses software mixing to provide two sample channels.\nthis one is in Extended Channel mode, which turns the third FM channel into four operators with independent notes/frequencies.\nthis one includes CSM mode control for special effects on Channel 3.";
    strings["an SN76489 derivative used in Neo Geo Pocket, has independent stereo volume and noise channel frequency.##sesd"].plurals[0] = "=an SN76489 derivative used in Neo Geo Pocket, has independent stereo volume and noise channel frequency.";
    strings["20xx: Set noise length (0: short, 1: long)##sesd"].plurals[0] = "=20xx: Set noise length (0: short, 1: long)";
    strings["Generic PCM DAC##sesd"].plurals[0] = "=Generic PCM DAC";
    strings["as generic sample playback as it gets.##sesd"].plurals[0] = "=as generic sample playback as it gets.";
    strings["this PCM chip was widely used at Konami arcade boards in 1986-1990.##sesd"].plurals[0] = "=this PCM chip was widely used at Konami arcade boards in 1986-1990.";
    strings["yet another PCM chip from Irem. like Amiga, but less pitch resolution and no sample loop.##sesd"].plurals[0] = "=yet another PCM chip from Irem. like Amiga, but less pitch resolution and no sample loop.";
    strings["a SoC with wavetable sound hardware.##sesd"].plurals[0] = "=a SoC with wavetable sound hardware.";
    strings["a game console with 3 channels of square wave. it's what happens after fusing TIA and VIC together.##sesd"].plurals[0] = "=a game console with 3 channels of square wave. it's what happens after fusing TIA and VIC together.";
    strings["10xx: Set ring modulation (0: disable, 1: enable)##sesd"].plurals[0] = "=10xx: Set ring modulation (0: disable, 1: enable)";
    strings["11xx: Raw frequency (0-3E)##sesd"].plurals[0] = "=11xx: Raw frequency (0-3E)";
    strings["ZX Spectrum Beeper (QuadTone Engine)##sesd"].plurals[0] = "=ZX Spectrum Beeper (QuadTone Engine)";
    strings["another ZX Spectrum beeper system with full PWM pulses and 3-level volume per channel. it also has a pitchable overlay sample channel.##sesd"].plurals[0] = "=another ZX Spectrum beeper system with full PWM pulses and 3-level volume per channel. it also has a pitchable overlay sample channel.";
    strings["12xx: Set pulse width##sesd1"].plurals[0] = "=12xx: Set pulse width";
    strings["this PCM chip was widely used at Konami arcade boards in 1990-1992.##sesd"].plurals[0] = "=this PCM chip was widely used at Konami arcade boards in 1990-1992.";
    strings["DFxx: Set sample playback direction (0: normal; 1: reverse)##sesd2"].plurals[0] = "=DFxx: Set sample playback direction (0: normal; 1: reverse)";
    strings["two square waves (one may be turned into noise). used in the Commodore Plus/4, 16 and 116.##sesd"].plurals[0] = "=two square waves (one may be turned into noise). used in the Commodore Plus/4, 16 and 116.";
    strings["Namco's first PCM chip from 1987. it's pretty good for being so.##sesd"].plurals[0] = "=Namco's first PCM chip from 1987. it's pretty good for being so.";
    strings["Namco's PCM chip used in their NA-1/2 hardware.\nvery similar to C140, but has noise generator.##sesd"].plurals[0] = "=Namco's PCM chip used in their NA-1/2 hardware.\nvery similar to C140, but has noise generator.";
    strings["11xx: Set noise mode##sesd1"].plurals[0] = "=11xx: Set noise mode";
    strings["12xy: Set invert mode (x: surround; y: invert)##sesd"].plurals[0] = "=12xy: Set invert mode (x: surround; y: invert)";
    strings["ESS ES1xxx series (ESFM)##sesd"].plurals[0] = "=ESS ES1xxx series (ESFM)";
    strings["a unique FM synth featured in PC sound cards.\nbased on the OPL3 design, but with lots of its features extended.##sesd"].plurals[0] = "=a unique FM synth featured in PC sound cards.\nbased on the OPL3 design, but with lots of its features extended.";
    strings["2Exx: Toggle hard envelope reset on new notes##sesd"].plurals[0] = "=2Exx: Toggle hard envelope reset on new notes";
    strings["first Ensoniq chip used in their synths and Apple IIGS computer. Has 32 hard-panned 8-bit wavetable/sample channels, can do oscillator sync (like SID) and amplitude modulation. Can have up to 128 KiB (2 banks of 64 KiB) of memory for wavetables/samples.\nAs Robert Yannes (SID chip creator) said, it's more or less what SID chip could be if he was given enough time for its development.##sesd"].plurals[0] = "=first Ensoniq chip used in their synths and Apple IIGS computer. Has 32 hard-panned 8-bit wavetable/sample channels, can do oscillator sync (like SID) and amplitude modulation. Can have up to 128 KiB (2 banks of 64 KiB) of memory for wavetables/samples.\nAs Robert Yannes (SID chip creator) said, it's more or less what SID chip could be if he was given enough time for its development.";
    strings["11xx: Set number of enabled oscillators (2-1F)##sesd"].plurals[0] = "=11xx: Set number of enabled oscillators (2-1F)";
    strings["12xx: Set oscillator output (0-7, 0=left, 1=right)##sesd"].plurals[0] = "=12xx: Set oscillator output (0-7, 0=left, 1=right)";
    strings["13xx: Set wave/sample length (0-7, 0=256, 1=512, 2=1024, etc.)##sesd"].plurals[0] = "=13xx: Set wave/sample length (0-7, 0=256, 1=512, 2=1024, etc.)";
    strings["14xx: Set wave/sample position in memory (xx*256 offset)##sesd"].plurals[0] = "=14xx: Set wave/sample position in memory (xx*256 offset)";
    strings["15xx: Set oscillator mode (0-3)##sesd"].plurals[0] = "=15xx: Set oscillator mode (0-3)";
    strings["a fantasy sound chip designed by jvsTSX and The Beesh-Spweesh!\nused in the Hexheld fantasy console.##sesd"].plurals[0] = "=a fantasy sound chip designed by jvsTSX and The Beesh-Spweesh!\nused in the Hexheld fantasy console.";
    strings["20xx: Load low byte of noise channel LFSR (00 to FF) or slope channel accumulator (00 to 7F)##sesd"].plurals[0] = "=20xx: Load low byte of noise channel LFSR (00 to FF) or slope channel accumulator (00 to 7F)";
    strings["21xx: Load high byte of noise channel LFSR (00 to FF)##sesd"].plurals[0] = "=21xx: Load high byte of noise channel LFSR (00 to FF)";
    strings["22xx: Write to I/O port A##sesd"].plurals[0] = "=22xx: Write to I/O port A";
    strings["23xx: Write to I/O port B##sesd"].plurals[0] = "=23xx: Write to I/O port B";
    strings["this chip was featured in the Enterprise 128 computer. it is similar to POKEY, but with stereo output, more features and frequency precision and the ability to turn left or right (or both) channel into a 6-bit DAC for sample playback.##sesd"].plurals[0] = "=this chip was featured in the Enterprise 128 computer. it is similar to POKEY, but with stereo output, more features and frequency precision and the ability to turn left or right (or both) channel into a 6-bit DAC for sample playback.";
    strings["10xx: Set waveform (0 to 4; 0 to 3 on noise)##sesd"].plurals[0] = "=10xx: Set waveform (0 to 4; 0 to 3 on noise)";
    strings["11xx: Set noise frequency source (0: fixed; 1-3: channels 1 to 3)##sesd"].plurals[0] = "=11xx: Set noise frequency source (0: fixed; 1-3: channels 1 to 3)";
    strings["12xx: Toggle high-pass with next channel##sesd"].plurals[0] = "=12xx: Toggle high-pass with next channel";
    strings["13xx: Toggle ring modulation with channel+2##sesd"].plurals[0] = "=13xx: Toggle ring modulation with channel+2";
    strings["14xx: Toggle swap counters (noise only)##sesd"].plurals[0] = "=14xx: Toggle swap counters (noise only)";
    strings["15xx: Toggle low pass (noise only)##sesd"].plurals[0] = "=15xx: Toggle low pass (noise only)";
    strings["16xx: Set clock divider (0: /2; 1: /3)##sesd"].plurals[0] = "=16xx: Set clock divider (0: /2; 1: /3)";
    strings["a fictional sound chip by LTVA. like SID, but with many of its problems fixed. also features extended functionality like more wave mixing modes, tonal noise, filter and volume per channel.##sesd"].plurals[0] = "=a fictional sound chip by LTVA. like SID, but with many of its problems fixed. also features extended functionality like more wave mixing modes, tonal noise, filter and volume per channel.";
    strings["a fictional sound chip by Euly. similar to Ricoh 2A03, but all the duty cycles are different, noise has 32 pitches instead of 16 and you have four hard-coded waveforms on triangle channel.##sesd"].plurals[0] = "=a fictional sound chip by Euly. similar to Ricoh 2A03, but all the duty cycles are different, noise has 32 pitches instead of 16 and you have four hard-coded waveforms on triangle channel.";
    strings["12xx: Set duty cycle/noise mode (pulse: 0 to 3; noise: 0 or 1, wave: 0 to 3)##sesd"].plurals[0] = "=12xx: Set duty cycle/noise mode (pulse: 0 to 3; noise: 0 or 1, wave: 0 to 3)";
    strings["19xx: Set wave linear counter (0 to 7F; 80 and higher halt)##sesd"].plurals[0] = "=19xx: Set wave linear counter (0 to 7F; 80 and higher halt)";
    strings["additional PCM FIFO channels in Game Boy Advance driven directly by its DMA hardware.##sesd"].plurals[0] = "=additional PCM FIFO channels in Game Boy Advance driven directly by its DMA hardware.";
    strings["additional PCM FIFO channels in Game Boy Advance driven by software mixing to provide up to sixteen sample channels.##sesd"].plurals[0] = "=additional PCM FIFO channels in Game Boy Advance driven by software mixing to provide up to sixteen sample channels.";
    strings["11xy: Set echo channel (x: left/right source; y: delay (0 disables))##sesd"].plurals[0] = "11xy: =Set echo channel (x: left/right source; y: delay (0 disables))";
    strings["12xy: Toggle invert (x: left; y: right)##sesd"].plurals[0] = "12xy: =Toggle invert (x: left; y: right)";
    strings["a handheld video game console with two screens. it uses a stylus.##sesd"].plurals[0] = "=a handheld video game console with two screens. it uses a stylus.";
    strings["12xx: Set duty cycle (pulse: 0 to 7)##sesd"].plurals[0] = "12xx: =Set duty cycle (pulse: 0 to 7)";
    strings["1Fxx: Set global volume (0 to 7F)##sesd"].plurals[0] = "1Fxx: =Set global volume (0 to 7F)";
    strings["Dummy System##sesd"].plurals[0] = "=Dummy System";
    strings["this is a system designed for testing purposes.##sesd"].plurals[0] = "=this is a system designed for testing purposes.";

    //channel names

    strings["Channel 1##sesd"].plurals[0] = "=Channel 1";
    strings["Channel 2##sesd"].plurals[0] = "=Channel 2";
    strings["Channel 3##sesd"].plurals[0] = "=Channel 3";
    strings["Channel 4##sesd"].plurals[0] = "=Channel 4";
    strings["Channel 5##sesd"].plurals[0] = "=Channel 5";
    strings["Channel 6##sesd"].plurals[0] = "=Channel 6";
    strings["Channel 7##sesd"].plurals[0] = "=Channel 7";
    strings["Channel 8##sesd"].plurals[0] = "=Channel 8";
    strings["Channel 9##sesd"].plurals[0] = "=Channel 9";
    strings["Channel 10##sesd"].plurals[0] = "=Channel 10";
    strings["Channel 11##sesd"].plurals[0] = "=Channel 11";
    strings["Channel 12##sesd"].plurals[0] = "=Channel 12";
    strings["Channel 13##sesd"].plurals[0] = "=Channel 13";
    strings["Channel 14##sesd"].plurals[0] = "=Channel 14";
    strings["Channel 15##sesd"].plurals[0] = "=Channel 15";
    strings["Channel 16##sesd"].plurals[0] = "=Channel 16";
    strings["Channel 17##sesd"].plurals[0] = "=Channel 17";
    strings["Channel 18##sesd"].plurals[0] = "=Channel 18";
    strings["Channel 19##sesd"].plurals[0] = "=Channel 19";
    strings["Channel 20##sesd"].plurals[0] = "=Channel 20";
    strings["Channel 21##sesd"].plurals[0] = "=Channel 21";
    strings["Channel 22##sesd"].plurals[0] = "=Channel 22";
    strings["Channel 23##sesd"].plurals[0] = "=Channel 23";
    strings["Channel 24##sesd"].plurals[0] = "=Channel 24";
    strings["Channel 25##sesd"].plurals[0] = "=Channel 25";
    strings["Channel 26##sesd"].plurals[0] = "=Channel 26";
    strings["Channel 27##sesd"].plurals[0] = "=Channel 27";
    strings["Channel 28##sesd"].plurals[0] = "=Channel 28";
    strings["Channel 29##sesd"].plurals[0] = "=Channel 29";
    strings["Channel 30##sesd"].plurals[0] = "=Channel 30";
    strings["Channel 31##sesd"].plurals[0] = "=Channel 31";
    strings["Channel 32##sesd"].plurals[0] = "=Channel 32";

    strings["Square##sesd"].plurals[0] = "=Square";

    strings["Square 1##sesd"].plurals[0] = "=Square 1";
    strings["Square 2##sesd"].plurals[0] = "=Square 2";
    strings["Square 3##sesd"].plurals[0] = "=Square 3";

    strings["Pulse##sesd"].plurals[0] = "=Pulse";

    strings["Pulse 1##sesd"].plurals[0] = "=Pulse 1";
    strings["Pulse 2##sesd"].plurals[0] = "=Pulse 2";

    strings["Wave##sesd"].plurals[0] = "=Wave";
    strings["Wavetable##sesd"].plurals[0] = "=Wavetable";

    strings["Triangle##sesd"].plurals[0] = "=Triangle";

    strings["PCM##sesd"].plurals[0] = "=PCM";

    strings["PCM 1##sesd"].plurals[0] = "=PCM 1";
    strings["PCM 2##sesd"].plurals[0] = "=PCM 2";
    strings["PCM 3##sesd"].plurals[0] = "=PCM 3";
    strings["PCM 4##sesd"].plurals[0] = "=PCM 4";
    strings["PCM 5##sesd"].plurals[0] = "=PCM 5";
    strings["PCM 6##sesd"].plurals[0] = "=PCM 6";
    strings["PCM 7##sesd"].plurals[0] = "=PCM 7";
    strings["PCM 8##sesd"].plurals[0] = "=PCM 8";
    strings["PCM 9##sesd"].plurals[0] = "=PCM 9";
    strings["PCM 10##sesd"].plurals[0] = "=PCM 10";
    strings["PCM 11##sesd"].plurals[0] = "=PCM 11";
    strings["PCM 12##sesd"].plurals[0] = "=PCM 12";
    strings["PCM 13##sesd"].plurals[0] = "=PCM 13";
    strings["PCM 14##sesd"].plurals[0] = "=PCM 14";
    strings["PCM 15##sesd"].plurals[0] = "=PCM 15";
    strings["PCM 16##sesd"].plurals[0] = "=PCM 16";
    strings["PCM 17##sesd"].plurals[0] = "=PCM 17";
    strings["PCM 18##sesd"].plurals[0] = "=PCM 18";
    strings["PCM 19##sesd"].plurals[0] = "=PCM 19";
    strings["PCM 20##sesd"].plurals[0] = "=PCM 20";
    strings["PCM 21##sesd"].plurals[0] = "=PCM 21";
    strings["PCM 22##sesd"].plurals[0] = "=PCM 22";
    strings["PCM 23##sesd"].plurals[0] = "=PCM 23";
    strings["PCM 24##sesd"].plurals[0] = "=PCM 24";

    strings["DPCM##sesd"].plurals[0] = "=DPCM";

    strings["ADPCM##sesd"].plurals[0] = "=ADPCM";

    strings["ADPCM 1##sesd"].plurals[0] = "=ADPCM 1";
    strings["ADPCM 2##sesd"].plurals[0] = "=ADPCM 2";
    strings["ADPCM 3##sesd"].plurals[0] = "=ADPCM 3";

    strings["ADPCM-A 1##sesd"].plurals[0] = "=ADPCM-A 1";
    strings["ADPCM-A 2##sesd"].plurals[0] = "=ADPCM-A 2";
    strings["ADPCM-A 3##sesd"].plurals[0] = "=ADPCM-A 3";
    strings["ADPCM-A 4##sesd"].plurals[0] = "=ADPCM-A 4";
    strings["ADPCM-A 5##sesd"].plurals[0] = "=ADPCM-A 5";
    strings["ADPCM-A 6##sesd"].plurals[0] = "=ADPCM-A 6";

    strings["ADPCM-B##sesd"].plurals[0] = "=ADPCM-B";

    strings["Sample##sesd"].plurals[0] = "=Sample";

    strings["DAC Left##sesd"].plurals[0] = "=DAC Left";
    strings["DAC Right##sesd"].plurals[0] = "=DAC Right";

    strings["Noise##sesd"].plurals[0] = "=Noise";

    strings["Noise 1##sesd"].plurals[0] = "=Noise 1";
    strings["Noise 2##sesd"].plurals[0] = "=Noise 2";
    strings["Noise 3##sesd"].plurals[0] = "=Noise 3";

    strings["Slope##sesd"].plurals[0] = "=Slope";
    
    strings["FM 6/PCM 1##sesd"].plurals[0] = "=FM 6/PCM 1";
    strings["CSM Timer##sesd"].plurals[0] = "=CSM Timer";

    strings["VRC6 Saw##sesd"].plurals[0] = "=VRC6 Saw";

    strings["4OP 1##sesd"].plurals[0] = "=4OP 1";
    strings["4OP 3##sesd"].plurals[0] = "=4OP 3";
    strings["4OP 5##sesd"].plurals[0] = "=4OP 5";
    strings["4OP 7##sesd"].plurals[0] = "=4OP 7";
    strings["4OP 9##sesd"].plurals[0] = "=4OP 9";
    strings["4OP 11##sesd"].plurals[0] = "=4OP 11";

    strings["Kick/FM 7##sesd"].plurals[0] = "=Kick/FM 7";
    strings["Kick/FM 16##sesd"].plurals[0] = "=Kick/FM 16";
    strings["Kick##sesd"].plurals[0] = "=Kick";
    strings["Snare##sesd"].plurals[0] = "=Snare";
    strings["Top##sesd"].plurals[0] = "=Top";
    strings["HiHat##sesd"].plurals[0] = "=HiHat";
    strings["Tom##sesd"].plurals[0] = "=Tom";
    strings["Rim##sesd"].plurals[0] = "=Rim";

    // channel short names

    strings["CH1##sesd"].plurals[0] = "=CH1";
    strings["CH2##sesd"].plurals[0] = "=CH2";
    strings["CH3##sesd"].plurals[0] = "=CH3";
    strings["CH4##sesd"].plurals[0] = "=CH4";
    strings["CH5##sesd"].plurals[0] = "=CH5";
    strings["CH6##sesd"].plurals[0] = "=CH6";
    strings["CH7##sesd"].plurals[0] = "=CH7";
    strings["CH8##sesd"].plurals[0] = "=CH8";
    strings["CH9##sesd"].plurals[0] = "=CH9";

    strings["NO##sesd"].plurals[0] = "=NO";
    strings["N1##sesd"].plurals[0] = "=N1";
    strings["N2##sesd"].plurals[0] = "=N2";
    strings["N3##sesd"].plurals[0] = "=N3";

    strings["SL##sesd"].plurals[0] = "=SL";

    strings["S1##sesd"].plurals[0] = "=S1";
    strings["S2##sesd"].plurals[0] = "=S2";
    strings["S3##sesd"].plurals[0] = "=S3";
    strings["S4##sesd"].plurals[0] = "=S4";
    strings["S5##sesd"].plurals[0] = "=S5";
    strings["S6##sesd"].plurals[0] = "=S6";

    strings["P1##sesd"].plurals[0] = "=P1";
    strings["P2##sesd"].plurals[0] = "=P2";
    strings["P3##sesd"].plurals[0] = "=P3";
    strings["P4##sesd"].plurals[0] = "=P4";
    strings["P5##sesd"].plurals[0] = "=P5";
    strings["P6##sesd"].plurals[0] = "=P6";
    strings["P7##sesd"].plurals[0] = "=P7";
    strings["P8##sesd"].plurals[0] = "=P8";
    strings["P9##sesd"].plurals[0] = "=P9";
    strings["P10##sesd"].plurals[0] = "=P10";
    strings["P11##sesd"].plurals[0] = "=P11";
    strings["P12##sesd"].plurals[0] = "=P12";
    strings["P13##sesd"].plurals[0] = "=P13";
    strings["P14##sesd"].plurals[0] = "=P14";
    strings["P15##sesd"].plurals[0] = "=P15";
    strings["P16##sesd"].plurals[0] = "=P16";
    strings["P17##sesd"].plurals[0] = "=P17";
    strings["P18##sesd"].plurals[0] = "=P18";
    strings["P19##sesd"].plurals[0] = "=P19";
    strings["P20##sesd"].plurals[0] = "=P20";
    strings["P21##sesd"].plurals[0] = "=P21";
    strings["P22##sesd"].plurals[0] = "=P22";
    strings["P23##sesd"].plurals[0] = "=P23";
    strings["P24##sesd"].plurals[0] = "=P24";

    strings["BD##sesd"].plurals[0] = "=BD";
    strings["SD##sesd"].plurals[0] = "=SD";
    strings["TP##sesd"].plurals[0] = "=TP";
    strings["HH##sesd"].plurals[0] = "=HH";
    strings["TM##sesd"].plurals[0] = "=TM";
    strings["RM##sesd"].plurals[0] = "=RM";

    strings["P##sesd"].plurals[0] = "=P";

    strings["VS##sesd"].plurals[0] = "=VS";

    strings["TR##sesd"].plurals[0] = "=TR";
    strings["DMC##sesd"].plurals[0] = "=DMC";

    strings["WA##sesd"].plurals[0] = "=WA";
}
