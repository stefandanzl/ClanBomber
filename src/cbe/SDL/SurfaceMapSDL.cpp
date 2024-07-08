/* This file is part of ClanBomber <http://www.nongnu.org/clanbomber>.
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

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_rotozoom.h"
#include "SurfaceMapSDL.hpp"

extern SDL_Surface *primary;

namespace cbe
{
  SurfaceMapSDL::SurfaceMapSDL(const boost::filesystem::path &file, unsigned int width, unsigned int height)
  {
    surface = IMG_Load(file.string().c_str());

    frames_per_row = surface->w/width;

    this->sprite_width = width;
    this->sprite_height = height;

    colorkeying = false;
  }

  SurfaceMapSDL::~SurfaceMapSDL()
  {
    SDL_FreeSurface(surface);
  }

  int SurfaceMapSDL::getHeight()
  {
    return sprite_height;
  }

  void SurfaceMapSDL::blit(int x, int y, int frame, uint8_t opacity)
  {
    SDL_Rect srect;
    SDL_Rect drect;

    srect.x = (frame % frames_per_row) * sprite_width;
    srect.y = (frame / frames_per_row) * sprite_height;
    srect.w = sprite_width;
    srect.h = sprite_height;

    drect.x = x;
    drect.y = y;

    if (opacity < 255) {
      ///primary->SetColor( primary, 0, 0, 0, opacity );
      SDL_BlitSurface(surface, &srect, primary, &drect);
      //TODO add opacity, where is used?
    }

    SDL_BlitSurface(surface, &srect, primary, &drect);
  }

  void SurfaceMapSDL::blit(int x, int y, float scale_x, float scale_y, int frame, uint8_t opacity)
  {
    //This function needs cleanup
    SDL_Rect srect;
    SDL_Rect irect;
    SDL_Rect drect;
    SDL_Surface *tmpSurface;
    SDL_Surface *surf;

    srect.x = (frame % frames_per_row) * sprite_width;
    srect.y = (frame / frames_per_row) * sprite_height;
    srect.w = sprite_width;
    srect.h = sprite_height;

    irect.x = 0;
    irect.y = 0;

    drect.x = x;
    drect.y = y;

    tmpSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, srect.w, srect.h, 32, 0, 0, 0, 0);

    Uint8 r, g, b;
    SDL_GetRGB(surface->format->colorkey, surface->format, &r, &g, &b);
    SDL_SetColorKey(tmpSurface, SDL_SRCCOLORKEY, SDL_MapRGB(tmpSurface->format, r, g, b));
    SDL_FillRect(tmpSurface, NULL, SDL_MapRGB(tmpSurface->format, r, g, b) );
    SDL_BlitSurface(surface, &srect, tmpSurface, &irect);

    surf = zoomSurface(tmpSurface, scale_x, scale_y, 0);

    SDL_SetColorKey(surf, SDL_SRCCOLORKEY, SDL_MapRGB(surf->format, r, g, b));

    srect.x = 0;
    srect.y = 0;
    srect.w = surf->w;
    srect.h = surf->h;

    if (opacity < 255) {
      ///primary->SetColor( primary, 0, 0, 0, opacity );
      SDL_BlitSurface(surf, &srect, primary, &drect);
      //TODO add opacity, where is used?
    }

    SDL_BlitSurface(surf, &srect, primary, &drect);

    SDL_FreeSurface(tmpSurface);
    SDL_FreeSurface(surf);
  }

  /*void SurfaceMapSDL::get_rect( int frame, SDL_Rect *ret_rect )
  {
    ret_rect->x = (frame % frames_per_row) * sprite_width;
    ret_rect->y = (frame / frames_per_row) * sprite_height;
    ret_rect->w = sprite_width;
    ret_rect->h = sprite_height;
    }*/
};
