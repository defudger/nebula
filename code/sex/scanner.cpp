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
#include "scanner.h"

namespace nebula { namespace sex { namespace detail {
/** @ingroup Sex
 * @{
 * */
//------------------------------------------------------------------------------
inline bool is_white(const char c) noexcept
{
    return ' ' == c
        || '\n' == c;
}
//------------------------------------------------------------------------------
inline bool is_alpha(const char c) noexcept
{
    return (64 < c && c < 91) // A..Z
        || (96 < c && c < 123); // a..z
}
//------------------------------------------------------------------------------
inline bool is_digit(const char c) noexcept
{
    return 47 < c && c < 58; // 0..9
}
//------------------------------------------------------------------------------
inline bool is_visible(const char c) noexcept
{
    return is_alpha(c) || is_digit(c)
        || '+' == c
        || '-' == c
        || '*' == c
        || '/' == c
        || '_' == c
        || '=' == c
        || '?' == c
        || '$' == c
        || '%' == c
        || '&' == c
        || '#' == c
        || '&' == c
        || '~' == c
        || '<' == c
        || '>' == c
        || '.' == c
        || '\'' == c
        || ':' == c
        || '^' == c
        || '|' == c
        || '@' == c;
}

//------------------------------------------------------------------------------
inline fnd::const_cstring skip_white(const fnd::const_cstring s) noexcept
{
    return {
        fnd::range::find_if(s, [] (const char c) { return!is_white(c); }),
        s.end()};
}
//------------------------------------------------------------------------------
inline fnd::const_cstring skip_comment(const fnd::const_cstring s) noexcept
{
    const char *i = s.begin();
    if(i == s.end())
        return s;
    if(1 < s.size())
    {
        if('/' == s[0]) // C++ style
        {
            if('/' == s[1])
            {
                const char *j = s.begin()+2;
                for( ; j < s.end(); ++j)
                    if(*j == '\n')
                        return {j+1, s.end()};
                return {s.end(), s.end()};
            }
            else if('*' == s[1])
            {
                if(4 > s.size())
                    return s;
                
                const char *j = s.begin()+2;
                for( ; j < s.end(); ++j)
                {
                    if('*' == *j)
                    {
                        ++j;
                        if(j == s.end())
                            return s;
                        if('/' == *j)
                            return {j+1, s.end()};
                    }
                }
            }
        }
        else if(s[0]==';') // emacs style
        {
            if(s[1]==';')
            {
                const char *j = s.begin()+2;
                for( ; j < s.end(); ++j)
                    if(*j == '\n')
                        return {j+1, s.end()};
                return {s.end(), s.end()};
            }
        }
    }
    return s;
}
//------------------------------------------------------------------------------
fnd::tuple<token, fnd::const_cstring> scan(fnd::const_cstring s)
{
    while(!s.empty())
    {
        const char *tmp = s.begin();
        s = skip_comment(skip_white(s));
        if(tmp == s.begin())
            break;
    }
    
    if(s.empty())
        return {token{token_id::eof, fnd::const_cstring{}}, s};
    
    switch(s.front())
    {
    case '(':
        return {
            token{
                token_id::lbracket,
                fnd::const_cstring{s.begin(), s.begin()+1}},
            fnd::const_cstring{s.begin()+1, s.end()}};
    case ')':
        return {
            token{
                token_id::rbracket,
                fnd::const_cstring{s.begin(), s.begin()+1}},
            fnd::const_cstring{s.begin()+1, s.end()}};
    case '"':
        for(const char *i = s.begin()+1; i != s.end(); ++i)
        {
            if('\\' == *i)
            {
                if(s.end() == ++i)
                    break;
            }
            else if('"' == *i)
            {
                return {
                    token{
                        token_id::quoted_string,
                        fnd::const_cstring{s.begin()+1, i}},
                    fnd::const_cstring{i+1, s.end()}};
            }
        }
        return {
            token{token_id::eof, fnd::const_cstring{}}, 
            s};
    case ':':
        return {
            token{
                token_id::invalid,
                fnd::const_cstring{s.begin(), s.begin()+1}},
            fnd::const_cstring{s.begin()+1, s.end()}};
    default:
        {
            const char *i = s.begin();
            
            if(is_digit(*i))
            {
                ++i;
                for( ; i != s.end() && is_digit(*i); ++i)
                    ; // empty
                if(s.end() == i)
                {
                    return {
                        token{token_id::eof, fnd::const_cstring{}}, 
                        s};
                }
                if(':' == *i)
                {
                    fnd::const_cstring val = fnd::const_cstring{s.begin(), i};
                    s = {i+1, s.end()};
                    
                    // so it fits into 32 bit unsigned int.
                    if(val.size() > 9)
                    {
                        return {token{token_id::invalid, val}, s};
                    }
                    if(val.front() == '0')
                    {
                        return {token{token_id::invalid, val}, s};
                    }
                    const size_t l = fnd::fmt::to_integer<size_t>(val);
                    if(l > s.size())
                    {
                        return {token{token_id::invalid, val}, s};
                    }
                    const fnd::const_cstring data = {
                        s.begin(),
                        s.begin()+l};
                    return {token{token_id::data, data},
                        fnd::const_cstring{data.end(), s.end()}};
                }
                if(!is_visible(*i))
                {
                    return {
                        token{
                            token_id::string,
                            fnd::const_cstring{s.begin(), i}},
                        fnd::const_cstring{i, s.end()}};
                }
                ++i;
            }
            
            for( ; i != s.end() && is_visible(*i); ++i)
                ; // empty
            
            if(s.begin() == i)
            {
                return {
                    token{
                        token_id::invalid,
                        fnd::const_cstring{s.begin(), s.begin()+1}},
                    fnd::const_cstring{s.begin()+1, s.end()}};
            }
            return {
                token{
                    token_id::string,
                    fnd::const_cstring{s.begin(), i}},
                fnd::const_cstring{i, s.end()}};
        }
    }
    
    n_assert(!"Dragons are real!");
}

/** @} */

}}} // namespaces

