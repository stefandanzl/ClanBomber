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

#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include <config.h>

#include "SDL_image.h"
#include "SDL_rotozoom.h"

#include "Resources.h"
#include "cbe/Surface.hpp"
#include "cbe/Font.hpp"
#include "ClanBomber.h"

extern SDL_Surface *primary;
extern ClanBomberApplication *app;

#ifdef WORDS_BIGENDIAN
#define SWAP16(a) (((a)>>8) | ((a) << 8))
#define SWAP32(a) (((a) >> 24) | (((a) & 0x00ff0000) >>  8) | (((a) & 0x0000ff00) <<  8) | (((a) << 24)))
#endif

cbe::Font*		Resources::fnt_big = NULL;
cbe::Font*		Resources::fnt_small = NULL;

cbe::Surface*		Resources::sur_titlescreen = NULL;

cbe::Surface*		Resources::sur_fl_logo = NULL;
cbe::AudioBuffer*	Resources::sfx_typewriter = NULL;
cbe::AudioBuffer*	Resources::sfx_winlevel = NULL;

cbe::SurfaceMap*		Resources::sur_ps_teams = NULL;
cbe::SurfaceMap*		Resources::sur_ps_controls = NULL;
cbe::SurfaceMap*		Resources::sur_ps_teamlamps = NULL;
cbe::Surface*	Resources::sur_ps_background = NULL;

cbe::Surface*		Resources::sur_ls_background = NULL;
cbe::Surface*		Resources::sur_ls_not_available = NULL;

cbe::SurfaceMap*		Resources::sur_gs_tools = NULL;
cbe::AudioBuffer*	Resources::sfx_klatsch = NULL;
cbe::Surface*		Resources::sur_gs_background = NULL;

cbe::AudioBuffer*	Resources::sfx_forward = NULL;
cbe::AudioBuffer*	Resources::sfx_rewind = NULL;
cbe::AudioBuffer*	Resources::sfx_stop = NULL;

cbe::Surface*	Resources::sur_horst_evil = NULL;

cbe::SurfaceMap*	Resources::sur_bombers[NR_BOMBERSKINS] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };

cbe::SurfaceCollection*	Resources::sur_extras = NULL;
cbe::AudioBuffer*	Resources::sfx_wow = NULL;
cbe::AudioBuffer*	Resources::sfx_joint = NULL;
cbe::AudioBuffer*	Resources::sfx_horny = NULL;
cbe::AudioBuffer*	Resources::sfx_schnief = NULL;

cbe::AudioBuffer*	Resources::sfx_whoosh = NULL;
cbe::AudioBuffer*	Resources::sfx_break = NULL;
cbe::AudioBuffer*	Resources::sfx_clear = NULL;
cbe::AudioBuffer*	Resources::sfx_menu_back = NULL;

cbe::SurfaceMap*	Resources::sur_observer = NULL;
cbe::AudioBuffer*	Resources::sfx_hurry_up = NULL;
cbe::AudioBuffer*	Resources::sfx_time_over = NULL;
cbe::AudioBuffer*	Resources::sfx_crunch = NULL;

cbe::AudioBuffer*	Resources::sfx_die = NULL;
cbe::AudioBuffer*	Resources::sfx_explode = NULL;
cbe::AudioBuffer*	Resources::sfx_putbomb = NULL;
cbe::AudioBuffer*	Resources::sfx_deepfall = NULL;
cbe::SurfaceMap*	Resources::sur_maptiles = NULL;
cbe::SurfaceMap*	Resources::sur_maptile_addons = NULL;
cbe::SurfaceMap*	Resources::sur_bombs = NULL;
cbe::SurfaceMap*	Resources::sur_explosion = NULL;
cbe::Surface*	Resources::sur_cb_logo_small = NULL;

cbe::Surface*	Resources::sur_me_background = NULL;

cbe::AudioBuffer*	Resources::sfx_corpse_explode = NULL;
cbe::SurfaceMap*	Resources::sur_corpse_part = NULL;

cbe::AudioBuffer*	Resources::sfx_splash[2] = { NULL, NULL};


Resources::Resources()
{
}

Resources::~Resources()
{
}

void Resources::init()
{
}

cbe::Font* Resources::Font_big()
{
  if (!fnt_big) {
    fnt_big = app->get_graphics()->createFont(CB_DATADIR"/fonts/DejaVuSans-Bold.ttf", 28);
  }
  return fnt_big;
}

