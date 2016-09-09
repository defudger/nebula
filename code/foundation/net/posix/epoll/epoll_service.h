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
#ifndef NIC_7083D51A7DD8B064_NIC
#define NIC_7083D51A7DD8B064_NIC

#include "../../config.h"
#if defined(N_NET_posix_socket) && defined(N_NET_epoll)

#include "../../defs.h"
#include "../../../async.h"
#include "../../../ptr.h"

#include <sys/epoll.h>

namespace nebula { namespace foundation { namespace net { namespace posix {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
class epoll_socket;

//------------------------------------------------------------------------------
class n_foundation_dll epoll_service : public ref_counted
{
public:
    inline epoll_service(const size_t n_threads)
    : h(-1), event_count(0)
    {
        this->init(n_threads);
    }
    inline ~epoll_service() noexcept {
        this->kill();
    }
    
    inline void shutdown() noexcept {
        this->kill();
    }

private:
    void init(const size_t n_threads);
    void add(epoll_socket *sock, const event e);
    void mod(epoll_socket *sock, const event e);
    void remove(epoll_socket *sock) noexcept;
    void kill() noexcept;
    void update(const chrono::milliseconds);
    
    int h;
    async::mutex epoll_mtx;
    async::condition_variable epoll_cv;
    size_t event_count;
    vector<async::thread> threads;
    bool stop;
    
    friend class epoll_socket;
};

/** @} */    

}}}} // namespaces

#endif

#endif // NIC_B65CA44FF35A676D_NIC
