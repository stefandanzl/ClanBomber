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

#ifndef SURFACEMAPSDL_HPP
#define SURFACEMAPSDL_HPP

#include <boost/filesystem.hpp>

#include "SurfaceMap.hpp"

namespace cbe
{
  class SurfaceMapSDL : public SurfaceMap
  {
  public:
    SurfaceMapSDL(const boost::filesystem::path &filename, unsigned int width, unsigned int height);
    ~SurfaceMapSDL();
    int getHeight();
    void blit(int x, int y, int frame, uint8_t opacity = 255);
    void blit(int x, int y, float scale_x, float scale_y, int frame, uint8_t opacity = 255);
    //void rect( int frame, SDL_Rect *ret_rect );
  private:
    bool colorkeying;
    int sprite_width;
    int sprite_height;
    int frames_per_row;
    SDL_Surface *surface;
  };
};

#endif
