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

#ifndef Menu_h
#define Menu_h

#include "Client.h"

#include "vector"

class MenuItem
{
friend class Menu;
public:
	MenuItem( const std::string _text, int _id, int _parent );
	virtual ~MenuItem() {};

	void add_child( MenuItem* child );
	bool has_children();
	int get_id() const;
	int get_parent() const;
	std::string get_text();
	void set_text( const std::string _text );

	typedef enum
	{
		MT_NORMAL,
		MT_VALUE,
		MT_STRING,
		MT_STRINGLIST
	 } MENUTYPE;

	virtual MENUTYPE get_type() { return MT_NORMAL; };

protected:
	std::string		text;
	int			id;
	int			parent;
	std::vector<MenuItem*>	children;
};

class MenuItem_Value : public MenuItem
{
friend class Menu;
public:
	MenuItem_Value( const std::string _text, int _id, int _parent, int _min, int _max, int _value );
	virtual ~MenuItem_Value() {};

	int get_value();
	void set_value(int _value);
	int get_min();
	int get_max();
	void set_min( int _min );
	void set_max( int _max );
	void inc_value();
	void dec_value();

	virtual MENUTYPE get_type() { return MT_VALUE; };

protected:
	void test_value();
	int value;
	int min;
	int max;
};


class MenuItem_StringList : public MenuItem
{
friend class Menu;
public:
 MenuItem_StringList( const std::string _text, int _id, int _parent, std::vector<std::string*> _string_list, int _value );
	virtual ~MenuItem_StringList() {};

        std::string *get_sel_string();
	std::vector<std::string*> get_strings();
	void set_strings(std::vector<std::string*> _string_list);
	void inc_value();
	void dec_value();
	int get_value();
	void set_value(int _value);

	virtual MENUTYPE get_type() { return MT_STRINGLIST; };

protected:
	std::vector<std::string*> string_list;
	void test_value();
	int value;
	int min;
	int max;
};

class Menu
{
public:
	Menu( const std::string& name, ClanBomberApplication* _app );
	~Menu();

	void add_item( const std::string& text, int id, int parent=-1 );
	void add_value( const std::string& text, int id, int parent, int min, int max, int value );
	void add_string( const std::string& text, int id, int parent, std::string string );
	void add_stringlist( const std::string& text, int id, int parent, std::vector<std::string*> string_list, int cur_string );

	void redraw(bool options_menu_hack, int yoffset=0);
	int execute(bool options_menu_hack);

	void scroll_in();
	void scroll_out();
	MenuItem* get_item_by_id( int id );

	void go_to_game_menu(bool server);
	void execute_options_menu_hack();
	void backup_options_values();
	void restore_options_values();
	void save_common_options(int id, bool options_menu_hack, bool force_save);
	void set_left_netgame_setup();
protected:
	ClanBomberApplication* app;
	std::vector<MenuItem*> items;
	int current_run_id;
	int current_selection;

	MenuItem_Value* options_values[MENU_OPTIONS_NUMBER];
	bool left_netgame_setup;
};

#endif
