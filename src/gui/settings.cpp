/**
 * Furnace Tracker - multi-system chiptune tracker
 * Copyright (C) 2021-2024 tildearrow and contributors
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "gui.h"
#include "imgui_internal.h"
#include "fonts.h"
#include "../ta-log.h"
#include "../fileutils.h"
#include "../utfutils.h"
#include "util.h"
#include "guiConst.h"
#include "intConst.h"
#include "ImGuiFileDialog.h"
#include "IconsFontAwesome4.h"
#include "furIcons.h"
#include "misc/cpp/imgui_stdlib.h"
#include "misc/freetype/imgui_freetype.h"
#include "scaling.h"
#include <fmt/printf.h>

#define DEFAULT_NOTE_KEYS "5:7;6:4;7:3;8:16;10:6;11:8;12:24;13:10;16:11;17:9;18:26;19:28;20:12;21:17;22:1;23:19;24:23;25:5;26:14;27:2;28:21;29:0;30:100;31:13;32:15;34:18;35:20;36:22;38:25;39:27;43:100;46:101;47:29;48:31;53:102;"

#if defined(_WIN32) || defined(__APPLE__) || defined(IS_MOBILE)
#define POWER_SAVE_DEFAULT 1
#else
// currently off on Linux/other due to Mesa catch-up behavior.
#define POWER_SAVE_DEFAULT 0
#endif

#ifdef HAVE_FREETYPE
#define FONT_BACKEND_DEFAULT 0
#else
#define FONT_BACKEND_DEFAULT 0
#endif

#if defined(__HAIKU__) || defined(IS_MOBILE) || (defined(_WIN32) && !defined(_WIN64))
// NFD doesn't support Haiku
// NFD doesn't support Windows XP either
#define SYS_FILE_DIALOG_DEFAULT 0
#else
#define SYS_FILE_DIALOG_DEFAULT 1
#endif

const char* fontBackends[]={
  "stb_truetype",
  "FreeType",
  NULL
};

const char* mainFonts[]={
  "IBM Plex Sans",
  "Liberation Sans",
  "Exo",
  "Proggy Clean",
  "GNU Unifont",
  "<Use system font>##sgse0",
  "<Custom...>##sgse0",
  NULL
};

const char* headFonts[]={
  "IBM Plex Sans",
  "Liberation Sans",
  "Exo",
  "Proggy Clean",
  "GNU Unifont",
  "<Use system font>##sgse1",
  "<Custom...>##sgse1",
  NULL
};

const char* patFonts[]={
  "IBM Plex Mono",
  "Mononoki",
  "PT Mono",
  "Proggy Clean",
  "GNU Unifont",
  "<Use system font>##sgse2",
  "<Custom...>##sgse2",
  NULL
};

const char* audioBackends[]={
  "JACK",
  "SDL",
  "PortAudio",
  NULL
};

const bool isProAudio[]={
  true,
  false,
  false
};

const char* nonProAudioOuts[]={
  "Mono##sgse0",
  "Stereo##sgse",
  "What?##sgse0",
  "Quadraphonic##sgse",
  "What?##sgse1",
  "5.1 Surround##sgse",
  "What?##sgse2",
  "7.1 Surround##sgse",
  NULL
};

const char* audioQualities[]={
  "High##sgse",
  "Low##sgse",
  NULL
};

const char* arcadeCores[]={
  "ymfm",
  "Nuked-OPM",
  NULL
};

const char* ym2612Cores[]={
  "Nuked-OPN2",
  "ymfm",
  "YMF276-LLE",
  NULL
};

const char* snCores[]={
  "MAME",
  "Nuked-PSG Mod",
  NULL
};

const char* nesCores[]={
  "puNES",
  "NSFplay",
  NULL
};

const char* c64Cores[]={
  "reSID",
  "reSIDfp",
  "dSID",
  NULL
};

const char* pokeyCores[]={
  "Atari800 (mzpokeysnd)",
  "ASAP (C++ port)##sgse",
  NULL
};

const char* opnCores[]={
  "ymfm only",
  "Nuked-OPN2 (FM) + ymfm (SSG/ADPCM)",
  NULL
};

const char* opl2Cores[]={
  "Nuked-OPL3",
  "ymfm",
  "YM3812-LLE",
  NULL
};

const char* opl3Cores[]={
  "Nuked-OPL3",
  "ymfm",
  "YMF262-LLE",
  NULL
};

const char* pcspkrOutMethods[]={
  "evdev SND_TONE",
  "KIOCSOUND on /dev/tty1##sgse",
  "/dev/port",
  "KIOCSOUND on standard output##sgse",
  "outb()",
  NULL
};

const char* valueInputStyles[]={
  "Disabled/custom##sgse0",
  "Two octaves (0 is C-4, F is D#5)##sgse",
  "Raw (note number is value)##sgse",
  "Two octaves alternate (lower keys are 0-9, upper keys are A-F)##sgse",
  "Use dual control change (one for each nibble)##sgse0",
  "Use 14-bit control change##sgse0",
  "Use single control change (imprecise)##sgse0",
  NULL
};

const char* valueSInputStyles[]={
  "Disabled/custom##sgse1",
  "Use dual control change (one for each nibble)##sgse1",
  "Use 14-bit control change##sgse1",
  "Use single control change (imprecise)##sgse1",
  NULL
};

const char* messageTypes[]={
  "--select--##sgse",
  "???",
  "???",
  "???",
  "???",
  "???",
  "???",
  "???",
  "Note Off##sgse",
  "Note On##sgse",
  "Aftertouch##sgse",
  "Control##sgse",
  "Program##sgse0",
  "ChanPressure##sgse",
  "Pitch Bend##sgse",
  "SysEx##sgse",
  NULL
};

const char* messageChannels[]={
  "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "=Any", NULL
};

const char* specificControls[19]={
  "Instrument##sgse0",
  "Volume##sgse0",
  "Effect 1 type##sgse",
  "Effect 1 value##sgse",
  "Effect 2 type##sgse",
  "Effect 2 value##sgse",
  "Effect 3 type##sgse",
  "Effect 3 value##sgse",
  "Effect 4 type##sgse",
  "Effect 4 value##sgse",
  "Effect 5 type##sgse",
  "Effect 5 value##sgse",
  "Effect 6 type##sgse",
  "Effect 6 value##sgse",
  "Effect 7 type##sgse",
  "Effect 7 value##sgse",
  "Effect 8 type##sgse",
  "Effect 8 value##sgse",
  NULL
};

#define SAMPLE_RATE_SELECTABLE(x) \
  if (ImGui::Selectable(#x,settings.audioRate==x)) { \
    settings.audioRate=x; \
    settingsChanged=true; \
  }

#define BUFFER_SIZE_SELECTABLE(x) \
  if (ImGui::Selectable(#x,settings.audioBufSize==x)) { \
    settings.audioBufSize=x; \
    settingsChanged=true; \
  }

#define CHANS_SELECTABLE(x) \
  if (ImGui::Selectable(_L(nonProAudioOuts[x-1]),settings.audioChans==x)) { \
    settings.audioChans=x; \
    settingsChanged=true; \
  }

#define UI_COLOR_CONFIG(what,label) \
  if (ImGui::ColorEdit4(_L(label "##CC_" #what),(float*)&uiColors[what])) { \
    applyUISettings(false); \
    settingsChanged=true; \
  }

#define KEYBIND_CONFIG_BEGIN(id) \
  if (ImGui::BeginTable(id,2)) {

#define KEYBIND_CONFIG_END \
    ImGui::EndTable(); \
  }

#define UI_KEYBIND_CONFIG(what) \
  ImGui::TableNextRow(); \
  ImGui::TableNextColumn(); \
  ImGui::AlignTextToFramePadding();\
  ImGui::TextUnformatted(_L(guiActions[what].friendlyName)); \
  ImGui::TableNextColumn(); \
  if (ImGui::Button(fmt::sprintf("%s##KC_" #what,(bindSetPending && bindSetTarget==what)?_L("Press key...##sgse"):_L(getKeyName(actionKeys[what]).c_str())).c_str())) { \
    promptKey(what); \
    settingsChanged=true; \
  } \
  if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) actionKeys[what]=0;

#define CONFIG_SUBSECTION(what) \
  if (_subInit) { \
    ImGui::Separator(); \
  } else { \
    _subInit=true; \
  } \
  ImGui::PushFont(headFont); \
  ImGui::TextUnformatted(what); \
  ImGui::PopFont();

#define CONFIG_SECTION(what) \
  if (ImGui::BeginTabItem(what)) { \
    bool _subInit=false; \
    ImVec2 settingsViewSize=ImGui::GetContentRegionAvail(); \
    settingsViewSize.y-=ImGui::GetFrameHeight()+ImGui::GetStyle().WindowPadding.y; \
    if (ImGui::BeginChild("SettingsView",settingsViewSize))

#define END_SECTION } \
  ImGui::EndChild(); \
  ImGui::EndTabItem();

String stripName(String what) {
  String ret;
  for (char& i: what) {
    if ((i>='A' && i<='Z') || (i>='a' && i<='z') || (i>='0' && i<='9')) {
      ret+=i;
    } else {
      ret+='-';
    }
  }
  return ret;
}

void FurnaceGUI::promptKey(int which) {
  bindSetTarget=which;
  bindSetActive=true;
  bindSetPending=true;
  bindSetPrevValue=actionKeys[which];
  actionKeys[which]=0;
}

struct MappedInput {
  int scan;
  int val;
  MappedInput():
    scan(SDL_SCANCODE_UNKNOWN), val(0) {}
  MappedInput(int s, int v):
    scan(s), val(v) {}
};

void FurnaceGUI::drawSettings() {
  if (nextWindow==GUI_WINDOW_SETTINGS) {
    settingsOpen=true;
    ImGui::SetNextWindowFocus();
    nextWindow=GUI_WINDOW_NOTHING;
  }
  if (!settingsOpen) return;
  if (mobileUI) {
    ImVec2 setWindowPos=ImVec2(0,0);
    ImVec2 setWindowSize=ImVec2(canvasW,canvasH);
    ImGui::SetNextWindowPos(setWindowPos);
    ImGui::SetNextWindowSize(setWindowSize);
  } else {
    ImGui::SetNextWindowSizeConstraints(ImVec2(200.0f*dpiScale,100.0f*dpiScale),ImVec2(canvasW,canvasH));
  }
  if (ImGui::Begin("Settings",&settingsOpen,ImGuiWindowFlags_NoDocking|globalWinFlags, _L("Settings###Settings"))) {
    if (!settingsOpen) {
      if (settingsChanged) {
        settingsOpen=true;
        showWarning(_L("Do you want to save your settings?##sgse"),GUI_WARN_CLOSE_SETTINGS);
      } else {
        settingsOpen=false;
      }
    }
    if (ImGui::BeginTabBar("settingsTab")) {
      // NEW SETTINGS HERE
      CONFIG_SECTION(_L("General##sgse")) {
        // SUBSECTION PROGRAM
        CONFIG_SUBSECTION(_L("Program##sgse1"));
        String curRenderBackend=settings.renderBackend.empty()?GUI_BACKEND_DEFAULT_NAME:settings.renderBackend;
        if (ImGui::BeginCombo(_L("Render backend##sgse"),curRenderBackend.c_str())) {
#ifdef HAVE_RENDER_SDL
          if (ImGui::Selectable("SDL Renderer",curRenderBackend=="SDL")) {
            settings.renderBackend="SDL";
            settingsChanged=true;
          }
#endif
#ifdef HAVE_RENDER_DX11
          if (ImGui::Selectable("DirectX 11",curRenderBackend=="DirectX 11")) {
            settings.renderBackend="DirectX 11";
            settingsChanged=true;
          }
#endif
#ifdef HAVE_RENDER_GL
          if (ImGui::Selectable("OpenGL",curRenderBackend=="OpenGL")) {
            settings.renderBackend="OpenGL";
            settingsChanged=true;
          }
#endif
          ImGui::EndCombo();
        }
        if (ImGui::IsItemHovered()) {
          ImGui::SetTooltip(_L("you may need to restart Furnace for this setting to take effect.##sgse0"));
        }
        if (curRenderBackend=="SDL") {
          if (ImGui::BeginCombo(_L("Render driver##sgse"),settings.renderDriver.empty()?_L("Automatic##sgse0"):settings.renderDriver.c_str())) {
            if (ImGui::Selectable(_L("Automatic##sgse1"),settings.renderDriver.empty())) {
              settings.renderDriver="";
              settingsChanged=true;
            }
            for (String& i: availRenderDrivers) {
              if (ImGui::Selectable(i.c_str(),i==settings.renderDriver)) {
                settings.renderDriver=i;
                settingsChanged=true;
              }
            }
            ImGui::EndCombo();
          }
          if (ImGui::IsItemHovered()) {
            ImGui::SetTooltip(_L("you may need to restart Furnace for this setting to take effect.##sgse1"));
          }
        }

        bool renderClearPosB=settings.renderClearPos;
        if (ImGui::Checkbox(_L("Late render clear##sgse"),&renderClearPosB)) {
          settings.renderClearPos=renderClearPosB;
          settingsChanged=true;
        }
        if (ImGui::IsItemHovered()) {
          ImGui::SetTooltip(_L("calls rend->clear() after rend->present(). might reduce UI latency by one frame in some drivers.##sgse"));
        }

        bool powerSaveB=settings.powerSave;
        if (ImGui::Checkbox(_L("Power-saving mode##sgse"),&powerSaveB)) {
          settings.powerSave=powerSaveB;
          settingsChanged=true;
        }
        if (ImGui::IsItemHovered()) {
          ImGui::SetTooltip(_L("saves power by lowering the frame rate to 2fps when idle.\nmay cause issues under Mesa drivers!##sgse"));
        }

#ifndef IS_MOBILE
        bool noThreadedInputB=settings.noThreadedInput;
        if (ImGui::Checkbox(_L("Disable threaded input (restart after changing!)##sgse"),&noThreadedInputB)) {
          settings.noThreadedInput=noThreadedInputB;
          settingsChanged=true;
        }
        if (ImGui::IsItemHovered()) {
          ImGui::SetTooltip(_L("threaded input processes key presses for note preview on a separate thread (on supported platforms), which reduces latency.\nhowever, crashes have been reported when threaded input is on. enable this option if that is the case.##sgse"));
        }
#endif

        bool eventDelayB=settings.eventDelay;
        if (ImGui::Checkbox(_L("Enable event delay##sgse"),&eventDelayB)) {
          settings.eventDelay=eventDelayB;
          settingsChanged=true;
          applyUISettings(false);
        }
        if (ImGui::IsItemHovered()) {
          ImGui::SetTooltip(_L("may cause issues with high-polling-rate mice when previewing notes.##sgse"));
        }

        pushWarningColor(settings.chanOscThreads>cpuCores,settings.chanOscThreads>(cpuCores*2));
        if (ImGui::InputInt(_L("Per-channel oscilloscope threads##sgse"),&settings.chanOscThreads)) {
          if (settings.chanOscThreads<0) settings.chanOscThreads=0;
          if (settings.chanOscThreads>(cpuCores*3)) settings.chanOscThreads=cpuCores*3;
          if (settings.chanOscThreads>256) settings.chanOscThreads=256;
          settingsChanged=true;
        }
        if (settings.chanOscThreads>=(cpuCores*3)) {
          if (ImGui::IsItemHovered()) {
            ImGui::SetTooltip(_L("you're being silly, aren't you? that's enough.##sgse"));
          }
        } else if (settings.chanOscThreads>(cpuCores*2)) {
          if (ImGui::IsItemHovered()) {
            ImGui::SetTooltip(_L("what are you doing? stop!##sgse"));
          }
        } else if (settings.chanOscThreads>cpuCores) {
          if (ImGui::IsItemHovered()) {
            ImGui::SetTooltip(_L("it is a bad idea to set this number higher than your CPU core count (%d)!##sgse"),cpuCores);
          }
        }
        popWarningColor();

        // SUBSECTION FILE
        CONFIG_SUBSECTION(_L("File##sgse"));

        bool sysFileDialogB=settings.sysFileDialog;
        if (ImGui::Checkbox(_L("Use system file picker##sgse"),&sysFileDialogB)) {
          settings.sysFileDialog=sysFileDialogB;
          settingsChanged=true;
        }

        if (ImGui::InputInt(_L("Number of recent files##sgse"),&settings.maxRecentFile,1,5)) {
          if (settings.maxRecentFile<0) settings.maxRecentFile=0;
          if (settings.maxRecentFile>30) settings.maxRecentFile=30;
          settingsChanged=true;
        }

        bool compressB=settings.compress;
        if (ImGui::Checkbox(_L("Compress when saving##sgse"),&compressB)) {
          settings.compress=compressB;
          settingsChanged=true;
        }
        if (ImGui::IsItemHovered()) {
          ImGui::SetTooltip(_L("use zlib to compress saved songs.##sgse"));
        }

        bool saveUnusedPatternsB=settings.saveUnusedPatterns;
        if (ImGui::Checkbox(_L("Save unused patterns##sgse"),&saveUnusedPatternsB)) {
          settings.saveUnusedPatterns=saveUnusedPatternsB;
          settingsChanged=true;
        }

        bool newPatternFormatB=settings.newPatternFormat;
        if (ImGui::Checkbox(_L("Use new pattern format when saving##sgse"),&newPatternFormatB)) {
          settings.newPatternFormat=newPatternFormatB;
          settingsChanged=true;
        }
        if (ImGui::IsItemHovered()) {
          ImGui::SetTooltip(_L("use a packed format which saves space when saving songs.\ndisable if you need compatibility with older Furnace and/or tools\nwhich do not support this format.##sgse"));
        }

        bool noDMFCompatB=settings.noDMFCompat;
        if (ImGui::Checkbox(_L("Don't apply compatibility flags when loading .dmf##sgse"),&noDMFCompatB)) {
          settings.noDMFCompat=noDMFCompatB;
          settingsChanged=true;
        }
        if (ImGui::IsItemHovered()) {
          ImGui::SetTooltip(_L("do not report any issues arising from the use of this option!##sgse"));
        }

        ImGui::Text(_L("Play after opening song:##sgse"));
        ImGui::Indent();
        if (ImGui::RadioButton(_L("No##pol0"),settings.playOnLoad==0)) {
          settings.playOnLoad=0;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Only if already playing##pol1"),settings.playOnLoad==1)) {
          settings.playOnLoad=1;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Yes##pol0"),settings.playOnLoad==2)) {
          settings.playOnLoad=2;
          settingsChanged=true;
        }
        ImGui::Unindent();

        ImGui::Text(_L("Audio export loop/fade out time:##sgse"));
        ImGui::Indent();
        if (ImGui::RadioButton(_L("Set to these values on start-up:##fot0"),settings.persistFadeOut==0)) {
          settings.persistFadeOut=0;
          settingsChanged=true;
        }
        ImGui::BeginDisabled(settings.persistFadeOut);
        ImGui::Indent();
        if (ImGui::InputInt(_L("Loops##sgse"),&settings.exportLoops,1,2)) {
          if (exportLoops<0) exportLoops=0;
          exportLoops=settings.exportLoops;
          settingsChanged=true;
        }
        if (ImGui::InputDouble(_L("Fade out (seconds)##sgse"),&settings.exportFadeOut,1.0,2.0,"%.1f##sgse")) {
          if (exportFadeOut<0.0) exportFadeOut=0.0;
          exportFadeOut=settings.exportFadeOut;
          settingsChanged=true;
        }
        ImGui::Unindent();
        ImGui::EndDisabled();
        if (ImGui::RadioButton(_L("Remember last values##fot1"),settings.persistFadeOut==1)) {
          settings.persistFadeOut=1;
          settingsChanged=true;
        }
        ImGui::Unindent();

        bool writeInsNamesB=settings.writeInsNames;
        if (ImGui::Checkbox(_L("Store instrument name in .fui##sgse"),&writeInsNamesB)) {
          settings.writeInsNames=writeInsNamesB;
          settingsChanged=true;
        }
        if (ImGui::IsItemHovered()) {
          ImGui::SetTooltip(_L("when enabled, saving an instrument will store its name.\nthis may increase file size.##sgse"));
        }

        bool readInsNamesB=settings.readInsNames;
        if (ImGui::Checkbox(_L("Load instrument name from .fui##sgse"),&readInsNamesB)) {
          settings.readInsNames=readInsNamesB;
          settingsChanged=true;
        }
        if (ImGui::IsItemHovered()) {
          ImGui::SetTooltip(_L("when enabled, loading an instrument will use the stored name (if present).\notherwise, it will use the file name.##sgse"));
        }

        // SUBSECTION NEW SONG
        CONFIG_SUBSECTION(_L("New Song##sgse"));
        ImGui::AlignTextToFramePadding();
        ImGui::Text(_L("Initial system:##sgse"));
        ImGui::SameLine();
        if (ImGui::Button(_L("Current system##sgse"))) {
          settings.initialSys.clear();
          for (int i=0; i<e->song.systemLen; i++) {
            settings.initialSys.set(fmt::sprintf("id%d",i),e->systemToFileFur(e->song.system[i]));
            settings.initialSys.set(fmt::sprintf("vol%d",i),(float)e->song.systemVol[i]);
            settings.initialSys.set(fmt::sprintf("pan%d",i),(float)e->song.systemPan[i]);
            settings.initialSys.set(fmt::sprintf("fr%d",i),(float)e->song.systemPanFR[i]);
            settings.initialSys.set(fmt::sprintf("flags%d",i),e->song.systemFlags[i].toBase64());
          }
          settings.initialSysName=e->song.systemName;
          settingsChanged=true;
        }
        ImGui::SameLine();
        if (ImGui::Button(_L("Randomize##sgse"))) {
          settings.initialSys.clear();
          int howMany=1+rand()%3;
          int totalAvailSys=0;
          for (totalAvailSys=0; availableSystems[totalAvailSys]; totalAvailSys++);
          if (totalAvailSys>0) {
            for (int i=0; i<howMany; i++) {
              settings.initialSys.set(fmt::sprintf("id%d",i),e->systemToFileFur((DivSystem)availableSystems[rand()%totalAvailSys]));
              settings.initialSys.set(fmt::sprintf("vol%d",i),1.0f);
              settings.initialSys.set(fmt::sprintf("pan%d",i),0.0f);
              settings.initialSys.set(fmt::sprintf("fr%d",i),0.0f);
              settings.initialSys.set(fmt::sprintf("flags%d",i),"");
            }
          } else {
            settings.initialSys.set("id0",e->systemToFileFur(DIV_SYSTEM_DUMMY));
            settings.initialSys.set("vol0",1.0f);
            settings.initialSys.set("pan0",0.0f);
            settings.initialSys.set("fr0",0.0f);
            settings.initialSys.set("flags0","");
            howMany=1;
          }
          // randomize system name
          std::vector<String> wordPool[6];
          for (int i=0; i<howMany; i++) {
            int wpPos=0;
            DivSystem sysID=e->systemFromFileFur(settings.initialSys.getInt(fmt::sprintf("id%d",i),0));
            String sName=e->getSystemName(sysID);
            String nameWord;
            sName+=" ";
            for (char& i: sName) {
              if (i==' ') {
                if (nameWord!="") {
                  wordPool[wpPos++].push_back(nameWord);
                  if (wpPos>=6) break;
                  nameWord="";
                }
              } else {
                nameWord+=i;
              }
            }
          }
          settings.initialSysName="";
          for (int i=0; i<6; i++) {
            if (wordPool[i].empty()) continue;
            settings.initialSysName+=wordPool[i][rand()%wordPool[i].size()];
            settings.initialSysName+=" ";
          }
          settingsChanged=true;
        }
        ImGui::SameLine();
        if (ImGui::Button(_L("Reset to defaults##sgse"))) {
          settings.initialSys.clear();
          settings.initialSys.set("id0",e->systemToFileFur(DIV_SYSTEM_YM2612));
          settings.initialSys.set("vol0",1.0f);
          settings.initialSys.set("pan0",0.0f);
          settings.initialSys.set("fr0",0.0f);
          settings.initialSys.set("flags0","");
          settings.initialSys.set("id1",e->systemToFileFur(DIV_SYSTEM_SMS));
          settings.initialSys.set("vol1",0.5f);
          settings.initialSys.set("pan1",0.0f);
          settings.initialSys.set("fr1",0.0f);
          settings.initialSys.set("flags1","");
          settings.initialSysName="Sega Genesis/Mega Drive";
          settingsChanged=true;
        }

        ImGui::AlignTextToFramePadding();
        ImGui::Text(_L("Name##sgse"));
        ImGui::SameLine();
        ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
        if (ImGui::InputText("##InitSysName",&settings.initialSysName)) settingsChanged=true;

        int sysCount=0;
        int doRemove=-1;
        for (size_t i=0; settings.initialSys.getInt(fmt::sprintf("id%d",i),0); i++) {
          DivSystem sysID=e->systemFromFileFur(settings.initialSys.getInt(fmt::sprintf("id%d",i),0));
          float sysVol=settings.initialSys.getFloat(fmt::sprintf("vol%d",i),0);
          float sysPan=settings.initialSys.getFloat(fmt::sprintf("pan%d",i),0);
          float sysPanFR=settings.initialSys.getFloat(fmt::sprintf("fr%d",i),0);

          sysCount=i+1;

          //bool doRemove=false;
          bool doInvert=(sysVol<0);
          float vol=fabs(sysVol);
          ImGui::PushID(i);

          ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x-ImGui::CalcTextSize(_L("Invert##sgse0")).x-ImGui::GetFrameHeightWithSpacing()*2.0-ImGui::GetStyle().ItemSpacing.x*2.0);
          if (ImGui::BeginCombo("##System",getSystemName(sysID),ImGuiComboFlags_HeightLargest)) {
            
            sysID=systemPicker(true);
            
            if (sysID!=DIV_SYSTEM_NULL)
            {
              settings.initialSys.set(fmt::sprintf("id%d",i),(int)e->systemToFileFur(sysID));
              settings.initialSys.set(fmt::sprintf("flags%d",i),"");
              settingsChanged=true;

              ImGui::CloseCurrentPopup();
            }

            ImGui::EndCombo();
          }

          ImGui::SameLine();
          if (ImGui::Checkbox(_L("Invert##sgse1"),&doInvert)) {
            sysVol=-sysVol;
            settings.initialSys.set(fmt::sprintf("vol%d",i),sysVol);
            settingsChanged=true;
          }
          ImGui::SameLine();
          //ImGui::BeginDisabled(settings.initialSys.size()<=4);
          pushDestColor();
          if (ImGui::Button(ICON_FA_MINUS "##InitSysRemove")) {
            doRemove=i;
            settingsChanged=true;
          }
          popDestColor();
          //ImGui::EndDisabled();
          ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x-ImGui::GetFrameHeightWithSpacing()*2.0-ImGui::GetStyle().ItemSpacing.x*2.0);
          if (CWSliderFloat(_L("Volume##sgse1"),&vol,0.0f,3.0f)) {
            if (doInvert) {
              if (vol<0.0001) vol=0.0001;
            }
            if (vol<0) vol=0;
            if (vol>10) vol=10;
            sysVol=doInvert?-vol:vol;
            settings.initialSys.set(fmt::sprintf("vol%d",i),(float)sysVol);
            settingsChanged=true;
          } rightClickable
          ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x-ImGui::GetFrameHeightWithSpacing()*2.0-ImGui::GetStyle().ItemSpacing.x*2.0);
          if (CWSliderFloat(_L("Panning##sgse"),&sysPan,-1.0f,1.0f)) {
            if (sysPan<-1.0f) sysPan=-1.0f;
            if (sysPan>1.0f) sysPan=1.0f;
            settings.initialSys.set(fmt::sprintf("pan%d",i),(float)sysPan);
            settingsChanged=true;
          } rightClickable
          ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x-ImGui::GetFrameHeightWithSpacing()*2.0-ImGui::GetStyle().ItemSpacing.x*2.0);
          if (CWSliderFloat(_L("Front/Rear##sgse"),&sysPanFR,-1.0f,1.0f)) {
            if (sysPanFR<-1.0f) sysPanFR=-1.0f;
            if (sysPanFR>1.0f) sysPanFR=1.0f;
            settings.initialSys.set(fmt::sprintf("fr%d",i),(float)sysPanFR);
            settingsChanged=true;
          } rightClickable

          // oh please MSVC don't cry
          if (ImGui::TreeNode(_L("Configure##sgse"))) {
            String sysFlagsS=settings.initialSys.getString(fmt::sprintf("flags%d",i),"");
            DivConfig sysFlags;
            sysFlags.loadFromBase64(sysFlagsS.c_str());
            if (drawSysConf(-1,i,sysID,sysFlags,false)) {
              settings.initialSys.set(fmt::sprintf("flags%d",i),sysFlags.toBase64());
            }
            ImGui::TreePop();
            settingsChanged=true;
          }

          ImGui::PopID();
        }

        if (doRemove>=0 && sysCount>1) {
          for (int i=doRemove; i<sysCount-1; i++) {
            int sysID=settings.initialSys.getInt(fmt::sprintf("id%d",i+1),0);
            float sysVol=settings.initialSys.getFloat(fmt::sprintf("vol%d",i+1),0);
            float sysPan=settings.initialSys.getFloat(fmt::sprintf("pan%d",i+1),0);
            float sysPanFR=settings.initialSys.getFloat(fmt::sprintf("fr%d",i+1),0);
            String sysFlags=settings.initialSys.getString(fmt::sprintf("flags%d",i+1),"");
            settings.initialSys.set(fmt::sprintf("id%d",i),sysID);
            settings.initialSys.set(fmt::sprintf("vol%d",i),sysVol);
            settings.initialSys.set(fmt::sprintf("pan%d",i),sysPan);
            settings.initialSys.set(fmt::sprintf("fr%d",i),sysPanFR);
            settings.initialSys.set(fmt::sprintf("flags%d",i),sysFlags);
          }

          settings.initialSys.remove(fmt::sprintf("id%d",sysCount-1));
          settings.initialSys.remove(fmt::sprintf("vol%d",sysCount-1));
          settings.initialSys.remove(fmt::sprintf("pan%d",sysCount-1));
          settings.initialSys.remove(fmt::sprintf("fr%d",sysCount-1));
          settings.initialSys.remove(fmt::sprintf("flags%d",sysCount-1));
        }

        if (sysCount<32) if (ImGui::Button(ICON_FA_PLUS "##InitSysAdd")) {
          settings.initialSys.set(fmt::sprintf("id%d",sysCount),(int)e->systemToFileFur(DIV_SYSTEM_YM2612));
          settings.initialSys.set(fmt::sprintf("vol%d",sysCount),1.0f);
          settings.initialSys.set(fmt::sprintf("pan%d",sysCount),0.0f);
          settings.initialSys.set(fmt::sprintf("fr%d",sysCount),0.0f);
          settings.initialSys.set(fmt::sprintf("flags%d",sysCount),"");
        }

        ImGui::Text(_L("When creating new song:##sgse"));
        ImGui::Indent();
        if (ImGui::RadioButton(_L("Display system preset selector##NSB0"),settings.newSongBehavior==0)) {
          settings.newSongBehavior=0;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Start with initial system##NSB1"),settings.newSongBehavior==1)) {
          settings.newSongBehavior=1;
          settingsChanged=true;
        }
        if (ImGui::InputText(_L("Default author name##sgse"), &settings.defaultAuthorName)) settingsChanged=true;
        ImGui::Unindent();

        // SUBSECTION START-UP
        CONFIG_SUBSECTION(_L("Start-up##sgse"));

        bool disableFadeInB=settings.disableFadeIn;
        if (ImGui::Checkbox(_L("Disable fade-in during start-up##sgse"),&disableFadeInB)) {
          settings.disableFadeIn=disableFadeInB;
          settingsChanged=true;
        }

        bool partyTimeB=settings.partyTime;
        if (ImGui::Checkbox(_L("About screen party time##sgse"),&partyTimeB)) {
          settings.partyTime=partyTimeB;
          settingsChanged=true;
        }
        if (ImGui::IsItemHovered()) {
          ImGui::SetTooltip(_L("Warning: may cause epileptic seizures.##sgse"));
        }

        // SUBSECTION BEHAVIOR
        CONFIG_SUBSECTION(_L("Behavior##sgse"));
        bool blankInsB=settings.blankIns;
        if (ImGui::Checkbox(_L("New instruments are blank##sgse"),&blankInsB)) {
          settings.blankIns=blankInsB;
          settingsChanged=true;
        }

        CONFIG_SUBSECTION(_L("Language##sgse"));

        if(ImGui::BeginCombo(_L("GUI language##sgse"), locale.getLangName(locale.getLangIndex())))
        {
          for(int i = 0; i < DIV_LANG_MAX; i++)
          {
            if (ImGui::Selectable(locale.getLangName((DivLang)i))) 
            {
              locale.setLanguage((DivLang)i);
              initSystemPresets();

              settings.language=i;
              settingsChanged=true;

              logI("The locale translated strings array size: %d", (int)locale.getMemoryUsage());
            }
          }

          ImGui::EndCombo();
        }
        //ImGui::TextUnformatted(_L("test##sgse"));

        /*if(settings.language == (int)DIV_LANG_RUSSIAN)
        {
          ImGui::Text(_LP("%d apple", 1), 1);
          ImGui::Text(_LP("%d apple", 2), 2);
          ImGui::Text(_LP("%d apple", 5), 5);
          ImGui::TextUnformatted(_L("iulserghiueshgui##sgse"));
        }*/

        END_SECTION;
      }

      CONFIG_SECTION(_L("Audio##sgse")) {
        // SUBSECTION OUTPUT
        CONFIG_SUBSECTION(_L("Output##sgse"));
        if (ImGui::BeginTable("##Output",2)) {
          ImGui::TableSetupColumn("##Label",ImGuiTableColumnFlags_WidthFixed);
          ImGui::TableSetupColumn("##Combo",ImGuiTableColumnFlags_WidthStretch);
#if defined(HAVE_JACK) || defined(HAVE_PA)
          ImGui::TableNextRow();
          ImGui::TableNextColumn();
          ImGui::AlignTextToFramePadding();
          ImGui::Text(_L("Backend##sgse"));
          ImGui::TableNextColumn();
          int prevAudioEngine=settings.audioEngine;
          if (ImGui::BeginCombo("##Backend",_L(audioBackends[settings.audioEngine]))) {
#ifdef HAVE_JACK
            if (ImGui::Selectable("JACK",settings.audioEngine==DIV_AUDIO_JACK)) {
              settings.audioEngine=DIV_AUDIO_JACK;
              settingsChanged=true;
            }
#endif
            if (ImGui::Selectable("SDL",settings.audioEngine==DIV_AUDIO_SDL)) {
              settings.audioEngine=DIV_AUDIO_SDL;
              settingsChanged=true;
            }
#ifdef HAVE_PA
            if (ImGui::Selectable("PortAudio",settings.audioEngine==DIV_AUDIO_PORTAUDIO)) {
              settings.audioEngine=DIV_AUDIO_PORTAUDIO;
              settingsChanged=true;
            }
#endif
            if (settings.audioEngine!=prevAudioEngine) {
              audioEngineChanged=true;
              settings.audioDevice="";
              if (!isProAudio[settings.audioEngine]) settings.audioChans=2;
            }
            ImGui::EndCombo();
          }
#endif

          if (settings.audioEngine==DIV_AUDIO_SDL) {
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::AlignTextToFramePadding();
            ImGui::Text(_L("Driver##sgse"));
            ImGui::TableNextColumn();
            if (ImGui::BeginCombo("##SDLADriver",settings.sdlAudioDriver.empty()?_L("Automatic##sgse2"):_L(settings.sdlAudioDriver.c_str()))) {
              if (ImGui::Selectable(_L("Automatic##sgse2"),settings.sdlAudioDriver.empty())) {
                settings.sdlAudioDriver="";
                settingsChanged=true;
              }
              for (String& i: availAudioDrivers) {
                if (ImGui::Selectable(i.c_str(),i==settings.sdlAudioDriver)) {
                  settings.sdlAudioDriver=i;
                  settingsChanged=true;
                }
              }
              ImGui::EndCombo();
            }
            if (ImGui::IsItemHovered()) {
              ImGui::SetTooltip(_L("you may need to restart Furnace for this setting to take effect.##sgse2"));
            }
          }

          ImGui::TableNextRow();
          ImGui::TableNextColumn();
          ImGui::AlignTextToFramePadding();
          ImGui::Text(_L("Device##sgse"));
          ImGui::TableNextColumn();
          if (audioEngineChanged) {
            ImGui::BeginDisabled();
            if (ImGui::BeginCombo("##AudioDevice",_L("<click on OK or Apply first>##sgse"))) {
              ImGui::Text(_L("ALERT - TRESPASSER DETECTED##sgse"));
              if (ImGui::IsItemHovered()) {
                showError(_L("you have been arrested for trying to engage with a disabled combo box.##sgse"));
                ImGui::CloseCurrentPopup();
              }
              ImGui::EndCombo();
            }
            ImGui::EndDisabled();
          } else {
            String audioDevName=settings.audioDevice.empty()?_L("<System default>##sgse0"):settings.audioDevice;
            if (ImGui::BeginCombo("##AudioDevice",audioDevName.c_str())) {
              if (ImGui::Selectable(_L("<System default>##sgse1"),settings.audioDevice.empty())) {
                settings.audioDevice="";
                settingsChanged=true;
              }
              for (String& i: e->getAudioDevices()) {
                if (ImGui::Selectable(i.c_str(),i==settings.audioDevice)) {
                  settings.audioDevice=i;
                  settingsChanged=true;
                }
              }
              ImGui::EndCombo();
            }
          }

          ImGui::TableNextRow();
          ImGui::TableNextColumn();
          ImGui::AlignTextToFramePadding();
          ImGui::Text(_L("Sample rate##sgse"));
          ImGui::TableNextColumn();
          String sr=fmt::sprintf("%d",settings.audioRate);
          if (ImGui::BeginCombo("##SampleRate",sr.c_str())) {
            SAMPLE_RATE_SELECTABLE(8000);
            SAMPLE_RATE_SELECTABLE(16000);
            SAMPLE_RATE_SELECTABLE(22050);
            SAMPLE_RATE_SELECTABLE(32000);
            SAMPLE_RATE_SELECTABLE(44100);
            SAMPLE_RATE_SELECTABLE(48000);
            SAMPLE_RATE_SELECTABLE(88200);
            SAMPLE_RATE_SELECTABLE(96000);
            SAMPLE_RATE_SELECTABLE(192000);
            ImGui::EndCombo();
          }

          ImGui::TableNextRow();
          ImGui::TableNextColumn();
          if (isProAudio[settings.audioEngine]) {
            ImGui::AlignTextToFramePadding();
            ImGui::Text(_L("Outputs##sgse"));
            ImGui::TableNextColumn();
            if (ImGui::InputInt("##AudioChansI",&settings.audioChans,1,2)) {
              if (settings.audioChans<1) settings.audioChans=1;
              if (settings.audioChans>16) settings.audioChans=16;
              settingsChanged=true;
            }
          } else {
            ImGui::AlignTextToFramePadding();
            ImGui::Text(_L("Channels##sgse"));
            ImGui::TableNextColumn();
            String chStr=(settings.audioChans<1 || settings.audioChans>8)?_L("What?##sgse3"):_L(nonProAudioOuts[settings.audioChans-1]);
            if (ImGui::BeginCombo("##AudioChans",chStr.c_str())) {
              CHANS_SELECTABLE(1);
              CHANS_SELECTABLE(2);
              CHANS_SELECTABLE(4);
              CHANS_SELECTABLE(6);
              CHANS_SELECTABLE(8);
              ImGui::EndCombo();
            }
          }

          ImGui::TableNextRow();
          ImGui::TableNextColumn();
          ImGui::AlignTextToFramePadding();
          ImGui::Text(_L("Buffer size##sgse"));
          ImGui::TableNextColumn();
          String bs=fmt::sprintf(_L("%d (latency: ~%.1fms)##sgse"),settings.audioBufSize,2000.0*(double)settings.audioBufSize/(double)MAX(1,settings.audioRate));
          if (ImGui::BeginCombo("##BufferSize",bs.c_str())) {
            BUFFER_SIZE_SELECTABLE(64);
            BUFFER_SIZE_SELECTABLE(128);
            BUFFER_SIZE_SELECTABLE(256);
            BUFFER_SIZE_SELECTABLE(512);
            BUFFER_SIZE_SELECTABLE(1024);
            BUFFER_SIZE_SELECTABLE(2048);
            ImGui::EndCombo();
          }
          ImGui::EndTable();
        }

        if (settings.showPool) {
          bool renderPoolThreadsB=(settings.renderPoolThreads>0);
          if (ImGui::Checkbox(_L("Multi-threaded (EXPERIMENTAL)##sgse"),&renderPoolThreadsB)) {
            if (renderPoolThreadsB) {
              settings.renderPoolThreads=2;
            } else {
              settings.renderPoolThreads=0;
            }
            settingsChanged=true;
          }
          if (ImGui::IsItemHovered()) {
            ImGui::SetTooltip(_L("runs chip emulation on separate threads.\nmay increase performance when using heavy emulation cores.\n\nwarnings:\n- experimental!\n- only useful on multi-chip songs.##sgse"));
          }

          if (renderPoolThreadsB) {
            pushWarningColor(settings.renderPoolThreads>cpuCores,settings.renderPoolThreads>cpuCores);
            if (ImGui::InputInt(_L("Number of threads##sgse"),&settings.renderPoolThreads)) {
              if (settings.renderPoolThreads<2) settings.renderPoolThreads=2;
              if (settings.renderPoolThreads>32) settings.renderPoolThreads=32;
              settingsChanged=true;
            }
            if (settings.renderPoolThreads>=DIV_MAX_CHIPS) {
              if (ImGui::IsItemHovered()) {
                ImGui::SetTooltip(_L("that's the limit!##sgse"));
              }
            } else if (settings.renderPoolThreads>cpuCores) {
              if (ImGui::IsItemHovered()) {
                ImGui::SetTooltip(_L("it is a VERY bad idea to set this number higher than your CPU core count (%d)!##sgse"),cpuCores);
              }
            }
            popWarningColor();
          }
        }

        bool lowLatencyB=settings.lowLatency;
        if (ImGui::Checkbox(_L("Low-latency mode##sgse"),&lowLatencyB)) {
          settings.lowLatency=lowLatencyB;
          settingsChanged=true;
        }
        if (ImGui::IsItemHovered()) {
          ImGui::SetTooltip(_L("reduces latency by running the engine faster than the tick rate.\nuseful for live playback/jam mode.\n\nwarning: only enable if your buffer size is small (10ms or less).##sgse"));
        }

        bool forceMonoB=settings.forceMono;
        if (ImGui::Checkbox(_L("Force mono audio##sgse"),&forceMonoB)) {
          settings.forceMono=forceMonoB;
          settingsChanged=true;
        }

        if (settings.audioEngine==DIV_AUDIO_PORTAUDIO) {
          if (settings.audioDevice.find("[Windows WASAPI] ")==0) {
            bool wasapiExB=settings.wasapiEx;
            if (ImGui::Checkbox(_L("Exclusive mode##sgse"),&wasapiExB)) {
              settings.wasapiEx=wasapiExB;
              settingsChanged=true;
            }
          }
        }

        TAAudioDesc& audioWant=e->getAudioDescWant();
        TAAudioDesc& audioGot=e->getAudioDescGot();

        ImGui::Text(_L("want: %d samples @ %.0fHz (%d %s)##sgse"),audioWant.bufsize,audioWant.rate,audioWant.outChans,(settings.language == (int)DIV_LANG_ENGLISH ? ((audioWant.outChans==1)?"channel":"channels") : (_LP("channel##sgse", audioWant.outChans))));
        ImGui::Text(_L("got: %d samples @ %.0fHz (%d %s)##sgse"),audioGot.bufsize,audioGot.rate,audioWant.outChans,(settings.language == (int)DIV_LANG_ENGLISH ? ((audioWant.outChans==1)?"channel":"channels") : (_LP("channel##sgse", audioWant.outChans))));

        // SUBSECTION MIXING
        CONFIG_SUBSECTION(_L("Mixing##sgse"));
        ImGui::AlignTextToFramePadding();
        ImGui::Text(_L("Quality##sgse"));
        ImGui::SameLine();
        //if (ImGui::Combo("##Quality",&settings.audioQuality,audioQualities,2)) settingsChanged=true;
        if (ImGui::BeginCombo("##Quality",_L(audioQualities[settings.audioQuality])))
        {
          int i = 0;
          while(audioQualities[i])
          {
            if (ImGui::Selectable(_L(audioQualities[i])))
            {
              settings.audioQuality = i;
              settingsChanged=true;
            }

            i++;
          }

            ImGui::EndCombo();
          }
        
        bool clampSamplesB=settings.clampSamples;
        if (ImGui::Checkbox(_L("Software clipping##sgse"),&clampSamplesB)) {
          settings.clampSamples=clampSamplesB;
          settingsChanged=true;
        }

        bool audioHiPassB=settings.audioHiPass;
        if (ImGui::Checkbox(_L("DC offset correction##sgse"),&audioHiPassB)) {
          settings.audioHiPass=audioHiPassB;
          settingsChanged=true;
        }

        // SUBSECTION METRONOME
        CONFIG_SUBSECTION(_L("Metronome##sgse"));
        ImGui::AlignTextToFramePadding();
        ImGui::Text(_L("Volume##sgse2"));
        ImGui::SameLine();
        if (ImGui::SliderInt("##MetroVol",&settings.metroVol,0,200,"%d%%")) {
          if (settings.metroVol<0) settings.metroVol=0;
          if (settings.metroVol>200) settings.metroVol=200;
          e->setMetronomeVol(((float)settings.metroVol)/100.0f);
          settingsChanged=true;
        }

        // SUBSECTION SAMPLE PREVIEW
        CONFIG_SUBSECTION(_L("Sample preview##sgse"));
        ImGui::AlignTextToFramePadding();
        ImGui::Text(_L("Volume##sgse3"));
        ImGui::SameLine();
        if (ImGui::SliderInt("##SampleVol",&settings.sampleVol,0,100,"%d%%")) {
          if (settings.sampleVol<0) settings.sampleVol=0;
          if (settings.sampleVol>100) settings.sampleVol=100;
          e->setSamplePreviewVol(((float)settings.sampleVol)/100.0f);
          settingsChanged=true;
        }

        END_SECTION;
      }

      CONFIG_SECTION(_L("MIDI##sgse")) {
        // SUBSECTION MIDI INPUT
        CONFIG_SUBSECTION(_L("MIDI input##sgse0"));
        ImGui::AlignTextToFramePadding();
        ImGui::Text(_L("MIDI input##sgse1"));
        ImGui::SameLine();
        String midiInName=settings.midiInDevice.empty()?_L("<disabled>##sgse0"):settings.midiInDevice;
        bool hasToReloadMidi=false;
        if (ImGui::BeginCombo("##MidiInDevice",midiInName.c_str())) {
          if (ImGui::Selectable(_L("<disabled>##sgse1"),settings.midiInDevice.empty())) {
            settings.midiInDevice="";
            hasToReloadMidi=true;
            settingsChanged=true;
          }
          for (String& i: e->getMidiIns()) {
            if (ImGui::Selectable(i.c_str(),i==settings.midiInDevice)) {
              settings.midiInDevice=i;
              hasToReloadMidi=true;
              settingsChanged=true;
            }
          }
          ImGui::EndCombo();
        }

        ImGui::SameLine();
        if (ImGui::Button(_L("Re-scan MIDI devices##sgse"))) {
          e->rescanMidiDevices();
          audioEngineChanged=true;
          settingsChanged=false;
        }

        if (hasToReloadMidi) {
          midiMap.read(e->getConfigPath()+DIR_SEPARATOR_STR+"midiIn_"+stripName(settings.midiInDevice)+".cfg");
          midiMap.compile();
        }

        if (ImGui::Checkbox(_L("Note input##sgse0"),&midiMap.noteInput)) settingsChanged=true;
        if (ImGui::Checkbox(_L("Velocity input##sgse"),&midiMap.volInput)) settingsChanged=true;
        // TODO
        //ImGui::Checkbox("Use raw velocity value (don't map from linear to log)",&midiMap.rawVolume);
        //ImGui::Checkbox("Polyphonic/chord input",&midiMap.polyInput);
        if (ImGui::Checkbox(_L("Map MIDI channels to direct channels##sgse"),&midiMap.directChannel)) {
          e->setMidiDirect(midiMap.directChannel);
          e->setMidiDirectProgram(midiMap.directChannel && midiMap.directProgram);
          settingsChanged=true;
        }
        if (midiMap.directChannel) {
          if (ImGui::Checkbox(_L("Program change pass-through##sgse"),&midiMap.directProgram)) {
            e->setMidiDirectProgram(midiMap.directChannel && midiMap.directProgram);
            settingsChanged=true;
          }
        }
        if (ImGui::Checkbox(_L("Map Yamaha FM voice data to instruments##sgse"),&midiMap.yamahaFMResponse)) settingsChanged=true;
        if (!(midiMap.directChannel && midiMap.directProgram)) {
          if (ImGui::Checkbox(_L("Program change is instrument selection##sgse"),&midiMap.programChange)) settingsChanged=true;
        }
        //ImGui::Checkbox(_L("Listen to MIDI clock##sgse"),&midiMap.midiClock);
        //ImGui::Checkbox(_L("Listen to MIDI time code##sgse"),&midiMap.midiTimeCode);
        //if (ImGui::Combo(_L("Value input style##sgse0"),&midiMap.valueInputStyle,valueInputStyles,7)) settingsChanged=true;
        if (ImGui::BeginCombo(_L("Value input style##sgse1"),_L(valueInputStyles[midiMap.valueInputStyle])))
        {
          int i = 0;
          while(valueInputStyles[i])
          {
            if (ImGui::Selectable(_L(valueInputStyles[i])))
            {
              midiMap.valueInputStyle = i;
              settingsChanged=true;
            }

            i++;
          }

          ImGui::EndCombo();
        }
        if (midiMap.valueInputStyle>3) {
          if (midiMap.valueInputStyle==6) {
            if (ImGui::InputInt(_L("Control##valueCCS"),&midiMap.valueInputControlSingle,1,16)) {
              if (midiMap.valueInputControlSingle<0) midiMap.valueInputControlSingle=0;
              if (midiMap.valueInputControlSingle>127) midiMap.valueInputControlSingle=127;
              settingsChanged=true;
            }
          } else {
            if (ImGui::InputInt((midiMap.valueInputStyle==4)?_L("CC of upper nibble##valueCC1"):_L("MSB CC##valueCC1"),&midiMap.valueInputControlMSB,1,16)) {
              if (midiMap.valueInputControlMSB<0) midiMap.valueInputControlMSB=0;
              if (midiMap.valueInputControlMSB>127) midiMap.valueInputControlMSB=127;
              settingsChanged=true;
            }
            if (ImGui::InputInt((midiMap.valueInputStyle==4)?_L("CC of lower nibble##valueCC2"):_L("LSB CC##valueCC2"),&midiMap.valueInputControlLSB,1,16)) {
              if (midiMap.valueInputControlLSB<0) midiMap.valueInputControlLSB=0;
              if (midiMap.valueInputControlLSB>127) midiMap.valueInputControlLSB=127;
              settingsChanged=true;
            }
          }
        }
        if (ImGui::TreeNode(_L("Per-column control change##sgse"))) {
          for (int i=0; i<18; i++) {
            ImGui::PushID(i);
            //if (ImGui::Combo(specificControls[i],&midiMap.valueInputSpecificStyle[i],valueSInputStyles,4)) settingsChanged=true;
            if (ImGui::BeginCombo(_L(specificControls[i]),_L(valueSInputStyles[midiMap.valueInputSpecificStyle[i]])))
            {
              int j = 0;
              while(valueSInputStyles[j])
              {
                if (ImGui::Selectable(_L(valueSInputStyles[j])))
                {
                  midiMap.valueInputSpecificStyle[i] = j;
                  settingsChanged=true;
                }

                j++;
              }

              ImGui::EndCombo();
            }
            if (midiMap.valueInputSpecificStyle[i]>0) {
              ImGui::Indent();
              if (midiMap.valueInputSpecificStyle[i]==3) {
                if (ImGui::InputInt(_L("Control##valueCCS"),&midiMap.valueInputSpecificSingle[i],1,16)) {
                  if (midiMap.valueInputSpecificSingle[i]<0) midiMap.valueInputSpecificSingle[i]=0;
                  if (midiMap.valueInputSpecificSingle[i]>127) midiMap.valueInputSpecificSingle[i]=127;
                  settingsChanged=true;
                }
              } else {
                if (ImGui::InputInt((midiMap.valueInputSpecificStyle[i]==4)?_L("CC of upper nibble##valueCC1"):_L("MSB CC##valueCC1"),&midiMap.valueInputSpecificMSB[i],1,16)) {
                  if (midiMap.valueInputSpecificMSB[i]<0) midiMap.valueInputSpecificMSB[i]=0;
                  if (midiMap.valueInputSpecificMSB[i]>127) midiMap.valueInputSpecificMSB[i]=127;
                  settingsChanged=true;
                }
                if (ImGui::InputInt((midiMap.valueInputSpecificStyle[i]==4)?_L("CC of lower nibble##valueCC2"):_L("LSB CC##valueCC2"),&midiMap.valueInputSpecificLSB[i],1,16)) {
                  if (midiMap.valueInputSpecificLSB[i]<0) midiMap.valueInputSpecificLSB[i]=0;
                  if (midiMap.valueInputSpecificLSB[i]>127) midiMap.valueInputSpecificLSB[i]=127;
                  settingsChanged=true;
                }
              }
              ImGui::Unindent();
            }
            ImGui::PopID();
          }
          ImGui::TreePop();
        }
        if (ImGui::SliderFloat(_L("Volume curve##sgse0"),&midiMap.volExp,0.01,8.0,"%.2f")) {
          if (midiMap.volExp<0.01) midiMap.volExp=0.01;
          if (midiMap.volExp>8.0) midiMap.volExp=8.0;
          e->setMidiVolExp(midiMap.volExp);
          settingsChanged=true;
        } rightClickable
        float curve[128];
        for (int i=0; i<128; i++) {
          curve[i]=(int)(pow((double)i/127.0,midiMap.volExp)*127.0);
        }
        ImGui::PlotLines("##VolCurveDisplay",curve,128,0,_L("Volume curve##sgse1"),0.0,127.0,ImVec2(200.0f*dpiScale,200.0f*dpiScale));

        ImGui::AlignTextToFramePadding();
        ImGui::Text(_L("Actions:##sgse"));
        ImGui::SameLine();
        if (ImGui::Button(ICON_FA_PLUS "##AddAction")) {
          midiMap.binds.push_back(MIDIBind());
          settingsChanged=true;
        }
        ImGui::SameLine();
        if (ImGui::Button(ICON_FA_EXTERNAL_LINK "##AddLearnAction")) {
          midiMap.binds.push_back(MIDIBind());
          learning=midiMap.binds.size()-1;
          settingsChanged=true;
        }
        if (learning!=-1) {
          ImGui::SameLine();
          ImGui::Text(_L("(learning! press a button or move a slider/knob/something on your device.)##sgse"));
        }

        if (ImGui::BeginTable("MIDIActions",7)) {
          ImGui::TableSetupColumn("c0",ImGuiTableColumnFlags_WidthStretch,0.2);
          ImGui::TableSetupColumn("c1",ImGuiTableColumnFlags_WidthStretch,0.1);
          ImGui::TableSetupColumn("c2",ImGuiTableColumnFlags_WidthStretch,0.3);
          ImGui::TableSetupColumn("c3",ImGuiTableColumnFlags_WidthStretch,0.2);
          ImGui::TableSetupColumn("c4",ImGuiTableColumnFlags_WidthStretch,0.5);
          ImGui::TableSetupColumn("c5",ImGuiTableColumnFlags_WidthFixed);
          ImGui::TableSetupColumn("c6",ImGuiTableColumnFlags_WidthFixed);

          ImGui::TableNextRow(ImGuiTableRowFlags_Headers);
          ImGui::TableNextColumn();
          ImGui::Text(_L("Type##sgse0"));
          ImGui::TableNextColumn();
          ImGui::Text(_L("Channel##sgse0"));
          ImGui::TableNextColumn();
          ImGui::Text(_L("Note/Control##sgse"));
          ImGui::TableNextColumn();
          ImGui::Text(_L("Velocity/Value##sgse"));
          ImGui::TableNextColumn();
          ImGui::Text(_L("Action##sgse"));
          ImGui::TableNextColumn();
          ImGui::TableNextColumn();

          for (size_t i=0; i<midiMap.binds.size(); i++) {
            MIDIBind& bind=midiMap.binds[i];
            char bindID[1024];
            ImGui::PushID(i);
            ImGui::TableNextRow();

            ImGui::TableNextColumn();
            ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
            if (ImGui::BeginCombo("##BType",_L(messageTypes[bind.type]))) {
              for (int j=8; j<15; j++) {
                if (ImGui::Selectable(_L(messageTypes[j]),bind.type==j)) {
                  bind.type=j;
                  settingsChanged=true;
                }
              }
              ImGui::EndCombo();
            }

            ImGui::TableNextColumn();
            ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
            if (ImGui::BeginCombo("##BChannel",_L(messageChannels[bind.channel]))) {
              if (ImGui::Selectable(_L(messageChannels[16]),bind.channel==16)) {
                bind.channel=16;
                settingsChanged=true;
              }
              for (int j=0; j<16; j++) {
                if (ImGui::Selectable(_L(messageChannels[j]),bind.channel==j)) {
                  bind.channel=j;
                  settingsChanged=true;
                }
              }
              ImGui::EndCombo();
            }

            ImGui::TableNextColumn();
            if (bind.data1==128) {
              snprintf(bindID,1024,_L("Any##sgse0"));
            } else {
              const char* nName="???";
              if ((bind.data1+60)>0 && (bind.data1+60)<180) {
                nName=noteNames[bind.data1+60];
              }
              snprintf(bindID,1024,"%d (0x%.2X, %s)",bind.data1,bind.data1,nName);
            }
            ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
            if (ImGui::BeginCombo("##BValue1",bindID)) {
              if (ImGui::Selectable(_L("Any##sgse1"),bind.data1==128)) {
                bind.data1=128;
                settingsChanged=true;
              }
              for (int j=0; j<128; j++) {
                const char* nName="???";
                if ((j+60)>0 && (j+60)<180) {
                  nName=noteNames[j+60];
                }
                snprintf(bindID,1024,"%d (0x%.2X, %s)##BV1_%d",j,j,nName,j);
                if (ImGui::Selectable(bindID,bind.data1==j)) {
                  bind.data1=j;
                  settingsChanged=true;
                }
              }
              ImGui::EndCombo();
            }

            ImGui::TableNextColumn();
            if (bind.data2==128) {
              snprintf(bindID,1024,_L("Any##sgse2"));
            } else {
              snprintf(bindID,1024,"%d (0x%.2X)",bind.data2,bind.data2);
            }
            ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
            if (ImGui::BeginCombo("##BValue2",bindID)) {
              if (ImGui::Selectable(_L("Any##sgse3"),bind.data2==128)) {
                bind.data2=128;
                settingsChanged=true;
              }
              for (int j=0; j<128; j++) {
                snprintf(bindID,1024,"%d (0x%.2X)##BV2_%d",j,j,j);
                if (ImGui::Selectable(bindID,bind.data2==j)) {
                  bind.data2=j;
                  settingsChanged=true;
                }
              }
              ImGui::EndCombo();
            }

            ImGui::TableNextColumn();
            ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
            if (ImGui::BeginCombo("##BAction",(bind.action==0)?_L("--none--##sgse"):_L(guiActions[bind.action].friendlyName))) {
              if (ImGui::Selectable(_L("--none--##sgse"),bind.action==0)) {
                bind.action=0;
                settingsChanged=true;
              }
              for (int j=0; j<GUI_ACTION_MAX; j++) {
                if (strcmp(guiActions[j].friendlyName,"")==0) continue;
                if (strstr(guiActions[j].friendlyName,"---")==guiActions[j].friendlyName) {
                  ImGui::TextUnformatted(_L(guiActions[j].friendlyName));
                } else {
                  snprintf(bindID,1024,"%s##BA_%d",_L(guiActions[j].friendlyName),j);
                  if (ImGui::Selectable(bindID,bind.action==j)) {
                    bind.action=j;
                    settingsChanged=true;
                  }
                }
              }
              ImGui::EndCombo();
            }

            ImGui::TableNextColumn();
            pushToggleColors(learning==(int)i);
            if (ImGui::Button((learning==(int)i)?(_L("waiting...##BLearn")):(_L("Learn##BLearn")))) {
              if (learning==(int)i) {
                learning=-1;
              } else {
                learning=i;
              }
              settingsChanged=true;
            }
            popToggleColors();

            ImGui::TableNextColumn();
            if (ImGui::Button(ICON_FA_TIMES "##BRemove")) {
              midiMap.binds.erase(midiMap.binds.begin()+i);
              if (learning==(int)i) learning=-1;
              i--;
              settingsChanged=true;
            }

            ImGui::PopID();
          }
          ImGui::EndTable();
        }

        // SUBSECTION MIDI OUTPUT
        CONFIG_SUBSECTION(_L("MIDI output##sgse0"));
        ImGui::AlignTextToFramePadding();
        ImGui::Text(_L("MIDI output##sgse1"));
        ImGui::SameLine();
        String midiOutName=settings.midiOutDevice.empty()?_L("<disabled>##sgse2"):settings.midiOutDevice;
        if (ImGui::BeginCombo("##MidiOutDevice",midiOutName.c_str())) {
          if (ImGui::Selectable(_L("<disabled>##sgse3"),settings.midiOutDevice.empty())) {
            settings.midiOutDevice="";
            settingsChanged=true;
          }
          for (String& i: e->getMidiIns()) {
            if (ImGui::Selectable(i.c_str(),i==settings.midiOutDevice)) {
              settings.midiOutDevice=i;
              settingsChanged=true;
            }
          }
          ImGui::EndCombo();
        }

        ImGui::Text(_L("Output mode:##sgse"));
        ImGui::Indent();
        if (ImGui::RadioButton(_L("Off (use for TX81Z)##sgse"),settings.midiOutMode==0)) {
          settings.midiOutMode=0;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Melodic##sgse"),settings.midiOutMode==1)) {
          settings.midiOutMode=1;
          settingsChanged=true;
        }
        /*
        if (ImGui::RadioButton(_L("Light Show (use for Launchpad)##sgse"),settings.midiOutMode==2)) {
          settings.midiOutMode=2;
        }*/
        ImGui::Unindent();

        bool midiOutProgramChangeB=settings.midiOutProgramChange;
        if (ImGui::Checkbox(_L("Send Program Change##sgse"),&midiOutProgramChangeB)) {
          settings.midiOutProgramChange=midiOutProgramChangeB;
          settingsChanged=true;
        }

        bool midiOutClockB=settings.midiOutClock;
        if (ImGui::Checkbox(_L("Send MIDI clock##sgse"),&midiOutClockB)) {
          settings.midiOutClock=midiOutClockB;
          settingsChanged=true;
        }

        bool midiOutTimeB=settings.midiOutTime;
        if (ImGui::Checkbox(_L("Send MIDI timecode##sgse"),&midiOutTimeB)) {
          settings.midiOutTime=midiOutTimeB;
          settingsChanged=true;
        }

        if (settings.midiOutTime) {
          ImGui::Text(_L("Timecode frame rate:##sgse"));
          ImGui::Indent();
          if (ImGui::RadioButton(_L("Closest to Tick Rate##sgse"),settings.midiOutTimeRate==0)) {
            settings.midiOutTimeRate=0;
            settingsChanged=true;
          }
          if (ImGui::RadioButton(_L("Film (24fps)##sgse"),settings.midiOutTimeRate==1)) {
            settings.midiOutTimeRate=1;
            settingsChanged=true;
          }
          if (ImGui::RadioButton(_L("PAL (25fps)##sgse"),settings.midiOutTimeRate==2)) {
            settings.midiOutTimeRate=2;
            settingsChanged=true;
          }
          if (ImGui::RadioButton(_L("NTSC drop (29.97fps)##sgse"),settings.midiOutTimeRate==3)) {
            settings.midiOutTimeRate=3;
            settingsChanged=true;
          }
          if (ImGui::RadioButton(_L("NTSC non-drop (30fps)##sgse"),settings.midiOutTimeRate==4)) {
            settings.midiOutTimeRate=4;
            settingsChanged=true;
          }
          ImGui::Unindent();
        }

        END_SECTION;
      }

      CONFIG_SECTION(_L("Emulation##sgse")) {
        // SUBSECTION LAYOUT
        CONFIG_SUBSECTION(_L("Cores##sgse"));
        if (ImGui::BeginTable("##Cores",3)) {
          ImGui::TableSetupColumn("##System",ImGuiTableColumnFlags_WidthFixed);
          ImGui::TableSetupColumn("##PlaybackCores",ImGuiTableColumnFlags_WidthStretch);
          ImGui::TableSetupColumn("##RenderCores",ImGuiTableColumnFlags_WidthStretch);
          ImGui::TableNextRow(ImGuiTableRowFlags_Headers);
          ImGui::TableNextColumn();
          ImGui::Text(_L("System##sgse"));
          ImGui::TableNextColumn();
          ImGui::Text(_L("Playback Core(s)##sgse"));
          if (ImGui::IsItemHovered()) {
            ImGui::SetTooltip(_L("used for playback##sgse"));
          }
          ImGui::TableNextColumn();
          ImGui::Text(_L("Render Core(s)##sgse"));
          if (ImGui::IsItemHovered()) {
            ImGui::SetTooltip(_L("used in audio export##sgse"));
          }

          ImGui::TableNextRow();
          ImGui::TableNextColumn();
          ImGui::AlignTextToFramePadding();
          ImGui::Text("YM2151");
          ImGui::TableNextColumn();
          ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
          if (ImGui::Combo("##ArcadeCore",&settings.arcadeCore,arcadeCores,2)) settingsChanged=true;
          ImGui::TableNextColumn();
          ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
          if (ImGui::Combo("##ArcadeCoreRender",&settings.arcadeCoreRender,arcadeCores,2)) settingsChanged=true;

          ImGui::TableNextRow();
          ImGui::TableNextColumn();
          ImGui::AlignTextToFramePadding();
          ImGui::Text("YM2612");
          ImGui::TableNextColumn();
          ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
          if (ImGui::Combo("##YM2612Core",&settings.ym2612Core,ym2612Cores,3)) settingsChanged=true;
          ImGui::TableNextColumn();
          ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
          if (ImGui::Combo("##YM2612CoreRender",&settings.ym2612CoreRender,ym2612Cores,3)) settingsChanged=true;

          ImGui::TableNextRow();
          ImGui::TableNextColumn();
          ImGui::AlignTextToFramePadding();
          ImGui::Text("SN76489");
          ImGui::TableNextColumn();
          ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
          if (ImGui::Combo("##SNCore",&settings.snCore,snCores,2)) settingsChanged=true;
          ImGui::TableNextColumn();
          ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
          if (ImGui::Combo("##SNCoreRender",&settings.snCoreRender,snCores,2)) settingsChanged=true;

          ImGui::TableNextRow();
          ImGui::TableNextColumn();
          ImGui::AlignTextToFramePadding();
          ImGui::Text("NES");
          ImGui::TableNextColumn();
          ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
          if (ImGui::Combo("##NESCore",&settings.nesCore,nesCores,2)) settingsChanged=true;
          ImGui::TableNextColumn();
          ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
          if (ImGui::Combo("##NESCoreRender",&settings.nesCoreRender,nesCores,2)) settingsChanged=true;

          ImGui::TableNextRow();
          ImGui::TableNextColumn();
          ImGui::AlignTextToFramePadding();
          ImGui::Text("FDS");
          ImGui::TableNextColumn();
          ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
          if (ImGui::Combo("##FDSCore",&settings.fdsCore,nesCores,2)) settingsChanged=true;
          ImGui::TableNextColumn();
          ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
          if (ImGui::Combo("##FDSCoreRender",&settings.fdsCoreRender,nesCores,2)) settingsChanged=true;

          ImGui::TableNextRow();
          ImGui::TableNextColumn();
          ImGui::AlignTextToFramePadding();
          ImGui::Text("SID");
          ImGui::TableNextColumn();
          ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
          if (ImGui::Combo("##C64Core",&settings.c64Core,c64Cores,3)) settingsChanged=true;
          ImGui::TableNextColumn();
          ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
          if (ImGui::Combo("##C64CoreRender",&settings.c64CoreRender,c64Cores,3)) settingsChanged=true;

          ImGui::TableNextRow();
          ImGui::TableNextColumn();
          ImGui::AlignTextToFramePadding();
          ImGui::Text("POKEY");
          ImGui::TableNextColumn();
          ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
          //if (ImGui::Combo("##POKEYCore",&settings.pokeyCore,pokeyCores,2)) settingsChanged=true;
          if (ImGui::BeginCombo("##POKEYCore",_L(pokeyCores[settings.pokeyCore])))
          {
            int i = 0;
            while(pokeyCores[i])
            {
              if (ImGui::Selectable(_L(pokeyCores[i])))
              {
                settings.pokeyCore = i;
                settingsChanged=true;
              }

              i++;
            }

            ImGui::EndCombo();
          }
          ImGui::TableNextColumn();
          ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
          //if (ImGui::Combo("##POKEYCoreRender",&settings.pokeyCoreRender,pokeyCores,2)) settingsChanged=true;
          if (ImGui::BeginCombo("##POKEYCoreRender",_L(pokeyCores[settings.pokeyCoreRender])))
          {
            int i = 0;
            while(pokeyCores[i])
            {
              if (ImGui::Selectable(_L(pokeyCores[i])))
              {
                settings.pokeyCoreRender = i;
                settingsChanged=true;
              }

              i++;
            }

            ImGui::EndCombo();
          }

          ImGui::TableNextRow();
          ImGui::TableNextColumn();
          ImGui::AlignTextToFramePadding();
          ImGui::Text("OPN/OPNA/OPNB");
          ImGui::TableNextColumn();
          ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
          if (ImGui::Combo("##OPNCore",&settings.opnCore,opnCores,2)) settingsChanged=true;
          ImGui::TableNextColumn();
          ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
          if (ImGui::Combo("##OPNCoreRender",&settings.opnCoreRender,opnCores,2)) settingsChanged=true;

          ImGui::TableNextRow();
          ImGui::TableNextColumn();
          ImGui::AlignTextToFramePadding();
          ImGui::Text("OPL/OPL2/Y8950");
          ImGui::TableNextColumn();
          ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
          if (ImGui::Combo("##OPL2Core",&settings.opl2Core,opl2Cores,3)) settingsChanged=true;
          ImGui::TableNextColumn();
          ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
          if (ImGui::Combo("##OPL2CoreRender",&settings.opl2CoreRender,opl2Cores,3)) settingsChanged=true;

          ImGui::TableNextRow();
          ImGui::TableNextColumn();
          ImGui::AlignTextToFramePadding();
          ImGui::Text("OPL3");
          ImGui::TableNextColumn();
          ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
          if (ImGui::Combo("##OPL3Core",&settings.opl3Core,opl3Cores,3)) settingsChanged=true;
          ImGui::TableNextColumn();
          ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
          if (ImGui::Combo("##OPL3CoreRender",&settings.opl3CoreRender,opl3Cores,3)) settingsChanged=true;

          ImGui::EndTable();
        }
        ImGui::Separator();

        ImGui::AlignTextToFramePadding();
        ImGui::Text(_L("PC Speaker strategy##sgse"));
        ImGui::SameLine();
        //if (ImGui::Combo("##PCSOutMethod",&settings.pcSpeakerOutMethod,pcspkrOutMethods,5)) settingsChanged=true;
        if (ImGui::BeginCombo("##PCSOutMethod",_L(pcspkrOutMethods[settings.pcSpeakerOutMethod])))
        {
          int i = 0;
          while(pcspkrOutMethods[i])
          {
            if (ImGui::Selectable(_L(pcspkrOutMethods[i])))
            {
              settings.pcSpeakerOutMethod = i;
              settingsChanged=true;
            }

            i++;
          }

          ImGui::EndCombo();
        }

        /*
        ImGui::Separator();
        ImGui::Text(_L("Sample ROMs:##sgse"));

        ImGui::AlignTextToFramePadding();
        ImGui::Text(_L("OPL4 YRW801 path##sgse"));
        ImGui::SameLine();
        ImGui::InputText("##YRW801Path",&settings.yrw801Path);
        ImGui::SameLine();
        if (ImGui::Button(ICON_FA_FOLDER "##YRW801Load")) {
          openFileDialog(GUI_FILE_YRW801_ROM_OPEN);
        }

        ImGui::AlignTextToFramePadding();
        ImGui::Text(_L("MultiPCM TG100 path##sgse"));
        ImGui::SameLine();
        ImGui::InputText("##TG100Path",&settings.tg100Path);
        ImGui::SameLine();
        if (ImGui::Button(ICON_FA_FOLDER "##TG100Load")) {
          openFileDialog(GUI_FILE_TG100_ROM_OPEN);
        }

        ImGui::AlignTextToFramePadding();
        ImGui::Text(_L("MultiPCM MU5 path##sgse"));
        ImGui::SameLine();
        ImGui::InputText("##MU5Path",&settings.mu5Path);
        ImGui::SameLine();
        if (ImGui::Button(ICON_FA_FOLDER "##MU5Load")) {
          openFileDialog(GUI_FILE_MU5_ROM_OPEN);
        }
        */

        END_SECTION;
      }

      CONFIG_SECTION(_L("Keyboard##sgse0")) {
        // SUBSECTION LAYOUT
        CONFIG_SUBSECTION(_L("Keyboard##sgse1"));
        if (ImGui::Button(_L("Import##sgse0"))) {
          openFileDialog(GUI_FILE_IMPORT_KEYBINDS);
        }
        ImGui::SameLine();
        if (ImGui::Button(_L("Export##sgse0"))) {
          openFileDialog(GUI_FILE_EXPORT_KEYBINDS);
        }
        ImGui::SameLine();
        if (ImGui::Button(_L("Reset defaults##sgse0"))) {
          showWarning(_L("Are you sure you want to reset the keyboard settings?##sgse"),GUI_WARN_RESET_KEYBINDS);
        }
        if (ImGui::TreeNode(_L("Global hotkeys##sgse"))) {
          KEYBIND_CONFIG_BEGIN("keysGlobal");

          UI_KEYBIND_CONFIG(GUI_ACTION_NEW);
          UI_KEYBIND_CONFIG(GUI_ACTION_CLEAR);
          UI_KEYBIND_CONFIG(GUI_ACTION_OPEN);
          UI_KEYBIND_CONFIG(GUI_ACTION_OPEN_BACKUP);
          UI_KEYBIND_CONFIG(GUI_ACTION_SAVE);
          UI_KEYBIND_CONFIG(GUI_ACTION_SAVE_AS);
          UI_KEYBIND_CONFIG(GUI_ACTION_EXPORT);
          UI_KEYBIND_CONFIG(GUI_ACTION_UNDO);
          UI_KEYBIND_CONFIG(GUI_ACTION_REDO);
          UI_KEYBIND_CONFIG(GUI_ACTION_PLAY_TOGGLE);
          UI_KEYBIND_CONFIG(GUI_ACTION_PLAY);
          UI_KEYBIND_CONFIG(GUI_ACTION_STOP);
          UI_KEYBIND_CONFIG(GUI_ACTION_PLAY_START);
          UI_KEYBIND_CONFIG(GUI_ACTION_PLAY_REPEAT);
          UI_KEYBIND_CONFIG(GUI_ACTION_PLAY_CURSOR);
          UI_KEYBIND_CONFIG(GUI_ACTION_STEP_ONE);
          UI_KEYBIND_CONFIG(GUI_ACTION_OCTAVE_UP);
          UI_KEYBIND_CONFIG(GUI_ACTION_OCTAVE_DOWN);
          UI_KEYBIND_CONFIG(GUI_ACTION_INS_UP);
          UI_KEYBIND_CONFIG(GUI_ACTION_INS_DOWN);
          UI_KEYBIND_CONFIG(GUI_ACTION_STEP_UP);
          UI_KEYBIND_CONFIG(GUI_ACTION_STEP_DOWN);
          UI_KEYBIND_CONFIG(GUI_ACTION_TOGGLE_EDIT);
          UI_KEYBIND_CONFIG(GUI_ACTION_METRONOME);
          UI_KEYBIND_CONFIG(GUI_ACTION_REPEAT_PATTERN);
          UI_KEYBIND_CONFIG(GUI_ACTION_FOLLOW_ORDERS);
          UI_KEYBIND_CONFIG(GUI_ACTION_FOLLOW_PATTERN);
          UI_KEYBIND_CONFIG(GUI_ACTION_FULLSCREEN);
          UI_KEYBIND_CONFIG(GUI_ACTION_TX81Z_REQUEST);
          UI_KEYBIND_CONFIG(GUI_ACTION_PANIC);
          UI_KEYBIND_CONFIG(GUI_ACTION_QUIT);

          KEYBIND_CONFIG_END;
          ImGui::TreePop();
        }
        if (ImGui::TreeNode(_L("Window activation##sgse"))) {
          KEYBIND_CONFIG_BEGIN("keysWindow");

          UI_KEYBIND_CONFIG(GUI_ACTION_WINDOW_FIND);
          UI_KEYBIND_CONFIG(GUI_ACTION_WINDOW_SETTINGS);
          UI_KEYBIND_CONFIG(GUI_ACTION_WINDOW_SONG_INFO);
          UI_KEYBIND_CONFIG(GUI_ACTION_WINDOW_SUBSONGS);
          UI_KEYBIND_CONFIG(GUI_ACTION_WINDOW_SPEED);
          UI_KEYBIND_CONFIG(GUI_ACTION_WINDOW_INS_LIST);
          UI_KEYBIND_CONFIG(GUI_ACTION_WINDOW_WAVE_LIST);
          UI_KEYBIND_CONFIG(GUI_ACTION_WINDOW_SAMPLE_LIST);
          UI_KEYBIND_CONFIG(GUI_ACTION_WINDOW_ORDERS);
          UI_KEYBIND_CONFIG(GUI_ACTION_WINDOW_PATTERN);
          UI_KEYBIND_CONFIG(GUI_ACTION_WINDOW_MIXER);
          UI_KEYBIND_CONFIG(GUI_ACTION_WINDOW_GROOVES);
          UI_KEYBIND_CONFIG(GUI_ACTION_WINDOW_CHANNELS);
          UI_KEYBIND_CONFIG(GUI_ACTION_WINDOW_PAT_MANAGER);
          UI_KEYBIND_CONFIG(GUI_ACTION_WINDOW_SYS_MANAGER);
          UI_KEYBIND_CONFIG(GUI_ACTION_WINDOW_COMPAT_FLAGS);
          UI_KEYBIND_CONFIG(GUI_ACTION_WINDOW_NOTES);
          UI_KEYBIND_CONFIG(GUI_ACTION_WINDOW_INS_EDIT);
          UI_KEYBIND_CONFIG(GUI_ACTION_WINDOW_WAVE_EDIT);
          UI_KEYBIND_CONFIG(GUI_ACTION_WINDOW_SAMPLE_EDIT);
          UI_KEYBIND_CONFIG(GUI_ACTION_WINDOW_EDIT_CONTROLS);
          UI_KEYBIND_CONFIG(GUI_ACTION_WINDOW_PIANO);
          UI_KEYBIND_CONFIG(GUI_ACTION_WINDOW_OSCILLOSCOPE);
          UI_KEYBIND_CONFIG(GUI_ACTION_WINDOW_CHAN_OSC);
          UI_KEYBIND_CONFIG(GUI_ACTION_WINDOW_VOL_METER);
          UI_KEYBIND_CONFIG(GUI_ACTION_WINDOW_CLOCK);
          UI_KEYBIND_CONFIG(GUI_ACTION_WINDOW_REGISTER_VIEW);
          UI_KEYBIND_CONFIG(GUI_ACTION_WINDOW_LOG);
          UI_KEYBIND_CONFIG(GUI_ACTION_WINDOW_STATS);
          UI_KEYBIND_CONFIG(GUI_ACTION_WINDOW_EFFECT_LIST);
          UI_KEYBIND_CONFIG(GUI_ACTION_WINDOW_DEBUG);
          UI_KEYBIND_CONFIG(GUI_ACTION_WINDOW_ABOUT);
          UI_KEYBIND_CONFIG(GUI_ACTION_COLLAPSE_WINDOW);
          UI_KEYBIND_CONFIG(GUI_ACTION_CLOSE_WINDOW);

          UI_KEYBIND_CONFIG(GUI_ACTION_COMMAND_PALETTE);
          UI_KEYBIND_CONFIG(GUI_ACTION_CMDPAL_RECENT);
          UI_KEYBIND_CONFIG(GUI_ACTION_CMDPAL_INSTRUMENTS);
          UI_KEYBIND_CONFIG(GUI_ACTION_CMDPAL_SAMPLES);

          KEYBIND_CONFIG_END;
          ImGui::TreePop();
        }
        if (ImGui::TreeNode(_L("Note input##sgse1"))) {
          std::vector<MappedInput> sorted;
          if (ImGui::BeginTable("keysNoteInput",4)) {
            for (std::map<int,int>::value_type& i: noteKeys) {
              std::vector<MappedInput>::iterator j;
              for (j=sorted.begin(); j!=sorted.end(); j++) {
                if (j->val>i.second) {
                  break;
                }
              }
              sorted.insert(j,MappedInput(i.first,i.second));
            }

            static char id[4096];

            ImGui::TableNextRow(ImGuiTableRowFlags_Headers);
            ImGui::TableNextColumn();
            ImGui::Text(_L("Key##sgse"));
            ImGui::TableNextColumn();
            ImGui::Text(_L("Type##sgse1"));
            ImGui::TableNextColumn();
            ImGui::Text(_L("Value##sgse"));
            ImGui::TableNextColumn();
            ImGui::Text(_L("Remove##sgse"));

            for (MappedInput& i: sorted) {
              ImGui::TableNextRow();
              ImGui::TableNextColumn();
              ImGui::Text("%s",SDL_GetScancodeName((SDL_Scancode)i.scan));
              ImGui::TableNextColumn();
              if (i.val==102) {
                snprintf(id,4095,_L("Macro release##SNType_%d"),i.scan);
                if (ImGui::Button(id)) {
                  noteKeys[i.scan]=0;
                }
              } else if (i.val==101) {
                snprintf(id,4095,_L("Note release##SNType_%d"),i.scan);
                if (ImGui::Button(id)) {
                  noteKeys[i.scan]=102;
                }
              } else if (i.val==100) {
                snprintf(id,4095,_L("Note off##SNType_%d"),i.scan);
                if (ImGui::Button(id)) {
                  noteKeys[i.scan]=101;
                }
              } else {
                snprintf(id,4095,_L("Note##SNType_%d"),i.scan);
                if (ImGui::Button(id)) {
                  noteKeys[i.scan]=100;
                }
              }
              ImGui::TableNextColumn();
              if (i.val<100) {
                snprintf(id,4095,"##SNValue_%d",i.scan);
                if (ImGui::InputInt(id,&i.val,1,12)) {
                  if (i.val<0) i.val=0;
                  if (i.val>96) i.val=96;
                  noteKeys[i.scan]=i.val;
                  settingsChanged=true;
                }
              }
              ImGui::TableNextColumn();
              snprintf(id,4095,ICON_FA_TIMES "##SNRemove_%d",i.scan);
              if (ImGui::Button(id)) {
                noteKeys.erase(i.scan);
                settingsChanged=true;
              }
            }
            ImGui::EndTable();

            if (ImGui::BeginCombo("##SNAddNew",_L("Add...##sgse"))) {
              for (int i=0; i<SDL_NUM_SCANCODES; i++) {
                const char* sName=SDL_GetScancodeName((SDL_Scancode)i);
                if (sName==NULL) continue;
                if (sName[0]==0) continue;
                snprintf(id,4095,"%s##SNNewKey_%d",sName,i);
                if (ImGui::Selectable(id)) {
                  noteKeys[(SDL_Scancode)i]=0;
                  settingsChanged=true;
                }
              }
              ImGui::EndCombo();
            }
          }
          ImGui::TreePop();
        }
        if (ImGui::TreeNode(_L("Pattern##sgse0"))) {
          KEYBIND_CONFIG_BEGIN("keysPattern");

          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_NOTE_UP);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_NOTE_DOWN);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_OCTAVE_UP);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_OCTAVE_DOWN);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_VALUE_UP);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_VALUE_DOWN);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_VALUE_UP_COARSE);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_VALUE_DOWN_COARSE);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_SELECT_ALL);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_CUT);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_COPY);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_PASTE);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_PASTE_MIX);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_PASTE_MIX_BG);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_PASTE_FLOOD);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_PASTE_OVERFLOW);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_CURSOR_UP);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_CURSOR_DOWN);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_CURSOR_LEFT);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_CURSOR_RIGHT);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_CURSOR_UP_ONE);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_CURSOR_DOWN_ONE);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_CURSOR_LEFT_CHANNEL);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_CURSOR_RIGHT_CHANNEL);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_CURSOR_PREVIOUS_CHANNEL);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_CURSOR_NEXT_CHANNEL);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_CURSOR_BEGIN);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_CURSOR_END);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_CURSOR_UP_COARSE);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_CURSOR_DOWN_COARSE);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_SELECTION_UP);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_SELECTION_DOWN);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_SELECTION_LEFT);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_SELECTION_RIGHT);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_SELECTION_UP_ONE);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_SELECTION_DOWN_ONE);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_SELECTION_BEGIN);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_SELECTION_END);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_SELECTION_UP_COARSE);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_SELECTION_DOWN_COARSE);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_DELETE);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_PULL_DELETE);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_INSERT);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_MUTE_CURSOR);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_SOLO_CURSOR);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_UNMUTE_ALL);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_NEXT_ORDER);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_PREV_ORDER);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_COLLAPSE);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_INCREASE_COLUMNS);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_DECREASE_COLUMNS);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_INTERPOLATE);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_FADE);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_INVERT_VALUES);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_FLIP_SELECTION);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_COLLAPSE_ROWS);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_EXPAND_ROWS);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_COLLAPSE_PAT);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_EXPAND_PAT);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_COLLAPSE_SONG);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_EXPAND_SONG);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_LATCH);
          UI_KEYBIND_CONFIG(GUI_ACTION_PAT_CLEAR_LATCH);

          KEYBIND_CONFIG_END;
          ImGui::TreePop();
        }
        if (ImGui::TreeNode(_L("Instrument list##sgse"))) {
          KEYBIND_CONFIG_BEGIN("keysInsList");

          UI_KEYBIND_CONFIG(GUI_ACTION_INS_LIST_ADD);
          UI_KEYBIND_CONFIG(GUI_ACTION_INS_LIST_DUPLICATE);
          UI_KEYBIND_CONFIG(GUI_ACTION_INS_LIST_OPEN);
          UI_KEYBIND_CONFIG(GUI_ACTION_INS_LIST_OPEN_REPLACE);
          UI_KEYBIND_CONFIG(GUI_ACTION_INS_LIST_SAVE);
          UI_KEYBIND_CONFIG(GUI_ACTION_INS_LIST_SAVE_DMP);
          UI_KEYBIND_CONFIG(GUI_ACTION_INS_LIST_MOVE_UP);
          UI_KEYBIND_CONFIG(GUI_ACTION_INS_LIST_MOVE_DOWN);
          UI_KEYBIND_CONFIG(GUI_ACTION_INS_LIST_DELETE);
          UI_KEYBIND_CONFIG(GUI_ACTION_INS_LIST_EDIT);
          UI_KEYBIND_CONFIG(GUI_ACTION_INS_LIST_UP);
          UI_KEYBIND_CONFIG(GUI_ACTION_INS_LIST_DOWN);
          UI_KEYBIND_CONFIG(GUI_ACTION_INS_LIST_DIR_VIEW);

          KEYBIND_CONFIG_END;
          ImGui::TreePop();
        }
        if (ImGui::TreeNode(_L("Wavetable list##sgse"))) {
          KEYBIND_CONFIG_BEGIN("keysWaveList");

          UI_KEYBIND_CONFIG(GUI_ACTION_WAVE_LIST_ADD);
          UI_KEYBIND_CONFIG(GUI_ACTION_WAVE_LIST_DUPLICATE);
          UI_KEYBIND_CONFIG(GUI_ACTION_WAVE_LIST_OPEN);
          UI_KEYBIND_CONFIG(GUI_ACTION_WAVE_LIST_OPEN_REPLACE);
          UI_KEYBIND_CONFIG(GUI_ACTION_WAVE_LIST_SAVE);
          UI_KEYBIND_CONFIG(GUI_ACTION_WAVE_LIST_SAVE_DMW);
          UI_KEYBIND_CONFIG(GUI_ACTION_WAVE_LIST_SAVE_RAW);
          UI_KEYBIND_CONFIG(GUI_ACTION_WAVE_LIST_MOVE_UP);
          UI_KEYBIND_CONFIG(GUI_ACTION_WAVE_LIST_MOVE_DOWN);
          UI_KEYBIND_CONFIG(GUI_ACTION_WAVE_LIST_DELETE);
          UI_KEYBIND_CONFIG(GUI_ACTION_WAVE_LIST_EDIT);
          UI_KEYBIND_CONFIG(GUI_ACTION_WAVE_LIST_UP);
          UI_KEYBIND_CONFIG(GUI_ACTION_WAVE_LIST_DOWN);
          UI_KEYBIND_CONFIG(GUI_ACTION_WAVE_LIST_DIR_VIEW);

          KEYBIND_CONFIG_END;
          ImGui::TreePop();
        }
        if (ImGui::TreeNode(_L("Sample list##sgse"))) {
          KEYBIND_CONFIG_BEGIN("keysSampleList");

          UI_KEYBIND_CONFIG(GUI_ACTION_SAMPLE_LIST_ADD);
          UI_KEYBIND_CONFIG(GUI_ACTION_SAMPLE_LIST_DUPLICATE);
          UI_KEYBIND_CONFIG(GUI_ACTION_SAMPLE_CREATE_WAVE);
          UI_KEYBIND_CONFIG(GUI_ACTION_SAMPLE_LIST_OPEN);
          UI_KEYBIND_CONFIG(GUI_ACTION_SAMPLE_LIST_OPEN_REPLACE);
          UI_KEYBIND_CONFIG(GUI_ACTION_SAMPLE_LIST_OPEN_RAW);
          UI_KEYBIND_CONFIG(GUI_ACTION_SAMPLE_LIST_OPEN_REPLACE_RAW);
          UI_KEYBIND_CONFIG(GUI_ACTION_SAMPLE_LIST_SAVE);
          UI_KEYBIND_CONFIG(GUI_ACTION_SAMPLE_LIST_SAVE_RAW);
          UI_KEYBIND_CONFIG(GUI_ACTION_SAMPLE_LIST_MOVE_UP);
          UI_KEYBIND_CONFIG(GUI_ACTION_SAMPLE_LIST_MOVE_DOWN);
          UI_KEYBIND_CONFIG(GUI_ACTION_SAMPLE_LIST_DELETE);
          UI_KEYBIND_CONFIG(GUI_ACTION_SAMPLE_LIST_EDIT);
          UI_KEYBIND_CONFIG(GUI_ACTION_SAMPLE_LIST_UP);
          UI_KEYBIND_CONFIG(GUI_ACTION_SAMPLE_LIST_DOWN);
          UI_KEYBIND_CONFIG(GUI_ACTION_SAMPLE_LIST_PREVIEW);
          UI_KEYBIND_CONFIG(GUI_ACTION_SAMPLE_LIST_STOP_PREVIEW);
          UI_KEYBIND_CONFIG(GUI_ACTION_SAMPLE_LIST_DIR_VIEW);
          UI_KEYBIND_CONFIG(GUI_ACTION_SAMPLE_LIST_MAKE_MAP);

          KEYBIND_CONFIG_END;
          ImGui::TreePop();
        }
        if (ImGui::TreeNode(_L("Orders##sgse0"))) {
          KEYBIND_CONFIG_BEGIN("keysOrders");

          UI_KEYBIND_CONFIG(GUI_ACTION_ORDERS_UP);
          UI_KEYBIND_CONFIG(GUI_ACTION_ORDERS_DOWN);
          UI_KEYBIND_CONFIG(GUI_ACTION_ORDERS_LEFT);
          UI_KEYBIND_CONFIG(GUI_ACTION_ORDERS_RIGHT);
          UI_KEYBIND_CONFIG(GUI_ACTION_ORDERS_INCREASE);
          UI_KEYBIND_CONFIG(GUI_ACTION_ORDERS_DECREASE);
          UI_KEYBIND_CONFIG(GUI_ACTION_ORDERS_EDIT_MODE);
          UI_KEYBIND_CONFIG(GUI_ACTION_ORDERS_LINK);
          UI_KEYBIND_CONFIG(GUI_ACTION_ORDERS_ADD);
          UI_KEYBIND_CONFIG(GUI_ACTION_ORDERS_DUPLICATE);
          UI_KEYBIND_CONFIG(GUI_ACTION_ORDERS_DEEP_CLONE);
          UI_KEYBIND_CONFIG(GUI_ACTION_ORDERS_DUPLICATE_END);
          UI_KEYBIND_CONFIG(GUI_ACTION_ORDERS_DEEP_CLONE_END);
          UI_KEYBIND_CONFIG(GUI_ACTION_ORDERS_REMOVE);
          UI_KEYBIND_CONFIG(GUI_ACTION_ORDERS_MOVE_UP);
          UI_KEYBIND_CONFIG(GUI_ACTION_ORDERS_MOVE_DOWN);
          UI_KEYBIND_CONFIG(GUI_ACTION_ORDERS_REPLAY);

          KEYBIND_CONFIG_END;
          ImGui::TreePop();
        }
        if (ImGui::TreeNode(_L("Sample editor##sgse"))) {
          KEYBIND_CONFIG_BEGIN("keysSampleEdit");

          UI_KEYBIND_CONFIG(GUI_ACTION_SAMPLE_SELECT);
          UI_KEYBIND_CONFIG(GUI_ACTION_SAMPLE_DRAW);
          UI_KEYBIND_CONFIG(GUI_ACTION_SAMPLE_CUT);
          UI_KEYBIND_CONFIG(GUI_ACTION_SAMPLE_COPY);
          UI_KEYBIND_CONFIG(GUI_ACTION_SAMPLE_PASTE);
          UI_KEYBIND_CONFIG(GUI_ACTION_SAMPLE_PASTE_REPLACE);
          UI_KEYBIND_CONFIG(GUI_ACTION_SAMPLE_PASTE_MIX);
          UI_KEYBIND_CONFIG(GUI_ACTION_SAMPLE_SELECT_ALL);
          UI_KEYBIND_CONFIG(GUI_ACTION_SAMPLE_RESIZE);
          UI_KEYBIND_CONFIG(GUI_ACTION_SAMPLE_RESAMPLE);
          UI_KEYBIND_CONFIG(GUI_ACTION_SAMPLE_AMPLIFY);
          UI_KEYBIND_CONFIG(GUI_ACTION_SAMPLE_NORMALIZE);
          UI_KEYBIND_CONFIG(GUI_ACTION_SAMPLE_FADE_IN);
          UI_KEYBIND_CONFIG(GUI_ACTION_SAMPLE_FADE_OUT);
          UI_KEYBIND_CONFIG(GUI_ACTION_SAMPLE_INSERT);
          UI_KEYBIND_CONFIG(GUI_ACTION_SAMPLE_SILENCE);
          UI_KEYBIND_CONFIG(GUI_ACTION_SAMPLE_DELETE);
          UI_KEYBIND_CONFIG(GUI_ACTION_SAMPLE_TRIM);
          UI_KEYBIND_CONFIG(GUI_ACTION_SAMPLE_REVERSE);
          UI_KEYBIND_CONFIG(GUI_ACTION_SAMPLE_INVERT);
          UI_KEYBIND_CONFIG(GUI_ACTION_SAMPLE_SIGN);
          UI_KEYBIND_CONFIG(GUI_ACTION_SAMPLE_FILTER);
          UI_KEYBIND_CONFIG(GUI_ACTION_SAMPLE_PREVIEW);
          UI_KEYBIND_CONFIG(GUI_ACTION_SAMPLE_STOP_PREVIEW);
          UI_KEYBIND_CONFIG(GUI_ACTION_SAMPLE_ZOOM_IN);
          UI_KEYBIND_CONFIG(GUI_ACTION_SAMPLE_ZOOM_OUT);
          UI_KEYBIND_CONFIG(GUI_ACTION_SAMPLE_ZOOM_AUTO);
          UI_KEYBIND_CONFIG(GUI_ACTION_SAMPLE_MAKE_INS);
          UI_KEYBIND_CONFIG(GUI_ACTION_SAMPLE_SET_LOOP);

          KEYBIND_CONFIG_END;
          ImGui::TreePop();
        }
        END_SECTION;
      }

      CONFIG_SECTION(_L("Interface##sgse0")) {
        // SUBSECTION LAYOUT
        CONFIG_SUBSECTION(_L("Layout##sgse"));
        ImGui::AlignTextToFramePadding();
        ImGui::Text(_L("Workspace layout:##sgse"));
        ImGui::SameLine();
        if (ImGui::Button(_L("Import##sgse1"))) {
          openFileDialog(GUI_FILE_IMPORT_LAYOUT);
        }
        ImGui::SameLine();
        if (ImGui::Button(_L("Export##sgse1"))) {
          openFileDialog(GUI_FILE_EXPORT_LAYOUT);
        }
        ImGui::SameLine();
        if (ImGui::Button(_L("Reset##sgse"))) {
          showWarning(_L("Are you sure you want to reset the workspace layout?##sgse"),GUI_WARN_RESET_LAYOUT);
        }

        bool allowEditDockingB=settings.allowEditDocking;
        if (ImGui::Checkbox(_L("Allow docking editors##sgse"),&allowEditDockingB)) {
          settings.allowEditDocking=allowEditDockingB;
          settingsChanged=true;
        }

#ifndef IS_MOBILE
          bool saveWindowPosB=settings.saveWindowPos;
          if (ImGui::Checkbox(_L("Remember window position##sgse"),&saveWindowPosB)) {
            settings.saveWindowPos=saveWindowPosB;
            settingsChanged=true;
          }
          if (ImGui::IsItemHovered()) {
            ImGui::SetTooltip(_L("remembers the window's last position on start-up.##sgse"));
          }
#endif

        bool moveWindowTitleB=settings.moveWindowTitle;
        if (ImGui::Checkbox(_L("Only allow window movement when clicking on title bar##sgse"),&moveWindowTitleB)) {
          settings.moveWindowTitle=moveWindowTitleB;
          applyUISettings(false);
          settingsChanged=true;
        }

        bool centerPopupB=settings.centerPopup;
        if (ImGui::Checkbox(_L("Center pop-up windows##sgse"),&centerPopupB)) {
          settings.centerPopup=centerPopupB;
          settingsChanged=true;
        }

        ImGui::Text(_L("Play/edit controls layout:##sgse"));
        ImGui::Indent();
        if (ImGui::RadioButton(_L("Classic##ecl0"),settings.controlLayout==0)) {
          settings.controlLayout=0;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Compact##ecl1"),settings.controlLayout==1)) {
          settings.controlLayout=1;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Compact (vertical)##ecl2"),settings.controlLayout==2)) {
          settings.controlLayout=2;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Split##ecl3"),settings.controlLayout==3)) {
          settings.controlLayout=3;
          settingsChanged=true;
        }
        ImGui::Unindent();

        ImGui::Text(_L("Position of buttons in Orders:##sgse"));
        ImGui::Indent();
        if (ImGui::RadioButton(_L("Top##obp0"),settings.orderButtonPos==0)) {
          settings.orderButtonPos=0;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Left##obp1"),settings.orderButtonPos==1)) {
          settings.orderButtonPos=1;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Right##obp2"),settings.orderButtonPos==2)) {
          settings.orderButtonPos=2;
          settingsChanged=true;
        }
        ImGui::Unindent();

        // SUBSECTION MOUSE
        CONFIG_SUBSECTION(_L("Mouse##sgse"));

        if (CWSliderFloat(_L("Double-click time (seconds)##sgse"),&settings.doubleClickTime,0.02,1.0,"%.2f")) {
          if (settings.doubleClickTime<0.02) settings.doubleClickTime=0.02;
          if (settings.doubleClickTime>1.0) settings.doubleClickTime=1.0;

          applyUISettings(false);
          settingsChanged=true;
        }

        bool avoidRaisingPatternB=settings.avoidRaisingPattern;
        if (ImGui::Checkbox(_L("Don't raise pattern editor on click##sgse"),&avoidRaisingPatternB)) {
          settings.avoidRaisingPattern=avoidRaisingPatternB;
          settingsChanged=true;
        }

        bool insFocusesPatternB=settings.insFocusesPattern;
        if (ImGui::Checkbox(_L("Focus pattern editor when selecting instrument##sgse"),&insFocusesPatternB)) {
          settings.insFocusesPattern=insFocusesPatternB;
          settingsChanged=true;
        }

        ImGui::Text(_L("Note preview behavior:##sgse"));
        ImGui::Indent();
        if (ImGui::RadioButton(_L("Never##npb0"),settings.notePreviewBehavior==0)) {
          settings.notePreviewBehavior=0;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("When cursor is in Note column##npb1"),settings.notePreviewBehavior==1)) {
          settings.notePreviewBehavior=1;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("When cursor is in Note column or not in edit mode##npb2"),settings.notePreviewBehavior==2)) {
          settings.notePreviewBehavior=2;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Always##npb3"),settings.notePreviewBehavior==3)) {
          settings.notePreviewBehavior=3;
          settingsChanged=true;
        }
        ImGui::Unindent();

        ImGui::Text(_L("Allow dragging selection:##sgse"));
        ImGui::Indent();
        if (ImGui::RadioButton(_L("No##dms0"),settings.dragMovesSelection==0)) {
          settings.dragMovesSelection=0;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Yes##dms1"),settings.dragMovesSelection==1)) {
          settings.dragMovesSelection=1;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Yes (while holding Ctrl only)##dms2"),settings.dragMovesSelection==2)) {
          settings.dragMovesSelection=2;
          settingsChanged=true;
        }
        ImGui::Unindent();

        ImGui::Text(_L("Toggle channel solo on:##sgse"));
        ImGui::Indent();
        if (ImGui::RadioButton(_L("Right-click or double-click##soloA"),settings.soloAction==0)) {
          settings.soloAction=0;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Right-click##soloR"),settings.soloAction==1)) {
          settings.soloAction=1;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Double-click##soloD"),settings.soloAction==2)) {
          settings.soloAction=2;
          settingsChanged=true;
        }
        ImGui::Unindent();

        bool doubleClickColumnB=settings.doubleClickColumn;
        if (ImGui::Checkbox(_L("Double click selects entire column##sgse"),&doubleClickColumnB)) {
          settings.doubleClickColumn=doubleClickColumnB;
          settingsChanged=true;
        }

        // SUBSECTION CURSOR BEHAVIOR
        CONFIG_SUBSECTION(_L("Cursor behavior##sgse"));
        bool insertBehaviorB=settings.insertBehavior;
        if (ImGui::Checkbox(_L("Insert pushes entire channel row##sgse"),&insertBehaviorB)) {
          settings.insertBehavior=insertBehaviorB;
          settingsChanged=true;
        }

        bool pullDeleteRowB=settings.pullDeleteRow;
        if (ImGui::Checkbox(_L("Pull delete affects entire channel row##sgse"),&pullDeleteRowB)) {
          settings.pullDeleteRow=pullDeleteRowB;
          settingsChanged=true;
        }

        bool pushNibbleB=settings.pushNibble;
        if (ImGui::Checkbox(_L("Push value when overwriting instead of clearing it##sgse"),&pushNibbleB)) {
          settings.pushNibble=pushNibbleB;
          settingsChanged=true;
        }

        ImGui::Text(_L("Effect input behavior:##sgse"));
        ImGui::Indent();
        if (ImGui::RadioButton(_L("Move down##eicb0"),settings.effectCursorDir==0)) {
          settings.effectCursorDir=0;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Move to effect value (otherwise move down)##eicb1"),settings.effectCursorDir==1)) {
          settings.effectCursorDir=1;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Move to effect value/next effect and wrap around##eicb2"),settings.effectCursorDir==2)) {
          settings.effectCursorDir=2;
          settingsChanged=true;
        }
        ImGui::Unindent();

        bool effectDeletionAltersValueB=settings.effectDeletionAltersValue;
        if (ImGui::Checkbox(_L("Delete effect value when deleting effect##sgse"),&effectDeletionAltersValueB)) {
          settings.effectDeletionAltersValue=effectDeletionAltersValueB;
          settingsChanged=true;
        }

        bool absorbInsInputB=settings.absorbInsInput;
        if (ImGui::Checkbox(_L("Change current instrument when changing instrument column (absorb)##sgse"),&absorbInsInputB)) {
          settings.absorbInsInput=absorbInsInputB;
          settingsChanged=true;
        }

        bool removeInsOffB=settings.removeInsOff;
        if (ImGui::Checkbox(_L("Remove instrument value when inserting note off/release##sgse"),&removeInsOffB)) {
          settings.removeInsOff=removeInsOffB;
          settingsChanged=true;
        }

        bool removeVolOffB=settings.removeVolOff;
        if (ImGui::Checkbox(_L("Remove volume value when inserting note off/release##sgse"),&removeVolOffB)) {
          settings.removeVolOff=removeVolOffB;
          settingsChanged=true;
        }

        // SUBSECTION CURSOR MOVEMENT
        CONFIG_SUBSECTION(_L("Cursor movement##sgse"));

        ImGui::Text(_L("Wrap horizontally:##sgse"));
        ImGui::Indent();
        if (ImGui::RadioButton(_L("No##wrapH0"),settings.wrapHorizontal==0)) {
          settings.wrapHorizontal=0;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Yes##wrapH1"),settings.wrapHorizontal==1)) {
          settings.wrapHorizontal=1;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Yes, and move to next/prev row##wrapH2"),settings.wrapHorizontal==2)) {
          settings.wrapHorizontal=2;
          settingsChanged=true;
        }
        ImGui::Unindent();

        ImGui::Text(_L("Wrap vertically:##sgse"));
        ImGui::Indent();
        if (ImGui::RadioButton(_L("No##wrapV0"),settings.wrapVertical==0)) {
          settings.wrapVertical=0;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Yes##wrapV1"),settings.wrapVertical==1)) {
          settings.wrapVertical=1;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Yes, and move to next/prev pattern##wrapV2"),settings.wrapVertical==2)) {
          settings.wrapVertical=2;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Yes, and move to next/prev pattern (wrap around)##wrapV2"),settings.wrapVertical==3)) {
          settings.wrapVertical=3;
          settingsChanged=true;
        }
        ImGui::Unindent();

        ImGui::Text(_L("Cursor movement keys behavior:##sgse"));
        ImGui::Indent();
        if (ImGui::RadioButton(_L("Move by one##cmk0"),settings.scrollStep==0)) {
          settings.scrollStep=0;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Move by Edit Step##cmk1"),settings.scrollStep==1)) {
          settings.scrollStep=1;
          settingsChanged=true;
        }
        ImGui::Unindent();

        bool stepOnDeleteB=settings.stepOnDelete;
        if (ImGui::Checkbox(_L("Move cursor by edit step on delete##sgse"),&stepOnDeleteB)) {
          settings.stepOnDelete=stepOnDeleteB;
          settingsChanged=true;
        }

        bool stepOnInsertB=settings.stepOnInsert;
        if (ImGui::Checkbox(_L("Move cursor by edit step on insert (push)##sgse"),&stepOnInsertB)) {
          settings.stepOnInsert=stepOnInsertB;
          settingsChanged=true;
        }

        bool pullDeleteBehaviorB=settings.pullDeleteBehavior;
        if (ImGui::Checkbox(_L("Move cursor up on backspace-delete##sgse"),&pullDeleteBehaviorB)) {
          settings.pullDeleteBehavior=pullDeleteBehaviorB;
          settingsChanged=true;
        }

        bool cursorPastePosB=settings.cursorPastePos;
        if (ImGui::Checkbox(_L("Move cursor to end of clipboard content when pasting##sgse"),&cursorPastePosB)) {
          settings.cursorPastePos=cursorPastePosB;
          settingsChanged=true;
        }

        // SUBSECTION SCROLLING
        CONFIG_SUBSECTION(_L("Scrolling##sgse"));

        ImGui::Text(_L("Change order when scrolling outside of pattern bounds:##sgse"));
        ImGui::Indent();
        if (ImGui::RadioButton(_L("No##pscroll0"),settings.scrollChangesOrder==0)) {
          settings.scrollChangesOrder=0;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Yes##pscroll1"),settings.scrollChangesOrder==1)) {
          settings.scrollChangesOrder=1;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Yes, and wrap around song##pscroll2"),settings.scrollChangesOrder==2)) {
          settings.scrollChangesOrder=2;
          settingsChanged=true;
        }
        ImGui::Unindent();

        bool cursorFollowsOrderB=settings.cursorFollowsOrder;
        if (ImGui::Checkbox(_L("Cursor follows current order when moving it##sgse"),&cursorFollowsOrderB)) {
          settings.cursorFollowsOrder=cursorFollowsOrderB;
          settingsChanged=true;
        }
        if (ImGui::IsItemHovered()) {
          ImGui::SetTooltip(_L("applies when playback is stopped.##sgse"));
        }

        bool cursorMoveNoScrollB=settings.cursorMoveNoScroll;
        if (ImGui::Checkbox(_L("Don't scroll when moving cursor##sgse"),&cursorMoveNoScrollB)) {
          settings.cursorMoveNoScroll=cursorMoveNoScrollB;
          settingsChanged=true;
        }

        ImGui::Text(_L("Move cursor with scroll wheel:##sgse"));
        ImGui::Indent();
        if (ImGui::RadioButton(_L("No##csw0"),settings.cursorFollowsWheel==0)) {
          settings.cursorFollowsWheel=0;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Yes##csw1"),settings.cursorFollowsWheel==1)) {
          settings.cursorFollowsWheel=1;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Inverted##csw2"),settings.cursorFollowsWheel==2)) {
          settings.cursorFollowsWheel=2;
          settingsChanged=true;
        }
        ImGui::Unindent();

        // SUBSECTION ASSETS
        CONFIG_SUBSECTION(_L("Assets##sgse0"));

        bool insTypeMenuB=settings.insTypeMenu;
        if (ImGui::Checkbox(_L("Display instrument type menu when adding instrument##sgse"),&insTypeMenuB)) {
          settings.insTypeMenu=insTypeMenuB;
          settingsChanged=true;
        }

        bool selectAssetOnLoadB=settings.selectAssetOnLoad;
        if (ImGui::Checkbox(_L("Select asset after opening one##sgse"),&selectAssetOnLoadB)) {
          settings.selectAssetOnLoad=selectAssetOnLoadB;
          settingsChanged=true;
        }

        END_SECTION;
      }

      CONFIG_SECTION(_L("Appearance##sgse")) {
        // SUBSECTION INTERFACE
        CONFIG_SUBSECTION(_L("Scaling##sgse"));
        bool dpiScaleAuto=(settings.dpiScale<0.5f);
        if (ImGui::Checkbox(_L("Automatic UI scaling factor##sgse"),&dpiScaleAuto)) {
          if (dpiScaleAuto) {
            settings.dpiScale=0.0f;
          } else {
            settings.dpiScale=1.0f;
          }
          settingsChanged=true;
        }
        if (!dpiScaleAuto) {
          if (ImGui::SliderFloat(_L("UI scaling factor##sgse"),&settings.dpiScale,1.0f,3.0f,"%.2fx")) {
            if (settings.dpiScale<0.5f) settings.dpiScale=0.5f;
            if (settings.dpiScale>3.0f) settings.dpiScale=3.0f;
            settingsChanged=true;
          } rightClickable
        }

        if (ImGui::InputInt(_L("Icon size##sgse"),&settings.iconSize,1,3)) {
          if (settings.iconSize<3) settings.iconSize=3;
          if (settings.iconSize>48) settings.iconSize=48;
          settingsChanged=true;
        }

        // SUBSECTION TEXT
        CONFIG_SUBSECTION(_L("Text##sgse"));
        if (ImGui::BeginTable("##Text",2)) {
          ImGui::TableSetupColumn("##Label",ImGuiTableColumnFlags_WidthFixed);
          ImGui::TableSetupColumn("##Combos",ImGuiTableColumnFlags_WidthStretch);
#ifdef HAVE_FREETYPE
          ImGui::TableNextRow();
          ImGui::TableNextColumn();
          ImGui::AlignTextToFramePadding();
          ImGui::Text(_L("Font renderer##sgse"));
          ImGui::TableNextColumn();
          //if (ImGui::Combo("##FontBack",&settings.fontBackend,fontBackends,2)) settingsChanged=true;
          if (ImGui::BeginCombo("##FontBack",_L(fontBackends[settings.fontBackend])))
          {
            int i = 0;
            while(fontBackends[i])
            {
              if (ImGui::Selectable(_L(fontBackends[i])))
              {
                settings.fontBackend = i;
                settingsChanged=true;
              }

              i++;
            }

            ImGui::EndCombo();
          }
#else
          settings.fontBackend=0;
#endif

          ImGui::TableNextRow();
          ImGui::TableNextColumn();
          ImGui::AlignTextToFramePadding();
          ImGui::Text(_L("Main font##sgse"));
          ImGui::TableNextColumn();
          //if (ImGui::Combo("##MainFont",&settings.mainFont,mainFonts,7)) settingsChanged=true;
          if (ImGui::BeginCombo("##MainFont",_L(mainFonts[settings.mainFont])))
          {
            int i = 0;
            while(mainFonts[i])
            {
              if (ImGui::Selectable(_L(mainFonts[i])))
              {
                settings.mainFont = i;
                settingsChanged=true;
              }

              i++;
            }

            ImGui::EndCombo();
          }
          if (settings.mainFont==6) {
            ImGui::InputText("##MainFontPath",&settings.mainFontPath);
            ImGui::SameLine();
            if (ImGui::Button(ICON_FA_FOLDER "##MainFontLoad")) {
              openFileDialog(GUI_FILE_LOAD_MAIN_FONT);
              settingsChanged=true;
            }
          }
          if (ImGui::InputInt(_L("Size##MainFontSize"),&settings.mainFontSize,1,3)) {
            if (settings.mainFontSize<3) settings.mainFontSize=3;
            if (settings.mainFontSize>96) settings.mainFontSize=96;
            settingsChanged=true;
          }
          ImGui::TableNextRow();
          ImGui::TableNextColumn();
          ImGui::AlignTextToFramePadding();
          ImGui::Text(_L("Header font##sgse"));
          ImGui::TableNextColumn();
          //if (ImGui::Combo("##HeadFont",&settings.headFont,headFonts,7)) settingsChanged=true;
          if (ImGui::BeginCombo("##HeadFont",_L(headFonts[settings.headFont])))
          {
            int i = 0;
            while(headFonts[i])
            {
              if (ImGui::Selectable(_L(headFonts[i])))
              {
                settings.headFont = i;
                settingsChanged=true;
              }

              i++;
            }

            ImGui::EndCombo();
          }
          if (settings.headFont==6) {
            ImGui::InputText("##HeadFontPath",&settings.headFontPath);
            ImGui::SameLine();
            if (ImGui::Button(ICON_FA_FOLDER "##HeadFontLoad")) {
              openFileDialog(GUI_FILE_LOAD_HEAD_FONT);
              settingsChanged=true;
            }
          }
          if (ImGui::InputInt(_L("Size##HeadFontSize"),&settings.headFontSize,1,3)) {
            if (settings.headFontSize<3) settings.headFontSize=3;
            if (settings.headFontSize>96) settings.headFontSize=96;
            settingsChanged=true;
          }
          ImGui::TableNextRow();
          ImGui::TableNextColumn();
          ImGui::AlignTextToFramePadding();
          ImGui::Text(_L("Pattern font##sgse"));
          ImGui::TableNextColumn();
          //if (ImGui::Combo("##PatFont",&settings.patFont,patFonts,7)) settingsChanged=true;
          if (ImGui::BeginCombo("##PatFont",_L(patFonts[settings.patFont])))
          {
            int i = 0;
            while(patFonts[i])
            {
              if (ImGui::Selectable(_L(patFonts[i])))
              {
                settings.patFont = i;
                settingsChanged=true;
              }

              i++;
            }

            ImGui::EndCombo();
          }
          if (settings.patFont==6) {
            ImGui::InputText("##PatFontPath",&settings.patFontPath);
            ImGui::SameLine();
            if (ImGui::Button(ICON_FA_FOLDER "##PatFontLoad")) {
              openFileDialog(GUI_FILE_LOAD_PAT_FONT);
              settingsChanged=true;
            }
          }
          if (ImGui::InputInt(_L("Size##PatFontSize"),&settings.patFontSize,1,3)) {
            if (settings.patFontSize<3) settings.patFontSize=3;
            if (settings.patFontSize>96) settings.patFontSize=96;
            settingsChanged=true;
          }
          ImGui::EndTable();
        }

        if (settings.fontBackend==1) {
          bool fontAntiAliasB=settings.fontAntiAlias;
          if (ImGui::Checkbox(_L("Anti-aliased fonts##sgse"),&fontAntiAliasB)) {
            settings.fontAntiAlias=fontAntiAliasB;
            settingsChanged=true;
          }

          bool fontBitmapB=settings.fontBitmap;
          if (ImGui::Checkbox(_L("Support bitmap fonts##sgse"),&fontBitmapB)) {
            settings.fontBitmap=fontBitmapB;
            settingsChanged=true;
          }

          ImGui::Text(_L("Hinting:##sgse"));
          ImGui::Indent();
          if (ImGui::RadioButton(_L("Off (soft)##fh0"),settings.fontHinting==0)) {
            settings.fontHinting=0;
            settingsChanged=true;
          }
          if (ImGui::RadioButton(_L("Slight##fh1"),settings.fontHinting==1)) {
            settings.fontHinting=1;
            settingsChanged=true;
          }
          if (ImGui::RadioButton(_L("Normal##fh2"),settings.fontHinting==2)) {
            settings.fontHinting=2;
            settingsChanged=true;
          }
          if (ImGui::RadioButton(_L("Full (hard)##fh3"),settings.fontHinting==3)) {
            settings.fontHinting=3;
            settingsChanged=true;
          }
          ImGui::Unindent();

          ImGui::Text(_L("Auto-hinter:##sgse"));
          ImGui::Indent();
          if (ImGui::RadioButton(_L("Disable##fah0"),settings.fontAutoHint==0)) {
            settings.fontAutoHint=0;
            settingsChanged=true;
          }
          if (ImGui::RadioButton(_L("Enable##fah1"),settings.fontAutoHint==1)) {
            settings.fontAutoHint=1;
            settingsChanged=true;
          }
          if (ImGui::RadioButton(_L("Force##fah2"),settings.fontAutoHint==2)) {
            settings.fontAutoHint=2;
            settingsChanged=true;
          }
          ImGui::Unindent();
        }

        bool loadJapaneseB=settings.loadJapanese;
        if (ImGui::Checkbox(_L("Display Japanese characters##sgse"),&loadJapaneseB)) {
          settings.loadJapanese=loadJapaneseB;
          settingsChanged=true;
        }
        if (ImGui::IsItemHovered()) {
          ImGui::SetTooltip(
            _L("Only toggle this option if you have enough graphics memory.\n"
            "This is a temporary solution until dynamic font atlas is implemented in Dear ImGui.\n\n"
            "このオプションは、十分なグラフィックメモリがある場合にのみ切り替えてください。\n"
            "これは、Dear ImGuiにダイナミックフォントアトラスが実装されるまでの一時的な解決策です。##sgse")
          );
        }

        bool loadChineseB=settings.loadChinese;
        if (ImGui::Checkbox(_L("Display Chinese (Simplified) characters##sgse"),&loadChineseB)) {
          settings.loadChinese=loadChineseB;
          settingsChanged=true;
        }
        if (ImGui::IsItemHovered()) {
          ImGui::SetTooltip(
            _L("Only toggle this option if you have enough graphics memory.\n"
            "This is a temporary solution until dynamic font atlas is implemented in Dear ImGui.\n\n"
            "请在确保你有足够的显存后再启动此设定\n"
            "这是一个在ImGui实现动态字体加载之前的临时解决方案##sgse")
          );
        }

        bool loadChineseTraditionalB=settings.loadChineseTraditional;
        if (ImGui::Checkbox(_L("Display Chinese (Traditional) characters##sgse"),&loadChineseTraditionalB)) {
          settings.loadChineseTraditional=loadChineseTraditionalB;
          settingsChanged=true;
        }
        if (ImGui::IsItemHovered()) {
          ImGui::SetTooltip(
            _L("Only toggle this option if you have enough graphics memory.\n"
            "This is a temporary solution until dynamic font atlas is implemented in Dear ImGui.\n\n"
            "請在確保你有足夠的顯存后再啟動此設定\n"
            "這是一個在ImGui實現動態字體加載之前的臨時解決方案##sgse")
          );
        }

        bool loadKoreanB=settings.loadKorean;
        if (ImGui::Checkbox(_L("Display Korean characters##sgse"),&loadKoreanB)) {
          settings.loadKorean=loadKoreanB;
          settingsChanged=true;
        }
        if (ImGui::IsItemHovered()) {
          ImGui::SetTooltip(
            _L("Only toggle this option if you have enough graphics memory.\n"
            "This is a temporary solution until dynamic font atlas is implemented in Dear ImGui.\n\n"
            "그래픽 메모리가 충분한 경우에만 이 옵션을 선택하십시오.\n"
            "이 옵션은 Dear ImGui에 동적 글꼴 아틀라스가 구현될 때까지 임시 솔루션입니다.##sgse")
          );
        }

        // SUBSECTION PROGRAM
        CONFIG_SUBSECTION(_L("Program##sgse2"));
        ImGui::Text(_L("Title bar:##sgse"));
        ImGui::Indent();
        if (ImGui::RadioButton(_L("Furnace-B##tbar0"),settings.titleBarInfo==0)) {
          settings.titleBarInfo=0;
          updateWindowTitle();
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Song Name - Furnace-B##tbar1"),settings.titleBarInfo==1)) {
          settings.titleBarInfo=1;
          updateWindowTitle();
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("file_name.fur - Furnace-B##tbar2"),settings.titleBarInfo==2)) {
          settings.titleBarInfo=2;
          updateWindowTitle();
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("/path/to/file.fur - Furnace-B##tbar3"),settings.titleBarInfo==3)) {
          settings.titleBarInfo=3;
          updateWindowTitle();
          settingsChanged=true;
        }
        ImGui::Unindent();

        bool titleBarSysB=settings.titleBarSys;
        if (ImGui::Checkbox(_L("Display system name on title bar##sgse"),&titleBarSysB)) {
          settings.titleBarSys=titleBarSysB;
          updateWindowTitle();
          settingsChanged=true;
        }

        bool noMultiSystemB=settings.noMultiSystem;
        if (ImGui::Checkbox(_L("Display chip names instead of \"multi-system\" in title bar##sgse"),&noMultiSystemB)) {
          settings.noMultiSystem=noMultiSystemB;
          updateWindowTitle();
          settingsChanged=true;
        }

        ImGui::Text(_L("Status bar:##sgse"));
        ImGui::Indent();
        if (ImGui::RadioButton(_L("Cursor details##sbar0"),settings.statusDisplay==0)) {
          settings.statusDisplay=0;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("File path##sbar1"),settings.statusDisplay==1)) {
          settings.statusDisplay=1;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Cursor details or file path##sbar2"),settings.statusDisplay==2)) {
          settings.statusDisplay=2;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Nothing##sbar3"),settings.statusDisplay==3)) {
          settings.statusDisplay=3;
          settingsChanged=true;
        }
        ImGui::Unindent();

        ImGui::Text(_L("Export options layout:##sgse"));
        ImGui::Indent();
        if (ImGui::RadioButton(_L("Sub-menus in File menu##eol0"),settings.exportOptionsLayout==0)) {
          settings.exportOptionsLayout=0;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Modal window with tabs##eol1"),settings.exportOptionsLayout==1)) {
          settings.exportOptionsLayout=1;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Modal windows with options in File menu##eol2"),settings.exportOptionsLayout==2)) {
          settings.exportOptionsLayout=2;
          settingsChanged=true;
        }
        ImGui::Unindent();

        bool capitalMenuBarB=settings.capitalMenuBar;
        if (ImGui::Checkbox(_L("Capitalize menu bar##sgse"),&capitalMenuBarB)) {
          settings.capitalMenuBar=capitalMenuBarB;
          settingsChanged=true;
        }

        bool classicChipOptionsB=settings.classicChipOptions;
        if (ImGui::Checkbox(_L("Display add/configure/change/remove chip menus in File menu##sgse"),&classicChipOptionsB)) {
          settings.classicChipOptions=classicChipOptionsB;
          settingsChanged=true;
        }

        // SUBSECTION ORDERS
        CONFIG_SUBSECTION(_L("Orders##sgse1"));
        // sorry. temporarily disabled until ImGui has a way to add separators in tables arbitrarily.
        /*bool sysSeparatorsB=settings.sysSeparators;
        if (ImGui::Checkbox("Add separators between systems in Orders",&sysSeparatorsB)) {
          settings.sysSeparators=sysSeparatorsB;
        }*/

        bool ordersCursorB=settings.ordersCursor;
        if (ImGui::Checkbox(_L("Highlight channel at cursor in Orders##sgse"),&ordersCursorB)) {
          settings.ordersCursor=ordersCursorB;
          settingsChanged=true;
        }

        ImGui::Text(_L("Orders row number format:##sgse"));
        ImGui::Indent();
        if (ImGui::RadioButton(_L("Decimal##orbD"),settings.orderRowsBase==0)) {
          settings.orderRowsBase=0;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Hexadecimal##orbH"),settings.orderRowsBase==1)) {
          settings.orderRowsBase=1;
          settingsChanged=true;
        }
        ImGui::Unindent();

        // SUBSECTION PATTERN
        CONFIG_SUBSECTION(_L("Pattern##sgse1"));
        bool centerPatternB=settings.centerPattern;
        if (ImGui::Checkbox(_L("Center pattern view##sgse"),&centerPatternB)) {
          settings.centerPattern=centerPatternB;
          settingsChanged=true;
        }

        bool overflowHighlightB=settings.overflowHighlight;
        if (ImGui::Checkbox(_L("Overflow pattern highlights##sgse"),&overflowHighlightB)) {
          settings.overflowHighlight=overflowHighlightB;
          settingsChanged=true;
        }

        bool viewPrevPatternB=settings.viewPrevPattern;
        if (ImGui::Checkbox(_L("Display previous/next pattern##sgse"),&viewPrevPatternB)) {
          settings.viewPrevPattern=viewPrevPatternB;
          settingsChanged=true;
        }

        ImGui::Text(_L("Pattern row number format:##sgse"));
        ImGui::Indent();
        if (ImGui::RadioButton(_L("Decimal##prbD"),settings.patRowsBase==0)) {
          settings.patRowsBase=0;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Hexadecimal##prbH"),settings.patRowsBase==1)) {
          settings.patRowsBase=1;
          settingsChanged=true;
        }
        ImGui::Unindent();

        ImGui::Text(_L("Pattern view labels:##sgse"));
        ImGui::PushFont(patFont);
        if (ImGui::InputTextWithHint("##PVLOff","OFF",&settings.noteOffLabel)) settingsChanged=true;
        ImGui::PopFont();
        ImGui::SameLine();
        ImGui::Text(_L("Note off (3-char)##sgse"));
        ImGui::PushFont(patFont);
        if (ImGui::InputTextWithHint("##PVLRel","===",&settings.noteRelLabel)) settingsChanged=true;
        ImGui::PopFont();
        ImGui::SameLine();
        ImGui::Text(_L("Note release (3-char)##sgse"));
        ImGui::PushFont(patFont);
        if (ImGui::InputTextWithHint("##PVLMacroRel","REL",&settings.macroRelLabel)) settingsChanged=true;
        ImGui::PopFont();
        ImGui::SameLine();
        ImGui::Text(_L("Macro release (3-char)##sgse"));
        ImGui::PushFont(patFont);
        if (ImGui::InputTextWithHint("##PVLE3","...",&settings.emptyLabel)) settingsChanged=true;
        ImGui::PopFont();
        ImGui::SameLine();
        ImGui::Text(_L("Empty field (3-char)##sgse"));
        ImGui::PushFont(patFont);
        if (ImGui::InputTextWithHint("##PVLE2","..",&settings.emptyLabel2)) settingsChanged=true;
        ImGui::PopFont();
        ImGui::SameLine();
        ImGui::Text(_L("Empty field (2-char)##sgse"));

        ImGui::Text(_L("Pattern view spacing after:##sgse"));

        if (CWSliderInt(_L("Note##sgse"),&settings.noteCellSpacing,0,32)) {
          if (settings.noteCellSpacing<0) settings.noteCellSpacing=0;
          if (settings.noteCellSpacing>32) settings.noteCellSpacing=32;
          settingsChanged=true;
        }

        if (CWSliderInt(_L("Instrument##sgse1"),&settings.insCellSpacing,0,32)) {
          if (settings.insCellSpacing<0) settings.insCellSpacing=0;
          if (settings.insCellSpacing>32) settings.insCellSpacing=32;
          settingsChanged=true;
        }

        if (CWSliderInt(_L("Volume##sgse4"),&settings.volCellSpacing,0,32)) {
          if (settings.volCellSpacing<0) settings.volCellSpacing=0;
          if (settings.volCellSpacing>32) settings.volCellSpacing=32;
          settingsChanged=true;
        }

        if (CWSliderInt(_L("Effect##sgse"),&settings.effectCellSpacing,0,32)) {
          if (settings.effectCellSpacing<0) settings.effectCellSpacing=0;
          if (settings.effectCellSpacing>32) settings.effectCellSpacing=32;
          settingsChanged=true;
        }

        if (CWSliderInt(_L("Effect value##sgse"),&settings.effectValCellSpacing,0,32)) {
          if (settings.effectValCellSpacing<0) settings.effectValCellSpacing=0;
          if (settings.effectValCellSpacing>32) settings.effectValCellSpacing=32;
          settingsChanged=true;
        }

        bool oneDigitEffectsB=settings.oneDigitEffects;
        if (ImGui::Checkbox(_L("Single-digit effects for 00-0F##sgse"),&oneDigitEffectsB)) {
          settings.oneDigitEffects=oneDigitEffectsB;
          settingsChanged=true;
        }

        bool flatNotesB=settings.flatNotes;
        if (ImGui::Checkbox(_L("Use flats instead of sharps##sgse"),&flatNotesB)) {
          settings.flatNotes=flatNotesB;
          settingsChanged=true;
        }

        bool germanNotationB=settings.germanNotation;
        if (ImGui::Checkbox(_L("Use German notation##sgse"),&germanNotationB)) {
          settings.germanNotation=germanNotationB;
          settingsChanged=true;
        }

        // SUBSECTION CHANNEL
        CONFIG_SUBSECTION(_L("Channel##sgse1"));

        ImGui::Text(_L("Channel style:##sgse"));
        ImGui::Indent();
        if (ImGui::RadioButton(_L("Classic##CHS0"),settings.channelStyle==0)) {
          settings.channelStyle=0;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Line##CHS1"),settings.channelStyle==1)) {
          settings.channelStyle=1;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Round##CHS2"),settings.channelStyle==2)) {
          settings.channelStyle=2;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Split button##CHS3"),settings.channelStyle==3)) {
          settings.channelStyle=3;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Square border##CHS4"),settings.channelStyle==4)) {
          settings.channelStyle=4;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Round border##CHS5"),settings.channelStyle==5)) {
          settings.channelStyle=5;
          settingsChanged=true;
        }
        ImGui::Unindent();

        ImGui::Text(_L("Channel volume bar:##sgse"));
        ImGui::Indent();
        if (ImGui::RadioButton(_L("Non##CHV0"),settings.channelVolStyle==0)) {
          settings.channelVolStyle=0;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Simple##CHV1"),settings.channelVolStyle==1)) {
          settings.channelVolStyle=1;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Stereo##CHV2"),settings.channelVolStyle==2)) {
          settings.channelVolStyle=2;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Real##CHV3"),settings.channelVolStyle==3)) {
          settings.channelVolStyle=3;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Real (stereo)##CHV4"),settings.channelVolStyle==4)) {
          settings.channelVolStyle=4;
          settingsChanged=true;
        }
        ImGui::Unindent();

        ImGui::Text(_L("Channel feedback style:##sgse"));
        ImGui::Indent();
        if (ImGui::RadioButton(_L("Off##CHF0"),settings.channelFeedbackStyle==0)) {
          settings.channelFeedbackStyle=0;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Note##CHF1"),settings.channelFeedbackStyle==1)) {
          settings.channelFeedbackStyle=1;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Volume##CHF2"),settings.channelFeedbackStyle==2)) {
          settings.channelFeedbackStyle=2;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Active##CHF3"),settings.channelFeedbackStyle==3)) {
          settings.channelFeedbackStyle=3;
          settingsChanged=true;
        }
        ImGui::Unindent();

        ImGui::Text(_L("Channel font:##sgse"));
        ImGui::Indent();
        if (ImGui::RadioButton(_L("Regular##CHFont0"),settings.channelFont==0)) {
          settings.channelFont=0;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Monospace##CHFont1"),settings.channelFont==1)) {
          settings.channelFont=1;
          settingsChanged=true;
        }
        ImGui::Unindent();

        bool channelTextCenterB=settings.channelTextCenter;
        if (ImGui::Checkbox(_L("Center channel name##sgse"),&channelTextCenterB)) {
          settings.channelTextCenter=channelTextCenterB;
          settingsChanged=true;
        }

        ImGui::Text(_L("Channel colors:##sgse"));
        ImGui::Indent();
        if (ImGui::RadioButton(_L("Single##CHC0"),settings.channelColors==0)) {
          settings.channelColors=0;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Channel type##CHC1"),settings.channelColors==1)) {
          settings.channelColors=1;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Instrument type##CHC2"),settings.channelColors==2)) {
          settings.channelColors=2;
          settingsChanged=true;
        }
        ImGui::Unindent();

        ImGui::Text(_L("Channel name colors:##sgse"));
        ImGui::Indent();
        if (ImGui::RadioButton(_L("Single##CTC0"),settings.channelTextColors==0)) {
          settings.channelTextColors=0;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Channel type##CTC1"),settings.channelTextColors==1)) {
          settings.channelTextColors=1;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Instrument type##CTC2"),settings.channelTextColors==2)) {
          settings.channelTextColors=2;
          settingsChanged=true;
        }
        ImGui::Unindent();

        // SUBSECTION ASSETS
        CONFIG_SUBSECTION(_L("Assets##sgse1"));
        bool unifiedDataViewB=settings.unifiedDataView;
        if (ImGui::Checkbox(_L("Unified instrument/wavetable/sample list##sgse"),&unifiedDataViewB)) {
          settings.unifiedDataView=unifiedDataViewB;
          settingsChanged=true;
        }
        if (settings.unifiedDataView) {
          settings.horizontalDataView=0;
        }

        ImGui::BeginDisabled(settings.unifiedDataView);
        bool horizontalDataViewB=settings.horizontalDataView;
        if (ImGui::Checkbox(_L("Horizontal instrument list##sgse"),&horizontalDataViewB)) {
          settings.horizontalDataView=horizontalDataViewB;
          settingsChanged=true;
        }
        ImGui::EndDisabled();

        ImGui::Text(_L("Instrument list icon style:##sgse"));
        ImGui::Indent();
        if (ImGui::RadioButton(_L("None##iis0"),settings.insIconsStyle==0)) {
          settings.insIconsStyle=0;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Graphical icons##iis1"),settings.insIconsStyle==1)) {
          settings.insIconsStyle=1;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Letter icons##iis2"),settings.insIconsStyle==2)) {
          settings.insIconsStyle=2;
          settingsChanged=true;
        }
        ImGui::Unindent();

        bool insEditColorizeB=settings.insEditColorize;
        if (ImGui::Checkbox(_L("Colorize instrument editor using instrument type##sgse"),&insEditColorizeB)) {
          settings.insEditColorize=insEditColorizeB;
          settingsChanged=true;
        }

        // SUBSECTION MACRO EDITOR
        CONFIG_SUBSECTION(_L("Macro Editor##sgse0"));
        ImGui::Text(_L("Macro editor layout:##sgse"));
        ImGui::Indent();
        if (ImGui::RadioButton(_L("Unified##mel0"),settings.macroLayout==0)) {
          settings.macroLayout=0;
          settingsChanged=true;
        }
        /*
        if (ImGui::RadioButton("Tabs##mel1",settings.macroLayout==1)) {
          settings.macroLayout=1;
          settingsChanged=true;
        }
        */
        if (ImGui::RadioButton(_L("Grid##mel2"),settings.macroLayout==2)) {
          settings.macroLayout=2;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Single (with list)##mel3"),settings.macroLayout==3)) {
          settings.macroLayout=3;
          settingsChanged=true;
        }
        /*
        if (ImGui::RadioButton("Single (combo box)##mel4",settings.macroLayout==4)) {
          settings.macroLayout=4;
          settingsChanged=true;
        }
        */
        ImGui::Unindent();

        bool oldMacroVSliderB=settings.oldMacroVSlider;
        if (ImGui::Checkbox(_L("Use classic macro editor vertical slider##sgse"),&oldMacroVSliderB)) {
          settings.oldMacroVSlider=oldMacroVSliderB;
          settingsChanged=true;
        }

        // SUBSECTION WAVE EDITOR
        CONFIG_SUBSECTION(_L("Wave Editor##sgse"));
        bool waveLayoutB=settings.waveLayout;
        if (ImGui::Checkbox(_L("Use compact wave editor##sgse"),&waveLayoutB)) {
          settings.waveLayout=waveLayoutB;
          settingsChanged=true;
        }

        // SUBSECTION FM EDITOR
        CONFIG_SUBSECTION(_L("FM Editor##sgse0"));
        ImGui::Text(_L("FM parameter names:##sgse"));
        ImGui::Indent();
        if (ImGui::RadioButton(_L("Friendly##fmn0"),settings.fmNames==0)) {
          settings.fmNames=0;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Technical##fmn1"),settings.fmNames==1)) {
          settings.fmNames=1;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Technical (alternate)##fmn2"),settings.fmNames==2)) {
          settings.fmNames=2;
          settingsChanged=true;
        }
        ImGui::Unindent();

        bool oplStandardWaveNamesB=settings.oplStandardWaveNames;
        if (ImGui::Checkbox(_L("Use standard OPL waveform names##sgse"),&oplStandardWaveNamesB)) {
          settings.oplStandardWaveNames=oplStandardWaveNamesB;
          settingsChanged=true;
        }

        ImGui::Text(_L("FM parameter editor layout:##sgse"));
        ImGui::Indent();
        if (ImGui::RadioButton(_L("Modern##fml0"),settings.fmLayout==0)) {
          settings.fmLayout=0;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Compact (2x2, classic)##fml1"),settings.fmLayout==1)) {
          settings.fmLayout=1;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Compact (1x4)##fml2"),settings.fmLayout==2)) {
          settings.fmLayout=2;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Compact (4x1)##fml3"),settings.fmLayout==3)) {
          settings.fmLayout=3;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Alternate (2x2)##fml4"),settings.fmLayout==4)) {
          settings.fmLayout=4;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Alternate (1x4)##fml5"),settings.fmLayout==5)) {
          settings.fmLayout=5;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Alternate (4x1)##fml6"),settings.fmLayout==6)) {
          settings.fmLayout=6;
          settingsChanged=true;
        }
        ImGui::Unindent();

        ImGui::Text(_L("Position of Sustain in FM editor:##sgse"));
        ImGui::Indent();
        if (ImGui::RadioButton(_L("Between Decay and Sustain Rate##susp0"),settings.susPosition==0)) {
          settings.susPosition=0;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("After Release Rate##susp1"),settings.susPosition==1)) {
          settings.susPosition=1;
          settingsChanged=true;
        }
        ImGui::Unindent();

        bool separateFMColorsB=settings.separateFMColors;
        if (ImGui::Checkbox(_L("Use separate colors for carriers/modulators in FM editor##sgse"),&separateFMColorsB)) {
          settings.separateFMColors=separateFMColorsB;
          settingsChanged=true;
        }

        bool unsignedDetuneB=settings.unsignedDetune;
        if (ImGui::Checkbox(_L("Unsigned FM detune values##sgse"),&unsignedDetuneB)) {
          settings.unsignedDetune=unsignedDetuneB;
          settingsChanged=true;
        }

        // SUBSECTION STATISTICS
        CONFIG_SUBSECTION(_L("Statistics##sgse"));
        ImGui::Text(_L("Chip memory usage unit:##sgse"));
        ImGui::Indent();
        if (ImGui::RadioButton(_L("Bytes##MUU0"),settings.memUsageUnit==0)) {
          settings.memUsageUnit=0;
          settingsChanged=true;
        }
        if (ImGui::RadioButton(_L("Kilobytes##MUU1"),settings.memUsageUnit==1)) {
          settings.memUsageUnit=1;
          settingsChanged=true;
        }
        ImGui::Unindent();

        // SUBSECTION OSCILLOSCOPE
        CONFIG_SUBSECTION(_L("Oscilloscope##set"));
        bool oscRoundedCornersB=settings.oscRoundedCorners;
        if (ImGui::Checkbox(_L("Rounded corners##sgse"),&oscRoundedCornersB)) {
          settings.oscRoundedCorners=oscRoundedCornersB;
          settingsChanged=true;
        }

        bool oscBorderB=settings.oscBorder;
        if (ImGui::Checkbox(_L("Border##sgse"),&oscBorderB)) {
          settings.oscBorder=oscBorderB;
          settingsChanged=true;
        }

        bool oscMonoB=settings.oscMono;
        if (ImGui::Checkbox(_L("Mono##sgse1"),&oscMonoB)) {
          settings.oscMono=oscMonoB;
          settingsChanged=true;
        }

        bool oscAntiAliasB=settings.oscAntiAlias;
        if (ImGui::Checkbox(_L("Anti-aliased##sgse"),&oscAntiAliasB)) {
          settings.oscAntiAlias=oscAntiAliasB;
          settingsChanged=true;
        }

        bool oscTakesEntireWindowB=settings.oscTakesEntireWindow;
        if (ImGui::Checkbox(_L("Fill entire window##sgse"),&oscTakesEntireWindowB)) {
          settings.oscTakesEntireWindow=oscTakesEntireWindowB;
          settingsChanged=true;
        }

        bool oscEscapesBoundaryB=settings.oscEscapesBoundary;
        if (ImGui::Checkbox(_L("Waveform goes out of bounds##sgse"),&oscEscapesBoundaryB)) {
          settings.oscEscapesBoundary=oscEscapesBoundaryB;
          settingsChanged=true;
        }

        // SUBSECTION WINDOWS
        CONFIG_SUBSECTION(_L("Windows##sgse"));
        bool roundedWindowsB=settings.roundedWindows;
        if (ImGui::Checkbox(_L("Rounded window corners##sgse"),&roundedWindowsB)) {
          settings.roundedWindows=roundedWindowsB;
          settingsChanged=true;
        }

        bool roundedButtonsB=settings.roundedButtons;
        if (ImGui::Checkbox(_L("Rounded buttons##sgse"),&roundedButtonsB)) {
          settings.roundedButtons=roundedButtonsB;
          settingsChanged=true;
        }

        bool roundedTabsB=settings.roundedTabs;
        if (ImGui::Checkbox(_L("Rounded tabs##sgse"),&roundedTabsB)) {
          settings.roundedTabs=roundedTabsB;
          settingsChanged=true;
        }

        bool roundedScrollbarsB=settings.roundedScrollbars;
        if (ImGui::Checkbox(_L("Rounded scrollbars##sgse"),&roundedScrollbarsB)) {
          settings.roundedScrollbars=roundedScrollbarsB;
          settingsChanged=true;
        }

        bool roundedMenusB=settings.roundedMenus;
        if (ImGui::Checkbox(_L("Rounded menu corners##sgse"),&roundedMenusB)) {
          settings.roundedMenus=roundedMenusB;
          settingsChanged=true;
        }

        bool frameBordersB=settings.frameBorders;
        if (ImGui::Checkbox(_L("Borders around widgets##sgse"),&frameBordersB)) {
          settings.frameBorders=frameBordersB;
          settingsChanged=true;
        }

        // SUBSECTION MISC
        CONFIG_SUBSECTION(_L("Misc##sgse"));
        bool wrapTextB=settings.wrapText;
        if (ImGui::Checkbox(_L("Wrap text##sgse"),&wrapTextB)) {
          settings.wrapText=wrapTextB;
          settingsChanged=true;
        }
        if (ImGui::IsItemHovered()) {
          ImGui::SetTooltip(_L("Wrap text in song/subsong comments window.##sgse"));
        }

        bool doFrameShadingForMultilineTextB=settings.doFrameShadingForMultilineText;
        if (ImGui::Checkbox(_L("Frame shading in text windows##sgse"),&doFrameShadingForMultilineTextB)) {
          settings.doFrameShadingForMultilineText=doFrameShadingForMultilineTextB;
          settingsChanged=true;
        }
        if (ImGui::IsItemHovered()) {
          ImGui::SetTooltip(_L("Apply frame shading to the multiline text fields\nsuch as song/subsong info/comments.##sgse"));
        }

        END_SECTION;
      }

