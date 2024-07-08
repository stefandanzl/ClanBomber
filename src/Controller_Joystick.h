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

#ifndef CONTROLLER_JOYSTICK_H
#define CONTROLLER_JOYSTICK_H

#include "Controller.h"

#include "SDL.h"

class Bomber;

class Controller_Joystick : public Controller
{
public:
  Controller_Joystick(int joystick_nr);
  ~Controller_Joystick();

  void update();
  void reset();
  bool is_left();
  bool is_right();
  bool is_up();
  bool is_down();
  bool is_bomb();

private:
  SDL_Joystick *joystick;

  bool bomb_button_down;

  bool left;
  bool right;
  bool up;
  bool down;
};

#endif
