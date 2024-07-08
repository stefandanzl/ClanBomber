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

#ifndef Bomber_Corpse_h
#define Bomber_Corpse_h

#include "GameObject.h"


class Bomber_Corpse : public GameObject
{
public:
	Bomber_Corpse (int _x, int _y, int _color, int _sprite_nr, ClanBomberApplication *_app );
	void act();
	~Bomber_Corpse();
	
	void explode();

	ObjectType get_type() const
	{
		return BOMBER_CORPSE;
	}
protected:
	int color;
	int splash_counter;
	bool ready_to_splash;
	
	float explode_delay;

private:
	void init();
};

#endif

