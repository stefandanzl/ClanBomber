/* This file is part of ClanBomber <http://www.nongnu.org/clanbomber>.
 * Copyright (C) 1999-2004, 2007 Andreas Hundt, Denis Oliver Kropp
 * Copyright (C) 2008-2011, 2017 Rene Lopez <rsl@member.fsf.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MAPTILE_ICE_H
#define MAPTILE_ICE_H

#include "MapTile_Ground.h"

/**
  *@author Andreas Hundt, Denis Oliver Kropp
  */

class MapTile_Ice : public MapTile_Ground
{
public:
	MapTile_Ice(int _x, int _y, ClanBomberApplication* _app);
	virtual ~MapTile_Ice();
	
	void act();
	void draw(int addx, int addy);
	void draw_tiny( int x, int y, float factor );
	TYPE get_type() { return ICE; }
};

#endif














