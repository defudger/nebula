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
#ifndef NIC_9B62D14C2545A78C_NIC
#define NIC_9B62D14C2545A78C_NIC

#include "../config.h"
#ifdef N_NET_posix_socket

#include "../address.h"
#include "../endpoint.h"
#include "../exception.h"
#include "../../endian.h"
#include <arpa/inet.h>

namespace nebula { namespace foundation { namespace net { namespace posix {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
extern ::socklen_t n_foundation_dll
to_sockaddr(const ip::ipv4_endpoint &ep, ::sockaddr &addr);

extern ::socklen_t n_foundation_dll
to_sockaddr(const endpoint &ep, ::sockaddr &addr);

extern endpoint n_foundation_dll to_endpoint(
    const ::sockaddr &addr, ::socklen_t n);

/** @} */

}}}} // namespaces

#endif // N_NET_posix_socket

#endif // NIC_9B62D14C2545A78C_NIC
