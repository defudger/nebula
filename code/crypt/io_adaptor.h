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
#ifndef NIC_6F456D5ED36B9518_NIC
#define NIC_6F456D5ED36B9518_NIC

#include "traits.h"

namespace nebula { namespace crypt { namespace detail {
/** @ingroup Crypt
 * @{
 * */
namespace cipher_stream_detail {
//------------------------------------------------------------------------------
template <class Stream_, class Cipher, bool Encrypt>
class cipher_stream : public fnd::adaptor_base<Stream_>
{
    n_static_assert(traits::_stream_able<Cipher>::value,
        "This kind of cipher can't be used for streaming.");
    
    template <int> struct nil {};
    
    using Stream = typename fnd::adaptor_base<Stream_>::adaptee_type;
    using Base = fnd::adaptor_base<Stream_>;
    using Enc = meta::bool_<Encrypt>;
    using Dec = meta::_not<Enc>;
    
public:
    using stream_size = io::_stream_size<Stream>;
    using stream_position = io::_stream_position<Stream>;
    using stream_offset = io::_stream_offset<Stream>;
    using stream_category = fnd::tag<
        meta::_if<io::has_write<Stream>, io::out_tag, nil<0>>,
        meta::_if<io::has_flush<Stream>, io::flush_tag, nil<1>>,
        meta::_if<io::has_read<Stream>, io::in_tag, nil<2>>>;
    
    template <class S, class Cipher_>
    inline cipher_stream(S &&s, Cipher_ &c)
    : Base(fnd::forward<S>(s)),
        cipher_(c)
    {}
    inline ~cipher_stream() noexcept {}
    
    template <class S = Stream,
        fnd::_enable_if<meta::and_<io::has_write<S>, Enc>>* = nullptr>
    inline void write(const char *buf_, stream_size n) {
        traits::_block<Cipher> b;
        while(n > 0) {
            const stream_size min_ = fnd::min(n, b.size());
            stream_size m = cipher_.encrypt(buf_, min_, b.data(), b.size());
            io::write(this->adaptee(), b.data(), m);
            n -= m;
            buf_ += m;
        }
    }
    template <class S = Stream,
        fnd::_enable_if<meta::and_<io::has_write<S>, Dec>>* = nullptr>
    inline void write(const char *buf_, stream_size n) {
        traits::_block<Cipher> b;
        while(n > 0) {
            const stream_size min_ = fnd::min(n, b.size());
            stream_size m = cipher_.decrypt(buf_, min_, b.data(), b.size());
            io::write(this->adaptee(), b.data(), m);
            n -= m;
            buf_ += m;
        }
    }
    template <class S = Stream,
        fnd::_enable_if<io::has_write<S>>* = nullptr>
    inline void put(const char c) {
        this->write(&c, 1);
    }
    
    template <class S = Stream,
        fnd::_enable_if<io::has_flush<S>>* = nullptr>
    inline void flush(const char c) {
        io::flush(this->adaptee());
    }
    
    template <class S = Stream,
        fnd::_enable_if<meta::and_<io::has_read<S>, Enc>>* = nullptr>
    inline stream_size read(char *buf_, stream_size n) {
        traits::_block<Cipher> b;
        stream_size r = 0;
        while(true) {
            const stream_size min_ = fnd::min(n, b.size());
            stream_size m = io::read(this->adaptee(),
                b.data(), min_);
            m = cipher_.encrypt(b.data(), m, buf_ + r, m);
            r += m;
            if(m < min_ || r == n)
                break;
        }
        return r;
    }
    template <class S = Stream,
        fnd::_enable_if<meta::and_<io::has_read<S>, Dec>>* = nullptr>
    inline stream_size read(char *buf_, stream_size n) {
        traits::_block<Cipher> b;
        stream_size r = 0;
        while(true) {
            const stream_size min_ = fnd::min(n, b.size());
            stream_size m = io::read(this->adaptee(),
                b.data(), min_);
            m = cipher_.decrypt(b.data(), m, buf_ + r, m);
            r += m;
            if(m < min_ || r == n)
                break;
        }
        return r;
    }
    template <class S = Stream,
        fnd::_enable_if<io::has_read<S>>* = nullptr>
    inline io::ceof get() {
        char c;
        if(0 == this->read(&c, 1))
            return io::eof;
        return c;
    }
    
private:
    Cipher &cipher_;
};

//------------------------------------------------------------------------------
template <class Cipher, bool Encrypt>
struct trigger {
    Cipher &c;
};
//------------------------------------------------------------------------------
template <class T, class Cipher, bool Encrypt>
inline cipher_stream<fnd::_remove_reference<T>, Cipher, Encrypt>
operator | (T &&x, trigger<Cipher, Encrypt> y)
{
    return cipher_stream<fnd::_remove_reference<T>, Cipher, Encrypt>(
        fnd::forward<T>(x),
        y.c);
}

} // cipher_stream_detail

//------------------------------------------------------------------------------
template <class Cipher>
inline cipher_stream_detail::trigger<Cipher, true> stream_encrypt(Cipher &c)
{
    return cipher_stream_detail::trigger<Cipher, true>{c};
}
//------------------------------------------------------------------------------
template <class Cipher>
inline cipher_stream_detail::trigger<Cipher, false> stream_decrypt(Cipher &c)
{
    return cipher_stream_detail::trigger<Cipher, false>{c};
}

/** @} */

}}} // namespaces

#endif // NIC_6F456D5ED36B9518_NIC

