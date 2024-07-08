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

#ifndef SURFACECOLLECTION_HPP
#define SURFACECOLLECTION_HPP

#include <string>
#include <stdint.h>

#include <boost/filesystem.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#include "Surface.hpp"
#include "SurfaceMap.hpp"
//#include "Graphics.hpp"
namespace cbe
{
  class Graphics;
};

namespace cbe
{
  class SurfaceCollection : public SurfaceMap
  {
  public:
    SurfaceCollection(Graphics *graphics, const boost::filesystem::path &path,
                      const std::string &name, const std::string &extension);
    virtual ~SurfaceCollection();
    int getHeight() {return 40;};
    virtual void blit(int x, int y, int frame, uint8_t opacity = 255);
    virtual void blit(int x, int y, float scale_x, float scale_y, int frame,
                      uint8_t opacity = 255);
  private:
    boost::ptr_vector<Surface> surfaces;
  };
};

#endif
