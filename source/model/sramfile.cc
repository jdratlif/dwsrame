/*
 * dwsrame - Dragon Warrior SRAM Editor
 * Copyright (C) 2006-2008 emuWorks
 * http://games.technoplaza.net/
 *
 * This file is part of dwsrame.
 *
 * dwsrame is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version.
 *
 * dwsrame is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * dwsrame; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <cstring>
#include <fstream>

#include "model/sramfile.hh"

using namespace dwsrame;

const std::pair<int, int> SRAMFile::QUEST_OFFSETS[] = {
    std::pair<int, int>(0xB, 0x04),  // charlock stairs
    std::pair<int, int>(0xB, 0x08),  // rainbow bridge
    std::pair<int, int>(0xB, 0x10),  // using dragon's scale
    std::pair<int, int>(0xB, 0x20),  // using fighter's ring
    std::pair<int, int>(0xB, 0x40),  // using cursed belt
    std::pair<int, int>(0xB, 0x80),  // using death necklace

    std::pair<int, int>(0xC, 0x01),  // holding gwaelin
    std::pair<int, int>(0xC, 0x02),  // gwaelin on throne
    std::pair<int, int>(0xC, 0x08),  // started quest

    std::pair<int, int>(0xD, 0x02),  // golem
    std::pair<int, int>(0xD, 0x04),  // dragonlord
    std::pair<int, int>(0xD, 0x40),  // green dragon
};

SRAMFile::SRAMFile(const wxString &filename) : modified(false) {
    std::ifstream file(filename.mb_str(),
                       std::ios_base::in | std::ios_base::binary);

    if (!file) {
        throw InvalidSRAMFileException(ISFE_FILENOTFOUND);
    }

    file.seekg(0, std::ios_base::end);

    if (file.tellg() != static_cast<std::streampos>(SRAM_SIZE)) {
        throw InvalidSRAMFileException(ISFE_INVALIDSIZE);
    }

    file.seekg(0, std::ios_base::beg);
    file.read(sram, SRAM_SIZE);
    file.close();

    // look for KEN MASUTA string
    if (std::strncmp("KEN MASUTA", (sram + KENMASUTA_OFFSET), 10) != 0) {
        throw InvalidSRAMFileException(ISFE_NOVALIDGAMES);
    }

    // checksum to determine valid games
    std::memset(valid, 0, 3 * sizeof(bool));

    bool foundValid = false;

    for (int game = 2; game >= 0; --game) {
        if (sram[SLOT_OFFSET + game] == MAGIC_NUMBER) {
            if (checksum(game) == getChecksum(game)) {
                valid[game] = foundValid = true;
                setGame(game);
            }
        }
    }

    if (!foundValid) {
        throw InvalidSRAMFileException(ISFE_NOVALIDGAMES);
    }
}

/*
    $FBEF:A0 1D     LDY #$1D        ; load counter with 0x1D
    $FBF1:84 94     STY $0094       ; init checksum low byte
    $FBF3:84 95     STY $0095       ; init checksum high byte
    $FBF5:B1 22     LDA ($22),Y     ; load data[counter] into a
    $FBF7:85 3C     STA $003C       ; store to memory
    $FBF9:20 2A FC  JSR $FC2A       ; jump to subroutine
    $FBFC:88        DEY             ; y = y - 1
    $FBFD:10 F6     BPL $FBF5       ; repeat 0x1D + 1 times
    $FBFF:60        RTS             ; end of checksum algorithm

    $FC2A:98        TYA             ; put counter into a
    $FC2B:48        PHA             ; push counter to stack
    $FC2C:A0 08     LDY #$08        ; load new counter with 8
    $FC2E:A5 95     LDA $0095       ; load checksum high byte
    $FC30:45 3C     EOR $003C       ; xor data[counter] with checksum high byte
    $FC32:06 94     ASL $0094       ; shift left checksum low byte
    $FC34:26 95     ROL $0095       ; rotate shifted bit onto checksum high byte
    $FC36:06 3C     ASL $003C       ; shift left data[counter]
    $FC38:0A        ASL             ; shift left original checksum high byte
    $FC39:90 0C     BCC $FC47       ; skip if shifted bit was 0
    $FC3B:A5 94     LDA $0094       ; load checksum low byte
    $FC3D:49 21     EOR #$21        ; xor checksum low byte with 0x21
    $FC3F:85 94     STA $0094       ; store into checksum low byte
    $FC41:A5 95     LDA $0095       ; load checksum high byte
    $FC43:49 10     EOR #$10        ; xor checksum high with 0x10
    $FC45:85 95     STA $0095       ; store checksum high byte
    $FC47:88        DEY             ; y = y - 1
    $FC48:D0 E4     BNE $FC2E       ; repeat 8 times
    $FC4A:68        PLA             ; pull counter from stack
    $FC4B:A8        TAY             ; restore counter to y
    $FC4C:60        RTS             ; return
*/

