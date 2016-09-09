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
#ifndef NIC_67C388C790958F1B_NIC
#define NIC_67C388C790958F1B_NIC

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
//------------------------------------------------------------------------------
template <class Stream_, class Codec>
class base16_enc final :
    public adaptor_base<
        Stream_,
        base16_enc<Stream_, Codec>>
{   
    template <int> struct nil {};
    
    using Stream = typename adaptor_base<Stream_>::adaptee_type;
    using Base = adaptor_base<
        Stream_,
        base16_enc<Stream_, Codec>>;
    
public:
    using stream_size = _stream_size<Stream>;
    using stream_position = _stream_position<Stream>;
    using stream_offset = _stream_offset<Stream>;
    using stream_category = tag<
        meta::_if<has_write<Stream>, out_tag, nil<0>>,
        meta::_if<has_write<Stream>, flush_tag, nil<1>>,
        meta::_if<has_read<Stream>, in_tag, nil<2>>>;
    
    template <class S>
    base16_enc(S &&strm)
    : Base(foundation::forward<S>(strm)),
        low(-1)
    {}
    inline ~base16_enc() noexcept {}
    
    template <class S = Stream,
        _enable_if<has_write<S>>* = nullptr>
    inline void write(const char *buf_, stream_size n) {
        if(0 == n)
            return;
        if(!buf_)
            n_throw(logic_error);
        
        for(const char *c = buf_; c < buf_+n; ++c)
            put(*c);
    }
    template <class S = Stream,
        _enable_if<has_write<S>>* = nullptr>
    inline void put(const char c) {
        array<char, 2> enc_ = encode<Codec>(c);
        io::write(this->adaptee(), enc_.data(), enc_.size());
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
        if(-1 != low)
        {
            buf_[i++] = low;
            low = -1;
            --n;
        }
        
        for( ; i+1 < n; i += 2)
        {
            ceof c = io::get(this->adaptee());
            if(c.eof())
                return i;
            auto r = encode<Codec>(c.get());
            buf_[i] = r[0];
            buf_[i+1] = r[1];
        }
        
        if(i < n)
        {
            ceof c = io::get(this->adaptee());
            if(c.eof())
                return i;
            auto r = encode<Codec>(c.get());
            low = r[1];
            buf_[i++] = r[0];
        }
        
        return i;
    }
    template <class S = Stream,
        _enable_if<has_read<S>>* = nullptr>
    inline ceof get()
    {
        if(-1 != low)
        {
            char r = low;
            low = -1;
            return r;
        }
        
        ceof c = io::get(this->adaptee());
        if(c.eof())
            return io::eof;
        auto r = encode<Codec>(c.get());
        low = r[1];
        return r[0];
    }
    
private:
    inline void on_adaptor_reset() noexcept {
        low = -1;
    }
    
    char low;
};

//------------------------------------------------------------------------------
template <class Codec>
struct enc_trigger {};
//------------------------------------------------------------------------------
template <class T, class Codec>
inline base16_enc<_remove_reference<T>, Codec>
operator | (T &&x, enc_trigger<Codec> y)
{
    return base16_enc<_remove_reference<T>, Codec>(foundation::forward<T>(x));
}

} // base16_detail

//------------------------------------------------------------------------------
inline base16_detail::enc_trigger<base16_detail::base16_digit_codec>
base16_enc()
{
    return base16_detail::enc_trigger<base16_detail::base16_digit_codec>{};
}

/** @} */

}}}} // namespaces

#endif // NIC_67C388C790958F1B_NIC
