/**
 * Furnace Tracker - multi-system chiptune tracker
 * Copyright (C) 2021-2025 tildearrow and contributors
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

//GoatTracker v2.72 (and lower) and GTUltra import by LTVA

#include "fileOpsCommon.h"

bool DivEngine::loadGT(unsigned char* file, size_t len, int magic_version)
{
    SafeReader reader=SafeReader(file,len);
    warnings="";

    try
    {
        DivSong ds;
        ds.version = DIV_VERSION_GT; //TODO: detect if GTUltra and change version
        ds.subsong.push_back(new DivSubSong);
        DivSubSong* s = ds.subsong[0];
        ds.systemLen = 1; //TODO: change if several SIDs are used
        ds.system[0] = DIV_SYSTEM_C64_8580; //one 8580 SID by default

        if (active) quitDispatch();
        BUSY_BEGIN_SOFT;
        saveLock.lock();
        song.unload();
        song=ds;
        changeSong(0);
        recalcChans();
        saveLock.unlock();
        BUSY_END;

        if (active) 
        {
            initDispatch();
            BUSY_BEGIN;
            renderSamples();
            reset();
            BUSY_END;
        }
    }
    catch (EndOfFileException& e) 
    {
        logE("premature end of file!");
        lastError=_("incomplete file");
        delete[] file;
        return false;
    }
    
    delete[] file;
    return true;
}