CONFIG_SECTION(_L("Color##sgse")) {
  // SUBSECTION COLOR SCHEME
  CONFIG_SUBSECTION(_L("Color scheme##sgse"));
  if (ImGui::Button(_L("Import##sgse2"))) {
    openFileDialog(GUI_FILE_IMPORT_COLORS);
  }
  ImGui::SameLine();
  if (ImGui::Button(_L("Export##sgse2"))) {
    openFileDialog(GUI_FILE_EXPORT_COLORS);
  }
  ImGui::SameLine();
  if (ImGui::Button(_L("Reset defaults##sgse1"))) {
    showWarning(_L("Are you sure you want to reset the color scheme?##sgse"),GUI_WARN_RESET_COLORS);
  }
  if (ImGui::TreeNode(_L("Interface##sgse1"))) {
    if (ImGui::SliderInt(_L("Frame shading##sgse"),&settings.guiColorsShading,0,100,"%d%%##sgse")) {
      if (settings.guiColorsShading<0) settings.guiColorsShading=0;
      if (settings.guiColorsShading>100) settings.guiColorsShading=100;
      applyUISettings(false);
      settingsChanged=true;
    }

    UI_COLOR_CONFIG(GUI_COLOR_BUTTON,"Button");
    UI_COLOR_CONFIG(GUI_COLOR_BUTTON_HOVER,"Button (hovered)");
    UI_COLOR_CONFIG(GUI_COLOR_BUTTON_ACTIVE,"Button (active)");
    UI_COLOR_CONFIG(GUI_COLOR_TAB,"Tab");
    UI_COLOR_CONFIG(GUI_COLOR_TAB_HOVER,"Tab (hovered)");
    UI_COLOR_CONFIG(GUI_COLOR_TAB_ACTIVE,"Tab (active)");
    UI_COLOR_CONFIG(GUI_COLOR_TAB_UNFOCUSED,"Tab (unfocused)");
    UI_COLOR_CONFIG(GUI_COLOR_TAB_UNFOCUSED_ACTIVE,"Tab (unfocused and active)");
    UI_COLOR_CONFIG(GUI_COLOR_IMGUI_HEADER,"ImGui header");
    UI_COLOR_CONFIG(GUI_COLOR_IMGUI_HEADER_HOVER,"ImGui header (hovered)");
    UI_COLOR_CONFIG(GUI_COLOR_IMGUI_HEADER_ACTIVE,"ImGui header (active)");
    UI_COLOR_CONFIG(GUI_COLOR_RESIZE_GRIP,"Resize grip");
    UI_COLOR_CONFIG(GUI_COLOR_RESIZE_GRIP_HOVER,"Resize grip (hovered)");
    UI_COLOR_CONFIG(GUI_COLOR_RESIZE_GRIP_ACTIVE,"Resize grip (active)");
    UI_COLOR_CONFIG(GUI_COLOR_WIDGET_BACKGROUND,"Widget background");
    UI_COLOR_CONFIG(GUI_COLOR_WIDGET_BACKGROUND_HOVER,"Widget background (hovered)");
    UI_COLOR_CONFIG(GUI_COLOR_WIDGET_BACKGROUND_ACTIVE,"Widget background (active)");
    UI_COLOR_CONFIG(GUI_COLOR_SLIDER_GRAB,"Slider grab");
    UI_COLOR_CONFIG(GUI_COLOR_SLIDER_GRAB_ACTIVE,"Slider grab (active)");
    UI_COLOR_CONFIG(GUI_COLOR_TITLE_BACKGROUND_ACTIVE,"Title background (active)");
    UI_COLOR_CONFIG(GUI_COLOR_CHECK_MARK,"Checkbox/radio button mark");
    UI_COLOR_CONFIG(GUI_COLOR_TEXT_SELECTION,"Text selection");
    UI_COLOR_CONFIG(GUI_COLOR_PLOT_LINES,"Line plot");
    UI_COLOR_CONFIG(GUI_COLOR_PLOT_LINES_HOVER,"Line plot (hovered)");
    UI_COLOR_CONFIG(GUI_COLOR_PLOT_HISTOGRAM,"Histogram plot");
    UI_COLOR_CONFIG(GUI_COLOR_PLOT_HISTOGRAM_HOVER,"Histogram plot (hovered)");
    UI_COLOR_CONFIG(GUI_COLOR_TABLE_ROW_EVEN,"Table row (even)");
    UI_COLOR_CONFIG(GUI_COLOR_TABLE_ROW_ODD,"Table row (odd)");

    ImGui::TreePop();
  }
  if (ImGui::TreeNode(_L("Interface (other)##sgse"))) {
    UI_COLOR_CONFIG(GUI_COLOR_BACKGROUND,"Background");
    UI_COLOR_CONFIG(GUI_COLOR_FRAME_BACKGROUND,"Window background");
    UI_COLOR_CONFIG(GUI_COLOR_FRAME_BACKGROUND_CHILD,"Sub-window background");
    UI_COLOR_CONFIG(GUI_COLOR_FRAME_BACKGROUND_POPUP,"Pop-up background");
    UI_COLOR_CONFIG(GUI_COLOR_MODAL_BACKDROP,"Modal backdrop");
    UI_COLOR_CONFIG(GUI_COLOR_HEADER,"Header");
    UI_COLOR_CONFIG(GUI_COLOR_TEXT,"Text");
    UI_COLOR_CONFIG(GUI_COLOR_TEXT_DISABLED,"Text (disabled)");
    UI_COLOR_CONFIG(GUI_COLOR_TITLE_INACTIVE,"Title bar (inactive)");
    UI_COLOR_CONFIG(GUI_COLOR_TITLE_COLLAPSED,"Title bar (collapsed)");
    UI_COLOR_CONFIG(GUI_COLOR_MENU_BAR,"Menu bar");
    UI_COLOR_CONFIG(GUI_COLOR_BORDER,"Border");
    UI_COLOR_CONFIG(GUI_COLOR_BORDER_SHADOW,"Border shadow");
    UI_COLOR_CONFIG(GUI_COLOR_SCROLL,"Scroll bar");
    UI_COLOR_CONFIG(GUI_COLOR_SCROLL_HOVER,"Scroll bar (hovered)");
    UI_COLOR_CONFIG(GUI_COLOR_SCROLL_ACTIVE,"Scroll bar (clicked)");
    UI_COLOR_CONFIG(GUI_COLOR_SCROLL_BACKGROUND,"Scroll bar background");
    UI_COLOR_CONFIG(GUI_COLOR_SEPARATOR,"Separator");
    UI_COLOR_CONFIG(GUI_COLOR_SEPARATOR_HOVER,"Separator (hover)");
    UI_COLOR_CONFIG(GUI_COLOR_SEPARATOR_ACTIVE,"Separator (active)");
    UI_COLOR_CONFIG(GUI_COLOR_DOCKING_PREVIEW,"Docking preview");
    UI_COLOR_CONFIG(GUI_COLOR_DOCKING_EMPTY,"Docking empty");
    UI_COLOR_CONFIG(GUI_COLOR_TABLE_HEADER,"Table header");
    UI_COLOR_CONFIG(GUI_COLOR_TABLE_BORDER_HARD,"Table border (hard)");
    UI_COLOR_CONFIG(GUI_COLOR_TABLE_BORDER_SOFT,"Table border (soft)");
    UI_COLOR_CONFIG(GUI_COLOR_DRAG_DROP_TARGET,"Drag and drop target");
    UI_COLOR_CONFIG(GUI_COLOR_NAV_WIN_HIGHLIGHT,"Window switcher (highlight)");
    UI_COLOR_CONFIG(GUI_COLOR_NAV_WIN_BACKDROP,"Window switcher backdrop");
    ImGui::TreePop();
  }
  if (ImGui::TreeNode(_L("Miscellaneous##sgse"))) {
    UI_COLOR_CONFIG(GUI_COLOR_TOGGLE_ON,"Toggle on");
    UI_COLOR_CONFIG(GUI_COLOR_TOGGLE_OFF,"Toggle off");
    UI_COLOR_CONFIG(GUI_COLOR_PLAYBACK_STAT,"Playback status");
    UI_COLOR_CONFIG(GUI_COLOR_DESTRUCTIVE,"Destructive hint");
    UI_COLOR_CONFIG(GUI_COLOR_WARNING,"Warning hint");
    UI_COLOR_CONFIG(GUI_COLOR_ERROR,"Error hint");
    ImGui::TreePop();
  }
  if (ImGui::TreeNode(_L("File Picker (built-in)##sgse"))) {
    UI_COLOR_CONFIG(GUI_COLOR_FILE_DIR,"Directory");
    UI_COLOR_CONFIG(GUI_COLOR_FILE_SONG_NATIVE,"Song (native)");
    UI_COLOR_CONFIG(GUI_COLOR_FILE_SONG_IMPORT,"Song (import)");
    UI_COLOR_CONFIG(GUI_COLOR_FILE_INSTR,"Instrument");
    UI_COLOR_CONFIG(GUI_COLOR_FILE_AUDIO,"Audio");
    UI_COLOR_CONFIG(GUI_COLOR_FILE_WAVE,"Wavetable");
    UI_COLOR_CONFIG(GUI_COLOR_FILE_VGM,"VGM");
    UI_COLOR_CONFIG(GUI_COLOR_FILE_ZSM,"ZSM");
    UI_COLOR_CONFIG(GUI_COLOR_FILE_FONT,"Font");
    UI_COLOR_CONFIG(GUI_COLOR_FILE_OTHER,"Other");
    ImGui::TreePop();
  }
  if (ImGui::TreeNode(_L("Oscilloscope##sgse"))) {
    UI_COLOR_CONFIG(GUI_COLOR_OSC_BORDER,"Border");
    UI_COLOR_CONFIG(GUI_COLOR_OSC_BG1,"Background (top-left)");
    UI_COLOR_CONFIG(GUI_COLOR_OSC_BG2,"Background (top-right)");
    UI_COLOR_CONFIG(GUI_COLOR_OSC_BG3,"Background (bottom-left)");
    UI_COLOR_CONFIG(GUI_COLOR_OSC_BG4,"Background (bottom-right)");
    UI_COLOR_CONFIG(GUI_COLOR_OSC_WAVE,"Waveform");
    UI_COLOR_CONFIG(GUI_COLOR_OSC_WAVE_PEAK,"Waveform (clip)");
    UI_COLOR_CONFIG(GUI_COLOR_OSC_REF,"Reference");
    UI_COLOR_CONFIG(GUI_COLOR_OSC_GUIDE,"Guide");

    if (ImGui::TreeNode(_L("Wave (non-mono)##sgse"))) {
      UI_COLOR_CONFIG(GUI_COLOR_OSC_WAVE_CH0,"Waveform (1)");
      UI_COLOR_CONFIG(GUI_COLOR_OSC_WAVE_CH1,"Waveform (2)");
      UI_COLOR_CONFIG(GUI_COLOR_OSC_WAVE_CH2,"Waveform (3)");
      UI_COLOR_CONFIG(GUI_COLOR_OSC_WAVE_CH3,"Waveform (4)");
      UI_COLOR_CONFIG(GUI_COLOR_OSC_WAVE_CH4,"Waveform (5)");
      UI_COLOR_CONFIG(GUI_COLOR_OSC_WAVE_CH5,"Waveform (6)");
      UI_COLOR_CONFIG(GUI_COLOR_OSC_WAVE_CH6,"Waveform (7)");
      UI_COLOR_CONFIG(GUI_COLOR_OSC_WAVE_CH7,"Waveform (8)");
      UI_COLOR_CONFIG(GUI_COLOR_OSC_WAVE_CH8,"Waveform (9)");
      UI_COLOR_CONFIG(GUI_COLOR_OSC_WAVE_CH9,"Waveform (10)");
      UI_COLOR_CONFIG(GUI_COLOR_OSC_WAVE_CH10,"Waveform (11)");
      UI_COLOR_CONFIG(GUI_COLOR_OSC_WAVE_CH11,"Waveform (12)");
      UI_COLOR_CONFIG(GUI_COLOR_OSC_WAVE_CH12,"Waveform (13)");
      UI_COLOR_CONFIG(GUI_COLOR_OSC_WAVE_CH13,"Waveform (14)");
      UI_COLOR_CONFIG(GUI_COLOR_OSC_WAVE_CH14,"Waveform (15)");
      UI_COLOR_CONFIG(GUI_COLOR_OSC_WAVE_CH15,"Waveform (16)");
      ImGui::TreePop();
    }
    ImGui::TreePop();
  }
  if (ImGui::TreeNode(_L("Volume Meter##sgse"))) {
    UI_COLOR_CONFIG(GUI_COLOR_VOLMETER_LOW,"Low");
    UI_COLOR_CONFIG(GUI_COLOR_VOLMETER_HIGH,"High");
    UI_COLOR_CONFIG(GUI_COLOR_VOLMETER_PEAK,"Clip");
    ImGui::TreePop();
  }
  if (ImGui::TreeNode(_L("Orders##sgse2"))) {
    UI_COLOR_CONFIG(GUI_COLOR_ORDER_ROW_INDEX,"Order number");
    UI_COLOR_CONFIG(GUI_COLOR_ORDER_ACTIVE,"Playing order background");
    UI_COLOR_CONFIG(GUI_COLOR_SONG_LOOP,"Song loop");
    UI_COLOR_CONFIG(GUI_COLOR_ORDER_SELECTED,"Selected order");
    UI_COLOR_CONFIG(GUI_COLOR_ORDER_SIMILAR,"Similar patterns");
    UI_COLOR_CONFIG(GUI_COLOR_ORDER_INACTIVE,"Inactive patterns");
    ImGui::TreePop();
  }
  if (ImGui::TreeNode(_L("Envelope View##sgse"))) {
    UI_COLOR_CONFIG(GUI_COLOR_FM_ENVELOPE,"Envelope");
    UI_COLOR_CONFIG(GUI_COLOR_FM_ENVELOPE_SUS_GUIDE,"Sustain guide");
    UI_COLOR_CONFIG(GUI_COLOR_FM_ENVELOPE_RELEASE,"Release");

    ImGui::TreePop();
  }
  if (ImGui::TreeNode(_L("FM Editor##sgse1"))) {
    UI_COLOR_CONFIG(GUI_COLOR_FM_ALG_BG,"Algorithm background");
    UI_COLOR_CONFIG(GUI_COLOR_FM_ALG_LINE,"Algorithm lines");
    UI_COLOR_CONFIG(GUI_COLOR_FM_MOD,"Modulator");
    UI_COLOR_CONFIG(GUI_COLOR_FM_CAR,"Carrier");

    UI_COLOR_CONFIG(GUI_COLOR_FM_SSG,"SSG-EG");
    UI_COLOR_CONFIG(GUI_COLOR_FM_WAVE,"Waveform");

    ImGui::TextWrapped("(the following colors only apply when \"Use separate colors for carriers/modulators in FM editor\" is on!)");

    UI_COLOR_CONFIG(GUI_COLOR_FM_PRIMARY_MOD,"Mod. accent (primary)");
    UI_COLOR_CONFIG(GUI_COLOR_FM_SECONDARY_MOD,"Mod. accent (secondary)");
    UI_COLOR_CONFIG(GUI_COLOR_FM_BORDER_MOD,"Mod. border");
    UI_COLOR_CONFIG(GUI_COLOR_FM_BORDER_SHADOW_MOD,"Mod. border shadow");
    UI_COLOR_CONFIG(GUI_COLOR_FM_PRIMARY_CAR,"Car. accent (primary)");
    UI_COLOR_CONFIG(GUI_COLOR_FM_SECONDARY_CAR,"Car. accent (secondary)");
    UI_COLOR_CONFIG(GUI_COLOR_FM_BORDER_CAR,"Car. border");
    UI_COLOR_CONFIG(GUI_COLOR_FM_BORDER_SHADOW_CAR,"Car. border shadow");

    ImGui::TreePop();
  }
  if (ImGui::TreeNode(_L("Macro Editor##sgse1"))) {
    UI_COLOR_CONFIG(GUI_COLOR_MACRO_VOLUME,"Volume");
    UI_COLOR_CONFIG(GUI_COLOR_MACRO_PITCH,"Pitch");
    UI_COLOR_CONFIG(GUI_COLOR_MACRO_WAVE,"Wave");
    UI_COLOR_CONFIG(GUI_COLOR_MACRO_OTHER,"Other");
    ImGui::TreePop();
  }
  if (ImGui::TreeNode(_L("Instrument Types##sgse"))) {
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_FM,"FM (OPN)");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_STD,"SN76489/Sega PSG");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_T6W28,"T6W28");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_GB,"Game Boy");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_C64,"C64");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_AMIGA,"Amiga/Generic Sample");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_PCE,"PC Engine");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_AY,"AY-3-8910/SSG");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_AY8930,"AY8930");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_TIA,"TIA");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_SAA1099,"SAA1099");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_VIC,"VIC");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_PET,"PET");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_VRC6,"VRC6");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_VRC6_SAW,"VRC6 (saw)");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_OPLL,"FM (OPLL)");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_OPL,"FM (OPL)");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_FDS,"FDS");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_VBOY,"Virtual Boy");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_N163,"Namco 163");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_SCC,"Konami SCC");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_OPZ,"FM (OPZ)");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_POKEY,"POKEY");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_BEEPER,"PC Beeper");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_SWAN,"WonderSwan");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_MIKEY,"Lynx");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_VERA,"VERA");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_X1_010,"X1-010");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_ES5506,"ES5506");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_MULTIPCM,"MultiPCM");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_SNES,"SNES");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_SU,"Sound Unit");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_NAMCO,"Namco WSG");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_OPL_DRUMS,"FM (OPL Drums)");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_OPM,"FM (OPM)");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_NES,"NES");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_MSM6258,"MSM6258");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_MSM6295,"MSM6295");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_ADPCMA,"ADPCM-A");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_ADPCMB,"ADPCM-B");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_SEGAPCM,"Sega PCM");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_QSOUND,"QSound");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_YMZ280B,"YMZ280B");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_RF5C68,"RF5C68");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_MSM5232,"MSM5232");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_K007232,"K007232");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_GA20,"GA20");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_POKEMINI,"Pokémon Mini");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_SM8521,"SM8521");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_PV1000,"PV-1000");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_K053260,"K053260");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_C140,"C140");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_C219,"C219");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_ESFM,"ESFM");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_ES5503,"ES5503");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_POWERNOISE,"PowerNoise (noise)");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_POWERNOISE_SLOPE,"PowerNoise (slope)");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_DAVE,"DAVE");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_SID2,"SID2");
    UI_COLOR_CONFIG(GUI_COLOR_INSTR_UNKNOWN,"Other/Unknown");
    ImGui::TreePop();
  }
  if (ImGui::TreeNode(_L("Channel##sgse2"))) {
    UI_COLOR_CONFIG(GUI_COLOR_CHANNEL_BG,"Single color (background)");
    UI_COLOR_CONFIG(GUI_COLOR_CHANNEL_FG,"Single color (text)");
    UI_COLOR_CONFIG(GUI_COLOR_CHANNEL_FM,"FM");
    UI_COLOR_CONFIG(GUI_COLOR_CHANNEL_PULSE,"Pulse");
    UI_COLOR_CONFIG(GUI_COLOR_CHANNEL_NOISE,"Noise");
    UI_COLOR_CONFIG(GUI_COLOR_CHANNEL_PCM,"PCM");
    UI_COLOR_CONFIG(GUI_COLOR_CHANNEL_WAVE,"Wave");
    UI_COLOR_CONFIG(GUI_COLOR_CHANNEL_OP,"FM operator");
    UI_COLOR_CONFIG(GUI_COLOR_CHANNEL_MUTED,"Muted");
    ImGui::TreePop();
  }
  if (ImGui::TreeNode(_L("Pattern##sgse2"))) {
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_PLAY_HEAD,"Playhead");
    UI_COLOR_CONFIG(GUI_COLOR_EDITING,"Editing");
    UI_COLOR_CONFIG(GUI_COLOR_EDITING_CLONE,"Editing (will clone)");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_CURSOR,"Cursor");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_CURSOR_HOVER,"Cursor (hovered)");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_CURSOR_ACTIVE,"Cursor (clicked)");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_SELECTION,"Selection");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_SELECTION_HOVER,"Selection (hovered)");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_SELECTION_ACTIVE,"Selection (clicked)");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_HI_1,"Highlight 1");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_HI_2,"Highlight 2");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_ROW_INDEX,"Row number");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_ROW_INDEX_HI1,"Row number (highlight 1)");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_ROW_INDEX_HI2,"Row number (highlight 2)");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_ACTIVE,"Note");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_ACTIVE_HI1,"Note (highlight 1)");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_ACTIVE_HI2,"Note (highlight 2)");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_INACTIVE,"Blank");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_INACTIVE_HI1,"Blank (highlight 1)");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_INACTIVE_HI2,"Blank (highlight 2)");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_INS,"Instrument");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_INS_WARN,"Instrument (invalid type)");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_INS_ERROR,"Instrument (out of range)");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_VOLUME_MIN,"Volume (0%)");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_VOLUME_HALF,"Volume (50%)");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_VOLUME_MAX,"Volume (100%)");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_EFFECT_INVALID,"Invalid effect");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_EFFECT_PITCH,"Pitch effect");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_EFFECT_VOLUME,"Volume effect");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_EFFECT_PANNING,"Panning effect");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_EFFECT_SONG,"Song effect");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_EFFECT_TIME,"Time effect");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_EFFECT_SPEED,"Speed effect");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_EFFECT_SYS_PRIMARY,"Primary specific effect");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_EFFECT_SYS_SECONDARY,"Secondary specific effect");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_EFFECT_MISC,"Miscellaneous");
    UI_COLOR_CONFIG(GUI_COLOR_EE_VALUE,"External command output");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_STATUS_OFF,"Status: off/disabled");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_STATUS_REL,"Status: off + macro rel");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_STATUS_REL_ON,"Status: on + macro rel");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_STATUS_ON,"Status: on");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_STATUS_VOLUME,"Status: volume");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_STATUS_PITCH,"Status: pitch");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_STATUS_PANNING,"Status: panning");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_STATUS_SYS1,"Status: chip (primary)");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_STATUS_SYS2,"Status: chip (secondary)");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_STATUS_MIXING,"Status: mixing");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_STATUS_DSP,"Status: DSP effect");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_STATUS_NOTE,"Status: note altering");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_STATUS_MISC1,"Status: misc color 1");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_STATUS_MISC2,"Status: misc color 2");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_STATUS_MISC3,"Status: misc color 3");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_STATUS_ATTACK,"Status: attack");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_STATUS_DECAY,"Status: decay");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_STATUS_SUSTAIN,"Status: sustain");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_STATUS_RELEASE,"Status: release");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_STATUS_DEC_LINEAR,"Status: decrease linear");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_STATUS_DEC_EXP,"Status: decrease exp");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_STATUS_INC,"Status: increase");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_STATUS_BENT,"Status: bent");
    UI_COLOR_CONFIG(GUI_COLOR_PATTERN_STATUS_DIRECT,"Status: direct");
    ImGui::TreePop();
  }
  if (ImGui::TreeNode(_L("Sample Editor##sgse"))) {
    UI_COLOR_CONFIG(GUI_COLOR_SAMPLE_BG,"Background");
    UI_COLOR_CONFIG(GUI_COLOR_SAMPLE_FG,"Waveform");
    UI_COLOR_CONFIG(GUI_COLOR_SAMPLE_TIME_BG,"Time background");
    UI_COLOR_CONFIG(GUI_COLOR_SAMPLE_TIME_FG,"Time text");
    UI_COLOR_CONFIG(GUI_COLOR_SAMPLE_LOOP,"Loop region");
    UI_COLOR_CONFIG(GUI_COLOR_SAMPLE_CENTER,"Center guide");
    UI_COLOR_CONFIG(GUI_COLOR_SAMPLE_GRID,"Grid");
    UI_COLOR_CONFIG(GUI_COLOR_SAMPLE_SEL,"Selection");
    UI_COLOR_CONFIG(GUI_COLOR_SAMPLE_SEL_POINT,"Selection points");
    UI_COLOR_CONFIG(GUI_COLOR_SAMPLE_NEEDLE,"Preview needle");
    UI_COLOR_CONFIG(GUI_COLOR_SAMPLE_NEEDLE_PLAYING,"Playing needles");
    UI_COLOR_CONFIG(GUI_COLOR_SAMPLE_LOOP_POINT,"Loop markers");
    UI_COLOR_CONFIG(GUI_COLOR_SAMPLE_CHIP_DISABLED,"Chip select: disabled");
    UI_COLOR_CONFIG(GUI_COLOR_SAMPLE_CHIP_ENABLED,"Chip select: enabled");
    UI_COLOR_CONFIG(GUI_COLOR_SAMPLE_CHIP_WARNING,"Chip select: enabled (failure)");
    ImGui::TreePop();
  }
  if (ImGui::TreeNode(_L("Pattern Manager##sgse"))) {
    UI_COLOR_CONFIG(GUI_COLOR_PAT_MANAGER_NULL,"Unallocated");
    UI_COLOR_CONFIG(GUI_COLOR_PAT_MANAGER_UNUSED,"Unused");
    UI_COLOR_CONFIG(GUI_COLOR_PAT_MANAGER_USED,"Used");
    UI_COLOR_CONFIG(GUI_COLOR_PAT_MANAGER_OVERUSED,"Overused");
    UI_COLOR_CONFIG(GUI_COLOR_PAT_MANAGER_EXTREMELY_OVERUSED,"Really overused");
    UI_COLOR_CONFIG(GUI_COLOR_PAT_MANAGER_COMBO_BREAKER,"Combo Breaker");
    ImGui::TreePop();
  }
  if (ImGui::TreeNode(_L("Piano##sgse"))) {
    UI_COLOR_CONFIG(GUI_COLOR_PIANO_BACKGROUND,"Background");
    UI_COLOR_CONFIG(GUI_COLOR_PIANO_KEY_TOP,"Upper key");
    UI_COLOR_CONFIG(GUI_COLOR_PIANO_KEY_TOP_HIT,"Upper key (feedback)");
    UI_COLOR_CONFIG(GUI_COLOR_PIANO_KEY_TOP_ACTIVE,"Upper key (pressed)");
    UI_COLOR_CONFIG(GUI_COLOR_PIANO_KEY_BOTTOM,"Lower key");
    UI_COLOR_CONFIG(GUI_COLOR_PIANO_KEY_BOTTOM_HIT,"Lower key (feedback)");
    UI_COLOR_CONFIG(GUI_COLOR_PIANO_KEY_BOTTOM_ACTIVE,"Lower key (pressed)");
    ImGui::TreePop();
  }
  if (ImGui::TreeNode(_L("Clock##sgse"))) {
    UI_COLOR_CONFIG(GUI_COLOR_CLOCK_TEXT,"Clock text");
    UI_COLOR_CONFIG(GUI_COLOR_CLOCK_BEAT_LOW,"Beat (off)");
    UI_COLOR_CONFIG(GUI_COLOR_CLOCK_BEAT_HIGH,"Beat (on)");

    ImGui::TreePop();
  }
  if (ImGui::TreeNode(_L("Patchbay##sgse"))) {
    UI_COLOR_CONFIG(GUI_COLOR_PATCHBAY_PORTSET,"PortSet");
    UI_COLOR_CONFIG(GUI_COLOR_PATCHBAY_PORT,"Port");
    UI_COLOR_CONFIG(GUI_COLOR_PATCHBAY_PORT_HIDDEN,"Port (hidden/unavailable)");
    UI_COLOR_CONFIG(GUI_COLOR_PATCHBAY_CONNECTION,"Connection (selected)");
    UI_COLOR_CONFIG(GUI_COLOR_PATCHBAY_CONNECTION_BG,"Connection (other)");

    ImGui::TreePop();
  }
  if (ImGui::TreeNode(_L("Log Viewer##sgse"))) {
    UI_COLOR_CONFIG(GUI_COLOR_LOGLEVEL_ERROR,"Log level: Error");
    UI_COLOR_CONFIG(GUI_COLOR_LOGLEVEL_WARNING,"Log level: Warning");
    UI_COLOR_CONFIG(GUI_COLOR_LOGLEVEL_INFO,"Log level: Info");
    UI_COLOR_CONFIG(GUI_COLOR_LOGLEVEL_DEBUG,"Log level: Debug");
    UI_COLOR_CONFIG(GUI_COLOR_LOGLEVEL_TRACE,"Log level: Trace/Verbose");
    ImGui::TreePop();
  }
  END_SECTION;
}
      
      ImGui::EndTabBar();
    }
    ImGui::Separator();
    if (ImGui::Button(_L("OK##SettingsOK"))) {
      settingsOpen=false;
      willCommit=true;
      settingsChanged=false;
    }
    ImGui::SameLine();
    if (ImGui::Button(_L("Cancel##SettingsCancel"))) {
      settingsOpen=false;
      audioEngineChanged=false;
      syncSettings();
      settingsChanged=false;
    }
    ImGui::SameLine();
    ImGui::BeginDisabled(!settingsChanged);
    if (ImGui::Button(_L("Apply##SettingsApply"))) {
      settingsOpen=true;
      willCommit=true;
      settingsChanged=false;
    }
    ImGui::EndDisabled();
  }
  if (ImGui::IsWindowFocused(ImGuiFocusedFlags_ChildWindows)) curWindow=GUI_WINDOW_SETTINGS;
  ImGui::End();
}

