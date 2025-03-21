// GroveEngine 2
// Copyright (C) 2020-2025 usernameak
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License, version 3, as
// published by the Free Software Foundation.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include <concepts>

namespace gtlMath2 {
    class VectorBase_Base {};

    template <int numComponents_>
    class VectorBase : public VectorBase_Base {
    public:
        static constexpr int numComponents = numComponents_;
    };

    template <typename T>
    concept VectorType = std::derived_from<T, VectorBase_Base>;

    template <typename T>
    concept NumericType = std::integral<T> || std::floating_point<T>;

    template <typename T>
    concept VectorOrNumeric = VectorType<T> || NumericType<T>;

    template <typename V, template <typename> typename T, typename U>
    T<V> VectorAs_DeductionHelper(T<U>);

    template <typename SourceVector, typename TargetVector>
    using VectorAs = decltype(VectorAs_DeductionHelper<TargetVector>(std::declval<SourceVector>()));

    template <template <typename> typename T, typename U>
        requires(VectorType<T<U>>)
    U UnderlyingNumericType_DeductionHelper(T<U>);

    template <NumericType T>
    T UnderlyingNumericType_DeductionHelper(T);

    template <VectorOrNumeric T>
    using UnderlyingNumericType = decltype(UnderlyingNumericType_DeductionHelper(std::declval<T>()));

    template <VectorType T>
    using VectorUnderlyingType = UnderlyingNumericType<T>;

    template <int N>
    struct SizedVector_Base;

    template <typename T, int N>
    using SizedVector = SizedVector_Base<N>::template type<T>;
}
