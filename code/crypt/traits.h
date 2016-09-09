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
#ifndef NIC_87B11322A7B47D20_NIC
#define NIC_87B11322A7B47D20_NIC

#include "defs.h"

namespace nebula { namespace crypt { namespace traits {
/** @ingroup Crypt
 * @{
 * */
//------------------------------------------------------------------------------
template <class T>
struct algorithm {
    using type = typename T::algorithm;
};
n_meta_alias(algorithm);
//------------------------------------------------------------------------------
template <class T>
struct mode {
    using type = typename T::mode;
};
n_meta_alias(mode);

//------------------------------------------------------------------------------
template <class T>
struct is_block_cipher {
    using type = foundation::_is_same<
        _algorithm<T>,
        detail::block_cipher_algorithm>;
};
n_meta_alias(is_block_cipher);

//------------------------------------------------------------------------------
template <class T>
struct block {
    using type = typename T::block_type;
};
n_meta_alias(block);
//------------------------------------------------------------------------------
template <class T>
struct block_size {
    using type = typename T::block_size;
};
n_meta_alias(block_size);
//------------------------------------------------------------------------------
template <class T>
struct key {
    using type = typename T::key_type;
};
n_meta_alias(key);
//------------------------------------------------------------------------------
template <class T>
struct key_size {
    using type = typename T::key_size;
};
n_meta_alias(key_size);

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
template <class T>
struct hash_result {
    using type = typename T::result_type;
};
n_meta_alias(hash_result);
//------------------------------------------------------------------------------
template <class T>
struct hash_size {
    using type = typename T::result_size;
};
n_meta_alias(hash_size);

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
template <class T>
struct secure {
    using type = typename T::secure;
};
n_meta_alias(secure);
//------------------------------------------------------------------------------
template <class T>
struct stream_able {
    using type = typename T::stream_able;
};
n_meta_alias(stream_able);

/** @} */

}}} // namespaces

#endif // NIC_87B11322A7B47D20_NIC

