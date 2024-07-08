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
#include "Disease_Fast.h"
#include "Extra_Koks.h"

#include "Bomber.h"

Disease_Fast::Disease_Fast(Bomber* _bomber) : Disease (_bomber)
{
	start();
}

Disease_Fast::~Disease_Fast()
{
}

void Disease_Fast::start()
{
	countdown = 10.0f;
	bomber->inc_speed(600);
}

void Disease_Fast::stop()
{
	bomber->dec_speed(600);
}

Disease* Disease_Fast::spawn(Bomber* _bomber)
{
	return new Disease_Fast(_bomber);
}

Extra* Disease_Fast::spawn_extra( int _x, int _y)
{
	return new Extra_Koks (_x,_y, bomber->app);
}
