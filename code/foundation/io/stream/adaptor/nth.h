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
#ifndef NIC_FFBBACADF8A16815_NIC
#define NIC_FFBBACADF8A16815_NIC

#include "../stream.h"
#include "../../../call_traits.h"
#include "../../../adaptor.h"

namespace nebula { namespace foundation { namespace io { namespace adaptor {
/** @ingroup Foundation
 * @{ 
 */
namespace nth_detail {
//------------------------------------------------------------------------------
template <class Stream_>
class nth_stream final :
    public adaptor_base<
        Stream_,
        nth_stream<Stream_>>
{
    template <int> struct nil {};
    
    using Stream = typename adaptor_base<Stream_>::adaptee_type;
    using Base = adaptor_base<
        Stream_,
        nth_stream<Stream_>>;
    
public:
    using stream_size = _stream_size<Stream>;
    using stream_position = _stream_position<Stream>;
    using stream_offset = _stream_offset<Stream>;
    using stream_category = tag<io::out_tag,
        meta::_if<has_flush<Stream>, flush_tag, nil<0>>>;
    
    template <class S>
    nth_stream(S &&strm, const char x, const stream_size ncols_)
    : Base(foundation::forward<S>(strm)),
        c_(x),
        ncols(ncols_),
        col(0)
    {
        if(0 == ncols)
            n_throw(logic_error);
    }
    
    inline void write(const char *buf, const size_t n)
    {
        if(col + n <= ncols)
        {
            io::write(this->adaptee(), buf, n);
            col += n;
        }
        else
        {
            stream_size m = ncols-col;
            
            if(m)
                io::write(this->adaptee(), buf, m);
            
            io::put(this->adaptee(), c_);
            col = 0;
            
            for( ; m + ncols < n; m += ncols)
            {
                io::write(this->adaptee(), buf + m, ncols);
                io::put(this->adaptee(), c_);
            }
            
            if(m < n)
            {
                col = n - m;
                io::write(this->adaptee(), buf + m, col);
            }
        }
    }
    inline void put(const char c)
    {
        if(col == ncols)
        {
            io::put(this->adaptee(), c_);
            col = 0;
        }
        
        io::put(this->adaptee(), c);
        ++col;
    }
    
    template <class Cond = has_flush<Stream>,
        _enable_if<Cond>* = nullptr>
    inline void flush() {
        io::flush(this->adaptee());
    }
    
private:
    inline void on_adaptor_reset() noexcept {
        col = 0;
    }
    
    char c_;
    const stream_size ncols;
    stream_size col;
};

//------------------------------------------------------------------------------
struct trigger {
    char c;
    size_t n;
};
//------------------------------------------------------------------------------
template <class T>
inline nth_stream<_remove_reference<T>> operator | (T &&x, trigger y)
{
    return nth_stream<_remove_reference<T>>(
        foundation::forward<T>(x),
        y.c,
        y.n);
}

} // nth_detail

//------------------------------------------------------------------------------
inline nth_detail::trigger nth(const char c, const size_t n)
{
    return nth_detail::trigger{c, n};
}

/** @} */

}}}} // namespaces

#endif // NIC_FFBBACADF8A16815_NIC
