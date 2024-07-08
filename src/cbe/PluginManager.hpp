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

#ifndef PLUGINMANAGER_HPP
#define PLUGINMANAGER_HPP

#include <string>
#include <vector>

#include <boost/ptr_container/ptr_list.hpp>

#include "Factories.hpp"
#include "AudioSimple.hpp"

namespace cbe
{
  class PluginManager
  {
  public:
    void registerPluginFactory(AudioSimpleFactory *ASF);
    void registerPluginFactory(GraphicsFactory *GF);
    AudioSimple *createAudioSimple(const std::string &type);
    Graphics *createGraphics(const std::string &type);
    std::vector<std::string> getAudioSimpleNames();
    std::vector<std::string> getGraphicsNames();
    void searchStatic();
    void searchDynamic();
    void search();
    ~PluginManager();
  private:
    boost::ptr_list<AudioSimpleFactory> ASFactories;
    boost::ptr_list<GraphicsFactory> GFactories;
  };
}

#endif
