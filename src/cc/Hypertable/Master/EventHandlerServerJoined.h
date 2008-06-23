/** -*- c++ -*-
 * Copyright (C) 2008 Doug Judd (Zvents, Inc.)
 *
 * This file is part of Hypertable.
 *
 * Hypertable is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; version 2 of the
 * License.
 *
 * Hypertable is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#ifndef HYPERTABLE_EVENTHANDLERSERVERJOINED_H
#define HYPERTABLE_EVENTHANDLERSERVERJOINED_H

#include "Common/Runnable.h"

#include "AsyncComm/ApplicationHandler.h"
#include "AsyncComm/Event.h"

#include "Master.h"


namespace Hypertable {

  class EventHandlerServerJoined : public ApplicationHandler {
  public:
    EventHandlerServerJoined(MasterPtr &master, std::string &location, EventPtr &event_ptr) : ApplicationHandler(event_ptr), m_master_ptr(master), m_location(location) {
      return;
    }

    virtual void run();

  private:
    MasterPtr    m_master_ptr;
    std::string  m_location;
  };

}

#endif // HYPERTABLE_EVENTHANDLERSERVERJOINED_H
