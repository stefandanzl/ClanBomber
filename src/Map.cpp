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

#include <stdio.h>
#include <string.h>
#include <sstream>
#include <stdexcept>
#include <iostream>

#include "ClanBomber.h"
#include "Map.h"

#include "MapTile.h"
#include "MapTile_Arrow.h"
#include "MapTile_Trap.h"
#include "MapTile_Wall.h"
#include "MapEntry.h"
#include "GameConfig.h"
#include "Bomb.h"
#include "Bomber.h"
#include "Server.h"

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

#include "Utils.h"
#include "UtilsGetHome.h"

std::vector<MapEntry*> Map::map_list;

Map::Map( ClanBomberApplication* _app )
  : current_server_map_name("receiving map...")
{
	app = _app;
	dummy_maptile = new MapTile_Wall(1000,1000,app);

	for (int y=0; y<MAP_HEIGHT; y++) {
		for (int x=0; x<MAP_WIDTH; x++) {
			maptiles[x][y] = NULL;
		}
	}
	current_map = NULL;
	enum_maps();
	sort_maps();
	load_selection();
	is_received_by_client = false;
	maps = 0;
	is_shaken = 0;
}

Map::~Map()
{

}

void Map::sort_maps()
{
	MapEntry **mapss = new MapEntry*[map_list.size()];
	int num = map_list.size();

	for (int i=0; i<num; i++) {
		mapss[i] = map_list[i];
	}

	bool found = true;
	while (found) {
		found = false;
		for (int i=0; i<num-1; i++) {
		  if (strcasecmp(mapss[i]->get_name().c_str(), mapss[i+1]->get_name().c_str()) > 0) {
				MapEntry *temp = mapss[i];
				mapss[i] = mapss[i+1];
				mapss[i+1] = temp;
				found = true;
			}
		}
	}

	map_list.clear();
	for (int i=0; i<num; i++) {
		map_list.push_back( mapss[i] );
	}

	delete[] mapss;
}

void Map::enum_maps()
{
  if (map_list.size()) {
    return;
  }

  boost::filesystem::directory_iterator end_iter;

  boost::filesystem::path path(app->get_map_path());
  if (boost::filesystem::exists(path)) {
    for (boost::filesystem::directory_iterator dir_iter(path);
         dir_iter != end_iter; dir_iter++) {
      if (dir_iter->path().extension() == ".map") {
        map_list.push_back(new MapEntry(path, dir_iter->path().filename()));
      }
    }
  }

  path = app->get_local_map_path();
  if (boost::filesystem::exists(path)) {
    for (boost::filesystem::directory_iterator dir_iter(path);
         dir_iter != end_iter; dir_iter++) {
      if (dir_iter->path().extension() == ".map") {
        map_list.push_back(new MapEntry(path, dir_iter->path().filename()));
      }
    }
  }
}

bool Map::any_valid_map()
{
	for (int i=0; i<get_map_count(); i++) {
		if (GameConfig::get_number_of_players() <= map_list[i]->get_max_players()  && map_list[i]->is_enabled()) {
			return true;
		}
	}
	return false;
}

int Map::get_map_count()
{
  return map_list.size();
}

void Map::spin_up()
{
  maps++;
  if(maps == map_list.size()) {
    maps = 0;
  }
  current_map = map_list[maps];
}

void Map::spin_down()
{
  maps--;
  if(maps < 0) {
    maps = map_list.size() - 1;
  }
  current_map = map_list[maps];
}

void Map::spin_to(int nr)
{
  maps = nr;
  current_map = map_list[maps];
}


void Map::load_random_valid()
{
	do {
		spin_to(rand()%get_map_count());
	} while (GameConfig::get_number_of_players() > get_max_players()  || !current_map->is_enabled());
	reload();
}


void Map::load_next_valid(int map_nr)
{
	if (map_nr != -1) {
		spin_to(map_nr);
	}
	else {
		spin_up();
	}
	
	//XXX This might loop forever if no map is usable
	while (GameConfig::get_number_of_players() > get_max_players()  || !current_map->is_enabled()) {
		spin_up();
	}
	
	reload();
}


