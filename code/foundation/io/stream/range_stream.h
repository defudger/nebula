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
#ifndef NIC_60D8309FC7573CAB_NIC
#define NIC_60D8309FC7573CAB_NIC

#include "stream.h"
#include "../../iterator.h"
#include "../../range/common.h"
#include "../../declval.h"

namespace nebula { namespace foundation { namespace io {
/** @ingroup Foundation
 * @{ 
 */
//------------------------------------------------------------------------------
/** Range to stream adaptor.
 * */
template <class Range>
class range_stream final :
    public stream_base,
    public adaptor_base<Range, range_stream<Range>>
{
    using range_ = _remove_const<Range>;
    using iter_ = range::_range_iterator<Range>;
    using wable_ = has_tag<iterator::_iterator_access<iter_>,
        iterator::writable_iterator_tag>;
    using bidir_ = has_tag<range::_range_traversal<range_>,
        range::bidirectional_traversal_tag>;
    
    n_static_assert(n_arg(
        has_tag<range::_range_traversal<range_>,
        range::forward_traversal_tag>::type::value),
        "Forward - Range required.");
    
public:
    using range_type = Range;
    
    using stream_size = streamsize;
    using stream_offset = streamoff;
    using stream_position = streampos;
    using stream_category =
        meta::_if<
            wable_,
            meta::_if<
                has_tag<range::_range_traversal<range_>,
                    range::bidirectional_traversal_tag>,
                tag<out_tag,
                    in_tag,
                    peek_tag,
                    unget_tag,
                    in_seek_tag,
                    direct_tag>,
                tag<out_tag,
                    in_tag,
                    peek_tag,
                    direct_tag>>,
            meta::_if<
                has_tag<range::_range_traversal<range_>,
                    range::bidirectional_traversal_tag>,
                tag<in_tag,
                    peek_tag,
                    unget_tag,
                    in_seek_tag,
                    direct_tag>,
                tag<in_tag,
                    peek_tag,
                    direct_tag>>>;
    
    range_stream() = delete;
    range_stream(range_stream &) = default;
    range_stream(const range_stream &) = default;
    range_stream(range_stream &&) = default;
    
    template <class R_>
    inline range_stream(R_ &&r)
    : adaptor_base<Range, range_stream<Range>>(foundation::forward<R_>(r)),
        pos(range::begin(r))
    {}
    
    range_stream &operator = (range_stream &) = default;
    range_stream &operator = (const range_stream &) = default;
    range_stream &operator = (range_stream &&) = default;
    
    inline void reset() noexcept {
        pos = range::begin(this->adaptee());
    }
    
    template <class Cond = wable_, _enable_if<wable_>* = nullptr>
    inline void write(const char *x, stream_size n) {
        const stream_size delta = iterator::distance(
            pos, range::end(this->adaptee()));
        if(n > delta)
            n_throw(io_error, out_of_range);
        iterator::copy(x, x+n, pos);
        iterator::advance(pos, n);
    }
    template <class Cond = wable_, _enable_if<wable_>* = nullptr>
    inline void put(char c_) {
        if(pos == range::end(this->adaptee()))
            n_throw(io_error, out_of_range);
        *pos++ = c_;
    }
    
    inline stream_size read(char *x, stream_size n) {
        const stream_size delta = iterator::distance(
            pos, range::end(this->adaptee()));
        if(delta < n)
        {
            iterator::copy(pos, range::end(this->adaptee()), x);
            pos = range::end(this->adaptee());
            return delta;
        }
        
        iterator::copy(pos, pos+n, x);
        iterator::advance(pos, n);
        return n;
    }
    inline ceof peek() {
        if(pos != range::end(this->adaptee()))
        {
            range::_range_iterator<range_type> nxt
                = iterator::advanced(pos, 1);
            if(nxt != range::end(this->adaptee()))
                return *nxt;
        }
        return io::eof;
    }
    inline ceof get() {
        if(pos != range::end(this->adaptee()))
            return *pos++;
        return io::eof;
    }
    template <class Cond = bidir_, _enable_if<wable_>* = nullptr>
    inline void unget() {
        if(pos != range::begin(this->adaptee()))
            --pos;
        else
            n_throw(io_error);
    }
    
    template <class Cond = bidir_, _enable_if<wable_>* = nullptr>
    inline void seekg_beg(const stream_offset off) {
        if(off < stream_offset(0))
            n_throw(logic_error);
        pos = stream_size(off) > range::size(this->adaptee()) ?
            range::end(this->adaptee())
            : iterator::advanced(range::begin(this->adaptee()), off);
    }
    template <class Cond = bidir_, _enable_if<wable_>* = nullptr>
    inline void seekg_cur(const stream_offset off) {
        const stream_offset boff = iterator::distance(
            range::begin(this->adaptee()), pos)
            + off;
        seekg_beg(boff);
    }
    template <class Cond = bidir_, _enable_if<wable_>* = nullptr>
    inline void seekg_end(const stream_offset off) {
        const stream_offset boff = iterator::distance(
            range::begin(this->adaptee()), range::end(this->adaptee()))
            + off;
        seekg_beg(boff);
    }
    
    template <class Cond = bidir_, _enable_if<wable_>* = nullptr>
    inline stream_position tellg() const {
        return iterator::distance(range::begin(this->adaptee()),
            range::_range_iterator<const range_type>(pos));
    }
    
    template <class Cond = meta::_and<bidir_, wable_>,
        _enable_if<wable_>* = nullptr>
    inline void seekp_beg(const stream_offset off) {
        seekg_beg(off);
    }
    template <class Cond = meta::_and<bidir_, wable_>,
        _enable_if<wable_>* = nullptr>
    inline void seekp_cur(const stream_offset off) {
        seekg_cur(off);
    }
    template <class Cond = meta::_and<bidir_, wable_>,
        _enable_if<wable_>* = nullptr>
    inline void seekp_end(const stream_offset off) {
        seekg_end(off);
    }
    
    template <class Cond = meta::_and<bidir_, wable_>,
        _enable_if<wable_>* = nullptr>
    inline stream_position tellp() const {
        return tellg();
    }
    
private:
    inline void on_adaptor_reset() noexcept {
        pos = range::begin(this->adaptee());
    }
    
    range::_range_iterator<Range> pos;
};

//------------------------------------------------------------------------------
template <class Range>
inline range_stream<_remove_reference<Range>> make_range_stream(Range &&r)
{
    return range_stream<_remove_reference<Range>>(
        foundation::forward<Range>(r));
}

/** @} */

}}} // namespaces

#endif // NIC_60D8309FC7573CAB_NIC
