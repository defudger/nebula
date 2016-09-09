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
#ifndef NIC_824C39C06C4CB58D_NIC
#define NIC_824C39C06C4CB58D_NIC

#include "gcrypt_error.h"

namespace nebula { namespace crypt { namespace detail { namespace gcrypt {
/** @ingroup Crypt
 * @{
 * */
//------------------------------------------------------------------------------
class n_crypt_dll hash : public io::stream_base
{
public:
    using stream_size = io::streamsize;
    using stream_offset = io::streamoff;
    using stream_position = io::streampos;
    using stream_category = fnd::tag<io::out_tag>;
    
    inline hash() noexcept
    : h(nullptr)
    {}
    hash(hash &other) = delete;
    hash(const hash &other) = delete;
    inline hash(hash &&other) noexcept
    : h(other.h)
    {
        other.h = nullptr;
    }
    
    hash(const int algo, const bool secure);
    
    inline ~hash() noexcept {
        kill();
    }
    
    hash &operator = (hash &other) = delete;
    hash &operator = (const hash &other) = delete;
    inline hash &operator = (hash &&other) noexcept {
        kill();
        h = other.h;
        other.h = nullptr;
        return *this;
    }
    
    inline void swap(hash &other) noexcept {
        fnd::swap(h, other.h);
    }

    inline gcry_md_hd_t native_handle() const noexcept {
        return h;
    }
    inline gcry_md_hd_t dismiss() noexcept {
        gcry_md_hd_t tmp = h;
        h = nullptr;
        return tmp;
    }
    
    void write(const char *buf, const stream_size n);
    inline void put(char c) {
        write(&c, 1);
    }
    void result(char *buf, const size_t n);
    
    void reset() noexcept;
    
private:
    void kill() noexcept;
    
    gcry_md_hd_t h;
};

/** @} */

}}}} // namespaces

#endif // NIC_824C39C06C4CB58D_NIC

