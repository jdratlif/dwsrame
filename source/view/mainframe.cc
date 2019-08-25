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

// $Id: mainframe.cc,v 1.9 2007/02/01 03:01:02 technoplaza Exp $

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/spinctrl.h>
#include <wx/xrc/xmlres.h>

#include "model/sramfile.hh"
#include "view/mainframe.hh"

using namespace dwsrame;

MainFrame::MainFrame() : sram(0) {
    SetParent(NULL);
    
    loadXRC();
    GetSizer()->SetSizeHints(this);
    Centre();
    
    // hide the notebook
    XRCCTRL(*this, "IDN_DWSRAME", wxNotebook)->Show(false);
}

void MainFrame::loadGame(int game) {
    wxASSERT(sram);
    wxASSERT(sram->isValid(game));
    
    sram->setGame(game);
    
    // hero's stats
    XRCCTRL(*this, "IDT_HERO_NAME", wxTextCtrl)->SetValue(sram->getName());
    XRCCTRL(*this, "IDT_HERO_HP", wxTextCtrl)->
        SetValue(wxString::Format("%u", sram->getHP()));
    XRCCTRL(*this, "IDT_HERO_MP", wxTextCtrl)->
        SetValue(wxString::Format("%u", sram->getMP()));
    XRCCTRL(*this, "IDT_HERO_EXP", wxTextCtrl)->
        SetValue(wxString::Format("%u", sram->getExperience()));
    XRCCTRL(*this, "IDT_HERO_GOLD", wxTextCtrl)->
        SetValue(wxString::Format("%u", sram->getGold()));
        
    // hero's inventory
    XRCCTRL(*this, "IDS_HERO_HERBS", wxSpinCtrl)->SetValue(sram->getHerbs());
    XRCCTRL(*this, "IDS_HERO_KEYS", wxSpinCtrl)->SetValue(sram->getKeys());
    
    XRCCTRL(*this, "IDC_HERO_INVENTORY1", wxChoice)->
        SetSelection(sram->getItem(0));
    XRCCTRL(*this, "IDC_HERO_INVENTORY2", wxChoice)->
        SetSelection(sram->getItem(1));
    XRCCTRL(*this, "IDC_HERO_INVENTORY3", wxChoice)->
        SetSelection(sram->getItem(2));
    XRCCTRL(*this, "IDC_HERO_INVENTORY4", wxChoice)->
        SetSelection(sram->getItem(3));
    XRCCTRL(*this, "IDC_HERO_INVENTORY5", wxChoice)->
        SetSelection(sram->getItem(4));
    XRCCTRL(*this, "IDC_HERO_INVENTORY6", wxChoice)->
        SetSelection(sram->getItem(5));
    XRCCTRL(*this, "IDC_HERO_INVENTORY7", wxChoice)->
        SetSelection(sram->getItem(6));
    XRCCTRL(*this, "IDC_HERO_INVENTORY8", wxChoice)->
        SetSelection(sram->getItem(7));
        
    // hero's equipment
    XRCCTRL(*this, "IDC_HERO_WEAPON", wxChoice)->
        SetSelection(sram->getWeapon() / 0x20);
    XRCCTRL(*this, "IDC_HERO_ARMOR", wxChoice)->
        SetSelection(sram->getArmor() / 0x4);
    XRCCTRL(*this, "IDC_HERO_SHIELD", wxChoice)->
        SetSelection(sram->getShield());
        
    XRCCTRL(*this, "IDN_DWSRAME", wxNotebook)->Show(true);
    
    // quest markers
    XRCCTRL(*this, "IDC_QUEST_LORIKSCHAMBER", wxCheckBox)->
        SetValue(sram->getQuestMarker(DW_LORIKSCHAMBER));
        
    XRCCTRL(*this, "IDC_QUEST_DRAGONSSCALE", wxCheckBox)->
        SetValue(sram->getQuestMarker(DW_USINGDRAGONSSCALE));
    XRCCTRL(*this, "IDC_QUEST_FIGHTERSRING", wxCheckBox)->
        SetValue(sram->getQuestMarker(DW_USINGFIGHTERSRING));
    XRCCTRL(*this, "IDC_QUEST_CURSEDBELT", wxCheckBox)->
        SetValue(sram->getQuestMarker(DW_USINGCURSEDBELT));
    XRCCTRL(*this, "IDC_QUEST_DEATHNECKLACE", wxCheckBox)->
        SetValue(sram->getQuestMarker(DW_USINGDEATHNECKLACE));
        
    if (sram->getQuestMarker(DW_GWAELINONTHRONE)) {
        XRCCTRL(*this, "IDC_QUEST_GWAELIN", wxChoice)->SetSelection(2);
    } else if (sram->getQuestMarker(DW_HOLDINGGWAELIN)) {
        XRCCTRL(*this, "IDC_QUEST_GWAELIN", wxChoice)->SetSelection(1);
    } else {
        XRCCTRL(*this, "IDC_QUEST_GWAELIN", wxChoice)->SetSelection(0);
    }
        
    XRCCTRL(*this, "IDC_QUEST_RAINBOWBRIDGE", wxCheckBox)->
        SetValue(sram->getQuestMarker(DW_RAINBOWBRIDGE));
    XRCCTRL(*this, "IDC_QUEST_HIDDENSTAIRS", wxCheckBox)->
        SetValue(sram->getQuestMarker(DW_HIDDENSTAIRS));
        
    XRCCTRL(*this, "IDC_QUEST_GREENDRAGON", wxCheckBox)->
        SetValue(sram->getQuestMarker(DW_GREENDRAGONDEAD));
    XRCCTRL(*this, "IDC_QUEST_GOLEM", wxCheckBox)->
        SetValue(sram->getQuestMarker(DW_GOLEMDEAD));
    XRCCTRL(*this, "IDC_QUEST_DRAGONLORD", wxCheckBox)->
        SetValue(sram->getQuestMarker(DW_DRAGONLORDDEAD));
}

