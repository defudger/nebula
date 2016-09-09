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
#ifndef NIC_AC0EAFC02F276306_NIC
#define NIC_AC0EAFC02F276306_NIC

#include "../../config.h"
#if defined(N_NET_posix_socket) && defined(N_NET_epoll)

#include "epoll_service.h"
#include "../posix_socket.h"
#include "../../../carray.h"

namespace nebula { namespace foundation { namespace net { namespace posix {
/** @ingroup Foundation
 * @{
 */
//------------------------------------------------------------------------------
class n_foundation_dll epoll_socket
{
    using callback_type = function<void (epoll_socket &, event)>;
    using socket_type = posix::socket;
    
    enum class state
    {
        idle,
        busy,
        again
    };
    
public:
    epoll_socket() = delete;
    epoll_socket(epoll_socket &) = delete;
    epoll_socket(const epoll_socket &) = delete;
    epoll_socket(epoll_socket &&) = default;
    
    template <class epoll_service, class X>
    inline epoll_socket(epoll_service &&serv_, X &&x, adopt_tag) noexcept
    :   serv(foundation::forward<epoll_service>(serv_)),
        sock(foundation::forward<X>(x)),
        ev(event::in),
        st(state::idle)
    {}
    
    template <class epoll_service, class ... Options>
    inline epoll_socket(
        epoll_service &&serv_,
        const net::address_family fam,
        const net::socket_category cat,
        const protocol_type proto,
        const Options & ... opts)
    :   serv(foundation::forward<epoll_service>(serv_)),
        sock(fam, cat, proto, opts...),
        ev(event::in),
        st(state::idle)
    {}
    
    epoll_socket &operator = (epoll_socket &) = delete;
    epoll_socket &operator = (const epoll_socket &) = delete;
    epoll_socket &operator = (epoll_socket &&) = default;
    
    inline void swap(epoll_socket &other) noexcept
    {
        foundation::swap(serv, other.serv);
        foundation::swap(sock, other.sock);
        foundation::swap(cb, other.cb);
        foundation::swap(ev, other.ev);
        foundation::swap(st, other.st);
    }
    
    template <class ... Options>
    inline void option(const Options & ... opts)
    {
        sock.set_option(opts ...);
    }
    template <class Option>
    inline Option option() const
    {
        return sock.get_option<Option>();
    }
    
    /**
     *  @return Either success or an error code.
     *  @note List of possible error codes:
     *      again
     *      timedout
     *      address_in_use
     *      connection_refused
     *      network_unreachable
     * */
    inline errc connect(const endpoint &ep) {
        sock.connect(ep);
    }
    /**
     *  @throw nothing
     * */
    inline void shutdown(const channel ch) noexcept {
        sock.shutdown(ch);
    }

    /**
     *  @return Either success or an error code.
     *  @note List of possible error codes:
     *      address_in_use
     * */
    inline errc listen(const size_t backlog) {
        return sock.listen(backlog);
    }
    /**
     *  @return Either success or an error code.
     *  @note List of possible error codes:
     *      address_in_use
     * */
    template <class Endpoint>
    inline errc bind(const Endpoint &ep) {
        return sock.bind(ep);
    } 
    /**
     * @return Either a new socket or an error code.
     * @note List of possible error codes:
     *      again
     *      address_in_use
     *      connection_aborted
     *      timedout
     * */
    inline expect<epoll_socket, errc> accept()
    {
        auto r = sock.accept();
        if(!r.valid())
            return r.error();
        return epoll_socket(serv, r.get(), adopt_tag());
    }
    
    /** @returns The address the socket is bound to.
     * */
    inline endpoint bound_endpoint() const {
        return sock.bound_endpoint();
    }
    /** @returns The address of the peer connected to the socket.
     * */
    inline endpoint peer_endpoint() const {
        return sock.peer_endpoint();
    }
    
    /** Calls ::send().
     * @return Either the result or an error code.
     * @note List of possible error codes:
     *      again
     *      connection_reset
     * */
    inline expect<size_t, errc> send(carray<const char> data) {
        return sock.send(data.data(), data.size());
    }
    /** Calls ::recv().
     * @return Either the result or an error code.
     * @note List of possible error codes:
     *      again
     *      connection_reset
     * */
    inline expect<size_t, errc> recv(carray<char> data) {
        return sock.recv(data.data(), data.size());
    }
    
    template <class F>
    inline void background(F &&f, const event e = event::io)
    {
        n_assert(serv);
        n_assert(!cb);
        n_assert(state::idle == st || state::busy == st);
        
        const bool was_idle = state::idle == st;
        ev = e;
        cb = foundation::forward<F>(f);
        st = state::busy;
        if(was_idle)
        {
            try {
                serv->add(this, ev);
            } catch(...) {
                st = state::idle;
                cb = nullptr;
                throw;
            }
        }
    }
    inline void background(const event e = event::io) noexcept
    {
        n_assert(serv);
        n_assert(!cb);
        n_assert(state::busy == st);
        
        ev = e;
        st = state::again;
    }
    
    inline auto native_handle() const noexcept {
        return sock.native_handle();
    }
    inline auto dismiss() noexcept {
        return sock.dismiss();
    }
    template <class X>
    inline void adopt(X x) noexcept {
        sock.adopt(x);
    }
    
private:
    inline posix::socket &backend() noexcept {
        return sock;
    }
    inline const posix::socket &backend() const noexcept {
        return sock;
    }
    void callback(const event ev) noexcept;
    
    intrusive_ptr<epoll_service> serv;
    socket_type sock;
    callback_type cb;
    event ev;
    state st;
    
    friend class epoll_service;
};

/** @} */    

}}}} // namespaces

#endif

#endif // NIC_AC0EAFC02F276306_NIC
