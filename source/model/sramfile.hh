/*
 * dwsrame - Dragon Warrior SRAM Editor
 * Copyright (C) 2006-2007 emuWorks
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

// $Id: sramfile.hh,v 1.6 2007/01/31 21:12:57 technoplaza Exp $

#ifndef _DWSRAME_SRAMFILE_HH_
#define _DWSRAME_SRAMFILE_HH_

#include <utility>

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
    
    /// the magic points offset
    const int MP_OFFSET = 0x18;
    
    /// the name offset
    const int NAME_OFFSET = 0xE;
    
    /// the shield bits of the equipment byte
    const int SHIELD_MASK = 0x3;
    
    /// the size of an SRAM file
    const int SRAM_SIZE = 0x2000;
    
    /// the weapon bits of the equipment byte
    const int WEAPON_MASK = 0xE0;
    
    /// the armors
    enum dw_armor {
        DW_NOARMOR, DW_CLOTHES = 0x4, DW_LEATHERARMOR = 0x8, DW_CHAINMAIL = 0xC,
        DW_HALFPLATE = 0x10, DW_FULLPLATE = 0x14, DW_MAGICARMOR = 0x18,
        DW_ERDRICKSARMOR = 0x1C
    };
    
    /// the items
    enum dw_item {
        DW_NOITEM, DW_TORCH, DW_FAIRYWATER, DW_WINGS, DW_DRAGONSSCALE,
        DW_FAIRYFLUTE, DW_FIGHTERSRING, DW_ERDRICKSTOKEN, DW_GWAELINSLOVE,
        DW_CURSEDBELT, DW_SILVERHARP, DW_DEATHNECKLACE, DW_STONESOFSUNLIGHT,
        DW_STAFFOFRAIN, DW_RAINBOWDROP
    };
    
    /// the quest markers
    enum dw_quest {
        DW_HIDDENSTAIRS, DW_RAINBOWBRIDGE, DW_USINGDRAGONSSCALE,
        DW_USINGFIGHTERSRING, DW_USINGCURSEDBELT, DW_USINGDEATHNECKLACE,
        DW_HOLDINGGWAELIN, DW_GWAELINONTHRONE, DW_LORIKSCHAMBER, DW_GOLEMDEAD,
        DW_DRAGONLORDDEAD, DW_GREENDRAGONDEAD
    };
    
    /// the shields
    enum dw_shield {
        DW_NOSHIELD, DW_SMALLSHIELD, DW_LARGESHIELD, DW_SILVERSHIELD
    };
    
    /// the weapons
    enum dw_weapon {
        DW_NOWEAPON, DW_BAMBOOPOLE = 0x20, DW_CLUB = 0x40,
        DW_COPPERSWORD = 0x60, DW_HANDAXE = 0x80, DW_BROADSWORD = 0xA0,
        DW_FLAMESWORD = 0xC0, DW_ERDRICKSSWORD = 0xE0
    };
    
    class SRAMFile {
    private:
        int game;
        char sram[SRAM_SIZE];
        unsigned char *offset;
        bool valid[3], modified;
        
        /// the various quest offsets
        static const std::pair<int, int> QUEST_OFFSETS[];
        
        /**
         * Calculates the checksum for one of the save games.
         *
         * @param game The game to checksum.
         *
         * @return The checksum.
         */
        wxUint16 checksum(int game) const;
        
        /**
         * Converts an ASCII character to the Dragon Warrior alphabet.
         */
        char fromASCII(char asciiChar) const;
        
        /**
         * Converts a Dragon Warrior alphabetic character to ASCII.
         *
         * @param dwChar The Dragon Warrior character.
         *
         * @return The ASCII character.
         */
        char toASCII(char dwChar) const;
        
        /**
         * Gets the checksum for one of the save games.
         *
         * @param game The game.
         *
         * @return The checksum.
         */
        wxUint16 getChecksum(int game) const;
        
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
        SRAMFile(const wxString &filename) throw(InvalidSRAMFileException);
        
        /**
         * Saves this SRAMfile back to disk.
         *
         * @param filename The filename to write the data to.
         *
         * @return true on success; false otherwise.
         */
        bool save(const wxString &filename);
        
        /**
         * Gets the hero's armor.
         *
         * @return The armor.
         */
        enum dw_armor getArmor() const;
        
        /**
         * Sets the hero's armor.
         *
         * @param armor The new armor.
         */
        void setArmor(enum dw_armor armor);
        
        /**
         * Gets the hero's experience.
         *
         * @return The experience.
         */
        wxUint16 getExperience() const;
        
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
        int getGame() const;
        
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
        wxUint16 getGold() const;
        
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
        int getHerbs() const;
        
        /**
         * Sets the hero's herbs.
         *
         * @param The new herbs.
         */
        void setHerbs(int herbs);
        
        /**
         * Gets the hero's current HP.
         *
         * @return The current HP.
         */
        unsigned int getHP() const;
        
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
        enum dw_item getItem(int number) const;
        
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
        int getKeys() const;
        
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
        bool isModified() const;
        
        /**
         * Gets the hero's current MP.
         *
         * @return The current MP.
         */
        unsigned int getMP() const;
        
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
        wxString getName() const;
        
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
        bool getQuestMarker(enum dw_quest marker) const;
        
        /**
         * Sets one of the quest markers.
         *
         * @param marker The quest marker to set.
         * @param set true to set, false to clear.
         */
        void setQuestMarker(enum dw_quest marker, bool set = true);
        
        /**
         * Gets the hero's shield.
         *
         * @return The shield.
         */
        enum dw_shield getShield() const;
        
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
        bool isValid(int game) const;
        
        /**
         * Gets the hero's weapon.
         *
         * @return The weapon.
         */
        enum dw_weapon getWeapon() const;
        
        /**
         * Sets the hero's weapon.
         *
         * @param weapon The new weapon.
         */
        void setWeapon(enum dw_weapon weapon);
    };
    
    inline enum dw_armor SRAMFile::getArmor() const
        {
            return static_cast<enum dw_armor>
                (offset[EQUIPMENT_OFFSET] & ARMOR_MASK);
        }
    
    inline int SRAMFile::getGame() const
        { return game; }
        
    inline int SRAMFile::getHerbs() const
        { return offset[HERBS_OFFSET]; }

    inline unsigned int SRAMFile::getHP() const
        { return offset[HP_OFFSET]; }

    inline int SRAMFile::getKeys() const
        { return offset[KEYS_OFFSET]; }
        
    inline bool SRAMFile::isModified() const 
        { return modified; }
        
    inline unsigned int SRAMFile::getMP() const
        { return offset[MP_OFFSET]; }

    inline bool SRAMFile::getQuestMarker(enum dw_quest marker) const
        {
            return offset[QUEST_OFFSETS[marker].first] &
                   QUEST_OFFSETS[marker].second;
        }
        
    inline enum dw_shield SRAMFile::getShield() const
        {
            return static_cast<enum dw_shield>
                (offset[EQUIPMENT_OFFSET] & SHIELD_MASK);
        }
    
    inline bool SRAMFile::isValid(int game) const
        {
            wxASSERT((game >= 0) && (game < 3));
            return valid[game];
        }
        
    inline enum dw_weapon SRAMFile::getWeapon() const
        {
            return static_cast<enum dw_weapon>
                (offset[EQUIPMENT_OFFSET] & WEAPON_MASK);
        }
}

#endif

