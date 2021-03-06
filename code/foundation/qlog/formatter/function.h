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
#ifndef NIC_ACE50B7EE462E4DB_NIC
#define NIC_ACE50B7EE462E4DB_NIC

#include "formatter_base.h"

#include "../../move.h"
#include "../../call_traits.h"

namespace nebula { namespace foundation { namespace qlog { namespace formatter {
//------------------------------------------------------------------------------
template <class F>
class function final : public formatter_base
{
public:
    template <class F_>
    inline function(F_ &&f)
    : func(foundation::forward<F_>(f))
    {}
    
    inline void operator () (level lvl, string &s)
    {
        func(lvl, s);
    }
    
private:
    F func;
};
//------------------------------------------------------------------------------
template <class F>
inline intrusive_ptr<function<typename ctraits::value<F>::type>>
capture(F &&f)
{
    return new function<
        typename ctraits::value<F>::type>(foundation::forward<F>(f));
}

}}}} // namespaces

#endif // NIC_ACE50B7EE462E4DB_NIC
