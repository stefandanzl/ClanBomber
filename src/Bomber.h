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

#ifndef Bomber_h
#define Bomber_h

#include "GameObject.h"
#include "Server.h"

class Disease;
class Controller;

class Bomber : public GameObject
{
public:
	typedef enum
	{
		RED		= 0,
		BLUE	= 1,
		YELLOW	= 2,
		GREEN	= 3,
		RED2	= 4,
		BLUE2	= 5,
		YELLOW2	= 6,
		GREEN2	= 7,
	} COLOR;

	Bomber( int _x, int _y, COLOR _color, Controller* _controller, std::string _name, int _team, int _number, ClanBomberApplication *_app);
	~Bomber();
	
	void dec_points();
	void inc_points();
	void set_points( int _points );
	int get_points() const;
	bool is_dead() const;
	void inc_kills();
	void set_dead();
	void set_sprite_nr(int snr);
	int get_deaths() const;
	int get_kills() const;
	
	int get_cur_bombs() const;
	int get_power() const;
	int get_bombs() const;

	int get_skateboards() const;
	void set_skateboards(int nr_skates);

	int get_number() const;
	int get_team() const;
	void set_team( int _team);

	COLOR get_color() const;

	void gain_extra_bomb();
	void gain_extra_skateboard();
	void gain_extra_kick();
	void gain_extra_glove();
	void gain_extra_power();
	void loose_all_extras();
	void delete_disease();
	void loose_disease();

	Disease* get_disease() const;
	void set_disease(Disease* _disease, bool play_sound);
	void infect (Disease* _disease);
	void infect_others();
	
	void inc_cur_bombs();
	void dec_cur_bombs();

	void put_bomb();
	void put_bomb(int mapx, int mapy);
	bool die();
	void show() const;
	bool allow_putbomb();
	void act_net();
	void act();
	void reset();

	std::string get_name() const;
	
	ObjectType get_type() const;
	
	Controller* controller;
	
	bool is_diseased();
	bool is_able_to_throw() const
	{
		return can_throw;
	}
	
	bool direction_has_changed(bool for_server);
	int get_gloves() const;
	int get_extra_gloves() const;
	int get_extra_skateboards() const;
	int get_extra_power() const;
	int get_extra_kick() const;
	int get_extra_bombs() const;
	void set_deaths(int d);
	void set_kills(int k);
	void set_cur_bombs(int cb);
	void set_bombs(int b);
	void set_extra_bombs(int eb);
	void set_power(int p);
	void set_extra_power(int ep);
	void set_extra_skateboards(int es);
	void set_is_able_to_kick(bool k);
	void set_extra_kick(int ek);
	void set_is_able_to_throw(bool t);
	void set_gloves(int g);
	void set_extra_gloves(int eg);
	Direction get_server_send_dir() const;
	void set_anim_count(float animcnt);
	void set_disconnected();
	bool is_disconnected() const;
protected:
	COLOR color;
	std::string name;
	int deaths;
	int kills;
	bool dead;
	float anim_count;
	int points;
	bool can_throw;
	Disease*  disease;
	
	int skateboards;
	int cur_bombs;
	int bombs;
	int power;
	int gloves;

	int extra_gloves;
	int extra_skateboards;
	int extra_power;
	int extra_kick;
	int extra_bombs;
	
	bool bomb_key;
	
	int team;
	int number;
	Direction server_send_dir;
	SimpleTimer allow_putbomb_timer;
	bool has_disconnected;
};

#endif
