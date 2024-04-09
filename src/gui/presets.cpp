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
#include "../baseutils.h"
#include "../fileutils.h"
#include <fmt/printf.h>
#include <imgui.h>

// add system configurations here.
// every entry is written in the following format:
//   ENTRY(
//     "System Name", {
//      CH(DIV_SYSTEM_???, Volume, Panning, Flags),
//      CH(DIV_SYSTEM_???, Volume, Panning, Flags),
//      ...
//     }
//   );
// flags are a string of new line-separated values.
// use SUB_ENTRY instead of ENTRY to add sub-entries to the previous entry.

#define CH FurnaceGUISysDefChip
#define CATEGORY_BEGIN(x,y) cat=FurnaceGUISysCategory(x,y);
#define CATEGORY_END sysCategories.push_back(cat);
#define ENTRY(...) \
  cat.systems.push_back(FurnaceGUISysDef(__VA_ARGS__));

void FurnaceGUI::initSystemPresets() {
  sysCategories.clear();

  FurnaceGUISysCategory cat;

  CATEGORY_BEGIN(_L("Game consoles##sgpr"),_L("let's play some chiptune making games!##sgpr"));
  ENTRY(
    "Sega Genesis", {
      CH(DIV_SYSTEM_YM2612, 1.0f, 0, ""),
      CH(DIV_SYSTEM_SMS, 0.5f, 0, "")
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("Sega Genesis (extended channel 3)##sgpr"), {
      CH(DIV_SYSTEM_YM2612_EXT, 1.0f, 0, ""),
      CH(DIV_SYSTEM_SMS, 0.5f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Sega Genesis (CSM)", {
      CH(DIV_SYSTEM_YM2612_CSM, 1.0f, 0, ""),
      CH(DIV_SYSTEM_SMS, 0.5f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Sega Genesis (DualPCM)", {
      CH(DIV_SYSTEM_YM2612_DUALPCM, 1.0f, 0, ""),
      CH(DIV_SYSTEM_SMS, 0.5f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Sega Genesis (DualPCM, extended channel 3)##sgpr"), {
      CH(DIV_SYSTEM_YM2612_DUALPCM_EXT, 1.0f, 0, ""),
      CH(DIV_SYSTEM_SMS, 0.5f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Sega Genesis (with Sega CD)##sgpr"), {
      CH(DIV_SYSTEM_YM2612, 1.0f, 0, ""),
      CH(DIV_SYSTEM_SMS, 0.5f, 0, ""),
      CH(DIV_SYSTEM_RF5C68, 1.0f, 0,
        "clockSel=2\n"
        "chipType=1\n"
      )
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Sega Genesis (extended channel 3 with Sega CD)##sgpr"), {
      CH(DIV_SYSTEM_YM2612_EXT, 1.0f, 0, ""),
      CH(DIV_SYSTEM_SMS, 0.5f, 0, ""),
      CH(DIV_SYSTEM_RF5C68, 1.0f, 0,
        "clockSel=2\n"
        "chipType=1\n"
      )
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Sega Genesis (CSM with Sega CD)##sgpr"), {
      CH(DIV_SYSTEM_YM2612_CSM, 1.0f, 0, ""),
      CH(DIV_SYSTEM_SMS, 0.5f, 0, ""),
      CH(DIV_SYSTEM_RF5C68, 1.0f, 0,
        "clockSel=2\n"
        "chipType=1\n"
      )
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "Sega Master System", {
      CH(DIV_SYSTEM_SMS, 1.0f, 0, "")
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("Sega Master System (with FM expansion)##sgpr"), {
      CH(DIV_SYSTEM_SMS, 1.0f, 0, ""),
      CH(DIV_SYSTEM_OPLL, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Sega Master System (with FM expansion in drums mode)##sgpr"), {
      CH(DIV_SYSTEM_SMS, 1.0f, 0, ""),
      CH(DIV_SYSTEM_OPLL_DRUMS, 1.0f, 0, "")
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "Sega Game Gear", {
      CH(DIV_SYSTEM_SMS, 1.0f, 0, "chipType=3")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Game Boy", {
      CH(DIV_SYSTEM_GB, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Game Boy Advance (no software mixing)##sgpr"), {
      CH(DIV_SYSTEM_GB, 1.0f, 0, "chipType=3"),
      CH(DIV_SYSTEM_GBA_DMA, 0.5f, 0, ""),
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Game Boy Advance (with MinMod)##sgpr"), {
      CH(DIV_SYSTEM_GB, 1.0f, 0, "chipType=3"),
      CH(DIV_SYSTEM_GBA_MINMOD, 0.5f, 0, ""),
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Neo Geo Pocket", {
      CH(DIV_SYSTEM_T6W28, 1.0f, 0, ""),
      CH(DIV_SYSTEM_PCM_DAC, 1.0f, -1.0f, 
        "rate=11025\n"
        "outDepth=5\n"
      ),
      CH(DIV_SYSTEM_PCM_DAC, 1.0f, 1.0f, 
        "rate=11025\n"
        "outDepth=5\n"
      ) // don't know what the actual sample rate is
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "NEC PC Engine/TurboGrafx-16", {
      CH(DIV_SYSTEM_PCE, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "NES/Famicom", {
      CH(DIV_SYSTEM_NES, 1.0f, 0, "")
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("Famicom with Konami VRC6##sgpr"), {
      CH(DIV_SYSTEM_NES, 1.0f, 0, ""),
      CH(DIV_SYSTEM_VRC6, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Famicom with Konami VRC7##sgpr0"), {
      CH(DIV_SYSTEM_NES, 1.0f, 0, ""),
      CH(DIV_SYSTEM_VRC7, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Famicom with MMC5##sgpr"), {
      CH(DIV_SYSTEM_NES, 1.0f, 0, ""),
      CH(DIV_SYSTEM_MMC5, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Famicom with Sunsoft 5B##sgpr"), {
      CH(DIV_SYSTEM_NES, 1.0f, 0, ""),
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "chipType=2")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Famicom with Namco 163##sgpr"), {
      CH(DIV_SYSTEM_NES, 1.0f, 0, ""),
      CH(DIV_SYSTEM_N163, 1.0f, 0, "channels=7")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Famicom Disk System", {
      CH(DIV_SYSTEM_NES, 1.0f, 0, ""),
      CH(DIV_SYSTEM_FDS, 1.0f, 0, "")
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "SNES", {
      CH(DIV_SYSTEM_SNES, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Mattel Intellivision", {
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "chipType=3")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Vectrex", {
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "clockSel=4")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Neo Geo AES", {
      CH(DIV_SYSTEM_YM2610_FULL, 1.0f, 0, "clockSel=1")
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("Neo Geo AES (extended channel 2)##sgpr"), {
      CH(DIV_SYSTEM_YM2610_FULL_EXT, 1.0f, 0, "clockSel=1")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Neo Geo AES (extended channel 2 and CSM)##sgpr"), {
      CH(DIV_SYSTEM_YM2610_CSM, 1.0f, 0, "clockSel=1")
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "Atari 2600/7800", {
      CH(DIV_SYSTEM_TIA, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Atari 7800 + Ballblazer/Commando", {
      CH(DIV_SYSTEM_TIA, 1.0f, 0, ""),
      CH(DIV_SYSTEM_POKEY, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Atari Lynx", {
      CH(DIV_SYSTEM_LYNX, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "WonderSwan", {
      CH(DIV_SYSTEM_SWAN, 1.0f, 0, "")
    },
    "tickRate=75.47169811320754716981"
  );
  ENTRY(
    "Virtual Boy", {
      CH(DIV_SYSTEM_VBOY, 1.0f, 0, "")
    },
    "tickRate=50.2734877734878"
  );
  ENTRY(
    "Gamate", {
      CH(DIV_SYSTEM_AY8910, 1.0f, 0,
        "clockSel=9\n"
        "chipType=0\n"
        "stereo=true\n"
      )
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Pokémon Mini", {
      CH(DIV_SYSTEM_POKEMINI, 0.5f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Tiger Game.com", {
      CH(DIV_SYSTEM_SM8521, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Casio PV-1000", {
      CH(DIV_SYSTEM_PV1000, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Nintendo DS (NDS)", {
      CH(DIV_SYSTEM_NDS, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Game Boy Advance (DMA)", {
      CH(DIV_SYSTEM_GBA_DMA, 1.0f, 0, "")
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    "Game Boy Advance (MinMod)", {
      CH(DIV_SYSTEM_GBA_MINMOD, 1.0f, 0, "")
    }, NULL, MENU_STATUS_LIST_END
  );
  CATEGORY_END;

  CATEGORY_BEGIN(_L("Computers##sgpr"),_L("let's get to work on chiptune today.##sgpr"));
  ENTRY(
    "Commodore PET", {
      CH(DIV_SYSTEM_PET, 1.0f, 0, "")
    },
    "tickRate=50",
    MENU_STATUS_USUAL
  );
  ENTRY(
    "Commodore VIC-20", {
      CH(DIV_SYSTEM_VIC20, 1.0f, 0, "clockSel=1")
    },
    "tickRate=50",
    MENU_STATUS_USUAL
  );
  ENTRY(
    "Commodore Plus/4", {
      CH(DIV_SYSTEM_TED, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Commodore 64 (C64, 6581 SID)", {
      CH(DIV_SYSTEM_C64_6581, 1.0f, 0, "clockSel=1")
    },
    "tickRate=50.1245421",
    MENU_STATUS_LIST_START
  );
  ENTRY(
    "Commodore 64 (C64, 8580 SID)", {
      CH(DIV_SYSTEM_C64_8580, 1.0f, 0, "clockSel=1")
    },
    "tickRate=50.1245421",
    MENU_STATUS_USUAL
  );
  ENTRY(
    "Commodore 64 (C64, 6581 SID + Sound Expander)", {
      CH(DIV_SYSTEM_C64_6581, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_OPL, 1.0f, 0, "")
    },
    "tickRate=50.1245421"
  );
  ENTRY(
    _L("Commodore 64 (C64, 6581 SID + Sound Expander in drums mode)##sgpr"), {
      CH(DIV_SYSTEM_C64_6581, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_OPL_DRUMS, 1.0f, 0, "")
    },
    "tickRate=50.1245421"
  );
  ENTRY(
    "Commodore 64 (C64, 8580 SID + Sound Expander)", {
      CH(DIV_SYSTEM_C64_8580, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_OPL, 1.0f, 0, "")
    },
    "tickRate=50.1245421"
  );
  ENTRY(
    _L("Commodore 64 (C64, 8580 SID + Sound Expander in drums mode)##sgpr"), {
      CH(DIV_SYSTEM_C64_8580, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_OPL_DRUMS, 1.0f, 0, "")
    },
    "tickRate=50.1245421"
  );
  ENTRY(
    "Commodore 64 (C64, 6581 SID + FM-YAM)", {
      CH(DIV_SYSTEM_C64_6581, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_OPL2, 1.0f, 0, "")
    },
    "tickRate=50.1245421"
  );
  ENTRY(
    _L("Commodore 64 (C64, 6581 SID + FM-YAM in drums mode)##sgpr"), {
      CH(DIV_SYSTEM_C64_6581, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_OPL2_DRUMS, 1.0f, 0, "")
    },
    "tickRate=50.1245421"
  );
  ENTRY(
    "Commodore 64 (C64, 8580 SID + FM-YAM)", {
      CH(DIV_SYSTEM_C64_8580, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_OPL2, 1.0f, 0, "")
    },
    "tickRate=50.1245421"
  );
  ENTRY(
    _L("Commodore 64 (C64, 8580 SID + FM-YAM in drums mode)##sgpr"), {
      CH(DIV_SYSTEM_C64_8580, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_OPL2_DRUMS, 1.0f, 0, "")
    },
    "tickRate=50.1245421",
    MENU_STATUS_LIST_END
  );
  ENTRY(
    "Amiga", {
      CH(DIV_SYSTEM_AMIGA, 1.0f, 0, "clockSel=1")
    },
    "tickRate=50"
  );
  ENTRY(
    "MSX", {
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "clockSel=0\nchipType=1")
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    "MSX + SFG-01", {
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "chipType=1"),
      CH(DIV_SYSTEM_YM2151, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "MSX + MSX-AUDIO", {
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "chipType=1"),
      CH(DIV_SYSTEM_Y8950, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("MSX + MSX-AUDIO (drums mode)##sgpr"), {
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "chipType=1"),
      CH(DIV_SYSTEM_Y8950_DRUMS, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "MSX + MSX-MUSIC", {
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "chipType=1"),
      CH(DIV_SYSTEM_OPLL, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("MSX + MSX-MUSIC (drums mode)##sgpr"), {
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "chipType=1"),
      CH(DIV_SYSTEM_OPLL_DRUMS, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "MSX + Darky", {
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "chipType=1"),
      CH(DIV_SYSTEM_AY8930, 1.0f, 0,
        "clockSel=11\n"
        "halfClock=true\n"
      ), // 3.58MHz
      CH(DIV_SYSTEM_AY8930, 1.0f, 0,
        "clockSel=11\n"
        "halfClock=true\n"
      ) // 3.58MHz or 3.6MHz selectable via register
      // per-channel mixer (soft panning, post processing) isn't emulated at all
    }, NULL, MENU_STATUS_USUAL
  );
    ENTRY(
    "MSX + Playsoniq", {
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "chipType=1"),
      CH(DIV_SYSTEM_SMS, 1.0f, 0, ""), // Sega VDP
      CH(DIV_SYSTEM_C64_8580, 1.0f, 0, ""),
      CH(DIV_SYSTEM_SCC_PLUS, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "MSX + SCC", {
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "chipType=1"),
      CH(DIV_SYSTEM_SCC, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "MSX + SCC+", {
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "chipType=1"),
      CH(DIV_SYSTEM_SCC_PLUS, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "MSX + Neotron", {
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "chipType=1"),
      CH(DIV_SYSTEM_YM2610_FULL, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("MSX + Neotron (extended channel 2)##sgpr"), {
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "chipType=1"),
      CH(DIV_SYSTEM_YM2610_FULL_EXT, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("MSX + Neotron (extended channel 2 and CSM)##sgpr"), {
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "chipType=1"),
      CH(DIV_SYSTEM_YM2610_CSM, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("MSX + Neotron (with YM2610B)##sgpr"), {
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "chipType=1"),
      CH(DIV_SYSTEM_YM2610B, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("MSX + Neotron (with YM2610B; extended channel 3)##sgpr"), {
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "chipType=1"),
      CH(DIV_SYSTEM_YM2610B_EXT, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("MSX + Neotron (with YM2610B; extended channel 3 and CSM)##sgpr"), {
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "chipType=1"),
      CH(DIV_SYSTEM_YM2610B_CSM, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "MSX + SIMPL", {
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "chipType=1"),
      CH(DIV_SYSTEM_PCM_DAC, 1.0f, 0,
        "rate=55930\n"
        "outDepth=7\n"
      ) // variable rate, Mono DAC
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    _L("NEC PC-88 (with PC-8801-10)##sgpr"), {
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "clockSel=15"), // external
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "clockSel=15") // ""
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("NEC PC-88 (with PC-8801-11)##sgpr"), {
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2203, 1.0f, 0, "clockSel=4") // external
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-88 (with PC-8801-11; extended channel 3)##sgpr"), {
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2203_EXT, 1.0f, 0, "clockSel=4") // external
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-88 (with PC-8801-11; extended channel 3 and CSM)##sgpr"), {
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2203_CSM, 1.0f, 0, "clockSel=4") // external
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-88 (with PC-8801-23)##sgpr"), {
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2608, 1.0f, 0, "clockSel=1") // external
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-88 (with PC-8801-23; extended channel 3)##sgpr"), {
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2608_EXT, 1.0f, 0, "clockSel=1") // external
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-88 (with PC-8801-23; extended channel 3 and CSM)##sgpr"), {
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2608_CSM, 1.0f, 0, "clockSel=1") // external
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-88 (with HMB-20 HIBIKI-8800)##sgpr"), {
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2151, 1.0f, 0, "clockSel=2") // external; 4.0000MHz
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    _L("NEC PC-8801mk2SR (with PC-8801-10)##sgpr"), {
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2203, 1.0f, 0, "clockSel=4"), // internal
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "clockSel=15"), // external
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "clockSel=15") // ""
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("NEC PC-8801mk2SR (with PC-8801-10; extended channel 3)##sgpr"), {
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2203_EXT, 1.0f, 0, "clockSel=4"), // internal
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "clockSel=15"), // external
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "clockSel=15") // ""
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-8801mk2SR (with PC-8801-10; extended channel 3 and CSM)##sgpr"), {
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2203_CSM, 1.0f, 0, "clockSel=4"), // internal
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "clockSel=15"), // external
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "clockSel=15") // ""
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-8801mk2SR (with PC-8801-11)##sgpr"), {
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2203, 1.0f, 0, "clockSel=4"), // internal
      CH(DIV_SYSTEM_YM2203, 1.0f, 0, "clockSel=4") // external
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-8801mk2SR (with PC-8801-11; extended channel 3 on internal OPN)##sgpr"), {
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2203_EXT, 1.0f, 0, "clockSel=4"), // internal
      CH(DIV_SYSTEM_YM2203, 1.0f, 0, "clockSel=4") // external
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-8801mk2SR (with PC-8801-11; extended channel 3 on external OPN)##sgpr"), {
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2203, 1.0f, 0, "clockSel=4"), // internal
      CH(DIV_SYSTEM_YM2203_EXT, 1.0f, 0, "clockSel=4") // external
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-8801mk2SR (with PC-8801-11; extended channel 3 on both OPNs)##sgpr"), {
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2203_EXT, 1.0f, 0, "clockSel=4"), // internal
      CH(DIV_SYSTEM_YM2203_EXT, 1.0f, 0, "clockSel=4") // external
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-8801mk2SR (with PC-8801-11; extended channel 3 and CSM on both OPNs)##sgpr"), {
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2203_CSM, 1.0f, 0, "clockSel=4"), // internal
      CH(DIV_SYSTEM_YM2203_CSM, 1.0f, 0, "clockSel=4") // external
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-8801mk2SR (with PC-8801-23)##sgpr"), {
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2203, 1.0f, 0, "clockSel=4"), // internal
      CH(DIV_SYSTEM_YM2608, 1.0f, 0, "clockSel=1") // external
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-8801mk2SR (with PC-8801-23; extended channel 3 on internal OPN)##sgpr"), {
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2203_EXT, 1.0f, 0, "clockSel=4"), // internal
      CH(DIV_SYSTEM_YM2608, 1.0f, 0, "clockSel=1") // external
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-8801mk2SR (with PC-8801-23; extended channel 3 and CSM on internal OPN)##sgpr"), {
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2203_CSM, 1.0f, 0, "clockSel=4"), // internal
      CH(DIV_SYSTEM_YM2608, 1.0f, 0, "clockSel=1") // external
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-8801mk2SR (with PC-8801-23; extended channel 3 on external OPN)##sgpr"), {
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2203, 1.0f, 0, "clockSel=4"), // internal
      CH(DIV_SYSTEM_YM2608_EXT, 1.0f, 0, "clockSel=1") // external
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-8801mk2SR (with PC-8801-23; extended channel 3 and CSM on external OPN)##sgpr"), {
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2203, 1.0f, 0, "clockSel=4"), // internal
      CH(DIV_SYSTEM_YM2608_CSM, 1.0f, 0, "clockSel=1") // external
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-8801mk2SR (with PC-8801-23; extended channel 3 on both OPNs)##sgpr"), {
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2203_EXT, 1.0f, 0, "clockSel=4"), // internal
      CH(DIV_SYSTEM_YM2608_EXT, 1.0f, 0, "clockSel=1") // external
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-8801mk2SR (with PC-8801-23; extended channel 3 and CSM on both OPNs)##sgpr"), {
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2203_CSM, 1.0f, 0, "clockSel=4"), // internal
      CH(DIV_SYSTEM_YM2608_CSM, 1.0f, 0, "clockSel=1") // external
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-8801mk2SR (with HMB-20 HIBIKI-8800)##sgpr"), {
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2203, 1.0f, 0, "clockSel=4"), // internal
      CH(DIV_SYSTEM_YM2151, 1.0f, 0, "clockSel=2") // external; 4.0000MHz
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-8801mk2SR (with HMB-20 HIBIKI-8800; extended channel 3)##sgpr"), {
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2203_EXT, 1.0f, 0, "clockSel=4"), // internal
      CH(DIV_SYSTEM_YM2151, 1.0f, 0, "clockSel=2") // external; 4.0000MHz
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-8801mk2SR (with HMB-20 HIBIKI-8800; extended channel 3 and CSM)##sgpr"), {
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2203_CSM, 1.0f, 0, "clockSel=4"), // internal
      CH(DIV_SYSTEM_YM2151, 1.0f, 0, "clockSel=2") // external; 4.0000MHz
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    _L("NEC PC-8801FA (with PC-8801-10)##sgpr"), {
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2608, 1.0f, 0, "clockSel=4"), // internal
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "clockSel=15"), // external
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "clockSel=15") // ""
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("NEC PC-8801FA (with PC-8801-10; extended channel 3)##sgpr"), {
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2608_EXT, 1.0f, 0, "clockSel=4"), // internal
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "clockSel=15"), // external
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "clockSel=15") // ""
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-8801FA (with PC-8801-11)##sgpr"), {
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2608, 1.0f, 0, "clockSel=1"), // internal
      CH(DIV_SYSTEM_YM2203, 1.0f, 0, "clockSel=4") // external
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-8801FA (with PC-8801-11; extended channel 3 on internal OPN)##sgpr"), {
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2608_EXT, 1.0f, 0, "clockSel=1"), // internal
      CH(DIV_SYSTEM_YM2203, 1.0f, 0, "clockSel=4") // external
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-8801FA (with PC-8801-11; extended channel 3 on external OPN)##sgpr"), {
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2608, 1.0f, 0, "clockSel=1"), // internal
      CH(DIV_SYSTEM_YM2203_EXT, 1.0f, 0, "clockSel=4") // external
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-8801FA (with PC-8801-11; extended channel 3 and CSM on external OPN)##sgpr"), {
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2608, 1.0f, 0, "clockSel=1"), // internal
      CH(DIV_SYSTEM_YM2203_CSM, 1.0f, 0, "clockSel=4") // external
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-8801FA (with PC-8801-11; extended channel 3 on both OPNs)##sgpr"), {
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2608_EXT, 1.0f, 0, "clockSel=1"), // internal
      CH(DIV_SYSTEM_YM2203_EXT, 1.0f, 0, "clockSel=4") // external
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-8801FA (with PC-8801-11; extended channel 3 and CSM on both OPNs)##sgpr"), {
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2608_CSM, 1.0f, 0, "clockSel=1"), // internal
      CH(DIV_SYSTEM_YM2203_CSM, 1.0f, 0, "clockSel=4") // external
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-8801FA (with PC-8801-23)##sgpr"), {
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2608, 1.0f, 0, "clockSel=1"), // internal
      CH(DIV_SYSTEM_YM2608, 1.0f, 0, "clockSel=1") // external
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-8801FA (with PC-8801-23; extended channel 3 on internal OPN)##sgpr"), {
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2608_EXT, 1.0f, 0, "clockSel=1"), // internal
      CH(DIV_SYSTEM_YM2608, 1.0f, 0, "clockSel=1") // external
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-8801FA (with PC-8801-23; extended channel 3 and CSM on internal OPN)##sgpr"), {
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2608_CSM, 1.0f, 0, "clockSel=1"), // internal
      CH(DIV_SYSTEM_YM2608, 1.0f, 0, "clockSel=1") // external
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-8801FA (with PC-8801-23; extended channel 3 on external OPN)##sgpr"), {
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2608, 1.0f, 0, "clockSel=1"), // internal
      CH(DIV_SYSTEM_YM2608_EXT, 1.0f, 0, "clockSel=1") // external
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-8801FA (with PC-8801-23; extended channel 3 and CSM on external OPN)##sgpr"), {
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2608, 1.0f, 0, "clockSel=1"), // internal
      CH(DIV_SYSTEM_YM2608_CSM, 1.0f, 0, "clockSel=1") // external
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-8801FA (with PC-8801-23; extended channel 3 on both OPNs)##sgpr"), {
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2608_EXT, 1.0f, 0, "clockSel=1"), // internal
      CH(DIV_SYSTEM_YM2608_EXT, 1.0f, 0, "clockSel=1") // external
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-8801FA (with PC-8801-23; extended channel 3 and CSM on both OPNs)##sgpr"), {
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2608_CSM, 1.0f, 0, "clockSel=1"), // internal
      CH(DIV_SYSTEM_YM2608_CSM, 1.0f, 0, "clockSel=1") // external
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-8801FA (with HMB-20 HIBIKI-8800)##sgpr"), {
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2608, 1.0f, 0, "clockSel=1"), // internal
      CH(DIV_SYSTEM_YM2151, 1.0f, 0, "clockSel=2") // external; 4.0000MHz
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-8801FA (with HMB-20 HIBIKI-8800; extended channel 3)##sgpr"), {
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2608_EXT, 1.0f, 0, "clockSel=1"), // internal
      CH(DIV_SYSTEM_YM2151, 1.0f, 0, "clockSel=2") // external; 4.0000MHz
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-8801FA (with HMB-20 HIBIKI-8800; extended channel 3 and CSM)##sgpr"), {
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2608_CSM, 1.0f, 0, "clockSel=1"), // internal
      CH(DIV_SYSTEM_YM2151, 1.0f, 0, "clockSel=2") // external; 4.0000MHz
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    _L("NEC PC-98 (with PC-9801-26/K)##sgpr"), {
      CH(DIV_SYSTEM_YM2203, 1.0f, 0, "clockSel=4"), // 3.9936MHz but some compatible card has 4MHz
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1")
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("NEC PC-98 (with PC-9801-26/K; extended channel 3)##sgpr"), {
      CH(DIV_SYSTEM_YM2203_EXT, 1.0f, 0, "clockSel=4"), // 3.9936MHz but some compatible card has 4MHz
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-98 (with PC-9801-26/K; extended channel 3 and CSM)##sgpr"), {
      CH(DIV_SYSTEM_YM2203_CSM, 1.0f, 0, "clockSel=4"), // 3.9936MHz but some compatible card has 4MHz
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-98 (with Sound Orchestra)##sgpr"), {
      CH(DIV_SYSTEM_YM2203, 1.0f, 0, "clockSel=4"),
      CH(DIV_SYSTEM_OPL2, 1.0f, 0, "clockSel=4"),
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-98 (with Sound Orchestra; extended channel 3)##sgpr"), {
      CH(DIV_SYSTEM_YM2203_EXT, 1.0f, 0, "clockSel=4"),
      CH(DIV_SYSTEM_OPL2, 1.0f, 0, "clockSel=4"),
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-98 (with Sound Orchestra; extended channel 3 and CSM)##sgpr"), {
      CH(DIV_SYSTEM_YM2203_CSM, 1.0f, 0, "clockSel=4"),
      CH(DIV_SYSTEM_OPL2, 1.0f, 0, "clockSel=4"),
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-98 (with Sound Orchestra in drums mode)##sgpr"), {
      CH(DIV_SYSTEM_YM2203, 1.0f, 0, "clockSel=4"),
      CH(DIV_SYSTEM_OPL2_DRUMS, 1.0f, 0, "clockSel=4"),
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-98 (with Sound Orchestra in drums mode; extended channel 3)##sgpr"), {
      CH(DIV_SYSTEM_YM2203_EXT, 1.0f, 0, "clockSel=4"),
      CH(DIV_SYSTEM_OPL2_DRUMS, 1.0f, 0, "clockSel=4"),
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-98 (with Sound Orchestra in drums mode; extended channel 3 and CSM)##sgpr"), {
      CH(DIV_SYSTEM_YM2203_CSM, 1.0f, 0, "clockSel=4"),
      CH(DIV_SYSTEM_OPL2_DRUMS, 1.0f, 0, "clockSel=4"),
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-98 (with Sound Orchestra V)##sgpr"), {
      CH(DIV_SYSTEM_YM2203, 1.0f, 0, "clockSel=4"),
      CH(DIV_SYSTEM_Y8950, 1.0f, 0, "clockSel=4"),
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-98 (with Sound Orchestra V; extended channel 3)##sgpr"), {
      CH(DIV_SYSTEM_YM2203_EXT, 1.0f, 0, "clockSel=4"),
      CH(DIV_SYSTEM_Y8950, 1.0f, 0, "clockSel=4"),
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-98 (with Sound Orchestra V; extended channel 3 and CSM)##sgpr"), {
      CH(DIV_SYSTEM_YM2203_CSM, 1.0f, 0, "clockSel=4"),
      CH(DIV_SYSTEM_Y8950, 1.0f, 0, "clockSel=4"),
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-98 (with Sound Orchestra V in drums mode)##sgpr"), {
      CH(DIV_SYSTEM_YM2203, 1.0f, 0, "clockSel=4"),
      CH(DIV_SYSTEM_Y8950_DRUMS, 1.0f, 0, "clockSel=4"),
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-98 (with Sound Orchestra V in drums mode; extended channel 3)##sgpr"), {
      CH(DIV_SYSTEM_YM2203_EXT, 1.0f, 0, "clockSel=4"),
      CH(DIV_SYSTEM_Y8950_DRUMS, 1.0f, 0, "clockSel=4"),
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-98 (with Sound Orchestra V in drums mode; extended channel 3 and CSM)##sgpr"), {
      CH(DIV_SYSTEM_YM2203_CSM, 1.0f, 0, "clockSel=4"),
      CH(DIV_SYSTEM_Y8950_DRUMS, 1.0f, 0, "clockSel=4"),
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-98 (with PC-9801-86)##sgpr"), { // -73 also has OPNA
      CH(DIV_SYSTEM_YM2608, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_PCM_DAC, 1.0f, 0, // 2x 16-bit Burr Brown DAC
        "rate=44100\n"
        "outDepth=15\n"
      ),
      CH(DIV_SYSTEM_PCM_DAC, 1.0f, 0,
        "rate=44100\n"
        "outDepth=15\n"
      ),
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-98 (with PC-9801-86; extended channel 3)##sgpr"), { // -73 also has OPNA
      CH(DIV_SYSTEM_YM2608_EXT, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_PCM_DAC, 1.0f, 0,
        "rate=44100\n"
        "outDepth=15\n"
      ),
      CH(DIV_SYSTEM_PCM_DAC, 1.0f, 0,
        "rate=44100\n"
        "outDepth=15\n"
      ),
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-98 (with PC-9801-86; extended channel 3 and CSM)##sgpr"), { // -73 also has OPNA
      CH(DIV_SYSTEM_YM2608_CSM, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_PCM_DAC, 1.0f, 0,
        "rate=44100\n"
        "outDepth=15\n"
      ),
      CH(DIV_SYSTEM_PCM_DAC, 1.0f, 0,
        "rate=44100\n"
        "outDepth=15\n"
      ),
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-98 (with PC-9801-86) stereo##sgpr"), { // -73 also has OPNA
      CH(DIV_SYSTEM_YM2608, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_PCM_DAC, 1.0f, -1.0f, // 2x 16-bit Burr Brown DAC
        "rate=44100\n"
        "outDepth=15\n"
      ),
      CH(DIV_SYSTEM_PCM_DAC, 1.0f, 1.0f,
        "rate=44100\n"
        "outDepth=15\n"
      ),
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-98 (with PC-9801-86; extended channel 3) stereo##sgpr"), { // -73 also has OPNA
      CH(DIV_SYSTEM_YM2608_EXT, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_PCM_DAC, 1.0f, -1.0f,
        "rate=44100\n"
        "outDepth=15\n"
      ),
      CH(DIV_SYSTEM_PCM_DAC, 1.0f, 1.0f,
        "rate=44100\n"
        "outDepth=15\n"
      ),
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-98 (with PC-9801-86; extended channel 3 and CSM) stereo##sgpr"), { // -73 also has OPNA
      CH(DIV_SYSTEM_YM2608_CSM, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_PCM_DAC, 1.0f, -1.0f,
        "rate=44100\n"
        "outDepth=15\n"
      ),
      CH(DIV_SYSTEM_PCM_DAC, 1.0f, 1.0f,
        "rate=44100\n"
        "outDepth=15\n"
      ),
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-98 (with PC-9801-73)##sgpr"), {
      CH(DIV_SYSTEM_YM2608, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-98 (with PC-9801-73; extended channel 3)##sgpr"), {
      CH(DIV_SYSTEM_YM2608_EXT, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-98 (with PC-9801-73; extended channel 3 and CSM)##sgpr"), {
      CH(DIV_SYSTEM_YM2608_CSM, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-98 (with Sound Blaster 16 for PC-9800 w/PC-9801-26/K compatible)##sgpr"), {
      CH(DIV_SYSTEM_YM2203, 1.0f, 0, "clockSel=2"), // 4MHz
      CH(DIV_SYSTEM_PCM_DAC, 1.0f, 0,
        "rate=44100\n"
        "outDepth=15\n"
        "stereo=true\n"
      ),
      CH(DIV_SYSTEM_OPL3, 1.0f, 0, "clockSel=2"),
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-98 (with Sound Blaster 16 for PC-9800 w/PC-9801-26/K compatible; extended channel 3)##sgpr"), {
      CH(DIV_SYSTEM_YM2203_EXT, 1.0f, 0, "clockSel=2"), // 4MHz
      CH(DIV_SYSTEM_PCM_DAC, 1.0f, 0,
        "rate=44100\n"
        "outDepth=15\n"
        "stereo=true\n"
      ),
      CH(DIV_SYSTEM_OPL3, 1.0f, 0, "clockSel=2"),
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-98 (with Sound Blaster 16 for PC-9800 w/PC-9801-26/K compatible; extended channel 3 and CSM)##sgpr"), {
      CH(DIV_SYSTEM_YM2203_CSM, 1.0f, 0, "clockSel=2"), // 4MHz
      CH(DIV_SYSTEM_PCM_DAC, 1.0f, 0,
        "rate=44100\n"
        "outDepth=15\n"
        "stereo=true\n"
      ),
      CH(DIV_SYSTEM_OPL3, 1.0f, 0, "clockSel=2"),
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-98 (with Sound Blaster 16 for PC-9800 w/PC-9801-26/K compatible in drums mode)##sgpr"), {
      CH(DIV_SYSTEM_YM2203, 1.0f, 0, "clockSel=2"), // 4MHz
      CH(DIV_SYSTEM_PCM_DAC, 1.0f, 0,
        "rate=44100\n"
        "outDepth=15\n"
        "stereo=true\n"
      ),
      CH(DIV_SYSTEM_OPL3_DRUMS, 1.0f, 0, "clockSel=2"),
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-98 (with Sound Blaster 16 for PC-9800 w/PC-9801-26/K compatible in drums mode; extended channel 3)##sgpr"), {
      CH(DIV_SYSTEM_YM2203_EXT, 1.0f, 0, "clockSel=2"), // 4MHz
      CH(DIV_SYSTEM_PCM_DAC, 1.0f, 0,
        "rate=44100\n"
        "outDepth=15\n"
        "stereo=true\n"
      ),
      CH(DIV_SYSTEM_OPL3_DRUMS, 1.0f, 0, "clockSel=2"),
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NEC PC-98 (with Sound Blaster 16 for PC-9800 w/PC-9801-26/K compatible in drums mode; extended channel 3 and CSM)##sgpr"), {
      CH(DIV_SYSTEM_YM2203_CSM, 1.0f, 0, "clockSel=2"), // 4MHz
      CH(DIV_SYSTEM_PCM_DAC, 1.0f, 0,
        "rate=44100\n"
        "outDepth=15\n"
        "stereo=true\n"
      ),
      CH(DIV_SYSTEM_OPL3_DRUMS, 1.0f, 0, "clockSel=2"),
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "clockSel=1")
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    _L("ZX Spectrum (48K, SFX-like engine)##sgpr"), {
      CH(DIV_SYSTEM_SFX_BEEPER, 1.0f, 0, "")
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("ZX Spectrum (48K, QuadTone engine)##sgpr"), {
      CH(DIV_SYSTEM_SFX_BEEPER_QUADTONE, 1.0f, 0, "")
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "ZX Spectrum (128K)", {
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "clockSel=1") //beeper was also included
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("ZX Spectrum (128K) with TurboSound##sgpr"), {
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "clockSel=1"), // or YM2149
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "clockSel=1") // or YM2149
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("ZX Spectrum (128K) with TurboSound FM##sgpr"), {
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2203, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2203, 1.0f, 0, "clockSel=1")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("ZX Spectrum (128K) with TurboSound FM (extended channel 3 on first OPN)##sgpr"), {
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2203_EXT, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2203, 1.0f, 0, "clockSel=1")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("ZX Spectrum (128K) with TurboSound FM (extended channel 3 and CSM on first OPN)##sgpr"), {
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2203_CSM, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2203, 1.0f, 0, "clockSel=1")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("ZX Spectrum (128K) with TurboSound FM (extended channel 3 on second OPN)##sgpr"), {
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2203, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2203_EXT, 1.0f, 0, "clockSel=1")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("ZX Spectrum (128K) with TurboSound FM (extended channel 3 and CSM on second OPN)##sgpr"), {
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2203, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2203_CSM, 1.0f, 0, "clockSel=1")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("ZX Spectrum (128K) with TurboSound FM (extended channel 3 on both OPNs)##sgpr"), {
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2203_EXT, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2203_EXT, 1.0f, 0, "clockSel=1")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("ZX Spectrum (128K) with TurboSound FM (extended channel 3 and CSM on both OPNs)##sgpr"), {
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2203_CSM, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_YM2203_CSM, 1.0f, 0, "clockSel=1")
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "Amstrad CPC", {
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "clockSel=5")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Atari 800", {
      CH(DIV_SYSTEM_POKEY, 1.0f, 0, "clockSel=1")
    },
    "tickRate=50", MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("Atari 800 (stereo)##sgpr"), {
      CH(DIV_SYSTEM_POKEY, 1.0f, -1.0f, "clockSel=1"),
      CH(DIV_SYSTEM_POKEY, 1.0f, 1.0f, "clockSel=1"),
    },
    "tickRate=50", MENU_STATUS_LIST_END
  );
  ENTRY(
    "Atari ST", {
      CH(DIV_SYSTEM_AY8910, 1.0f, 0,
        "clockSel=3\n"
        "chipType=1\n"
      )
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Atari STE", {
      CH(DIV_SYSTEM_AY8910, 1.0f, 0,
        "clockSel=3\n"
        "chipType=1\n"
      ),
      CH(DIV_SYSTEM_PCM_DAC, 1.0f, 0,
        "rate=50668\n"
        "outDepth=7\n"
      ),
      CH(DIV_SYSTEM_PCM_DAC, 1.0f, 0,
        "rate=50668\n"
        "outDepth=7\n"
      )
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "SAM Coupé", {
      CH(DIV_SYSTEM_SAA1099, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Enterprise 128", {
      CH(DIV_SYSTEM_DAVE, 1.0f, 0, "")
    },
    "tickRate=50", MENU_STATUS_USUAL
  );
  ENTRY(
    "BBC Micro", {
      CH(DIV_SYSTEM_SMS, 1.0f, 0,
        "clockSel=2\n"
        "chipType=4\n" // SN76489A 4MHz
      )
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("PC (beeper)##sgpr"), {
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "")
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    "IBM PCjr", {
      // it can be enable sound output at once
      CH(DIV_SYSTEM_SMS, 1.0f, 0, "chipType=5") // SN76496
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Tandy 1000", {
      CH(DIV_SYSTEM_SMS, 1.0f, 0, "chipType=5"), // NCR 8496 or SN76496 or Tandy PSSJ(with 8 bit DAC)
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "PC + Covox Sound Master", {
      CH(DIV_SYSTEM_AY8930, 1.0f, 0, "clockSel=3"),
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "PC + SSI 2001", {
      CH(DIV_SYSTEM_C64_6581, 1.0f, 0, "clockSel=2"),
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "PC + Game Blaster", {
      CH(DIV_SYSTEM_SAA1099, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_SAA1099, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "PC + AdLib", {
      CH(DIV_SYSTEM_OPL2, 1.0f, 0, ""),
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("PC + AdLib (drums mode)##sgpr"), {
      CH(DIV_SYSTEM_OPL2_DRUMS, 1.0f, 0, ""),
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "PC + Sound Blaster", {
      CH(DIV_SYSTEM_OPL2, 1.0f, 0, ""),
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, ""),
      CH(DIV_SYSTEM_PCM_DAC, 1.0f, 0, 
        "rate=22050\n"
        "outDepth=7\n"
      )
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("PC + Sound Blaster (drums mode)##sgpr"), {
      CH(DIV_SYSTEM_OPL2_DRUMS, 1.0f, 0, ""),
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, ""),
      CH(DIV_SYSTEM_PCM_DAC, 1.0f, 0, 
        "rate=22050\n"
        "outDepth=7\n"
      )
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("PC + Sound Blaster w/Game Blaster Compatible##sgpr"), {
      CH(DIV_SYSTEM_OPL2, 1.0f, 0, ""),
      CH(DIV_SYSTEM_SAA1099, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_SAA1099, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_PCM_DAC, 1.0f, 0, 
        "rate=22050\n"
        "outDepth=7\n"
      ),
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("PC + Sound Blaster w/Game Blaster Compatible (drums mode)##sgpr"), {
      CH(DIV_SYSTEM_OPL2_DRUMS, 1.0f, 0, ""),
      CH(DIV_SYSTEM_SAA1099, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_SAA1099, 1.0f, 0, "clockSel=1"),
      CH(DIV_SYSTEM_PCM_DAC, 1.0f, 0, 
        "rate=22050\n"
        "outDepth=7\n"
      ),
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "PC + Sound Blaster Pro", {
      CH(DIV_SYSTEM_OPL2, 1.0f, -1.0f, ""),
      CH(DIV_SYSTEM_OPL2, 1.0f, 1.0f, ""),
      CH(DIV_SYSTEM_PCM_DAC, 1.0f, 0, 
        "rate=22050\n"
        "outDepth=7\n"
        "stereo=true\n"
      ), //alternatively 44.1 khz mono
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("PC + Sound Blaster Pro (drums mode)##sgpr"), {
      CH(DIV_SYSTEM_OPL2_DRUMS, 1.0f, -1.0f, ""),
      CH(DIV_SYSTEM_OPL2_DRUMS, 1.0f, 1.0f, ""),
      CH(DIV_SYSTEM_PCM_DAC, 1.0f, 0, 
        "rate=22050\n"
        "outDepth=7\n"
        "stereo=true\n"
      ), //alternatively 44.1 khz mono
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "PC + Sound Blaster Pro 2", {
      CH(DIV_SYSTEM_OPL3, 1.0f, 0, ""),
      CH(DIV_SYSTEM_PCM_DAC, 1.0f, 0, 
        "rate=44100\n"
        "outDepth=15\n"
        "stereo=true\n"
      ),
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("PC + Sound Blaster Pro 2 (drums mode)##sgpr"), {
      CH(DIV_SYSTEM_OPL3_DRUMS, 1.0f, 0, ""),
      CH(DIV_SYSTEM_PCM_DAC, 1.0f, 0, 
        "rate=44100\n"
        "outDepth=15\n"
        "stereo=true\n"
      ),
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("PC + ESS AudioDrive ES1488 (native ESFM mode)##sgpr"), {
      CH(DIV_SYSTEM_ESFM, 1.0f, 0, ""),
      CH(DIV_SYSTEM_PCM_DAC, 1.0f, 0, 
        "rate=44100\n"
        "outDepth=15\n"
        "stereo=true\n"
      ),
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "")
    }
  );
  ENTRY(
    "PC + PC-FXGA", {
      CH(DIV_SYSTEM_PCE, 1.0f, 0, ""), // HuC6230 (WSG from HuC6280 but with built in 2 OKI ADPCM playback engines)
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "PC + SAAYM", {
      CH(DIV_SYSTEM_YM2151, 1.0f, 0, ""), // 3.58MHz or 4MHz selectable via jumper
      CH(DIV_SYSTEM_SAA1099, 1.0f, 0, "clockSel=1"), // 7.16MHz or 8MHz selectable via jumper
      CH(DIV_SYSTEM_SAA1099, 1.0f, 0, "clockSel=1"), // ""
      CH(DIV_SYSTEM_PCSPKR, 1.0f, 0, "")
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "Sharp X1", {
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "clockSel=3")
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("Sharp X1 + FM addon##sgpr"), {
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "clockSel=3"),
      CH(DIV_SYSTEM_YM2151, 1.0f, 0, "clockSel=2")
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "Sharp X68000", {
      CH(DIV_SYSTEM_YM2151, 1.0f, 0, "clockSel=2"),
      CH(DIV_SYSTEM_MSM6258, 1.0f, 0, "clockSel=2")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "FM Towns", {
      CH(DIV_SYSTEM_YM2612, 1.0f, 0, "clockSel=2"), // YM3438
      CH(DIV_SYSTEM_RF5C68, 1.0f, 0, "")
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("FM Towns (extended channel 3)##sgpr"), {
      CH(DIV_SYSTEM_YM2612_EXT, 1.0f, 0, "clockSel=2"), // YM3438
      CH(DIV_SYSTEM_RF5C68, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "FM Towns (CSM)", {
      CH(DIV_SYSTEM_YM2612_CSM, 1.0f, 0, "clockSel=2"), // YM3438
      CH(DIV_SYSTEM_RF5C68, 1.0f, 0, "")
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    _L("Commander X16 (VERA only)##sgpr0"), {
      CH(DIV_SYSTEM_VERA, 1.0f, 0, "")
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("Commander X16 (with OPM)##sgpr"), {
      CH(DIV_SYSTEM_VERA, 1.0f, 0, ""),
      CH(DIV_SYSTEM_YM2151, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Commander X16 (with Twin OPL3)##sgpr"), {
      CH(DIV_SYSTEM_VERA, 1.0f, 0, ""),
      CH(DIV_SYSTEM_OPL3, 1.0f, 0, ""),
      CH(DIV_SYSTEM_OPL3, 1.0f, 0, "")
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "TI-99/4A", {
      CH(DIV_SYSTEM_SMS, 1.0f, 0,
        "clockSel=6\n"
        "chipType=8\n" // SN94624 447KHz
      )
    }, NULL, MENU_STATUS_USUAL
  );
  CATEGORY_END;

  CATEGORY_BEGIN(_L("Arcade systems##sgpr"),_L("INSERT COIN##sgpr"));
  ENTRY(
    "Pong", {
      CH(DIV_SYSTEM_PONG, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Bally Midway MCR", {
      // SSIO sound board
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "clockSel=3"), // 2MHz
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "clockSel=3") // 2MHz
      // additional sound boards, mostly software controlled DAC
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Williams/Midway Y/T unit w/ADPCM sound board##sgpr"), {
      // ADPCM sound board
      CH(DIV_SYSTEM_YM2151, 1.0f, 0, ""),
      CH(DIV_SYSTEM_PCM_DAC, 1.0f, 0,
        "rate=15625\n"
        "outDepth=7\n"
      ), // variable via OPM timer?
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Konami Gyruss", {
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, ""),
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, ""),
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, ""),
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, ""),
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "")
      // additional discrete sound logics
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Konami Bubble System", {
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, ""),
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, ""),
      CH(DIV_SYSTEM_BUBSYS_WSG, 1.0f, 0, "")
      // VLM5030 exists but not used for music at all
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Konami MX5000", {
      CH(DIV_SYSTEM_YM2151, 1.0f, 0, ""), // 3.58MHz
      CH(DIV_SYSTEM_K007232, 1.0f, 0, "")  // ""
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Konami Battlantis", {
      CH(DIV_SYSTEM_OPL2, 1.0f, 0, "clockSel=3"), // 3MHz
      CH(DIV_SYSTEM_OPL2, 1.0f, 0, "clockSel=3")  // ""
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("Konami Battlantis (drums mode on first OPL2)##sgpr"), {
      CH(DIV_SYSTEM_OPL2_DRUMS, 1.0f, 0, "clockSel=3"), // 3MHz
      CH(DIV_SYSTEM_OPL2, 1.0f, 0, "clockSel=3") // ""
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Konami Battlantis (drums mode on second OPL2)##sgpr"), {
      CH(DIV_SYSTEM_OPL2, 1.0f, 0, "clockSel=3"), // 3MHz
      CH(DIV_SYSTEM_OPL2_DRUMS, 1.0f, 0, "clockSel=3") // ""
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Konami Battlantis (drums mode on both OPL2s)##sgpr"), {
      CH(DIV_SYSTEM_OPL2_DRUMS, 1.0f, 0, "clockSel=3"), // 3MHz
      CH(DIV_SYSTEM_OPL2_DRUMS, 1.0f, 0, "clockSel=3") // ""
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "Konami Fast Lane", {
      CH(DIV_SYSTEM_K007232, 1.0f, 0, ""),  // 3.58MHz
      CH(DIV_SYSTEM_K007232, 1.0f, 0, "")  // ""
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Konami Chequered Flag", {
      CH(DIV_SYSTEM_YM2151, 1.0f, 0, ""), // 3.58MHz
      CH(DIV_SYSTEM_K007232, 1.0f, 0, "stereo=true"),  // ""
      CH(DIV_SYSTEM_K007232, 1.0f, 0, "")  // ""
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Konami Haunted Castle", {
      CH(DIV_SYSTEM_OPL2, 1.0f, 0, ""), // 3.58MHz
      CH(DIV_SYSTEM_SCC, 1.0f, 0, ""),  // ""
      CH(DIV_SYSTEM_K007232, 1.0f, 0, "")  // ""
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("Konami Haunted Castle (drums mode)##sgpr"), {
      CH(DIV_SYSTEM_OPL2_DRUMS, 1.0f, 0, ""), // 3.58MHz
      CH(DIV_SYSTEM_SCC, 1.0f, 0, ""), // ""
      CH(DIV_SYSTEM_K007232, 1.0f, 0, "")  // ""
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "Konami Hot Chase", {
      CH(DIV_SYSTEM_K007232, 1.0f, 0, "stereo=true"),  // 3.58MHz
      CH(DIV_SYSTEM_K007232, 1.0f, 0, "stereo=true"),  // ""
      CH(DIV_SYSTEM_K007232, 1.0f, 0, "stereo=true")  // ""
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Konami S.P.Y.", {
      CH(DIV_SYSTEM_OPL2, 1.0f, 0, ""), // 3.58MHz
      CH(DIV_SYSTEM_K007232, 1.0f, 0, ""),  // ""
      CH(DIV_SYSTEM_K007232, 1.0f, 0, "")  // ""
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("Konami S.P.Y. (drums mode)##sgpr"), {
      CH(DIV_SYSTEM_OPL2_DRUMS, 1.0f, 0, ""), // 3.58MHz
      CH(DIV_SYSTEM_K007232, 1.0f, 0, ""), // ""
      CH(DIV_SYSTEM_K007232, 1.0f, 0, "")  // ""
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "Konami Rollergames", {
      CH(DIV_SYSTEM_OPL2, 1.0f, 0, ""), // 3.58MHz
      CH(DIV_SYSTEM_K053260, 1.0f, 0, ""),  // ""
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("Konami Rollergames (drums mode)##sgpr"), {
      CH(DIV_SYSTEM_OPL2_DRUMS, 1.0f, 0, ""), // 3.58MHz
      CH(DIV_SYSTEM_K053260, 1.0f, 0, ""), // ""
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "Konami Golfing Greats", {
      CH(DIV_SYSTEM_K053260, 1.0f, 0, ""), // 3.58MHz
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Konami Lightning Fighters", {
      CH(DIV_SYSTEM_YM2151, 1.0f, 0, ""), // 3.58MHz
      CH(DIV_SYSTEM_K053260, 1.0f, 0, ""), // ""
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Konami Over Drive", {
      CH(DIV_SYSTEM_YM2151, 1.0f, 0, ""), // 3.58MHz
      CH(DIV_SYSTEM_K053260, 1.0f, 0, ""), // ""
      CH(DIV_SYSTEM_K053260, 1.0f, 0, ""), // ""
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Konami Asterix", {
      CH(DIV_SYSTEM_YM2151, 1.0f, 0, "clockSel=2"), // 4MHz
      CH(DIV_SYSTEM_K053260, 1.0f, 0, "clockSel=1"), // ""
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Konami Hexion", {
      CH(DIV_SYSTEM_SCC, 1.0f, 0, "clockSel=2"), // 1.5MHz (3MHz input)
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0, "clockSel=1")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Sega Kyugo", {
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "clockSel=14"),
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "clockSel=14")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Sega System 1", {
      CH(DIV_SYSTEM_SMS, 1.0f, 0,
        "clockSel=2\n"
        "chipType=4\n"
      ), // SN76489A 4MHz
      CH(DIV_SYSTEM_SMS, 1.0f, 0,
        "clockSel=5\n"
        "chipType=4\n"
      ) // SN76489A 2MHz
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Sega System E", {
      CH(DIV_SYSTEM_SMS, 1.0f, 0, ""),
      CH(DIV_SYSTEM_SMS, 1.0f, 0, "")
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("Sega System E (with FM expansion)##sgpr"), {
      CH(DIV_SYSTEM_SMS, 1.0f, 0, ""),
      CH(DIV_SYSTEM_SMS, 1.0f, 0, ""),
      CH(DIV_SYSTEM_OPLL, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Sega System E (with FM expansion in drums mode)##sgpr"), {
      CH(DIV_SYSTEM_SMS, 1.0f, 0, ""),
      CH(DIV_SYSTEM_SMS, 1.0f, 0, ""),
      CH(DIV_SYSTEM_OPLL_DRUMS, 1.0f, 0, "")
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "Sega Hang-On", {
      CH(DIV_SYSTEM_YM2203, 1.0f, 0, "clockSel=2"), // 4MHz
      CH(DIV_SYSTEM_SEGAPCM, 1.0f, 0, "") // discrete logics, 62.5KHz output rate
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("Sega Hang-On (extended channel 3)##sgpr"), {
      CH(DIV_SYSTEM_YM2203_EXT, 1.0f, 0, "clockSel=2"), // 4MHz
      CH(DIV_SYSTEM_SEGAPCM, 1.0f, 0, "") // discrete logics, 62.5KHz output rate
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Sega Hang-On (extended channel 3 and CSM)##sgpr"), {
      CH(DIV_SYSTEM_YM2203_CSM, 1.0f, 0, "clockSel=2"), // 4MHz
      CH(DIV_SYSTEM_SEGAPCM, 1.0f, 0, "") // discrete logics, 62.5KHz output rate
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "Sega OutRun/X Board", {
      CH(DIV_SYSTEM_YM2151, 1.0f, 0, "clockSel=2"), // 4MHz
      CH(DIV_SYSTEM_SEGAPCM, 1.0f, 0, "") // ASIC, 31.25KHz output rate
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Sega System 24", {
      CH(DIV_SYSTEM_YM2151, 1.0f, 0, "clockSel=2"), // 4MHz
      CH(DIV_SYSTEM_PCM_DAC, 1.0f, 0,
        "rate=61500\n"
        "outDepth=7\n"
      ) // software controlled, variable rate via configurable timers
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Sega System 18", {
      CH(DIV_SYSTEM_YM2612, 1.0f, 0, "clockSel=2"), // discrete 8MHz YM3438
      CH(DIV_SYSTEM_YM2612, 1.0f, 0, "clockSel=2"), // ^^
      CH(DIV_SYSTEM_RF5C68, 1.0f, 0, "clockSel=1") // 10MHz
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("Sega System 18 (extended channel 3 on first OPN2C)##sgpr"), {
      CH(DIV_SYSTEM_YM2612_EXT, 1.0f, 0, "clockSel=2"), // discrete 8MHz YM3438
      CH(DIV_SYSTEM_YM2612, 1.0f, 0, "clockSel=2"), // ^^
      CH(DIV_SYSTEM_RF5C68, 1.0f, 0, "clockSel=1") // 10MHz
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Sega System 18 (extended channel 3 and CSM on first OPN2C)##sgpr"), {
      CH(DIV_SYSTEM_YM2612_CSM, 1.0f, 0, "clockSel=2"), // discrete 8MHz YM3438
      CH(DIV_SYSTEM_YM2612, 1.0f, 0, "clockSel=2"), // ^^
      CH(DIV_SYSTEM_RF5C68, 1.0f, 0, "clockSel=1") // 10MHz
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Sega System 18 (extended channel 3 on second OPN2C)##sgpr"), {
      CH(DIV_SYSTEM_YM2612, 1.0f, 0, "clockSel=2"), // discrete 8MHz YM3438
      CH(DIV_SYSTEM_YM2612_EXT, 1.0f, 0, "clockSel=2"), // ^^
      CH(DIV_SYSTEM_RF5C68, 1.0f, 0, "clockSel=1") // 10MHz
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Sega System 18 (extended channel 3 and CSM on second OPN2C)##sgpr"), {
      CH(DIV_SYSTEM_YM2612, 1.0f, 0, "clockSel=2"), // discrete 8MHz YM3438
      CH(DIV_SYSTEM_YM2612_CSM, 1.0f, 0, "clockSel=2"), // ^^
      CH(DIV_SYSTEM_RF5C68, 1.0f, 0, "clockSel=1") // 10MHz
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Sega System 18 (extended channel 3 on both OPN2Cs)##sgpr"), {
      CH(DIV_SYSTEM_YM2612_EXT, 1.0f, 0, "clockSel=2"), // discrete 8MHz YM3438
      CH(DIV_SYSTEM_YM2612_EXT, 1.0f, 0, "clockSel=2"), // ^^
      CH(DIV_SYSTEM_RF5C68, 1.0f, 0, "clockSel=1") // 10MHz
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Sega System 18 (extended channel 3 and CSM on both OPN2Cs)##sgpr"), {
      CH(DIV_SYSTEM_YM2612_CSM, 1.0f, 0, "clockSel=2"), // discrete 8MHz YM3438
      CH(DIV_SYSTEM_YM2612_CSM, 1.0f, 0, "clockSel=2"), // ^^
      CH(DIV_SYSTEM_RF5C68, 1.0f, 0, "clockSel=1") // 10MHz
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "Sega System 32", {
      CH(DIV_SYSTEM_YM2612, 1.0f, 0, "clockSel=4"), // discrete 8.05MHz YM3438
      CH(DIV_SYSTEM_YM2612, 1.0f, 0, "clockSel=4"), // ^^
      CH(DIV_SYSTEM_RF5C68, 1.0f, 0, 
        "clockSel=2\n" 
        "chipType=1\n"
      ) // 12.5MHz
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("Sega System 32 (extended channel 3 on first OPN2C)##sgpr"), {
      CH(DIV_SYSTEM_YM2612_EXT, 1.0f, 0, "clockSel=4"), // discrete 8.05MHz YM3438
      CH(DIV_SYSTEM_YM2612, 1.0f, 0, "clockSel=4"), // ^^
      CH(DIV_SYSTEM_RF5C68, 1.0f, 0, 
        "clockSel=2\n" 
        "chipType=1\n"
      ) // 12.5MHz
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Sega System 32 (extended channel 3 and CSM on first OPN2C)##sgpr"), {
      CH(DIV_SYSTEM_YM2612_CSM, 1.0f, 0, "clockSel=4"), // discrete 8.05MHz YM3438
      CH(DIV_SYSTEM_YM2612, 1.0f, 0, "clockSel=4"), // ^^
      CH(DIV_SYSTEM_RF5C68, 1.0f, 0, 
        "clockSel=2\n" 
        "chipType=1\n"
      ) // 12.5MHz
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Sega System 32 (extended channel 3 on second OPN2C)##sgpr"), {
      CH(DIV_SYSTEM_YM2612, 1.0f, 0, "clockSel=4"), // discrete 8.05MHz YM3438
      CH(DIV_SYSTEM_YM2612_EXT, 1.0f, 0, "clockSel=4"), // ^^
      CH(DIV_SYSTEM_RF5C68, 1.0f, 0, 
        "clockSel=2\n" 
        "chipType=1\n"
      ) // 12.5MHz
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Sega System 32 (extended channel 3 and CSM on second OPN2C)##sgpr"), {
      CH(DIV_SYSTEM_YM2612, 1.0f, 0, "clockSel=4"), // discrete 8.05MHz YM3438
      CH(DIV_SYSTEM_YM2612_CSM, 1.0f, 0, "clockSel=4"), // ^^
      CH(DIV_SYSTEM_RF5C68, 1.0f, 0, 
        "clockSel=2\n" 
        "chipType=1\n"
      ) // 12.5MHz
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Sega System 32 (extended channel 3 on both OPN2Cs)##sgpr"), {
      CH(DIV_SYSTEM_YM2612_EXT, 1.0f, 0, "clockSel=4"), // discrete 8.05MHz YM3438
      CH(DIV_SYSTEM_YM2612_EXT, 1.0f, 0, "clockSel=4"), // ^^
      CH(DIV_SYSTEM_RF5C68, 1.0f, 0, 
        "clockSel=2\n" 
        "chipType=1\n"
      ) // 12.5MHz
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Sega System 32 (extended channel 3 and CSM on both OPN2Cs)##sgpr"), {
      CH(DIV_SYSTEM_YM2612_EXT, 1.0f, 0, "clockSel=4"), // discrete 8.05MHz YM3438
      CH(DIV_SYSTEM_YM2612_EXT, 1.0f, 0, "clockSel=4"), // ^^
      CH(DIV_SYSTEM_RF5C68, 1.0f, 0, 
        "clockSel=2\n" 
        "chipType=1\n"
      ) // 12.5MHz
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "Capcom Exed Eyes", {
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "clockSel=4"), // 1.5MHz
      CH(DIV_SYSTEM_SMS, 1.0f, 0,
        "clockSel=4\n"
        "chipType=1\n"
      ), // SN76489 3MHz
      CH(DIV_SYSTEM_SMS, 1.0f, 0,
        "clockSel=4\n"
        "chipType=1\n"
      ) // SN76489 3MHz
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Capcom Arcade##sgpr"), { // 1943, Side arms, etc
      CH(DIV_SYSTEM_YM2203, 1.0f, 0, "clockSel=5"), // 4 or 1.5MHz; various per games
      CH(DIV_SYSTEM_YM2203, 1.0f, 0, "clockSel=5")
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("Capcom Arcade (extended channel 3 on first OPN)##sgpr"), {
      CH(DIV_SYSTEM_YM2203_EXT, 1.0f, 0, "clockSel=5"),
      CH(DIV_SYSTEM_YM2203, 1.0f, 0, "clockSel=5")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Capcom Arcade (extended channel 3 and CSM on first OPN)##sgpr"), {
      CH(DIV_SYSTEM_YM2203_CSM, 1.0f, 0, "clockSel=5"),
      CH(DIV_SYSTEM_YM2203, 1.0f, 0, "clockSel=5")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Capcom Arcade (extended channel 3 on second OPN)##sgpr"), {
      CH(DIV_SYSTEM_YM2203, 1.0f, 0, "clockSel=5"),
      CH(DIV_SYSTEM_YM2203_EXT, 1.0f, 0, "clockSel=5")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Capcom Arcade (extended channel 3 and CSM on second OPN)##sgpr"), {
      CH(DIV_SYSTEM_YM2203, 1.0f, 0, "clockSel=5"),
      CH(DIV_SYSTEM_YM2203_CSM, 1.0f, 0, "clockSel=5")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Capcom Arcade (extended channel 3 on both OPNs)##sgpr"), {
      CH(DIV_SYSTEM_YM2203_EXT, 1.0f, 0, "clockSel=5"),
      CH(DIV_SYSTEM_YM2203_EXT, 1.0f, 0, "clockSel=5")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Capcom Arcade (extended channel 3 and CSM on both OPNs)##sgpr"), {
      CH(DIV_SYSTEM_YM2203_CSM, 1.0f, 0, "clockSel=5"),
      CH(DIV_SYSTEM_YM2203_CSM, 1.0f, 0, "clockSel=5")
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "Capcom CPS-1", { 
      CH(DIV_SYSTEM_YM2151, 1.0f, 0, ""), // 3.58MHz
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Capcom CPS-2 (QSound)", {
      CH(DIV_SYSTEM_QSOUND, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Jaleco Ginga NinkyouDen", {
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "chipType=1"), // 1.79MHz
      CH(DIV_SYSTEM_Y8950, 1.0f, 0, "") // 3.58MHz
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("Jaleco Ginga NinkyouDen (drums mode)##sgpr"), {
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "chipType=1"), // 1.79MHz
      CH(DIV_SYSTEM_Y8950_DRUMS, 1.0f, 0, "") // 3.58MHz
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "Jaleco Mega System 1", {
      CH(DIV_SYSTEM_YM2151, 1.0f, 0, "clockSel=1"), // 3.5MHz (7MHz / 2)
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0, "clockSel=2"), // 4MHz
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0, "clockSel=2") // 4MHz
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NMK 16-bit Arcade##sgpr"), {
      CH(DIV_SYSTEM_YM2203, 1.0f, 0, "clockSel=5"), // 1.5MHz; optional
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0,
        "clockSel=2\n"
        "rateSel=true\n"
      ), // 4MHz
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0,
        "clockSel=2\n"
        "rateSel=true\n"
      ) // ^^
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("NMK 16-bit Arcade (extended channel 3)##sgpr"), {
      CH(DIV_SYSTEM_YM2203_EXT, 1.0f, 0, "clockSel=5"), // 1.5MHz; optional
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0,
        "clockSel=2\n"
        "rateSel=true\n"
      ), // 4MHz
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0,
        "clockSel=2\n"
        "rateSel=true\n"
      ) // ^^
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("NMK 16-bit Arcade (extended channel 3 and CSM)##sgpr"), {
      CH(DIV_SYSTEM_YM2203_CSM, 1.0f, 0, "clockSel=5"), // 1.5MHz; optional
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0,
        "clockSel=2\n"
        "rateSel=true\n"
      ), // 4MHz
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0,
        "clockSel=2\n"
        "rateSel=true\n"
      ) // ^^
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "NMK 16-bit Arcade (w/NMK112 bankswitching)##sgpr", {
      CH(DIV_SYSTEM_YM2203, 1.0f, 0, "clockSel=5"), // 1.5MHz; optional
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0,
        "clockSel=2\n"
        "rateSel=true\n"
        "isBanked=true\n"
      ), // 4MHz
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0,
        "clockSel=2\n"
        "rateSel=true\n"
        "isBanked=true\n"
      ) // ^^
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    "NMK 16-bit Arcade (w/NMK112 bankswitching, extended channel 3)##sgpr", {
      CH(DIV_SYSTEM_YM2203_EXT, 1.0f, 0, "clockSel=5"), // 1.5MHz; optional
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0,
        "clockSel=2\n"
        "rateSel=true\n"
        "isBanked=true\n"
      ), // 4MHz
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0,
        "clockSel=2\n"
        "rateSel=true\n"
        "isBanked=true\n"
      ) // ^^
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "NMK 16-bit Arcade (w/NMK112 bankswitching, extended channel 3 and CSM)##sgpr", {
      CH(DIV_SYSTEM_YM2203_CSM, 1.0f, 0, "clockSel=5"), // 1.5MHz; optional
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0,
        "clockSel=2\n"
        "rateSel=true\n"
        "isBanked=true\n"
      ), // 4MHz
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0,
        "clockSel=2\n"
        "rateSel=true\n"
        "isBanked=true\n"
      ) // ^^
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "Atlus Power Instinct 2", {
      CH(DIV_SYSTEM_YM2203, 1.0f, 0, "clockSel=2"), // 4MHz
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0,
        "clockSel=13\n"
        "rateSel=true\n"
        "isBanked=true\n"
      ), // 3MHz
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0,
        "clockSel=13\n"
        "rateSel=true\n"
        "isBanked=true\n"
      ) // ^^
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    "Atlus Power Instinct 2 (extended channel 3)##sgpr", {
      CH(DIV_SYSTEM_YM2203_EXT, 1.0f, 0, "clockSel=2"), // 4MHz
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0,
        "clockSel=13\n"
        "rateSel=true\n"
        "isBanked=true\n"
      ), // 3MHz
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0,
        "clockSel=13\n"
        "rateSel=true\n"
        "isBanked=true\n"
      ) // ^^
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Atlus Power Instinct 2 (extended channel 3 and CSM)##sgpr", {
      CH(DIV_SYSTEM_YM2203_CSM, 1.0f, 0, "clockSel=2"), // 4MHz
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0,
        "clockSel=13\n"
        "rateSel=true\n"
        "isBanked=true\n"
      ), // 3MHz
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0,
        "clockSel=13\n"
        "rateSel=true\n"
        "isBanked=true\n"
      ) // ^^
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "Raizing/Eighting Battle Garegga", {
      CH(DIV_SYSTEM_YM2151, 1.0f, 0, "clockSel=2"), // 4MHz
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0,
        "clockSel=8\n"
        "isBanked=true\n"
      ) // 2MHz
    }
  );
  ENTRY(
    "Raizing/Eighting Batrider", {
      CH(DIV_SYSTEM_YM2151, 1.0f, 0, "clockSel=2"), // 4MHz
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0,
        "clockSel=15\n"
        "isBanked=true\n"
      ), // 3.2MHz
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0,
        "clockSel=15\n"
        "rateSel=true\n"
        "isBanked=true\n"
      ) // 3.2MHz
    }
  );
  ENTRY(
    "Kaneko DJ Boy", {
      CH(DIV_SYSTEM_YM2203, 1.0f, 0, "clockSel=3"), // 3MHz
      CH(DIV_SYSTEM_MSM6295, 1.0f, -1.0f, "clockSel=12"), // 1.5MHz, Left output
      CH(DIV_SYSTEM_MSM6295, 1.0f, 1.0f, "clockSel=12"), // 1.5MHz, Right output
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("Kaneko DJ Boy (extended channel 3)##sgpr"), {
      CH(DIV_SYSTEM_YM2203_EXT, 1.0f, 0, "clockSel=3"), // 3MHz
      CH(DIV_SYSTEM_MSM6295, 1.0f, -1.0f, "clockSel=12"), // 1.5MHz, Left output
      CH(DIV_SYSTEM_MSM6295, 1.0f, 1.0f, "clockSel=12") // 1.5MHz, Right output
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Kaneko DJ Boy (extended channel 3 and CSM)##sgpr"), {
      CH(DIV_SYSTEM_YM2203_CSM, 1.0f, 0, "clockSel=3"), // 3MHz
      CH(DIV_SYSTEM_MSM6295, 1.0f, -1.0f, "clockSel=12"), // 1.5MHz, Left output
      CH(DIV_SYSTEM_MSM6295, 1.0f, 1.0f, "clockSel=12") // 1.5MHz, Right output
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "Kaneko Air Buster", {
      CH(DIV_SYSTEM_YM2203, 1.0f, 0, "clockSel=3"), // 3MHz
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0,
        "clockSel=13\n"
        "rateSel=true\n"
      ) // 3MHz
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("Kaneko Air Buster (extended channel 3)##sgpr"), {
      CH(DIV_SYSTEM_YM2203_EXT, 1.0f, 0, "clockSel=3"), // 3MHz
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0,
        "clockSel=13\n"
        "rateSel=true\n"
      ) // 3MHz
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Kaneko Air Buster (extended channel 3 and CSM)##sgpr"), {
      CH(DIV_SYSTEM_YM2203_CSM, 1.0f, 0, "clockSel=3"), // 3MHz
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0,
        "clockSel=13\n"
        "rateSel=true\n"
      ) // 3MHz
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "Kaneko Toybox System", {
      CH(DIV_SYSTEM_AY8910, 1.0f, 0,
        "clockSel=3\n"
        "chipType=1\n"
      ), // YM2149 2MHz
      CH(DIV_SYSTEM_AY8910, 1.0f, 0,
        "clockSel=3\n"
        "chipType=1\n"
      ), // ^^
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0, "clockSel=8") // 2MHz
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Kaneko Jackie Chan", {
      CH(DIV_SYSTEM_YMZ280B, 1.0f, 0, "clockSel=3") // 16MHz
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Super Kaneko Nova System", {
      CH(DIV_SYSTEM_YMZ280B, 1.0f, 0, "clockSel=4") // 16.67MHz (33.33MHz / 2)
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Tecmo Ninja Gaiden", { // Ninja Gaiden, Raiga, etc
      CH(DIV_SYSTEM_YM2203, 1.0f, 0, "clockSel=2"), // 4MHz
      CH(DIV_SYSTEM_YM2203, 1.0f, 0, "clockSel=2"), // 4MHz
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0, "") // 1MHz
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("Tecmo Ninja Gaiden (extended channel 3 on first OPN)##sgpr"), { // Ninja Gaiden, Raiga, etc
      CH(DIV_SYSTEM_YM2203_EXT, 1.0f, 0, "clockSel=2"), // 4MHz
      CH(DIV_SYSTEM_YM2203, 1.0f, 0, "clockSel=2"), // 4MHz
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0, "") // 1MHz
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Tecmo Ninja Gaiden (extended channel 3 and CSM on first OPN)##sgpr"), { // Ninja Gaiden, Raiga, etc
      CH(DIV_SYSTEM_YM2203_CSM, 1.0f, 0, "clockSel=2"), // 4MHz
      CH(DIV_SYSTEM_YM2203, 1.0f, 0, "clockSel=2"), // 4MHz
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0, "") // 1MHz
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Tecmo Ninja Gaiden (extended channel 3 on second OPN)##sgpr"), { // Ninja Gaiden, Raiga, etc
      CH(DIV_SYSTEM_YM2203, 1.0f, 0, "clockSel=2"), // 4MHz
      CH(DIV_SYSTEM_YM2203_EXT, 1.0f, 0, "clockSel=2"), // 4MHz
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0, "") // 1MHz
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Tecmo Ninja Gaiden (extended channel 3 and CSM on second OPN)##sgpr"), { // Ninja Gaiden, Raiga, etc
      CH(DIV_SYSTEM_YM2203, 1.0f, 0, "clockSel=2"), // 4MHz
      CH(DIV_SYSTEM_YM2203_CSM, 1.0f, 0, "clockSel=2"), // 4MHz
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0, "") // 1MHz
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Tecmo Ninja Gaiden (extended channel 3 on both OPNs)##sgpr"), { // Ninja Gaiden, Raiga, etc
      CH(DIV_SYSTEM_YM2203_EXT, 1.0f, 0, "clockSel=2"), // 4MHz
      CH(DIV_SYSTEM_YM2203_EXT, 1.0f, 0, "clockSel=2"), // 4MHz
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0, "") // 1MHz
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Tecmo Ninja Gaiden (extended channel 3 and CSM on both OPNs)##sgpr"), { // Ninja Gaiden, Raiga, etc
      CH(DIV_SYSTEM_YM2203_CSM, 1.0f, 0, "clockSel=2"), // 4MHz
      CH(DIV_SYSTEM_YM2203_CSM, 1.0f, 0, "clockSel=2"), // 4MHz
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0, "") // 1MHz
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "Tecmo System", {
      CH(DIV_SYSTEM_OPL3, 1.0f, 0, ""),
      CH(DIV_SYSTEM_YMZ280B, 1.0f, 0, ""),
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0, "clockSel=8") // 2MHz
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("Tecmo System (drums mode)##sgpr"), {
      CH(DIV_SYSTEM_OPL3_DRUMS, 1.0f, 0, ""),
      CH(DIV_SYSTEM_YMZ280B, 1.0f, 0, ""),
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0, "clockSel=8") // 2MHz
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "Seibu Kaihatsu Raiden", { // Raiden, Seibu cup soccer, Zero team, etc
      CH(DIV_SYSTEM_OPL2, 1.0f, 0, ""), // YM3812 3.58MHz
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0, "") // 1 or 1.023MHz (28.636363MHz / 28); various per games
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("Seibu Kaihatsu Raiden (drums mode)##sgpr"), { // Raiden, Seibu cup soccer, Zero team, etc
      CH(DIV_SYSTEM_OPL2_DRUMS, 1.0f, 0, ""), // YM3812 3.58MHz
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0, "") // 1 or 1.023MHz (28.636363MHz / 28); various per games
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "Sunsoft Shanghai 3", {
      CH(DIV_SYSTEM_AY8910, 1.0f, 0,
        "clockSel=4\n"
        "chipType=1\n"
      ), // YM2149 1.5MHz
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0, "clockSel=1") // 1.056MHz
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Sunsoft Arcade##sgpr"), {
      CH(DIV_SYSTEM_YM2612, 1.0f, 0, "clockSel=2"), // discrete YM3438 8MHz
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0, "clockSel=1") // 1.056MHz
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("Sunsoft Arcade (extended channel 3)##sgpr"), {
      CH(DIV_SYSTEM_YM2612_EXT, 1.0f, 0, "clockSel=2"), // discrete YM3438 8MHz
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0, "clockSel=1") // 1.056MHz
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Sunsoft Arcade (extended channel 3 and CSM)##sgpr"), {
      CH(DIV_SYSTEM_YM2612_CSM, 1.0f, 0, "clockSel=2"), // discrete YM3438 8MHz
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0, "clockSel=1") // 1.056MHz
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "Atari Klax", { 
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0, "clockSel=7") // 0.895MHz (3.579545MHz / 4)
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Atari Rampart", {
      CH(DIV_SYSTEM_OPLL, 1.0f, 0, ""), // 3.579545MHz
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0, "clockSel=14") // 1.193MHz (3.579545MHz / 3)
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("Atari Rampart (drums mode)##sgpr"), { 
      CH(DIV_SYSTEM_OPLL_DRUMS, 1.0f, 0, ""), // 3.579545MHz
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0, "clockSel=14") // 1.193MHz (3.579545MHz / 3)
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "Atari JSA IIIs", { 
      CH(DIV_SYSTEM_YM2151, 1.0f, 0, ""), // 3.579545MHz
      CH(DIV_SYSTEM_MSM6295, 1.0f, -1.0f, "clockSel=14"), // 1.193MHz (3.579545MHz / 3), Left output
      CH(DIV_SYSTEM_MSM6295, 1.0f, 1.0f, "clockSel=14") // 1.193MHz (3.579545MHz / 3), Right output
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Atari Marble Madness", {
      CH(DIV_SYSTEM_YM2151, 1.0f, 0, ""),
      CH(DIV_SYSTEM_POKEY, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Atari Championship Sprint", {
      CH(DIV_SYSTEM_YM2151, 1.0f, 0, ""),
      CH(DIV_SYSTEM_POKEY, 1.0f, 0, ""),
      CH(DIV_SYSTEM_POKEY, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Atari Tetris", {
      CH(DIV_SYSTEM_POKEY, 1.0f, 0, ""),
      CH(DIV_SYSTEM_POKEY, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Atari I, Robot", {
      CH(DIV_SYSTEM_POKEY, 1.0f, 0, "customClock=1512000"),
      CH(DIV_SYSTEM_POKEY, 1.0f, 0, "customClock=1512000"),
      CH(DIV_SYSTEM_POKEY, 1.0f, 0, "customClock=1512000"),
      CH(DIV_SYSTEM_POKEY, 1.0f, 0, "customClock=1512000")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Data East Karnov", {
      CH(DIV_SYSTEM_YM2203, 1.0f, 0, "clockSel=5"), // 1.5MHz
      CH(DIV_SYSTEM_OPL, 1.0f, 0, "clockSel=3") // 3MHz
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("Data East Karnov (extended channel 3)##sgpr"), {
      CH(DIV_SYSTEM_YM2203_EXT, 1.0f, 0, "clockSel=5"), // 1.5MHz
      CH(DIV_SYSTEM_OPL, 1.0f, 0, "clockSel=3") // 3MHz
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Data East Karnov (extended channel 3 and CSM)##sgpr"), {
      CH(DIV_SYSTEM_YM2203_CSM, 1.0f, 0, "clockSel=5"), // 1.5MHz
      CH(DIV_SYSTEM_OPL, 1.0f, 0, "clockSel=3") // 3MHz
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Data East Karnov (drums mode)##sgpr"), {
      CH(DIV_SYSTEM_YM2203, 1.0f, 0, "clockSel=5"), // 1.5MHz
      CH(DIV_SYSTEM_OPL_DRUMS, 1.0f, 0, "clockSel=3") // 3MHz
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Data East Karnov (extended channel 3; drums mode)##sgpr"), {
      CH(DIV_SYSTEM_YM2203_EXT, 1.0f, 0, "clockSel=5"), // 1.5MHz
      CH(DIV_SYSTEM_OPL_DRUMS, 1.0f, 0, "clockSel=3") // 3MHz
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Data East Karnov (extended channel 3 and CSM; drums mode)##sgpr"), {
      CH(DIV_SYSTEM_YM2203_CSM, 1.0f, 0, "clockSel=5"), // 1.5MHz
      CH(DIV_SYSTEM_OPL_DRUMS, 1.0f, 0, "clockSel=3") // 3MHz
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    _L("Data East Arcade##sgpr"), { // Bad dudes, Robocop, etc
      CH(DIV_SYSTEM_YM2203, 1.0f, 0, "clockSel=5"), // 1.5MHz
      CH(DIV_SYSTEM_OPL2, 1.0f, 0, "clockSel=3"), // 3MHz
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0, "") // 1 to 1.056MHz; various per games or optional
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("Data East Arcade (extended channel 3)##sgpr"), { // Bad dudes, Robocop, etc
      CH(DIV_SYSTEM_YM2203_EXT, 1.0f, 0, "clockSel=5"), // 1.5MHz
      CH(DIV_SYSTEM_OPL2, 1.0f, 0, "clockSel=3"), // 3MHz
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0, "") // 1 to 1.056MHz; various per games or optional
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Data East Arcade (extended channel 3 and CSM)##sgpr"), { // Bad dudes, Robocop, etc
      CH(DIV_SYSTEM_YM2203_CSM, 1.0f, 0, "clockSel=5"), // 1.5MHz
      CH(DIV_SYSTEM_OPL2, 1.0f, 0, "clockSel=3"), // 3MHz
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0, "") // 1 to 1.056MHz; various per games or optional
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Data East Arcade (drums mode)##sgpr"), { // Bad dudes, Robocop, etc
      CH(DIV_SYSTEM_YM2203, 1.0f, 0, "clockSel=5"), // 1.5MHz
      CH(DIV_SYSTEM_OPL2_DRUMS, 1.0f, 0, "clockSel=3"), // 3MHz
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0, "") // 1 to 1.056MHz; various per games or optional
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Data East Arcade (extended channel 3; drums mode)##sgpr"), { // Bad dudes, Robocop, etc
      CH(DIV_SYSTEM_YM2203_EXT, 1.0f, 0, "clockSel=5"), // 1.5MHz
      CH(DIV_SYSTEM_OPL2_DRUMS, 1.0f, 0, "clockSel=3"), // 3MHz
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0, "") // 1 to 1.056MHz; various per games or optional
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Data East Arcade (extended channel 3 and CSM; drums mode)##sgpr"), { // Bad dudes, Robocop, etc
      CH(DIV_SYSTEM_YM2203_CSM, 1.0f, 0, "clockSel=5"), // 1.5MHz
      CH(DIV_SYSTEM_OPL2_DRUMS, 1.0f, 0, "clockSel=3"), // 3MHz
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0, "") // 1 to 1.056MHz; various per games or optional
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "Data East PCX", {
      CH(DIV_SYSTEM_YM2203, 1.0f, 0, "clockSel=5"), // 1.5MHz
      CH(DIV_SYSTEM_PCE, 1.0f, 0, "")
      // software controlled MSM5205
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("Data East PCX (extended channel 3)##sgpr"), {
      CH(DIV_SYSTEM_YM2203_EXT, 1.0f, 0, "clockSel=5"), // 1.5MHz
      CH(DIV_SYSTEM_PCE, 1.0f, 0, "")
      // software controlled MSM5205
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Data East PCX (extended channel 3 and CSM)##sgpr"), {
      CH(DIV_SYSTEM_YM2203_CSM, 1.0f, 0, "clockSel=5"), // 1.5MHz
      CH(DIV_SYSTEM_PCE, 1.0f, 0, "")
      // software controlled MSM5205
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "Data East Dark Seal", { // Dark Seal, Crude Buster, Vapor Trail, etc
      CH(DIV_SYSTEM_YM2151, 1.0f, 0, ""), // 3.580MHz (32.22MHz / 9)
      CH(DIV_SYSTEM_YM2203, 1.0f, 0, "clockSel=2"), // 4.0275MHz (32.22MHz / 8); optional
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0, ""), // 1.007MHz (32.22MHz / 32)
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0, "clockSel=8") // 2.014MHz (32.22MHz / 16); optional
      // HuC6280 is for control them, internal sound isn't used
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("Data East Dark Seal (extended channel 3)##sgpr"), { // Dark Seal, Crude Buster, Vapor Trail, etc
      CH(DIV_SYSTEM_YM2151, 1.0f, 0, ""), // 3.580MHz (32.22MHz / 9)
      CH(DIV_SYSTEM_YM2203_EXT, 1.0f, 0, "clockSel=2"), // 4.0275MHz (32.22MHz / 8); optional
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0, ""), // 1.007MHz (32.22MHz / 32)
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0, "clockSel=8") // 2.014MHz (32.22MHz / 16); optional
      // HuC6280 is for control them, internal sound isn't used
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Data East Dark Seal (extended channel 3 and CSM)##sgpr"), { // Dark Seal, Crude Buster, Vapor Trail, etc
      CH(DIV_SYSTEM_YM2151, 1.0f, 0, ""), // 3.580MHz (32.22MHz / 9)
      CH(DIV_SYSTEM_YM2203_CSM, 1.0f, 0, "clockSel=2"), // 4.0275MHz (32.22MHz / 8); optional
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0, ""), // 1.007MHz (32.22MHz / 32)
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0, "clockSel=8") // 2.014MHz (32.22MHz / 16); optional
      // HuC6280 is for control them, internal sound isn't used
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "Data East Deco 156", {
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0, "clockSel=0"), // 1 or 1.007MHz (32.22MHz / 32); various per games
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0, "clockSel=8") // 1 or 2 or 2.014MHz (32.22MHz / 16); various per games
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Data East MLC", {
      CH(DIV_SYSTEM_YMZ280B, 1.0f, 0, "clockSel=5") // 14MHz
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "SNK Ikari Warriors", {
      CH(DIV_SYSTEM_OPL, 1.0f, 0, "clockSel=2"),
      CH(DIV_SYSTEM_OPL, 1.0f, 0, "clockSel=2")
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("SNK Ikari Warriors (drums mode on first OPL)##sgpr"), {
      CH(DIV_SYSTEM_OPL_DRUMS, 1.0f, 0, "clockSel=2"),
      CH(DIV_SYSTEM_OPL, 1.0f, 0, "clockSel=2")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("SNK Ikari Warriors (drums mode on second OPL)##sgpr"), {
      CH(DIV_SYSTEM_OPL, 1.0f, 0, "clockSel=2"),
      CH(DIV_SYSTEM_OPL_DRUMS, 1.0f, 0, "clockSel=2")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("SNK Ikari Warriors (drums mode on both OPLs)##sgpr"), {
      CH(DIV_SYSTEM_OPL_DRUMS, 1.0f, 0, "clockSel=2"),
      CH(DIV_SYSTEM_OPL_DRUMS, 1.0f, 0, "clockSel=2")
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "SNK Triple Z80", {
      CH(DIV_SYSTEM_Y8950, 1.0f, 0, "clockSel=2"),
      CH(DIV_SYSTEM_OPL, 1.0f, 0, "clockSel=2")
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("SNK Triple Z80 (drums mode on Y8950)##sgpr"), {
      CH(DIV_SYSTEM_Y8950_DRUMS, 1.0f, 0, "clockSel=2"),
      CH(DIV_SYSTEM_OPL, 1.0f, 0, "clockSel=2")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("SNK Triple Z80 (drums mode on OPL)##sgpr"), {
      CH(DIV_SYSTEM_Y8950, 1.0f, 0, "clockSel=2"),
      CH(DIV_SYSTEM_OPL_DRUMS, 1.0f, 0, "clockSel=2")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("SNK Triple Z80 (drums mode on Y8950 and OPL)##sgpr"), {
      CH(DIV_SYSTEM_Y8950_DRUMS, 1.0f, 0, "clockSel=2"),
      CH(DIV_SYSTEM_OPL_DRUMS, 1.0f, 0, "clockSel=2")
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "SNK Chopper I", {
      CH(DIV_SYSTEM_Y8950, 1.0f, 0, "clockSel=2"),
      CH(DIV_SYSTEM_OPL2, 1.0f, 0, "clockSel=2")
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("SNK Chopper I (drums mode on Y8950)##sgpr"), {
      CH(DIV_SYSTEM_Y8950_DRUMS, 1.0f, 0, "clockSel=2"),
      CH(DIV_SYSTEM_OPL2, 1.0f, 0, "clockSel=2")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("SNK Chopper I (drums mode on OPL2)##sgpr"), {
      CH(DIV_SYSTEM_Y8950, 1.0f, 0, "clockSel=2"),
      CH(DIV_SYSTEM_OPL2_DRUMS, 1.0f, 0, "clockSel=2")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("SNK Chopper I (drums mode on Y8950 and OPL2)##sgpr"), {
      CH(DIV_SYSTEM_Y8950_DRUMS, 1.0f, 0, "clockSel=2"),
      CH(DIV_SYSTEM_OPL2_DRUMS, 1.0f, 0, "clockSel=2")
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "SNK Touchdown Fever", {
      CH(DIV_SYSTEM_OPL, 1.0f, 0, "clockSel=2"),
      CH(DIV_SYSTEM_Y8950, 1.0f, 0, "clockSel=2")
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("SNK Touchdown Fever (drums mode on OPL)##sgpr"), {
      CH(DIV_SYSTEM_OPL_DRUMS, 1.0f, 0, "clockSel=2"),
      CH(DIV_SYSTEM_Y8950, 1.0f, 0, "clockSel=2")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("SNK Touchdown Fever (drums mode on Y8950)##sgpr"), {
      CH(DIV_SYSTEM_OPL, 1.0f, 0, "clockSel=2"),
      CH(DIV_SYSTEM_Y8950_DRUMS, 1.0f, 0, "clockSel=2")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("SNK Touchdown Fever (drums mode on OPL and Y8950)##sgpr"), {
      CH(DIV_SYSTEM_OPL_DRUMS, 1.0f, 0, "clockSel=2"),
      CH(DIV_SYSTEM_Y8950_DRUMS, 1.0f, 0, "clockSel=2")
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "Alpha denshi Alpha-68K", {
      CH(DIV_SYSTEM_YM2203, 1.0f, 0, "clockSel=3"), // 3MHz
      CH(DIV_SYSTEM_OPLL, 1.0f, 0, "clockSel=0"), // 3.58MHz
      CH(DIV_SYSTEM_PCM_DAC, 1.0f, 0,
        "rate=7614\n"
        "outDepth=7\n"
      ) // software controlled 8 bit DAC
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("Alpha denshi Alpha-68K (extended channel 3)##sgpr"), {
      CH(DIV_SYSTEM_YM2203_EXT, 1.0f, 0, "clockSel=3"), // 3MHz
      CH(DIV_SYSTEM_OPLL, 1.0f, 0, "clockSel=0"), // 3.58MHz
      CH(DIV_SYSTEM_PCM_DAC, 1.0f, 0,
        "rate=7614\n"
        "outDepth=7\n"
      ) // software controlled 8 bit DAC
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Alpha denshi Alpha-68K (extended channel 3 and CSM)##sgpr"), {
      CH(DIV_SYSTEM_YM2203_CSM, 1.0f, 0, "clockSel=3"), // 3MHz
      CH(DIV_SYSTEM_OPLL, 1.0f, 0, "clockSel=0"), // 3.58MHz
      CH(DIV_SYSTEM_PCM_DAC, 1.0f, 0,
        "rate=7614\n"
        "outDepth=7\n"
      ) // software controlled 8 bit DAC
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Alpha denshi Alpha-68K (drums mode)##sgpr"), {
      CH(DIV_SYSTEM_YM2203, 1.0f, 0, "clockSel=3"), // 3MHz
      CH(DIV_SYSTEM_OPLL_DRUMS, 1.0f, 0, "clockSel=0"), // 3.58MHz
      CH(DIV_SYSTEM_PCM_DAC, 1.0f, 0,
        "rate=7614\n"
        "outDepth=7\n"
      ) // software controlled 8 bit DAC
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Alpha denshi Alpha-68K (extended channel 3; drums mode)##sgpr"), {
      CH(DIV_SYSTEM_YM2203_EXT, 1.0f, 0, "clockSel=3"), // 3MHz
      CH(DIV_SYSTEM_OPLL_DRUMS, 1.0f, 0, "clockSel=0"), // 3.58MHz
      CH(DIV_SYSTEM_PCM_DAC, 1.0f, 0,
        "rate=7614\n"
        "outDepth=7\n"
      ) // software controlled 8 bit DAC
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Alpha denshi Alpha-68K (extended channel 3 and CSM; drums mode)##sgpr"), {
      CH(DIV_SYSTEM_YM2203_CSM, 1.0f, 0, "clockSel=3"), // 3MHz
      CH(DIV_SYSTEM_OPLL_DRUMS, 1.0f, 0, "clockSel=0"), // 3.58MHz
      CH(DIV_SYSTEM_PCM_DAC, 1.0f, 0,
        "rate=7614\n"
        "outDepth=7\n"
      ) // software controlled 8 bit DAC
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "Alpha denshi Equites", {
      CH(DIV_SYSTEM_MSM5232, 1.0f, 0, "customClock=6144000"),
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "clockSel=14"),
      CH(DIV_SYSTEM_PCM_DAC, 1.0f, 0, 
         "rate=11025\n" 
         "outDepth=5\n"
      ),
      CH(DIV_SYSTEM_PCM_DAC, 1.0f, 0, 
         "rate=11025\n" 
         "outDepth=5\n"
      ) // don't know what the actual sample rate is
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Neo Geo MVS", {
      CH(DIV_SYSTEM_YM2610_FULL, 1.0f, 0, "")
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("Neo Geo MVS (extended channel 2)##sgpr"), {
      CH(DIV_SYSTEM_YM2610_FULL_EXT, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Neo Geo MVS (extended channel 2 and CSM)##sgpr"), {
      CH(DIV_SYSTEM_YM2610_CSM, 1.0f, 0, "")
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "Nichibutsu Mag Max", {
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "clockSel=13"),
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "clockSel=13"),
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "clockSel=13")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Namco (3-channel WSG)##sgpr"), { // Pac-Man, Galaga, Xevious, etc
      CH(DIV_SYSTEM_NAMCO, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Namco Mappy", { // Mappy, Super Pac-Man, Libble Rabble, etc
      CH(DIV_SYSTEM_NAMCO_15XX, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Namco Pac-Land", { // Pac-Land, Baraduke, Sky kid, etc
      CH(DIV_SYSTEM_NAMCO_CUS30, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Namco System 86", { // without expansion board case; Hopping Mappy, etc
      CH(DIV_SYSTEM_YM2151, 1.0f, 0, ""),
      CH(DIV_SYSTEM_NAMCO_CUS30, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Namco Thunder Ceptor", {
      CH(DIV_SYSTEM_YM2151, 1.0f, 0, ""),
      CH(DIV_SYSTEM_NAMCO_CUS30, 1.0f, 0, ""),
      CH(DIV_SYSTEM_PCM_DAC, 1.0f, 0, 
        "rate=8000\n"
        "outDepth=7\n"
      ) // M65C02 software driven, correct sample rate?
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Namco System 1", {
      CH(DIV_SYSTEM_YM2151, 1.0f, 0, ""),
      CH(DIV_SYSTEM_NAMCO_CUS30, 1.0f, 0, ""),
      CH(DIV_SYSTEM_PCM_DAC, 1.0f, 0,
        "rate=6000\n"
        "outDepth=7\n"
      ), // sample rate verified from https://github.com/mamedev/mame/blob/master/src/devices/sound/n63701x.cpp
      CH(DIV_SYSTEM_PCM_DAC, 1.0f, 0,
        "rate=6000\n"
        "outDepth=7\n"
      ) // ""
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Namco System 2", {
      CH(DIV_SYSTEM_YM2151, 1.0f, 0, ""),
      CH(DIV_SYSTEM_C140, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Namco NA-1/2", {
      CH(DIV_SYSTEM_C219, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Taito Arcade##sgpr"), {
      CH(DIV_SYSTEM_YM2610B, 1.0f, 0, "")
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("Taito Arcade (extended channel 3)##sgpr"), {
      CH(DIV_SYSTEM_YM2610B_EXT, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Taito Arcade (extended channel 3 and CSM)##sgpr"), {
      CH(DIV_SYSTEM_YM2610B_CSM, 1.0f, 0, "")
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "Taito Metal Soldier Isaac II", {
      CH(DIV_SYSTEM_MSM5232, 1.0f, 0, ""),
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "clockSel=3"),
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "clockSel=3")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Taito The Fairyland Story", {
      CH(DIV_SYSTEM_MSM5232, 1.0f, 0, ""),
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, 
         "clockSel=3\n"
         "chipType=1\n"
      ),
      CH(DIV_SYSTEM_PCM_DAC, 1.0f, 0, 
         "rate=11025\n" 
         "outDepth=7\n"
      ) // don't know what the actual sample rate is
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Taito Wyvern F-0", {
      CH(DIV_SYSTEM_MSM5232, 1.0f, 0, ""),
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, 
         "clockSel=3\n"
         "chipType=1\n"
      ),
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, 
         "clockSel=3\n"
         "chipType=1\n"
      ),
      CH(DIV_SYSTEM_PCM_DAC, 1.0f, 0, 
         "rate=11025\n" 
         "outDepth=7\n"
      ) // don't know what the actual sample rate is
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Seta 1", {
      CH(DIV_SYSTEM_X1_010, 1.0f, 0, "")
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("Seta 1 + FM addon##sgpr"), {
      CH(DIV_SYSTEM_X1_010, 1.0f, 0, ""),
      CH(DIV_SYSTEM_YM2612, 1.0f, 0, "clockSel=2") // Discrete YM3438
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Seta 1 + FM addon (extended channel 3)##sgpr"), {
      CH(DIV_SYSTEM_X1_010, 1.0f, 0, ""),
      CH(DIV_SYSTEM_YM2612_EXT, 1.0f, 0, "clockSel=2") // Discrete YM3438
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Seta 1 + FM addon (extended channel 3 and CSM)##sgpr"), {
      CH(DIV_SYSTEM_X1_010, 1.0f, 0, ""),
      CH(DIV_SYSTEM_YM2612_EXT, 1.0f, 0, "clockSel=2") // Discrete YM3438
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "Seta 2", {
      CH(DIV_SYSTEM_X1_010, 1.0f, 0,
         "clockSel=1\n"
         "isBanked=true\n"
      )
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Sammy/Seta/Visco SSV", {
      CH(DIV_SYSTEM_ES5506, 1.0f, 0, "channels=31")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Cave 68000", {
      CH(DIV_SYSTEM_YMZ280B, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Coreland Cyber Tank", {
      CH(DIV_SYSTEM_Y8950, 1.0f, -1.0f, ""), // 3.58MHz, Left output
      CH(DIV_SYSTEM_Y8950, 1.0f, 1.0f, "") // 3.58MHz, Right output
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("Coreland Cyber Tank (drums mode)##sgpr"), {
      CH(DIV_SYSTEM_Y8950_DRUMS, 1.0f, -1.0f, ""), // 3.58MHz, Left output
      CH(DIV_SYSTEM_Y8950_DRUMS, 1.0f, 1.0f, "") // 3.58MHz, Right output
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "ICE Skimaxx", {
      CH(DIV_SYSTEM_MSM6295, 1.0f, -1.0f,
        "clockSel=2\n"
        "rateSel=true\n"
      ), // 4MHz, Left output
      CH(DIV_SYSTEM_MSM6295, 1.0f, 1.0f,
        "clockSel=2\n"
        "rateSel=true\n"
      ), // 4MHz, Right output
      CH(DIV_SYSTEM_MSM6295, 1.0f, -1.0f, "clockSel=8"), // 2MHz, Left output
      CH(DIV_SYSTEM_MSM6295, 1.0f, 1.0f, "clockSel=8") // 2MHz, Right output
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Toaplan 1", {
      CH(DIV_SYSTEM_OPL2, 1.0f, 0, "clockSel=5") // 3.5MHz
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("Toaplan 1 (drums mode)##sgpr"), {
      CH(DIV_SYSTEM_OPL2_DRUMS, 1.0f, 0, "clockSel=5") // 3.5MHz
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    _L("Dynax/Nakanihon 3rd generation hardware##sgpr"), {
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, ""), // AY or YM, optional - 1.79MHz or 3.58MHz; various per game
      CH(DIV_SYSTEM_OPLL, 1.0f, 0, ""),
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0, "clockSel=6") // 1.023MHz mostly
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("Dynax/Nakanihon 3rd generation hardware (drums mode)##sgpr"), {
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, ""), // AY or YM, optional - 1.79MHz or 3.58MHz; various per game
      CH(DIV_SYSTEM_OPLL_DRUMS, 1.0f, 0, ""),
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0, "clockSel=6") // 1.023MHz mostly
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "Dynax/Nakanihon Real Break", {
      CH(DIV_SYSTEM_OPLL, 1.0f, 0, ""),
      CH(DIV_SYSTEM_YMZ280B, 1.0f, 0, "")
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("Dynax/Nakanihon Real Break (drums mode)##sgpr"), {
      CH(DIV_SYSTEM_OPLL_DRUMS, 1.0f, 0, ""),
      CH(DIV_SYSTEM_YMZ280B, 1.0f, 0, "")
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "Irem M72", {
      CH(DIV_SYSTEM_YM2151, 1.0f, 0, ""),
      CH(DIV_SYSTEM_PCM_DAC, 1.0f, 0,
        "rate=7812\n"
        "outDepth=7\n"
      )
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Irem M92/M107", {
      CH(DIV_SYSTEM_YM2151, 1.0f, 0, ""),
      CH(DIV_SYSTEM_GA20, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  CATEGORY_END;

  /*
  CATEGORY_BEGIN(_L("User##sgpr"),_L("system presets that you have saved.##sgpr"));
  CATEGORY_END;
  */

  CATEGORY_BEGIN("FM",_L("chips which use frequency modulation (FM) to generate sound.\nsome of these also pack more (like square and sample channels).\nActually \"FM\" here stands for phase modulation,\nbut these two are indistinguishable\nif you use sine waves.##sgpr"));
  ENTRY(
    "Yamaha YM2151 (OPM)", {
      CH(DIV_SYSTEM_YM2151, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Yamaha YM2203 (OPN)", {
      CH(DIV_SYSTEM_YM2203, 1.0f, 0, "clockSel=3")
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("Yamaha YM2203 (extended channel 3)##sgpr"), {
      CH(DIV_SYSTEM_YM2203_EXT, 1.0f, 0, "clockSel=3")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Yamaha YM2203 (extended channel 3 and CSM)##sgpr"), {
      CH(DIV_SYSTEM_YM2203_CSM, 1.0f, 0, "clockSel=3")
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "Yamaha YM2608 (OPNA)", {
      CH(DIV_SYSTEM_YM2608, 1.0f, 0, "")
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("Yamaha YM2608 (extended channel 3)##sgpr"), {
      CH(DIV_SYSTEM_YM2608_EXT, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Yamaha YM2608 (extended channel 3 and CSM)##sgpr"), {
      CH(DIV_SYSTEM_YM2608_CSM, 1.0f, 0, "")
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "Yamaha YM2610 (OPNB)", {
      CH(DIV_SYSTEM_YM2610_FULL, 1.0f, 0, "")
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("Yamaha YM2610 (extended channel 2)##sgpr"), {
      CH(DIV_SYSTEM_YM2610_FULL_EXT, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Yamaha YM2610 (extended channel 2 and CSM)##sgpr"), {
      CH(DIV_SYSTEM_YM2610_CSM, 1.0f, 0, "")
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "Yamaha YM2610B (OPNB2)", {
      CH(DIV_SYSTEM_YM2610B, 1.0f, 0, "")
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("Yamaha YM2610B (extended channel 3)##sgpr"), {
      CH(DIV_SYSTEM_YM2610B_EXT, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Yamaha YM2610B (extended channel 3 and CSM)##sgpr"), {
      CH(DIV_SYSTEM_YM2610B_CSM, 1.0f, 0, "")
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "Yamaha YM2612 (OPN2)", {
      CH(DIV_SYSTEM_YM2612, 1.0f, 0, "chipType=1")
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("Yamaha YM2612 (extended channel 3)##sgpr"), {
      CH(DIV_SYSTEM_YM2612_EXT, 1.0f, 0, "chipType=1")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Yamaha YM2612 (OPN2) CSM", {
      CH(DIV_SYSTEM_YM2612_CSM, 1.0f, 0, "chipType=1")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Yamaha YM2612 (OPN2) with DualPCM##sgpr"), {
      CH(DIV_SYSTEM_YM2612_DUALPCM, 1.0f, 0, "chipType=1")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Yamaha YM2612 (extended channel 3) with DualPCM and CSM##sgpr"), {
      CH(DIV_SYSTEM_YM2612_DUALPCM_EXT, 1.0f, 0, "chipType=1")
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "Yamaha YMF276", {
      CH(DIV_SYSTEM_YM2612, 1.0f, 0, "chipType=2")
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("Yamaha YMF276 (extended channel 3)##sgpr"), {
      CH(DIV_SYSTEM_YM2612_EXT, 1.0f, 0, "chipType=2")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Yamaha YMF276 CSM", {
      CH(DIV_SYSTEM_YM2612_CSM, 1.0f, 0, "chipType=2")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Yamaha YMF276 with DualPCM##sgpr"), {
      CH(DIV_SYSTEM_YM2612_DUALPCM, 1.0f, 0, "chipType=2")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Yamaha YMF276 (extended channel 3) with DualPCM and CSM##sgpr"), {
      CH(DIV_SYSTEM_YM2612_DUALPCM_EXT, 1.0f, 0, "chipType=2")
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "Yamaha YM2413 (OPLL)", {
      CH(DIV_SYSTEM_OPLL, 1.0f, 0, "")
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("Yamaha YM2413 (drums mode)##sgpr"), {
      CH(DIV_SYSTEM_OPLL_DRUMS, 1.0f, 0, "")
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "Yamaha YM2414 (OPZ)", {
      CH(DIV_SYSTEM_OPZ, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Yamaha YM3438 (OPN2C)", {
      CH(DIV_SYSTEM_YM2612, 1.0f, 0, "")
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("Yamaha YM3438 (extended channel 3)##sgpr"), {
      CH(DIV_SYSTEM_YM2612_EXT, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Yamaha YM3438 (OPN2C) CSM", {
      CH(DIV_SYSTEM_YM2612_CSM, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Yamaha YM3438 (OPN2C) with DualPCM##sgpr"), {
      CH(DIV_SYSTEM_YM2612_DUALPCM, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Yamaha YM3438 (extended channel 3) with DualPCM and CSM##sgpr"), {
      CH(DIV_SYSTEM_YM2612_DUALPCM_EXT, 1.0f, 0, "")
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "Yamaha YM3526 (OPL)", {
      CH(DIV_SYSTEM_OPL, 1.0f, 0, "")
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("Yamaha YM3526 (drums mode)##sgpr"), {
      CH(DIV_SYSTEM_OPL_DRUMS, 1.0f, 0, "")
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "Yamaha Y8950", {
      CH(DIV_SYSTEM_Y8950, 1.0f, 0, "")
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("Yamaha Y8950 (drums mode)##sgpr"), {
      CH(DIV_SYSTEM_Y8950_DRUMS, 1.0f, 0, "")
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "Yamaha YM3812 (OPL2)", {
      CH(DIV_SYSTEM_OPL2, 1.0f, 0, "")
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("Yamaha YM3812 (drums mode)##sgpr"), {
      CH(DIV_SYSTEM_OPL2_DRUMS, 1.0f, 0, "")
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "Yamaha YMF262 (OPL3)", {
      CH(DIV_SYSTEM_OPL3, 1.0f, 0, "")
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("Yamaha YMF262 (drums mode)##sgpr"), {
      CH(DIV_SYSTEM_OPL3_DRUMS, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Yamaha YMF289B (OPL3-L)", {
      CH(DIV_SYSTEM_OPL3, 1.0f, 0, 
         "clockSel=5\n"
         "chipType=1\n"
      )
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Yamaha YMF289B (drums mode)##sgpr"), {
      CH(DIV_SYSTEM_OPL3_DRUMS, 1.0f, 0, 
         "clockSel=5\n"
         "chipType=1\n"
      )
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    _L("ESS ES1xxx series (ESFM)##sgpr"), {
      CH(DIV_SYSTEM_ESFM, 1.0f, 0, "")
    }
  );
  if (settings.hiddenSystems) {
    ENTRY(
      "Yamaha YMU759 (MA-2)", {
        CH(DIV_SYSTEM_YMU759, 1.0f, 0, "")
      }, NULL, MENU_STATUS_USUAL
    );
  }
  CATEGORY_END;

  CATEGORY_BEGIN(_L("Square##sgpr"),_L("these chips generate square/pulse tones only (but may include noise).##sgpr"));
  ENTRY(
    "TI SN76489", {
      CH(DIV_SYSTEM_SMS, 1.0f, 0, "chipType=1")
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    "TI SN76489A", {
      CH(DIV_SYSTEM_SMS, 1.0f, 0, "chipType=4")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "TI SN76496", {
      CH(DIV_SYSTEM_SMS, 1.0f, 0, "chipType=5")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "NCR 8496", {
      CH(DIV_SYSTEM_SMS, 1.0f, 0, "chipType=6")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Tandy PSSJ 3-voice sound##sgpr"), {
      CH(DIV_SYSTEM_SMS, 1.0f, 0, "chipType=7")
      // 8 bit DAC
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Sega PSG (SN76489-like)##sgpr"), {
      CH(DIV_SYSTEM_SMS, 1.0f, 0, ""),
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Sega PSG (SN76489-like, Stereo)##sgpr"), {
      CH(DIV_SYSTEM_SMS, 1.0f, 0, "chipType=3")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "TI SN94624", {
      CH(DIV_SYSTEM_SMS, 1.0f, 0,
        "clockSel=6\n"
        "chipType=8\n"
      )
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "TI SN76494", {
      CH(DIV_SYSTEM_SMS, 1.0f, 0,
        "clockSel=6\n"
        "chipType=9\n"
      )
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "Toshiba T6W28", {
      CH(DIV_SYSTEM_T6W28, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "AY-3-8910", {
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "")
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    "AY-3-8914", {
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "chipType=3")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Yamaha YM2149(F)", {
      CH(DIV_SYSTEM_AY8910, 1.0f, 0, "chipType=1")
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "Philips SAA1099", {
      CH(DIV_SYSTEM_SAA1099, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("PC Speaker##sgpr"), {
      CH(DIV_SYSTEM_PCSPKR, 0.5f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Pokémon Mini", {
      CH(DIV_SYSTEM_POKEMINI, 0.5f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Commodore VIC", {
      CH(DIV_SYSTEM_VIC20, 1.0f, 0, "clockSel=1")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "OKI MSM5232", {
      CH(DIV_SYSTEM_MSM5232, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Pong", {
      CH(DIV_SYSTEM_PONG, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "NEC D65010G031", {
      CH(DIV_SYSTEM_PV1000, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "MOS Technology TED", {
      CH(DIV_SYSTEM_TED, 1.0f, 0, "clockSel=1")
    }, NULL, MENU_STATUS_USUAL
  );
  CATEGORY_END;

  CATEGORY_BEGIN(_L("Sample##sgpr"),_L("chips/systems which use PCM or ADPCM samples for sound synthesis.##sgpr"));
  ENTRY(
    "Amiga", {
      CH(DIV_SYSTEM_AMIGA, 1.0f, 0, "clockSel=1")
    },
    "tickRate=50"
  );
  ENTRY(
    "SegaPCM", {
      CH(DIV_SYSTEM_SEGAPCM, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Capcom QSound", {
      CH(DIV_SYSTEM_QSOUND, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Seta/Allumer X1-010", {
      CH(DIV_SYSTEM_X1_010, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Yamaha YMZ280B (PCMD8)", {
      CH(DIV_SYSTEM_YMZ280B, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Ricoh RF5C68", {
      CH(DIV_SYSTEM_RF5C68, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  ); 
  ENTRY(
    "OKI MSM6258", {
      CH(DIV_SYSTEM_MSM6258, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "OKI MSM6295", {
      CH(DIV_SYSTEM_MSM6295, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "SNES", {
      CH(DIV_SYSTEM_SNES, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Konami K007232", {
      CH(DIV_SYSTEM_K007232, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Irem GA20", {
      CH(DIV_SYSTEM_GA20, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Generic PCM DAC##sgpr"), {
      CH(DIV_SYSTEM_PCM_DAC, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Ensoniq ES5506 (OTTO)", {
      CH(DIV_SYSTEM_ES5506, 1.0f, 0, "channels=31")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Ensoniq ES5503", {
      CH(DIV_SYSTEM_ES5503, 1.0f, 0, "")
    }
  );
  ENTRY(
    "Konami K053260", {
      CH(DIV_SYSTEM_K053260, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Namco C140", {
      CH(DIV_SYSTEM_C140, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Namco C219", {
      CH(DIV_SYSTEM_C219, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Nintendo DS (NDS)", {
      CH(DIV_SYSTEM_NDS, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Game Boy Advance (DMA)", {
      CH(DIV_SYSTEM_GBA_DMA, 1.0f, 0, "")
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    "Game Boy Advance (MinMod)", {
      CH(DIV_SYSTEM_GBA_MINMOD, 1.0f, 0, "")
    }, NULL, MENU_STATUS_LIST_END
  );
  CATEGORY_END;

  CATEGORY_BEGIN(_L("Wavetable##sgpr"),_L("chips which use user-specified waveforms to generate sound.##sgpr"));
  ENTRY(
    "PC Engine", {
      CH(DIV_SYSTEM_PCE, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Konami Bubble System WSG", {
      CH(DIV_SYSTEM_BUBSYS_WSG, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Konami SCC", {
      CH(DIV_SYSTEM_SCC, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Konami SCC+", {
      CH(DIV_SYSTEM_SCC_PLUS, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Namco WSG", {
      CH(DIV_SYSTEM_NAMCO, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Namco C15 (8-channel mono)##sgpr"), {
      CH(DIV_SYSTEM_NAMCO_15XX, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Namco C30 (8-channel stereo)##sgpr"), {
      CH(DIV_SYSTEM_NAMCO_CUS30, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Namco 163", {
      CH(DIV_SYSTEM_N163, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Famicom Disk System (chip)##sgpr"), {
      CH(DIV_SYSTEM_FDS, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "WonderSwan", {
      CH(DIV_SYSTEM_SWAN, 1.0f, 0, "")
    },
    "tickRate=75.47169811320754716981"
  );
  ENTRY(
    "Virtual Boy", {
      CH(DIV_SYSTEM_VBOY, 1.0f, 0, "")
    },
    "tickRate=50.2734877734878"
  );
  ENTRY(
    "Seta/Allumer X1-010", {
      CH(DIV_SYSTEM_X1_010, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  CATEGORY_END;

  CATEGORY_BEGIN(_L("Specialized##sgpr"),_L("chips/systems with unique sound synthesis methods.##sgpr"));
  ENTRY(
    "MOS Technology SID (6581)", {
      CH(DIV_SYSTEM_C64_6581, 1.0f, 0, "clockSel=1")
    },
    "tickRate=50.1245421"
  );
  ENTRY(
    "MOS Technology SID (8580)", {
      CH(DIV_SYSTEM_C64_8580, 1.0f, 0, "clockSel=1")
    },
    "tickRate=50.1245421"
  );
  ENTRY(
    _L("Commodore PET (pseudo-wavetable)##sgpr"), {
      CH(DIV_SYSTEM_PET, 1.0f, 0, "")
    },
    "tickRate=50"
  );
  ENTRY(
    "Konami VRC6", {
      CH(DIV_SYSTEM_VRC6, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "MMC5", {
      CH(DIV_SYSTEM_MMC5, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Microchip AY8930", {
      CH(DIV_SYSTEM_AY8930, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Game Boy", {
      CH(DIV_SYSTEM_GB, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Atari Lynx", {
      CH(DIV_SYSTEM_LYNX, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "POKEY", {
      CH(DIV_SYSTEM_POKEY, 1.0f, 0, "clockSel=1")
    },
    "tickRate=50"
  );
  ENTRY(
    "Atari TIA", {
      CH(DIV_SYSTEM_TIA, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "NES (Ricoh 2A03)", {
      CH(DIV_SYSTEM_NES, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("ZX Spectrum (beeper only, SFX-like engine)##sgpr"), {
      CH(DIV_SYSTEM_SFX_BEEPER, 1.0f, 0, "")
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("ZX Spectrum (beeper only, QuadTone engine)##sgpr"), {
      CH(DIV_SYSTEM_SFX_BEEPER_QUADTONE, 1.0f, 0, "")
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "Sharp SM8521", {
      CH(DIV_SYSTEM_SM8521, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "DAVE", {
      CH(DIV_SYSTEM_DAVE, 1.0f, 0, "")
    },
    "tickRate=50", MENU_STATUS_USUAL
  );
  CATEGORY_END;

  CATEGORY_BEGIN(_L("Modern/fantasy##sgpr"),_L("chips/systems which do not exist in reality or were made just several years ago.##sgpr"));
  ENTRY(
    "tildearrow Sound Unit", {
      CH(DIV_SYSTEM_SOUND_UNIT, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    _L("Commander X16 (VERA only)##sgpr1"), {
      CH(DIV_SYSTEM_VERA, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  if (settings.hiddenSystems) {
    ENTRY(
      "Dummy System", {
        CH(DIV_SYSTEM_DUMMY, 1.0f, 0, "")
      }, NULL, MENU_STATUS_USUAL
    );
  }
  ENTRY(
    "PowerNoise", {
      CH(DIV_SYSTEM_POWERNOISE, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "SID2", {
      CH(DIV_SYSTEM_SID2, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "5E01", {
      CH(DIV_SYSTEM_5E01, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Nintendo DS (NDS)", {
      CH(DIV_SYSTEM_NDS, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Flizzer Tracker sound source (FZT)", {
      CH(DIV_SYSTEM_FZT, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  CATEGORY_END;

  CATEGORY_BEGIN(_L("DefleMask-compatible##sgpr"),_L("these configurations are compatible with DefleMask.\nselect this if you need to save as .dmf or work with that program.##sgpr"));
  ENTRY(
    "Sega Genesis", {
      CH(DIV_SYSTEM_YM2612, 1.0f, 0, ""),
      CH(DIV_SYSTEM_SMS, 0.5f, 0, "")
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("Sega Genesis (extended channel 3)##sgpr1"), {
      CH(DIV_SYSTEM_YM2612_EXT, 1.0f, 0, ""),
      CH(DIV_SYSTEM_SMS, 0.5f, 0, "")
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "Sega Master System", {
      CH(DIV_SYSTEM_SMS, 1.0f, 0, "")
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("Sega Master System (with FM expansion)##sgpr1"), {
      CH(DIV_SYSTEM_SMS, 1.0f, 0, ""),
      CH(DIV_SYSTEM_OPLL, 1.0f, 0, "")
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "Game Boy", {
      CH(DIV_SYSTEM_GB, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "NEC PC Engine/TurboGrafx-16", {
      CH(DIV_SYSTEM_PCE, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "NES/Famicom", {
      CH(DIV_SYSTEM_NES, 1.0f, 0, "")
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("Famicom with Konami VRC7##sgpr1"), {
      CH(DIV_SYSTEM_NES, 1.0f, 0, ""),
      CH(DIV_SYSTEM_VRC7, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Famicom Disk System", {
      CH(DIV_SYSTEM_NES, 1.0f, 0, ""),
      CH(DIV_SYSTEM_FDS, 1.0f, 0, "")
    }, NULL, MENU_STATUS_LIST_END
  );
  ENTRY(
    "Commodore 64 (6581 SID)", {
      CH(DIV_SYSTEM_C64_6581, 1.0f, 0, "clockSel=1")
    },
    "tickRate=50.1245421"
  );
  ENTRY(
    "Commodore 64 (8580 SID)", {
      CH(DIV_SYSTEM_C64_8580, 1.0f, 0, "clockSel=1")
    },
    "tickRate=50.1245421"
  );
  ENTRY(
    _L("Arcade (YM2151 and SegaPCM)##sgpr1"), {
      CH(DIV_SYSTEM_YM2151, 1.0f, 0, ""),
      CH(DIV_SYSTEM_SEGAPCM_COMPAT, 1.0f, 0, "")
    }, NULL, MENU_STATUS_USUAL
  );
  ENTRY(
    "Neo Geo CD", {
      CH(DIV_SYSTEM_YM2610, 1.0f, 0, "")
    }, NULL, MENU_STATUS_LIST_START
  );
  ENTRY(
    _L("Neo Geo CD (extended channel 2)##sgpr1"), {
      CH(DIV_SYSTEM_YM2610_EXT, 1.0f, 0, "")
    }, NULL, MENU_STATUS_LIST_END
  );
  CATEGORY_END;
}

FurnaceGUISysDef::FurnaceGUISysDef(const char* n, std::initializer_list<FurnaceGUISysDefChip> def, const char* e, menu_status menuStatuss):
  name(n),
  extra((e==NULL)?"":e),
  menuStatus(menuStatuss) {
  orig=def;
  int index=0;
  for (FurnaceGUISysDefChip& i: orig) {
    definition+=fmt::sprintf(
      "id%d=%d\nvol%d=%f\npan%d=%f\nflags%d=%s\n",
      index,
      DivEngine::systemToFileFur(i.sys),
      index,
      i.vol,
      index,
      i.pan,
      index,
      taEncodeBase64(i.flags)
    );
    index++;
  }
  if (!extra.empty()) {
    definition+=extra;
  }
}

/*FurnaceGUISysDef::FurnaceGUISysDef(const char* n, const char* def, DivEngine* e):
  name(n),
  definition(def) {
  // extract definition
  DivConfig conf;
  conf.loadFromBase64(def);
  for (int i=0; i<DIV_MAX_CHIPS; i++) {
    String nextStr=fmt::sprintf("id%d",i);
    int id=conf.getInt(nextStr.c_str(),0);
    if (id==0) break;
    conf.remove(nextStr.c_str());

    nextStr=fmt::sprintf("vol%d",i);
    float vol=conf.getFloat(nextStr.c_str(),1.0f);
    conf.remove(nextStr.c_str());
    nextStr=fmt::sprintf("pan%d",i);
    float pan=conf.getFloat(nextStr.c_str(),0.0f);
    conf.remove(nextStr.c_str());
    nextStr=fmt::sprintf("fr%d",i);
    float panFR=conf.getFloat(nextStr.c_str(),0.0f);
    conf.remove(nextStr.c_str());
    nextStr=fmt::sprintf("flags%d",i);
    String flags=conf.getString(nextStr.c_str(),"");
    conf.remove(nextStr.c_str());

    orig.push_back(FurnaceGUISysDefChip(e->systemFromFileFur(id),vol,pan,flags.c_str(),panFR));
  }
  // extract extra
  extra=conf.toString();
}

// functions for loading/saving user presets
#ifdef _WIN32
#define PRESETS_FILE "\\presets.cfg"
#else
#define PRESETS_FILE "/presets.cfg"
#endif

#define REDUNDANCY_NUM_ATTEMPTS 5
#define CHECK_BUF_SIZE 8192

std::vector<FurnaceGUISysDef>* digDeep(std::vector<FurnaceGUISysDef>& entries, int depth) {
  if (depth==0) return &entries;
  std::vector<FurnaceGUISysDef>& result=entries;

  for (int i=0; i<depth; i++) {
    if (result.empty()) {
      logW("digDeep: %d is as far as it goes!",depth);
      break;
    }
    result=result.at(result.size()).subDefs;
  }
  return &result;
}

bool FurnaceGUI::loadUserPresets(bool redundancy) {
  String path=e->getConfigPath()+PRESETS_FILE;
  String line;
  logD("opening user presets: %s",path);

  FILE* f=NULL;

  if (redundancy) {
    unsigned char* readBuf=new unsigned char[CHECK_BUF_SIZE];
    size_t readBufLen=0;
    for (int i=0; i<REDUNDANCY_NUM_ATTEMPTS; i++) {
      bool viable=false;
      if (i>0) {
        line=fmt::sprintf("%s.%d",path,i);
      } else {
        line=path;
      }
      logV("trying: %s",line);

      // try to open config
      f=ps_fopen(line.c_str(),"rb");
      // check whether we could open it
      if (f==NULL) {
        logV("fopen(): %s",strerror(errno));
        continue;
      }

      // check whether there's something
      while (!feof(f)) {
        readBufLen=fread(readBuf,1,CHECK_BUF_SIZE,f);
        if (ferror(f)) {
          logV("fread(): %s",strerror(errno));
          break;
        }

        for (size_t j=0; j<readBufLen; j++) {
          if (readBuf[j]==0) {
            viable=false;
            logW("a zero?");
            break;
          }
          if (readBuf[j]!='\r' && readBuf[j]!='\n' && readBuf[j]!=' ') {
            viable=true;
          }
        }

        if (viable) break;
      }

      // there's something
      if (viable) {
        if (fseek(f,0,SEEK_SET)==-1) {
          logV("fseek(): %s",strerror(errno));
          viable=false;
        } else {
          break;
        }
      }
      
      // close it (because there's nothing)
      fclose(f);
      f=NULL;
    }
    delete[] readBuf;

    // we couldn't read at all
    if (f==NULL) {
      logD("presets file does not exist");
      return false;
    }
  } else {
    f=ps_fopen(path.c_str(),"rb");
    if (f==NULL) {
      logD("presets file does not exist");
      return false;
    }
  }

  // now read stuff
  FurnaceGUISysCategory* userCategory=NULL;

  for (FurnaceGUISysCategory& i: sysCategories) {
    if (strcmp(i.name,"User")==0) {
      userCategory=&i;
      break;
    }
  }

  if (userCategory==NULL) {
    logE("could not find user category!");
    fclose(f);
    return false;
  }

  userCategory->systems.clear();

  char nextLine[4096];
  while (!feof(f)) {
    if (fgets(nextLine,4095,f)==NULL) {
      break;
    }
    int indent=0;
    bool readIndent=true;
    bool keyOrValue=false;
    String key="";
    String value="";
    for (char* i=nextLine; *i; i++) {
      if ((*i)=='\n') break;
      if (readIndent) {
        if ((*i)==' ') {
          indent++;
        } else {
          readIndent=false;
        }
      }
      if (!readIndent) {
        if (keyOrValue) {
          value+=*i;
        } else {
          if ((*i)=='=') {
            keyOrValue=true;
          } else {
            key+=*i;
          }
        }
      }
    }
    indent>>=1;

    if (!key.empty() && !value.empty()) {
      std::vector<FurnaceGUISysDef>* where=digDeep(userCategory->systems,indent);
      where->push_back(FurnaceGUISysDef(key.c_str(),value.c_str(),e));
    }
  }

  fclose(f);
  return true;
}

void writeSubEntries(FILE* f, std::vector<FurnaceGUISysDef>& entries, int depth) {
  for (FurnaceGUISysDef& i: entries) {
    String safeName;
    safeName.reserve(i.name.size());
    bool beginning=false;
    for (char j: i.name) {
      if (beginning && j==' ') continue;
      if (j=='=') continue;
      if (j<0x20) continue;
      safeName+=j;
    }
    
    String data;
    for (int i=0; i<depth; i++) {
      data+="  ";
    }
    data+=fmt::sprintf("%s=%s\n",safeName,i.definition);
    fputs(data.c_str(),f);

    writeSubEntries(f,i.subDefs,depth+1);
  }
}

bool FurnaceGUI::saveUserPresets(bool redundancy) {
  String path=e->getConfigPath()+PRESETS_FILE;
  FurnaceGUISysCategory* userCategory=NULL;

  for (FurnaceGUISysCategory& i: sysCategories) {
    if (strcmp(i.name,"User")==0) {
      userCategory=&i;
      break;
    }
  }

  if (userCategory==NULL) {
    logE("could not find user category!");
    return false;
  }

  if (redundancy) {
    char oldPath[4096];
    char newPath[4096];

    if (fileExists(path.c_str())==1) {
      logD("rotating preset files...");
      for (int i=4; i>=0; i--) {
        if (i>0) {
          snprintf(oldPath,4095,"%s.%d",path.c_str(),i);
        } else {
          strncpy(oldPath,path.c_str(),4095);
        }
        snprintf(newPath,4095,"%s.%d",path.c_str(),i+1);

        if (i>=4) {
          logV("remove %s",oldPath);
          deleteFile(oldPath);
        } else {
          logV("move %s to %s",oldPath,newPath);
          moveFiles(oldPath,newPath);
        }
      }
    }
  }
  logD("saving user presets: %s",path);
  FILE* f=ps_fopen(path.c_str(),"wb");
  if (f==NULL) {
    logW("could not write presets! %s",strerror(errno));
    return false;
  }

  writeSubEntries(f,userCategory->systems,0);

  fclose(f);
  logD("presets written successfully.");
  return true;
}*/

// user presets management
void FurnaceGUI::printPresets(std::vector<FurnaceGUISysDef>& items, int depth) 
{
  if (depth>0) ImGui::Indent();
  for (FurnaceGUISysDef& i: items) 
  {
    if (ImGui::Selectable(i.name.c_str())) 
    {
      // TODO
    }
    /*if (!i.subDefs.empty()) {
      printPresets(i.subDefs,depth+1);
    }*/
  }
  if (depth>0) ImGui::Unindent();
}

void FurnaceGUI::drawUserPresets() {
  /*if (nextWindow==GUI_WINDOW_USER_PRESETS) {
    userPresetsOpen=true;
    ImGui::SetNextWindowFocus();
    nextWindow=GUI_WINDOW_NOTHING;
  }
  if (!userPresetsOpen) return;
  if (ImGui::Begin("User Presets",&userPresetsOpen,globalWinFlags)) {
    FurnaceGUISysCategory* userCategory=NULL;
    for (FurnaceGUISysCategory& i: sysCategories) {
      if (strcmp(i.name,"User")==0) {
        userCategory=&i;
        break;
      }
    }

    //std::vector<int> depthStack;

    if (userCategory==NULL) {
      ImGui::Text("Error! User category does not exist!");
    } else if (ImGui::BeginTable("UserPresets",2,ImGuiTableFlags_BordersInnerV)) {
      // preset list
      ImGui::TableNextRow();
      ImGui::TableNextColumn();
      ImGui::Text("Presets...");
      printPresets(userCategory->systems,0);

      // editor
      ImGui::TableNextColumn();
      if (selectedUserPreset<0 || selectedUserPreset>=(int)userCategory->systems.size()) {
        ImGui::Text("select a preset");
      } else {
        
        ImGui::Text("Edit...");
      }

      ImGui::EndTable();
    }

    if (ImGui::Button("Save and Close")) {
      userPresetsOpen=false;
    }
  }
  if (!userPresetsOpen) {
    saveUserPresets(true);
  }
  if (ImGui::IsWindowFocused(ImGuiFocusedFlags_ChildWindows)) curWindow=GUI_WINDOW_USER_PRESETS;
  ImGui::End();*/
}
