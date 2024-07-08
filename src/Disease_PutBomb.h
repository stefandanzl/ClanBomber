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

#ifndef DISEASE_PUTBOMB_H
#define DISEASE_PUTBOMB_H

#include "Disease.h"

/**
 * Makes a Bomber put a bomb always.
 * Causes a Bomber to always put a bomb while it can.
 * Given by "Viagra"
 * @author Andreas Hundt
 * @author Denis Oliver Kropp
 * @see Extra_Viagra
 */
class Disease_PutBomb : public Disease
{
public: 
	Disease_PutBomb(Bomber* _bomber);
	void start();
	void stop();
	~Disease_PutBomb();
	
	Disease* spawn(Bomber* _bomber);
	Extra* spawn_extra(int _x, int _y);

	DiseaseType get_DiseaseType()
  	{
         	return PUTBOMB; 
        }
};

#endif
