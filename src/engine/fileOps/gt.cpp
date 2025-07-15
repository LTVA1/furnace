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
    char name[GT_MAX_INSTRNAMELEN + 1];
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

static int findEmptyEffectSlot(short* data)
{
    for(int i = 0; i < DIV_MAX_EFFECTS; i++)
    {
        if(data[4 + i * 2] == -1)
        {
            return i;
        }
    }

    return -1;
}

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

void GT_import_effect(short* data, int effect, unsigned char* speedtable_r, unsigned char* speedtable_l)
{
    switch((effect >> 8) & 0xFF)
    {
        case 1:
        case 2:
        {
            data[4] = (effect >> 8) & 0xFF;
            unsigned int spd = ((speedtable_r[effect & 0xFF] | ((unsigned int)speedtable_l[effect & 0xFF] << 8)) / 8);
            data[5] = spd > 0xFF ? 0xFF : spd;
            break;
        }
        case 3:
        {
            data[4] = (effect >> 8) & 0xFF;

            if((effect & 0xFF) != 0)
            {
                unsigned int spd = ((speedtable_r[effect & 0xFF] | ((unsigned int)speedtable_l[effect & 0xFF] << 8)) / 8);
                data[5] = spd > 0xFF ? 0xFF : spd;
            }
            else
            {
                data[5] = 0xFF;
            }
            break;
        }
        case 4:
        {
            data[4] = (effect >> 8) & 0xFF;
            data[5] = ((((0xFF - speedtable_l[effect & 0xFF]) >> 4) & 0xF) << 4) | (speedtable_r[effect & 0xFF] >> 4);
            break;
        }
        case 5:
        {
            data[4] = 0x20;
            data[5] = effect & 0xFF;
            break;
        }
        case 6:
        {
            data[4] = 0x21;
            data[5] = effect & 0xFF;
            break;
        }
        case 7:
        {
            data[4] = 0x10;
            data[5] = ((effect >> 4) & 0xF); //TODO: deal with ringmod/gate/etc.
            break;
        }

        //TODO: what to do with other effects?

        case 0xB:
        {
            data[4] = 0x13;
            data[5] = ((effect >> 4) & 0xF); //resonance

            for(int i = 0; i < 3; i++)
            {
                int emptyEffSlot = findEmptyEffectSlot(data);
                data[4 + emptyEffSlot * 2] = 0x1E;
                data[5 + emptyEffSlot * 2] = ((7 + i) << 4) | ((effect & (1 << i)) ? 1 : 0);
            }
            
            break;
        }
        case 0xC:
        {
            data[4] = 0x40 | ((((effect & 0xFF) << 3) & 0x300) >> 8);
            data[5] = ((effect & 0xFF) << 3) & 0xFF; //cutoff
            break;
        }
        case 0xD:
        {
            if(((effect >> 4) & 0xF) == 0)
            {
                data[3] = effect & 0xF; //master volume
            }
            break;
        }
        default: break;
    }
}

