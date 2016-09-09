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
#ifndef NIC_1CE81BD7C72E41A7_NIC
#define NIC_1CE81BD7C72E41A7_NIC

#include "../stream.h"
#include "../../../call_traits.h"
#include "../../../adaptor.h"
#include "../../../vector.h"
#include "../../../scope_exit.h"

namespace nebula { namespace foundation { namespace io { namespace adaptor {
/** @ingroup Foundation
 * @{ 
 */
namespace buffer_detail {
//------------------------------------------------------------------------------
template <class Stream_, class Alloc = memory::allocator<char>>
class buffered_stream final :
    public adaptor_base<
        Stream_,
        buffered_stream<Stream_, Alloc>>
{   
    using Stream = typename adaptor_base<Stream_>::adaptee_type;
    using Base = adaptor_base<
        Stream_,
        buffered_stream<Stream_, Alloc>>;
    
    n_static_assert(has_write<Stream>::value, "");
    
public:
    using stream_size = _stream_size<Stream>;
    using stream_position = _stream_position<Stream>;
    using stream_offset = _stream_offset<Stream>;
    using stream_category = tag<out_tag, flush_tag>;
    
    template <class S, class Alloc_>
    buffered_stream(S &&strm, size_t n, Alloc_ &&alc)
    : Base(foundation::forward<S>(strm)),
        limit_(0 == n ? 1024*3*5*7 : n),
        buf(foundation::forward<Alloc_>(alc))
    {
        buf.reserve(limit_);
    }
    inline ~buffered_stream() noexcept(false)
    {
        try { flush_(); }
        catch(...) {
            if(!this->nothrow_dtor())
                throw;
        }
    }
    
    inline void write(const char *x, const stream_size n)
    {
        if(buf.size() + n > limit_)
            flush();
        buf.append(x, n);
    }
    inline void put(const char c)
    {
        if(buf.size() + 1 > limit_)
            flush();
        buf.emplace_back(c);
    }
    template <class Cond = has_flush<Stream>,
        _disable_if<Cond>* = nullptr>
    inline void flush()
    {
        if(!buf.empty())
        {
            n_scope_exit(&) {
                buf.clear();
            };
            io::write(this->adaptee(), buf.data(), buf.size());
        }
    }
    template <class Cond = has_flush<Stream>,
        _enable_if<Cond>* = nullptr>
    inline void flush()
    {
        if(!buf.empty())
        {
            flush_();
            io::flush(this->adaptee());
        }
    }
    
private:
    inline void flush_() {
        io::write(this->adaptee(), buf.data(), buf.size());
        buf.clear();
    }
    inline void on_adaptor_reset() noexcept {
        buf.clear();
    }
    
    vector<char, Alloc> buf;
    size_t limit_;
};

//------------------------------------------------------------------------------
template <class Alloc>
struct trigger {
    size_t n;
    Alloc alloc;
};
//------------------------------------------------------------------------------
template <class T, class Alloc>
inline buffered_stream<_remove_reference<T>, ctraits::_value<Alloc>>
operator | (T &&x, trigger<Alloc> y)
{
    return buffered_stream<_remove_reference<T>, ctraits::_value<Alloc>>(
        foundation::forward<T>(x),
        y.n,
        foundation::move(y.alloc));
}

} // buffer_detail

//------------------------------------------------------------------------------
template <class Alloc = memory::allocator<char>>
inline buffer_detail::trigger<ctraits::_value<Alloc>> buffer(
    size_t n = 0,
    Alloc &&alloc = Alloc())
{
    return buffer_detail::trigger<ctraits::_value<Alloc>>{
        n,
        foundation::forward<Alloc>(alloc)};
}

/** @} */

}}}} // namespaces

#endif // NIC_1CE81BD7C72E41A7_NIC
