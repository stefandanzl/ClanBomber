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
#include "MapTile_None.h"
#include "GameObject.h"
#include "Server.h"

#include "Utils.h"

MapTile_None::MapTile_None(int _x, int _y, ClanBomberApplication* _app) : MapTile(_x , _y, _app)
{
	passable = false;
	blocking = false;
}

MapTile_None::~MapTile_None()
{
}

void MapTile_None::draw(int addx, int addy)
{
/*	primary->SetDrawingFlags( primary, DSDRAW_NOFX );
	primary->SetColor( primary, 0, 0, 0, 0xFF);
	primary->FillRectangle( primary, x+60+addx, y+40+addy, 40, 40 );*/
  CB_FillRect(x+60+addx, y+40+addy, 40, 40, 0, 0, 0);
}

void MapTile_None::draw_tiny( int x, int y, float factor )
{
}

void MapTile_None::act()
{
	MapTile::act();
	if (ClanBomberApplication::is_server() || !ClanBomberApplication::is_client()) {
	  //CL_Iterator<GameObject> object_counter(objects);
	  for(std::list<GameObject*>::iterator object_iter = objects.begin();
	      object_iter != objects.end();
	      object_iter++) {
	    (*object_iter)->fall();
	  }
	}
}

void MapTile_None::vanish()
{
}
