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
#include "Controller_Joystick.h"

#include "SDL.h"

Controller_Joystick::Controller_Joystick(int joystick_nr) : Controller()
{
  joystick = SDL_JoystickOpen(joystick_nr);
}

Controller_Joystick::~Controller_Joystick()
{
  SDL_JoystickClose(joystick);
}

void Controller_Joystick::update()
{
  const unsigned int tolerance = 10000;
  if (active && joystick != NULL) {
    right = false;
    left = false;
    up = false;
    down = false;

    Sint16 x = SDL_JoystickGetAxis(joystick, 0);
    Sint16 y = SDL_JoystickGetAxis(joystick, 1);

    //X Axis
    if (abs(x) > tolerance) {
      if (x > 0) {
        right = true;
      } else {
        left = true;
      }
    }

    //Y Axis, negatives are up positives are down
    if (abs(y) > tolerance) {
      if (y > 0) {
        down = true;
      } else {
        up = true;
      }
    }

    Uint8 hat = SDL_JoystickGetHat(joystick, 0);
    switch(hat) {
    case SDL_HAT_CENTERED:
      break;
    case SDL_HAT_UP:
      up = true;
      break;
    case SDL_HAT_RIGHT:
      right = true;
      break;
    case SDL_HAT_DOWN:
      down = true;
      break;
    case SDL_HAT_LEFT:
      left = true;
      break;
    case SDL_HAT_RIGHTUP:
      right = true;
      up = true;
      break;
    case SDL_HAT_RIGHTDOWN:
      right = true;
      down = true;
      break;
    case SDL_HAT_LEFTUP:
      left = true;
      up = true;
      break;
    case SDL_HAT_LEFTDOWN:
      left = true;
      down = true;
      break;
    }

    //Reverse
    if (reverse) {
      bool r_right = left;
      left = right;
      right = r_right;

      bool r_down = up;
      up = down;
      down = r_down;
    }

    //Button
    if (SDL_JoystickGetButton(joystick, 0)) {
      if (bomb_button_down) {
        put_bomb = true;
      }
      else {
        put_bomb = false;
      }
      bomb_button_down = false;
    }
    else {
      put_bomb = false;
      bomb_button_down = true;
    }
  }
}

void Controller_Joystick::reset()
{
  right = false;
  left = false;
  down = false;
  up = false;

  put_bomb = false;
  bomb_button_down = false;

  reverse = false;
}

bool Controller_Joystick::is_left()
{
  return left;
}

bool Controller_Joystick::is_right()
{
  return right;
}

bool Controller_Joystick::is_up()
{
  return up;
}

bool Controller_Joystick::is_down()
{
  return down;
}

bool Controller_Joystick::is_bomb()
{
  switch (bomb_mode) {
  case NEVER:
    return false;
  case ALWAYS:
    return true;
  default:
    break;
  }
  return put_bomb && active;
}
