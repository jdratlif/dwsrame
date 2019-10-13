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

#ifndef _DWSRAME_HH_
#define _DWSRAME_HH_

/// The project namespace
namespace dwsrame {
    class MainFrame;

    /// The main application class
    class dwsrameApp : public wxApp {
        DECLARE_CLASS(dwsrameApp)

      private:
        MainFrame *frame;

      public:
        /**
         * Called to initialize the application.
         *
         * @return true on successful initialization; false otherwise.
         */
        virtual bool OnInit();
    };

    DECLARE_APP(dwsrameApp)
} // namespace dwsrame

#endif
