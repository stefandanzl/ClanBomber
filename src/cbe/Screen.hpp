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

#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <stdint.h>

namespace cbe
{
  class Screen
  {
  public:
    virtual void Flip() = 0;
    virtual void Fill(uint8_t r, uint8_t g, uint8_t b) = 0;
    virtual void FillRect(int x, int y, int w, int h, uint8_t r, uint8_t g,
                          uint8_t b) = 0;
    virtual void FillRect(int x, int y, int w, int h, uint8_t r, uint8_t g,
                          uint8_t b, uint8_t a) = 0;
    //void FillRects(SDL_Rect *rects, int num, uint8_t r, uint8_t g, uint8_t b, uint8_t a) = 0;
    //void CB_FillRects(SDL_Rect *rects, int numº, uint8_t r, uint8_t g, uint8_t b) = 0;
  };
};

#endif
