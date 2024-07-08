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

#include "AudioBufferOAL.hpp"

#include <AL/al.h>
#include "SDL.h"

namespace cbe
{
  AudioBufferOAL::AudioBufferOAL(boost::filesystem::path filename)
  {
    //XXX Sources probably need to be created at AudioSimple and only be requested from here at play if none is available then the sound will not be played
    alGenBuffers(1, buffers);

    loadWav(filename);

    alGenSources(1, sources);

    alSourcei(sources[0], AL_BUFFER, buffers[0]);

    //ALfloat sourcePos[]={0.0f, 0.0f, 0.0f};
    //ALfloat sourceOri[]={0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f};
    //alSourcef(sources[0], AL_PITCH, 1.5f);
    //alSourcei(sources[0], AL_LOOPING, AL_TRUE);
    //alSourcefv(sources[0], AL_POSITION, sourcePos);
    //alSourcefv(sources[0], AL_VELOCITY, listenerVel);
    //alSourcefv(sources[0], AL_ORIENTATION, sourceOri);

  }

  AudioBufferOAL::~AudioBufferOAL()
  {

  }

  void AudioBufferOAL::play()
  {
    alSourcePlay(sources[0]);
  }

  void AudioBufferOAL::loadWav(boost::filesystem::path &filename)
  {
    SDL_AudioSpec wav_spec;
    Uint8 *wav_buffer;
    Uint32 wav_length;

    SDL_LoadWAV(filename.string().c_str(), &wav_spec,
                &wav_buffer, &wav_length);

    ALenum format;
    switch (wav_spec.format) {
    case AUDIO_U8:
      format = AL_FORMAT_MONO8;
      break;
    case AUDIO_S16SYS:
      format = AL_FORMAT_MONO16;
      break;
    default:
      printf("Error: unsupported wav format");
    }
    alBufferData(buffers[0], format, wav_buffer, wav_length,
                 wav_spec.freq);

    SDL_FreeWAV(wav_buffer);
  }
};
