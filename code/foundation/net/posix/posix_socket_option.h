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
#ifndef NIC_31A3D1823B45A59F_NIC
#define NIC_31A3D1823B45A59F_NIC

#include "../config.h"
#ifdef N_NET_posix_socket

#include "../../tagged_type.h"

#include <sys/socket.h>

namespace nebula { namespace foundation { namespace net { namespace posix {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
namespace option_detail {
template <int Option>
struct option_tag {
    constexpr static int name = Option;
};

struct blocking_tag {};
} // option_detail

//------------------------------------------------------------------------------
template <class T, int Option>
using sol_socket_option = tagged_type<T, option_detail::option_tag<Option>>;

namespace socket_option {
//------------------------------------------------------------------------------
/** Socket operations are blocking.
 * */
using blocking = tagged_type<bool, option_detail::blocking_tag>;
/** Socket is marked to accept connections with listen().
 * */
using accept_connection = sol_socket_option<bool, SO_ACCEPTCONN>;
/** Enable sending of keep-alive messages on connection-oriented sockets.
 * */
using keep_alive = sol_socket_option<bool, SO_KEEPALIVE>;
/** Don't send via a gateway, send only to directly connected hosts.
 * */
using dont_route = sol_socket_option<bool, SO_DONTROUTE>;
/** Indicates that the rules used in validating addresses supplied in
 * a bind() call should allow reuse of local addresses.
 * */
using reuse_address = sol_socket_option<bool, SO_REUSEADDR>;
/** Permits multiple inet or inet6 sockets to be bound to an
 * identical socket address.
 * */
using reuse_port = sol_socket_option<bool, SO_REUSEPORT>;
/** Debug option for sockets.
 * */
using debug = sol_socket_option<bool, SO_DEBUG>;

} // socket_option

/** @} */    

}}}} // namespaces

#endif // N_NET_posix_socket

#endif // NIC_31A3D1823B45A59F_NIC
