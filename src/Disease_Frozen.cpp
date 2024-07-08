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
#include "Disease_Frozen.h"
#include "Extra_Viagra.h"

#include "Bomber.h"
#include "Controller.h"

Disease_Frozen::Disease_Frozen(Bomber* _bomber) : Disease (_bomber)
{
	start();
}

Disease_Frozen::~Disease_Frozen()
{
}

void Disease_Frozen::start()
{
	countdown = 3.0f;
	bomber->controller->deactivate();
}

void Disease_Frozen::stop()
{
	bomber->controller->activate();
}

Disease* Disease_Frozen::spawn(Bomber* _bomber)
{
	return new Disease_Frozen(_bomber);
}

Extra* Disease_Frozen::spawn_extra( int _x, int _y)
{
	return new Extra_Viagra (_x,_y, bomber->app);
}
