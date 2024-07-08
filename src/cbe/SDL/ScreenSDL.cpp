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

#include "ScreenSDL.hpp"

#include "SDL.h"

namespace cbe
{
  ScreenSDL::ScreenSDL(SDL_Surface *surf)
  {
    surface = surf;
  }

  void ScreenSDL::Flip()
  {
    SDL_Flip(surface);
  }

  void ScreenSDL::Fill(uint8_t r, uint8_t g, uint8_t b)
  {
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, r, g, b));
  }

  void ScreenSDL::FillRect(int x,	int y, int w, int h, uint8_t r, uint8_t g,
                           uint8_t b)
  {
    SDL_Rect rect = {x, y, w, h};
    SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, r, g, b));
  }

  void ScreenSDL::FillRect(int x, int y, int w, int h, uint8_t r, uint8_t g,
                           uint8_t b, uint8_t a)
  {
    SDL_Rect rect = {x, y, 0, 0};
    SDL_Surface *tmpSurface = SDL_CreateRGBSurface(SDL_HWSURFACE,
                                                   w,
                                                   h,
                                                   surface->format->BitsPerPixel,
                                                   surface->format->Rmask,
                                                   surface->format->Gmask,
                                                   surface->format->Bmask,
                                                   surface->format->Amask);
    SDL_SetAlpha(tmpSurface, SDL_SRCALPHA, a);
    SDL_FillRect(tmpSurface, NULL, SDL_MapRGB(tmpSurface->format, r, g, b));
    SDL_BlitSurface(tmpSurface, NULL, surface, &rect);
    SDL_FreeSurface(tmpSurface);
  }

  SDL_Surface *ScreenSDL::getSDL_Surface()
  {
    return surface;
  }
};
