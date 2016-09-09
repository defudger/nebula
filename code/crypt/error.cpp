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
#include "error.h"

namespace nebula { namespace crypt { namespace detail {
//------------------------------------------------------------------------------
class crypt_category_impl : public system::error_category
{
public:
    crypt_category_impl() = default;

    inline const char *name() const noexcept {
        return "crypt";
    }
    inline fnd::string message(system::errval_t e) const
    {
        switch(e)
        {
        case static_cast<system::errval_t>(errc::success):
            return "success";
        case static_cast<system::errval_t>(errc::general_error):
            return "general_error";
        case static_cast<system::errval_t>(errc::eof):
            return "eof";
        case static_cast<system::errval_t>(errc::invalid_version):
            return "invalid_version";
        default: "unknown";
        }
    }

    inline system::error_condition default_error_condition(
        system::errval_t e) const noexcept
    {
        return system::error_condition(e, *this);
    }
};

//------------------------------------------------------------------------------
const system::error_category &crypt_error_category() noexcept {
    static crypt_category_impl r;
    return r;
}

}}} // namespaces
