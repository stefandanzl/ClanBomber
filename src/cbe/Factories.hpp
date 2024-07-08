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

#ifndef FACTORIES_HPP
#define FACTORIES_HPP

#include <string>

#include "AudioSimple.hpp"
#include "Graphics.hpp"

namespace cbe
{
  //Teplate for the creation of interfaces for subsystems
  template<typename T>
  class PluginFactoryAbstract
  {
  public:
    virtual T *create() = 0;
    virtual std::string getName() = 0;
  };

  //Teplate for the creation of implementations for subsystems
  //P = Plugin Implementation
  //PA = Plugin Abstract
  template<typename P, typename PA>
  class PluginFactoryImplementation : public PluginFactoryAbstract<PA>
  {
  public:
    PA *create()
    {
      return new P();
    }
    std::string getName()
    {
      return P::getName();
    }
  };

  typedef PluginFactoryAbstract<AudioSimple> AudioSimpleFactory;
  typedef PluginFactoryAbstract<Graphics> GraphicsFactory;
};

#endif