void MainFrame::loadXRC() {
    wxXmlResource::Get()->LoadFrame(this, GetParent(), wxT("IDF_DWSRAME"));
    //SetIcon(wxIcon(icon32x32_xpm));
}

void MainFrame::openSRAM(const wxString &filename) {
    // TODO: need some check for already open files somewhere
    try {
        sram = new SRAMFile(filename);
        sramFile = filename;
        
        for (int i = 0; i < 3; ++i) {
            if (sram->isValid(i)) {
                loadGame(i);
                break;
            }
        }
    } catch (InvalidSRAMFileException &e) {
        wxString error;
        
        switch (e.getError()) {
            case ISFE_FILENOTFOUND:
                error = wxT("File Not Found");
                break;
            case ISFE_INVALIDSIZE:
                error = wxT("Invalid SRAM File Size");
                break;
            case ISFE_NOVALIDGAMES:
                error = wxT("No Games Exist");
                break;
        }
        
        wxMessageBox(error,
            wxT("Error: Invalid SRAM file"),
            wxOK | wxICON_ERROR);
    }
}

void MainFrame::onArmorChange(wxCommandEvent &) {
    sram->setArmor(static_cast<enum dw_armor>
        (XRCCTRL(*this, "IDC_HERO_ARMOR", wxChoice)->GetSelection() * 0x4));
}

void MainFrame::onExperienceEdit(wxCommandEvent &) {
    long temp;
    
    if (XRCCTRL(*this, "IDT_HERO_EXP", wxTextCtrl)->GetValue().ToLong(&temp)) {
        sram->setExperience(temp);
    }
}

void MainFrame::onFileOpen(wxCommandEvent &) {
    wxFileDialog dlg(this, wxT("Select a Dragon Warrior (NES) SRAM file"),
                     wxEmptyString, wxEmptyString,
                     wxT("SRAM Files (*.sav)|*.sav"), wxOPEN);
                     
    if (dlg.ShowModal() == wxID_OK) {
        openSRAM(dlg.GetPath());
    }
}

void MainFrame::onFileSave(wxCommandEvent &) {
    wxASSERT(sram);
    
    // TODO: what if save returned false?
    sram->save(sramFile);
}

void MainFrame::onGoldEdit(wxCommandEvent &) {
    long temp;
    
    if (XRCCTRL(*this, "IDT_HERO_GOLD", wxTextCtrl)->GetValue().ToLong(&temp)) {
        sram->setGold(temp);
    }
}

void MainFrame::onGwaelinChange(wxCommandEvent &) {
    int value = XRCCTRL(*this, "IDC_QUEST_GWAELIN", wxChoice)->GetSelection();
    
    switch (value) {
        case 0:
            sram->setQuestMarker(DW_HOLDINGGWAELIN, false);
            sram->setQuestMarker(DW_GWAELINONTHRONE, false);
            break;
            
        case 1:
            sram->setQuestMarker(DW_HOLDINGGWAELIN, true);
            sram->setQuestMarker(DW_GWAELINONTHRONE, false);
            break;
            
        case 2:
            sram->setQuestMarker(DW_HOLDINGGWAELIN, false);
            sram->setQuestMarker(DW_GWAELINONTHRONE, true);
            break;
    }
}