void Map::load_previous_valid(int map_nr)
{
	if (map_nr != -1) {
		spin_to(map_nr);
	}
	else {
		spin_down();
	}
	
	//XXX Same as with load_next_valid
	while (GameConfig::get_number_of_players() > get_max_players()  || !current_map->is_enabled()) {
		spin_down();
	}
	
	reload();
}

void Map::load( int map_nr )
{
	spin_to(map_nr);
	reload();
}

void Map::reload()
{
	current_map->read_bomber_positions(); // needed by MapEditor
	clear();
	
	for (int y=0; y<MAP_HEIGHT; y++) {
		for (int x=0; x<MAP_WIDTH; x++) {
			switch (current_map->get_data(x,y)) {
				case 48:
				case 49:
				case 50:
				case 51:
				case 52:
				case 53:
				case 54:
				case 55:
				case ' ':
					maptiles[x][y] = MapTile::create(MapTile::GROUND, 40*x, 40*y, app);
					break;
				case '*':
					maptiles[x][y] = MapTile::create(MapTile::WALL, 40*x, 40*y, app);
					break;
				case '+':
					maptiles[x][y] = MapTile::create(MapTile::BOX, 40*x, 40*y, app);
					break;
				case 'R':
					if ( rand() %3) {
						maptiles[x][y] = MapTile::create(MapTile::BOX, 40*x, 40*y, app);
					}
					else {
						maptiles[x][y] = MapTile::create(MapTile::GROUND, 40*x, 40*y, app);
					}					
					break;
				case 'S':
					maptiles[x][y] = MapTile::create( MapTile::ICE, 40*x, 40*y, app);
					break;
				case '<':
					maptiles[x][y] = new MapTile_Arrow(40*x, 40*y, DIR_LEFT,app);
					break;
				case '>':
					maptiles[x][y] = new MapTile_Arrow(40*x, 40*y, DIR_RIGHT,app);
					break;
				case '^':
					maptiles[x][y] = new MapTile_Arrow( 40*x, 40*y, DIR_UP,app);
					break;
				case 'v':
					maptiles[x][y] = new MapTile_Arrow( 40*x, 40*y, DIR_DOWN,app);
					break;
				case 'o':
					maptiles[x][y] = new MapTile_Trap( 40*x, 40*y, app);
					break;
				default:
					maptiles[x][y] = MapTile::create(MapTile::NONE, 40*x, 40*y, app);
					break;
			}
		}
	}
}

void Map::show()
{
  for (int y=0; y<MAP_HEIGHT; y++) {
    for (int x=0; x<MAP_WIDTH; x++) {
      MapTile *maptile = maptiles[x][y];

      if (!maptile) {
        continue;
      }

      if (maptile->get_type() == MapTile::NONE) {
        continue;
      }

      if (maptile->vanishing) {
        maptile->draw();
        continue;
      }


      int X = 60 + 40*x;
      int Y = 40 + 40*y;

      if (is_shaken > 0) {
        X += rand()%5 - 2;
        Y += rand()%5 - 2;
      }

      Resources::Game_maptiles()->blit(X, Y, maptile->sprite_nr);

      if (maptile->get_addon_sprite_nr() >= 0) {
        Resources::Game_maptile_addons()->blit(X, Y,
                                               maptile->get_addon_sprite_nr());
      }

      if (GameConfig::get_highlight_maptiles()) {
        for(std::list<GameObject*>::iterator object_iter
              = maptile->objects.begin();
            object_iter != maptile->objects.end();
            object_iter++) {
          if ((*object_iter)->get_type() == GameObject::BOMBER) {
            if (GameConfig::bomber[static_cast<Bomber*>(*object_iter)->get_number()]
                .get_highlight_maptile()) {
              CB_FillRect(X, Y, 40, 40, 0x00, 0x00, 0xff, 50);
            }
          }
        }
      }
    }
  }

  if (is_shaken > 0) {
    is_shaken--;
  }
}

