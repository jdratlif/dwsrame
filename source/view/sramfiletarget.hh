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

#ifndef _DWSRAME_SRAMFILETARGET_HH_
#define _DWSRAME_SRAMFILETARGET_HH_

#include <wx/dnd.h>

namespace dwsrame {
    class MainFrame;

    /// Class to implement a drop target for SRAM files
    class SRAMFileTarget : public wxFileDropTarget {
      private:
        MainFrame *frame;

      public:
        /**
         * Creates a new SRAMFileTarget.
         *
         * @param frame The MainFrame to send files to.
         */
        SRAMFileTarget(MainFrame *frame);

        /**
         * Called when files are dropped on the associated MainFrame.
         *
         * @param files The filenames.
         *
         * @return true if the drop was accepted; false otherwise.
         */
        auto OnDropFiles(wxCoord, wxCoord, const wxArrayString &files)
            -> bool override;
    };

    inline SRAMFileTarget::SRAMFileTarget(MainFrame *frame) : frame(frame) {}
}  // namespace dwsrame

#endif
