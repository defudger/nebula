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
#ifndef INC_00DE5A0718596D6E_INC
#define INC_00DE5A0718596D6E_INC

#include "config.h"

namespace nebula { namespace sex { namespace detail {
/** @ingroup Sex
 * @{
 * */
//------------------------------------------------------------------------------
enum class errc
{
    success,
    eof,
    unexpected_eof,
    invalid_token,
    stray_rbracket,
    missing_rbracket,
    unexpected_token
};

//------------------------------------------------------------------------------
extern const fnd::system::error_category & n_sex_dll
sex_error_category() noexcept;

/** @} */

}}} // namespaces

//------------------------------------------------------------------------------
n_register_error_code_enum(
    ::nebula::sex::detail::errc,
    ::nebula::sex::detail::sex_error_category());
n_register_error_condition_enum(
    ::nebula::sex::detail::errc,
    ::nebula::sex::detail::sex_error_category());

#endif // INC_00DE5A0718596D6E_INC

