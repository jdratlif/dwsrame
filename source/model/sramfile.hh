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

#ifndef _DWSRAME_SRAMFILE_HH_
#define _DWSRAME_SRAMFILE_HH_

#include <utility>
#include <wx/defs.h>

#include "exception/invalidsramfileexception.hh"

namespace dwsrame {
    /// the armor bits of the equipment byte
    const int ARMOR_MASK = 0x1C;

    /// the checksum offset
    const int CHECKSUM_OFFSET = 0x1E;

    /// the equipment offset
    const int EQUIPMENT_OFFSET = 0xA;

    /// the experience offset
    const int EXP_OFFSET = 0x0;

    /// the starting offset of the games
    const int GAME_OFFSET = 0x68;

    /// the size of a save game
    const int GAME_SIZE = 0x140;

    /// the gold offset
    const int GOLD_OFFSET = 0x2;

    /// the medical herbs offset
    const int HERBS_OFFSET = 0x9;

    /// the hit points offset
    const int HP_OFFSET = 0x17;

    /// the starting item offset
    const int ITEM_OFFSET = 0x4;

    /// the offset of the KEN MASUTA string
    const int KENMASUTA_OFFSET = 0x3B;

    /// the magic keys offset
    const int KEYS_OFFSET = 0x8;

    /// the magic number appears many times in the SRAM
    const char MAGIC_NUMBER = '\xC8';

    /// the magic points offset
    const int MP_OFFSET = 0x18;

    /// the name offset
    const int NAME_OFFSET = 0xE;

    /// the shield bits of the equipment byte
    const int SHIELD_MASK = 0x3;

    /// the starting offset of the game slot usage bytes
    const int SLOT_OFFSET = 0x35;

    /// the size of an SRAM file
    const int SRAM_SIZE = 0x2000;

    /// the weapon bits of the equipment byte
    const int WEAPON_MASK = 0xE0;

    /// the armors
    enum dw_armor {
        DW_NOARMOR,
        DW_CLOTHES       = 0x4,
        DW_LEATHERARMOR  = 0x8,
        DW_CHAINMAIL     = 0xC,
        DW_HALFPLATE     = 0x10,
        DW_FULLPLATE     = 0x14,
        DW_MAGICARMOR    = 0x18,
        DW_ERDRICKSARMOR = 0x1C
    };

    /// the items
    enum dw_item {
        DW_NOITEM,
        DW_TORCH,
        DW_FAIRYWATER,
        DW_WINGS,
        DW_DRAGONSSCALE,
        DW_FAIRYFLUTE,
        DW_FIGHTERSRING,
        DW_ERDRICKSTOKEN,
        DW_GWAELINSLOVE,
        DW_CURSEDBELT,
        DW_SILVERHARP,
        DW_DEATHNECKLACE,
        DW_STONESOFSUNLIGHT,
        DW_STAFFOFRAIN,
        DW_RAINBOWDROP
    };

    /// the quest markers
    enum dw_quest {
        DW_HIDDENSTAIRS,
        DW_RAINBOWBRIDGE,
        DW_USINGDRAGONSSCALE,
        DW_USINGFIGHTERSRING,
        DW_USINGCURSEDBELT,
        DW_USINGDEATHNECKLACE,
        DW_HOLDINGGWAELIN,
        DW_GWAELINONTHRONE,
        DW_LORIKSCHAMBER,
        DW_GOLEMDEAD,
        DW_DRAGONLORDDEAD,
        DW_GREENDRAGONDEAD
    };

    /// the shields
    enum dw_shield {
        DW_NOSHIELD,
        DW_SMALLSHIELD,
        DW_LARGESHIELD,
        DW_SILVERSHIELD
    };

    /// the weapons
    enum dw_weapon {
        DW_NOWEAPON,
        DW_BAMBOOPOLE    = 0x20,
        DW_CLUB          = 0x40,
        DW_COPPERSWORD   = 0x60,
        DW_HANDAXE       = 0x80,
        DW_BROADSWORD    = 0xA0,
        DW_FLAMESWORD    = 0xC0,
        DW_ERDRICKSSWORD = 0xE0
    };

    /// class to interface with an SRAM file
    class SRAMFile {
      private:
        int            game;
        char           sram[SRAM_SIZE];
        unsigned char *offset;
        bool           valid[3], modified;

        /// the various quest offsets
        static const std::pair<int, int> QUEST_OFFSETS[];

        /**
         * Calculates the checksum for one of the save games.
         *
         * @param game The game to checksum.
         *
         * @return The checksum.
         */
        auto checksum(int game) const -> wxUint16;

        /**
         * Converts an ASCII character to the Dragon Warrior alphabet.
         */
        auto fromASCII(char asciiChar) const -> char;

        /**
         * Converts a Dragon Warrior alphabetic character to ASCII.
         *
         * @param dwChar The Dragon Warrior character.
         *
         * @return The ASCII character.
         */
        auto toASCII(char dwChar) const -> char;

        /**
         * Gets the checksum for one of the save games.
         *
         * @param game The game.
         *
         * @return The checksum.
         */
        auto getChecksum(int game) const -> wxUint16;

        /**
         * Sets the checksum for one of the save games.
         *
         * @param game The game.
         * @param checksum The new checksum.
         */
        void setChecksum(int game, wxUint16 checksum);

      public:
        /**
         * Creates a new SRAMFile.
         *
         * @param filename The SRAM filename.
         *
         * @throws InvalidSRAMFileException if the filename is not a valid
         *     Dragon Warrior SRAM file.
         */
        SRAMFile(const wxString &filename);

