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
#ifndef NIC_18A840A8871830C4_NIC
#define NIC_18A840A8871830C4_NIC

//------------------------------------------------------------------------------
#ifndef __STDC_WANT_LIB_EXT1__
#   define __STDC_WANT_LIB_EXT1__
#endif

//------------------------------------------------------------------------------
#ifdef BUILDING_NEBULA_
#   include <code/foundation/config/nebula_auto_config.h>
#else
#   include "nebula_auto_config.h"
#endif

/** @ingroup Foundation
 * @}
 */

//------------------------------------------------------------------------------
/** @def N_DEBUG
 * Defined if DEBUG or _DEBUG or NEBULA_DEBUG is defined.
 * @note NEBULA_DEBUG is pre-defined by the build system and must not be used
 * anywhere else but here.
* */
#if defined(DEBUG) || defined(_DEBUG) || defined(NEBULA_DEBUG)
#    define N_DEBUG
#endif

/** @} */

#endif // NIC_18A840A8871830C4_NIC