#define clampSetting(x,minV,maxV) \
  if (x<minV) { \
    x=minV; \
  } \
  if (x>maxV) { \
    x=maxV; \
  }

void FurnaceGUI::readConfig(DivConfig& conf, FurnaceGUISettingGroups groups) {
  if (groups&GUI_SETTINGS_GENERAL) {
    settings.renderDriver=conf.getString("renderDriver","");
    settings.noDMFCompat=conf.getInt("noDMFCompat",0);

    settings.dpiScale=conf.getFloat("dpiScale",0.0f);

    settings.initialSysName=conf.getString("initialSysName","");

    // initial system
    String initialSys2=conf.getString("initialSys2","");
    bool oldVol=conf.getInt("configVersion",DIV_ENGINE_VERSION)<135;
    if (initialSys2.empty()) {
      initialSys2=e->decodeSysDesc(conf.getString("initialSys",""));
      oldVol=false;
    }
    settings.initialSys.clear();
    settings.initialSys.loadFromBase64(initialSys2.c_str());
    if (settings.initialSys.getInt("id0",0)==0) {
      settings.initialSys.clear();
      settings.initialSys.set("id0",e->systemToFileFur(DIV_SYSTEM_YM2612));
      settings.initialSys.set("vol0",1.0f);
      settings.initialSys.set("pan0",0.0f);
      settings.initialSys.set("fr0",0.0f);
      settings.initialSys.set("flags0","");
      settings.initialSys.set("id1",e->systemToFileFur(DIV_SYSTEM_SMS));
      settings.initialSys.set("vol1",0.5f);
      settings.initialSys.set("pan1",0);
      settings.initialSys.set("fr1",0);
      settings.initialSys.set("flags1","");
    } else {
      if (oldVol) {
        for (int i=0; settings.initialSys.getInt(fmt::sprintf("id%d",i),0); i++) {
          float newVol=settings.initialSys.getInt(fmt::sprintf("vol%d",i),64);
          float newPan=settings.initialSys.getInt(fmt::sprintf("pan%d",i),0);
          newVol/=64.0f;
          newPan/=127.0f;
          settings.initialSys.set(fmt::sprintf("vol%d",i),newVol);
          settings.initialSys.set(fmt::sprintf("pan%d",i),newPan);
        }
        conf.set("initialSys2",settings.initialSys.toBase64());
        conf.set("configVersion",DIV_ENGINE_VERSION);
      }
    }

    settings.noThreadedInput=conf.getInt("noThreadedInput",0);
    settings.powerSave=conf.getInt("powerSave",POWER_SAVE_DEFAULT);
    settings.eventDelay=conf.getInt("eventDelay",0);

    settings.renderBackend=conf.getString("renderBackend",GUI_BACKEND_DEFAULT_NAME);
    settings.renderClearPos=conf.getInt("renderClearPos",0);

    settings.chanOscThreads=conf.getInt("chanOscThreads",0);
    settings.renderPoolThreads=conf.getInt("renderPoolThreads",0);
    settings.showPool=conf.getInt("showPool",0);
    settings.writeInsNames=conf.getInt("writeInsNames",0);
    settings.readInsNames=conf.getInt("readInsNames",1);
    settings.defaultAuthorName=conf.getString("defaultAuthorName","");

    settings.hiddenSystems=conf.getInt("hiddenSystems",0);
    settings.allowEditDocking=conf.getInt("allowEditDocking",1);
    settings.sysFileDialog=conf.getInt("sysFileDialog",SYS_FILE_DIALOG_DEFAULT);
    settings.displayAllInsTypes=conf.getInt("displayAllInsTypes",0);
    settings.displayPartial=conf.getInt("displayPartial",0);

    settings.blankIns=conf.getInt("blankIns",0);

    settings.saveWindowPos=conf.getInt("saveWindowPos",1);

    settings.saveUnusedPatterns=conf.getInt("saveUnusedPatterns",0);
    settings.maxRecentFile=conf.getInt("maxRecentFile",10);

    settings.persistFadeOut=conf.getInt("persistFadeOut",1);
    settings.exportLoops=conf.getInt("exportLoops",0);
    settings.exportFadeOut=conf.getDouble("exportFadeOut",0.0);

    settings.doubleClickTime=conf.getFloat("doubleClickTime",0.3f);
    settings.disableFadeIn=conf.getInt("disableFadeIn",0);
    settings.iCannotWait=conf.getInt("iCannotWait",0);

    settings.compress=conf.getInt("compress",1);
    settings.newPatternFormat=conf.getInt("newPatternFormat",1);
    settings.newSongBehavior=conf.getInt("newSongBehavior",0);
    settings.playOnLoad=conf.getInt("playOnLoad",0);
    settings.centerPopup=conf.getInt("centerPopup",1);

    settings.language=conf.getInt("language",(int)DIV_LANG_ENGLISH);
    locale.setLanguage((DivLang)settings.language);
    initSystemPresets();
    updateWindowTitle();
  }

  if (groups&GUI_SETTINGS_AUDIO) {
    settings.audioEngine=(conf.getString("audioEngine","SDL")=="SDL")?1:0;
    if (conf.getString("audioEngine","SDL")=="JACK") {
      settings.audioEngine=DIV_AUDIO_JACK;
    } else if (conf.getString("audioEngine","SDL")=="PortAudio") {
      settings.audioEngine=DIV_AUDIO_PORTAUDIO;
    } else {
      settings.audioEngine=DIV_AUDIO_SDL;
    }
    settings.audioDevice=conf.getString("audioDevice","");
    settings.sdlAudioDriver=conf.getString("sdlAudioDriver","");
    settings.audioQuality=conf.getInt("audioQuality",0);
    settings.audioHiPass=conf.getInt("audioHiPass",1);
    settings.audioBufSize=conf.getInt("audioBufSize",1024);
    settings.audioRate=conf.getInt("audioRate",44100);
    settings.audioChans=conf.getInt("audioChans",2);

    settings.lowLatency=conf.getInt("lowLatency",0);

    settings.metroVol=conf.getInt("metroVol",100);
    settings.sampleVol=conf.getInt("sampleVol",50);

    settings.wasapiEx=conf.getInt("wasapiEx",0);

    settings.clampSamples=conf.getInt("clampSamples",0);
    settings.forceMono=conf.getInt("forceMono",0);
  }

  if (groups&GUI_SETTINGS_MIDI) {
    settings.midiInDevice=conf.getString("midiInDevice","");
    settings.midiOutDevice=conf.getString("midiOutDevice","");
    settings.midiOutClock=conf.getInt("midiOutClock",0);
    settings.midiOutTime=conf.getInt("midiOutTime",0);
    settings.midiOutProgramChange=conf.getInt("midiOutProgramChange",0);
    settings.midiOutMode=conf.getInt("midiOutMode",1);
    settings.midiOutTimeRate=conf.getInt("midiOutTimeRate",0);
  }

  if (groups&GUI_SETTINGS_KEYBOARD) {
    // keybinds
    for (int i=0; i<GUI_ACTION_MAX; i++) {
      if (guiActions[i].defaultBind==-1) continue; // not a bind
      actionKeys[i]=conf.getInt(String("keybind_GUI_ACTION_")+String(guiActions[i].name),guiActions[i].defaultBind);
    }

    decodeKeyMap(noteKeys,conf.getString("noteKeys",DEFAULT_NOTE_KEYS));
  }

  if (groups&GUI_SETTINGS_BEHAVIOR) {
    settings.soloAction=conf.getInt("soloAction",0);
    settings.pullDeleteBehavior=conf.getInt("pullDeleteBehavior",1);
    settings.wrapHorizontal=conf.getInt("wrapHorizontal",0);
    settings.wrapVertical=conf.getInt("wrapVertical",0);

    settings.stepOnDelete=conf.getInt("stepOnDelete",0);
    settings.scrollStep=conf.getInt("scrollStep",0);
    settings.avoidRaisingPattern=conf.getInt("avoidRaisingPattern",0);
    settings.insFocusesPattern=conf.getInt("insFocusesPattern",1);
    settings.stepOnInsert=conf.getInt("stepOnInsert",0);
    settings.effectCursorDir=conf.getInt("effectCursorDir",1);
    settings.cursorPastePos=conf.getInt("cursorPastePos",1);

    settings.effectDeletionAltersValue=conf.getInt("effectDeletionAltersValue",1);

    settings.pushNibble=conf.getInt("pushNibble",0);
    settings.scrollChangesOrder=conf.getInt("scrollChangesOrder",0);
    settings.cursorMoveNoScroll=conf.getInt("cursorMoveNoScroll",0);

    settings.notePreviewBehavior=conf.getInt("notePreviewBehavior",1);
    
    settings.absorbInsInput=conf.getInt("absorbInsInput",0);
    
    settings.moveWindowTitle=conf.getInt("moveWindowTitle",1);

    settings.doubleClickColumn=conf.getInt("doubleClickColumn",1);
    settings.dragMovesSelection=conf.getInt("dragMovesSelection",2);

    settings.cursorFollowsOrder=conf.getInt("cursorFollowsOrder",1);

    settings.insertBehavior=conf.getInt("insertBehavior",1);
    settings.pullDeleteRow=conf.getInt("pullDeleteRow",1);
    settings.cursorFollowsWheel=conf.getInt("cursorFollowsWheel",0);
    settings.removeInsOff=conf.getInt("removeInsOff",0);
    settings.removeVolOff=conf.getInt("removeVolOff",0);
    settings.insTypeMenu=conf.getInt("insTypeMenu",1);

    settings.selectAssetOnLoad=conf.getInt("selectAssetOnLoad",1);
  }

  if (groups&GUI_SETTINGS_FONT) {
    settings.mainFontSize=conf.getInt("mainFontSize",18);
    settings.headFontSize=conf.getInt("headFontSize",27);
    settings.patFontSize=conf.getInt("patFontSize",18);
    settings.iconSize=conf.getInt("iconSize",16);

    settings.mainFont=conf.getInt("mainFont",0);
    settings.headFont=conf.getInt("headFont",0);
    settings.patFont=conf.getInt("patFont",0);
    settings.mainFontPath=conf.getString("mainFontPath","");
    settings.headFontPath=conf.getString("headFontPath","");
    settings.patFontPath=conf.getString("patFontPath","");

    settings.loadJapanese=conf.getInt("loadJapanese",0);
    settings.loadChinese=conf.getInt("loadChinese",0);
    settings.loadChineseTraditional=conf.getInt("loadChineseTraditional",0);
    settings.loadKorean=conf.getInt("loadKorean",0);

    settings.fontBackend=conf.getInt("fontBackend",FONT_BACKEND_DEFAULT);
    settings.fontHinting=conf.getInt("fontHinting",0);
    settings.fontBitmap=conf.getInt("fontBitmap",0);
    settings.fontAutoHint=conf.getInt("fontAutoHint",1);
    settings.fontAntiAlias=conf.getInt("fontAntiAlias",1);
  }

  if (groups&GUI_SETTINGS_APPEARANCE) {
    settings.oscRoundedCorners=conf.getInt("oscRoundedCorners",1);
    settings.oscTakesEntireWindow=conf.getInt("oscTakesEntireWindow",0);
    settings.oscBorder=conf.getInt("oscBorder",1);
    settings.oscEscapesBoundary=conf.getInt("oscEscapesBoundary",0);
    settings.oscMono=conf.getInt("oscMono",1);
    settings.oscAntiAlias=conf.getInt("oscAntiAlias",1);

    settings.channelColors=conf.getInt("channelColors",1);
    settings.channelTextColors=conf.getInt("channelTextColors",0);
    settings.channelStyle=conf.getInt("channelStyle",1);
    settings.channelVolStyle=conf.getInt("channelVolStyle",0);
    settings.channelFeedbackStyle=conf.getInt("channelFeedbackStyle",1);
    settings.channelFont=conf.getInt("channelFont",1);
    settings.channelTextCenter=conf.getInt("channelTextCenter",1);

    settings.roundedWindows=conf.getInt("roundedWindows",1);
    settings.roundedButtons=conf.getInt("roundedButtons",1);
    settings.roundedTabs=conf.getInt("roundedTabs",1);
    settings.wrapText=conf.getInt("wrapText",1);
    settings.roundedScrollbars=conf.getInt("roundedScrollbars",1);
    settings.roundedMenus=conf.getInt("roundedMenus",0);

    settings.separateFMColors=conf.getInt("separateFMColors",0);
    settings.insEditColorize=conf.getInt("insEditColorize",0);

    settings.chipNames=conf.getInt("chipNames",0);
    settings.overflowHighlight=conf.getInt("overflowHighlight",0);
    settings.partyTime=conf.getInt("partyTime",0);
    settings.flatNotes=conf.getInt("flatNotes",0);
    settings.germanNotation=conf.getInt("germanNotation",0);

    settings.frameBorders=conf.getInt("frameBorders",0);
    settings.doFrameShadingForMultilineText=conf.getInt("doFrameShadingForMultilineText",0);

    settings.noteOffLabel=conf.getString("noteOffLabel","OFF");
    settings.noteRelLabel=conf.getString("noteRelLabel","===");
    settings.macroRelLabel=conf.getString("macroRelLabel","REL");
    settings.emptyLabel=conf.getString("emptyLabel","...");
    settings.emptyLabel2=conf.getString("emptyLabel2","..");

    settings.noteCellSpacing=conf.getInt("noteCellSpacing",0);
    settings.insCellSpacing=conf.getInt("insCellSpacing",0);
    settings.volCellSpacing=conf.getInt("volCellSpacing",0);
    settings.effectCellSpacing=conf.getInt("effectCellSpacing",0);
    settings.effectValCellSpacing=conf.getInt("effectValCellSpacing",0);

    settings.patRowsBase=conf.getInt("patRowsBase",0);
    settings.orderRowsBase=conf.getInt("orderRowsBase",1);
    settings.fmNames=conf.getInt("fmNames",0);
    settings.statusDisplay=conf.getInt("statusDisplay",0);
    settings.viewPrevPattern=conf.getInt("viewPrevPattern",1);
    settings.susPosition=conf.getInt("susPosition",0);

    settings.titleBarInfo=conf.getInt("titleBarInfo",1);
    settings.titleBarSys=conf.getInt("titleBarSys",1);

    settings.oplStandardWaveNames=conf.getInt("oplStandardWaveNames",0);

    settings.horizontalDataView=conf.getInt("horizontalDataView",0);
    settings.noMultiSystem=conf.getInt("noMultiSystem",0);
    settings.oldMacroVSlider=conf.getInt("oldMacroVSlider",0);
    settings.unsignedDetune=conf.getInt("unsignedDetune",0);
    settings.centerPattern=conf.getInt("centerPattern",0);
    settings.ordersCursor=conf.getInt("ordersCursor",1);
    settings.oneDigitEffects=conf.getInt("oneDigitEffects",0);
    settings.orderButtonPos=conf.getInt("orderButtonPos",2);
    settings.memUsageUnit=conf.getInt("memUsageUnit",1);
    settings.capitalMenuBar=conf.getInt("capitalMenuBar",0);
    settings.insIconsStyle=conf.getInt("insIconsStyle",1);
    settings.sysSeparators=conf.getInt("sysSeparators",1);
  }

  if (groups&GUI_SETTINGS_LAYOUTS) {
    settings.fmLayout=conf.getInt("fmLayout",4);
    settings.sampleLayout=conf.getInt("sampleLayout",0);
    settings.waveLayout=conf.getInt("waveLayout",0);
    settings.exportOptionsLayout=conf.getInt("exportOptionsLayout",1);
    settings.unifiedDataView=conf.getInt("unifiedDataView",0);
    settings.macroLayout=conf.getInt("macroLayout",0);
    settings.controlLayout=conf.getInt("controlLayout",3);
    settings.classicChipOptions=conf.getInt("classicChipOptions",0);
  }

  if (groups&GUI_SETTINGS_COLOR) {
    settings.guiColorsBase=conf.getInt("guiColorsBase",0);
    settings.guiColorsShading=conf.getInt("guiColorsShading",0);

    // colors
    for (int i=0; i<GUI_COLOR_MAX; i++) {
      uiColors[i]=ImGui::ColorConvertU32ToFloat4(conf.getInt(guiColors[i].name,guiColors[i].defaultColor));
    }
  }

  if (groups&GUI_SETTINGS_EMULATION) {
    settings.arcadeCore=conf.getInt("arcadeCore",0);
    settings.ym2612Core=conf.getInt("ym2612Core",0);
    settings.snCore=conf.getInt("snCore",0);
    settings.nesCore=conf.getInt("nesCore",0);
    settings.fdsCore=conf.getInt("fdsCore",0);
    settings.c64Core=conf.getInt("c64Core",0);
    settings.pokeyCore=conf.getInt("pokeyCore",1);
    settings.opnCore=conf.getInt("opnCore",1);
    settings.opl2Core=conf.getInt("opl2Core",0);
    settings.opl3Core=conf.getInt("opl3Core",0);
    settings.arcadeCoreRender=conf.getInt("arcadeCoreRender",1);
    settings.ym2612CoreRender=conf.getInt("ym2612CoreRender",0);
    settings.snCoreRender=conf.getInt("snCoreRender",0);
    settings.nesCoreRender=conf.getInt("nesCoreRender",0);
    settings.fdsCoreRender=conf.getInt("fdsCoreRender",1);
    settings.c64CoreRender=conf.getInt("c64CoreRender",1);
    settings.pokeyCoreRender=conf.getInt("pokeyCoreRender",1);
    settings.opnCoreRender=conf.getInt("opnCoreRender",1);
    settings.opl2CoreRender=conf.getInt("opl2CoreRender",0);
    settings.opl3CoreRender=conf.getInt("opl3CoreRender",0);

    settings.pcSpeakerOutMethod=conf.getInt("pcSpeakerOutMethod",0);

    settings.yrw801Path=conf.getString("yrw801Path","");
    settings.tg100Path=conf.getString("tg100Path","");
    settings.mu5Path=conf.getString("mu5Path","");
  }

  clampSetting(settings.mainFontSize,2,96);
  clampSetting(settings.headFontSize,2,96);
  clampSetting(settings.patFontSize,2,96);
  clampSetting(settings.iconSize,2,48);
  clampSetting(settings.audioEngine,0,2);
  clampSetting(settings.audioQuality,0,1);
  clampSetting(settings.audioHiPass,0,1);
  clampSetting(settings.audioBufSize,32,4096);
  clampSetting(settings.audioRate,8000,384000);
  clampSetting(settings.audioChans,1,16);
  clampSetting(settings.arcadeCore,0,1);
  clampSetting(settings.ym2612Core,0,2);
  clampSetting(settings.snCore,0,1);
  clampSetting(settings.nesCore,0,1);
  clampSetting(settings.fdsCore,0,1);
  clampSetting(settings.c64Core,0,2);
  clampSetting(settings.pokeyCore,0,1);
  clampSetting(settings.opnCore,0,1);
  clampSetting(settings.opl2Core,0,2);
  clampSetting(settings.opl3Core,0,2);
  clampSetting(settings.arcadeCoreRender,0,1);
  clampSetting(settings.ym2612CoreRender,0,2);
  clampSetting(settings.snCoreRender,0,1);
  clampSetting(settings.nesCoreRender,0,1);
  clampSetting(settings.fdsCoreRender,0,1);
  clampSetting(settings.c64CoreRender,0,2);
  clampSetting(settings.pokeyCoreRender,0,1);
  clampSetting(settings.opnCoreRender,0,1);
  clampSetting(settings.opl2CoreRender,0,2);
  clampSetting(settings.opl3CoreRender,0,2);
  clampSetting(settings.pcSpeakerOutMethod,0,4);
  clampSetting(settings.mainFont,0,6);
  clampSetting(settings.patFont,0,6);
  clampSetting(settings.patRowsBase,0,1);
  clampSetting(settings.orderRowsBase,0,1);
  clampSetting(settings.soloAction,0,2);
  clampSetting(settings.pullDeleteBehavior,0,1);
  clampSetting(settings.wrapHorizontal,0,2);
  clampSetting(settings.wrapVertical,0,3);
  clampSetting(settings.fmNames,0,2);
  clampSetting(settings.allowEditDocking,0,1);
  clampSetting(settings.chipNames,0,1);
  clampSetting(settings.overflowHighlight,0,1);
  clampSetting(settings.partyTime,0,1);
  clampSetting(settings.flatNotes,0,1);
  clampSetting(settings.germanNotation,0,1);
  clampSetting(settings.stepOnDelete,0,1);
  clampSetting(settings.scrollStep,0,1);
  clampSetting(settings.sysSeparators,0,1);
  clampSetting(settings.forceMono,0,1);
  clampSetting(settings.controlLayout,0,3);
  clampSetting(settings.statusDisplay,0,3);
  clampSetting(settings.dpiScale,0.0f,4.0f);
  clampSetting(settings.viewPrevPattern,0,1);
  clampSetting(settings.guiColorsBase,0,1);
  clampSetting(settings.guiColorsShading,0,100);
  clampSetting(settings.doFrameShadingForMultilineText,0,1);
  clampSetting(settings.avoidRaisingPattern,0,1);
  clampSetting(settings.insFocusesPattern,0,1);
  clampSetting(settings.stepOnInsert,0,1);
  clampSetting(settings.unifiedDataView,0,1);
  clampSetting(settings.sysFileDialog,0,1);
  clampSetting(settings.roundedWindows,0,1);
  clampSetting(settings.roundedButtons,0,1);
  clampSetting(settings.roundedTabs,0,1);
  clampSetting(settings.wrapText,0,1);
  clampSetting(settings.roundedScrollbars,0,1);
  clampSetting(settings.roundedMenus,0,1);
  clampSetting(settings.roundedTabs,0,1);
  clampSetting(settings.roundedScrollbars,0,1);
  clampSetting(settings.loadJapanese,0,1);
  clampSetting(settings.loadChinese,0,1);
  clampSetting(settings.loadChineseTraditional,0,1);
  clampSetting(settings.loadKorean,0,1);
  clampSetting(settings.fmLayout,0,6);
  clampSetting(settings.susPosition,0,1);
  clampSetting(settings.effectCursorDir,0,2);
  clampSetting(settings.cursorPastePos,0,1);
  clampSetting(settings.titleBarInfo,0,3);
  clampSetting(settings.titleBarSys,0,1);
  clampSetting(settings.frameBorders,0,1);
  clampSetting(settings.effectDeletionAltersValue,0,1);
  clampSetting(settings.sampleLayout,0,1);
  clampSetting(settings.waveLayout,0,1);
  clampSetting(settings.separateFMColors,0,1);
  clampSetting(settings.insEditColorize,0,1);
  clampSetting(settings.metroVol,0,200);
  clampSetting(settings.sampleVol,0,100);
  clampSetting(settings.pushNibble,0,1);
  clampSetting(settings.scrollChangesOrder,0,2);
  clampSetting(settings.oplStandardWaveNames,0,1);
  clampSetting(settings.cursorMoveNoScroll,0,1);
  clampSetting(settings.lowLatency,0,1);
  clampSetting(settings.notePreviewBehavior,0,3);
  clampSetting(settings.powerSave,0,1);
  clampSetting(settings.absorbInsInput,0,1);
  clampSetting(settings.eventDelay,0,1);
  clampSetting(settings.moveWindowTitle,0,1);
  clampSetting(settings.hiddenSystems,0,1);
  clampSetting(settings.horizontalDataView,0,1);
  clampSetting(settings.noMultiSystem,0,1);
  clampSetting(settings.oldMacroVSlider,0,1);
  clampSetting(settings.displayAllInsTypes,0,1);
  clampSetting(settings.displayPartial,0,1);
  clampSetting(settings.noteCellSpacing,0,32);
  clampSetting(settings.insCellSpacing,0,32);
  clampSetting(settings.volCellSpacing,0,32);
  clampSetting(settings.effectCellSpacing,0,32);
  clampSetting(settings.effectValCellSpacing,0,32);
  clampSetting(settings.doubleClickColumn,0,1);
  clampSetting(settings.blankIns,0,1);
  clampSetting(settings.dragMovesSelection,0,2);
  clampSetting(settings.unsignedDetune,0,1);
  clampSetting(settings.noThreadedInput,0,1);
  clampSetting(settings.saveWindowPos,0,1);
  clampSetting(settings.clampSamples,0,1);
  clampSetting(settings.saveUnusedPatterns,0,1);
  clampSetting(settings.channelColors,0,2);
  clampSetting(settings.channelTextColors,0,2);
  clampSetting(settings.channelStyle,0,5);
  clampSetting(settings.channelVolStyle,0,4);
  clampSetting(settings.channelFeedbackStyle,0,3);
  clampSetting(settings.channelFont,0,1);
  clampSetting(settings.channelTextCenter,0,1);
  clampSetting(settings.maxRecentFile,0,30);
  clampSetting(settings.midiOutClock,0,1);
  clampSetting(settings.midiOutTime,0,1);
  clampSetting(settings.midiOutProgramChange,0,1);
  clampSetting(settings.midiOutMode,0,2);
  clampSetting(settings.midiOutTimeRate,0,4);
  clampSetting(settings.centerPattern,0,1);
  clampSetting(settings.ordersCursor,0,1);
  clampSetting(settings.persistFadeOut,0,1);
  clampSetting(settings.macroLayout,0,4);
  clampSetting(settings.doubleClickTime,0.02,1.0);
  clampSetting(settings.oneDigitEffects,0,1);
  clampSetting(settings.disableFadeIn,0,1);
  clampSetting(settings.cursorFollowsOrder,0,1);
  clampSetting(settings.iCannotWait,0,1);
  clampSetting(settings.orderButtonPos,0,2);
  clampSetting(settings.compress,0,1);
  clampSetting(settings.newPatternFormat,0,1);
  clampSetting(settings.renderClearPos,0,1);
  clampSetting(settings.insertBehavior,0,1);
  clampSetting(settings.pullDeleteRow,0,1);
  clampSetting(settings.newSongBehavior,0,1);
  clampSetting(settings.memUsageUnit,0,1);
  clampSetting(settings.cursorFollowsWheel,0,2);
  clampSetting(settings.noDMFCompat,0,1);
  clampSetting(settings.removeInsOff,0,1);
  clampSetting(settings.removeVolOff,0,1);
  clampSetting(settings.playOnLoad,0,2);
  clampSetting(settings.insTypeMenu,0,1);
  clampSetting(settings.capitalMenuBar,0,1);
  clampSetting(settings.centerPopup,0,1);
  clampSetting(settings.insIconsStyle,0,2);
  clampSetting(settings.classicChipOptions,0,1);
  clampSetting(settings.exportOptionsLayout,0,2);
  clampSetting(settings.wasapiEx,0,1);
  clampSetting(settings.chanOscThreads,0,256);
  clampSetting(settings.renderPoolThreads,0,DIV_MAX_CHIPS);
  clampSetting(settings.showPool,0,1);
  clampSetting(settings.writeInsNames,0,1);
  clampSetting(settings.readInsNames,0,1);
  clampSetting(settings.fontBackend,0,1);
  clampSetting(settings.fontHinting,0,3);
  clampSetting(settings.fontBitmap,0,1);
  clampSetting(settings.fontAutoHint,0,2);
  clampSetting(settings.fontAntiAlias,0,1);
  clampSetting(settings.selectAssetOnLoad,0,1);

  clampSetting(settings.language,0,DIV_LANG_MAX-1);

  if (settings.exportLoops<0.0) settings.exportLoops=0.0;
  if (settings.exportFadeOut<0.0) settings.exportFadeOut=0.0;  
}

