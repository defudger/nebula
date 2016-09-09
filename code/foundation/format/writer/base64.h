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
#ifndef NIC_D305D5041316DFC9_NIC
#define NIC_D305D5041316DFC9_NIC

#include "../fwrite.h"
#include "../../io/stream/adaptor/base64.h"
#include "../../io/stream/adaptor/nth.h"

namespace nebula { namespace foundation { namespace fmt {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
/** Simple base64 encoder.
 *
 *  This does not wrap lines and it outputs padding characters.
 *
 *  @see base64_ex
 * */
class base64
{
public:
    /** Constructor
     *
     *  @param buf_ The input data which must be null-terminated.
     * */
    inline base64(const char *buf_) noexcept
    : buf(buf_), n(strlen(buf_))
    {}
    /** Constructor
     *
     *  @param buf_ The input data.
     *  @param n_ Size of the input data in bytes.
     * */
    inline base64(const char *buf_, const size_t n_) noexcept
    : buf(buf_), n(n_)
    {}
    /** Constructor
     *
     *  @param beg The start of the input data.
     *  @param end The end of the input data.
     * */
    inline base64(const char *beg, const char *end) noexcept
    : buf(beg), n(end-beg)
    {}
    
    template <class Sink>
    inline void operator () (Sink &snk, fout_tag) const
    {
        io::write(snk | io::adaptor::base64_enc(), buf, n);
    }
    
private:
    const char *buf;
    const size_t n;
};
//------------------------------------------------------------------------------
/** Base64 encoder which is a little more customizable than format::base64.
 *
 *  @see base64
 * */
class base64_ex
{
public:
    /** Constructor
     *
     *  @param padding Enable padding.
     *  @param cols The number of characters per line (0 = no wrapping).
     *  @param buf_ The input data which must be null-terminated.
     * */
    inline base64_ex(bool padding, const size_t cols,
        const char *buf_) noexcept
    : ncols(cols), pad(padding), buf(buf_), n(strlen(buf_))
    {}
    /** Constructor
     *
     *  @param padding Enable padding.
     *  @param cols The number of characters per line (0 = no wrapping).
     *  @param buf_ The input data.
     *  @param n_ Size of the input data in bytes.
     * */
    inline base64_ex(bool padding, const size_t cols,
        const char *buf_, const size_t n_) noexcept
    : ncols(cols), pad(padding), buf(buf_), n(n_)
    {}
    /** Constructor
     *
     *  @param padding Enable padding.
     *  @param cols The number of characters per line (0 = no wrapping).
     *  @param beg The start of the input data.
     *  @param end The end of the input data.
     * */
    inline base64_ex(bool padding, const size_t cols,
        const char *beg, const char *end) noexcept
    : ncols(cols), pad(padding), buf(beg), n(end-beg)
    {}
    
    template <class Sink>
    inline void operator () (Sink &snk, fout_tag) const
    {
        io::write(
            snk | io::adaptor::nth('\n', ncols) | io::adaptor::base64_enc(pad),
            buf, n);
    }
    
private:
    const size_t ncols;
    const bool pad;
    const char *buf;
    const size_t n;
};
//------------------------------------------------------------------------------
/** Simple base64 decoder.
 * */
class base64_d
{
public:
    /** Constructor
     *
     *  @param buf_ The input data which must be null-terminated.
     * */
    inline base64_d(const char *buf_) noexcept
    : buf(buf_), n(strlen(buf_))
    {}
    /** Constructor
     *
     *  @param buf_ The input data.
     *  @param n_ Size of the input data in bytes.
     * */
    inline base64_d(const char *buf_, const size_t n_) noexcept
    : buf(buf_), n(n_)
    {}
    /** Constructor
     *
     *  @param beg The start of the input data.
     *  @param end The end of the input data.
     * */
    inline base64_d(const char *beg, const char *end) noexcept
    : buf(beg), n(end-beg)
    {}
    
    template <class Sink>
    inline void operator () (Sink &snk, fout_tag) const
    {
        io::write(snk | io::adaptor::base64_dec(), buf, n);
    }
    
private:
    const char *buf;
    const size_t n;
};
//------------------------------------------------------------------------------
class base64url
{
public:
    inline base64url(const char *buf_) noexcept
    : buf(buf_), n(strlen(buf_))
    {}
    inline base64url(const char *buf_, const size_t n_) noexcept
    : buf(buf_), n(n_)
    {}
    inline base64url(const char *beg, const char *end) noexcept
    : buf(beg), n(end-beg)
    {}
    
    template <class Sink>
    inline void operator () (Sink &snk, fout_tag) const
    {
        io::write(snk | io::adaptor::base64url_enc(), buf, n);
    }
    
private:
    const char *buf;
    const size_t n;
};
//------------------------------------------------------------------------------
class base64url_ex
{
public:
    inline base64url_ex(bool padding, const size_t cols,
        const char *buf_) noexcept
    : ncols(cols), pad(padding), buf(buf_), n(strlen(buf_))
    {}
    inline base64url_ex(bool padding, const size_t cols,
        const char *buf_, const size_t n_) noexcept
    : ncols(cols), pad(padding), buf(buf_), n(n_)
    {}
    inline base64url_ex(bool padding, const size_t cols,
        const char *beg, const char *end) noexcept
    : ncols(cols), pad(padding), buf(beg), n(end-beg)
    {}
    
    template <class Sink>
    inline void operator () (Sink &snk, fout_tag) const
    {
        io::write(
            snk | io::adaptor::nth('\n', ncols)
                | io::adaptor::base64url_enc(pad),
            buf, n);
    }
    
private:
    const size_t ncols;
    const bool pad;
    const char *buf;
    const size_t n;
};

/** @} */

}}} // namespaces

#endif // NIC_D305D5041316DFC9_NIC
