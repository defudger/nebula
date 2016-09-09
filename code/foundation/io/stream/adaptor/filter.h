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
#ifndef NIC_351220C5D04D36D3_NIC
#define NIC_351220C5D04D36D3_NIC

#include "../stream.h"
#include "../../../call_traits.h"
#include "../../../adaptor.h"

namespace nebula { namespace foundation { namespace io { namespace adaptor {
/** @ingroup Foundation
 * @{ 
 */
namespace filter_detail {
//------------------------------------------------------------------------------
template <class Stream_, class F>
class filtered_stream final : public adaptor_base<Stream_>
{
    template <int> struct nil {};
    
    using Stream = typename adaptor_base<Stream_>::adaptee_type;
    
public:
    using stream_size = _stream_size<Stream>;
    using stream_position = _stream_position<Stream>;
    using stream_offset = _stream_offset<Stream>;
    using stream_category = tag<
        meta::_if<has_write<Stream>, io::out_tag, nil<0>>,
        meta::_if<has_read<Stream>, io::in_tag, nil<1>>,
        meta::_if<has_flush<Stream>, io::flush_tag, nil<2>>,
        meta::_if<has_sync<Stream>, io::sync_tag, nil<3>>,
        meta::_if<is_direct<Stream>, io::direct_tag, nil<4>>>;
    
    template <class S, class F_>
    filtered_stream(S &&strm, F_ &&f_)
    : adaptor_base<Stream_>(foundation::forward<S>(strm)),
        f(foundation::forward<F_>(f_))
    {}
    
    template <class Cond = has_write<Stream>,
        _enable_if<Cond>* = nullptr>
    inline void write(const char *x, const stream_size n) {
        for(const char *i = x; i < x+n; ++i)
            put(*i);
    }
    template <class Cond = has_write<Stream>,
        _enable_if<Cond>* = nullptr>
    inline void put(const char c) {
        if(f(c))
            io::put(this->adaptee(), c);
    }
    
    template <class Cond = has_read<Stream>,
        _enable_if<Cond>* = nullptr>
    inline stream_size read(char *x, const stream_size n) {
        stream_size m = 0;
        for(stream_size i = 0; i < n; ++i)
        {
            ceof c = get();
            if(c.eof())
                return m;
            x[i] = c.get();
            ++m;
        }
    }
    template <class Cond = has_read<Stream>,
        _enable_if<Cond>* = nullptr>
    inline ceof get() {
        while(true) {
            ceof c = io::get(this->adaptee());
            if(c.eof())
                return c;
            if(f(c.get()))
                return c;
        }
    }
    
    template <class Cond = has_flush<Stream>,
        _enable_if<Cond>* = nullptr>
    inline void flush() {
        io::flush(this->adaptee());
    }
    template <class Cond = has_sync<Stream>,
        _enable_if<Cond>* = nullptr>
    inline void sync() {
        io::sync(this->adaptee());
    }
    
private:
    F f;
};

//------------------------------------------------------------------------------
template <class F>
struct trigger {
    F f;
};
//------------------------------------------------------------------------------
template <class T, class F>
inline filtered_stream<_remove_reference<T>, ctraits::_value<F>>
operator | (T &&x, trigger<F> y)
{
    return filtered_stream<_remove_reference<T>, ctraits::_value<F>>(
        foundation::forward<T>(x),
        foundation::move(y.f));
}

} // filter_detail

//------------------------------------------------------------------------------
template <class F>
inline filter_detail::trigger<ctraits::_value<F>> filter(
    F &&f)
{
    return filter_detail::trigger<ctraits::_value<F>>{
        foundation::forward<F>(f)};
}

/** @} */

}}}} // namespaces

#endif // NIC_351220C5D04D36D3_NIC
