/*
 * Copyright (C) 2007-2015 Hypertable, Inc.
 *
 * This file is part of Hypertable.
 *
 * Hypertable is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or any later version.
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

#include <Common/Compat.h>
#include "LogReplayBarrier.h"

#include <Hypertable/Lib/Key.h>

using namespace Hypertable;
using namespace std;

void LogReplayBarrier::set_root_complete() {
  lock_guard<mutex> lock(m_mutex);
  m_root_complete = true;
  m_root_complete_cond.notify_all();
}

void LogReplayBarrier::set_metadata_complete() {
  lock_guard<mutex> lock(m_mutex);
  m_metadata_complete = true;
  m_metadata_complete_cond.notify_all();
}

void LogReplayBarrier::set_system_complete() {
  lock_guard<mutex> lock(m_mutex);
  m_system_complete = true;
  m_system_complete_cond.notify_all();
}

void LogReplayBarrier::set_user_complete() {
  lock_guard<mutex> lock(m_mutex);
  m_user_complete = true;
  m_user_complete_cond.notify_all();
}

bool LogReplayBarrier::wait_for_root(chrono::time_point<chrono::steady_clock> deadline) {
  if (m_root_complete)
    return true;
  unique_lock<mutex> lock(m_mutex);
  HT_INFO("Waiting for ROOT recovery to complete...");
  return m_root_complete_cond.wait_until(lock, deadline,
                                         [this](){ return m_root_complete; });
}

bool LogReplayBarrier::wait_for_metadata(chrono::time_point<chrono::steady_clock> deadline) {
  if (m_metadata_complete)
    return true;
  unique_lock<mutex> lock(m_mutex);
  HT_INFO("Waiting for METADATA recovery to complete...");
  return m_metadata_complete_cond.wait_until(lock, deadline,
                                             [this](){ return m_metadata_complete; });
}

bool LogReplayBarrier::wait_for_system(chrono::time_point<chrono::steady_clock> deadline) {
  if (m_system_complete)
    return true;
  unique_lock<mutex> lock(m_mutex);
  HT_INFO("Waiting for SYSTEM recovery to complete...");
  return m_system_complete_cond.wait_until(lock, deadline,
                                           [this](){ return m_system_complete; });
}

bool LogReplayBarrier::wait_for_user(chrono::time_point<chrono::steady_clock> deadline) {
  if (m_user_complete)
    return true;
  unique_lock<mutex> lock(m_mutex);
  HT_INFO("Waiting for USER recovery to complete...");
  return m_user_complete_cond.wait_until(lock, deadline,
                                         [this](){ return m_user_complete; });
}

bool
LogReplayBarrier::wait(chrono::time_point<chrono::steady_clock> deadline,
                      const TableIdentifier &table,
                      const RangeSpec &range_spec) {
  if (m_user_complete)
    return true;
  if (table.is_metadata()) {
    if (!strcmp(range_spec.end_row, Key::END_ROOT_ROW))
      return wait_for_root(deadline);
    else
      return wait_for_metadata(deadline);
  }
  else if (table.is_system())
    return wait_for_system(deadline);
  return wait_for_user(deadline);
}


bool LogReplayBarrier::wait(chrono::time_point<chrono::steady_clock> deadline,
                            const TableIdentifier &table) {
  if (m_user_complete)
    return true;
  if (table.is_metadata())
    return wait_for_metadata(deadline);
  else if (table.is_system())
    return wait_for_system(deadline);
  return wait_for_user(deadline);
}

bool LogReplayBarrier::user_complete() {
  lock_guard<mutex> lock(m_mutex);
  return m_user_complete;
}
