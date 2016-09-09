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
#ifndef INC_59CDB48924B2F365_INC
#define INC_59CDB48924B2F365_INC

#include "scanner.h"

namespace nebula { namespace sex { namespace detail {
/** @ingroup Sex
 * @{
 * */
//------------------------------------------------------------------------------
template <class CB>
inline fnd::const_cstring parse_expr(CB &cb, fnd::const_cstring s)
{
    n_static_assert(sizeof(size_t)*n_char_bit >= 32, "");
    
    token t;
    
    while(true)
    {
        if(s.begin() == nullptr)
            return {};
        fnd::tie(t, s) = scan(s);
        switch(t.id())
        {
        case token_id::lbracket:
            if(!cb.push(t.value().begin()))
                return {};
            s = parse_expr(cb, s);
            break;
        case token_id::rbracket:
            if(!cb.pop(t.value().begin()))
                return {};
            return s;
        case token_id::quoted_string:
            if(!cb.quoted_string(t.value()))
                return {};
            break;
        case token_id::data:
            if(!cb.data(t.value()))
                return {};
            break;
        case token_id::string:
            if(!cb.string(t.value()))
                return {};
            break;
        case token_id::eof:
            cb.error(errc::unexpected_eof, s.begin());
            return {};
        case token_id::invalid:
            cb.error(errc::invalid_token, s.begin());
            return {};
        default:
            n_throw(logic_error);
        }
    }
}
//------------------------------------------------------------------------------
template <class CB>
struct listener_wrapper
{
    inline bool push(const char *pos) {
        return cb.push(pos-src_beg);
    }
    inline bool pop(const char *pos) {
        return cb.pop(pos-src_beg);
    }
    inline bool string(const fnd::const_cstring s) {
        return cb.string(s, s.begin()-src_beg);
    }
    inline bool quoted_string(const fnd::const_cstring s) {
        return cb.quoted_string(s, s.begin()-src_beg);
    }
    inline bool data(const fnd::const_cstring s) {
        return cb.data(s, s.begin()-src_beg);
    }
    inline void error(const errc e, const char *pos) {
        cb.error(e, pos-src_beg);
    }
    
    const char *src_beg;
    CB &cb;
};
//------------------------------------------------------------------------------
/** Simple S-Expressions parser.
 *
 *  Does not allocate memory or modify the input source.
 * */
template <class CB>
inline void parse(CB &&cb_, fnd::const_cstring s)
{
    auto cb = listener_wrapper<fnd::ctraits::_value<CB>>{s.begin(), cb_};
    
    do
    {
        if(s.begin() == nullptr)
            return;
        token t;
        const char *old_beg = s.begin();
        fnd::tie(t, s) = scan(s);
        if(token_id::lbracket == t.id())
        {
            if(!cb.push(t.value().begin()))
                return;
        }
        else if(token_id::eof == t.id())
        {
            return;
        }
        else
        {
            cb.error(
                token_id::invalid == t.id()
                ? errc::invalid_token : errc::unexpected_token,
                old_beg);
            return;
        }
        
        s = parse_expr(cb, s);
    }
    while(true);
}

//------------------------------------------------------------------------------
/** Simple S-Expressions parser.
 *
 *  Does not allocate memory or modify the input source.
 * */
template <class String = fnd::string>
class iterative_parser
{
    n_static_assert(fnd::_is_nothrow_movable<String>::value, "");
    
public:
    using result_type = fnd::optional<token>;
    
    iterative_parser(iterative_parser &) = default;
    iterative_parser(const iterative_parser &) = default;
    iterative_parser(iterative_parser &&) = default;
    
    template <class S>
    iterative_parser(S &&source)
    {
        this->reset(fnd::forward<S>(source));
    }
    
    iterative_parser &operator = (iterative_parser &) = default;
    iterative_parser &operator = (const iterative_parser &) = default;
    iterative_parser &operator = (iterative_parser &&) = default;
    
    inline void swap(iterative_parser &other) noexcept {
        fnd::swap(src, other.src);
        fnd::swap(pos, other.pos);
        fnd::swap(lvl, other.lvl);
        fnd::swap(err, other.err);
    }
    
