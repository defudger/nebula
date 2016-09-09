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
#ifndef NIC_3441ED732890F20C_NIC
#define NIC_3441ED732890F20C_NIC

#include "promise.h"

namespace nebula { namespace foundation { namespace async {
//------------------------------------------------------------------------------
template <class T = void>
class future
{
public:
    using value_type = T;
    using promise_type = async::promise<T>;
    
    future()
    : impl(nullptr)
    {
        impl = new future_detail::future_backend<T>();
    }
    future(future &) = default;
    future(const future &) = default;
    future(future &&x) = default;
    
    future &operator = (const future &) = default;
    future &operator = (future &&x) = default;
    
    inline void wait()
    {
        impl->wait();
    }
    template <class Duration>
    inline bool wait_for(const Duration &dur)
    {
        return impl->wait_for(dur);
    }
    
    inline auto get()
    {
        return impl->get();
    }
    
    inline bool valid() const noexcept {
        return impl->valid();
    }
    inline operator bool () const noexcept {
        return this->valid();
    }
    
    inline promise_type promise() {
        return promise_type(impl);
    }
    
private:
    intrusive_ptr<future_detail::future_backend<T>> impl;
};

}}} // namespaces

#endif // NIC_3441ED732890F20C_NIC