auto SRAMFile::checksum(int game) const -> wxUint16 {
    wxASSERT((game >= 0) && (game < 3));

    // registers
    unsigned char a;

    // working sram byte at $003C
    unsigned char data;

    // carry flag
    bool carry = false;

    // LDY #$1D
    // STY $0094 (first)
    // STY $0095 (second)
    std::pair<unsigned char, unsigned char> checksum(0x1d, 0x1d);

    // DEY
    // BPL $FBF5
    for (int y = 0x1d; y >= 0; --y) {
        // LDA ($22),Y
        // STA $003C (data)
        data = sram[GAME_OFFSET + (game * GAME_SIZE) + y];

        // y is shadowed here to match the assembly
        // LDY #$08

        // DEY
        // BNE $FC2E
        for (int y = 8; y > 0; --y) {
            // LDA $0095 (checksum.second)
            // EOR $003C (data)
            a = checksum.second ^ data;

            // ASL $0094 (checksum.first)
            carry = (checksum.first & 0x80) != 0;
            checksum.first <<= 1;

            // ROL $0095
            // ignore the carry -- we don't need it
            checksum.second = (checksum.second << 1) | (carry ? 1 : 0);

            // ASL $003C (data)
            // ignore the carry -- we don't need it
            data <<= 1;

            // ASL
            // ignore the operation -- we only need the carry
            carry = (a & 0x80) != 0;

            // BCC $FC47
            if (carry) {
                checksum.first ^= 0x21;
                checksum.second ^= 0x10;
            }
        }
    }

    return checksum.first | (checksum.second << 8);
}

auto SRAMFile::fromASCII(char asciiChar) const -> char {
    char ch;

    switch (asciiChar) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            ch = static_cast<char>(asciiChar - '0');
            break;

        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
        case 'g':
        case 'h':
        case 'i':
        case 'j':
        case 'k':
        case 'l':
        case 'm':
        case 'n':
        case 'o':
        case 'p':
        case 'q':
        case 'r':
        case 's':
        case 't':
        case 'u':
        case 'v':
        case 'w':
        case 'x':
        case 'y':
        case 'z':
            ch = static_cast<char>(asciiChar - 'a' + 0xA);
            break;

        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
        case 'G':
        case 'H':
        case 'I':
        case 'J':
        case 'K':
        case 'L':
        case 'M':
        case 'N':
        case 'O':
        case 'P':
        case 'Q':
        case 'R':
        case 'S':
        case 'T':
        case 'U':
        case 'V':
        case 'W':
        case 'X':
        case 'Y':
        case 'Z':
            ch = static_cast<char>(asciiChar - 'A' + 0x24);
            break;

        case '\'':
            ch = 0x40;
            break;
        case '.':
            ch = 0x47;
            break;
        case ',':
            ch = 0x48;
            break;
        case '-':
            ch = 0x49;
            break;
        case '?':
            ch = 0x4B;
            break;
        case '!':
            ch = 0x4C;
            break;
        case ')':
            ch = 0x4E;
            break;
        case '(':
            ch = 0x4F;
            break;
        case ' ':
            ch = 0x60;
            break;

        default:
            // we should NEVER reach the default case
            wxASSERT(false);

            ch = 0x60;
            break;
    }

    return ch;
}

auto SRAMFile::save(const wxString &filename) -> bool {
    std::ofstream file(filename.mb_str(),
                       std::ios_base::out | std::ios_base::binary);

    if (!file) {
        return false;
    }

    for (int i = 0; i < 3; ++i) {
        setChecksum(i, checksum(i));
    }

    file.write(sram, SRAM_SIZE);
    file.close();

    modified = false;

    return true;
}

auto SRAMFile::toASCII(char dwChar) const -> char {
    char ch;

    switch (dwChar) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            ch = static_cast<char>('0' + dwChar);
            break;

        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
        case 26:
        case 27:
        case 28:
        case 29:
        case 30:
        case 31:
        case 32:
        case 33:
        case 34:
        case 35:
            ch = static_cast<char>('a' + dwChar - 0xA);
            break;

        case 36:
        case 37:
        case 38:
        case 39:
        case 40:
        case 41:
        case 42:
        case 43:
        case 44:
        case 45:
        case 46:
        case 47:
        case 48:
        case 49:
        case 50:
        case 51:
        case 52:
        case 53:
        case 54:
        case 55:
        case 56:
        case 57:
        case 58:
        case 59:
        case 60:
        case 61:
            ch = static_cast<char>('A' + dwChar - 0x24);
            break;

        case 0x40:
            ch = '\'';
            break;
        case 0x47:
            ch = '.';
            break;
        case 0x48:
            ch = ',';
            break;
        case 0x49:
            ch = '-';
            break;
        case 0x4B:
            ch = '?';
            break;
        case 0x4C:
            ch = '!';
            break;
        case 0x4E:
            ch = ')';
            break;
        case 0x4F:
            ch = '(';
            break;
        case 0x60:
            ch = ' ';
            break;

        default:
            // we should NEVER get to the default case
            wxASSERT(false);

            ch = '_';
            break;
    }

    return ch;
}

void SRAMFile::setArmor(enum dw_armor armor) {
    auto *ptr = reinterpret_cast<unsigned char *>(offset + EQUIPMENT_OFFSET);

    *ptr &= ~ARMOR_MASK;
    *ptr |= armor;

    modified = true;
}

