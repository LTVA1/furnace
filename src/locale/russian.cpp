#include <map>
#include <string>
#include "locale.h"

#include "russian.h"

int getPluralIndexRussian(int n)
{
    return (n%10==1 && n%100!=11) ? 0 : ((n%10>=2 && n%10<=4 && (n%100<10 || n%100>=20)) ? 1 : 2);
    //here you can provide plural forms indices based on the integer.
    //you can find one-liners for common languages here:
    //https://www.gnu.org/software/gettext/manual/html_node/Plural-forms.html
    //these would need some adaptation to work in this code
}

static const ImGuiLocEntry GLocalizationEntriesRuRU[] =
{
    { ImGuiLocKey_VersionStr,           "Dear ImGui " IMGUI_VERSION " (" IM_STRINGIFY(IMGUI_VERSION_NUM) ")" },
    { ImGuiLocKey_TableSizeOne,         "Масштабировать столбец по размеру###SizeOne"           },
    { ImGuiLocKey_TableSizeAllFit,      "Масштабировать все столбцы по размеру###SizeAll"       },
    { ImGuiLocKey_TableSizeAllDefault,  "Масштабировать все столбцы по умолчанию###SizeAll"     },
    { ImGuiLocKey_TableResetOrder,      "Сбросить порядок###ResetOrder"                         },
    { ImGuiLocKey_WindowingMainMenuBar, "(полоса главного меню)"                                },
    { ImGuiLocKey_WindowingPopup,       "(Всплывающее окно)"                                    },
    { ImGuiLocKey_WindowingUntitled,    "(Без названия)"                                        },
    { ImGuiLocKey_DockingHideTabBar,    "Скрыть полосу с вкладками###HideTabBar"                },
};

class DivLocale;

void DivLocale::addTranslationsRussian()
{
    // everything in a string after the ## or ### must remain as is
    // example: Sparkles!##sgab1 means the second instance of "Sparkles!"
    //   in `src/gui/about.cpp`.

    ImGui::LocalizeRegisterEntries(GLocalizationEntriesRuRU, IM_ARRAYSIZE(GLocalizationEntriesRuRU));

    strings["%d apple"].plurals[0] = "%d яблоко";
    strings["%d apple"].plurals[1] = "%d яблока";
    strings["%d apple"].plurals[2] = "%d яблок";

    //strings["Yamaha YM2151 (OPM)"].plurals[0] = "opmopmopmёшгывргшуыкп";
    strings["this was Yamaha's first integrated FM chip.\nit was used in several synthesizers, computers and arcade boards."].plurals[0] = "этот чип был первой интегральной микросхемой Yamaha.\nОн использовался в нескольких синтезаторах, компьютерах и аркадных автоматах.";

    //src/gui/about.cpp

    strings["About Furnace###About Furnace"].plurals[0] = "О Furnace";

    strings["and Furnace-B developers##sgab"].plurals[0] = "и разработчики Furnace-B";
    strings["are proud to present##sgab"].plurals[0] = "с гордостью представляют";
    strings["the biggest multi-system chiptune tracker!##sgab"].plurals[0] = "самый большой мультисистемный чиптюн-трекер!";
    strings["featuring DefleMask song compatibility.##sgab"].plurals[0] = "совместим с файлами Deflemask.";

    strings["> CREDITS <##sgab"].plurals[0] = "> ТИТРЫ <";
    strings["-- program --##sgab"].plurals[0] = "-- код --";
    strings["A M 4 N (intro tune)##sgab"].plurals[0] = "A M 4 N (музыка в интро)";
    strings["-- graphics/UI design --##sgab"].plurals[0] = "-- графика/дизайн интерфейса --";
    strings["-- documentation --##sgab"].plurals[0] = "-- документация --";
    strings["-- demo songs --##sgab"].plurals[0] = "-- демо-модули --";
    strings["-- additional feedback/fixes --##sgab"].plurals[0] = "-- обратная связь/фиксы --";
    strings["-- translations and related work --##sgab"].plurals[0] = "-- переводы и связанное с ними --";
    strings["LTVA1 (Russian translation)##sgab"].plurals[0] = "LTVA1 (перевод на русский язык)";

    strings["powered by:##sgab"].plurals[0] = "программа использует:";
    strings["Dear ImGui by Omar Cornut##sgab"].plurals[0] = "Dear ImGui за авторством Omar Cornut";
    strings["SDL2 by Sam Lantinga##sgab"].plurals[0] = "SDL2 за авторством Sam Lantinga";
    strings["zlib by Jean-loup Gailly##sgab"].plurals[0] = "zlib за авторством Jean-loup Gailly";
    strings["and Mark Adler##sgab"].plurals[0] = "и Mark Adler";
    strings["libsndfile by Erik de Castro Lopo##sgab"].plurals[0] = "libsndfile за авторством Erik de Castro Lopo";
    strings["Portable File Dialogs by Sam Hocevar##sgab"].plurals[0] = "Portable File Dialogs за авторством Sam Hocevar";
    strings["Native File Dialog by Frogtoss Games##sgab"].plurals[0] = "Native File Dialog за авторством Frogtoss Games";
    strings["Weak-JACK by x42##sgab"].plurals[0] = "Weak-JACK за авторством x42";
    strings["RtMidi by Gary P. Scavone##sgab"].plurals[0] = "RtMidi за авторством Gary P. Scavone";
    strings["FFTW by Matteo Frigo and Steven G. Johnson##sgab"].plurals[0] = "FFTW за авторством Matteo Frigo и Steven G. Johnson";
    strings["backward-cpp by Google##sgab"].plurals[0] = "backward-cpp за авторством Google";
    strings["adpcm by superctr##sgab"].plurals[0] = "adpcm за авторством superctr";
    strings["Nuked-OPL3/OPLL/OPM/OPN2/PSG by nukeykt##sgab"].plurals[0] = "Nuked-OPL3/OPLL/OPM/OPN2/PSG за авторством nukeykt";
    strings["YM3812-LLE, YMF262-LLE and YMF276-LLE by nukeykt##sgab"].plurals[0] = "YM3812-LLE, YMF262-LLE и YMF276-LLE за авторством nukeykt";
    strings["ymfm by Aaron Giles##sgab"].plurals[0] = "ymfm за авторством Aaron Giles";
    strings["MAME SN76496 by Nicola Salmoria##sgab"].plurals[0] = "MAME SN76496 за авторством Nicola Salmoria";
    strings["MAME AY-3-8910 by Couriersud##sgab"].plurals[0] = "MAME AY-3-8910 за авторством Couriersud";
    strings["with AY8930 fixes by Eulous, cam900 and Grauw##sgab"].plurals[0] = "с исправлениями для AY8930 за авторством Eulous, cam900 и Grauw";
    strings["MAME SAA1099 by Juergen Buchmueller and Manuel Abadia##sgab"].plurals[0] = "MAME SAA1099 за авторством Juergen Buchmueller и Manuel Abadia";
    strings["MAME Namco WSG by Nicola Salmoria and Aaron Giles##sgab"].plurals[0] = "MAME Namco WSG за авторством Nicola Salmoria и Aaron Giles";
    strings["MAME RF5C68 core by Olivier Galibert and Aaron Giles##sgab"].plurals[0] = "MAME RF5C68 core за авторством Olivier Galibert и Aaron Giles";
    strings["MAME MSM5232 core by Jarek Burczynski and Hiromitsu Shioya##sgab"].plurals[0] = "MAME MSM5232 core за авторством Jarek Burczynski и Hiromitsu Shioya";
    strings["MAME MSM6258 core by Barry Rodewald##sgab"].plurals[0] = "MAME MSM6258 core за авторством Barry Rodewald";
    strings["MAME YMZ280B core by Aaron Giles##sgab"].plurals[0] = "MAME YMZ280B core за авторством Aaron Giles";
    strings["MAME GA20 core by Acho A. Tang and R. Belmont##sgab"].plurals[0] = "MAME GA20 core за авторством Acho A. Tang и R. Belmont";
    strings["MAME SegaPCM core by Hiromitsu Shioya and Olivier Galibert##sgab"].plurals[0] = "MAME SegaPCM core за авторством Hiromitsu Shioya и Olivier Galibert";
    strings["SAASound by Dave Hooper and Simon Owen##sgab"].plurals[0] = "SAASound за авторством Dave Hooper и Simon Owen";
    strings["SameBoy by Lior Halphon##sgab"].plurals[0] = "SameBoy за авторством Lior Halphon";
    strings["Mednafen PCE, WonderSwan, T6W28 and Virtual Boy audio cores##sgab"].plurals[0] = "Ядра эмуляции Mednafen PCE, WonderSwan, T6W28 и Virtual Boy";
    strings["SNES DSP core by Blargg##sgab"].plurals[0] = "SNES DSP core за авторством Blargg";
    strings["puNES (NES, MMC5 and FDS) by FHorse##sgab"].plurals[0] = "puNES (NES, MMC5 и FDS) за авторством FHorse";
    strings["NSFPlay (NES and FDS) by Brad Smith and Brezza##sgab"].plurals[0] = "NSFPlay (NES and FDS) за авторством Brad Smith и Brezza";
    strings["reSID by Dag Lem##sgab"].plurals[0] = "reSID за авторством Dag Lem";
    strings["reSIDfp by Dag Lem, Antti Lankila##sgab"].plurals[0] = "reSIDfp за авторством Dag Lem, Antti Lankila";
    strings["and Leandro Nini##sgab"].plurals[0] = "и Leandro Nini";
    strings["dSID by DefleMask Team based on jsSID##sgab"].plurals[0] = "dSID за авторством команды DefleMask (на основе jsSID)";
    strings["Stella by Stella Team##sgab"].plurals[0] = "Stella за авторством Stella Team";
    strings["QSound emulator by superctr and Valley Bell##sgab"].plurals[0] = "Эмулятор QSound за авторством superctr и Valley Bell";
    strings["VICE VIC-20 sound core by Rami Rasanen and viznut##sgab"].plurals[0] = "Ядро эмуляции VICE VIC-20 за авторством Rami Rasanen и viznut";
    strings["VICE TED sound core by Andreas Boose, Tibor Biczo##sgab"].plurals[0] = "Ядро эмуляции VICE TED за авторством Andreas Boose, Tibor Biczo";
    strings["and Marco van den Heuvel##sgab"].plurals[0] = "и Marco van den Heuvel";
    strings["VERA sound core by Frank van den Hoef##sgab"].plurals[0] = "Ядро эмуляции VERA за авторством Frank van den Hoef";
    strings["mzpokeysnd POKEY emulator by Michael Borisov##sgab"].plurals[0] = "mzpokeysnd (эмулятор POKEY) за авторством Michael Borisov";
    strings["ASAP POKEY emulator by Piotr Fusik##sgab"].plurals[0] = "ASAP (эмулятор POKEY) за авторством Piotr Fusik";
    strings["ported by laoo to C++##sgab"].plurals[0] = "портирован на C++ laoo";
    strings["vgsound_emu (second version, modified version) by cam900##sgab"].plurals[0] = "vgsound_emu (версия вторая, модифицированная) за авторством cam900";
    strings["SM8521 emulator (modified version) by cam900##sgab"].plurals[0] = "Эмулятор SM8521 (модифицированная версия) за авторством cam900";
    strings["D65010G031 emulator (modified version) by cam900##sgab"].plurals[0] = "Эмулятор D65010G031 (модифицированная версия) за авторством cam900";
    strings["Namco C140/C219 emulator (modified version) by cam900##sgab"].plurals[0] = "Эмулятор C140/C219 (модифицированная версия) за авторством cam900";
    strings["ESFMu emulator by Kagamiin~##sgab"].plurals[0] = "Эмулятор ESFMu за авторством Kagamiin~";
    strings["PowerNoise emulator by scratchminer##sgab"].plurals[0] = "Эмулятор PowerNoise за авторством scratchminer";

    strings["greetings to:##sgab"].plurals[0] = "передаём привет:";
    strings["NEOART Costa Rica##sgab"].plurals[0] = "NEOART Costa Rica";
    strings["Xenium Demoparty##sgab"].plurals[0] = "Демопати Xenium";
    strings["all members of Deflers of Noice!##sgab"].plurals[0] = "всем участникам Deflers of Noice!";

    strings["copyright © 2021-2024 tildearrow##sgab"].plurals[0] = "Все права защищены © 2021-2024 tildearrow";
    strings["(and contributors).##sgab"].plurals[0] = "(и участники разработки).";
    strings["licensed under GPLv2+! see##sgab"].plurals[0] = "лицензировано по GPLv2+! см.";
    strings["LICENSE for more information.##sgab"].plurals[0] = "LICENSE для доп. информации.";

    strings["help Furnace grow:##sgab"].plurals[0] = "помогите в развитии Furnace:";
    strings["help Furnace-B:##sgab"].plurals[0] = "помогите в развитии Furnace-B:";

    strings["contact tildearrow at:##sgab"].plurals[0] = "вы можете связаться с tildearrow:";

    strings["disclaimer:##sgab"].plurals[0] = "внимание:";
    strings["despite the fact this program works##sgab"].plurals[0] = "несмотря на то что эта программа работает";
    strings["with the .dmf file format, it is NOT##sgab"].plurals[0] = "с файлами формата .dmf, она НЕ";
    strings["affiliated with Delek or DefleMask in##sgab"].plurals[0] = "связана с Delek'ом или программой DefleMask,";
    strings["any way, nor it is a replacement for##sgab"].plurals[0] = "и не является заменой";
    strings["the original program.##sgab"].plurals[0] = "оригинальной программы.";

    strings["it also comes with ABSOLUTELY NO WARRANTY.##sgab"].plurals[0] = "она также предоставляется БЕЗ КАКИХ-ЛИБО ГАРАНТИЙ.";

    strings["thanks to all contributors/bug reporters!##sgab"].plurals[0] = "спасибо всем, кто помогает с разработкой и сообщает о багах!";

    //src/gui/channels.cpp

    strings["Pat##sgch"].plurals[0] = "Пат.";
    strings["Osc##sgch"].plurals[0] = "Осц.";
    strings["Swap##sgch"].plurals[0] = "Перем.";
    strings["Name##sgch"].plurals[0] = "Имя";
    strings["Show in pattern##sgch"].plurals[0] = "Показывать в окне паттернов";
    strings["Show in per-channel oscilloscope##sgch"].plurals[0] = "Показывать в окне осциллографов (для отдельных каналов)";
    strings["%s #%d\n(drag to swap channels)##sgch"].plurals[0] = "%s #%d\n(перетащите, чтобы поменять местами каналы)";

    //src/gui/chanOsc.cpp

    strings["None (0%)##sgco"].plurals[0] = "Нет (0%)";
    strings["None (50%)##sgco"].plurals[0] = "Нет (50%)";
    strings["None (100%)##sgco"].plurals[0] = "Нет (100%)";
    strings["Frequency##sgco"].plurals[0] = "Частота";
    strings["Volume##sgco"].plurals[0] = "Громкость";
    strings["Channel##sgco"].plurals[0] = "Канал";
    strings["Brightness##sgco"].plurals[0] = "Яркость";
    strings["Note Trigger##sgco"].plurals[0] = "Новая нота";
    strings["Off##sgco"].plurals[0] = "Выкл.";
    strings["Mode 1##sgco"].plurals[0] = "Режим 1";
    strings["Mode 2##sgco"].plurals[0] = "Режим 2";
    strings["Mode 3##sgco"].plurals[0] = "Режим 3";

    strings["Columns##sgco"].plurals[0] = "Столбцов";
    strings["Size (ms)##sgco"].plurals[0] = "Ширина (в мс)";
    strings["Automatic columns##sgco"].plurals[0] = "Автоматическое число столбцов";
    strings["Center waveform##sgco"].plurals[0] = "Центрировать сигнал";
    strings["Randomize phase on note##sgco"].plurals[0] = "Случайная фаза при запуске ноты";
    strings["Amplitude##sgco"].plurals[0] = "Амплитуда";
    strings["Gradient##sgco"].plurals[0] = "Градиент";
    strings["Color##sgco0"].plurals[0] = "Цвет";
    strings["Distance##sgco"].plurals[0] = "Расстояние";
    strings["Spread##sgco"].plurals[0] = "Размыть";
    strings["Remove##sgco"].plurals[0] = "Убрать";
    strings["Background##sgco"].plurals[0] = "Цвет фона";
    strings["X Axis##AxisX"].plurals[0] = "Ось X##AxisX";
    strings["Y Axis##AxisY"].plurals[0] = "Ось Y##AxisY";
    strings["Color##sgco1"].plurals[0] = "Цвет";
    strings["Text format:##sgco"].plurals[0] = "Форматирование текста:";

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

            "инструкция по форматированию:\n"
            "- %c: имя канала\n"
            "- %C: короткое имя канала\n"
            "- %d: номер канала (начиная с 0)\n"
            "- %D: номер канала (начиная с 1)\n"
            "- %n: нота канала\n"
            "- %i: название инструмента\n"
            "- %I: номер инструмента (десятеричный)\n"
            "- %x: номер инструмента (шестнадцатеричный)\n"
            "- %s: название чипа\n"
            "- %p: настоящее название чипа\n"
            "- %S: идентификатор чипа\n"
            "- %v: громкость (десятеричная)\n"
            "- %V: громкость (в процентах)\n"
            "- %b: громкость (шестнадцатеричная)\n"
            "- %l: перенос на новую строку\n"
            "- %%: знак процента";

    strings["Text color##sgco"].plurals[0] = "Цвет текста";
    strings["Error!##sgco"].plurals[0] = "Ошибка!";
    strings["\nquiet##sgco"].plurals[0] = "\nтихо";

    //src/gui/clock.cpp

    strings["Clock###Clock"].plurals[0] = "Часы###Clock";

    //src/gui/dataList.cpp

    strings["Bug!##sgdl"].plurals[0] = "Баг!";
    strings["Unknown##sgdl"].plurals[0] = "Неизвестный тип инструмента";
    strings["duplicate##sgdl0"].plurals[0] = "клонировать";
    strings["replace...##sgdl0"].plurals[0] = "заменить...";
    strings["save##sgdl0"].plurals[0] = "сохранить";
    strings["export (.dmp)##sgdl"].plurals[0] = "экспортировать в .dmp";
    strings["delete##sgdl0"].plurals[0] = "удалить";
    strings["%.2X: <INVALID>##sgdl"].plurals[0] = "%.2X: <НЕДЕЙСТВ.>";
    strings["- None -##sgdl"].plurals[0] = "- Нет -";
    strings["out of memory for this sample!##sgdl"].plurals[0] = "недостаточно памяти для этого сэмпла!";
    strings["make instrument##sgdl"].plurals[0] = "создать инструмент";
    strings["duplicate##sgdl1"].plurals[0] = "клонировать";
    strings["replace...##sgdl1"].plurals[0] = "заменить...";
    strings["save##sgdl1"].plurals[0] = "сохранить";
    strings["delete##sgdl1"].plurals[0] = "удалить";
    strings["Add##sgdl0"].plurals[0] = "Добавить";
    strings["Duplicate##sgdl2"].plurals[0] = "Клонировать";
    strings["Open##sgdl0"].plurals[0] = "Открыть";
    strings["replace instrument...##sgdl"].plurals[0] = "заменить инструмент...";
    strings["load instrument from TX81Z##sgdl"].plurals[0] = "загрузить инструмент с TX81Z";
    strings["replace wavetable...##sgdl"].plurals[0] = "заменить волновую таблицу...";
    strings["replace sample...##sgdl"].plurals[0] = "заменить сэмпл...";
    strings["import raw sample...##sgdl"].plurals[0] = "загрузить сырые данные сэмпла...";
    strings["import raw sample (replace)...##sgdl"].plurals[0] = "загрузить сырые данные сэмпла (заменить)...";
    strings["replace...##sgdl2"].plurals[0] = "заменить...";
    strings["load from TX81Z##sgdl"].plurals[0] = "загрузить с TX81Z";
    strings["Open (insert; right-click to replace)##sgdl"].plurals[0] = "Открыть (вставить; ПКМ для замены)";
    strings["Save##sgdl2"].plurals[0] = "Сохранить";
    strings["save instrument as .dmp...##sgdl"].plurals[0] = "сохранить инструмент как .dmp...";
    strings["save wavetable as .dmw...##sgdl"].plurals[0] = "сохранить волновую таблицу как .dmw...";
    strings["save raw wavetable...##sgdl"].plurals[0] = "сохранить сырые данные волновой таблицы...";
    strings["save raw sample...##sgdl"].plurals[0] = "сохранить сырые данные сэмпла...";
    strings["save as .dmp...##sgdl"].plurals[0] = "сохранить как .dmp...";
    strings["Toggle folders/standard view##sgdl0"].plurals[0] = "Переключиться между видом с разбиением по папкам и обычным видом";
    strings["Move up##sgdl0"].plurals[0] = "Переместить на одну позицию вверх";
    strings["Move down##sgdl0"].plurals[0] = "Переместить на одну позицию вниз";
    strings["Create##sgdl0"].plurals[0] = "Создать";
    strings["New folder##sgdl0"].plurals[0] = "Новая папка";
    strings["Preview (right click to stop)##sgdl0"].plurals[0] = "Превью (ПКМ для остановки)";
    strings["Delete##sgdl2"].plurals[0] = "Удалить";
    strings["Instruments##sgdl"].plurals[0] = "Инструменты";
    strings["<uncategorized>##sgdl0"].plurals[0] = "<нерассортированные>";
    strings["rename...##sgdl0"].plurals[0] = "переименовать...";
    strings["delete##sgdl3"].plurals[0] = "удалить";
    strings["Wavetables##sgdl"].plurals[0] = "Волновые таблицы";
    strings["Samples##sgdl"].plurals[0] = "Сэмплы";
    strings["Add##sgdl1"].plurals[0] = "Добавить";
    strings["Duplicate##sgdl3"].plurals[0] = "Клоинровать";
    strings["Open##sgdl1"].plurals[0] = "Открыть";
    strings["replace...##sgdl3"].plurals[0] = "заменить...";
    strings["Save##sgdl3"].plurals[0] = "Сохранить";
    strings["save as .dmw...##sgdl"].plurals[0] = "сохранить как .dmw...";
    strings["save raw...##sgdl0"].plurals[0] = "сохранить сырые данные...";
    strings["Toggle folders/standard view##sgdl1"].plurals[0] = "Переключиться между видом с разбиением по папкам и обычным видом";
    strings["Move up##sgdl1"].plurals[0] = "Переместить на одну позицию вверх";
    strings["Move down##sgdl1"].plurals[0] = "Переместить на одну позицию вниз";
    strings["Create##sgdl1"].plurals[0] = "Создать";
    strings["New folder##sgdl1"].plurals[0] = "Новая папка";
    strings["Delete##sgdl4"].plurals[0] = "Удалить";
    strings["Add##sgdl2"].plurals[0] = "Добавить";
    strings["Duplicate##sgdl4"].plurals[0] = "Клонировать";
    strings["Open##sgdl2"].plurals[0] = "Открыть";
    strings["replace...##sgdl4"].plurals[0] = "заменить...";
    strings["import raw...##sgdl"].plurals[0] = "импорт сырых данных...";
    strings["import raw (replace)...##sgdl"].plurals[0] = "импорт сырых данных (заменить)...";
    strings["Save##sgdl4"].plurals[0] = "Сохранить";
    strings["save raw...##sgdl1"].plurals[0] = "сохранить сырые данные...";
    strings["Toggle folders/standard view##sgdl2"].plurals[0] = "Переключиться между видом с разбиением по папкам и обычным видом";
    strings["Move up##sgdl2"].plurals[0] = "Переместить на одну позицию вверх";
    strings["Move down##sgdl2"].plurals[0] = "Переместить на одну позицию вниз";
    strings["Create##sgdl2"].plurals[0] = "Создать";
    strings["New folder##sgdl2"].plurals[0] = "Новая папка";
    strings["Preview (right click to stop)##sgdl1"].plurals[0] = "Превью (ПКМ для остановки)";
    strings["Delete##sgdl5"].plurals[0] = "Удалить";
    strings["<uncategorized>##sgdl1"].plurals[0] = "<нерассортированные>";
    strings["rename...##sgdl1"].plurals[0] = "переименовать...";
    strings["delete##sgdl6"].plurals[0] = "удалить";
    strings["rename...##sgdl2"].plurals[0] = "переименовать...";
    strings["Delete##sgdl7"].plurals[0] = "Удалить";

    //src/gui/gui.cpp

    strings["Instrument %d##sggu"].plurals[0] = "Инструмент %d";
    strings["the song is over!##sggu0"].plurals[0] = "трек закончился!";
    strings["the song is over!##sggu1"].plurals[0] = "трек закончился!";
    strings["Open File##sggu"].plurals[0] = "Открыть файл";
    strings["compatible files##sggu0"].plurals[0] = "совместимые файлы";
    strings["all files##sggu0"].plurals[0] = "все файлы";
    strings["no backups made yet!##sggu"].plurals[0] = "резервных копий пока нет!";
    strings["Restore Backup##sggu"].plurals[0] = "Загрузить резервную копию";
    strings["Furnace song##sggu0"].plurals[0] = "модуль Furnace";
    strings["Save File##sggu0"].plurals[0] = "Сохранить файл";
    strings["DefleMask 1.1.3 module##sggu"].plurals[0] = "модуль DefleMask 1.1.3";
    strings["Save File##sggu1"].plurals[0] = "Сохранить файл";
    strings["DefleMask 1.0/legacy module##sggu"].plurals[0] = "модуль DefleMask 1.0/legacy";
    strings["Save File##sggu2"].plurals[0] = "Сохранить файл";
    strings["Furnace song##sggu1"].plurals[0] = "модуль Furnace";
    strings["Load Instrument##sggu"].plurals[0] = "загрузить инструмент";
    strings["all compatible files##sggu1"].plurals[0] = "все совместимые файлы";
    strings["Furnace instrument##sggu0"].plurals[0] = "инструмент Furnace";
    strings["DefleMask preset##sggu0"].plurals[0] = "пресет DefleMask";
    strings["TFM Music Maker instrument##sggu"].plurals[0] = "инструмент из программы TFM Music Maker";
    strings["VGM Music Maker instrument##sggu"].plurals[0] = "инструмент из программы VGM Music Maker";
    strings["Scream Tracker 3 instrument##sggu"].plurals[0] = "инструмент из программы Scream Tracker 3";
    strings["SoundBlaster instrument##sggu"].plurals[0] = "инструмент SoundBlaster";
    strings["Wohlstand OPL instrument##sggu"].plurals[0] = "инструмент из программы Wohlstand OPL";
    strings["Wohlstand OPN instrument##sggu"].plurals[0] = "инструмент из программы Wohlstand OPN";
    strings["Gens KMod patch dump##sggu"].plurals[0] = "дамп патчей Gens KMod";
    strings["BNK file (AdLib)##sggu"].plurals[0] = "файл BNK (AdLib)";
    strings["FF preset bank##sggu"].plurals[0] = "банк пресетов FF";
    strings["2612edit GYB preset bank##sggu"].plurals[0] = "банк пресетов 2612edit GYB";
    strings["VOPM preset bank##sggu"].plurals[0] = "банк пресетов VOPM";
    strings["Wohlstand WOPL bank##sggu"].plurals[0] = "банк Wohlstand WOPL";
    strings["Wohlstand WOPN bank##sggu"].plurals[0] = "банк Wohlstand WOPN";
    strings["all files##sggu1"].plurals[0] = "все файлы";
    strings["Save Instrument##sggu0"].plurals[0] = "Сохранить инструмент";
    strings["Furnace instrument##sggu1"].plurals[0] = "инструмент Furnace";
    strings["Save Instrument##sggu1"].plurals[0] = "Сохранить инструмент";
    strings["DefleMask preset##sggu1"].plurals[0] = "пресет DefleMask";
    strings["Load Wavetable##sggu"].plurals[0] = "Загрузить волновую таблицу";
    strings["compatible files##sggu2"].plurals[0] = "совместимые файлы";
    strings["all files##sggu2"].plurals[0] = "все файлы";
    strings["Save Wavetable##sggu0"].plurals[0] = "Сохранить волновую таблицу";
    strings["Furnace wavetable##sggu"].plurals[0] = "волновая таблица Furnace";
    strings["Save Wavetable##sggu1"].plurals[0] = "Сохранить волновую таблицу";
    strings["DefleMask wavetable##sggu"].plurals[0] = "волновая таблица DefleMask";
    strings["Save Wavetable##sggu2"].plurals[0] = "Сохранить волновую таблицу";
    strings["raw data##sggu"].plurals[0] = "сырые данные";
    strings["Load Sample##sggu"].plurals[0] = "Загрузить сэмпл";
    strings["compatible files##sggu3"].plurals[0] = "совместимые файлы";
    strings["all files##sggu3"].plurals[0] = "все файлы";
    strings["Load Raw Sample##sggu"].plurals[0] = "Загрузить сырые данные сэмпла";
    strings["all files##sggu4"].plurals[0] = "все файлы";
    strings["Save Sample##sggu"].plurals[0] = "Сохранить сэмпл";
    strings["Wave file##sggu0"].plurals[0] = "файл WAV";
    strings["Save Raw Sample##sggu"].plurals[0] = "Сохранить сырые данные сэмпла";
    strings["all files##sggu5"].plurals[0] = "все файлы";
    strings["Export Audio##sggu0"].plurals[0] = "Экспорт аудио";
    strings["Wave file##sggu1"].plurals[0] = "файл WAV";
    strings["Export Audio##sggu1"].plurals[0] = "Экспорт аудио";
    strings["Wave file##sggu2"].plurals[0] = "файл WAV";
    strings["Export Audio##sggu2"].plurals[0] = "Экспорт аудио";
    strings["Wave file##sggu3"].plurals[0] = "файл WAV";
    strings["Export VGM##sggu"].plurals[0] = "Экспорт VGM";
    strings["VGM file##sggu"].plurals[0] = "Файл VGM";
    strings["Export ZSM##sggu"].plurals[0] = "Экспорт ZSM";
    strings["ZSM file##sggu"].plurals[0] = "Файл ZSM";
    strings["Export Command Stream##sggu0"].plurals[0] = "Экспорт потока команд";
    strings["text file##sggu0"].plurals[0] = "текстовый файл";
    strings["Export Command Stream##sggu1"].plurals[0] = "Экспорт потока команд";
    strings["text file##sggu1"].plurals[0] = "текстовый файл";
    strings["Export Command Stream##sggu2"].plurals[0] = "Экспорт потока команд";
    strings["binary file##sggu"].plurals[0] = "бинарный файл";
    strings["Coming soon!##sggu"].plurals[0] = "скоро появится!";
    strings["Select Font##sggu0"].plurals[0] = "Выберите шрифт";
    strings["compatible files##sggu4"].plurals[0] = "совместимые файлы";
    strings["Select Font##sggu1"].plurals[0] = "Выберите шрифт";
    strings["compatible files##sggu5"].plurals[0] = "совместимые файлы";
    strings["Select Font##sggu2"].plurals[0] = "Выберите шрифт";
    strings["compatible files##sggu6"].plurals[0] = "совместимые файлы";
    strings["Select Color File##sggu"].plurals[0] = "Выберите файл с настройками цветов";
    strings["configuration files##sggu0"].plurals[0] = "файлы конфигурации";
    strings["Select Keybind File##sggu"].plurals[0] = "Выберите файл с настройками клавиатуры";
    strings["configuration files##sggu1"].plurals[0] = "файлы конфигурации";
    strings["Select Layout File##sggu"].plurals[0] = "Выберите файл с настройками компоновки окон интерфейса";
    strings[".ini files##sggu0"].plurals[0] = "файлы .ini";
    strings["Export Colors##sggu"].plurals[0] = "Экспортировать настройки цветов";
    strings["configuration files##sggu2"].plurals[0] = "файлы конфигурации";
    strings["Export Keybinds##sggu"].plurals[0] = "Экспортировать настройки клавиатуры";
    strings["configuration files##sggu3"].plurals[0] = "файлы конфигурации";
    strings["Export Layout##sggu"].plurals[0] = "Экспортиировать компоновку окон интерфейса";
    strings[".ini files##sggu1"].plurals[0] = "файлы .ini";
    strings["Load ROM##sggu"].plurals[0] = "Загрузить ROM";
    strings["compatible files##sggu7"].plurals[0] = "совместимые файлы";
    strings["all files##sggu6"].plurals[0] = "все файлы";
    strings["Play Command Stream##sggu"].plurals[0] = "Воспроизвести поток команд";
    strings["command stream##sggu"].plurals[0] = "поток команд";
    strings["all files##sggu7"].plurals[0] = "все файлы";
    strings["Open Test##sggu"].plurals[0] = "Открыть (тест)";
    strings["compatible files##sggu8"].plurals[0] = "совместимые файлы";
    strings["another option##sggu0"].plurals[0] = "другая опция";
    strings["all files##sggu8"].plurals[0] = "все файлы";
    strings["Open Test (Multi)##sggu"].plurals[0] = "Открыть (тест, несколько файлов)";
    strings["compatible files##sggu9"].plurals[0] = "совместимые файлы";
    strings["another option##sggu1"].plurals[0] = "другая опция";
    strings["all files##sggu9"].plurals[0] = "все файлы";
    strings["Save Test##sggu"].plurals[0] = "Сохранить (тест)";
    strings["Furnace song##sggu"].plurals[0] = "Модуль Furnace";
    strings["DefleMask module##sggu"].plurals[0] = "Модуль DefleMask";
    strings["you have loaded a backup!\nif you need to, please save it somewhere.\n\nDO NOT RELY ON THE BACKUP SYSTEM FOR AUTO-SAVE!\nFurnace will not save backups of backups.##sggu"].plurals[0] = "вы загрузили резервную копию!\nесли необходимо, сохраните её где-то ещё.\n\nСИСТЕМА РЕЗЕРВНОГО КОПИРОВАНИЯ НЕ ЯВЛЯЕТСЯ СИСТЕМОЙ АВТОСОХРАНЕНИЯ!\nFurnace не сохраняет резервные копии резервных копий.";
    strings["cut##sggu"].plurals[0] = "вырезать";
    strings["copy##sggu"].plurals[0] = "копировать";
    strings["paste##sggu0"].plurals[0] = "вставить";
    strings["paste special...##sggu"].plurals[0] = "вставить...";
    strings["paste mix##sggu"].plurals[0] = "вставить поверх";
    strings["paste mix (background)##sggu"].plurals[0] = "вставить поверх (с заменой существующего)";
    strings["paste with ins (foreground)##sggu"].plurals[0] = "вставить поверх с инстр. (без замены существующего)";
    strings["no instruments available##sggu0"].plurals[0] = "нет доступных инструментов";
    strings["paste with ins (background)##sggu"].plurals[0] = "вставить поверх с инстр. (с заменой существующего)";
    strings["no instruments available##sggu1"].plurals[0] = "нет доступных инструментов";
    strings["paste flood##sggu"].plurals[0] = "вставить с цикл. повт. буфера (до конца патт.)";
    strings["paste overflow##sggu"].plurals[0] = "вставить (с возможным переходом в след. паттерн)";
    strings["delete##sggu0"].plurals[0] = "удалить";
    strings["select all##sggu"].plurals[0] = "выбрать всё";
    strings["operation mask...##sggu"].plurals[0] = "маска операций...";
    strings["delete##sggu1"].plurals[0] = "удаление";
    strings["pull delete##sggu"].plurals[0] = "удал. с подтяг. след. строк";
    strings["insert##sggu"].plurals[0] = "вставка пустой строки";
    strings["paste##sggu1"].plurals[0] = "вставка";
    strings["transpose (note)##sggu"].plurals[0] = "транспонирование (нота)";
    strings["transpose (value)##sggu"].plurals[0] = "транспонирование (других параметров)";
    strings["interpolate##sggu0"].plurals[0] = "интерполяция";
    strings["fade##sggu"].plurals[0] = "градиент/затухание";
    strings["invert values##sggu0"].plurals[0] = "инверсия значений";
    strings["scale##sggu"].plurals[0] = "масштабирование";
    strings["randomize##sggu"].plurals[0] = "заполнение случайными значениями";
    strings["flip##sggu"].plurals[0] = "переворот";
    strings["collapse/expand##sggu"].plurals[0] = "сжать/расширить";
    strings["input latch##sggu"].plurals[0] = "буфер ввода";
    strings["&&: selected instrument\n..: no instrument##sggu"].plurals[0] = "&&: выбранный инструмент\n..: без инструмента";
    strings["Set##sggu"].plurals[0] = "Очистить";
    strings["Reset##sggu"].plurals[0] = "Сбросить";
    strings["note up##sggu"].plurals[0] = "на полутон вверх";
    strings["note down##sggu"].plurals[0] = "на полутон вниз";
    strings["octave up##sggu"].plurals[0] = "на октаву вверх";
    strings["octave down##sggu"].plurals[0] = "на октаву вниз";
    strings["values up##sggu"].plurals[0] = "параметры вверх";
    strings["values down##sggu"].plurals[0] = "параметры вниз";
    strings["values up (+16)##sggu"].plurals[0] = "параметры вверх (+16)";
    strings["values down (-16)##sggu"].plurals[0] = "параметры вниз (-16)";
    strings["transpose##sggu"].plurals[0] = "транспонировать";
    strings["Notes##sggu"].plurals[0] = "Ноты";
    strings["Values##sggu"].plurals[0] = "Параметры";
    strings["interpolate##sggu1"].plurals[0] = "транспонировать";
    strings["change instrument...##sggu"].plurals[0] = "заменить инструмент...";
    strings["no instruments available##sggu"].plurals[0] = "нет доступных инструментов";
    strings["gradient/fade...##sggu"].plurals[0] = "градиент/затухание...";
    strings["Start##sggu"].plurals[0] = "Начало";
    strings["End##sggu"].plurals[0] = "Конец";
    strings["Nibble mode##sggu0"].plurals[0] = "Режим тетрад";
    strings["Go ahead##sggu"].plurals[0] = "Применить";
    strings["scale...##sggu"].plurals[0] = "масштабировать...";
    strings["Scale##sggu"].plurals[0] = "Масштабировать";
    strings["randomize...##sggu"].plurals[0] = "заполнить случайными значениями...";
    strings["Minimum##sggu"].plurals[0] = "Нижняя граница";
    strings["Maximum##sggu"].plurals[0] = "Верхняя граница";
    strings["Nibble mode##sggu1"].plurals[0] = "Режим тетрад";
    strings["Randomize##sggu"].plurals[0] = "Заполнить";
    strings["invert values##sggu1"].plurals[0] = "инвертировать параметры";
    strings["flip selection##sggu"].plurals[0] = "перевернуть выделенную область";
    strings["collapse/expand amount##CollapseAmount"].plurals[0] = "коэффициент сжатия/расширения##CollapseAmount";
    strings["collapse##sggu"].plurals[0] = "сжать";
    strings["expand##sggu"].plurals[0] = "расширить";
    strings["collapse pattern##sggu"].plurals[0] = "сжать паттерн";
    strings["expand pattern##sggu"].plurals[0] = "расширить паттерн";
    strings["collapse song##sggu"].plurals[0] = "сжать трек";
    strings["expand song##sggu"].plurals[0] = "расширить трек";
    strings["find/replace##sggu"].plurals[0] = "найти/заменить";
    strings["Furnace has been started in Safe Mode.\nthis means that:\n\n- software rendering is being used\n- audio output may not work\n- font loading is disabled\n\ncheck any settings which may have made Furnace start up in this mode.\nfont loading is one of these.##sggu"].plurals[0] = "Furnace был запущен в безопасном режиме.\nэто означает:\n\n- используется программная отрисовка\n- может не работать вывод звука\n- отключена загрузка шрифтов\n\nпроверьте, какие настройки могли привести к запуску программы в этом режиме.\nзагрузка шрифтов может быть одной из таких.";
    strings["Unsaved changes! Save changes before opening file?##sggu0"].plurals[0] = "Остались несохранённые изменения! Сохранить их перед открытием файла?";
    strings["Error while loading file! (%s)##sggu0"].plurals[0] = "Ошибка при загрузке файла! (%s)";
    strings["Unsaved changes! Save changes before quitting?##sggu"].plurals[0] = "Остались несохранённые изменения! Сохранить их перед выходом?";
    strings["error while loading fonts! please check your settings.##sggu0"].plurals[0] = "Ошибка при загрузке шрифтов! Проверьте свои настройки.";
    strings["File##menubar"].plurals[0] = "Файл##menubar";
    strings["file##menubar"].plurals[0] = "файл##menubar";
    strings["new...##sggu"].plurals[0] = "новый...";
    strings["Unsaved changes! Save changes before creating a new song?##sggu"].plurals[0] = "Остались несохранённые изменения! Сохранить их перед созданием нового трека?";
    strings["open...##sggu"].plurals[0] = "открыть...";
    strings["Unsaved changes! Save changes before opening another file?##sggu"].plurals[0] = "Остались несохранённые изменения! Сохранить их перед открытием другого файла?";
    strings["open recent##sggu"].plurals[0] = "открыть недавние";
    strings["Unsaved changes! Save changes before opening file?##sggu1"].plurals[0] = "Остались несохранённые изменения! Сохранить их перед открытием файла?";
    strings["Error while loading file! (%s)##sggu1"].plurals[0] = "Ошибка при загрузке файла! (%s)";
    strings["nothing here yet##sggu"].plurals[0] = "пока здесь ничего нет";
    strings["clear history##sggu"].plurals[0] = "очистить историю";
    strings["Are you sure you want to clear the recent file list?##sggu"].plurals[0] = "Вы уверены, что хотите очистить список недавних файлов?";
    strings["save##sggu"].plurals[0] = "сохранить";
    strings["Error while saving file! (%s)##sggu0"].plurals[0] = "Ошибка при сохранении файла! (%s)";
    strings["save as...##sggu"].plurals[0] = "сохранить как...";
    strings["export audio...##sggu0"].plurals[0] = "экспорт аудио...";
    strings["export VGM...##sggu0"].plurals[0] = "экспорт VGM...";
    strings["export .dmf (1.1.3+)...##sggu0"].plurals[0] = "экспорт .dmf (1.1.3+)...";
    strings["export .dmf (1.0/legacy)...##sggu0"].plurals[0] = "экспорт .dmf (1.0/legacy)...";
    strings["export ZSM...##sggu0"].plurals[0] = "экспорт ZSM...";
    strings["export Amiga validation data...##sggu0"].plurals[0] = "экспорт проверочного файла для компьютера Amiga...";
    strings["export text...##sggu0"].plurals[0] = "экспорт текста...";
    strings["export command stream...##sggu0"].plurals[0] = "экспорт потока команд...";
    strings["export audio...##sggu1"].plurals[0] = "экспорт аудио...";
    strings["export VGM...##sggu1"].plurals[0] = "экспорт VGM...";
    strings["export .dmf (1.1.3+)...##sggu1"].plurals[0] = "экспорт .dmf (1.1.3+)...";
    strings["export .dmf (1.0/legacy)...##sggu1"].plurals[0] = "экспорт .dmf (1.0/legacy)...";
    strings["export ZSM...##sggu1"].plurals[0] = "экспорт ZSM...";
    strings["export Amiga validation data...##sggu1"].plurals[0] = "экспорт проверочного файла для компьютера Amiga...";
    strings["export text...##sggu1"].plurals[0] = "экспорт текста...";
    strings["export command stream...##sggu1"].plurals[0] = "экспорт потока команд...";
    strings["export...##sggu"].plurals[0] = "экспорт...";
    strings["manage chips##sggu"].plurals[0] = "менеджер чипов";
    strings["add chip...##sggu"].plurals[0] = "добавить чип...";
    strings["cannot add chip! (##sggu"].plurals[0] = "не могу добавить чип! (";
    strings["configure chip...##sggu"].plurals[0] = "настроить чип...";
    strings["change chip...##sggu"].plurals[0] = "сменить чип...";
    strings["Preserve channel positions##sggu0"].plurals[0] = "Сохранить положение каналов";
    strings["remove chip...##sggu"].plurals[0] = "убрать чип...";
    strings["Preserve channel positions##sggu1"].plurals[0] = "Сохранить положение каналов";
    strings["cannot remove chip! (##sggu"].plurals[0] = "не могу убрать чип! (";
    strings["restore backup##sggu"].plurals[0] = "загрузить резервную копию";
    strings["exit##sggu"].plurals[0] = "выход";
    strings["Unsaved changes! Save before quitting?##sggu"].plurals[0] = "Остались несохранённые изменения! Сохранить их перед выходом?";
    strings["Edit##menubar"].plurals[0] = "Правка##menubar";
    strings["edit##menubar"].plurals[0] = "правка##menubar";
    strings["undo##sggu"].plurals[0] = "отменить";
    strings["redo##sggu"].plurals[0] = "вернуть";
    strings["clear...##sggu"].plurals[0] = "очистить...";
    strings["Settings##menubar"].plurals[0] = "Настройки##menubar";
    strings["settings##menubar"].plurals[0] = "настройки##menubar";
    strings["full screen##sggu"].plurals[0] = "полноэкранный режим";
    strings["lock layout##sggu"].plurals[0] = "зафиксировать компоновку окон";
    strings["visualizer##sggu"].plurals[0] = "визуализатор эффектов";
    strings["reset layout##sggu"].plurals[0] = "сбросить компоновку окон";
    strings["Are you sure you want to reset the workspace layout?##sggu"].plurals[0] = "Вы уверены, что хотите сброить компоновку окон интерфейса?";
    strings["switch to mobile view##sggu"].plurals[0] = "переключиться на мобильный интерфейс";
    strings["settings...##sggu"].plurals[0] = "настройки...";
    strings["Window##menubar"].plurals[0] = "Окно##menubar";
    strings["window##menubar"].plurals[0] = "окно##menubar";
    strings["song information##sggu"].plurals[0] = "о треке";
    strings["subsongs##sggu"].plurals[0] = "подпесни";
    strings["speed##sggu"].plurals[0] = "скорость";
    strings["assets##sggu"].plurals[0] = "ресурсы";
    strings["instruments##sggu"].plurals[0] = "инструменты";
    strings["wavetables##sggu"].plurals[0] = "волновые таблицы";
    strings["samples##sggu"].plurals[0] = "сэмплы";
    strings["orders##sggu"].plurals[0] = "матрица паттернов";
    strings["pattern##sggu"].plurals[0] = "паттерны";
    strings["mixer##sggu"].plurals[0] = "микшер";
    strings["grooves##sggu"].plurals[0] = "ритм-паттерны";
    strings["channels##sggu"].plurals[0] = "каналы";
    strings["pattern manager##sggu"].plurals[0] = "менеджер паттернов";
    strings["chip manager##sggu"].plurals[0] = "менеджер чипов";
    strings["compatibility flags##sggu"].plurals[0] = "флаги совместимости";
    strings["song comments##sggu"].plurals[0] = "комментарии трека";
    strings["instrument editor##sggu"].plurals[0] = "редактор инструментов";
    strings["wavetable editor##sggu"].plurals[0] = "редактор волновых таблиц";
    strings["sample editor##sggu"].plurals[0] = "редактор сэмплов";
    strings["play/edit controls##sggu"].plurals[0] = "управление редактированием/воспроизведением";
    strings["piano/input pad##sggu"].plurals[0] = "клавиатура пианино/панель ввода";
    strings["oscilloscope (master)##sggu"].plurals[0] = "осциллограф";
    strings["oscilloscope (per-channel)##sggu"].plurals[0] = "осциллографы (для отдельных каналов)";
    strings["oscilloscope (X-Y)##sggu"].plurals[0] = "осциллограф (X-Y)";
    strings["volume meter##sggu"].plurals[0] = "измеритель громкости";
    strings["clock##sggu"].plurals[0] = "часы";
    strings["register view##sggu"].plurals[0] = "просмотр регистров";
    strings["log viewer##sggu"].plurals[0] = "просмотр логов";
    strings["statistics##sggu"].plurals[0] = "статистика";
    strings["spoiler##sggu"].plurals[0] = "спойлер";
    strings["Help##menubar"].plurals[0] = "Справка##menubar";
    strings["help##menubar"].plurals[0] = "справка##menubar";
    strings["effect list##sggu"].plurals[0] = "список эффектов";
    strings["debug menu##sggu"].plurals[0] = "отладка";
    strings["inspector##sggu"].plurals[0] = "отладка ImGUI";
    strings["panic##sggu"].plurals[0] = "паника";
    strings["about...##sggu"].plurals[0] = "о программе...";
    strings["| Speed %d:%d##sggu"].plurals[0] = "| Скорость %d:%d";
    strings["| Speed %d##sggu"].plurals[0] = "| Скорость %d";
    strings["| Groove##sggu"].plurals[0] = "| Ритм-паттерн";
    strings[" @ %gHz (%g BPM) ##sggu"].plurals[0] = " @ %gHz (%g BPM) ";
    strings["| Order %.2X/%.2X ##sggu"].plurals[0] = "| Строка матр. патт. %.2X/%.2X ";
    strings["| Order %d/%d ##sggu"].plurals[0] = "| Строка матр. патт. %d/%d ";
    strings["| Row %.2X/%.2X ##sggu"].plurals[0] = "| Строка %.2X/%.2X ";
    strings["| Row %d/%d ##sggu"].plurals[0] = "| Строка %d/%d ";
    strings["Don't you have anything better to do?##sggu"].plurals[0] = "Вам точно больше нечем заняться?";
    strings["%d years ##sggu"].plurals[0] = "%d год ";
    strings["%d years ##sggu"].plurals[1] = "%d года ";
    strings["%d years ##sggu"].plurals[2] = "%d лет ";
    strings["%d months ##sggu"].plurals[0] = "%d месяц ";
    strings["%d months ##sggu"].plurals[1] = "%d месяца ";
    strings["%d months ##sggu"].plurals[2] = "%d месяцев ";
    strings["%d days ##sggu"].plurals[0] = "%d день ";
    strings["%d days ##sggu"].plurals[1] = "%d дня ";
    strings["%d days ##sggu"].plurals[2] = "%d дней ";
    strings["Note off (cut)##sggu"].plurals[0] = "\"Отпускание клавиши\" (резкое)";
    strings["Note off (release)##sggu"].plurals[0] = "\"Отпускание клавиши\" (с включением фазы затухания огибающей)";
    strings["Macro release only##sggu"].plurals[0] = "\"Отпускание клавиши\" (только для макросов)";
    strings["Note on: %s##sggu"].plurals[0] = "Нота: %s";
    strings["Ins %d: <invalid>##sggu"].plurals[0] = "Инструмент %d: <недейств.>";
    strings["Ins %d: %s##sggu"].plurals[0] = "Инструмент %d: %s";
    strings["Set volume: %d (%.2X, INVALID!)##sggu"].plurals[0] = "Громкость: %d (%.2X, НЕДЕЙСТВИТЕЛЬНА!)";
    strings["Set volume: %d (%.2X, %d%%)##sggu"].plurals[0] = "Громкость: %d (%.2X, %d%%)";
    strings["| modified##sggu"].plurals[0] = "| изменено";
    strings["there was an error in the file dialog! you may want to report this issue to:\nhttps://github.com/tildearrow/furnace/issues\ncheck the Log Viewer (window > log viewer) for more information.\n\nfor now please disable the system file picker in Settings > General.##sggu"].plurals[0] = "возникла ошибка в окне файлового диалога! возможно, вы захотите сообщить об ошибке:\nhttps://github.com/tildearrow/furnace/issues\nвы можете открыть просмотр логов (окно > просмотр логов) для получения дополнительной информации.\n\nпока можете отключить файловый диалог ОС в настройки > основные.";
    strings["can't do anything without Storage permissions!##sggu"].plurals[0] = "не могу ничего сделать без разрешения \"Хранилище\"!";
    strings["Zenity/KDialog not available!\nplease install one of these, or disable the system file picker in Settings > General.##sggu"].plurals[0] = "Zenity/KDialog недоступны!\nпожалуйста, установите один из них, или отключите файловый диалог ОС в настройки > основные.";
    strings["Error while loading file! (%s)##sggu2"].plurals[0] = "Ошибка при загрузке файла! (%s)";
    strings["Error while saving file! (%s)##sggu1"].plurals[0] = "Ошибка при сохранении файла! (%s)";
    strings["Error while loading file! (%s)##sggu3"].plurals[0] = "Ошибка при загрузке файла! (%s)";
    strings["Error while saving file! (%s)##sggu2"].plurals[0] = "Ошибка при сохранении файла! (%s)";
    strings["Error while saving file! (%s)##sggu3"].plurals[0] = "Ошибка при сохранении файла! (%s)";
    strings["error while saving instrument! make sure your instrument is compatible.##sggu"].plurals[0] = "ошибка при сохранении инструмента! убедитесь, что ваш инструмент совместим с Deflemask.";
    strings["there were some errors while loading samples:\n#sggu"].plurals[0] = "при загрузке сэмплов возникли следующие ошибки:\n";
    strings["...but you haven't selected a sample!##sggu0"].plurals[0] = "...но вы не выбрали сэмпл!";
    strings["could not save sample! open Log Viewer for more information.##sggu0"].plurals[0] = "не удалось сохранить сэмпл! откройте просмотрщик логов для получения дополнительной информации.";
    strings["could not save sample! open Log Viewer for more information.##sggu1"].plurals[0] = "не удалось сохранить сэмпл! откройте просмотрщик логов для получения дополнительной информации.";
    strings["there were some warnings/errors while loading instruments:\n#sggu"].plurals[0] = "при загрузке инструментов возникли следующие ошибки и предупреждения:\n";
    strings["> %s: cannot load instrument! (%s)\n#sggu"].plurals[0] = "> %s: не могу загрузить инструмент! (%s)\n";
    strings["...but you haven't selected an instrument!##sggu0"].plurals[0] = "...но вы не выбрали инструмент!";
    strings["cannot load instrument! (##sggu"].plurals[0] = "не могу загрузить инструмент! (";
    strings["congratulations! you managed to load nothing.\nyou are entitled to a bug report.##sggu"].plurals[0] = "поздравляю! вам удалось загрузить ничто.\nвы приглашаетесь к написанию отчёта об ошибке.";
    strings["there were some errors while loading wavetables:\n##sggu"].plurals[0] = "при загрузке волновых таблиц возникли следующие ошибки:\n";
    strings["cannot load wavetable! (##sggu"].plurals[0] = "не могу загрузить волновую таблицу! (";
    strings["...but you haven't selected a wavetable!##sggu"].plurals[0] = "...но вы не выбрали волновую таблицу!";
    strings["could not open file!##sggu"].plurals[0] = "не удалось открыть файл!";
    strings["Could not write ZSM! (%s)##sggu"].plurals[0] = "Не удалось записать файл ZSM! (%s)";
    strings["could not write text! (%s)##sggu"].plurals[0] = "не удалось записать текстовый файл! (%s)";
    strings["could not write command stream! (%s)##sggu"].plurals[0] = "не удалось записать файл с потоком команд! (%s)";
    strings["Error while loading file! (%s)##sggu4"].plurals[0] = "Ошибка при загрузке файла! (%s)";
    strings["You opened: %s##sggu"].plurals[0] = "Вы открыли: %s";
    strings["You opened:##sggu"].plurals[0] = "Вы открыли:";
    strings["You saved: %s##sggu"].plurals[0] = "Вы сохранили: %s";
    strings["Rendering...###Rendering..."].plurals[0] = "Рендер...###Rendering...";
    strings["Please wait...##sggu"].plurals[0] = "Пожалуйста, подождите...";
    strings["Abort##sggu"].plurals[0] = "Прервать";
    strings["New Song###New Song"].plurals[0] = "Новый трек###New Song";
    strings["Export###Export"].plurals[0] = "Экспорт###Export";
    strings["Error###Error"].plurals[0] = "Ошибка###Error";
    strings["OK##sggu0"].plurals[0] = "ОК";
    strings["Warning###Warning"].plurals[0] = "Внимание###Warning";
    strings["Yes##sggu0"].plurals[0] = "Да";
    strings["No##sggu0"].plurals[0] = "Нет";
    strings["Yes##sggu1"].plurals[0] = "Да";
    strings["No##sggu1"].plurals[0] = "Нет";
    strings["Yes##sggu2"].plurals[0] = "Да";
    strings["No##sggu2"].plurals[0] = "Нет";
    strings["Yes##sggu3"].plurals[0] = "Да";
    strings["No##sggu3"].plurals[0] = "Нет";
    strings["Cancel##sggu0"].plurals[0] = "Отмена";
    strings["Erasing##sggu"].plurals[0] = "Удалить:";
    strings["All subsongs##sggu"].plurals[0] = "Все подпесни";
    strings["Current subsong##sggu"].plurals[0] = "Текущую подпесню";
    strings["Orders##sggu"].plurals[0] = "Матрицу паттернов";
    strings["Pattern##sggu"].plurals[0] = "Паттерны";
    strings["Instruments##sggu"].plurals[0] = "Инструменты";
    strings["Wavetables##sggu"].plurals[0] = "Волновые таблицы";
    strings["Samples##sggu"].plurals[0] = "Сэмплы";
    strings["Optimization##sggu"].plurals[0] = "Оптимизировать:";
    strings["De-duplicate patterns##sggu"].plurals[0] = "Удалить дубликаты паттернов";
    strings["Remove unused instruments##sggu"].plurals[0] = "Удалить неиспользуемые инструменты";
    strings["Remove unused samples##sggu"].plurals[0] = "Удалить неиспользуемые сэмплы";
    strings["Never mind! Cancel##sggu1"].plurals[0] = "Не надо! Отмена";
    strings["Yes##sggu4"].plurals[0] = "Да";
    strings["No##sggu4"].plurals[0] = "Нет";
    strings["Yes##sggu5"].plurals[0] = "Да";
    strings["No##sggu5"].plurals[0] = "Нет";
    strings["Yes##sggu6"].plurals[0] = "Да";
    strings["No##sggu6"].plurals[0] = "Нет";
    strings["Yes##sggu7"].plurals[0] = "Да";
    strings["Yes##sggu8"].plurals[0] = "Да";
    strings["Yes##sggu9"].plurals[0] = "Да";
    strings["Yes##sggu10"].plurals[0] = "Да";
    strings["Yes##sggu11"].plurals[0] = "Да";
    strings["No##sggu8"].plurals[0] = "Нет";
    strings["No##sggu9"].plurals[0] = "Нет";
    strings["No##sggu10"].plurals[0] = "Нет";
    strings["No##sggu11"].plurals[0] = "Нет";
    strings["No##sggu12"].plurals[0] = "Нет";
    strings["Cancel##sggu4"].plurals[0] = "Отмена";
    strings["Cancel##sggu5"].plurals[0] = "Отмена";
    strings["Cancel##sggu6"].plurals[0] = "Отмена";
    strings["Cancel##sggu7"].plurals[0] = "Отмена";
    strings["Cancel##sggu8"].plurals[0] = "Отмена";
    strings["OK##sggu1"].plurals[0] = "ОК";
    strings["too many instruments!##sggu"].plurals[0] = "слишком много инструментов!";
    strings["too many wavetables!##sggu"].plurals[0] = "слишком много волновых таблиц!";
    strings["Select Instrument###Select Instrument"].plurals[0] = "Выберите инструмент###Select Instrument";
    strings["this is an instrument bank! select which one to use:##sggu"].plurals[0] = "это банк инструментов! выберите, какой вы хотите использовать:";
    strings["this is an instrument bank! select which ones to load:##sggu"].plurals[0] = "это банк инструментов! выберите, какой вы хотите загрузить";
    strings["All##sggu"].plurals[0] = "Все";
    strings["None##sggu"].plurals[0] = "Никакой";
    strings["OK##sggu2"].plurals[0] = "ОК";
    strings["Cancel##sggu2"].plurals[0] = "Отмена";
    strings["...but you haven't selected an instrument!##sggu1"].plurals[0] = "...но вы не выбрали инструмент!";
    strings["Import Raw Sample###Import Raw Sample"].plurals[0] = "Импортировать сырые данные сэмпла###Import Raw Sample";
    strings["Data type:##sggu"].plurals[0] = "Тип данных:";
    strings["Sample rate##sggu"].plurals[0] = "Частота квантования";
    strings["Channels##sggu"].plurals[0] = "Число каналов";
    strings["(will be mixed down to mono)##sggu"].plurals[0] = "(будет сведено в моно)";
    strings["Unsigned##sggu"].plurals[0] = "Беззнаковый";
    strings["Big endian##sggu"].plurals[0] = "Обратный порядок байтов (Big endian)";
    strings["Swap nibbles##sggu"].plurals[0] = "Поменять местами тетрады";
    strings["Swap words##sggu"].plurals[0] = "Поменять местами машинные слова";
    strings["Encoding:##sggu"].plurals[0] = "Кодировка:";
    strings["Reverse bit order##sggu"].plurals[0] = "Обратный порядок битов";
    strings["OK##sggu3"].plurals[0] = "ОК";
    strings["...but you haven't selected a sample!##sggu1"].plurals[0] = "...но вы не выбрали сэмпл!";
    strings["Cancel##sggu3"].plurals[0] = "Отмена";
    strings["Error! No string provided!##sggu"].plurals[0] = "Ошибка! Не предоставлена строка!";
    strings["OK##sggu4"].plurals[0] = "ОК";
    strings["error while loading fonts! please check your settings.##sggu1"].plurals[0] = "Ошибка при загрузке шрифтов! пожалуйста, проверьте настройки.";
    strings["it appears I couldn't load these fonts. any setting you can check?##sggu"].plurals[0] = "кажется, я не могу загрузить эти шрифты. проверьте настройки?";
    strings["could not init renderer! %s##sggu"].plurals[0] = "не получилось инициализировать движок отрисовки! %s";
    strings["\r\nthe render driver has been set to a safe value. please restart Furnace.##sggu"].plurals[0] = "\r\nдвижок отрисовки был сброшен до безопасного. пожалуйста, перезапустите Furnace.";
    strings["could not open window! %s##sggu"].plurals[0] = "не удалось открыть окно! %s";
    strings["error while loading fonts! please check your settings.##sggu2"].plurals[0] = "Ошибка при загрузке шрифтов! пожалуйста, проверьте настройки.";
    strings["could NOT save layout! %s##sggu"].plurals[0] = "Не получилось сохранить компоновку окон! %s";

    //   sggc  src/gui/guiConst.cpp

    strings["Forward##sggc"].plurals[0] = "Вперёд";
    strings["Backward##sggc"].plurals[0] = "Назад";
    strings["Ping pong##sggc"].plurals[0] = "Туда-обратно";
    strings["1-bit PCM##sggc"].plurals[0] = "1-битная ИКМ";
    strings["1-bit DPCM##sggc"].plurals[0] = "1-битная ДИКМ";
    strings["8-bit PCM##sggc"].plurals[0] = "8-битная ИКМ";
    strings["8-bit µ-law PCM##sggc"].plurals[0] = "8-битная ИКМ (µ-закон)";
    strings["16-bit PCM##sggc"].plurals[0] = "16-битная ИКМ";
    strings["none##sggc"].plurals[0] = "нет";
    strings["linear##sggc"].plurals[0] = "линейная";
    strings["cubic spline##sggc"].plurals[0] = "кубический сплайн";
    strings["blep synthesis##sggc"].plurals[0] = "BLEP-синтез";
    strings["sinc##sggc"].plurals[0] = "sinc";
    strings["best possible##sggc"].plurals[0] = "наилучший";
    strings["Pitch##sggc"].plurals[0] = "Частота";
    strings["Song##sggc"].plurals[0] = "Трек";
    strings["Time##sggc"].plurals[0] = "Время";
    strings["Speed##sggc"].plurals[0] = "Скорость";
    strings["Panning##sggc"].plurals[0] = "Панорамирование";
    strings["Volume##sggc"].plurals[0] = "Громкость";
    strings["System Primary##sggc"].plurals[0] = "Основные эффекты чипа";
    strings["System Secondary##sggc"].plurals[0] = "Вспомогательные эффекты чипа";
    strings["Miscellaneous##sggc"].plurals[0] = "Разное";
    strings["Invalid##sggc"].plurals[0] = "Недейств.";
    strings["All chips##sggc"].plurals[0] = "Все чипы";
    strings["Square##sggc"].plurals[0] = "Меандр";
    strings["Wavetable##sggc"].plurals[0] = "Волн. табл.";
    strings["Special##sggc"].plurals[0] = "Особые";
    strings["Sample##sggc"].plurals[0] = "Сэмплеры";
    strings["Modern/fantasy##sggc"].plurals[0] = "Совр./вымышл.";

    //   sgda  src/gui/doAction.cpp

    strings["Unsaved changes! Save changes before creating a new song?##sgda"].plurals[0] = "Остались несохранённые изменения! Сохранить их перед созданием нового трека?";
    strings["Unsaved changes! Save changes before opening another file?##sgda"].plurals[0] = "Остались несохранённые изменения! Сохранить их перед открытием другого файла?";
    strings["Unsaved changes! Save changes before opening backup?##sgda"].plurals[0] = "Остались несохранённые изменения! Сохранить их перед открытием резервной копии?";
    strings["Error while saving file! (%s)##sgda"].plurals[0] = "Ошибка при сохранении файла! (%s)";
    strings["Error while sending request (MIDI output not configured?)##sgda"].plurals[0] = "Ошибка при посылке запроса (MIDI вывод не настроен?)";
    strings["Select an option: (cannot be undone!)##sgda"].plurals[0] = "Выберите опцию: (действие не может быть отменено!)";
    strings["too many instruments!##sgda0"].plurals[0] = "слишком много инструментов!";
    strings["too many instruments!##sgda1"].plurals[0] = "слишком много инструментов!";
    strings["too many wavetables!##sgda0"].plurals[0] = "слишком много волновых таблиц!";
    strings["too many wavetables!##sgda1"].plurals[0] = "слишком много волновых таблиц!";
    strings["too many samples!##sgda0"].plurals[0] = "слишком много сэмплов!";
    strings["too many samples!##sgda1"].plurals[0] = "слишком много сэмплов!";
    strings["couldn't paste! make sure your sample is 8 or 16-bit.##sgda"].plurals[0] = "Не получилось вставить сэмпл! убедитесь, что это 8- или 16-битный сэмпл.";
    strings["too many instruments!##sgda2"].plurals[0] = "слишком много инструментов!";
    strings["select at least one sample!##sgda"].plurals[0] = "выберите хотя бы один сэмпл!";
    strings["maximum size is 256 samples!##sgda"].plurals[0] = "максимальный размер равен 256 сэмплам!";
    strings["too many wavetables!##sgda2"].plurals[0] = "слишком много волновых таблиц!";

    //   sgec  src/gui/editControls.cpp

    strings["Mobile Edit###MobileEdit"].plurals[0] = "Мобильное меню редактирования###MobileEdit";
    strings["Mobile Controls###Mobile Controls"].plurals[0] = "Мобильное меню управления###Mobile Controls";
    strings["Mobile Menu###Mobile Menu"].plurals[0] = "Мобильное меню###Mobile Menu";
    strings["Pattern##sgec0"].plurals[0] = "Паттерны";
    strings["Orders##sgec0"].plurals[0] = "МАтрица паттернов";
    strings["Ins##sgec"].plurals[0] = "Инстр.";
    strings["Wave##sgec"].plurals[0] = "Волн. табл.";
    strings["Sample##sgec"].plurals[0] = "Сэмплы";
    strings["Song##sgec"].plurals[0] = "Трек";
    strings["Channels##sgec"].plurals[0] = "Каналы";
    strings["Chips##sgec"].plurals[0] = "Чипы";
    strings["Mixer##sgec"].plurals[0] = "Микшер";
    strings["Other##sgec"].plurals[0] = "Другое";
    strings["New##sgec"].plurals[0] = "Новый";
    strings["Unsaved changes! Save changes before creating a new song?##sgec"].plurals[0] = "Остались несохранённые изменения! Сохранить их перед созданием нового трека?";
    strings["Open##sgec"].plurals[0] = "Открыть";
    strings["Save##sgec"].plurals[0] = "Сохранить";
    strings["Save as...##sgec"].plurals[0] = "Сохранить как...";
    strings["Legacy .dmf##sgec"].plurals[0] = ".dmf (legacy)";
    strings["Export##sgec"].plurals[0] = "Экспорт";
    strings["Restore Backup##sgec"].plurals[0] = "Загрузить резервную копию";
    strings["Song Info##sgec"].plurals[0] = "О треке";
    strings["Subsongs##sgec"].plurals[0] = "Подпесни";
    strings["Speed##sgec"].plurals[0] = "Скорость";
    strings["Channels here...##sgec"].plurals[0] = "Каналы здесь...";
    strings["Chips here...##sgec"].plurals[0] = "Чипы здесь...";
    strings["What the hell...##sgec"].plurals[0] = "Что за хрень...";
    strings["Osc##sgec"].plurals[0] = "Осц.";
    strings["ChanOsc##sgec"].plurals[0] = "Осц-фы кан.";
    strings["RegView##sgec"].plurals[0] = "Регистры";
    strings["Stats##sgec"].plurals[0] = "Стат.";
    strings["Grooves##sgec"].plurals[0] = "Ритм-паттерны";
    strings["Compat Flags##sgec"].plurals[0] = "Флаги совм.";
    strings["XYOsc##sgec"].plurals[0] = "Осц. XY";
    strings["Panic##sgec"].plurals[0] = "Паника";
    strings["Settings##sgec"].plurals[0] = "Настройки";
    strings["Log##sgec"].plurals[0] = "Логи";
    strings["Debug##sgec"].plurals[0] = "Отладка";
    strings["About##sgec"].plurals[0] = "О программе";
    strings["Switch to Desktop Mode##sgec"].plurals[0] = "Переключ. на интерфейс ПК";
    strings["this is NOT ROM export! only use for making sure the\n"
            "Furnace Amiga emulator is working properly by\n"
            "comparing it with real Amiga output."].plurals[0] = 

            "это НЕ экспорт в файл ROM! используйте только для\n"
            "проверки того, что эмулятор Амиги в Furnace работает правильно,\n"
            "сравнивая звук настоящей Амиги и Furnace.";
    strings["Directory##sgec"].plurals[0] = "Папка";
    strings["Bake Data##sgec"].plurals[0] = "Создать данные";
    strings["Done! Baked %d files.##sgec"].plurals[0] = "Готово! Создан %d файл.";
    strings["Done! Baked %d files.##sgec"].plurals[1] = "Готово! Создано %d файла.";
    strings["Done! Baked %d files.##sgec"].plurals[2] = "Готово! Создано %d файлов.";
    strings["Play/Edit Controls###Play/Edit Controls"].plurals[0] = "Управл. воспр./ред.###Play/Edit Controls";
    strings["Octave##sgec0"].plurals[0] = "Октава";
    strings["Edit Step##sgec0"].plurals[0] = "Шаг редактирования";
    strings["Play##sgec0"].plurals[0] = "Воспроизвести";
    strings["Stop##sgec0"].plurals[0] = "Стоп";
    strings["Edit##sgec0"].plurals[0] = "Режим редактирования";
    strings["Metronome##sgec0"].plurals[0] = "Метроном";
    strings["Follow##sgec0"].plurals[0] = "Следовать за прогрессом воспроизведения";
    strings["Orders##sgec1"].plurals[0] = "Матрица паттернов";
    strings["Pattern##sgec1"].plurals[0] = "Паттерны";
    strings["Repeat pattern##sgec0"].plurals[0] = "Зациклить текущий паттерн";
    strings["Step one row##sgec0"].plurals[0] = "Сделать один шаг по паттерну";
    strings["Poly##PolyInput"].plurals[0] = "Полифония##PolyInput";
    strings["Mono##PolyInput"].plurals[0] = "Моно##PolyInput";
    strings["Polyphony##sgec0"].plurals[0] = "Полифония превью";
    strings["Stop##sgec1"].plurals[0] = "Стоп";
    strings["Play##sgec1"].plurals[0] = "Воспроизвести";
    strings["Step one row##sgec1"].plurals[0] = "Сделать один шаг по паттерну";
    strings["Repeat pattern##sgec1"].plurals[0] = "Зациклить текущий паттерн";
    strings["Edit##sgec1"].plurals[0] = "Режим редактирования";
    strings["Metronome##sgec1"].plurals[0] = "Метроном";
    strings["Octave##sgec1"].plurals[0] = "Октава";
    strings["Edit Step##sgec1"].plurals[0] = "Шаг";
    strings["Follow##sgec1"].plurals[0] = "Следовать за прогрессом воспроизведения";
    strings["Orders##sgec2"].plurals[0] = "Матрица паттернов";
    strings["Pattern##sgec2"].plurals[0] = "Паттерны";
    strings["Poly##PolyInput"].plurals[0] = "Полифония##PolyInput";
    strings["Mono##PolyInput"].plurals[0] = "Моно##PolyInput";
    strings["Polyphony##sgec1"].plurals[0] = "Полифония превью";
    strings["Play##sgec2"].plurals[0] = "Воспроизвести";
    strings["Stop##sgec2"].plurals[0] = "const ";
    strings["Step one row##sgec2"].plurals[0] = "Сделать один шаг по паттерну";
    strings["Repeat pattern##sgec2"].plurals[0] = "Зациклить текущий паттерн";
    strings["Edit##sgec2"].plurals[0] = "Режим редактирования";
    strings["Metronome##sgec2"].plurals[0] = "Метроном";
    strings["Oct.##sgec"].plurals[0] = "Окт.";
    strings["Octave##sgec2"].plurals[0] = "Октава";
    strings["Step##sgec0"].plurals[0] = "Шаг";
    strings["Foll.##sgec"].plurals[0] = "След.";
    strings["Follow##sgec2"].plurals[0] = "Следовать за прогрессом воспроизведения";
    strings["Ord##FollowOrders"].plurals[0] = "Матр.##FollowOrders";
    strings["Orders##sgec3"].plurals[0] = "Матрица паттернов";
    strings["Pat##FollowPattern"].plurals[0] = "Патт.##FollowPattern";
    strings["Pattern##sgec3"].plurals[0] = "Паттерны";
    strings["Poly##PolyInput"].plurals[0] = "Полифония##PolyInput";
    strings["Mono##PolyInput"].plurals[0] = "Моно##PolyInput";
    strings["Polyphony##sgec2"].plurals[0] = "Полифония превью";
    strings["Play Controls###Play Controls"].plurals[0] = "Управление воспроизведением###Play Controls";
    strings["Stop##sgec3"].plurals[0] = "Стоп";
    strings["Play##sgec3"].plurals[0] = "Воспроизвести";
    strings["Play from the beginning of this pattern##sgec"].plurals[0] = "Воспроизвести с начала этого паттерна";
    strings["Repeat from the beginning of this pattern##sgec"].plurals[0] = "Воспроизвести с начала этого паттерна с зацикливанием паттерна";
    strings["Step one row##sgec3"].plurals[0] = "Сделать один шаг по паттерну";
    strings["Edit##sgec3"].plurals[0] = "Редактировать";
    strings["Metronome##sgec3"].plurals[0] = "Метроном";
    strings["Repeat pattern##sgec3"].plurals[0] = "Зациклить текущий паттерн";
    strings["Poly##PolyInput"].plurals[0] = "Полифония##PolyInput";
    strings["Mono##PolyInput"].plurals[0] = "Моно##PolyInput";
    strings["Polyphony##sgec3"].plurals[0] = "Полифония превью";
    strings["Edit Controls###Edit Controls"].plurals[0] = "Управление редактированием###Edit Controls";
    strings["Octave##sgec3"].plurals[0] = "Октава";
    strings["Step##sgec1"].plurals[0] = "Шаг";
    strings["Follow orders##sgec"].plurals[0] = "След. за воспр. в матр. патт.";
    strings["Follow pattern##sgec"].plurals[0] = "След. за воспр. в патт.";

    //   sged  src/gui/editing.cpp

    strings["can't collapse any further!##sged"].plurals[0] = "дальнейшее сжатие невозможно!";
    strings["can't expand any further!##sged"].plurals[0] = "дальнейшее расширение невозможно!";

    //   sgef  src/gui/effectList.cpp

    strings["Effect List###Effect List"].plurals[0] = "Список эффектов###Effect List";
    strings["Chip at cursor: %s##sgef"].plurals[0] = "Курсор на канале чипа: %s";
    strings["All##sgef"].plurals[0] = "Все";
    strings["None##sgef"].plurals[0] = "Ни одного";
    strings["Name##sgef"].plurals[0] = "Имя";
    strings["Description##sgef"].plurals[0] = "Описание";

    //   sgeo  src/gui/exportOptions.cpp

    strings["one file##sgeo"].plurals[0] = "один файл";
    strings["multiple files (one per chip)##sgeo"].plurals[0] = "файлы (по одному на чип)";
    strings["multiple files (one per channel)##sgeo"].plurals[0] = "файлы (по одному на канал)";
    strings["Loops##sgeo"].plurals[0] = "Повторов трека";
    strings["Fade out (seconds)##sgeo"].plurals[0] = "Затухание (в секундах)";
    strings["Cancel##sgeo0"].plurals[0] = "Отмена";
    strings["Export##sgeo0"].plurals[0] = "Экспорт";
    strings["settings:##sgeo"].plurals[0] = "настройки:";
    strings["format version##sgeo"].plurals[0] = "версия формата";
    strings["loop##sgeo0"].plurals[0] = "зациклить";
    strings["loop trail:##sgeo"].plurals[0] = "маркер конца цикла:";
    strings["auto-detect##sgeo"].plurals[0] = "автоматически";
    strings["add one loop##sgeo1"].plurals[0] = "добавить один цикл";
    strings["custom##sgeo"].plurals[0] = "пользовательский";
    strings["add pattern change hints##sgeo"].plurals[0] = "добавить метки концов паттернов";
    strings["inserts data blocks on pattern changes.\n"
            "useful if you are writing a playback routine.\n\n"
            "the format of a pattern change data block is:\n"
            "67 66 FE ll ll ll ll 01 oo rr pp pp pp ...\n"
            "- ll: length, a 32-bit little-endian number\n"
            "- oo: order\n"
            "- rr: initial row (a 0Dxx effect is able to select a different row)\n"
            "- pp: pattern index (one per channel)\n\n"
            "pattern indexes are ordered as they appear in the song."].plurals[0] = 

            "вставляет блоки данных в местах смены паттернов.\n"
            "полезно, если вы пишете программу для воспроизведения.\n\n"
            "формат блока данных при смене паттерна:\n"
            "67 66 FE ll ll ll ll 01 oo rr pp pp pp ...\n"
            "- ll: длина, 32-битное число, прямой порядок байтов (little endian)\n"
            "- oo: строка матрицы паттернов\n"
            "- rr: начальная строка паттерна (эффект 0Dxx может её поменять)\n"
            "- pp: индекс паттерна (один на канал)\n\n"
            "индексы паттернов рассортированы в том порядке, в котором они\n"
            "встречаются в треке\n";
    strings["direct stream mode##sgeo"].plurals[0] = "запись прямого потока";
    strings["required for DualPCM and MSM6258 export.\n\n"
            "allows for volume/direction changes when playing samples,\n"
            "at the cost of a massive increase in file size."].plurals[0] = 

            "необходим для экспорта DualPCM и MSM6258.\n\n"
            "повзоляет записывать изменение громкости/направления воспроизведения сэмплов\n"
            "ценой сильного увеличения размера файла.";
    strings["chips to export:##sgeo"].plurals[0] = "экспорт следующих чипов:";
    strings["this chip is only available in VGM %d.%.2x and higher!##sgeo"].plurals[0] = "этот чип доступен только в файле VGM версии %d.%.2x и выше!";
    strings["this chip is not supported by the VGM format!##sgeo"].plurals[0] = "этот чип не поддерживается форматом VGM!";
    strings["select the chip you wish to export, but only up to %d of each type.##sgeo"].plurals[0] = "выберите чипы, данные для которых вы хотите включить в файл, но не более %d чипа каждого типа.";
    strings["select the chip you wish to export, but only up to %d of each type.##sgeo"].plurals[1] = "выберите чипы, данные для которых вы хотите включить в файл, но не более %d чипов каждого типа.";
    strings["select the chip you wish to export, but only up to %d of each type.##sgeo"].plurals[2] = "выберите чипы, данные для которых вы хотите включить в файл, но не более %d чипов каждого типа.";
    strings["Cancel##sgeo1"].plurals[0] = "Отмена";
    strings["Export##sgeo1"].plurals[0] = "Экспорт";
    strings["nothing to export##sgeo2"].plurals[0] = "нечего экспортировать";
    strings["Cancel##sgeo2"].plurals[0] = "Отмена";
    strings["Commander X16 Zsound Music File##sgeo"].plurals[0] = "Commander X16 Zsound Music File";
    strings["Tick Rate (Hz)##sgeo"].plurals[0] = "Частота движка (Гц)";
    strings["loop##sgeo2"].plurals[0] = "зациклить";
    strings["optimize size##sgeo"].plurals[0] = "оптимизировать размер";
    strings["Cancel##sgeo3"].plurals[0] = "Отмена";
    strings["Export##sgeo3"].plurals[0] = "Экспорт";
    strings["DefleMask file (1.1.3+)##sgeo"].plurals[0] = "Файл DefleMask (1.1.3+)";
    strings["Cancel##sgeo4"].plurals[0] = "Отмена";
    strings["Export##sgeo4"].plurals[0] = "Экспорт";
    strings["DefleMask file (1.0/legacy)##sgeo"].plurals[0] = "Файл DefleMask (1.0/legacy)";
    strings["Cancel##sgeo5"].plurals[0] = "Отмена";
    strings["Export##sgeo5"].plurals[0] = "Экспорт";
    strings["Directory##sgeo"].plurals[0] = "Папка";
    strings["Cancel##sgeo6"].plurals[0] = "Отмена";
    strings["Bake Data##sgeo"].plurals[0] = "Создать данные";
    strings["Done! Baked %d files.##sgeo"].plurals[0] = "Готово! Создан %d файл.";
    strings["Done! Baked %d files.##sgeo"].plurals[1] = "Готово! Создано %d файла.";
    strings["Done! Baked %d files.##sgeo"].plurals[2] = "Готово! Создано %d файлов.";
    strings["this option exports the song to a text file.\n##sgeo"].plurals[0] = "эта опция позволяет экспортировать трек в текстовый файл.\n";
    strings["Cancel##sgeo7"].plurals[0] = "Отмена";
    strings["Export##sgeo6"].plurals[0] = "Экспорт";
    strings["this option exports a text or binary file which\n"
            "contains a dump of the internal command stream\n"
            "produced when playing the song.\n\n"
            "technical/development use only!"].plurals[0] = 

            "эта опция позволяет создать текстовый или бинарный файл,\n"
            "в котором содержится дамп внутренних команд,\n"
            "созданных во время проигрыаания трека.\n\n"
            "используйте только при разработке!";
    strings["Cancel##sgeo8"].plurals[0] = "Отмена";
    strings["Export (binary)##sgeo"].plurals[0] = "Экспорт (бинарный)";
    strings["Export (text)##sgeo"].plurals[0] = "Экспорт (текст)";
    strings["Audio##sgeo"].plurals[0] = "Аудио";
    strings["DMF (1.0/legacy)##sgeo"].plurals[0] = "DMF (1.0/legacy)";
    strings["Amiga Validation##sgeo"].plurals[0] = "Проверка Amiga";
    strings["Text##sgeo"].plurals[0] = "Текст";
    strings["Command Stream##sgeo"].plurals[0] = "Поток команд";
    strings["congratulations! you've unlocked a secret panel.##sgeo"].plurals[0] = "поздравляю! вы открыли секретную панель.";
    strings["Toggle hidden systems##sgeo"].plurals[0] = "Включить скрытые системы";
    strings["Toggle all instrument types##sgeo"].plurals[0] = "Включить все типы инструментов";
    strings["Set pitch linearity to Partial##sgeo"].plurals[0] = "Выставить частичную линейность высоты тона";
    strings["Enable multi-threading settings##sgeo"].plurals[0] = "Открыть настройки многопоточности";
    strings["Set fat to max##sgeo"].plurals[0] = "Выкрутить жирность на максимум";
    strings["Set muscle and fat to zero##sgeo"].plurals[0] = "Убрать все мышцы и жир";
    strings["Tell tildearrow this must be a mistake##sgeo"].plurals[0] = "Сказать tildearrow, что, возможно, это ошибка";
    strings["yeah, it's a bug. write a bug report in the GitHub page and tell me how did you get here.##sgeo"].plurals[0] = "да, это баг. заполните отчёт на гитхабе и скажите мне, как вы сюда добрались.";

    //   sgfr  src/gui/findReplace.cpp

    strings["ignore##sgfr"].plurals[0] = "игнорировать";
    strings["equals##sgfr"].plurals[0] = "равно";
    strings["not equal##sgfr"].plurals[0] = "не равно";
    strings["between##sgfr"].plurals[0] = "между";
    strings["not between##sgfr"].plurals[0] = "за пределами интервала";
    strings["any##sgfr"].plurals[0] = "любой";
    strings["none##sgfr"].plurals[0] = "никакого";
    strings["set##sgfr"].plurals[0] = "выставить значение";
    strings["add##sgfr"].plurals[0] = "добавить";
    strings["add (overflow)##sgfr"].plurals[0] = "добавить (с переполнением)";
    strings["scale %##sgfr"].plurals[0] = "масштабировать (в %)";
    strings["clear##sgfr"].plurals[0] = "удалить";

    strings["Find/Replace###Find/Replace"].plurals[0] = "Найти/Заменить###Find/Replace";
    strings["Find##sgfr0"].plurals[0] = "Найти";
    strings["order##sgfr0"].plurals[0] = "строка матрицы паттернов";
    strings["row##sgfr0"].plurals[0] = "строка";
    strings["order##sgfr1"].plurals[0] = "строка матрицы паттернов";
    strings["row##sgfr1"].plurals[0] = "строка";
    strings["channel##sgfr"].plurals[0] = "канал";
    strings["go##sgfr"].plurals[0] = "запустить";
    strings["no matches found!##sgfr"].plurals[0] = "совпадений не найдено!";
    strings["Back##sgfr"].plurals[0] = "Назад";
    strings["Note##sgfr0"].plurals[0] = "Нота";
    strings["Ins##sgfr0"].plurals[0] = "Инструмент";
    strings["Volume##sgfr0"].plurals[0] = "Громкость";
    strings["Effect##sgfr0"].plurals[0] = "Эффект";
    strings["Value##sgfr0"].plurals[0] = "Параметр";
    strings["Delete query##sgfr"].plurals[0] = "Удалить строку";
    strings["Add effect##sgfr0"].plurals[0] = "Добавить эффект";
    strings["Remove effect##sgfr0"].plurals[0] = "Удалить эффект";
    strings["Search range:##sgfr"].plurals[0] = "Диапазон поиска:";
    strings["Song##sgfr"].plurals[0] = "Трек";
    strings["Selection##sgfr"].plurals[0] = "Выделенное";
    strings["Pattern##sgfr"].plurals[0] = "Паттерн";
    strings["Confine to channels##sgfr"].plurals[0] = "Только выбранные каналы";
    strings["From##sgfr"].plurals[0] = "От";
    strings["To##sgfr"].plurals[0] = "До";
    strings["Match effect position:##sgfr"].plurals[0] = "Совпадение с положением эффекта:";
    strings["No##sgfr"].plurals[0] = "Нет";
    strings["match effects regardless of position.##sgfr"].plurals[0] = "эффекты обнаруживаются вне зависимости от положения.";
    strings["Lax##sgfr"].plurals[0] = "Нестрогое";
    strings["match effects only if they appear in-order.##sgfr"].plurals[0] = "эффекты обнаруживаются, если они идут в правильном порядке.";
    strings["Strict##sgfr"].plurals[0] = "Строгое";
    strings["match effects only if they appear exactly as specified.##sgfr"].plurals[0] = "эффекты обнаруживаются, если они полностью соответствуют запросу.";
    strings["Find##sgfr1"].plurals[0] = "Найти";
    strings["Replace##sgfr"].plurals[0] = "Заменить";
    strings["Note##sgfr1"].plurals[0] = "Нота";
    strings["INVALID##sgfr"].plurals[0] = "НЕДЕЙСТВ.";
    strings["Ins##sgfr1"].plurals[0] = "Инструмент";
    strings["Volume##sgfr1"].plurals[0] = "Громкость";
    strings["Effect##sgfr1"].plurals[0] = "Эффект";
    strings["Value##sgfr1"].plurals[0] = "Параметр";
    strings["Add effect##sgfr1"].plurals[0] = "Добавить эффект";
    strings["Remove effect##sgfr1"].plurals[0] = "Удалить эффект";
    strings["Effect replace mode:##sgfr"].plurals[0] = "Режим замены эффектов:";
    strings["Replace matches only##sgfr"].plurals[0] = "Заменять только совпадения";
    strings["Replace matches, then free spaces##sgfr"].plurals[0] = "Заменять совпадения, заполнять пустые ячейки";
    strings["Clear effects##sgfr"].plurals[0] = "Заменять эффекты";
    strings["Insert in free spaces##sgfr"].plurals[0] = "Вставлять эффекты в пустых ячейках";
    strings["Replace##QueryReplace"].plurals[0] = "Заменить##QueryReplace";

    //   sggv  src/gui/grooves.cpp

    strings["Grooves###Grooves"].plurals[0] = "Ритм-паттерны###Grooves";
    strings["use effect 09xx to select a groove pattern.##sggv"].plurals[0] = "используйте эффект 09xx для выбора ритм-паттерна.##sggv";
    strings["pattern##sggv"].plurals[0] = "паттерн##sggv";
    strings["remove##sggv"].plurals[0] = "удалить##sggv";

    //   sgie  src/gui/insEdit.cpp

    strings["Name##sgie"].plurals[0] = "Название";
    strings["Open##sgie0"].plurals[0] = "Открыть";
    strings["Save##sgie"].plurals[0] = "Сохранить";
    strings["export .dmp...##sgie"].plurals[0] = "экспорт .dmp...";
    strings["Type##sgie"].plurals[0] = "Тип";
    strings["Unknown##sgie"].plurals[0] = "Неизвестен";
    strings["none of the currently present chips are able to play this instrument type!##sgie"].plurals[0] = "ни один из добавленных чипов не поддерживает этот тип инструмента!";
    strings["Error##sgie"].plurals[0] = "Ошибка";
    strings["invalid instrument type! change it first.##sgie"].plurals[0] = "недопустимый тип инструмента! сначала поменяйте его.";
    strings["Instrument Editor###Instrument Editor"].plurals[0] = "Ред. инструментов###Instrument Editor";
    strings["waiting...##sgie0"].plurals[0] = "ожидание...";
    strings["waiting...##sgie1"].plurals[0] = "ожидание...";
    strings["no instrument selected##sgie0"].plurals[0] = "не выбрано ни одного инструмента";
    strings["no instrument selected##sgie1"].plurals[0] = "не выбрано ни одного инструмента";
    strings["select one...##sgie"].plurals[0] = "выберите один...";
    strings["or##sgie0"].plurals[0] = "или";
    strings["Open##sgie1"].plurals[0] = "Откройте";
    strings["or##sgie1"].plurals[0] = "или";
    strings["Create New##sgie"].plurals[0] = "Создайте новый";
    strings["copy##sgie"].plurals[0] = "копировать";
    strings["paste##sgie"].plurals[0] = "вставить";
    strings["clear contents##sgie"].plurals[0] = "очистить содержимое";
    strings["offset...##sgie"].plurals[0] = "сместить...";
    strings["offset##sgie"].plurals[0] = "сместить";
    strings["scale...##sgie"].plurals[0] = "масштабировать...";
    strings["scale##sgie"].plurals[0] = "масштабировать";
    strings["randomize...##sgie"].plurals[0] = "заполнить случайными значениями...";
    strings["Min##sgie"].plurals[0] = "Минимум";
    strings["Max##sgie"].plurals[0] = "Максимум";
    strings["randomize##sgie"].plurals[0] = "заполнить";

    //   sgmx  src/gui/mixer.cpp

    strings["input##sgmx"].plurals[0] = "вход";
    strings["output##sgmx"].plurals[0] = "выход";
    strings["Mixer##sgmx"].plurals[0] = "Микшер";
    strings["Master Volume##sgmx"].plurals[0] = "Общая громкость";
    strings["Invert##sgmx"].plurals[0] = "Инвертировать";
    strings["Volume##sgmx"].plurals[0] = "Громкость";
    strings["Panning##sgmx"].plurals[0] = "Панорамирование";
    strings["Front/Rear##sgmx"].plurals[0] = "Передн./задн.";
    strings["Patchbay##sgmx"].plurals[0] = "Соединение каналов";
    strings["Automatic patchbay##sgmx"].plurals[0] = "Автоматически";
    strings["Display hidden ports##sgmx"].plurals[0] = "Отобразить скрытые порты";
    strings["Display internal##sgmx"].plurals[0] = "Внутренние порты";
    strings["System##sgmx0"].plurals[0] = "Система";
    strings["Sample Preview##sgmx"].plurals[0] = "Превью сэмпла";
    strings["Metronome##sgmx"].plurals[0] = "Метроном";
    strings["System##sgmx1"].plurals[0] = "Система";
    strings["disconnect all##sgmx"].plurals[0] = "отсоединить все";

    //   sgns  src/gui/newSong.cpp

    strings["Choose a System!##sgns"].plurals[0] = "Выберите систему!";
    strings["Search...##sgns"].plurals[0] = "Поиск...";
    strings["Categories##sgns"].plurals[0] = "Категории";
    strings["Systems##sgns"].plurals[0] = "Системы";
    strings["I'm feeling lucky##sgns"].plurals[0] = "Мне повезёт!";
    strings["Cancel##sgns"].plurals[0] = "Отмена";

    //   sgor  src/gui/orders.cpp

    strings["Add new order##sgor"].plurals[0] = "Добавить строку";
    strings["Remove order##sgor"].plurals[0] = "Удалить строку";
    strings["Duplicate order (right-click to deep clone)##sgor"].plurals[0] = "Клонировать строку (ПКМ для клонирования с выделением новых индексов)";
    strings["Move order up##sgor"].plurals[0] = "Сдвинуть строку вверх";
    strings["Move order down##sgor"].plurals[0] = "двинуть строку вниз";
    strings["Duplicate order at end of song (right-click to deep clone)##sgor"].plurals[0] = "Клонировать строку (ПКМ для клонирования с выделением новых индексов) в конец трека";
    strings["Order change mode: entire row##sgor"].plurals[0] = "Режим изменения: вся строка";
    strings["Order change mode: one##sgor"].plurals[0] = "Режим изменения: ячейка";
    strings["Order edit mode: Select and type (scroll vertically)##sgor"].plurals[0] = "Режим редактирования: Выбрать и печатать (вертикальная прокрутка)";
    strings["Order edit mode: Select and type (scroll horizontally)##sgor"].plurals[0] = "Режим редактирования: Выбрать и печатать (горизонтальная прокрутка)";
    strings["Order edit mode: Select and type (don't scroll)##sgor"].plurals[0] = "Режим редактирования: Выбрать и печатать (без прокрутки)";
    strings["Order edit mode: Click to change##sgor"].plurals[0] = "Режим редактирования: нажмите для изменения";

    //   sgos  src/gui/osc.cpp

    strings["Oscilloscope###Oscilloscope"].plurals[0] = "Осциллограф###Oscilloscope";
    strings["zoom: %.2fx (%.1fdB)##sgos"].plurals[0] = "увеличение: %.2fx (%.1f дБ)";
    strings["window size: %.1fms##sgos"].plurals[0] = "ширина окна: %.1f мс";
    strings["(-Infinity)dB##sgos"].plurals[0] = "(минус бесконечность) дБ";

    //   sgpm  src/gui/patManager.cpp

    strings["Pattern Manager###Pattern Manager"].plurals[0] = "Менеджер паттернов###Pattern Manager";
    strings["Global Tasks##sgpm"].plurals[0] = "Глобальное редактирование";
    strings["De-duplicate patterns##sgpm"].plurals[0] = "Удалить дубликаты паттернов";
    strings["Re-arrange patterns##sgpm"].plurals[0] = "Отсортировать паттерны";
    strings["Pattern %.2X\n- not allocated##sgpm"].plurals[0] = "Паттерн %.2X\n- не используется";
    strings["Pattern %.2X\n- use count: %d (%.0f%%)\n\nright-click to erase##sgpm"].plurals[0] = "Паттерн %.2X\n- сколько раз встречается в треке: %d (%.0f%%)\n\nПКМ, чтобы удалить";

    //   sgpa  src/gui/pattern.cpp

    strings["Pattern###Pattern"].plurals[0] = "Паттерны###Pattern";
    strings["click for pattern options (effect columns/pattern names/visualizer)##sgpa"].plurals[0] = "нажмите для открытия меню настроек (столбцы эффектов/названия паттернов/визуализатор эффектов)";
    strings["Options:##sgpa"].plurals[0] = "Настройки:";
    strings["Effect columns/collapse##sgpa"].plurals[0] = "Столбцы эффектов и свёртка канала";
    strings["Pattern names##sgpa"].plurals[0] = "Названия паттернов";
    strings["Channel group hints##sgpa"].plurals[0] = "Подсказки о группировке каналов";
    strings["Visualizer##sgpa"].plurals[0] = "Визуализатор эффектов";
    strings["Channel status:##sgpa"].plurals[0] = "Статус канала:";
    strings["No##_PCS0"].plurals[0] = "Нет##_PCS0";
    strings["Yes##_PCS1"].plurals[0] = "Да##_PCS1";
    strings["WARNING!!##sgpa"].plurals[0] = "ВНИМАНИЕ!!!";
    strings["this instrument cannot be previewed because##sgpa"].plurals[0] = "превью этого инструмента невозможно, потому что";
    strings["none of the chips can play it##sgpa"].plurals[0] = "ни один из чипов не совместим с ним";
    strings["your instrument is in peril!! be careful...##sgpa"].plurals[0] = "ваш инструмент под угрозой!! будьте осторожны...";

    //   sgpi  src/gui/piano.cpp

    strings["Piano###Piano"].plurals[0] = "Клав. пианино###Piano";
    strings["Options##sgpi"].plurals[0] = "Настройки";
    strings["Key layout:##sgpi"].plurals[0] = "Компоновка клавиш:";
    strings["Automatic##sgpi"].plurals[0] = "Автоматически";
    strings["Standard##sgpi"].plurals[0] = "Стандартная";
    strings["Continuous##sgpi"].plurals[0] = "Непрерывная";
    strings["Value input pad:##sgpi"].plurals[0] = "Панель ввода значений:";
    strings["Disabled##sgpi"].plurals[0] = "Выкл.";
    strings["Replace piano##sgpi"].plurals[0] = "Заменяет пианино";
    strings["Split (automatic)##sgpi"].plurals[0] = "Разделённая (автоматически)";
    strings["Split (always visible)##sgpi"].plurals[0] = "Разделённая (всегда отображать)";
    strings["Share play/edit offset/range##sgpi"].plurals[0] = "Соблюдать настройки из окна настроек воспроизв./ред.";
    strings["Read-only (can't input notes)##sgpi"].plurals[0] = "Только чтение (нельзя вводить ноты)";
    strings["Input Pad###Input Pad"].plurals[0] = "Панель ввода###Input Pad";

    //   sgpr  src/gui/presets.cpp

    strings["Game consoles##sgpr"].plurals[0] = "Игровые консоли";
    strings["let's play some chiptune making games!##sgpr"].plurals[0] = "давайте поиграем в создание чиптюнов!";
    strings["Sega Genesis (extended channel 3)##sgpr"].plurals[0] = "Sega Genesis (расширенный 3-ий канал)";
    strings["Sega Genesis (DualPCM, extended channel 3)##sgpr"].plurals[0] = "Sega Genesis (DualPCM, расширенный 3-ий канал)";
    strings["Sega Genesis (with Sega CD)##sgpr"].plurals[0] = "Sega Genesis (с Sega CD)";
    strings["Sega Genesis (extended channel 3 with Sega CD)##sgpr"].plurals[0] = "Sega Genesis (расширенный 3-ий канал с Sega CD)";
    strings["Sega Genesis (CSM with Sega CD)##sgpr"].plurals[0] = "Sega Genesis (CSM с Sega CD)";
    strings["Sega Master System (with FM expansion)##sgpr"].plurals[0] = "Sega Master System (с FM-расширением)";
    strings["Sega Master System (with FM expansion in drums mode)##sgpr"].plurals[0] = "Sega Master System (с FM-расширением в режиме ударных)";
    strings["Famicom with Konami VRC6##sgpr"].plurals[0] = "Famicom с Konami VRC6";
    strings["Famicom with Konami VRC7##sgpr"].plurals[0] = "Famicom с Konami VRC7";
    strings["Famicom with MMC5##sgpr"].plurals[0] = "Famicom с MMC5";
    strings["Famicom with Sunsoft 5B##sgpr"].plurals[0] = "Famicom с Sunsoft 5B";
    strings["Famicom with Namco 163##sgpr"].plurals[0] = "Famicom с Namco 163";
    strings["Neo Geo AES (extended channel 2)##sgpr"].plurals[0] = "Neo Geo AES (расширенный 2-ой канал)";
    strings["Neo Geo AES (extended channel 2 and CSM)##sgpr"].plurals[0] = "Neo Geo AES (расширенный 2-ой канал и CSM)";
    strings["Computers##sgpr"].plurals[0] = "Компьютеры";
    strings["let's get to work on chiptune today.##sgpr"].plurals[0] = "давайте сегодня поработаем над чиптюнами.";
    strings["Commodore 64 (C64, 6581 SID + Sound Expander in drums mode)##sgpr"].plurals[0] = "Commodore 64 (C64, 6581 SID + Sound Expander в режиме ударных)";
    strings["Commodore 64 (C64, 8580 SID + Sound Expander in drums mode)##sgpr"].plurals[0] = "Commodore 64 (C64, 8580 SID + Sound Expander в режиме ударных)";
    strings["Commodore 64 (C64, 6581 SID + FM-YAM in drums mode)##sgpr"].plurals[0] = "Commodore 64 (C64, 6581 SID + FM-YAM в режиме ударных)";
    strings["Commodore 64 (C64, 8580 SID + FM-YAM in drums mode)##sgpr"].plurals[0] = "Commodore 64 (C64, 8580 SID + FM-YAM в режиме ударных)";
    strings["MSX + MSX-AUDIO (drums mode)##sgpr"].plurals[0] = "MSX + MSX-AUDIO (в режиме ударных)";
    strings["MSX + MSX-MUSIC (drums mode)##sgpr"].plurals[0] = "MSX + MSX-MUSIC (в режиме ударных)";
    strings["MSX + Neotron (extended channel 2)##sgpr"].plurals[0] = "MSX + Neotron (расширенный 2-ой канал)";
    strings["MSX + Neotron (extended channel 2 and CSM)##sgpr"].plurals[0] = "MSX + Neotron (расширенный 2-ой канал и CSM)";
    strings["MSX + Neotron (with YM2610B)##sgpr"].plurals[0] = "MSX + Neotron (с YM2610B)";
    strings["MSX + Neotron (with YM2610B; extended channel 3)##sgpr"].plurals[0] = "MSX + Neotron (с YM2610B; расширенный 3-ий канал 3)";
    strings["MSX + Neotron (with YM2610B; extended channel 3 and CSM)##sgpr"].plurals[0] = "MSX + Neotron (с YM2610B; расширенный 3-ий канал и CSM)";
    strings["NEC PC-88 (with PC-8801-10)##sgpr"].plurals[0] = "NEC PC-88 (с PC-8801-10)";
    strings["NEC PC-88 (with PC-8801-11)##sgpr"].plurals[0] = "NEC PC-88 (с PC-8801-11)";
    strings["NEC PC-88 (with PC-8801-11; extended channel 3)##sgpr"].plurals[0] = "NEC PC-88 (с PC-8801-11; расширенный 3-ий канал)";
    strings["NEC PC-88 (with PC-8801-11; extended channel 3 and CSM)##sgpr"].plurals[0] = "NEC PC-88 (с PC-8801-11; расширенный 3-ий канал и CSM)";
    strings["NEC PC-88 (with PC-8801-23)##sgpr"].plurals[0] = "NEC PC-88 (с PC-8801-23)";
    strings["NEC PC-88 (with PC-8801-23; extended channel 3)##sgpr"].plurals[0] = "NEC PC-88 (с PC-8801-23; расширенный 3-ий канал)";
    strings["NEC PC-88 (with PC-8801-23; extended channel 3 and CSM)##sgpr"].plurals[0] = "NEC PC-88 (с PC-8801-23; расширенный 3-ий канал и CSM)";
    strings["NEC PC-88 (with HMB-20 HIBIKI-8800)##sgpr"].plurals[0] = "NEC PC-88 (с HMB-20 HIBIKI-8800)";
    strings["NEC PC-8801mk2SR (with PC-8801-10)##sgpr"].plurals[0] = "NEC PC-8801mk2SR (с PC-8801-10)";
    strings["NEC PC-8801mk2SR (with PC-8801-10; extended channel 3)##sgpr"].plurals[0] = "NEC PC-8801mk2SR (с PC-8801-10; расширенный 3-ий канал)";
    strings["NEC PC-8801mk2SR (with PC-8801-10; extended channel 3 and CSM)##sgpr"].plurals[0] = "NEC PC-8801mk2SR (с PC-8801-10; расширенный 3-ий канал и CSM)";
    strings["NEC PC-8801mk2SR (with PC-8801-11)##sgpr"].plurals[0] = "NEC PC-8801mk2SR (с PC-8801-11)";
    strings["NEC PC-8801mk2SR (with PC-8801-11; extended channel 3 on internal OPN)##sgpr"].plurals[0] = "NEC PC-8801mk2SR (с PC-8801-11; расширенный 3-ий канал на внутреннем чипе OPN)";
    strings["NEC PC-8801mk2SR (with PC-8801-11; extended channel 3 on external OPN)##sgpr"].plurals[0] = "NEC PC-8801mk2SR (с PC-8801-11; расширенный 3-ий канал на внешнем чипе OPN)";
    strings["NEC PC-8801mk2SR (with PC-8801-11; extended channel 3 on both OPNs)##sgpr"].plurals[0] = "NEC PC-8801mk2SR (с PC-8801-11; расширенный 3-ий канал на обоих чипах OPN)";
    strings["NEC PC-8801mk2SR (with PC-8801-11; extended channel 3 and CSM on both OPNs)##sgpr"].plurals[0] = "NEC PC-8801mk2SR (с PC-8801-11; расширенный 3-ий канал и CSM на обоих чипах OPN)";
    strings["NEC PC-8801mk2SR (with PC-8801-23)##sgpr"].plurals[0] = "NEC PC-8801mk2SR (с PC-8801-23)";
    strings["NEC PC-8801mk2SR (with PC-8801-23; extended channel 3 on internal OPN)##sgpr"].plurals[0] = "NEC PC-8801mk2SR (с PC-8801-23; расширенный 3-ий канал на внутреннем чипе OPN)";
    strings["NEC PC-8801mk2SR (with PC-8801-23; extended channel 3 and CSM on internal OPN)##sgpr"].plurals[0] = "NEC PC-8801mk2SR (с PC-8801-23; расширенный 3-ий канал и CSM на внутреннем чипе OPN)";
    strings["NEC PC-8801mk2SR (with PC-8801-23; extended channel 3 on external OPN)##sgpr"].plurals[0] = "NEC PC-8801mk2SR (с PC-8801-23; расширенный 3-ий канал на внешнем чипе OPN)";
    strings["NEC PC-8801mk2SR (with PC-8801-23; extended channel 3 and CSM on external OPN)##sgpr"].plurals[0] = "NEC PC-8801mk2SR (с PC-8801-23; расширенный 3-ий канал и CSM на внешнем чипе OPN)";
    strings["NEC PC-8801mk2SR (with PC-8801-23; extended channel 3 on both OPNs)##sgpr"].plurals[0] = "NEC PC-8801mk2SR (с PC-8801-23; extended channel 3 on both OPNs)";
    strings["NEC PC-8801mk2SR (with PC-8801-23; extended channel 3 and CSM on both OPNs)##sgpr"].plurals[0] = "NEC PC-8801mk2SR (с PC-8801-23; расширенный 3-ий канал и CSM на обоих чипах OPN)";
    strings["NEC PC-8801mk2SR (with HMB-20 HIBIKI-8800)##sgpr"].plurals[0] = "NEC PC-8801mk2SR (с HMB-20 HIBIKI-8800)";
    strings["NEC PC-8801mk2SR (with HMB-20 HIBIKI-8800; extended channel 3)##sgpr"].plurals[0] = "NEC PC-8801mk2SR (с HMB-20 HIBIKI-8800; расширенный 3-ий канал)";
    strings["NEC PC-8801mk2SR (with HMB-20 HIBIKI-8800; extended channel 3 and CSM)##sgpr"].plurals[0] = "NEC PC-8801mk2SR (с HMB-20 HIBIKI-8800; расширенный 3-ий канал и CSM)";
    strings["NEC PC-8801FA (with PC-8801-10)##sgpr"].plurals[0] = "NEC PC-8801FA (с PC-8801-10)";
    strings["NEC PC-8801FA (with PC-8801-10; extended channel 3)##sgpr"].plurals[0] = "NEC PC-8801FA (с PC-8801-10; расширенный 3-ий канал)";
    strings["NEC PC-8801FA (with PC-8801-11)##sgpr"].plurals[0] = "NEC PC-8801FA (с PC-8801-11)";
    strings["NEC PC-8801FA (with PC-8801-11; extended channel 3 on internal OPN)##sgpr"].plurals[0] = "NEC PC-8801FA (с PC-8801-11; расширенный 3-ий канал на внутреннем чипе OPN)";
    strings["NEC PC-8801FA (with PC-8801-11; extended channel 3 on external OPN)##sgpr"].plurals[0] = "NEC PC-8801FA (с PC-8801-11; расширенный 3-ий канал на внешнем чипе OPN)";
    strings["NEC PC-8801FA (with PC-8801-11; extended channel 3 and CSM on external OPN)##sgpr"].plurals[0] = "NEC PC-8801FA (с PC-8801-11; расширенный 3-ий канал и CSM на внешнем чипе OPN)";
    strings["NEC PC-8801FA (with PC-8801-11; extended channel 3 on both OPNs)##sgpr"].plurals[0] = "NEC PC-8801FA (с PC-8801-11; расширенный 3-ий канал на обоих чипах OPN)";
    strings["NEC PC-8801FA (with PC-8801-11; extended channel 3 and CSM on both OPNs)##sgpr"].plurals[0] = "NEC PC-8801FA (с PC-8801-11; расширенный 3-ий канал и CSM на обоих чипах OPN)";
    strings["NEC PC-8801FA (with PC-8801-23)##sgpr"].plurals[0] = "NEC PC-8801FA (с PC-8801-23)";
    strings["NEC PC-8801FA (with PC-8801-23; extended channel 3 on internal OPN)##sgpr"].plurals[0] = "NEC PC-8801FA (с PC-8801-23; расширенный 3-ий канал на внутреннем чипе OPN)";
    strings["NEC PC-8801FA (with PC-8801-23; extended channel 3 and CSM on internal OPN)##sgpr"].plurals[0] = "NEC PC-8801FA (с PC-8801-23; расширенный 3-ий канал и CSM на внутреннем чипе OPN)";
    strings["NEC PC-8801FA (with PC-8801-23; extended channel 3 on external OPN)##sgpr"].plurals[0] = "NEC PC-8801FA (с PC-8801-23; расширенный 3-ий канал на внешнем чипе OPN)";
    strings["NEC PC-8801FA (with PC-8801-23; extended channel 3 and CSM on external OPN)##sgpr"].plurals[0] = "NEC PC-8801FA (с PC-8801-23; расширенный 3-ий канал и CSM на внешнем чипе OPN)";
    strings["NEC PC-8801FA (with PC-8801-23; extended channel 3 on both OPNs)##sgpr"].plurals[0] = "NEC PC-8801FA (с PC-8801-23; расширенный 3-ий канал на обоих чипах OPN)";
    strings["NEC PC-8801FA (with PC-8801-23; extended channel 3 and CSM on both OPNs)##sgpr"].plurals[0] = "NEC PC-8801FA (с PC-8801-23; расширенный 3-ий канал и CSM на обоих чипах OPN)";
    strings["NEC PC-8801FA (with HMB-20 HIBIKI-8800)##sgpr"].plurals[0] = "NEC PC-8801FA (с HMB-20 HIBIKI-8800)";
    strings["NEC PC-8801FA (with HMB-20 HIBIKI-8800; extended channel 3)##sgpr"].plurals[0] = "NEC PC-8801FA (с HMB-20 HIBIKI-8800; расширенный 3-ий канал)";
    strings["NEC PC-8801FA (with HMB-20 HIBIKI-8800; extended channel 3 and CSM)##sgpr"].plurals[0] = "NEC PC-8801FA (с HMB-20 HIBIKI-8800; расширенный 3-ий канал и CSM)";
    strings["NEC PC-98 (with PC-9801-26/K)##sgpr"].plurals[0] = "NEC PC-98 (с PC-9801-26/K)";
    strings["NEC PC-98 (with PC-9801-26/K; extended channel 3)##sgpr"].plurals[0] = "NEC PC-98 (с PC-9801-26/K; расширенный 3-ий канал)";
    strings["NEC PC-98 (with PC-9801-26/K; extended channel 3 and CSM)##sgpr"].plurals[0] = "NEC PC-98 (с PC-9801-26/K; расширенный 3-ий канал и CSM)";
    strings["NEC PC-98 (with Sound Orchestra)##sgpr"].plurals[0] = "NEC PC-98 (с Sound Orchestra)";
    strings["NEC PC-98 (with Sound Orchestra; extended channel 3)##sgpr"].plurals[0] = "NEC PC-98 (с Sound Orchestra; расширенный 3-ий канал)";
    strings["NEC PC-98 (with Sound Orchestra; extended channel 3 and CSM)##sgpr"].plurals[0] = "NEC PC-98 (с Sound Orchestra; расширенный 3-ий канал и CSM)";
    strings["NEC PC-98 (with Sound Orchestra in drums mode)##sgpr"].plurals[0] = "NEC PC-98 (с Sound Orchestra в режиме ударных)";
    strings["NEC PC-98 (with Sound Orchestra in drums mode; extended channel 3)##sgpr"].plurals[0] = "NEC PC-98 (с Sound Orchestra в режиме ударных; расширенный 3-ий канал)";
    strings["NEC PC-98 (with Sound Orchestra in drums mode; extended channel 3 and CSM)##sgpr"].plurals[0] = "NEC PC-98 (с Sound Orchestra в режиме ударных; расширенный 3-ий канал и CSM)";
    strings["NEC PC-98 (with Sound Orchestra V)##sgpr"].plurals[0] = "NEC PC-98 (с Sound Orchestra V)";
    strings["NEC PC-98 (with Sound Orchestra V; extended channel 3)##sgpr"].plurals[0] = "NEC PC-98 (с Sound Orchestra V; расширенный 3-ий канал)";
    strings["NEC PC-98 (with Sound Orchestra V; extended channel 3 and CSM)##sgpr"].plurals[0] = "NEC PC-98 (с Sound Orchestra V; расширенный 3-ий канал и CSM)";
    strings["NEC PC-98 (with Sound Orchestra V in drums mode)##sgpr"].plurals[0] = "NEC PC-98 (с Sound Orchestra V в режиме ударных)";
    strings["NEC PC-98 (with Sound Orchestra V in drums mode; extended channel 3)##sgpr"].plurals[0] = "NEC PC-98 (с Sound Orchestra V в режиме ударных; расширенный 3-ий канал)";
    strings["NEC PC-98 (with Sound Orchestra V in drums mode; extended channel 3 and CSM)##sgpr"].plurals[0] = "NEC PC-98 (с Sound Orchestra V в режиме ударных; расширенный 3-ий канал и CSM)";
    strings["NEC PC-98 (with PC-9801-86)##sgpr"].plurals[0] = "NEC PC-98 (с PC-9801-86)";
    strings["NEC PC-98 (with PC-9801-86; extended channel 3)##sgpr"].plurals[0] = "NEC PC-98 (с PC-9801-86; расширенный 3-ий канал)";
    strings["NEC PC-98 (with PC-9801-86; extended channel 3 and CSM)##sgpr"].plurals[0] = "NEC PC-98 (с PC-9801-86; расширенный 3-ий канал и CSM)";
    strings["NEC PC-98 (with PC-9801-86) stereo##sgpr"].plurals[0] = "NEC PC-98 (с PC-9801-86) стерео";
    strings["NEC PC-98 (with PC-9801-86; extended channel 3) stereo##sgpr"].plurals[0] = "NEC PC-98 (с PC-9801-86; расширенный 3-ий канал) стерео";
    strings["NEC PC-98 (with PC-9801-86; extended channel 3 and CSM) stereo##sgpr"].plurals[0] = "NEC PC-98 (с PC-9801-86; расширенный 3-ий канал и CSM) стерео";
    strings["NEC PC-98 (with PC-9801-73)##sgpr"].plurals[0] = "NEC PC-98 (с PC-9801-73)";
    strings["NEC PC-98 (with PC-9801-73; extended channel 3)##sgpr"].plurals[0] = "NEC PC-98 (с PC-9801-73; расширенный 3-ий канал)";
    strings["NEC PC-98 (with PC-9801-73; extended channel 3 and CSM)##sgpr"].plurals[0] = "NEC PC-98 (с PC-9801-73; расширенный 3-ий канал и CSM)";
    strings["NEC PC-98 (with Sound Blaster 16 for PC-9800 w/PC-9801-26/K compatible)##sgpr"].plurals[0] = "NEC PC-98 (с Sound Blaster 16 для PC-9800, совместимый с PC-9801-26/K)";
    strings["NEC PC-98 (with Sound Blaster 16 for PC-9800 w/PC-9801-26/K compatible; extended channel 3)##sgpr"].plurals[0] = "NEC PC-98 (с Sound Blaster 16 для PC-9800, совместимый с PC-9801-26/K; расширенный 3-ий канал)";
    strings["NEC PC-98 (with Sound Blaster 16 for PC-9800 w/PC-9801-26/K compatible; extended channel 3 and CSM)##sgpr"].plurals[0] = "NEC PC-98 (с Sound Blaster 16 для PC-9800, совместимый с PC-9801-26/K; расширенный 3-ий канал и CSM)";
    strings["NEC PC-98 (with Sound Blaster 16 for PC-9800 w/PC-9801-26/K compatible in drums mode)##sgpr"].plurals[0] = "NEC PC-98 (с Sound Blaster 16 для PC-9800, совместимый с PC-9801-26/K в режиме ударных)";
    strings["NEC PC-98 (with Sound Blaster 16 for PC-9800 w/PC-9801-26/K compatible in drums mode; extended channel 3)##sgpr"].plurals[0] = "NEC PC-98 (с Sound Blaster 16 для PC-9800, совместимый с PC-9801-26/K в режиме ударных; расширенный 3-ий канал)";
    strings["NEC PC-98 (with Sound Blaster 16 for PC-9800 w/PC-9801-26/K compatible in drums mode; extended channel 3 and CSM)##sgpr"].plurals[0] = "NEC PC-98 (с Sound Blaster 16 для PC-9800, совместимый с PC-9801-26/K в режиме ударных; расширенный 3-ий канал и CSM)";
    strings["ZX Spectrum (48K, SFX-like engine)##sgpr"].plurals[0] = "ZX Spectrum (48K, драйвер типа SFX)";
    strings["ZX Spectrum (48K, QuadTone engine)##sgpr"].plurals[0] = "ZX Spectrum (48K, драйвер QuadTone)";
    strings["ZX Spectrum (128K) with TurboSound##sgpr"].plurals[0] = "ZX Spectrum (128K) с TurboSound";
    strings["ZX Spectrum (128K) with TurboSound FM##sgpr"].plurals[0] = "ZX Spectrum (128K) с TurboSound FM";
    strings["ZX Spectrum (128K) with TurboSound FM (extended channel 3 on first OPN)##sgpr"].plurals[0] = "ZX Spectrum (128K) с TurboSound FM (расширенный 3-ий канал на первом чипе OPN)";
    strings["ZX Spectrum (128K) with TurboSound FM (extended channel 3 and CSM on first OPN)##sgpr"].plurals[0] = "ZX Spectrum (128K) с TurboSound FM (расширенный 3-ий канал и CSM на первом чипе OPN)";
    strings["ZX Spectrum (128K) with TurboSound FM (extended channel 3 on second OPN)##sgpr"].plurals[0] = "ZX Spectrum (128K) с TurboSound FM (расширенный 3-ий канал на втором чипе OPN)";
    strings["ZX Spectrum (128K) with TurboSound FM (extended channel 3 and CSM on second OPN)##sgpr"].plurals[0] = "ZX Spectrum (128K) с TurboSound FM (расширенный 3-ий канал и CSM на втором чипе OPN)";
    strings["ZX Spectrum (128K) with TurboSound FM (extended channel 3 on both OPNs)##sgpr"].plurals[0] = "ZX Spectrum (128K) с TurboSound FM (расширенный 3-ий канал на обоих чипах OPN)";
    strings["ZX Spectrum (128K) with TurboSound FM (extended channel 3 and CSM on both OPNs)##sgpr"].plurals[0] = "ZX Spectrum (128K) с TurboSound FM (расширенный 3-ий канал и CSM на обоих чипах OPN)";
    strings["Atari 800 (stereo)##sgpr"].plurals[0] = "Atari 800 (стерео)";
    strings["PC (beeper)##sgpr"].plurals[0] = "PC (пищалка)";
    strings["PC + AdLib (drums mode)##sgpr"].plurals[0] = "PC + AdLib (в режиме ударных)";
    strings["PC + Sound Blaster (drums mode)##sgpr"].plurals[0] = "PC + Sound Blaster (в режиме ударных)";
    strings["PC + Sound Blaster w/Game Blaster Compatible (drums mode)##sgpr"].plurals[0] = "PC + Sound Blaster w/Game Blaster Compatible (в режиме ударных)";
    strings["PC + Sound Blaster Pro (drums mode)##sgpr"].plurals[0] = "PC + Sound Blaster Pro (в режиме ударных)";
    strings["PC + Sound Blaster Pro 2 (drums mode)##sgpr"].plurals[0] = "PC + Sound Blaster Pro 2 (в режиме ударных)";
    strings["PC + ESS AudioDrive ES1488 (native ESFM mode)##sgpr"].plurals[0] = "PC + ESS AudioDrive ES1488 (нативный режим ESFM)";
    strings["Sharp X1 + FM addon##sgpr"].plurals[0] = "Sharp X1 + FM-дополнение";
    strings["FM Towns (extended channel 3)##sgpr"].plurals[0] = "FM Towns (расширенный 3-ий канал)";
    strings["Commander X16 (VERA only)##sgpr"].plurals[0] = "Commander X16 (только VERA)";
    strings["Commander X16 (with OPM)##sgpr"].plurals[0] = "Commander X16 (с OPM)";
    strings["Commander X16 (with Twin OPL3)##sgpr"].plurals[0] = "Commander X16 (с Twin OPL3)";
    strings["Arcade systems##sgpr"].plurals[0] = "Аркадные автоматы";
    strings["INSERT COIN##sgpr"].plurals[0] = "ВСТАВЬТЕ ЖЕТОН##sgpr";
    strings["Williams/Midway Y/T unit w/ADPCM sound board##sgpr"].plurals[0] = "Автомат Williams/Midway Y/T со звуковой картой ADPCM";
    strings["Konami Battlantis (drums mode on first OPL2)##sgpr"].plurals[0] = "Konami Battlantis (первый OPL2 в режиме ударных)";
    strings["Konami Battlantis (drums mode on second OPL2)##sgpr"].plurals[0] = "Konami Battlantis (второй OPL2 в режиме ударных)";
    strings["Konami Battlantis (drums mode on both OPL2s)##sgpr"].plurals[0] = "Konami Battlantis (оба OPL2 в режиме ударных)";
    strings["Konami Haunted Castle (drums mode)##sgpr"].plurals[0] = "Konami Haunted Castle (в режиме ударных)";
    strings["Konami S.P.Y. (drums mode)##sgpr"].plurals[0] = "Konami S.P.Y. (в режиме ударных)";
    strings["Konami Rollergames (drums mode)##sgpr"].plurals[0] = "Konami Rollergames (в режиме ударных)";
    strings["Sega System E (with FM expansion)##sgpr"].plurals[0] = "Sega System E (с FM-расширением)";
    strings["Sega System E (with FM expansion in drums mode)##sgpr"].plurals[0] = "Sega System E (с FM-расширением в режиме ударных)";
    strings["Sega Hang-On (extended channel 3)##sgpr"].plurals[0] = "Sega Hang-On (расширенный 3-ий канал)";
    strings["Sega Hang-On (extended channel 3 and CSM)##sgpr"].plurals[0] = "Sega Hang-On (расширенный 3-ий канал и CSM)";
    strings["Sega System 18 (extended channel 3 on first OPN2C)##sgpr"].plurals[0] = "Sega System 18 (расширенный 3-ий канал на первом OPN2C)";
    strings["Sega System 18 (extended channel 3 and CSM on first OPN2C)##sgpr"].plurals[0] = "Sega System 18 (расширенный 3-ий канал и CSM на первом OPN2C)";
    strings["Sega System 18 (extended channel 3 on second OPN2C)##sgpr"].plurals[0] = "Sega System 18 (расширенный 3-ий канал на втором OPN2C)";
    strings["Sega System 18 (extended channel 3 and CSM on second OPN2C)##sgpr"].plurals[0] = "Sega System 18 (расширенный 3-ий канал и CSM на втором OPN2C)";
    strings["Sega System 18 (extended channel 3 on both OPN2Cs)##sgpr"].plurals[0] = "Sega System 18 (расширенный 3-ий канал на обоих чипах OPN2C)";
    strings["Sega System 18 (extended channel 3 and CSM on both OPN2Cs)##sgpr"].plurals[0] = "Sega System 18 (расширенный 3-ий канал и CSM на обоих чипах OPN2C)";
    strings["Sega System 32 (extended channel 3 on first OPN2C)##sgpr"].plurals[0] = "Sega System 32 (расширенный 3-ий канал на первом OPN2C)";
    strings["Sega System 32 (extended channel 3 and CSM on first OPN2C)##sgpr"].plurals[0] = "Sega System 32 (расширенный 3-ий канал и CSM на первом OPN2C)";
    strings["Sega System 32 (extended channel 3 on second OPN2C)##sgpr"].plurals[0] = "Sega System 32 (расширенный 3-ий канал на втором OPN2C)";
    strings["Sega System 32 (extended channel 3 and CSM on second OPN2C)##sgpr"].plurals[0] = "Sega System 32 (расширенный 3-ий канал и CSM на втором OPN2C)";
    strings["Sega System 32 (extended channel 3 on both OPN2Cs)##sgpr"].plurals[0] = "Sega System 32 (расширенный 3-ий канал на обоих чипах OPN2C)";
    strings["Sega System 32 (extended channel 3 and CSM on both OPN2Cs)##sgpr"].plurals[0] = "Sega System 32 (расширенный 3-ий канал и CSM на обоих чипах OPN2C)";
    strings["Capcom Arcade##sgpr"].plurals[0] = "Capcom Arcade";
    strings["Capcom Arcade (extended channel 3 on first OPN)##sgpr"].plurals[0] = "Capcom Arcade (расширенный 3-ий канал на первом OPN)";
    strings["Capcom Arcade (extended channel 3 and CSM on first OPN)##sgpr"].plurals[0] = "Capcom Arcade (расширенный 3-ий канал на втором OPN)";
    strings["Capcom Arcade (extended channel 3 on second OPN)##sgpr"].plurals[0] = "Capcom Arcade (расширенный 3-ий канал и CSM на втором OPN)";
    strings["Capcom Arcade (extended channel 3 and CSM on second OPN)##sgpr"].plurals[0] = "Capcom Arcade (расширенный 3-ий канал и CSM на втором OPN)";
    strings["Capcom Arcade (extended channel 3 on both OPNs)##sgpr"].plurals[0] = "Capcom Arcade (расширенный 3-ий канал на обоих чипах OPN)";
    strings["Capcom Arcade (extended channel 3 and CSM on both OPNs)##sgpr"].plurals[0] = "Capcom Arcade (расширенный 3-ий канал и CSM на обоих чипах OPN)";
    strings["Jaleco Ginga NinkyouDen (drums mode)##sgpr"].plurals[0] = "Jaleco Ginga NinkyouDen (в режиме ударных)";
    strings["NMK 16-bit Arcade##sgpr"].plurals[0] = "NMK 16-bit Arcade";
    strings["NMK 16-bit Arcade (extended channel 3)##sgpr"].plurals[0] = "NMK 16-bit Arcade (расширенный 3-ий канал)";
    strings["NMK 16-bit Arcade (extended channel 3 and CSM)##sgpr"].plurals[0] = "NMK 16-bit Arcade (расширенный 3-ий канал и CSM)";
    strings["Kaneko DJ Boy (extended channel 3)##sgpr"].plurals[0] = "Kaneko DJ Boy (расширенный 3-ий канал)";
    strings["Kaneko DJ Boy (extended channel 3 and CSM)##sgpr"].plurals[0] = "Kaneko DJ Boy (расширенный 3-ий канал и CSM)";
    strings["Kaneko Air Buster (extended channel 3)##sgpr"].plurals[0] = "Kaneko Air Buster (расширенный 3-ий канал)";
    strings["Kaneko Air Buster (extended channel 3 and CSM)##sgpr"].plurals[0] = "Kaneko Air Buster (расширенный 3-ий канал и CSM)";
    strings["Tecmo Ninja Gaiden (extended channel 3 on first OPN)##sgpr"].plurals[0] = "Tecmo Ninja Gaiden (расширенный 3-ий канал на первом OPN)";
    strings["Tecmo Ninja Gaiden (extended channel 3 and CSM on first OPN)##sgpr"].plurals[0] = "Tecmo Ninja Gaiden (расширенный 3-ий канал и CSM на первом OPN)";
    strings["Tecmo Ninja Gaiden (extended channel 3 on second OPN)##sgpr"].plurals[0] = "Tecmo Ninja Gaiden (расширенный 3-ий канал на втором OPN)";
    strings["Tecmo Ninja Gaiden (extended channel 3 and CSM on second OPN)##sgpr"].plurals[0] = "Tecmo Ninja Gaiden (расширенный 3-ий канал и CSM на втором OPN)";
    strings["Tecmo Ninja Gaiden (extended channel 3 on both OPNs)##sgpr"].plurals[0] = "Tecmo Ninja Gaiden (расширенный 3-ий канал на обоих чипах OPN)";
    strings["Tecmo Ninja Gaiden (extended channel 3 and CSM on both OPNs)##sgpr"].plurals[0] = "Tecmo Ninja Gaiden (расширенный 3-ий канал и CSM на обоих чипах OPN)";
    strings["Tecmo System (drums mode)##sgpr"].plurals[0] = "Tecmo System (в режиме ударных)";
    strings["Seibu Kaihatsu Raiden (drums mode)##sgpr"].plurals[0] = "Seibu Kaihatsu Raiden (в режиме ударных)";
    strings["Sunsoft Arcade##sgpr"].plurals[0] = "Sunsoft Arcade";
    strings["Sunsoft Arcade (extended channel 3)##sgpr"].plurals[0] = "Sunsoft Arcade (расширенный 3-ий канал)";
    strings["Sunsoft Arcade (extended channel 3 and CSM)##sgpr"].plurals[0] = "Sunsoft Arcade (расширенный 3-ий канал и CSM)";
    strings["Atari Rampart (drums mode)##sgpr"].plurals[0] = "Atari Rampart (в режиме ударных)";
    strings["Data East Karnov (extended channel 3)##sgpr"].plurals[0] = "Data East Karnov (расширенный 3-ий канал 3)";
    strings["Data East Karnov (extended channel 3 and CSM)##sgpr"].plurals[0] = "Data East Karnov (расширенный 3-ий канал и CSM)";
    strings["Data East Karnov (drums mode)##sgpr"].plurals[0] = "Data East Karnov (в режиме ударных)";
    strings["Data East Karnov (extended channel 3; drums mode)##sgpr"].plurals[0] = "Data East Karnov (расширенный 3-ий канал; в режиме ударных)";
    strings["Data East Karnov (extended channel 3 and CSM; drums mode)##sgpr"].plurals[0] = "Data East Karnov (расширенный 3-ий канал и CSM; в режиме ударных)";
    strings["Data East Arcade##sgpr"].plurals[0] = "Data East Arcade";
    strings["Data East Arcade (extended channel 3)##sgpr"].plurals[0] = "Data East Arcade (расширенный 3-ий канал)";
    strings["Data East Arcade (extended channel 3 and CSM)##sgpr"].plurals[0] = "Data East Arcade (расширенный 3-ий канал и CSM)";
    strings["Data East Arcade (drums mode)##sgpr"].plurals[0] = "Data East Arcade (в режиме ударных)";
    strings["Data East Arcade (extended channel 3; drums mode)##sgpr"].plurals[0] = "Data East Arcade (расширенный 3-ий канал; в режиме ударных)";
    strings["Data East Arcade (extended channel 3 and CSM; drums mode)##sgpr"].plurals[0] = "Data East Arcade (расширенный 3-ий канал и CSM; в режиме ударных)";
    strings["Data East PCX (extended channel 3)##sgpr"].plurals[0] = "Data East PCX (расширенный 3-ий канал)";
    strings["Data East PCX (extended channel 3 and CSM)##sgpr"].plurals[0] = "Data East PCX (расширенный 3-ий канал и CSM)";
    strings["Data East Dark Seal (extended channel 3)##sgpr"].plurals[0] = "Data East Dark Seal (расширенный 3-ий канал)";
    strings["SNK Ikari Warriors (drums mode on first OPL)##sgpr"].plurals[0] = "SNK Ikari Warriors (первый OPL в режиме ударных)";
    strings["SNK Ikari Warriors (drums mode on second OPL)##sgpr"].plurals[0] = "SNK Ikari Warriors (второй OPL в режиме ударных)";
    strings["SNK Ikari Warriors (drums mode on both OPLs)##sgpr"].plurals[0] = "SNK Ikari Warriors (оба чипа OPL в режиме ударных)";
    strings["SNK Triple Z80 (drums mode on Y8950)##sgpr"].plurals[0] = "SNK Triple Z80 (Y8950 в режиме ударных)";
    strings["SNK Triple Z80 (drums mode on OPL)##sgpr"].plurals[0] = "SNK Triple Z80 (OPL в режиме ударных)";
    strings["SNK Triple Z80 (drums mode on Y8950 and OPL)##sgpr"].plurals[0] = "SNK Triple Z80 (Y8950 и OPL в режиме ударных)";
    strings["SNK Chopper I (drums mode on Y8950)##sgpr"].plurals[0] = "SNK Chopper I (Y8950 в режиме ударных)";
    strings["SNK Chopper I (drums mode on OPL2)##sgpr"].plurals[0] = "SNK Chopper I (OPL2 в режиме ударных)";
    strings["SNK Chopper I (drums mode on Y8950 and OPL2)##sgpr"].plurals[0] = "SNK Chopper I (Y8950 и OPL2 в режиме ударных)";
    strings["SNK Touchdown Fever (drums mode on OPL)##sgpr"].plurals[0] = "SNK Touchdown Fever (OPL в режиме ударных)";
    strings["SNK Touchdown Fever (drums mode on Y8950)##sgpr"].plurals[0] = "SNK Touchdown Fever (Y8950 в режиме ударных)";
    strings["SNK Touchdown Fever (drums mode on OPL and Y8950)##sgpr"].plurals[0] = "SNK Touchdown Fever (Y8950 и OPL2 в режиме ударных)";
    strings["Alpha denshi Alpha-68K (extended channel 3)##sgpr"].plurals[0] = "Alpha denshi Alpha-68K (расширенный 3-ий канал)";
    strings["Alpha denshi Alpha-68K (extended channel 3 and CSM)##sgpr"].plurals[0] = "Alpha denshi Alpha-68K (расширенный 3-ий канал и CSM)";
    strings["Alpha denshi Alpha-68K (drums mode)##sgpr"].plurals[0] = "Alpha denshi Alpha-68K (в режиме ударных)";
    strings["Alpha denshi Alpha-68K (extended channel 3; drums mode)##sgpr"].plurals[0] = "Alpha denshi Alpha-68K (расширенный 3-ий канал; в режиме ударных)";
    strings["Alpha denshi Alpha-68K (extended channel 3 and CSM; drums mode)##sgpr"].plurals[0] = "Alpha denshi Alpha-68K (расширенный 3-ий канал и CSM; в режиме ударных)";
    strings["Neo Geo MVS (extended channel 2)##sgpr"].plurals[0] = "Neo Geo MVS (расширенный 2-ой канал)";
    strings["Neo Geo MVS (extended channel 2 and CSM)##sgpr"].plurals[0] = "Neo Geo MVS (расширенный 2-ой канал и CSM)";
    strings["Namco (3-channel WSG)##sgpr"].plurals[0] = "Namco (3-канальный генератор звука на волновых таблицах)";
    strings["Taito Arcade##sgpr"].plurals[0] = "Taito Arcade";
    strings["Taito Arcade (extended channel 3)##sgpr"].plurals[0] = "Taito Arcade (расширенный 3-ий канал)";
    strings["Taito Arcade (extended channel 3 and CSM)##sgpr"].plurals[0] = "Taito Arcade (расширенный 3-ий канал и CSM)";
    strings["Seta 1 + FM addon##sgpr"].plurals[0] = "Seta 1 + FM-дополнение";
    strings["Seta 1 + FM addon (extended channel 3)##sgpr"].plurals[0] = "Seta 1 + FM-дополнение (расширенный 3-ий канал)";
    strings["Seta 1 + FM addon (extended channel 3 and CSM)##sgpr"].plurals[0] = "Seta 1 + FM-дополнение (расширенный 3-ий канал и CSM)";
    strings["Coreland Cyber Tank (drums mode)##sgpr"].plurals[0] = "Coreland Cyber Tank (в режиме ударных)";
    strings["Toaplan 1 (drums mode)##sgpr"].plurals[0] = "Toaplan 1 (в режиме ударных)";
    strings["Dynax/Nakanihon 3rd generation hardware##sgpr"].plurals[0] = "Аппаратная платформа 3-го поколения Dynax/Nakanihon";
    strings["Dynax/Nakanihon 3rd generation hardware (drums mode)##sgpr"].plurals[0] = "Аппаратная платформа 3-го поколения Dynax/Nakanihon (в режиме ударных)";
    strings["Dynax/Nakanihon Real Break (drums mode)##sgpr"].plurals[0] = "Dynax/Nakanihon Real Break (в режиме ударных)";
    strings["chips which use frequency modulation (FM) to generate sound.\nsome of these also pack more (like square and sample channels).\nActually \"FM\" here stands for phase modulation,\nbut these two are indistinguishable\nif you use sine waves.##sgpr"].plurals[0] = "чипы, использующую частотную модуляцию (FM-синтез) для генерации звука.\nв некоторых из них присутствуют и другие способы синтеза звука (каналы с квадратными волнами или сэмплами).\nНа самом деле, \"FM\" здесь означает фазовую модуляцию,\nно они неотличимы друг от друга при использовании синусоидальных волн.";
    strings["Yamaha YM2203 (extended channel 3)##sgpr"].plurals[0] = "Yamaha YM2203 (расширенный 3-ий канал)";
    strings["Yamaha YM2203 (extended channel 3 and CSM)##sgpr"].plurals[0] = "Yamaha YM2203 (расширенный 3-ий канал и CSM)";
    strings["Yamaha YM2608 (extended channel 3)##sgpr"].plurals[0] = "Yamaha YM2608 (расширенный 3-ий канал)";
    strings["Yamaha YM2608 (extended channel 3 and CSM)##sgpr"].plurals[0] = "Yamaha YM2608 (расширенный 3-ий канал и CSM)";
    strings["Yamaha YM2610 (extended channel 2)##sgpr"].plurals[0] = "Yamaha YM2610 (расширенный 2-ой канал)";
    strings["Yamaha YM2610 (extended channel 2 and CSM)##sgpr"].plurals[0] = "Yamaha YM2610 (расширенный 2-ой канал и CSM)";
    strings["Yamaha YM2610B (extended channel 3)##sgpr"].plurals[0] = "Yamaha YM2610B (расширенный 3-ий канал)";
    strings["Yamaha YM2610B (extended channel 3 and CSM)##sgpr"].plurals[0] = "Yamaha YM2610B (расширенный 3-ий канал и CSM)";
    strings["Yamaha YM2612 (extended channel 3)##sgpr"].plurals[0] = "Yamaha YM2612 (расширенный 3-ий канал)";
    strings["Yamaha YM2612 (OPN2) with DualPCM##sgpr"].plurals[0] = "Yamaha YM2612 (OPN2) с DualPCM";
    strings["Yamaha YM2612 (extended channel 3) with DualPCM and CSM##sgpr"].plurals[0] = "Yamaha YM2612 (расширенный 3-ий канал) с DualPCM и CSM";
    strings["Yamaha YM2413 (drums mode)##sgpr"].plurals[0] = "Yamaha YM2413 (в режиме ударных)";
    strings["Yamaha YM3438 (extended channel 3)##sgpr"].plurals[0] = "Yamaha YM3438 (расширенный 3-ий канал)";
    strings["Yamaha YM3438 (OPN2C) with DualPCM##sgpr"].plurals[0] = "Yamaha YM3438 (OPN2C) с DualPCM";
    strings["Yamaha YM3438 (extended channel 3) with DualPCM and CSM##sgpr"].plurals[0] = "Yamaha YM3438 (расширенный 3-ий канал) с DualPCM и CSM";
    strings["Yamaha YM3526 (drums mode)##sgpr"].plurals[0] = "Yamaha YM3526 (в режиме ударных)";
    strings["Yamaha Y8950 (drums mode)##sgpr"].plurals[0] = "Yamaha Y8950 (в режиме ударных)";
    strings["Yamaha YM3812 (drums mode)##sgpr"].plurals[0] = "Yamaha YM3812 (в режиме ударных)";
    strings["Yamaha YMF262 (drums mode)##sgpr"].plurals[0] = "Yamaha YMF262 (в режиме ударных)";
    strings["Yamaha YMF289B (drums mode)##sgpr"].plurals[0] = "Yamaha YMF289B (в режиме ударных)";
    strings["Square##sgpr"].plurals[0] = "Меандр";
    strings["these chips generate square/pulse tones only (but may include noise).##sgpr"].plurals[0] = "эти чипы способны генерировать лишь квадратные/прямоугольные волны (но могут также генерировать шум).";
    strings["Tandy PSSJ 3-voice sound##sgpr"].plurals[0] = "Tandy PSSJ трёхканальный генератор звука";
    strings["Sega PSG (SN76489-like)##sgpr"].plurals[0] = "Sega PSG (похож на SN76489)";
    strings["Sega PSG (SN76489-like, Stereo)##sgpr"].plurals[0] = "Sega PSG (похож на SN76489, стерео)";
    strings["PC Speaker##sgpr"].plurals[0] = "PC Speaker (пищалка)";
    strings["Sample##sgpr"].plurals[0] = "Сэмплеры";
    strings["chips/systems which use PCM or ADPCM samples for sound synthesis.##sgpr"].plurals[0] = "чипы/системы, которые используют ИКМ- или АДИКМ-сэмплы для воспроизведения звука.";
    strings["Generic PCM DAC##sgpr"].plurals[0] = "Типичный ИКМ ЦАП";
    strings["Wavetable##sgpr"].plurals[0] = "Волн. табл.";
    strings["chips which use user-specified waveforms to generate sound.##sgpr"].plurals[0] = "чипы, которые использует задаваемые пользователем волны для синтеза звука.";
    strings["Namco C15 (8-channel mono)##sgpr"].plurals[0] = "Namco C15 (8-канальный, моно)";
    strings["Namco C30 (8-channel stereo)##sgpr"].plurals[0] = "Namco C30 (8-канальный, стерео)";
    strings["Famicom Disk System (chip)##sgpr"].plurals[0] = "Famicom Disk System (чип)";
    strings["Specialized##sgpr"].plurals[0] = "Особые";
    strings["chips/systems with unique sound synthesis methods.##sgpr"].plurals[0] = "чипы/системы с уникальными методами синтеза звука.";
    strings["Commodore PET (pseudo-wavetable)##sgpr"].plurals[0] = "Commodore PET (псевдо-волновая таблица)";
    strings["ZX Spectrum (beeper only, SFX-like engine)##sgpr"].plurals[0] = "ZX Spectrum (только пищалка, драйвер типа SFX)";
    strings["ZX Spectrum (beeper only, QuadTone engine)##sgpr"].plurals[0] = "ZX Spectrum (только пищалка, драйвер QuadTone)";
    strings["Modern/fantasy##sgpr"].plurals[0] = "Совр./вымышл.";
    strings["chips/systems which do not exist in reality or were made just several years ago.##sgpr"].plurals[0] = "чипы/системы, не имеющие физического воплощения или сделанные всего несколько лет назад.";
    strings["Commander X16 (VERA only)##sgpr1"].plurals[0] = "Commander X16 (только VERA)";
    strings["DefleMask-compatible##sgpr"].plurals[0] = "Совместимые с DefleMask";
    strings["these configurations are compatible with DefleMask.\nselect this if you need to save as .dmf or work with that program.##sgpr"].plurals[0] = "эти пресеты совместимы с DefleMask.\nвыбирайте их, если вам будет нужно будет экспортировать модуль в .dmf или работать с этой программой.";
    strings["Sega Genesis (extended channel 3)##sgpr1"].plurals[0] = "Sega Genesis (расширенный 3-ий канал)";
    strings["Sega Master System (with FM expansion)##sgpr1"].plurals[0] = "Sega Master System (с FM-расширением)";
    strings["Arcade (YM2151 and SegaPCM)##sgpr1"].plurals[0] = "Arcade (YM2151 и SegaPCM)";
    strings["Neo Geo CD (extended channel 2)##sgpr1"].plurals[0] = "Neo Geo CD (расширенный 2-ой канал)";

    //   sgrv  src/gui/regView.cpp

    strings["Register View###Register View"].plurals[0] = "Просмотр регистров###Register View";
    strings["- no register pool available##sgrv"].plurals[0] = "- список регистров недоступен";

    //   sgse  src/gui/sampleEdit.cpp

    strings["%s: maximum sample rate is %d##sgse"].plurals[0] = "%s: максимальная частота квантования равна %d";
    strings["%s: minimum sample rate is %d##sgse"].plurals[0] = "%s: минимальная частота квантования равна %d";
    strings["%s: sample rate must be %d##sgse"].plurals[0] = "%s: частота квантования должна быть равна %d";
    strings["Sample Editor###Sample Editor"].plurals[0] = "Редактор сэмплов###Sample Editor";
    strings["no sample selected##sgse"].plurals[0] = "сэмпл не выбран";
    strings["select one...##sgse"].plurals[0] = "выберите сэмпл...";
    strings["or##sgse0"].plurals[0] = "или";
    strings["Open##sgse0"].plurals[0] = "Откройте";
    strings["or##sgse1"].plurals[0] = "или";
    strings["Create New##sgse"].plurals[0] = "Создайте новый";
    strings["Invalid##sgse0"].plurals[0] = "Недейств.";
    strings["Invalid##sgse1"].plurals[0] = "Недейств.";
    strings["Open##sgse1"].plurals[0] = "Открыть";
    strings["import raw...##sgse"].plurals[0] = "импорт сырых данных...";
    strings["Save##sgse"].plurals[0] = "Сохранить";
    strings["save raw...##sgse"].plurals[0] = "сохранить сырые данные...";
    strings["Name##sgse"].plurals[0] = "Название";
    strings["SNES: loop start must be a multiple of 16 (try with %d)##sgse"].plurals[0] = "SNES: начало цикла должно быть кратно 16 (попробуйте %d)";
    strings["SNES: loop end must be a multiple of 16 (try with %d)##sgse"].plurals[0] = "SNES: конец цикла должен быть кратен 16 (попробуйте %d)";
    strings["SNES: sample length will be padded to multiple of 16##sgse"].plurals[0] = "SNES: длина сэмпла будет скорректирована до кратности 16";
    strings["QSound: loop cannot be longer than 32767 samples##sgse"].plurals[0] = "QSound: цикл не может быть длиннее 32767 сэмплов";
    strings["QSound: maximum sample length is 65535##sgse"].plurals[0] = "QSound: максимальная длина сэмпла: 65535";
    strings["NES: loop point ignored on DPCM (may only loop entire sample)##sgse"].plurals[0] = "NES: точка зацикливания игнорируется для DPCM (зациклить можно только сэмпл целиком)";
    strings["NES: maximum DPCM sample length is 32648##sgse"].plurals[0] = "NES: максимальная длина DPCM-сэмпла равна 32648";
    strings["X1-010: samples can't loop##sgse"].plurals[0] = "X1-010: сэмплы не могут быть зациклены";
    strings["X1-010: maximum sample length is 131072##sgse"].plurals[0] = "X1-010: максимальная длина сэмпла равна 131072";
    strings["GA20: samples can't loop##sgse"].plurals[0] = "GA20: сэмплы не могут быть зациклены";
    strings["YM2608: loop point ignored on ADPCM (may only loop entire sample)##sgse"].plurals[0] = "YM2608: точка зацикливания игнорируется для ADPCM (зациклить можно только сэмпл целиком)";
    strings["YM2608: sample length will be padded to multiple of 512##sgse"].plurals[0] = "YM2608: длина сэмпла будет скорректирована до кратности 512";
    strings["YM2610: ADPCM-A samples can't loop##sgse"].plurals[0] = "YM2610: ADPCM-A сэмплы не могут быть зациклены";
    strings["YM2610: loop point ignored on ADPCM-B (may only loop entire sample)##sgse"].plurals[0] = "YM2610: точка зацикливания игнорируется для ADPCM-B (зациклить можно только сэмпл целиком)";
    strings["YM2610: sample length will be padded to multiple of 512##sgse"].plurals[0] = "YM2610: длина сэмпла будет скорректирована до кратности 512";
    strings["YM2610: maximum ADPCM-A sample length is 2097152##sgse"].plurals[0] = "YM2610: максимальная длина ADPCM-A сэмпла равна 2097152";
    strings["Y8950: loop point ignored on ADPCM (may only loop entire sample)##sgse"].plurals[0] = "Y8950: точка зацикливания игнорируется для ADPCM (зациклить можно только сэмпл целиком)";
    strings["Y8950: sample length will be padded to multiple of 512##sgse"].plurals[0] = "Y8950: длина сэмпла будет скорректирована до кратности 512";
    strings["Amiga: loop start must be a multiple of 2##sgse"].plurals[0] = "Amiga: начало зацикливания должно быть кратно 2";
    strings["Amiga: loop end must be a multiple of 2##sgse"].plurals[0] = "Amiga: конец зацикливания должен быть кратен 2";
    strings["Amiga: maximum sample length is 131070##sgse"].plurals[0] = "Amiga: максимальная длина сэмпла равна 131070";
    strings["SegaPCM: maximum sample length is 65280##sgse"].plurals[0] = "SegaPCM: максимальная длина сэмпла равна 65280";
    strings["K053260: loop point ignored (may only loop entire sample)##sgse"].plurals[0] = "K053260: точка зацикливания игнорируется (зациклить можно только сэмпл целиком)";
    strings["K053260: maximum sample length is 65535##sgse"].plurals[0] = "K053260: максимальная длина сэмпла равна 65535";
    strings["C140: maximum sample length is 65535##sgse"].plurals[0] = "C140: максимальная длина сэмпла равна 65535";
    strings["C219: loop start must be a multiple of 2##sgse"].plurals[0] = "C219: начало зацикливания должно быть кратно 2";
    strings["C219: loop end must be a multiple of 2##sgse"].plurals[0] = "C219: конец зацикливания должен быть кратен 2";
    strings["C219: maximum sample length is 131072##sgse"].plurals[0] = "C219: максимальная длина сэмпла равна 131072";
    strings["MSM6295: samples can't loop##sgse"].plurals[0] = "MSM6295: сэмплы не могут быть зациклены";
    strings["ES5506: backward loop mode isn't supported##sgse"].plurals[0] = "ES5506: режим обратного зацикливания не поддерживается";
    strings["backward/ping-pong only supported in Generic PCM DAC\nping-pong also on ES5506##sgse"].plurals[0] = "режим обратного и \"туда-обратно\" зацикливания поддерживается только для универсального ИКМ ЦАП\n\"туда-обратно\" также поддерживается для ES5506";
    strings["Info##sgse"].plurals[0] = "Информация";
    strings["Rate##sgse0"].plurals[0] = "Частота";
    strings["Compat Rate##sgse"].plurals[0] = "Совместимая частота";
    strings["used in DefleMask-compatible sample mode (17xx), in where samples are mapped to an octave.##sgse"].plurals[0] = "используется при воспроизведении в режиме совместимости с DefleMask (17xx), в котором сэмплы соответствуют октаве.";
    strings["Loop##sgse"].plurals[0] = "Цикл";
    strings["Loop (length: %d)##Loop"].plurals[0] = "Цикл (длина: %d)##Loop";
    strings["changing the loop in a BRR sample may result in glitches!##sgse0"].plurals[0] = "Смена зацикленной части в сэмпле BRR может привести к сбоям!";
    strings["Chips##sgse"].plurals[0] = "Чипы";
    strings["Type##sgse"].plurals[0] = "Тип";
    strings["BRR emphasis##sgse"].plurals[0] = "Постобработка для BRR";
    strings["this is a BRR sample.\nenabling this option will muffle it (only affects non-SNES chips).##sgse"].plurals[0] = "это сэмпл BRR.\nвключение этой опции \"замылит\" его (на всех чипах кроме SNES).";
    strings["enable this option to slightly boost high frequencies\nto compensate for the SNES' Gaussian filter's muffle.##sgse"].plurals[0] = "включите эту опцию для небольшого усиления высоких частот\nдля компенсации фильтрующего свойства гауссовой интерполяции, из-за которого сэмпл \"замыливается\".";
    strings["8-bit dither##sgse"].plurals[0] = "8-битный дизеринг";
    strings["dither the sample when used on a chip that only supports 8-bit samples.##sgse"].plurals[0] = "произвести дизеринг для сэмпла при его использовании для чипа, поддерживающего только 8-битные сэмплы.";
    strings["Note##sgse"].plurals[0] = "Нота";
    strings["Fine##sgse"].plurals[0] = "Расстройка";
    strings["Mode##sgse"].plurals[0] = "Режим";
    strings["Start##sgse"].plurals[0] = "Начало";
    strings["changing the loop in a BRR sample may result in glitches!##sgse1"].plurals[0] = "смена зацикленной части в сэмпле BRR может привести к сбоям!";
    strings["End##sgse"].plurals[0] = "Конец";
    strings["changing the loop in a BRR sample may result in glitches!##sgse2"].plurals[0] = "смена зацикленной части в сэмпле BRR может привести к сбоям!";
    strings["%s\n%d bytes free##sgse"].plurals[0] = "%s\nсвободен %d байт";
    strings["%s\n%d bytes free##sgse"].plurals[1] = "%s\nсвободно %d байта";
    strings["%s\n%d bytes free##sgse"].plurals[2] = "%s\nсвободно %d байт";
    strings["%s (%s)\n%d bytes free##sgse"].plurals[0] = "%s (%s)\nсвободен %d байт";
    strings["%s (%s)\n%d bytes free##sgse"].plurals[1] = "%s (%s)\nсвободно %d байта";
    strings["%s (%s)\n%d bytes free##sgse"].plurals[2] = "%s (%s)\nсвободно %d байт";
    strings["\n\nnot enough memory for this sample!##sgse"].plurals[0] = "\n\nнедостаточно памяти для этого сэмпла!";
    strings["Edit mode: Select##sgse"].plurals[0] = "Режим редактирования: выделение";
    strings["Edit mode: Draw##sgse"].plurals[0] = "Режим редактирования: рисование";
    strings["Resize##sgse0"].plurals[0] = "Масштабировать";
    strings["Samples##sgse0"].plurals[0] = "Сэмплов (новый размер)";
    strings["Resize##sgse1"].plurals[0] = "Масштабировать";
    strings["couldn't resize! make sure your sample is 8 or 16-bit.##sgse"].plurals[0] = "не получилось отмасштабировать! убедитесь, что это 8- или 16-битный сэмпл.";
    strings["Resample##sgse0"].plurals[0] = "Изменить частоту дискретизации";
    strings["Rate##sgse1"].plurals[0] = "Частота";
    strings["Factor##sgse"].plurals[0] = "Коэффициент";
    strings["Filter##sgse"].plurals[0] = "Фильтр";
    strings["Resample##sgse1"].plurals[0] = "Применить";
    strings["couldn't resample! make sure your sample is 8 or 16-bit.##sgse"].plurals[0] = "не получилось изменить частоту дискретизации! убедитесь, что это 8- или 16-битный сэмпл.";
    strings["Undo##sgse"].plurals[0] = "Отменить";
    strings["Redo##sgse"].plurals[0] = "Повторить";
    strings["Amplify##sgse"].plurals[0] = "Усилить";
    strings["Volume##sgse"].plurals[0] = "Громкость";
    strings["Apply##sgse0"].plurals[0] = "Применить";
    strings["Normalize##sgse"].plurals[0] = "Нормализовать";
    strings["Fade in##sgse"].plurals[0] = "Плавное нарастание";
    strings["Fade out##sgse"].plurals[0] = "Плавное затухание";
    strings["Insert silence##sgse"].plurals[0] = "Вставить тишину";
    strings["Samples##sgse1"].plurals[0] = "Сэмплов";
    strings["Go##sgse"].plurals[0] = "Применить";
    strings["couldn't insert! make sure your sample is 8 or 16-bit.##sgse"].plurals[0] = "не получилось вставить! убедитесь, что это 8- или 16-битный сэмпл.";
    strings["Apply silence##sgse"].plurals[0] = "Применить тишину";
    strings["Delete##sgse"].plurals[0] = "Удалить";
    strings["Trim##sgse"].plurals[0] = "Обрезать";
    strings["Reverse##sgse"].plurals[0] = "Реверс";
    strings["Invert##sgse"].plurals[0] = "Инвертировать";
    strings["Signed/unsigned exchange##sgse"].plurals[0] = "Знаковый <-> беззнаковый";
    strings["Apply filter##sgse"].plurals[0] = "Применить фильтр";
    strings["Cutoff:##sgse"].plurals[0] = "Частота среза:";
    strings["From##sgse"].plurals[0] = "От";
    strings["To##sgse"].plurals[0] = "До";
    strings["Resonance##sgse"].plurals[0] = "Резонанс (добротность)";
    strings["Power##sgse"].plurals[0] = "Порядок фильтра";
    strings["Low-pass##sgse"].plurals[0] = "ФНЧ";
    strings["Band-pass##sgse"].plurals[0] = "ППФ";
    strings["High-pass##sgse"].plurals[0] = "ФВЧ";
    strings["Apply##sgse1"].plurals[0] = "Применить";
    strings["Crossfade loop points##sgse"].plurals[0] = "Сделать плавный переход между началом и концом зацикленной части";
    strings["Number of samples##sgse"].plurals[0] = "Число сэмплов";
    strings["Linear <-> Equal power##sgse"].plurals[0] = "Линейный <-> Одинаковая степень";
    strings["Apply##sgse2"].plurals[0] = "Применить";
    strings["Crossfade: length would go out of bounds. Aborted...##sgse"].plurals[0] = "Плавный переход: длина выйдет за границы. Действие отменено.";
    strings["Crossfade: length would overflow loopStart. Try a smaller random value.##sgse"].plurals[0] = "Плавный переход: длина выйдет за пределы начала цикла. Попробуйте с меньшим случайным значением.";
    strings["Preview sample##sgse"].plurals[0] = "Превью сэмпла";
    strings["Stop sample preview##sgse"].plurals[0] = "Остановить превью сэмпла";
    strings["Create instrument from sample##sgse"].plurals[0] = "Создать инструмент из сэмпла";
    strings["Zoom##sgse0"].plurals[0] = "Масштаб";
    strings["Zoom##sgse1"].plurals[0] = "Масштаб";
    strings["Auto##sgse"].plurals[0] = "Автоматически";
    strings["cut##sgse"].plurals[0] = "вырезать";
    strings["copy##sgse"].plurals[0] = "копировать";
    strings["paste##sgse"].plurals[0] = "вставить";
    strings["paste (replace)##sgse"].plurals[0] = "вставить (с заменой)";
    strings["paste (mix)##sgse"].plurals[0] = "вставить со смешением";
    strings["select all##sgse"].plurals[0] = "выбрать всё";
    strings["set loop to selection##sgse"].plurals[0] = "зациклить по выделенной части";
    strings["create wavetable from selection##sgse"].plurals[0] = "создать волновую таблицу из выделенной части";
    strings["Draw##sgse"].plurals[0] = "Рисовать";
    strings["%d samples, %d bytes##sgse"].plurals[0] = "%d сэмплов, %d байт";
    strings[" (%d-%d: %d samples)##sgse"].plurals[0] = " (%d-%d: %d сэмплов)";
    strings["Non-8/16-bit samples cannot be edited without prior conversion.##sgse"].plurals[0] = "Сэмплы в формате, отличающемся от 8- или 16-битной ИКМ, невозможно редактировать\nбез предварительной конвертации в один из этих форматов.";

    //   sgsi  src/gui/songInfo.cpp

    strings["Song Info###Song Information"].plurals[0] = "О треке###Song Information";
    strings["Name##sgsi"].plurals[0] = "Название";
    strings["Author##sgsi"].plurals[0] = "Автор";
    strings["Album##sgsi"].plurals[0] = "Альбом";
    strings["System##sgsi"].plurals[0] = "Система";
    strings["Auto##sgsi"].plurals[0] = "Авто";
    strings["Tuning (A-4)##sgsi"].plurals[0] = "Частота (ля 4-ой октавы)";

    //   sgsn  src/gui/songNotes.cpp

    strings["Song Comments###Song Comments"].plurals[0] = "Комментарии трека###Song Comments";

    //   sgsp  src/gui/speed.cpp

    strings["Speed###Speed"].plurals[0] = "Скорость###Speed";
    strings["Base Tempo##TempoOrHz"].plurals[0] = "Основной темп##TempoOrHz";
    strings["Tick Rate##TempoOrHz"].plurals[0] = "Частота движка##TempoOrHz";
    strings["click to display tick rate##sgsp"].plurals[0] = "нажмите для отображения частоты движка";
    strings["click to display base tempo##sgsp"].plurals[0] = "ажмите для отображения основного темпа";
    strings["Groove##sgsp"].plurals[0] = "Ритм-паттерн";
    strings["click for one speed##sgsp"].plurals[0] = "Нажмите для отображения одной скорости";
    strings["Speeds##sgsp"].plurals[0] = "Скорости";
    strings["click for groove pattern##sgsp"].plurals[0] = "Нажмите для отображения ритм-паттернов";
    strings["Speed##sgsp"].plurals[0] = "Скорость";
    strings["click for two (alternating) speeds##sgsp"].plurals[0] = "Нажмите для отображения двух (чередующихся) скоростей";
    strings["Virtual Tempo##sgsp"].plurals[0] = "Виртуальный темп";
    strings["Numerator##sgsp"].plurals[0] = "Числитель";
    strings["Denominator (set to base tempo)##sgsp"].plurals[0] = "Знаменатель (установите равным основному темпу)";
    strings["Divider##sgsp"].plurals[0] = "Делитель";
    strings["Highlight##sgsp"].plurals[0] = "Подсветка";
    strings["Pattern Length##sgsp"].plurals[0] = "Длина паттерна";
    strings["Song Length##sgsp"].plurals[0] = "Длина трека";

    //   sgst  src/gui/stats.cpp

    strings["Statistics###Statistics"].plurals[0] = "Статистика###Statistics";
    strings["Audio load##sgst"].plurals[0] = "Нагрузка от аудио";

    //   sgss  src/gui/subSongs.cpp

    strings["Subsongs###Subsongs"].plurals[0] = "Подпесни###Subsongs";
    strings["%d. <no name>##sgss0"].plurals[0] = "%d. <без названия>";
    strings["%d. <no name>##sgss1"].plurals[0] = "%d. <без названия>";
    strings["Move up##sgss"].plurals[0] = "Сдвинуть вверх";
    strings["Move down##sgss"].plurals[0] = "Сдвинуть вниз";
    strings["too many subsongs!##sgss0"].plurals[0] = "слишком много подпесен!";
    strings["Add##sgss"].plurals[0] = "Добавить";
    strings["too many subsongs!##sgss1"].plurals[0] = "слишком много подпесен!";
    strings["Duplicate##sgss"].plurals[0] = "Клонировать";
    strings["this is the only subsong!##sgss"].plurals[0] = "это единственная подпесня!";
    strings["are you sure you want to remove this subsong?##sgss"].plurals[0] = "вы действительно хотите удалить эту подпесню?";
    strings["Remove##sgss"].plurals[0] = "Удалить";
    strings["Name##sgss"].plurals[0] = "Название";

    //   sgsc  src/gui/sysConf.cpp

    strings["Clock rate:##sgsc0"].plurals[0] = "Тактовая частота:";
    strings["Chip type:##sgsc0"].plurals[0] = "Тип чипа:";
    strings["YM3438 (9-bit DAC)##sgsc"].plurals[0] = "YM3438 (9-битный ЦАП)";
    strings["YM2612 (9-bit DAC with distortion)##sgsc"].plurals[0] = "YM2612 (9-битный ЦАП с искажениями)";
    strings["YMF276 (external DAC)##sgsc"].plurals[0] = "YMF276 (внешний ЦАП)";
    strings["Disable ExtCh FM macros (compatibility)##sgsc0"].plurals[0] = "Отключить FM-макросы для расширенного канала (совместимость)";
    strings["Ins change in ExtCh operator 2-4 affects FB (compatibility)##sgsc0"].plurals[0] = "Смена инструмента на операторах 2-4 расш. канала меняет FB (совместимость)";
    strings["Clock rate:##sgsc1"].plurals[0] = "Тактовая частота:";
    strings["1.79MHz (Half NTSC)##sgsc"].plurals[0] = "1.79 МГц (половина NTSC)";
    strings["Chip type:##sgsc1"].plurals[0] = "Тип чипа:";
    strings["TI SN76489 with Atari-like short noise##sgsc"].plurals[0] = "TI SN76489 с коротким шумом, похожим на Atari";
    strings["Tandy PSSJ 3-voice sound##sgsc"].plurals[0] = "Tandy PSSJ трёхголосый звук";
    strings["Disable noise period change phase reset##sgsc"].plurals[0] = "Отключить сброс фазы при изменении периода шума";
    strings["Disable easy period to note mapping on upper octaves##sgsc0"].plurals[0] = "Отключить простое преобразование периода в ноту на верхних октавах";
    strings["Pseudo-PAL##sgsc0"].plurals[0] = "Псевдо-PAL";
    strings["Disable anti-click##sgsc0"].plurals[0] = "Отключить анти-щелчок";
    strings["Chip revision:##sgsc0"].plurals[0] = "Ревизия чипа:";
    strings["HuC6280 (original)##sgsc"].plurals[0] = "HuC6280 (оригинальный)";
    strings["CPU rate:##sgsc"].plurals[0] = "Частота ЦП:";
    strings["Sample memory:##sgsc"].plurals[0] = "Память сэмплов:";
    strings["8K (rev A/B/E)##sgsc"].plurals[0] = "8 КиБ (версия A/B/E)";
    strings["64K (rev D/F)##sgsc"].plurals[0] = "64 КиБ (версия D/F)";
    strings["DAC resolution:##sgsc"].plurals[0] = "Разрешение ЦАП:";
    strings["16-bit (rev A/B/D/F)##sgsc"].plurals[0] = "16 бит (версия A/B/D/F)";
    strings["8-bit + TDM (rev C/E)##sgsc"].plurals[0] = "8 бит + мультиплексирование с разделением по времени (версия C/E)";
    strings["Enable echo##sgsc0"].plurals[0] = "Включить эхо";
    strings["Swap echo channels##sgsc"].plurals[0] = "Поменять местами каналы эхо";
    strings["Echo delay:##sgsc0"].plurals[0] = "Задержка эхо:";
    strings["Echo resolution:##sgsc"].plurals[0] = "Разрешение эхо:";
    strings["Echo feedback:##sgsc0"].plurals[0] = "Обратная связь эхо:";
    strings["Echo volume:##sgsc0"].plurals[0] = "Громкость эхо:";
    strings["Disable anti-click##sgsc1"].plurals[0] = "Отключить анти-щелчок";
    strings["Chip revision:##sgsc1"].plurals[0] = "Ревизия чипа:";
    strings["Original (DMG)##sgsc"].plurals[0] = "Оригинальный (DMG)";
    strings["Game Boy Color (rev C)##sgsc"].plurals[0] = "Game Boy Color (версия C)";
    strings["Game Boy Color (rev E)##sgsc"].plurals[0] = "Game Boy Color (версия E)";
    strings["Wave channel orientation:##sgsc"].plurals[0] = "Канал волновых таблиц";
    strings["Normal##sgsc"].plurals[0] = "Нормально";
    strings["Inverted##sgsc"].plurals[0] = "Инвертирован";
    strings["Exact data (inverted)##sgsc"].plurals[0] = "Точные данные (инвертирован)";
    strings["Exact output (normal)##sgsc"].plurals[0] = "Точный вывод (нормально)";
    strings["Pretty please one more compat flag when I use arpeggio and my sound length##sgsc"].plurals[0] = "Ну пожалуйста ещё один флаг совместимости когда я использую арпеджио и малую длину звука на шумовом канале";
    strings["Clock rate:##sgsc2"].plurals[0] = "Частота:";
    strings["Arcade (4MHz)##sgsc"].plurals[0] = "Arcade (4 МГц)";
    strings["Half NTSC (1.79MHz)##sgsc"].plurals[0] = "Половина NTSC (1.79 МГц)";
    strings["Patch set:##sgsc"].plurals[0] = "Набор патчей:";
    strings["Ignore top/hi-hat frequency changes##sgsc"].plurals[0] = "Игнорировать смену частоты тарелок/хай-хэтов";
    strings["Apply fixed frequency to all drums at once##sgsc"].plurals[0] = "Применять режим фиксированной частоты ко всем ударным";
    strings["Broken pitch macro/slides (compatibility)##sgsc0"].plurals[0] = "Сломанное портаменто эффектов и макросов (совместимость)";
    strings["Pseudo-PAL##sgsc1"].plurals[0] = "Псевдо-PAL";
    strings["Broken pitch macro/slides (compatibility)##sgsc1"].plurals[0] = "Сломанное портаменто эффектов и макросов (совместимость)";
    strings["DPCM channel mode:##sgsc"].plurals[0] = "Режим ДИКМ-канала:";
    strings["DPCM (muffled samples; low CPU usage)##sgsc"].plurals[0] = "ДИКМ (замыленные сэмплы; малое использование ЦП)";
    strings["PCM (crisp samples; high CPU usage)##sgsc"].plurals[0] = "ИКМ (чёткие сэмплы; большое использование ЦП)";
    strings["Clock rate:##sgsc18"].plurals[0] = "Тактовая частота:";
    strings["Clock rate:##sgsc19"].plurals[0] = "Тактовая частота:";
    strings["Global parameter priority:##sgsc0"].plurals[0] = "Приоритет глобальных параметров:";
    strings["Left to right##sgsc0"].plurals[0] = "Слева направо";
    strings["Last used channel##sgsc0"].plurals[0] = "Последний использованный канал";
    strings["Hard reset envelope:##sgsc"].plurals[0] = "Огибающая при жёстком перезапуске:";
    strings["Attack##sgsc"].plurals[0] = "Атака";
    strings["Decay##sgsc"].plurals[0] = "Спад";
    strings["Sustain##sgsc"].plurals[0] = "Сустейн";
    strings["Release##sgsc"].plurals[0] = "Релиз";
    strings["Envelope reset time:##sgsc"].plurals[0] = "Время сброса огибающей:";
    strings["- 0 disables envelope reset. not recommended!\n- 1 may trigger SID envelope bugs.\n- values that are too high may result in notes being skipped.##sgsc"].plurals[0] = "- 0 отключает сброс огибающей. не рекомендуется!\n- 1 может привести к появлению сбоев огибающей SID.\n- слишком большие значения могут привести к пропуску коротких нот.";
    strings["Disable 1Exy env update (compatibility)##sgsc"].plurals[0] = "Отключить обновление огибающей при применении эффекта 1Exy (совместимость)";
    strings["Relative duty and cutoff macros are coarse (compatibility)##sgsc"].plurals[0] = "Макросы скважности и частоты среза в относительном режиме имеют меньшее разрешение (совместимость)";
    strings["Disable ExtCh FM macros (compatibility)##sgsc1"].plurals[0] = "Отключить FM-макросы для расширенного канала (совместимость)";
    strings["Ins change in ExtCh operator 2-4 affects FB (compatibility)##sgsc1"].plurals[0] = "Смена инструмента на операторах 2-4 расш. канала меняет FB (совместимость)";
    strings["SSG Volume##sgsc0"].plurals[0] = "Громкость SSG";
    strings["FM/ADPCM Volume##sgsc0"].plurals[0] = "Громкость FM/ADPCM";
    strings["Clock rate:##sgsc3"].plurals[0] = "Тактовая частота:";
    strings["0.83MHz (Pre-divided Sunsoft 5B on PAL)##sgsc"].plurals[0] = "0.83 МГц (Sunsoft 5B с предварительным делителем частоты, PAL)";
    strings["0.89MHz (Pre-divided Sunsoft 5B)##sgsc"].plurals[0] = "0.89 МГц (Sunsoft 5B с предварительным делителем частоты)";
    strings["Chip type:##sgsc2"].plurals[0] = "Тип чипа:";
    strings["note: AY-3-8914 is not supported by the VGM format!##sgsc"].plurals[0] = "примечание: AY-3-8914 не поддерживается в формате VGM!";
    strings["Stereo##_AY_STEREO"].plurals[0] = "Стерео##_AY_STEREO";
    strings["Separation##sgsc"].plurals[0] = "Разделение в стерео";
    strings["Half Clock divider##_AY_CLKSEL"].plurals[0] = "Делить тактовую частоту на 2##_AY_CLKSEL";
    strings["Stereo separation:##sgsc"].plurals[0] = "Разделение в стерео:";
    strings["Model:##sgsc"].plurals[0] = "Модель:";
    strings["Chip memory:##sgsc"].plurals[0] = "Память чипа:";
    strings["2MB (ECS/AGA max)##sgsc"].plurals[0] = "2 МиБ (максимум для ECS/AGA)";
    strings["512KB (OCS max)##sgsc"].plurals[0] = "512 КиБ (максимум для OCS)";
    strings["Bypass frequency limits##sgsc"].plurals[0] = "Игнорировать ограничения частоты";
    strings["Mixing mode:##sgsc"].plurals[0] = "Режим микширования:";
    strings["Mono##sgsc"].plurals[0] = "Моно";
    strings["Mono (no distortion)##sgsc"].plurals[0] = "Моно (без искажений)";
    strings["Stereo##sgsc0"].plurals[0] = "Стерео";
    strings["Clock rate:##sgsc4"].plurals[0] = "Тактовая частота:";
    strings["Speaker type:##sgsc"].plurals[0] = "Тип пищалки:";
    strings["Unfiltered##sgsc"].plurals[0] = "Без фильтрации";
    strings["Cone##sgsc"].plurals[0] = "Диффузор";
    strings["Piezo##sgsc"].plurals[0] = "Пьезопищалка";
    strings["Use system beeper (Linux only!)##sgsc"].plurals[0] = "Использовать пищалку на материнской плате (только для Linux!)";
    strings["Reset phase on frequency change##sgsc"].plurals[0] = "Сбор фазы при изменении частоты";
    strings["Echo delay:##sgsc1"].plurals[0] = "Задержка эхо:";
    strings["Echo feedback:##sgsc1"].plurals[0] = "Обратная связь эхо:";
    strings["Clock rate:##sgsc5"].plurals[0] = "Тактовая частота:";
    strings["Stereo##sgsc1"].plurals[0] = "Стерео";
    strings["Bankswitched (Seta 2)##sgsc"].plurals[0] = "Со сменой банков памяти (Seta 2)";
    strings["Clock rate:##sgsc6"].plurals[0] = "Тактовая частота:";
    strings["Initial channel limit:##sgsc0"].plurals[0] = "Изначальный лимит числа каналов:";
    strings["Disable hissing##sgsc"].plurals[0] = "Отключить высокочастотное пищание";
    strings["Scale frequency to wave length##sgsc"].plurals[0] = "Масштабировать частоту под длину волны";
    strings["Initial channel limit:##sgsc1"].plurals[0] = "Изначальный лимит числа каналов:";
    strings["Volume scale:##sgsc0"].plurals[0] = "Масштабирование громкости:";
    strings["Clock rate:##sgsc7"].plurals[0] = "Тактовая частота:";
    strings["Output rate:##sgsc0"].plurals[0] = "Частота квантования на выходе:";
    strings["FM: clock / 72, SSG: clock / 16##sgsc0"].plurals[0] = "FM: такт. част. / 72, SSG: такт. част. / 16";
    strings["FM: clock / 36, SSG: clock / 8##sgsc"].plurals[0] = "FM: такт. част. / 36, SSG: такт. част. / 8";
    strings["FM: clock / 24, SSG: clock / 4##sgsc"].plurals[0] = "FM: такт. част. / 24, SSG: такт. част. / 4";
    strings["SSG Volume##sgsc1"].plurals[0] = "Громкость SSG";
    strings["FM Volume##sgsc"].plurals[0] = "Громкость FM";
    strings["Disable ExtCh FM macros (compatibility)##sgsc2"].plurals[0] = "Отключить FM-макросы для расширенного канала (совместимость)";
    strings["Ins change in ExtCh operator 2-4 affects FB (compatibility)##sgsc2"].plurals[0] = "Смена инструмента на операторах 2-4 расш. канала меняет FB (совместимость)";
    strings["Clock rate:##sgsc8"].plurals[0] = "Тактовая частота:";
    strings["8MHz (Arcade)##sgsc"].plurals[0] = "8 МГц (Arcade)";
    strings["Output rate:##sgsc1"].plurals[0] = "Частота квантования на выходе:";
    strings["FM: clock / 144, SSG: clock / 32##sgsc"].plurals[0] = "FM: такт. част. / 144, SSG: такт. част. / 32";
    strings["FM: clock / 72, SSG: clock / 16##sgsc1"].plurals[0] = "FM: такт. част. / 72, SSG: такт. част. / 16";
    strings["FM: clock / 48, SSG: clock / 8##sgsc"].plurals[0] = "FM: такт. част. / 48, SSG: такт. част. / 8";
    strings["SSG Volume##sgsc2"].plurals[0] = "Громкость SSG";
    strings["FM/ADPCM Volume##sgsc1"].plurals[0] = "Громкость FM/ADPCM";
    strings["Disable ExtCh FM macros (compatibility)##sgsc3"].plurals[0] = "Отключить FM-макросы для расширенного канала (совместимость)";
    strings["Ins change in ExtCh operator 2-4 affects FB (compatibility)##sgsc3"].plurals[0] = "Смена инструмента на операторах 2-4 расш. канала меняет FB (совместимость)";
    strings["Clock rate:##sgsc9"].plurals[0] = "Тактовая частота:";
    strings["Chip type:##sgsc3"].plurals[0] = "Тип чипа:";
    strings["RF5C68 (10-bit output)##sgsc"].plurals[0] = "RF5C68 (10-битный звук)";
    strings["RF5C164 (16-bit output)##sgsc"].plurals[0] = "RF5C164 (16-битный звук)";
    strings["Clock rate:##sgsc10"].plurals[0] = "Тактовая частота:";
    strings["Sample rate table:##sgsc"].plurals[0] = "Таблица частот квантования:";
    strings["divider \\ clock##sgsc"].plurals[0] = "Делитель тактовой частоты";
    strings["full##sgsc"].plurals[0] = "полная";
    strings["half##sgsc"].plurals[0] = "половина";
    strings["Clock rate:##sgsc11"].plurals[0] = "Тактовая частота:";
    strings["Output rate:##sgsc2"].plurals[0] = "Частота квантования на выходе:";
    strings["clock / 132##sgsc"].plurals[0] = "такт. част. / 132";
    strings["clock / 165##sgsc"].plurals[0] = "такт. част. / 165";
    strings["Clock rate:##sgsc12"].plurals[0] = "Тактовая частота:";
    strings["1.5MHz (Arcade)##sgsc"].plurals[0] = "1.5 МГц (Arcade)";
    strings["Clock rate:##sgsc13"].plurals[0] = "Тактовая частота:";
    strings["Clock rate:##sgsc14"].plurals[0] = "Тактовая частота:";
    strings["Chip type:##sgsc4"].plurals[0] = "Тип чипа:";
    strings["Compatible panning (0800)##sgsc"].plurals[0] = "Совместимое панорамирование (0800)";
    strings["Clock rate:##sgsc15"].plurals[0] = "Тактовая частота:";
    strings["Output rate:##sgsc3"].plurals[0] = "Частота квантования на выходе:";
    strings["Output bit depth:##sgsc"].plurals[0] = "Глубина квантования на выходе:";
    strings["Stereo##sgsc2"].plurals[0] = "Стерео";
    strings["Interpolation:##sgsc"].plurals[0] = "Интерполяция:";
    strings["None##sgsc"].plurals[0] = "Выкл.";
    strings["Linear##sgsc"].plurals[0] = "Линейная";
    strings["Cubic##sgsc"].plurals[0] = "Кубическая";
    strings["Sinc##sgsc"].plurals[0] = "Sinc";
    strings["Volume scale:##sgsc1"].plurals[0] = "Масштабирование громкости:";
    strings["Left##VolScaleL"].plurals[0] = "Слева##VolScaleL";
    strings["Right##VolScaleL"].plurals[0] = "Справа##VolScaleL";
    strings["Enable echo##sgsc1"].plurals[0] = "Включить эхо";
    strings["Initial echo state:##sgsc"].plurals[0] = "Начальное состояние эхо:";
    strings["Delay##EchoDelay"].plurals[0] = "Задержка##EchoDelay";
    strings["Feedback##EchoFeedback"].plurals[0] = "Обр. связь##EchoFeedback";
    strings["Echo volume:##sgsc1"].plurals[0] = "Громкость эхо:";
    strings["Left##EchoVolL"].plurals[0] = "Слева##EchoVolL";
    strings["Right##EchoVolL"].plurals[0] = "Справа##EchoVolL";
    strings["Echo filter:##sgsc"].plurals[0] = "Фильтр эхо:";
    strings["Hex##SNESFHex"].plurals[0] = "Шест.##SNESFHex";
    strings["Dec##SNESFHex"].plurals[0] = "Дес.##SNESFHex";
    strings["sum: %d##sgsc"].plurals[0] = "сумма: %d";
    strings["Detune##sgsc"].plurals[0] = "Расстройка";
    strings["Capacitor values (nF):##sgsc"].plurals[0] = "Ёмкость конденсаторов (нФ):";
    strings["Initial part volume (channel 1-4):##sgsc"].plurals[0] = "Начальная громкость (каналы 1-4):";
    strings["Initial part volume (channel 5-8):##sgsc"].plurals[0] = "Начальная громкость (каналы 5-8):";
    strings["Envelope mode (channel 1-4):##sgsc"].plurals[0] = "Режим огибающей (каналы 1-4):";
    strings["Capacitor (attack/decay)##EM00"].plurals[0] = "Конденсатор (атака/спад)##EM00";
    strings["External (volume macro)##EM01"].plurals[0] = "Внешняя (макрос громкости)##EM01";
    strings["Envelope mode (channel 5-8):##sgsc"].plurals[0] = "Режим огибающей (каналы 5-8):";
    strings["Capacitor (attack/decay)##EM10"].plurals[0] = "Конденсатор (атака/спад)##EM10";
    strings["External (volume macro)##EM11"].plurals[0] = "Внешняя (макрос громкости)##EM11";
    strings["Global vibrato:##sgsc"].plurals[0] = "Глобальное вибрато:";
    strings["Speed##sgsc"].plurals[0] = "Скорость";
    strings["Depth##sgsc"].plurals[0] = "Глубина";
    strings["Disable easy period to note mapping on upper octaves##sgsc1"].plurals[0] = "Отключить простое преобразование периода в ноту на верхних октавах";
    strings["Stereo##sgsc3"].plurals[0] = "Стерео";
    strings["Waveform storage mode:##sgsc0"].plurals[0] = "Способ хранения волн:";
    strings["RAM##sgsc"].plurals[0] = "ОЗУ";
    strings["ROM (up to 8 waves)##sgsc"].plurals[0] = "ПЗУ (до 8 волн)";
    strings["Compatible noise frequencies##sgsc"].plurals[0] = "Совместимые частоты шума";
    strings["Legacy slides and pitch (compatibility)##sgsc"].plurals[0] = "Старые частоты и портаменто (совместимость)";
    strings["Clock rate:##sgsc16"].plurals[0] = "Тактовая частота:";
    strings["Clock rate:##sgsc17"].plurals[0] = "Тактовая частота:";
    strings["Global parameter priority:##sgsc1"].plurals[0] = "Приоритет глобальных параметров:";
    strings["Left to right##sgsc1"].plurals[0] = "Слева направо";
    strings["Last used channel##sgsc1"].plurals[0] = "Последний использованный канал";
    strings["Banking style:##sgsc"].plurals[0] = "Стиль переключения банков:";
    strings["Raw (16MB; no VGM export!)##sgsc"].plurals[0] = "Сырой (16 МиБ; не поддерживается при экспорте в VGM!)";
    strings["Waveform storage mode:##sgsc1"].plurals[0] = "Способ хранения волн:";
    strings["Dynamic (unconfirmed)##sgsc"].plurals[0] = "Динамический (не подтверждён)";
    strings["Static (up to 5 waves)##sgsc"].plurals[0] = "Статический (до 5 волн)";
    strings["nothing to configure##sgsc"].plurals[0] = "настраивать нечего";
    strings["Downmix chip output to mono##sgsc"].plurals[0] = "Свести звук чипа в моно";
    strings["Reserved blocks for wavetables:##sgsc"].plurals[0] = "Зарезервированных блоков под волновые таблицы:";
    strings["Reserve this many blocks 256 bytes each in sample memory.\nEach block holds one wavetable (is used for one wavetable channel),\nso reserve as many as you need.##sgsc"].plurals[0] = "Зрезервировать столько блоков, каждый по 256 байт, в памяти сэмплов.\nВ каждый блок помещается одна волновая таблица (он используется для одного канала в режиме волновых таблиц),\nтак что выделяйте столько, сколько вам нужно.";
    strings["Custom clock rate##sgsc"].plurals[0] = "Пользовательская тактовая частота";

    //   sgsm  src/gui/sysManager.cpp

    strings["Chip Manager###Chip Manager"].plurals[0] = "Менеджер чипов###Chip Manager";
    strings["Preserve channel order##sgsm"].plurals[0] = "Сохранить порядок каналов";
    strings["Name##sgsm"].plurals[0] = "Название";
    strings["Actions##sgsm"].plurals[0] = "Действия";
    strings["(drag to swap chips)##sgsm"].plurals[0] = "(перетащите, чтобы поменять местами каналы)";
    strings["Change##SysChange"].plurals[0] = "Сменить##SysChange";
    strings["Are you sure you want to remove this chip?##sgsm"].plurals[0] = "Вы действительно хотите удалить этот чип?";
    strings["Remove##sgsm"].plurals[0] = "Удалить";
    strings["cannot add chip! (##sgsm"].plurals[0] = "не могу добавить чип! (";

    //   sgsa  src/gui/sysPartNumber.cpp

    strings["ZXS Beeper##sgsa"].plurals[0] = "ZXS (пищалка)";

    //   sgsp  src/gui/sysPicker.cpp

    strings["Search...##sgsp"].plurals[0] = "Поиск...";

    // # sgvm  src/gui/volMeter.cpp

    strings["Volume Meter###Volume Meter"].plurals[0] = "Измеритель громкости###Volume Meter";

    //   sgwe  src/gui/waveEdit.cpp

    strings["Sine##sgwe0"].plurals[0] = "Синус";
    strings["Triangle##sgwe0"].plurals[0] = "Треуг. волна";
    strings["Saw##sgwe0"].plurals[0] = "Пила";
    strings["Pulse##sgwe"].plurals[0] = "Меандр";

    strings["None##sgwe"].plurals[0] = "Нет";
    strings["Linear##sgwe"].plurals[0] = "Линейная";
    strings["Cosine##sgwe"].plurals[0] = "Косинусоидная";
    strings["Cubic##sgwe"].plurals[0] = "Кубическая";

    strings["Sine##sgwe1"].plurals[0] = "Синус";
    strings["Rect. Sine##sgwe"].plurals[0] = "Выпрямл. синус";
    strings["Abs. Sine##sgwe"].plurals[0] = "Модуль синуса";
    strings["Quart. Sine##sgwe"].plurals[0] = "Четвертинки синуса";
    strings["Squish. Sine##sgwe"].plurals[0] = "Сжатый синус";
    strings["Abs. Squish. Sine##sgwe"].plurals[0] = "Модуль сж. синуса";
    strings["Square##sgwe"].plurals[0] = "Меандр";
    strings["rectSquare##sgwe"].plurals[0] = "Выпрямл. меандр";
    strings["Saw##sgwe1"].plurals[0] = "Пила";
    strings["Rect. Saw##sgwe"].plurals[0] = "Выпрямл. пила";
    strings["Abs. Saw##sgwe"].plurals[0] = "Модуль пилы";
    strings["Cubed Saw##sgwe"].plurals[0] = "Пила в кубе";
    strings["Rect. Cubed Saw##sgwe"].plurals[0] = "Выпрямл. пила в кубе";
    strings["Abs. Cubed Saw##sgwe"].plurals[0] = "Модуль пилы в кубе";
    strings["Cubed Sine##sgwe"].plurals[0] = "Куб синуса";
    strings["Rect. Cubed Sine##sgwe"].plurals[0] = "Выпрямл. куб синуса";
    strings["Abs. Cubed Sine##sgwe"].plurals[0] = "Модуль куба синуса";
    strings["Quart. Cubed Sine##sgwe"].plurals[0] = "Четвертинки куба синуса";
    strings["Squish. Cubed Sine##sgwe"].plurals[0] = "Сжатый куб синуса";
    strings["Squish. Abs. Cub. Sine##sgwe"].plurals[0] = "Модуль сж. куба синуса";
    strings["Triangle##sgwe1"].plurals[0] = "Треуг. волна";
    strings["Rect. Triangle##sgwe"].plurals[0] = "Выпрямл. треуг. волна";
    strings["Abs. Triangle##sgwe"].plurals[0] = "Модуль треуг. волны";
    strings["Quart. Triangle##sgwe"].plurals[0] = "Четвертинки треуг. волны";
    strings["Squish. Triangle##sgwe"].plurals[0] = "Сжатая треуг. волна";
    strings["Abs. Squish. Triangle##sgwe"].plurals[0] = "Модуль сж. треуг. волны";
    strings["Cubed Triangle##sgwe"].plurals[0] = "Куб треуг. волны";
    strings["Rect. Cubed Triangle##sgwe"].plurals[0] = "Выпрямл. куб треуг. волны";
    strings["Abs. Cubed Triangle##sgwe"].plurals[0] = "Модуль куба треуг. волны";
    strings["Quart. Cubed Triangle##sgwe"].plurals[0] = "Четвертинки куба треуг. волны";
    strings["Squish. Cubed Triangle##sgwe"].plurals[0] = "Сжатый куб треуг. волны";
    strings["Squish. Abs. Cub. Triangle##sgwe"].plurals[0] = "Сжатый модуль куба треуг. волны";

    strings["Wavetable Editor###Wavetable Editor"].plurals[0] = "Редактор волновых таблиц###Wavetable Editor";
    strings["no wavetable selected##sgwe"].plurals[0] = "не выбрано ни одной волновой таблицы";
    strings["no wavetable selected##sgwe"].plurals[0] = "не выбрано ни одной волновой таблицы";
    strings["select one...##sgwe"].plurals[0] = "выберите волновую таблицу...";
    strings["or##sgwe0"].plurals[0] = "или";
    strings["Open##sgwe0"].plurals[0] = "Откройте";
    strings["or##sgwe1"].plurals[0] = "или";
    strings["Create New##sgwe"].plurals[0] = "Создайте новую";
    strings["Open##sgwe1"].plurals[0] = "Открыть";
    strings["Save##sgwe"].plurals[0] = "Сохранить";
    strings["export .dmw...##sgwe"].plurals[0] = "экспорт .dmw...";
    strings["export raw...##sgwe"].plurals[0] = "экспорт сырых данных...";
    strings["Steps##sgwe"].plurals[0] = "Уровни";
    strings["Lines##sgwe"].plurals[0] = "Линии";
    strings["Width##sgwe"].plurals[0] = "Длина";
    strings["use a width of:\n- any on Amiga/N163\n- 32 on Game Boy, PC Engine, SCC, Konami Bubble System, Namco WSG, Virtual Boy and WonderSwan\n- 64 on FDS\n- 128 on X1-010\n- 256 for ES5503\nany other widths will be scaled during playback.##sgwe"].plurals[0] = "используйте следующие длины:\n- любую для Amiga/N163\n- 32 для Game Boy, PC Engine, SCC, Konami Bubble System, Namco WSG, Virtual Boy и WonderSwan\n- 64 для FDS\n- 128 для X1-010\n- 256 для ES5503\nлюбые другие длины будут отмасштабированы во время воспроизведения.";
    strings["Height##sgwe"].plurals[0] = "Высота";
    strings["use a height of:\n- 16 for Game Boy, WonderSwan, Namco WSG, Konami Bubble System, X1-010 Envelope shape and N163\n- 32 for PC Engine\n- 64 for FDS and Virtual Boy\n- 256 for X1-010, SCC and ES5503\nany other heights will be scaled during playback.##sgwe"].plurals[0] = "используйте следующие высоты:\n- 16 для Game Boy, WonderSwan, Namco WSG, Konami Bubble System, формы огибающей X1-010 и N163\n- 32 для PC Engine\n- 64 для FDS и Virtual Boy\n- 256 для X1-010, SCC и ES5503\nлюбые другие высоты будут отмасштабированы во время воспроизведения.";
    strings["Shapes##sgwe"].plurals[0] = "Волны";
    strings["Duty##sgwe"].plurals[0] = "Скважность";
    strings["Exponent##sgwe"].plurals[0] = "Пок. степени";
    strings["XOR Point##sgwe"].plurals[0] = "Точка XOR";
    strings["Amplitude/Phase##sgwe"].plurals[0] = "Амплитуда/фаза";
    strings["Op##sgwe0"].plurals[0] = "Опер.";
    strings["Level##sgwe"].plurals[0] = "Громкость";
    strings["Mult##sgwe"].plurals[0] = "Множитель";
    strings["FB##sgwe"].plurals[0] = "Обр. св.";
    strings["Op##sgwe1"].plurals[0] = "Опер.";
    strings["Waveform##sgwe"].plurals[0] = "Волна";
    strings["Connection Diagram##sgwe"].plurals[0] = "Матрица модуляции";
    strings["Connection Diagram##sgwe"].plurals[0] = "Матрица модуляции";
    strings["Out##sgwe"].plurals[0] = "Вывод";
    strings["WaveTools##sgwe"].plurals[0] = "Инструменты";
    strings["Scale X##sgwe"].plurals[0] = "Масштаб X";
    strings["wavetable longer than 256 samples!##sgwe"].plurals[0] = "волновая таблица длинее 256 шагов!";
    strings["Scale Y##sgwe"].plurals[0] = "Масштаб Y";
    strings["Offset X##sgwe"].plurals[0] = "Сдвиг X";
    strings["Offset Y##sgwe"].plurals[0] = "Сдвиг Y";
    strings["Smooth##sgwe"].plurals[0] = "Сгладить";
    strings["Amplify##sgwe"].plurals[0] = "Усилить";
    strings["Normalize##sgwe"].plurals[0] = "Нормализовать";
    strings["Invert##sgwe"].plurals[0] = "Инвертировать";
    strings["Reverse##sgwe"].plurals[0] = "Реверс";
    strings["Half##sgwe"].plurals[0] = "Сократить 2х";
    strings["Double##sgwe"].plurals[0] = "Растянуть 2х";
    strings["Convert Signed/Unsigned##sgwe"].plurals[0] = "Конверт. знаковая <-> беззнаковая";
    strings["Randomize##sgwe"].plurals[0] = "Заполнить случ. знач.";
    strings["Dec##sgwe"].plurals[0] = "Дес.";
    strings["Hex##sgwe"].plurals[0] = "Шест.";
    strings["Signed/Unsigned##sgwe"].plurals[0] = "Знаковая <-> беззнаковая";

    //   sgxy  src/gui/xyOsc.cpp

    strings["Oscilloscope (X-Y)###Oscilloscope (X-Y)"].plurals[0] = "Осциллограф (X-Y)###Oscilloscope (X-Y)";
    strings["X Channel##sgxy"].plurals[0] = "Канал оси X";
    strings["Invert##X"].plurals[0] = "Инвертировать";
    strings["Y Channel##sgxy"].plurals[0] = "Канал оси Y";
    strings["Invert##Y"].plurals[0] = "Инвертировать";
    strings["Zoom##sgxy"].plurals[0] = "Масштаб";
    strings["Samples##sgxy"].plurals[0] = "Сэмплов";
    strings["Decay Time (ms)##sgxy"].plurals[0] = "Время затухания (мс)";
    strings["Intensity##sgxy"].plurals[0] = "Яркость";
    strings["Line Thickness##sgxy"].plurals[0] = "Толщина линий";
    strings["OK##sgxy"].plurals[0] = "ОК";
    strings["(-Infinity)dB,(-Infinity)dB##sgxy"].plurals[0] = "(минус бесконечность) дБ,(минус бесконечность) дБ";
    strings["(-Infinity)dB,%.1fdB##sgxy"].plurals[0] = "(минус бесконечность) дБ,%.1f дБ";
    strings["%.1fdB,(-Infinity)dB##sgxy"].plurals[0] = "%.1f дБ,(минус бесконечность) дБ";

    //WINDOW NAMES

    strings["Orders###Orders"].plurals[0] = "Матрица паттернов###Orders";
    strings["About Furnace###About Furnace"].plurals[0] = "О Furnace###About Furnace";
    strings["Channels###Channels"].plurals[0] = "Каналы###Channels";
    strings["Oscilloscope (per-channel)###Oscilloscope (per-channel)"].plurals[0] = "Осциллографы (отд. кан.)###Oscilloscope (per-channel)";
    strings["Compatibility Flags###Compatibility Flags"].plurals[0] = "Флаги совместимости###Compatibility Flags";
    strings["Instruments###Instruments"].plurals[0] = "Инструменты###Instruments";
    strings["Wavetables###Wavetables"].plurals[0] = "Волновые таблицы###Wavetables";
    strings["Debug###Debug"].plurals[0] = "Отладка###Debug";
    strings["Samples###Samples"].plurals[0] = "Сэмплы###Samples";
    strings["MobileEdit###MobileEdit"].plurals[0] = "Моб. меню ред.###MobileEdit";
    strings["Log Viewer###Log Viewer"].plurals[0] = "Просмотр логов###Log Viewer";
    strings["Mixer###Mixer"].plurals[0] = "Микшер###Mixer";
    strings["OrderSel###OrderSel"].plurals[0] = "Выб. матр. пат.###OrderSel";
    strings["Spoiler###Spoiler"].plurals[0] = "Спойлер###Spoiler";
    //popups
    strings["Warning###Warning"].plurals[0] = "Внимание###Warning";
    strings["Error###Error"].plurals[0] = "Ошибка###Error";
    strings["Select Instrument###Select Instrument"].plurals[0] = "Выберете инструмент###Select Instrument";
    strings["Import Raw Sample###Import Raw Sample"].plurals[0] = "Импорт сырых данных сэмпла###Import Raw Sample";
    strings["Rendering...###Rendering..."].plurals[0] = "Рендер...###Rendering...";

    //EFFECT LIST

    //common (non-chip-specific) effects

    strings["00xy: Arpeggio"].plurals[0] = "00xy: Арпеджио";
    
    //MACRO EDITOR

    //macro hover notes

    strings["exponential##sgmu"].plurals[0] = "экспоненциальное";
    strings["linear##sgmu"].plurals[0] = "линейное";
    strings["direct##sgmu"].plurals[0] = "прямое";

    strings["Release"].plurals[0] = "Релиз";
    strings["Loop"].plurals[0] = "Цикл";

    strings["HP/K2, HP/K2##sgmu"].plurals[0] = "ФВЧ/K2, ФВЧ/K2";
    strings["HP/K2, LP/K1##sgmu"].plurals[0] = "ФВЧ/K2, ФНЧ/K1";
    strings["LP/K2, LP/K2##sgmu"].plurals[0] = "ФНЧ/K2, ФНЧ/K2";
    strings["LP/K2, LP/K1##sgmu"].plurals[0] = "ФНЧ/K2, ФНЧ/K1";

    strings["Saw##sgmu"].plurals[0] = "Пила";
    strings["Square##sgmu"].plurals[0] = "Меандр";
    strings["Triangle##sgmu"].plurals[0] = "Треугольная волна";
    strings["Random##sgmu"].plurals[0] = "Шум";

    //keyboard hotkeys

    strings["---Global##sggc"].plurals[0] = "---Global";
    strings["New##sggc"].plurals[0] = "Новый";
    strings["Open file##sggc"].plurals[0] = "Открыть файл";
    strings["Restore backup##sggc"].plurals[0] = "Загрузить резервную копию";
    strings["Save file##sggc"].plurals[0] = "Сохранить файл";
    strings["Save as##sggc"].plurals[0] = "Сохранить как";
    strings["Export##sggc"].plurals[0] = "Экспорт";
    strings["Undo##sggc"].plurals[0] = "Отменить";
    strings["Redo##sggc"].plurals[0] = "Вернуть";
    strings["Play/Stop (toggle)##sggc"].plurals[0] = "Старт/стоп (переключение)";
    strings["Play##sggc"].plurals[0] = "Воспроизведение";
    strings["Stop##sggc"].plurals[0] = "Стоп";
    strings["Play (from beginning)##sggc"].plurals[0] = "Воспроизведение (с начала)";
    strings["Play (repeat pattern)##sggc"].plurals[0] = "Воспроизведение (зациклить текущий паттерн)";
    strings["Play from cursor##sggc"].plurals[0] = "Воспроизведение с курсора";
    strings["Step row##sggc"].plurals[0] = "Сделать один шаг по паттерну";
    strings["Octave up##sggc"].plurals[0] = "На октаву вверх";
    strings["Octave down##sggc"].plurals[0] = "На октаву вниз";
    strings["Previous instrument##sggc"].plurals[0] = "Предыдущий инструмент";
    strings["Next instrument##sggc"].plurals[0] = "Следующий инструмент";
    strings["Increase edit step##sggc"].plurals[0] = "Увеличить шаг редактирования";
    strings["Decrease edit step##sggc"].plurals[0] = "Уменьшить шаг редактирования";
    strings["Toggle edit mode##sggc"].plurals[0] = "Переключить режим редактирования";
    strings["Metronome##sggc"].plurals[0] = "Метроном";
    strings["Toggle repeat pattern##sggc"].plurals[0] = "Переключить режим зацикливания паттерна";
    strings["Follow orders##sggc"].plurals[0] = "След. за воспр. в матр. патт.";
    strings["Follow pattern##sggc"].plurals[0] = "След. за воспр. в патт.";
    strings["Toggle full-screen##sggc"].plurals[0] = "Перключить полноэкранный режим";
    strings["Request voice from TX81Z##sggc"].plurals[0] = "Запросить канал у TX81Z";
    strings["Panic##sggc"].plurals[0] = "Паника";
    strings["Clear song data##sggc"].plurals[0] = "Удалить данные трека";

    strings["Edit Controls##sggc"].plurals[0] = "Редактирование";
    strings["Orders##sggc"].plurals[0] = "Матрица паттернов";
    strings["Instrument List##sggc"].plurals[0] = "Список инструментов";
    strings["Instrument Editor##sggc"].plurals[0] = "Редактор инструментов";
    strings["Song Information##sggc"].plurals[0] = "Информация о треке";
    strings["Speed##sggc"].plurals[0] = "Скорость";
    strings["Pattern##sggc"].plurals[0] = "Паттерны";
    strings["Wavetable List##sggc"].plurals[0] = "Список волновых таблиц";
    strings["Wavetable Editor##sggc"].plurals[0] = "Редактор волновых таблиц";
    strings["Sample List##sggc"].plurals[0] = "Список сэмплов";
    strings["Sample Editor##sggc"].plurals[0] = "Редактор сэмплов";
    strings["About##sggc"].plurals[0] = "О программе";
    strings["Settings##sggc"].plurals[0] = "Настройки";
    strings["Mixer##sggc"].plurals[0] = "Микшер";
    strings["Debug Menu##sggc"].plurals[0] = "Отладка";
    strings["Oscilloscope (master)##sggc"].plurals[0] = "Осциллограф";
    strings["Volume Meter##sggc"].plurals[0] = "Измеритель громкости";
    strings["Statistics##sggc"].plurals[0] = "Статистика";
    strings["Compatibility Flags##sggc"].plurals[0] = "Флаги совместимости";
    strings["Piano##sggc"].plurals[0] = "Клавиатура пианино";
    strings["Song Comments##sggc"].plurals[0] = "Комментарии трека";
    strings["Channels##sggc"].plurals[0] = "Каналы";
    strings["Pattern Manager##sggc"].plurals[0] = "Менеджер паттернов";
    strings["Chip Manager##sggc"].plurals[0] = "Менеджер чипов";
    strings["Register View##sggc"].plurals[0] = "Просмотр регистров";
    strings["Log Viewer##sggc"].plurals[0] = "Просмотр логов";
    strings["Effect List##sggc"].plurals[0] = "Список эффектов";
    strings["Oscilloscope (per-channel)##sggc"].plurals[0] = "Осциллографы (для отдельных каналов)";
    strings["Subsongs##sggc"].plurals[0] = "Подпесни";
    strings["Find/Replace##sggc"].plurals[0] = "Найти/Заменить";
    strings["Clock##sggc"].plurals[0] = "Часы";
    strings["Grooves##sggc"].plurals[0] = "Ритм-паттерны";
    strings["Oscilloscope (X-Y)##sggc"].plurals[0] = "Осциллограф (X-Y)";

    strings["Collapse/expand current window##sggc"].plurals[0] = "Свернуть/развернуть текущее окно";
    strings["Close current window##sggc"].plurals[0] = "Закрыть текущее окно";

    strings["---Pattern##sggc"].plurals[0] = "---Pattern";
    strings["Transpose (+1)##sggc"].plurals[0] = "Транспонировать (+1)";
    strings["Transpose (-1)##sggc"].plurals[0] = "Транспонировать (-1)";
    strings["Transpose (+1 octave)##sggc"].plurals[0] = "Транспонировать (+1 октава)";
    strings["Transpose (-1 octave)##sggc"].plurals[0] = "Транспонировать (-1 октава)";
    strings["Increase values (+1)##sggc"].plurals[0] = "Увеличить значения (+1)";
    strings["Increase values (-1)##sggc"].plurals[0] = "Уменьшить значения (-1)";
    strings["Increase values (+16)##sggc"].plurals[0] = "Увеличить значения (+16)";
    strings["Increase values (-16)##sggc"].plurals[0] = "Уменьшить значения (-16)";
    strings["Select all##sggc0"].plurals[0] = "Выбрать всё";
    strings["Cut##sggc0"].plurals[0] = "Вырезать";
    strings["Copy##sggc0"].plurals[0] = "Копировать";
    strings["Paste##sggc0"].plurals[0] = "Вставить";
    strings["Paste Mix (foreground)##sggc"].plurals[0] = "Вставить поверх";
    strings["Paste Mix (background)##sggc"].plurals[0] = "Вставить поверх (с заменой существующего)";
    strings["Paste Flood##sggc"].plurals[0] = "Вставить с цикл. повт. буфера (до конца патт.)";
    strings["Paste Overflow##sggc"].plurals[0] = "Вставить (с возможным переходом в след. паттерн)";
    strings["Move cursor up##sggc"].plurals[0] = "Курсор вверх";
    strings["Move cursor down##sggc"].plurals[0] = "Курсор вниз";
    strings["Move cursor left##sggc"].plurals[0] = "Курсор влево";
    strings["Move cursor right##sggc"].plurals[0] = "Курсор вправо";
    strings["Move cursor up by one (override Edit Step)##sggc"].plurals[0] = "Курсор вверх на один шаг (игнорировать шаг редактирования)";
    strings["Move cursor down by one (override Edit Step)##sggc"].plurals[0] = "Курсор вниз на один шаг (игнорировать шаг редактирования)";
    strings["Move cursor to previous channel##sggc"].plurals[0] = "Сдвинуть курсор на предыдущий канал";
    strings["Move cursor to next channel##sggc"].plurals[0] = "Сдвинуть курсор на следующий канал";
    strings["Move cursor to next channel (overflow)##sggc"].plurals[0] = "Сдвинуть курсор на предыдущий канал (с переполнением)";
    strings["Move cursor to previous channel (overflow)##sggc"].plurals[0] = "Сдвинуть курсор на следующий канал (с переполнением)";
    strings["Move cursor to beginning of pattern##sggc"].plurals[0] = "Сдвинуть курсор в начало паттерна";
    strings["Move cursor to end of pattern##sggc"].plurals[0] = "Сдвинуть курсор в конец паттерна";
    strings["Move cursor up (coarse)##sggc"].plurals[0] = "Курсор вверх (грубо)";
    strings["Move cursor down (coarse)##sggc"].plurals[0] = "Курсор вниз (грубо)";
    strings["Expand selection upwards##sggc"].plurals[0] = "Расширить выделенную область вверх";
    strings["Expand selection downwards##sggc"].plurals[0] = "Расширить выделенную область вниз";
    strings["Expand selection to the left##sggc"].plurals[0] = "Расширить выделенную область влево";
    strings["Expand selection to the right##sggc"].plurals[0] = "Расширить выделенную область вправо";
    strings["Expand selection upwards by one (override Edit Step)##sggc"].plurals[0] = "Расширить выделенную область вверх (игнорировать шаг редактирования)";
    strings["Expand selection downwards by one (override Edit Step)##sggc"].plurals[0] = "Расширить выделенную область вниз (игнорировать шаг редактирования)";
    strings["Expand selection to beginning of pattern##sggc"].plurals[0] = "Расширить выделенную область до начала паттерна";
    strings["Expand selection to end of pattern##sggc"].plurals[0] = "Расширить выделенную область до конца паттерна";
    strings["Expand selection upwards (coarse)##sggc"].plurals[0] = "Расширить выделенную область вверх (грубо)";
    strings["Expand selection downwards (coarse)##sggc"].plurals[0] = "Расширить выделенную область вниз (грубо)";
    strings["Delete##sggc"].plurals[0] = "Удалить";
    strings["Pull delete##sggc"].plurals[0] = "Удалить с подтягиванием следующих строк";
    strings["Insert##sggc"].plurals[0] = "Вставить с сдвигом строк вниз";
    strings["Mute channel at cursor##sggc"].plurals[0] = "Заглушить выделенный канал";
    strings["Solo channel at cursor##sggc"].plurals[0] = "Соло выделенного канала";
    strings["Unmute all channels##sggc"].plurals[0] = "Включить все каналы";
    strings["Go to next order##sggc"].plurals[0] = "Перейти на следующую строку матрицы паттернов";
    strings["Go to previous order##sggc"].plurals[0] = "Перейти на предыдущую строку матрицы паттернов";
    strings["Collapse channel at cursor##sggc"].plurals[0] = "Сжать текущий канал";
    strings["Increase effect columns##sggc"].plurals[0] = "Добавить столбец эффектов";
    strings["Decrease effect columns##sggc"].plurals[0] = "Убрать столбец эффектов";
    strings["Interpolate##sggc"].plurals[0] = "Интерполировать";
    strings["Fade##sggc"].plurals[0] = "Затухание/градиент";
    strings["Invert values##sggc"].plurals[0] = "Инвертировать параметры";
    strings["Flip selection##sggc"].plurals[0] = "Перевернуть выделенную область";
    strings["Collapse rows##sggc"].plurals[0] = "Сжать строки";
    strings["Expand rows##sggc"].plurals[0] = "Расширить строки";
    strings["Collapse pattern##sggc"].plurals[0] = "Сжать паттерн";
    strings["Expand pattern##sggc"].plurals[0] = "Расширить паттерн";
    strings["Collapse song##sggc"].plurals[0] = "Сжать трек";
    strings["Expand song##sggc"].plurals[0] = "Расширить трек";
    strings["Set note input latch##sggc"].plurals[0] = "Задать буфер ввода для нот";
    strings["Change mobile scroll mode##sggc"].plurals[0] = "Переключить режим мобильной прокрутки";
    strings["Clear note input latch##sggc"].plurals[0] = "Очистить буфер ввода для нот";

    strings["---Instrument list##sggc"].plurals[0] = "---Instrument list";
    strings["Add##sggc0"].plurals[0] = "Добавить";
    strings["Duplicate##sggc0"].plurals[0] = "Клонировать";
    strings["Open##sggc0"].plurals[0] = "Открыть";
    strings["Open (replace current)##sggc0"].plurals[0] = "Открыть (с заменой выделенного)";
    strings["Save##sggc0"].plurals[0] = "Сохранить";
    strings["Export (.dmp)##sggc"].plurals[0] = "Экспорт (.dmp)";
    strings["Move up##sggc0"].plurals[0] = "Сдвинуть вверх";
    strings["Move down##sggc0"].plurals[0] = "Сдвинуть вниз";
    strings["Delete##sggc0"].plurals[0] = "Удалить";
    strings["Edit##sggc0"].plurals[0] = "Редактировать";
    strings["Cursor up##sggc0"].plurals[0] = "Курсор вверх";
    strings["Cursor down##sggc0"].plurals[0] = "Курсор вниз";
    strings["Toggle folders/standard view##sggc0"].plurals[0] = "Переключиться между видом с разбиением по папкам и обычным видом";

    strings["---Wavetable list##sggc"].plurals[0] = "---Wavetable list";
    strings["Add##sggc1"].plurals[0] = "Добавить";
    strings["Duplicate##sggc1"].plurals[0] = "Клонировать";
    strings["Open##sggc1"].plurals[0] = "Открыть";
    strings["Open (replace current)##sggc1"].plurals[0] = "Открыть (с заменой выделенной)";
    strings["Save##sggc1"].plurals[0] = "Сохранить";
    strings["Save (.dmw)##sggc"].plurals[0] = "Сохранить (.dmw)";
    strings["Save (raw)##sggc0"].plurals[0] = "Сохранить (сырые данные)";
    strings["Move up##sggc1"].plurals[0] = "Сдвинуть вверх";
    strings["Move down##sggc1"].plurals[0] = "Сдвинуть вниз";
    strings["Delete##sggc1"].plurals[0] = "Удалить";
    strings["Edit##sggc1"].plurals[0] = "Редактировать";
    strings["Cursor up##sggc1"].plurals[0] = "Курсор вверх";
    strings["Cursor down##sggc1"].plurals[0] = "Курсор вниз";
    strings["Toggle folders/standard view##sggc1"].plurals[0] = "Переключиться между видом с разбиением по папкам и обычным видом";

    strings["---Sample list##sggc"].plurals[0] = "---Sample list";
    strings["Add##sggc2"].plurals[0] = "Добавить";
    strings["Duplicate##sggc2"].plurals[0] = "Клонировать";
    strings["Open##sggc2"].plurals[0] = "Открыть";
    strings["Open (replace current)##sggc2"].plurals[0] = "Открыть (с заменой выделенного)";
    strings["Import raw data##sggc"].plurals[0] = "Импорт сырых данных";
    strings["Import raw data (replace current)##sggc"].plurals[0] = "Импорт сырых данных (с заменой выделенного)";
    strings["Save##sggc2"].plurals[0] = "Сохранить";
    strings["Save (raw)##sggc1"].plurals[0] = "Сохранить (сырые данные)";
    strings["Move up##sggc2"].plurals[0] = "Сдвинуть вверх";
    strings["Move down##sggc2"].plurals[0] = "Сдвинуть вниз";
    strings["Delete##sggc2"].plurals[0] = "Удалить";
    strings["Edit##sggc2"].plurals[0] = "Редактировать";
    strings["Cursor up##sggc2"].plurals[0] = "Курсор вверх";
    strings["Cursor down##sggc2"].plurals[0] = "Курсор вниз";
    strings["Preview##sggc"].plurals[0] = "Превью";
    strings["Stop preview##sggc"].plurals[0] = "Остановить превью";
    strings["Make me a drum kit##sggc"].plurals[0] = "Сделай мне набор ударных";
    strings["Toggle folders/standard view##sggc2"].plurals[0] = "Переключиться между видом с разбиением по папкам и обычным видом";

    strings["---Sample editor##sggc"].plurals[0] = "---Sample editor";
    strings["Edit mode: Select##sggc"].plurals[0] = "Режим редактирования: выделение";
    strings["Edit mode: Draw##sggc"].plurals[0] = "Режим редактирования: рисование";
    strings["Cut##sggc1"].plurals[0] = "Вырезать";
    strings["Copy##sggc1"].plurals[0] = "Копировать";
    strings["Paste##sggc1"].plurals[0] = "Вставить";
    strings["Paste replace##sggc"].plurals[0] = "Вставить с заменой";
    strings["Paste mix##sggc"].plurals[0] = "Вставить со смешением";
    strings["Select all##sggc1"].plurals[0] = "Выбрать всё";
    strings["Resize##sggc"].plurals[0] = "Изменить размер";
    strings["Resample##sggc"].plurals[0] = "Изменить частоту дискретизации";
    strings["Amplify##sggc"].plurals[0] = "Усилить";
    strings["Normalize##sggc"].plurals[0] = "Нормализовать";
    strings["Fade in##sggc"].plurals[0] = "Плавное нарастание";
    strings["Fade out##sggc"].plurals[0] = "Плавное затухание";
    strings["Apply silence##sggc"].plurals[0] = "Применить тишину";
    strings["Insert silence##sggc"].plurals[0] = "Вставить тишину";
    strings["Delete##sggc3"].plurals[0] = "Удалить";
    strings["Trim##sggc"].plurals[0] = "Обрезать";
    strings["Reverse##sggc"].plurals[0] = "Реверс";
    strings["Invert##sggc"].plurals[0] = "Инверсия";
    strings["Signed/unsigned exchange##sggc"].plurals[0] = "Знаковый <-> беззнаковый";
    strings["Apply filter##sggc"].plurals[0] = "Применить фильтр";
    strings["Crossfade loop points##sggc"].plurals[0] = "Сделать плавный переход между началом и концом зацикленной части";
    strings["Preview sample##sggc"].plurals[0] = "Превью";
    strings["Stop sample preview##sggc"].plurals[0] = "Остановить превью";
    strings["Zoom in##sggc"].plurals[0] = "Увеличить масштаб";
    strings["Zoom out##sggc"].plurals[0] = "Уменьшить масштаб";
    strings["Toggle auto-zoom##sggc"].plurals[0] = "Переключить авто-увеличение";
    strings["Create instrument from sample##sggc"].plurals[0] = "Создать инструмент из сэмпла";
    strings["Set loop to selection##sggc"].plurals[0] = "Зациклить выделенную часть";
    strings["Create wavetable from selection##sggc"].plurals[0] = "Создать волновую таблицу из выделенной части";

    strings["---Orders##sggc"].plurals[0] = "---Orders";
    strings["Previous order##sggc"].plurals[0] = "Предыдущая строка матрицы паттернов";
    strings["Next order##sggc"].plurals[0] = "Следующая строка матрицы паттернов";
    strings["Cursor left##sggc"].plurals[0] = "Курсор влево";
    strings["Cursor right##sggc"].plurals[0] = "Курсор вправо";
    strings["Increase value##sggc"].plurals[0] = "Увеличить значение";
    strings["Decrease value##sggc"].plurals[0] = "Уменьшить значение";
    strings["Switch edit mode##sggc"].plurals[0] = "Переключить режим редактирования";
    strings["Toggle alter entire row##sggc"].plurals[0] = "Переключить режим изменения всей строки";
    strings["Add##sggc3"].plurals[0] = "Добавить";
    strings["Duplicate##sggc3"].plurals[0] = "Клонировать";
    strings["Deep clone##sggc"].plurals[0] = "Клонировать с выделением новых индексов";
    strings["Duplicate to end of song##sggc"].plurals[0] = "Клонировать в конец трека";
    strings["Deep clone to end of song##sggc"].plurals[0] = "Клонировать в конец трека с выделением новых индексов";
    strings["Remove##sggc"].plurals[0] = "Удалить";
    strings["Move up##sggc3"].plurals[0] = "Сдвинуть вверх";
    strings["Move down##sggc3"].plurals[0] = "Сдвинуть вниз";
    strings["Replay##sggc"].plurals[0] = "Воспроизвести";


    //src/gui/settings.cpp


    strings["<Use system font>##sgse0"].plurals[0] = "<Использовать системный шрифт>";
    strings["<Custom...>##sgse0"].plurals[0] = "<Внешний...>";
    strings["<Use system font>##sgse1"].plurals[0] = "<Использовать системный шрифт>";
    strings["<Custom...>##sgse1"].plurals[0] = "<Внешний...>";
    strings["<Use system font>##sgse2"].plurals[0] = "<Использовать системный шрифт>";
    strings["<Custom...>##sgse2"].plurals[0] = "<Внешний...>";
    strings["Mono##sgse0"].plurals[0] = "Моно";
    strings["Stereo##sgse"].plurals[0] = "Стерео";
    strings["What?##sgse0"].plurals[0] = "Что?";
    strings["Quadraphonic##sgse"].plurals[0] = "Евадрафонический";
    strings["What?##sgse1"].plurals[0] = "Что?";
    strings["5.1 Surround##sgse"].plurals[0] = "5.1 объёмный звук";
    strings["What?##sgse2"].plurals[0] = "Что?";
    strings["7.1 Surround##sgse"].plurals[0] = "7.1 объёмный звук";
    strings["High##sgse"].plurals[0] = "Высокое";
    strings["Low##sgse"].plurals[0] = "Низкое";
    strings["ASAP (C++ port)##sgse"].plurals[0] = "ASAP (портирован на C++)";
    strings["KIOCSOUND on /dev/tty1##sgse"].plurals[0] = "KIOCSOUND в /dev/tty1";
    strings["KIOCSOUND on standard output##sgse"].plurals[0] = "KIOCSOUND в стандартном выводе";
    strings["Disabled/custom##sgse0"].plurals[0] = "Выкл./пользовательский";
    strings["Two octaves (0 is C-4, F is D#5)##sgse"].plurals[0] = "Две октавы (0 = C-4, F = D#5)";
    strings["Raw (note number is value)##sgse"].plurals[0] = "Сырой ввод (номер ноты - само значение)";
    strings["Two octaves alternate (lower keys are 0-9, upper keys are A-F)##sgse"].plurals[0] = "Альтернативный ввод двух октав (нижние клавиши 0-9, верхние - A-F)";
    strings["Use dual control change (one for each nibble)##sgse0"].plurals[0] = "Использовать двойную смену значения контроллера (по одному на тетраду)";
    strings["Use 14-bit control change##sgse0"].plurals[0] = "Использовать 14-битную смену значения контроллера";
    strings["Use single control change (imprecise)##sgse0"].plurals[0] = "Использовать однократную смену значения контроллера (малая точность)";
    strings["Disabled/custom##sgse1"].plurals[0] = "Выкл./пользовательский";
    strings["Use dual control change (one for each nibble)##sgse1"].plurals[0] = "Использовать двойную смену значения контроллера (по одному на тетраду)";
    strings["Use 14-bit control change##sgse1"].plurals[0] = "Использовать 14-битную смену значения контроллера";
    strings["Use single control change (imprecise)##sgse1"].plurals[0] = "Использовать однократную смену значения контроллера (малая точность)";
    strings["--select--##sgse"].plurals[0] = "--выберите--";
    strings["Note Off##sgse"].plurals[0] = "Отпускание клавиши";
    strings["Note On##sgse"].plurals[0] = "Нажатие клавиши";
    strings["Aftertouch##sgse"].plurals[0] = "Давление на клавишу после нажатия";
    strings["Control##sgse"].plurals[0] = "Значение контроллера";
    strings["Program##sgse0"].plurals[0] = "Программа";
    strings["ChanPressure##sgse"].plurals[0] = "Одинаковое давление на все нажатые клавиши в одном канале";
    strings["Pitch Bend##sgse"].plurals[0] = "Смена высоты тона";
    strings["SysEx##sgse"].plurals[0] = "SysEx";
    strings["Instrument##sgse0"].plurals[0] = "Инструмент";
    strings["Volume##sgse0"].plurals[0] = "Громкость";
    strings["Effect 1 type##sgse"].plurals[0] = "Индекс эффекта №1";
    strings["Effect 1 value##sgse"].plurals[0] = "Параметр эффекта №1";
    strings["Effect 2 type##sgse"].plurals[0] = "Индекс эффекта №2";
    strings["Effect 2 value##sgse"].plurals[0] = "Параметр эффекта №2";
    strings["Effect 3 type##sgse"].plurals[0] = "Индекс эффекта №3";
    strings["Effect 3 value##sgse"].plurals[0] = "Параметр эффекта №3";
    strings["Effect 4 type##sgse"].plurals[0] = "Индекс эффекта №4";
    strings["Effect 4 value##sgse"].plurals[0] = "Параметр эффекта №4";
    strings["Effect 5 type##sgse"].plurals[0] = "Индекс эффекта №5";
    strings["Effect 5 value##sgse"].plurals[0] = "Параметр эффекта №5";
    strings["Effect 6 type##sgse"].plurals[0] = "Индекс эффекта №6";
    strings["Effect 6 value##sgse"].plurals[0] = "Параметр эффекта №6";
    strings["Effect 7 type##sgse"].plurals[0] = "Индекс эффекта №7";
    strings["Effect 7 value##sgse"].plurals[0] = "Параметр эффекта №7";
    strings["Effect 8 type##sgse"].plurals[0] = "Индекс эффекта №8";
    strings["Effect 8 value##sgse"].plurals[0] = "Параметр эффекта №8";

    strings["Press key...##sgse"].plurals[0] = "Нажмите клавишу...";
    strings["Settings###Settings"].plurals[0] = "Настройки###Settings";
    strings["Do you want to save your settings?##sgse"].plurals[0] = "Вы хотите сохранить свои настройки?";

    strings["General##sgse"].plurals[0] = "Основные";
    strings["Program##sgse1"].plurals[0] = "Программа";
    strings["Render backend##sgse"].plurals[0] = "Библиотека отрисовки";
    strings["you may need to restart Furnace for this setting to take effect.##sgse0"].plurals[0] = "возможно, вам потребуется перезапустить Furnace, чтобы эта настрока применилась.";
    strings["Render driver##sgse"].plurals[0] = "Драйвер отрисовки";
    strings["Automatic##sgse0"].plurals[0] = "Выбирать автоматически";
    strings["Automatic##sgse1"].plurals[0] = "Выбирать автоматически";
    strings["you may need to restart Furnace for this setting to take effect.##sgse1"].plurals[0] = "возможно, вам потребуется перезапустить Furnace, чтобы эта настрока применилась.";
    strings["Late render clear##sgse"].plurals[0] = "Запаздывающая очистка буфера отрисовщика";
    strings["calls rend->clear() after rend->present(). might reduce UI latency by one frame in some drivers.##sgse"].plurals[0] = "вызывает rend->clear() после rend->present(). может устранить запаздывание отрисовки интерфейса на один кадр для некоторых драйверов.";
    strings["Power-saving mode##sgse"].plurals[0] = "Режим энергосбережения";
    strings["saves power by lowering the frame rate to 2fps when idle.\nmay cause issues under Mesa drivers!##sgse"].plurals[0] = "уменьшает энергопотребление при помощи уменьшения частоты отрисовки до двух кадров в секунду в режиме ожидания.\nможет приводить к проблемам на драйверах Mesa!";
    strings["Disable threaded input (restart after changing!)##sgse"].plurals[0] = "Отключить обработку нажатий для превью инструмента в отдельном потоке (перезагрузите программу после изменения!)";
    strings["threaded input processes key presses for note preview on a separate thread (on supported platforms), which reduces latency.\nhowever, crashes have been reported when threaded input is on. enable this option if that is the case.##sgse"].plurals[0] = "обработка нажатий клавиш для превью инструмента происходит в отдельном потоке (на поддерживаемых платформах), что позволяет уменьшить задержку ввода.\nтем не менее, есть сообщения о вылетах программы при выключённой настройке. включите её, если у вас программа вылетает.";
    strings["Enable event delay##sgse"].plurals[0] = "Включить задержку событий";
    strings["may cause issues with high-polling-rate mice when previewing notes.##sgse"].plurals[0] = "может привести к проблемам во время превью инструмента, если подключена мышь с большой частотой обновления.";
    strings["Per-channel oscilloscope threads##sgse"].plurals[0] = "Потоки исполнения осциллографов для отдельных каналов";
    strings["you're being silly, aren't you? that's enough.##sgse"].plurals[0] = "может, хватит уже хернёй страдать? этого достаточно.";
    strings["what are you doing? stop!##sgse"].plurals[0] = "ты чё делаешь? хватит!";
    strings["it is a bad idea to set this number higher than your CPU core count (%d)!##sgse"].plurals[0] = "не рекомендуется выставлять здесь значение, большее количества ядер вашего ЦП (%d)!";
    strings["File##sgse"].plurals[0] = "Файл";
    strings["Use system file picker##sgse"].plurals[0] = "Использовать диалоговое окно выбора файлов ОС";
    strings["Number of recent files##sgse"].plurals[0] = "Количество недавних файлов";
    strings["Compress when saving##sgse"].plurals[0] = "Сжимать сохраняемые файлы";
    strings["use zlib to compress saved songs.##sgse"].plurals[0] = "использовать библиотеку zlib для сжатия сохраняемых модулей.";
    strings["Save unused patterns##sgse"].plurals[0] = "Сохранять неиспользуемые паттерны";
    strings["Use new pattern format when saving##sgse"].plurals[0] = "Использовать новый формат сохранения паттернов";
    strings["use a packed format which saves space when saving songs.\ndisable if you need compatibility with older Furnace and/or tools\nwhich do not support this format.##sgse"].plurals[0] = "использовать сжатый формат сохранения паттернов, что позволяет уменьшить размер файла с модулем.\nотключите, если нужна совместимость со старыми версиями Furnace и/или другими программами,\nкоторые не поддерживают новый формат.";
    strings["Don't apply compatibility flags when loading .dmf##sgse"].plurals[0] = "Не применять флаги совместимости при загрузке .dmf";
    strings["do not report any issues arising from the use of this option!##sgse"].plurals[0] = "не жалуйтесь на проблемы, которые возникнут после включения этой настройки!";
    strings["Play after opening song:##sgse"].plurals[0] = "Проигрывание модуля после его загрузки:";
    strings["No##pol0"].plurals[0] = "Нет##pol0";
    strings["Only if already playing##pol1"].plurals[0] = "Только если до этого уже играл##pol1";
    strings["Yes##pol0"].plurals[0] = "Да##pol0";
    strings["Audio export loop/fade out time:##sgse"].plurals[0] = "Количество циклов проигрывания и время затухания при экспорте аудио:";
    strings["Set to these values on start-up:##fot0"].plurals[0] = "Выставить эти значения при запуске:##fot0";
    strings["Loops##sgse"].plurals[0] = "Циклы";
    strings["Fade out (seconds)##sgse"].plurals[0] = "Затухание (в секундах)";
    strings["Remember last values##fot1"].plurals[0] = "Запоминать предыдущие значения##fot1";
    strings["Store instrument name in .fui##sgse"].plurals[0] = "Сохранять название инструмента в файле .fui";
    strings["when enabled, saving an instrument will store its name.\nthis may increase file size.##sgse"].plurals[0] = "При включении имя инструмента будет сохраняться в файле.\nэто может увеличить размер файла.";
    strings["Load instrument name from .fui##sgse"].plurals[0] = "Загружать имя инструмента из файла .fui";
    strings["when enabled, loading an instrument will use the stored name (if present).\notherwise, it will use the file name.##sgse"].plurals[0] = "При включении имя инструмента будет загружаться из файла (при наличии имени в файле).\nВ противном случае будет использоваться имя файла.";
    strings["New Song##sgse"].plurals[0] = "Новая композиция";
    strings["Initial system:##sgse"].plurals[0] = "Система по умолчанию:";
    strings["Current system##sgse"].plurals[0] = "Текущая";
    strings["Randomize##sgse"].plurals[0] = "Выбрать случайно";
    strings["Reset to defaults##sgse"].plurals[0] = "Устан. по умолчанию";
    strings["Name##sgse"].plurals[0] = "Название";
    strings["Invert##sgse0"].plurals[0] = "Обр.";
    strings["Invert##sgse1"].plurals[0] = "Обр.";
    strings["Volume##sgse1"].plurals[0] = "Громкость";
    strings["Panning##sgse"].plurals[0] = "Панорамирование";
    strings["Front/Rear##sgse"].plurals[0] = "Передн./задн.";
    strings["Configure##sgse"].plurals[0] = "Настроить";
    strings["When creating new song:##sgse"].plurals[0] = "При создании новой композиции:";
    strings["Display system preset selector##NSB0"].plurals[0] = "Отобразить окно выбора пресета системы##NSB0";
    strings["Start with initial system##NSB1"].plurals[0] = "Начать с системы по умолчанию##NSB1";
    strings["Default author name##sgse"].plurals[0] = "Имя автора по умолчанию";
    strings["Start-up##sgse"].plurals[0] = "Запуск";
    strings["Disable fade-in during start-up##sgse"].plurals[0] = "Отключить плавное появление интерфейса при запуске";
    strings["About screen party time##sgse"].plurals[0] = "Вечеринка на экране \"О программе\"";
    strings["Warning: may cause epileptic seizures.##sgse"].plurals[0] = "Внимание: может вызвать эпилептические приступы.";
    strings["Behavior##sgse"].plurals[0] = "Поведение программы";
    strings["New instruments are blank##sgse"].plurals[0] = "Пустые новые инструменты";
    strings["Language##sgse"].plurals[0] = "Язык";
    strings["GUI language##sgse"].plurals[0] = "Язык интерфейса";
    strings["Audio##sgse"].plurals[0] = "Аудио";
    strings["Output##sgse"].plurals[0] = "Вывод";
    strings["Backend##sgse"].plurals[0] = "Интерфейс";
    strings["Driver##sgse"].plurals[0] = "Драйвер";
    strings["Automatic##sgse2"].plurals[0] = "Автоматически";
    strings["you may need to restart Furnace for this setting to take effect.##sgse2"].plurals[0] = "возможно, вам придётся перезапустить Furnace для применения настройки.";
    strings["Device##sgse"].plurals[0] = "Устройство вывода";
    strings["<click on OK or Apply first>##sgse"].plurals[0] = "<сначала нажмите на кнопки \"ОК\" или \"Применить\">";
    strings["ALERT - TRESPASSER DETECTED##sgse"].plurals[0] = "ВНИМАНИЕ - ОБНАРУЖЕН НАРУШИТЕЛЬ";
    strings["you have been arrested for trying to engage with a disabled combo box.##sgse"].plurals[0] = "вы были арестованы за попытку взаимодействия с выключенным выпадающим списком.";
    strings["<System default>##sgse0"].plurals[0] = "<По умолчанию>";
    strings["<System default>##sgse1"].plurals[0] = "<По умолчанию>";
    strings["Sample rate##sgse"].plurals[0] = "Частота дискретизации";
    strings["Outputs##sgse"].plurals[0] = "Выводы";
    strings["Channels##sgse"].plurals[0] = "Число каналов";
    strings["What?##sgse3"].plurals[0] = "Что?";
    strings["Buffer size##sgse"].plurals[0] = "Размер буфера";
    strings["%d (latency: ~%.1fms)##sgse"].plurals[0] = "%d (задержка: ~%.1f мс)";
    strings["Multi-threaded (EXPERIMENTAL)##sgse"].plurals[0] = "Многопоточность (ЭКСПЕРИМЕНТАЛЬНАЯ)";
    strings["runs chip emulation on separate threads.\nmay increase performance when using heavy emulation cores.\n\nwarnings:\n- experimental!\n- only useful on multi-chip songs.##sgse"].plurals[0] = "исполняет эмуляторы чипов в отдельных потоках.\nможет повысить производительность при использовании тяжёлых эмуляторов.\n\nвнимание:\n- экспериментальная функция!\n- полезна только для композиций, использующих несколько чипов.";
    strings["Number of threads##sgse"].plurals[0] = "Количество потоков";
    strings["that's the limit!##sgse"].plurals[0] = "это предел!";
    strings["it is a VERY bad idea to set this number higher than your CPU core count (%d)!##sgse"].plurals[0] = "это ОЧЕНЬ плохая идея - устанавливать это значение большим, чем колчество ядер ЦП (%d)!";
    strings["Low-latency mode##sgse"].plurals[0] = "Режим малой задержки";
    strings["reduces latency by running the engine faster than the tick rate.\nuseful for live playback/jam mode.\n\nwarning: only enable if your buffer size is small (10ms or less).##sgse"].plurals[0] = "уменьшает задержку, исполняя код движка трекера быстрее, чем указано в настройках.\nполезно для режима исполнения в реальном времени.\n\nвнимание: включайте только если размер вашего аудиобуфера мал (10 мс или меньше).";
    strings["Force mono audio##sgse"].plurals[0] = "Принудительно сводить в моно";
    strings["Exclusive mode##sgse"].plurals[0] = "Исключительный режим";
    strings["want: %d samples @ %.0fHz (%d %s)##sgse"].plurals[0] = "запрошено: %d сэмплов @ %.0f Гц (%d %s)";
    strings["channel##sgse"].plurals[0] = "канал";
    strings["channel##sgse"].plurals[1] = "канала";
    strings["channel##sgse"].plurals[2] = "каналов";
    strings["got: %d samples @ %.0fHz (%d %s)##sgse"].plurals[0] = "получено: %d сэмплов @ %.0f Гц (%d %s)";
    strings["Mixing##sgse"].plurals[0] = "Микширование";
    strings["Quality##sgse"].plurals[0] = "Качество";
    strings["Software clipping##sgse"].plurals[0] = "Программное ограничение сигнала";
    strings["DC offset correction##sgse"].plurals[0] = "Коррекция смещения пост. составляющей";
    strings["Metronome##sgse"].plurals[0] = "Метроном";
    strings["Volume##sgse2"].plurals[0] = "Громкость метронома";
    strings["Sample preview##sgse"].plurals[0] = "Превью сэмпла";
    strings["Volume##sgse3"].plurals[0] = "Громкость";
    strings["MIDI##sgse"].plurals[0] = "MIDI";
    strings["MIDI input##sgse0"].plurals[0] = "Ввод MIDI";
    strings["MIDI input##sgse1"].plurals[0] = "MIDI вход";
    strings["<disabled>##sgse0"].plurals[0] = "<выкл.>";
    strings["<disabled>##sgse1"].plurals[0] = "<выкл.>";
    strings["Re-scan MIDI devices##sgse"].plurals[0] = "Перезап. скан. для обнаруж. MIDI-устройств";
    strings["Note input##sgse0"].plurals[0] = "Ввод нот";
    strings["Velocity input##sgse"].plurals[0] = "Ввод скорости нажатия";
    strings["Map MIDI channels to direct channels##sgse"].plurals[0] = "Привязать MIDI-каналы к прямым каналам";
    strings["Program change pass-through##sgse"].plurals[0] = "Пропускать на выход сообщения об изменении программы";
    strings["Map Yamaha FM voice data to instruments##sgse"].plurals[0] = "Привязать данные тембров Yamaha FM к инструментам";
    strings["Program change is instrument selection##sgse"].plurals[0] = "Смена программы = выбор инструмента";
    strings["Listen to MIDI clock##sgse"].plurals[0] = "Следить за тактовой частотой MIDI";
    strings["Listen to MIDI time code##sgse"].plurals[0] = "Следить за временным кодом MIDI";
    strings["Value input style##sgse0"].plurals[0] = "Стиль ввода значений";
    strings["Value input style##sgse1"].plurals[0] = "Стиль ввода значений";
    strings["Control##valueCCS"].plurals[0] = "Управление##valueCCS";
    strings["CC of upper nibble##valueCC1"].plurals[0] = "Управляющая команда для верхней тетрады##valueCC1";
    strings["MSB CC##valueCC1"].plurals[0] = "Управл. ком. для старш. бита##valueCC1";
    strings["CC of lower nibble##valueCC2"].plurals[0] = "Управляющая команда для нижней тетрады##valueCC2";
    strings["LSB CC##valueCC2"].plurals[0] = "Управл. ком. для младш. бита##valueCC2";
    strings["Per-column control change##sgse"].plurals[0] = "Изменение управления для каждого столбца";
    strings["Control##valueCCS"].plurals[0] = "Управление##valueCCS";
    strings["CC of upper nibble##valueCC1"].plurals[0] = "Управляющая команда для верхней тетрады##valueCC1";
    strings["MSB CC##valueCC1"].plurals[0] = "Управл. ком. для старш. бита##valueCC1";
    strings["CC of lower nibble##valueCC2"].plurals[0] = "Управляющая команда для нижней тетрады##valueCC2";
    strings["LSB CC##valueCC2"].plurals[0] = "Управл. ком. для младш. бита##valueCC2";
    strings["Volume curve##sgse0"].plurals[0] = "Кривая громкости";
    strings["Volume curve##sgse1"].plurals[0] = "Кривая громкости";
    strings["Actions:##sgse"].plurals[0] = "Действия:";
    strings["(learning! press a button or move a slider/knob/something on your device.)##sgse"].plurals[0] = "(обучение! нажмите кнопку или подвигайте что-то на вашем устройстве.)";
    strings["Type##sgse0"].plurals[0] = "Тип";
    strings["Channel##sgse0"].plurals[0] = "Канал";
    strings["Note/Control##sgse"].plurals[0] = "Нота/управление";
    strings["Velocity/Value##sgse"].plurals[0] = "Скор. наж./парам.";
    strings["Action##sgse"].plurals[0] = "Действие";
    strings["Any##sgse0"].plurals[0] = "Любой";
    strings["Any##sgse1"].plurals[0] = "Любая";
    strings["Any##sgse2"].plurals[0] = "Любая";
    strings["Any##sgse3"].plurals[0] = "Любое";
    strings["--none--##sgse"].plurals[0] = "--нет--";
    strings["waiting...##BLearn"].plurals[0] = "ожидание...##BLearn";
    strings["Learn##BLearn"].plurals[0] = "Запомнить##BLearn";
    strings["MIDI output##sgse0"].plurals[0] = "MIDI вывод";
    strings["MIDI output##sgse1"].plurals[0] = "Устройство вывода MIDI";
    strings["<disabled>##sgse2"].plurals[0] = "<выкл.>";
    strings["<disabled>##sgse3"].plurals[0] = "<выкл.>";
    strings["Output mode:##sgse"].plurals[0] = "Режим вывода:";
    strings["Off (use for TX81Z)##sgse"].plurals[0] = "Выкл. (используйте для TX81Z)";
    strings["Melodic##sgse"].plurals[0] = "Мелодия";
    //strings["Light Show (use for Launchpad)##sgse"].plurals[0] = "Light Show (use for Launchpad)";
    strings["Send Program Change##sgse"].plurals[0] = "Посылать команду изменения программы";
    strings["Send MIDI clock##sgse"].plurals[0] = "Посылать тактовую частоту MIDI";
    strings["Send MIDI timecode##sgse"].plurals[0] = "Посылать временной код MIDI";
    strings["Timecode frame rate:##sgse"].plurals[0] = "Частота посылок временного кода:";
    strings["Closest to Tick Rate##sgse"].plurals[0] = "Ближайшая к частоте движка трекера";
    strings["Film (24fps)##sgse"].plurals[0] = "Киноплёнка (24 кадра в секунду)";
    strings["PAL (25fps)##sgse"].plurals[0] = "PAL (25 кадров в секунду)";
    strings["NTSC drop (29.97fps)##sgse"].plurals[0] = "NTSC с выпадением кадров (29.97 кадров в секунду)";
    strings["NTSC non-drop (30fps)##sgse"].plurals[0] = "NTSC без выпадения кадров (30 кадров в секунду)";
    strings["Emulation##sgse"].plurals[0] = "Эмуляция";
    strings["Cores##sgse"].plurals[0] = "Ядра эмуляции";
    strings["System##sgse"].plurals[0] = "Система/чип";
    strings["Playback Core(s)##sgse"].plurals[0] = "Ядро(-а) воспроизведения";
    strings["used for playback##sgse"].plurals[0] = "используется(-ются) для воспроизведения";
    strings["Render Core(s)##sgse"].plurals[0] = "Ядро(-а) рендера";
    strings["used in audio export##sgse"].plurals[0] = "используется(-ются) при рендере звука в аудиофайл";
    strings["PC Speaker strategy##sgse"].plurals[0] = "Взаимодействие с PC Speaker";
    strings["Sample ROMs:##sgse"].plurals[0] = "Образы ROM сэмплов:";
    strings["OPL4 YRW801 path##sgse"].plurals[0] = "Путь к OPL4 YRW801";
    strings["MultiPCM TG100 path##sgse"].plurals[0] = "Путь к MultiPCM TG100";
    strings["MultiPCM MU5 path##sgse"].plurals[0] = "Путь к MultiPCM MU5";
    strings["Keyboard##sgse0"].plurals[0] = "Клавиатура";
    strings["Keyboard##sgse1"].plurals[0] = "Привязка клавиш";
    strings["Import##sgse0"].plurals[0] = "Импорт";
    strings["Export##sgse0"].plurals[0] = "Экспорт";
    strings["Reset defaults##sgse0"].plurals[0] = "Сбросить до настроек по умолчанию";
    strings["Are you sure you want to reset the keyboard settings?##sgse"].plurals[0] = "Вы действительно хотите сбросить настройки привязки клавиш?";
    strings["Global hotkeys##sgse"].plurals[0] = "Глобальные горячие клавиши";
    strings["Window activation##sgse"].plurals[0] = "Активация окон";
    strings["Note input##sgse1"].plurals[0] = "Ввод нот";
    strings["Key##sgse"].plurals[0] = "Клавиша";
    strings["Type##sgse1"].plurals[0] = "Тип";
    strings["Value##sgse"].plurals[0] = "Значение";
    strings["Remove##sgse"].plurals[0] = "Убрать";
    strings["Macro release##SNType_%d"].plurals[0] = "\"Отпускание клавиши\" (только для макросов)##SNType_%d";
    strings["Note release##SNType_%d"].plurals[0] = "\"Отпускание клавиши\" (с включением фазы затухания огибающей)##SNType_%d";
    strings["Note off##SNType_%d"].plurals[0] = "\"Отпускание клавиши\" (резкое)##SNType_%d";
    strings["Note##SNType_%d"].plurals[0] = "Нота##SNType_%d";
    strings["Add...##sgse"].plurals[0] = "Добавить...";
    strings["Pattern##sgse0"].plurals[0] = "Паттерн";
    strings["Instrument list##sgse"].plurals[0] = "Список инструментов";
    strings["Wavetable list##sgse"].plurals[0] = "Список волновых таблиц";
    strings["Sample list##sgse"].plurals[0] = "Список сэмплов";
    strings["Orders##sgse0"].plurals[0] = "Матрица паттернов";
    strings["Sample editor##sgse"].plurals[0] = "Редактор сэмплов";
    strings["Interface##sgse0"].plurals[0] = "Интерфейс";
    strings["Layout##sgse"].plurals[0] = "Компоновка интерфейса";
    strings["Workspace layout:##sgse"].plurals[0] = "Расположение окон интерфейса:";
    strings["Import##sgse1"].plurals[0] = "Импорт";
    strings["Export##sgse1"].plurals[0] = "Экспорт";
    strings["Reset##sgse"].plurals[0] = "Сбросить";
    strings["Are you sure you want to reset the workspace layout?##sgse"].plurals[0] = "Вы действительно хотите сбросить компоновку окон интерфейса?";
    strings["Allow docking editors##sgse"].plurals[0] = "Разрешить стыковать окна редакторов";
    strings["Remember window position##sgse"].plurals[0] = "Запоминать положение окон";
    strings["remembers the window's last position on start-up.##sgse"].plurals[0] = "при запуске программы восстанавливает последнее положение каждого окна.";
    strings["Only allow window movement when clicking on title bar##sgse"].plurals[0] = "Разрешать перемещение окон только при нажатии на их полосу заголовка";
    strings["Center pop-up windows##sgse"].plurals[0] = "Центрировать всплывающие окна";
    strings["Play/edit controls layout:##sgse"].plurals[0] = "Компоновка управления вспроизведением/редактированием:";
    strings["Classic##ecl0"].plurals[0] = "Классическая##ecl0";
    strings["Compact##ecl1"].plurals[0] = "Компактная##ecl1";
    strings["Compact (vertical)##ecl2"].plurals[0] = "Компактная (вертикальная)##ecl2";
    strings["Split##ecl3"].plurals[0] = "С раздлением на два окна##ecl3";
    strings["Position of buttons in Orders:##sgse"].plurals[0] = "Позиция кнопок в редакторе матрицы паттернов:";
    strings["Top##obp0"].plurals[0] = "Сверху##obp0";
    strings["Left##obp1"].plurals[0] = "Слева##obp1";
    strings["Right##obp2"].plurals[0] = "Справа##obp2";
    strings["Mouse##sgse"].plurals[0] = "Мышь";
    strings["Double-click time (seconds)##sgse"].plurals[0] = "Время двойного нажатия (в секундах)";
    strings["Don't raise pattern editor on click##sgse"].plurals[0] = "Не поднимать редактор паттернов при нажатии";
    strings["Focus pattern editor when selecting instrument##sgse"].plurals[0] = "Переместить фокус на редактор паттернов при выборе инструмента";
    strings["Note preview behavior:##sgse"].plurals[0] = "Превью нот:";
    strings["Never##npb0"].plurals[0] = "Никогда##npb0";
    strings["When cursor is in Note column##npb1"].plurals[0] = "Когда курсор находится в столбце нот##npb1";
    strings["When cursor is in Note column or not in edit mode##npb2"].plurals[0] = "Когда курсор находится в столбце нот или не включён режим редактирования##npb2";
    strings["Always##npb3"].plurals[0] = "Всегда##npb3";
    strings["Allow dragging selection:##sgse"].plurals[0] = "Разрешить перемещение выделенного фрагмента:";
    strings["No##dms0"].plurals[0] = "Нет##dms0";
    strings["Yes##dms1"].plurals[0] = "Да##dms1";
    strings["Yes (while holding Ctrl only)##dms2"].plurals[0] = "Да (только при нажатой клавише Ctrl)##dms2";
    strings["Toggle channel solo on:##sgse"].plurals[0] = "Включать режим соло для канала:";
    strings["Right-click or double-click##soloA"].plurals[0] = "ПКМ или двойное нажатие##soloA";
    strings["Right-click##soloR"].plurals[0] = "ПКМ##soloR";
    strings["Double-click##soloD"].plurals[0] = "Двойное нажатие##soloD";
    strings["Double click selects entire column##sgse"].plurals[0] = "Двойное нажатие выделяет весь столбец";
    strings["Cursor behavior##sgse"].plurals[0] = "Поведение курсора";
    strings["Insert pushes entire channel row##sgse"].plurals[0] = "Клавиша Insert сдвигает паттерны на всех каналах";
    strings["Pull delete affects entire channel row##sgse"].plurals[0] = "Удаление с подтягиванием следующих строк сдвигает паттерны на всех каналах";
    strings["Push value when overwriting instead of clearing it##sgse"].plurals[0] = "Отодвинуть значение ячейки в соседнюю вместо удаления при перезаписи ячейки";
    strings["Effect input behavior:##sgse"].plurals[0] = "Ввод эффектов:";
    strings["Move down##eicb0"].plurals[0] = "перемещаться вниз##eicb0";
    strings["Move to effect value (otherwise move down)##eicb1"].plurals[0] = "Перепрыгнуть на параметр эффекта (иначе перемещаться вниз)##eicb1";
    strings["Move to effect value/next effect and wrap around##eicb2"].plurals[0] = "Перепрыгнуть на параметр эффекта/следующий эффект, в конце строки перепрыгнуть в начало строки эффектов##eicb2";
    strings["Delete effect value when deleting effect##sgse"].plurals[0] = "Удалять параметр эффекта при удалении эффекта";
    strings["Change current instrument when changing instrument column (absorb)##sgse"].plurals[0] = "Изменять выделенный инструмент при редактировании столбца инструмента";
    strings["Remove instrument value when inserting note off/release##sgse"].plurals[0] = "Удалять значение столбца инструмента при вводе ноты OFF/===";
    strings["Remove volume value when inserting note off/release##sgse"].plurals[0] = "Удалять значение столбца громкости при вводе ноты OFF/===";
    strings["Cursor movement##sgse"].plurals[0] = "Передвижение курсора";
    strings["Wrap horizontally:##sgse"].plurals[0] = "Переносить по горизонтали:";
    strings["No##wrapH0"].plurals[0] = "Нет##wrapH0";
    strings["Yes##wrapH1"].plurals[0] = "Да##wrapH1";
    strings["Yes, and move to next/prev row##wrapH2"].plurals[0] = "Да, и переходить на следующую/предыдущую строку##wrapH2";
    strings["Wrap vertically:##sgse"].plurals[0] = "Переносить по вертикали:";
    strings["No##wrapV0"].plurals[0] = "Нет##wrapV0";
    strings["Yes##wrapV1"].plurals[0] = "Да##wrapV1";
    strings["Yes, and move to next/prev pattern##wrapV2"].plurals[0] = "Да, и переходить на следующий/предыдущий паттерн##wrapV2";
    strings["Yes, and move to next/prev pattern (wrap around)##wrapV2"].plurals[0] = "Да, и переходить на следующий/предыдущий паттерн (с переносом в начало/конец)##wrapV2";
    strings["Cursor movement keys behavior:##sgse"].plurals[0] = "Передвижение курсора при помощи клавиш:";
    strings["Move by one##cmk0"].plurals[0] = "Сдвигать на одну позицию##cmk0";
    strings["Move by Edit Step##cmk1"].plurals[0] = "Сдвигать на шаг редактирования##cmk1";
    strings["Move cursor by edit step on delete##sgse"].plurals[0] = "Сдвигать курсор на шаг редактирования при удалении";
    strings["Move cursor by edit step on insert (push)##sgse"].plurals[0] = "Сдвигать курсор на шаг редактирования при вставке";
    strings["Move cursor up on backspace-delete##sgse"].plurals[0] = "Сдвигать курсор вверх при удалении по нажатию Backspace";
    strings["Move cursor to end of clipboard content when pasting##sgse"].plurals[0] = "Сдвигать курсор в конец вставленного фрагмента при вставке";
    strings["Scrolling##sgse"].plurals[0] = "Прокрутка";
    strings["Change order when scrolling outside of pattern bounds:##sgse"].plurals[0] = "Менять положение в матрице паттернов при прокрутке за пределы паттернов:";
    strings["No##pscroll0"].plurals[0] = "Нет##pscroll0";
    strings["Yes##pscroll1"].plurals[0] = "Да##pscroll1";
    strings["Yes, and wrap around song##pscroll2"].plurals[0] = "Да, и переносить в начало/конец трека##pscroll2";
    strings["Cursor follows current order when moving it##sgse"].plurals[0] = "Курсор остаётся на строке матрицы паттернов при перемещении этой строки";
    strings["applies when playback is stopped.##sgse"].plurals[0] = "действительно только при остановленном воспроизведении.";
    strings["Don't scroll when moving cursor##sgse"].plurals[0] = "Не прокручивать при перемещении курсора";
    strings["Move cursor with scroll wheel:##sgse"].plurals[0] = "Перемещать курсор при помощи колёсика мыши:";
    strings["No##csw0"].plurals[0] = "Нет##csw0";
    strings["Yes##csw1"].plurals[0] = "Да##csw1";
    strings["Inverted##csw2"].plurals[0] = "Да, но в обратном направлении##csw2";
    strings["Assets##sgse0"].plurals[0] = "Ресурсы";
    strings["Display instrument type menu when adding instrument##sgse"].plurals[0] = "Отображать тип инструмента при добавлении инструмента";
    strings["Select asset after opening one##sgse"].plurals[0] = "Выделять объект после открытия";
    strings["Appearance##sgse"].plurals[0] = "Внешний вид";
    strings["Scaling##sgse"].plurals[0] = "Масштаб";
    strings["Automatic UI scaling factor##sgse"].plurals[0] = "Автоматическое масштабирование интерфейса";
    strings["UI scaling factor##sgse"].plurals[0] = "Масштаб интерфейса";
    strings["Icon size##sgse"].plurals[0] = "Размер иконок";
    strings["Text##sgse"].plurals[0] = "Текст";
    strings["Font renderer##sgse"].plurals[0] = "Отрисовщик шрифта";
    strings["Main font##sgse"].plurals[0] = "Основной шрифт";
    strings["Size##MainFontSize"].plurals[0] = "Размер##MainFontSize";
    strings["Header font##sgse"].plurals[0] = "Шрифт заголовков";
    strings["Size##HeadFontSize"].plurals[0] = "Размер##HeadFontSize";
    strings["Pattern font##sgse"].plurals[0] = "Шрифт паттернов";
    strings["Size##PatFontSize"].plurals[0] = "Размер##PatFontSize";
    strings["Anti-aliased fonts##sgse"].plurals[0] = "Сглаживание шрифтов";
    strings["Support bitmap fonts##sgse"].plurals[0] = "Поддерживать растровые шрифты";
    strings["Hinting:##sgse"].plurals[0] = "Хинтование";
    strings["Off (soft)##fh0"].plurals[0] = "Нет (слабое)##fh0";
    strings["Slight##fh1"].plurals[0] = "Небольшое##fh1";
    strings["Normal##fh2"].plurals[0] = "Нормальное##fh2";
    strings["Full (hard)##fh3"].plurals[0] = "Полное (жёсткое)##fh3";
    strings["Auto-hinter:##sgse"].plurals[0] = "Автоматическое хинтирование";
    strings["Disable##fah0"].plurals[0] = "Отключить##fah0";
    strings["Enable##fah1"].plurals[0] = "Включить##fah1";
    strings["Force##fah2"].plurals[0] = "Принудительное##fah2";
    strings["Display Japanese characters##sgse"].plurals[0] = "Отображать японские символы (вкл. иероглифы)";
    strings["Only toggle this option if you have enough graphics memory.\n"
            "This is a temporary solution until dynamic font atlas is implemented in Dear ImGui.\n\n"
            "このオプションは、十分なグラフィックメモリがある場合にのみ切り替えてください。\n"
            "これは、Dear ImGuiにダイナミックフォントアトラスが実装されるまでの一時的な解決策です。##sgse"].plurals[0] = 
            
            "Включайте эту настройку только в случае наличия достаточного количества графической памяти.\n"
            "Это временное решение, поскольку пока Dear ImGui не поддерживает динамический атлас шрифтов.\n\n"
            "このオプションは、十分なグラフィックメモリがある場合にのみ切り替えてください。\n"
            "これは、Dear ImGuiにダイナミックフォントアトラスが実装されるまでの一時的な解決策です。";
    strings["Display Chinese (Simplified) characters##sgse"].plurals[0] = "Отображать китайские иероглифы (упрощённые)";
    strings["Only toggle this option if you have enough graphics memory.\n"
            "This is a temporary solution until dynamic font atlas is implemented in Dear ImGui.\n\n"
            "请在确保你有足够的显存后再启动此设定\n"
            "这是一个在ImGui实现动态字体加载之前的临时解决方案##sgse"].plurals[0] = 
            
            "Включайте эту настройку только в случае наличия достаточного количества графической памяти.\n"
            "Это временное решение, поскольку пока Dear ImGui не поддерживает динамический атлас шрифтов.\n\n"
            "请在确保你有足够的显存后再启动此设定\n"
            "这是一个在ImGui实现动态字体加载之前的临时解决方案";
    strings["Display Chinese (Traditional) characters##sgse"].plurals[0] = "Отображать китайские иероглифы (традиционные)";
    strings["Only toggle this option if you have enough graphics memory.\n"
            "This is a temporary solution until dynamic font atlas is implemented in Dear ImGui.\n\n"
            "請在確保你有足夠的顯存后再啟動此設定\n"
            "這是一個在ImGui實現動態字體加載之前的臨時解決方案##sgse"].plurals[0] = 
            
            "Включайте эту настройку только в случае наличия достаточного количества графической памяти.\n"
            "Это временное решение, поскольку пока Dear ImGui не поддерживает динамический атлас шрифтов.\n\n"
            "請在確保你有足夠的顯存后再啟動此設定\n"
            "這是一個在ImGui實現動態字體加載之前的臨時解決方案";
    strings["Display Korean characters##sgse"].plurals[0] = "Отображать корейские иероглифы";
    strings["Only toggle this option if you have enough graphics memory.\n"
            "This is a temporary solution until dynamic font atlas is implemented in Dear ImGui.\n\n"
            "그래픽 메모리가 충분한 경우에만 이 옵션을 선택하십시오.\n"
            "이 옵션은 Dear ImGui에 동적 글꼴 아틀라스가 구현될 때까지 임시 솔루션입니다.##sgse"].plurals[0] = 
            
            "Включайте эту настройку только в случае наличия достаточного количества графической памяти.\n"
            "Это временное решение, поскольку пока Dear ImGui не поддерживает динамический атлас шрифтов.\n\n"
            "그래픽 메모리가 충분한 경우에만 이 옵션을 선택하십시오.\n"
            "이 옵션은 Dear ImGui에 동적 글꼴 아틀라스가 구현될 때까지 임시 솔루션입니다.";

    strings["Program##sgse2"].plurals[0] = "Программа";
    strings["Title bar:##sgse"].plurals[0] = "Полоса заголовка окна";
    strings["Furnace-B##tbar0"].plurals[0] = "Furnace-B##tbar0";
    strings["Song Name - Furnace-B##tbar1"].plurals[0] = "Название композиции - Furnace-B##tbar1";
    strings["file_name.fur - Furnace-B##tbar2"].plurals[0] = "название_файла.fur - Furnace-B##tbar2";
    strings["/path/to/file.fur - Furnace-B##tbar3"].plurals[0] = "/путь/к/файлу.fur - Furnace-B##tbar3";
    strings["Display system name on title bar##sgse"].plurals[0] = "Отображать название чипа/системы в полосе заголовка окна";
    strings["Display chip names instead of \"multi-system\" in title bar##sgse"].plurals[0] = "Отображать названия чипов/систем вместо \"мульти-система\" в полосе заголовка окна";
    strings["Status bar:##sgse"].plurals[0] = "Строка состояния:";
    strings["Cursor details##sbar0"].plurals[0] = "Информация о выделенном элементе##sbar0";
    strings["File path##sbar1"].plurals[0] = "Путь к файлу##sbar1";
    strings["Cursor details or file path##sbar2"].plurals[0] = "Информация о выделенном элементе или путь к файлу##sbar2";
    strings["Nothing##sbar3"].plurals[0] = "Ничего##sbar3";
    strings["Export options layout:##sgse"].plurals[0] = "Вид настроек экспорта:";
    strings["Sub-menus in File menu##eol0"].plurals[0] = "Подпункты в меню \"Файл\"##eol0";
    strings["Modal window with tabs##eol1"].plurals[0] = "Модальное окно с вкладками##eol1";
    strings["Modal windows with options in File menu##eol2"].plurals[0] = "Модальное окно с настройками в меню \"Файл\"";
    strings["Capitalize menu bar##sgse"].plurals[0] = "Названия пунктов в горизонтальном меню с большой буквы";
    strings["Display add/configure/change/remove chip menus in File menu##sgse"].plurals[0] = "Отображать в меню \"Файл\" пункты: добавить/настроить/изменить/убрать чип";
    strings["Orders##sgse1"].plurals[0] = "Матрица паттернов";
    strings["Highlight channel at cursor in Orders##sgse"].plurals[0] = "Выделить в матрице паттернов канал, на котором находится курсор";
    strings["Orders row number format:##sgse"].plurals[0] = "Формат отображения номера строки матрицы паттернов:";
    strings["Decimal##orbD"].plurals[0] = "Десятеричный##orbD";
    strings["Hexadecimal##orbH"].plurals[0] = "Шестнадцатеричный##orbH";
    strings["Pattern##sgse1"].plurals[0] = "Паттерн";
    strings["Center pattern view##sgse"].plurals[0] = "Центрировать отображаемые паттерны внутри окна";
    strings["Overflow pattern highlights##sgse"].plurals[0] = "Продолжать полосы подсветки строк паттернов за пределы самих паттернов";
    strings["Display previous/next pattern##sgse"].plurals[0] = "Отображать предыдущий/следующий паттерн";
    strings["Pattern row number format:##sgse"].plurals[0] = "Формат отображения номера строки паттерна:";
    strings["Decimal##prbD"].plurals[0] = "Десятеричный##prbD";
    strings["Hexadecimal##prbH"].plurals[0] = "Шестнадцатеричный##prbH";
    strings["Pattern view labels:##sgse"].plurals[0] = "Маркировка ячеек в паттерне";
    strings["Note off (3-char)##sgse"].plurals[0] = "\"Отпускание клавиши\" (резкое) (3 символа)";
    strings["Note release (3-char)##sgse"].plurals[0] = "\"Отпускание клавиши\" (с включением фазы затухания огибающей) (3 символа)";
    strings["Macro release (3-char)##sgse"].plurals[0] = "\"Отпускание клавиши\" (только для макросов (3 символа))";
    strings["Empty field (3-char)##sgse"].plurals[0] = "Пустая ячейка (3 символа)";
    strings["Empty field (2-char)##sgse"].plurals[0] = "Пустая ячейка (2 символа)";
    strings["Pattern view spacing after:##sgse"].plurals[0] = "Разбивка в отображении паттерна:";
    strings["Note##sgse"].plurals[0] = "Нота";
    strings["Instrument##sgse1"].plurals[0] = "Инструмент";
    strings["Volume##sgse4"].plurals[0] = "Громкость";
    strings["Effect##sgse"].plurals[0] = "Индекс эффекта";
    strings["Effect value##sgse"].plurals[0] = "Параметр эффекта";
    strings["Single-digit effects for 00-0F##sgse"].plurals[0] = "Отображать одной цифрой индекс эффекта для индексов 00-0F";
    strings["Use flats instead of sharps##sgse"].plurals[0] = "Отображать бемоли вместо диезов";
    strings["Use German notation##sgse"].plurals[0] = "Использовать немецкие имена нот";
    strings["Channel##sgse1"].plurals[0] = "Канал";
    strings["Channel style:##sgse"].plurals[0] = "Стиль заголовка:";
    strings["Classic##CHS0"].plurals[0] = "Классический##CHS0";
    strings["Line##CHS1"].plurals[0] = "Линия##CHS1";
    strings["Round##CHS2"].plurals[0] = "Со скруглениями##CHS2";
    strings["Split button##CHS3"].plurals[0] = "С отдельной кнопкой отключения звука##CHS3";
    strings["Square border##CHS4"].plurals[0] = "С прямоугольной границей вокруг названия##CHS4";
    strings["Round border##CHS5"].plurals[0] = "Со скруглённой границей вокруг названия##CHS5";
    strings["Channel volume bar:##sgse"].plurals[0] = "Полоска громкости в заголовке канала:";
    strings["Non##CHV0"].plurals[0] = "Нет##CHV0";
    strings["Simple##CHV1"].plurals[0] = "Простая##CHV1";
    strings["Stereo##CHV2"].plurals[0] = "Стерео##CHV2";
    strings["Real##CHV3"].plurals[0] = "Настоящая громкость##CHV3";
    strings["Real (stereo)##CHV4"].plurals[0] = "Настоящая громкость (стерео)##CHV4";
    strings["Channel feedback style:##sgse"].plurals[0] = "Подсветка заголовка канала:";
    strings["Off##CHF0"].plurals[0] = "Выкл.##CHF0";
    strings["Note##CHF1"].plurals[0] = "Начало ноты##CHF1";
    strings["Volume##CHF2"].plurals[0] = "Пропорционально громкости##CHF2";
    strings["Active##CHF3"].plurals[0] = "При активности канала##CHF3";
    strings["Channel font:##sgse"].plurals[0] = "Шрифт заголовка канала:";
    strings["Regular##CHFont0"].plurals[0] = "Обычный##CHFont0";
    strings["Monospace##CHFont1"].plurals[0] = "Моноширинный##CHFont1";
    strings["Center channel name##sgse"].plurals[0] = "Центрировать название канала";
    strings["Channel colors:##sgse"].plurals[0] = "Цвета заголовка канала";
    strings["Single##CHC0"].plurals[0] = "Единый цвет##CHC0";
    strings["Channel type##CHC1"].plurals[0] = "Согласно типу канала##CHC1";
    strings["Instrument type##CHC2"].plurals[0] = "Согласно типу инструмента##CHC2";
    strings["Channel name colors:##sgse"].plurals[0] = "Цвета названия канала:";
    strings["Single##CTC0"].plurals[0] = "Единый цвет##CTC0";
    strings["Channel type##CTC1"].plurals[0] = "Согласно типу канала##CTC1";
    strings["Instrument type##CTC2"].plurals[0] = "Согласно типу инструмента##CTC2";
    strings["Assets##sgse1"].plurals[0] = "Представление ресурсов модуля";
    strings["Unified instrument/wavetable/sample list##sgse"].plurals[0] = "Единый список инструментов, волновых таблиц и сэмплов";
    strings["Horizontal instrument list##sgse"].plurals[0] = "Горизонтальный список инструментов";
    strings["Instrument list icon style:##sgse"].plurals[0] = "Стиль иконок в списке инструментов:";
    strings["None##iis0"].plurals[0] = "Не показывать##iis0";
    strings["Graphical icons##iis1"].plurals[0] = "Графические иконки##iis1";
    strings["Letter icons##iis2"].plurals[0] = "Иконки с буквами##iis2";
    strings["Colorize instrument editor using instrument type##sgse"].plurals[0] = "Изменять оттенки цветов редактора инструмента согласно типу инструмента";
    strings["Macro Editor##sgse0"].plurals[0] = "Редактор макросов";
    strings["Macro editor layout:##sgse"].plurals[0] = "Компоновка редактора макросов:";
    strings["Unified##mel0"].plurals[0] = "Общий список##mel0";
    strings["Grid##mel2"].plurals[0] = "Прямоугольная сетка##mel2";
    strings["Single (with list)##mel3"].plurals[0] = "Окно редактирования одного макроса + список##mel3";
    strings["Use classic macro editor vertical slider##sgse"].plurals[0] = "Использовать классическую вертикальную полосу прокрутки";
    strings["Wave Editor##sgse"].plurals[0] = "Редактор волновых таблиц";
    strings["Use compact wave editor##sgse"].plurals[0] = "Использовать компактный редактор волновых таблиц";
    strings["FM Editor##sgse0"].plurals[0] = "Редактор FM-инструментов";
    strings["FM parameter names:##sgse"].plurals[0] = "Названия параметров:";
    strings["Friendly##fmn0"].plurals[0] = "Понятные##fmn0";
    strings["Technical##fmn1"].plurals[0] = "Исходные формальные##fmn1";
    strings["Technical (alternate)##fmn2"].plurals[0] = "Исходные формальные (альтернативные)##fmn2";
    strings["Use standard OPL waveform names##sgse"].plurals[0] = "Использовать стандартные названия волн для чипов серии OPL";
    strings["FM parameter editor layout:##sgse"].plurals[0] = "Компоновка редактора FM-инструментов";
    strings["Modern##fml0"].plurals[0] = "Современная##fml0";
    strings["Compact (2x2, classic)##fml1"].plurals[0] = "Компактная (2x2, классическая)##fml1";
    strings["Compact (1x4)##fml2"].plurals[0] = "Компактная (1x4)##fml2";
    strings["Compact (4x1)##fml3"].plurals[0] = "Компактная (4x1)##fml3";
    strings["Alternate (2x2)##fml4"].plurals[0] = "Альтернативная (2x2)##fml4";
    strings["Alternate (1x4)##fml5"].plurals[0] = "Альтернативная (1x4)##fml5";
    strings["Alternate (4x1)##fml6"].plurals[0] = "Альтернативная (4x1)##fml6";
    strings["Position of Sustain in FM editor:##sgse"].plurals[0] = "Позиция параметра \"Сустейн\" в редакторе:";
    strings["Between Decay and Sustain Rate##susp0"].plurals[0] = "Между спадом и уклоном сустейна##susp0";
    strings["After Release Rate##susp1"].plurals[0] = "После уклона релиза##susp1";
    strings["Use separate colors for carriers/modulators in FM editor##sgse"].plurals[0] = "Использовать различные цвета для модулирующих и несущих операторов";
    strings["Unsigned FM detune values##sgse"].plurals[0] = "Беззнаковое значение параметра расстройки";
    strings["Statistics##sgse"].plurals[0] = "Окно статистики";
    strings["Chip memory usage unit:##sgse"].plurals[0] = "Единицы измерения использования памяти чипа:";
    strings["Bytes##MUU0"].plurals[0] = "Байты##MUU0";
    strings["Kilobytes##MUU1"].plurals[0] = "Килобайты##MUU1";
    strings["Oscilloscope##set"].plurals[0] = "Осциллограф##set";
    strings["Rounded corners##sgse"].plurals[0] = "Закруглённые края";
    strings["Border##sgse"].plurals[0] = "Граница";
    strings["Mono##sgse1"].plurals[0] = "Моно";
    strings["Anti-aliased##sgse"].plurals[0] = "Со сглаживанием";
    strings["Fill entire window##sgse"].plurals[0] = "Полностью заполняет окно";
    strings["Waveform goes out of bounds##sgse"].plurals[0] = "Волна может выходить за пределы окна";
    strings["Windows##sgse"].plurals[0] = "Окна";
    strings["Rounded window corners##sgse"].plurals[0] = "Закруглённые края окон";
    strings["Rounded buttons##sgse"].plurals[0] = "Закруглённые края кнопок";
    strings["Rounded tabs##sgse"].plurals[0] = "Закруглённые края заголовков вкладок";
    strings["Rounded scrollbars##sgse"].plurals[0] = "Закруглённые края ползунка полосы прокрутки";
    strings["Rounded menu corners##sgse"].plurals[0] = "Закруглённые края выпадающих меню";
    strings["Borders around widgets##sgse"].plurals[0] = "Границы вокруг кнопок, списков и т.д.";
    strings["Misc##sgse"].plurals[0] = "Разное";
    strings["Wrap text##sgse"].plurals[0] = "Переносить текст на новую строку";
    strings["Wrap text in song/subsong comments window.##sgse"].plurals[0] = "Переносить текст на новую строку в окне информации/комментариев к композиции.";
    strings["Frame shading in text windows##sgse"].plurals[0] = "Градиент в текстовых окнах";
    strings["Apply frame shading to the multiline text fields\nsuch as song/subsong info/comments.##sgse"].plurals[0] = "Применять градиент в окне информации/комментариев к композиции.";
    strings["Color##sgse"].plurals[0] = "Цвета";
    strings["Color scheme##sgse"].plurals[0] = "Цветовая схема";
    strings["Import##sgse2"].plurals[0] = "Импорт";
    strings["Export##sgse2"].plurals[0] = "Экспорт";
    strings["Reset defaults##sgse1"].plurals[0] = "Сбросить";
    strings["Are you sure you want to reset the color scheme?##sgse"].plurals[0] = "Вы действительно хотите сбросить цветовую схему?";
    strings["Interface##sgse1"].plurals[0] = "Интерфейс";
    strings["Frame shading##sgse"].plurals[0] = "Затенение рамок";
    strings["Interface (other)##sgse"].plurals[0] = "Интерфейс (другое)";
    strings["Miscellaneous##sgse"].plurals[0] = "Разное";
    strings["File Picker (built-in)##sgse"].plurals[0] = "Меню выбора файлов (встроенное)";
    strings["Oscilloscope##sgse"].plurals[0] = "Осциллограф";
    strings["Wave (non-mono)##sgse"].plurals[0] = "Волна (не моно)";
    strings["Volume Meter##sgse"].plurals[0] = "Измеритель громкости";
    strings["Orders##sgse2"].plurals[0] = "Матрица паттернов";
    strings["Envelope View##sgse"].plurals[0] = "Визуализатор огибающей";
    strings["FM Editor##sgse1"].plurals[0] = "Редактор FM-инструментов";
    strings["Macro Editor##sgse1"].plurals[0] = "Редактор макросов";
    strings["Instrument Types##sgse"].plurals[0] = "Типы инструментов";
    strings["Channel##sgse2"].plurals[0] = "Канал";
    strings["Pattern##sgse2"].plurals[0] = "Паттерн";
    strings["Sample Editor##sgse"].plurals[0] = "Редактор сэмплов";
    strings["Pattern Manager##sgse"].plurals[0] = "Менеджер паттернов";
    strings["Piano##sgse"].plurals[0] = "Клавиатура пианино";
    strings["Clock##sgse"].plurals[0] = "Часы";
    strings["Patchbay##sgse"].plurals[0] = "Соединение каналов";
    strings["Log Viewer##sgse"].plurals[0] = "Просмотр логов";

    // these are messy, but the ##CC_GUI... is required.
    strings["Button##CC_GUI_COLOR_BUTTON"].plurals[0] = "Кнопка##CC_GUI_COLOR_BUTTON";
    strings["Button (hovered)##CC_GUI_COLOR_BUTTON_HOVER"].plurals[0] = "Кнопка (курсор на кнопке)##CC_GUI_COLOR_BUTTON_HOVER";
    strings["Button (active)##CC_GUI_COLOR_BUTTON_ACTIVE"].plurals[0] = "Кнопка (нажатая)##CC_GUI_COLOR_BUTTON_ACTIVE";
    strings["Tab##CC_GUI_COLOR_TAB"].plurals[0] = "Вкладка##CC_GUI_COLOR_TAB";
    strings["Tab (hovered)##CC_GUI_COLOR_TAB_HOVER"].plurals[0] = "Вкладка (курсор на вкладке)##CC_GUI_COLOR_TAB_HOVER";
    strings["Tab (active)##CC_GUI_COLOR_TAB_ACTIVE"].plurals[0] = "Вкладка (активная)##CC_GUI_COLOR_TAB_ACTIVE";
    strings["Tab (unfocused)##CC_GUI_COLOR_TAB_UNFOCUSED"].plurals[0] = "Вкладка (не текущая)##CC_GUI_COLOR_TAB_UNFOCUSED";
    strings["Tab (unfocused and active)##CC_GUI_COLOR_TAB_UNFOCUSED_ACTIVE"].plurals[0] = "Вкладка (курсор на вкладке, текущая)##CC_GUI_COLOR_TAB_UNFOCUSED_ACTIVE";
    strings["ImGui header##CC_GUI_COLOR_IMGUI_HEADER"].plurals[0] = "Заголовок ImGui##CC_GUI_COLOR_IMGUI_HEADER";
    strings["ImGui header (hovered)##CC_GUI_COLOR_IMGUI_HEADER_HOVER"].plurals[0] = "Заголовок ImGui (курсор на заголовке)##CC_GUI_COLOR_IMGUI_HEADER_HOVER";
    strings["ImGui header (active)##CC_GUI_COLOR_IMGUI_HEADER_ACTIVE"].plurals[0] = "Заголовок ImGui (активный)##CC_GUI_COLOR_IMGUI_HEADER_ACTIVE";
    strings["Resize grip##CC_GUI_COLOR_RESIZE_GRIP"].plurals[0] = "Захват для изменения размера окна##CC_GUI_COLOR_RESIZE_GRIP";
    strings["Resize grip (hovered)##CC_GUI_COLOR_RESIZE_GRIP_HOVER"].plurals[0] = "Захват для изменения размера окна (курсор на захвате)##CC_GUI_COLOR_RESIZE_GRIP_HOVER";
    strings["Resize grip (active)##CC_GUI_COLOR_RESIZE_GRIP_ACTIVE"].plurals[0] = "Захват для изменения размера окна (активный)##CC_GUI_COLOR_RESIZE_GRIP_ACTIVE";
    strings["Widget background##CC_GUI_COLOR_WIDGET_BACKGROUND"].plurals[0] = "Задний фон виджета##CC_GUI_COLOR_WIDGET_BACKGROUND";
    strings["Widget background (hovered)##CC_GUI_COLOR_WIDGET_BACKGROUND_HOVER"].plurals[0] = "Задний фон виджета (курсор на виджете)##CC_GUI_COLOR_WIDGET_BACKGROUND_HOVER";
    strings["Widget background (active)##CC_GUI_COLOR_WIDGET_BACKGROUND_ACTIVE"].plurals[0] = "Задний фон виджета (активный)##CC_GUI_COLOR_WIDGET_BACKGROUND_ACTIVE";
    strings["Slider grab##CC_GUI_COLOR_SLIDER_GRAB"].plurals[0] = "Ползунок выставления значения##CC_GUI_COLOR_SLIDER_GRAB";
    strings["Slider grab (active)##CC_GUI_COLOR_SLIDER_GRAB_ACTIVE"].plurals[0] = "Ползунок выставления значения (активный)##CC_GUI_COLOR_SLIDER_GRAB_ACTIVE";
    strings["Title background (active)##CC_GUI_COLOR_TITLE_BACKGROUND_ACTIVE"].plurals[0] = "Задний фон заголовка (активный)##CC_GUI_COLOR_TITLE_BACKGROUND_ACTIVE";
    strings["Checkbox/radio button mark##CC_GUI_COLOR_CHECK_MARK"].plurals[0] = "Маркировка в поле для галочки и радиокнопке##CC_GUI_COLOR_CHECK_MARK";
    strings["Text selection##CC_GUI_COLOR_TEXT_SELECTION"].plurals[0] = "ВЫделение текста##CC_GUI_COLOR_TEXT_SELECTION";
    strings["Line plot##CC_GUI_COLOR_PLOT_LINES"].plurals[0] = "Цвет линий##CC_GUI_COLOR_PLOT_LINES";
    strings["Line plot (hovered)##CC_GUI_COLOR_PLOT_LINES_HOVER"].plurals[0] = "Цвет линий (курсор на поле)##CC_GUI_COLOR_PLOT_LINES_HOVER";
    strings["Histogram plot##CC_GUI_COLOR_PLOT_HISTOGRAM"].plurals[0] = "Столбчатая диаграмма##CC_GUI_COLOR_PLOT_HISTOGRAM";
    strings["Histogram plot (hovered)##CC_GUI_COLOR_PLOT_HISTOGRAM_HOVER"].plurals[0] = "Столбчатая диаграмма (курсор на диаграмме)##CC_GUI_COLOR_PLOT_HISTOGRAM_HOVER";
    strings["Table row (even)##CC_GUI_COLOR_TABLE_ROW_EVEN"].plurals[0] = "Строка таблицы (чётная)##CC_GUI_COLOR_TABLE_ROW_EVEN";
    strings["Table row (odd)##CC_GUI_COLOR_TABLE_ROW_ODD"].plurals[0] = "Строка таблицы (нечётная)##CC_GUI_COLOR_TABLE_ROW_ODD";

    strings["Background##CC_GUI_COLOR_BACKGROUND"].plurals[0] = "Задний фон##CC_GUI_COLOR_BACKGROUND";
    strings["Window background##CC_GUI_COLOR_FRAME_BACKGROUND"].plurals[0] = "Фон окон##CC_GUI_COLOR_FRAME_BACKGROUND";
    strings["Sub-window background##CC_GUI_COLOR_FRAME_BACKGROUND_CHILD"].plurals[0] = "Фон подокн##CC_GUI_COLOR_FRAME_BACKGROUND_CHILD";
    strings["Pop-up background##CC_GUI_COLOR_FRAME_BACKGROUND_POPUP"].plurals[0] = "Фон всплывающих окон##CC_GUI_COLOR_FRAME_BACKGROUND_POPUP";
    strings["Modal backdrop##CC_GUI_COLOR_MODAL_BACKDROP"].plurals[0] = "Затенение при возникновении модального окна##CC_GUI_COLOR_MODAL_BACKDROP";
    strings["Header##CC_GUI_COLOR_HEADER"].plurals[0] = "Заголовок##CC_GUI_COLOR_HEADER";
    strings["Text##CC_GUI_COLOR_TEXT"].plurals[0] = "Текст##CC_GUI_COLOR_TEXT";
    strings["Text (disabled)##CC_GUI_COLOR_TEXT_DISABLED"].plurals[0] = "Текст (выключенный)##CC_GUI_COLOR_TEXT_DISABLED";
    strings["Title bar (inactive)##CC_GUI_COLOR_TITLE_INACTIVE"].plurals[0] = "Полоса заголовка (неактивная)##CC_GUI_COLOR_TITLE_INACTIVE";
    strings["Title bar (collapsed)##CC_GUI_COLOR_TITLE_COLLAPSED"].plurals[0] = "Полоса заголовка (свёрнутое окно)##CC_GUI_COLOR_TITLE_COLLAPSED";
    strings["Menu bar##CC_GUI_COLOR_MENU_BAR"].plurals[0] = "Полоса меню##CC_GUI_COLOR_MENU_BAR";
    strings["Border##CC_GUI_COLOR_BORDER"].plurals[0] = "Граница##CC_GUI_COLOR_BORDER";
    strings["Border shadow##CC_GUI_COLOR_BORDER_SHADOW"].plurals[0] = "Тень границы##CC_GUI_COLOR_BORDER_SHADOW";
    strings["Scroll bar##CC_GUI_COLOR_SCROLL"].plurals[0] = "Полоса прокрутки##CC_GUI_COLOR_SCROLL";
    strings["Scroll bar (hovered)##CC_GUI_COLOR_SCROLL_HOVER"].plurals[0] = "Полоса прокрутки (курсор на полосе)##CC_GUI_COLOR_SCROLL_HOVER";
    strings["Scroll bar (clicked)##CC_GUI_COLOR_SCROLL_ACTIVE"].plurals[0] = "Полоса прокрутки (нажата)##CC_GUI_COLOR_SCROLL_ACTIVE";
    strings["Scroll bar background##CC_GUI_COLOR_SCROLL_BACKGROUND"].plurals[0] = "Фон полосы прокрутки##CC_GUI_COLOR_SCROLL_BACKGROUND";
    strings["Separator##CC_GUI_COLOR_SEPARATOR"].plurals[0] = "Разделитель строк##CC_GUI_COLOR_SEPARATOR";
    strings["Separator (hover)##CC_GUI_COLOR_SEPARATOR_HOVER"].plurals[0] = "Разделитель строк (курсор на разделителе)##CC_GUI_COLOR_SEPARATOR_HOVER";
    strings["Separator (active)##CC_GUI_COLOR_SEPARATOR_ACTIVE"].plurals[0] = "Разделитель строк (активный)##CC_GUI_COLOR_SEPARATOR_ACTIVE";
    strings["Docking preview##CC_GUI_COLOR_DOCKING_PREVIEW"].plurals[0] = "Превью стыковки окон##CC_GUI_COLOR_DOCKING_PREVIEW";
    strings["Docking empty##CC_GUI_COLOR_DOCKING_EMPTY"].plurals[0] = "Пустое поле стыковки окон##CC_GUI_COLOR_DOCKING_EMPTY";
    strings["Table header##CC_GUI_COLOR_TABLE_HEADER"].plurals[0] = "Заголовок таблицы##CC_GUI_COLOR_TABLE_HEADER";
    strings["Table border (hard)##CC_GUI_COLOR_TABLE_BORDER_HARD"].plurals[0] = "Заголовок таблицы (жёсткий)##CC_GUI_COLOR_TABLE_BORDER_HARD";
    strings["Table border (soft)##CC_GUI_COLOR_TABLE_BORDER_SOFT"].plurals[0] = "Заголовок таблицы (мягкий)##CC_GUI_COLOR_TABLE_BORDER_SOFT";
    strings["Drag and drop target##CC_GUI_COLOR_DRAG_DROP_TARGET"].plurals[0] = "Цель перетаскивания##CC_GUI_COLOR_DRAG_DROP_TARGET";
    strings["Window switcher (highlight)##CC_GUI_COLOR_NAV_WIN_HIGHLIGHT"].plurals[0] = "Переключатель окон (подсвечен)##CC_GUI_COLOR_NAV_WIN_HIGHLIGHT";
    strings["Window switcher backdrop##CC_GUI_COLOR_NAV_WIN_BACKDROP"].plurals[0] = "Переключатель окон (цвет затенения остального интерфейса)##CC_GUI_COLOR_NAV_WIN_BACKDROP";

    strings["Toggle on##CC_GUI_COLOR_TOGGLE_ON"].plurals[0] = "Переключатель вкл.##CC_GUI_COLOR_TOGGLE_ON";
    strings["Toggle off##CC_GUI_COLOR_TOGGLE_OFF"].plurals[0] = "Переключатель выкл.##CC_GUI_COLOR_TOGGLE_OFF";
    strings["Playback status##CC_GUI_COLOR_PLAYBACK_STAT"].plurals[0] = "Статус воспроизведения##CC_GUI_COLOR_PLAYBACK_STAT";
    strings["Destructive hint##CC_GUI_COLOR_DESTRUCTIVE"].plurals[0] = "Подсказка об удалении##CC_GUI_COLOR_DESTRUCTIVE";
    strings["Warning hint##CC_GUI_COLOR_WARNING"].plurals[0] = "Подсказка о сообщении##CC_GUI_COLOR_WARNING";
    strings["Error hint##CC_GUI_COLOR_ERROR"].plurals[0] = "Подсказка об ошибке##CC_GUI_COLOR_ERROR";

    strings["Directory##CC_GUI_COLOR_FILE_DIR"].plurals[0] = "Папка##CC_GUI_COLOR_FILE_DIR";
    strings["Song (native)##CC_GUI_COLOR_FILE_SONG_NATIVE"].plurals[0] = "Файл трека (нативно поддерживается)##CC_GUI_COLOR_FILE_SONG_NATIVE";
    strings["Song (import)##CC_GUI_COLOR_FILE_SONG_IMPORT"].plurals[0] = "Файл трека (импорт)##CC_GUI_COLOR_FILE_SONG_IMPORT";
    strings["Instrument##CC_GUI_COLOR_FILE_INSTR"].plurals[0] = "Инструмент##CC_GUI_COLOR_FILE_INSTR";
    strings["Audio##CC_GUI_COLOR_FILE_AUDIO"].plurals[0] = "Аудиофайл##CC_GUI_COLOR_FILE_AUDIO";
    strings["Wavetable##CC_GUI_COLOR_FILE_WAVE"].plurals[0] = "Волновая таблица##CC_GUI_COLOR_FILE_WAVE";
    strings["VGM##CC_GUI_COLOR_FILE_VGM"].plurals[0] = "VGM##CC_GUI_COLOR_FILE_VGM";
    strings["ZSM##CC_GUI_COLOR_FILE_ZSM"].plurals[0] = "ZSM##CC_GUI_COLOR_FILE_ZSM";
    strings["Font##CC_GUI_COLOR_FILE_FONT"].plurals[0] = "Шрифт##CC_GUI_COLOR_FILE_FONT";
    strings["Other##CC_GUI_COLOR_FILE_OTHER"].plurals[0] = "Другое##CC_GUI_COLOR_FILE_OTHER";

    strings["Border##CC_GUI_COLOR_OSC_BORDER"].plurals[0] = "Граница осциллографа##CC_GUI_COLOR_OSC_BORDER";
    strings["Background (top-left)##CC_GUI_COLOR_OSC_BG1"].plurals[0] = "Фон (верхний левый угол)##CC_GUI_COLOR_OSC_BG1";
    strings["Background (top-right)##CC_GUI_COLOR_OSC_BG2"].plurals[0] = "Фон (верхний правый угол)##CC_GUI_COLOR_OSC_BG2";
    strings["Background (bottom-left)##CC_GUI_COLOR_OSC_BG3"].plurals[0] = "Фон (нижний левый угол)##CC_GUI_COLOR_OSC_BG3";
    strings["Background (bottom-right)##CC_GUI_COLOR_OSC_BG4"].plurals[0] = "Фон (нижний правый угол)##CC_GUI_COLOR_OSC_BG4";
    strings["Waveform##CC_GUI_COLOR_OSC_WAVE"].plurals[0] = "Волна##CC_GUI_COLOR_OSC_WAVE";
    strings["Waveform (clip)##CC_GUI_COLOR_OSC_WAVE_PEAK"].plurals[0] = "Волна (зашкал амплитуды)##CC_GUI_COLOR_OSC_WAVE_PEAK";
    strings["Reference##CC_GUI_COLOR_OSC_REF"].plurals[0] = "Образец##CC_GUI_COLOR_OSC_REF";
    strings["Guide##CC_GUI_COLOR_OSC_GUIDE"].plurals[0] = "Справка##CC_GUI_COLOR_OSC_GUIDE";

    strings["Waveform (1)##CC_GUI_COLOR_OSC_WAVE_CH0"].plurals[0] = "Волна (1)##CC_GUI_COLOR_OSC_WAVE_CH0";
    strings["Waveform (2)##CC_GUI_COLOR_OSC_WAVE_CH1"].plurals[0] = "Волна (2)##CC_GUI_COLOR_OSC_WAVE_CH1";
    strings["Waveform (3)##CC_GUI_COLOR_OSC_WAVE_CH2"].plurals[0] = "Волна (3)##CC_GUI_COLOR_OSC_WAVE_CH2";
    strings["Waveform (4)##CC_GUI_COLOR_OSC_WAVE_CH3"].plurals[0] = "Волна (4)##CC_GUI_COLOR_OSC_WAVE_CH3";
    strings["Waveform (5)##CC_GUI_COLOR_OSC_WAVE_CH4"].plurals[0] = "Волна (5)##CC_GUI_COLOR_OSC_WAVE_CH4";
    strings["Waveform (6)##CC_GUI_COLOR_OSC_WAVE_CH5"].plurals[0] = "Волна (6)##CC_GUI_COLOR_OSC_WAVE_CH5";
    strings["Waveform (7)##CC_GUI_COLOR_OSC_WAVE_CH6"].plurals[0] = "Волна (7)##CC_GUI_COLOR_OSC_WAVE_CH6";
    strings["Waveform (8)##CC_GUI_COLOR_OSC_WAVE_CH7"].plurals[0] = "Волна (8)##CC_GUI_COLOR_OSC_WAVE_CH7";
    strings["Waveform (9)##CC_GUI_COLOR_OSC_WAVE_CH8"].plurals[0] = "Волна (9)##CC_GUI_COLOR_OSC_WAVE_CH8";
    strings["Waveform (10)##CC_GUI_COLOR_OSC_WAVE_CH9"].plurals[0] = "Волна (10)##CC_GUI_COLOR_OSC_WAVE_CH9";
    strings["Waveform (11)##CC_GUI_COLOR_OSC_WAVE_CH10"].plurals[0] = "Волна (11)##CC_GUI_COLOR_OSC_WAVE_CH10";
    strings["Waveform (12)##CC_GUI_COLOR_OSC_WAVE_CH11"].plurals[0] = "Волна (12)##CC_GUI_COLOR_OSC_WAVE_CH11";
    strings["Waveform (13)##CC_GUI_COLOR_OSC_WAVE_CH12"].plurals[0] = "Волна (13)##CC_GUI_COLOR_OSC_WAVE_CH12";
    strings["Waveform (14)##CC_GUI_COLOR_OSC_WAVE_CH13"].plurals[0] = "Волна (14)##CC_GUI_COLOR_OSC_WAVE_CH13";
    strings["Waveform (15)##CC_GUI_COLOR_OSC_WAVE_CH14"].plurals[0] = "Волна (15)##CC_GUI_COLOR_OSC_WAVE_CH14";
    strings["Waveform (16)##CC_GUI_COLOR_OSC_WAVE_CH15"].plurals[0] = "Волна (16)##CC_GUI_COLOR_OSC_WAVE_CH15";

    strings["Low##CC_GUI_COLOR_VOLMETER_LOW"].plurals[0] = "Низкий уровень##CC_GUI_COLOR_VOLMETER_LOW";
    strings["High##CC_GUI_COLOR_VOLMETER_HIGH"].plurals[0] = "Высокий уровень##CC_GUI_COLOR_VOLMETER_HIGH";
    strings["Clip##CC_GUI_COLOR_VOLMETER_PEAK"].plurals[0] = "Зашкал##CC_GUI_COLOR_VOLMETER_PEAK";

    strings["Order number##CC_GUI_COLOR_ORDER_ROW_INDEX"].plurals[0] = "Номер строки##CC_GUI_COLOR_ORDER_ROW_INDEX";
    strings["Playing order background##CC_GUI_COLOR_ORDER_ACTIVE"].plurals[0] = "Фон текущей строки##CC_GUI_COLOR_ORDER_ACTIVE";
    strings["Song loop##CC_GUI_COLOR_SONG_LOOP"].plurals[0] = "Место зацикливания трека##CC_GUI_COLOR_SONG_LOOP";
    strings["Selected order##CC_GUI_COLOR_ORDER_SELECTED"].plurals[0] = "Выделенный столбец##CC_GUI_COLOR_ORDER_SELECTED";
    strings["Similar patterns##CC_GUI_COLOR_ORDER_SIMILAR"].plurals[0] = "Похожие паттерны##CC_GUI_COLOR_ORDER_SIMILAR";
    strings["Inactive patterns##CC_GUI_COLOR_ORDER_INACTIVE"].plurals[0] = "Неактивные паттерны##CC_GUI_COLOR_ORDER_INACTIVE";

    strings["Envelope##CC_GUI_COLOR_FM_ENVELOPE"].plurals[0] = "Огибающая##CC_GUI_COLOR_FM_ENVELOPE";
    strings["Sustain guide##CC_GUI_COLOR_FM_ENVELOPE_SUS_GUIDE"].plurals[0] = "Визуализация сустейна##CC_GUI_COLOR_FM_ENVELOPE_SUS_GUIDE";
    strings["Release##CC_GUI_COLOR_FM_ENVELOPE_RELEASE"].plurals[0] = "Релиз##CC_GUI_COLOR_FM_ENVELOPE_RELEASE";

    strings["Algorithm background##CC_GUI_COLOR_FM_ALG_BG"].plurals[0] = "Задний фон схемы алгоритма##CC_GUI_COLOR_FM_ALG_BG";
    strings["Algorithm lines##CC_GUI_COLOR_FM_ALG_LINE"].plurals[0] = "Линии схемы алгоритма##CC_GUI_COLOR_FM_ALG_LINE";
    strings["Modulator##CC_GUI_COLOR_FM_MOD"].plurals[0] = "Модулирующий оператор##CC_GUI_COLOR_FM_MOD";
    strings["Carrier##CC_GUI_COLOR_FM_CAR"].plurals[0] = "Несущий оператор##CC_GUI_COLOR_FM_CAR";

    strings["SSG-EG##CC_GUI_COLOR_FM_SSG"].plurals[0] = "SSG-EG##CC_GUI_COLOR_FM_SSG";
    strings["Waveform##CC_GUI_COLOR_FM_WAVE"].plurals[0] = "Волна##CC_GUI_COLOR_FM_WAVE";

    strings["Mod. accent (primary)##CC_GUI_COLOR_FM_PRIMARY_MOD"].plurals[0] = "Оттенок модулирующего оператора (основной)##CC_GUI_COLOR_FM_PRIMARY_MOD";
    strings["Mod. accent (secondary)##CC_GUI_COLOR_FM_SECONDARY_MOD"].plurals[0] = "Оттенок модулирующего оператора (неосновной)##CC_GUI_COLOR_FM_SECONDARY_MOD";
    strings["Mod. border##CC_GUI_COLOR_FM_BORDER_MOD"].plurals[0] = "Граница модулирующего оператора##CC_GUI_COLOR_FM_BORDER_MOD";
    strings["Mod. border shadow##CC_GUI_COLOR_FM_BORDER_SHADOW_MOD"].plurals[0] = "Тень границы модулирующего оператора##CC_GUI_COLOR_FM_BORDER_SHADOW_MOD";

    strings["Car. accent (primary)##CC_GUI_COLOR_FM_PRIMARY_CAR"].plurals[0] = "Оттенок несущего оператора (основной)##CC_GUI_COLOR_FM_PRIMARY_CAR";
    strings["Car. accent (secondary)##CC_GUI_COLOR_FM_SECONDARY_CAR"].plurals[0] = "Оттенок несущего оператора (неосновной)##CC_GUI_COLOR_FM_SECONDARY_CAR";
    strings["Car. border##CC_GUI_COLOR_FM_BORDER_CAR"].plurals[0] = "Граница несущего оператора##CC_GUI_COLOR_FM_BORDER_CAR";
    strings["Car. border shadow##CC_GUI_COLOR_FM_BORDER_SHADOW_CAR"].plurals[0] = "Тень границы несущего оператора##CC_GUI_COLOR_FM_BORDER_SHADOW_CAR";

    strings["Volume##CC_GUI_COLOR_MACRO_VOLUME"].plurals[0] = "Громкость##CC_GUI_COLOR_MACRO_VOLUME";
    strings["Pitch##CC_GUI_COLOR_MACRO_PITCH"].plurals[0] = "Частота##CC_GUI_COLOR_MACRO_PITCH";
    strings["Wave##CC_GUI_COLOR_MACRO_WAVE"].plurals[0] = "Волна##CC_GUI_COLOR_MACRO_WAVE";
    strings["Other##CC_GUI_COLOR_MACRO_OTHER"].plurals[0] = "Другое##CC_GUI_COLOR_MACRO_OTHER";

    strings["FM (OPN)##CC_GUI_COLOR_INSTR_FM"].plurals[0] = "FM (OPN)##CC_GUI_COLOR_INSTR_FM";
    strings["SN76489/Sega PSG##CC_GUI_COLOR_INSTR_STD"].plurals[0] = "SN76489/Sega PSG##CC_GUI_COLOR_INSTR_STD";
    strings["T6W28##CC_GUI_COLOR_INSTR_T6W28"].plurals[0] = "T6W28##CC_GUI_COLOR_INSTR_T6W28";
    strings["Game Boy##CC_GUI_COLOR_INSTR_GB"].plurals[0] = "Game Boy##CC_GUI_COLOR_INSTR_GB";
    strings["C64##CC_GUI_COLOR_INSTR_C64"].plurals[0] = "C64##CC_GUI_COLOR_INSTR_C64";
    strings["Amiga/Generic Sample##CC_GUI_COLOR_INSTR_AMIGA"].plurals[0] = "Amiga/Типичный сэмпл##CC_GUI_COLOR_INSTR_AMIGA";
    strings["PC Engine##CC_GUI_COLOR_INSTR_PCE"].plurals[0] = "PC Engine##CC_GUI_COLOR_INSTR_PCE";
    strings["AY-3-8910/SSG##CC_GUI_COLOR_INSTR_AY"].plurals[0] = "AY-3-8910/SSG##CC_GUI_COLOR_INSTR_AY";
    strings["AY8930##CC_GUI_COLOR_INSTR_AY8930"].plurals[0] = "AY8930##CC_GUI_COLOR_INSTR_AY8930";
    strings["TIA##CC_GUI_COLOR_INSTR_TIA"].plurals[0] = "TIA##CC_GUI_COLOR_INSTR_TIA";
    strings["SAA1099##CC_GUI_COLOR_INSTR_SAA1099"].plurals[0] = "SAA1099##CC_GUI_COLOR_INSTR_SAA1099";
    strings["VIC##CC_GUI_COLOR_INSTR_VIC"].plurals[0] = "VIC##CC_GUI_COLOR_INSTR_VIC";
    strings["PET##CC_GUI_COLOR_INSTR_PET"].plurals[0] = "PET##CC_GUI_COLOR_INSTR_PET";
    strings["VRC6##CC_GUI_COLOR_INSTR_VRC6"].plurals[0] = "VRC6##CC_GUI_COLOR_INSTR_VRC6";
    strings["VRC6 (saw)##CC_GUI_COLOR_INSTR_VRC6_SAW"].plurals[0] = "VRC6 (пила)##CC_GUI_COLOR_INSTR_VRC6_SAW";
    strings["FM (OPLL)##CC_GUI_COLOR_INSTR_OPLL"].plurals[0] = "FM (OPLL)##CC_GUI_COLOR_INSTR_OPLL";
    strings["FM (OPL)##CC_GUI_COLOR_INSTR_OPL"].plurals[0] = "FM (OPL)##CC_GUI_COLOR_INSTR_OPL";
    strings["FDS##CC_GUI_COLOR_INSTR_FDS"].plurals[0] = "FDS##CC_GUI_COLOR_INSTR_FDS";
    strings["Virtual Boy##CC_GUI_COLOR_INSTR_VBOY"].plurals[0] = "Virtual Boy##CC_GUI_COLOR_INSTR_VBOY";
    strings["Namco 163##CC_GUI_COLOR_INSTR_N163"].plurals[0] = "Namco 163##CC_GUI_COLOR_INSTR_N163";
    strings["Konami SCC##CC_GUI_COLOR_INSTR_SCC"].plurals[0] = "Konami SCC##CC_GUI_COLOR_INSTR_SCC";
    strings["FM (OPZ)##CC_GUI_COLOR_INSTR_OPZ"].plurals[0] = "FM (OPZ)##CC_GUI_COLOR_INSTR_OPZ";
    strings["POKEY##CC_GUI_COLOR_INSTR_POKEY"].plurals[0] = "POKEY##CC_GUI_COLOR_INSTR_POKEY";
    strings["PC Beeper##CC_GUI_COLOR_INSTR_BEEPER"].plurals[0] = "PC Beeper##CC_GUI_COLOR_INSTR_BEEPER";
    strings["WonderSwan##CC_GUI_COLOR_INSTR_SWAN"].plurals[0] = "WonderSwan##CC_GUI_COLOR_INSTR_SWAN";
    strings["Lynx##CC_GUI_COLOR_INSTR_MIKEY"].plurals[0] = "Lynx##CC_GUI_COLOR_INSTR_MIKEY";
    strings["VERA##CC_GUI_COLOR_INSTR_VERA"].plurals[0] = "VERA##CC_GUI_COLOR_INSTR_VERA";
    strings["X1-010##CC_GUI_COLOR_INSTR_X1_010"].plurals[0] = "X1-010##CC_GUI_COLOR_INSTR_X1_010";
    strings["ES5506##CC_GUI_COLOR_INSTR_ES5506"].plurals[0] = "ES5506##CC_GUI_COLOR_INSTR_ES5506";
    strings["MultiPCM##CC_GUI_COLOR_INSTR_MULTIPCM"].plurals[0] = "MultiPCM##CC_GUI_COLOR_INSTR_MULTIPCM";
    strings["SNES##CC_GUI_COLOR_INSTR_SNES"].plurals[0] = "SNES##CC_GUI_COLOR_INSTR_SNES";
    strings["Sound Unit##CC_GUI_COLOR_INSTR_SU"].plurals[0] = "Sound Unit##CC_GUI_COLOR_INSTR_SU";
    strings["Namco WSG##CC_GUI_COLOR_INSTR_NAMCO"].plurals[0] = "Namco WSG##CC_GUI_COLOR_INSTR_NAMCO";
    strings["FM (OPL Drums)##CC_GUI_COLOR_INSTR_OPL_DRUMS"].plurals[0] = "FM (OPL, ударные)##CC_GUI_COLOR_INSTR_OPL_DRUMS";
    strings["FM (OPM)##CC_GUI_COLOR_INSTR_OPM"].plurals[0] = "FM (OPM)##CC_GUI_COLOR_INSTR_OPM";
    strings["NES##CC_GUI_COLOR_INSTR_NES"].plurals[0] = "NES##CC_GUI_COLOR_INSTR_NES";
    strings["MSM6258##CC_GUI_COLOR_INSTR_MSM6258"].plurals[0] = "MSM6258##CC_GUI_COLOR_INSTR_MSM6258";
    strings["MSM6295##CC_GUI_COLOR_INSTR_MSM6295"].plurals[0] = "MSM6295##CC_GUI_COLOR_INSTR_MSM6295";
    strings["ADPCM-A##CC_GUI_COLOR_INSTR_ADPCMA"].plurals[0] = "ADPCM-A##CC_GUI_COLOR_INSTR_ADPCMA";
    strings["ADPCM-B##CC_GUI_COLOR_INSTR_ADPCMB"].plurals[0] = "ADPCM-B##CC_GUI_COLOR_INSTR_ADPCMB";
    strings["Sega PCM##CC_GUI_COLOR_INSTR_SEGAPCM"].plurals[0] = "Sega PCM##CC_GUI_COLOR_INSTR_SEGAPCM";
    strings["QSound##CC_GUI_COLOR_INSTR_QSOUND"].plurals[0] = "QSound##CC_GUI_COLOR_INSTR_QSOUND";
    strings["YMZ280B##CC_GUI_COLOR_INSTR_YMZ280B"].plurals[0] = "YMZ280B##CC_GUI_COLOR_INSTR_YMZ280B";
    strings["RF5C68##CC_GUI_COLOR_INSTR_RF5C68"].plurals[0] = "RF5C68##CC_GUI_COLOR_INSTR_RF5C68";
    strings["MSM5232##CC_GUI_COLOR_INSTR_MSM5232"].plurals[0] = "MSM5232##CC_GUI_COLOR_INSTR_MSM5232";
    strings["K007232##CC_GUI_COLOR_INSTR_K007232"].plurals[0] = "K007232##CC_GUI_COLOR_INSTR_K007232";
    strings["GA20##CC_GUI_COLOR_INSTR_GA20"].plurals[0] = "GA20##CC_GUI_COLOR_INSTR_GA20";
    strings["Pokémon Mini##CC_GUI_COLOR_INSTR_POKEMINI"].plurals[0] = "Pokémon Mini##CC_GUI_COLOR_INSTR_POKEMINI";
    strings["SM8521##CC_GUI_COLOR_INSTR_SM8521"].plurals[0] = "SM8521##CC_GUI_COLOR_INSTR_SM8521";
    strings["PV-1000##CC_GUI_COLOR_INSTR_PV1000"].plurals[0] = "PV-1000##CC_GUI_COLOR_INSTR_PV1000";
    strings["K053260##CC_GUI_COLOR_INSTR_K053260"].plurals[0] = "K053260##CC_GUI_COLOR_INSTR_K053260";
    strings["C140##CC_GUI_COLOR_INSTR_C140"].plurals[0] = "C140##CC_GUI_COLOR_INSTR_C140";
    strings["C219##CC_GUI_COLOR_INSTR_C219"].plurals[0] = "C219##CC_GUI_COLOR_INSTR_C219";
    strings["ESFM##CC_GUI_COLOR_INSTR_ESFM"].plurals[0] = "ESFM##CC_GUI_COLOR_INSTR_ESFM";
    strings["ES5503##CC_GUI_COLOR_INSTR_ES5503"].plurals[0] = "ES5503##CC_GUI_COLOR_INSTR_ES5503";
    strings["PowerNoise (noise)##CC_GUI_COLOR_INSTR_POWERNOISE"].plurals[0] = "PowerNoise (шум)##CC_GUI_COLOR_INSTR_POWERNOISE";
    strings["PowerNoise (slope)##CC_GUI_COLOR_INSTR_POWERNOISE_SLOPE"].plurals[0] = "PowerNoise (скат)##CC_GUI_COLOR_INSTR_POWERNOISE_SLOPE";
    strings["Other/Unknown##CC_GUI_COLOR_INSTR_UNKNOWN"].plurals[0] = "Другой/неизв.##CC_GUI_COLOR_INSTR_UNKNOWN";

    strings["Single color (background)##CC_GUI_COLOR_CHANNEL_BG"].plurals[0] = "Один цвет (фон)##CC_GUI_COLOR_CHANNEL_BG";
    strings["Single color (text)##CC_GUI_COLOR_CHANNEL_FG"].plurals[0] = "Один цвет (текст)##CC_GUI_COLOR_CHANNEL_FG";
    strings["FM##CC_GUI_COLOR_CHANNEL_FM"].plurals[0] = "FM##CC_GUI_COLOR_CHANNEL_FM";
    strings["Pulse##CC_GUI_COLOR_CHANNEL_PULSE"].plurals[0] = "Меандр##CC_GUI_COLOR_CHANNEL_PULSE";
    strings["Noise##CC_GUI_COLOR_CHANNEL_NOISE"].plurals[0] = "Шум##CC_GUI_COLOR_CHANNEL_NOISE";
    strings["PCM##CC_GUI_COLOR_CHANNEL_PCM"].plurals[0] = "ИКМ##CC_GUI_COLOR_CHANNEL_PCM";
    strings["Wave##CC_GUI_COLOR_CHANNEL_WAVE"].plurals[0] = "Волна##CC_GUI_COLOR_CHANNEL_WAVE";
    strings["FM operator##CC_GUI_COLOR_CHANNEL_OP"].plurals[0] = "FM-оператор##CC_GUI_COLOR_CHANNEL_OP";
    strings["Muted##CC_GUI_COLOR_CHANNEL_MUTED"].plurals[0] = "Заглушен##CC_GUI_COLOR_CHANNEL_MUTED";

    strings["Playhead##CC_GUI_COLOR_PATTERN_PLAY_HEAD"].plurals[0] = "Указатель воспроизведения##CC_GUI_COLOR_PATTERN_PLAY_HEAD";
    strings["Editing##CC_GUI_COLOR_EDITING"].plurals[0] = "Редактирование##CC_GUI_COLOR_EDITING";
    strings["Editing (will clone)##CC_GUI_COLOR_EDITING_CLONE"].plurals[0] = "Редактирование (будет клонирован)##CC_GUI_COLOR_EDITING_CLONE";
    strings["Cursor##CC_GUI_COLOR_PATTERN_CURSOR"].plurals[0] = "Курсор##CC_GUI_COLOR_PATTERN_CURSOR";
    strings["Cursor (hovered)##CC_GUI_COLOR_PATTERN_CURSOR_HOVER"].plurals[0] = "Курсор (мышь на курсоре)##CC_GUI_COLOR_PATTERN_CURSOR_HOVER";
    strings["Cursor (clicked)##CC_GUI_COLOR_PATTERN_CURSOR_ACTIVE"].plurals[0] = "Курсор (нажат)##CC_GUI_COLOR_PATTERN_CURSOR_ACTIVE";
    strings["Selection##CC_GUI_COLOR_PATTERN_SELECTION"].plurals[0] = "Выделение##CC_GUI_COLOR_PATTERN_SELECTION";
    strings["Selection (hovered)##CC_GUI_COLOR_PATTERN_SELECTION_HOVER"].plurals[0] = "Выделение (курсор мыши на выделении)##CC_GUI_COLOR_PATTERN_SELECTION_HOVER";
    strings["Selection (clicked)##CC_GUI_COLOR_PATTERN_SELECTION_ACTIVE"].plurals[0] = "Выделение (нажато)##CC_GUI_COLOR_PATTERN_SELECTION_ACTIVE";
    strings["Highlight 1##CC_GUI_COLOR_PATTERN_HI_1"].plurals[0] = "Подсветка 1##CC_GUI_COLOR_PATTERN_HI_1";
    strings["Highlight 2##CC_GUI_COLOR_PATTERN_HI_2"].plurals[0] = "Подсветка 2##CC_GUI_COLOR_PATTERN_HI_2";
    strings["Row number##CC_GUI_COLOR_PATTERN_ROW_INDEX"].plurals[0] = "Номер строки##CC_GUI_COLOR_PATTERN_ROW_INDEX";
    strings["Row number (highlight 1)##CC_GUI_COLOR_PATTERN_ROW_INDEX_HI1"].plurals[0] = "Номер строки (подсветка 1)##CC_GUI_COLOR_PATTERN_ROW_INDEX_HI1";
    strings["Row number (highlight 2)##CC_GUI_COLOR_PATTERN_ROW_INDEX_HI2"].plurals[0] = "Номер строки (подсветка 2)##CC_GUI_COLOR_PATTERN_ROW_INDEX_HI2";
    strings["Note##CC_GUI_COLOR_PATTERN_ACTIVE"].plurals[0] = "Нота##CC_GUI_COLOR_PATTERN_ACTIVE";
    strings["Note (highlight 1)##CC_GUI_COLOR_PATTERN_ACTIVE_HI1"].plurals[0] = "Нота (подсветка 1)##CC_GUI_COLOR_PATTERN_ACTIVE_HI1";
    strings["Note (highlight 2)##CC_GUI_COLOR_PATTERN_ACTIVE_HI2"].plurals[0] = "Нота (подсветка 2)##CC_GUI_COLOR_PATTERN_ACTIVE_HI2";
    strings["Blank##CC_GUI_COLOR_PATTERN_INACTIVE"].plurals[0] = "Пустая ячейка##CC_GUI_COLOR_PATTERN_INACTIVE";
    strings["Blank (highlight 1)##CC_GUI_COLOR_PATTERN_INACTIVE_HI1"].plurals[0] = "Пустая ячейка (подсветка 1)##CC_GUI_COLOR_PATTERN_INACTIVE_HI1";
    strings["Blank (highlight 2)##CC_GUI_COLOR_PATTERN_INACTIVE_HI2"].plurals[0] = "Пустая ячейка (подсветка 2)##CC_GUI_COLOR_PATTERN_INACTIVE_HI2";
    strings["Instrument##CC_GUI_COLOR_PATTERN_INS"].plurals[0] = "Инструмент##CC_GUI_COLOR_PATTERN_INS";
    strings["Instrument (invalid type)##CC_GUI_COLOR_PATTERN_INS_WARN"].plurals[0] = "Инструмент (неправильный тип)##CC_GUI_COLOR_PATTERN_INS_WARN";
    strings["Instrument (out of range)##CC_GUI_COLOR_PATTERN_INS_ERROR"].plurals[0] = "Инструмент (индекс не соответствует существующему инструменту)##CC_GUI_COLOR_PATTERN_INS_ERROR";
    strings["Volume (0%)##CC_GUI_COLOR_PATTERN_VOLUME_MIN"].plurals[0] = "Громкость (0%)##CC_GUI_COLOR_PATTERN_VOLUME_MIN";
    strings["Volume (50%)##CC_GUI_COLOR_PATTERN_VOLUME_HALF"].plurals[0] = "Громкость (50%)##CC_GUI_COLOR_PATTERN_VOLUME_HALF";
    strings["Volume (100%)##CC_GUI_COLOR_PATTERN_VOLUME_MAX"].plurals[0] = "Громкость (100%)##CC_GUI_COLOR_PATTERN_VOLUME_MAX";
    strings["Invalid effect##CC_GUI_COLOR_PATTERN_EFFECT_INVALID"].plurals[0] = "Неправильный индекс эффекта##CC_GUI_COLOR_PATTERN_EFFECT_INVALID";
    strings["Pitch effect##CC_GUI_COLOR_PATTERN_EFFECT_PITCH"].plurals[0] = "Эффект (частота)##CC_GUI_COLOR_PATTERN_EFFECT_PITCH";
    strings["Volume effect##CC_GUI_COLOR_PATTERN_EFFECT_VOLUME"].plurals[0] = "Эффект (громкость)##CC_GUI_COLOR_PATTERN_EFFECT_VOLUME";
    strings["Panning effect##CC_GUI_COLOR_PATTERN_EFFECT_PANNING"].plurals[0] = "Эффект (панорамирование)##CC_GUI_COLOR_PATTERN_EFFECT_PANNING";
    strings["Song effect##CC_GUI_COLOR_PATTERN_EFFECT_SONG"].plurals[0] = "Эффект (трек)##CC_GUI_COLOR_PATTERN_EFFECT_SONG";
    strings["Time effect##CC_GUI_COLOR_PATTERN_EFFECT_TIME"].plurals[0] = "Эффект (время)##CC_GUI_COLOR_PATTERN_EFFECT_TIME";
    strings["Speed effect##CC_GUI_COLOR_PATTERN_EFFECT_SPEED"].plurals[0] = "Эффект (громкость)##CC_GUI_COLOR_PATTERN_EFFECT_SPEED";
    strings["Primary specific effect##CC_GUI_COLOR_PATTERN_EFFECT_SYS_PRIMARY"].plurals[0] = "Основной эффект чипа##CC_GUI_COLOR_PATTERN_EFFECT_SYS_PRIMARY";
    strings["Secondary specific effect##CC_GUI_COLOR_PATTERN_EFFECT_SYS_SECONDARY"].plurals[0] = "Вспомогательный эффект чипа##CC_GUI_COLOR_PATTERN_EFFECT_SYS_SECONDARY";
    strings["Miscellaneous##CC_GUI_COLOR_PATTERN_EFFECT_MISC"].plurals[0] = "Эффект (рзное)##CC_GUI_COLOR_PATTERN_EFFECT_MISC";
    strings["External command output##CC_GUI_COLOR_EE_VALUE"].plurals[0] = "Вывод внешней команды##CC_GUI_COLOR_EE_VALUE";
    strings["Status: off/disabled##CC_GUI_COLOR_PATTERN_STATUS_OFF"].plurals[0] = "Статус: выкл./отключён##CC_GUI_COLOR_PATTERN_STATUS_OFF";
    strings["Status: off + macro rel##CC_GUI_COLOR_PATTERN_STATUS_REL"].plurals[0] = "Статус: выкл. + релиз макроса##CC_GUI_COLOR_PATTERN_STATUS_REL";
    strings["Status: on + macro rel##CC_GUI_COLOR_PATTERN_STATUS_REL_ON"].plurals[0] = "Статус: вкл. + релиз макроса##CC_GUI_COLOR_PATTERN_STATUS_REL_ON";
    strings["Status: on##CC_GUI_COLOR_PATTERN_STATUS_ON"].plurals[0] = "Статус: вкл.##CC_GUI_COLOR_PATTERN_STATUS_ON";
    strings["Status: volume##CC_GUI_COLOR_PATTERN_STATUS_VOLUME"].plurals[0] = "Статус: громкость##CC_GUI_COLOR_PATTERN_STATUS_VOLUME";
    strings["Status: pitch##CC_GUI_COLOR_PATTERN_STATUS_PITCH"].plurals[0] = "Статус: частота##CC_GUI_COLOR_PATTERN_STATUS_PITCH";
    strings["Status: panning##CC_GUI_COLOR_PATTERN_STATUS_PANNING"].plurals[0] = "Статус: панорамирование##CC_GUI_COLOR_PATTERN_STATUS_PANNING";
    strings["Status: chip (primary)##CC_GUI_COLOR_PATTERN_STATUS_SYS1"].plurals[0] = "Статус: основной эффект чипа##CC_GUI_COLOR_PATTERN_STATUS_SYS1";
    strings["Status: chip (secondary)##CC_GUI_COLOR_PATTERN_STATUS_SYS2"].plurals[0] = "Статус: вспомогательный эффект чипа##CC_GUI_COLOR_PATTERN_STATUS_SYS2";
    strings["Status: mixing##CC_GUI_COLOR_PATTERN_STATUS_MIXING"].plurals[0] = "Статус: микширование##CC_GUI_COLOR_PATTERN_STATUS_MIXING";
    strings["Status: DSP effect##CC_GUI_COLOR_PATTERN_STATUS_DSP"].plurals[0] = "Статус: эффект ЦОС##CC_GUI_COLOR_PATTERN_STATUS_DSP";
    strings["Status: note altering##CC_GUI_COLOR_PATTERN_STATUS_NOTE"].plurals[0] = "Статус: изменение ноты##CC_GUI_COLOR_PATTERN_STATUS_NOTE";
    strings["Status: misc color 1##CC_GUI_COLOR_PATTERN_STATUS_MISC1"].plurals[0] = "Статус: разное (цвет 1)##CC_GUI_COLOR_PATTERN_STATUS_MISC1";
    strings["Status: misc color 2##CC_GUI_COLOR_PATTERN_STATUS_MISC2"].plurals[0] = "Статус: разное (цвет 2)##CC_GUI_COLOR_PATTERN_STATUS_MISC2";
    strings["Status: misc color 3##CC_GUI_COLOR_PATTERN_STATUS_MISC3"].plurals[0] = "Статус: разное (цвет 3)##CC_GUI_COLOR_PATTERN_STATUS_MISC3";
    strings["Status: attack##CC_GUI_COLOR_PATTERN_STATUS_ATTACK"].plurals[0] = "Статус: атака##CC_GUI_COLOR_PATTERN_STATUS_ATTACK";
    strings["Status: decay##CC_GUI_COLOR_PATTERN_STATUS_DECAY"].plurals[0] = "Статус: спад##CC_GUI_COLOR_PATTERN_STATUS_DECAY";
    strings["Status: sustain##CC_GUI_COLOR_PATTERN_STATUS_SUSTAIN"].plurals[0] = "Статус: сустейн##CC_GUI_COLOR_PATTERN_STATUS_SUSTAIN";
    strings["Status: release##CC_GUI_COLOR_PATTERN_STATUS_RELEASE"].plurals[0] = "Статус: релиз##CC_GUI_COLOR_PATTERN_STATUS_RELEASE";
    strings["Status: decrease linear##CC_GUI_COLOR_PATTERN_STATUS_DEC_LINEAR"].plurals[0] = "Статус: линейное уменьшение##CC_GUI_COLOR_PATTERN_STATUS_DEC_LINEAR";
    strings["Status: decrease exp##CC_GUI_COLOR_PATTERN_STATUS_DEC_EXP"].plurals[0] = "Статус: экспоненциальное уменьшение##CC_GUI_COLOR_PATTERN_STATUS_DEC_EXP";
    strings["Status: increase##CC_GUI_COLOR_PATTERN_STATUS_INC"].plurals[0] = "Статус: увеличение##CC_GUI_COLOR_PATTERN_STATUS_INC";
    strings["Status: bent##CC_GUI_COLOR_PATTERN_STATUS_BENT"].plurals[0] = "Статус: изменена частота##CC_GUI_COLOR_PATTERN_STATUS_BENT";
    strings["Status: direct##CC_GUI_COLOR_PATTERN_STATUS_DIRECT"].plurals[0] = "Статус: прямой##CC_GUI_COLOR_PATTERN_STATUS_DIRECT";

    strings["Background##CC_GUI_COLOR_SAMPLE_BG"].plurals[0] = "Фон##CC_GUI_COLOR_SAMPLE_BG";
    strings["Waveform##CC_GUI_COLOR_SAMPLE_FG"].plurals[0] = "Волна##CC_GUI_COLOR_SAMPLE_FG";
    strings["Time background##CC_GUI_COLOR_SAMPLE_TIME_BG"].plurals[0] = "Фон поля времени##CC_GUI_COLOR_SAMPLE_TIME_BG";
    strings["Time text##CC_GUI_COLOR_SAMPLE_TIME_FG"].plurals[0] = "Текст поля времени##CC_GUI_COLOR_SAMPLE_TIME_FG";
    strings["Loop region##CC_GUI_COLOR_SAMPLE_LOOP"].plurals[0] = "Зацикленная часть##CC_GUI_COLOR_SAMPLE_LOOP";
    strings["Center guide##CC_GUI_COLOR_SAMPLE_CENTER"].plurals[0] = "Центральная полоса##CC_GUI_COLOR_SAMPLE_CENTER";
    strings["Grid##CC_GUI_COLOR_SAMPLE_GRID"].plurals[0] = "Сетка##CC_GUI_COLOR_SAMPLE_GRID";
    strings["Selection##CC_GUI_COLOR_SAMPLE_SEL"].plurals[0] = "Выделение##CC_GUI_COLOR_SAMPLE_SEL";
    strings["Selection points##CC_GUI_COLOR_SAMPLE_SEL_POINT"].plurals[0] = "Границы выделения##CC_GUI_COLOR_SAMPLE_SEL_POINT";
    strings["Preview needle##CC_GUI_COLOR_SAMPLE_NEEDLE"].plurals[0] = "Курсор воспроизведения превью##CC_GUI_COLOR_SAMPLE_NEEDLE";
    strings["Playing needles##CC_GUI_COLOR_SAMPLE_NEEDLE_PLAYING"].plurals[0] = "Курсоры воспроизведения##CC_GUI_COLOR_SAMPLE_NEEDLE_PLAYING";
    strings["Loop markers##CC_GUI_COLOR_SAMPLE_LOOP_POINT"].plurals[0] = "Маркеры зацикливания##CC_GUI_COLOR_SAMPLE_LOOP_POINT";
    strings["Chip select: disabled##CC_GUI_COLOR_SAMPLE_CHIP_DISABLED"].plurals[0] = "Выбор чипа: выкл.##CC_GUI_COLOR_SAMPLE_CHIP_DISABLED";
    strings["Chip select: enabled##CC_GUI_COLOR_SAMPLE_CHIP_ENABLED"].plurals[0] = "Выбор чипа: вкл.##CC_GUI_COLOR_SAMPLE_CHIP_ENABLED";
    strings["Chip select: enabled (failure)##CC_GUI_COLOR_SAMPLE_CHIP_WARNING"].plurals[0] = "Выбор чипа: вкл. (ошибка)##CC_GUI_COLOR_SAMPLE_CHIP_WARNING";

    strings["Unallocated##CC_GUI_COLOR_PAT_MANAGER_NULL"].plurals[0] = "Паттерн не используется и память под него не выделена##CC_GUI_COLOR_PAT_MANAGER_NULL";
    strings["Unused##CC_GUI_COLOR_PAT_MANAGER_UNUSED"].plurals[0] = "Паттерн не используется##CC_GUI_COLOR_PAT_MANAGER_UNUSED";
    strings["Used##CC_GUI_COLOR_PAT_MANAGER_USED"].plurals[0] = "Паттерн используется##CC_GUI_COLOR_PAT_MANAGER_USED";
    strings["Overused##CC_GUI_COLOR_PAT_MANAGER_OVERUSED"].plurals[0] = "Паттерн используется очень часто##CC_GUI_COLOR_PAT_MANAGER_OVERUSED";
    strings["Really overused##CC_GUI_COLOR_PAT_MANAGER_EXTREMELY_OVERUSED"].plurals[0] = "Паттерн используется крайне часто##CC_GUI_COLOR_PAT_MANAGER_EXTREMELY_OVERUSED";
    strings["Combo Breaker##CC_GUI_COLOR_PAT_MANAGER_COMBO_BREAKER"].plurals[0] = "Число использований паттерна больше, чем длина трека!##CC_GUI_COLOR_PAT_MANAGER_COMBO_BREAKER";

    strings["Background##CC_GUI_COLOR_PIANO_BACKGROUND"].plurals[0] = "Фон##CC_GUI_COLOR_PIANO_BACKGROUND";
    strings["Upper key##CC_GUI_COLOR_PIANO_KEY_TOP"].plurals[0] = "Верхние клавиши##CC_GUI_COLOR_PIANO_KEY_TOP";
    strings["Upper key (feedback)##CC_GUI_COLOR_PIANO_KEY_TOP_HIT"].plurals[0] = "Верхние клавиши (обратная связь)##CC_GUI_COLOR_PIANO_KEY_TOP_HIT";
    strings["Upper key (pressed)##CC_GUI_COLOR_PIANO_KEY_TOP_ACTIVE"].plurals[0] = "Верхние клавиши (нажатые)##CC_GUI_COLOR_PIANO_KEY_TOP_ACTIVE";
    strings["Lower key##CC_GUI_COLOR_PIANO_KEY_BOTTOM"].plurals[0] = "Нижние клавиши##CC_GUI_COLOR_PIANO_KEY_BOTTOM";
    strings["Lower key (feedback)##CC_GUI_COLOR_PIANO_KEY_BOTTOM_HIT"].plurals[0] = "Нижние клавиши (обратная связь)##CC_GUI_COLOR_PIANO_KEY_BOTTOM_HIT";
    strings["Lower key (pressed)##CC_GUI_COLOR_PIANO_KEY_BOTTOM_ACTIVE"].plurals[0] = "Нижние клавиши (нажатые)##CC_GUI_COLOR_PIANO_KEY_BOTTOM_ACTIVE";

    strings["Clock text##CC_GUI_COLOR_CLOCK_TEXT"].plurals[0] = "Текст часов##CC_GUI_COLOR_CLOCK_TEXT";
    strings["Beat (off)##CC_GUI_COLOR_CLOCK_BEAT_LOW"].plurals[0] = "Слабая доля##CC_GUI_COLOR_CLOCK_BEAT_LOW";
    strings["Beat (on)##CC_GUI_COLOR_CLOCK_BEAT_HIGH"].plurals[0] = "Сильная доля##CC_GUI_COLOR_CLOCK_BEAT_HIGH";

    strings["PortSet##CC_GUI_COLOR_PATCHBAY_PORTSET"].plurals[0] = "Группа портов##CC_GUI_COLOR_PATCHBAY_PORTSET";
    strings["Port##CC_GUI_COLOR_PATCHBAY_PORT"].plurals[0] = "Порт##CC_GUI_COLOR_PATCHBAY_PORT";
    strings["Port (hidden/unavailable)##CC_GUI_COLOR_PATCHBAY_PORT_HIDDEN"].plurals[0] = "Порт (скрыт/недоступен)##CC_GUI_COLOR_PATCHBAY_PORT_HIDDEN";
    strings["Connection (selected)##CC_GUI_COLOR_PATCHBAY_CONNECTION"].plurals[0] = "Соединение (выделенное)##CC_GUI_COLOR_PATCHBAY_CONNECTION";
    strings["Connection (other)##CC_GUI_COLOR_PATCHBAY_CONNECTION_BG"].plurals[0] = "Соединение (обычное)##CC_GUI_COLOR_PATCHBAY_CONNECTION_BG";

    strings["Log level: Error##CC_GUI_COLOR_LOGLEVEL_ERROR"].plurals[0] = "Уровень лога: ошибка##CC_GUI_COLOR_LOGLEVEL_ERROR";
    strings["Log level: Warning##CC_GUI_COLOR_LOGLEVEL_WARNING"].plurals[0] = "Уровень лога: предупреждение##CC_GUI_COLOR_LOGLEVEL_WARNING";
    strings["Log level: Info##CC_GUI_COLOR_LOGLEVEL_INFO"].plurals[0] = "Уровень лога: информация##CC_GUI_COLOR_LOGLEVEL_INFO";
    strings["Log level: Debug##CC_GUI_COLOR_LOGLEVEL_DEBUG"].plurals[0] = "Уровень лога: отладка##CC_GUI_COLOR_LOGLEVEL_DEBUG";
    strings["Log level: Trace/Verbose##CC_GUI_COLOR_LOGLEVEL_TRACE"].plurals[0] = "Уровень лога: диагностика/подробный##CC_GUI_COLOR_LOGLEVEL_TRACE";

    strings["OK##SettingsOK"].plurals[0] = "ОК##SettingsOK";
    strings["Cancel##SettingsCancel"].plurals[0] = "Отмена##SettingsCancel";
    strings["Apply##SettingsApply"].plurals[0] = "Применить##SettingsApply";

    //src/gui/util.cpp

    strings["<nothing>##sgut"].plurals[0] = "<ничего>";
    strings["Unknown##sgut0"].plurals[0] = "Неизв.";
    strings["Unknown##sgut1"].plurals[0] = "Неизв.";
    
    //   sgiPCMA  src/gui/inst/adpcma.cpp

    strings["Macros##sgiPCMA"].plurals[0] = "Макросы";
    strings["Volume##sgiPCMA"].plurals[0] = "Громкость";
    strings["Global Volume##sgiPCMA"].plurals[0] = "Глобальная громкость";
    strings["Panning##sgiPCMA"].plurals[0] = "Панорамирование";
    strings["Phase Reset##sgiPCMA"].plurals[0]  = "Сброс фазы";

    //   sgiPCMB   src/gui/inst/adpcmb.cpp

    strings["Macros##sgiPCMB"].plurals[0] = "Макросы";
    strings["Volume##sgiPCMB"].plurals[0] = "Громкость";
    strings["Arpeggio##sgiPCMB"].plurals[0] = "Арпеджио";
    strings["Pitch##sgiPCMB"].plurals[0] = "Частота";
    strings["Panning##sgiPCMB"].plurals[0] = "Панорамирование";
    strings["Phase Reset##sgiPCMB"].plurals[0]  = "Сброс фазы";

    //   sgiSAMPLE src/gui/inst/amiga.cpp

    strings["Macros##sgiSAMPLE"].plurals[0] = "Макросы";
    strings["Volume##sgiSAMPLE"].plurals[0] = "Громкость";
    strings["Arpeggio##sgiSAMPLE"].plurals[0] = "Арпеджио";
    strings["Pitch##sgiSAMPLE"].plurals[0] = "Частота";
    strings["Panning##sgiSAMPLE"].plurals[0] = "Панорамирование";
    strings["Panning (left)##sgiSAMPLE"].plurals[0] = "Панорамирование (лево)";
    strings["Surround##sgiSAMPLE"].plurals[0] = "Окружающее звучание";
    strings["Panning (right)##sgiSAMPLE"].plurals[0] = "Панорамирование (право)";
    strings["Waveform##sgiSAMPLE"].plurals[0] = "Волна";
    strings["Phase Reset##sgiSAMPLE"].plurals[0]  = "Сброс фазы";

    //   sgiAY     src/gui/inst/ay.cpp

    strings["Macros##sgiAY"].plurals[0] = "Макросы";
    strings["Volume##sgiAY"].plurals[0] = "Громкость";
    strings["Arpeggio##sgiAY"].plurals[0] = "Арпеджио";
    strings["Pitch##sgiAY"].plurals[0] = "Частота";
    strings["Noise Freq##sgiAY"].plurals[0] = "Частота шума";
    strings["Waveform##sgiAY"].plurals[0] = "Волна";
    strings["Phase Reset##sgiAY"].plurals[0]  = "Сброс фазы";
    strings["Envelope##sgiAY"].plurals[0] = "Огибающая";
    strings["AutoEnv Num##sgiAY"].plurals[0] = "Множ. част. авто-огиб.";
    strings["AutoEnv Den##sgiAY"].plurals[0] = "Дел. част. авто-огиб.";

    //   sgi8930   src/gui/inst/ay8930.cpp

    strings["Macros##sgi8930"].plurals[0] = "Макросы";
    strings["Volume##sgi8930"].plurals[0] = "Громкость";
    strings["Arpeggio##sgi8930"].plurals[0] = "Арпеджио";
    strings["Pitch##sgi8930"].plurals[0] = "Частота";
    strings["Noise Freq##sgi8930"].plurals[0] = "Частота шума";
    strings["Waveform##sgi8930"].plurals[0] = "Волна";
    strings["Phase Reset##sgi8930"].plurals[0]  = "Сброс фазы";
    strings["Duty##sgi8930"].plurals[0] = "Скважность";
    strings["Envelope##sgi8930"].plurals[0] = "Огибающая";
    strings["AutoEnv Num##sgi8930"].plurals[0] = "Множ. част. авто-огиб.";
    strings["AutoEnv Den##sgi8930"].plurals[0] = "Дел. част. авто-огиб.";
    strings["Noise AND Mask##sgi8930"].plurals[0] = "Маска шума (И)";
    strings["Noise OR Mask##sgi8930"].plurals[0] = "Маска шума (ИЛИ)";

    //   sgiB      src/gui/inst/beeper.cpp

    strings["Macros##sgiB"].plurals[0] = "Макросы";
    strings["Volume##sgiB"].plurals[0] = "Громкость";
    strings["Arpeggio##sgiB"].plurals[0] = "Арпеджио";
    strings["Pitch##sgiB"].plurals[0] = "Частота";
    strings["Pulse Width##sgiB"].plurals[0] = "Скважность";

    //   sgiC140   src/gui/inst/c140.cpp

    strings["Macros##sgiC140"].plurals[0] = "Макросы";
    strings["Volume##sgiC140"].plurals[0] = "Громкость";
    strings["Arpeggio##sgiC140"].plurals[0] = "Арпеджио";
    strings["Pitch##sgiC140"].plurals[0] = "Частота";
    strings["Panning (left)##sgiC140"].plurals[0] = "Панорамирование (лево)";
    strings["Panning (right)##sgiC140"].plurals[0] = "Панорамирование (право)";
    strings["Phase Reset##sgiC140"].plurals[0] = "Сброс фазы";

    //   sgiC219   src/gui/inst/c219.cpp

    strings["Macros##sgiC219"].plurals[0] = "Макросы";
    strings["Volume##sgiC219"].plurals[0] = "Громкость";
    strings["Arpeggio##sgiC219"].plurals[0] = "Арпеджио";
    strings["Pitch##sgiC219"].plurals[0] = "Частота";
    strings["Control##sgiC219"].plurals[0] = "Управление";
    strings["Panning (left)##sgiC219"].plurals[0] = "Панорамирование (лево)";
    strings["Panning (right)##sgiC219"].plurals[0] = "Панорамирование (право)";
    strings["Phase Reset##sgiC219"].plurals[0] = "Сброс фазы";

    //   sgiC64    src/gui/inst/c64.cpp

    strings["Waveform##sgiC640"].plurals[0] = "Волна";
    strings["tri##sgiC64"].plurals[0] = "треуг.";
    strings["saw##sgiC64"].plurals[0] = "пила";
    strings["pulse##sgiC64"].plurals[0] = "меандр";
    strings["noise##sgiC64"].plurals[0] = "шум";
    strings["A##sgiC640"].plurals[0] = "А";
    strings["A##sgiC641"].plurals[0] = "А";
    strings["D##sgiC640"].plurals[0] = "С";
    strings["D##sgiC641"].plurals[0] = "С";
    strings["S##sgiC640"].plurals[0] = "С";
    strings["S##sgiC641"].plurals[0] = "С";
    strings["R##sgiC640"].plurals[0] = "Р";
    strings["R##sgiC641"].plurals[0] = "Р";
    strings["Envelope##sgiC640"].plurals[0] = "Огибающая";
    strings["Envelope##sgiC641"].plurals[0] = "Огибающая";
    strings["Duty##sgiC640"].plurals[0] = "Скважность";
    strings["Ring Modulation##sgiC64"].plurals[0] = "Кольцевая модуляция";
    strings["Oscillator Sync##sgiC64"].plurals[0] = "Синхронизация осцилляторов";
    strings["Enable filter##sgiC64"].plurals[0] = "Включить фильтр";
    strings["Initialize filter##sgiC64"].plurals[0] = "Инициализировать фильтр";
    strings["Cutoff##sgiC640"].plurals[0] = "Частота среза";
    strings["Resonance##sgiC640"].plurals[0] = "Резонанс (добротность)";
    strings["Filter Mode##sgiC640"].plurals[0] = "Тип фильтра";
    strings["low##sgiC64"].plurals[0] = "ФНЧ";
    strings["band##sgiC64"].plurals[0] = "ППФ";
    strings["high##sgiC64"].plurals[0] = "ФВЧ";
    strings["ch3off##sgiC64"].plurals[0] = "выкл. 3 кан.";
    strings["Absolute Cutoff Macro##sgiC64"].plurals[0] = "Абсолютный макрос частоты среза";
    strings["Absolute Duty Macro##sgiC64"].plurals[0] = "Абсолютный макрос скважности";
    strings["Don't test before new note##sgiC64"].plurals[0] = "Не включать тестовый бит перед новой нотой";
    strings["Macros##sgiC64"].plurals[0] = "Макросы";
    strings["Volume##sgiC64"].plurals[0] = "Громкость";
    strings["Arpeggio##sgiC64"].plurals[0] = "Арпеджио";
    strings["Pitch##sgiC64"].plurals[0] = "Частота";
    strings["Duty##sgiC641"].plurals[0] = "Скважность";
    strings["Waveform##sgiC641"].plurals[0] = "Волна";
    strings["Cutoff##sgiC641"].plurals[0] = "Частота среза";
    strings["Filter Mode##sgiC641"].plurals[0] = "Тип фильтра";
    strings["Filter Toggle##sgiC64"].plurals[0] = "Вкл./выкл. фильтр";
    strings["Resonance##sgiC641"].plurals[0] = "Резонанс";
    strings["Special##sgiC64"].plurals[0] = "Разное";
    strings["Attack##sgiC64"].plurals[0] = "Атака";
    strings["Decay##sgiC64"].plurals[0] = "Спад";
    strings["Sustain##sgiC64"].plurals[0] = "Сустейн";
    strings["Release##sgiC64"].plurals[0] = "Релиз";

    //   sgi5503   src/gui/inst/es5503.cpp

    strings["Oscillator mode:##sgi5503"].plurals[0] = "Режим осциллятора:";
    strings["Freerun##sgi5503"].plurals[0] = "Свободн. (зацикл.)";
    strings["Oneshot##sgi5503"].plurals[0] = "Однократн.";
    strings["Sync/AM##sgi5503"].plurals[0] = "Синхр./АМ";
    strings["Swap##sgi5503"].plurals[0] = "Смена";
    strings["Virtual softpan channel##sgi5503"].plurals[0] = "Виртуальный стерео-канал";
    strings["Combines odd and next even channel into one virtual channel with 256-step panning.\nInstrument, volume and effects need to be placed on the odd channel (e.g. 1st, 3rd, 5th etc.)##sgi5503"].plurals[0] = "Использует нечётный и следующий за ним чётный канал для создания виртуального канала с возможностью плавного панорамирования (256 шагов).\nНоты, инструменты, команды громкости и эффекты необходимо размещать в нечётном канале (1-ый, 3-ий и т.д.)";
    strings["Phase reset on key-on##sgi5503"].plurals[0] = "Сброс фазы в начале ноты";
    strings["Macros##sgi5503"].plurals[0] = "Макросы";
    strings["Volume##sgi5503"].plurals[0] = "Громкость";
    strings["Arpeggio##sgi5503"].plurals[0] = "Арпеджио";
    strings["Pitch##sgi5503"].plurals[0] = "Частота";
    strings["Osc. mode##sgi5503"].plurals[0] = "Реж. осцилл.";
    strings["Panning (left)##sgi5503"].plurals[0] = "Панорамирование (лево)";
    strings["Panning (right)##sgi5503"].plurals[0] = "Панорамирование (право)";
    strings["Waveform##sgi5503"].plurals[0] = "Волна";
    strings["Phase Reset##sgi5503"].plurals[0] = "Сброс фазы";
    strings["Wave/sample pos.##sgi5503"].plurals[0] = "Полож. волны/сэмпла в памяти";
    strings["Osc. output##sgi5503"].plurals[0] = "Вывод осцилл.";

    //   sgiOTTO   src/gui/inst/es5506.cpp

    strings["Filter Mode##sgiOTTO0"].plurals[0] = "Режим фильтра";
    strings["Filter K1##sgiOTTO0"].plurals[0] = "K1 фильтра";
    strings["Filter K2##sgiOTTO0"].plurals[0] = "K2 фильтра";
    strings["Envelope count##sgiOTTO"].plurals[0] = "Длина огиб.";
    strings["Left Volume Ramp##sgiOTTO"].plurals[0] = "Нараст. лев. громк.";
    strings["Right Volume Ramp##sgiOTTO"].plurals[0] = "Нараст. прав. громк.";
    strings["Filter K1 Ramp##sgiOTTO"].plurals[0] = "Нараст. K1 фильтра";
    strings["Filter K2 Ramp##sgiOTTO"].plurals[0] = "Нараст. K2 фильтра";
    strings["K1 Ramp Slowdown##sgiOTTO"].plurals[0] = "Замедл. нараст. K1";
    strings["K2 Ramp Slowdown##sgiOTTO"].plurals[0] = "Замедл. нараст. K2";
    strings["Macros##sgiOTTO"].plurals[0] = "Макросы";
    strings["Volume##sgiOTTO"].plurals[0] = "Громкость";
    strings["Arpeggio##sgiOTTO"].plurals[0] = "Арпеджио";
    strings["Pitch##sgiOTTO"].plurals[0] = "Частота";
    strings["Panning (left)##sgiOTTO"].plurals[0] = "Панорамирование (лево)";
    strings["Panning (right)##sgiOTTO"].plurals[0] = "Панорамирование (право)";
    strings["Phase Reset##sgiOTTO"].plurals[0] = "Сброс фазы";
    strings["Filter Mode##sgiOTTO1"].plurals[0] = "Режим фильтра";
    strings["Filter K1##sgiOTTO1"].plurals[0] = "K1 фильтра";
    strings["Filter K2##sgiOTTO1"].plurals[0] = "K2 фильтра";
    strings["Outputs##sgiOTTO"].plurals[0] = "Выводы";
    strings["Control##sgiOTTO"].plurals[0] = "Управление";

    //   sgiESFM   src/gui/inst/esfm.cpp

    strings["Other##sgiESFM0"].plurals[0] = "Другое";
    strings["Other##sgiESFM1"].plurals[0] = "Другое";
    strings["Envelope##sgiESFM0"].plurals[0] = "Огибающая";
    strings["Envelope##sgiESFM1"].plurals[0] = "Огибающая";
    strings["op%d##sgiESFM0"].plurals[0] = "оп%d";
    strings["OP%d##sgiESFM1"].plurals[0] = "ОП%d";
    strings["Detune in semitones##sgiESFM0"].plurals[0] = "Расстройка в полутонах";
    strings["Detune in fractions of semitone.\n128 = +1 semitone, -128 = -1 semitone.##sgiESFM0"].plurals[0] = "Расстройка в долях полутона.\n128 = +1 полутон, -128 = -1 полутон.";
    strings["If operator outputs sound, enable left channel output.##sgiESFM0"].plurals[0] = "Включить вывод звука в левый канал.";
    strings["If operator outputs sound, enable right channel output.##sgiESFM0"].plurals[0] = "Включить вывод звука в правый канал.";
    strings["Block##sgiESFM0"].plurals[0] = "Блок";
    strings["FreqNum##sgiESFM0"].plurals[0] = "Частота";
    strings["op%d##sgiESFM2"].plurals[0] = "оп%d";
    strings["Operator %d##sgiESFM"].plurals[0] = "Оператор %d";
    strings["Waveform##sgiESFM"].plurals[0] = "Волна";
    strings["Envelope##sgiESFM"].plurals[0] = "Огибающая";
    strings["Blk##sgiESFM"].plurals[0] = "Блк";
    strings["Block##sgiESFM1"].plurals[0] = "Блок";
    strings["F##sgiESFM"].plurals[0] = "Ч";
    strings["Frequency (F-Num)##sgiESFM"].plurals[0] = "Частота (F-Num)";
    strings["Detune in semitones##sgiESFM1"].plurals[0] = "Расстройка в полутонах";
    strings["Detune in fractions of semitone.\n128 = +1 semitone, -128 = -1 semitone.##sgiESFM1"].plurals[0] = "Расстройка в долях полутона.\n128 = +1 полутон, -128 = -1 полутон.";
    strings["If operator outputs sound, enable left channel output.##sgiESFM1"].plurals[0] = "Включить вывод звука в левый канал.";
    strings["If operator outputs sound, enable right channel output.##sgiESFM1"].plurals[0] = "Включить вывод звука в правый канал.";
    strings["op%d##sgiESFM3"].plurals[0] = "оп%d";
    strings["OP%d##sgiESFM4"].plurals[0] = "ОП%d";
    strings["Block##sgiESFM2"].plurals[0] = "Блок";
    strings["FreqNum##sgiESFM1"].plurals[0] = "Частота";
    strings["Detune in semitones##sgiESFM2"].plurals[0] = "Расстройка в полутонах";
    strings["Detune in fractions of semitone.\n128 = +1 semitone, -128 = -1 semitone.##sgiESFM2"].plurals[0] = "Расстройка в долях полутона.\n128 = +1 полутон, -128 = -1 полутон.";
    strings["If operator outputs sound, enable left channel output.##sgiESFM2"].plurals[0] = "Включить вывод звука в левый канал.";
    strings["If operator outputs sound, enable right channel output.##sgiESFM2"].plurals[0] = "Включить вывод звука в правый канал.";
    strings["OP%d Macros##sgiESFM"].plurals[0] = "Макросы ОП%d";
    strings["Block##sgiESFM3"].plurals[0] = "Блок";
    strings["FreqNum##sgiESFM2"].plurals[0] = "Частота";
    strings["Op. Arpeggio##sgiESFM"].plurals[0] = "Арпеджио оператора";
    strings["Op. Pitch##sgiESFM"].plurals[0] = "Частота оператора";
    strings["Op. Panning##sgiESFM"].plurals[0] = "Панорамирование оператора";
    strings["Macros##sgiESFM"].plurals[0] = "Макросы";
    strings["Volume##sgiESFM"].plurals[0] = "Громкость";
    strings["Arpeggio##sgiESFM"].plurals[0] = "Арпеджио";
    strings["Pitch##sgiESFM"].plurals[0] = "Частота";
    strings["OP4 Noise Mode##sgiESFM"].plurals[0] = "Режим шума ОП4";
    strings["Panning##sgiESFM"].plurals[0] = "Панорамирование";
    strings["Phase Reset##sgiESFM"].plurals[0] = "Сброс фазы";

    //   sgiFDS    src/gui/inst/fds.cpp

    strings["Compatibility mode##sgiFDS"].plurals[0] = "Режим совместимости";
    strings["only use for compatibility with .dmf modules!\n- initializes modulation table with first wavetable\n- does not alter modulation parameters on instrument change##sgiFDS"].plurals[0] = "только для совместимости с модулями .dmf!\n- инициализирует волновую таблицу модулятора первой волновой таблицей\n- не изменяет параметры модуляции при смене инструмента";
    strings["Modulation depth##sgiFDS"].plurals[0] = "Глубина модуляции";
    strings["Modulation speed##sgiFDS"].plurals[0] = "Скорость модуляции";
    strings["Modulation table##sgiFDS"].plurals[0] = "Волновая таблица модуляции";
    strings["Macros##sgiFDS"].plurals[0] = "Макросы";
    strings["Volume##sgiFDS"].plurals[0] = "Громкость";
    strings["Arpeggio##sgiFDS"].plurals[0] = "Арпеджио";
    strings["Pitch##sgiFDS"].plurals[0] = "Частота";
    strings["Waveform##sgiFDS"].plurals[0] = "Волна";
    strings["Mod Depth##sgiFDS"].plurals[0] = "Глуб. мод.";
    strings["Mod Speed##sgiFDS"].plurals[0] = "Скор. мод.";
    strings["Mod Position##sgiFDS"].plurals[0] = "Полож. мод.";

    //   sgifmeu   src/gui/inst/fmEnvUtil.cpp

    strings["left click to restart\nmiddle click to pause\nright click to see algorithm##sgifmeu"].plurals[0] = "ЛКМ для перезапуска\nНажмите колёсико, чтобы поставить на паузу\nПКМ для переключения на визуализацию алгоритма";
    strings["left click to configure TL scaling\nright click to see FM preview##sgifmeu"].plurals[0] = "ЛКМ для конфигурации масштабирования громкости операторов\nПКМ для переключения на превью FM-сигнала";
    strings["right click to see FM preview##sgifmeu"].plurals[0] = "ПКМ для переключения на превью FM-сигнала";
    strings["operator level changes with volume?##sgifmeu"].plurals[0] = "Громкость оператора зависит от общей громкости?";
    strings["AUTO##OPKVS"].plurals[0] = "АВТО##OPKVS";
    strings["NO##OPKVS"].plurals[0] = "НЕТ##OPKVS";
    strings["YES##OPKVS"].plurals[0] = "ДА##OPKVS";

    //   sgifmeh   src/gui/inst/fmEnvUtil.h

    strings["(copying)##sgifmeh"].plurals[0] = "(копирование)";
    strings["(swapping)##sgifmeh"].plurals[0] = "(замена)";
    strings["- drag to swap operator\n- shift-drag to copy operator##sgifmeh"].plurals[0] = "- перетащите, чтобы поменять настройки операторов местами\n- перетащите с зажатой клавишей SHIFT, чтобы скопировать настройки оператораshift-drag to copy operator";

    //   sgiGA20   src/gui/inst/ga20.cpp

    strings["Macros##sgiGA20"].plurals[0] = "Макросы";
    strings["Volume##sgiGA20"].plurals[0] = "Громкость";
    strings["Arpeggio##sgiGA20"].plurals[0] = "Арпеджио";
    strings["Pitch##sgiGA20"].plurals[0] = "Частота";
    strings["Phase Reset##sgiGA20"].plurals[0] = "Сброс фазы";
    
    //   sgiGB     src/gui/inst/gb.cpp

    strings["Game Boy##sgiGB"].plurals[0] = "Game Boy";
    strings["Use software envelope##sgiGB"].plurals[0] = "Использовать программную огибающую громкости";
    strings["Initialize envelope on every note##sgiGB"].plurals[0] = "Инициализировать огибающую на каждой ноте";
    strings["Volume##sgiGB0"].plurals[0] = "Громкость";
    strings["Length##sgiGB"].plurals[0] = "Длина";
    strings["Sound Length##sgiGB"].plurals[0] = "Длина звука";
    strings["Direction##sgiGB"].plurals[0] = "Направление";
    strings["Up##sgiGB0"].plurals[0] = "Вверх";
    strings["Down##sgiGB0"].plurals[0] = "Вниз";
    strings["Hardware Sequence##sgiGB"].plurals[0] = "Аппаратная последовательность";
    strings["Tick##sgiGB"].plurals[0] = "Шаг движка";
    strings["Command##sgiGB"].plurals[0] = "Команда";
    strings["Move/Remove##sgiGB"].plurals[0] = "Перем./Удал.";
    strings["Volume##sgiGB1"].plurals[0] = "Громкость";
    strings["Env Length##sgiGB"].plurals[0] = "Длина огибающей";
    strings["Sound Length##sgiGB"].plurals[0] = "Длина звука";
    strings["Up##sgiGB1"].plurals[0] = "Вверх";
    strings["Down##sgiGB1"].plurals[0] = "Вниз";
    strings["Shift##sgiGB"].plurals[0] = "На сколько";
    strings["Speed##sgiGB"].plurals[0] = "Скорость";
    strings["Up##sgiGB2"].plurals[0] = "Вверх";
    strings["Down##sgiGB2"].plurals[0] = "Вниз";
    strings["Ticks##sgiGB"].plurals[0] = "Шагов";
    strings["Position##sgiGB"].plurals[0] = "Положение";
    strings["Macros##sgiGB"].plurals[0] = "Макросы";
    strings["Volume##sgiGB2"].plurals[0] = "Громкость";
    strings["Arpeggio##sgiGB"].plurals[0] = "Арпеджио";
    strings["Pitch##sgiGB"].plurals[0] = "Частота";
    strings["Duty/Noise##sgiGB"].plurals[0] = "Скважность/режим шума";
    strings["Waveform##sgiGB"].plurals[0] = "Волна";
    strings["Panning##sgiGB"].plurals[0] = "Панорамирование";
    strings["Phase Reset##sgiGB"].plurals[0] = "Сброс фазы";

    //   sgistru   src/gui/inst/stringsUtil.cpp

    strings["Down Down Down##sgistru"].plurals[0] = "Вниз Вниз Вниз";
    strings["Down.##sgistru"].plurals[0] = "Вниз.";
    strings["Down Up Down Up##sgistru"].plurals[0] = "Вниз Вверх Вниз Вверх";
    strings["Down UP##sgistru"].plurals[0] = "Вниз ВВЕРХ";
    strings["Up Up Up##sgistru"].plurals[0] = "Вверх Вверх Вверх";
    strings["Up.##sgistru"].plurals[0] = "Вверх.";
    strings["Up Down Up Down##sgistru"].plurals[0] = "Вверх Вниз Вверх Вниз";
    strings["Up DOWN##sgistru"].plurals[0] = "Вверх ВНИЗ";
    strings["Algorithm##sgistru"].plurals[0] = "Алгоритм";
    strings["Feedback##sgistru"].plurals[0] = "Обр. связь.";
    strings["LFO > Freq##sgistru"].plurals[0] = "ОНЧ > част.";
    strings["LFO > Amp##sgistru"].plurals[0] = "ОНЧ > ампл.";
    strings["Attack##sgistru"].plurals[0] = "Атака";
    strings["Decay##sgistru"].plurals[0] = "Спад";
    strings["Decay 2##sgistru"].plurals[0] = "Спад 2";
    strings["Release##sgistru"].plurals[0] = "Релиз";
    strings["Sustain##sgistru0"].plurals[0] = "Сустейн";
    strings["Level##sgistru"].plurals[0] = "Уровень";
    strings["EnvScale##sgistru"].plurals[0] = "Масш. огиб.";
    strings["Multiplier##sgistru"].plurals[0] = "Множитель";
    strings["Detune##sgistru0"].plurals[0] = "Расстройка";
    strings["Detune 2##sgistru"].plurals[0] = "Расстройка 2";
    strings["SSG-EG##sgistru"].plurals[0] = "SSG-EG";
    strings["AM Depth##sgistru"].plurals[0] = "Глубина АМ";
    strings["Vibrato Depth##sgistru"].plurals[0] = "Глубина вибрато";
    strings["Sustained##sgistru0"].plurals[0] = "Сустейн";
    strings["Sustained##sgistru1"].plurals[0] = "Сустейн";
    strings["Level Scaling##sgistru"].plurals[0] = "Масштаб. громкости";
    strings["Sustain##sgistru1"].plurals[0] = "Сустейн";
    strings["Vibrato##sgistru"].plurals[0] = "Вибрато";
    strings["Waveform##sgistru"].plurals[0] = "Волна";
    strings["Scale Rate##sgistru"].plurals[0] = "Измен. коэфф. масш. в зав. от част.";
    strings["OP2 Half Sine##sgistru"].plurals[0] = "полу-синус для ОП2";
    strings["OP1 Half Sine##sgistru"].plurals[0] = "полу-синус для ОП1";
    strings["EnvShift##sgistru"].plurals[0] = "Сдвиг огиб.";
    strings["Reverb##sgistru"].plurals[0] = "Реверб";
    strings["Fine##sgistru0"].plurals[0] = "Точн.";
    strings["LFO2 > Freq##sgistru"].plurals[0] = "ОНЧ2 > част.";
    strings["LFO2 > Amp##sgistru"].plurals[0] = "ОНЧ2 > част.";
    strings["Fine##sgistru1"].plurals[0] = "Точн.";
    strings["Fine##sgistru2"].plurals[0] = "Точн.";
    strings["OP4 Noise Mode##sgistru0"].plurals[0] = "Режим шума у ОП4";
    strings["Envelope Delay##sgistru"].plurals[0] = "Задержка огибающей";
    strings["Output Level##sgistru0"].plurals[0] = "Громкость вывода";
    strings["Modulation Input Level##sgistru"].plurals[0] = "Сила модуляции на входе";
    strings["Left Output##sgistru"].plurals[0] = "Вывод звука влево";
    strings["Right Output##sgistru"].plurals[0] = "Вывод звука вправо";
    strings["Coarse Tune (semitones)##sgistru"].plurals[0] = "Грубая расстройка (полутоны)";
    strings["Detune##sgistru1"].plurals[0] = "Расстройка";
    strings["Fixed Frequency Mode##sgistru"].plurals[0] = "Режим фиксированной частоты";
    strings["OP4 Noise Mode##sgistru1"].plurals[0] = "Режим шума у ОП4";
    strings["Env. Delay##sgistru"].plurals[0] = "Задержка огибающей";
    strings["Output Level##sgistru1"].plurals[0] = "Громкость вывода";
    strings["ModInput##sgistru"].plurals[0] = "Мод. на входе";
    strings["Left##sgistru"].plurals[0] = "Лево";
    strings["Right##sgistru"].plurals[0] = "Право";
    strings["Tune##sgistru"].plurals[0] = "Груб. расстр.";
    strings["Detune##sgistru2"].plurals[0] = "Растройка";
    strings["Fixed##sgistru0"].plurals[0] = "Фикс. част.";
    strings["Fine##sgistru3"].plurals[0] = "Точн.";
    strings["Fine##sgistru4"].plurals[0] = "Точн.";
    strings["Fine##sgistru5"].plurals[0] = "Точн.";
    strings["User##sgistru0"].plurals[0] = "Пользовательский";
    strings["1. Violin##sgistru"].plurals[0] = "1. Скрипка";
    strings["2. Guitar##sgistru0"].plurals[0] = "2. Гитара";
    strings["3. Piano##sgistru0"].plurals[0] = "3. Пианино";
    strings["4. Flute##sgistru0"].plurals[0] = "4. Флейта";
    strings["5. Clarinet##sgistru0"].plurals[0] = "5. Кларнет";
    strings["6. Oboe##sgistru"].plurals[0] = "6. Гобой";
    strings["7. Trumpet##sgistru0"].plurals[0] = "7. Тромбон";
    strings["8. Organ##sgistru"].plurals[0] = "8. Орган";
    strings["9. Horn##sgistru"].plurals[0] = "9. Рог";
    strings["10. Synth##sgistru"].plurals[0] = "10. Синтезатор";
    strings["11. Harpsichord##sgistru"].plurals[0] = "11. Клавесин";
    strings["12. Vibraphone##sgistru0"].plurals[0] = "12. Вибрафон";
    strings["13. Synth Bass##sgistru"].plurals[0] = "13. Синтезаторный бас";
    strings["14. Acoustic Bass##sgistru"].plurals[0] = "14. Акустический бас";
    strings["15. Electric Guitar##sgistru"].plurals[0] = "15. Электрогитара";
    strings["Drums##sgistru0"].plurals[0] = "Ударные";
    strings["User##sgistru1"].plurals[0] = "Пользовательский";
    strings["1. Electric String##sgistru"].plurals[0] = "1. Электронный струнный инструмент";
    strings["2. Bow wow##sgistru"].plurals[0] = "2. Гам-гам";
    strings["3. Electric Guitar##sgistru0"].plurals[0] = "3. Электрогитара";
    strings["4. Organ##sgistru"].plurals[0] = "4. Орган";
    strings["5. Clarinet##sgistru1"].plurals[0] = "5. Кларнет";
    strings["6. Saxophone##sgistru"].plurals[0] = "6. Саксофон";
    strings["7. Trumpet##sgistru1"].plurals[0] = "7. Тромбон";
    strings["8. Street Organ##sgistru"].plurals[0] = "8. Шарманка";
    strings["9. Synth Brass##sgistru"].plurals[0] = "9. Синтезаторный медный духовой";
    strings["10. Electric Piano##sgistru"].plurals[0] = "10. Электронное пианино";
    strings["11. Bass##sgistru"].plurals[0] = "11. Бас";
    strings["12. Vibraphone##sgistru1"].plurals[0] = "12. Вибрафон";
    strings["13. Chime##sgistru"].plurals[0] = "13. Колокольчик";
    strings["14. Tom Tom II##sgistru"].plurals[0] = "14. Там-там №2";
    strings["15. Noise##sgistru"].plurals[0] = "15. Шум";
    strings["Drums##sgistru1"].plurals[0] = "Ударные";
    strings["User##sgistru2"].plurals[0] = "Пользовательский";
    strings["1. Strings##sgistru"].plurals[0] = "1. Струнные";
    strings["2. Guitar##sgistru1"].plurals[0] = "2. Гитара";
    strings["3. Electric Guitar##sgistru1"].plurals[0] = "3. Электрогитара";
    strings["4. Electric Piano##sgistru"].plurals[0] = "4. Электронное пианино";
    strings["5. Flute##sgistru"].plurals[0] = "5. Флейта";
    strings["6. Marimba##sgistru"].plurals[0] = "6. Маримба";
    strings["7. Trumpet##sgistru2"].plurals[0] = "7. Тромбон";
    strings["8. Harmonica##sgistru"].plurals[0] = "8. Гармоника";
    strings["9. Tuba##sgistru"].plurals[0] = "9. Туба";
    strings["10. Synth Brass##sgistru"].plurals[0] = "10. Синтезаторный медный духовой";
    strings["11. Short Saw##sgistru"].plurals[0] = "11. Короткая пила";
    strings["12. Vibraphone##sgistru2"].plurals[0] = "12. Вибрафон";
    strings["13. Electric Guitar 2##sgistru"].plurals[0] = "13. Электрогитара 2";
    strings["14. Synth Bass##sgistru"].plurals[0] = "14. Синтезаторный бас";
    strings["15. Sitar##sgistru"].plurals[0] = "15. Ситар";
    strings["Drums##sgistru2"].plurals[0] = "Ударные";
    strings["User##sgistru3"].plurals[0] = "Пользровательский";
    strings["1. Bell##sgistru"].plurals[0] = "1. Колокол";
    strings["2. Guitar##sgistru2"].plurals[0] = "2. Гитара";
    strings["3. Piano##sgistru1"].plurals[0] = "3. Пианино";
    strings["4. Flute##sgistru1"].plurals[0] = "4. Флейта";
    strings["5. Clarinet##sgistru2"].plurals[0] = "5. Кларнет";
    strings["6. Rattling Bell##sgistru"].plurals[0] = "6. Дребезжащий колокол";
    strings["7. Trumpet##sgistru3"].plurals[0] = "7. Тромбон";
    strings["8. Reed Organ##sgistru"].plurals[0] = "8. Свирель";
    strings["9. Soft Bell##sgistru"].plurals[0] = "9. \"Мягкий\" колокол";
    strings["10. Xylophone##sgistru"].plurals[0] = "10. Ксилофон";
    strings["11. Vibraphone##sgistru"].plurals[0] = "11. Вибрафон";
    strings["12. Brass##sgistru"].plurals[0] = "12. Медный духовой инструмент";
    strings["13. Bass Guitar##sgistru"].plurals[0] = "13. Бас-гитара";
    strings["14. Synth##sgistru"].plurals[0] = "14. Синтезатор";
    strings["15. Chorus##sgistru"].plurals[0] = "15. Хорус";
    strings["Drums##sgistru3"].plurals[0] = "Ударные";
    strings["Sine##sgistru0"].plurals[0] = "Синус";
    strings["Half Sine##sgistru0"].plurals[0] = "Половинка синуса";
    strings["Absolute Sine##sgistru0"].plurals[0] = "Модуль синуса";
    strings["Quarter Sine##sgistru"].plurals[0] = "Четверть синуса";
    strings["Squished Sine##sgistru0"].plurals[0] = "Сжатый синус";
    strings["Squished AbsSine##sgistru0"].plurals[0] = "Сж. модуль синуса";
    strings["Square##sgistru0"].plurals[0] = "Меандр";
    strings["Derived Square##sgistru0"].plurals[0] = "Производная от меандра";
    strings["Sine##sgistru1"].plurals[0] = "Синус";
    strings["Half Sine##sgistru1"].plurals[0] = "Половинка синуса";
    strings["Absolute Sine##sgistru1"].plurals[0] = "Модуль синуса";
    strings["Pulse Sine##sgistru"].plurals[0] = "Синус-меандр";
    strings["Sine (Even Periods)##sgistru"].plurals[0] = "Синус (чётные периоды)";
    strings["AbsSine (Even Periods)##sgistru"].plurals[0] = "Мод. синуса (чётн. пер.)";
    strings["Square##sgistru1"].plurals[0] = "Меандр";
    strings["Derived Square##sgistru1"].plurals[0] = "Производная от меандра";
    strings["Sine##sgistru2"].plurals[0] = "Синус";
    strings["Triangle##sgistru"].plurals[0] = "Треуг. волна";
    strings["Cut Sine##sgistru"].plurals[0] = "Обрезанный синус";
    strings["Cut Triangle##sgistru"].plurals[0] = "Обрез. треуг. волна";
    strings["Squished Sine##sgistru1"].plurals[0] = "Сжатый синус";
    strings["Squished Triangle##sgistru"].plurals[0] = "Сжатая треуг. волна";
    strings["Squished AbsSine##sgistru1"].plurals[0] = "Сжатый модуль синуса";
    strings["Squished AbsTriangle##sgistru"].plurals[0] = "Сж. мод. треуг. волны";
    strings["Snare##sgistru0"].plurals[0] = "Рабочий барабан";
    strings["Tom##sgistru"].plurals[0] = "Там-там";
    strings["Top##sgistru0"].plurals[0] = "Тарелка";
    strings["HiHat##sgistru0"].plurals[0] = "Хай-хэт";
    strings["Normal##sgistru"].plurals[0] = "Обычный";
    strings["Snare##sgistru1"].plurals[0] = "Малый барабан";
    strings["HiHat##sgistru1"].plurals[0] = "Хай-хэт";
    strings["Top##sgistru1"].plurals[0] = "Тарелка";
    strings["Noise disabled##sgistru"].plurals[0] = "Шум выключен";
    strings["Square + noise##sgistru"].plurals[0] = "Меандр + шум";
    strings["Ringmod from OP3 + noise##sgistru"].plurals[0] = "Кольцевая модуляция от ОП3 + шум";
    strings["Ringmod from OP3 + double pitch ModInput\nWARNING - has emulation issues, subject to change##sgistru"].plurals[0] = "Кольцевая модуляция от ОП3 + входная модуляция с удвоенной частотой\nВНИМАНИЕ - имеются проблемы с эмуляцией этого режима, она может измениться";
    strings["op1##sgistru"].plurals[0] = "оп1";
    strings["op2##sgistru"].plurals[0] = "оп2";
    strings["op3##sgistru"].plurals[0] = "оп3";
    strings["op4##sgistru"].plurals[0] = "оп4";
    strings["triangle##sgistru"].plurals[0] = "треуг.";
    strings["saw##sgistru"].plurals[0] = "пила";
    strings["pulse##sgistru"].plurals[0] = "меандр";
    strings["noise##sgistru0"].plurals[0] = "шум";
    strings["tone##sgistru"].plurals[0] = "тон";
    strings["noise##sgistru1"].plurals[0] = "шум";
    strings["envelope##sgistru"].plurals[0] = "огибающая";
    strings["hold##sgistru"].plurals[0] = "удержание";
    strings["alternate##sgistru"].plurals[0] = "изм. направл.";
    strings["direction##sgistru0"].plurals[0] = "направление";
    strings["enable##sgistru0"].plurals[0] = "вкл.";
    strings["enabled##sgistru0"].plurals[0] = "вкл.";
    strings["mirror##sgistru"].plurals[0] = "отраж.";
    strings["loop##sgistru0"].plurals[0] = "цикл";
    strings["cut##sgistru"].plurals[0] = "обрез.";
    strings["direction##sgistru1"].plurals[0] = "направление";
    strings["resolution##sgistru"].plurals[0] = "разрешение";
    strings["fixed##sgistru1"].plurals[0] = "фиксир.";
    strings["N/A##sgistru"].plurals[0] = "-";
    strings["enabled##sgistru1"].plurals[0] = "вкл.";
    strings["noise##sgistru2"].plurals[0] = "шум";
    strings["echo##sgistru"].plurals[0] = "эхо";
    strings["pitch mod##sgistru"].plurals[0] = "част. мод.";
    strings["invert right##sgistru"].plurals[0] = "инв. справа";
    strings["invert left##sgistru"].plurals[0] = "инв. слева";
    strings["low##sgistru"].plurals[0] = "ФВЧ";
    strings["band##sgistru"].plurals[0] = "ППФ";
    strings["high##sgistru"].plurals[0] = "ФВЧ";
    strings["ch3off##sgistru"].plurals[0] = "выкл. 3 кан.";
    strings["gate##sgistru"].plurals[0] = "старт/стоп огиб.";
    strings["sync##sgistru"].plurals[0] = "синхр.";
    strings["ring##sgistru"].plurals[0] = "кольц.";
    strings["test##sgistru"].plurals[0] = "тест";
    strings["filter 2+4##sgistru"].plurals[0] = "фильтр 2+4";
    strings["filter 1+3##sgistru"].plurals[0] = "фильтр 1+3";
    strings["16-bit 3+4##sgistru"].plurals[0] = "16-битн. 3+4";
    strings["16-bit 1+2##sgistru"].plurals[0] = "16-битн. 1+2";
    strings["high3##sgistru"].plurals[0] = "ФВЧ 3";
    strings["high1##sgistru"].plurals[0] = "ФВЧ 1";
    strings["poly9##sgistru"].plurals[0] = "полином 9";
    strings["int##sgistru"].plurals[0] = "интегр.";
    strings["sustain##sgistru2"].plurals[0] = "сустейн";
    strings["square##sgistru2"].plurals[0] = "меандр";
    strings["noise##sgistru3"].plurals[0] = "шум";
    strings["noise##sgistru4"].plurals[0] = "шум";
    strings["invert##sgistru"].plurals[0] = "инверт.";
    strings["surround##sgistru"].plurals[0] = "окр. звуч.";
    strings["enable##sgistru1"].plurals[0] = "вкл.";
    strings["oneshot##sgistru"].plurals[0] = "однокр.";
    strings["split L/R##sgistru"].plurals[0] = "разд. лев/прав";
    strings["HinvR##sgistru"].plurals[0] = "HинвR";
    strings["VinvR##sgistru"].plurals[0] = "VинвR";
    strings["HinvL##sgistru"].plurals[0] = "HинвL";
    strings["VinvL##sgistru"].plurals[0] = "VинвL";
    strings["ring mod##sgistru"].plurals[0] = "кольц. мод.";
    strings["low pass##sgistru"].plurals[0] = "ФНЧ";
    strings["high pass##sgistru"].plurals[0] = "ФВЧ";
    strings["band pass##sgistru"].plurals[0] = "ППФ";
    strings["right##sgistru"].plurals[0] = "правый";
    strings["left##sgistru"].plurals[0] = "левый";
    strings["rear right##sgistru"].plurals[0] = "задний правый";
    strings["rear left##sgistru"].plurals[0] = "задний левый";
    strings["enable tap B##sgistru"].plurals[0] = "вкл. отвод B";
    strings["AM with slope##sgistru"].plurals[0] = "АМ со скатом";
    strings["invert B##sgistru"].plurals[0] = "инв. B";
    strings["invert A##sgistru"].plurals[0] = "инв. A";
    strings["reset B##sgistru"].plurals[0] = "перезап. B";
    strings["reset A##sgistru"].plurals[0] = "перезап. A";
    strings["clip B##sgistru"].plurals[0] = "огран. B";
    strings["clip A##sgistru"].plurals[0] = "огран. A";
    strings["on##sgistru"].plurals[0] = "вкл.";
    strings["k1 slowdown##sgistru"].plurals[0] = "замедл. k1";
    strings["k2 slowdown##sgistru"].plurals[0] = "замедл. k2";
    strings["pause##sgistru"].plurals[0] = "стоп";
    strings["reverse##sgistru"].plurals[0] = "реверс";
    strings["None##sgistru"].plurals[0] = "Нет";
    strings["Invert##sgistru"].plurals[0] = "Инвертировать";
    strings["Add##sgistru"].plurals[0] = "Сложить";
    strings["Subtract##sgistru"].plurals[0] = "Вычесть";
    strings["Average##sgistru"].plurals[0] = "Усреднить";
    strings["Phase##sgistru"].plurals[0] = "Временной сдвиг";
    strings["Chorus##sgistru"].plurals[0] = "Хорус";
    strings["None (dual)##sgistru"].plurals[0] = "Нет (две таблицы)";
    strings["Wipe##sgistru"].plurals[0] = "Замена";
    strings["Fade##sgistru"].plurals[0] = "Плавный переход";
    strings["Fade (ping-pong)##sgistru"].plurals[0] = "Плавный переход (туда-обратно)";
    strings["Overlay##sgistru"].plurals[0] = "Наложение";
    strings["Negative Overlay##sgistru"].plurals[0] = "Наложение с обратным знаком";
    strings["Slide##sgistru"].plurals[0] = "Сдвиг";
    strings["Mix Chorus##sgistru"].plurals[0] = "Микширование с хорусом";
    strings["Phase Modulation##sgistru"].plurals[0] = "Фазовая модуляция";
    strings["Envelope##sgistru"].plurals[0] = "Огибающая";
    strings["Sweep##sgistru"].plurals[0] = "Аппаратное портаменто";
    strings["Wait##sgistru0"].plurals[0] = "Ждать";
    strings["Wait for Release##sgistru0"].plurals[0] = "Ждать релиз";
    strings["Loop##sgistru1"].plurals[0] = "Цикл";
    strings["Loop until Release##sgistru0"].plurals[0] = "Цикл до релиза";
    strings["Volume Sweep##sgistru"].plurals[0] = "Изменение громкости";
    strings["Frequency Sweep##sgistru"].plurals[0] = "Изменение частоты";
    strings["Cutoff Sweep##sgistru"].plurals[0] = "Изменение частоты среза";
    strings["Wait##sgistru1"].plurals[0] = "Ждать";
    strings["Wait for Release##sgistru1"].plurals[0] = "Ждать релиз";
    strings["Loop##sgistru2"].plurals[0] = "Цикл";
    strings["Loop until Release##sgistru1"].plurals[0] = "Цикл до релиза";
    strings["Direct##sgistru"].plurals[0] = "Прямое";
    strings["Decrease (linear)##sgistru"].plurals[0] = "Уменьш. (линейное)";
    strings["Decrease (logarithmic)##sgistru"].plurals[0] = "Уменьш. (логарифмическое)";
    strings["Increase (linear)##sgistru"].plurals[0] = "Увелич. (линейное)";
    strings["Increase (bent line)##sgistru"].plurals[0] = "Увелич. (изогн. линия)";
    strings["Fixed##sgistru2"].plurals[0] = "Абсолютное";
    strings["Relative##sgistru"].plurals[0] = "Относительное";
    strings["QSound##sgistru"].plurals[0] = "QSound";
    strings["Bug##sgistru"].plurals[0] = "Сбой";
}