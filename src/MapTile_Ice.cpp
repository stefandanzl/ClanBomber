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

#include "ClanBomber.h"
#include "MapTile_Ice.h"
#include "GameObject.h"

MapTile_Ice::MapTile_Ice(int _x, int _y, ClanBomberApplication* _app) : MapTile_Ground(_x, _y, _app)
{
  addon_sprite_nr = 0;
}

MapTile_Ice::~MapTile_Ice()
{
}

void MapTile_Ice::act()
{
	MapTile::act();

	//CL_Iterator<GameObject> object_counter(objects);
	for(std::list<GameObject*>::iterator object_iter = objects.begin();
	    object_iter != objects.end();
	    object_iter++) {
	  (*object_iter)->move(80,DIR_NONE);
	}
}



void MapTile_Ice::draw(int addx, int addy)
{
	MapTile::draw (addx, addy);

	if (!vanishing) {
	  Resources::Game_maptile_addons()->blit( x+60+addx, y+40+addy,0);
	}
}

void MapTile_Ice::draw_tiny( int x, int y, float factor )
{
	uint8_t opacity = 255;

	if (vanishing) {
		opacity = vanish_countdown * 255;
	}

	MapTile::draw_tiny(  x,  y,  factor );
	Resources::Game_maptile_addons()->blit( x, y, factor, factor, 0, opacity );
}
