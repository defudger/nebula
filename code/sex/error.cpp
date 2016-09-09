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
along with this program.  If not, see <sex://www.gnu.org/licenses/>.
--------------------------------------------------------------------------<!--*/
#include "error.h"

namespace nebula { namespace sex { namespace detail {
/** @ingroup Sex
 * @{
 * */
//------------------------------------------------------------------------------
class sex_error_category_impl : public fnd::system::error_category
{
public:
    sex_error_category_impl() = default;

    inline const char *name() const noexcept {
        return "sex";
    }
    inline fnd::string message(fnd::system::errval_t e) const
    {
        using fnd::system::errval_t;
        
        switch(e)
        {
        case static_cast<errval_t>(errc::success):
            return "success";
        case static_cast<errval_t>(errc::eof):
            return "Expected EOF";
        case static_cast<errval_t>(errc::unexpected_eof):
            return "Unexpected EOF";
        case static_cast<errval_t>(errc::invalid_token):
            return "Invalid token";
        case static_cast<errval_t>(errc::stray_rbracket):
            return "Found a stray ')' without a matching '('";
        case static_cast<errval_t>(errc::missing_rbracket):
            return "Expected a ')'";
        case static_cast<errval_t>(errc::unexpected_token):
            return "Unexpected token";
        default: "unknown";
        }
    }

    inline fnd::system::error_condition default_error_condition(
        fnd::system::errval_t e) const noexcept
    {
        return fnd::system::error_condition(e, *this);
    }
};

//------------------------------------------------------------------------------
const fnd::system::error_category &sex_error_category() noexcept {
    static detail::sex_error_category_impl r;
    return r;
}

/** @} */

}}} // namespaces

