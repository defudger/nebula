/*--!>
This file is part of Nebula, a multi-purpose library mainly written in C++.

Copyright 2015-2016 outshined (outshined@riseup.net)
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
#include "ipv4_address.h"

namespace nebula { namespace foundation { namespace net { namespace ip {
//------------------------------------------------------------------------------
/** @ingroup Foundation */
inline optional<typename ipv4_address::storage_type>
_parse_num(const const_cstring s)
{
    using storage_type = typename ipv4_address::storage_type;
    
    if(s.empty())
        return nil_tag();
    
    if(s[0] == '0')
    {
        if(s.size() == 1)
            return 0;
        else
        {                
            if( (s[1] == 'x') || (s[1] == 'X') )
            {
                if(s.size() < 3)
                    return nil_tag();
                
                return fmt::to_integer<storage_type>(
                    {s.begin()+2, s.end()}, 16, nothrow_tag());
            }
            else
                return fmt::to_integer<storage_type>(
                    {s.begin()+1, s.end()}, 8, nothrow_tag());
        }
    }
    else
        return fmt::to_integer<storage_type>(s, 10, nothrow_tag());
}
//------------------------------------------------------------------------------
optional<ipv4_address> parse_ipv4_address(const const_cstring str)
{    
    if(str.empty())
        return nil_tag();
    
    const char *i = range::find(str, '.');
    
    if(i == str.end())
    {
        optional<typename ipv4_address::storage_type> r = _parse_num(str);
        if(!r)
            return nil_tag();
        return ipv4_address(r.get());
    }
    else
    {            
        typename ipv4_address::storage_type a,b,c,d;
        optional<typename ipv4_address::storage_type> x
            = _parse_num(const_cstring(str.begin(), i));
        if(!x)
            return nil_tag();
        a = x.get();
        
        const char *beg = i+1;
        i = iterator::find(beg, str.end(), '.');
        if(i == str.end())
            return nil_tag();
        x = _parse_num(const_cstring(beg, i));
        if(!x)
            return nil_tag();
        b = x.get();
        
        beg = i+1;
        i = iterator::find(beg, str.end(), '.');
        if(i == str.end())
            return nil_tag();
        x = _parse_num(const_cstring(beg, i));
        if(!x)
            return nil_tag();
        c = x.get();
        
        beg = i+1;
        x = _parse_num(const_cstring(beg, str.end()));
        if(!x)
            return false;
        d = x.get();
        
        return ipv4_address(a,b,c,d);
    }
}

}}}} // namespaces
