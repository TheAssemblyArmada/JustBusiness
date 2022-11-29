/**
 * @file
 *
 * @author OmniBlade
 *
 * @brief
 *
 * @copyright JustBusiness is free software: you can redistribute it and/or
 *            modify it under the terms of the GNU General Public License
 *            as published by the Free Software Foundation, either version
 *            3 of the License, or (at your option) any later version.
 *            A full copy of the GNU General Public License can be found in
 *            LICENSE
 */
#pragma once

#include <stdint.h>

enum PlayerType : int8_t
{
    PLAYER_1,
    PLAYER_2,
    PLAYER_3,
    PLAYER_4,
    PLAYER_5,
    PLAYER_6,
    TOTAL_PLAYERS,
    FIRST_PLAYER = PLAYER_1,
    LAST_PLAYER = PLAYER_6,
    ALL_PLAYERS = -1,
    NO_PLAYER = -1,
};