void FurnaceGUI::writeConfig(DivConfig& conf, FurnaceGUISettingGroups groups) {
  // general
  if (groups&GUI_SETTINGS_GENERAL) {
    conf.set("renderDriver",settings.renderDriver);
    conf.set("noDMFCompat",settings.noDMFCompat);

    conf.set("dpiScale",settings.dpiScale);

    conf.set("initialSys2",settings.initialSys.toBase64());
    conf.set("initialSysName",settings.initialSysName);

    conf.set("noThreadedInput",settings.noThreadedInput);
    conf.set("powerSave",settings.powerSave);
    conf.set("eventDelay",settings.eventDelay);

    conf.set("renderBackend",settings.renderBackend);
    conf.set("renderClearPos",settings.renderClearPos);
    
    conf.set("chanOscThreads",settings.chanOscThreads);
    conf.set("renderPoolThreads",settings.renderPoolThreads);
    conf.set("showPool",settings.showPool);
    conf.set("writeInsNames",settings.writeInsNames);
    conf.set("readInsNames",settings.readInsNames);
    conf.set("defaultAuthorName",settings.defaultAuthorName);

    conf.set("hiddenSystems",settings.hiddenSystems);
    conf.set("allowEditDocking",settings.allowEditDocking);
    conf.set("sysFileDialog",settings.sysFileDialog);
    conf.set("displayAllInsTypes",settings.displayAllInsTypes);
    conf.set("displayPartial",settings.displayPartial);

    conf.set("blankIns",settings.blankIns);

    conf.set("saveWindowPos",settings.saveWindowPos);
    
    conf.set("saveUnusedPatterns",settings.saveUnusedPatterns);
    conf.set("maxRecentFile",settings.maxRecentFile);
    
    conf.set("persistFadeOut",settings.persistFadeOut);
    conf.set("exportLoops",settings.exportLoops);
    conf.set("exportFadeOut",settings.exportFadeOut);

    conf.set("doubleClickTime",settings.doubleClickTime);
    conf.set("disableFadeIn",settings.disableFadeIn);
    conf.set("iCannotWait",settings.iCannotWait);

    conf.set("compress",settings.compress);
    conf.set("newPatternFormat",settings.newPatternFormat);
    conf.set("newSongBehavior",settings.newSongBehavior);
    conf.set("playOnLoad",settings.playOnLoad);
    conf.set("centerPopup",settings.centerPopup);

    conf.set("language",settings.language);
  }

  // audio
  if (groups&GUI_SETTINGS_AUDIO) {
    conf.set("audioEngine",String(audioBackends[settings.audioEngine]));
    conf.set("audioDevice",settings.audioDevice);
    conf.set("sdlAudioDriver",settings.sdlAudioDriver);
    conf.set("audioQuality",settings.audioQuality);
    conf.set("audioHiPass",settings.audioHiPass);
    conf.set("audioBufSize",settings.audioBufSize);
    conf.set("audioRate",settings.audioRate);
    conf.set("audioChans",settings.audioChans);

    conf.set("lowLatency",settings.lowLatency);

    conf.set("metroVol",settings.metroVol);
    conf.set("sampleVol",settings.sampleVol);

    conf.set("wasapiEx",settings.wasapiEx);

    conf.set("clampSamples",settings.clampSamples);
    conf.set("forceMono",settings.forceMono);
  }

  // MIDI
  if (groups&GUI_SETTINGS_MIDI) {
    conf.set("midiInDevice",settings.midiInDevice);
    conf.set("midiOutDevice",settings.midiOutDevice);
    conf.set("midiOutClock",settings.midiOutClock);
    conf.set("midiOutTime",settings.midiOutTime);
    conf.set("midiOutProgramChange",settings.midiOutProgramChange);
    conf.set("midiOutMode",settings.midiOutMode);
    conf.set("midiOutTimeRate",settings.midiOutTimeRate);
  }

  // keyboard
  if (groups&GUI_SETTINGS_KEYBOARD) {
    // keybinds
    for (int i=0; i<GUI_ACTION_MAX; i++) {
      if (guiActions[i].defaultBind==-1) continue; // not a bind
      conf.set(String("keybind_GUI_ACTION_")+String(guiActions[i].name),actionKeys[i]);
    }

    conf.set("noteKeys",encodeKeyMap(noteKeys));
  }

  // behavior
  if (groups&GUI_SETTINGS_BEHAVIOR) {
    conf.set("soloAction",settings.soloAction);
    conf.set("pullDeleteBehavior",settings.pullDeleteBehavior);
    conf.set("wrapHorizontal",settings.wrapHorizontal);
    conf.set("wrapVertical",settings.wrapVertical);
    
    conf.set("stepOnDelete",settings.stepOnDelete);
    conf.set("scrollStep",settings.scrollStep);
    conf.set("avoidRaisingPattern",settings.avoidRaisingPattern);
    conf.set("insFocusesPattern",settings.insFocusesPattern);
    conf.set("stepOnInsert",settings.stepOnInsert);
    conf.set("effectCursorDir",settings.effectCursorDir);
    conf.set("cursorPastePos",settings.cursorPastePos);
    
    conf.set("effectDeletionAltersValue",settings.effectDeletionAltersValue);

    conf.set("pushNibble",settings.pushNibble);
    conf.set("scrollChangesOrder",settings.scrollChangesOrder);
    conf.set("cursorMoveNoScroll",settings.cursorMoveNoScroll);

    conf.set("notePreviewBehavior",settings.notePreviewBehavior);
    
    conf.set("absorbInsInput",settings.absorbInsInput);
    
    conf.set("moveWindowTitle",settings.moveWindowTitle);
    
    conf.set("doubleClickColumn",settings.doubleClickColumn);
    conf.set("dragMovesSelection",settings.dragMovesSelection);
    
    conf.set("cursorFollowsOrder",settings.cursorFollowsOrder);
    
    conf.set("insertBehavior",settings.insertBehavior);
    conf.set("pullDeleteRow",settings.pullDeleteRow);
    conf.set("cursorFollowsWheel",settings.cursorFollowsWheel);
    conf.set("removeInsOff",settings.removeInsOff);
    conf.set("removeVolOff",settings.removeVolOff);
    conf.set("insTypeMenu",settings.insTypeMenu);
    
    conf.set("selectAssetOnLoad",settings.selectAssetOnLoad);
  }

  // font
  if (groups&GUI_SETTINGS_FONT) {
    conf.set("mainFontSize",settings.mainFontSize);
    conf.set("headFontSize",settings.headFontSize);
    conf.set("patFontSize",settings.patFontSize);
    conf.set("iconSize",settings.iconSize);

    conf.set("mainFont",settings.mainFont);
    conf.set("headFont",settings.headFont);
    conf.set("patFont",settings.patFont);
    conf.set("mainFontPath",settings.mainFontPath);
    conf.set("headFontPath",settings.headFontPath);
    conf.set("patFontPath",settings.patFontPath);

    conf.set("loadJapanese",settings.loadJapanese);
    conf.set("loadChinese",settings.loadChinese);
    conf.set("loadChineseTraditional",settings.loadChineseTraditional);
    conf.set("loadKorean",settings.loadKorean);

    conf.set("fontBackend",settings.fontBackend);
    conf.set("fontHinting",settings.fontHinting);
    conf.set("fontBitmap",settings.fontBitmap);
    conf.set("fontAutoHint",settings.fontAutoHint);
    conf.set("fontAntiAlias",settings.fontAntiAlias);
  }

  // appearance
  if (groups&GUI_SETTINGS_APPEARANCE) {
    conf.set("oscRoundedCorners",settings.oscRoundedCorners);
    conf.set("oscTakesEntireWindow",settings.oscTakesEntireWindow);
    conf.set("oscBorder",settings.oscBorder);
    conf.set("oscEscapesBoundary",settings.oscEscapesBoundary);
    conf.set("oscMono",settings.oscMono);
    conf.set("oscAntiAlias",settings.oscAntiAlias);

    conf.set("channelColors",settings.channelColors);
    conf.set("channelTextColors",settings.channelTextColors);
    conf.set("channelStyle",settings.channelStyle);
    conf.set("channelVolStyle",settings.channelVolStyle);
    conf.set("channelFeedbackStyle",settings.channelFeedbackStyle);
    conf.set("channelFont",settings.channelFont);
    conf.set("channelTextCenter",settings.channelTextCenter);

    conf.set("roundedWindows",settings.roundedWindows);
    conf.set("roundedButtons",settings.roundedButtons);
    conf.set("roundedTabs",settings.roundedTabs);
    conf.set("wrapText",settings.wrapText);
    conf.set("roundedScrollbars",settings.roundedScrollbars);
    conf.set("roundedMenus",settings.roundedMenus);

    conf.set("separateFMColors",settings.separateFMColors);
    conf.set("insEditColorize",settings.insEditColorize);

    conf.set("chipNames",settings.chipNames);
    conf.set("overflowHighlight",settings.overflowHighlight);
    conf.set("partyTime",settings.partyTime);
    conf.set("flatNotes",settings.flatNotes);
    conf.set("germanNotation",settings.germanNotation);

    conf.set("frameBorders",settings.frameBorders);

    conf.set("noteOffLabel",settings.noteOffLabel);
    conf.set("noteRelLabel",settings.noteRelLabel);
    conf.set("macroRelLabel",settings.macroRelLabel);
    conf.set("emptyLabel",settings.emptyLabel);
    conf.set("emptyLabel2",settings.emptyLabel2);

    conf.set("noteCellSpacing",settings.noteCellSpacing);
    conf.set("insCellSpacing",settings.insCellSpacing);
    conf.set("volCellSpacing",settings.volCellSpacing);
    conf.set("effectCellSpacing",settings.effectCellSpacing);
    conf.set("effectValCellSpacing",settings.effectValCellSpacing);

    conf.set("patRowsBase",settings.patRowsBase);
    conf.set("orderRowsBase",settings.orderRowsBase);
    conf.set("fmNames",settings.fmNames);
    conf.set("statusDisplay",settings.statusDisplay);
    conf.set("viewPrevPattern",settings.viewPrevPattern);
    conf.set("susPosition",settings.susPosition);

    conf.set("titleBarInfo",settings.titleBarInfo);
    conf.set("titleBarSys",settings.titleBarSys);

    conf.set("oplStandardWaveNames",settings.oplStandardWaveNames);

    conf.set("horizontalDataView",settings.horizontalDataView);
    conf.set("noMultiSystem",settings.noMultiSystem);
    conf.set("oldMacroVSlider",settings.oldMacroVSlider);
    conf.set("unsignedDetune",settings.unsignedDetune);
    conf.set("centerPattern",settings.centerPattern);
    conf.set("ordersCursor",settings.ordersCursor);
    conf.set("oneDigitEffects",settings.oneDigitEffects);
    conf.set("orderButtonPos",settings.orderButtonPos);
    conf.set("memUsageUnit",settings.memUsageUnit);
    conf.set("capitalMenuBar",settings.capitalMenuBar);
    conf.set("insIconsStyle",settings.insIconsStyle);
    conf.set("sysSeparators",settings.sysSeparators);

    conf.set("doFrameShadingForMultilineText",settings.doFrameShadingForMultilineText);
  }

  // layout
  if (groups&GUI_SETTINGS_LAYOUTS) {
    conf.set("fmLayout",settings.fmLayout);
    conf.set("sampleLayout",settings.sampleLayout);
    conf.set("waveLayout",settings.waveLayout);
    conf.set("exportOptionsLayout",settings.exportOptionsLayout);
    conf.set("unifiedDataView",settings.unifiedDataView);
    conf.set("macroLayout",settings.macroLayout);
    conf.set("controlLayout",settings.controlLayout);
    conf.set("classicChipOptions",settings.classicChipOptions);
  }

  // color
  if (groups&GUI_SETTINGS_COLOR) {
    conf.set("guiColorsBase",settings.guiColorsBase);
    conf.set("guiColorsShading",settings.guiColorsShading);

    // colors
    for (int i=0; i<GUI_COLOR_MAX; i++) {
      conf.set(guiColors[i].name,(int)ImGui::ColorConvertFloat4ToU32(uiColors[i]));
    }
  }

  // emulation
  if (groups&GUI_SETTINGS_EMULATION) {
    conf.set("arcadeCore",settings.arcadeCore);
    conf.set("ym2612Core",settings.ym2612Core);
    conf.set("snCore",settings.snCore);
    conf.set("nesCore",settings.nesCore);
    conf.set("fdsCore",settings.fdsCore);
    conf.set("c64Core",settings.c64Core);
    conf.set("pokeyCore",settings.pokeyCore);
    conf.set("opnCore",settings.opnCore);
    conf.set("opl2Core",settings.opl2Core);
    conf.set("opl3Core",settings.opl3Core);
    conf.set("arcadeCoreRender",settings.arcadeCoreRender);
    conf.set("ym2612CoreRender",settings.ym2612CoreRender);
    conf.set("snCoreRender",settings.snCoreRender);
    conf.set("nesCoreRender",settings.nesCoreRender);
    conf.set("fdsCoreRender",settings.fdsCoreRender);
    conf.set("c64CoreRender",settings.c64CoreRender);
    conf.set("pokeyCoreRender",settings.pokeyCoreRender);
    conf.set("opnCoreRender",settings.opnCoreRender);
    conf.set("opl2CoreRender",settings.opl2CoreRender);
    conf.set("opl3CoreRender",settings.opl3CoreRender);

    conf.set("pcSpeakerOutMethod",settings.pcSpeakerOutMethod);

    conf.set("yrw801Path",settings.yrw801Path);
    conf.set("tg100Path",settings.tg100Path);
    conf.set("mu5Path",settings.mu5Path);
  }
}

