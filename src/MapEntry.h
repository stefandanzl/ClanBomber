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

#ifndef MAPENTRY_H
#define MAPENTRY_H

#define MAP_WIDTH	17
#define MAP_HEIGHT	13

#include <string>

#include <boost/filesystem.hpp>

#include "UtilsCL_Vector.h"

class MapEntry
{
public:
  MapEntry(boost::filesystem::path _path, boost::filesystem::path _filename);
  MapEntry(std::string _name, bool write );
	~MapEntry();
	
	CL_Vector	get_bomber_pos(int nr);
	int			get_max_players();
	std::string	get_name();
	std::string	get_author();
	bool		is_enabled();
	bool		is_writable();
	bool		toggle();
	void		enable();
	void		disable();

	int	get_data(int x, int y);
	bool	is_random(int x, int y);
	void	set_data(int x, int y, char data);
	void	set_bomber_pos(int x, int y, int number);
	void	set_max_players(int nr);
	void	set_author(std::string _author);
	void	set_name(std::string _name);
	void	reset_filename(char* client_name);
	void	write_back();
	void 	clear();
	void	reload();
	void	read_bomber_positions();
	void	delete_file();
	void	randomize_bomber_positions();

	unsigned int get_name_checksum(const char* name);
	unsigned int get_data_checksum();
protected:
        boost::filesystem::path path;
	boost::filesystem::path filename;
        std::string	map_name;
	std::string	author;
	bool		enabled;
	bool		writable;
	int			max_players;
	CL_Vector	bomber_pos[8];
	char		map_data[MAP_WIDTH][MAP_HEIGHT];
};

#endif


