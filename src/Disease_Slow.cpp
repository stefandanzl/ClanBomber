/* This file is part of ClanBomber <http://www.nongnu.org/clanbomber>.
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

#include "Disease_Slow.hpp"

#include "Bomber.h"
#include "Extra_Snail.hpp"

Disease_Slow::Disease_Slow(Bomber* _bomber) : Disease(_bomber)
{
  start();
}

void Disease_Slow::start()
{
  countdown = 15.0f;
  speed = bomber->get_speed();
  bomber->set_speed(speed / 4);
}

void Disease_Slow::stop()
{
  bomber->set_speed(speed);
}

Extra* Disease_Slow::spawn_extra(int _x, int _y)
{
  return new Extra_Snail(_x, _y, bomber->app);
}

Disease* Disease_Slow::spawn(Bomber* _bomber)
{
  return new Disease_Slow(_bomber);
}