cbe::Font* Resources::Font_small()
{
  if (!fnt_small) {
    fnt_small = app->get_graphics()->createFont(CB_DATADIR"/fonts/DejaVuSans-Bold.ttf", 18);
  }
  return fnt_small;
}

cbe::Surface* Resources::Titlescreen()
{
  if (!sur_titlescreen) {
    sur_titlescreen = app->get_graphics()->createSurface(CB_DATADIR"/pics/clanbomber_title_andi.png");
  }
  return sur_titlescreen;
}

cbe::Surface* Resources::Intro_fl_logo()
{
  if (!sur_fl_logo) {
    sur_fl_logo = app->get_graphics()->createSurface(CB_DATADIR"/pics/fischlustig_logo.png");
  }
  return sur_fl_logo;
}

cbe::AudioBuffer* Resources::Intro_typewriter()
{
  if (!sfx_typewriter) {
    sfx_typewriter = app->get_audio()->createBuffer(CB_DATADIR"/wavs/typewriter.wav");
  }
  return sfx_typewriter;
}

cbe::AudioBuffer* Resources::Intro_winlevel()
{
	if (!sfx_winlevel) {
		sfx_winlevel = app->get_audio()->createBuffer(CB_DATADIR"/wavs/winlevel.wav");
		///if (sfx_winlevel == NULL)
		///exit(1);
	}
	return sfx_winlevel;
}

cbe::SurfaceMap* Resources::Playersetup_teams()
{
	if (!sur_ps_teams) {
		sur_ps_teams = app->get_graphics()->createSurfaceMap( CB_DATADIR"/pics/ps_teams.png", 125, 56);
	}
	return sur_ps_teams;
}

cbe::SurfaceMap* Resources::Playersetup_controls()
{
	if (!sur_ps_controls) {
		sur_ps_controls = app->get_graphics()->createSurfaceMap( CB_DATADIR"/pics/ps_controls.png", 125, 56);
	}
	return sur_ps_controls;
}

cbe::SurfaceMap* Resources::Playersetup_teamlamps()
{
	if (!sur_ps_teamlamps) {
		sur_ps_teamlamps = app->get_graphics()->createSurfaceMap( CB_DATADIR"/pics/ps_teamlamps.png", 30, 32);
	}
	return sur_ps_teamlamps;
}

cbe::Surface* Resources::Playersetup_background()
{
  if (!sur_ps_background) {
    sur_ps_background = app->get_graphics()->createSurface(CB_DATADIR"/pics/playersetup.png");
  }
  return sur_ps_background;
}

cbe::Surface* Resources::Mapselector_background()
{
  if (!sur_ls_background) {
    sur_ls_background = app->get_graphics()->createSurface(CB_DATADIR"/pics/level_selection.png");
  }
  return sur_ls_background;
}

cbe::Surface* Resources::Mapselector_not_available()
{
  if (!sur_ls_not_available) {
    sur_ls_not_available = app->get_graphics()->createSurface(CB_DATADIR"/pics/not_available.png");
  }
  return sur_ls_not_available;
}

cbe::SurfaceMap* Resources::Gamestatus_tools()
{
	if (!sur_gs_tools) {
		sur_gs_tools = app->get_graphics()->createSurfaceMap( CB_DATADIR"/pics/cup2.png", 40, 40);
	}
	return sur_gs_tools;
}

cbe::AudioBuffer* Resources::Gamestatus_klatsch()
{
	if (!sfx_klatsch) {
		sfx_klatsch = app->get_audio()->createBuffer( CB_DATADIR"/wavs/klatsch.wav");
	}
	return sfx_klatsch;
}

cbe::Surface* Resources::Gamestatus_background()
{
  if (!sur_gs_background) {
    sur_gs_background = app->get_graphics()->createSurface(CB_DATADIR"/pics/game_status.png");
  }
  return sur_gs_background;
}

cbe::AudioBuffer* Resources::Credits_forward()
{
	if (!sfx_forward) {
		sfx_forward = app->get_audio()->createBuffer( CB_DATADIR"/wavs/forward.wav");
	}
	return sfx_forward;
}

cbe::AudioBuffer* Resources::Credits_rewind()
{
	if (!sfx_rewind) {
		sfx_rewind = app->get_audio()->createBuffer( CB_DATADIR"/wavs/rewind.wav");
	}
	return sfx_rewind;
}

cbe::AudioBuffer* Resources::Credits_stop()
{
	if (!sfx_stop) {
		sfx_stop = app->get_audio()->createBuffer( CB_DATADIR"/wavs/stop.wav");
	}
	return sfx_stop;
}


