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
#ifndef NIC_D2F74682467412D3_NIC
#define NIC_D2F74682467412D3_NIC

#include "basic.h"
#include "../../stream.h"
#include "../../../../adaptor.h"
#include "../../../../enable_if.h"
#include "../../../../range.h"
#include "../../../../array.h"
#include "../../../../assert.h"

namespace nebula { namespace foundation { namespace io { namespace adaptor {
/** @ingroup Foundation
 * @{ 
 */
namespace base64_detail {
//------------------------------------------------------------------------------
template <class S, bool, bool>
struct base64_dec_data;
template<class S> struct base64_dec_data<S, true, true>
{
    inline base64_dec_data() noexcept
    : n_obuffer(0), ipos(0), n_ibuffer(0)
    {}
    
    inline void reset() noexcept {
        n_obuffer = ipos = n_ibuffer = 0;
    }
    
    array<char, 4> obuffer;
    S n_obuffer;
    array<char, 3> ibuffer;
    S ipos, n_ibuffer;
};
template<class S> struct base64_dec_data<S, true, false>
{
    inline base64_dec_data() noexcept
    : n_obuffer(0)
    {}
    
    inline void reset() noexcept {
        n_obuffer = 0;
    }
    
    array<char, 4> obuffer;
    S n_obuffer;
};
template<class S> struct base64_dec_data<S, false, true>
{
    inline base64_dec_data() noexcept
    : ipos(0), n_ibuffer(0)
    {}
    
    inline void reset() noexcept {
        ipos = n_ibuffer = 0;
    }
    
    array<char, 3> ibuffer;
    S ipos, n_ibuffer;
};
//------------------------------------------------------------------------------
template <class Stream_>
class base64_dec final :
     public adaptor_base<
        Stream_,
        base64_dec<Stream_>>
{
    template <int> struct nil {};
    
    using Stream = typename adaptor_base<Stream_>::adaptee_type;
    using Base = adaptor_base<
        Stream_,
        base64_dec<Stream_>>;
    
public:
    using stream_size = _stream_size<Stream>;
    using stream_position = _stream_position<Stream>;
    using stream_offset = _stream_offset<Stream>;
    using stream_category = tag<
        meta::_if<has_write<Stream>, out_tag, nil<0>>,
        meta::_if<has_write<Stream>, flush_tag, nil<1>>,
        meta::_if<has_read<Stream>, in_tag, nil<2>>>;
    
    template <class S>
    base64_dec(S &&strm)
    : Base(foundation::forward<S>(strm))
    {}
    
    inline ~base64_dec() noexcept(false)
    {
        try { flush_(); }
        catch(...) {
            if(!this->nothrow_dtor())
                throw;
        }
    }
    
    template <class S = Stream,
        _enable_if<has_write<S>>* = nullptr>
    inline void write(const char *buf, stream_size n) {
        if(0 == n)
            return;
        if(!buf)
            n_throw(logic_error);
        
        stream_size i = 0;
        
        while(true)
        {
            if(i == n)
                return;
            char u = decode_digit(buf[i++]);
            
            while(-1 == u)
            {
                if(i == n)
                    return;
                u = decode_digit(buf[i++]);
            }
            
            data.obuffer[data.n_obuffer++] = u;
            
            if(4 == data.n_obuffer)
            {
                auto r = decode(data.obuffer[0], data.obuffer[1],
                    data.obuffer[2], data.obuffer[3]);
                io::write(this->adaptee(), r.data(), r.size());
                data.n_obuffer = 0;
            }
        }
    }
    template <class S = Stream,
        _enable_if<has_write<S>>* = nullptr>
    inline void put(const char c_) {
        const char c = decode_digit(c_);
        if(-1 == c)
            return;
        if(3 == data.n_obuffer)
        {
            data.obuffer[3] = c;
            auto r = decode(data.obuffer[0], data.obuffer[1],
                data.obuffer[2], data.obuffer[3]);
            io::write(this->adaptee(), r.data(), r.size());
            data.n_obuffer = 0;
        }
        else
        {
            data.obuffer[data.n_obuffer++] = c;
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
    inline stream_size read(char *x, const stream_size n) {
        if(0 == n)
            return 0;
        if(!x)
            n_throw(logic_error);
        
        size_t m = 0;
        if(data.ipos < data.n_ibuffer)
        {
            if(data.n_ibuffer - data.ipos <= n)
            {
                iterator::copy(
                    data.ibuffer.begin() + data.ipos, 
                    data.ibuffer.begin() + data.n_ibuffer,
                    x);
                m += data.n_ibuffer - data.ipos;
                data.n_ibuffer = data.ipos = 0;
            }
            else
            {
                *x = data.ibuffer[data.ipos++];
                data.ipos += 1;
                return 1;
            }
        }
        while(m+3 < n)
        {
            stream_size r = load(x+m);
            if(r != 3)
                return m + r;
            m += 3;
        }
        if(m < n)
        {
            load();
            
            switch(data.n_ibuffer)
            {
            case 0: return m;
            case 1:
                x[m++] = data.ibuffer[0];
                data.ipos = data.n_ibuffer = 0;
                return m;
            case 2:
                if(n-m == 1)
                {
                    x[m] = data.ibuffer[0];
                    data.ipos = 1;
                }
                else
                {
                    x[m++] = data.ibuffer[0];
                    x[m] = data.ibuffer[1];
                    data.ipos = data.n_ibuffer = 0;
                }
                return n;
            case 3:
                if(n-m == 1)
                {
                    x[m] = data.ibuffer[0];
                    data.ipos = 1;
                }
                else
                {
                    x[m++] = data.ibuffer[0];
                    x[m] = data.ibuffer[1];
                    data.ipos = 2;
                }
                return n;
            default:
                n_throw(logic_error);
            }
        }
    }
    template <class S = Stream,
        _enable_if<has_read<S>>* = nullptr>
    inline ceof get() {
        if(data.ipos == data.n_ibuffer)
            load();
        if(0 == data.n_ibuffer)
            return eof;
        return data.ibuffer[data.ipos++];
    }
    
private:
    template <class S = Stream,
        _enable_if<has_write<S>>* = nullptr>
    inline void flush_()
    {
        switch(data.n_obuffer)
        {
        case 2:
            {
                io::put(this->adaptee(),
                    decode(data.obuffer[0], data.obuffer[1]));
                data.n_obuffer = 0;
            }
            break;
        case 3:
            {
                auto r = decode(data.obuffer[0], data.obuffer[1],
                    data.obuffer[2]);
                io::write(this->adaptee(), r.data(), r.size());
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
    stream_size load(char *buffer)
    {
        n_assert(buffer);
        
        char q[4];
        unsigned k = 0;
        
        while(true)
        {
            unsigned u;
            do
            {
                ceof c_ = io::get(this->adaptee());
                if(c_.eof())
                {
                    switch(k)
                    {
                    case 2:
                        buffer[0] = decode(q[0], q[1]);
                        return 1;
                    case 3:
                        {
                            auto r = decode(q[0], q[1], q[2]);
                            range::copy(r, buffer);
                        }
                        return 2;
                    default:
                        return 0;
                    }
                }
                unsigned char c = c_.get();
                u = decode_digit(c);
            }
            while(unsigned(-1) == u);
            
            q[k++] = static_cast<char>(u);
            
            if(k == 4)
            {
                k = 0;
                auto r = decode(q[0], q[1], q[2], q[3]);
                range::copy(r, buffer);
                return 3;
            }
        }
    }
    template <class S = Stream,
        _enable_if<has_read<S>>* = nullptr>
    void load()
    {
        data.n_ibuffer = load(data.ibuffer.data());
        data.ipos = 0;
    }
    inline void on_adaptor_reset() noexcept {
        data.reset();
    }
    
    base64_dec_data<stream_size,
        has_write<Stream>::type::value,
        has_read<Stream>::type::value> data;
};

//------------------------------------------------------------------------------
struct dec_trigger {};
//------------------------------------------------------------------------------
template <class T>
inline base64_dec<_remove_reference<T>>
operator | (T &&x, dec_trigger y)
{
    return base64_dec<_remove_reference<T>>(foundation::forward<T>(x));
}

} // base64_detail

//------------------------------------------------------------------------------
inline base64_detail::dec_trigger base64_dec()
{
    return base64_detail::dec_trigger{};
}

/** @} */

}}}} // namespaces

#endif // NIC_D2F74682467412D3_NIC
