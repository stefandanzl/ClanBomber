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

#ifndef _header_clanbomber_event_
#define _header_clanbomber_event_

#include "UtilsThreads.h"

class Event
{
    public:
        Event();
        ~Event();
        void lock();
        void unlock();
        void signal();
        void broadcast();
        void wait();
    private:
        CB_Mutex *event_mutex;
        CB_Condition *wait_condition;
};

#endif
