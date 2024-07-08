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
#include "MapTile_Wall.h"
#include "GameConfig.h"

MapTile_Wall::MapTile_Wall(int _x, int _y, ClanBomberApplication* _app) : MapTile(_x, _y, _app)
{
	sprite_nr = GameConfig::get_theme()*4 +1;
	passable = false;
	blocking = true;
	next = GROUND;
}

MapTile_Wall::~MapTile_Wall()
{
}

void MapTile_Wall::act()
{
	MapTile::act();
}

void MapTile_Wall::vanish()
{
	if (ClanBomberApplication::is_server() || !ClanBomberApplication::is_client()) {
		delete_me = true;
	}
}
