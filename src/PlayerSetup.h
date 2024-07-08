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

#ifndef PLAYERSETUP_H
#define PLAYERSETUP_H


/**
  *@author Andreas Hundt, Denis Oliver Kropp
  */

class ClanBomberApplication;

class PlayerSetup
{
public: 
	PlayerSetup(ClanBomberApplication* _app);
	~PlayerSetup();

	void exec();
	
protected:
	ClanBomberApplication*	app;
	
	int	cur_row, cur_col;
	
	void draw(bool fick=false);
	void enter_name();
	void handle_enter();
};

#endif










