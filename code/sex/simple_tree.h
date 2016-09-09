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
#ifndef INC_F9F49F1BB67523BA_INC
#define INC_F9F49F1BB67523BA_INC

#include "basic_parser.h"

namespace nebula { namespace sex { namespace detail {
/** @ingroup Sex
 * @{
 * */
//------------------------------------------------------------------------------
/** Just a simple and convenient parser.
 *
 *  This is much slower than the primitive parse() function but
 *  more convenient than callback based parsing.
 *
 *  @param String By default this is nebula::foundation::const_cstring and
 *  thus requires the input source to stay alive. Also resolving
 *  escape-sequences isn't possible if you use this type. Alternatively you
 *  can use nebula::foundation::string (or an interface compatible type)
 *  to elminate such shortcomings.
 *  @param HandleEsc A flag that indicates wether escape-sequence are
 *  resolved. This options is off by default unless you use
 *  nebula::foundation::string for strings.
 *
 *  Example:
 *  @code
 *  simple_tree<> s(SRC);
 *  for(const typename simple_tree<>::node_type &e : s.entries())
 *  {
 *      if(s.is_string())
 *          fwrite(cout, "A string: ", s.string());
 *      else
 *          do_something(s.simple_tree()); // another list
 *  }
 *  @endcode
 * */
template <
    class String = fnd::const_cstring,
    class HandleEsc = fnd::_is_same<String, fnd::string>>
class simple_tree
{
    template <class Str, class SE>
    class node
    {
    public:
        node() = default;
        node(node &) = default;
        node(const node &) = default;
        node(node &&) = default;
        
        template <class ... X>
        inline node(X && ... x)
        : v(fnd::forward<X>(x)...)
        {}
        
        node &operator = (node &) = default;
        node &operator = (const node &) = default;
        node &operator = (node &&) = default;
        
        inline void swap(node &other) noexcept {
            foundation::swap(v, other.v);
        }

        inline bool is_string() const noexcept {
            return v.index() == 0;
        }
        
        inline Str &string() {
            return fnd::variant_cast<Str>(v);
        }
        inline const Str &string() const {
            return fnd::variant_cast<Str>(v);
        }
        inline SE &simple_tree() {
            return fnd::variant_cast<SE>(v);
        }
        inline const SE &simple_tree() const {
            return fnd::variant_cast<SE>(v);
        }
        
    private:
        fnd::variant<Str, SE> v;
    };
    
public:
    using this_type = simple_tree<String, HandleEsc>;
    using string_type = String;
    using node_type = node<string_type, this_type>;
    
private:
    struct parser_cb
    {
        inline bool push(size_t) {
            ses.emplace_back(se);
            se = &se->add_simple_tree();
            return true;
        }
        inline bool pop(size_t) {
            n_assert(!ses.empty());
            se->v.shrink_to_fit();
            se = ses.back();
            ses.pop_back();
            return true;
        }
        inline bool string(const fnd::const_cstring s, size_t) {
            se->add(s);
            return true;
        }
        template <class C = HandleEsc,
            fnd::_enable_if<C>* = nullptr>
        inline bool quoted_string(const fnd::const_cstring s, size_t) {
            String tmp;
            tmp.reserve(s.size());
            for(const char *i = s.begin(); i != s.end(); ++i)
            {
                if('\\' != *i)
                    tmp.push_back(*i);
                else
                {
                    ++i;
                    // The parser shouldn't allow this.
                    n_assert(s.end() != i);
                    tmp.push_back(*i);
                }
            }
            // tmp.shrink_to_fit();
            se->add(fnd::move(tmp));
            return true;
        }
        template <class C = HandleEsc,
            fnd::_disable_if<C>* = nullptr>
        inline bool quoted_string(const fnd::const_cstring s, const size_t p) {
            return this->string(s, p);
        }
        inline bool data(const fnd::const_cstring s, const size_t p) {
            return this->string(s, p);
        }
        inline void error(const errc e, const size_t p) {
            err = e;
            pos = p;
        }
        
        simple_tree *se;
        errc err;
        size_t pos;
        fnd::stack<simple_tree*> ses;
    };
    
    using container_type = fnd::vector<node_type>;
    
public:
    using node_range_type = fnd::range::iterator_range<
        typename container_type::const_iterator>;
    
    simple_tree() = default;
    simple_tree(simple_tree &) = default;
    simple_tree(const simple_tree &) = default;
    simple_tree(simple_tree &&) = default;
    
    /** Like the parse() member function but throws in case of errors. 
     *
     *  @throw parsing_error When parsing fails.
     * */
    inline simple_tree(const fnd::const_cstring src)
    {
        auto f = fnd::scope_exit([&] () { v.reset(); });
        parser_cb cb{this, errc::success, 0};
        sex::detail::parse(cb, src);
        if(errc::success != cb.err)
        {
            fnd::string msg = fnd::fmt::to_string(
                "Parsing S-Expression failed at byte ", cb.pos, '.');
            n_throw(parsing_error)
            << fnd::ei_msg(fnd::move(msg))
            << fnd::system::ei_error_code(cb.err);
        }
        f.dismiss();
    }
    
    inline ~simple_tree() noexcept {
        v.reset();
    }
    
    simple_tree &operator = (simple_tree &) = default;
    simple_tree &operator = (const simple_tree &) = default;
    simple_tree &operator = (simple_tree &&) = default;
    
    inline void swap(simple_tree &other) noexcept {
        foundation::swap(v, other.v);
    }
    
    /** Parse a script and return possible errors.
     *
     *  This doesn't throw when parsing fails but instead returns the
     *  error code together with a position indicator which is only defined
     *  if the error code is not errc::success.
     *
     *  If this function fails either due to an exception or a bad script
     *  (returning an error-code other than errc::success)
     *  then the state of this instance is not changed.
     * */
    inline fnd::tuple<errc, size_t> parse(const fnd::const_cstring src)
    {
        container_type old = fnd::move(v);
        auto f = fnd::scope_exit([&] () { v = fnd::move(old); });
        parser_cb cb{this, errc::success, 0};
        sex::detail::parse(cb, src);
        if(errc::success == cb.err)
            f.dismiss();
        return {cb.err, cb.pos};
    }
    
    /** Read-only access. */
    inline node_range_type nodes() const noexcept {
        return {v.begin(), v.end()};
    }
    
    /** Reset this instance as if it was default constructed. */
    inline void reset() noexcept {
        v.reset();
    }
    
private:
    template <class Str>
    inline void add(Str &&s) {
        v.emplace_back(string_type(fnd::forward<Str>(s)));
    }
    inline simple_tree &add_simple_tree() {
        v.emplace_back(simple_tree());
        return v.back().simple_tree();
    }
    
    container_type v;
};

/** @} */

}}} // namespaces

#endif // INC_F9F49F1BB67523BA_INC

