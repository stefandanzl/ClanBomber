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

#ifndef SURFACESDL_HPP
#define SURFACESDL_HPP

#include <boost/filesystem.hpp>

#include "Surface.hpp"
#include "SDL.h"

namespace cbe
{
  class SurfaceSDL : public Surface
  {
  public:
    SurfaceSDL(const boost::filesystem::path &file);
    SurfaceSDL(SDL_Surface *extSurface, SDL_Rect *rect);
    ~SurfaceSDL();
    void blit(int x, int y, uint8_t opacity = 255);
    void scaled_blit(int x, int y, float scale_x, float scale_y,
                     uint8_t opacity = 255);
  private:
    void create(SDL_Surface *extSurface, SDL_Rect *rect);

    SDL_Surface *surface;
  };
};

#endif