        /**
         * Saves this SRAMfile back to disk.
         *
         * @param filename The filename to write the data to.
         *
         * @return true on success; false otherwise.
         */
        auto save(const wxString &filename) -> bool;

        /**
         * Gets the hero's armor.
         *
         * @return The armor.
         */
        auto getArmor() const -> dw_armor;

        /**
         * Sets the hero's armor.
         *
         * @param armor The new armor.
         */
        void setArmor(dw_armor armor);

        /**
         * Gets the hero's experience.
         *
         * @return The experience.
         */
        auto getExperience() const -> wxUint16;

        /**
         * Sets the hero's experience.
         *
         * @param experience The new experience.
         */
        void setExperience(wxUint16 experience);

        /**
         * Gets the current game.
         *
         * @return The game.
         */
        auto getGame() const -> int;

        /**
         * Sets the game currently being edited.
         *
         * @param game The game.
         */
        void setGame(int game);

        /**
         * Gets the hero's gold.
         *
         * @return The gold.
         */
        auto getGold() const -> wxUint16;

        /**
         * Sets the hero's gold.
         *
         * @param gold The new gold.
         */
        void setGold(wxUint16 gold);

        /**
         * Gets the hero's herbs.
         *
         * @return The herbs.
         */
        auto getHerbs() const -> int;

        /**
         * Sets the hero's herbs.
         *
         * @param herbs The new herbs.
         */
        void setHerbs(int herbs);

        /**
         * Gets the hero's current HP.
         *
         * @return The current HP.
         */
        auto getHP() const -> unsigned int;

        /**
         * Sets the hero's current HP.
         *
         * @param hp The new current HP.
         */
        void setHP(unsigned int hp);

        /**
         * Gets one of the hero's items.
         *
         * @param number The item number.
         *
         * @return The item.
         */
        auto getItem(int number) const -> dw_item;

        /**
         * Sets one of the hero's items.
         *
         * @param item The new item.
         * @param number The item number.
         */
        void setItem(dw_item item, int number);

        /**
         * Gets the hero's keys.
         *
         * @return The keys.
         */
        auto getKeys() const -> int;

        /**
         * Sets the hero's keys.
         *
         * @param keys The new keys.
         */
        void setKeys(int keys);

        /**
         * Checks whether this SRAMFile has been modified or not.
         *
         * @return true if modified; false otherwise.
         */
        auto isModified() const -> bool;

        /**
         * Gets the hero's current MP.
         *
         * @return The current MP.
         */
        auto getMP() const -> unsigned int;

        /**
         * Sets the hero's current MP.
         *
         * @param mp The new current MP.
         */
        void setMP(unsigned int mp);

        /**
         * Gets the hero's name.
         *
         * @return The name.
         */
        auto getName() const -> wxString;

        /**
         * Sets the hero's name.
         *
         * @param name The new name.
         */
        void setName(const wxString &name);

        /**
         * Checks one of the quest markers.
         *
         * @param marker The quest marker to check.
         *
         * @return true if the quest marker is set, false otherwise.
         */
        auto getQuestMarker(dw_quest marker) const -> bool;

        /**
         * Sets one of the quest markers.
         *
         * @param marker The quest marker to set.
         * @param set true to set, false to clear.
         */
        void setQuestMarker(dw_quest marker, bool set = true);

        /**
         * Gets the hero's shield.
         *
         * @return The shield.
         */
        auto getShield() const -> dw_shield;

        /**
         * Sets the hero's shield.
         *
         * @param shield The new shield.
         */
        void setShield(dw_shield shield);

        /**
         * Checks whether a game is valid or not.
         *
         * @param game The game to check.
         *
         * @return true if valid; false otherwise.
         */
        auto isValid(int game) const -> bool;

        /**
         * Gets the hero's weapon.
         *
         * @return The weapon.
         */
        auto getWeapon() const -> dw_weapon;

        /**
         * Sets the hero's weapon.
         *
         * @param weapon The new weapon.
         */
        void setWeapon(dw_weapon weapon);
    };

    inline auto SRAMFile::getArmor() const -> dw_armor {
        return static_cast<dw_armor>(offset[EQUIPMENT_OFFSET] & ARMOR_MASK);
    }

    inline auto SRAMFile::getGame() const -> int {
        return game;
    }

    inline auto SRAMFile::getHerbs() const -> int {
        return offset[HERBS_OFFSET];
    }

    inline auto SRAMFile::getHP() const -> unsigned int {
        return offset[HP_OFFSET];
    }

    inline auto SRAMFile::getKeys() const -> int {
        return offset[KEYS_OFFSET];
    }

    inline auto SRAMFile::isModified() const -> bool {
        return modified;
    }

    inline auto SRAMFile::getMP() const -> unsigned int {
        return offset[MP_OFFSET];
    }

    inline auto SRAMFile::getQuestMarker(dw_quest marker) const -> bool {
        return offset[QUEST_OFFSETS[marker].first]
               & QUEST_OFFSETS[marker].second;
    }

    inline auto SRAMFile::getShield() const -> dw_shield {
        return static_cast<dw_shield>(offset[EQUIPMENT_OFFSET] & SHIELD_MASK);
    }

    inline auto SRAMFile::isValid(int game) const -> bool {
        wxASSERT((game >= 0) && (game < 3));
        return valid[game];
    }

    inline auto SRAMFile::getWeapon() const -> dw_weapon {
        return static_cast<dw_weapon>(offset[EQUIPMENT_OFFSET] & WEAPON_MASK);
    }
}  // namespace dwsrame

#endif
