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

// $Id: mainframe.hh,v 1.9 2007/02/01 03:01:02 technoplaza Exp $

#ifndef _DWSRAME_MAINFRAME_HH_
#define _DWSRAME_MAINFRAME_HH_

namespace dwsrame {
    class SRAMFile;
    
    class MainFrame : public wxFrame {
        DECLARE_CLASS(MainFrame)
        DECLARE_EVENT_TABLE()
        
    private:
        wxString sramFile;
        SRAMFile *sram;
        
        /**
         * Loads game data from the SRAM.
         *
         * @param game The game slot to load.
         */
        void loadGame(int game);
    
        /**
         * Loads the XRC controls and initializes this MainFrame.
         */
        void loadXRC();
        
        /**
         * Opens a Dragon Warrior SRAM file for editing.
         *
         * @param filename The filename to open.
         */
        void openSRAM(const wxString &filename);
        
        /**
         * Called when the hero's armor is changed.
         */
        void onArmorChange(wxCommandEvent &);
        
        /**
         * Called when the hero's experience is changed.
         */
        void onExperienceEdit(wxCommandEvent &);
        
        /**
         * Called when the file menu's exit command is triggered.
         */
        void onFileExit(wxCommandEvent &);
        
        /**
         * Called when the file menu's open command is triggered.
         */
        void onFileOpen(wxCommandEvent &);
        
        /**
         * Called when the file menu's save command is triggered.
         */
        void onFileSave(wxCommandEvent &);
        
        /**
         * Called when the hero's gold is changed.
         */
        void onGoldEdit(wxCommandEvent &);
        
        /**
         * Called when Gwaelin's location is changed.
         */
        void onGwaelinChange(wxCommandEvent &);
        
        /**
         * Called when the help menu's about command is triggered.
         */
        void onHelpAbout(wxCommandEvent &);
        
        /**
         * Called when the hero's herbs are changed.
         */
        void onHerbsEdit(wxCommandEvent &);
        
        /**
         * Called when the hero's HP is changed.
         */
        void onHPEdit(wxCommandEvent &);
        
        /**
         * Called when one of the hero's inventory items is changed.
         *
         * @param event The triggering wxCommandEvent.
         */
        void onInventoryChange(wxCommandEvent &event);
        
        /**
         * Called when the hero's keys are changed.
         */
        void onKeysEdit(wxCommandEvent &);
        
        /**
         * Called when the hero's MP is changed.
         */
        void onMPEdit(wxCommandEvent &);
        
        /**
         * Called when the hero's name is changed.
         */
        void onNameEdit(wxCommandEvent &);
        
        /**
         * Called when one of the quest markers is changed.
         *
         * @param event The triggering wxCommandEvent.
         */
        void onQuestMarkerChange(wxCommandEvent &event);
        
        /**
         * Called when the hero's shield is changed.
         */
        void onShieldChange(wxCommandEvent &);
        
        /**
         * Called when the hero's weapon is changed.
         */
        void onWeaponChange(wxCommandEvent &);
        
    public:
        /**
         * Creates a new MainFrame.
         */
        MainFrame();
    };
    
    inline void MainFrame::onFileExit(wxCommandEvent &)
        { Close(); }
}

#endif