cbe::Surface* Resources::Credits_horst_evil()
{
  if (!sur_horst_evil) {
    sur_horst_evil = app->get_graphics()->createSurface(CB_DATADIR"/pics/horst_evil.png");
  }
  return sur_horst_evil;
}

cbe::SurfaceMap* Resources::Bombers(int nr)
{
	if (nr >= NR_BOMBERSKINS || nr < 0) {
		return NULL;
	}
	if (!sur_bombers[nr]) {
		sur_bombers[0] = app->get_graphics()->createSurfaceMap( CB_DATADIR"/pics/bomber_snake.png", 40, 60);
		sur_bombers[1] = app->get_graphics()->createSurfaceMap( CB_DATADIR"/pics/bomber_tux.png", 40, 60);
		sur_bombers[2] = app->get_graphics()->createSurfaceMap( CB_DATADIR"/pics/bomber_spider.png", 40, 40);
		sur_bombers[3] = app->get_graphics()->createSurfaceMap( CB_DATADIR"/pics/bomber_bsd.png", 40, 60);
		sur_bombers[4] = app->get_graphics()->createSurfaceMap( CB_DATADIR"/pics/bomber_dull_red.png", 40, 40);
		sur_bombers[5] = app->get_graphics()->createSurfaceMap( CB_DATADIR"/pics/bomber_dull_blue.png", 40, 40);
		sur_bombers[6] = app->get_graphics()->createSurfaceMap( CB_DATADIR"/pics/bomber_dull_yellow.png", 40, 40);
		sur_bombers[7] = app->get_graphics()->createSurfaceMap( CB_DATADIR"/pics/bomber_dull_green.png", 40, 40);
	//	sur_bombers[8] = app->get_graphics()->createSurfaceMap( CB_DATADIR"/pics/bomber_black.png", 40, 40, 0x00FF00FF );
	}
	return sur_bombers[nr];
}

cbe::SurfaceMap* Resources::Extras_extras()
{
  if (!sur_extras) {
    sur_extras = app->get_graphics()->createSurfaceCollection(CB_DATADIR"/pics/", "extras2", ".png");
  }
  return sur_extras;
}

cbe::AudioBuffer* Resources::Extras_wow()
{
	if (!sfx_wow) {
		sfx_wow = app->get_audio()->createBuffer( CB_DATADIR"/wavs/wow.wav");
	}
	return sfx_wow;
}

cbe::AudioBuffer* Resources::Extras_joint()
{
	if (!sfx_joint) {
		sfx_joint = app->get_audio()->createBuffer(CB_DATADIR"/wavs/joint.wav");
	}
	return sfx_joint;
}

cbe::AudioBuffer* Resources::Extras_horny()
{
	if (!sfx_horny) {
		sfx_horny = app->get_audio()->createBuffer(CB_DATADIR"/wavs/horny.wav");
	}
	return sfx_horny;
}

cbe::AudioBuffer* Resources::Extras_schnief()
{
	if (!sfx_schnief) {
		sfx_schnief = app->get_audio()->createBuffer(CB_DATADIR"/wavs/schnief.wav");
	}
	return sfx_schnief;
}

cbe::AudioBuffer* Resources::Menu_whoosh()
{
	if (!sfx_whoosh) {
		sfx_whoosh = app->get_audio()->createBuffer(CB_DATADIR"/wavs/whoosh.wav");
	}
	return sfx_whoosh;
}

cbe::AudioBuffer* Resources::Menu_break()
{
	if (!sfx_break) {
		sfx_break = app->get_audio()->createBuffer(CB_DATADIR"/wavs/break.wav");
	}
	return sfx_break;
}

cbe::AudioBuffer* Resources::Menu_clear()
{
	if (!sfx_clear) {
		sfx_clear = app->get_audio()->createBuffer(CB_DATADIR"/wavs/clear.wav");
	}
	return sfx_clear;
}
	
cbe::AudioBuffer* Resources::Menu_back()
{
	if (!sfx_menu_back) {
		sfx_menu_back = app->get_audio()->createBuffer(CB_DATADIR"/wavs/menu_back.wav");
	}
	return sfx_menu_back;
}
	
cbe::SurfaceMap* Resources::Observer_observer()
{
	if (!sur_observer) {
   		sur_observer = app->get_graphics()->createSurfaceMap( CB_DATADIR"/pics/observer.png", 40, 40);
	}
	return sur_observer;
}

