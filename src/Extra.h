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

#ifndef Extra_h
#define Extra_h

#include "GameObject.h"

class ClanBomberApplication;
class Bomber;

/**
 * Base for all extras.
 * An extra is a GameObject that when touched by a Bomber modifies her variables
 * or gives her a disease.
 * @author Andreas Hundt
 * @author Denis Oliver Kropp
 */
class Extra : public GameObject
{
public:
	void destroy();
	Extra( int _x, int _y, ClanBomberApplication *_app );
	~Extra();

	void act();
	
	const char* get_name()
	{
	  return "Extra";
	}

	ObjectType get_type() const
	{
		return EXTRA;
	}
	
	typedef enum
	{
          SNAIL = -5,
          VIAGRA = -3,
          JOINT = -2,
          KOKS = -1,
          GLOVE = 1,
          KICK = 2,
          SKATEBOARD = 3,
          BOMB = 4,
          POWER = 5
	} ExtraType;

	static Extra* create( ExtraType type, int _x, int _y, ClanBomberApplication* _app );

	virtual ExtraType get_ExtraType() =0;

	bool is_destroyable() const;
		
protected:
	bool destroyable;
	bool destroyed;
	float destroy_countdown;
	virtual void effect( Bomber* bomber ) = 0;
};

#endif
