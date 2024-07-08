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
#include "MapTile_Box.h"
#include "GameConfig.h"
#include "Server.h"

MapTile_Box::MapTile_Box(int _x, int _y, ClanBomberApplication* _app) : MapTile(_x, _y, _app)
{
	sprite_nr = GameConfig::get_theme()*4 +2;
	next = GROUND;
	passable = false;
	blocking = true;
}

MapTile_Box::~MapTile_Box()
{
}

void MapTile_Box::act()
{
	MapTile::act();
	if (ClanBomberApplication::is_server() || !ClanBomberApplication::is_client()) {
		if (destroyed && destroy_countdown <= 0) {
			spawn_extra();
		}
	}
}

void MapTile_Box::destroy()
{
	if (!destroyed) {
		if (ClanBomberApplication::is_server()) {
		 	ClanBomberApplication::get_server()->send_SERVER_MAPTILE_VANISH(x, y);
		}
		destroyed = true;
		destroy_countdown = 0.5f;
		sprite_nr++;
	}
}

void MapTile_Box::vanish()
{
	destroy();
}
