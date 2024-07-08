/* This file is part of ClanBomber <http://www.nongnu.org/clanbomber>.
 * Copyright (C) 2001-2004, 2007 mass
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

#include "Thread.h"

Thread::Thread()
{
    thread_handle = NULL;
}

Thread::~Thread()
{
    stop();
}

void Thread::run(THREADFUNCTION proc, void* param)
{
  //pthread_create(&thread_handle, NULL, proc, param);
  thread_handle = CB_ThreadCreate(proc, param);
}

void Thread::stop()
{
  //TODO check why the same thread tries to be stoped twice
  //pthread_cancel(thread_handle);
  //printf("thread to destroy: %d\n", thread_handle);
  if (thread_handle == NULL) {
    return;
  }
  CB_ThreadKill(thread_handle);
  thread_handle = NULL;
}
