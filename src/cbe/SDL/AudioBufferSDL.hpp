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

#ifndef AUDIOBUFFERSDL_HPP
#define AUDIOBUFFERSDL_HPP

#include <boost/filesystem.hpp>

#include "AudioBuffer.hpp"
#include "SDL_mixer.h"

namespace cbe
{
  class AudioBufferSDL : public AudioBuffer
  {
  public:
    AudioBufferSDL(boost::filesystem::path filename);
    ~AudioBufferSDL();
    virtual void play();
  private:
    Mix_Chunk *chunk;
  };
};

#endif