void Map::show_random_boxes()
{
  for (int y=0; y<MAP_HEIGHT; y++) {
    for (int x=0; x<MAP_WIDTH; x++) {
      if (current_map->get_data(x,y) == 'R') {
	Resources::Game_maptile_addons()->blit( 60+x*40, 40+y*40, 5 );
      }
    }
  }
}

void Map::show_start_positions()
{
  for (int i=0; i<current_map->get_max_players(); i++) {
    CL_Vector pos = current_map->get_bomber_pos(i);
    Resources::Game_maptile_addons()->blit( (int)(60 + pos.x*40), (int)(40+pos.y*40), 6 );
    
    std::ostringstream s;
    s << i + 1;
    std::string number = s.str();
    ///primary->SetFont( primary, Resources::Font_small() );
    ///primary->SetColor( primary, 0xFF, 0xFF, 0xFF, 0xFF );
    ///primary->DrawString( primary, number, -1, (int)(80 + pos.x*40), (int)(52 + pos.y*40), DSTF_TOPCENTER );
    Resources::Font_small()->render(number, 80 + pos.x*40, 52 + pos.y*40,
                                    cbe::FontAlignment_0topcenter);
  }
}

void Map::show_preview( int x, int y, float factor )
{
	int tile_size = (int)(40*factor);
	for (int yy=0; yy<MAP_HEIGHT; yy++) {
		for (int xx=0; xx<MAP_WIDTH; xx++) {
			if (maptiles[xx][yy]) {
				maptiles[xx][yy]->draw_tiny( x+xx*tile_size, y+yy*tile_size, factor );
			}
		}
	}
}

void Map::refresh_holes()
{
  int count = 0;

  for (int y=0; y<MAP_HEIGHT; y++) {
    for (int x=0; x<MAP_WIDTH; x++) {
      if (maptiles[x][y]) {
	if (maptiles[x][y]->get_type() == MapTile::NONE) {
          CB_FillRect(60+40*x, 40+40*y, 40, 40, 0, 0, 0);
	  if (is_shaken > 0) {
	    maptiles[x][y]->draw_shaken();
	  }
	  else {
	    maptiles[x][y]->draw();
	  }
	}
      }
    }
  }
}

void Map::maptilize_objects()
{
  for (int y=0; y<MAP_HEIGHT; y++) {
    for (int x=0; x<MAP_WIDTH; x++) {
      maptiles[x][y]->objects.clear();
      maptiles[x][y]->bomb = NULL;
    }
  }

  //CL_Iterator<Bomber> bomber_object_counter(app->bomber_objects);
  for(std::list<Bomber*>::iterator bomber_object_iter = app->bomber_objects.begin();
      bomber_object_iter != app->bomber_objects.end();
      bomber_object_iter++) {
    if (!(*bomber_object_iter)->is_flying() && !(*bomber_object_iter)->is_dead()) {
      (*bomber_object_iter)->get_maptile()->objects.push_back(*bomber_object_iter);
    }
  }

  //CL_Iterator<GameObject> object_counter(app->objects);
  for(std::list<GameObject*>::iterator object_iter = app->objects.begin();
      object_iter != app->objects.end();
      object_iter++) {
    if (!(*object_iter)->is_flying()) {
      if((*object_iter)->get_maptile() != NULL) {
	(*object_iter)->get_maptile()->objects.push_back((*object_iter));
	if ((*object_iter)->get_type() == GameObject::BOMB && !((*object_iter)->is_falling())) {
	  (*object_iter)->get_maptile()->bomb = static_cast<Bomb*>(*object_iter);
	}
      }
    }
  }
}

