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
#ifndef NIC_7D284CF0E01C0F8B_NIC
#define NIC_7D284CF0E01C0F8B_NIC

#include "../config.h"

/** @def N_NET_posix_socket
 * Pposix socket api is available.
 * Guarantees that sys/socket.h, arpa/inet.h exist.
 * */
/** @def N_NET_posix_netdb
 * Guarantees that netdb.h exists.
 * */
#if defined(N_API_SOCKET) \
    && defined(N_HEADER_ARPA_INET_H) \
    && defined(N_HEADER_NETDB_H)
#   define N_NET_posix_socket
#   define N_NET_posix_netdb
#else
#   error "Posix Socket API is missing."
#endif

/** @def N_NET_epoll
 * epoll API is available.
 * */
#if defined(N_OS_LINUX)
#   define N_NET_epoll
#   define N_NET_use_epoll
#endif

#endif // NIC_7D284CF0E01C0F8B_NIC