void FurnaceGUI::syncSettings() {
  readConfig(e->getConfObject());

  parseKeybinds();

  midiMap.read(e->getConfigPath()+DIR_SEPARATOR_STR+"midiIn_"+stripName(settings.midiInDevice)+".cfg");
  midiMap.compile();

  e->setMidiDirect(midiMap.directChannel);
  e->setMidiDirectProgram(midiMap.directChannel && midiMap.directProgram);
  e->setMidiVolExp(midiMap.volExp);
  e->setMetronomeVol(((float)settings.metroVol)/100.0f);
  e->setSamplePreviewVol(((float)settings.sampleVol)/100.0f);
}

void FurnaceGUI::commitSettings() {
  bool sampleROMsChanged=settings.yrw801Path!=e->getConfString("yrw801Path","") ||
    settings.tg100Path!=e->getConfString("tg100Path","") ||
    settings.mu5Path!=e->getConfString("mu5Path","");

  bool coresChanged=(
    settings.arcadeCore!=e->getConfInt("arcadeCore",0) ||
    settings.ym2612Core!=e->getConfInt("ym2612Core",0) ||
    settings.snCore!=e->getConfInt("snCore",0) ||
    settings.nesCore!=e->getConfInt("nesCore",0) ||
    settings.fdsCore!=e->getConfInt("fdsCore",0) ||
    settings.c64Core!=e->getConfInt("c64Core",0) ||
    settings.pokeyCore!=e->getConfInt("pokeyCore",1) ||
    settings.opnCore!=e->getConfInt("opnCore",1) ||
    settings.opl2Core!=e->getConfInt("opl2Core",0) ||
    settings.opl3Core!=e->getConfInt("opl3Core",0) ||
    settings.arcadeCoreRender!=e->getConfInt("arcadeCoreRender",0) ||
    settings.ym2612CoreRender!=e->getConfInt("ym2612CoreRender",0) ||
    settings.snCoreRender!=e->getConfInt("snCoreRender",0) ||
    settings.nesCoreRender!=e->getConfInt("nesCoreRender",0) ||
    settings.fdsCoreRender!=e->getConfInt("fdsCoreRender",0) ||
    settings.c64CoreRender!=e->getConfInt("c64CoreRender",0) ||
    settings.pokeyCoreRender!=e->getConfInt("pokeyCoreRender",1) ||
    settings.opnCoreRender!=e->getConfInt("opnCoreRender",1) ||
    settings.opl2CoreRender!=e->getConfInt("opl2CoreRender",0) ||
    settings.opl3CoreRender!=e->getConfInt("opl3CoreRender",0) ||
    settings.audioQuality!=e->getConfInt("audioQuality",0) ||
    settings.audioHiPass!=e->getConfInt("audioHiPass",1)
  );

  writeConfig(e->getConfObject());

  parseKeybinds();

  midiMap.compile();
  midiMap.write(e->getConfigPath()+DIR_SEPARATOR_STR+"midiIn_"+stripName(settings.midiInDevice)+".cfg");

  e->saveConf();

  while (!recentFile.empty() && (int)recentFile.size()>settings.maxRecentFile) {
    recentFile.pop_back();
  }

  if (sampleROMsChanged) {
    if (e->loadSampleROMs()) {
      showError(e->getLastError());
    }
  }

  if (!e->switchMaster(coresChanged)) {
    showError("could not initialize audio!");
  }

  ImGui::GetIO().Fonts->Clear();

  applyUISettings();

  if (rend) rend->destroyFontsTexture();
  if (!ImGui::GetIO().Fonts->Build()) {
    logE("error while building font atlas!");
    showError("error while loading fonts! please check your settings.");
    ImGui::GetIO().Fonts->Clear();
    mainFont=ImGui::GetIO().Fonts->AddFontDefault();
    patFont=mainFont;
    bigFont=mainFont;
    headFont=mainFont;
    if (rend) rend->destroyFontsTexture();
    if (!ImGui::GetIO().Fonts->Build()) {
      logE("error again while building font atlas!");
    } else {
      rend->createFontsTexture();
    }
  } else {
    rend->createFontsTexture();
  }

  audioEngineChanged=false;
}