void Map::act()
{
  maptilize_objects();
  
  for (int y=0; y<MAP_HEIGHT; y++) {
    for (int x=0; x<MAP_WIDTH; x++) {
      maptiles[x][y]->act();
      if (ClanBomberApplication::is_server() || !ClanBomberApplication::is_client()) {
	if (maptiles[x][y]->delete_me) {
	  MapTile* new_tile;
	  new_tile = MapTile::spawn( maptiles[x][y] );
	  delete maptiles[x][y];
	  maptiles[x][y] = new_tile;
	  if (ClanBomberApplication::is_server()) {
	    Direction dir_tmp = DIR_NONE;
	    if (new_tile->get_type() == MapTile::ARROW) {
	      dir_tmp = ((MapTile_Arrow*)new_tile)->get_direction();
	    }
	    ClanBomberApplication::get_server()->send_SERVER_MAPTILE_REFRESH(x, y, new_tile->get_type(), dir_tmp);
	  }
	}
      }
    }
  }
}	


void Map::shake( int _shake )
{
	is_shaken = GameConfig::get_shaky_explosions()?_shake:0;
}


void Map::clear()
{
	for (int y=0; y<MAP_HEIGHT; y++) {
		for (int x=0; x<MAP_WIDTH; x++) {
			if (maptiles[x][y]) {
				delete maptiles[x][y];
				maptiles[x][y] = NULL;
			}
		}
	}
	is_shaken = 0;
}

bool Map::add_bomb(int bx, int by, int bpower, Bomber *bomber, int bomber_x, int bomber_y)
{
	if ((bx<0) || (by<0) || (bx>=MAP_WIDTH) || (by>=MAP_HEIGHT)) {
		return false;
	}
	if (maptiles[bx][by] == NULL) {
		return false;
	}
	if (maptiles[bx][by]->bomb == NULL) {
		maptiles[bx][by]->bomb = new Bomb( bx*40, by*40, bpower, bomber, app );
		if (ClanBomberApplication::is_server()) {
			app->get_server()->send_SERVER_ADD_BOMB(bomber_x, bomber_y, bx, by, bpower, bomber->get_object_id(), maptiles[bx][by]->bomb->get_object_id());
		}
		return true;
	}
	return false;
}

std::string Map::get_name()
{	
	return current_map->get_name();
}

std::string Map::get_author()
{
	return current_map->get_author();
}

CL_Vector Map::get_bomber_pos(int nr)
{
	return current_map->get_bomber_pos(nr);
}

void Map::randomize_bomber_positions()
{
	current_map->randomize_bomber_positions();
}

int Map::get_max_players()
{
	return current_map->get_max_players();
}


MapTile* Map::get_passable()
{
	int i =0;
	int xmapfield;
	int ymapfield;
	do {
		xmapfield = rand() % 17;
		ymapfield = rand() % 13;
		if (maptiles[xmapfield][ymapfield]->is_passable() && !maptiles[xmapfield][ymapfield]->is_vanishing()) {
			return maptiles[xmapfield][ymapfield];				
		}
		i++;
	} while (i<1000);
	return NULL;
}

MapTile* Map::get_random()
{
	int i =0;
	int xmapfield;
	int ymapfield;
	do {
		xmapfield = rand() % 17;
		ymapfield = rand() % 13;
		if (maptiles[xmapfield][ymapfield]->get_type()!=MapTile::NONE && !maptiles[xmapfield][ymapfield]->is_vanishing()) {
			return maptiles[xmapfield][ymapfield];				
		}
		i++;
	} while (i<1000);
	return NULL;
}

void Map::set_maptile(int x, int y, MapTile* mt)
{
    if(maptiles[x][y]) {
        delete maptiles[x][y];
    }
    maptiles[x][y]=mt;
}

MapTile* Map::get_maptile(int x, int y)
{
  if (x < 0 || x > MAP_WIDTH-1 || y < 0 || y > MAP_HEIGHT-1) {
    return dummy_maptile;
  }
  else {
    return maptiles[x][y];
  }
}

MapTile* Map::get_maptile_xy(int x, int y)
{
	if (x < 0 || x >= (MAP_WIDTH)*40  || y < 0 || y >= (MAP_HEIGHT)*40 ) {
		return dummy_maptile;
	}
	else {
		return maptiles[x/40][y/40];
	}
}


