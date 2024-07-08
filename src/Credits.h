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

#ifndef CREDITS_H
#define CREDITS_H

#include <boost/ptr_container/ptr_list.hpp>

/**
  *@author Andreas Hundt, Denis Oliver Kropp
  */
class Credits
{
public: 
	Credits( ClanBomberApplication *app );
	~Credits();
	
	void exec();
	
protected:
	ClanBomberApplication	*app;
	void draw();
	void draw_objects();
	
	boost::ptr_list<std::string> text;
	float yoffset;
	int   speed;
	bool  stopped;
 private:
	static constexpr float yoffset_start = 50.0f;
	static const int normal_speed = 40;
	static const int text_height = 40;
	
	int yoffset_end;
};

#endif
