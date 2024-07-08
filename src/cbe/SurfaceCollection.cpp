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

#include "SurfaceCollection.hpp"

#include <boost/format.hpp>

#include "Graphics.hpp"
#include "Exceptions.hpp"

namespace cbe
{
  SurfaceCollection::SurfaceCollection(Graphics *graphics,
                                       const boost::filesystem::path &path,
                                       const std::string &name,
                                       const std::string &extension)
  {
    const int max_image_number = 1000;
    boost::format file_format(name + "_%1$d" + extension);
    for (int i = 0; i < max_image_number; i++) {
      std::string filename = str(file_format % i);
      try {
        surfaces.push_back(graphics->createSurface(path / filename));
      }
      catch (CannotOpenFile&) {
        //XXX Check if at least one image was found?
        break;
      }
    }
  }

  SurfaceCollection::~SurfaceCollection()
  {
    //nothing
  }

  void SurfaceCollection::blit(int x, int y, int frame, uint8_t opacity)
  {
    surfaces[frame].blit(x, y, opacity);
  }

  void SurfaceCollection::blit(int x, int y, float scale_x, float scale_y,
                               int frame, uint8_t opacity)
  {
    surfaces[frame].scaled_blit(x, y, scale_x, scale_y, opacity);
  }
};