bool FurnaceGUI::importColors(String path) {
  DivConfig c;
  if (!c.loadFromFile(path.c_str(),false,false)) {
    logW("error while opening color file for import: %s",strerror(errno));
    return false;
  }

  readConfig(c,GUI_SETTINGS_COLOR);

  applyUISettings(false);
  return true;
}

bool FurnaceGUI::exportColors(String path) {
  DivConfig c;

  c.set("configVersion",DIV_ENGINE_VERSION);
  writeConfig(c,GUI_SETTINGS_COLOR);

  FILE* f=ps_fopen(path.c_str(),"wb");
  if (f==NULL) {
    logW("error while opening color file for export: %s",strerror(errno));
    return false;
  }

  String result=c.toString();

  if (fwrite(result.c_str(),1,result.size(),f)!=result.size()) {
    logW("couldn't write color file entirely.");
  }

  fclose(f);
  return true;
}

bool FurnaceGUI::importKeybinds(String path) {
  FILE* f=ps_fopen(path.c_str(),"rb");
  if (f==NULL) {
    logW("error while opening keybind file for import: %s",strerror(errno));
    return false;
  }
  resetKeybinds();
  char line[4096];
  while (!feof(f)) {
    String key="";
    String value="";
    bool keyOrValue=false;
    if (fgets(line,4095,f)==NULL) {
      break;
    }
    for (char* i=line; *i; i++) {
      if (*i=='\n') continue;
      if (keyOrValue) {
        value+=*i;
      } else {
        if (*i=='=') {
          keyOrValue=true;
        } else {
          key+=*i;
        }
      }
    }
    if (keyOrValue) {
      // unoptimal
      const char* cs=key.c_str();
      bool found=false;
      for (int i=0; i<GUI_ACTION_MAX; i++) {
        try {
          if (strcmp(cs,guiActions[i].name)==0) {
            actionKeys[i]=std::stoi(value);
            found=true;
            break;
          }
        } catch (std::out_of_range& e) {
          break;
        } catch (std::invalid_argument& e) {
          break;
        }
      }
      if (!found) logW("line invalid: %s",line);
    }
  }
  fclose(f);
  return true;
}

