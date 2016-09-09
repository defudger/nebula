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
#ifndef _n_nebula_foundation_assert_
#define _n_nebula_foundation_assert_

#include "config.h"
// Always include cassert here.
#include <cassert>

/** @ingroup Foundation
 * @{
 * */

//------------------------------------------------------------------------------
/** @def n_assert
 * Same as the vanilla assert macro but capable of future alterations.
 * @attention Must not throw! 
 * */
/** @def n_assert_msg
 * @see n_assert 
 * */
#ifdef N_USE_ASSERT
#    define n_assert( x ) assert(x);
#    define n_assert_msg( x, msg ) n_assert( (x) && msg );
#else
#    define n_assert( x )
#    define n_assert_msg( x, msg )
#endif

/** @} */

#endif // _n_nebula_foundation_assert_
