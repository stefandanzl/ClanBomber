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

#include "PluginManager.hpp"

#include <iostream>
#include <string>

#include "config.h"
#include "Factories.hpp"
#include "SDL/FactoriesSDL.hpp"
#ifdef ENABLE_OPENAL
#  include "OAL/FactoriesOAL.hpp"
#endif

namespace cbe
{
  void RegisterSDL(PluginManager *PM)
  {
    //Register SDL sound
    PM->registerPluginFactory(new AudioSimpleFactorySDL());
    //Register SDL graphics
    PM->registerPluginFactory(new GraphicsFactorySDL());
  }

  void RegisterOAL(PluginManager *PM)
  {
    #ifdef ENABLE_OPENAL
    PM->registerPluginFactory(new AudioSimpleFactoryOAL());
    #endif
  }

  void PluginManager::registerPluginFactory(AudioSimpleFactory *ASF)
  {
    //std::cout << "(Audio) Pushing " << ASF->getName() << std::endl;
    ASFactories.push_back(ASF);
  }

  void PluginManager::registerPluginFactory(GraphicsFactory *GF)
  {
    //std::cout << "(Graphics) Pushing " << GF->getName() << std::endl;
    GFactories.push_back(GF);
  }

  AudioSimple *PluginManager::createAudioSimple(const std::string &type)
  {
    boost::ptr_list<AudioSimpleFactory>::iterator ite;
    for(ite = ASFactories.begin(); ite != ASFactories.end(); ite++) {
      if(ite->getName() == type) {
        return ite->create();
      }
    }
    return NULL;
  }

  Graphics *PluginManager::createGraphics(const std::string &type)
  {
    boost::ptr_list<GraphicsFactory>::iterator ite;
    for (ite = GFactories.begin(); ite != GFactories.end(); ite++) {
      if (ite->getName() == type) {
        return ite->create();
      }
    }
    return NULL;
  }

  std::vector<std::string> PluginManager::getAudioSimpleNames()
  {
    std::vector<std::string> names;
    boost::ptr_list<AudioSimpleFactory>::iterator ite;
    for(ite = ASFactories.begin(); ite != ASFactories.end(); ite++) {
      names.push_back(ite->getName());
    }
    return names;
  }

  std::vector<std::string> PluginManager::getGraphicsNames()
  {
    std::vector<std::string> names;
    boost::ptr_list<GraphicsFactory>::iterator ite;
    for(ite = GFactories.begin(); ite != GFactories.end(); ite++) {
      names.push_back(ite->getName());
    }
    return names;
  }

  void PluginManager::searchStatic()
  {
    //std::cout << "Registering Plugins\n";
    RegisterSDL(this);
    RegisterOAL(this);
  }

  void PluginManager::searchDynamic()
  {

  }

  void PluginManager::search()
  {
    searchStatic();
    searchDynamic();
  }

  PluginManager::~PluginManager()
  {

  }
};
