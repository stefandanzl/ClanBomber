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

#ifndef OBSERVER_H
#define OBSERVER_H

#include "GameObject.h"
#include "GameStatus.h"
#include "Bomber.h"

class ClanBomberApplication;


class Observer : public GameObject
{
public: 
	Observer( int _x, int _y, ClanBomberApplication *_app );
	~Observer();
	
	virtual void show();
	virtual void act();
	virtual void fall() {}; // does not fall ;-)
	
	bool end_of_game_requested();
	int active_players();
	float get_round_time() const;
	void reset_round_time();
	void make_client_game_status();
	GameStatus* get_game_status();
	
	ObjectType get_type() const
	{
		return OBSERVER;
	}
	
	typedef enum
	{
		NORMAL,
		TEAM
	} Mode;

	void set_client_game_runs(bool is_running);
	bool client_game_is_running();

protected:
	bool		end_of_game;
	float		round_time;
	Mode		mode;
	GameStatus	*game_status;
	bool		play_hurryup;
	bool		first_destruction;
	int		repaint_hack;
	void kill_all_bombers();

	bool client_game_runs;
};

#endif