#define GT_FREE_MEMORY \
delete[] file; \
delete[] songorder; \
delete[] songorder_len; \
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
    auto songorder_len = new unsigned char[32][6];
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
                    songorder_len[song][c] = loadsize;
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
                gt_insts[i].vibdelay = reader.readC(); // TODO: can this be approximated by pattern effects?
                gt_insts[i].gatetimer = reader.readC();
                gt_insts[i].firstwave = reader.readC();
                reader.read(gt_insts[i].name, GT_MAX_INSTRNAMELEN);
                gt_insts[i].name[GT_MAX_INSTRNAMELEN] = '\0';

                ins->name = gt_insts[i].name;

                DivInstrumentMacro* wave = &ins->std.waveMacro;
                DivInstrumentMacro* arp = &ins->std.arpMacro;
                DivInstrumentMacro* gate = &ins->std.ex4Macro;
                DivInstrumentMacro* duty = &ins->std.dutyMacro;
                DivInstrumentMacro* filter = &ins->std.algMacro;
                DivInstrumentMacro* filter_type = &ins->std.ex1Macro;
                DivInstrumentMacro* filter_resonance = &ins->std.ex2Macro;

                ins->c64.dutyIsAbs = true;
                ins->c64.filterIsAbs = true;

                ins->c64.oscSync = (gt_insts[i].firstwave & (1 << 1)) ? 1 : 0;
                ins->c64.ringMod = (gt_insts[i].firstwave & (1 << 2)) ? 1 : 0;
                ins->c64.noTest = (gt_insts[i].firstwave & (1 << 3)) ? 0 : 1;

                ins->c64.triOn = (gt_insts[i].firstwave & (1 << 4)) ? 1 : 0;
                ins->c64.sawOn = (gt_insts[i].firstwave & (1 << 5)) ? 1 : 0;
                ins->c64.pulseOn = (gt_insts[i].firstwave & (1 << 6)) ? 1 : 0;
                ins->c64.noiseOn = (gt_insts[i].firstwave & (1 << 7)) ? 1 : 0;

                ins->c64.toFilter = gt_insts[i].ptr[FTBL] > 0 ? true : false;
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
            
            //adapt tables into instrument macros where possible
            //thnx AnnoyedArt1256
            for(int i = 0; i < num_instruments; i++)
            {
                DivInstrument* ins = ds.ins[i];

                DivInstrumentMacro* wave = &ins->std.waveMacro;
                DivInstrumentMacro* arp = &ins->std.arpMacro;
                DivInstrumentMacro* gate = &ins->std.ex4Macro;
                DivInstrumentMacro* duty = &ins->std.dutyMacro;
                DivInstrumentMacro* filter = &ins->std.algMacro;
                DivInstrumentMacro* filter_type = &ins->std.ex1Macro;
                DivInstrumentMacro* filter_resonance = &ins->std.ex2Macro;

                DivInstrumentMacro* attack = &ins->std.ex5Macro;
                DivInstrumentMacro* decay = &ins->std.ex6Macro;
                DivInstrumentMacro* sustain = &ins->std.ex7Macro;
                DivInstrumentMacro* release = &ins->std.ex8Macro;

                int wav_pointer = gt_insts[i].ptr[WTBL];
                int macros_pointer = 0;
                unsigned char delay = 0;

                unsigned char curwav = gt_insts[i].firstwave;
                unsigned int arpval = 0;

                unsigned char ptr_loop = wav_pointer;

                int ins_loop = 1;

                bool use_a_macro = false;
                bool use_d_macro = false;
                bool use_s_macro = false;
                bool use_r_macro = false;

                unsigned char cur_a = ins->c64.a;
                unsigned char cur_d = ins->c64.d;
                unsigned char cur_s = ins->c64.s;
                unsigned char cur_r = ins->c64.r;

                for (int tick = 0; tick < 256; tick++) 
                {
                    if (delay == 0 && tick) 
                    {
                        unsigned char left = ltable[WTBL][wav_pointer];
                        unsigned char right = rtable[WTBL][wav_pointer];

                        if (left <= 0xEF) 
                        {
                            // arpeggio
                            if (right <= 0x5F) 
                            {
                                // relative notes
                                arpval = right;
                            } 
                            else if (right <= 0x7F) 
                            {
                                arpval = -(0x7F - right) - 1;
                            } 
                            else if (right >= 0x81 && right <= 0xDF) 
                            {
                                arpval=((right - 0x81) + 1) ^ 0x40000000;
                            }
                        }
                        if (left == 0) 
                        {
                            // no change
                            wav_pointer++;
                        } 
                        else if (left >= 1 && left <= 15) 
                        {
                            // delay by N frames
                            delay = left&0xf;
                            wav_pointer++;
                        } 
                        else if (left >= 0x10 && left <= 0xDF) 
                        {
                            // waveform $10-$DF
                            curwav = left;
                            wav_pointer++;
                        } 
                        else if (left >= 0xE0 && left <= 0xEF)
                        {
                            // waveform $00-$0F (INAUDIBLE)
                            curwav = 0x00;
                            wav_pointer++;
                        } 
                        else if (left >= 0xF0 && left <= 0xFE) 
                        {
                            if(left == 0xF5) //attack + decay
                            {   
                                use_a_macro = true;
                                use_d_macro = true;

                                cur_a = right >> 4;
                                cur_d = right & 0xF;
                            }
                            if(left == 0xF6) //sustain + release
                            {
                                use_s_macro = true;
                                use_r_macro = true;

                                cur_s = right >> 4;
                                cur_r = right & 0xF;
                            }
                            wav_pointer++;
                        }  
                        else if (left == 0xFF) 
                        {
                            // jump to $NN
                            if (right == 0) break;
                            else 
                            {
                                if (right == ptr_loop) 
                                {
                                    wave->loop = ins_loop;
                                    arp->loop = ins_loop;
                                    gate->loop = ins_loop;

                                    attack->loop = ins_loop;
                                    decay->loop = ins_loop;
                                    sustain->loop = ins_loop;
                                    release->loop = ins_loop;
                                    break;
                                }

                                ins_loop = tick;
                                ptr_loop = right;
                                wav_pointer = right;
                            }
                        }
                    } 
                    else if (tick) 
                    {
                        delay--;
                    }

                    wave->len = tick + 1;
                    arp->len = tick + 1;
                    gate->len = tick + 1;
                    wave->val[tick] = (curwav >> 4) & 0xf;
                    gate->val[tick] = curwav & 0xf;
                    arp->val[tick] = arpval;

                    attack->val[tick] = cur_a;
                    decay->val[tick] = cur_d;
                    sustain->val[tick] = cur_s;
                    release->val[tick] = cur_r;

                    if(use_a_macro) attack->len = tick + 1;
                    if(use_d_macro) decay->len = tick + 1;
                    if(use_s_macro) sustain->len = tick + 1;
                    if(use_r_macro) release->len = tick + 1;
                }

                int pulse_pointer = gt_insts[i].ptr[PTBL];
                unsigned short curpulse = 0x800;
                signed char sweep_amt = 0;
                delay = 0;
                ptr_loop = pulse_pointer;
                ins_loop=1;

                for (int tick=0;tick<256;tick++) 
                {
                    if (pulse_pointer == 0) break;

                    if (delay==0) 
                    {
                        //unsigned char left=(pulsetable[pulse_pointer]>>8)&0xff;
                        //unsigned char right=pulsetable[pulse_pointer]&0xff;
                        unsigned char left = ltable[PTBL][pulse_pointer];
                        unsigned char right = rtable[PTBL][pulse_pointer];

                        if (left == 0xFF) 
                        {
                            // jump to $NN
                            if (right == 0) break;
                            else 
                            {
                                if (right == ptr_loop) 
                                {
                                    duty->loop=ins_loop;
                                    break;
                                }
                                ins_loop=tick;
                                ptr_loop=right;
                                pulse_pointer=right;
                            }
                        } 
                        else if (left & 0x80) 
                        {
                            // set pulse
                            curpulse=left | ((right & 0xF) << 8);
                            pulse_pointer++;
                            sweep_amt=0;
                        } 
                        else 
                        {
                            // sweep pulse
                            delay=left-1;
                            sweep_amt=(int8_t)right;
                            pulse_pointer++;
                        }
                    } 
                    else if (tick) 
                    {
                        delay--;
                    }
                    curpulse += (int8_t)sweep_amt;
                    duty->len=tick+1;
                    duty->val[tick]=curpulse;
                }

                int filter_pointer = gt_insts[i].ptr[FTBL];
                unsigned char curfilt=0;
                unsigned char curfiltype=0;
                unsigned char curres=0;
                delay=0;
                ptr_loop=filter_pointer;
                ins_loop=1;
                unsigned char updated_type=0;
                unsigned char real_tick=1;
                sweep_amt = 0;

                for (int tick=0;tick<256;tick++) 
                {
                    if (filter_pointer == 0) break;

                    if (delay==0) 
                    {
                        //unsigned char left=(filtertable[filter_pointer]>>8)&0xff;
                        //unsigned char right=filtertable[filter_pointer]&0xff;
                        unsigned char left = ltable[FTBL][filter_pointer];
                        unsigned char right = rtable[FTBL][filter_pointer];

                        if (left == 0xFF) 
                        {
                            // jump to $NN
                            if (right == 0) break;
                            else 
                            {
                                if (right == ptr_loop) 
                                {
                                    filter->loop=ins_loop;
                                    filter_type->loop=ins_loop;
                                    filter_resonance->loop=ins_loop;
                                    break;
                                }

                                ins_loop=tick;
                                ptr_loop=right;
                                filter_pointer=right;
                            }
                        } 
                        else if (left == 0) 
                        {
                            // set cutoff
                            curfilt=right;
                            filter_pointer++;
                            sweep_amt=0;
                        } 
                        else if (left & 0x80) 
                        {
                            // set filter usage/resonance
                            if (!updated_type) 
                            {
                                filter_type->len=real_tick+1;
                                for (int i=0; i<real_tick; i++)
                                {
                                    filter_type->val[i]=0;
                                }
                            }

                            updated_type=1;
                            curfiltype=(left>>4)&0x7;
                            curres=(right>>4)&0xf;
                            filter_pointer++;
                            continue;
                        } 
                        else 
                        {
                            // sweep cutoff
                            delay = left-1;
                            sweep_amt = (signed char)right;
                            filter_pointer++;
                        }
                    } 
                    else if (tick) 
                    {
                        delay--;
                    }

                    curfilt += (signed char)sweep_amt;
                    filter->len = real_tick+1;
                    filter->val[real_tick] = ((unsigned short)curfilt) << 3;

                    if (updated_type) 
                    {
                        filter_type->len=real_tick+1;
                        filter_type->val[real_tick]=curfiltype&15;
                    }

                    filter_resonance->len=real_tick+1;
                    filter_resonance->val[real_tick]=curres&15;
                    real_tick++;
                }
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

                unsigned char what_the = reader.readC();
                unsigned int length = (unsigned int)what_the * 4;

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

            bool gtultra = false;

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

                    gtultra = true;

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

            //import orders... the best way it could be done, I believe?
            for(int i = 0; i < num_subsongs;)
            {
                auto subsong_orders = songorder[i];
                DivSubSong* s1 = ds.subsong[i];

                int max_orders_len = 0;
                
                for(int ch = 0; ch < (((int)ds.systemLen * 3 > 6) ? 6 : (int)ds.systemLen * 3); ch++)
                {
                    int orderpos = 0;
                    max_orders_len = 0;

                    for(int pos = 0; ; )
                    {
                        int posinc = 0;

                        if(subsong_orders[ch][pos] <= 0xCF)
                        {
                            max_orders_len++;
                            s1->orders.ord[ch][orderpos] = subsong_orders[ch][pos];
                            orderpos++;
                            posinc++;
                        }
                        if(subsong_orders[ch][pos] >= 0xD0 && subsong_orders[ch][pos] <= 0xDF)
                        {
                            max_orders_len += subsong_orders[ch][pos] - 0xCF;

                            for(int rep = 0; rep < subsong_orders[ch][pos] - 0xCF; rep++)
                            {
                                s1->orders.ord[ch][orderpos] = subsong_orders[ch][pos + 1];
                                orderpos++;
                            }
                            
                            posinc += 2;
                        }
                        if(subsong_orders[ch][pos] >= 0xE0 && subsong_orders[ch][pos] <= 0xFE)
                        {
                            posinc++; //skip?
                            //TODO: can I properly handle transpose note data?
                        }
                        if(subsong_orders[ch][pos] == 0xFF)
                        {
                            posinc += 2; //skip?
                            //TODO: can I properly handle restart marker?
                        }

                        pos += posinc;

                        if(pos >= songorder_len[i][ch]) break;
                    }

                    if(max_orders_len > s1->ordersLen) s1->ordersLen = max_orders_len;
                }

                if(gtultra && editorInfo->maxSIDChannels > 6)
                {
                    auto subsong2_orders = songorder[i + 1];

                    //DivSubSong* s2 = ds.subsong[i + 1];

                    for(int ch = 0; ch < ((editorInfo->maxSIDChannels == 12) ? 6 : 3); ch++)
                    {
                        int orderpos = 0;
                        max_orders_len = 0;

                        for(int pos = 0; ; )
                        {
                            int posinc = 0;

                            if(subsong2_orders[ch][pos] <= 0xCF)
                            {
                                max_orders_len++;
                                s1->orders.ord[ch + 6][orderpos] = subsong2_orders[ch][pos];
                                orderpos++;
                                posinc++;
                            }
                            if(subsong2_orders[ch][pos] >= 0xD0 && subsong2_orders[ch][pos] <= 0xDF)
                            {
                                max_orders_len += subsong2_orders[ch][pos] - 0xCF;

                                for(int rep = 0; rep < subsong2_orders[ch][pos] - 0xCF; rep++)
                                {
                                    s1->orders.ord[ch + 6][orderpos] = subsong2_orders[ch][pos + 1];
                                    orderpos++;
                                }
                                
                                posinc += 2;
                            }
                            if(subsong2_orders[ch][pos] >= 0xE0 && subsong2_orders[ch][pos] <= 0xFE)
                            {
                                posinc++; //skip?
                                //TODO: can I properly handle transpose note data?
                            }
                            if(subsong2_orders[ch][pos] == 0xFF)
                            {
                                posinc += 2; //skip?
                                //TODO: can I properly handle restart marker?
                            }

                            pos += posinc;

                            if(pos >= songorder_len[i + 1][ch]) break;
                        }

                        if(max_orders_len > s1->ordersLen) s1->ordersLen = max_orders_len; //TODO: handle loops in orders and fill in missing info if one subsong is longer???
                    }
                }

                if(gtultra && editorInfo->maxSIDChannels > 6) i += 2;
                else i++;
            }

            //import patterns
            for(int subs = 0; subs < (int)ds.subsong.size(); subs++)
            {
                int max_pat_len = 0;

                for(int p = 0; p < num_patterns; p++)
                {
                    int row = 0;

                    DivPattern* patterns[12];

                    for(int ch = 0; ch < ds.systemLen * 3; ch++)
                    {
                        patterns[ch] = ds.subsong[subs]->pat[ch].getPattern(p, true);
                    }

                    int pat_pointer = 0;

                    while(row < 128)
                    {
                        int note = pattern[p][pat_pointer];
                        int instrument = pattern[p][pat_pointer + 1];
                        int effect = (pattern[p][pat_pointer + 2] << 8) | pattern[p][pat_pointer + 3];

                        if(note == 0xFF) 
                        {
                            if(row > 0)
                            {
                                for(int ch = 0; ch < ds.systemLen * 3; ch++)
                                {
                                    int emptyEffSlot = findEmptyEffectSlot(patterns[ch]->data[row - 1]);

                                    patterns[ch]->data[row - 1][4 + emptyEffSlot * 2] = 0x0D;
                                    patterns[ch]->data[row - 1][5 + emptyEffSlot * 2] = 0;
                                }
                            }
                            break; //pattern end
                        }

                        int furnace_note = 0;
                        int furnace_octave = 0;

                        if(note >= 0x60 && note <= 0xBC)
                        {
                            furnace_note = (note - 0x60) % 12;
                            furnace_octave = (note - 0x60) / 12;

                            if(((note - 0x60) % 12) == 0 && note > 0x60 && furnace_octave != 0)
                            {
                                furnace_note = 12; //what the fuck?
                                furnace_octave--;
                            }
                            if(note == 0x60)
                            {
                                furnace_note = 12;
                                furnace_octave = -1;
                            }
                        }
                        if(note == 0xBE) //key off
                        {
                            furnace_note = 101;
                        }

                        //TODO: 0xBF is key-on, how you deal with it????

                        for(int ch = 0; ch < ds.systemLen * 3; ch++)
                        {
                            patterns[ch]->data[row][0] = furnace_note;
                            patterns[ch]->data[row][1] = furnace_octave;

                            patterns[ch]->data[row][2] = instrument - 1;

                            if((effect >> 8) > 0)
                            {
                                GT_import_effect(patterns[ch]->data[row], effect, rtable[STBL], ltable[STBL]);
                                //patterns[ch]->data[row][4] = effect >> 8;
                                //patterns[ch]->data[row][5] = effect & 0xFF;
                            }
                        }

                        pat_pointer += 4;
                        row++;
                    }

                    if(max_pat_len < row) max_pat_len = row;
                }

                ds.subsong[subs]->patLen = max_pat_len;
            }
        }

        // open hidden effect columns
        for(int subs = 0; subs < (int)ds.subsong.size(); subs++)
        {
            DivSubSong* s = ds.subsong[subs];

            for (int c = 0; c < ds.systemLen * 3; c++) 
            {
                int num_fx = 1;

                for (int p = 0; p < s->ordersLen; p++)
                {
                    for (int r = 0; r < s->patLen; r++) 
                    {
                        DivPattern* pat = s->pat[c].getPattern(s->orders.ord[c][p], true);
                        short* s_row_data = pat->data[r];

                        for (int eff = 0; eff < DIV_MAX_EFFECTS - 1; eff++) 
                        {
                            if (s_row_data[4 + 2 * eff] != -1 && eff + 1 > num_fx) 
                            {
                                num_fx = eff + 1;
                            }
                        }
                    }
                }

                s->pat[c].effectCols = num_fx;
            }
        }

        ds.linearPitch = 0;
        ds.pitchMacroIsLinear = false;
        ds.pitchSlideSpeed = 8;

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
