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
#ifndef INC_16B83F64908BEC85_INC
#define INC_16B83F64908BEC85_INC

#include "../foundation/config.h"
#include "../foundation/assert.h"
#include "../foundation/exception.h"
#include "../foundation/array.h"
#include "../foundation/system_error.h"
#include "../foundation/range.h"
#include "../foundation/iterator.h"
#include "../foundation/cstring.h"
#include "../foundation/string.h"
#include "../foundation/tuple.h"
#include "../foundation/format.h"
#include "../foundation/variant.h"
#include "../foundation/stack.h"
#include "../foundation/optional.h"

namespace nebula { namespace sex { namespace detail {

namespace fnd = foundation;

/** @ingroup Sex
 * @{
 * */
//------------------------------------------------------------------------------
#ifdef N_SEX_SHARED
#    ifdef N_SEX_BUILD_DLL
#        define n_sex_dll n_dll_export
#    else
#        define n_sex_dll n_dll_import
#    endif
#else
#    define n_sex_dll
#endif

//------------------------------------------------------------------------------
#define NEBULA_SEX                  NAUTO_SEX_NAME
#define NEBULA_SEX_VERSION          NAUTO_SEX_VERSION
#define NEBULA_SEX_STRING           NAUTO_SEX_STRING
#define NEBULA_SEX_BUGREPORT        NAUTO_SEX_BUGREPORT
#define NEBULA_SEX_URL              NAUTO_SEX_URL
#define NEBULA_SEX_VERSION_MAJOR    NAUTO_SEX_VERSION_MAJOR
#define NEBULA_SEX_VERSION_MINOR    NAUTO_SEX_VERSION_MINOR
#define NEBULA_SEX_VERSION_MICRO    NAUTO_SEX_VERSION_MICRO

/** @} */

}}} // namespaces

#endif // INC_16B83F64908BEC85_INC

