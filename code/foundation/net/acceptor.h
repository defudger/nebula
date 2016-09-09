/*--!>
This file is part of Nebula, a multi-purpose library mainly written in C++.

Copyright 2016 outshined (outshined@riseup.net)
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
#ifndef NIC_641DC87871B3571E_NIC
#define NIC_641DC87871B3571E_NIC

#include "socket.h"
#include "socket_option.h"
#include "../async.h"

namespace nebula { namespace foundation { namespace net {
/** @ingroup Foundation
 * @{
 */  
//------------------------------------------------------------------------------
class n_foundation_dll acceptor
{
    using accept_cb_t = function<bool (optional<socket>, errc, exception_ptr)>;
    
public:
    template <class Service, class ... SocketOpts>
    inline acceptor(
        Service &&serv,
        const address_family fam,
        const socket_category cat,
        const protocol_type proto,
        const SocketOpts & ... opts)
    :   socket_(
            foundation::forward<Service>(serv),
            fam,
            cat,
            proto,
            opts...)
    {
        socket_.option(socket_option::blocking{false});
    }
    inline ~acceptor() noexcept {
        this->close();
    }

    errc open(endpoint ep, accept_cb_t acb, size_t backlog = 0);
    void close() noexcept;

private:
    socket socket_;
    accept_cb_t accept_cb;
    async::mutex mtx;
};

}}} // namespaces

#endif // NIC_641DC87871B3571E_NIC
