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

#include "SurfaceSDL.hpp"

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_rotozoom.h"

#include "Exceptions.hpp"

extern SDL_Surface *primary;

namespace cbe
{
  SurfaceSDL::SurfaceSDL(const boost::filesystem::path &file)
  {
    std::string fnf = "Couldn't open " + file.string();
    surface = IMG_Load(file.string().c_str());
    if (surface == NULL) {
      if (IMG_GetError() == fnf) {
        throw CannotOpenFile(IMG_GetError());
      }
      throw Exception(IMG_GetError());
    }
  }

  SurfaceSDL::SurfaceSDL(SDL_Surface *extSurface, SDL_Rect *rect)
  {
    create(extSurface, rect);
  }

  SurfaceSDL::~SurfaceSDL()
  {
    SDL_FreeSurface(surface);
  }

  void SurfaceSDL::blit(int x, int y, uint8_t opacity)
  {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    SDL_SetAlpha(surface, SDL_SRCALPHA, opacity);
    SDL_BlitSurface(surface, NULL, primary, &rect);
  }
  void SurfaceSDL::scaled_blit(int x, int y, float scale_x, float scale_y,
                               uint8_t opacity)
  {
    SDL_Surface *tmpSurface;
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;

    tmpSurface = zoomSurface(surface, scale_x, scale_y, 0);
    SDL_BlitSurface(tmpSurface, NULL, primary, &rect);
    SDL_FreeSurface(tmpSurface);
  }

  void SurfaceSDL::create(SDL_Surface *extSurface, SDL_Rect *rect)
  {
    surface = SDL_CreateRGBSurface(SDL_HWSURFACE,
                                   rect->w,
                                   rect->h,
                                   primary->format->BitsPerPixel,
                                   primary->format->Rmask,
                                   primary->format->Gmask,
                                   primary->format->Bmask,
                                   primary->format->Amask);

    SDL_PixelFormat *format = extSurface->format;
    Uint8 r ,g, b;
    r = ((format->colorkey & format->Rmask) >> format->Rshift) << format->Rloss;
    g = ((format->colorkey & format->Gmask) >> format->Gshift) << format->Gloss;
    b = ((format->colorkey & format->Bmask) >> format->Bshift) << format->Bloss;
    SDL_SetColorKey(surface,
                    SDL_SRCCOLORKEY,
                    SDL_MapRGB(surface->format, r, g, b));

    SDL_BlitSurface(extSurface, rect, surface, NULL);
  }

  Surface *CreateSurface(char *filename)
  {
    return new SurfaceSDL(filename);
  }

  Surface *CreateSurface(SDL_Surface *extSurface, SDL_Rect *rect)
  {
    return new SurfaceSDL(extSurface, rect);
  }
};