bool FurnaceGUI::exportKeybinds(String path) {
  FILE* f=ps_fopen(path.c_str(),"wb");
  if (f==NULL) {
    logW("error while opening keybind file for export: %s",strerror(errno));
    return false;
  }
  for (int i=0; i<GUI_ACTION_MAX; i++) {
    if (guiActions[i].defaultBind==-1) continue;
    if (fprintf(f,"%s=%d\n",guiActions[i].name,actionKeys[i])<0) {
      logW("error while exporting keybinds: %s",strerror(errno));
      break;
    }
  }
  fclose(f);
  return true;
}

bool FurnaceGUI::importLayout(String path) {
  if (mobileUI) {
    logW("but you are on the mobile UI!");
    return false;
  }
  FILE* f=ps_fopen(path.c_str(),"rb");
  if (f==NULL) {
    logW("error while opening keybind file for import: %s",strerror(errno));
    return false;
  }
  if (fseek(f,0,SEEK_END)<0) {
    fclose(f);
    return false;
  }
  ssize_t len=ftell(f);
  if (len==(SIZE_MAX>>1)) {
    fclose(f);
    return false;
  }
  if (len<1) {
    if (len==0) {
      logE("that file is empty!");
      lastError="file is empty";
    } else {
      perror("tell error");
    }
    fclose(f);
    return false;
  }
  if (fseek(f,0,SEEK_SET)<0) {
    perror("size error");
    lastError=fmt::sprintf("on get size: %s",strerror(errno));
    fclose(f);
    return false;
  }
  pendingLayoutImport=new unsigned char[len];
  if (fread(pendingLayoutImport,1,(size_t)len,f)!=(size_t)len) {
    perror("read error");
    lastError=fmt::sprintf("on read: %s",strerror(errno));
    fclose(f);
    delete[] pendingLayoutImport;
    return false;
  }
  fclose(f);

  pendingLayoutImportLen=len;
  return true;
}

bool FurnaceGUI::exportLayout(String path) {
  if (mobileUI) {
    logW("but you are on the mobile UI!");
    return false;
  }
  FILE* f=ps_fopen(path.c_str(),"wb");
  if (f==NULL) {
    logW("error while opening layout file for export: %s",strerror(errno));
    return false;
  }
  size_t dataSize=0;
  const char* data=ImGui::SaveIniSettingsToMemory(&dataSize);
  if (fwrite(data,1,dataSize,f)!=dataSize) {
    logW("error while exporting layout: %s",strerror(errno));
  }
  fclose(f);
  return true;
}

void FurnaceGUI::resetColors() {
  for (int i=0; i<GUI_COLOR_MAX; i++) {
    uiColors[i]=ImGui::ColorConvertU32ToFloat4(guiColors[i].defaultColor);
  }
}

void FurnaceGUI::resetKeybinds() {
  for (int i=0; i<GUI_ACTION_MAX; i++) {
    if (guiActions[i].defaultBind==-1) continue;
    actionKeys[i]=guiActions[i].defaultBind;
  }
  parseKeybinds();
}

void FurnaceGUI::parseKeybinds() {
  actionMapGlobal.clear();
  actionMapPat.clear();
  actionMapInsList.clear();
  actionMapWaveList.clear();
  actionMapSampleList.clear();
  actionMapSample.clear();
  actionMapOrders.clear();

  for (int i=GUI_ACTION_GLOBAL_MIN+1; i<GUI_ACTION_GLOBAL_MAX; i++) {
    if (actionKeys[i]&FURK_MASK) {
      actionMapGlobal[actionKeys[i]]=i;
    }
  }

  for (int i=GUI_ACTION_PAT_MIN+1; i<GUI_ACTION_PAT_MAX; i++) {
    if (actionKeys[i]&FURK_MASK) {
      actionMapPat[actionKeys[i]]=i;
    }
  }

  for (int i=GUI_ACTION_INS_LIST_MIN+1; i<GUI_ACTION_INS_LIST_MAX; i++) {
    if (actionKeys[i]&FURK_MASK) {
      actionMapInsList[actionKeys[i]]=i;
    }
  }

  for (int i=GUI_ACTION_WAVE_LIST_MIN+1; i<GUI_ACTION_WAVE_LIST_MAX; i++) {
    if (actionKeys[i]&FURK_MASK) {
      actionMapWaveList[actionKeys[i]]=i;
    }
  }

  for (int i=GUI_ACTION_SAMPLE_LIST_MIN+1; i<GUI_ACTION_SAMPLE_LIST_MAX; i++) {
    if (actionKeys[i]&FURK_MASK) {
      actionMapSampleList[actionKeys[i]]=i;
    }
  }

  for (int i=GUI_ACTION_SAMPLE_MIN+1; i<GUI_ACTION_SAMPLE_MAX; i++) {
    if (actionKeys[i]&FURK_MASK) {
      actionMapSample[actionKeys[i]]=i;
    }
  }

  for (int i=GUI_ACTION_ORDERS_MIN+1; i<GUI_ACTION_ORDERS_MAX; i++) {
    if (actionKeys[i]&FURK_MASK) {
      actionMapOrders[actionKeys[i]]=i;
    }
  }
}

void FurnaceGUI::pushAccentColors(const ImVec4& one, const ImVec4& two, const ImVec4& border, const ImVec4& borderShadow) {
  float hue, sat, val;

  ImVec4 primaryActive=one;
  ImVec4 primaryHover, primary;
  primaryHover.w=primaryActive.w;
  primary.w=primaryActive.w;
  ImGui::ColorConvertRGBtoHSV(primaryActive.x,primaryActive.y,primaryActive.z,hue,sat,val);
  if (settings.guiColorsBase) {
    primary=primaryActive;
    ImGui::ColorConvertHSVtoRGB(hue,sat*0.9,val*0.9,primaryHover.x,primaryHover.y,primaryHover.z);
    ImGui::ColorConvertHSVtoRGB(hue,sat,val*0.5,primaryActive.x,primaryActive.y,primaryActive.z);
  } else {
    ImGui::ColorConvertHSVtoRGB(hue,sat*0.9,val*0.5,primaryHover.x,primaryHover.y,primaryHover.z);
    ImGui::ColorConvertHSVtoRGB(hue,sat*0.8,val*0.35,primary.x,primary.y,primary.z);
  }

  ImVec4 secondaryActive=two;
  ImVec4 secondaryHover, secondary, secondarySemiActive;
  secondarySemiActive.w=secondaryActive.w;
  secondaryHover.w=secondaryActive.w;
  secondary.w=secondaryActive.w;
  ImGui::ColorConvertRGBtoHSV(secondaryActive.x,secondaryActive.y,secondaryActive.z,hue,sat,val);
  if (settings.guiColorsBase) {
    secondary=secondaryActive;
    ImGui::ColorConvertHSVtoRGB(hue,sat*0.9,val*0.7,secondarySemiActive.x,secondarySemiActive.y,secondarySemiActive.z);
    ImGui::ColorConvertHSVtoRGB(hue,sat*0.9,val*0.9,secondaryHover.x,secondaryHover.y,secondaryHover.z);
    ImGui::ColorConvertHSVtoRGB(hue,sat,val*0.5,secondaryActive.x,secondaryActive.y,secondaryActive.z);
  } else {
    ImGui::ColorConvertHSVtoRGB(hue,sat*0.9,val*0.75,secondarySemiActive.x,secondarySemiActive.y,secondarySemiActive.z);
    ImGui::ColorConvertHSVtoRGB(hue,sat*0.9,val*0.5,secondaryHover.x,secondaryHover.y,secondaryHover.z);
    ImGui::ColorConvertHSVtoRGB(hue,sat*0.9,val*0.25,secondary.x,secondary.y,secondary.z);
  }

  ImGui::PushStyleColor(ImGuiCol_Button,primary);
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered,primaryHover);
  ImGui::PushStyleColor(ImGuiCol_ButtonActive,primaryActive);
  ImGui::PushStyleColor(ImGuiCol_Tab,primary);
  ImGui::PushStyleColor(ImGuiCol_TabHovered,secondaryHover);
  ImGui::PushStyleColor(ImGuiCol_TabActive,secondarySemiActive);
  ImGui::PushStyleColor(ImGuiCol_TabUnfocused,primary);
  ImGui::PushStyleColor(ImGuiCol_TabUnfocusedActive,primaryHover);
  ImGui::PushStyleColor(ImGuiCol_Header,secondary);
  ImGui::PushStyleColor(ImGuiCol_HeaderHovered,secondaryHover);
  ImGui::PushStyleColor(ImGuiCol_HeaderActive,secondaryActive);
  ImGui::PushStyleColor(ImGuiCol_ResizeGrip,secondary);
  ImGui::PushStyleColor(ImGuiCol_ResizeGripHovered,secondaryHover);
  ImGui::PushStyleColor(ImGuiCol_ResizeGripActive,secondaryActive);
  ImGui::PushStyleColor(ImGuiCol_FrameBg,secondary);
  ImGui::PushStyleColor(ImGuiCol_FrameBgHovered,secondaryHover);
  ImGui::PushStyleColor(ImGuiCol_FrameBgActive,secondaryActive);
  ImGui::PushStyleColor(ImGuiCol_SliderGrab,primaryActive);
  ImGui::PushStyleColor(ImGuiCol_SliderGrabActive,primaryActive);
  ImGui::PushStyleColor(ImGuiCol_TitleBgActive,primary);
  ImGui::PushStyleColor(ImGuiCol_CheckMark,primaryActive);
  ImGui::PushStyleColor(ImGuiCol_TextSelectedBg,secondaryHover);
  ImGui::PushStyleColor(ImGuiCol_Border,border);
  ImGui::PushStyleColor(ImGuiCol_BorderShadow,borderShadow);
}

void FurnaceGUI::popAccentColors() {
  ImGui::PopStyleColor(24);
}

void FurnaceGUI::pushDestColor() {
  pushAccentColors(uiColors[GUI_COLOR_DESTRUCTIVE],uiColors[GUI_COLOR_DESTRUCTIVE],uiColors[GUI_COLOR_DESTRUCTIVE],ImVec4(0.0f,0.0f,0.0f,0.0f));
}

void FurnaceGUI::popDestColor() {
  popAccentColors();
}

void FurnaceGUI::pushWarningColor(bool warnCond, bool errorCond) {
  if (warnColorPushed) {
    logE("warnColorPushed");
    abort();
  }
  if (errorCond) {
    pushAccentColors(uiColors[GUI_COLOR_ERROR],uiColors[GUI_COLOR_ERROR],uiColors[GUI_COLOR_ERROR],ImVec4(0.0f,0.0f,0.0f,0.0f));
    warnColorPushed=true;
  } else if (warnCond) {
    pushAccentColors(uiColors[GUI_COLOR_WARNING],uiColors[GUI_COLOR_WARNING],uiColors[GUI_COLOR_WARNING],ImVec4(0.0f,0.0f,0.0f,0.0f));
    warnColorPushed=true;
  }
}

void FurnaceGUI::popWarningColor() {
  if (warnColorPushed) {
    popAccentColors();
    warnColorPushed=false;
  }
}

#define IGFD_FileStyleByExtension IGFD_FileStyleByExtention

#ifdef _WIN32
#define SYSTEM_FONT_PATH_1 "C:\\Windows\\Fonts\\segoeui.ttf"
#define SYSTEM_FONT_PATH_2 "C:\\Windows\\Fonts\\tahoma.ttf"
#define SYSTEM_FONT_PATH_3 "C:\\Windows\\Fonts\\micross.ttf"
#define SYSTEM_HEAD_FONT_PATH_1 "C:\\Windows\\Fonts\\segoeui.ttf"
#define SYSTEM_HEAD_FONT_PATH_2 "C:\\Windows\\Fonts\\tahoma.ttf"
#define SYSTEM_HEAD_FONT_PATH_3 "C:\\Windows\\Fonts\\micross.ttf"
#define SYSTEM_PAT_FONT_PATH_1 "C:\\Windows\\Fonts\\consola.ttf"
#define SYSTEM_PAT_FONT_PATH_2 "C:\\Windows\\Fonts\\cour.ttf"
// GOOD LUCK WITH THIS ONE - UNTESTED
#define SYSTEM_PAT_FONT_PATH_3 "C:\\Windows\\Fonts\\vgasys.fon"
#elif defined(__APPLE__)
#define SYSTEM_FONT_PATH_1 "/System/Library/Fonts/SFAANS.ttf"
#define SYSTEM_FONT_PATH_2 "/System/Library/Fonts/Helvetica.ttc"
#define SYSTEM_FONT_PATH_3 "/System/Library/Fonts/Helvetica.dfont"
#define SYSTEM_HEAD_FONT_PATH_1 "/System/Library/Fonts/SFAANS.ttf"
#define SYSTEM_HEAD_FONT_PATH_2 "/System/Library/Fonts/Helvetica.ttc"
#define SYSTEM_HEAD_FONT_PATH_3 "/System/Library/Fonts/Helvetica.dfont"
#define SYSTEM_PAT_FONT_PATH_1 "/System/Library/Fonts/SFNSMono.ttf"
#define SYSTEM_PAT_FONT_PATH_2 "/System/Library/Fonts/Courier New.ttf"
#define SYSTEM_PAT_FONT_PATH_3 "/System/Library/Fonts/Courier New.ttf"
#elif defined(ANDROID)
#define SYSTEM_FONT_PATH_1 "/system/fonts/Roboto-Regular.ttf"
#define SYSTEM_FONT_PATH_2 "/system/fonts/DroidSans.ttf"
#define SYSTEM_FONT_PATH_3 "/system/fonts/DroidSans.ttf"
// ???
#define SYSTEM_HEAD_FONT_PATH_1 "/system/fonts/Roboto-Regular.ttf"
#define SYSTEM_HEAD_FONT_PATH_2 "/system/fonts/DroidSans.ttf"
#define SYSTEM_HEAD_FONT_PATH_3 "/system/fonts/DroidSans.ttf"
#define SYSTEM_PAT_FONT_PATH_1 "/system/fonts/RobotoMono-Regular.ttf"
#define SYSTEM_PAT_FONT_PATH_2 "/system/fonts/DroidSansMono.ttf"
#define SYSTEM_PAT_FONT_PATH_3 "/system/fonts/CutiveMono.ttf"
#else
#define SYSTEM_FONT_PATH_1 "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"
#define SYSTEM_FONT_PATH_2 "/usr/share/fonts/TTF/DejaVuSans.ttf"
#define SYSTEM_FONT_PATH_3 "/usr/share/fonts/ubuntu/Ubuntu-R.ttf"
#define SYSTEM_HEAD_FONT_PATH_1 "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"
#define SYSTEM_HEAD_FONT_PATH_2 "/usr/share/fonts/TTF/DejaVuSans.ttf"
#define SYSTEM_HEAD_FONT_PATH_3 "/usr/share/fonts/ubuntu/Ubuntu-R.ttf"
#define SYSTEM_PAT_FONT_PATH_1 "/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf"
#define SYSTEM_PAT_FONT_PATH_2 "/usr/share/fonts/TTF/DejaVuSansMono.ttf"
#define SYSTEM_PAT_FONT_PATH_3 "/usr/share/fonts/ubuntu/UbuntuMono-R.ttf"
#endif

void setupLabel(const char* lStr, char* label, int len) {
  memset(label,0,32);
  for (int i=0, p=0; i<len; i++) {
    signed char cl;
    if (lStr[p]==0) {
      strncat(label," ",32);
    } else {
      decodeUTF8((const unsigned char*)&lStr[p],cl);
      memcpy(label+p,lStr+p,cl);
      p+=cl;
    }
  }
}