    inline result_type operator () ()
    {
        if(!is_valid())
            return fnd::nil_tag();
        
        token t;
        fnd::const_cstring s = {pos, src.end()};
        fnd::tie(t, s) = scan(s);
        
        switch(t.id())
        {
        case token_id::lbracket:
            pos = s.begin();
            ++lvl;
            return t;
        case token_id::rbracket:
            if(0 == lvl)
            {
                pos = t.value().begin();
                err = errc::stray_rbracket;
                return fnd::nil_tag();
            }
            pos = s.begin();
            --lvl;
            return t;
        case token_id::string:
        case token_id::quoted_string:
        case token_id::data:
            pos = s.begin();
            return t;
        case token_id::eof:
            if(0 != lvl)
            {
                err = errc::missing_rbracket;
                return fnd::nil_tag();
            }
            pos = s.end();
            err = errc::eof;
            return t;
        case token_id::invalid:
            pos = t.value().begin();
            err = errc::invalid_token;
            return fnd::nil_tag();
        default:
            n_throw(logic_error);
        }
    }
    inline result_type parse() {
        return this->operator ();
    }
    
    inline fnd::optional<fnd::const_cstring> parse_string()
    {
        result_type r = this->operator () ();
        if(!r.valid())
            return fnd::nil_tag();
        token t = r.get();
        if(token_id::string != t.id())
        {
            err = errc::unexpected_token;
            pos = t.value().begin();
            return fnd::nil_tag();
        }
        return t.value();
    }
    inline fnd::optional<fnd::const_cstring> parse_quoted_string()
    {
        result_type r = this->operator () ();
        if(!r.valid())
            return fnd::nil_tag();
        token t = r.get();
        if(token_id::quoted_string != t.id())
        {
            err = errc::unexpected_token;
            pos = t.value().begin();
            return fnd::nil_tag();
        }
        return t.value();
    }
    inline fnd::optional<fnd::const_cstring> parse_data()
    {
        result_type r = this->operator () ();
        if(!r.valid())
            return fnd::nil_tag();
        token t = r.get();
        if(token_id::data != t.id())
        {
            err = errc::unexpected_token;
            pos = t.value().begin();
            return fnd::nil_tag();
        }
        return t.value();
    }
    inline fnd::optional<fnd::const_cstring> parse_any_string()
    {
        result_type r = this->operator () ();
        if(!r.valid())
            return fnd::nil_tag();
        token t = r.get();
        if(token_id::string == t.id()
            || token_id::quoted_string == t.id()
            || token_id::data == t.id())
        {
            return t.value();
        }
        err = errc::unexpected_token;
        pos = t.value().begin();
        return fnd::nil_tag();
    }
    inline bool parse_lbracket()
    {
        result_type r = this->operator () ();
        if(!r.valid())
            return false;
        token t = r.get();
        if(token_id::lbracket != t.id())
        {
            pos = t.value().begin();
            err = errc::unexpected_token;
            return false;
        }
        return true;
    }
    inline bool parse_rbracket()
    {
        result_type r = this->operator () ();
        if(!r.valid())
            return false;
        token t = r.get();
        if(token_id::rbracket != t.id())
        {
            pos = t.value().begin();
            err = errc::unexpected_token;
            return false;
        }
        return true;
    }
    inline bool parse_eof()
    {
        result_type r = this->operator () ();
        if(!r.valid())
            return false;
        token t = r.get();
        if(token_id::eof != t.id())
        {
            pos = t.value().begin();
            err = errc::unexpected_token;
            return false;
        }
        return true;
    }
    
    template <class S>
    inline void
    reset(S &&s = String()) noexcept {
        src = fnd::forward<S>(s);
        pos = src.begin();
        lvl = 0;
        err = errc::success;
    }
    
    inline const String &source() const noexcept {
        return src;
    }
    inline operator bool () const noexcept {
        return errc::success == err;
    }
    inline bool is_valid() const noexcept {
        return !!*this;
    }
    inline errc error() const noexcept {
        return err;
    }
    inline size_t position() const noexcept {
        return pos - src.begin();
    }
    
private:
    String src;
    const char *pos;
    size_t lvl;
    errc err;
};

/** @} */

}}} // namespaces

#endif // INC_59CDB48924B2F365_INC

