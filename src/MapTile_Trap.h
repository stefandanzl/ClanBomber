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

#ifndef MAPTILE_TRAP_H
#define MAPTILE_TRAP_H

class Bomb;

#include "MapTile_Ground.h"

#include <list>

/**
  *@author Andreas Hundt, Denis Oliver Kropp
  */

class MapTile_Trap : public MapTile_Ground  {
public: 
	MapTile_Trap(int _x, int _y, ClanBomberApplication* _app);
	~MapTile_Trap();

	void act();
	void draw(int addx, int addy);
	void draw_tiny( int x, int y, float factor );
	TYPE get_type() { return TRAP; }

protected:
	class Bomb_Entry
	{
	public:
		Bomb_Entry( Bomb *_bomb );
		void count();
		bool ready_to_shoot();
		Bomb *get_bomb() { return bomb; }
	protected:
		float countdown;
		Bomb *bomb;
	};

	std::list<Bomb_Entry*> bombs;
};

#endif






