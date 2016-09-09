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
#ifndef NIC_92B1AD219F2ED6FA_NIC
#define NIC_92B1AD219F2ED6FA_NIC

#include "basic.h"
#include "../../stream.h"
#include "../../../../adaptor.h"
#include "../../../../enable_if.h"
#include "../../../../array.h"
#include "../../../../assert.h"

namespace nebula { namespace foundation { namespace io { namespace adaptor {
/** @ingroup Foundation
 * @{ 
 */
namespace base16_detail {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
template <class Stream_>
class base16_dec final :
    public adaptor_base<
        Stream_,
        base16_dec<Stream_>>
{   
    template <int> struct nil {};
    
    using Stream = typename adaptor_base<Stream_>::adaptee_type;
    using Base = adaptor_base<
        Stream_,
        base16_dec<Stream_>>;
    
public:
    using stream_size = _stream_size<Stream>;
    using stream_position = _stream_position<Stream>;
    using stream_offset = _stream_offset<Stream>;
    using stream_category = tag<
        meta::_if<has_write<Stream>, out_tag, nil<0>>,
        meta::_if<has_write<Stream>, flush_tag, nil<1>>,
        meta::_if<has_read<Stream>, in_tag, nil<2>>>;
    
    template <class S>
    base16_dec(S &&strm)
    : Base(foundation::forward<S>(strm)),
        high(-1)
    {}
    inline ~base16_dec() noexcept {}
    
    template <class S = Stream,
        _enable_if<has_write<S>>* = nullptr>
    inline void write(const char *buf_, stream_size n) {
        if(0 == n)
            return;
        if(!buf_)
            n_throw(logic_error);
        
        stream_size i = 0;
        if(-1 != high) {
            io::put(this->adaptee(), decode(high, buf_[i++]));
            high = -1;
        }
        
        while(i < n)
        {
            char d = decode_digit(buf_[i++]);
            if(-1 == d)
                continue;
            if(-1 == high)
                high = d;
            else
            {
                io::put(this->adaptee(), decode(high, d));
                high = -1;
            }
        }
    }
    template <class S = Stream,
        _enable_if<has_write<S>>* = nullptr>
    inline void put(const char c) {
        char d = decode_digit(c);
        if(-1 == d)
            return;
        if(-1 != high) {
            io::put(this->adaptee(), decode(high, d));
            high = -1;
        } else {
            high = d;
        }
    }
    
    template <class S = Stream,
        _enable_if<meta::and_<has_write<S>, has_flush<S>>>* = nullptr>
    inline void flush() {
        io::flush(this->adaptee());
    }
    
    template <class S = Stream,
        _enable_if<has_read<S>>* = nullptr>
    inline stream_size read(char *buf_, stream_size n)
    {
        if(0 == n)
            return 0;
        if(!buf_)
            n_throw(logic_error);
        
        stream_size i = 0;   
        for( ; i < n; ++i)
        {
            ceof c = get();
            if(c.eof())
                return i;
            buf_[i] = c.get();
        }
        
        return i;
    }
    template <class S = Stream,
        _enable_if<has_read<S>>* = nullptr>
    inline ceof get()
    {
        array<char, 2> b;
        unsigned i = 0;
        while(i < 2)
        {
            ceof c = io::get(this->adaptee());
            if(c.eof())
                return io::eof;
            char d = decode_digit(c.get());
            if(-1 == d)
                continue;
            b[i++] = d;
        }
        return decode(b[0], b[1]);
    }
    
private:
    inline void on_adaptor_reset() noexcept {
        high = -1;
    }
    
    char high;
};

//------------------------------------------------------------------------------
struct dec_trigger {};
//------------------------------------------------------------------------------
template <class T>
inline base16_dec<_remove_reference<T>> operator | (T &&x, dec_trigger y)
{
    return base16_dec<_remove_reference<T>>(
        foundation::forward<T>(x));
}

} // base16_detail

//------------------------------------------------------------------------------
inline base16_detail::dec_trigger base16_dec()
{
    return base16_detail::dec_trigger{};
}

/** @} */

}}}} // namespaces

#endif // NIC_92B1AD219F2ED6FA_NIC