void MainFrame::onHelpAbout(wxCommandEvent &) {
    wxMessageBox(wxT("dwsrame 0.80 - Dragon Warrior SRAM Editor\n"
                     "Copyright (C) 2006-2007 emuWorks\n"
                     "http://games.technoplaza.net/"),
        wxT("About dwsrame..."), wxOK | wxICON_INFORMATION);
}

void MainFrame::onHerbsEdit(wxCommandEvent &) {
    sram->setHerbs(XRCCTRL(*this, "IDS_HERO_HERBS", wxSpinCtrl)->GetValue());
}

void MainFrame::onHPEdit(wxCommandEvent &) {
    long temp;
    
    if (XRCCTRL(*this, "IDT_HERO_HP", wxTextCtrl)->GetValue().ToLong(&temp)) {
        sram->setHP(temp);
    }
}

void MainFrame::onInventoryChange(wxCommandEvent &event) {
    int item;
    
    if (event.GetId() == XRCID("IDC_HERO_INVENTORY1")) {
        item = 0;
    } else if (event.GetId() == XRCID("IDC_HERO_INVENTORY2")) {
        item = 1;
    } else if (event.GetId() == XRCID("IDC_HERO_INVENTORY3")) {
        item = 2;
    } else if (event.GetId() == XRCID("IDC_HERO_INVENTORY4")) {
        item = 3;
    } else if (event.GetId() == XRCID("IDC_HERO_INVENTORY5")) {
        item = 4;
    } else if (event.GetId() == XRCID("IDC_HERO_INVENTORY6")) {
        item = 5;
    } else if (event.GetId() == XRCID("IDC_HERO_INVENTORY7")) {
        item = 6;
    } else {
        wxASSERT(event.GetId() == XRCID("IDC_HERO_INVENTORY8"));
        
        item = 7;
    }
    
    sram->setItem(static_cast<enum dw_item>(event.GetSelection()), item);
}

void MainFrame::onKeysEdit(wxCommandEvent &) {
    sram->setKeys(XRCCTRL(*this, "IDS_HERO_KEYS", wxSpinCtrl)->GetValue());
}

void MainFrame::onMPEdit(wxCommandEvent &) {
    long temp;
    
    if (XRCCTRL(*this, "IDT_HERO_MP", wxTextCtrl)->GetValue().ToLong(&temp)) {
        sram->setMP(temp);
    }
}

void MainFrame::onNameEdit(wxCommandEvent &) {
    sram->setName(XRCCTRL(*this, "IDT_HERO_NAME", wxTextCtrl)->GetValue());
}

void MainFrame::onQuestMarkerChange(wxCommandEvent &event) {
    enum dw_quest marker;
    
    if (event.GetId() == XRCID("IDC_QUEST_LORIKSCHAMBER")) {
        marker = DW_LORIKSCHAMBER;
    } else if (event.GetId() == XRCID("IDC_QUEST_DRAGONSSCALE")) {
        marker = DW_USINGDRAGONSSCALE;
    } else if (event.GetId() == XRCID("IDC_QUEST_FIGHTERSRING")) {
        marker = DW_USINGFIGHTERSRING;
    } else if (event.GetId() == XRCID("IDC_QUEST_CURSEDBELT")) {
        marker = DW_USINGCURSEDBELT;
    } else if (event.GetId() == XRCID("IDC_QUEST_DEATHNECKLACE")) {
        marker = DW_USINGDEATHNECKLACE;
    } else if (event.GetId() == XRCID("IDC_QUEST_RAINBOWBRIDGE")) {
        marker = DW_RAINBOWBRIDGE;
    } else if (event.GetId() == XRCID("IDC_QUEST_HIDDENSTAIRS")) {
        marker = DW_HIDDENSTAIRS;
    } else if (event.GetId() == XRCID("IDC_QUEST_GREENDRAGON")) {
        marker = DW_GREENDRAGONDEAD;
    } else if (event.GetId() == XRCID("IDC_QUEST_GOLEM")) {
        marker = DW_GOLEMDEAD;
    } else {
        wxASSERT(event.GetId() == XRCID("IDC_QUEST_DRAGONLORD"));
        
        marker = DW_DRAGONLORDDEAD;
    }
    
    sram->setQuestMarker(marker, event.IsChecked());
}

