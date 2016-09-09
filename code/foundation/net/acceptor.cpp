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
#include "acceptor.h"

namespace nebula { namespace foundation { namespace net {
//------------------------------------------------------------------------------
errc acceptor::open(endpoint ep, accept_cb_t acb, const size_t backlog)
{
    accept_cb = foundation::move(acb);
    
    if(!accept_cb)
        n_throw(logic_error);
    
    errc err = socket_.bind(foundation::move(ep));
    if(errc::success != err)
    {
        return err;
    }
    err = socket_.listen(backlog);
    if(errc::success != err)
    {
        return err;
    }
    
    auto f = [this] (socket &sock, const event ev)
    {
        async::lock(this->mtx);
        n_scoped_unlock(this->mtx);
        
        if(!this->accept_cb)
            return;
        
        try
        {   
            while(true)
            {
                auto r = sock.accept();
                if(!r.valid())
                {
                    const errc err = r.error();
                    if(errc::again == err)
                    {
                        break;
                    }
                    else
                    {
                        this->accept_cb(nil_tag(), err, exception_ptr());
                        sock.shutdown(channel::both);
                        this->accept_cb = nullptr;
                        return;
                    }
                }
                else
                {
                    if(!this->accept_cb(
                        r.get(), errc::success, exception_ptr()))
                    {
                        sock.shutdown(channel::both);
                        this->accept_cb = nullptr;
                        return;
                    }
                }
            }
            
            sock.background(event::in);
        }
        catch(...)
        {
            this->accept_cb(nil_tag(), errc::unknown, current_exception());
            sock.shutdown(channel::both);
            this->accept_cb = nullptr;
        }
    };
    
    socket_.background(foundation::move(f), event::in);
    
    return errc::success;
}
//------------------------------------------------------------------------------
void acceptor::close() noexcept
{
    if(accept_cb)
    {
        async::lock(mtx);
        n_scoped_unlock(mtx);
        accept_cb = nullptr;
        socket_.shutdown(channel::both);
    }
}

}}} // namespaces
