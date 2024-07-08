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

#include "AudioSimpleOAL.hpp"

#include "AL/al.h"
#include "AL/alc.h"

#include "AudioBufferOAL.hpp"

namespace cbe
{
  bool AudioSimpleOAL::init()
  {
    if (!initialized) {
      device = alcOpenDevice(NULL);
      if (device) {
        context = alcCreateContext(device, NULL);
        alcMakeContextCurrent(context);
      }
      alGetError();
    }
    initialized++;
    return true;
  }

  void AudioSimpleOAL::close()
  {
    if (initialized = 1) {
      alcMakeContextCurrent(NULL);
      alcDestroyContext(context);
      alcCloseDevice(device);
    }
    if (initialized > 0) {
      initialized--;
    }
  }

  AudioSimpleOAL::AudioSimpleOAL()
  {
    initialized = 0;
  }

  AudioSimpleOAL::~AudioSimpleOAL()
  {
    if (initialized) {
      initialized = 1;
      close();
    }
  }

  AudioBuffer *AudioSimpleOAL::createBuffer(boost::filesystem::path filename)
  {
    return new AudioBufferOAL(filename);
  }
};
