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
#ifndef N_INCLUDE_96FB686C445D64C2326ADC1552DD0560
#define N_INCLUDE_96FB686C445D64C2326ADC1552DD0560

#include "config.h"

#ifdef N_REGEX_std_regex
#   include "std/regex.h"
#endif

namespace nebula { namespace foundation { namespace regex {
//------------------------------------------------------------------------------
#ifdef N_REGEX_std_regex
using std_regex = cppstd::std_regex;
using default_regex = cppstd::std_regex;
#endif

}}} // namespaces

#endif // N_INCLUDE_96FB686C445D64C2326ADC1552DD0560