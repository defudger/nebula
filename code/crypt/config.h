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
#ifndef NIC_E5FEEE454F433D2E_NIC
#define NIC_E5FEEE454F433D2E_NIC

#include "../foundation/config.h"
#include "../foundation/assert.h"
#include "../foundation/endian.h"
#include "../foundation/mem.h"
#include "../foundation/string.h"
#include "../foundation/cstring.h"
#include "../foundation/carray.h"
#include "../foundation/vector.h"
#include "../foundation/range.h"
#include "../foundation/io.h"
#include "../foundation/format.h"
#include "../foundation/system_error.h"
#include "../foundation/tuple.h"
#include "../foundation/chrono.h"
#include "../foundation/scope_exit.h"
#include "../foundation/math/exact_cast.h"

#ifdef NAUTO_HAVE_GCRYPT
#   define N_CRYPT_GCRYPT
#else
#   error "libgcrypt is missing"
#endif

namespace nebula { namespace crypt {
/** @ingroup Crypt
 * @{
 * */
namespace detail {
//------------------------------------------------------------------------------
namespace fnd = foundation;
namespace endian = fnd::endian;
namespace memory = fnd::memory;
namespace system = fnd::system;
namespace io = fnd::io;
namespace fmt = fnd::fmt;
namespace chrono = fnd::chrono;
namespace iterator = fnd::iterator;
namespace range = fnd::range;
namespace math = fnd::math;
namespace meta = fnd::meta;
namespace ctraits = fnd::ctraits;

//------------------------------------------------------------------------------
using buffer_static_limit_ = meta::size_t_<16>;

} // detail

//------------------------------------------------------------------------------
/** @def n_crypt_dll
 * */
#ifdef N_CRYPT_SHARED
#    ifdef N_CRYPT_BUILD_DLL
#        define n_crypt_dll n_dll_export
#    else
#        define n_crypt_dll n_dll_import
#    endif
#else
#    define n_crypt_dll
#endif

//------------------------------------------------------------------------------
#define NEBULA_CRYPT_NAME             NAUTO_CRYPT_NAME
#define NEBULA_CRYPT_VERSION          NAUTO_CRYPT_VERSION
#define NEBULA_CRYPT_STRING           NAUTO_CRYPT_STRING
#define NEBULA_CRYPT_BUGREPORT        NAUTO_CRYPT_BUGREPORT
#define NEBULA_CRYPT_URL              NAUTO_CRYPT_URL
#define NEBULA_CRYPT_VERSION_MAJOR    NAUTO_CRYPT_VERSION_MAJOR
#define NEBULA_CRYPT_VERSION_MINOR    NAUTO_CRYPT_VERSION_MINOR
#define NEBULA_CRYPT_VERSION_MICRO    NAUTO_CRYPT_VERSION_MICRO

/** @} */

}} // namespaces

#endif // NIC_E5FEEE454F433D2E_NIC

