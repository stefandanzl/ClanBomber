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
#include "MapTile_Arrow.h"

#include "GameObject.h"
#include "Bomb.h"
#include "Timer.h"

#include <stdio.h>

MapTile_Arrow::MapTile_Arrow(int _x, int _y , Direction _dir, ClanBomberApplication* _app) : MapTile_Ground( _x, _y,_app)
{
  dir = _dir;
  old_bomb = NULL;
  chill_countdown = 0;
  addon_sprite_nr = 1;
}

MapTile_Arrow::~MapTile_Arrow()
{
}

void MapTile_Arrow::act()
{
	MapTile::act();

	if (bomb) {
		if (bomb->is_stopped()) {
			bomb->snap();
		}
		if (bomb->get_cur_dir() != DIR_NONE  &&  bomb->get_cur_dir() != dir  &&  (bomb->get_cur_dir()+dir)%2 == 0  &&  !old_bomb) {
			bomb->snap();
			bomb->stop(true);
			chill_countdown = 0.5f;
		}
		if (chill_countdown > 0) {
			chill_countdown -= Timer::time_elapsed();
		}
		else {
			bomb->kick(dir, true);
		}
	}
	else {
		chill_countdown = 0;
	}
	old_bomb = bomb;
}

void MapTile_Arrow::draw(int addx, int addy)
{
	MapTile::draw (addx, addy);
	if (!vanishing) {
	  Resources::Game_maptile_addons()->blit( x+60+addx, y+40+addy,dir+1);
	}
}

void MapTile_Arrow::draw_tiny( int x, int y, float factor )
{
	uint8_t opacity = 255;

	if (vanishing) {
		opacity = vanish_countdown * 255;
	}

	MapTile::draw_tiny(  x,  y,  factor );
	Resources::Game_maptile_addons()->blit( x, y, factor, factor, dir+1, opacity );
}

int MapTile_Arrow::get_addon_sprite_nr() const
{
  return addon_sprite_nr + dir;
}

