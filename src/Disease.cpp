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

#include <stdlib.h>

#include "Disease.h"

#include "Timer.h"

#include "Disease_Frozen.h"
#include "Disease_PutBomb.h"
#include "Disease_Stoned.h"
#include "Disease_Fast.h"
#ifdef ENABLE_EXPERIMENTAL_EXTRAS
#  include "Disease_Slow.hpp"
#endif

Disease::Disease(Bomber* _bomber)
{
	bomber = _bomber;
	countdown = -1;
}


void Disease::act()
{
	if (countdown != -1) {
		countdown-= Timer::time_elapsed();
		if (countdown < 0) {
			stop();
			countdown =-1;
		}
	}		
}

float Disease::get_countdown() const
{
	return countdown;
}

Disease::~Disease()
{
}

Disease* Disease::create(DiseaseType type, Bomber* _bomber)
{
  switch (type) {
#ifdef ENABLE_EXPERIMENTAL_EXTRAS
  case SLOW:
    return new Disease_Slow(_bomber);
#endif
  case FROZEN:
    return new Disease_Frozen(_bomber);
  case PUTBOMB:
    return new Disease_PutBomb(_bomber);
  case STONED:
    return new Disease_Stoned(_bomber);
  case FAST:
    return new Disease_Fast(_bomber);
  }
  return NULL;
}
