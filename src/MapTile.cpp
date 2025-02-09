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

#include "config.h"

#include "ClanBomber.h"
#include "MapTile.h"

#include "MapTile_None.h"
#include "MapTile_Ground.h"
#include "MapTile_Box.h"
#include "MapTile_Wall.h"
#include "MapTile_Ice.h"
#include "MapTile_Arrow.h"
#include "MapTile_Trap.h"

#include "Extra_Bomb.h"
#include "Extra_Power.h"
#include "Extra_Skateboard.h"
#include "Extra_Kick.h"
#include "Extra_Glove.h"
#include "Extra_Joint.h"
#include "Extra_Viagra.h"
#include "Extra_Koks.h"
#ifdef ENABLE_EXPERIMENTAL_EXTRAS
#  include "Extra_Snail.hpp"
#endif

#include "GameConfig.h"
#include "Timer.h"
#include "GameObject.h"
#include "Bomb.h"
#include "Bomber.h"
#include "Map.h"
#include "Server.h"

#include "Utils.h"

MapTile::MapTile(int _x, int _y, ClanBomberApplication* _app)
{
	app = _app;
	x = _x;
	y = _y;
	vanishing = false;
	destroyed = false;
	bomb = NULL;
	sprite_nr = 0;
        addon_sprite_nr = -1;
	delete_me = false;
	passable = false;
	blocking = true;
	
	next = NONE;
}

MapTile::~MapTile()
{
}

int MapTile::get_x()
{
	return x;
}

int MapTile::get_y()
{
	return y;
}

void MapTile::set_vanishing(bool v)
{
	vanishing = v;
}

void MapTile::set_vanish_countdown(float cd)
{
	vanish_countdown = cd;
}

void MapTile::set_destroy_countdown(float cd)
{
        destroy_countdown = cd;
}

bool MapTile::is_passable()
{
	return passable;
}

bool MapTile::is_blocking()
{
	return blocking;
}

void MapTile::set_pos( int _x, int _y )
{
	x = _x;
	y = _y;
}

MapTile* MapTile::create( TYPE type, int _x, int _y, Direction _dir, ClanBomberApplication* _app )
{
	MapTile* ret = NULL;
	
	switch (type) {
		case NONE:
			ret = new MapTile_None(_x,_y,_app);
			break;
		case ARROW:
			ret = new MapTile_Arrow(_x,_y,_dir,_app);
			break;
		case TRAP:
			ret = new MapTile_Trap(_x,_y,_app);
			break;
		case GROUND:
			ret = new MapTile_Ground(_x,_y,_app);
			break;
		case BOX:
			ret = new MapTile_Box(_x,_y,_app);
			break;
		case WALL:
			ret = new MapTile_Wall(_x,_y,_app);
			break;
		case ICE:
			ret = new MapTile_Ice(_x,_y,_app);
			break;
		default:
			break;
	}

// this was for randomization
/* 
	if (GameConfig::get_theme() == 4) {
		ret->set_sprite_nr( (rand()%4) *4 +type);
	}
	else {
//		ret->set_sprite_nr( GameConfig::get_theme()*4 + type );
	}
*/
	return ret;
}

MapTile* MapTile::create( TYPE type, int _x, int _y, ClanBomberApplication* _app )
{
 	MapTile* ret = NULL;
 	
 	switch (type) {
 	 	case NONE:
 	        ret = new MapTile_None(_x,_y,_app);
	 	 	break;
       	case ARROW:
   	        ret = new MapTile_Arrow(_x,_y,DIR_NONE,_app);
		 	break;
       	case GROUND:
	        ret = new MapTile_Ground(_x,_y,_app);
			break;
 		case BOX:
	        ret = new MapTile_Box(_x,_y,_app);
			break;
		case WALL:
	        ret = new MapTile_Wall(_x,_y,_app);
			break;
 		case ICE:
	        ret = new MapTile_Ice(_x,_y,_app);
			break;
 		default:
			break;  
	}
// this was for randomization
/* 
	if (GameConfig::get_theme() == 4) {
 	 	ret->set_sprite_nr( (rand()%4) *4 +type);
	}
 	else {   
//		ret->set_sprite_nr( GameConfig::get_theme()*4 + type );
	}
*/
  	return ret;
}

MapTile* MapTile::spawn( MapTile* old_tile )
{
	return create( old_tile->next, old_tile->x, old_tile->y, old_tile->app );
}

void MapTile::draw(int addx, int addy)
{
  if (vanishing) {
    ///primary->SetDrawingFlags( primary, DSDRAW_NOFX );
    ///primary->SetColor( primary, 0, 0, 0, 0xFF );
    ///primary->FillRectangle( primary, x+60+addx, y+40+addy, 40, 40 );
    CB_FillRect(x+60+addx, y+40+addy, 40, 40, 0, 0, 0);
    draw_tiny((int)(x+80-vanish_countdown*20+addx), (int)(y+60-vanish_countdown*20+addy), vanish_countdown);
  }
  else {
    Resources::Game_maptiles()->blit( x+60+addx, y+40+addy, sprite_nr );
  }
  if (GameConfig::get_highlight_maptiles()) {
    ///primary->SetDrawingFlags( primary, DSDRAW_BLEND );
    ///primary->SetColor( primary, 0x00, 0x00, 0xFF, 50 );
    //CL_Iterator<GameObject> object_counter(objects);
    for(std::list<GameObject*>::iterator object_iter = objects.begin();
	object_iter != objects.end();
	object_iter++) {
      if ((*object_iter)->get_type() == GameObject::BOMBER) {
	if (GameConfig::bomber[static_cast<Bomber*>(*object_iter)->get_number()].get_highlight_maptile()) {
	  ///primary->FillRectangle( primary, x+60+addx, y+40+addy, 40, 40 );
	  CB_FillRect(x+60+addx, y+40+addy, 40, 40, 0, 0, 0);
	}
      }
    }
  }
}

