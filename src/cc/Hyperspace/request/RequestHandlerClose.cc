/*
 * Copyright (C) 2007-2016 Hypertable, Inc.
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

#include "Common/Compat.h"
#include "Common/Error.h"
#include "Common/Logger.h"

#include "AsyncComm/ResponseCallback.h"
#include "Common/Serialization.h"

#include "Hyperspace/Master.h"
#include "RequestHandlerClose.h"

using namespace Hyperspace;
using namespace Hypertable;
using namespace Serialization;

/*
 *
 */
void RequestHandlerClose::run() {
  ResponseCallback cb(m_comm, m_event);
  size_t decode_remain = m_event->payload_len;
  const uint8_t *decode_ptr = m_event->payload;

  try {
    uint64_t handle = decode_i64(&decode_ptr, &decode_remain);

    m_master->close(&cb, m_session_id, handle);
  }
  catch (Exception &e) {
    HT_ERROR_OUT << e << HT_END;
    cb.error(e.code(), "Error handling CLOSE message");
  }
}
