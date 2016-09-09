/*--!>
This file is part of Nebula, a multi-purpose library mainly written in C++.

Copyright 2015-2016 outshined (outshined@riseup.net)
    (PGP: 0x8A80C12396A4836F82A93FA79CA3D0F7E8FBCED6)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as
published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
--------------------------------------------------------------------------<!--*/
#ifndef NIC_027F3C63737AB3A2_NIC
#define NIC_027F3C63737AB3A2_NIC

#include "config.h"

#ifdef N_NET_posix_socket
#   ifdef N_NET_use_epoll
#       include "posix/epoll/epoll_socket.h"
#   endif // N_NET_use_epoll
#endif // N_NET_posix_socket

namespace nebula { namespace foundation { namespace net {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
#ifdef N_NET_posix_socket
#ifdef N_NET_use_epoll
using service = posix::epoll_service;
using socket = posix::epoll_socket;
#endif // N_NET_use_epoll
#endif // N_NET_posix_socket

/** @} */    

}}} // namespaces

#endif // NIC_027F3C63737AB3A2_NIC
