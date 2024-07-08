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
#include "Corpse_Part.h"

#include "Timer.h"

Corpse_Part::Corpse_Part(int _x, int _y, ClanBomberApplication* _app) : GameObject(_x, _y, _app)
{
	speed = 800;
	surface = Resources::Corpse_part();
	sprite_nr = rand()%4;
	z = Z_CORPSE_PART;
	countdown = 2.0f;
	can_fly_over_walls = false;
	app->objects.push_back(this);
}

Corpse_Part::~Corpse_Part()
{
}

void Corpse_Part::act()
{
	if (!flying) {
		countdown -= Timer::time_elapsed();
		if (countdown < 0) {
			countdown = 0;
			delete_me = true;
		}
		opacity = std::min( 255, (int)(255 * countdown) );
	}
	
	GameObject::act();
}
