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

#ifndef GRAPHICSSDL_HPP
#define GRAPHICSSDL_HPP

#include "Graphics.hpp"
#include "Screen.hpp"

namespace cbe
{
  class GraphicsSDL : public Graphics
  {
  public:
    GraphicsSDL();
    ~GraphicsSDL();
    void init();
    void init(unsigned int width, unsigned int height, unsigned int bpp);
    void close();
    void setFullscreen(bool fs);
    bool isFullscreen() {return fullscreen;};
    Screen *getScreen();
    Font *createFont(const boost::filesystem::path &file, unsigned int size);
    SurfaceMap *createSurfaceMap(const boost::filesystem::path &file, unsigned int width, unsigned int height);
    Surface *createSurface(const boost::filesystem::path &file);
    SurfaceCollection
    *createSurfaceCollection(const boost::filesystem::path &path,
                             const std::string &name,
                             const std::string &extension);
    static std::string getName() {return "SDL";};
  private:
    Screen *screen;
    bool fullscreen;
  };
};

#endif