int Map::new_entry( std::string _name )
{
	map_list.push_back( new MapEntry(_name , true) );
	return map_list.size() -1;
}

int Map::delete_entry( int nr )
{	
	map_list[nr]->delete_file();
	delete map_list[nr];
	map_list.erase(map_list.begin() + nr);
	
	if (nr > get_map_count()-1) {
		return nr-1;
	}
	return nr;
}

std::ostream& operator<<(std::ostream& os, const Map& m)
{
	for (int y=0; y<MAP_HEIGHT; y++) {
		for (int x=0; x<MAP_WIDTH; x++) {
			if (m.maptiles[x][y]->bomb) {
				os << "*";
			}
			else if (m.maptiles[x][y]->has_bomber()) {
				os << "B";
			}
			else if (m.maptiles[x][y]->has_extra()) {
				os << "e";
			}
			else {
				switch (m.maptiles[x][y]->get_type()) {
					case MapTile::NONE:
						os << "-";
						break;
					case MapTile::GROUND:
						os << " ";
						break;
					case MapTile::WALL:
						os << "#";
						break;
					case MapTile::BOX:
						os << "+";
						break;
					case MapTile::TRAP:
						os << " ";
						break;
					case MapTile::ARROW:
						os << " ";
						break;
					case MapTile::ICE:
						os << " ";
						break;
				}
			}
			os << " ";
		}
		os << std::endl;
	}
	return os;
}


void Map::save_selection()
{
  boost::filesystem::path filename(GetConfigHome() / "clanbomber/maps.disabled");

  boost::filesystem::ofstream map_selection_file(filename);
	//CL_Iterator<MapEntry> map_entry_iterator(map_list);
	for(std::vector<MapEntry*>::iterator map_entry_iter = map_list.begin();
	    map_entry_iter != map_list.end();
	    map_entry_iter++) {
	  if (!(*map_entry_iter)->is_enabled()) {
	    map_selection_file << (*map_entry_iter)->get_name() << std::endl;
	  }
	}
}

void Map::load_selection()
{
  boost::filesystem::path filename(GetConfigHome() / "clanbomber/maps.disabled");

  char map_name[100];

  boost::filesystem::ifstream map_selection_file(filename);
  if(!map_selection_file.fail()) {
    while (!map_selection_file.eof()) {
      map_selection_file.getline(map_name, 100);
      //CL_Iterator<MapEntry> map_entry_iterator(map_list);
      for(std::vector<MapEntry*>::iterator map_entry_iter = map_list.begin();
          map_entry_iter != map_list.end();
          map_entry_iter++) {
        if ((*map_entry_iter)->get_name() == map_name) {
          (*map_entry_iter)->disable();
        }
      }
    }
  }
}

bool Map::is_dummy_maptile(MapTile* mt)
{
	return (dummy_maptile == mt);
}

unsigned int Map::get_current_map_name_checksum()
{
    return current_map->get_name_checksum(NULL);
}

unsigned int Map::get_current_map_data_checksum()
{
	return current_map->get_data_checksum();
}

int Map::get_map_name_checksums(unsigned int** chesksum_array)
{
    int num = map_list.size();
    unsigned int* csa = new unsigned int[num];
    for (int i=0; i<num; i++) {
        csa[i] = map_list[i]->get_name_checksum(NULL);
    }
    (*chesksum_array) = csa;
    return num;
}

int Map::get_map_data_checksums(unsigned int** chesksum_array)
{
	int num = map_list.size();
	unsigned int* csa = new unsigned int[num];
	for (int i=0; i<num; i++) {
		csa[i] = map_list[i]->get_data_checksum();
	}
	(*chesksum_array) = csa;
	return num;
}

void Map::load_by_data_checksum( unsigned int checksum )
{
    int map_nr = 0;
    int num = map_list.size();
    for (int i=0; i<num; i++) {
        if (map_list[i]->get_data_checksum() == checksum) {
            map_nr = i;
            break;
        }
    }
    spin_to(map_nr);
    reload();
}

MapEntry* Map::get_current_map()
{
	return current_map;
}
