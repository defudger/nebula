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
#ifndef NIC_C0D6FEC0E7D00F32_NIC
#define NIC_C0D6FEC0E7D00F32_NIC

#include "stream.h"
#include "../../call_traits.h"
#include "../../tuple.h"
#include "../../math/exact_cast.h"

namespace nebula { namespace foundation { namespace io {
/** @ingroup Foundation
 * @{ 
 */
namespace tee_detail {
//------------------------------------------------------------------------------
template <class ... Streams>
class tee_stream final : io::stream_base
{
    template <int> struct nil {};
    
    using has_write_ = meta::_and<io::has_write<ctraits::_value<Streams>>...>;
    using has_flush_ = meta::_and<io::has_flush<ctraits::_value<Streams>>...>;
    using has_sync_ = meta::_and<io::has_sync<ctraits::_value<Streams>>...>;
    using is_direct_ = meta::_and<io::is_direct<ctraits::_value<Streams>>...>;
    
    using has_seekp_beg_ = meta::_and<
        io::has_seekp_beg<ctraits::_value<Streams>>...>;
    using has_seekp_cur_ = meta::_and<
        io::has_seekp_cur<ctraits::_value<Streams>>...>;
    using has_seekp_end_ = meta::_and<
        io::has_seekp_end<ctraits::_value<Streams>>...>;
    
    n_static_assert(has_write_::type::value, "");
    
public:
    using stream_size = streamsize;
    using stream_offset = streamoff;
    using stream_position = streampos;
    using stream_category = tag<out_tag,
        meta::_if<has_flush_, io::flush_tag, nil<0>>,
        meta::_if<has_sync_, io::sync_tag, nil<1>>,
        meta::_if<is_direct_, io::direct_tag, nil<2>>,
        meta::_if<has_seekp_beg_, io::out_seek_beg_tag, nil<3>>,
        meta::_if<has_seekp_cur_, io::out_seek_cur_tag, nil<4>>,
        meta::_if<has_seekp_end_, io::out_seek_end_tag, nil<5>>>;
    
    tee_stream(tee_stream &) = delete;
    tee_stream(const tee_stream &) = delete;
    tee_stream(tee_stream &&) = default;
    
    template <class ... S>
    inline tee_stream(S && ... s)
    : streams(foundation::forward<S>(s) ...)
    {}
    
    tee_stream &operator = (tee_stream &) = delete;
    tee_stream &operator = (const tee_stream &) = delete;
    tee_stream &operator = (tee_stream &&) = default;
    
    inline void write(const char *buf, const stream_size n)
    {
        auto f = [&] (auto &strm) -> bool {
            using S = _stream_size<ctraits::_value<decltype(strm)>>;
            math::require_exact_cast<S>(n);
            io::write(strm, buf, n);
            return true;
        };
        tuple_for_each(streams, f);
    }
    inline void put(char c)
    {
        auto f = [&] (auto &strm) -> bool {
            io::put(strm, c);
            return true;
        };
        tuple_for_each(streams, f);
    }
    template <class Cond = has_flush_,
        _enable_if<Cond>* = nullptr>
    inline void flush()
    {
        auto f = [] (auto &strm) -> bool {
            io::flush(strm);
            return true;
        };
        tuple_for_each(streams, f);
    }
    template <class Cond = has_sync_,
        _enable_if<Cond>* = nullptr>
    inline void sync()
    {
        auto f = [] (auto &strm) -> bool {
            io::sync(strm);
            return true;
        };
        tuple_for_each(streams, f);
    }
    
    template <class Cond = has_seekp_beg_,
        _enable_if<Cond>* = nullptr>
    inline void seekp_beg(stream_offset off)
    {
        auto f = [&] (auto &strm) -> bool {
            using S = _stream_offset<ctraits::_value<decltype(strm)>>;
            math::require_exact_cast<S>(off);
            io::seekp_beg(strm, off);
            return true;
        };
        tuple_for_each(streams, f);
    }
    template <class Cond = has_seekp_cur_,
        _enable_if<Cond>* = nullptr>
    inline void seekp_cur(stream_offset off)
    {
        auto f = [&] (auto &strm) -> bool {
            using S = _stream_offset<ctraits::_value<decltype(strm)>>;
            math::require_exact_cast<S>(off);
            io::seekp_cur(strm, off);
            return true;
        };
        tuple_for_each(streams, f);
    }
    template <class Cond = has_seekp_end_,
        _enable_if<Cond>* = nullptr>
    inline void seekp_end(stream_offset off)
    {
        auto f = [&] (auto &strm) -> bool {
            using S = _stream_offset<ctraits::_value<decltype(strm)>>;
            math::require_exact_cast<S>(off);
            io::seekp_end(strm, off);
            return true;
        };
        tuple_for_each(streams, f);
    }

private:
    tuple<Streams...> streams;
};

} // tee_detail

//------------------------------------------------------------------------------
template <class ... Streams>
inline tee_detail::tee_stream<Streams...> tee(
    Streams && ... streams)
{
    return tee_detail::tee_stream<Streams...>(
        foundation::forward<Streams>(streams) ...);
}

/** @} */

}}} // namespaces

#endif // NIC_C0D6FEC0E7D00F32_NIC
