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
#ifndef NIC_17A3D1823B45A59A_NIC
#define NIC_17A3D1823B45A59A_NIC

#include "../config.h"
#ifdef N_NET_posix_socket

#include "../error.h"

namespace nebula { namespace foundation { namespace net { namespace posix {
/** @ingroup Foundation
 * @{
 */  
//------------------------------------------------------------------------------
inline net::errc map_error(const system::errval_t e)
{
    switch(e)
    {
    case 0:
        return net::errc::success;
        
    case EADDRINUSE:
        return net::errc::address_in_use;
       
    case ECONNREFUSED:
        return net::errc::connection_refused;
    case ECONNABORTED:
        return net::errc::connection_aborted;
    case ECONNRESET:
        return net::errc::connection_reset;
        
    case ENETDOWN:
        return net::errc::network_down;
    case ENETUNREACH:
        return net::errc::network_unreachable;
    case ENETRESET:
        return net::errc::network_reset;
        
    case EHOSTUNREACH:
        return net::errc::host_unreachable;
        
    case EALREADY: // ::connect()
    case EINPROGRESS: // ::connect()
    case EAGAIN:
        return net::errc::again;
    case ETIMEDOUT:
        return net::errc::timedout;
        
    default:
        return net::errc::unknown;
    }
};

/** @} */    

}}}} // namespaces

#endif // N_NET_posix_socket

#endif // NIC_17A3D1823B45A59A_NIC
