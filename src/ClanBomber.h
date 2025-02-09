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

#ifndef CLANBOMBER_H
#define CLANBOMBER_H

#include <list>

#include <boost/filesystem.hpp>

#include "cbe/PluginManager.hpp"
#include "cbe/AudioSimple.hpp"
#include "cbe/Graphics.hpp"

//XXX Not needed here but in most files that include this one
#include "Resources.h"

class Menu;
class Observer;
class Map;
class Bomb;
class Bomber;
class GameObject;
class Server;
class Client;
class Mutex;
class Event;
class ClientSetup;
class ServerSetup;
class Chat;

enum
{
  MENU_GAME,
  MENU_OPTIONS,
  MENU_GRAPHICS,
  MENU_CREDITS,
  MENU_PLAYER_SETUP,
  MENU_EXTRA_VALUES,
  MENU_EXTRA_ONOFF,
  MENU_EXIT,
  MENU_CONTROLLER,
  MENU_HELP,
  MENU_DISEASE_ONOFF,
  MENU_MAP_EDITOR,
  MENU_TIMING,

  CONFIG_START_BOMBS,
  CONFIG_START_POWER,
  CONFIG_START_SKATES,
  CONFIG_START_KICK,
  CONFIG_START_GLOVE,

  CONFIG_BOMBS,
  CONFIG_POWER,
  CONFIG_SKATES,
  CONFIG_KICK,
  CONFIG_GLOVE,

  CONFIG_MAX_BOMBS,
  CONFIG_MAX_POWER,
  CONFIG_MAX_SKATES,

  CONFIG_POINTS,
  CONFIG_MAP_SEL,
  CONFIG_ROUND_TIME,

  CONFIG_JOINT,
  CONFIG_VIAGRA,
  CONFIG_KOKS,

  CONFIG_KIDS_MODE,
  CONFIG_SHAKE,
  CONFIG_CORPSE_PARTS,
  CONFIG_RANDOM_POSITIONS,
  CONFIG_RANDOM_MAP_ORDER,

  CONFIG_BOMB_COUNTDOWN,
  CONFIG_BOMB_DELAY,
  CONFIG_BOMB_SPEED,

  CONFIG_RANDOM_POSITIONS_DUPLICATE,
  CONFIG_RANDOM_MAP_ORDER_DUPLICATE,
  CONFIG_POINTS_DUPLICATE,
  CONFIG_ROUND_TIME_DUPLICATE,

  LOCALGAME_START,
  SERVERGAME_START,
  CLIENTGAME_START
};

enum Direction
{
  DIR_NONE  = -1,
  DIR_DOWN  = 0,
  DIR_LEFT  = 1,
  DIR_UP    = 2,
  DIR_RIGHT = 3
};

/**
 * @author Andreas Hundt
 * @author Denis Oliver Kropp
 */
class ClanBomberApplication
{
 public:
  ClanBomberApplication();
  ~ClanBomberApplication();
  int main();
  Map* map;
  std::list<GameObject*> objects;
  std::list<Bomber*> bomber_objects;

  bool init_server_game();
  bool init_client_game();
  int get_server_status();
  static int run_server_with_players();
  /**
   * Check if the this process is a server.
   * Returns true for server.
   * @return true for server, false otherwise.
   */
  static bool is_server();
  /**
   * Check if the this process is a client.
   * Returns true for both server and client. False if is a local game.
   * @return true for both server and client, false for local game.
   */
  static bool is_client();

  static Server* get_server();
  static Client* get_client();
  static ServerSetup* get_server_setup();
  static ClientSetup* get_client_setup();
  static Chat* get_chat();
  static Menu* get_menu();

  void set_client_disconnected_from_server(bool d);
  bool is_client_disconnected_from_server();
  void set_client_connecting_to_new_server(bool c);
  bool is_client_connecting_to_new_server();
  void client_to_server();
  void make_observer();
  void make_map();
  Observer* get_observer();
  Map* get_map();
  bool paused_game();
  void set_pause_game(bool paused);
  void reload_map();
  void delete_all_game_objects();

  GameObject* get_object_by_id(int object_id);
  Bomb* activate_suspended_client_bomb_by_id(int object_id);

  static unsigned short get_next_object_id();

  static boost::filesystem::path get_map_path();
  static boost::filesystem::path get_local_map_path();
  static void lock();
  static void unlock();
  static void wait();
  static void signal();

  bool bombers_received_by_client;
  static int get_server_frame_counter();
  static void inc_server_frame_counter();
  std::list<Bomb*> suspended_client_bombs;

  cbe::AudioSimple *get_audio() {return AS;};
  cbe::Graphics *get_graphics() {return G;};
 protected:
  int init_SDL();
  void init_audio();
  bool init_game(); // single player init
  void deinit_game();
  void show_tutorial();

  void run_game();
  void show_all();
  void act_all();
  void delete_some();

  void start_net_game();
  void init_net_game();

  Server* cb_server;
  Client* cb_client;
  ClientSetup* client_setup_menu;
  ServerSetup* server_setup_menu;
  Chat* chat;
  Menu* menu;

  Observer* observer;

  static boost::filesystem::path map_path;
  static boost::filesystem::path local_map_path;

  bool key_F1;
  bool show_fps;
  int fps;
  int frame_count;
  float frame_time;
  int server_status;
  static int server_frame_counter;
  bool pause_game;
  bool client_disconnected_from_server;
  bool client_connecting_to_new_server;
  Mutex* cb_mutex;
  Event* cb_event;
 private:
  cbe::PluginManager *PM;
  cbe::AudioSimple *AS;
  cbe::Graphics *G;
};

#endif

#ifdef WITH_DEBUG
# include <iostream>
# define dout(dstring) std::cout << std::endl << "__ " << __FILE__ << ":" << __LINE__ << " __" << std::endl << dstring << std::endl
#else
# ifdef WITH_DEBUG_SIMPLE
#  include <iostream>
#  define dout(dstring) std::cout << dstring << std::endl
# else
#  define dout(dstring)
# endif
#endif
