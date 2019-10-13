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

#ifndef _DWSRAME_INVALIDSRAMFILEEXCEPTION_HH_
#define _DWSRAME_INVALIDSRAMFILEEXCEPTION_HH_

#include <stdexcept>

namespace dwsrame {
    /// The possible InvalidSRAMFileException error codes
    enum isfe_error { ISFE_FILENOTFOUND, ISFE_INVALIDSIZE, ISFE_NOVALIDGAMES };

    /// exception thrown when an invalid SRAM file is detected
    class InvalidSRAMFileException : public std::runtime_error {
      private:
        enum isfe_error error;

      public:
        /**
         * Creates a new InvalidSRAMFileException.
         *
         * @param error The error code that triggered this exception.
         */
        InvalidSRAMFileException(enum isfe_error error);

        /**
         * Gets the error code for this InvalidSRAMFileException.
         *
         * @return The error code.
         */
        enum isfe_error getError() const;
    };

    inline InvalidSRAMFileException::InvalidSRAMFileException(
        enum isfe_error error)
        : std::runtime_error("InvalidSRAMFileException"), error(error) {}

    inline enum isfe_error InvalidSRAMFileException::getError() const {
        return error;
    }
} // namespace dwsrame

#endif
