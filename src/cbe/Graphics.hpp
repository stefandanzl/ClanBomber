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

#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <string>

#include <boost/filesystem.hpp>

#include "Screen.hpp"
#include "Font.hpp"
#include "Surface.hpp"
#include "SurfaceMap.hpp"
#include "SurfaceCollection.hpp"

namespace cbe
{
  class Graphics
  {
  public:
    virtual ~Graphics() {};
    virtual void init() = 0;
    virtual void init(unsigned int width, unsigned int height, unsigned int bpp) = 0;
    virtual void close() = 0;
    virtual void setFullscreen(bool fs) = 0;
    virtual bool isFullscreen() = 0;
    virtual Screen *getScreen() = 0;
    virtual Font *createFont(const boost::filesystem::path &file, unsigned int size) = 0;
    virtual SurfaceMap *createSurfaceMap(const boost::filesystem::path &file, unsigned int width, unsigned int height) = 0;
    virtual Surface *createSurface(const boost::filesystem::path &file) = 0;
    virtual SurfaceCollection *createSurfaceCollection(const boost::filesystem::path &path,
                                    const std::string &name,
                                    const std::string &extension) = 0;
    static std::string getName() {};
  };
};

#endif
