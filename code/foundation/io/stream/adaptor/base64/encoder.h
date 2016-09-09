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
#ifndef NIC_4BEF439036FFFAC9_NIC
#define NIC_4BEF439036FFFAC9_NIC

#include "basic.h"
#include "../../stream.h"
#include "../../../../adaptor.h"
#include "../../../../enable_if.h"
#include "../../../../iterator.h"
#include "../../../../array.h"
#include "../../../../range.h"
#include "../../../../assert.h"

namespace nebula { namespace foundation { namespace io { namespace adaptor {
/** @ingroup Foundation
 * @{ 
 */
namespace base64_detail {
//------------------------------------------------------------------------------
template <class S, bool, bool>
struct base64_enc_data;
template<class S> struct base64_enc_data<S, true, true>
{
    inline base64_enc_data(const bool pad) noexcept
    : n_obuffer(0), ipos(0), n_ibuffer(0), padding(pad)
    {}
    
    inline void reset() noexcept {
        n_obuffer = ipos = n_ibuffer = 0;
    }
    
    array<unsigned char, 3> obuffer;
    S n_obuffer;
    array<char, 4> ibuffer;
    S ipos, n_ibuffer;
    bool padding;
};
template<class S> struct base64_enc_data<S, true, false>
{
    inline base64_enc_data(const bool pad) noexcept
    : n_obuffer(0), padding(pad)
    {}
    
    inline void reset() noexcept {
        n_obuffer = 0;
    }
    
    array<unsigned char, 3> obuffer;
    S n_obuffer;
    bool padding;
};
template<class S> struct base64_enc_data<S, false, true>
{
    inline base64_enc_data(const bool pad) noexcept
    : ipos(0), n_ibuffer(0), padding(pad)
    {}
    
    inline void reset() noexcept {
        ipos = n_ibuffer = 0;
    }
    
    array<char, 4> ibuffer;
    S ipos, n_ibuffer;
    bool padding;
};
//------------------------------------------------------------------------------
template <class Stream_, class Codec>
class base64_enc final :
    public adaptor_base<
        Stream_,
        base64_enc<Stream_, Codec>>
{   
    template <int> struct nil {};
    
    using Stream = typename adaptor_base<Stream_>::adaptee_type;
    using Base = adaptor_base<
        Stream_,
        base64_enc<Stream_, Codec>>;
    
public:
    using stream_size = _stream_size<Stream>;
    using stream_position = _stream_position<Stream>;
    using stream_offset = _stream_offset<Stream>;
    using stream_category = tag<
        meta::_if<has_write<Stream>, out_tag, nil<0>>,
        meta::_if<has_write<Stream>, flush_tag, nil<1>>,
        meta::_if<has_read<Stream>, in_tag, nil<2>>>;
    
    template <class S>
    base64_enc(S &&strm, const bool padding_)
    : Base(foundation::forward<S>(strm)),
      data(padding_)
    {}
    inline ~base64_enc() noexcept(false)
    {
        try { flush_(); }
        catch(...) {
            if(!this->nothrow_dtor())
                throw;
        }
    }
    
    template <class S = Stream,
        _enable_if<has_write<S>>* = nullptr>
    inline void write(const char *buf_, stream_size n) {
        if(0 == n)
            return;
        if(!buf_)
            n_throw(logic_error);
        
        const unsigned char *buf = static_cast<const unsigned char *>(
            static_cast<const void *>(buf_));
        
        if(data.n_obuffer)
        {
            stream_size delta = 3 - data.n_obuffer;
            if(delta <= n)
            {
                iterator::copy(buf, buf + delta,
                    data.obuffer.begin() + data.n_obuffer);
                auto r = encode<Codec>(data.obuffer[0], data.obuffer[1],
                    data.obuffer[2]);
                io::write(this->adaptee(), r.data(), r.size());
                n -= delta;
                buf += delta;
                data.n_obuffer = 0;
            }
            else
            {
                data.obuffer[1] = *buf;
                ++data.n_obuffer;
                return;
            }
        }
        if(n)
        {
            data.n_obuffer = n % 3;
            buf = write_full(buf, n);
            iterator::copy(buf, buf+data.n_obuffer, data.obuffer.begin());
        }
    }
    template <class S = Stream,
        _enable_if<has_write<S>>* = nullptr>
    inline void put(const char c) {
        if(data.n_obuffer < 2)
            data.obuffer[data.n_obuffer++] = c;
        else
        {
            data.obuffer[2] = c;
            auto r = encode<Codec>(data.obuffer[0], data.obuffer[1],
                data.obuffer[2]);
            io::write(this->adaptee(), r.data(), r.size());
            data.n_obuffer = 0;
        }
    }
    
    template <class S = Stream,
        _enable_if<meta::and_<has_write<S>, has_flush<S>>>* = nullptr>
    inline void flush() {
        flush_();
        io::flush(this->adaptee());
    }
    template <class S = Stream,
        _enable_if<meta::and_<has_write<S>,
            meta::not_<has_flush<S>>>>* = nullptr>
    inline void flush() {
        flush_();
    }
    
    template <class S = Stream,
        _enable_if<has_read<S>>* = nullptr>
    inline stream_size read(char *buf_, const stream_size n)
    {
        if(0 == n)
            return 0;
        if(!buf_)
            n_throw(logic_error);
        
        stream_size m = 0;
        
        if(data.n_ibuffer)
        {
            if(data.n_ibuffer - data.ipos <= n)
            {
                iterator::copy(
                    data.ibuffer.begin() + data.ipos,
                    data.ibuffer.end(),
                    buf_);
                m = data.n_ibuffer - data.ipos;
                data.n_ibuffer = data.ipos = 0;
            }
            else
            {
                iterator::copy(
                    data.ibuffer.begin() + data.ipos,
                    data.ibuffer.begin() + data.ipos+n,
                    buf_);
                data.ipos += n;
                return n;
            }
        }
        
        while(m+3 < n)
        {
            stream_size l = load(buf_+m);
            m += l;
            if(l < 4)
                return m;
        }
        
        if(m < n)
        {
            load();
            if(data.n_ibuffer)
            {
                if(data.n_ibuffer - data.ipos <= (n-m))
                {
                    iterator::copy(
                        data.ibuffer.begin() + data.ipos,
                        data.ibuffer.end(),
                        buf_+m);
                    m += data.n_ibuffer - data.ipos;
                    data.n_ibuffer = data.ipos = 0;
                    return m;
                }
                else
                {
                    iterator::copy(data.ibuffer.begin()+data.ipos,
                        data.ibuffer.begin()+data.ipos+(n-m),
                        buf_+m);
                    data.ipos += (n-m);
                    return n;
                }
            }
            else
                return m;
        }
        
        return n;
    }
    template <class S = Stream,
        _enable_if<has_read<S>>* = nullptr>
    inline ceof get()
    {
        if(data.ipos == data.n_ibuffer)
            load();
        if(0 == data.n_ibuffer)
            return io::eof;
        return data.ibuffer[data.ipos++];
    }
    
private:
    template <class S = Stream,
        _enable_if<has_write<S>>* = nullptr>
    inline const unsigned char *write_full(
        const unsigned char *buf, const stream_size n)
    {
        stream_size i = 0;
        for( ; i+2 < n; i += 3)
        {
            auto r = encode<Codec>(buf[i], buf[i+1], buf[i+2]);
            io::write(this->adaptee(), r.data(), r.size());
        }
        return buf + i;
    }
    template <class S = Stream,
        _enable_if<has_write<S>>* = nullptr>
    inline void flush_()
    {
        switch(data.n_obuffer)
        {
        case 2:
            {
                auto r = encode<Codec>(data.obuffer[0], data.obuffer[1]);
                io::write(this->adaptee(), r.data(), r.size());
                
                if(data.padding)
                    io::put(this->adaptee(), '=');
                
                data.n_obuffer = 0;
            }
            break;
        case 1:
            {
                auto r = encode<Codec>(data.obuffer[0]);
                io::write(this->adaptee(), r.data(), r.size());
                
                if(data.padding)
                    io::write(this->adaptee(), "==", 2);
                
                data.n_obuffer = 0;
            }
            break;
        default:
            break;
        }
    }
    template <class S = Stream,
        _disable_if<has_write<S>>* = nullptr>
    inline void flush_() const noexcept {
        // empty
    }
    
    template <class S = Stream,
        _enable_if<has_read<S>>* = nullptr>
    stream_size load(char *buf_)
    {
        n_assert(buf_);
        
        array<char, 3> buf;
        stream_size n = io::read(this->adaptee(), buf.data(), buf.size());
        
        switch(n)
        {
        case 1:
            {
                auto r = encode<Codec>(buf[0]);
                range::copy(r, buf_);
                if(data.padding)
                {
                    buf_[2] = buf_[3] = '=';
                    return 4;
                }
                else
                    return 2;
            }
        case 2:
            {
                auto r = encode<Codec>(buf[0], buf[1]);
                range::copy(r, buf_);
                if(data.padding)
                {
                    buf_[3] = '=';
                    return 4;
                }
                else
                    return 3;
            }
        case 3:
            {
                auto r = encode<Codec>(buf[0], buf[1], buf[2]);
                range::copy(r, buf_);
            }
            return 4;
        default:
            return 0;
        }
    }
    template <class S = Stream,
        _enable_if<has_read<S>>* = nullptr>
    inline void load()
    {
        data.n_ibuffer = load(data.ibuffer.data());
        data.ipos = 0;
    }
    inline void on_adaptor_reset() noexcept {
        data.reset();
    }
    
    base64_enc_data<stream_size,
        has_write<Stream>::type::value,
        has_read<Stream>::type::value> data;
};

//------------------------------------------------------------------------------
template <class Codec>
struct enc_trigger {
    bool padding;
};
//------------------------------------------------------------------------------
template <class T, class Codec>
inline base64_enc<_remove_reference<T>, Codec>
operator | (T &&x, enc_trigger<Codec> y)
{
    return base64_enc<_remove_reference<T>, Codec>(
        foundation::forward<T>(x),
        y.padding);
}

} // base64_detail

//------------------------------------------------------------------------------
inline base64_detail::enc_trigger<base64_detail::base64_digit_codec>
base64_enc(const bool padding = false)
{
    return base64_detail::enc_trigger<base64_detail::base64_digit_codec>{
        padding};
}
//------------------------------------------------------------------------------
inline base64_detail::enc_trigger<base64_detail::base64url_digit_codec>
base64url_enc(const bool padding = false)
{
    return base64_detail::enc_trigger<base64_detail::base64url_digit_codec>{
        padding};
}

/** @} */

}}}} // namespaces

#endif // NIC_4BEF439036FFFAC9_NIC