cbe::AudioBuffer* Resources::Observer_hurry_up()
{
	if (!sfx_hurry_up) {
		sfx_hurry_up = app->get_audio()->createBuffer(CB_DATADIR"/wavs/hurry_up.wav");
	}
	return sfx_hurry_up;
}

cbe::AudioBuffer* Resources::Observer_time_over()
{
	if (!sfx_time_over) {
		sfx_time_over = app->get_audio()->createBuffer(CB_DATADIR"/wavs/time_over.wav");
	}
	return sfx_time_over;
}

cbe::AudioBuffer* Resources::Observer_crunch()
{
	if (!sfx_crunch) {
		sfx_crunch = app->get_audio()->createBuffer(CB_DATADIR"/wavs/crunch.wav");
	}
	return sfx_crunch;
}

cbe::AudioBuffer* Resources::Game_die()
{
	if (!sfx_die) {
		sfx_die = app->get_audio()->createBuffer(CB_DATADIR"/wavs/die.wav");
	}
	return sfx_die;
}

cbe::AudioBuffer* Resources::Game_explode()
{
	if (!sfx_explode) {
		sfx_explode = app->get_audio()->createBuffer(CB_DATADIR"/wavs/explode.wav");
	}
	return sfx_explode;
}

cbe::AudioBuffer* Resources::Game_putbomb()
{
	if (!sfx_putbomb) {
		sfx_putbomb = app->get_audio()->createBuffer(CB_DATADIR"/wavs/putbomb.wav");
	}
	return sfx_putbomb;
}

cbe::AudioBuffer* Resources::Game_deepfall()
{
	if (!sfx_deepfall) {
		sfx_deepfall = app->get_audio()->createBuffer(CB_DATADIR"/wavs/deepfall.wav");
	}
	return sfx_deepfall;
}

cbe::SurfaceMap* Resources::Game_maptiles()
{
	if (!sur_maptiles) {
		sur_maptiles = app->get_graphics()->createSurfaceMap( CB_DATADIR"/pics/maptiles.png", 40, 40 );
	}
	return sur_maptiles;
}

cbe::SurfaceMap* Resources::Game_maptile_addons()
{
	if (!sur_maptile_addons) {
		sur_maptile_addons = app->get_graphics()->createSurfaceMap( CB_DATADIR"/pics/maptile_addons.png", 40, 40);
	}
	return sur_maptile_addons;
}

cbe::SurfaceMap* Resources::Game_bombs()
{
	if (!sur_bombs) {
		sur_bombs = app->get_graphics()->createSurfaceMap( CB_DATADIR"/pics/bombs.png", 40, 40);
	}
	return sur_bombs;
}

cbe::SurfaceMap* Resources::Game_explosion()
{
	if (!sur_explosion) {
		sur_explosion = app->get_graphics()->createSurfaceMap( CB_DATADIR"/pics/explosion2.png", 40, 40);
	}
	return sur_explosion;
}

cbe::Surface* Resources::Game_cb_logo_small()
{
  if (!sur_cb_logo_small) {
    sur_cb_logo_small = app->get_graphics()->createSurface(CB_DATADIR"/pics/cb_logo_small.png");
  }
  return sur_cb_logo_small;
}
	
cbe::Surface* Resources::MapEditor_background()
{
  if (!sur_me_background) {
    sur_me_background = app->get_graphics()->createSurface(CB_DATADIR"/pics/map_editor.png");
  }
  return sur_me_background;
}

cbe::AudioBuffer* Resources::Corpse_explode()
{
	if (!sfx_corpse_explode) {
		sfx_corpse_explode = app->get_audio()->createBuffer(CB_DATADIR"/wavs/corpse_explode.wav");
	}
	return sfx_corpse_explode;
}

cbe::SurfaceMap* Resources::Corpse_part()
{
	if (!sur_corpse_part) {
		sur_corpse_part = app->get_graphics()->createSurfaceMap( CB_DATADIR"/pics/corpse_parts.png", 40, 40);
	}
	return sur_corpse_part;
}

cbe::AudioBuffer* Resources::Splash(int nr)
{
	if (nr > 1 || nr < 0) {
		return NULL;
	}
	if (!sfx_splash[nr]) {
		sfx_splash[0] = app->get_audio()->createBuffer(CB_DATADIR"/wavs/splash1a.wav");
		sfx_splash[1] = app->get_audio()->createBuffer(CB_DATADIR"/wavs/splash2a.wav");
	}
	return sfx_splash[nr];
}
