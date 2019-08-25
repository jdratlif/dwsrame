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

// $Id: dwsrame.cc,v 1.3 2008/12/15 22:48:11 jdratlif Exp $

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/xrc/xmlres.h>

#include "dwsrame.hh"
#include "view/mainframe.hh"

using namespace dwsrame;

// prototype for InitXmlResource function
void InitXmlResource();

bool dwsrameApp::OnInit() {
    // initialize the XRC resources
    wxXmlResource::Get()->InitAllHandlers();
    InitXmlResource();
    
    frame = new MainFrame;
    frame->Show();
    
    return true;
}

IMPLEMENT_CLASS(dwsrameApp, wxApp)
IMPLEMENT_APP(dwsrameApp)

