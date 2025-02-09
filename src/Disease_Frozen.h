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

#ifndef DIESEASE_FROZEN_H
#define DIESEASE_FROZEN_H

#include "Disease.h"


/**
 * Paralyzes a Bomber.
 * If applyed to a Bomber paralyzes it (it's unable to move).
 * This is not used by the game.
 * @author Andreas Hundt
 * @author Denis Oliver Kropp
 */
class Disease_Frozen : public Disease
{
public: 
  Disease_Frozen(Bomber* bomber);
  void start();
  void stop();
  ~Disease_Frozen();
  
  Disease* spawn(Bomber* _bomber);
  Extra* spawn_extra(int _x, int _y);
  
  DiseaseType get_DiseaseType()
  {
    return FROZEN;
  }
};

#endif