void MainFrame::onShieldChange(wxCommandEvent &) {
    sram->setShield(static_cast<enum dw_shield>
        (XRCCTRL(*this, "IDC_HERO_SHIELD", wxChoice)->GetSelection()));
}

void MainFrame::onWeaponChange(wxCommandEvent &) {
    sram->setWeapon(static_cast<enum dw_weapon>
        (XRCCTRL(*this, "IDC_HERO_WEAPON", wxChoice)->GetSelection() * 0x20));
}

IMPLEMENT_CLASS(MainFrame, wxFrame)

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_CHECKBOX(XRCID("IDC_QUEST_LORIKSCHAMBER"),
        MainFrame::onQuestMarkerChange)
    EVT_CHECKBOX(XRCID("IDC_QUEST_DRAGONSSCALE"),
        MainFrame::onQuestMarkerChange)
    EVT_CHECKBOX(XRCID("IDC_QUEST_FIGHTERSRING"),
        MainFrame::onQuestMarkerChange)
    EVT_CHECKBOX(XRCID("IDC_QUEST_CURSEDBELT"),
        MainFrame::onQuestMarkerChange)
    EVT_CHECKBOX(XRCID("IDC_QUEST_DEATHNECKLACE"),
        MainFrame::onQuestMarkerChange)
    EVT_CHECKBOX(XRCID("IDC_QUEST_RAINBOWBRIDGE"),
        MainFrame::onQuestMarkerChange)
    EVT_CHECKBOX(XRCID("IDC_QUEST_HIDDENSTAIRS"),
        MainFrame::onQuestMarkerChange)
    EVT_CHECKBOX(XRCID("IDC_QUEST_GREENDRAGON"),
        MainFrame::onQuestMarkerChange)
    EVT_CHECKBOX(XRCID("IDC_QUEST_GOLEM"),
        MainFrame::onQuestMarkerChange)
    EVT_CHECKBOX(XRCID("IDC_QUEST_DRAGONLORD"),
        MainFrame::onQuestMarkerChange)

    EVT_CHOICE(XRCID("IDC_HERO_INVENTORY1"), MainFrame::onInventoryChange)
    EVT_CHOICE(XRCID("IDC_HERO_INVENTORY2"), MainFrame::onInventoryChange)
    EVT_CHOICE(XRCID("IDC_HERO_INVENTORY3"), MainFrame::onInventoryChange)
    EVT_CHOICE(XRCID("IDC_HERO_INVENTORY4"), MainFrame::onInventoryChange)
    EVT_CHOICE(XRCID("IDC_HERO_INVENTORY5"), MainFrame::onInventoryChange)
    EVT_CHOICE(XRCID("IDC_HERO_INVENTORY6"), MainFrame::onInventoryChange)
    EVT_CHOICE(XRCID("IDC_HERO_INVENTORY7"), MainFrame::onInventoryChange)
    EVT_CHOICE(XRCID("IDC_HERO_INVENTORY8"), MainFrame::onInventoryChange)
    
    EVT_CHOICE(XRCID("IDC_HERO_WEAPON"), MainFrame::onWeaponChange)
    EVT_CHOICE(XRCID("IDC_HERO_ARMOR"), MainFrame::onArmorChange)
    EVT_CHOICE(XRCID("IDC_HERO_SHIELD"), MainFrame::onShieldChange)
    
    EVT_CHOICE(XRCID("IDC_QUEST_GWAELIN"), MainFrame::onGwaelinChange)

    EVT_MENU(wxID_OPEN, MainFrame::onFileOpen)
    EVT_MENU(wxID_SAVE, MainFrame::onFileSave)
    EVT_MENU(wxID_EXIT, MainFrame::onFileExit)
    
    EVT_TEXT(XRCID("IDT_HERO_NAME"), MainFrame::onNameEdit)
    EVT_TEXT(XRCID("IDT_HERO_HP"), MainFrame::onHPEdit)
    EVT_TEXT(XRCID("IDT_HERO_MP"), MainFrame::onMPEdit)
    EVT_TEXT(XRCID("IDT_HERO_EXP"), MainFrame::onExperienceEdit)
    EVT_TEXT(XRCID("IDT_HERO_GOLD"), MainFrame::onGoldEdit)
    
    EVT_TEXT(XRCID("IDS_HERO_HERBS"), MainFrame::onHerbsEdit)
    EVT_TEXT(XRCID("IDS_HERO_KEYS"), MainFrame::onKeysEdit)
    
    EVT_MENU(wxID_ABOUT, MainFrame::onHelpAbout)
END_EVENT_TABLE()

