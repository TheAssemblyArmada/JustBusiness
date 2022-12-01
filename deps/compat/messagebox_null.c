/**
 * @file
 *
 * @author OmniBlade
 *
 * @brief Warpper around various platform windowing systems modal message boxes.
 *
 * @copyright Maverick is free software: you can redistribute it and/or
 *            modify it under the terms of the GNU General Public License
 *            as published by the Free Software Foundation, either version
 *            3 of the License, or (at your option) any later version.
 *            A full copy of the GNU General Public License can be found in
 *            LICENSE
 */
#include "messagebox.h"

int platform_messagebox(const char *message, const char *caption, int buttons, int type)
{
    return MSGBOX_UNKNOWN;
}
