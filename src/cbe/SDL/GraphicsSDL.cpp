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

#include "GraphicsSDL.hpp"

#include "SDL.h"

#include "ScreenSDL.hpp"
#include "FontSDL.hpp"
#include "SurfaceSDL.hpp"
#include "SurfaceMapSDL.hpp"


SDL_Surface *primary;

namespace cbe
{
  GraphicsSDL::GraphicsSDL()
  {
    fullscreen = false;
  }

  void GraphicsSDL::init()
  {
    init(800, 600, 32);
  }

  void GraphicsSDL::init(unsigned int width, unsigned int height, unsigned int bpp)
  {
    SDL_InitSubSystem(SDL_INIT_VIDEO);
    Uint32 fs = 0;
    if(fullscreen) {
      fs = SDL_FULLSCREEN;
    }
    primary = SDL_SetVideoMode(width, height, bpp, SDL_SWSURFACE | SDL_DOUBLEBUF | fs);
    screen = new ScreenSDL(primary);
  }

  void GraphicsSDL::setFullscreen(bool fs)
  {
    fullscreen = fs;
    if(screen != NULL) {
      init(800, 600, 32);
    }
  }

  Screen *GraphicsSDL::getScreen()
  {
    return screen;
  }

  void GraphicsSDL::close()
  {
    delete screen;
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    //SDL_Quit();
  }

  GraphicsSDL::~GraphicsSDL()
  {
    close();
  }

  Font *GraphicsSDL::createFont(const boost::filesystem::path &file, unsigned int size)
  {
    Font *font = new FontSDL(file, size);
    //font->setScreen(getScreen());
    return font;
  }

  SurfaceMap *GraphicsSDL::createSurfaceMap(const boost::filesystem::path &file, unsigned int width, unsigned int height)
  {
    return new SurfaceMapSDL(file, width, height);
  }

  Surface *GraphicsSDL::createSurface(const boost::filesystem::path &file)
  {
    return new SurfaceSDL(file);
  }

  SurfaceCollection
  *GraphicsSDL::createSurfaceCollection(const boost::filesystem::path &path,
                                        const std::string &name,
                                        const std::string &extension)
  {
    return new SurfaceCollection(static_cast<Graphics*>(this), path, name, extension);
  }
};
