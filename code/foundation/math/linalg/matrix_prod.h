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
#ifndef NIC_4D087FE9DC1344E2_NIC
#define NIC_4D087FE9DC1344E2_NIC

#include "../vector.h"

namespace nebula { namespace foundation { namespace math { namespace linalg {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
template <class LHS>
struct matrix_prod_impl
{
    template <class RHS,
        class RET = vec::_resize<
            LHS,
            meta::seq<
                vec::_size_at<LHS, meta::size_t_<0>>,
                vec::_size_at<RHS, meta::size_t_<1>>>>>
    inline static RET apply(const LHS &lhs, const RHS &rhs)
    {
        static constexpr size_t rows = vec::_size_at<
            LHS, meta::size_t_<0>>::value;
        static constexpr size_t cols = vec::_size_at<
            RHS, meta::size_t_<1>>::value;
        static constexpr size_t K = vec::_size_at<
            LHS, meta::size_t_<1>>::value;
        
        RET r;
        for(size_t i = 0; i < rows; ++i)
        {
            for(size_t j = 0; j < cols; ++j)
            {
                r(i,j) = lhs(i,0)*rhs(0,j);
                for(size_t k = 1; k < K; ++k)
                {
                    r(i,j) += lhs(i,k)*rhs(k,j); 
                }
            }
        }
        return r;
    }
};
//------------------------------------------------------------------------------
template <class LHS, class RHS,
    class RET = vec::_resize<
        LHS,
        meta::seq<
            vec::_size_at<LHS, meta::size_t_<0>>,
            vec::_size_at<RHS, meta::size_t_<1>>>>>
inline RET matrix_prod(const LHS &lhs, const RHS &rhs)
{
    n_static_assert(
        vec::_order<LHS>::value == vec::_order<RHS>::value
        && vec::_order<LHS>::value == 2, "");
    n_static_assert(n_arg(
        meta::_equal<
            vec::_size_at<LHS, meta::size_t_<1>>,
            vec::_size_at<RHS, meta::size_t_<0>>>::value), "");
    return matrix_prod_impl<LHS>::apply(lhs, rhs);
}

/** @} */

}}}} // namespaces

#endif // NIC_4D087FE9DC1344E2_NIC

