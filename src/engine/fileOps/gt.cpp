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

#define GT_MAX_TABLES 4
#define GT_MAX_INSTRNAMELEN 16

#define WTBL 0
#define PTBL 1
#define FTBL 2
#define STBL 3

typedef struct
{
    unsigned char ptr[GT_MAX_TABLES];
    unsigned char vibdelay;
    unsigned char gatetimer;
    unsigned char firstwave;
    unsigned char pan;
    char name[GT_MAX_INSTRNAMELEN];
} INSTR;

typedef struct {
// From gtstereo.c
    unsigned int sidmodel;
    int maxSIDChannels;
    unsigned int adparam;

    unsigned int optimizepulse;
    unsigned int optimizerealtime;
    unsigned int ntsc;
    unsigned int usefinevib;
    unsigned int multiplier;

} EDITOR_INFO;

bool GT_determinechannels(SafeReader& reader, int& num_channels, int& num_subsongs)
{
    size_t returnpos = reader.tell();

    if(reader.size() == reader.tell())
    {
        return false;
    }

    unsigned char num_songs = reader.readC();
    unsigned char songbuffer[257];
    num_subsongs = num_songs;

    for(int song = 0; song < num_songs; song++)
    {
        for(int c = 0; c < 6; c++) //max chans in one subsong = 6
        {
            if(reader.size() == reader.tell())
            {
                reader.seek(returnpos, SEEK_SET);
                return false;
            }

            unsigned char loadsize = reader.readC();
            loadsize++;

            memset(songbuffer, 0, 257);

            if(reader.size() - reader.tell() < (size_t)loadsize)
            {
                reader.seek(returnpos, SEEK_SET);
                return false;
            }

            reader.read(songbuffer, loadsize);

            if ((songbuffer[loadsize - 2] != 0xff) || (songbuffer[loadsize - 1] >= loadsize))
            {
                reader.seek(returnpos, SEEK_SET);
                num_channels = 3;
                return true;
            }
        }
    }

    reader.seek(returnpos, SEEK_SET);
    num_channels = 6;
    return true;
}

#define GT_FREE_MEMORY \
delete[] file; \
delete[] songorder; \
delete[] gt_insts; \
delete[] ltable; \
delete[] rtable; \
delete editorInfo;

