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
#ifndef NIC_0C1E61EDBF2C7230_NIC
#define NIC_0C1E61EDBF2C7230_NIC

#include "secure_allocator.h"

namespace nebula { namespace crypt { namespace detail {
/** @ingroup Crypt
 * @{
 * */
//------------------------------------------------------------------------------
template <size_t N, class Secure, class Tag = void>
class buffer
{
    using container_t = meta::_if<Secure,
        fnd::dynamic_array<char, N, secure_allocator<char>>,
        meta::_if< meta::bool_<N <= buffer_static_limit_::value>,
            fnd::array<char, N>,
            fnd::dynamic_array<char, N>>>;
    
public:
    using value_type = range::_range_value<container_t>;
    using reference = range::_range_reference<container_t>;
    using const_reference = range::_range_reference<const container_t>;
    using pointer = range::_range_pointer<container_t>;
    using const_pointer = range::_range_pointer<const container_t>;
    using size_type = range::_range_size<container_t>;
    using difference_type = range::_range_difference<container_t>;
    
    using iterator = range::_range_iterator<container_t>;
    using const_iterator = range::_range_iterator<const container_t>;
    using reverse_iterator = range::_range_reverse_iterator<container_t>;
    using const_reverse_iterator = range::_range_reverse_iterator<
        const container_t>;
    
    using secure = Secure;
    
    buffer() = default;
    buffer(buffer &) = default;
    buffer(const buffer &) = default;
    buffer(buffer &&) = default;
    
    template <class I>
    inline buffer(I beg, I end)
    {
        if(iterator::distance(beg, end) != size())
            n_throw(out_of_range);
        iterator::copy(beg, end, begin());
    }
    
    buffer &operator = (buffer &) = default;
    buffer &operator = (const buffer &) = default;
    buffer &operator = (buffer &&) = default;
    
    inline void swap(buffer &other) noexcept {
        fnd::swap(c, other.c);
    }
    
    template <class I>
    inline buffer &assign(I beg, I end)
    {
        if(iterator::distance(beg, end) != size())
            n_throw(out_of_range);
        iterator::copy(beg, end, begin());
        return *this;
    }
    template <class Range>
    inline buffer &assign(const Range &r)
    {
        if(range::size(r) != size())
            n_throw(out_of_range);
        range::copy(r, begin());
        return *this;
    }
    
    inline iterator begin() noexcept { return range::begin(c); }
    inline iterator end() noexcept { return range::end(c); }
    inline const_iterator begin() const noexcept { return range::begin(c); }
    inline const_iterator end() const noexcept { return range::end(c); }
    inline const_iterator cbegin() const noexcept { return range::begin(c); }
    inline const_iterator cend() const noexcept { return range::end(c); }
    
    inline reverse_iterator rbegin() noexcept { 
        return range::rbegin(c);
    }
    inline reverse_iterator rend() noexcept { 
        return range::rend(c);
    }
    inline const_reverse_iterator rbegin() const noexcept { 
        return range::rbegin(c);
    }
    inline const_reverse_iterator rend() const noexcept { 
        return range::rend(c);
    }
    inline const_reverse_iterator crbegin() const noexcept { 
        return range::rbegin(c);
    }
    inline const_reverse_iterator crend() const noexcept { 
        return range::rend(c);
    }
    
    inline pointer data() noexcept { return c.data(); }
    inline const_pointer data() const noexcept { return c.data(); }
    
    inline reference front() { return range::front(c); }
    inline constexpr const_reference front() const { return range::front(c); }
    inline reference back() { return range::back(c); }
    inline constexpr const_reference back() const { return range::back(c); }
    
    inline constexpr size_t size() const noexcept { return range::size(c); }
    inline constexpr size_t max_size() const noexcept { return c.max_size(); }
    inline constexpr bool empty() const noexcept { return range::empty(c); }
    
    inline constexpr const_reference operator [] (const size_type i) const {
        return begin()[i];
    }
    inline reference operator [] (const size_type i) {
        return begin()[i];
    }
    inline const_reference at(const size_type i) const {
        if(i >= size())
            n_throw(out_of_range);
        return begin()[i];
    }
    inline reference at(const size_type i) {
        if(i >= size())
            n_throw(out_of_range);
        return begin()[i];
    }
    
    inline void fill(const value_type &x) noexcept {
        iterator::fill(begin(), end(), x);
    }
    template <class C = Secure,
        fnd::_enable_if<C>* = nullptr>
    inline void zero() noexcept {
        fnd::scrub_s(begin(), size());
    }
    template <class C = Secure,
        fnd::_disable_if<C>* = nullptr>
    inline void zero() noexcept {
        iterator::fill(begin(), end(), 0);
    }
    
    inline bool operator == (const buffer &other) const noexcept {
        return c == other.c;
    }
    inline bool operator != (const buffer &other) const noexcept {
        return c != other.c;
    }
    inline bool operator < (const buffer &other) const noexcept {
        return c < other.c;
    }
    inline bool operator <= (const buffer &other) const noexcept {
        return c <= other.c;
    }
    inline bool operator > (const buffer &other) const noexcept {
        return c > other.c;
    }
    inline bool operator >= (const buffer &other) const noexcept {
        return c >= other.c;
    }
    
    template <class Stream>
    inline void operator () (Stream &&s, fmt::fout_tag) const
    {
        fmt::fwrite(s, fmt::base64(data(), size()));
    }

private:
    container_t c;
};

/** @} */

}}} // namespaces

#endif // NIC_0C1E61EDBF2C7230_NIC

