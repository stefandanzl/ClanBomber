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

#include "AudioSimpleSDL.hpp"

#include "SDL_mixer.h"

#include "AudioBufferSDL.hpp"

namespace cbe
{
  bool AudioSimpleSDL::init()
  {
    if (!initialized) {
      if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 1024)) {
        Mix_CloseAudio();
        return false;
      }
    }
    initialized++;
    return true;
  }

  void AudioSimpleSDL::close()
  {
    if (initialized = 1) {
      Mix_CloseAudio();
    }
    if (initialized > 0) {
      initialized--;
    }
  }

  AudioSimpleSDL::AudioSimpleSDL()
  {
    initialized = 0;
  }

  AudioSimpleSDL::~AudioSimpleSDL()
  {
    Mix_CloseAudio();
  }

  AudioBuffer *AudioSimpleSDL::createBuffer(boost::filesystem::path filename)
  {
    return new AudioBufferSDL(filename);
  }
};
