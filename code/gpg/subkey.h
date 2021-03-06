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
#ifndef NIC_BC04130D0445E8EB_NIC
#define NIC_BC04130D0445E8EB_NIC

#include "defs.h"

namespace nebula { namespace gpg { namespace detail {
/** @ingroup GPG
 * @{
 * */
//------------------------------------------------------------------------------
/** This represents a subkey.
 *
 *  @attention Lifetime is bound to the lifetime of the associated key. 
 *  @internal This only holds a pointer to the actual data which is owned by
 *  the associated key. So copy/move operations only copy the internally
 *  stored pointer.
 * */
class subkey
{
public:
    inline bool revoked() const {
        n_assert(h);
        return h->revoked;
    }
    inline bool expired() const {
        n_assert(h);
        return h->expired;
    }
    inline bool disabled() const {
        n_assert(h);
        return h->disabled;
    }
    inline bool invalid() const {
        n_assert(h);
        return h->invalid;
    }
    inline bool can_encrypt() const {
        n_assert(h);
        return h->can_encrypt;
    }
    inline bool can_sign() const {
        n_assert(h);
        return h->can_sign;
    }
    inline bool can_certify() const {
        n_assert(h);
        return h->can_certify;
    }
    inline bool can_authenticate() const {
        n_assert(h);
        return h->can_authenticate;
    }
    inline bool secret() const {
        n_assert(h);
        return h->secret;
    }
    
    /** This is the length of the subkey (in bits). */
    inline size_t length() const {
        n_assert(h);
        math::require_exact_cast<size_t>(h->length);
        return h->length;
    }
    
    /** This is the key ID of the subkey in hexadecimal digits. */
    inline const_cstring keyid() const {
        n_assert(h);
        return h->keyid;
    }
    /** This is the fingerprint of the subkey in hexadecimal digits. */ 
    inline const_cstring fingerprint() const {
        n_assert(h);
        return h->fpr;
    }
    
    inline chrono::seconds creation_time() const {
        n_assert(h);
        return h->timestamp;
    }
    inline chrono::seconds expiration_time() const {
        n_assert(h);
        return h->timestamp;
    }
    
    inline bool is_cardkey() const {
        n_assert(h);
        return h->is_cardkey;
    }
    /** The serial number of a smart card holding this key or empty. */
    inline const_cstring card_number() const {
        n_assert(h);
        return h->card_number;
    }
    
    /** For ECC algoritms the name of the curve or empty. */
    inline const_cstring curve() const {
        n_assert(h);
        return h->curve;
    }
    
    inline detail::public_key_algorithm public_key_algorithm() const {
        n_assert(h);
        return to_public_key_algorithm(h->pubkey_algo);
    }
    
    inline gpgme_subkey_t native_handle() const noexcept {
        return h;
    }
    
private:
    inline subkey(gpgme_subkey_t x) noexcept
    : h(x)
    {}
    
    gpgme_subkey_t h;
    
    friend class subkey_iterator;
};

//------------------------------------------------------------------------------
class subkey_iterator : public iterator::iterator_facade<
    subkey_iterator,
    subkey,
    iterator::forward_traversal_tag,
    iterator::readable_iterator_tag,
    subkey,
    subkey*,
    ptrdiff_t>
{
public:    
    inline subkey_iterator(gpgme_subkey_t x = nullptr) noexcept
    : h(x)
    {}
    
    inline subkey dereference() const
    {
        return subkey(h);
    }
    
    inline void increment()
    {
        h = h->next;
    }
    
    inline bool equal(const subkey_iterator other) const
    {
        return h == other.h;
    }

private:
    gpgme_subkey_t h;
};

//------------------------------------------------------------------------------
using subkey_range = range::iterator_range<subkey_iterator>;

/** @} */

}}} // namespaces

#endif // NIC_BC04130D0445E8EB_NIC

