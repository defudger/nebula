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
#include "epoll_socket.h"

#if defined(N_NET_posix_socket) && defined(N_NET_epoll)

namespace nebula { namespace foundation { namespace net { namespace posix {
//------------------------------------------------------------------------------
void epoll_service::init(const size_t n_threads)
{
    h = ::epoll_create1(::EPOLL_CLOEXEC);
    if(-1 == h)
    {
        n_throw(network_error, system::system_error)
        << ei_msg_c("epoll_create1() failed")
        << system::ei_error_code(system::error_code(
            errno, system::system_category()));
    }
    
    try
    {
        stop = false;
        
        auto f = [this] () {
            while(true)
            {
                size_t n = 0;
                
                {
                    async::lock(this->epoll_mtx);
                    n_scoped_unlock(this->epoll_mtx);
                    while(!this->stop && 0 == this->event_count)
                        async::wait(this->epoll_cv, this->epoll_mtx);
                    if(this->stop)
                        return;
                }
                
                this->update(chrono::milliseconds(100));
            }
        };
        
        threads.reserve(n_threads);
        for(size_t i = 0; i < n_threads; ++i)
            threads.emplace_back(f);
    }
    catch(...)
    {
        this->kill();
    }
}
//------------------------------------------------------------------------------
inline int to_epoll_event(const event e)
{
    switch(e)
    {
    case event::in: return ::EPOLLIN;
    case event::out: return ::EPOLLOUT;
    case event::io: return ::EPOLLIN | ::EPOLLOUT;
    default:
        n_throw(logic_error);
    }
}
//------------------------------------------------------------------------------
void epoll_service::add(epoll_socket *sock, const event e)
{
    n_assert(-1 != h);
    n_assert(sock);

    ::epoll_event epev = ::epoll_event {
        to_epoll_event(e) | ::EPOLLONESHOT,
        ::epoll_data{ sock }};
    if(-1 == ::epoll_ctl(h, EPOLL_CTL_ADD, sock->native_handle(), &epev))
    {
        n_throw(network_error, system::system_error)
        << ei_msg_c("epoll_ctl() failed")
        << system::ei_error_code(system::error_code(
            errno, system::system_category()));
    }
    
    async::lock(epoll_mtx);
    n_scoped_unlock(epoll_mtx);
    
    ++event_count;
    async::signal(epoll_cv);
}
//------------------------------------------------------------------------------
void epoll_service::mod(epoll_socket *sock, const event e)
{
    n_assert(-1 != h);
    n_assert(sock);
    
    ::epoll_event epev = ::epoll_event {
        to_epoll_event(e) | ::EPOLLONESHOT,
        ::epoll_data{ sock }};
    if(-1 == ::epoll_ctl(h, EPOLL_CTL_MOD, sock->native_handle(), &epev))
    {
        n_throw(network_error, system::system_error)
        << ei_msg_c("epoll_ctl() failed")
        << system::ei_error_code(system::error_code(
            errno, system::system_category()));
    }
}
//------------------------------------------------------------------------------
void epoll_service::remove(epoll_socket *sock) noexcept
{
    n_assert(-1 != h);
    n_assert(sock);
    
    ::epoll_ctl(h, EPOLL_CTL_DEL, sock->native_handle(), nullptr);
    
    async::lock(epoll_mtx);
    n_scoped_unlock(epoll_mtx);
    
    --event_count;
}
//------------------------------------------------------------------------------
void epoll_service::update(const chrono::milliseconds blk)
{
    n_assert(-1 != h);
    
    static thread_local array<::epoll_event, 1000> ep_events;
    
    const int r = ::epoll_wait(
        h, ep_events.data(), ep_events.size(), blk.count());
    
    if(-1 == r)
    {
        n_throw(network_error, system::system_error)
        << ei_msg_c("epoll_wait() failed")
        << system::ei_error_code(system::error_code(
            errno, system::system_category()));
    }
    
    for(auto &x : ep_events | range::adaptor::slice(0, r))
    {
        epoll_socket *s = static_cast<epoll_socket *>(x.data.ptr);
        
        event ev;
        if( ((x.events & ::EPOLLIN) == ::EPOLLIN)
            && ((x.events & ::EPOLLOUT) == ::EPOLLOUT) )
            ev = event::io;
        else if( (x.events & ::EPOLLIN) == ::EPOLLIN)
            ev = event::in;
        else
            ev = event::out;
        
        s->callback(ev);
    }
}
//------------------------------------------------------------------------------
void epoll_service::kill() noexcept
{
    if(-1 != h)
    {
        {
            stop = true;
            async::lock(epoll_mtx);
            n_scoped_unlock(epoll_mtx);
            async::broadcast(epoll_cv);
        }
        for(auto &x : threads)
            async::join(x);
        
        ::close(h);
        h = -1;
    }
}

}}}} // namespaces

#endif