void FurnaceGUI::applyUISettings(bool updateFonts) {
  ImGuiStyle sty;

  if (settings.guiColorsBase) {
    ImGui::StyleColorsLight(&sty);
  } else {
    ImGui::StyleColorsDark(&sty);
  }

  if (dpiScale<0.1) dpiScale=0.1;

  setupLabel(settings.noteOffLabel.c_str(),noteOffLabel,3);
  setupLabel(settings.noteRelLabel.c_str(),noteRelLabel,3);
  setupLabel(settings.macroRelLabel.c_str(),macroRelLabel,3);
  setupLabel(settings.emptyLabel.c_str(),emptyLabel,3);
  setupLabel(settings.emptyLabel2.c_str(),emptyLabel2,2);

  if (updateFonts) {
    // get scale factor
    const char* videoBackend=SDL_GetCurrentVideoDriver();
    if (settings.dpiScale>=0.5f) {
      logD("setting UI scale factor from config (%f).",settings.dpiScale);
      dpiScale=settings.dpiScale;
    } else {
      logD("auto-detecting UI scale factor.");
      dpiScale=getScaleFactor(videoBackend,sdlWin);
      logD("scale factor: %f",dpiScale);
      if (dpiScale<0.1f) {
        logW("scale what?");
        dpiScale=1.0f;
      }
    }
  }
  
  // chan osc work pool
  if (chanOscWorkPool!=NULL) {
    delete chanOscWorkPool;
    chanOscWorkPool=NULL;
  }

  for (int i=0; i<64; i++) {
    ImVec4 col1=uiColors[GUI_COLOR_PATTERN_VOLUME_MIN];
    ImVec4 col2=uiColors[GUI_COLOR_PATTERN_VOLUME_HALF];
    ImVec4 col3=uiColors[GUI_COLOR_PATTERN_VOLUME_MAX];
    volColors[i]=ImVec4(col1.x+((col2.x-col1.x)*float(i)/64.0f),
                        col1.y+((col2.y-col1.y)*float(i)/64.0f),
                        col1.z+((col2.z-col1.z)*float(i)/64.0f),
                        1.0f);
    volColors[i+64]=ImVec4(col2.x+((col3.x-col2.x)*float(i)/64.0f),
                           col2.y+((col3.y-col2.y)*float(i)/64.0f),
                           col2.z+((col3.z-col2.z)*float(i)/64.0f),
                           1.0f);
  }

  float hue, sat, val;

  ImVec4 primaryActive=uiColors[GUI_COLOR_ACCENT_PRIMARY];
  ImVec4 primaryHover, primary;
  primaryHover.w=primaryActive.w;
  primary.w=primaryActive.w;
  ImGui::ColorConvertRGBtoHSV(primaryActive.x,primaryActive.y,primaryActive.z,hue,sat,val);
  if (settings.guiColorsBase) {
    primary=primaryActive;
    ImGui::ColorConvertHSVtoRGB(hue,sat*0.9,val*0.9,primaryHover.x,primaryHover.y,primaryHover.z);
    ImGui::ColorConvertHSVtoRGB(hue,sat,val*0.5,primaryActive.x,primaryActive.y,primaryActive.z);
  } else {
    ImGui::ColorConvertHSVtoRGB(hue,sat*0.9,val*0.5,primaryHover.x,primaryHover.y,primaryHover.z);
    ImGui::ColorConvertHSVtoRGB(hue,sat*0.8,val*0.35,primary.x,primary.y,primary.z);
  }

  ImVec4 secondaryActive=uiColors[GUI_COLOR_ACCENT_SECONDARY];
  ImVec4 secondaryHoverActual, secondaryHover, secondary, secondarySemiActive;
  secondarySemiActive.w=secondaryActive.w;
  secondaryHover.w=secondaryActive.w;
  secondary.w=secondaryActive.w;
  ImGui::ColorConvertRGBtoHSV(secondaryActive.x,secondaryActive.y,secondaryActive.z,hue,sat,val);
  if (settings.guiColorsBase) {
    secondary=secondaryActive;
    ImGui::ColorConvertHSVtoRGB(hue,sat*0.9,val*0.7,secondarySemiActive.x,secondarySemiActive.y,secondarySemiActive.z);
    ImGui::ColorConvertHSVtoRGB(hue,sat*0.9,val*0.9,secondaryHover.x,secondaryHover.y,secondaryHover.z);
    ImGui::ColorConvertHSVtoRGB(hue,sat,val*0.5,secondaryActive.x,secondaryActive.y,secondaryActive.z);
  } else {
    ImGui::ColorConvertHSVtoRGB(hue,sat*0.9,val*0.75,secondarySemiActive.x,secondarySemiActive.y,secondarySemiActive.z);
    ImGui::ColorConvertHSVtoRGB(hue,sat*0.9,val*0.5,secondaryHover.x,secondaryHover.y,secondaryHover.z);
    ImGui::ColorConvertHSVtoRGB(hue,sat*0.9,val*0.25,secondary.x,secondary.y,secondary.z);
  }

  secondaryHoverActual=secondaryHover;

  // TODO: improve
  if (mobileUI) { // disable all hovered colors
    primaryHover=primary;
    secondaryHover=secondary;
  }

  sty.Colors[ImGuiCol_WindowBg]=uiColors[GUI_COLOR_FRAME_BACKGROUND];
  sty.Colors[ImGuiCol_ChildBg]=uiColors[GUI_COLOR_FRAME_BACKGROUND_CHILD];
  sty.Colors[ImGuiCol_PopupBg]=uiColors[GUI_COLOR_FRAME_BACKGROUND_POPUP];
  sty.Colors[ImGuiCol_TitleBg]=uiColors[GUI_COLOR_TITLE_INACTIVE];
  sty.Colors[ImGuiCol_TitleBgCollapsed]=uiColors[GUI_COLOR_TITLE_COLLAPSED];
  sty.Colors[ImGuiCol_MenuBarBg]=uiColors[GUI_COLOR_MENU_BAR];
  sty.Colors[ImGuiCol_ModalWindowDimBg]=uiColors[GUI_COLOR_MODAL_BACKDROP];
  sty.Colors[ImGuiCol_ScrollbarBg]=uiColors[GUI_COLOR_SCROLL_BACKGROUND];
  sty.Colors[ImGuiCol_ScrollbarGrab]=uiColors[GUI_COLOR_SCROLL];
  sty.Colors[ImGuiCol_ScrollbarGrabHovered]=uiColors[GUI_COLOR_SCROLL_HOVER];
  sty.Colors[ImGuiCol_ScrollbarGrabActive]=uiColors[GUI_COLOR_SCROLL_ACTIVE];
  sty.Colors[ImGuiCol_Separator]=uiColors[GUI_COLOR_SEPARATOR];
  sty.Colors[ImGuiCol_SeparatorHovered]=uiColors[GUI_COLOR_SEPARATOR_HOVER];
  sty.Colors[ImGuiCol_SeparatorActive]=uiColors[GUI_COLOR_SEPARATOR_ACTIVE];
  sty.Colors[ImGuiCol_DockingPreview]=uiColors[GUI_COLOR_DOCKING_PREVIEW];
  sty.Colors[ImGuiCol_DockingEmptyBg]=uiColors[GUI_COLOR_DOCKING_EMPTY];
  sty.Colors[ImGuiCol_TableHeaderBg]=uiColors[GUI_COLOR_TABLE_HEADER];
  sty.Colors[ImGuiCol_TableBorderStrong]=uiColors[GUI_COLOR_TABLE_BORDER_HARD];
  sty.Colors[ImGuiCol_TableBorderLight]=uiColors[GUI_COLOR_TABLE_BORDER_SOFT];
  sty.Colors[ImGuiCol_DragDropTarget]=uiColors[GUI_COLOR_DRAG_DROP_TARGET];
  sty.Colors[ImGuiCol_NavHighlight]=uiColors[GUI_COLOR_NAV_HIGHLIGHT];
  sty.Colors[ImGuiCol_NavWindowingHighlight]=uiColors[GUI_COLOR_NAV_WIN_HIGHLIGHT];
  sty.Colors[ImGuiCol_NavWindowingDimBg]=uiColors[GUI_COLOR_NAV_WIN_BACKDROP];
  sty.Colors[ImGuiCol_Text]=uiColors[GUI_COLOR_TEXT];
  sty.Colors[ImGuiCol_TextDisabled]=uiColors[GUI_COLOR_TEXT_DISABLED];
  sty.Colors[ImGuiCol_Button]=uiColors[GUI_COLOR_BUTTON];
  sty.Colors[ImGuiCol_ButtonHovered]=uiColors[GUI_COLOR_BUTTON_HOVER];
  sty.Colors[ImGuiCol_ButtonActive]=uiColors[GUI_COLOR_BUTTON_ACTIVE];
  sty.Colors[ImGuiCol_Tab]=uiColors[GUI_COLOR_TAB];
  sty.Colors[ImGuiCol_TabHovered]=uiColors[GUI_COLOR_TAB_HOVER];
  sty.Colors[ImGuiCol_TabActive]=uiColors[GUI_COLOR_TAB_ACTIVE];
  sty.Colors[ImGuiCol_TabUnfocused]=uiColors[GUI_COLOR_TAB_UNFOCUSED];
  sty.Colors[ImGuiCol_TabUnfocusedActive]=uiColors[GUI_COLOR_TAB_UNFOCUSED_ACTIVE];
  sty.Colors[ImGuiCol_Header]=uiColors[GUI_COLOR_IMGUI_HEADER];
  sty.Colors[ImGuiCol_HeaderHovered]=uiColors[GUI_COLOR_IMGUI_HEADER_HOVER];
  sty.Colors[ImGuiCol_HeaderActive]=uiColors[GUI_COLOR_IMGUI_HEADER_ACTIVE];
  sty.Colors[ImGuiCol_ResizeGrip]=uiColors[GUI_COLOR_RESIZE_GRIP];
  sty.Colors[ImGuiCol_ResizeGripHovered]=uiColors[GUI_COLOR_RESIZE_GRIP_HOVER];
  sty.Colors[ImGuiCol_ResizeGripActive]=uiColors[GUI_COLOR_RESIZE_GRIP_ACTIVE];
  sty.Colors[ImGuiCol_FrameBg]=uiColors[GUI_COLOR_WIDGET_BACKGROUND];
  sty.Colors[ImGuiCol_FrameBgHovered]=uiColors[GUI_COLOR_WIDGET_BACKGROUND_HOVER];
  sty.Colors[ImGuiCol_FrameBgActive]=uiColors[GUI_COLOR_WIDGET_BACKGROUND_ACTIVE];
  sty.Colors[ImGuiCol_SliderGrab]=uiColors[GUI_COLOR_SLIDER_GRAB];
  sty.Colors[ImGuiCol_SliderGrabActive]=uiColors[GUI_COLOR_SLIDER_GRAB_ACTIVE];
  sty.Colors[ImGuiCol_TitleBgActive]=uiColors[GUI_COLOR_TITLE_BACKGROUND_ACTIVE];
  sty.Colors[ImGuiCol_CheckMark]=uiColors[GUI_COLOR_CHECK_MARK];
  sty.Colors[ImGuiCol_TextSelectedBg]=uiColors[GUI_COLOR_TEXT_SELECTION];
  sty.Colors[ImGuiCol_PlotLines]=uiColors[GUI_COLOR_PLOT_LINES];
  sty.Colors[ImGuiCol_PlotLinesHovered]=uiColors[GUI_COLOR_PLOT_LINES_HOVER];
  sty.Colors[ImGuiCol_PlotHistogram]=uiColors[GUI_COLOR_PLOT_HISTOGRAM];
  sty.Colors[ImGuiCol_PlotHistogramHovered]=uiColors[GUI_COLOR_PLOT_HISTOGRAM_HOVER];
  sty.Colors[ImGuiCol_TableRowBg]=uiColors[GUI_COLOR_TABLE_ROW_EVEN];
  sty.Colors[ImGuiCol_TableRowBgAlt]=uiColors[GUI_COLOR_TABLE_ROW_ODD];
  sty.Colors[ImGuiCol_Border]=uiColors[GUI_COLOR_BORDER];
  sty.Colors[ImGuiCol_BorderShadow]=uiColors[GUI_COLOR_BORDER_SHADOW];

  if (settings.roundedWindows) sty.WindowRounding=8.0f;
  if (settings.roundedButtons) {
    sty.FrameRounding=6.0f;
    sty.GrabRounding=6.0f;
  }
  if (settings.roundedTabs) sty.TabRounding = 6.0f;
  else sty.TabRounding = 0.0f;

  if (settings.roundedScrollbars) sty.ScrollbarRounding = 6.0f;
  else sty.ScrollbarRounding = 0.0f;

  if (settings.roundedMenus) sty.PopupRounding=8.0f;

  if (settings.frameBorders) {
    sty.FrameBorderSize=1.0f;
  } else {
    sty.FrameBorderSize=0.0f;
  }

  if (settings.doFrameShadingForMultilineText) {
    sty.DoFrameShadingForMultilineText=true;
  } else {
    sty.DoFrameShadingForMultilineText=false;
  }

  if (settings.guiColorsShading>0) {
    sty.FrameShading=(float)settings.guiColorsShading/100.0f;
  }

  if (safeMode) {
    sty.WindowRounding=0.0f;
    sty.FrameRounding=0.0f;
    sty.GrabRounding=0.0f;
    sty.FrameShading=0.0f;
    sty.DoFrameShadingForMultilineText=false;
    sty.AntiAliasedLines=false;
    sty.AntiAliasedLinesUseTex=false;
    sty.AntiAliasedFill=false;

    locale.setLanguage((DivLang)DIV_LANG_ENGLISH);
    initSystemPresets();
  }

  if (mobileUI) {
    sty.FramePadding=ImVec2(8.0f,6.0f);
  }

  sty.ScaleAllSizes(dpiScale);

  ImGui::GetStyle()=sty;
  
  updateSampleTex=true;

  ImGui::GetIO().ConfigInputTrickleEventQueue=settings.eventDelay;
  ImGui::GetIO().ConfigWindowsMoveFromTitleBarOnly=settings.moveWindowTitle;
  ImGui::GetIO().ConfigInertialScrollToleranceSqr=pow(dpiScale*4.0f,2.0f);
  ImGui::GetIO().MouseDoubleClickTime=settings.doubleClickTime;

  for (int i=0; i<256; i++) {
    ImVec4& base=uiColors[GUI_COLOR_PATTERN_EFFECT_PITCH];
    pitchGrad[i]=ImGui::GetColorU32(ImVec4(base.x,base.y,base.z,((float)i/255.0f)*base.w));
  }
  for (int i=0; i<256; i++) {
    ImVec4& base=uiColors[GUI_COLOR_PATTERN_ACTIVE];
    noteGrad[i]=ImGui::GetColorU32(ImVec4(base.x,base.y,base.z,((float)i/255.0f)*base.w));
  }
  for (int i=0; i<256; i++) {
    ImVec4& base=uiColors[GUI_COLOR_PATTERN_EFFECT_PANNING];
    panGrad[i]=ImGui::GetColorU32(ImVec4(base.x,base.y,base.z,((float)i/255.0f)*base.w));
  }
  for (int i=0; i<256; i++) {
    ImVec4& base=uiColors[GUI_COLOR_PATTERN_INS];
    insGrad[i]=ImGui::GetColorU32(ImVec4(base.x,base.y,base.z,((float)i/255.0f)*base.w));
  }
  for (int i=0; i<256; i++) {
    ImVec4& base=volColors[i/2];
    volGrad[i]=ImGui::GetColorU32(ImVec4(base.x,base.y,base.z,((float)i/255.0f)*base.w));
  }
  for (int i=0; i<256; i++) {
    ImVec4& base=uiColors[GUI_COLOR_PATTERN_EFFECT_SYS_PRIMARY];
    sysCmd1Grad[i]=ImGui::GetColorU32(ImVec4(base.x,base.y,base.z,((float)i/255.0f)*base.w));
  }
  for (int i=0; i<256; i++) {
    ImVec4& base=uiColors[GUI_COLOR_PATTERN_EFFECT_SYS_SECONDARY];
    sysCmd2Grad[i]=ImGui::GetColorU32(ImVec4(base.x,base.y,base.z,((float)i/255.0f)*base.w));
  }

  if (updateFonts && !safeMode) {
    // prepare
#ifdef HAVE_FREETYPE
    if (settings.fontBackend==1) {
      ImGui::GetIO().Fonts->FontBuilderIO=ImGuiFreeType::GetBuilderForFreeType();
      ImGui::GetIO().Fonts->FontBuilderFlags&=~(
        ImGuiFreeTypeBuilderFlags_NoHinting|
        ImGuiFreeTypeBuilderFlags_NoAutoHint|
        ImGuiFreeTypeBuilderFlags_ForceAutoHint|
        ImGuiFreeTypeBuilderFlags_LightHinting|
        ImGuiFreeTypeBuilderFlags_MonoHinting|
        ImGuiFreeTypeBuilderFlags_Bold|
        ImGuiFreeTypeBuilderFlags_Oblique|
        ImGuiFreeTypeBuilderFlags_Monochrome|
        ImGuiFreeTypeBuilderFlags_LoadColor|
        ImGuiFreeTypeBuilderFlags_Bitmap
      );

      if (!settings.fontAntiAlias) ImGui::GetIO().Fonts->FontBuilderFlags|=ImGuiFreeTypeBuilderFlags_Monochrome;
      if (settings.fontBitmap) ImGui::GetIO().Fonts->FontBuilderFlags|=ImGuiFreeTypeBuilderFlags_Bitmap;

      switch (settings.fontHinting) {
        case 0: // off
          ImGui::GetIO().Fonts->FontBuilderFlags|=ImGuiFreeTypeBuilderFlags_NoHinting;
          break;
        case 1: // slight
          ImGui::GetIO().Fonts->FontBuilderFlags|=ImGuiFreeTypeBuilderFlags_LightHinting;
          break;
        case 2: // normal
          break;
        case 3: // full
          ImGui::GetIO().Fonts->FontBuilderFlags|=ImGuiFreeTypeBuilderFlags_MonoHinting;
          break;
      }

      switch (settings.fontAutoHint) {
        case 0: // off
          ImGui::GetIO().Fonts->FontBuilderFlags|=ImGuiFreeTypeBuilderFlags_NoAutoHint;
          break;
        case 1: // on
          break;
        case 2: // force
          ImGui::GetIO().Fonts->FontBuilderFlags|=ImGuiFreeTypeBuilderFlags_ForceAutoHint;
          break;
      }
    } else {
      ImGui::GetIO().Fonts->FontBuilderIO=ImFontAtlasGetBuilderForStbTruetype();
    }
#endif


    // set to 800 for now due to problems with unifont
    static const ImWchar upTo800[]={0x20,0x7e,0xa0,0x800,0};
    ImFontGlyphRangesBuilder range;
    ImVector<ImWchar> outRange;

    ImFontConfig fontConf;
    ImFontConfig fontConfP;
    ImFontConfig fontConfB;
    ImFontConfig fontConfH;

    fontConf.OversampleV=1;
    fontConf.OversampleH=2;
    fontConfP.OversampleV=1;
    fontConfP.OversampleH=2;
    fontConfB.OversampleV=1;
    fontConfB.OversampleH=1;
    fontConfH.OversampleV=1;
    fontConfH.OversampleH=1;

    //fontConf.RasterizerMultiply=1.5;
    //fontConfP.RasterizerMultiply=1.5;

    range.AddRanges(upTo800);
    if (settings.loadJapanese) {
      range.AddRanges(ImGui::GetIO().Fonts->GetGlyphRangesJapanese());
    }
    if (settings.loadChinese) {
      range.AddRanges(ImGui::GetIO().Fonts->GetGlyphRangesChineseSimplifiedCommon());
    }
    if (settings.loadChineseTraditional) {
      range.AddRanges(ImGui::GetIO().Fonts->GetGlyphRangesChineseFull());
    }
    if (settings.loadKorean) {
      range.AddRanges(ImGui::GetIO().Fonts->GetGlyphRangesKorean());
    }
    // I'm terribly sorry
    range.UsedChars[0x80>>5]=0;

    range.BuildRanges(&outRange);
    if (fontRange!=NULL) delete[] fontRange;
    fontRange=new ImWchar[outRange.size()];
    int index=0;
    for (ImWchar& i: outRange) {
      fontRange[index++]=i;
    }

    if (settings.mainFont<0 || settings.mainFont>6) settings.mainFont=0;
    if (settings.headFont<0 || settings.headFont>6) settings.headFont=0;
    if (settings.patFont<0 || settings.patFont>6) settings.patFont=0;

    if (settings.mainFont==6 && settings.mainFontPath.empty()) {
      logW("UI font path is empty! reverting to default font");
      settings.mainFont=0;
    }
    if (settings.headFont==6 && settings.headFontPath.empty()) {
      logW("header font path is empty! reverting to default font");
      settings.headFont=0;
    }
    if (settings.patFont==6 && settings.patFontPath.empty()) {
      logW("pattern font path is empty! reverting to default font");
      settings.patFont=0;
    }

    ImFontConfig fc1;
    fc1.MergeMode=true;
    // save memory
    fc1.OversampleH=1;
    fc1.OversampleV=1;

    if (settings.mainFont==6) { // custom font
      if ((mainFont=ImGui::GetIO().Fonts->AddFontFromFileTTF(settings.mainFontPath.c_str(),MAX(1,e->getConfInt("mainFontSize",18)*dpiScale),&fontConf,fontRange))==NULL) {
        logW("could not load UI font! reverting to default font");
        settings.mainFont=0;
        if ((mainFont=ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(builtinFont[settings.mainFont],builtinFontLen[settings.mainFont],MAX(1,e->getConfInt("mainFontSize",18)*dpiScale),&fontConf,fontRange))==NULL) {
          logE("could not load UI font! falling back to Proggy Clean.");
          mainFont=ImGui::GetIO().Fonts->AddFontDefault();
        }
      }
    } else if (settings.mainFont==5) { // system font
      if ((mainFont=ImGui::GetIO().Fonts->AddFontFromFileTTF(SYSTEM_FONT_PATH_1,MAX(1,e->getConfInt("mainFontSize",18)*dpiScale),&fontConf,fontRange))==NULL) {
        if ((mainFont=ImGui::GetIO().Fonts->AddFontFromFileTTF(SYSTEM_FONT_PATH_2,MAX(1,e->getConfInt("mainFontSize",18)*dpiScale),&fontConf,fontRange))==NULL) {
          if ((mainFont=ImGui::GetIO().Fonts->AddFontFromFileTTF(SYSTEM_FONT_PATH_3,MAX(1,e->getConfInt("mainFontSize",18)*dpiScale),&fontConf,fontRange))==NULL) {
            logW("could not load UI font! reverting to default font");
            settings.mainFont=0;
            if ((mainFont=ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(builtinFont[settings.mainFont],builtinFontLen[settings.mainFont],MAX(1,e->getConfInt("mainFontSize",18)*dpiScale),&fontConf,fontRange))==NULL) {
              logE("could not load UI font! falling back to Proggy Clean.");
              mainFont=ImGui::GetIO().Fonts->AddFontDefault();
            }
          }
        }
      }
    } else {
      if ((mainFont=ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(builtinFont[settings.mainFont],builtinFontLen[settings.mainFont],MAX(1,e->getConfInt("mainFontSize",18)*dpiScale),&fontConf,fontRange))==NULL) {
        logE("could not load UI font! falling back to Proggy Clean.");
        mainFont=ImGui::GetIO().Fonts->AddFontDefault();
      }
    }

    // two fallback fonts
    mainFont=ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(font_liberationSans_compressed_data,font_liberationSans_compressed_size,MAX(1,e->getConfInt("mainFontSize",18)*dpiScale),&fc1,fontRange);
    mainFont=ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(font_unifont_compressed_data,font_unifont_compressed_size,MAX(1,e->getConfInt("mainFontSize",18)*dpiScale),&fc1,fontRange);

    ImFontConfig fc;
    fc.MergeMode=true;
    fc.OversampleH=1;
    fc.OversampleV=1;
    fc.PixelSnapH=true;
    fc.GlyphMinAdvanceX=e->getConfInt("iconSize",16)*dpiScale;
    static const ImWchar fontRangeIcon[]={ICON_MIN_FA,ICON_MAX_FA,0};
    if ((iconFont=ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(iconFont_compressed_data,iconFont_compressed_size,MAX(1,e->getConfInt("iconSize",16)*dpiScale),&fc,fontRangeIcon))==NULL) {
      logE("could not load icon font!");
    }

    static const ImWchar fontRangeFurIcon[]={ICON_MIN_FUR,ICON_MAX_FUR,0};
    if ((furIconFont=ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(furIcons_compressed_data,furIcons_compressed_size,MAX(1,e->getConfInt("iconSize",16)*dpiScale),&fc,fontRangeFurIcon))==NULL) {
      logE("could not load Furnace icons font!");
    }

    if (settings.mainFontSize==settings.patFontSize && settings.patFont<5 && builtinFontM[settings.patFont]==builtinFont[settings.mainFont]) {
      logD("using main font for pat font.");
      patFont=mainFont;
    } else {
      if (settings.patFont==6) { // custom font
        if ((patFont=ImGui::GetIO().Fonts->AddFontFromFileTTF(settings.patFontPath.c_str(),MAX(1,e->getConfInt("patFontSize",18)*dpiScale),&fontConfP,upTo800))==NULL) {
          logW("could not load pattern font! reverting to default font");
          settings.patFont=0;
          if ((patFont=ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(builtinFontM[settings.patFont],builtinFontMLen[settings.patFont],MAX(1,e->getConfInt("patFontSize",18)*dpiScale),&fontConfP,upTo800))==NULL) {
            logE("could not load pattern font! falling back to Proggy Clean.");
            patFont=ImGui::GetIO().Fonts->AddFontDefault();
          }
        }
      } else if (settings.patFont==5) { // system font
        if ((patFont=ImGui::GetIO().Fonts->AddFontFromFileTTF(SYSTEM_PAT_FONT_PATH_1,MAX(1,e->getConfInt("patFontSize",18)*dpiScale),&fontConfP,upTo800))==NULL) {
          if ((patFont=ImGui::GetIO().Fonts->AddFontFromFileTTF(SYSTEM_PAT_FONT_PATH_2,MAX(1,e->getConfInt("patFontSize",18)*dpiScale),&fontConfP,upTo800))==NULL) {
            if ((patFont=ImGui::GetIO().Fonts->AddFontFromFileTTF(SYSTEM_PAT_FONT_PATH_3,MAX(1,e->getConfInt("patFontSize",18)*dpiScale),&fontConfP,upTo800))==NULL) {
              logW("could not load pattern font! reverting to default font");
              settings.patFont=0;
              if ((patFont=ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(builtinFontM[settings.patFont],builtinFontMLen[settings.patFont],MAX(1,e->getConfInt("patFontSize",18)*dpiScale),&fontConfP,upTo800))==NULL) {
                logE("could not load pattern font! falling back to Proggy Clean.");
                patFont=ImGui::GetIO().Fonts->AddFontDefault();
              }
            }
          }
        }
      } else {
        if ((patFont=ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(builtinFontM[settings.patFont],builtinFontMLen[settings.patFont],MAX(1,e->getConfInt("patFontSize",18)*dpiScale),&fontConfP,upTo800))==NULL) {
          logE("could not load pattern font!");
          patFont=ImGui::GetIO().Fonts->AddFontDefault();
        }
      }
    }

    // 0x39B = Λ
    //static const ImWchar bigFontRange[]={0x20,0xFF,0x39b,0x39b,0};

    if(settings.language == DIV_LANG_RUSSIAN)
    {
      static const ImWchar bigFontRangeRus[] = {0x20,0xFF,0x39b,0x39b,0x400,0x451,0};
      if ((bigFont = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(font_plexSans_compressed_data, font_plexSans_compressed_size, MAX(1, 40 * dpiScale), &fontConfB, bigFontRangeRus)) == NULL) {
        logE("could not load big UI font for Russian language!");
      }
    }
    else
    {
      static const ImWchar bigFontRange[] = { 0x20,0xFF,0x39b,0x39b,0 };
      if ((bigFont = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(font_plexSans_compressed_data, font_plexSans_compressed_size, MAX(1, 40 * dpiScale), &fontConfB, bigFontRange)) == NULL) {
        logE("could not load big UI font!");
      }
    }

    if (settings.mainFontSize==settings.headFontSize && settings.headFont<5 && builtinFont[settings.headFont]==builtinFont[settings.mainFont]) {
      logD("using main font for header font.");
      headFont=mainFont;
    } else {
      if (settings.headFont==6) { // custom font
        if ((headFont=ImGui::GetIO().Fonts->AddFontFromFileTTF(settings.headFontPath.c_str(),MAX(1,e->getConfInt("headFontSize",27)*dpiScale),&fontConfH,upTo800))==NULL) {
          logW("could not load header font! reverting to default font");
          settings.headFont=0;
          if ((headFont=ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(builtinFont[settings.headFont],builtinFontLen[settings.headFont],MAX(1,e->getConfInt("headFontSize",27)*dpiScale),&fontConfH,upTo800))==NULL) {
            logE("could not load header font! falling back to IBM Plex Sans.");
            headFont=ImGui::GetIO().Fonts->AddFontDefault();
          }
        }
      } else if (settings.headFont==5) { // system font
        if ((headFont=ImGui::GetIO().Fonts->AddFontFromFileTTF(SYSTEM_HEAD_FONT_PATH_1,MAX(1,e->getConfInt("headFontSize",27)*dpiScale),&fontConfH,upTo800))==NULL) {
          if ((headFont=ImGui::GetIO().Fonts->AddFontFromFileTTF(SYSTEM_HEAD_FONT_PATH_2,MAX(1,e->getConfInt("headFontSize",27)*dpiScale),&fontConfH,upTo800))==NULL) {
            if ((headFont=ImGui::GetIO().Fonts->AddFontFromFileTTF(SYSTEM_HEAD_FONT_PATH_3,MAX(1,e->getConfInt("headFontSize",27)*dpiScale),&fontConfH,upTo800))==NULL) {
              logW("could not load header font! reverting to default font");
              settings.headFont=0;
              if ((headFont=ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(builtinFont[settings.headFont],builtinFontLen[settings.headFont],MAX(1,e->getConfInt("headFontSize",27)*dpiScale),&fontConfH,upTo800))==NULL) {
                logE("could not load header font! falling back to IBM Plex Sans.");
                headFont=ImGui::GetIO().Fonts->AddFontDefault();
              }
            }
          }
        }
      } else {
        if ((headFont=ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(builtinFont[settings.headFont],builtinFontLen[settings.headFont],MAX(1,e->getConfInt("headFontSize",27)*dpiScale),&fontConfH,upTo800))==NULL) {
          logE("could not load header font!");
          headFont=ImGui::GetIO().Fonts->AddFontDefault();
        }
      }
    }

    mainFont->FallbackChar='?';
    mainFont->EllipsisChar='.';
    mainFont->EllipsisCharCount=3;
  } else if (updateFonts) {
    // safe mode
    mainFont=ImGui::GetIO().Fonts->AddFontDefault();
    patFont=mainFont;
    bigFont=mainFont;
    headFont=mainFont;

    mainFont->FallbackChar='?';
    mainFont->EllipsisChar='.';
    mainFont->EllipsisCharCount=3;
  }

  ImGuiFileDialog::Instance()->SetFileStyle(IGFD_FileStyleByTypeDir,"",uiColors[GUI_COLOR_FILE_DIR],ICON_FA_FOLDER_O);
  ImGuiFileDialog::Instance()->SetFileStyle(IGFD_FileStyleByTypeFile,"",uiColors[GUI_COLOR_FILE_OTHER],ICON_FA_FILE_O);
  ImGuiFileDialog::Instance()->SetFileStyle(IGFD_FileStyleByExtension,".fur",uiColors[GUI_COLOR_FILE_SONG_NATIVE],ICON_FA_FILE);
  ImGuiFileDialog::Instance()->SetFileStyle(IGFD_FileStyleByExtension,".fui",uiColors[GUI_COLOR_FILE_INSTR],ICON_FA_FILE);
  ImGuiFileDialog::Instance()->SetFileStyle(IGFD_FileStyleByExtension,".fuw",uiColors[GUI_COLOR_FILE_WAVE],ICON_FA_FILE);
  ImGuiFileDialog::Instance()->SetFileStyle(IGFD_FileStyleByExtension,".dmf",uiColors[GUI_COLOR_FILE_SONG_NATIVE],ICON_FA_FILE);
  ImGuiFileDialog::Instance()->SetFileStyle(IGFD_FileStyleByExtension,".dmp",uiColors[GUI_COLOR_FILE_INSTR],ICON_FA_FILE);
  ImGuiFileDialog::Instance()->SetFileStyle(IGFD_FileStyleByExtension,".dmw",uiColors[GUI_COLOR_FILE_WAVE],ICON_FA_FILE);
  ImGuiFileDialog::Instance()->SetFileStyle(IGFD_FileStyleByExtension,".wav",uiColors[GUI_COLOR_FILE_AUDIO],ICON_FA_FILE_AUDIO_O);
  ImGuiFileDialog::Instance()->SetFileStyle(IGFD_FileStyleByExtension,".dmc",uiColors[GUI_COLOR_FILE_AUDIO],ICON_FA_FILE_AUDIO_O);
  ImGuiFileDialog::Instance()->SetFileStyle(IGFD_FileStyleByExtension,".brr",uiColors[GUI_COLOR_FILE_AUDIO],ICON_FA_FILE_AUDIO_O);
  ImGuiFileDialog::Instance()->SetFileStyle(IGFD_FileStyleByExtension,".vgm",uiColors[GUI_COLOR_FILE_VGM],ICON_FA_FILE_AUDIO_O);
  ImGuiFileDialog::Instance()->SetFileStyle(IGFD_FileStyleByExtension,".zsm",uiColors[GUI_COLOR_FILE_ZSM],ICON_FA_FILE_AUDIO_O);
  ImGuiFileDialog::Instance()->SetFileStyle(IGFD_FileStyleByExtension,".ttf",uiColors[GUI_COLOR_FILE_FONT],ICON_FA_FONT);
  ImGuiFileDialog::Instance()->SetFileStyle(IGFD_FileStyleByExtension,".otf",uiColors[GUI_COLOR_FILE_FONT],ICON_FA_FONT);
  ImGuiFileDialog::Instance()->SetFileStyle(IGFD_FileStyleByExtension,".ttc",uiColors[GUI_COLOR_FILE_FONT],ICON_FA_FONT);
  ImGuiFileDialog::Instance()->SetFileStyle(IGFD_FileStyleByExtension,".dfont",uiColors[GUI_COLOR_FILE_FONT],ICON_FA_FONT);
  ImGuiFileDialog::Instance()->SetFileStyle(IGFD_FileStyleByExtension,".fon",uiColors[GUI_COLOR_FILE_FONT],ICON_FA_FONT);
  ImGuiFileDialog::Instance()->SetFileStyle(IGFD_FileStyleByExtension,".pcf",uiColors[GUI_COLOR_FILE_FONT],ICON_FA_FONT);
  ImGuiFileDialog::Instance()->SetFileStyle(IGFD_FileStyleByExtension,".psf",uiColors[GUI_COLOR_FILE_FONT],ICON_FA_FONT);

  ImGuiFileDialog::Instance()->SetFileStyle(IGFD_FileStyleByExtension,".mod",uiColors[GUI_COLOR_FILE_SONG_IMPORT],ICON_FA_FILE);
  ImGuiFileDialog::Instance()->SetFileStyle(IGFD_FileStyleByExtension,".fc13",uiColors[GUI_COLOR_FILE_SONG_IMPORT],ICON_FA_FILE);
  ImGuiFileDialog::Instance()->SetFileStyle(IGFD_FileStyleByExtension,".fc14",uiColors[GUI_COLOR_FILE_SONG_IMPORT],ICON_FA_FILE);
  ImGuiFileDialog::Instance()->SetFileStyle(IGFD_FileStyleByExtension,".fc",uiColors[GUI_COLOR_FILE_SONG_IMPORT],ICON_FA_FILE);
  ImGuiFileDialog::Instance()->SetFileStyle(IGFD_FileStyleByExtension,".smod",uiColors[GUI_COLOR_FILE_SONG_IMPORT],ICON_FA_FILE);
  ImGuiFileDialog::Instance()->SetFileStyle(IGFD_FileStyleByExtension,".ftm",uiColors[GUI_COLOR_FILE_SONG_IMPORT],ICON_FA_FILE);

  ImGuiFileDialog::Instance()->SetFileStyle(IGFD_FileStyleByExtension,".tfi",uiColors[GUI_COLOR_FILE_INSTR],ICON_FA_FILE);
  ImGuiFileDialog::Instance()->SetFileStyle(IGFD_FileStyleByExtension,".vgi",uiColors[GUI_COLOR_FILE_INSTR],ICON_FA_FILE);
  ImGuiFileDialog::Instance()->SetFileStyle(IGFD_FileStyleByExtension,".s3i",uiColors[GUI_COLOR_FILE_INSTR],ICON_FA_FILE);
  ImGuiFileDialog::Instance()->SetFileStyle(IGFD_FileStyleByExtension,".sbi",uiColors[GUI_COLOR_FILE_INSTR],ICON_FA_FILE);
  ImGuiFileDialog::Instance()->SetFileStyle(IGFD_FileStyleByExtension,".opli",uiColors[GUI_COLOR_FILE_INSTR],ICON_FA_FILE);
  ImGuiFileDialog::Instance()->SetFileStyle(IGFD_FileStyleByExtension,".opni",uiColors[GUI_COLOR_FILE_INSTR],ICON_FA_FILE);
  ImGuiFileDialog::Instance()->SetFileStyle(IGFD_FileStyleByExtension,".y12",uiColors[GUI_COLOR_FILE_INSTR],ICON_FA_FILE);
  ImGuiFileDialog::Instance()->SetFileStyle(IGFD_FileStyleByExtension,".bnk",uiColors[GUI_COLOR_FILE_INSTR],ICON_FA_FILE);
  ImGuiFileDialog::Instance()->SetFileStyle(IGFD_FileStyleByExtension,".fti",uiColors[GUI_COLOR_FILE_INSTR],ICON_FA_FILE);
  ImGuiFileDialog::Instance()->SetFileStyle(IGFD_FileStyleByExtension,".bti",uiColors[GUI_COLOR_FILE_INSTR],ICON_FA_FILE);
  ImGuiFileDialog::Instance()->SetFileStyle(IGFD_FileStyleByExtension,".ff",uiColors[GUI_COLOR_FILE_INSTR],ICON_FA_FILE);
  ImGuiFileDialog::Instance()->SetFileStyle(IGFD_FileStyleByExtension,".opm",uiColors[GUI_COLOR_FILE_INSTR],ICON_FA_FILE);

  if (updateFonts) {
    if (fileDialog!=NULL) delete fileDialog;
    fileDialog=new FurnaceGUIFileDialog(settings.sysFileDialog);

    fileDialog->mobileUI=mobileUI;
  }
}