void MapTile::draw_tiny( int x, int y, float factor )
{
	uint8_t opacity = 255;

	if (vanishing) {
		opacity = vanish_countdown * 255;
	}

	Resources::Game_maptiles()->blit( x, y, factor, factor, sprite_nr, opacity );
}

int MapTile::get_addon_sprite_nr() const
{
  return addon_sprite_nr;
}

void MapTile::draw_shaken()
{
	draw( rand()%4, rand()%4 );
}

void MapTile::vanish()
{
	if (!vanishing) {
		if (ClanBomberApplication::is_server()) {
			ClanBomberApplication::get_server()->send_SERVER_MAPTILE_VANISH(x, y);
		}
		passable = false;
		vanishing = true;
		vanish_countdown = 1.0f;
		if (ClanBomberApplication::is_server() || !ClanBomberApplication::is_client()) {
		  //CL_Iterator<GameObject> object_counter(objects);
		  for(std::list<GameObject*>::iterator object_iter = objects.begin();
		      object_iter != objects.end();
		      object_iter++) {
		    if ((*object_iter)->get_type() == GameObject::EXTRA) {
		      (*object_iter)->fly_to(app->map->get_passable());
		    }
		  }	
		}
	}
}

void MapTile::destroy()
{
	if (ClanBomberApplication::is_server() || !ClanBomberApplication::is_client()) {
	  //CL_Iterator<GameObject> object_counter(objects);
	  for(std::list<GameObject*>::iterator object_iter = objects.begin();
	      object_iter != objects.end();
	      object_iter++) {
	    if ((*object_iter)->get_type() == GameObject::EXTRA) {
	      static_cast<Extra*>(*object_iter)->destroy();
	    }
	  }
	}
}

void MapTile::act()
{
	if (vanishing) {
		vanish_countdown -= Timer::time_elapsed();
		if (vanish_countdown <= 0) {
			if (ClanBomberApplication::is_server() || !ClanBomberApplication::is_client()) {
				delete_me = true;
			}
		}
	}

	if (destroyed) {
		destroy_countdown -= Timer::time_elapsed();
		if (destroy_countdown <= 0) {
			if (ClanBomberApplication::is_server() || !ClanBomberApplication::is_client()) {
				delete_me = true;
			}
		}
	}
}

void MapTile::set_sprite_nr( int sprite )
{
	sprite_nr = sprite;
}

int MapTile::get_sprite_nr()
{
	return sprite_nr;
}

bool MapTile::has_extra()
{
  //CL_Iterator<GameObject> object_counter(objects);
  for(std::list<GameObject*>::iterator object_iter = objects.begin();
      object_iter != objects.end();
      object_iter++) {
    if ((*object_iter)->get_type() == GameObject::EXTRA) {
      return true;
    }
  }
  return false;
}

bool MapTile::has_bomber()
{
  //CL_Iterator<GameObject> object_counter(objects);
  for(std::list<GameObject*>::iterator object_iter = objects.begin();
      object_iter != objects.end();
      object_iter++) {
    if ((*object_iter)->get_type() == GameObject::BOMBER) {
      return true;
    }
  }
  return false;
}

void MapTile::spawn_extra()
{
	if (!ClanBomberApplication::is_server() && ClanBomberApplication::is_client()) {
		return;
	}
	switch (rand()%8) {
		case 0:
			if (GameConfig::get_power()) {
				new Extra_Power( x, y, app );
			}
			else {
				spawn_extra();
			}
			break;
		case 1:
			if (GameConfig::get_bombs()) {
				new Extra_Bomb( x, y, app );
			}
			else {
				spawn_extra();
			}
			break;
		case 2:
			if (GameConfig::get_skateboards()) {
				new Extra_Skateboard( x, y, app );
			}
			else {
				spawn_extra();
			}
			break;
		case 3:
			switch (rand()%2) {
				case 0:
					if (!GameConfig::get_start_kick() && GameConfig::get_kick()) {
						new Extra_Kick( x, y, app );
					}
					else {
						spawn_extra();
					}
					break;
				case 1:
					if (!GameConfig::get_start_glove() && GameConfig::get_glove()) {
						new Extra_Glove( x, y, app );
					}
					else {
						spawn_extra();
					}
					break;
			}
			break;
		case 4:
			switch (rand()%16) {
				case 0:
					if (GameConfig::get_joint()) {
						new Extra_Joint( x, y, app );
					}
					else {
						spawn_extra();
					}
					break;
				case 1:
					if (GameConfig::get_viagra()) {
						new Extra_Viagra( x, y, app );
					}
					else {
						spawn_extra();
					}
					break;
				case 2:
					if (GameConfig::get_koks()) {
						new Extra_Koks( x, y, app );
					}
					else {
						spawn_extra();
					}
					break;
			}
			break;
#ifdef ENABLE_EXPERIMENTAL_EXTRAS
        case 5:
        case 6:
          //TODO Check if it is enabled
          new Extra_Snail(x, y, app);
          break;
#endif
	}
}