bool DivEngine::loadGT(unsigned char* file, size_t len, int magic_version)
{
    SafeReader reader=SafeReader(file,len);
    warnings="";

    //allocate arrays
    auto songorder = new unsigned char[32][6][256];
    INSTR* gt_insts = new INSTR[64];
    auto ltable = new unsigned char[4][255];
    auto rtable = new unsigned char[4][255];
    auto pattern = new unsigned char[208][516];
    EDITOR_INFO* editorInfo = new EDITOR_INFO;

    try
    {
        DivSong ds;
        ds.version = DIV_VERSION_GT; //TODO: detect if GTUltra and change version
        ds.subsong.push_back(new DivSubSong);
        DivSubSong* s = ds.subsong[0];
        ds.systemLen = 1; //TODO: change if several SIDs are used
        ds.system[0] = DIV_SYSTEM_C64_8580; //one 8580 SID by default

        if(magic_version > 5 || magic_version < 1)
        {
            logE("unsupported file version!");
            lastError = _("unsupported file version!");
            GT_FREE_MEMORY
            return false;
        }

        reader.seek(4, SEEK_CUR);

        logI("goattracker file version %d", magic_version);

        if(magic_version >= 3 && magic_version <= 5)
        {
            char buffer[33] = { 0 };

            if(reader.size() - reader.tell() < 32)
            {
                logE("premature end of file!");
                lastError = _("premature end of file!");
                GT_FREE_MEMORY
                return false;
            }

            reader.read(buffer, 32);
            buffer[32] = '\0';
            ds.name = buffer;

            if(reader.size() - reader.tell() < 32)
            {
                logE("premature end of file!");
                lastError = _("premature end of file!");
                GT_FREE_MEMORY
                return false;
            }

            reader.read(buffer, 32);
            buffer[32] = '\0';
            ds.author = buffer;

            if(reader.size() - reader.tell() < 32)
            {
                logE("premature end of file!");
                lastError = _("premature end of file!");
                GT_FREE_MEMORY
                return false;
            }

            reader.read(buffer, 32);
            buffer[32] = '\0';
            ds.copyright = buffer;

            int num_channels = 0;
            int num_subsongs = 0;

            if(!GT_determinechannels(reader, num_channels, num_subsongs))
            {
                logE("error in GT_determinechannels!");
                lastError = _("error in GT_determinechannels!");
                GT_FREE_MEMORY
                return false;
            }

            logI("number of subsongs %d", num_subsongs);
            logI("number of channels %d", num_channels);

            if(num_subsongs > 31)
            {
                logE("too many subsongs!");
                lastError = _("too many subsongs!");
                GT_FREE_MEMORY
                return false;
            }

            if(num_channels == 6)
            {
                ds.systemLen = 2;
                ds.system[1] = DIV_SYSTEM_C64_8580; //by default second SID also is 8580
            }

            unsigned char __subsongs = reader.readC(); //skip
            (void)(__subsongs);

            int loadsize = 0;
            ds.subsong.reserve(num_subsongs);

            //read orders
            for(int song = 0; song < num_subsongs; song++)
            {
                ds.subsong.push_back(new DivSubSong);

                for(int c = 0; c < num_channels; c++)
                {
                    if(reader.size() == reader.tell())
                    {
                        logE("premature end of file!");
                        lastError = _("premature end of file!");
                        GT_FREE_MEMORY
                        return false;
                    }
                    unsigned char length = reader.readC();
                    
                    loadsize = length + 1;

                    if(reader.size() - reader.tell() < (size_t)loadsize)
                    {
                        logE("premature end of file!");
                        lastError = _("premature end of file!");
                        GT_FREE_MEMORY
                        return false;
                    }
                    
                    //TODO: convert orders info...
                    //it would be hard because looks like GT has semi-independent channel patterns execution?
                    reader.read(songorder[song][c], loadsize);
                }
            }

            //read instruments
            if(reader.size() == reader.tell())
            {
                logE("premature end of file!");
                lastError = _("premature end of file!");
                GT_FREE_MEMORY
                return false;
            }

            unsigned char num_instruments = reader.readC();

            if(num_instruments > 64)
            {
                logE("too many instruments!");
                lastError = _("too many instruments!");
                GT_FREE_MEMORY
                return false;
            }

            for(int i = 0; i < num_instruments; i++)
            {
                DivInstrument* ins = new DivInstrument;
                ds.ins.push_back(ins);
                ds.ins[i]->type = DIV_INS_C64;

                if(reader.size() - reader.tell() < 9 + 16)
                {
                    logE("premature end of file!");
                    lastError = _("premature end of file!");
                    GT_FREE_MEMORY
                    return false;
                }

                unsigned char temp = reader.readC();
                ins->c64.a = temp >> 4;
                ins->c64.d = temp & 0xF;
                temp = reader.readC();
                ins->c64.s = temp >> 4;
                ins->c64.r = temp & 0xF;
                gt_insts[i].ptr[WTBL] = reader.readC();
                gt_insts[i].ptr[PTBL] = reader.readC();
                gt_insts[i].ptr[FTBL] = reader.readC();
                gt_insts[i].ptr[STBL] = reader.readC();
                gt_insts[i].vibdelay = reader.readC();
                gt_insts[i].gatetimer = reader.readC();
                gt_insts[i].firstwave = reader.readC();
                reader.read(gt_insts[i].name, GT_MAX_INSTRNAMELEN);
                gt_insts[i].name[GT_MAX_INSTRNAMELEN - 1] = '\0';

                ins->name = gt_insts[i].name;
            }

            ds.insLen = ds.ins.size();

            //read tables...
            for (int c = 0; c < GT_MAX_TABLES; c++)
            {
                if(reader.size() == reader.tell())
                {
                    logE("premature end of file!");
                    lastError = _("premature end of file!");
                    GT_FREE_MEMORY
                    return false;
                }

                unsigned char loadsize = reader.readC();

                if(reader.size() - reader.tell() < (size_t)loadsize * 2)
                {
                    logE("premature end of file!");
                    lastError = _("premature end of file!");
                    GT_FREE_MEMORY
                    return false;
                }

                reader.read(ltable[c], loadsize);
                reader.read(rtable[c], loadsize);
            }

            //read patterns
            if(reader.size() == reader.tell())
            {
                logE("premature end of file!");
                lastError = _("premature end of file!");
                GT_FREE_MEMORY
                return false;
            }
            unsigned char num_patterns = reader.readC();

            for (int c = 0; c < num_patterns; c++)
            {
                if(reader.size() - reader.tell() < 4)
                {
                    logE("premature end of file!");
                    lastError = _("premature end of file!");
                    GT_FREE_MEMORY
                    return false;
                }

                unsigned int length = reader.readC() * 4;

                if(reader.size() - reader.tell() < (size_t)length)
                {
                    logE("premature end of file!");
                    lastError = _("premature end of file!");
                    GT_FREE_MEMORY
                    return false;
                }

                reader.read(pattern[c], length);
            }

            int getNext = 0;
            unsigned char ID = 0;
            unsigned char stereoMode = 0;
            (void)(stereoMode);

            do
            {
                getNext = 0;
                ID = 0;
                // JP - Need to check that this works (previously read into a char array and then copied into uchar...)
                if(reader.size() == reader.tell())
                {
                    /*logE("premature end of file!");
                    lastError = _("premature end of file!");
                    GT_FREE_MEMORY
                    return false;*/
                    break;
                }
                ID = reader.readC();

                // JP: New. Load GTUltra settings (FV/R0/P0/HR/SIDType & Speed)
                if (ID == 0x1f)	// ID for info
                {
                    if(reader.size() - reader.tell() < 9)
                    {
                        logE("premature end of file!");
                        lastError = _("premature end of file!");
                        GT_FREE_MEMORY
                        return false;
                    }
                    editorInfo->usefinevib = reader.readC();		// FV
                    editorInfo->optimizepulse = reader.readC();		// PO
                    editorInfo->optimizerealtime = reader.readC();		// RO
                    editorInfo->ntsc = reader.readC();		// editorInfo.ntsc / PAL
                    editorInfo->sidmodel = reader.readC();	// editorInfo.sidmodel
                    //TODO: replace SID model for all SIDs?
                    editorInfo->adparam = (unsigned int)reader.readI();	// HR
                    editorInfo->multiplier = (unsigned int)reader.readI();	// speed editorInfo.multiplier
                    editorInfo->maxSIDChannels = (int)reader.readI();		// sid channels
                    stereoMode = reader.readC();

                    ds.version = DIV_VERSION_GTULTRA;

                    ds.systemLen = editorInfo->maxSIDChannels / 3;
                    
                    for(int i = 0; i < (int)ds.systemLen; i++)
                    {
                        ds.system[i] = editorInfo->sidmodel ? DIV_SYSTEM_C64_8580 : DIV_SYSTEM_C64_6581;
                    }

                    s->speeds.val[0] = (editorInfo->ntsc ? 60 : 50) * editorInfo->multiplier;

                    //validateStereoMode();
                    //reInitSID();
                    getNext++;
                }

                // JP: New. Load instrument pan info (if it exists)

                if (ID == 0x9a)	// ID for pan
                {
                    for (int c = 0; c < num_instruments; c++)
                    {
                        if(reader.size() == reader.tell())
                        {
                            logE("premature end of file!");
                            lastError = _("premature end of file!");
                            GT_FREE_MEMORY
                            return false;
                        }
                        gt_insts[c].pan = reader.readC();
                    }
                    getNext++;
                }

                if (ID == 0x9b)
                {
                    if(reader.size() == reader.tell())
                    {
                        logE("premature end of file!");
                        lastError = _("premature end of file!");
                        GT_FREE_MEMORY
                        return false;
                    }
                    unsigned char SIDTracker64ForIPadIsAmazing = reader.readC();
                    (void)(SIDTracker64ForIPadIsAmazing);
                    getNext++;
                }
            } while (getNext != 0);
        }

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

        GT_FREE_MEMORY
    }
    catch (EndOfFileException& e) 
    {
        logE("premature end of file!");
        lastError=_("incomplete file");
        GT_FREE_MEMORY
        return false;
    }

    return true;
}