auto SRAMFile::getChecksum(int game) const -> wxUint16 {
    wxASSERT((game >= 0) && (game < 3));

    const auto *ptr = reinterpret_cast<const wxUint16 *>(
        sram + GAME_OFFSET + (GAME_SIZE * game) + CHECKSUM_OFFSET);

    return wxUINT16_SWAP_ON_BE(*ptr);
}

void SRAMFile::setChecksum(int game, wxUint16 checksum) {
    wxASSERT((game >= 0) && (game < 3));

    auto *ptr = reinterpret_cast<wxUint16 *>(
        sram + GAME_OFFSET + (GAME_SIZE * game) + CHECKSUM_OFFSET);

    *ptr = wxUINT16_SWAP_ON_BE(checksum);
}

auto SRAMFile::getExperience() const -> wxUint16 {
    const auto *ptr = reinterpret_cast<const wxUint16 *>(offset + EXP_OFFSET);

    return wxUINT16_SWAP_ON_BE(*ptr);
}

void SRAMFile::setExperience(wxUint16 experience) {
    auto *ptr = reinterpret_cast<wxUint16 *>(offset + EXP_OFFSET);

    *ptr = wxUINT16_SWAP_ON_BE(experience);

    modified = true;
}

void SRAMFile::setGame(int game) {
    wxASSERT((game >= 0) && (game < 3));
    wxASSERT(isValid(game));

    this->game = game;
    offset     = reinterpret_cast<unsigned char *>(sram + GAME_OFFSET
                                               + (GAME_SIZE * game));
}

auto SRAMFile::getGold() const -> wxUint16 {
    const auto *ptr = reinterpret_cast<const wxUint16 *>(offset + GOLD_OFFSET);

    return wxUINT16_SWAP_ON_BE(*ptr);
}

void SRAMFile::setGold(wxUint16 gold) {
    auto *ptr = reinterpret_cast<wxUint16 *>(offset + GOLD_OFFSET);

    *ptr = wxUINT16_SWAP_ON_BE(gold);

    modified = true;
}

void SRAMFile::setHerbs(int herbs) {
    offset[HERBS_OFFSET] = herbs;
    modified             = true;
}

void SRAMFile::setHP(unsigned int hp) {
    offset[HP_OFFSET] = hp;
    modified          = true;
}

auto SRAMFile::getItem(int number) const -> enum dw_item {
    auto value = static_cast<unsigned char>(*(offset + ITEM_OFFSET
                                              + (number / 2)));

    if ((number % 2) == 1){value >>= 4;}

return static_cast<enum dw_item>(value & 0xF);
}

void SRAMFile::setItem(enum dw_item item, int number) {
    unsigned char value = item;
    auto         *ptr =
        reinterpret_cast<unsigned char *>(offset + ITEM_OFFSET + (number / 2));

    if ((number % 2) == 1) {
        value <<= 4;
        *ptr &= 0xF;
    } else {
        *ptr &= 0xF0;
    }

    *ptr |= value;

    modified = true;
}

void SRAMFile::setKeys(int keys) {
    offset[KEYS_OFFSET] = keys;
    modified            = true;
}

void SRAMFile::setMP(unsigned int mp) {
    offset[MP_OFFSET] = mp;
    modified          = true;
}

auto SRAMFile::getName() const -> wxString {
    wxString    name;
    const char *ptr = reinterpret_cast<const char *>(offset + NAME_OFFSET);

    for (int i = 0; i < 2; ++i) {
        for (int j = 3; j >= 0; --j) {
            name.Append(toASCII(ptr[j]));
        }

        ptr += 4;
    }

    return name.Trim();
}

void SRAMFile::setName(const wxString &name) {
    char        *ptr   = reinterpret_cast<char *>(offset + NAME_OFFSET);
    unsigned int count = 0;

    for (int i = 0; i < 2; ++i) {
        for (int j = 3; j >= 0; --j) {
            if (count < name.Length()) {
                ptr[j] = fromASCII(name[count]);
            } else {
                ptr[j] = fromASCII(' ');
            }

            ++count;
        }

        ptr += 4;
    }

    modified = true;
}

void SRAMFile::setQuestMarker(enum dw_quest marker, bool set) {
    if (set) {
        offset[QUEST_OFFSETS[marker].first] |= QUEST_OFFSETS[marker].second;
    } else {
        offset[QUEST_OFFSETS[marker].first] &= ~QUEST_OFFSETS[marker].second;
    }

    modified = true;
}

void SRAMFile::setShield(enum dw_shield shield) {
    auto *ptr = reinterpret_cast<unsigned char *>(offset + EQUIPMENT_OFFSET);

    *ptr &= ~SHIELD_MASK;
    *ptr |= shield;

    modified = true;
}

void SRAMFile::setWeapon(enum dw_weapon weapon) {
    auto *ptr = reinterpret_cast<unsigned char *>(offset + EQUIPMENT_OFFSET);

    *ptr &= ~WEAPON_MASK;
    *ptr |= weapon;

    modified = true;
}
