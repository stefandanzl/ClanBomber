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

#ifndef SURFACE_HPP
#define SURFACE_HPP
#include <stdint.h>

namespace cbe
{
  class Surface
  {
  public:
    virtual ~Surface() {};
    virtual void blit(int x, int y, uint8_t opacity = 255) = 0;
    virtual void scaled_blit(int x, int y, float scale_x, float scale_y,
                             uint8_t opacity = 255) = 0;
  };
};

#endif
