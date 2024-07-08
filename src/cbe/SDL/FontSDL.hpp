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

#ifndef FONTSDL_HPP
#define FONTSDL_HPP

#include "Font.hpp"

#include "SDL.h"
#include "SDL_ttf.h"
#include <boost/filesystem.hpp>

namespace cbe
{
  class FontSDL : public Font
  {
  public:
    FontSDL(const boost::filesystem::path &ttfFile, unsigned int size);
    ~FontSDL();
    void render(const std::string &text, int x, int y,
                FontAlignment alignment = FontAlignment_0left);
    void render(const std::wstring &text, int x, int y,
                FontAlignment alignment = FontAlignment_0left);
    void getSize(const std::string &text, int *w, int *h);
    int getHeight();
  private:
    //static unsigned int count;
    //void StartFontSystem();
    //void StopFontSystem();
    TTF_Font *font;
    static bool high_quality;
  };
};

#endif
